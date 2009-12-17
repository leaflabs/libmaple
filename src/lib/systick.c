#include "systick.h"

#define MILLIS_INC 1

volatile uint32_t systick_timer_overflow_count = 0;
volatile uint32_t systick_timer_millis = 0;
static uint8_t systick_timer_fract = 0;

void systick_init(void) {
    /* Set the reload counter to tick every 1ms  */
    SYSTICK_RELOAD = MAPLE_RELOAD_VAL;

    /* Clock the system timer with the core clock
     * and turn it on, interrrupt every 1ms to keep track of millis()*/
    SYSTICK_CSR = SYSTICK_SRC_HCLK |
                  SYSTICK_ENABLE   |
                  SYSTICK_TICKINT;
}

void SysTickHandler(void)
{
   uint32_t m = systick_timer_millis;
   uint8_t f = systick_timer_fract;

   m += MILLIS_INC;
   systick_timer_millis = m;
   systick_timer_overflow_count++;
}


