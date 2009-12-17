/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM 7PWM_Output example.
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

This example shows how to configure the TIM1 peripheral to generate 7 PWM signals 
with 4 different duty cycles.

TIM1CLK is fixed to 72 MHz, the TIM1 Prescaler is equal to 0 so the TIM1 counter
clock used is 72 MHz.

TIM1 frequency is defined as follow:
TIM1 frequency = TIM1CLK/(TIM1_Period + 1) = 17.57 KHz.

The TIM1 CCR1 register value is equal to 0x7FF, so the TIM1 Channel 1 and TIM1 
Channel 1N generate a PWM signal with a frequency equal to 17.57 KHz 
and a duty cycle equal to:
TIM1 Channel1 duty cycle = TIM1_CCR1 /( TIM1_Period + 1) = 50%.

The TIM1 CCR2 register value is equal to 0x5FF, so the TIM1 Channel 2 and TIM1
Channel 2N generate a PWM signal with a frequency equal to 17.57 KHz 
and a duty cycle equal to:
TIM1 Channel2 duty cycle = TIM1_CCR2 / ( TIM1_Period + 1)= 37.5%.

The TIM1 CCR3 register value is equal to 0x3FF, so the TIM1 Channel 3 and TIM1 
Channel 3N generate a PWM signal with a frequency equal to 17.57 KHz 
and a duty cycle equal to:
TIM1 Channel3 duty cycle = TIM1_CCR3 / ( TIM1_Period + 1) = 25%.

The TIM1 CCR4 register value is equal to 0x1FF, so the TIM1 Channel 4 
generate a PWM signal with a frequency equal to 17.57 KHz 
and a duty cycle equal to:
TIM1 Channel4 duty cycle = TIM1_CCR4 / ( TIM1_Period + 1) = 12.5%.

The TIM1 waveform can be displayed using an oscilloscope.
 

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

Connect the TIM1 pins to an oscilloscope to monitor the different waveforms:
  - TIM1_CH1  pin (PA.08)  
  - TIM1_CH1N pin (PB.13)  
  - TIM1_CH2  pin (PA.09)  
  - TIM1_CH2N pin (PB.14)  
  - TIM1_CH3  pin (PA.10)  
  - TIM1_CH3N pin (PB.15)
  - TIM1_CH4  pin (PA.11)
  
  
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
