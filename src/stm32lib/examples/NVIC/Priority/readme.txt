/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the NVIC Priority Example.
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
This example demontrates the use of the Nested Vectored Interrupt Controller (NVIC): 

- Configuration of 2 EXTI Lines (Wakeup button EXTI Line & Key button EXTI Line)
  to generate an interrupt on each falling edge and use the SysTick interrupt.
- These interrupts are configured with the following parameters:
  Wakeup button EXTI Line: o PreemptionPriority = PreemptionPriorityValue
                           o SubPriority = 0
  Key button EXTI Line:    o PreemptionPriority = 0
                           o SubPriority = 1           
  SysTick Handler: o PreemptionPriority = !PreemptionPriorityValue
                   o SubPriority = 0             
First, the PreemptionPriorityValue is equal to 0, the Wakeup button EXTI Line 
has higher preemption priority than the SysTick handler. 

In the key button EXTI Line interrupt routine the Wakeup button EXTI Line and 
SysTick preemption priorities are inverted. 
In the Wakeup button EXTI Line interrupt routine the pending bit of the SysTick 
interrupt is set this will cause SysTick ISR to preempt the Wakeup button EXTI 
Line ISR only if it has higher preemption priority.

The system behaves as following: 
1) The first time Key button EXTI Line interrupt occurs the SysTick preemption 
become higher than Wakeup button EXTI Line one. So when the Wakeup button EXTI 
Line interrupt occurs, the SysTick ISR is executed and the PreemptionOccured 
variable become TRUE and the four leds (LD1, LD2, LD3, LD4) start toggling.

2) When the next Key button EXTI Line interrupt occurs the SysTick preemption
become lower than Wakeup button EXTI Line one. So when the Wakeup button EXTI Line
interrupt occurs, the PreemptionOccured variable became FALSE and the four leds
(LD1, LD2, LD3, LD4) stop toggling.

Then this behavior is repeated from point 1) in an infinite loop.


Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Interrupt handlers header file
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins
    - Use the Key push-button connected to pin PB.09 (EXTI Line9).
    - Use the Wakeup push-button connected to pin PA.00 (EXTI Line0).         
 
 + STM3210E-EVAL
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - Use the Key push-button connected to pin PG.08 (EXTI Line8).
    - Use the Wakeup push-button connected to pin PA.00 (EXTI Line0).
 
    
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_exti.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
