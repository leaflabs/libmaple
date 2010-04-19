/* insert license */

#ifndef __USB_CONFIG_H
#define __USB_CONFIG_H

#define VCOM_ID_VENDOR    0x0110
#define VCOM_ID_PRODUCT   0x1003

#define USB_CONFIG_MAX_POWER      (100 >> 1)

/* choose addresses to give endpoints the max 64 byte buffers */
#define USB_BTABLE_ADDRESS        0x00
#define VCOM_CTRL_EPNUM           0x00
#define VCOM_CTRL_RX_ADDR         0x40
#define VCOM_CTRL_TX_ADDR         0x80
#define VCOM_CTRL_EPSIZE          0x40

#define VCOM_NOTIFICATION_EPNUM   0x01
#define VCOM_NOTIFICATION_ADDR    0xC0
#define VCOM_NOTIFICATION_EPSIZE  0x40

#define VCOM_TX_EPNUM             0x02
#define VCOM_TX_ADDR              0x100
#define VCOM_TX_SIZE              0x040

#define VCOM_RX_EPNUM             0x03
#define VCOM_RX_ADDR              0x140
#define VCOM_RX_EPSIZE            0x40

#endif
