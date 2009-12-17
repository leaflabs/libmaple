/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the TIM ExTrigger_Synchro example.
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

This example shows how to synchronize TIM peripherals in cascade mode with an
external trigger.
In this example three timers are used:

1/TIM2 is configured as Master Timer:
 - Toggle Mode is used
 - The TIM2 Enable event is used as Trigger Output 
 
2/TIM2 is configured as Slave Timer for an external Trigger connected to TIM2 TI2 pin 
(TIM2 CH2 configured as input pin):
 - The TIM2 TI2FP2 is used as Trigger Input
 - Rising edge is used to enable and stop the TIM2: Gated Mode.
  
3/TIM3 is slave for TIM2 and Master for TIM4,
 - Toggle Mode is used
 - The ITR1(TIM2) is used as input trigger 
 - Gated mode is used, so start and stop of slave counter are controlled by the Master
   trigger output signal(TIM2 enable event).
 - The TIM3 enable event is used as Trigger Output. 

4/TIM4 is slave for TIM3,
 - Toggle Mode is used
 - The ITR2(TIM3) is used as input trigger
 - Gated mode is used, so start and stop of slave counter are controlled by the Master 
trigger output signal(TIM3 enable event).

The TIMxCLK is fixed to 72 MHZ, the Prescaler is equal to 2 so the TIMx clock counter
is equal to 24 MHz.
The Three Timers are running at: 
TIMx frequency = TIMx clock counter/ 2*(TIMx_Period + 1) = 162.1 KHz.

The starts and stops of the TIM2 counter are controlled by the external trigger.
The TIM3 starts and stops are controlled by the TIM2, and the TIM4 starts and stops 
are controlled by the TIM3.	 
  

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

- Connect an external trigger, with a frequency <= 40KHz, to the TIM2 CH2 pin (PA.01).
  In this example the frequency is equal to 5 KHz.

- Connect the:
  - TIM2 CH1 (PA.00)
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
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32ff10x_flash.c

- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
