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

#define FUNCTION_C 1
#define FUNCTION_ACCEL 2

#define NB_ITER 512


int main(void) {
	pixel img[IM_SIZE];
	pixel mean_c = { 0, 0, 0, 0 };
	pixel mean_accel = { 0, 0, 0, 0 };
	PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
	PERF_START_MEASURING(PERFORMANCE_COUNTER_0_BASE);

	// First run - test without ISR (count time to Done bit)
	for (uint32_t i = 0; i < NB_ITER; i++) {
		for (int j = 0; j < IM_SIZE; j++) {
			img[j].r = 0xaa + i % 3;
			img[j].g = 0xbb + i % 3;
			img[j].b = 0x01 + i % 3;
		}
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL);
		calculAccel(img, &mean_accel, IM_SIZE);
		while (!(IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 3 * 4) & 2)) {
		}
		PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL);

		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_C);
		calculC(img, &mean_c, IM_SIZE);
		PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_C);

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
	PERF_STOP_MEASURING(PERFORMANCE_COUNTER_0_BASE);
	perf_print_formatted_report((void*) PERFORMANCE_COUNTER_0_BASE, 50000000, 2,
			"C", "Accel");

	return 0;
}
