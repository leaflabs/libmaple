/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the USART IrDA Receive Example.
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
This example provides a basic communication USART3 IrDA receive mode. Four leds
are used to show which byte is received. 

  - LD1 toggle when 0x04 is received
  - LD2 toggle when 0x05 is received
  - LD3 toggle when 0x03 is received
  - LD4 toggle when 0x02 is received
  - LD1, LD2, LD3 and LD4 toggle when 0x01 is received        

USART3 configured as follow:
   - BaudRate = 115200 baud  
   - Word Length = 8 Bits
   - One Stop Bit
   - No parity
   - Hardware flow control disabled (RTS and CTS signals)
   - Receive and transmit enabled

The USART IrDA example provides two IrDA program: transmitter&receiver and requires two boards
to be able to run the full demonstration:
 - one board will act as IrDA transmitter
 - one board will act as IrDA receiver


Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.h       Interrupt handlers header file
stm32f10x_it.c       Interrupt handlers
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use an IrDA tranceiver connected to the USART3 Tx pin (U11 connector, JP5 
      jumper must be fitted).
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins 
 
 + STM3210E-EVAL
    - Use an IrDA tranceiver connected to the USART3 Tx pin (U13 connector, JP21
      and JP22 jumper must be fitted).
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins

  
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_usart.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  
- Link all compiled files and load your image into target memory
- Run the example

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
