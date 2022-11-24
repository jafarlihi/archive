package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
)

var RedisC RedisClient
var Receivers ReceiverSlice
var Loggers LoggerStateSlice

func CleanExit() {
	Receivers.UnbindAll()
	for logger := range Loggers {
		Loggers[logger].BufferedWriter.Flush()
	}
	fmt.Println("\nExiting.")
	os.Exit(1)
}

func main() {
	c := make(chan os.Signal, 2)
	signal.Notify(c, os.Interrupt, syscall.SIGTERM, syscall.SIGINT, syscall.SIGQUIT, syscall.SIGABRT, syscall.SIGKILL)
	go func() {
		<-c
		CleanExit()
	}()

	if len(os.Args) != 3 {
		fmt.Println("Please pass exactly two fullpath arguments, first specifying config file location, and second the logging directory.")
		CleanExit()
	}

	fmt.Println("Passed parameters:", os.Args)

	config := LoadConfiguration(os.Args[1])
	LogDir = os.Args[2]

	RedisC = InitRedis(config)
	config.SMPP_Connections.ConnectToActivated()

	for receiver := range Receivers {
		id := Receivers[receiver].ID
		bw, errCycler := CycleToNewLogBufferedWriter(id)

		if errCycler != nil {
			fmt.Println("\nError getting a buffered log writer: ", errCycler)
			CleanExit()
		}

		logger := LoggerState{BufferedWriter: bw,
			MessagesWritten: 0, FlushCounter: 0, ReceiverID: id,
			MessagePerFile: config.Loggers_Message_Per_File,
			FlushAfter:     config.Loggers_Flush_After}

		Loggers = append(Loggers, logger)
	}

	go InitMonitor(config.Monitor_Port, &config)

	Receivers.ListenToAll(RedisC)
}
