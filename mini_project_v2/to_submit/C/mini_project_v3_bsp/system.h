/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'soc_system'
 * SOPC Builder design path: /home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/soc_system.sopcinfo
 *
 * Generated: Sun Jun 04 13:43:34 CEST 2023
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x04000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x04000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ACCEL_AVERAGE
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PERFORMANCE_COUNTER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x40010f8
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x40010f8
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x40010f8
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "soc_system"


/*
 * accel_average_0 configuration
 *
 */

#define ACCEL_AVERAGE_0_BASE 0x40010e0
#define ACCEL_AVERAGE_0_IRQ 0
#define ACCEL_AVERAGE_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ACCEL_AVERAGE_0_NAME "/dev/accel_average_0"
#define ACCEL_AVERAGE_0_SPAN 16
#define ACCEL_AVERAGE_0_TYPE "accel_average"
#define ALT_MODULE_CLASS_accel_average_0 accel_average


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK TIMER_0


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x40010f8
#define JTAG_UART_0_IRQ 1
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * nios_hex_0 configuration
 *
 */

#define ALT_MODULE_CLASS_nios_hex_0 altera_avalon_pio
#define NIOS_HEX_0_BASE 0x40010b0
#define NIOS_HEX_0_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_HEX_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_HEX_0_CAPTURE 0
#define NIOS_HEX_0_DATA_WIDTH 7
#define NIOS_HEX_0_DO_TEST_BENCH_WIRING 0
#define NIOS_HEX_0_DRIVEN_SIM_VALUE 0
#define NIOS_HEX_0_EDGE_TYPE "NONE"
#define NIOS_HEX_0_FREQ 50000000
#define NIOS_HEX_0_HAS_IN 0
#define NIOS_HEX_0_HAS_OUT 1
#define NIOS_HEX_0_HAS_TRI 0
#define NIOS_HEX_0_IRQ -1
#define NIOS_HEX_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_HEX_0_IRQ_TYPE "NONE"
#define NIOS_HEX_0_NAME "/dev/nios_hex_0"
#define NIOS_HEX_0_RESET_VALUE 0
#define NIOS_HEX_0_SPAN 16
#define NIOS_HEX_0_TYPE "altera_avalon_pio"


/*
 * nios_hex_1 configuration
 *
 */

#define ALT_MODULE_CLASS_nios_hex_1 altera_avalon_pio
#define NIOS_HEX_1_BASE 0x40010a0
#define NIOS_HEX_1_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_HEX_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_HEX_1_CAPTURE 0
#define NIOS_HEX_1_DATA_WIDTH 7
#define NIOS_HEX_1_DO_TEST_BENCH_WIRING 0
#define NIOS_HEX_1_DRIVEN_SIM_VALUE 0
#define NIOS_HEX_1_EDGE_TYPE "NONE"
#define NIOS_HEX_1_FREQ 50000000
#define NIOS_HEX_1_HAS_IN 0
#define NIOS_HEX_1_HAS_OUT 1
#define NIOS_HEX_1_HAS_TRI 0
#define NIOS_HEX_1_IRQ -1
#define NIOS_HEX_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_HEX_1_IRQ_TYPE "NONE"
#define NIOS_HEX_1_NAME "/dev/nios_hex_1"
#define NIOS_HEX_1_RESET_VALUE 0
#define NIOS_HEX_1_SPAN 16
#define NIOS_HEX_1_TYPE "altera_avalon_pio"


/*
 * nios_hex_2 configuration
 *
 */

#define ALT_MODULE_CLASS_nios_hex_2 altera_avalon_pio
#define NIOS_HEX_2_BASE 0x4001090
#define NIOS_HEX_2_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_HEX_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_HEX_2_CAPTURE 0
#define NIOS_HEX_2_DATA_WIDTH 7
#define NIOS_HEX_2_DO_TEST_BENCH_WIRING 0
#define NIOS_HEX_2_DRIVEN_SIM_VALUE 0
#define NIOS_HEX_2_EDGE_TYPE "NONE"
#define NIOS_HEX_2_FREQ 50000000
#define NIOS_HEX_2_HAS_IN 0
#define NIOS_HEX_2_HAS_OUT 1
#define NIOS_HEX_2_HAS_TRI 0
#define NIOS_HEX_2_IRQ -1
#define NIOS_HEX_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_HEX_2_IRQ_TYPE "NONE"
#define NIOS_HEX_2_NAME "/dev/nios_hex_2"
#define NIOS_HEX_2_RESET_VALUE 0
#define NIOS_HEX_2_SPAN 16
#define NIOS_HEX_2_TYPE "altera_avalon_pio"


