/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
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
 * @file   libmaple/stm32f1/timer.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM32F1 timer support.
 */

#include <libmaple/timer.h>
#include "timer_private.h"

/*
 * Devices
 */

/* Use timer_private macros to save typing. */
static DECLARE_ADVANCED_TIMER(timer1, 1);
static DECLARE_GENERAL_TIMER(timer2, 2);
static DECLARE_GENERAL_TIMER(timer3, 3);
static DECLARE_GENERAL_TIMER(timer4, 4);

/** Timer 1 device (advanced) */
timer_dev *TIMER1 = &timer1;
/** Timer 2 device (general-purpose) */
timer_dev *TIMER2 = &timer2;
/** Timer 3 device (general-purpose) */
timer_dev *TIMER3 = &timer3;
/** Timer 4 device (general-purpose) */
timer_dev *TIMER4 = &timer4;

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
static DECLARE_GENERAL_TIMER(timer5, 5);
static DECLARE_BASIC_TIMER(timer6, 6);
static DECLARE_BASIC_TIMER(timer7, 7);
static DECLARE_ADVANCED_TIMER(timer8, 8);

/** Timer 5 device (general-purpose) */
timer_dev *TIMER5 = &timer5;
/** Timer 6 device (basic) */
timer_dev *TIMER6 = &timer6;
/** Timer 7 device (basic) */
timer_dev *TIMER7 = &timer7;
/** Timer 8 device (advanced) */
timer_dev *TIMER8 = &timer8;
#endif

/*
 * Routines
 */

/**
 * @brief Call a function on timer devices.
 * @param fn Function to call on each timer device.
 */
void timer_foreach(void (*fn)(timer_dev*)) {
    fn(TIMER1);
    fn(TIMER2);
    fn(TIMER3);
    fn(TIMER4);
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    fn(TIMER5);
    fn(TIMER6);
    fn(TIMER7);
    fn(TIMER8);
#endif
}

/*
 * IRQ handlers
 */

void __irq_tim1_brk(void) {
    dispatch_adv_brk(TIMER1);
}

void __irq_tim1_up(void) {
    dispatch_adv_up(TIMER1);
}

void __irq_tim1_trg_com(void) {
    dispatch_adv_trg_com(TIMER1);
}

void __irq_tim1_cc(void) {
    dispatch_adv_cc(TIMER1);
}

void __irq_tim2(void) {
    dispatch_general(TIMER2);
}

void __irq_tim3(void) {
    dispatch_general(TIMER3);
}

void __irq_tim4(void) {
    dispatch_general(TIMER4);
}

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
void __irq_tim5(void) {
    dispatch_general(TIMER5);
}

void __irq_tim6(void) {
    dispatch_basic(TIMER6);
}

void __irq_tim7(void) {
    dispatch_basic(TIMER7);
}

void __irq_tim8_brk(void) {
    dispatch_adv_brk(TIMER8);
}

void __irq_tim8_up(void) {
    dispatch_adv_up(TIMER8);
}

void __irq_tim8_trg_com(void) {
    dispatch_adv_trg_com(TIMER8);
}

void __irq_tim8_cc(void) {
    dispatch_adv_cc(TIMER8);
}
#endif
