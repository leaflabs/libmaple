/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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
 * @file usb_cdcacm.h
 * @brief USB CDC ACM (virtual serial terminal) support
 */

#ifndef _USB_CDCACM_H_
#define _USB_CDCACM_H_

#include "libmaple_types.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

void usb_cdcacm_enable(gpio_dev*, uint8);
void usb_cdcacm_disable(gpio_dev*, uint8);

void   usb_cdcacm_putc(char ch);
uint32 usb_cdcacm_tx(const uint8* buf, uint32 len);
uint32 usb_cdcacm_rx(uint8* buf, uint32 len);

uint32 usb_cdcacm_data_available(void); /* in RX buffer */
uint16 usb_cdcacm_get_pending(void);

uint8 usb_cdcacm_get_dtr(void);
uint8 usb_cdcacm_get_rts(void);

#ifdef __cplusplus
}
#endif

#endif
