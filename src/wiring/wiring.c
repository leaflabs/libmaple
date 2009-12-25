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
#include "stm32f10x_rcc.h"
#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"
#include "systick.h"
#include "gpio.h"

void RCC_Configuration(void);
void NVIC_Configuration(void);

void init(void) {
   RCC_Configuration();
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                          RCC_APB2Periph_GPIOB |
                          RCC_APB2Periph_GPIOC |
                          RCC_APB2Periph_AFIO
                        , ENABLE);
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


void RCC_Configuration(void) {
   ErrorStatus HSEStartUpStatus;
   /* RCC system reset(for debug purpose) */
   RCC_DeInit();

   /* Enable HSE */
   RCC_HSEConfig(RCC_HSE_ON);

   /* Wait till HSE is ready */
   HSEStartUpStatus = RCC_WaitForHSEStartUp();

   if(HSEStartUpStatus == SUCCESS) {
      /* Enable Prefetch Buffer */
      FLASH_PrefetchBufferCmd( (u32)FLASH_PrefetchBuffer_Enable);

      /* Flash 2 wait state */
      FLASH_SetLatency(FLASH_Latency_2);

      /* HCLK = SYSCLK */
      RCC_HCLKConfig(RCC_SYSCLK_Div1);

      /* PCLK2 = HCLK APB2 Periphs, no prescaler 72MHz */
      RCC_PCLK2Config(RCC_HCLK_Div1);

      /* PCLK1 = HCLK/2 APB1 periphs = 36MHZ*/
      RCC_PCLK1Config(RCC_HCLK_Div2);

      /* PLLCLK = 8MHz * 9 = 72 MHz */
      RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

      /* Enable PLL */
      RCC_PLLCmd(ENABLE);

      /* Wait till PLL is ready */
      while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
          ;

      /* Select PLL as system clock source */
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

      /* Wait till PLL is used as system clock source */
      while(RCC_GetSYSCLKSource() != 0x08)
          ;
   }
}
