/******************************************************************************
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
 *****************************************************************************/

/**
 * @file nvic.h
 * @brief Nested interrupt controller defines and prototypes
 */

#ifndef _NVIC_H_
#define _NVIC_H_

#ifdef __cplusplus
extern "C"{
#endif

#define NVIC_INT_USBHP      19
#define NVIC_INT_USBLP      20

/* NVIC Interrupt Enable registers  */
#define NVIC_ISER0          0xE000E100
#define NVIC_ISER1          0xE000E104
/* NVIC_ISER2 only on connectivity line */

/* NVIC Interrupt Clear registers  */
#define NVIC_ICER0          0xE000E180
#define NVIC_ICER1          0xE000E184
/* NVIC_ICER2 only on connectivity line */

/* System control registers  */
#define SCB_VTOR            0xE000ED08  // Vector table offset register

enum {
    NVIC_TIMER1       = 27,
    NVIC_TIMER2       = 28,
    NVIC_TIMER3       = 29,
    NVIC_TIMER4       = 30,
    NVIC_TIMER5       = 50,   // high density only (Maple Native, Maple Audio)
    NVIC_TIMER6       = 54,   // high density only
    NVIC_TIMER7       = 55,   // high density only
    NVIC_TIMER8       = 46,   // high density only

    NVIC_USART1       = 37,
    NVIC_USART2       = 38,
    NVIC_USART3       = 39,
    NVIC_UART4        = 52,   // high density only
    NVIC_UART5        = 53,   // high density only

    NVIC_EXTI0        = 6,
    NVIC_EXTI1        = 7,
    NVIC_EXTI2        = 8,
    NVIC_EXTI3        = 9,
    NVIC_EXTI4        = 10,
    NVIC_EXTI9_5      = 23,
    NVIC_EXTI15_10    = 40,

    NVIC_DMA_CH1      = 11,
    NVIC_DMA_CH2      = 12,
    NVIC_DMA_CH3      = 13,
    NVIC_DMA_CH4      = 14,
    NVIC_DMA_CH5      = 15,
    NVIC_DMA_CH6      = 16,
    NVIC_DMA_CH7      = 17
};


#define nvic_globalirq_enable()   asm volatile("cpsie i")
#define nvic_globalirq_disable()  asm volatile("cpsid i")

void nvic_init(void);
void nvic_irq_enable(uint32 device);
void nvic_irq_disable(uint32 device);
void nvic_irq_disable_all(void);

#ifdef __cplusplus
}
#endif

#endif

