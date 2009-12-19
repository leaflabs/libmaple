#ifndef _USB_H_
#define _USB_H_

#include <inttypes.h>
#include "util.h"
#include "cortexm3_macro.h"
#include "usb_regs.h"

#ifdef __cpluscplus
extern "C" {
#endif

#define USB_ISR_ADDR              (0x08000090)
#define USB_SERIAL_ENDP_TXADDR    ((uint32_t) 0xC0)
#define USB_SERIAL_ENDP_RXADDR    ((uint32_t) 0x110)
#define USB_SERIAL_ENDP_TX        ((uint16_t) 0x1)
#define USB_SERIAL_ENDP_RX        ((uint16_t) 0x3)
#define USB_SERIAL_BUF_SIZE       (0x40)

void usb_lpIRQHandler(void);  
void usb_userToPMABufferCopy(uint8_t  *pbUsrBuf,
			     uint16_t *wPMABufAddr,
			     uint16_t *wNBytes);
void usb_PMABToUserufferCopy(uint8_t  *pbUsrBuf,
			     uint16_t *wPMABufAddr,
			     uint16_t *wNBytes);
void usb_serialWriteStr(char* str);


#ifdef __cpluscplus
} // extern "C"
#endif
#endif //_USB_H
