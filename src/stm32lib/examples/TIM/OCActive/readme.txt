/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM OCActive example.
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
This example shows how to configure the TIM peripheral to generate four different 
signals with four different delays.

The TIMxCLK frequency is set to 36 MHz, the Prescaler is set to 35999 and used in 
Output Compare Active Mode.
 
TIM2 counter clock = TIMxCLK / (Prescaler +1) = 1 KHz 

The TIM2 CCR1 register value is equal to 1000:
TIM2_CH1 delay = CCR1_Val/TIM2 counter clock  = 1000 ms
so the TIM2 Channel 1 generates a signal with a delay equal to 1000 ms.

The TIM2 CCR2 register value is equal to 500:
TIM2_CH2 delay = CCR2_Val/TIM2 counter clock = 500 ms
so the TIM2 Channel 2 generates a signal with a delay equal to 500 ms.

The TIM2 CCR3 register value is equal to 250:
TIM2_CH3 delay = CCR3_Val/TIM2 counter clock = 250 ms
so the TIM2 Channel 3 generates a signal with a delay equal to 250 ms.

The TIM2 CCR4 register value is equal to 125:
TIM2_CH4 delay = CCR4_Val/TIM2 counter clock = 125 ms
so the TIM2 Channel 4 generates a signal with a delay equal to 125 ms.

The delay correspond to the time difference between PC.06 and TIM2_CHx signal rising edges

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
- PA.00 (TIM2_CH1)
- PA.01 (TIM2_CH2)
- PA.02 (TIM2_CH3)
- PA.03 (TIM2_CH4)
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

- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
