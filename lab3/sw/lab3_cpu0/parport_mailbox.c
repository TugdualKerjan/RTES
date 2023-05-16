
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

void receive_callback(void *message) {
  if (!message) {
    printf("Received successfully.\n");
  } else {
    printf("Error while receiving!\n");
  }
}

/* Take mutex then increase counter */
void task1(void *pdata) {
  printf("CPU0 waiting to receive a message:\n");
  // Fetch mailbox
  altera_avalon_mailbox_dev *mailbox =
      altera_avalon_mailbox_open(MAILBOX_SIMPLE_1_NAME, NULL, receive_callback);
  // Message storage array
  alt_u32 mail[2];
  altera_avalon_mailbox_retrieve_poll(mailbox, mail, 0);
  alt_dcache_flush_all();
  char *msg_ptr = (void *)mail[1];
  printf("Received message with contents: ");
  for (int i = 0; i < mail[0]; i++) {
    printf("%c", msg_ptr[i]);
  }
  printf("\n");
  // Close mailbox
  altera_avalon_mailbox_close(mailbox);
}

/* The main function creates two task and starts multi-tasking */
int main(void) {
  OSTaskCreateExt(task1, NULL, (void *)&task1_stk[TASK_STACKSIZE - 1],
                  TASK1_PRIORITY, TASK1_PRIORITY, task1_stk, TASK_STACKSIZE,
                  NULL, 0);
  OSStart();
  return 0;
}
