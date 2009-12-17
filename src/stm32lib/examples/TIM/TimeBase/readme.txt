/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM Time Base example.
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

This example shows how to configure the TIM peripheral in Output Compare Timing 
mode with the corresponding Interrupt requests for each channel in order to generate
4 different time bases.

The TIMxCLK frequency is set to 36 MHz, the Prescaler is 4 so the TIM2 counter
clock is 7.2 MHz. 

The TIM2 CC1 register value is equal to 49152, 
CC1 update rate = TIM2 counter clock / CCR1_Val = 146.48 Hz,
so the TIM2 Channel 1 generates an interrupt each 6.8ms

The TIM2 CC2 register is equal to 32768, 
CC2 update rate = TIM2 counter clock / CCR2_Val = 219.7 HzHz
so the TIM2 Channel 2 generates an interrupt each 4.55ms

The TIM2 CC3 register is equal to 16384, 
CC3 update rate = TIM2 counter clock / CCR3_Val = 439.4Hz
so the TIM2 Channel 3 generates an interrupt each 2.27ms

The TIM2 CC4 register is equal to 8192, 
CC4 update rate = TIM2 counter clock / CCR4_Val =  878.9 Hz
so the TIM2 Channel 4 generates an interrupt each 1.13ms.


When the counter value reaches the Output compare registers values, the Output 
Compare interrupts are generated and, in the handler routine, 4 pins(PC.06, PC.07,
PC.08 and  PC.09) are toggled with the following frequencies: 

- PC.06: 73.24Hz (CC1)
- PC.07: 109.8Hz (CC2)
- PC.08: 219.7Hz (CC3) 
- PC.09: 439.4Hz (CC4)


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

Connect an oscilloscope on PC.06, PC.07, PC.08 and  PC.09 to show the different
Time Base signals.
  
  
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_tim.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c

- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
