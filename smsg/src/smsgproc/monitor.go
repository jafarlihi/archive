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
	Dequeue        uint64
	Requeue        uint64
	Release        uint64
	DirectiveHit   map[string]uint64
	DestinationHit map[int64]int64
	Connection     int
}

var STATS StatsType
var influxClient client.Client
var podName string

func StartMonitor() {
	STATS.DirectiveHit = make(map[string]uint64)
	STATS.DestinationHit = make(map[int64]int64)

	if CONFIG.InfluxActive {
		initInflux()
		go startInflux()
	}

	LOG.Noticef("Serving statistics at http://127.0.0.1:%s/stats", strconv.Itoa(CONFIG.MonitorPort))
	http.HandleFunc("/stats", serveStatus)
	go http.ListenAndServe("127.0.0.1:"+strconv.Itoa(CONFIG.MonitorPort), nil)
}

func initInflux() {
	c, err := client.NewHTTPClient(client.HTTPConfig{
		Addr:     CONFIG.InfluxAddress,
		Username: CONFIG.InfluxUsername,
		Password: CONFIG.InfluxPassword,
	})

	if err != nil {
		LOG.Errorf("Failed to create an InfluxDB client, error: %s", err)
		CleanExit()
	}

	_, _, pingErr := c.Ping(2 * time.Second)

	if pingErr != nil {
		LOG.Errorf("Failed to ping InfluxDB, error: %s", pingErr)
		CleanExit()
	}

	podName = "smsgproc-pod-" + os.Getenv("POD_NAME")
	influxClient = c
	LOG.Noticef("Connected to the InfluxDB at %s", CONFIG.InfluxAddress)
}

func startInflux() {
	for {
		time.Sleep(time.Second * time.Duration(CONFIG.InfluxInterval))

		bp, err := client.NewBatchPoints(client.BatchPointsConfig{
			Database:  CONFIG.InfluxDB,
			Precision: "s",
		})
		if err != nil {
			LOG.Warningf("Failed to create InfluxDB BatchPoints, error: %s", err)
		}

		tags := map[string]string{"proc": podName}
		fields := map[string]interface{}{
			"dequeue":    STATS.Dequeue,
			"requeue":    STATS.Requeue,
			"release":    STATS.Release,
			"connection": len(OPENCONNS),
		}

		pt, err := client.NewPoint("proc-stats", tags, fields)
		if err != nil {
			LOG.Warningf("Error on InfluxDB NewPoint: %s", err)
		}
		bp.AddPoint(pt)
		if err := influxClient.Write(bp); err != nil {
			LOG.Warningf("Error on InfluxDB BatchPoints Write: %s", err)
		}
	}
}

func serveStatus(w http.ResponseWriter, r *http.Request) {
	STATS.Connection = len(OPENCONNS)
	json, err := json.Marshal(STATS)
	if err != nil {
		LOG.Error("[Monitor API] Could not convert Stats object to JSON. Marshal error:", err)
		//return // Trade-off, serve junk/empty data or don't respond at all
	}

	fmt.Fprintf(w, string(json))
}
