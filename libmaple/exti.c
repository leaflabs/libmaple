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
 * @brief External interrupt control routines
 */

#include "libmaple.h"
#include "exti.h"
#include "nvic.h"

typedef struct ExtIChannel {
    void (*handler)(void);
    uint32 irq_line;
} ExtIChannel;

static ExtIChannel exti_channels[] = {
    { .handler = NULL, .irq_line = NVIC_EXTI0     },  // EXTI0
    { .handler = NULL, .irq_line = NVIC_EXTI1     },  // EXTI1
    { .handler = NULL, .irq_line = NVIC_EXTI2     },  // EXTI2
    { .handler = NULL, .irq_line = NVIC_EXTI3     },  // EXTI3
    { .handler = NULL, .irq_line = NVIC_EXTI4     },  // EXTI4
    { .handler = NULL, .irq_line = NVIC_EXTI9_5   },  // EXTI5
    { .handler = NULL, .irq_line = NVIC_EXTI9_5   },  // EXTI6
    { .handler = NULL, .irq_line = NVIC_EXTI9_5   },  // EXTI7
    { .handler = NULL, .irq_line = NVIC_EXTI9_5   },  // EXTI8
    { .handler = NULL, .irq_line = NVIC_EXTI9_5   },  // EXTI9
    { .handler = NULL, .irq_line = NVIC_EXTI15_10 },  // EXTI10
    { .handler = NULL, .irq_line = NVIC_EXTI15_10 },  // EXTI11
    { .handler = NULL, .irq_line = NVIC_EXTI15_10 },  // EXTI12
    { .handler = NULL, .irq_line = NVIC_EXTI15_10 },  // EXTI13
    { .handler = NULL, .irq_line = NVIC_EXTI15_10 },  // EXTI14
    { .handler = NULL, .irq_line = NVIC_EXTI15_10 },  // EXTI15
};

static inline void clear_pending(int bit) {
    __set_bits(EXTI_PR, BIT(bit));
    /* If the pending bit is cleared as the last instruction in an ISR,
     * it won't actually be cleared in time and the ISR will fire again.
     * Insert a 2-cycle buffer to allow it to take effect. */
    asm volatile("nop");
    asm volatile("nop");
}

static inline void dispatch_handler(uint32 channel) {
    ASSERT(exti_channels[channel].handler);
    if (exti_channels[channel].handler) {
        (exti_channels[channel].handler)();
    }
}

/* For EXTI0 through EXTI4, only one handler
 * is associated with each channel, so we
 * don't have to keep track of which channel
 * we came from */
void EXTI0_IRQHandler(void) {
    dispatch_handler(EXTI0);
    clear_pending(EXTI0);
}

void EXTI1_IRQHandler(void) {
    dispatch_handler(EXTI1);
    clear_pending(EXTI1);
}

void EXTI2_IRQHandler(void) {
    dispatch_handler(EXTI2);
    clear_pending(EXTI2);
}

void EXTI3_IRQHandler(void) {
    dispatch_handler(EXTI3);
    clear_pending(EXTI3);
}

void EXTI4_IRQHandler(void) {
    dispatch_handler(EXTI4);
    clear_pending(EXTI4);
}

void EXTI9_5_IRQHandler(void) {
    /* Figure out which channel it came from  */
    uint32 pending;
    uint32 i;
    pending = REG_GET(EXTI_PR);
    pending = GET_BITS(pending, 5, 9);

    /* Dispatch every handler if the pending bit is set */
    for (i = 0; i < 5; i++) {
        if (pending & 0x1) {
            dispatch_handler(EXTI5 + i);
            clear_pending(EXTI5 + i);
        }
        pending >>= 1;
    }
}

void EXTI15_10_IRQHandler(void) {
    /* Figure out which channel it came from  */
    uint32 pending;
    uint32 i;
    pending = REG_GET(EXTI_PR);
    pending = GET_BITS(pending, 10, 15);

    /* Dispatch every handler if the pending bit is set */
    for (i = 0; i < 6; i++) {
        if (pending & 0x1) {
            dispatch_handler(EXTI10 + i);
            clear_pending(EXTI10 + i);
        }
        pending >>= 1;
    }
}


/**
 * @brief Register a handler to run upon external interrupt
 * @param port source port of pin (eg EXTI_CONFIG_PORTA)
 * @param pin pin number on the source port
 * @param handler function handler to execute
 * @param mode type of transition to trigger on
 */
void exti_attach_interrupt(uint32 port,
                           uint32 pin,
                           voidFuncPtr handler,
                           uint32 mode) {
    static uint32 afio_regs[] = {
        AFIO_EXTICR1,         // EXT0-3
        AFIO_EXTICR2,         // EXT4-7
        AFIO_EXTICR3,         // EXT8-11
        AFIO_EXTICR4,         // EXT12-15
    };

    /* Note: All of the following code assumes that EXTI0 = 0  */
    ASSERT(EXTI0 == 0);
    ASSERT(handler);

    uint32 channel = pin;

    /* map port to channel */
    __write(afio_regs[pin/4], (port << ((pin % 4) * 4)));

    /* Unmask appropriate interrupt line  */
    __set_bits(EXTI_IMR, BIT(channel));

    /* Set trigger mode  */
    switch (mode) {
    case EXTI_RISING:
        __set_bits(EXTI_RTSR, BIT(channel));
        break;

    case EXTI_FALLING:
        __set_bits(EXTI_FTSR, BIT(channel));
        break;

    case EXTI_RISING_FALLING:
        __set_bits(EXTI_RTSR, BIT(channel));
        __set_bits(EXTI_FTSR, BIT(channel));
        break;
    }

    /* Register the handler  */
    exti_channels[channel].handler = handler;

    /* Configure the enable interrupt bits for the NVIC  */
    nvic_irq_enable(exti_channels[channel].irq_line);
}


/**
 * @brief Unregister an external interrupt handler
 * @param channel channel to disable (eg EXTI0)
 */
void exti_detach_interrupt(uint32 channel) {
    ASSERT(channel < NR_EXTI_CHANNELS);
    ASSERT(EXTI0 == 0);

    __clear_bits(EXTI_IMR,  BIT(channel));
    __clear_bits(EXTI_FTSR, BIT(channel));
    __clear_bits(EXTI_RTSR, BIT(channel));

    nvic_irq_disable(exti_channels[channel].irq_line);

    exti_channels[channel].handler = NULL;
}
