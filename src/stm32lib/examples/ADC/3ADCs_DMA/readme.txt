/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the 3ADCs DMA example.
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
This example describes how to use the 3 ADCs in independant conversions. 
Two of them; ADC1 and ADC3 are transfering continuously converted data using DMA
while ADC2 converted data are stored using End of conversion interrupt.

ADC1 is configured to converts continuously ADC channel14. Each time an end of
conversion occurs the DMA1 transfers, in circular mode, the converted data from 
ADC1 DR register to the ADC1_ConvertedValue variable.

ADC2 is configured to converts continuously ADC channel13. Each time an end of
conversion occurs an end of conversion interrupt is generated and inside the
interrupt routine the converted data are read from ADC2 DR register and stored
into the ADC2_ConvertedValue variable.

ADC3 is configured to converts continuously ADC channel12. Each time an end of
conversion occurs the DMA2 transfers, in circular mode, the converted data from
ADC3 DR register to the ADC3_ConvertedValue variable.

The ADCs clocks are set to 14 MHz.

The result of ADC1, ADC2 and ADC3 conversion is monitored through the three
variables: ADC1ConvertedValue, ADC2ConvertedValue and ADC3ConvertedValue.


Directory contents
==================
stm32f10x_conf.h  Library Configuration file
stm32f10x_it.c    Interrupt handlers
stm32f10x_it.h    Interrupt handlers header file
main.c            Main program



Hardware environment
====================
This example runs on STMicroelectronics STM3210E-EVAL evaluation board and can be 
easily tailored to any other hardware.

 - Connect a variable power supply 0-3.3V to ADC Channel12 mapped on pin PC.02
 - Connect a variable power supply 0-3.3V to ADC Channel13 mapped on pin PC.03
 - Connect a variable power supply 0-3.3V to ADC Channel14 mapped on pin PC.04
   (potentiometer RV1 on STM3210E-EVAL board) 
   
      
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_adc.c
  + stm32f10x_dma.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
