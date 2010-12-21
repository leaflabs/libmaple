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
 * @file timers.h
 *
 * @brief Timer prototypes and various definitions
 */

/* Note to self:
 * The timer clock frequencies are automatically fixed by hardware.
 * There are two cases:
 *     1.  if the APB prescaler is 1, the timer clock frequencies are
 *         set to the same frequency as that of the APB domain to which
 *         the timers are connected.
 *     2.  otherwise, they are set to twice (x2) the frequency of the
 *         APB domain to which the timers are connected.
 * See stm32 manual, 77/995
 *
 * hence, 72 mhz timers
 */

/* Maple Timer channels:
 * Timer        Maple Pin               STM32 Pin     Type
 * TIM1_CH1     D6                      PA8           Advanced
 * TIM1_CH2     D7                      PA9           Advanced
 * TIM1_CH3     D8                      PA10          Advanced
 *
 * TIM2_CH1     D2                      PA0
 * TIM2_CH2     D3                      PA1
 * TIM2_CH3     D1                      PA2
 * TIM2_CH4     D0                      PA3
 *
 * TIM3_CH1     D12                     PA6
 * TIM3_CH2     D11                     PA7
 * TIM3_CH3     EXT7                    PB0
 * TIM3_CH4     EXT8                    PB1
 *
 * TIM4_CH1     EXT5                    PB6
 * TIM4_CH1     EXT9                    PB7
 * TIM4_CH1     EXT15                   PB8
 * TIM4_CH1     EXT4                    PB9
 *
 * Not supported:
 * TIM1_CH4    USBDM, not available     PA11          Advanced
 * TIM1_CH1_N  EXT12                    PB13
 * TIM1_CH2_N  EXT13                    PB14
 * TIM1_CH3_N  EXT14                    PB15
 * */

/* I don't like the Arduino API for dealing with pin modes.
 * How about...
 *
 * pinMode(digitalPin, PWM);
 * pwmWrite(digitalPin) */

#ifndef _TIMERS_H_
#define _TIMERS_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef volatile uint16* TimerCCR;

#define TIMER1_BASE        0x40012C00
#define TIMER2_BASE        0x40000000
#define TIMER3_BASE        0x40000400
#define TIMER4_BASE        0x40000800
#define TIMER5_BASE        0x40000C00   // High-density devices only
#define TIMER6_BASE        0x40001000   // High-density devices only
#define TIMER7_BASE        0x40001400   // High-density devices only
#define TIMER8_BASE        0x40013400   // High-density devices only

#define ARPE               BIT(7)       // Auto-reload preload enable
#define NOT_A_TIMER        0

#define TIMER_CCR(NUM,CHAN)  (TIMER ## NUM ## _CH ## CHAN ## _CRR)

/* Timers 1-4 are present on the entire STM32 line. */

#define TIMER1_CH1_CCR     ((TimerCCR)(TIMER1_BASE + 0x34))
#define TIMER1_CH2_CCR     ((TimerCCR)(TIMER1_BASE + 0x38))
#define TIMER1_CH3_CCR     ((TimerCCR)(TIMER1_BASE + 0x3C))
#define TIMER1_CH4_CCR     ((TimerCCR)(TIMER1_BASE + 0x40))

#define TIMER2_CH1_CCR     ((TimerCCR)(TIMER2_BASE + 0x34))
#define TIMER2_CH2_CCR     ((TimerCCR)(TIMER2_BASE + 0x38))
#define TIMER2_CH3_CCR     ((TimerCCR)(TIMER2_BASE + 0x3C))
#define TIMER2_CH4_CCR     ((TimerCCR)(TIMER2_BASE + 0x40))

#define TIMER3_CH1_CCR     ((TimerCCR)(TIMER3_BASE + 0x34))
#define TIMER3_CH2_CCR     ((TimerCCR)(TIMER3_BASE + 0x38))
#define TIMER3_CH3_CCR     ((TimerCCR)(TIMER3_BASE + 0x3C))
#define TIMER3_CH4_CCR     ((TimerCCR)(TIMER3_BASE + 0x40))

#define TIMER4_CH1_CCR     ((TimerCCR)(TIMER4_BASE + 0x34))
#define TIMER4_CH2_CCR     ((TimerCCR)(TIMER4_BASE + 0x38))
#define TIMER4_CH3_CCR     ((TimerCCR)(TIMER4_BASE + 0x3C))
#define TIMER4_CH4_CCR     ((TimerCCR)(TIMER4_BASE + 0x40))

/* Timers 5 and 8 are in high-density devices only (such as Maple
   Native).  Timers 6 and 7 in these devices have no output compare
   pins. */

#define TIMER5_CH1_CCR     ((TimerCCR)(TIMER5_BASE + 0x34))
#define TIMER5_CH2_CCR     ((TimerCCR)(TIMER5_BASE + 0x38))
#define TIMER5_CH3_CCR     ((TimerCCR)(TIMER5_BASE + 0x3C))
#define TIMER5_CH4_CCR     ((TimerCCR)(TIMER5_BASE + 0x40))