/*
 * nios_hex_3 configuration
 *
 */

#define ALT_MODULE_CLASS_nios_hex_3 altera_avalon_pio
#define NIOS_HEX_3_BASE 0x4001080
#define NIOS_HEX_3_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_HEX_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_HEX_3_CAPTURE 0
#define NIOS_HEX_3_DATA_WIDTH 7
#define NIOS_HEX_3_DO_TEST_BENCH_WIRING 0
#define NIOS_HEX_3_DRIVEN_SIM_VALUE 0
#define NIOS_HEX_3_EDGE_TYPE "NONE"
#define NIOS_HEX_3_FREQ 50000000
#define NIOS_HEX_3_HAS_IN 0
#define NIOS_HEX_3_HAS_OUT 1
#define NIOS_HEX_3_HAS_TRI 0
#define NIOS_HEX_3_IRQ -1
#define NIOS_HEX_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_HEX_3_IRQ_TYPE "NONE"
#define NIOS_HEX_3_NAME "/dev/nios_hex_3"
#define NIOS_HEX_3_RESET_VALUE 0
#define NIOS_HEX_3_SPAN 16
#define NIOS_HEX_3_TYPE "altera_avalon_pio"


/*
 * nios_hex_4 configuration
 *
 */

#define ALT_MODULE_CLASS_nios_hex_4 altera_avalon_pio
#define NIOS_HEX_4_BASE 0x4001070
#define NIOS_HEX_4_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_HEX_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_HEX_4_CAPTURE 0
#define NIOS_HEX_4_DATA_WIDTH 7
#define NIOS_HEX_4_DO_TEST_BENCH_WIRING 0
#define NIOS_HEX_4_DRIVEN_SIM_VALUE 0
#define NIOS_HEX_4_EDGE_TYPE "NONE"
#define NIOS_HEX_4_FREQ 50000000
#define NIOS_HEX_4_HAS_IN 0
#define NIOS_HEX_4_HAS_OUT 1
#define NIOS_HEX_4_HAS_TRI 0
#define NIOS_HEX_4_IRQ -1
#define NIOS_HEX_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_HEX_4_IRQ_TYPE "NONE"
#define NIOS_HEX_4_NAME "/dev/nios_hex_4"
#define NIOS_HEX_4_RESET_VALUE 0
#define NIOS_HEX_4_SPAN 16
#define NIOS_HEX_4_TYPE "altera_avalon_pio"


/*
 * nios_hex_5 configuration
 *
 */

#define ALT_MODULE_CLASS_nios_hex_5 altera_avalon_pio
#define NIOS_HEX_5_BASE 0x4001060
#define NIOS_HEX_5_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_HEX_5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_HEX_5_CAPTURE 0
#define NIOS_HEX_5_DATA_WIDTH 7
#define NIOS_HEX_5_DO_TEST_BENCH_WIRING 0
#define NIOS_HEX_5_DRIVEN_SIM_VALUE 0
#define NIOS_HEX_5_EDGE_TYPE "NONE"
#define NIOS_HEX_5_FREQ 50000000
#define NIOS_HEX_5_HAS_IN 0
#define NIOS_HEX_5_HAS_OUT 1
#define NIOS_HEX_5_HAS_TRI 0
#define NIOS_HEX_5_IRQ -1
#define NIOS_HEX_5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_HEX_5_IRQ_TYPE "NONE"
#define NIOS_HEX_5_NAME "/dev/nios_hex_5"
#define NIOS_HEX_5_RESET_VALUE 0
#define NIOS_HEX_5_SPAN 16
#define NIOS_HEX_5_TYPE "altera_avalon_pio"


/*
 * nios_leds configuration
 *
 */

