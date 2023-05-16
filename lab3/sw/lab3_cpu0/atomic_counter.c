#include "altera_avalon_mailbox_simple.h"
#include "io.h"
#include "system.h"
#include <altera_avalon_mutex.h>
#include <altera_avalon_performance_counter.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* ---------------------- CPU_0 Code ---------------------- */

/* Definition of Task Stacks */
#define TASK_STACKSIZE 2048
OS_STK task1_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define TASK1_PRIORITY 1

/* Take mutex then increase counter */
void task1(void *pdata) {
  // Set performance counter
  PERF_RESET(CPU_0_PERFORMANCE_COUNTER_0_BASE);
  PERF_START_MEASURING(CPU_0_PERFORMANCE_COUNTER_0_BASE);

  // Limit number of iterations
  for (int i = 0; i < 500; i++) {
    // Start measuring
    PERF_BEGIN(CPU_0_PERFORMANCE_COUNTER_0_BASE, 1);
    // Increment
    IOWR_8DIRECT(ATOMIC_COUNTER_0_BASE, 1, 1);
    // Stop measuring
    PERF_END(CPU_0_PERFORMANCE_COUNTER_0_BASE, 1);
    // Read value
    printf("Value read: %d\n", IORD_8DIRECT(ATOMIC_COUNTER_0_BASE, 0));
    // Wait
    OSTimeDlyHMSM(0, 0, 0, 20);
  }
  PERF_STOP_MEASURING(CPU_0_PERFORMANCE_COUNTER_0_BASE);
  perf_print_formatted_report(CPU_0_PERFORMANCE_COUNTER_0_BASE,
                              alt_get_cpu_freq(), 1,
                              "Time to increment/decrement");
}

/* The main function creates two task and starts multi-tasking */
int main(void) {
  // Setup start value
  IOWR_8DIRECT(ATOMIC_COUNTER_0_BASE, 0, 0);

  OSTaskCreateExt(task1, NULL, (void *)&task1_stk[TASK_STACKSIZE - 1],
                  TASK1_PRIORITY, TASK1_PRIORITY, task1_stk, TASK_STACKSIZE,
                  NULL, 0);
  OSStart();
  return 0;
}