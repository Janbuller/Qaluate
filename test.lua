local Q = require("Qaluate")
Q.Init()

while true do
    io.write("Calculate> ")
    local cmd = io.read();

    print(Q.CalcString(cmd, 2000))
end
