# Lab 1
Nathan PELUSO & Tugdual KERJAN

# Part I: Interrupts measurements - Latency, Response Time, Recovery time
## Configurations
- NIOS processor version "II/f"
- Clock: 50 MHz for all components except 100MHz PLL for SDRAM (when relevant)
- SDRAM (when relevant): 16bits width, 4 banks, 13 rows x 10 cols, Memory size = 64 Mbytes
- ROM/RAM (when relevant): 32bits width, 262144 bytes, RAM (writeable)
- I Cache (when relevant): 4Kby for both SDRAM and RAM/ROM
- D Cache (when relevant): 2Kby  for both SDRAM and RAM/ROM

## Components
### Custom ParallelPort
[Code for ParallelPort](submit_files/parallel.vhd)
### Custom Counter
[Code for Counter](submit_files/Counter.vhd)

## Measurements
### Latency
Using *Signal Tap Logic Analyzer*, a trigger is included in the compiled file to start recording on rising edges of `soc_system:u0|ParallelPort:par_port_0|IRQ` signal, which we then analyze to find how many cycles are spent between the IRQ and the first loaded PC (signal `soc_system:u0|soc_system_nios2_gen2_0:nios2_gen2_0|soc_system_nios2_gen2_0_cpu:cpu|Nios II Inst Address`).
### Response time
Three techniques are used to measure the response time:
- "Timer": Using a Timer component from the library: the ISR sets a flag and launches a timer, which is read once back in the main routine.
- "Counter": Similarly, using a Custom Counter component that throws an interrupt when reaching its set "max value", but continues to count: once the main routine resumes, the current counter value is read (and we substract max_value from it).
- "ParallelPort": The main routine continuously sets a bit to '1' on a PIO exported to a GPIO (to which a SALEA logic analyzer is connected), the ISR clears the interrupt and sets it back to 0. The time at 1-level is the response time.

### Recovery time
Three methods are used to measure recovery time:
- "Counter & Timer": The Timer is used as interrupt source: once thrown, the Counter is started. In the main routine, as soon as the counter value is non-zero we print it: we obtain a measurement of the recovery cycles.
- "Counter & ParallelPort": Similarly, but using the ParallelPort as IRQ source.
- "ParallelPort": Using the previously defined "ParallelPort" response time measurement method, the time spent at 0-level gives us the recovery time value.


## Results
|I Cache|D Cache|SDRAM|Interrupt latency|Response Time|Recovery Time|
|:-:|:-:|:-:|:-|:-|:-|
|X|X|X|10 cycles => 0.2µs|(Timer) 0x85 => 2.66µs <br>(Counter) 0x79 => 2.4µs <br> (ParallelPort) 2.56 µs|(Counter & Timer) 0x3a => 1.16µs <br> (Counter & ParallelPort) 0x3a => 1.16µs <br>  (ParallelPort) 1.04 µs |
|X||X|11 cycles=> 0.22µs|(Timer) 0x227 => 11.0µs<br>(Counter) 0x194 => 8.08µs<br>(ParallelPort) 7.18µs|(Counter & Timer) 0x18a => 7.88µs<br>(Counter & ParallelPort) 0x183 => 7.74µs<br>(ParallelPort) 7.16µs|
|||X| 34 cycles => 6.8µs|(Timer) 0x694 => 33.7µs<br>(Counter) 0x43f => 21.7µs<br>(ParallelPort) 25.88µs|(Counter & Timer) 0x384 => 18.0µs<br>(Counter & ParallelPort) 0x3b4 => 19.0µs<br>(ParallelPort) 19.64µs|
|X|X||  8 cycles => 0.16µs|(Timer)  0xc0 => 3.84µs<br>(Counter)  0x92 => 2.92µs<br>(ParallelPort) 2.48µs|(Counter & Timer) 0x58 => 1.76 µs<br>(Counter & ParallelPort) 0x59 => 1.78µs<br>(ParallelPort) 1.88µs|
|X||| 8 cycles => 0.16µs|(Timer)  0x119 => 5.62µs<br>(Counter)  0xc9=> 4.02 µs<br>(ParallelPort) 4.06µs|(Counter & Timer) 0x94 => 2.96µs<br>(Counter & ParallelPort) 0x97 => 3.02µs<br>(ParallelPort) 2.98µs|
|||| 14 cycles => 0.28µs|(Timer) 0x27a => 12.7µs<br>(Counter)  0x19d => 8.26 µs<br>(ParallelPort) 9.78 µs|(Counter & Timer)  0x13f => 6.38 µs<br>(Counter & ParallelPort) 0x14e => 6.68 µs<br>(ParallelPort) 6.9µs|

### Interpretation
First of all, using on-chip memory seems to be faster than using SDRAM, for all measurements and cache settings. Regarding caches, the Instruction cache seems to bring a considerable optimization, especially regarding latency and response time. The Data cache also brings better performance, with less impact on latency time.

# Part 2 - µC-OSII
## Configuration
- NIOS processor version "II/f"
- Clock: 50 MHz for all components
- ROM/RAM: 32bits width, 262144 bytes, RAM (writeable)
- I Cache: 4Kby (RAM)
- D Cache: 2Kby (RAM)

## Code used
[Code for µC-OSII measurements](ucosii_measurements.c)

## Semaphore
Using timer: 536 cycles,10.7 µs  
Using logic analyzer: 10.6µs  

## Flags
OS_FLAG_WAIT_SET_ANY+OS_FLAG_CONSUME: 529 cycles, 10.6µs (timer) | 11.4µs (logic analyzer)
OS_FLAG_WAIT_SET_ALL: Very high variance, depends on time to press all buttons.

## Mail
Using timer: 570 cycles => 11.4µs
Using logic analyzer: 11.2µs

## Queue
Using timer: 564 cycles => 11.3µs
Using logic analyzer: 11.1µs

## Summary
All communication primitives seem to offer similar levels of performance, slighly slower for Mail & Queue primitives.
This seems logical, given that these primitives rely on more complex logic.

We observe that the time needed for those primitives to be passed is comparable to the total overhead of exception handling (latency+response+recovery) in similar cache settings: around 10-15µs per signal.



