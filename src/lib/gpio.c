#include "wiring.h"
#include "stm32f10x_rcc.h"
#include "gpio.h"
#include "util.h"

void gpio_init(void) {
   /* Turn on clocks for GPIO  */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                          RCC_APB2Periph_GPIOB |
                          RCC_APB2Periph_GPIOC |
                          RCC_APB2Periph_AFIO, 
                          ENABLE);
}

