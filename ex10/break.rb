command = "./ex10"

# Anything above 19368 single character command
# line arguments and we get an Errno::E2BIG
# exception raised.
19368.times do |i|
  command << " #{i}"
end

exec(command)
