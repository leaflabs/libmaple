#ifndef _USB_H_
#define _USB_H_

#include <inttypes.h>
#include "util.h"
#include "cortexm3_macro.h"
#include "usb_regs.h"
#include "bootVect.h"

#define USB_ISR_ADDR              (0x08000090)
#define USB_SERIAL_ENDP_TXADDR    ((uint32_t) 0xC0)
#define USB_SERIAL_ENDP_RXADDR    ((uint32_t) 0x110)
#define USB_SERIAL_ENDP_TX        ((uint16_t) 0x1)
#define USB_SERIAL_ENDP_RX        ((uint16_t) 0x3)
#define USB_SERIAL_BUF_SIZE       (0x40)

#ifdef __cplusplus
extern "C" {
#endif

void usb_lpIRQHandler(void);  
void usb_userToPMABufferCopy(u8  *pbUsrBuf,u16 wPMABufAddr,u16 wNBytes);
void usb_PMAToUserBufferCopy(u8  *pbUsrBuf,u16 wPMABufAddr,u16 wNBytes);
void usb_serialWriteStr(const char *outStr);
void usb_serialWriteChar(unsigned char ch);
uint8_t usb_serialGetRecvLen();
void usb_copyRecvBuffer(unsigned char* dest, uint8_t len);

#ifdef __cplusplus
} // extern "C"
#endif
#endif //_USB_H
