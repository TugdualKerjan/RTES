#ifndef CALCULS
#define CALCULS

#define IM_SIZE 256
#include "io.h"
#include "system.h"
#include "includes.h"

void calculAccel(pixel image_array[IM_SIZE], pixel *result_address,
		size_t length) {
	// Ecrit l'adresse de base de la zone à calculer
	IOWR_32DIRECT(ACCEL_AVERAGE_0_BASE, 0 * 4, image_array);
	// Ecrit la longueur
	IOWR_32DIRECT(ACCEL_AVERAGE_0_BASE, 1 * 4, result_address);
	IOWR_32DIRECT(ACCEL_AVERAGE_0_BASE, 2 * 4, length);
	// ClrDone, start
	IOWR_32DIRECT(ACCEL_AVERAGE_0_BASE, 3 * 4, 0b1101);

//	// Readback (debug)
//	printf("src: %x\ndest: %x\nlen: %x\nstatus: %x\n",
//			IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 0 * 4),
//			IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 1 * 4),
//			IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 2 * 4),
//			IORD_32DIRECT(ACCEL_AVERAGE_0_BASE, 3 * 4));
}

void calculC(pixel image_array[IM_SIZE], pixel *result_address, size_t length) {
	uint32_t aggreg_r = 0, aggreg_g = 0, aggreg_b = 0;
	for (size_t i = 0; i < length; i++) {
		aggreg_r += image_array[i].r;
		aggreg_g += image_array[i].g;
		aggreg_b += image_array[i].b;
	}
	result_address->r = (uint8_t)(aggreg_r / length);
	result_address->g = (uint8_t)(aggreg_g / length);
	result_address->b = (uint8_t)(aggreg_b / length);
}

#endif
