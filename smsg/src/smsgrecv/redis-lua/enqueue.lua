local lpushResult = redis.call("LPUSH", "pending", KEYS[1])
local hsetResult = redis.call("HSET", "messages", KEYS[1], KEYS[2])

if hsetResult == 1 or hsetResult == 0 then
  if lpushResult > 0 then
    return 1
  end
end

return 0
