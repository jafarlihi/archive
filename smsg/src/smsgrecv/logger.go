package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"time"
)

var LogDir string
var logFile string = "/smsc-deliveries.log"

var errCycler error

type LoggerStateSlice []LoggerState

type LoggerState struct {
	BufferedWriter  *bufio.Writer
	MessagesWritten uint32
	FlushCounter    uint16
	ReceiverID      uint8
	MessagePerFile  uint32
	FlushAfter      uint16
}

func CycleToNewLogBufferedWriter(receiverID uint8) (*bufio.Writer, error) {
	w, err := getBufferedLogWriter(getNewLogFileHandle(receiverID))
	return w, err
}

func getBufferedLogWriter(f *os.File) (*bufio.Writer, error) {
	w := bufio.NewWriter(f)
	_, err := w.WriteString("Created at " + time.Now().Format(time.RFC3339) + "\n")

	if err != nil {
		fmt.Println("\nCould not create a current logfile buffered writer.")
	}

	return w, err
}

func getNewLogFileHandle(receiverID uint8) *os.File {
	if _, err := os.Stat(LogDir); os.IsNotExist(err) {
		os.Mkdir(LogDir, 0777)
	}

	receiverSpecificLogFile := LogDir + logFile + "-" + strconv.Itoa(int(receiverID))

	if _, err := os.Stat(receiverSpecificLogFile); err == nil {
		pushBackOldLogs(receiverSpecificLogFile)
	}

	_, err := os.Create(receiverSpecificLogFile)

	if err != nil {
		fmt.Println("\nCould not create a current logfile, error: ", err)
		CleanExit()
	}

	currentF, err := os.OpenFile(receiverSpecificLogFile, os.O_RDWR, 0644)

	if err != nil {
		fmt.Println("\nCould not open a current logfile, error: ", err)
		CleanExit()
	}

	Stats.Logged_File_Count++
	return currentF
}

func pushBackOldLogs(receiverSpecificLogFile string) {
	if _, err := os.Stat(receiverSpecificLogFile); err == nil {
		err := os.Rename(receiverSpecificLogFile, receiverSpecificLogFile+"-old-"+time.Now().Format(time.RFC3339))

		if err != nil {
			fmt.Println(err)
			CleanExit()
		}
	}
}

func (logger LoggerState) LogMessage(message Message) error {
	if logger.MessagesWritten < logger.MessagePerFile {
		_, err := logger.BufferedWriter.WriteString(JSONize(message) + "\n")
		if err != nil {
			return err
		}
		logger.MessagesWritten++
	} else {
		logger.BufferedWriter.Flush()
		logger.BufferedWriter, errCycler = CycleToNewLogBufferedWriter(logger.ReceiverID)
		if errCycler != nil {
			return errCycler
		}
		logger.MessagesWritten = 0
		logger.FlushCounter = 0
		return logger.LogMessage(message)
	}

	if logger.FlushCounter < logger.FlushAfter {
		logger.FlushCounter++
	} else {
		logger.BufferedWriter.Flush()
		logger.FlushCounter = 0
	}

	return nil
}
