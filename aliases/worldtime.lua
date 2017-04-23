#!/usr/bin/env luajit
-- print current time in different places
local fmt       = "\t %X | %A, %d %B %Y"
local now       = os.time()
local hour      = 3600
local timezones = {
  -1, -2, -3, -5, -7, -9,
   1,  2,  3,  5,  7,  9,
   0
}
local tz_time = function(time)
  return os.date(fmt, time)
end

print("local:" .. tz_time(now))
for i, e in ipairs(timezones) do
  print(e .. tz_time(now + e * hour))
end
