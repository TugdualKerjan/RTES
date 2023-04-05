#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "counter_macros.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>

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

int flag;
int snap;
static void my_isr(void *context);

int main()
{
	alt_ic_isr_register(PAR_PORT_0_IRQ_INTERRUPT_CONTROLLER_ID, PAR_PORT_0_IRQ, my_isr, NULL, NULL);

	IOWR(MY_COUNTER_0_BASE, IRESETVAL, 0);		   // Reset value(0) is loaded
	IOWR(MY_COUNTER_0_BASE, IRZ, ARBITVAL);		   // Reset activated to load the counter with the reset value
	IOWR_8DIRECT(PAR_PORT_0_BASE, IREGDIR, MODE_ALL_INPUT); // Selected as output
	IOWR_8DIRECT(PAR_PORT_0_BASE, IREGPORT, 0x00);
	IOWR_8DIRECT(PAR_PORT_0_BASE, PARIRQEN, ALL_IRQ_EN); // Enable IRQ on each bit
	while (1)
	{
		IOWR_8DIRECT(PAR_PORT_0_BASE, IREGPORT, 0x02);
		while (IORD(MY_COUNTER_0_BASE, ICOUNTER) == 0)
			;
		alt_printf("0x%x,\n", IORD(MY_COUNTER_0_BASE, ICOUNTER));
		IOWR(MY_COUNTER_0_BASE, ISTOP, ARBITVAL); // Stop the counter
		IOWR(MY_COUNTER_0_BASE, IRZ, ARBITVAL);	// Reset the counter
	};
	return 0;
}

static void my_isr(void *context)
{
	IOWR_8DIRECT(PAR_PORT_0_BASE, PARIRQCLR, ALL_IRQ_CLR); // CLEAR IRQ
	IOWR(MY_COUNTER_0_BASE, ISTART, ARBITVAL);	  // Start the counter
}
