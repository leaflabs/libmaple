/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the DMA SPI example.
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
This example provides a description of how to use four DMA channels to transfer a 
data buffer from memory to SPI2 through SPI1 and a second data buffer from memory
to SPI1 through SPI2 in ful-duplex mode.

The NSS pins are configured by software to set SPI1 as master and SPI2 as slave.
DMA1 Channel2 and Channel4 are configured to store, respectively, the data
received by SPI1 into the SPI1_Buffer_Rx and the data received by SPI2 into the
SPI2_Buffer_Rx. 
DMA1 Channel3 is configured to transfer data from the SPI1_Buffer_Tx to	the
SPI1_DR register for transmission to SPI2. DMA1 Channel5 is configured to transfer
data from the SPI2_Buffer_Tx to the SPI2_DR register for transmission to SPI1.

As soon as the two SPIs TxDMAEN and RxDMAEN bits are set in the SPI1_CR2 and
SPI2_CR2 registers, DMA1 Channel3 and Channel5 start transmitting, respectively,
the SPI1 and SPI2 Tx buffers at the same time. At the same moment, the data received
on SPI1 and SPI2 are stored by DMA1 Channel2 and Channel4 to the SPI1 and SPI2
Rx buffers, respectively.

A polling on all Transfer complete flags are done for all used DMA channels to
check the end of all DMA channels transfers. The last received data on SPI1 and
SPI2 are the CRC values sent by each SPI to the other. The transmitted and received
buffers are compared to check that all data have been correctly transferred.


Directory contents
==================
stm32f10x_conf.h  Library Configuration file
stm32f10x_it.c    Interrupt handlers
stm32f10x_it.h    Interrupt handlers header file
main.c            Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.

 - Connect SPI1 SCK pin (PA.05) to SPI2 SCK pin	(PB.13)
 - Connect SPI1 MISO pin (PA.06) to SPI2 MISO pin (PB.14)
 - Connect SPI1 MOSI pin (PA.07) to SPI2 MOSI pin (PB.15)

Note: in STM3210E-EVAL board, the jumper 14 (USB Disconnect) must be set in 
      position 1<->2 in order to not interfer with SPI2 MISO pin PB14.
      

How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_dma.c
  + stm32f10x_rcc.c
  + stm32f10x_spi.c
  + stm32f10x_nvic.c
  + stm32f10x_gpio.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
