package main

import (
	"encoding/json"
	"fmt"
	redis "github.com/go-redis/redis"
	uuid "github.com/satori/go.uuid"
)

type Message struct {
	Source      uint64
	Destination uint64
	Content     string
}

func JSONize(message Message) string {
	json, err := json.Marshal(message)
	if err != nil {
		fmt.Println("\nFailed to JSONize a message: ", err)
		return ""
	}
	return string(json)
}

func Operate(client *redis.Client, message Message) error {
	uuid := uuid.NewV4()
	uuidString := uuid.String()
	_, err := client.EvalSha(ScriptDigests["enqueue.lua"], []string{uuidString, JSONize(message)}).Result()

	if err == nil {
		Stats.Redis_Enqueue_Count++
	}

	return err
}
