/* insert license */

#ifndef __USB_H_
#define __USB_H_

#include "usb_config.h"
#include "usb_callbacks.h"
#include "usb_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
  {
    RESUME_EXTERNAL,
    RESUME_INTERNAL,
    RESUME_LATER,
    RESUME_WAIT,
    RESUME_START,
    RESUME_ON,
    RESUME_OFF,
    RESUME_ESOF
  } RESUME_STATE;

typedef enum 
  {
    UNCONNECTED,
    ATTACHED,
    POWERED,
    SUSPENDED,
    ADDRESSED,
    CONFIGURED
  } DEVICE_STATE;

  void setupUSB(void);
  void usbSuspend(void);
  void usbResumeInit(void);
  void usbResume(RESUME_STATE);
  
  RESULT usbPowerOn(void);
  RESULT usbPowerOff(void);
  
  void usbDsbISR(void);
  void usbEnbISR(void);

  /* overloaded ISR routine, this is the main usb ISR */
  void usb_lpIRQHandler(void);

#ifdef __cplusplus
} // extern "C"
#endif
#endif //_USB_H
