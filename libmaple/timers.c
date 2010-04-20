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
 *  @file timers.c
 *
 *  @brief General timer routines
 */

#include "libmaple.h"
#include "rcc.h"
#include "timers.h"

typedef struct {
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
    volatile uint16 RCR;
    uint16  RESERVED12;
    volatile uint16 CCR1;
    uint16  RESERVED13;
    volatile uint16 CCR2;
    uint16  RESERVED14;
    volatile uint16 CCR3;
    uint16  RESERVED15;
    volatile uint16 CCR4;
    uint16  RESERVED16;
    volatile uint16 BDTR;   // Not used in general purpose timers
    uint16  RESERVED17;     // Not used in general purpose timers
    volatile uint16 DCR;
    uint16  RESERVED18;
    volatile uint16 DMAR;
    uint16  RESERVED19;
} Timer;

void timer_init(uint8 timer_num, uint16 prescale) {
    Timer *timer;
    uint32 is_advanced = 0;

    ASSERT(timer_num > 0 && timer_num <= 4);

    switch(timer_num) {
    case 1:
        timer = (Timer*)TIMER1_BASE;
        rcc_enable_clk_timer1();
        is_advanced = 1;
        break;
    case 2:
        timer = (Timer*)TIMER2_BASE;
        rcc_enable_clk_timer2();
        break;
    case 3:
        timer = (Timer*)TIMER3_BASE;
        rcc_enable_clk_timer3();
        break;
    case 4:
        timer = (Timer*)TIMER4_BASE;
        rcc_enable_clk_timer4();
        break;
    }

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
    timer->CCER  |= 0x001;      // enable ch

    timer->CCR2   = 0x8FFF;     // PWM start value
    timer->CCMR1 |= (0x68 << 8);// PWM mode 1, enable preload register.
    timer->CCER  |= 0x010;      // enable ch

    timer->CCR3   = 0x8FFF;     // PWM start value
    timer->CCMR2 |= 0x68;       // PWM mode 1, enable preload register.
    timer->CCER  |= 0x100;      // enable ch

    timer->CCR4   = 0x8FFF;     // PWM start value
    timer->CCMR2 |= (0x68 << 8);// PWM mode 1, enable preload register.
    timer->CCER  |= 0x1000;      // enable ch

    /* Advanced timer?  */
    if (is_advanced) {
        timer->BDTR = 0x8000;     // moe enable
    }

    timer->DIER = 0;          // disable update interrupt
    timer->EGR  = 1;          // Initialize update event and shadow registers
    timer->CR1  |= 1;         // Enable timer
}

void timers_set_prescaler(uint32 timer_num, uint16 prescale) {
    Timer *timer;
    ASSERT(timer_num > 0 && timer_num <= 4);

    switch(timer_num) {
    case 1:
        timer = (Timer*)TIMER1_BASE;
        break;
    case 2:
        timer = (Timer*)TIMER2_BASE;
        break;
    case 3:
        timer = (Timer*)TIMER3_BASE;
        break;
    case 4:
        timer = (Timer*)TIMER4_BASE;
        break;
    }
    timer->PSC = prescale;
}

void timers_set_reload(uint32 timer_num, uint16 max_reload) {
    Timer *timer;
    ASSERT(timer_num > 0 && timer_num <= 4);

    switch(timer_num) {
    case 1:
        timer = (Timer*)TIMER1_BASE;
        break;
    case 2:
        timer = (Timer*)TIMER2_BASE;
        break;
    case 3:
        timer = (Timer*)TIMER3_BASE;
        break;
    case 4:
        timer = (Timer*)TIMER4_BASE;
        break;
    }
    timer->ARR = max_reload;
}


void timers_disable(void) {
    Timer *timer;
    int i;
    Timer *timers[4] = {
        (Timer*)TIMER1_BASE,
        (Timer*)TIMER2_BASE,
        (Timer*)TIMER3_BASE,
        (Timer*)TIMER4_BASE,
    };

    for (i = 0; i < 4; i++) {
        timer = timers[i];
        timer->CR1 = 0;
        timer->CCER = 0;
    }
}

void timers_disable_channel(uint8 timer_num, uint8 channel) {
    Timer *timer;
    switch (timer_num) {
    case 1:
        timer = (Timer*)TIMER1_BASE;
        break;
    case 2:
        timer = (Timer*)TIMER2_BASE;
        break;
    case 3:
        timer = (Timer*)TIMER3_BASE;
        break;
    case 4:
        timer = (Timer*)TIMER4_BASE;
        break;
    default:
        ASSERT(0);
    }

    switch (channel) {
    case 1:
        timer->CCER &= ~(0x1);
        break;
    case 2:
        timer->CCER &= ~(0x10);
        break;
    case 3:
        timer->CCER &= ~(0x100);
        break;
    case 4:
        timer->CCER &= ~(0x1000);
        break;
    default:
        ASSERT(0);
    }
}
