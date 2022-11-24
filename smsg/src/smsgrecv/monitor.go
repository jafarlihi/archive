package main

import (
	"encoding/json"
	"fmt"
	"github.com/influxdata/influxdb/client/v2"
	"net/http"
	"os"
	"strconv"
	"time"
)

type StatsType struct {
	Status                string
	Deliver_Sm_Count      uint64
	Requeue_Expired_Hits  uint64
	Redis_Enqueue_Count   uint64
	SMPP_Connection_Count uint8
	Logged_File_Count     uint32
	Configuration         *Configuration
}

var Stats StatsType
var influxClient client.Client
var podName string

func InitMonitor(port uint16, config *Configuration) {
	portS := strconv.FormatUint(uint64(port), 10)
	Stats.Configuration = config

	if config.InfluxActive {
		initInflux(config)
		go startInflux(config)
	}

	fmt.Println("\nServing monitor stats via HTTP at port", portS)

	http.HandleFunc("/", serveStatus)
	http.ListenAndServe(":"+portS, nil)
}

func initInflux(config *Configuration) {
	c, err := client.NewHTTPClient(client.HTTPConfig{
		Addr:     config.InfluxAddress,
		Username: config.InfluxUsername,
		Password: config.InfluxPassword,
	})

	if err != nil {
		fmt.Println("Failed to create an InfluxDB client, error:", err)
		CleanExit()
	}

	_, _, pingErr := c.Ping(2 * time.Second)

	if pingErr != nil {
		fmt.Println("Failed to ping InfluxDB, error:", pingErr)
		CleanExit()
	}

	podName = "smsgrecv-pod-" + os.Getenv("POD_NAME")
	influxClient = c
	fmt.Println("Connected to the InfluxDB at", config.InfluxAddress)
}

func startInflux(config *Configuration) {
	for {
		time.Sleep(time.Second * time.Duration(config.InfluxInterval))

		bp, err := client.NewBatchPoints(client.BatchPointsConfig{
			Database:  config.InfluxDB,
			Precision: "s",
		})
		if err != nil {
			fmt.Println("Warning: Failed to create InfluxDB BatchPoints, error:", err)
		}

		tags := map[string]string{"recv": podName}
		fields := map[string]interface{}{
			"deliverSm":      Stats.Deliver_Sm_Count,
			"enqueue":        Stats.Redis_Enqueue_Count,
			"requeueExpired": Stats.Requeue_Expired_Hits,
			"smppConnection": len(Receivers),
		}

		pt, err := client.NewPoint("recv-stats", tags, fields)
		if err != nil {
			fmt.Println("Error on InfluxDB NewPoint:", err)
		}
		bp.AddPoint(pt)
		if err := influxClient.Write(bp); err != nil {
			fmt.Println("Error on InfluxDB BatchPoints Write:", err)
		}
	}
}

func serveStatus(w http.ResponseWriter, r *http.Request) {
	Stats.Status = "OK"                                 // You could put some conditionals here
	Stats.SMPP_Connection_Count = uint8(len(Receivers)) // TODO: Either delete inactive receiver from Receivers or find another way of showing activated vs. connected connections.

	json, err := json.Marshal(Stats)
	if err != nil {
		fmt.Println("Failed to JSON marshal the Stats var for monitoring API:", err)
		return
	}

	fmt.Fprintf(w, string(json))
}
