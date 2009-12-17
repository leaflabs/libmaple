/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the SPI CRC Example.
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
SPIs in full-duplex mode and performs a transfer from Master to Slave and  
Slave to Master followed by CRC transmission.

SPI1 is configured as master and SPI2 as slave and both are in full-duplex
configuration mode with 16bit data size and a 4.5Mbit/s communication speed.
CRC calculation is enabled for both SPIs.

After enabling both SPIs, the first data from SPI2_Buffer_Tx is transmitted from
slave followed by the first data from SPI1_Buffer_Tx send by the master. A test 
on RxNE flag is done for both master and slave to check the reception of data on
their respective data register. The same procedure is done for the remaining data
to transfer except the last ones. 

Last data from SPI1_Buffer_Tx is transmitted followed by enabling CRC transmission
for SPI1 and the last data from SPI2_Buffer_Tx is transmitted followed by enabling
CRC transmission for SPI2: user must take care to reduce code on this phase for
high speed communication. 

Last transmitted buffer data and CRC value are then received successively on
master and slave data registers. The received CRC value are stored on CRC1Value
and CRC2Value respectively for SPI1 and SPI2.

Once the transfer is completed a comparison is done and TransferStatus1 and 
TransferStatus2 gives the data transfer status for each data transfer direction 
where it is PASSED if transmitted and received data are the same otherwise it 
is FAILED.
A check of CRC error flag, for the master and the salve, is done after receiving
CRC data.


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

 - Connect SPI1 SCK (PA.05) pin to SPI2 SCK (PB.13) pin
 - Connect SPI1 MISO (PA.06) pin to SPI2 MISO (PB.14) pin
 - Connect SPI1 MOSI (PA.07) pin to SPI2 MOSI (PB.15) pin

Note: in STM3210E-EVAL board, the jumper 14 (USB Disconnect) must be set in 
      position 1<->2 in order to not interfer with SPI2 MISO pin PB14.
       
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_spi.c
  + stm32f10x_rcc.c
  + stm32f10x_gpio.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
