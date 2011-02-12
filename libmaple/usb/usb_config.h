/* insert license */

#ifndef __USB_CONFIG_H
#define __USB_CONFIG_H

#include "usb_lib.h"

/* choose addresses to give endpoints the max 64 byte buffers */
#define USB_BTABLE_ADDRESS        0x00
#define VCOM_CTRL_EPNUM           0x00
#define VCOM_CTRL_RX_ADDR         0x40
#define VCOM_CTRL_TX_ADDR         0x80
#define VCOM_CTRL_EPSIZE          0x40

#define VCOM_TX_ENDP              ENDP1
#define VCOM_TX_EPNUM             0x01
#define VCOM_TX_ADDR              0xC0
#define VCOM_TX_EPSIZE            0x40

#define VCOM_NOTIFICATION_ENDP    ENDP2
#define VCOM_NOTIFICATION_EPNUM   0x02
#define VCOM_NOTIFICATION_ADDR    0x100
#define VCOM_NOTIFICATION_EPSIZE  0x40

#define VCOM_RX_ENDP              ENDP3
#define VCOM_RX_EPNUM             0x03
#define VCOM_RX_ADDR              0x110
#define VCOM_RX_EPSIZE            0x40
#define VCOM_RX_BUFLEN            (VCOM_RX_EPSIZE*3)

#define bMaxPacketSize            0x40  /* 64B, maximum for USB FS Devices */

#define NUM_ENDPTS                0x04

/* handle all usb interrupts */
#define ISR_MSK ( CNTR_CTRM    |           \
		  CNTR_WKUPM   |	   \
		  CNTR_SUSPM   |	   \
		  CNTR_ERRM    |	   \
		  CNTR_SOFM    |	   \
		  CNTR_ESOFM   |	   \
		  CNTR_RESETM  )

#define F_SUSPEND_ENABLED 1

#endif
