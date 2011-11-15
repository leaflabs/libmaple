/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
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

/*
 * NOTE: This API is _unstable_ and will change drastically over time.
 */

#ifndef _LIBMAPLE_USB_H_
#define _LIBMAPLE_USB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <libmaple/libmaple_types.h>
#include <libmaple/rcc.h>

#ifndef USB_ISR_MSK
/* Handle CTRM, WKUPM, SUSPM, ERRM, SOFM, ESOFM, RESETM */
#define USB_ISR_MSK 0xBF00
#endif

typedef enum usb_dev_state {
    USB_UNCONNECTED,
    USB_ATTACHED,
    USB_POWERED,
    USB_SUSPENDED,
    USB_ADDRESSED,
    USB_CONFIGURED
} usb_dev_state;

/* Encapsulates global state formerly handled by usb_lib/ */
typedef struct usblib_dev {
    uint32 irq_mask;
    void (**ep_int_in)(void);
    void (**ep_int_out)(void);
    usb_dev_state state;
    rcc_clk_id clk_id;
} usblib_dev;

extern usblib_dev *USBLIB;

void usb_init_usblib(usblib_dev *dev,
                     void (**ep_int_in)(void),
                     void (**ep_int_out)(void));

static inline uint8 usb_is_connected(usblib_dev *dev) {
    return dev->state != USB_UNCONNECTED;
}

static inline uint8 usb_is_configured(usblib_dev *dev) {
    return dev->state == USB_CONFIGURED;
}

#ifdef __cplusplus
}
#endif

#endif
