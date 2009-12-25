/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created: 12/18/09 02:36:01
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
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

/* Pin modes are set by [CNFx[1:0] : MODEx[1:0]] */
#define GPIO_SPEED_50MHZ            (0x3) // Max output speed 50 MHz
#define GPIO_MODE_OUTPUT_PP         ((0x00 << 2) | GPIO_SPEED_50MHZ)
#define GPIO_MODE_OUTPUT_OD         ((0x01 << 2) | GPIO_SPEED_50MHZ)

#define GPIO_MODE_AF_OUTPUT_PP      ((0x02 << 2) | GPIO_SPEED_50MHZ)
#define GPIO_MODE_AF_OUTPUT_OD      ((0x03 << 2) | GPIO_SPEED_50MHZ)

/* Note: mode bits must be set to zero for input mode  */
#define GPIO_MODE_INPUT_ANALOG      (0x00 << 2)
#define GPIO_MODE_INPUT_FLOATING    (0x01 << 2)
#define GPIO_MODE_INPUT_PD          (0x02 << 2)
#define GPIO_MODE_INPUT_PU          (0x02 << 2)

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
void gpio_set_mode(GPIO_Port* port, uint8 gpio_pin, uint8 mode);

static inline void gpio_write_bit(GPIO_Port *port, uint8 gpio_pin, uint8 val) {
    if (val){
        port->BSRR = BIT(gpio_pin);
    } else {
        port->BRR = BIT(gpio_pin);
    }
}

#ifdef __cplusplus
} // extern "C"
#endif


#endif

