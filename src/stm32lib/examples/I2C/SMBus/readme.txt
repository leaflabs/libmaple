/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the I2C SMBus mode example.
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
This example provides a description of how to send an ARP command from I2C1 to
I2C2 in SMBus mode.

After configuring the I2C1 and I2C2 as SMBus Host and Device, respectively, both
I2Cs are enabled. The PEC calculation is enabled for both I2Cs.
The ARP capability is enabled for the slave I2C2. Following the start condition
generation, the master I2C1 sends the SMBus default header and I2C2 responds by
setting its SMBDEFAULT flag. The master I2C1 then issues the "Prepare to ARP"
command to the slave I2C2. PEC transfer is then enabled for both I2Cs, and the
PEC value received on I2C2 is stored into the PEC_Value variable.

A correct transmission leads to obtaining the following variable values:
         - Status = 0x01 (the flag SMBDEFAULT has been set)
         - ReceivedCommand = 0x01 (the Command value has been correctly received)
         
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
  + stm32f10x_nvic.c
  + stm32f10x_gpio.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
