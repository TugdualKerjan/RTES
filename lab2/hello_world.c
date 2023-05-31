#include "system.h"
#include "stdint.h"
#include "altera_avalon_performance_counter.h"
#include "io.h"
#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
	((byte)&0x80 ? '1' : '0'),     \
		((byte)&0x40 ? '1' : '0'), \
		((byte)&0x20 ? '1' : '0'), \
		((byte)&0x10 ? '1' : '0'), \
		((byte)&0x08 ? '1' : '0'), \
		((byte)&0x04 ? '1' : '0'), \
		((byte)&0x02 ? '1' : '0'), \
		((byte)&0x01 ? '1' : '0')

#define FUNCTION_ACCEL 1
#define FUNCTION_ACCEL2 4

#define FUNCTION_CUSTOM 2
#define FUNCTION_C 3


void calculAccel(uint32_t *input_address, uint32_t *result_address,
				 uint32_t length)
{
	// Ecrit l'adresse de base de la zone à calculer
	IOWR_32DIRECT(ACCEL_0_BASE, 0 * 4, input_address);
	// Ecrit la longueur
	IOWR_32DIRECT(ACCEL_0_BASE, 1 * 4, result_address);
	IOWR_32DIRECT(ACCEL_0_BASE, 2 * 4, length);
	// IRQEN = 0x1 and clrdone = 0x4
	IOWR_32DIRECT(ACCEL_0_BASE, 3 * 4, 1);
}

void calculCustom(uint32_t input_value, uint32_t *result_address)
{
	*result_address = ALT_CI_CUSTOM_INSTRUCTION_0(input_value, 0); // don't use B
}

void calculC(uint32_t input, uint32_t *result2)
{
	uint32_t a_swap = ((input & 0xff000000) >> 24) | ((input & 0x000000ff) << 24);
	uint32_t mask2 = 0x00800000;
	for (int i = 15; i >= 1; i = i - 2)
	{
		a_swap = ((input & mask2) >> i) | a_swap;
		mask2 = (uint32_t)mask2 >> 1;
	}
	mask2 = 0x00000100;
	for (int i = 15; i >= 1; i = i - 2)
	{
		a_swap = ((input & mask2) << i) | a_swap;
		mask2 = (uint32_t)mask2 << 1;
	}
	*result2 = a_swap;
}

uint32_t a = 0x000ff000;
uint32_t resultAccel = 0;
uint32_t resultCustom = 0;
uint32_t resultC = 0;

static void my_isr(void *context)
{
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL);
	IOWR_32DIRECT(ACCEL_0_BASE, 3, 8); // reset
		PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL);

}

int main(void)
{
	alt_ic_isr_register(ACCEL_0_IRQ_INTERRUPT_CONTROLLER_ID, ACCEL_0_IRQ,
						my_isr, NULL, NULL);

	PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
	PERF_START_MEASURING(PERFORMANCE_COUNTER_0_BASE);

	for (uint32_t i = 0; i < (2 << 16); i++)
	{
		// a = i;
		// printf("%d\n", a);
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL);
		calculAccel(&i, &resultAccel, 1);
		PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_ACCEL);
		while (IORD_32DIRECT(ACCEL_0_BASE, 3 * 4) & 2 == 0)
		{
		}

		// PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_CUSTOM);
		// calculCustom(i, &resultCustom);
		// PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_CUSTOM);

		// PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, FUNCTION_C);
		// calculC(i, &resultC);
		// PERF_END(PERFORMANCE_COUNTER_0_BASE, FUNCTION_C);
		// if (resultAccel != resultCustom || resultAccel != resultC)
		// {
		// 	printf("Error: %d, %d, %d\n", resultAccel, resultCustom, resultC);
		// }
	}

	PERF_STOP_MEASURING(PERFORMANCE_COUNTER_0_BASE);
	perf_print_formatted_report(PERFORMANCE_COUNTER_0_BASE, 50000000, 3, "Accelerator", "Custom", "C", "Accel2");

	return 0;
}
