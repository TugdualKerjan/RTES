#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
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
	alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, my_isr,
						NULL, NULL);

	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0); // Clear control register
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 2); // Continuous mode ON
	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, 0xFFFF);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, 0x00FF);
	IOWR(MY_COUNTER_0_BASE, IRESETVAL, 0);			   // Reset value(0) is loaded
	IOWR(MY_COUNTER_0_BASE, IRZ, ARBITVAL);			   // Reset activated to load the counter with the reset value
	// IOWR(MY_COUNTER_0_BASE, MAXC, MAXCVAL);			   // Write suitable endval
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 3); // Enable timer interrupt
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 7); // Start timer
	while (1)
	{
		while (IORD(MY_COUNTER_0_BASE, ICOUNTER) == 0)
		{
		}
		alt_printf("0x%x,\n", IORD(MY_COUNTER_0_BASE, ICOUNTER));
		IOWR(MY_COUNTER_0_BASE, ISTOP, ARBITVAL);		   // Stop the counter
		IOWR(MY_COUNTER_0_BASE, IRZ, ARBITVAL);			   // Reset the counter
		IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 7); // Start timer
	}
	return 0;
}

static void my_isr(void *context)
{
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0); // Clear interrupt (ITO)
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);  // CLEAR TO
	IOWR(MY_COUNTER_0_BASE, ISTART, ARBITVAL);		   // Start the counter
}
