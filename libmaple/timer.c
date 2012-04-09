/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file   libmaple/timer.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Portable timer routines.
 */

#include <libmaple/timer.h>

static void disable_channel(timer_dev *dev, uint8 channel);
static void pwm_mode(timer_dev *dev, uint8 channel);
static void output_compare_mode(timer_dev *dev, uint8 channel);

static inline void enable_irq(timer_dev *dev, uint8 interrupt);

/**
 * Initialize a timer, and reset its register map.
 * @param dev Timer to initialize
 */
void timer_init(timer_dev *dev) {
    rcc_clk_enable(dev->clk_id);
    rcc_reset_dev(dev->clk_id);
}

/**
 * @brief Disable a timer.
 *
 * The timer will stop counting, all DMA requests and interrupts will
 * be disabled, and no state changes will be output.
 *
 * @param dev Timer to disable.
 */
void timer_disable(timer_dev *dev) {
    (dev->regs).bas->CR1 = 0;
    (dev->regs).bas->DIER = 0;
    switch (dev->type) {
    case TIMER_ADVANCED:        /* fall-through */
    case TIMER_GENERAL:
        (dev->regs).gen->CCER = 0;
        break;
    case TIMER_BASIC:
        break;
    }
}

/**
 * Sets the mode of an individual timer channel.
 *
 * Note that not all timers can be configured in every mode.  For
 * example, basic timers cannot be configured to output compare mode.
 * Be sure to use a timer which is appropriate for the mode you want.
 *
 * @param dev Timer whose channel mode to set
 * @param channel Relevant channel
 * @param mode New timer mode for channel
 */
void timer_set_mode(timer_dev *dev, uint8 channel, timer_mode mode) {
    ASSERT_FAULT(channel > 0 && channel <= 4);

    /* TODO decide about the basic timers */
    ASSERT(dev->type != TIMER_BASIC);
    if (dev->type == TIMER_BASIC)
        return;

    switch (mode) {
    case TIMER_DISABLED:
        disable_channel(dev, channel);
        break;
    case TIMER_PWM:
        pwm_mode(dev, channel);
        break;
    case TIMER_OUTPUT_COMPARE:
        output_compare_mode(dev, channel);
        break;
    }
}

/**
 * @brief Attach a timer interrupt.
 * @param dev Timer device
 * @param interrupt Interrupt number to attach to; this may be any
 *                  timer_interrupt_id or timer_channel value appropriate
 *                  for the timer.
 * @param handler Handler to attach to the given interrupt.
 * @see timer_interrupt_id
 * @see timer_channel
 */
void timer_attach_interrupt(timer_dev *dev,
                            uint8 interrupt,
                            voidFuncPtr handler) {
    dev->handlers[interrupt] = handler;
    timer_enable_irq(dev, interrupt);
    enable_irq(dev, interrupt);
}

/**
 * @brief Detach a timer interrupt.
 * @param dev Timer device
 * @param interrupt Interrupt number to detach; this may be any
 *                  timer_interrupt_id or timer_channel value appropriate
 *                  for the timer.
 * @see timer_interrupt_id
 * @see timer_channel
 */
void timer_detach_interrupt(timer_dev *dev, uint8 interrupt) {
    timer_disable_irq(dev, interrupt);
    dev->handlers[interrupt] = NULL;
}

/*
 * Utilities
 */

static void disable_channel(timer_dev *dev, uint8 channel) {
    timer_detach_interrupt(dev, channel);
    timer_cc_disable(dev, channel);
}

static void pwm_mode(timer_dev *dev, uint8 channel) {
    timer_disable_irq(dev, channel);
    timer_oc_set_mode(dev, channel, TIMER_OC_MODE_PWM_1, TIMER_OC_PE);
    timer_cc_enable(dev, channel);
}

static void output_compare_mode(timer_dev *dev, uint8 channel) {
    timer_oc_set_mode(dev, channel, TIMER_OC_MODE_ACTIVE_ON_MATCH, 0);
    timer_cc_enable(dev, channel);
}

static void enable_adv_irq(timer_dev *dev, timer_interrupt_id id);
static void enable_bas_gen_irq(timer_dev *dev);

static inline void enable_irq(timer_dev *dev, timer_interrupt_id iid) {
    if (dev->type == TIMER_ADVANCED) {
        enable_adv_irq(dev, iid);
    } else {
        enable_bas_gen_irq(dev);
    }
}

/* Advanced control timers have several IRQ lines corresponding to
 * different timer interrupts.
 *
 * Note: This function assumes that the only advanced timers are TIM1
 * and TIM8, and needs the obvious changes if that assumption is
 * violated by a later STM32 series. */
static void enable_adv_irq(timer_dev *dev, timer_interrupt_id id) {
    uint8 is_tim1 = dev->clk_id == RCC_TIMER1;
    nvic_irq_num irq_num;
    switch (id) {
    case TIMER_UPDATE_INTERRUPT:
        irq_num = (is_tim1 ?
                   NVIC_TIMER1_UP_TIMER10 :
                   NVIC_TIMER8_UP_TIMER13);
        break;
    case TIMER_CC1_INTERRUPT:   /* Fall through */
    case TIMER_CC2_INTERRUPT:   /* ... */
    case TIMER_CC3_INTERRUPT:   /* ... */
    case TIMER_CC4_INTERRUPT:
        irq_num = is_tim1 ? NVIC_TIMER1_CC : NVIC_TIMER8_CC;
        break;
    case TIMER_COM_INTERRUPT:   /* Fall through */
    case TIMER_TRG_INTERRUPT:
        irq_num = (is_tim1 ?
                   NVIC_TIMER1_TRG_COM_TIMER11 :
                   NVIC_TIMER8_TRG_COM_TIMER14);
        break;
    case TIMER_BREAK_INTERRUPT:
        irq_num = (is_tim1 ?
                   NVIC_TIMER1_BRK_TIMER9 :
                   NVIC_TIMER8_BRK_TIMER12);
        break;
    default:
        /* Can't happen, but placate the compiler */
        ASSERT(0);
        return;
    }
    nvic_irq_enable(irq_num);
}

/* Basic and general purpose timers have a single IRQ line, which is
 * shared by all interrupts supported by a particular timer. */
static void enable_bas_gen_irq(timer_dev *dev) {
    nvic_irq_num irq_num;
    switch (dev->clk_id) {
    case RCC_TIMER2:
        irq_num = NVIC_TIMER2;
        break;
    case RCC_TIMER3:
        irq_num = NVIC_TIMER3;
        break;
    case RCC_TIMER4:
        irq_num = NVIC_TIMER4;
        break;
    case RCC_TIMER5:
        irq_num = NVIC_TIMER5;
        break;
    case RCC_TIMER6:
        irq_num = NVIC_TIMER6;
        break;
    case RCC_TIMER7:
        irq_num = NVIC_TIMER7;
        break;
    case RCC_TIMER9:
        irq_num = NVIC_TIMER1_BRK_TIMER9;
        break;
    case RCC_TIMER10:
        irq_num = NVIC_TIMER1_UP_TIMER10;
        break;
    case RCC_TIMER11:
        irq_num = NVIC_TIMER1_TRG_COM_TIMER11;
        break;
    case RCC_TIMER12:
        irq_num = NVIC_TIMER8_BRK_TIMER12;
        break;
    case RCC_TIMER13:
        irq_num = NVIC_TIMER8_UP_TIMER13;
        break;
    case RCC_TIMER14:
        irq_num = NVIC_TIMER8_TRG_COM_TIMER14;
        break;
    default:
        ASSERT_FAULT(0);
        return;
    }
    nvic_irq_enable(irq_num);
}
