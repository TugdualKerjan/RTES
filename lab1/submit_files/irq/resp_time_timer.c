#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "counter_macros.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>

static void my_isr(void *context);
int flag;
int snap;

int main()
{
  alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, my_isr,
                      NULL, NULL);
  flag = 0;                                               // Flag is a global variable
  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0);      // Clear control register
  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 2);      // Continuous mode ON
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, 0xFFFF); // Set initial value
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, 0x00FF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 3); // Enable timer interrupt
  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 7); // Start timer
  while (1)
  {
    // Normal program routine HERE…
    if (flag)
    {
      alt_printf("0x%x,\n", 0xffff - snap + 1);
      flag = 0;
      IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 7); // Enable IRQ and Start
    }
  };
  return 0;
}

static void my_isr(void *context)
{
  IOWR_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE, ARBITVAL);
  snap = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_0_BASE);
  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0); // Clear interrupt (ITO)
  IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);  // CLEAR TO
  flag = 1;                                          // Flag is a global variable
}
