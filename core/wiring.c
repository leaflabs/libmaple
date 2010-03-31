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
 *  Created: 12/18/09 02:41:47
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file wiring.c
 *
 *  @brief
 */

#include "wiring.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"
#include "rcc.h"
#include "systick.h"
#include "gpio.h"

void NVIC_Configuration(void);

void init(void) {
   rcc_init();
   NVIC_Configuration();
   systick_init();
   gpio_init();
   adc_init();
   timer_init(1, 1);
   timer_init(2, 1);
   timer_init(3, 1);
   timer_init(4, 1);
}

void NVIC_Configuration(void) {
#ifdef VECT_TAB_ROM
   NVIC_SetVectorTable(USER_ADDR_ROM, 0x0);
#warning writing to ROM
#elif defined VECT_TAB_RAM
   NVIC_SetVectorTable(USER_ADDR_RAM, 0x0);
#warning writing to RAM
#else // VECT_TAB_BASE
   /* Set the Vector Table base location at 0x08000000 */
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}

