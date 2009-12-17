/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the Lib_DEBUG Example.
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
This example demonstrates the STM32F10x Firmware Library DEBUG mode.  

To enter Debug mode you have to define the label DEBUG in the stm32f10x_conf.h file.
This creates a pointer to the peripheral structure in SRAM. Debugging consequently
becomes easier and all register settings can be obtained by dumping a peripheral variable.
When the Debug mode is selected, the assert_param macro is expanded and run-time checking 
is enabled in the firmware library code. The run-time checking allows checking that
all the library functions input value lies within the parameter allowed values.

The associated program simulates wrong parameter passed to library function and the
source of the error is printed on Hyperterminal (through USART1).


Note:
The Debug mode increases the code size and reduces the code performance. For this
reason, it is recommended to used it only when debugging the application and to
remove it from the final application code.


Directory contents
==================
stm32f10x_conf.h  Library Configuration file
stm32f10x_it.c    Interrupt handlers
stm32f10x_it.h    Header for stm32f10x_it.c
main.c            Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.

 + STM3210B-EVAL 
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      CN6 and PC serial port.
 
 + STM3210E-EVAL
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      CN12 and PC serial port.
 

 - Hyperterminal configuration:
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - BaudRate = 115200 baud
    - flow control: None 

      
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  + stm32f10x_usart.c
      
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
