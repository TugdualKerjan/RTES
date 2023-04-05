#define IREGDIR 0 // Change the values if your register map is different than
#define IREGPIN 1
#define IREGPORT 2
#define PARIRQEN 5
#define PARIRQCLR 6
#define MODE_ALL_OUTPUT 0xFF
#define MODE_ALL_INPUT 0X00
#define ALL_IRQ_EN 0X01
#define ALL_IRQ_DIS 0X00
#define ALL_IRQ_CLR 0x01

#define SLEEP_DELAY_US (100 * 1000)

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
int snap;
static void my_isr(void *context);

int main()
{
	alt_ic_isr_register(PAR_PORT_0_IRQ_INTERRUPT_CONTROLLER_ID, PAR_PORT_0_IRQ, my_isr, NULL, NULL);
	IOWR_8DIRECT(PAR_PORT_0_BASE, IREGDIR, MODE_ALL_OUTPUT); // Selected as output
	IOWR_8DIRECT(PAR_PORT_0_BASE, IREGPORT, 0x00);
	IOWR_8DIRECT(PAR_PORT_0_BASE, PARIRQEN, ALL_IRQ_EN); // Enable IRQ on each bit
	while (1)
	{
		IOWR_8DIRECT(PAR_PORT_0_BASE, IREGPORT, 0x02);
	} // Bit2 is SET st IRQ generated
	return 0;
}

static void my_isr(void *context)
{
	IOWR_8DIRECT(PAR_PORT_0_BASE, IREGPORT, 0);
	IOWR_8DIRECT(PAR_PORT_0_BASE, PARIRQCLR, ALL_IRQ_CLR); // CLEAR IRQ
}
