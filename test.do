restart
force -freeze sim:/custom_accel_swap/Clk 1 0, 0 {10000 ps} -r 20ns

force sim:/custom_accel_swap/nReset 0
force sim:/custom_accel_swap/sChipSelect 1
force sim:/custom_accel_swap/sRead 0
force sim:/custom_accel_swap/sWrite 0
run 20ns



# RZ
force sim:/custom_accel_swap/nReset 1
run 20ns

## First Iteration

# SrcAddr
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#00
force {sim:/custom_accel_swap/sWriteData[31:0]} 16#AAAAAAAA
run 20ns

# DestAddr
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#01
force {sim:/custom_accel_swap/sWriteData[31:0]} 16#BBBBBBBBB
run 20ns

# Ln
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#10
force {sim:/custom_accel_swap/sWriteData[31:0]} 10#4
run 20ns

# START w IRQ
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
force {sim:/custom_accel_swap/sWriteData[31:0]} 2#0101
#force sim:/mWaitRequest 1
run 20ns

# WAIT
force sim:/custom_accel_swap/sWrite 0
force sim:/custom_accel_swap/sRead 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
run 20ns

# Memory answer (once only)
force {sim:/mReadData[31:0]} 16#AABBCCDD
force sim:/mWaitRequest 0
run 40ns

# WAIT for accel answer
#force sim:/mWaitRequest 1
force sim:/custom_accel_swap/sWrite 0
force sim:/custom_accel_swap/sRead 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
run 40ns

# Accept incoming
#force sim:/mWaitRequest 0
run 20ns

# Continue
#force sim:/mWaitRequest 1
force sim:/custom_accel_swap/sWrite 0
force sim:/custom_accel_swap/sRead 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
run 700ns

# Clear IRQ & disable IRQ
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
force {sim:/custom_accel_swap/sWriteData[31:0]} 2#1000
#force sim:/mWaitRequest 1
run 20ns

## Second Iteration

# SrcAddr
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#00
force {sim:/custom_accel_swap/sWriteData[31:0]} 16#0
run 20ns

# DestAddr
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#01
force {sim:/custom_accel_swap/sWriteData[31:0]} 16#01
run 20ns

# Ln
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#10
force {sim:/custom_accel_swap/sWriteData[31:0]} 10#2
run 20ns

# START w IRQ
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
force {sim:/custom_accel_swap/sWriteData[31:0]} 2#0101
#force sim:/mWaitRequest 1
run 20ns

# WAIT
force sim:/custom_accel_swap/sWrite 0
force sim:/custom_accel_swap/sRead 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
run 20ns

# Memory answer (once only)
force {sim:/mReadData[31:0]} 16#dd33ddaa
force sim:/mWaitRequest 0
run 40ns

# WAIT for accel answer
#force sim:/mWaitRequest 1
force sim:/custom_accel_swap/sWrite 0
force sim:/custom_accel_swap/sRead 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
run 40ns

# Accept incoming
#force sim:/mWaitRequest 0
run 20ns

# Continue
#force sim:/mWaitRequest 1
force sim:/custom_accel_swap/sWrite 0
force sim:/custom_accel_swap/sRead 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
run 250ns

# Clear IRQ & disable IRQ
force sim:/custom_accel_swap/sWrite 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
force {sim:/custom_accel_swap/sWriteData[31:0]} 2#1000
#force sim:/mWaitRequest 1
run 20ns

# WAIT read status
#force sim:/mWaitRequest 1
force sim:/custom_accel_swap/sWrite 0
force sim:/custom_accel_swap/sRead 1
force {sim:/custom_accel_swap/sAddress[1:0]} 2#11
run 20ns
