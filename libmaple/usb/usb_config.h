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

#ifndef __USB_CONFIG_H
#define __USB_CONFIG_H

/******************************************************************************
 ******************************************************************************
 ***
 ***   HACK ALERT
 ***
 ***   FIXME FIXME FIXME FIXME
 ***
 ***   A bunch of board-specific #defines that are only used by the
 ***   USB routines got put into libmaple.h for what appear to be
 ***   historical reasons.  I'm [mbolivar] putting them in here for
 ***   now, so that we can treat the usb/ directory as a black box,
 ***   freeing the rest of libmaple/ to be implemented as a
 ***   general-purpose STM32 library. All of this REALLY needs to get
 ***   moved into wirish when we get a chance to redo the USB stack.
 ***
 ******************************************************************************
 *****************************************************************************/

#define VCOM_ID_VENDOR            0x1EAF
#define VCOM_ID_PRODUCT           0x0004
#define RESET_DELAY               (100000)
#define USB_CONFIG_MAX_POWER      (100 >> 1)

#if !(defined(BOARD_maple) || defined(BOARD_maple_RET6) ||              \
      defined(BOARD_maple_mini) || defined(BOARD_maple_native))

#warning ("Warning! The USB stack relies on LeafLabs board-specific "   \
          "configuration right now.  If you want, you can pretend "     \
          "you're one of our boards; i.e., #define BOARD_maple, "       \
          "BOARD_maple_mini, etc.  according to what matches your MCU " \
          "best. You should also take a look at "                       \
          "libmaple/usb/descriptors.c; "                                \
          "we make some assumptions there that you probably won't like.")

#endif

/******************************************************************************
 ******************************************************************************
 ***
 ***   END HACK
 ***
 ******************************************************************************
 *****************************************************************************/


/* choose addresses to give endpoints the max 64 byte buffers */
#define USB_BTABLE_ADDRESS        0x00
#define VCOM_CTRL_EPNUM           0x00
#define VCOM_CTRL_RX_ADDR         0x40
#define VCOM_CTRL_TX_ADDR         0x80
#define VCOM_CTRL_EPSIZE          0x40

#define VCOM_TX_ENDP              1
#define VCOM_TX_EPNUM             0x01
#define VCOM_TX_ADDR              0xC0
#define VCOM_TX_EPSIZE            0x40

#define VCOM_NOTIFICATION_ENDP    2
#define VCOM_NOTIFICATION_EPNUM   0x02
#define VCOM_NOTIFICATION_ADDR    0x100
#define VCOM_NOTIFICATION_EPSIZE  0x40

#define VCOM_RX_ENDP              3
#define VCOM_RX_EPNUM             0x03
#define VCOM_RX_ADDR              0x110
#define VCOM_RX_EPSIZE            0x40
#define VCOM_RX_BUFLEN            (VCOM_RX_EPSIZE*3)

#define bMaxPacketSize            0x40  /* 64B, maximum for USB FS Devices */

#define NUM_ENDPTS                0x04

/* handle CTRM, WKUPM, SUSPM, ERRM, SOFM, ESOFM, RESETM */
#define ISR_MSK                   0xBF00

#define F_SUSPEND_ENABLED 1

#endif
