/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the SPI_I2S_Switch Example.
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
SPIs in I2S mode, and how to switch between SPI and I2S modes, performing a 
transfer from Master to Slave in I2S modes then a transfer from master to slave 
in SPI mode and finally a transfer from Slave to Master in I2S mode.

I2S2 is configured as master transmitter and I2S3 as slave reciever and both are 
in Phillips standard configuration with 16bit data size in 32bit packet length 
and 48KHz audio frequnecy.

In the first phase, the master I2S2 starts the I2S2_Buffer_Tx transfer while the 
slave I2S3 receieves and loads the values in I2S3_Buffer_Rx. Once the transfer is 
completed a comparison is done and TransferStatus1 gives the data transfer status 
where it is PASSED if transmitted and received data are the same otherwise it is 
FAILED.

In the second step, both preripherals are configured in SPI modes (simplex 
communication) and SPI2_Buffer_Tx transfer is performed in simplex mode from SPI2 to
SPI3.Once the transfer is completed a comparison is done and TransferStatus2 gives 
the data transfer status where it is PASSED if transmitted and received data are 
the same otherwise it is FAILED.
As the master/slave mode is managed by software (the master is the clock (CK and WS) 
generator), this allows to I2S2 to become slave transmitter and I2S3 to become master 
receiver whithout hardware modification. 

In the third step, the slave I2S2 prepares the first data to be sent before the 
master is enabled. Once the master is enabled, the clocks are released from the 
master and the data are released on the slave. Once the transfer is completed 
a comparison is done and TransferStatus3 gives the data transfer status where it 
is PASSED if transmitted and received data are the same otherwise it is FAILED.


Directory contents
==================
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Header for stm32f10x_it.c
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210E-EVAL evaluation board and can be 
easily tailored to any other hardware.

 - Connect I2S2 WS (PB.12) pin to I2S3 WS (PA.15) pin
 - Connect I2S2 CK (PB.13) pin to I2S3 CK (PB.03) pin
 - Connect I2S2 SD (PB.15) pin to I2S3 SD (PB.05) pin

Since some SPI3/I2S3 pins are shared with JTAG pins (SPI3_NSS/I2S3_WS with JTDI 
and SPI3_SCK/I2S3_CK with JTDO), they are not controlled by the I/O controller
and are reserved for JTAG usage (after each Reset).
For this purpose prior to configure the SPI3/I2S3 pins, the user has to disable
the JTAG and use the SWD interface (when debugging the application), or disable
both JTAG/SWD interfaces (for standalone application).


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
