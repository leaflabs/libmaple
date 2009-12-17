/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the SPI Simplex_Intrerrupt Example.
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
This example provides a description of how to set a communication between two
SPIs in simplex mode and performs a data buffer transfer from Master to Slave 
using TxE interrupt for master and RxNE interrupt for slave.

Both SPIs are configured with 8bit data frame and a 9Mbit/s communication speed.
SPI1 is configured to be a master transmitter and SPI2 as slave receiver. 
The TxE interrupt is enabled for the master and the RxNE interrupt is enabled for
the slave.

Once both SPIs are enabled, first TxE interrupt is generated for the master
and in its interrupt service routine the first data is sent from SPI1_Buffer_Tx. 
Once this data is received by the slave a RxNE interrupt is generated and in the 
routine this data is stored in the SPI2_Buffer_Rx.

The same procedure is followed for the remaining SPI1_Buffer_Tx data.
Once all data buffer are received by the slave the TxE interrupt is disabled.
A comparison is done and TransferStatus gives the data transfer status where 
it is PASSED if transmitted and received data are the same otherwise it is FAILED.


Directory contents
==================
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Header for stm32f10x_it.c
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
There is no need for any modification when switching between these two boards.

 - Connect SPI1 SCK pin (PA.05) to SPI2 SCK pin (PB.13)
 - Connect SPI1 MOSI pin (PA.07) to SPI2 MISO pin (PB.14)


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