#define ALT_MODULE_CLASS_nios_leds altera_avalon_pio
#define NIOS_LEDS_BASE 0x40010c0
#define NIOS_LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_LEDS_CAPTURE 0
#define NIOS_LEDS_DATA_WIDTH 10
#define NIOS_LEDS_DO_TEST_BENCH_WIRING 0
#define NIOS_LEDS_DRIVEN_SIM_VALUE 0
#define NIOS_LEDS_EDGE_TYPE "NONE"
#define NIOS_LEDS_FREQ 50000000
#define NIOS_LEDS_HAS_IN 0
#define NIOS_LEDS_HAS_OUT 1
#define NIOS_LEDS_HAS_TRI 0
#define NIOS_LEDS_IRQ -1
#define NIOS_LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_LEDS_IRQ_TYPE "NONE"
#define NIOS_LEDS_NAME "/dev/nios_leds"
#define NIOS_LEDS_RESET_VALUE 0
#define NIOS_LEDS_SPAN 16
#define NIOS_LEDS_TYPE "altera_avalon_pio"


/*
 * nios_switches configuration
 *
 */

#define ALT_MODULE_CLASS_nios_switches altera_avalon_pio
#define NIOS_SWITCHES_BASE 0x40010d0
#define NIOS_SWITCHES_BIT_CLEARING_EDGE_REGISTER 0
#define NIOS_SWITCHES_BIT_MODIFYING_OUTPUT_REGISTER 0
#define NIOS_SWITCHES_CAPTURE 0
#define NIOS_SWITCHES_DATA_WIDTH 10
#define NIOS_SWITCHES_DO_TEST_BENCH_WIRING 0
#define NIOS_SWITCHES_DRIVEN_SIM_VALUE 0
#define NIOS_SWITCHES_EDGE_TYPE "NONE"
#define NIOS_SWITCHES_FREQ 50000000
#define NIOS_SWITCHES_HAS_IN 1
#define NIOS_SWITCHES_HAS_OUT 0
#define NIOS_SWITCHES_HAS_TRI 0
#define NIOS_SWITCHES_IRQ -1
#define NIOS_SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID -1
#define NIOS_SWITCHES_IRQ_TYPE "NONE"
#define NIOS_SWITCHES_NAME "/dev/nios_switches"
#define NIOS_SWITCHES_RESET_VALUE 0
#define NIOS_SWITCHES_SPAN 16
#define NIOS_SWITCHES_TYPE "altera_avalon_pio"


/*
 * performance_counter_0 configuration
 *
 */

#define ALT_MODULE_CLASS_performance_counter_0 altera_avalon_performance_counter
#define PERFORMANCE_COUNTER_0_BASE 0x4001000
#define PERFORMANCE_COUNTER_0_HOW_MANY_SECTIONS 3
#define PERFORMANCE_COUNTER_0_IRQ -1
#define PERFORMANCE_COUNTER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PERFORMANCE_COUNTER_0_NAME "/dev/performance_counter_0"
#define PERFORMANCE_COUNTER_0_SPAN 64
#define PERFORMANCE_COUNTER_0_TYPE "altera_avalon_performance_counter"


/*
 * sdram_controller_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sdram_controller_0 altera_avalon_new_sdram_controller
#define SDRAM_CONTROLLER_0_BASE 0x0
#define SDRAM_CONTROLLER_0_CAS_LATENCY 3
#define SDRAM_CONTROLLER_0_CONTENTS_INFO
#define SDRAM_CONTROLLER_0_INIT_NOP_DELAY 0.0
#define SDRAM_CONTROLLER_0_INIT_REFRESH_COMMANDS 2
#define SDRAM_CONTROLLER_0_IRQ -1
#define SDRAM_CONTROLLER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_CONTROLLER_0_IS_INITIALIZED 1
#define SDRAM_CONTROLLER_0_NAME "/dev/sdram_controller_0"
#define SDRAM_CONTROLLER_0_POWERUP_DELAY 100.0
#define SDRAM_CONTROLLER_0_REFRESH_PERIOD 7.8125
#define SDRAM_CONTROLLER_0_REGISTER_DATA_IN 1
#define SDRAM_CONTROLLER_0_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_CONTROLLER_0_SDRAM_BANK_WIDTH 2
#define SDRAM_CONTROLLER_0_SDRAM_COL_WIDTH 10
#define SDRAM_CONTROLLER_0_SDRAM_DATA_WIDTH 16
#define SDRAM_CONTROLLER_0_SDRAM_NUM_BANKS 4
#define SDRAM_CONTROLLER_0_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_CONTROLLER_0_SDRAM_ROW_WIDTH 13
#define SDRAM_CONTROLLER_0_SHARED_DATA 0
#define SDRAM_CONTROLLER_0_SIM_MODEL_BASE 0
#define SDRAM_CONTROLLER_0_SPAN 67108864
#define SDRAM_CONTROLLER_0_STARVATION_INDICATOR 0
#define SDRAM_CONTROLLER_0_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_CONTROLLER_0_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_CONTROLLER_0_T_AC 5.4
#define SDRAM_CONTROLLER_0_T_MRD 3
#define SDRAM_CONTROLLER_0_T_RCD 15.0
#define SDRAM_CONTROLLER_0_T_RFC 70.0
#define SDRAM_CONTROLLER_0_T_RP 15.0
#define SDRAM_CONTROLLER_0_T_WR 14.0


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x40010f0
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1685877809
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x4001040
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 2
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * ucosii configuration
 *
 */

