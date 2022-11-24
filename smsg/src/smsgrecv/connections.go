package main

import (
	"fmt"
	smpp "github.com/fiorix/go-smpp/smpp"
	pdu "github.com/fiorix/go-smpp/smpp/pdu"
	"strconv"
	"sync"
	"time"
)

type ReceiverSlice []Receiver
type Receiver struct {
	RX *smpp.Receiver
	ID uint8
	CN SMPPConnection
	CH chan pdu.Body
	CS <-chan smpp.ConnStatus
}

var loopGuillotine chan uint8
var wg sync.WaitGroup

func (connectionList SMPPConnectionSlice) ConnectToActivated() {
	loopGuillotine = make(chan uint8)

	for conn := range connectionList {
		if connectionList[conn].Active == true {
			fmt.Printf("\nSMPP connection ID#%d is activated. Attempting connection...", connectionList[conn].ID)
			rx, rc, cs := connectionList[conn].connect()

			if rx == nil {
				continue
			}

			Receivers = append(Receivers, Receiver{ID: connectionList[conn].ID,
				CN: connectionList[conn],
				RX: rx,
				CH: rc,
				CS: cs})
		} else {
			fmt.Printf("\nSMPP connection ID#%d is NOT activated. Skipping...", connectionList[conn].ID)
		}
	}

	if len(Receivers) < 1 {
		fmt.Println("\nNo connections were established.")
		CleanExit()
	}
}

func (receivers ReceiverSlice) UnbindAll() {
	for receiver := range receivers {
		receivers[receiver].RX.Close()
	}
}

func (receivers ReceiverSlice) ListenToAll(redisClient RedisClient) {
	if len(receivers) > 0 {
		for receiver := range receivers {
			if receivers[receiver].RX != nil {
				wg.Add(1)
				go receivers[receiver].listen(redisClient)
			}
		}
	}

	wg.Wait()
	CleanExit()
}

func (receiver Receiver) healthWatch() {
	for c := range receiver.CS {
		switch c.Status() {
		case smpp.Connected:
			fmt.Println("Connection appears to be up. No further action is required.")
		default:
			fmt.Println("Connection appears to be down. Attempting reconnection...")
			rx, rc, cs := receiver.CN.connect()

			if rx == nil {
				loopGuillotine <- receiver.ID
				continue
			}

			receiver := Receiver{ID: receiver.ID,
				CN: receiver.CN,
				RX: rx,
				CH: rc,
				CS: cs}

			Receivers = append(Receivers, receiver)

			wg.Add(1)
			go receiver.listen(RedisC)

			loopGuillotine <- receiver.ID
		}
	}
}

func (receiver Receiver) listen(redisClient RedisClient) {
	defer wg.Done()

	var logger *LoggerState
	for loggerC := range Loggers {
		if Loggers[loggerC].ReceiverID == receiver.ID {
			logger = &Loggers[loggerC]
		}
	}

	go receiver.healthWatch()

loop:
	for {
		select {
		case m := <-receiver.CH:
			switch m.Header().ID.String() {
			case "DeliverSM":
				Stats.Deliver_Sm_Count++

				fmt.Println(m.Header())

				m_fm := m.Fields()
				source, _ := strconv.ParseUint(m_fm["source_addr"].String(), 10, 64)
				destination, _ := strconv.ParseUint(m_fm["destination_addr"].String(), 10, 64)

				message := Message{Source: source,
					Destination: destination,
					Content:     m_fm["short_message"].String()}

				fmt.Println(message)

				errLogger := logger.LogMessage(message)
				if errLogger != nil {
					fmt.Println("\nError occured while trying to log a received message:", errLogger)
				}

				errOperator := Operate(redisClient, message)
				if errOperator != nil {
					fmt.Println("\nError on message-to-Redis delivery process:", errOperator)
				}
			default:
				fmt.Println("Non-DeliverSm PDU received:", m.Header())
			}
		case beheadedLoop := <-loopGuillotine:
			if receiver.ID == beheadedLoop {
				break loop
			}
		}
	}
}

func (details *SMPPConnection) connect() (*smpp.Receiver, chan pdu.Body, <-chan smpp.ConnStatus) {
	rc := make(chan pdu.Body)
	r := &smpp.Receiver{
		Addr:        details.Address,
		User:        details.Username,
		Passwd:      details.Password,
		SystemType:  details.SystemType,
		EnquireLink: time.Duration(time.Duration(details.Eli) * time.Second),
		Handler:     func(p pdu.Body) { rc <- p },
	}

	conn := r.Bind()

	for c := range conn {
		switch c.Status() {
		case smpp.Connected:
			fmt.Printf("\nSuccessfully connected to SMSC ID#%d", details.ID)
			return r, rc, conn
		default:
			fmt.Println("\nCould not connect to SMSC ID#%d: %s", details.ID, c.Error())
			return nil, nil, nil
		}
	}

	return nil, nil, nil
}
