/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the RTC LSI_Calib Example.
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
This example demonstrates and explains how to use the LSI clock source auto
calibration to get a precise RTC clock. 
As an application example, it demonstrates how to configure the TIM5 timer
internally connected to LSI clock output, in order to adjust the RTC prescaler. 

The Low Speed External (LSI) clock is used as RTC clock source.
After reset, the RTC prescaler is set with the default value (40000). 
The inaccuracy of the LSI clock causes the Second signal to be inaccurate. This
signal is output on the Tamper pin (PC.13) and can be measured by on oscilloscope
or a frequencymeter.

The program waits until the PG.08 pin level goes low (push Key button on STM3210E-EVAL
board) to begin the auto calibration procedure:
 - Configure the TIM5 to remap internally the TIM5 Channel 4 Input Capture to the
   LSI clock output.
 - Enable the TIM5 Input Capture interrupt: after one cycle of LSI clock, the
   period value is stored in a variable and compared to the HCLK clock to get
   its real value.
 - The RTC prescaler is adjusted with this LSI frequency value so that the RTC
   Second value become more accurate.
 - When calibration is done a led connected to PF.07 is turned ON to indicate the
    end of this operation. At this moment, you can  monitor the Second signal on
    an oscilloscope to measure its accuracy again.

The Seconds signal can be monitored either on Tamper pin or on a specific PF.06
pin toggled into the RTC Seconds interrupt service routine.
    
 
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

Use LD1 and LD2 leds connected respectively to PF.06 and PF.07 pins, and the Key 
push button connected to PG.08 pin. 
    
    
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_rtc.c
  + stm32f10x_tim.c
  + stm32f10x_bkp.c
  + stm32f10x_pwr.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
