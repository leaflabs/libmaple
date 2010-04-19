/* insert license */
#ifndef __DESCRIPTORS_H
#define __DESCRIPTORS_H


#include "usb_lib.h"

#if defined(__cplusplus)
  extern "C" {
#endif

#define CDC_FUCNTIONAL_DESCRIPTOR(DataSize)	\
  struct					\
  {						\
    uint8 bLength;				\
    uint8 bDescriptorType;			\
    uint8 SubType;				\
    uint8 Data[DataSize];			\
  }

typedef struct {
  uint8                 bLength;
  uint8                 bDescriptorType;
  uint16                bcdUSB;
  uint8                 bDeviceClass;
  uint8                 bDeviceSubClass;
  uint8                 bDeviceProtocol;
  uint8                 bMaxPacketSize0;
  uint16                idVendor;
  uint16                idProduct;
  uint16                bcdDevice;
  uint8                 iManufacturer;
  uint8                 iProduct;
  uint8                 iSerialNumber;
  uint8                 bNumConfigurations;
} USB_Descriptor_Device;

typedef struct {
  uint8_t                 bLength;
  uint8_t                 bDescriptorType;
  uint16_t                wTotalLength;
  uint8_t                 bNumInterfaces;
  uint8_t                 bConfigurationValue;
  uint8_t                 iConfiguration;
  uint8_t                 bmAttributes;
  uint8_t                 bMaxPower;
} USB_Descriptor_Config_Header;

typedef struct {
  uint8_t                 bLength;
  uint8_t                 bDescriptorType;
  uint8_t                 bInterfaceNumber;
  uint8_t                 bAlternateSetting;
  uint8_t                 bNumEndpoints;
  uint8_t                 bInterfaceClass;
  uint8_t                 bInterfaceSubClass;
  uint8_t                 bInterfaceProtocol;
  uint8_t                 iInterface;
} USB_Descriptor_Interface;

typedef struct {
  uint8_t                 bLength;
  uint8_t                 bDescriptorType;
  uint8_t                 bEndpointAddress;
  uint8_t                 bmAttributes;
  uint16_t                wMaxPacketSize;
  uint8_t                 bInterval;
} USB_Descriptor_Endpoint;

typedef struct {
  USB_Descriptor_Config_Header        Header;
  USB_Descriptor_Interface            CCI_Interface;
  CDC_FUNCTIONAL_DESCRIPTOR(2)        CDC_Functional_IntHeader;
  CDC_FUNCTIONAL_DESCRIPTOR(2)        CDC_Functional_CallManagement;
  CDC_FUNCTIONAL_DESCRIPTOR(1)        CDC_Functional_ACM;
  CDC_FUNCTIONAL_DESCRIPTOR(2)        CDC_Functional_Union;
  USB_Descriptor_Endpoint             ManagementEndpoint;
  USB_Descriptor_Interface            DCI_Interface;
  USB_Descriptor_Endpoint             DataOutEndpoint;
  USB_Descriptor_Endpoint             DataInEndpoint;
} USB_Descriptor_Configuration;


#if defined(__cplusplus)
  }
#endif

#endif  // __DESCRIPTORS_H
