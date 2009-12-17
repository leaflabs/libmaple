/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the USART Multi Processor Example.
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
This example provides a description of how to use the USART in multi-processor mode.
First, the USART1 and USART2 address are set to 0x1 and 0x2. The USART1 send 
continusouly the character 0x33 to the USART2. The USART2 toggle LD1, LD2, LD3 
and LD4 pins while receiving 0x33.

When a falling edge is applied on Key Button EXTI line, an interrupt is generated
and in the EXTI9_5_IRQHandler routine, the USART2 is entred in mute mode and still
in this mode (no LED toggling) until a rising edge is applied on EXTI Line 0.
In this interrupt routine the USART1 send the character of address mark (0x102)
to wakeup USART2. The LED restart toggling.

USART1 and USART2 configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 9 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled


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
    - Connect a null-modem female/female RS232 cable between CN5 and CN6.
    - Note: in this case USART2 Tx and Rx pins are remapped by software on 
            PD.05 and PD.06 respectively. 
    - Use Key push-button connected to pin PB.09 (EXTI Line9)
    - Use Wakeup push-button connected to pin PA.00 (EXTI Line0)
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins             
 
 + STM3210E-EVAL
    - Connect a null-modem female/female RS232 cable between CN12 and CN8.
    - Use Key push-button connected to pin PG.08 (EXTI Line8)
    - Use Wakeup push-button connected to pin PA.00 (EXTI Line0)
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - Make sure that the Jumper 4 (JP4) is in position 1<-->2.    
   
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
  + stm32f10x_exti.c
  
- Link all compiled files and load your image into target memory
- Run the example

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
