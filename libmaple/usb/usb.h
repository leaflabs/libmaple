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

#ifndef _USB_H_
#define _USB_H_

#include "libmaple_types.h"

#ifdef __cplusplus
extern "C" {
#endif

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

/* Encapsulates global state formerly handled by usb_lib/
 * functionality */
typedef struct usblib_dev {
    uint32 irq_mask;
    void (**ep_int_in)(void);
    void (**ep_int_out)(void);
    usb_dev_state state;
} usblib_dev;

extern usblib_dev *USBLIB;

/*
 * Convenience routines, etc.
 */

typedef enum {
    RESUME_EXTERNAL,
    RESUME_INTERNAL,
    RESUME_LATER,
    RESUME_WAIT,
    RESUME_START,
    RESUME_ON,
    RESUME_OFF,
    RESUME_ESOF
} RESUME_STATE;

void usb_init_usblib(void (**ep_int_in)(void), void (**ep_int_out)(void));

void usbSuspend(void);
void usbResumeInit(void);
void usbResume(RESUME_STATE);

/* overloaded ISR routine, this is the main usb ISR */
void __irq_usb_lp_can_rx0(void);
void usbWaitReset(void);

uint8 usbIsConnected(void);
uint8 usbIsConfigured(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _USB_H_
