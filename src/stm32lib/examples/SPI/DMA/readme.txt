/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the SPI DMA Example.
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
SPIs in simplex mode and performs a transfer from Master in polling mode to the
Slave in DMA receive mode. The NSS pin is managed by hardware.
Both SPIs are configured with 8bit data frame and a 18Mbit/s communication speed.
The dedicated DMA1 channel4 is configured for SPI2 Rx request to store received data
in SPI2_Buffer_Rx. The master SPI1 is configured in bidirectional mode as transmitter
only. The slave SPI2 is also configured in bidirectional but as receiver only. 
Both master and slave NSS pins are managed by hardware. The SS output is enabled 
for SPI1 to set it as a master and SPI2 as a slave.
After transfering the first SPI1 data an SPI2 RxNE request on DMA1 channel4 is generated
and the received data is stored in SPI2_Buffer_Rx. The same action is done for the rest 
of the buffer.
Once the transfer is completed a comparison is done and TransferStatus gives the
data transfer status where it is PASSED if transmitted and received data 
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

 - Connect SPI2 NSS pin (PB.12) to SPI1 NSS pin	(PA.04)
 - Connect SPI2 SCK pin (PB.13) to SPI1 SCK pin (PA.05)
 - Connect SPI2 MISO pin (PB.14) to SPI1 MOSI pin (PA.07)



How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_spi.c
  + stm32f10x_rcc.c
  + stm32f10x_gpio.c
  + stm32f10x_dma.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
