#include "system.h"
#include "stdint.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include "num_disp.h"
#include "calculs.h"
#include "io.h"
#include "system.h"
#include "includes.h"

/* Queue object size */
#define QUEUE_SIZE 1024

typedef struct message {
	pixel* image;
	pixel* result;
} message;

OS_EVENT *queue_res;
message* msg_queue[1024];

/* Definition of Task Stacks */
#define TASK_STACKSIZE 1024
OS_STK task1_stk[TASK_STACKSIZE];
OS_STK task2_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define TASK1_PRIORITY 1
#define TASK2_PRIORITY 2

/* ISR for accelerator: send result to display, then send next image */
void task_call_accel(void* pdata) {
	int first = 1;
	message* prev_msg = NULL;
	while (1) {
		if (prev_msg) { // skip first iteration
			while (IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 3 * 4) & 2 == 0) {
			} // wait for previous call to end, except in first iteration
//			printf("accel dest: %x, expected dest: %x\n", (void*)IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 1*4), (void*)(prev_msg->result));
			print_pixel(*(prev_msg->result), 0);
			free(prev_msg->image); // cleanup to avoid bloating memory
			free(prev_msg->result);
			free(prev_msg);
//			printf("freeing: %x %x %x\n", prev_msg, prev_msg->image, prev_msg->result);
		}
		uint8_t err;
		printf("Accel caller waiting for a message...\n");
		prev_msg = (message*) OSQPend(queue_res, 0, &err);
		if (err == OS_NO_ERR) {
			printf("Getting message from queue: %x, (%x->%x), first pix r: %x\n", prev_msg,
					prev_msg->image, prev_msg->result, (prev_msg->image)[0].r);
		} else {
			printf("Not getting message\n");
		}
		if (!prev_msg->image) {
			printf("Received end frame, exiting.\n");
			return;
		}
		calculAccel(prev_msg->image, prev_msg->result, IM_SIZE);
//		calculC(prev_msg->image, prev_msg->result, IM_SIZE);
		OSTimeDlyHMSM(0, 0, 0, 10); // small delay for visibility
	}
}

/* Generate fake images and post on Queue*/
void task_fake_camera(void* pdata) {
	uint8_t val = 1;
	printf("Camera task started...\n");
	while (val) { // Stop after 255 images ~= 8.5s
		pixel* img = (pixel*) malloc(sizeof(pixel) * IM_SIZE);
		message* msg = (message*) malloc(sizeof(message));
		pixel* dest = (pixel*) malloc(sizeof(pixel));
//		printf("Allocated: %x, %x, %x\n", msg, img, dest);
		dest->r = 0;
		dest->g = 0;
		dest->b = 0;
		dest->empty = 0;

		for (int j = 0; j < IM_SIZE; j++) {
			img[j].r = val + 1;
			img[j].g = val + 2;
			img[j].b = val + 3;
			img[j].empty = 0;
		}
		msg->image = img;
		msg->result = dest;
		printf("Posting message: %x, (%x->%x)\n", msg, msg->image, msg->result);
		OSQPost(queue_res, msg);
		OSTimeDlyHMSM(0, 0, 0, 33); // ~30fps
		val++;
	}
	printf("Posted last image, exiting\n");
	message mess = { NULL, NULL };
	OSQPost(queue_res, &mess);
}

int main(void) {
	queue_res = OSQCreate(msg_queue, QUEUE_SIZE);
	OSTaskCreateExt(task_fake_camera, NULL,
			(void *) &task1_stk[TASK_STACKSIZE - 1],
			TASK1_PRIORITY, TASK1_PRIORITY, task1_stk, TASK_STACKSIZE,
			NULL, 0);
	OSTaskCreateExt(task_call_accel, NULL,
			(void *) &task2_stk[TASK_STACKSIZE - 1],
			TASK2_PRIORITY, TASK2_PRIORITY, task2_stk, TASK_STACKSIZE,
			NULL, 0);
	printf("Starting both tasks\n");
	OSStart();

	return 0;
}
