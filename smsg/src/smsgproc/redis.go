package main

import (
	"encoding/json"
	redis "github.com/go-redis/redis"
	"strconv"
	"time"
)

var REDIS *redis.Client

var dequeueHash string
var requeueHash string
var releaseHash string

func InitRedis() {
	REDIS = redis.NewClient(&redis.Options{
		Network:  CONFIG.RedisConnType,
		Addr:     CONFIG.RedisAddress,
		Password: CONFIG.RedisPassword,
		DB:       CONFIG.RedisDBNumber,
	})

	pong, err := REDIS.Ping().Result()
	if err != nil || pong != "PONG" {
		LOG.Error("Failed to connect to the Redis; Error:", err, "\nRedis ping return value (should be \"PONG\"):", pong)
		CleanExit()
	} else {
		LOG.Info("Connected to the Redis.")
	}

	loadScripts()
}

func loadScripts() {
	dequeueLoadRes, dequeueLoadErr := REDIS.ScriptLoad(dequeueScript).Result()
	if dequeueLoadRes != "" {
		dequeueHash = dequeueLoadRes
		LOG.Info("Dequeue Lua script loaded to the Redis.")
	} else {
		LOG.Error("Failed to load the dequeue Lua script to the Redis. Error:", dequeueLoadErr)
		CleanExit()
	}

	requeueLoadRes, requeueLoadErr := REDIS.ScriptLoad(requeueScript).Result()
	if requeueLoadRes != "" {
		requeueHash = requeueLoadRes
		LOG.Info("Requeue Lua script loaded to the Redis.")
	} else {
		LOG.Error("Failed to load the requeue Lua script to the Redis. Error:", requeueLoadErr)
		CleanExit()
	}

	releaseLoadRes, releaseLoadErr := REDIS.ScriptLoad(releaseScript).Result()
	if releaseLoadRes != "" {
		releaseHash = releaseLoadRes
		LOG.Info("Release Lua script loaded to the Redis.")
	} else {
		LOG.Error("Failed to load the release Lua script to the Redis. Error:", releaseLoadErr)
		CleanExit()
	}
}

func Dequeue() Message {
	for {
		res, err := REDIS.EvalSha(dequeueHash, []string{strconv.FormatInt(time.Now().UnixNano()/1000000, 10)}).Result()

		if err == nil {
			var message Message
			umErr := json.Unmarshal([]byte(res.(string)), &message)
			if umErr == nil {
				STATS.Dequeue++
				STATS.DestinationHit[message.Destination]++
				return message
			} else {
				LOG.Warning("Received data in an unexpected format from the Redis queue. Discarding item. Unmarshal error:", umErr)
			}
		}

		time.Sleep(time.Millisecond * 50)
	}
}

func Requeue(UUID string) {
	res, err := REDIS.EvalSha(requeueHash, []string{UUID}).Result()
	if err != nil || res == 0 {
		LOG.Noticef("Failed to requeue the message with UUID of %s. It might have already been released by another processor instance.", UUID)
		return
	}

	STATS.Requeue++
}

func Release(UUID string) {
	res, err := REDIS.EvalSha(releaseHash, []string{UUID}).Result()
	if err != nil || res == 0 {
		LOG.Noticef("Failed to release the message with UUID of %s. It might have already been released by another processor instance.", UUID)
		return
	}

	STATS.Release++
}

var dequeueScript string = `
local rpopResult = redis.call("RPOP", "pending")
if (rpopResult == nil or (type(rpopResult) == "boolean" and not rpopResult)) then return nil end
local zaddResult = redis.call("ZADD", "processing", KEYS[1], rpopResult)
local hgetResult = redis.call("HGET", "messages", rpopResult)
local res = cjson.decode(hgetResult)
res["UUID"] = rpopResult
return cjson.encode(res)`

var requeueScript string = `
local zremResult = redis.call("ZREM", "processing", KEYS[1])
if zremResult ~= 0 then
    local lpushResult = redis.call("LPUSH", "pending", KEYS[1])
    return 1
end
return 0`

var releaseScript string = `
local zremResult = redis.call("ZREM", "processing", KEYS[1])
if zremResult == 0 then
    zremResult = redis.call("LREM", "pending", 0, KEYS[1])
end
if zremResult ~= 0 then
    local hdelResult = redis.call("HDEL", "messages", KEYS[1])
    return 1
end
return 0`
