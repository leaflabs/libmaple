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
 *  @file usart.h
 *
 *  @brief USART Definitions
 */

#ifndef _USART_H_
#define _USART_H_

#define NR_USARTS           0x3

#ifdef __cplusplus
extern "C"{
#endif

#define USART_MAX_BAUD      225000

void usart_init(uint8 usart_num, uint32 baud);
void usart_disable(uint8 usart_num);

void usart_putstr(uint8 usart_num, const char*);
void usart_putudec(uint8 usart_num, uint32 val);
void usart_putc(uint8 usart_num, uint8 ch);

uint32 usart_data_available(uint8 usart_num);
uint8 usart_getc(uint8 usart_num);
void usart_clear_buffer(uint8 usart_num);

#ifdef __cplusplus
} // extern "C"
#endif


#endif

