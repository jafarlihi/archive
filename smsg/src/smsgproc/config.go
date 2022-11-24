package main

import (
	"gopkg.in/yaml.v2"
	"io/ioutil"
)

type Configuration struct {
	MonitorPort    int          `yaml:"monitor_port"`
	RedisConnType  string       `yaml:"redis_connection_type"`
	RedisAddress   string       `yaml:"redis_address"`
	RedisPassword  string       `yaml:"redis_password"`
	RedisDBNumber  int          `yaml:"redis_database_number"`
	InfluxActive   bool         `yaml:"influxdb_active"`
	InfluxInterval int          `yaml:"influxdb_insert_interval_seconds"`
	InfluxConnType string       `yaml:"influxdb_connection_type"`
	InfluxAddress  string       `yaml:"influxdb_address"`
	InfluxUsername string       `yaml:"influxdb_username"`
	InfluxPassword string       `yaml:"influxdb_password"`
	InfluxDB       string       `yaml:"influxdb_database"`
	Connections    []Connection `yaml:"connections"`
	Directives     []Directive  `yaml:"directives"`
}

type Connection struct {
	ConnType   string `yaml:"connection_type"`
	Identifier string `yaml:"identifier"`
	Host       string `yaml:"host"`
	Port       int    `yaml:"port"`
	Statement  string `yaml:"statement"`
	ReqType    string `yaml:"request_type"`
	ContType   string `yaml:"content_type"`
	Path       string `yaml:"path"`
	Username   string `yaml:"username"`
	Password   string `yaml:"password"`
	Database   string `yaml:"database"`
	Sid        string `yaml:"sid"`
}

type Directive struct {
	Name   string `yaml:"name"`
	ConnID string `yaml:"connection_identifier"`
	JBD    bool   `yaml:"judge_by_destination"`
	DRS    int64  `yaml:"destination_range_start"`
	DRE    int64  `yaml:"destination_range_end"`
	JBS    bool   `yaml:"judge_by_source"`
	SRS    int64  `yaml:"source_range_start"`
	SRE    int64  `yaml:"source_range_end"`
}

var CONFIG Configuration

func LoadConfiguration(configPath string) {
	config, err := ioutil.ReadFile(configPath)
	if err != nil {
		LOG.Errorf("Failed to read the config file. Error: %s", err)
		CleanExit()
	}

	umErr := yaml.Unmarshal(config, &CONFIG)
	if umErr != nil {
		LOG.Errorf("Failed to unmarshal the config file. Error: %s", umErr)
		CleanExit()
	}

	consistencyCheck()
	LOG.Info("Config file loaded.")
}

func consistencyCheck() {
	var dircErrs map[string]string
	var connErrs []string
	var deathFlag bool = false

	dircErrs = make(map[string]string)

OuterDirc:
	for dirc := range CONFIG.Directives {
		for conn := range CONFIG.Connections {
			if CONFIG.Connections[conn].Identifier == CONFIG.Directives[dirc].ConnID {
				continue OuterDirc
			}
		}

		deathFlag = true
		dircErrs[CONFIG.Directives[dirc].Name] = CONFIG.Directives[dirc].ConnID
	}

OuterConn:
	for conn := range CONFIG.Connections {
		for dirc := range CONFIG.Directives {
			if CONFIG.Directives[dirc].ConnID == CONFIG.Connections[conn].Identifier {
				continue OuterConn
			}
		}

		deathFlag = true
		connErrs = append(connErrs, CONFIG.Connections[conn].Identifier)
	}

	for dirc, conn := range dircErrs {
		LOG.Errorf("Directive %s specifies connection_identifier %s, but such connection is not defined.", dirc, conn)
	}

	for conn := range connErrs {
		LOG.Errorf("Connection %s is defined but never used by any directives. Please comment out unused definitions from the config file.", connErrs[conn])
	}

	if deathFlag {
		CleanExit()
	}
}
