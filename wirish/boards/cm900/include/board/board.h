
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


/*
 * CM900.h
 *
 *  Created on: 2012. 10. 14.
 *      Author: ROBOTIS[sm6787@robotis.com]
 *      ported from maple.h(leaflabs.com)
 *      @brief  Private include file for cm-900 in boards.h
 */

#ifndef CM_900_H_
#define CM_900_H_

//#include "gpio.h"


#define CYCLES_PER_MICROSECOND  72
#define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */
/*
 * [ROBOTIS][CHANGE] CM-900 Do not have built-in button.
 * 2013-04-22
 * */
#define BOARD_BUTTON_PIN        23//38
#define BOARD_LED_PIN           16

/* Number of USARTs/UARTs whose pins are broken out to headers */
//#define BOARD_NR_USARTS         3

/* Default USART pin numbers (not considering AFIO remap) */
#define BOARD_USART1_TX_PIN     9   //D9(PA9)
#define BOARD_USART1_RX_PIN     10	//D10(PA10)
#define BOARD_USART2_TX_PIN     2	//D2 (PA2)
#define BOARD_USART2_RX_PIN     3	//D3 (PA3)
#define BOARD_USART3_TX_PIN     24	//D24 (PB10)
#define BOARD_USART3_RX_PIN     25	//D25 (PB11)

/* Number of SPI ports */
//#define BOARD_NR_SPI            2

/* Default SPI pin numbers (not considering AFIO remap) */
#define BOARD_SPI1_NSS_PIN      10 //D10 (PA4)
#define BOARD_SPI1_MOSI_PIN     11 //D11 PA7
#define BOARD_SPI1_MISO_PIN     12 //D12 PA6
#define BOARD_SPI1_SCK_PIN      13 //D13 PA5
#define BOARD_SPI2_NSS_PIN      26 //D26 PB12
#define BOARD_SPI2_MOSI_PIN     29 //D29 PB15
#define BOARD_SPI2_MISO_PIN     28 //D28 PB14
#define BOARD_SPI2_SCK_PIN      27 //D27 PB13

/* Total number of GPIO pins that are broken out to headers and
 * intended for general use. */
#define BOARD_NR_GPIO_PINS      32//44

/* Number of pins capable of PWM output */
#define BOARD_NR_PWM_PINS       15

/* Number of pins capable of ADC conversion */
#define BOARD_NR_ADC_PINS       10

/* Number of pins already connected to external hardware.  For Maple,
 * these are just BOARD_LED_PIN and BOARD_BUTTON_PIN. */
#define BOARD_NR_USED_PINS       1

/* Debug port pins */
#define BOARD_JTMS_SWDIO_PIN    11
#define BOARD_JTCK_SWCLK_PIN    12
#define BOARD_JTDI_PIN          13
#define BOARD_JTDO_PIN          17
#define BOARD_NJTRST_PIN        18

#define BOARD_USB_DISC_DEV      GPIOC
#define BOARD_USB_DISC_BIT      13

void boardInit(void);

#define BOARD_DYNAMIXEL_DIR     19
#define BOARD_DYNAMIXEL_TX      20
#define BOARD_DYNAMIXEL_RX      21

#endif /* CM_900_H_ */
