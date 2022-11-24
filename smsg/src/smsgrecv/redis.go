package main

import (
	"fmt"
	redis "github.com/go-redis/redis"
	"io/ioutil"
	"time"
)

type RedisClient *redis.Client

var luaDirectory string = "./redis-lua/"
var luaScripts = [...]string{"enqueue.lua", "requeueExpired.lua"}
var ScriptDigests map[string]string

func InitRedis(config Configuration) *redis.Client {
	client := redis.NewClient(&redis.Options{
		Network:  config.Redis_Connection_Type,
		Addr:     config.Redis_Address,
		Password: config.Redis_Password,
		DB:       config.Redis_Database_Number,
	})

	pong, err := client.Ping().Result()

	if err != nil || pong != "PONG" {
		fmt.Println("Redis connection error:", err, " Ping return value:", pong)
		CleanExit()
	} else {
		fmt.Println("Successfully connected to Redis.")
	}

	ScriptDigests = make(map[string]string)
	loadScriptsToRedis(client)
	go watchForExpired(client, config.Requeue_Messages_After_Milliseconds)
	return client
}

func watchForExpired(client *redis.Client, ms uint32) {
	for {
		now := time.Now()
		nanosNow := now.UnixNano()
		millisNow := nanosNow / 1000000

		amountRequeued, err := client.EvalSha(ScriptDigests["requeueExpired.lua"], []string{}, millisNow-int64(ms)).Result()

		if amountRequeued != nil {
			ar := amountRequeued.(int64)
			Stats.Requeue_Expired_Hits += uint64(ar)
		}

		if err != nil {
			fmt.Println("Error returned when executing expired message requeuing script in Redis: ", err)
		}

		time.Sleep(time.Duration(ms/2) * time.Millisecond)
	}
}

func loadScriptsToRedis(client *redis.Client) {
	for script := range luaScripts {
		scriptFileContent, err := ioutil.ReadFile(luaDirectory + luaScripts[script])

		if err != nil {
			fmt.Print("\nError while reading a Lua script file named %s: %s", luaScripts[script], err)
		}

		digest, err := client.ScriptLoad(string(scriptFileContent)).Result()

		if err != nil {
			fmt.Printf("\nRedis returned an error while trying to load a LUA script named %s: %s", luaScripts[script], err)
			continue
		}

		if digest == "" {
			fmt.Printf("\nRedis didn't return a digest after trying to load a LUA script named %s", luaScripts[script])
		} else {
			ScriptDigests[luaScripts[script]] = digest
		}
	}
}
