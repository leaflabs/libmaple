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
 *  Created: 12/18/09 02:36:47
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file nvic.h
 *
 *  @brief Nested interrupt controller defines and prototypes
 */

#ifndef _NVIC_H_
#define _NVIC_H_

#define NVIC_INT_USBHP      19
#define NVIC_INT_USBLP      20
#define NVIC_EXTI1_OFFSET   (NVIC_ISER0 + 0x07)
#define NVIC_EXTI9_5_OFFSET (NVIC_ISER0 + 0x17)

/* NVIC Interrupt Enable registers  */
#define NVIC_ISER0          0xE000E100
#define NVIC_ISER1          0xE000E104
#define NVIC_ISER2          0xE000E108
#define NVIC_ISER3          0xE000E10C

/* NVIC Interrupt Clear registers  */
#define NVIC_ICER0          0xE000E180
#define NVIC_ICER1          0xE000E184
#define NVIC_ICER2          0xE000E188
#define NVIC_ICER3          0xE000E18C

/* System control registers  */
#define SCB_VTOR            0xE000ED08  // Vector table offset register

#define NVIC_VectTab_RAM             ((u32)0x20000000)
#define NVIC_VectTab_FLASH           ((u32)0x08000000)

#define NVIC_NR_INTERRUPTS        60

#ifdef __cplusplus
extern "C"{
#endif

void nvic_disable_interrupts(void);
void nvic_enable_interrupt(uint32);

#ifdef __cplusplus
}
#endif


#endif

