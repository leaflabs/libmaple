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
 *  Created: 12/18/09 02:38:35
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
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

#ifdef __cplusplus
} // extern "C"
#endif


#endif

