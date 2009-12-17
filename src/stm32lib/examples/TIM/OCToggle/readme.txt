/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM OCToggle example.
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
This example shows how to configure the TIM2 peripheral to generate four different 
signals with four different frequencies.

The TIM2CLK frequency is set to 36 MHz, the Prescaler is set to 2, and used in 
Output Compare Toggle Mode.

TIM2 counter clock = TIMxCLK / (Prescaler +1) = 12 MHz 

The TIM2 CCR1 register value is equal to 32768: 
CC1 update rate = TIM2 counter clock / CCR1_Val = 366.2 Hz,
so the TIM2 Channel 1 generates a periodic signal with a frequency equal to 183.1 Hz.

The TIM2 CCR2 register is equal to 16384:
CC2 update rate = TIM2 counter clock / CCR2_Val = 732.4 Hz
so the TIM2 channel 2 generates a periodic signal with a frequency equal to 366.3 Hz.

The TIM2 CCR3 register is equal to 8192:
CC3 update rate = TIM2 counter clock / CCR3_Val = 1464.8 Hz
so the TIM2 channel 3 generates a periodic signal with a frequency equal to 732.4 Hz.

The TIM2 CCR4 register is equal to 4096:
CC4 update rate = TIM2 counter clock / CCR4_Val =  2929.6 Hz
so the TIM2 channel 4 generates a periodic signal with a frequency equal to 1464.8 Hz.



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
- PA.00 (TIM2_CH1)
- PA.01 (TIM2_CH2)
- PA.02 (TIM2_CH3)
- PA.03 (TIM2_CH4)
pins to an oscilloscope to monitor the different waveform.
  
  
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
