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
 *  @file exti.c
 *
 *  @brief External interrupt control routines
 */

#include "libmaple.h"
#include "exti.h"
#include "nvic.h"

volatile static voidFuncPtr exti_handlers[NR_EXTI_CHANNELS];

static inline void clear_pending(int bit) {
    REG_SET(EXTI_PR, BIT(bit));
    /* If the pending bit is cleared as the last instruction in an ISR,
     * it won't actually be cleared in time and the ISR will fire again.
     * Insert a 2-cycle buffer to allow it to take effect. */
    asm volatile("nop");
    asm volatile("nop");
}

/* For EXTI0 through EXTI4, only one handler
 * is associated with each channel, so we
 * don't have to keep track of which channel
 * we came from */
void EXTI0_IRQHandler(void) {
    ASSERT(exti_handlers[EXTI0]);
    if (exti_handlers[EXTI0]) {
        exti_handlers[EXTI0]();
    }

    /* Clear pending bit*/
    clear_pending(EXTI0);
}

void EXTI1_IRQHandler(void) {
    ASSERT(exti_handlers[EXTI1]);
    /* Call registered handler  */
    if (exti_handlers[EXTI1]) {
        exti_handlers[EXTI1]();
    }

    /* Clear pending bit*/
    clear_pending(EXTI1);
}

void EXTI2_IRQHandler(void) {
    ASSERT(exti_handlers[EXTI2]);
    /* Call registered handler  */
    if (exti_handlers[EXTI2]) {
        exti_handlers[EXTI2]();
    }

    /* Clear pending bit*/
    clear_pending(EXTI2);
}

void EXTI3_IRQHandler(void) {
    ASSERT(exti_handlers[EXTI3]);
    /* Call registered handler  */
    if (exti_handlers[EXTI3]) {
        exti_handlers[EXTI3]();
    }

    /* Clear pending bit*/
    clear_pending(EXTI3);
}

void EXTI4_IRQHandler(void) {
    ASSERT(exti_handlers[EXTI4]);
    /* Call registered handler  */
    if (exti_handlers[EXTI4]) {
        exti_handlers[EXTI4]();
    }

    /* Clear pending bit*/
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
            ASSERT(exti_handlers[EXTI5 + i]);
            exti_handlers[EXTI5 + i]();
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
            ASSERT(exti_handlers[EXTI10 + i]);
            exti_handlers[EXTI10 + i]();
            clear_pending(EXTI10 + i);
        }
        pending >>= 1;
    }
}


void exti_attach_interrupt(uint8 channel, uint8 port, voidFuncPtr handler, uint8 mode) {
    ASSERT(channel < NR_EXTI_CHANNELS);
    ASSERT(port < NR_EXTI_PORTS);
    ASSERT(mode < NR_EXTI_MODES);
    ASSERT(EXTI0 == 0);
    ASSERT(handler);

    /* Note: All of the following code assumes that EXTI0 = 0  */

    /* Map port to the correct EXTI channel */
    switch (channel) {
    case EXTI0:
    case EXTI1:
    case EXTI2:
    case EXTI3:
        REG_SET_MASK(AFIO_EXTICR1, BIT_MASK_SHIFT(port, channel*4));
        break;

    case EXTI4:
    case EXTI5:
    case EXTI6:
    case EXTI7:
        REG_SET_MASK(AFIO_EXTICR2, BIT_MASK_SHIFT(port, (channel-4)*4));
        break;

    case EXTI8:
    case EXTI9:
    case EXTI10:
    case EXTI11:
        REG_SET_MASK(AFIO_EXTICR3, BIT_MASK_SHIFT(port, (channel-8)*4));
        break;

    case EXTI12:
    case EXTI13:
    case EXTI14:
    case EXTI15:
        REG_SET_MASK(AFIO_EXTICR4, BIT_MASK_SHIFT(port, (channel-12)*4));
        break;
    }

    /* Unmask appropriate interrupt line  */
    REG_SET_BIT(EXTI_IMR, channel);

    /* Set trigger mode  */
    switch (mode) {
    case EXTI_RISING:
        REG_SET_BIT(EXTI_RTSR, channel);
        break;

    case EXTI_FALLING:
        REG_SET_BIT(EXTI_FTSR, channel);
        break;

    case EXTI_RISING_FALLING:
        REG_SET_BIT(EXTI_RTSR, channel);
        REG_SET_BIT(EXTI_FTSR, channel);
        break;
    }

    /* Configure the enable interrupt bits for the NVIC  */
    switch (channel) {
    case EXTI0:
    case EXTI1:
    case EXTI2:
    case EXTI3:
    case EXTI4:
        REG_SET(NVIC_ISER0, BIT(channel + 6));
        break;

    /* EXTI5-9 map to the same isr */
    case EXTI5:
    case EXTI6:
    case EXTI7:
    case EXTI8:
    case EXTI9:
        REG_SET(NVIC_ISER0, BIT(23));
        break;

    /* EXTI10-15 map to the same isr */
    case EXTI10:
    case EXTI11:
    case EXTI12:
    case EXTI13:
    case EXTI14:
    case EXTI15:
        REG_SET(NVIC_ISER1, BIT(8));
        break;
    }

    /* Register the handler  */
    exti_handlers[channel] = handler;
}


void exti_detach_interrupt(uint8 channel) {
    ASSERT(channel < NR_EXTI_CHANNELS);
    ASSERT(EXTI0 == 0);
    /* Is this interrupt actually on?  */
    ASSERT((REG_GET(EXTI_IMR) >> channel) & 0x01);

    /* Clear EXTI_IMR line  */
    REG_CLEAR_BIT(EXTI_IMR, channel);

    /* Clear triggers  */
    REG_CLEAR_BIT(EXTI_FTSR, channel);
    REG_CLEAR_BIT(EXTI_RTSR, channel);

    /* Turn off the associated interrupt */
    switch (channel) {
    case EXTI0:
    case EXTI1:
    case EXTI2:
    case EXTI3:
    case EXTI4:
        REG_SET(NVIC_ICER0, BIT(channel + 6));
        break;
    case EXTI5:
    case EXTI6:
    case EXTI7:
    case EXTI8:
    case EXTI9:
        /* Are there any other channels enabled?
         * If so, don't disable the interrupt handler */
        if (GET_BITS(REG_GET(EXTI_IMR), 5, 9) == 0) {
            REG_SET(NVIC_ICER0, BIT(23));
        }
        break;
    case EXTI10:
    case EXTI11:
    case EXTI12:
    case EXTI13:
    case EXTI14:
    case EXTI15:
        /* Are there any other channels enabled?
         * If so, don't disable the interrupt handler */
        if (GET_BITS(REG_GET(EXTI_IMR), 10, 15) == 0) {
            REG_SET(NVIC_ICER1, BIT(8));
        }
        break;
    }

    /* Clear handler function pointer  */
    exti_handlers[channel] = 0;
}
