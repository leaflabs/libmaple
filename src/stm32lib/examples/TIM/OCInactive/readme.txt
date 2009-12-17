/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM OCInactive example.
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

This example shows how to configure the TIM peripheral in Output Compare Inactive 
mode with the corresponding Interrupt requests for each channel.

The TIMxCLK frequency is set to 36 MHz, the Prescaler is set to 35999 and used in 
Output Compare Inactive Mode.
TIM2 counter clock = TIMxCLK / (Prescaler +1) = 1 KHz 

The TIM2 CCR1 register value is equal to 1000:
TIM2_CC1 delay = CCR1_Val/TIM2 counter clock  = 1000 ms
so the PC.06  is reset after a delay equal to 1000 ms.

The TIM2 CCR2 register value is equal to 500:
TIM2_CC2 delay = CCR2_Val/TIM2 counter clock = 500 ms
so the PC.07  is reset after a delay equal to 500 ms.

The TIM2 CCR3 register value is equal to 250:
TIM2_CC3 delay = CCR3_Val/TIM2 counter clock = 250 ms
so the PC.08  is reset after a delay equal to 250 ms.

The TIM2 CCR4 register value is equal to 125:
TIM2_CC4 delay = CCR4_Val/TIM2 counter clock = 125 ms
so the PC.09  is reset after a delay equal to 125 ms.

While the counter is lower than the Output compare registers values, which 
determines the Output delay, the PC.06, PC.07, PC.08 and PC.09 pin are turned on. 

When the counter value reaches the Output compare registers values, the Output 
Compare interrupts are generated and, in the handler routine, these pins are turned off.


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

Connect the:
- PC.06
- PC.07
- PC.08 
- PC.09 
pins to an oscilloscope to monitor the different waveforms.
  
  
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

- Link all compiled files and load your image into either RAM or Flash
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
