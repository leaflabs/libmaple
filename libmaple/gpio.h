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
 *  @file gpio.h
 *
 *  @brief GPIO prototypes, defines, and inlined access functions
 */

#ifndef _GPIO_H
#define _GPIO_H

/* Each of the GPIO port bits can be in the following modes (STM32 138/995):
 *      Input floating
 *      Input pull-up
 *      Input pull-down
 *      Analog Input
 *      Output open-drain
 *      Output push-pull
 *      Alternate function push-pull
 *      Alternate function open-drain
 *
 * - After reset, the alternate functions are not active and IO prts
 * are set to Input Floating mode */

#define GPIOA_BASE               (GPIO_Port*)0x40010800
#define GPIOB_BASE               (GPIO_Port*)0x40010C00
#define GPIOC_BASE               (GPIO_Port*)0x40011000
#define GPIOD_BASE               (GPIO_Port*)0x40011400

#define GPIO_SPEED_50MHZ            (0x3)

#define MODE_OUTPUT_PP         ((0x00 << 2) | GPIO_SPEED_50MHZ)
#define MODE_OUTPUT_OD         ((0x01 << 2) | GPIO_SPEED_50MHZ)
#define MODE_AF_OUTPUT_PP      ((0x02 << 2) | GPIO_SPEED_50MHZ)
#define MODE_AF_OUTPUT_OD      ((0x03 << 2) | GPIO_SPEED_50MHZ)

#define CNF_INPUT_ANALOG      (0x00 << 2)
#define CNF_INPUT_FLOATING    (0x01 << 2)
#define CNF_INPUT_PD          (0x02 << 2)
#define CNF_INPUT_PU          (0x02 << 2)

typedef enum GPIOPinMode {
   GPIO_MODE_OUTPUT_PP      = MODE_OUTPUT_PP,
   GPIO_MODE_OUTPUT_OD      = MODE_OUTPUT_OD,
   GPIO_MODE_AF_OUTPUT_PP   = MODE_AF_OUTPUT_PP,
   GPIO_MODE_AF_OUTPUT_OD   = MODE_AF_OUTPUT_OD,
   GPIO_MODE_INPUT_ANALOG   = CNF_INPUT_ANALOG,
   GPIO_MODE_INPUT_FLOATING = CNF_INPUT_FLOATING,
   GPIO_MODE_INPUT_PD       = CNF_INPUT_PD,
   GPIO_MODE_INPUT_PU,
} GPIOPinMode;

typedef struct {
   volatile uint32 CRL;      // Port configuration register low
   volatile uint32 CRH;      // Port configuration register high
   volatile uint32 IDR;      // Port input data register
   volatile uint32 ODR;      // Port output data register
   volatile uint32 BSRR;     // Port bit set/reset register
   volatile uint32 BRR;      // Port bit reset register
   volatile uint32 LCKR;     // Port configuration lock register
} GPIO_Port;

typedef volatile uint32* GPIOReg;

#define POS_MASK(shift) (~(0xF << shift))
#define POS(val)        (val << 2)

#ifdef __cplusplus
extern "C"{
#endif

void gpio_init(void);
void gpio_set_mode(GPIO_Port* port, uint8 gpio_pin, GPIOPinMode mode);

static inline void gpio_write_bit(GPIO_Port *port, uint8 gpio_pin, uint8 val) {
   if (val){
      port->BSRR = BIT(gpio_pin);
   } else {
      port->BRR = BIT(gpio_pin);
   }
}

static inline uint32 gpio_read_bit(GPIO_Port *port, uint8 gpio_pin) {
   return (port->IDR & BIT(gpio_pin) ? 1 : 0);
}

#ifdef __cplusplus
} // extern "C"
#endif


#endif

