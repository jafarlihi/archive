package main

import (
	"fmt"
	"github.com/op/go-logging"
	"os"
	"os/signal"
	"syscall"
)

func CleanExit() {
	fmt.Println("\nExiting.")
	os.Exit(1)
}

var LOG = logging.MustGetLogger("smsgproc")
var FORMAT = logging.MustStringFormatter(
	`%{color}%{time:15:04:05.000} ▶ %{level:.4s} %{id:03x}%{color:reset} %{message}`,
)

func main() {
	c := make(chan os.Signal, 2)
	signal.Notify(c, os.Interrupt, syscall.SIGTERM)
	go func() {
		<-c
		CleanExit()
	}()

	loggerBackend := logging.NewLogBackend(os.Stderr, "", 0)
	loggerBackendFormatter := logging.NewBackendFormatter(loggerBackend, FORMAT)
	logging.SetBackend(loggerBackendFormatter)

	if len(os.Args) != 2 {
		LOG.Error("Only 1 argument specifying the config file path is required.")
		CleanExit()
	}

	LOG.Info("Passed parameters:", os.Args)

	LoadConfiguration(os.Args[1])

	InitRedis()
	InitConnections()

	StartMonitor()
	StartProcessor()

	CleanExit()
}