#define TIMER8_CH1_CCR     ((TimerCCR)(TIMER8_BASE + 0x34))
#define TIMER8_CH2_CCR     ((TimerCCR)(TIMER8_BASE + 0x38))
#define TIMER8_CH3_CCR     ((TimerCCR)(TIMER8_BASE + 0x3C))
#define TIMER8_CH4_CCR     ((TimerCCR)(TIMER8_BASE + 0x40))

/**
 * Used to configure the behavior of a timer.
 */
typedef enum TimerMode {
    TIMER_DISABLED, /**< In this mode, the timer stops counting,
                       interrupts are not called, and no state changes
                       are output. */
    TIMER_PWM, /**< This is the default mode for pins after
                  initialization. */
    TIMER_OUTPUTCOMPARE, /**< In this mode, the timer counts from 0 to
                            its reload value repeatedly; every time
                            the counter value reaches one of the
                            channel compare values, the corresponding
                            interrupt is fired. */
} TimerMode;

typedef struct {
    /* Fields up to ARR common to general purpose (2,3,4,5), advanced
       control (1,8) and basic (6, 7) timers: */
    volatile uint16 CR1;
    uint16  RESERVED0;
    volatile uint16 CR2;
    uint16  RESERVED1;
    volatile uint16 SMCR;
    uint16  RESERVED2;
    volatile uint16 DIER;
    uint16  RESERVED3;
    volatile uint16 SR;
    uint16  RESERVED4;
    volatile uint16 EGR;
    uint16  RESERVED5;
    volatile uint16 CCMR1;
    uint16  RESERVED6;
    volatile uint16 CCMR2;
    uint16  RESERVED7;
    volatile uint16 CCER;
    uint16  RESERVED8;
    volatile uint16 CNT;
    uint16  RESERVED9;
    volatile uint16 PSC;
    uint16  RESERVED10;
    volatile uint16 ARR;
    uint16  RESERVED11;
    /* Basic timers have none of the following: */
    volatile uint16 RCR;        /* Advanced control timers only */
    uint16  RESERVED12;         /* Advanced control timers only */
    volatile uint16 CCR1;
    uint16  RESERVED13;
    volatile uint16 CCR2;
    uint16  RESERVED14;
    volatile uint16 CCR3;
    uint16  RESERVED15;
    volatile uint16 CCR4;
    uint16  RESERVED16;
    volatile uint16 BDTR;       /* Advanced control timers only */
    uint16  RESERVED17;         /* Advanced control timers only */
    volatile uint16 DCR;
    uint16  RESERVED18;
    volatile uint16 DMAR;
    uint16  RESERVED19;
} timer_port;

/**
 * Timer device numbers.  See STM32 reference manual, chapters 13-15.
 */
/* several locations depend on TIMER1=0, etc.; don't change the
   enumerator values to start at 1. */
typedef enum {
    TIMER1,      /*< Advanced control timer TIM1 */
    TIMER2,      /*< General purpose timer TIM2 */
    TIMER3,      /*< General purpose timer TIM3 */
    TIMER4,      /*< General purpose timer TIM4 */
#if NR_TIMERS >= 8
    TIMER5,      /*< General purpose timer TIM5; high density only */
    /* TIMER6,      /\*< Basic timer TIM6; high density only *\/ */
    /* TIMER7,      /\*< Basic timer TIM7; high density only *\/ */
    TIMER8,      /*< Advanced control timer TIM8; high density only */
#endif
    TIMER_INVALID /* FIXME: this is starting to seem like a bad idea */
} timer_dev_num;

/* timer descriptor */
struct timer_dev {
    timer_port *base;
    const uint8 rcc_dev_num;
    const uint8 nvic_dev_num;
    volatile voidFuncPtr handlers[4];
};

extern struct timer_dev timer_dev_table[];

/**
 * Initializes timer with prescale as the clock divisor.
 *
 * @param timer_num Timer number.
 *
 * @param prescale value in the range 1--65535 to use as a prescaler
 * for timer counter increment frequency.
 *
 * @see timer_dev_num
 * @see timer_set_prescaler()
 * @see timer_set_mode()
 */
void timer_init(timer_dev_num timer_num, uint16 prescale);

/**
 * Quickly disable all timers.  Calling this function is faster than,
 * e.g., calling timer_set_mode() for all available timers/channels.
 */
void timer_disable_all(void);

/**
 * Returns the timer's counter value.  Due to function call overhead,
 * this value is likely to be inaccurate if the counter is running
 * with a low prescaler.
 *
 * @param timer_num the timer whose counter to return.
 *
 * @pre Timer has been initialized.
 */
uint16 timer_get_count(timer_dev_num timer_num);

