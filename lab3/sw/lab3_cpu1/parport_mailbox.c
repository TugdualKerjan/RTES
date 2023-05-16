
#include "altera_avalon_mailbox_simple.h"
#include "io.h"
#include "system.h"
#include <altera_avalon_mutex.h>
#include <altera_avalon_performance_counter.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* ---------------------- CPU_1 Code ---------------------- */

/* Definition of Task Stacks */
#define TASK_STACKSIZE 2048
OS_STK task1_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define TASK1_PRIORITY 1

void send_callback(void *report, int status) {
  if (!status) {
    printf("Sent successfully.\n");
  } else {
    printf("Error while sending!\n");
  }
}

/* Take mutex then increase counter */
void task1(void *pdata) {
  printf("CPU1 sending a message:\n");
  // Fetch mailbox
  altera_avalon_mailbox_dev *mailbox =
      altera_avalon_mailbox_open(MAILBOX_SIMPLE_1_NAME, send_callback, NULL);
  // Create message structure
  alt_u32 mail[2] = {0x0, 0x0};
  // Write message
  char *msg_ptr = SDRAM_CONTROLLER_0_BASE;
  char *message = "Hello from the other side!";
  memcpy(msg_ptr, message, strlen(message) + 1);
  mail[0] = strlen(message) + 1;
  mail[1] = (alt_u32)msg_ptr;
  alt_dcache_flush_all();
  // Send message
  altera_avalon_mailbox_send(mailbox, mail, 0, POLL);
  printf("Sent message to mailbox: \n\t{%ld, %p:\"%c%c%c...\"}\n", mail[0],
         mail[1], msg_ptr[0], msg_ptr[1], msg_ptr[2]);
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
