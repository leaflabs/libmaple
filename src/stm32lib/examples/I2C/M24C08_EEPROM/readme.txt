/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the I2C and M24C08 EEPROM communication example.
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
This example provides a basic example of how to use the I2C software library
and an associate I2C EEPROM driver to communicate with an M24C08 EEPROM.
I2C1 is configured in Master transmitter during write operation and in Master 
receiver during read operation from I2C EEPROM. 
The speed is set to the maximum frequency of 400kHz. This value is defined in 
the I2c_ee.c file, which could be in the range of 0 to 400KHZ.
One I2C EEPROM Block address where the program will write the buffer have to be
selected from the four address available and defined in the I2c_ee.h file. 
The EEPROM address where the program start the write and the read operations is
defined in the main.c file. 

First, the contents of Tx1_Buffer are written to the EEPROM_WriteAddress1 and the
written data are read. The written and the read buffers data are then compared.
Following the read operation, the program wait that the EEPROM reverts to its 
Standby state. A second write operation is, then, performed and this time, Tx2_Buffer
is written to EEPROM_WriteAddress2, which represents the address just after the last 
written one in the first write. After completion of the second write operation, the 
written data are read. The contents of the written and the read	buffers are compared. 


Directory contents
==================
stm32f10x_conf.h  Library Configuration file
stm32f10x_it.c    Interrupt handlers
stm32f10x_it.h    Interrupt handlers header file
main.c            Main program
i2c_ee.c          I2C EEPROM driver
i2c_ee.h          Header for the i2c_ee.c file


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards with addition of the following hardware connection:
   - Connect I2C1 SCL pin (PB.06) to I2C EEPROM SCL (pin6)
   - Connect I2C1 SDA pin (PB.07) to I2C EEPROM SDA (pin5)
   - Check that a pull-up resistor is connected on one I2C SDA pin
   - Check that a pull-up resistor is connected on one I2C SCL pin
   - Connect I2C EEPROM Vcc (pin8) to Vdd
   - Connect I2C EEPROM Vss (pin4) to Vss

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
