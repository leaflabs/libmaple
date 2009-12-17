/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the I2S Interrupt Example.
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
SPIs in I2S mode using interrupts and performing a transfer from Master to Slave.

In the first step, I2S2 is configured as master transmitter and I2S3 as slave 
reciever and both are in Phillips standard configuration with 16bit extended to 
32 bit data packet and 48KHz audio frequnecy. 

The I2S2 transmit interrupt and the I2S3 receive interrupt are both enabled. And
in these interrupts subroutines, the I2S2_Buffer_Tx is transmitted and the received
values are loaded in the I2S3_Buffer_Rx buffer. Only the significant 16 MSBs are
sent and received, while the 32 packet remaining 16 LSBs are filled with 0 values
and don't generate any interrupt.

Once the transfer is completed a comparison is done and TransferStatus1 gives the 
data transfer status where it is PASSED if transmitted and received data are the 
same otherwise it is FAILED.

In the second step both peripherals are configured in I2S Phillips standard 24 bits
data length in 32 bits packets and 16KHz audio frequency. The interrupts are
enabled and the transfer is performed from the I2S2 master to the I2S3 slave.
The 24 bits are transmited then the 8 remaining LSBs are filled automatically
with 0 values.

Once the transfer is completed a comparison is done (on the 24 MSBs only, the 8 
LSBs are replaced by 0) and TransferStatus2 gives the data transfer status where 
it is PASSED if transmitted and received data are the same otherwise it is FAILED.


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
