/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the DAC one channel noise wave example.
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
This example describes how to use one DAC channel to generate a signal with noise
waves on DAC Channel1 output.

DAC channel1 conversion are configured to be triggered by software with noise wave 
generation.12bit left data alignement is selected since we choose to acces DAC_DHR12L1
register. Bits 0 to 8 are masked for the Linear feedback shift register. 
DAC channel1 is then enabled. DAC Channel1 DHR12L1 register is configured to have
an output voltage of VREF/2.

Software triggers are generated continuously in an infinite loop, and on each
trigger the DAC channel1 start the conversion and calculate the noise value to
apply on the DAC channel1 output.

The output signal with noise waves can be visualized by connecting PA.04 pin to
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

 - Connect PA.04 pin to an oscilloscope

    
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
  
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
