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
 * @brief General timer routines
 */

/* TODO: actually support timer5 and timer8 */

#include "libmaple.h"
#include "rcc.h"
#include "nvic.h"
#include "timers.h"

/* Timer descriptor table */
struct timer_dev timer_dev_table[] = {
    [TIMER1] = {
        .base = (timer_port*)TIMER1_BASE,
        .rcc_dev_num = RCC_TIMER1,
        .nvic_dev_num = NVIC_TIMER1
    },
    [TIMER2] = {
        .base = (timer_port*)TIMER2_BASE,
        .rcc_dev_num = RCC_TIMER2,
        .nvic_dev_num = NVIC_TIMER2
    },
    [TIMER3] = {
        .base = (timer_port*)TIMER3_BASE,
        .rcc_dev_num = RCC_TIMER3,
        .nvic_dev_num = NVIC_TIMER3
    },
    [TIMER4] = {
        .base = (timer_port*)TIMER4_BASE,
        .rcc_dev_num = RCC_TIMER4,
        .nvic_dev_num = NVIC_TIMER4
    },
#if NR_TIMERS >= 8
    /* High density devices only (eg, Maple Native) */
    [TIMER5] = {
        .base = (timer_port*)TIMER5_BASE,
        .rcc_dev_num = RCC_TIMER5,
        .nvic_dev_num = NVIC_TIMER5
    },
    [TIMER8] = {
        .base = (timer_port*)TIMER8_BASE,
        .rcc_dev_num = RCC_TIMER8,
        .nvic_dev_num = NVIC_TIMER8
    },
#endif
};

/* This function should probably be rewriten to take (timer_num, mode)
 * and have prescaler set elsewhere. The mode can be passed through to
 * set_mode at the end */
void timer_init(timer_dev_num timer_num, uint16 prescale) {
    /* TODO: doesn't catch 6+7 */

    timer_port *timer = timer_dev_table[timer_num].base;
    uint8 is_advanced = 0;

    if (timer_num == TIMER1) {
        is_advanced = 1;
    }
#if NR_TIMERS >= 8
    if (timer_num == TIMER8) {
        is_advanced = 1;
    }
#endif

    rcc_clk_enable(timer_dev_table[timer_num].rcc_dev_num);

    timer->CR1 = ARPE;        // No clock division
                              // Do not buffer auto-reload preload
                              // Edge aligned
                              // Upcounter
                              // Do not stop counter at update event
                              // Update events enabled (etc, see bits [1:2])
                              // Counter disabled for now

    timer->PSC = prescale;    // Prescaling by prescale (duh)
    timer->ARR = 0xFFFF;      // Max reload cont

    /* initialize all the channels to 50% duty cycle,
     * TODO: none of them actually get output unless the gpio pin
     * is set, this will probably consume a bit more power but
     * we'll worry about that later. */
    timer->CCR1   = 0x8FFF;     // PWM start value
    timer->CCMR1 |= 0x68;       // PWM mode 1, enable preload register.

    timer->CCR2   = 0x8FFF;     // PWM start value
    timer->CCMR1 |= (0x68 << 8);// PWM mode 1, enable preload register.

    timer->CCR3   = 0x8FFF;     // PWM start value
    timer->CCMR2 |= 0x68;       // PWM mode 1, enable preload register.

    timer->CCR4   = 0x8FFF;     // PWM start value
    timer->CCMR2 |= (0x68 << 8);// PWM mode 1, enable preload register.

    /* Advanced timer?  */
    if (is_advanced) {
        timer->BDTR = 0x8000;     // moe enable
    }

    timer->SR = 0;            // clear it
    timer->DIER = 0;          // disable update interrupt
    timer->EGR  = 1;          // Initialize update event and shadow registers
    timer->CR1  |= 1;         // Enable timer
}

/* Stops the counter; the mode and settings are not modified */
void timer_pause(timer_dev_num timer_num) {
    timer_port *timer = timer_dev_table[timer_num].base;

    timer->CR1 &= ~(0x0001);    // CEN
}

/* Starts the counter; the mode and settings are not modified */
void timer_resume(timer_dev_num timer_num) {
    timer_port *timer = timer_dev_table[timer_num].base;

    timer->CR1 |= 0x0001;       // CEN
}

/* Returns the current timer counter value. Probably very inaccurate
 * if the counter is running with a low prescaler. */
uint16 timer_get_count(timer_dev_num timer_num) {
    timer_port *timer = timer_dev_table[timer_num].base;

    return timer->CNT;
}

/* This function sets the counter value via register for the specified
 * timer.  Can't think of specific usecases except for resetting to
 * zero but it's easy to implement and allows for "creative"
 * programming */
void timer_set_count(timer_dev_num timer_num, uint16 value) {
    timer_port *timer = timer_dev_table[timer_num].base;

    timer->CNT = value;
}

/* Get the prescaler buffer value (remember, the actual prescaler
 * doesn't get set until an update event). */
uint16 timer_get_prescaler(timer_dev_num timer_num) {
    timer_port *timer = timer_dev_table[timer_num].base;
    return timer->PSC;
}

