#include "altera_avalon_pio_regs.h"
#include "counter_macros.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>

int flag;
int snap;
static void my_isr(void *context);

int main()
{
	alt_ic_isr_register(MY_COUNTER_0_IRQ_INTERRUPT_CONTROLLER_ID,
						MY_COUNTER_0_IRQ, my_isr, NULL, NULL);
	flag = 0;									  // Flag is a global variable
	IOWR(MY_COUNTER_0_BASE, IRESETVAL, 0); // Reset value is loaded
	IOWR(MY_COUNTER_0_BASE, IRZ,
		 ARBITVAL); // Reset activated to load the counter with the reset value
	IOWR(MY_COUNTER_0_BASE, IIRQEN,
		 IRQENVAL);							// Enable IRQ
	IOWR(MY_COUNTER_0_BASE, MAXC, MAXCVAL); // Write suitable endval
	IOWR(MY_COUNTER_0_BASE, ISTART,
		 ARBITVAL); // Start the counter

	while (1)
	{
		// Normal program routine HERE…
		if (flag)
		{
			alt_printf("0x%x,\n", snap-MAXCVAL);
			flag = 0;
			IOWR(MY_COUNTER_0_BASE, IIRQEN,
				 IRQENVAL); // Enable the interrupt
			IOWR(MY_COUNTER_0_BASE, ISTART,
				 ARBITVAL); // Start the counter
		}
	}
	return 0;
}

static void my_isr(void *context)
{
	snap = IORD(MY_COUNTER_0_BASE, ICOUNTER);
	IOWR(MY_COUNTER_0_BASE, IIRQEN, IRQDISVAL);	 // Clear interrupt
	IOWR(MY_COUNTER_0_BASE, ICLREOT, CLREOTVAL); // Clear iEOT
	IOWR(MY_COUNTER_0_BASE, ISTOP, ARBITVAL);	 // Stop the counter
	IOWR(MY_COUNTER_0_BASE, IRZ, ARBITVAL);		 // Reset the counter
	flag = 1;									 // Flag is a global variable
}
