/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM OnePulse example.
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

This example shows how to use the TIM peripheral to generate a One pulse Mode 
after a Rising edge of an external signal is received in Timer Input pin.

The TIM2CLK frequency is set to 72 MHz, the Prescaler is 1 so the TIM2 counter
clock is 36 MHz. 
The Autoreload value is 65535 (TIM2->ARR), so the maximum frequency value to trigger 
the TIM2 input is 500 Hz.

The TIM2 is configured as follows: 
The One Pulse mode is used, the external signal is connected to TIM2 CH2 pin (PA.01), 
the Rising edge is used as active edge, the One Pulse signal is output 
on TIM2_CH1 (PA.00).

The TIM_Pulse defines the delay value, the delay value is fixed to 455.08 us:
delay =  CCR1/TIM2 counter clock = 455.08 us. 
The (TIM_Period - TIM_Pulse) defines the One Pulse value, the pulse value is fixed to 1.365ms:
One Pulse value = (TIM_Period - TIM_Pulse)/TIM2 counter clock = 1.365 ms.


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

- Connect the external signal to the TIM2_CH2 pin (PA.01)
- Connect the TIM2_CH1 (PA.00) pin to an oscilloscope to monitor the waveform.
   
  
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
