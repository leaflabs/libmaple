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
 * @file libmaple/include/libmaple/usb_cdcacm.h
 * @brief USB CDC ACM (virtual serial terminal) support
 *
 * IMPORTANT: this API is unstable, and may change without notice.
 */

#ifndef _LIBMAPLE_USB_CDCACM_H_
#define _LIBMAPLE_USB_CDCACM_H_

#include <libmaple/libmaple_types.h>
#include <libmaple/gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Exposed configuration
 */

#define USB_CDCACM_CTRL_EPNUM           0x00
#define USB_CDCACM_CTRL_RX_ADDR         0x40
#define USB_CDCACM_CTRL_TX_ADDR         0x80
#define USB_CDCACM_CTRL_EPSIZE          0x40

#define USB_CDCACM_TX_ENDP              1
#define USB_CDCACM_TX_EPNUM             0x01
#define USB_CDCACM_TX_ADDR              0xC0
#define USB_CDCACM_TX_EPSIZE            0x40

#define USB_CDCACM_NOTIFICATION_ENDP    2
#define USB_CDCACM_NOTIFICATION_EPNUM   0x02
#define USB_CDCACM_NOTIFICATION_ADDR    0x100
#define USB_CDCACM_NOTIFICATION_EPSIZE  0x40

#define USB_CDCACM_RX_ENDP              3
#define USB_CDCACM_RX_EPNUM             0x03
#define USB_CDCACM_RX_ADDR              0x110
#define USB_CDCACM_RX_EPSIZE            0x40
#define USB_CDCACM_RX_BUFLEN            (USB_CDCACM_RX_EPSIZE*3)

/*
 * CDC ACM Requests
 */

#define USB_CDCACM_SET_LINE_CODING        0x20
#define USB_CDCACM_GET_LINE_CODING        0x21
#define USB_CDCACM_SET_COMM_FEATURE       0x02
#define USB_CDCACM_SET_CONTROL_LINE_STATE 0x22
#define USB_CDCACM_CONTROL_LINE_DTR       (0x01)
#define USB_CDCACM_CONTROL_LINE_RTS       (0x02)

/*
 * CDC ACM interface
 */

void usb_cdcacm_enable(gpio_dev*, uint8);
void usb_cdcacm_disable(gpio_dev*, uint8);

void   usb_cdcacm_putc(char ch);
uint32 usb_cdcacm_tx(const uint8* buf, uint32 len);
uint32 usb_cdcacm_rx(uint8* buf, uint32 len);
uint32 usb_cdcacm_peek(uint8* buf, uint32 len);

uint32 usb_cdcacm_data_available(void); /* in RX buffer */
uint16 usb_cdcacm_get_pending(void);

uint8 usb_cdcacm_get_dtr(void);
uint8 usb_cdcacm_get_rts(void);

/*
 * Hack: hooks for bootloader reset signalling
 */

#define USB_CDCACM_HOOK_RX 0x1
#define USB_CDCACM_HOOK_IFACE_SETUP 0x2

void usb_cdcacm_set_hooks(unsigned hook_flags, void (*hook)(unsigned, void*));

static __always_inline void usb_cdcacm_remove_hooks(unsigned hook_flags) {
    usb_cdcacm_set_hooks(hook_flags, 0);
}

#ifdef __cplusplus
}
#endif

#endif
