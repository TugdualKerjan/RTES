#include "system.h"
#include "stdint.h"
#include "altera_avalon_performance_counter.h"
#include "io.h"
#include <stdio.h>
#include "num_disp.h"
#include "calculs.h"
#include "sys/alt_irq.h"
#include "io.h"
#include "system.h"

#define FUNCTION_ACCEL_SETUP 1
#define FUNCTION_ACCEL_ISR 2
#define FUNCTION_ACCEL_NO_ISR 3
#define FUNCTION_C 4
static void my_isr(void *context) {
	PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL_ISR);
	IOWR_32DIRECT(ACCEL_AVERAGE_0_BASE, 3 * 4, 0b1000);
	PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL_ISR);
}

int main(void) {
	pixel img[IM_SIZE];
	pixel mean_c = { 0, 0, 0, 0 };
	pixel mean_accel = { 0, 0, 0, 0 };
	PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
	PERF_START_MEASURING(PERFORMANCE_COUNTER_0_BASE);

	// First run - test without ISR (count time to Done bit)
	for (uint32_t i = 0; i < 1024; i++) {
		for (int j = 0; j < IM_SIZE; j++) {
			img[j].r = 0xaa + i % 3;
			img[j].g = 0xbb + i % 3;
			img[j].b = 0x01 + i % 3;
		}
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL_NO_ISR);
		calculAccel(img, &mean_accel, IM_SIZE);
		while (IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 3 * 4) & 2 == 0) {
		}
		PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL_NO_ISR);
		calculC(img, &mean_c, IM_SIZE);
		if (mean_c.r != mean_accel.r || mean_c.g != mean_accel.g
				|| mean_c.b != mean_accel.b) {
			printf("Error! Different results:\n");
			printf("Obtained mean pixel (C): %x %x %x\n", mean_c.r, mean_c.g,
					mean_c.b);
			printf("Obtained mean pixel (accel, no ISR): %x %x %x\n",
					mean_accel.r, mean_accel.g, mean_accel.b);
		}
		print_pixel(mean_c, 0);
	}

	// Second run - using ISR
	// Register ISR
	alt_ic_isr_register(ACCEL_AVERAGE_0_IRQ_INTERRUPT_CONTROLLER_ID,
	ACCEL_AVERAGE_0_IRQ, my_isr, NULL, NULL);

	for (uint32_t i = 0; i < 1024; i++) {
		for (int j = 0; j < IM_SIZE; j++) {
			img[j].r = 0xaa + i % 3;
			img[j].g = 0xbb + i % 3;
			img[j].b = 0x01 + i % 3;
		}
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL_SETUP);
		calculAccel(img, &mean_accel, IM_SIZE);
		PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL_SETUP);
		while (IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 3 * 4) & 2 == 0) {
		}

		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_C);
		calculC(img, &mean_c, IM_SIZE);
		PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_C);

		if (mean_c.r != mean_accel.r || mean_c.g != mean_accel.g
				|| mean_c.b != mean_accel.b) {
			printf("Error! Different results:\n");
			printf("Obtained mean pixel (C): %x %x %x\n", mean_c.r, mean_c.g,
					mean_c.b);
			printf("Obtained mean pixel (accel): %x %x %x\n", mean_accel.r,
					mean_accel.g, mean_accel.b);
		}
		print_pixel(mean_c, 0);
	}

	PERF_STOP_MEASURING(PERFORMANCE_COUNTER_0_BASE);
	perf_print_formatted_report((void*) PERFORMANCE_COUNTER_0_BASE, 50000000, 4,
			"Acc Setup", "Acc ISR", "Acc no ISR", "C");

	return 0;
}
