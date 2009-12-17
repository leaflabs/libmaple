/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the DAC two channels triangle wave example.
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
This example describes how to use two DAC channels to generate two different
signals with triangle waves on each DAC Channel output.

DAC channels conversion are configured to be triggered by TIM2 TRGO with triangle
wave generation. 12bit right data alignement is selected since we choose to acces
both DAC_DHR12R1 and DAC_DHR12R2 registers.
A triangle amplitude of 2047 is selected for DAC channel1 and 1023 for DAC channel2.
Both DAC channels are then enabled. DAC Channel1 DHR12R1 and DAC channel2 DHR12R2
registers are set to have a base output voltage of VREF/16 on each output.

Once TIM2 is enabled, each TIM2 TRGO update event trigger both DAC channels start
of conversion. The triangle counter is incremented, added to the base value and
applied to the corresponding DAC channel output. The same calculation is repeated
on each trigger.
The triangle waves can be visualized by connecting both PA.04 and PA.05 pins to
an oscilloscope.


Directory contents
==================
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Header for stm32f10x_it.c
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210E-EVAL evaluation board and can be 
easily tailored to any other hardware.

 - Connect PA.04 and PA.05 pins to an oscilloscope

    
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  + stm32f10x_dac.c
  + stm32f10x_tim.c
  
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
