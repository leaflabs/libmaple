/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM TIM1_Synchro example.
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
This example shows how to synchronize TIM1 and Timers (TIM3 and TIM4) in parallel mode.

Timers synchronisation in parallel mode:

1/ TIM1 is configured as Master Timer:
 - PWM Mode is used
 - The TIM1 Update event is used as Trigger Output 
 
2/ TIM3 and TIM4 are slaves for TIM1,
 - PWM Mode is used
 - The ITR0(TIM1) is used as input trigger for both slaves
 - Gated mode is used, so starts and stops of slaves counters
  are controlled by the Master trigger output signal(update event).

TIM1CLK = 72 MHz, Prescaler = 0, TIM1 counter clock = 72 MHz
The Master Timer TIM1 is running at:
TIM1 frequency = TIM1 counter clock / (TIM1_Period + 1) = 281.250 KHz
and the duty cycle is equal to: TIM1_CCR1/(TIM1_ARR + 1) = 50%

The TIM3 is running:
 - At (TIM1 frequency)/ ((TIM3 period +1)* (Repetion_Counter+1)) = 18.750 KHz and
 a duty cycle equal to TIM3_CCR1/(TIM3_ARR + 1) = 33.3%

The TIM4 is running:
 - At (TIM1 frequency)/ ((TIM4 period +1)* (Repetion_Counter+1)) = 28.125 KHz and
 a duty cycle equal to TIM4_CCR1/(TIM4_ARR + 1) = 50%


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
- TIM1 CH1 (PA.08)
- TIM3 CH1 (PA.06)
- TIM4 CH1 (PB.06)
pins to an oscilloscope to monitor the different waveforms.
   
  
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_tim.c
  + stm32f10x_tim1.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c

- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