/* Sets the prescaler */
void timer_set_prescaler(timer_dev_num timer_num, uint16 prescale) {
    timer_port *timer = timer_dev_table[timer_num].base;

    timer->PSC = prescale;
}

/* Get the reload value for the entire timer. */
uint16 timer_get_reload(timer_dev_num timer_num) {
    timer_port *timer = timer_dev_table[timer_num].base;
    return timer->ARR;
}

/* This sets the "reload" or "overflow" value for the entire timer. We
 * should probably settle on either "reload" or "overflow" to prevent
 * confusion? */
void timer_set_reload(timer_dev_num timer_num, uint16 max_reload) {
    timer_port *timer = timer_dev_table[timer_num].base;

    timer->ARR = max_reload;
}

/* This quickly disables all 4 timers, presumably as part of a system shutdown
 * or similar to prevent interrupts and PWM output without 16 seperate function
 * calls to timer_set_mode */
void timer_disable_all(void) {
    // TODO: refactor

    /* Note: this must be very robust because it gets called from,
       e.g., ASSERT */
    timer_port *timer;
#if NR_TIMERS >= 8
    timer_port *timers[6] = { (timer_port*)TIMER1_BASE,
                              (timer_port*)TIMER2_BASE,
                              (timer_port*)TIMER3_BASE,
                              (timer_port*)TIMER4_BASE,
                              (timer_port*)TIMER5_BASE,
                              (timer_port*)TIMER8_BASE,
    };
    uint8 i;
    for (i = 0; i < 6; i++) {
        timer = timers[i];
        timer->CR1 = 0;
        timer->CCER = 0;
    }
#else
    timer_port *timers[4] = { (timer_port*)TIMER1_BASE,
                              (timer_port*)TIMER2_BASE,
                              (timer_port*)TIMER3_BASE,
                              (timer_port*)TIMER4_BASE,
    };
    uint8 i;
    for (i = 0; i < 4; i++) {
        timer = timers[i];
        timer->CR1 = 0;
        timer->CCER = 0;
    }
#endif
}

/* Sets the mode of individual timer channels, including a DISABLE mode */
void timer_set_mode(timer_dev_num timer_num, uint8 channel, TimerMode mode) {
    timer_port *timer = timer_dev_table[timer_num].base;
    ASSERT(channel >= 1);

    switch(mode) {
    case TIMER_DISABLED:
        /* Disable the channel
         * Disable any interrupt
         * Clear interrupt SR? (TODO) */
        timer->DIER &= ~(1 << channel); // 1-indexed compare nums
        timer_detach_interrupt(timer_num, channel);
        timer->CCER &= ~(1 << (4*(channel - 1))); // 0-indexed
        break;
    case TIMER_PWM:
        /* Set CCMR mode
         * Keep existing reload value
         * Disable any interrupt
         * Clear interrupt SR? (TODO)
         * Enable channel */
        timer->DIER &= ~(1 << channel); // 1-indexed compare nums
        switch (channel) {
        case 1:
            timer->CCMR1 &= ~(0xFF);
            timer->CCMR1 |= 0x68;       // PWM mode 1, enable preload register.
            break;
        case 2:
            timer->CCMR1 &= ~(0xFF00);
            timer->CCMR1 |= (0x68 << 8);// PWM mode 1, enable preload register.
            break;
        case 3:
            timer->CCMR2 &= ~(0xFF);
            timer->CCMR2 |= 0x68;       // PWM mode 1, enable preload register.
            break;
        case 4:
            timer->CCMR2 &= ~(0xFF00);
            timer->CCMR2 |= (0x68 << 8);// PWM mode 1, enable preload register.
            break;
        default:
            ASSERT(0);
        }
        timer->CCER |= (1 << (4*(channel - 1))); // Enable
        break;
    case TIMER_OUTPUTCOMPARE:
        /* Set CCMR mode
         * Keep existing reload value
         * Don't modify interrupt (needs to be attached to enable)
         * Clear interrupt SR? (TODO)
         * Enable channel */
        switch (channel) {
        case 1:
            timer->CCMR1 &= ~(0xFF);
            timer->CCMR1 |= 0x0010; // PWM mode 1, enable preload register.
            break;
        case 2:
            timer->CCMR1 &= ~(0xFF00);
            timer->CCMR1 |= 0x1000; // PWM mode 1, enable preload register.
            break;
        case 3:
            timer->CCMR2 &= ~(0xFF);
            timer->CCMR2 |= 0x0010; // PWM mode 1, enable preload register.
            break;
        case 4:
            timer->CCMR2 &= ~(0xFF00);
            timer->CCMR2 |= 0x1000; // PWM mode 1, enable preload register.
            break;
        default:
            ASSERT(0);
        }
        timer->CCER |= (1 << (4*(channel - 1))); // Enable
        break;
    default:
        ASSERT(0);
    }
}

