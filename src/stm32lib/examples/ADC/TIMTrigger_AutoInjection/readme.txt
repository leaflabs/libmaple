/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the ADC TIM trigger and auto-injection Example.
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
This example describes how to convert ADC regular group channels continuously using
TIM1 external trigger and injected group channels using the auto-injected feature.

ADC1 is configured to convert on each TIM1 capture compare event ADC channel14.
Each time an end of regular conversion occurs the DMA transfers, the converted data 
from ADC1 DR register to the ADC_RegularConvertedValueTab table. 
Enabling the auto-injected feature, allows to convert automatically the injected 
channel ADC channel11 after the end of the regular channel14. An ADC interrupt is 
generated then by JEOC flag at the end of the injected channel conversion and in 
the interrupt routine the result is stored in the ADC_InjectedConvertedValueTab table.
The procedure is repeated 32 times then the TIM1 peripheral is disabled and thus, 
no conversion will be done neither regular or injected.
TIM1 start conversion triggers can be visualized on oscilloscope on PA.08 and at the
same time the toggle of pin PC.06 which indicates the automatic auto-injection conversion.
The ADC1 clock is set to 14 MHz.


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

 - Connect a known voltage, between 0-3.3V, to ADC Channel14 mapped on pin PC.04
   (potentiometer RV1 on STM3210B-EVAL and STM3210E-EVAL boards) and ADC Channel11 
   mapped on pin PC.01
 - Connect PA.08 and PC.06 pins to an oscilloscope
   
      
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_adc.c
  + stm32f10x_dma.c
  + stm32f10x_tim.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
