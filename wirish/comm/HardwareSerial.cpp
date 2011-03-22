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
 * @file HardwareSerial.cpp
 *
 * @brief Wiring-like serial api
 */

#include "wirish.h"
#include "HardwareSerial.h"
#include "usart.h"

HardwareSerial Serial1(USART1, 4500000UL, GPIOA,  9, 10, TIMER1, 2);
HardwareSerial Serial2(USART2, 2250000UL, GPIOA,  2,  3, TIMER2, 3);
HardwareSerial Serial3(USART3, 2250000UL, GPIOB, 10, 11,   NULL, 0);
// TODO: High density device ports

HardwareSerial::HardwareSerial(uint8 usart_num,
                               uint32 max_baud,
                               gpio_dev *gpio_device,
                               uint8 tx_pin,
                               uint8 rx_pin,
                               timer_dev *timer_device,
                               uint8 channel_num) {
    this->usart_num = usart_num;
    this->max_baud = max_baud;
    this->gpio_device = gpio_device;
    this->tx_pin = tx_pin;
    this->rx_pin = rx_pin;
    this->timer_device = timer_device;
    this->channel_num = channel_num;
}

uint8 HardwareSerial::read(void) {
    return usart_getc(usart_num);
}

uint32 HardwareSerial::available(void) {
    return usart_data_available(usart_num);
}

void HardwareSerial::write(unsigned char ch) {
    usart_putc(usart_num, ch);
}

void HardwareSerial::begin(uint32 baud) {
    if (baud > max_baud) {
        return;
    }

    gpio_set_mode(gpio_device, tx_pin, GPIO_AF_OUTPUT_PP);
    gpio_set_mode(gpio_device, rx_pin, GPIO_INPUT_FLOATING);

    if (timer_device != NULL) {
        /* turn off any pwm if there's a conflict on this usart */
        timer_set_mode(timer_device, channel_num, TIMER_DISABLED);
    }

    usart_init(usart_num, baud);
}

void HardwareSerial::end(void) {
    usart_disable(usart_num);
}

void HardwareSerial::flush(void) {
    usart_reset_rx(usart_num);
}
