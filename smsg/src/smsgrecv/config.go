package main

import (
	"fmt"
	"gopkg.in/yaml.v2"
	"io/ioutil"
)

type SMPPConnectionSlice []SMPPConnection

type SMPPConnection struct {
	ID         uint8  `yaml:"id"`
	Active     bool   `yaml:"active"`
	Address    string `yaml:"address"`
	Eli        int    `yaml:"eli"`
	SystemType string `yaml:"systemType"`
	Username   string `yaml:"username"`
	Password   string `yaml:"password"`
}

type Configuration struct {
	SMPP_Connections                    SMPPConnectionSlice `yaml:"smpp_connections"`
	Monitor_Port                        uint16              `yaml:"monitor_port"`
	Redis_Connection_Type               string              `yaml:"redis_connection_type"`
	Redis_Address                       string              `yaml:"redis_address"`
	Redis_Password                      string              `yaml:"redis_passwrd"`
	Redis_Database_Number               int                 `yaml:"redis_database_number"`
	InfluxActive                        bool                `yaml:"influxdb_active"`
	InfluxInterval                      int                 `yaml:"influxdb_insert_interval_seconds"`
	InfluxConnType                      string              `yaml:"influxdb_connection_type"`
	InfluxAddress                       string              `yaml:"influxdb_address"`
	InfluxUsername                      string              `yaml:"influxdb_username"`
	InfluxPassword                      string              `yaml:"influxdb_password"`
	InfluxDB                            string              `yaml:"influxdb_database"`
	Requeue_Messages_After_Milliseconds uint32              `yaml:"requeue_messages_after_ms"`
	Loggers_Message_Per_File            uint32              `yaml:"loggers_message_per_file"`
	Loggers_Flush_After                 uint16              `yaml:"loggers_flush_after"`
}

func LoadConfiguration(file string) Configuration {
	var config Configuration

	configFile, err := ioutil.ReadFile(file)
	if err != nil {
		fmt.Println("Failed to read the config file. Error:", err)
		CleanExit()
	}

	umErr := yaml.Unmarshal(configFile, &config)
	if umErr != nil {
		fmt.Println("Failed to unmarshal the config file. Error:", umErr)
		CleanExit()
	}

	return config
}
