/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the USART Synchronous Example.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

Example description
===================
This example provides a basic communication between USART1 (Synchronous mode) 
and SPI1 using flags.

First, the USART1 sends data from TxBuffer1 buffer to SPI1 using USART1 TXE flag.
Data received, using RXNE flag, by SPI1 is stored in RxBuffer2 then compared with
the sent ones and the result of this comparison is stored in the "TransferStatus1" 
variable.
 
Then, the SPI1 sends data from TxBuffer2 buffer to USART1 using SPI1 TXE flag.
Data received, using RXNE flag, by USART1 is stored in RxBuffer1 then compared with
the sent ones and the result of this comparison is stored in the "TransferStatus2" 
variable.   


USART1 configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  - USART Clock enabled
  - USART CPOL: Clock is active high
  - USART CPHA: Data is captured on the second edge 
  - USART LastBit: The clock pulse of the last data bit is output to the SCLK pin

SPI1 configured as follow:
  - Direction = 2 Lines FullDuplex
  - Mode = Slave Mode
  - DataSize = 8 Bits
  - CPOL = Clock is active high
  - CPHA = Data is captured on the second edge 
  - NSS = NSS Software
  - First Bit = First Bit is the LSB     


Directory contents
==================
stm32f10x_conf.h  Library Configuration file
stm32f10x_it.h    Interrupt handlers header file
stm32f10x_it.c    Interrupt handlers
main.c            Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
There is no need for any modification when switching between these two boards.

Connect USART1_Tx(PA.09) to SPI1_MOSI(PA.07), USART1_Rx(PA.10) to SPI1_MISO(PA.06)
and USART1_CK(PA.08) to SPI1_SCK(PA.05).
 
  
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_usart.c
  + stm32f10x_spi.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c    

- Link all compiled files and load your image into target memory
- Run the example

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
