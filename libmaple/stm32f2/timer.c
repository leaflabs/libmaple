/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file   libmaple/stm32f2/timer.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM32F2 timers.
 */

#include <libmaple/timer.h>
#include "timer_private.h"

/*
 * Devices
 *
 * Defer to the timer_private API for declaring these.
 */

static DECLARE_ADVANCED_TIMER(timer1, 1);
static DECLARE_GENERAL_TIMER(timer2, 2);
static DECLARE_GENERAL_TIMER(timer3, 3);
static DECLARE_GENERAL_TIMER(timer4, 4);
static DECLARE_GENERAL_TIMER(timer5, 5);
static DECLARE_BASIC_TIMER(timer6, 6);
static DECLARE_BASIC_TIMER(timer7, 7);
static DECLARE_ADVANCED_TIMER(timer8, 8);
/* TIM9 has UIE, CC1IE, CC2IE, TIE bits in DIER. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer9, 9, TIMER_DIER_TIE_BIT);
/* TIM10 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer10, 10, TIMER_DIER_CC1IE_BIT);
/* TIM11 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer11, 11, TIMER_DIER_CC1IE_BIT);
/* TIM12 has UIE, CC1IE, CC2IE, TIE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer12, 12, TIMER_DIER_TIE_BIT);
/* TIM13 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer13, 13, TIMER_DIER_CC1IE_BIT);
/* TIM14 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer14, 14, TIMER_DIER_CC1IE_BIT);

/** Timer 1 device (advanced) */
timer_dev *TIMER1 = &timer1;
/** Timer 2 device (general-purpose) */
timer_dev *TIMER2 = &timer2;
/** Timer 3 device (general-purpose) */
timer_dev *TIMER3 = &timer3;
/** Timer 4 device (general-purpose) */
timer_dev *TIMER4 = &timer4;
/** Timer 5 device (general-purpose) */
timer_dev *TIMER5 = &timer5;
/** Timer 6 device (basic) */
timer_dev *TIMER6 = &timer6;
/** Timer 7 device (basic) */
timer_dev *TIMER7 = &timer7;
/** Timer 8 device (advanced) */
timer_dev *TIMER8 = &timer8;
/** Timer 9 device (general-purpose) */
timer_dev *TIMER9 = &timer9;
/** Timer 10 device (general-purpose) */
timer_dev *TIMER10 = &timer10;
/** Timer 11 device (general-purpose) */
timer_dev *TIMER11 = &timer11;
/** Timer 12 device (general-purpose) */
timer_dev *TIMER12 = &timer12;
/** Timer 13 device (general-purpose) */
timer_dev *TIMER13 = &timer13;
/** Timer 14 device (general-purpose) */
timer_dev *TIMER14 = &timer14;

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
    fn(TIMER5);
    fn(TIMER6);
    fn(TIMER7);
    fn(TIMER8);
    fn(TIMER9);
    fn(TIMER10);
    fn(TIMER11);
    fn(TIMER12);
    fn(TIMER13);
    fn(TIMER14);
}

/*
 * IRQ handlers
 *
 * Defer to the timer_private dispatch API.
 */

void __irq_tim1_brk_tim9(void) {
    dispatch_adv_brk(TIMER1);
    dispatch_tim_9_12(TIMER9);
}

void __irq_tim1_up_tim10(void) {
    dispatch_adv_up(TIMER1);
    dispatch_tim_10_11_13_14(TIMER10);
}

void __irq_tim1_trg_com_tim11(void) {
    dispatch_adv_trg_com(TIMER1);
    dispatch_tim_10_11_13_14(TIMER11);
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

void __irq_tim5(void) {
    dispatch_general(TIMER5);
}

/* FIXME: this is also the DAC DMA underrun interrupt, so it needs a
 * different name (and to be supported?). */
void __irq_tim6(void) {
    dispatch_basic(TIMER6);
}

void __irq_tim7(void) {
    dispatch_basic(TIMER7);
}

void __irq_tim8_brk_tim12(void) {
    dispatch_adv_brk(TIMER8);
    dispatch_tim_9_12(TIMER12);
}

void __irq_tim8_up_tim13(void) {
    dispatch_adv_up(TIMER8);
    dispatch_tim_10_11_13_14(TIMER13);
}

void __irq_tim8_trg_com_tim14(void) {
    dispatch_adv_trg_com(TIMER8);
    dispatch_tim_10_11_13_14(TIMER14);
}

void __irq_tim8_cc(void) {
    dispatch_adv_cc(TIMER8);
}
