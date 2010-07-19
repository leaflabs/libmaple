/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/

/**
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

/* Where to put code  */
#define USER_ADDR_ROM 0x08005000
#define USER_ADDR_RAM 0x20000C00

#ifdef __cplusplus
extern "C"{
#endif

void nvic_init(void);
void nvic_disable_interrupts(void);
void nvic_enable_interrupt(uint32);
void nvic_disable_interrupt(uint32);

#ifdef __cplusplus
}
#endif

#endif

