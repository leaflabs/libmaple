/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the I2C dual addressng mode example.
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
This example provides a description of how to transfer two data buffer from I2C1
to I2C2 using its both addresses in the same application.

The example consist in two parts:
1. First step, the I2C1 master transmitter sends the Tx_Buffer1 data buffer to the 
   slave I2C2 which saves the received data in Rx_Buffer1. I2C2 is addressed in 
   this case by its first slave address I2C2_SLAVE1_ADDRESS7 programmed in the
   I2C2 OAR1 register.
   The transmitted and received buffers are compared to check that all data
   have been correctly transferred.
2. Second step, the I2C2 is now addressed by its second slave address
   I2C2_SLAVE2_ADDRESS7 programmed in the I2C2 OAR2 register. The Tx_Buffer2
   contents are transmitted by the master I2C1 to the slave I2C2 which stores
   them into Rx_Buffer2.
   A second comparison takes place between the transmitted and received buffers.

The communication clock speed is set to 200KHz.


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

 - Connect I2C1 SCL pin (PB.06) to I2C2 SCL pin (PB.10)
 - Connect I2C1 SDA pin (PB.07) to I2C2 SDA pin	(PB.11)
 - Check that a pull-up resistor is connected on one I2C SDA pin
 - Check that a pull-up resistor is connected on one I2C SCL pin

Note: The pull-up resitors are already implemented on the STM3210B-EVAL and
      STM3210E-EVAL evaluation boards.
     

How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_i2c.c
  + stm32f10x_rcc.c
  + stm32f10x_gpio.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
