/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM DMA example.
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
This example provides a description of how to use DMA with TIM1 Update request
to transfer Data from memory to TIM1 Capture Compare Register3.

TIM1CLK = 72 MHz, Prescaler = 0, TIM1 counter clock = 72 MHz 
The TIM1 Channel3 is configured to generate a complementary PWM signal with 
a frequency equal to: TIM1 counter clock / (TIM1_Period + 1) = 17.57 KHz

The TIM1 Channel3 is configured to generate a complementary PWM signal with 
a frequency equal to 17.578 KHz and a variable duty cycle that is changed 
by the DMA after a specific number of Update event. 
The number of this repetitive requests is defined by the TIM1 Repetion counter,
each 3 Update Requests, the TIM1 Channel3 Duty Cycle changes to the next new value
defined by the SRC_Buffer.


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

Connect the pins 
  - TIM1 CH3  (PA.10)
  - TIM1 CH3N (PB.15)
to an oscilloscope to monitor the different waveforms.
   
  
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32F10x_lib.c
  + stm32F10x_tim.c
  + stm32F10x_gpio.c
  + stm32F10x_rcc.c
  + stm32F10x_dma.c
  + stm32F10x_nvic.c
  + stm32F10x_flash.c

- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
