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
 *  @file HardwareSerial.cpp
 *
 *  @brief Wiring-like serial api
 */

#include "wirish.h"
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

HardwareSerial::HardwareSerial(uint8 usartNum) {
    ASSERT(usartNum == 1 ||
           usartNum == 2 ||
           usartNum == 3);
    this->usartNum = usartNum;
}

uint8 HardwareSerial::read(void) {
    return usart_getc(usartNum);
}

uint32 HardwareSerial::available(void) {

    return usart_data_available(usartNum);
}

void HardwareSerial::write(unsigned char ch) {
    usart_putc(usartNum, ch);
}

void HardwareSerial::begin(uint32 baud) {
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

void HardwareSerial::end(void) {
    usart_disable(usartNum);
}

void HardwareSerial::flush(void) {
    usart_clear_buffer(usartNum);
}

HardwareSerial Serial1(1);
HardwareSerial Serial2(2);
HardwareSerial Serial3(3);