/**
 * Sets the counter value for the given timer.
 *
 * @param timer_num the timer whose counter to set.
 *
 * @param value the new counter value.
 *
 * @pre Timer has been initialized.
 */
void timer_set_count(timer_dev_num timer_num, uint16 value);

/**
 * Stops the timer's counter from incrementing.  Does not modify the
 * timer's mode or settings.
 *
 * @param timer_num the timer to pause.
 *
 * @see timer_resume()
 *
 * @pre Timer has been initialized.
 */
void timer_pause(timer_dev_num timer_num);

/**
 * Starts the counter for the given timer.  Does not modify the
 * timer's mode or settings.  The timer will begin counting on the
 * first rising clock cycle after it has been re-enabled using this
 * function.
 *
 * @param timer_num the timer to resume.
 *
 * @see timer_pause()
 *
 * @pre Timer has been initialized.
 */
void timer_resume(timer_dev_num timer_num);

/**
 * Returns the prescaler for the given timer.
 *
 * @param timer_num the timer whose prescaler to return.
 *
 * @see timer_set_prescaler()
 *
 * @pre Timer has been initialized.
 */
uint16 timer_get_prescaler(timer_dev_num timer_num);

/**
 * Sets the prescaler for the given timer.  This value goes into the
 * PSC register, so it's 0-based (i.e., a prescale of 0 counts 1 tick
 * per clock cycle).  This prescale does not take effect until the
 * next update event.
 *
 * @param timer_num the timer whose prescaler to set.
 *
 * @param prescale the new prescaler.
 *
 * @pre Timer has been initialized.
 */
void timer_set_prescaler(timer_dev_num timer_num, uint16 prescale);

/**
 * Gets the reload value for the timer.
 *
 * @see timer_set_reload()
 *
 * @pre Timer has been initialized.
 */
uint16 timer_get_reload(timer_dev_num timer_num);

/**
 * Sets the reload value for the timer.
 *
 * After this function returns, the timer's counter will reset to 0
 * after it has reached the value max_reload.
 *
 * @pre Timer has been initialized.
 */
void timer_set_reload(timer_dev_num timer_num, uint16 max_reload);

/* TODO: timer_get_mode */

/**
 * Set the mode of an individual timer channel.
 *
 * @see timer_disable_all()
 * @see TimerMode
 * @see timer_dev_num
 * @pre Timer has been initialized.
 */
void timer_set_mode(timer_dev_num timer_num, uint8 channel, TimerMode mode);

/**
 * Get the compare value for the given timer channel.
 * @see timer_set_compare_value()
 * @see timer_dev_num
 * @pre Timer has been initialized.
 */
uint16 timer_get_compare_value(timer_dev_num timer_num, uint8 channel);

/**
 * Sets the compare value for a given timer channel.  Useful for
 * scheduling when interrupt handlers will be called.
 *
 * @see timer_attach_interrupt()
 * @see timer_detach_interrupt()
 * @see timer_set_reload()
 * @see timer_dev_num
 * @pre Timer has been initialized.
 */
void timer_set_compare_value(timer_dev_num timer_num, uint8 channel,
                             uint16 value);

/**
 * Detach the interrupt handler for the given timer channel, if any.
 * After this function returns, any handler attached to the given
 * channel will no longer be called.
 *
 * @see timer_attach_interrupt()
 * @pre Timer has been initialized.
 * @see timer_dev_num
 */
void timer_detach_interrupt(timer_dev_num timer_num, uint8 channel);

/**
 * Attach an interrupt handler for the given timer and channel.  The
 * given ISR, handler, will be called whenever the timer's counter
 * reaches the compare value for the given timer and channel.
 *
 * @see timer_set_compare_value()
 * @see timer_detach_interrupt()
 * @see timer_set_mode()
 * @see timer_dev_num
 * @see voidFuncPtr
 * @pre Timer has been initialized.
 * @pre The channel's mode must be set to TIMER_OUTPUTCOMPARE, or the
 *      interrupt handler will not get called.
 */
void timer_attach_interrupt(timer_dev_num timer_num, uint8 channel,
                            voidFuncPtr handler);

/**
 * Programmatically generate an update event on the given timer.  This
 * updates the prescaler, reloads the compare value (in upcounting
 * mode, etc.).
 *
 * @pre Timer has been initialized.
 */
void timer_generate_update(timer_dev_num timer_num);

/**
 * Turn on PWM with duty_cycle.
 *
 * @param ccr TIMERx_CHn_CCR, where x goes from 1 to NR_TIMERS,
 * and n goes from 1 to 4.
 *
 * @param duty_cycle: A number between 0 and
 * timer_get_compare_value(TIMERx, y), where x and y are as above.
 *
 * @pre Pin has been set to alternate function output.
 *
 * @pre Timer has been initialized.
 */
static inline void timer_pwm_write_ccr(TimerCCR ccr, uint16 duty_cycle) {
    *ccr = duty_cycle;
}

#ifdef __cplusplus
} // extern "C"
#endif


#endif

