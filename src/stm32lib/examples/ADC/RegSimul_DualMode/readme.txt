/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the ADC regular simultaneous dual mode Example.
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
This example describes how to use ADC1 and ADC2 in regular simultaneous dual mode.
ADC1 is configured to convert channel14 and channel17 regular channels continuously.
ADC2 is configured to convert channel11 and channel12 regular channels continuously.
The connection between internal Vref and channel17 is enabled for ADC1.

Once the regular channels conversion is started by software, channel14 is converted
on ADC1 and channel11 is converted on ADC2 on the same time. The 32bits conversion 
result is then stored on ADC1 DR register. The DMA will transfer this data which
will be stored ADC_DualConvertedValueTab table. Consecutively to those conversion,
channel17 is converted on ADC1 and channel12 on ADC2. The combined conversion
result is also transfered by DMA to the same destination buffer. 

The same procedure is repeated until the specified number of data to be transfered
by DMA is reached.

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
   (potentiometer RV1 on STM3210B-EVAL and STM3210E-EVAL boards),ADC Channel11 mapped 
   on pin PC.01 and ADC Channel12 mapped on pin PC.02.
   
      
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
