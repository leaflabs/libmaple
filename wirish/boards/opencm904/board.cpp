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
 * @file   maple.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Maple PIN_MAP and boardInit().
 */
/*
 *  CM904.cpp ported from CM900.cpp
 *
 *  Created on: 2013. 5. 22.
 *      Author: in2storm
 */

#include <board/board.h>         // For this board's header file

#include <wirish/wirish_types.h> // For stm32_pin_info and its contents
                                 // (these go into PIN_MAP).

#include "boards_private.h"      // For PMAP_ROW(), which makes


void boardInit(void) {

	afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY); //[ROBOTIS] 2013-07-17

	//[ROBOTIS][CHANGE] add here if you want to initialize something
	gpio_set_mode(GPIOB, 9, GPIO_OUTPUT_PP);
	gpio_write_bit(GPIOB, 9,1); //LED off when start board
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {
   /* Top header */
	{GPIOA,   NULL, ADC1,  4, 0,    4}, /* D0/PA4 */
	{GPIOA,   NULL, ADC1,  5, 0,    5}, /* D1/PA5  */
	{GPIOA, TIMER2, ADC1,  0, 1,    0}, /* D2/PA0 */
	{GPIOA, TIMER2, ADC1,  1, 2,    1}, /* D3/PA1 */
	{GPIOA, TIMER2, ADC1,  2, 3,    2}, /* D4/PA2 */
	{GPIOA, TIMER2, ADC1,  3, 4,    3}, /* D5/PA3 */
	{GPIOA, TIMER3, ADC1,  6, 1,    6}, /* D6/PA6 */
	{GPIOA, TIMER3, ADC1,  7, 2,    7}, /* D7/PA7 */
	{GPIOB, TIMER3, ADC1,  0, 3,    8}, /* D8/PB0 */
	{GPIOB, TIMER3, ADC1,  1, 4,    9}, /* D9/PB1 */

	{GPIOA, TIMER1, NULL,  8, 1, ADCx}, /* D10/PA8 */
	{GPIOA, TIMER1, NULL,  9, 2, ADCx}, /* D11/PA9 */
	{GPIOA, TIMER1, NULL, 10, 3, ADCx}, /* D12/PA10 */
	{GPIOB, TIMER4, NULL,  8, 3, ADCx}, /* D13/PB8 */
	{GPIOB, TIMER4, NULL,  9, 4, ADCx}, /* D14/PB9 (LED)*/
//	{GPIOA,   NULL, NULL, 13, 0, ADCx}, /* D15/PA13 */
//	{GPIOA,   NULL, NULL, 14, 0, ADCx}, /* D16/PA14 */
	{GPIOA,   NULL, NULL, 15, 0, ADCx}, /* D15/PA15 */
	{GPIOB,   NULL, NULL,  3, 0, ADCx}, /* D16/PB3  */
	{GPIOB,   NULL, NULL,  4, 0, ADCx}, /* D17/PB4  */
	{GPIOB,   NULL, NULL, 12, 0, ADCx}, /* D18/PB12 */	
	{GPIOB,   NULL, NULL, 13, 0, ADCx}, /* D19/PB13 */
	
	{GPIOB,   NULL, NULL, 14, 0, ADCx}, /* D20/PB14 */
	{GPIOB,   NULL, NULL, 15, 0, ADCx}, /* D21/PB15 */
	{GPIOC,   NULL, NULL, 14, 0, ADCx}, /* D22/PC14 */
	{GPIOC,   NULL, NULL, 15, 0, ADCx}, /* D23/PC15 (User Button)*/
	{GPIOB,   NULL, NULL, 10, 0, ADCx}, /* D24/PB10 */
	{GPIOB,   NULL, NULL, 11, 0, ADCx}, /* D25/PB11 */
/*
 * Hidden pin map
 * the below pins are used carefully, need to check schematic of OpenCM9.04
 * */
	{GPIOA,   NULL, NULL, 13, 0, ADCx}, /* D26/PA13 JTAG SWDIO*/
	{GPIOA,   NULL, NULL, 14, 0, ADCx}, /* D27/PA14 JTAG SWDCLK*/
	{GPIOB,   NULL, NULL,  5, 0, ADCx}, /* D28/PB5 DXL DIR*/
	{GPIOB, TIMER4, NULL,  6, 1, ADCx}, /* D29/PB6 DXL TXD*/
	{GPIOB, TIMER4, NULL,  7, 2, ADCx} /* D30/PB7 DXL RXD -> dont work as output and input*/

};

extern const uint8 boardPWMPins[] __FLASH__ = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 27, 28
};

extern const uint8 boardADCPins[] __FLASH__ = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

extern const uint8 boardUsedPins[] __FLASH__ = {
    BOARD_LED_PIN, BOARD_BUTTON_PIN
};


