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
 *  Created: 12/19/09 05:15:24 EST
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file HardwareSerial.cpp
 *
 *  @brief Wiring-like serial api
 */

#include "wiring.h"
#include "HardwareSerial.h"
#include "usart.h"
#include "gpio.h"
#include "timers.h"

#define USART1_TX_PORT             GPIOA_BASE
#define USART1_TX_PIN              9
#define USART1_RX_PORT             GPIOA_BASE
#define USART1_RX_PIN              10

#define USART2_TX_PORT             GPIOA_BASE
#define USART2_TX_PIN              2
#define USART2_RX_PORT             GPIOA_BASE
#define USART2_RX_PIN              3

#define USART3_TX_PORT             GPIOB_BASE
#define USART3_TX_PIN              10
#define USART3_RX_PORT             GPIOB_BASE
#define USART3_RX_PIN              11

HardwareSerial::HardwareSerial(uint8_t usartNum) {
    ASSERT(usartNum == 1 ||
           usartNum == 2 ||
           usartNum == 3);
    this->usartNum = usartNum;
}

uint8_t HardwareSerial::read(void) {
    return usart_getc(usartNum);
}

uint32 HardwareSerial::available(void) {

    return usart_data_available(usartNum);
}

void HardwareSerial::write(unsigned char ch) {
    usart_putc(usartNum, ch);
}

void HardwareSerial::begin(uint32_t baud) {
    ASSERT(!(baud > USART_MAX_BAUD));

    /* Set appropriate pin modes  */
    switch (usartNum) {
    case 1:
        gpio_set_mode(USART1_TX_PORT, USART1_TX_PIN, GPIO_MODE_AF_OUTPUT_PP);
        gpio_set_mode(USART1_RX_PORT, USART1_RX_PIN, GPIO_MODE_INPUT_FLOATING);
        /* Turn off any pwm  */
        timers_disable_channel(1, 2);
        break;
    case 2:
        gpio_set_mode(USART2_TX_PORT, USART2_TX_PIN, GPIO_MODE_AF_OUTPUT_PP);
        gpio_set_mode(USART2_RX_PORT, USART2_RX_PIN, GPIO_MODE_INPUT_FLOATING);
        /* Turn off any pwm  */
        timers_disable_channel(2, 3);
        break;
    case 3:
        gpio_set_mode(USART3_TX_PORT, USART3_TX_PIN, GPIO_MODE_AF_OUTPUT_PP);
        gpio_set_mode(USART3_RX_PORT, USART3_RX_PIN, GPIO_MODE_INPUT_FLOATING);
        break;
    default:
        ASSERT(0);
    }

    usart_init(usartNum, baud);
}

HardwareSerial Serial1(1);
HardwareSerial Serial2(2);
HardwareSerial Serial3(3);
