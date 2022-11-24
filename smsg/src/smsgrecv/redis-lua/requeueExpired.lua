local zrangebyscoreResult = redis.call("ZRANGEBYSCORE", "processing", 0, ARGV[1])
if #zrangebyscoreResult == 0 then
  return 0
end

for i, result in ipairs(zrangebyscoreResult) do
  redis.call("LPUSH", "pending", result)
  redis.call("ZREM", "processing", result)
end

return #zrangebyscoreResult