uint16 timer_get_compare_value(timer_dev_num timer_num, uint8 channel_num) {
    /* faster: just read TIMERx_CHy_CCR (see timers.h) */
    ASSERT(channel_num > 0 && channel_num <= 4);
    timer_port *timer = timer_dev_table[timer_num].base;
    switch(channel_num) {
    case 1:
        return timer->CCR1;
    case 2:
        return timer->CCR2;
    case 3:
        return timer->CCR3;
    case 4:
        return timer->CCR4;
    default:                    /* in case ASSERT is disabled */
        return 0;
    }
}

/* This sets the compare value (aka the trigger) for a given timer
 * channel */
void timer_set_compare_value(timer_dev_num timer_num,
                             uint8 channel_num,
                             uint16 value) {
    ASSERT(channel_num > 0 && channel_num <= 4);

    /* The faster version of this function is the inline
       timer_pwm_write_ccr */
    timer_port *timer = timer_dev_table[timer_num].base;

    switch(channel_num) {
    case 1:
        timer->CCR1 = value;
        break;
    case 2:
        timer->CCR2 = value;
        break;
    case 3:
        timer->CCR3 = value;
        break;
    case 4:
        timer->CCR4 = value;
        break;
    }
}

/* Stores a pointer to the passed usercode interrupt function and configures
 * the actual ISR so that it will actually be called */
void timer_attach_interrupt(timer_dev_num timer_num,
                            uint8 compare_num,
                            voidFuncPtr handler) {
    ASSERT(compare_num > 0 && compare_num <= 4);

    timer_port *timer = timer_dev_table[timer_num].base;

    timer_dev_table[timer_num].handlers[compare_num-1] = handler;
    timer->DIER |= (1 << compare_num); // 1-indexed compare nums
    nvic_irq_enable(timer_dev_table[timer_num].nvic_dev_num);
}

void timer_detach_interrupt(timer_dev_num timer_num, uint8 compare_num) {
    ASSERT(compare_num > 0 && compare_num <= 4);

    timer_port *timer = timer_dev_table[timer_num].base;

    timer_dev_table[timer_num].handlers[compare_num-1] = 0;
    timer->DIER &= ~(1 << compare_num); // 1-indexed compare nums
}

void timer_generate_update(timer_dev_num timer_num) {
    /* cause update event by setting UG bit in EGR.  updates prescaler
       ratio etc. */
    timer_port *timer = timer_dev_table[timer_num].base;
    timer->EGR |= 0x1;
}

/* The following are the actual interrupt handlers; 1 for each timer which must
 * determine which actual compare value (aka channel) was triggered.
 *
 * These ISRs get called when the timer interrupt is enabled, the
 * timer is running, and the timer count equals any of the CCR
 * registers /or/ has overflowed.
 *
 * This is a rather long implementation... */
void TIM1_CC_IRQHandler(void) {
    timer_port *timer = (timer_port*)TIMER1_BASE;
    uint16 sr_buffer;
    sr_buffer = timer->SR;

    /* Simply switch/case-ing here doesn't work because multiple
     * CC flags may be high. */
    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer_dev_table[TIMER1].handlers[3]) {
            timer_dev_table[TIMER1].handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer_dev_table[TIMER1].handlers[2]) {
            timer_dev_table[TIMER1].handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer_dev_table[TIMER1].handlers[1]) {
            timer_dev_table[TIMER1].handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer_dev_table[TIMER1].handlers[0]) {
            timer_dev_table[TIMER1].handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}
void TIM2_IRQHandler(void) {
    /* This is a rather long implementation... */
    timer_port *timer = (timer_port*)TIMER2_BASE;
    uint16 sr_buffer;
    sr_buffer = timer->SR;

    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer_dev_table[TIMER2].handlers[3]) {
            timer_dev_table[TIMER2].handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer_dev_table[TIMER2].handlers[2]) {
            timer_dev_table[TIMER2].handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer_dev_table[TIMER2].handlers[1]) {
            timer_dev_table[TIMER2].handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer_dev_table[TIMER2].handlers[0]) {
            timer_dev_table[TIMER2].handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}
void TIM3_IRQHandler(void) {
    /* This is a rather long implementation... */
    timer_port *timer = (timer_port*)TIMER3_BASE;
    uint16 sr_buffer;
    sr_buffer = timer->SR;

    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer_dev_table[TIMER3].handlers[3]) {
            timer_dev_table[TIMER3].handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer_dev_table[TIMER3].handlers[2]) {
            timer_dev_table[TIMER3].handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer_dev_table[TIMER3].handlers[1]) {
            timer_dev_table[TIMER3].handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer_dev_table[TIMER3].handlers[0]) {
            timer_dev_table[TIMER3].handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}

void TIM4_IRQHandler(void) {
    /* This is a rather long implementation... */
    timer_port*timer = (timer_port*)TIMER4_BASE;
    uint16 sr_buffer;
    sr_buffer = timer->SR;

    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer_dev_table[TIMER4].handlers[3]) {
            timer_dev_table[TIMER4].handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer_dev_table[TIMER4].handlers[2]) {
            timer_dev_table[TIMER4].handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer_dev_table[TIMER4].handlers[1]) {
            timer_dev_table[TIMER4].handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer_dev_table[TIMER4].handlers[0]) {
            timer_dev_table[TIMER4].handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}
