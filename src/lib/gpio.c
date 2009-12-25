/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created: 12/18/09 02:35:49
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file gpio.c
 *
 *  @brief GPIO initialization routine
 */

#include "libmaple.h"
#include "stm32f10x_rcc.h"
#include "gpio.h"

void gpio_init(void) {
   /* Turn on clocks for GPIO  */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                          RCC_APB2Periph_GPIOB |
                          RCC_APB2Periph_GPIOC |
                          RCC_APB2Periph_AFIO,
                          ENABLE);
}

void gpio_set_mode(GPIO_Port* port, uint8 gpio_pin, uint8 mode) {
    uint32_t tmp;
    uint32_t shift = POS(gpio_pin % 8);
    GPIOReg CR;

    ASSERT(port);
    ASSERT(gpio_pin < 16);

    CR = (gpio_pin < 8) ? &(port->CRL) : &(port->CRH);

    tmp = *CR;
    tmp &= POS_MASK(shift);
    tmp |= mode << shift;

    *CR = tmp;
}
