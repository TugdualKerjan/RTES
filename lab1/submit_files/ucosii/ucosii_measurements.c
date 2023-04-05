#include <stdio.h>
#include "includes.h"
#include "system.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"
/* Definition of Task Stacks */
#define TASK_STACKSIZE 2048
OS_STK task1_stk[TASK_STACKSIZE];
OS_STK task2_stk[TASK_STACKSIZE];
OS_STK task3_stk[TASK_STACKSIZE];
OS_STK task4_stk[TASK_STACKSIZE];
/* Definition of Task Priorities */
#define TASK1_PRIORITY 1
#define TASK2_PRIORITY 2
#define TASK3_PRIORITY 3
#define TASK4_PRIORITY 4
#define QUEUE_SIZE 10
OS_EVENT *sem_res;
OS_FLAG_GRP *flag_res;
OS_FLAGS flags;
OS_EVENT *mail_res;
OS_EVENT *queue_res;
//unsigned char c = 0x0f;
typedef struct {
	unsigned char button_number;
	unsigned char edge;
} msg;
msg* msg_queue[10];
msg some_msg;
unsigned int start, stop;

int flag = 0;

void task_sem(void* pdata) {
	printf("Starting task for Semaphore\n");
	INT8U err;
	while (1) {
		OSSemPend(sem_res, 0, &err);
		IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
		stop = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
		IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x0); // set bit to 0
		if (err == OS_NO_ERR)
			printf("Getting semaphore in : %u cycle\n", start - stop);
		else
			printf("Not getting semaphore\n");
	}
}
void my_isr_sem(void* context) {
	INT8U err;
	unsigned char v = IORD(NIOS_BUTTONS_BASE, 3);
	switch (v) {
	case 0x1:
		if ((IORD(NIOS_BUTTONS_BASE,0) & 0x1) == 0) {
			OSSemPost(sem_res);
			IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x2); // set bit to one
			IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
			start = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
		}
		break;
	default:
		break;
	}
	IOWR(NIOS_BUTTONS_BASE, 3, 0xf);
}

void task_flag(void* pdata) {
	INT8U err;
	printf("Starting task for Flag\n");
	while (1) {
		OSFlagPend(flag_res, 0x7, OS_FLAG_WAIT_SET_ALL, 0, &err);
		IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
		stop = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
		IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x0); // set bit to 0
		if (err == OS_NO_ERR)
			printf("Getting flag in : %u cycle\n", start - stop);
		else
			printf("Not getting flag\n");
	}
}
void my_isr_flag(void* context) {
	INT8U err;
	unsigned char v = IORD(NIOS_BUTTONS_BASE, 3);
	OSFlagPost(flag_res, v, OS_FLAG_SET, &err);
	IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
	start = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
	IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x2); // set bit to one
	IOWR(NIOS_BUTTONS_BASE, 3, 0x0f);
}
void task_mail(void* pdata) {
	INT8U err;
	msg* bla;
	printf("Starting task for PostMail\n");
	while (1) {
		bla = (msg*) OSMboxPend(mail_res, 0, &err);
		IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
		stop = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
		IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x0); // set bit to false
		if (err == OS_NO_ERR)
			printf(
					"Getting message in : %u cycles with button number %u and edge %02X\n",
					start - stop, bla->button_number, bla->edge);
		else
			printf("Not getting message\n");
	}
}

void my_isr_mail(void* context) {
	INT8U err;
	unsigned char v = IORD(NIOS_BUTTONS_BASE, 3);
	some_msg.button_number = v;
	some_msg.edge = ((IORD(NIOS_BUTTONS_BASE,0) & 0x1) == 0) ? 0x80 : 0;
	OSMboxPost(mail_res, &some_msg);
	IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
	start = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
	IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x2); // set bit to one
	IOWR(NIOS_BUTTONS_BASE, 3, 0x0f);
}

void task_queue(void* pdata) {
	INT8U err;
	msg* bla;
	printf("Starting task for QueueMail\n");
	while (1) {
		bla = (msg*) OSQPend(queue_res, 0, &err);
		IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
		stop = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
		IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x0); // set bit to zero
		if (err == OS_NO_ERR)
			printf(
					"Getting message from queue in : %u cycles with button number %u and edge %02X\n",
					start - stop, bla->button_number, bla->edge);
		else
			printf("Not getting message\n");
	}
}

void my_isr_queue(void* context) {
	unsigned char v = IORD(NIOS_BUTTONS_BASE, 3);
	some_msg.button_number = v;
	some_msg.edge = ((IORD(NIOS_BUTTONS_BASE,0) & 0x1) == 0) ? 0x80 : 0;
	OSQPost(queue_res, &some_msg);
	IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, 9);
	start = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
	IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x2); // set bit to one
	IOWR(NIOS_BUTTONS_BASE, 3, 0x0f);
}


int main(void) {
	INT8U err;
	sem_res = OSSemCreate(1);
	flag_res = OSFlagCreate(0, &err);
	mail_res = OSMboxCreate(NULL);
	queue_res = OSQCreate(msg_queue, QUEUE_SIZE);

	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, 0xffff);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, 0x0000);
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 2);
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 6);

	IOWR_8DIRECT(PAR_PORT_0_BASE, 0, 0xFF); // all output
	IOWR_8DIRECT(PAR_PORT_0_BASE, 2, 0x00); // write 0

//	alt_ic_isr_register(NIOS_BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,
//	NIOS_BUTTONS_IRQ, my_isr_sem, NULL, NULL);
//	alt_ic_isr_register(NIOS_BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,
//	NIOS_BUTTONS_IRQ, my_isr_flag, NULL, NULL);
//	alt_ic_isr_register(NIOS_BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,
//	NIOS_BUTTONS_IRQ, my_isr_mail, NULL, NULL);
	alt_ic_isr_register(NIOS_BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,
	NIOS_BUTTONS_IRQ, my_isr_queue, NULL, NULL);

	IOWR(NIOS_BUTTONS_BASE, 3, 0x0); // Clearing IRQs
	IOWR(NIOS_BUTTONS_BASE, 2, 0xf); // Activating IRQ on all buttons

	printf("Creating tasks\n");
//	printf("Button value: %d\n", IORD(NIOS_BUTTONS_BASE, 0));
//	printf("Button IR mask: %d\n", IORD(NIOS_BUTTONS_BASE, 2));
//	printf("Button ECR: %d\n", IORD(NIOS_BUTTONS_BASE, 3));
//	OSTaskCreateExt(task_sem,
//	NULL, (void *) &task1_stk[TASK_STACKSIZE - 1],
//	TASK1_PRIORITY,
//	TASK1_PRIORITY, task1_stk,
//	TASK_STACKSIZE,
//	NULL, 0);

//	OSTaskCreateExt(task_flag,
//	NULL, (void *) &task2_stk[TASK_STACKSIZE - 1],
//	TASK2_PRIORITY,
//	TASK2_PRIORITY, task2_stk,
//	TASK_STACKSIZE,
//	NULL, 0);

//	OSTaskCreateExt(task_mail,
//	NULL, (void *) &task3_stk[TASK_STACKSIZE - 1],
//	TASK3_PRIORITY,
//	TASK3_PRIORITY, task3_stk,
//	TASK_STACKSIZE,
//	NULL, 0);

	OSTaskCreateExt(task_queue,
	NULL, (void *) &task4_stk[TASK_STACKSIZE - 1],
	TASK4_PRIORITY,
	TASK4_PRIORITY, task4_stk,
	TASK_STACKSIZE,
	NULL, 0);
	OSStart();
	return 0;
}
