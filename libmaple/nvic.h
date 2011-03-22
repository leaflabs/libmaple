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

/* NVIC Priority  */
#define NVIC_PRI_BASE       0xE000E400

/* System control registers  */
#define SCB_VTOR            0xE000ED08  // Vector table offset register

#define NVIC_BASE           0xE000E100
#define NVIC                ((nvic_reg_map*)NVIC_BASE)

typedef struct nvic_reg_map {
  __io uint32 ISER[8];                 // Interrupt Set Enable Registers
       uint32 RESERVED0[24];
  __io uint32 ICER[8];                 // Interrupt Clear Enable Registers
       uint32 RSERVED1[24];
  __io uint32 ISPR[8];                 // Interrupt Set Pending Registers
       uint32 RESERVED2[24];
  __io uint32 ICPR[8];                 // Interrupt Clear Pending Registers
       uint32 RESERVED3[24];
  __io uint32 IABR[8];                 // Interrupt Active bit Registers
       uint32 RESERVED4[56];
  __io uint8  IP[240];                 // Interrupt Priority Registers
       uint32 RESERVED5[644];
  __io uint32 STIR;                    // Software Trigger Interrupt Registers
} nvic_reg_map;

typedef enum nvic_irq_num {
    NVIC_NMI            = -14,
    NVIC_MEM_MANAGE     = -12,
    NVIC_BUS_FAULT      = -11,
    NVIC_USAGE_FAULT    = -10,
    NVIC_SVC            = -5,
    NVIC_DEBUG_MON      = -4,
    NVIC_PEND_SVC       = -2,
    NVIC_SYSTICK        = -1,

    NVIC_TIMER1_BRK     = 24,
    NVIC_TIMER1_UP      = 25,
    NVIC_TIMER1_TRG_COM = 26,
    NVIC_TIMER1_CC      = 27,
    NVIC_TIMER2         = 28,
    NVIC_TIMER3         = 29,
    NVIC_TIMER4         = 30,
    NVIC_TIMER5         = 50,
    NVIC_TIMER6         = 54,
    NVIC_TIMER7         = 55,
    NVIC_TIMER8_BRK     = 43,
    NVIC_TIMER8_UP      = 44,
    NVIC_TIMER8_TRG_COM = 45,
    NVIC_TIMER8_CC      = 46,

    NVIC_USART1         = 37,
    NVIC_USART2         = 38,
    NVIC_USART3         = 39,
    NVIC_UART4          = 52,
    NVIC_UART5          = 53,

    NVIC_EXTI0          = 6,
    NVIC_EXTI1          = 7,
    NVIC_EXTI2          = 8,
    NVIC_EXTI3          = 9,
    NVIC_EXTI4          = 10,
    NVIC_EXTI9_5        = 23,
    NVIC_EXTI15_10      = 40,

    NVIC_DMA_CH1        = 11,
    NVIC_DMA_CH2        = 12,
    NVIC_DMA_CH3        = 13,
    NVIC_DMA_CH4        = 14,
    NVIC_DMA_CH5        = 15,
    NVIC_DMA_CH6        = 16,
    NVIC_DMA_CH7        = 17,

    NVIC_I2C1_EV        = 31,
    NVIC_I2C1_ER        = 32,
    NVIC_I2C2_EV        = 33,
    NVIC_I2C2_ER        = 34
} nvic_irq_num;

#define nvic_globalirq_enable()   asm volatile("cpsie i")
#define nvic_globalirq_disable()  asm volatile("cpsid i")

void nvic_init(void);
void nvic_irq_enable(uint32 device);
void nvic_irq_disable(uint32 device);
void nvic_irq_disable_all(void);
void nvic_set_priority(int32 irqn, uint8 priority);

#ifdef __cplusplus
}
#endif

#endif

