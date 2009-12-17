/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the DMA ADC1 TIM1 example.
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
This example provides a description of how to use a DMA channel to transfer
continuously a data from a peripheral (ADC1) to another peripheral (TIM1) supporting
DMA transfer.
The ADC channel14 is configured to be converted continuously. TIM1_CH1 is configured
to generate a PWM signal on its output.
The dedicated DMA1 channel5 is configured to transfer in circular mode the last ADC 
channel14 converted value to the TIM1_CCR1 register. The DMA channel request is driven
by the TIM1 update event. The duty cycle of TIM1_CH1 output signal is then changed
each time the input voltage value on ADC channel14 pin is modified.
The duty cycle variation can be visualized on oscilloscope on the TIM1_CH1 pin
PA.08 while changing the analog input on ADC channel14 using the potentiometer.


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

 - Connect a variable power supply 0-3.3V to ADC Channel14 mapped on pin PC.04
   (potentiometer RV1 on STM3210B-EVAL or STM3210E-EVAL boards)
 - Connect an oscilloscope to TIM1_CH1 (PA.08) pin  
      

How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_dma.c
  + stm32f10x_rcc.c
  + stm32f10x_gpio.c
  + stm32f10x_adc.c
  + stm32f10x_tim.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
