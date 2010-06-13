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


volatile static voidFuncPtr timer1_handlers[4];
volatile static voidFuncPtr timer2_handlers[4];
volatile static voidFuncPtr timer3_handlers[4];
volatile static voidFuncPtr timer4_handlers[4];

void timer_init(uint8 timer_num, uint16 prescale) {
    // This initialization is very PWM-specific. That's a good default but it
    // should probably call down to a set_mode function
    
    Timer *timer; uint8 is_advanced = 0;

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
    timer->CCER  |= 0x002;      // enable ch

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

    timer->SR = 0;            // clear it
    timer->DIER = 0;          // disable update interrupt
    timer->EGR  = 1;          // Initialize update event and shadow registers
    timer->CR1  |= 1;         // Enable timer
}

void timer_set_count(uint8 timer_num, uint16 value) {
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
    timer->CNT = value;
}

uint16 timer_get_count(uint8 timer_num) {
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
    return timer->CNT;
}

void timer_set_prescaler(uint8 timer_num, uint16 prescale) {
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

void timer_set_reload(uint8 timer_num, uint16 max_reload) {
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


void timer_disable_all(void) {
    // Note: this must be very robust because it gets called from, eg, ASSERT
    // TODO: rewrite?
    Timer *timer; Timer *timers[4] = { (Timer*)TIMER1_BASE,
    (Timer*)TIMER2_BASE, (Timer*)TIMER3_BASE, (Timer*)TIMER4_BASE, }; int i;
    for (i = 0; i < 4; i++) { timer = timers[i]; timer->CR1 = 0; timer->CCER =
    0; } }

void timer_set_mode(uint8 timer_num, uint8 channel, uint8 mode) {
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
    switch(mode) {
    case TIMER_DISABLED:
        // Disable the channel
        // Disable any interrupt
        // Clear interrupt SR? (TODO)
        switch (channel) {
        case 1:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCER &= ~(0x1);
            break;
        case 2:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCER &= ~(0x10);
            break;
        case 3:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCER &= ~(0x100);
            break;
        case 4:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCER &= ~(0x1000);
            break;
        default:
            ASSERT(0);
        }
        break;
    case TIMER_PWM:
        // Set CCMR mode
        // Keep existing reload value
        // Disable any interrupt
        // Clear interrupt SR? (TODO)
        // Enable channel
        switch (channel) {
        case 1:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCMR1 &= ~(0xFF);    
            timer->CCMR1 |= 0x68;       // PWM mode 1, enable preload register.
            timer->CCER  |= 0x0001;     // enable ch
            break;
        case 2:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCMR1 &= ~(0xFF00);    
            timer->CCMR1 |= (0x68 << 8);// PWM mode 1, enable preload register.
            timer->CCER  |= 0x0010;     // enable ch
            break;
        case 3:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCMR2 &= ~(0xFF);    
            timer->CCMR2 |= 0x68;       // PWM mode 1, enable preload register.
            timer->CCER  |= 0x0100;     // enable ch
            break;
        case 4:
            timer->DIER &= ~(1 << channel); // 1-indexed compare nums
            timer->CCMR2 &= ~(0xFF00);    
            timer->CCMR2 |= (0x68 << 8);// PWM mode 1, enable preload register.
            timer->CCER  |= 0x1000;     // enable ch
            break;
        default:
            ASSERT(0);
        }
    case TIMER_OUTPUTCOMPARE:
        // Set CCMR mode
        // Keep existing reload value
        // Don't modify interrupt (needs to be attached to enable)
        // Clear interrupt SR? (TODO)
        // Enable channel
        switch (channel) {
        case 1:
            timer->CCMR1 &= ~(0xFF);    
            timer->CCMR1 |= 0x0010;       // PWM mode 1, enable preload register.
            timer->CCER  |= 0x001;        // enable ch
            break;
        case 2:
            timer->CCMR1 &= ~(0xFF00);    
            timer->CCMR1 |= 0x1000;       // PWM mode 1, enable preload register.
            timer->CCER  |= 0x0010;       // enable ch
            break;
        case 3:
            timer->CCMR2 &= ~(0xFF);    
            timer->CCMR2 |= 0x0010;       // PWM mode 1, enable preload register.
            timer->CCER  |= 0x0100;       // enable ch
            break;
        case 4:
            timer->CCMR2 &= ~(0xFF00);    
            timer->CCMR2 |= 0x1000;       // PWM mode 1, enable preload register.
            timer->CCER  |= 0x1000;       // enable ch
            break;
        default:
            ASSERT(0);
        }
        break;
    // TODO: others
    default:
        ASSERT(0);
    }
}

void timer_set_compare_value(uint8 timer_num, uint8 compare_num, uint16 value) {
    // The faster version of this function is the inline timer_pwm_write_ccr
    
    Timer *timer; TimerCCR *timer_ccr; ASSERT(timer_num > 0 && timer_num <= 4
    && compare_num > 0 && compare_num <= 4);

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
    switch(compare_num) {
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

void timer_attach_interrupt(uint8 timer_num, uint8 compare_num, voidFuncPtr handler) {
    Timer *timer;
    ASSERT(timer_num > 0 && timer_num <= 4 && compare_num > 0 && compare_num <= 4);

    switch(timer_num) {
    case 1:
        timer = (Timer*)TIMER1_BASE;
        timer1_handlers[compare_num-1] = handler;
        nvic_enable_interrupt(27);
        timer->DIER |= (1 << compare_num); // 1-indexed compare nums
        break;
    case 2:
        timer = (Timer*)TIMER2_BASE;
        timer2_handlers[compare_num-1] = handler;
        nvic_enable_interrupt(28);
        timer->DIER |= (1 << compare_num); // 1-indexed compare nums
        break;
    case 3:
        timer = (Timer*)TIMER3_BASE;
        timer3_handlers[compare_num-1] = handler;
        nvic_enable_interrupt(29);
        timer->DIER |= (1 << compare_num); // 1-indexed compare nums
        break;
    case 4:
        timer = (Timer*)TIMER4_BASE;
        timer4_handlers[compare_num-1] = handler;
        nvic_enable_interrupt(30);
        timer->DIER |= (1 << compare_num); // 1-indexed compare nums
        break;
    }
}

void timer_detach_interrupt(uint8 timer_num, uint8 compare_num) {
    Timer *timer;
    ASSERT(timer_num > 0 && timer_num <= 4 && compare_num > 0 && compare_num <= 4);

    switch(timer_num) {
    case 1:
        timer = (Timer*)TIMER1_BASE;
        timer1_handlers[compare_num-1] = 0;
        timer->DIER &= ~(1 << compare_num); // 1-indexed compare nums
        break;
    case 2:
        timer = (Timer*)TIMER2_BASE;
        timer2_handlers[compare_num-1] = 0;
        timer->DIER &= ~(1 << compare_num); // 1-indexed compare nums
        break;
    case 3:
        timer = (Timer*)TIMER3_BASE;
        timer3_handlers[compare_num-1] = 0;
        timer->DIER &= ~(1 << compare_num); // 1-indexed compare nums
        break;
    case 4:
        timer = (Timer*)TIMER4_BASE;
        timer4_handlers[compare_num-1] = 0;
        timer->DIER &= ~(1 << compare_num); // 1-indexed compare nums
        break;
    }
}

void TIM1_CC_IRQHandler(void) {
    // This is a rather long implementation...
    Timer *timer = (Timer*)TIMER1_BASE;
    uint16 sr_buffer; 
    sr_buffer = timer->SR;

    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer1_handlers[3]) {
            timer1_handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer1_handlers[2]) {
            timer1_handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer1_handlers[1]) {
            timer1_handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer1_handlers[0]) {
            timer1_handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}
void TIM2_IRQHandler(void) {
    // This is a rather long implementation...
    Timer *timer = (Timer*)TIMER2_BASE;
    uint16 sr_buffer; 
    sr_buffer = timer->SR;

    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer2_handlers[3]) {
            timer2_handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer2_handlers[2]) {
            timer2_handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer2_handlers[1]) {
            timer2_handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer2_handlers[0]) {
            timer2_handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}
void TIM3_IRQHandler(void) {
    // This is a rather long implementation...
    Timer *timer = (Timer*)TIMER3_BASE;
    uint16 sr_buffer; 
    sr_buffer = timer->SR;

    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer3_handlers[3]) {
            timer3_handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer3_handlers[2]) {
            timer3_handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer3_handlers[1]) {
            timer3_handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer3_handlers[0]) {
            timer3_handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}

void TIM4_IRQHandler(void) {
    // This is a rather long implementation...
    Timer *timer = (Timer*)TIMER4_BASE;
    uint16 sr_buffer; 
    sr_buffer = timer->SR;

    if(sr_buffer & 0x10){ // CC4 flag
        timer->SR &= ~(0x10);
        if(timer4_handlers[3]) {
            timer4_handlers[3]();
        }
    }
    if(sr_buffer & 0x8){ // CC3 flag
        timer->SR &= ~(0x8);
        if(timer4_handlers[2]) {
            timer4_handlers[2]();
        }
    }
    if(sr_buffer & 0x4){ // CC2 flag
        timer->SR &= ~(0x4);
        if(timer4_handlers[1]) {
            timer4_handlers[1]();
        }
    }
    if(sr_buffer & 0x2){ // CC1 flag
        timer->SR &= ~(0x2);
        if(timer4_handlers[0]) {
            timer4_handlers[0]();
        }
    }
    if(sr_buffer & 0x1){ // Update flag
        timer->SR &= ~(0x1);
        //timer->EGR  = 1;
    }
}

