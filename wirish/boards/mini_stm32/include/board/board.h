/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file   wirish/boards/mini_stm32/include/board/board.h
 * @author Daniel Serpell <daniel.serpell@gmail.com>
 * @brief  Board header for mini STM32F103C8T6 board from www.lctech-inc.com.
 *
 * Board is available from:
 * http://www.lctech-inc.com/Hardware/Detail.aspx?id=0172e854-77b0-43d5-b300-68e570c914fd
 *
 * Based on maple-mini configuration.
 */

#ifndef _BOARD_MINI_STM32_H_
#define _BOARD_MINI_STM32_H_

#define CYCLES_PER_MICROSECOND    72
#define SYSTICK_RELOAD_VAL     71999 /* takes a cycle to reload */

// The board does not have buttons or LEDs, the following are suggested locations.
#define BOARD_BUTTON_PIN          27
#define BOARD_LED_PIN             28

#define BOARD_NR_USARTS           3
#define BOARD_USART1_TX_PIN       19
#define BOARD_USART1_RX_PIN       18
#define BOARD_USART2_TX_PIN       2
#define BOARD_USART2_RX_PIN       3
#define BOARD_USART3_TX_PIN       11
#define BOARD_USART3_RX_PIN       13

#define BOARD_NR_SPI              2
#define BOARD_SPI1_NSS_PIN        4
#define BOARD_SPI1_MOSI_PIN       7
#define BOARD_SPI1_MISO_PIN       6
#define BOARD_SPI1_SCK_PIN        5
#define BOARD_SPI2_NSS_PIN        12
#define BOARD_SPI2_MOSI_PIN       17
#define BOARD_SPI2_MISO_PIN       14
#define BOARD_SPI2_SCK_PIN        15

#define BOARD_NR_GPIO_PINS        35
#define BOARD_NR_PWM_PINS         16
#define BOARD_NR_ADC_PINS         10
#define BOARD_NR_USED_PINS         4

#define BOARD_JTMS_SWDIO_PIN      32
#define BOARD_JTCK_SWCLK_PIN      31
#define BOARD_JTDI_PIN            30
#define BOARD_JTDO_PIN            29
#define BOARD_NJTRST_PIN          28

// The board has no USB DISK pin, only a jumper, so we use a non existent GPIO.
#define BOARD_USB_DISC_DEV        GPIOC
#define BOARD_USB_DISC_BIT        0

enum {
    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PB0, PB1, PB2, PB10, PB12, PB11, PB14,
    PB13, PA8, PB15, PA10, PA9, PC15, PC14, PC13, PB9, PB8, PB7, PB6, PB5, PB4, PB3,
    PA15, PA14, PA13, PA12, PA11
};

#endif
