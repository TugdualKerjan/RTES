#include "altera_avalon_mailbox_simple.h"
#include "io.h"
#include "system.h"
#include <altera_avalon_mutex.h>
#include <altera_avalon_performance_counter.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* ---------------------- CPU1 Code ---------------------- */

/* Definition of Task Stacks */
#define TASK_STACKSIZE 2048
OS_STK task1_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define TASK1_PRIORITY 1

/* Take mutex then increase counter */
void task1(void *pdata) {
  uint8_t val;
  // Fetch mutex address
  alt_mutex_dev *common_mutex = altera_avalon_mutex_open(MUTEX_0_NAME);
  // Set performance counter
  PERF_RESET(CPU_1_PERFORMANCE_COUNTER_0_BASE);
  PERF_START_MEASURING(CPU_1_PERFORMANCE_COUNTER_0_BASE);

  // Limit number of iterations
  for (int i = 0; i < 500; i++) {
    // Start measuring
    PERF_BEGIN(CPU_1_PERFORMANCE_COUNTER_0_BASE, 1);
    // Lock mutex
    altera_avalon_mutex_lock(common_mutex, 1);
    // Decrement
    val = IORD_8DIRECT(PIO_0_BASE, 0);
    IOWR_8DIRECT(PIO_0_BASE, 0, val-1);
    // Release mutex
    altera_avalon_mutex_unlock(common_mutex);
    // Stop measuring
    PERF_END(CPU_1_PERFORMANCE_COUNTER_0_BASE, 1);
    printf("Value read: %d\n", val);
    // Wait
    OSTimeDlyHMSM(0, 0, 0, 10);
  }
  PERF_STOP_MEASURING(CPU_1_PERFORMANCE_COUNTER_0_BASE);
  perf_print_formatted_report(CPU_1_PERFORMANCE_COUNTER_0_BASE,
                              alt_get_cpu_freq(), 1,
                              "Time to increment/decrement");
}

/* The main function creates two task and starts multi-tasking */
int main(void) {
  OSTaskCreateExt(task1, NULL, (void *)&task1_stk[TASK_STACKSIZE - 1],
                  TASK1_PRIORITY, TASK1_PRIORITY, task1_stk, TASK_STACKSIZE,
                  NULL, 0);
  OSStart();
  return 0;
}
