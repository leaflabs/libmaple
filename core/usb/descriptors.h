/* insert license */
#ifndef __DESCRIPTORS_H
#define __DESCRIPTORS_H


#include "libmaple.h"
#include "usb_lib.h"

#define USB_DESCRIPTOR_TYPE_DEVICE        0x01
#define USB_DESCRIPTOR_TYPE_CONFIGURATION 0x02
#define USB_DESCRIPTOR_TYPE_STRING        0x03
#define USB_DESCRIPTOR_TYPE_INTERFACE     0x04
#define USB_DESCRIPTOR_TYPE_ENDPOINT      0x05

#define USB_DEVICE_CLASS_CDC              0x02
#define USB_DEVICE_SUBCLASS_CDC           0x00

#define USB_CONFIG_ATTR_BUSPOWERED        0b10000000
#define USB_CONFIG_ATTR_SELF_POWERED       0b11000000

#define EP_TYPE_INTERRUPT                 0x03
#define EP_TYPE_BULK                      0x02

#define USB_DESCRIPTOR_ENDPOINT_IN        0x80
#define USB_DESCRIPTOR_ENDPOINT_OUT       0x00

#define USB_DESCRIPTOR_STRING_LEN(x) (2 + (x << 1))


#if defined(__cplusplus)
extern "C" {
#endif

#define USB_DESCRIPTOR_STRING(len)		\
  struct {					\
    uint8 bLength;				\
    uint8 bDescriptorType;			\
    uint16 bString[len];			\
  }

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
  /* config header */
  uint8_t                 bLength;
  uint8_t                 bDescriptorType;
  uint16_t                wTotalLength;
  uint8_t                 bNumInterfaces;
  uint8_t                 bConfigurationValue;
  uint8_t                 iConfiguration;
  uint8_t                 bmAttributes;
  uint8_t                 bMaxPower;

  USB_Descriptor_Interface            CCI_Interface;
  struct {						
    uint8 bLength;				
    uint8 bDescriptorType;			
    uint8 SubType;				
    uint8 Data[2];			
  }                                   CDC_Functional_IntHeader;
  struct {						
    uint8 bLength;				
    uint8 bDescriptorType;			
    uint8 SubType;				
    uint8 Data[2];			
  }                                   CDC_Functional_CallManagement;
  struct {						
    uint8 bLength;				
    uint8 bDescriptorType;			
    uint8 SubType;				
    uint8 Data[1];			
  }                                   CDC_Functional_ACM;
  struct {						
    uint8 bLength;				
    uint8 bDescriptorType;			
    uint8 SubType;				
    uint8 Data[2];			
  }                                   CDC_Functional_Union;

  /*
  USB_Descriptor_Endpoint             ManagementEndpoint;
  */
  uint8_t                 EP1_bLength;
  uint8_t                 EP1_bDescriptorType;
  uint8_t                 EP1_bEndpointAddress;
  uint8_t                 EP1_bmAttributes;
  uint8_t                 EP1_wMaxPacketSize0;
  uint8_t                 EP1_wMaxPacketSize1;
  uint8_t                 EP1_bInterval;

  /*
  USB_Descriptor_Interface            DCI_Interface;
  */

  uint8_t                 DCI_bLength;
  uint8_t                 DCI_bDescriptorType;
  uint8_t                 DCI_bInterfaceNumber;
  uint8_t                 DCI_bAlternateSetting;
  uint8_t                 DCI_bNumEndpoints;
  uint8_t                 DCI_bInterfaceClass;
  uint8_t                 DCI_bInterfaceSubClass;
  uint8_t                 DCI_bInterfaceProtocol;
  uint8_t                 DCI_iInterface;

  /*
  USB_Descriptor_Endpoint             DataOutEndpoint;
  USB_Descriptor_Endpoint             DataInEndpoint;
  */

  uint8_t                 EP2_bLength;
  uint8_t                 EP2_bDescriptorType;
  uint8_t                 EP2_bEndpointAddress;
  uint8_t                 EP2_bmAttributes;
  uint8_t                 EP2_wMaxPacketSize0;
  uint8_t                 EP2_wMaxPacketSize1;
  uint8_t                 EP2_bInterval;

  uint8_t                 EP3_bLength;
  uint8_t                 EP3_bDescriptorType;
  uint8_t                 EP3_bEndpointAddress;
  uint8_t                 EP3_bmAttributes;
  uint8_t                 EP3_wMaxPacketSize0;
  uint8_t                 EP3_wMaxPacketSize1;
  uint8_t                 EP3_bInterval;

  
}USB_Descriptor_Config;
 
  typedef struct {
    uint8          bLength;
    uint8          bDescriptorType;
    uint16         bString[];
  } USB_Descriptor_String;

extern const USB_Descriptor_Device usbVcomDescriptor_Device;
extern const USB_Descriptor_Config usbVcomDescriptor_Config;

extern uint8 usbVcomDescriptor_LangID[USB_DESCRIPTOR_STRING_LEN(1)];
extern uint8 usbVcomDescriptor_iManufacturer[USB_DESCRIPTOR_STRING_LEN(8)];
extern uint8 usbVcomDescriptor_iProduct[USB_DESCRIPTOR_STRING_LEN(8)];

#if defined(__cplusplus)
  }
#endif

#endif  // __DESCRIPTORS_H
