/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the SPI FullDuplex_SoftNSS Example.
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
This example provides a description of how to set a communication between the two
SPIs in full-duplex mode and performs a transfer from Master to Slave and then 
Slave to Master in the same application with software NSS management.
Both SPIs are configured with 8bit data frame and a 9Mbit/s communication speed.
In the first phase, the master SPI1 starts the SPI1_Buffer_Tx transfer while the 
slave SPI2 transmit SPI2_Buffer_Tx. Once the transfer is completed a comparison 
is done and TransferStatus1 and TransferStatus2 gives the data transfer status for
each data transfer direction where it is PASSED if transmitted and received data 
are the same otherwise it is FAILED.
As the NSS pin is managed by software, this permit to SPI1 to become slave and SPI2
to become master whithout hardware modification
In the second step, the slave SPI1 starts the SPI1_Buffer_Tx transfer while the 
master SPI2 transmit SPI2_Buffer_Tx. Once the transfer is completed a comparison 
is done and TransferStatus3 and TransferStatus4 gives the data transfer status for
each data transfer direction where it is PASSED if transmitted and received data 
are the same otherwise it is FAILED.


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
There is no need for any modification when switching between these two boards.

 - Connect SPI1 SCK pin (PA.05) to SPI2 SCK pin	(PB.13)
 - Connect SPI1 MISO pin (PA.06) to SPI2 MISO pin (PB.14)
 - Connect SPI1 MOSI pin (PA.07) to SPI2 MOSI pin (PB.15)


How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_spi.c
  + stm32f10x_rcc.c
  + stm32f10x_gpio.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