#define OS_ARG_CHK_EN 1
#define OS_CPU_HOOKS_EN 1
#define OS_DEBUG_EN 1
#define OS_EVENT_NAME_SIZE 32
#define OS_FLAGS_NBITS 16
#define OS_FLAG_ACCEPT_EN 1
#define OS_FLAG_DEL_EN 1
#define OS_FLAG_EN 1
#define OS_FLAG_NAME_SIZE 32
#define OS_FLAG_QUERY_EN 1
#define OS_FLAG_WAIT_CLR_EN 1
#define OS_LOWEST_PRIO 20
#define OS_MAX_EVENTS 60
#define OS_MAX_FLAGS 20
#define OS_MAX_MEM_PART 60
#define OS_MAX_QS 20
#define OS_MAX_TASKS 10
#define OS_MBOX_ACCEPT_EN 1
#define OS_MBOX_DEL_EN 1
#define OS_MBOX_EN 1
#define OS_MBOX_POST_EN 1
#define OS_MBOX_POST_OPT_EN 1
#define OS_MBOX_QUERY_EN 1
#define OS_MEM_EN 1
#define OS_MEM_NAME_SIZE 32
#define OS_MEM_QUERY_EN 1
#define OS_MUTEX_ACCEPT_EN 1
#define OS_MUTEX_DEL_EN 1
#define OS_MUTEX_EN 1
#define OS_MUTEX_QUERY_EN 1
#define OS_Q_ACCEPT_EN 1
#define OS_Q_DEL_EN 1
#define OS_Q_EN 1
#define OS_Q_FLUSH_EN 1
#define OS_Q_POST_EN 1
#define OS_Q_POST_FRONT_EN 1
#define OS_Q_POST_OPT_EN 1
#define OS_Q_QUERY_EN 1
#define OS_SCHED_LOCK_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_DEL_EN 1
#define OS_SEM_EN 1
#define OS_SEM_QUERY_EN 1
#define OS_SEM_SET_EN 1
#define OS_TASK_CHANGE_PRIO_EN 1
#define OS_TASK_CREATE_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_IDLE_STK_SIZE 512
#define OS_TASK_NAME_SIZE 32
#define OS_TASK_PROFILE_EN 1
#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_STAT_STK_CHK_EN 1
#define OS_TASK_STAT_STK_SIZE 512
#define OS_TASK_SUSPEND_EN 1
#define OS_TASK_SW_HOOK_EN 1
#define OS_TASK_TMR_PRIO 0
#define OS_TASK_TMR_STK_SIZE 512
#define OS_THREAD_SAFE_NEWLIB 1
#define OS_TICKS_PER_SEC TIMER_0_TICKS_PER_SEC
#define OS_TICK_STEP_EN 1
#define OS_TIME_DLY_HMSM_EN 1
#define OS_TIME_DLY_RESUME_EN 1
#define OS_TIME_GET_SET_EN 1
#define OS_TIME_TICK_HOOK_EN 1
#define OS_TMR_CFG_MAX 16
#define OS_TMR_CFG_NAME_SIZE 16
#define OS_TMR_CFG_TICKS_PER_SEC 10
#define OS_TMR_CFG_WHEEL_SIZE 2
#define OS_TMR_EN 0

#endif /* __SYSTEM_H_ */
