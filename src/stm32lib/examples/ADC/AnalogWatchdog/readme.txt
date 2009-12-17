/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the ADC analog watchdog example.
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
This example describes how to use the ADC analog watchdog to guard continuously  
an ADC channel.
The ADC1 is configured to convert continuously ADC channel14. The analog watchdog
is configured and enabled to guard a single regular channel. 
Each time the channel14 converted value exceed programmed analog watchdog high 
threshold (value 0x0B00) or goes down analog watchdog low threshold (value 0x0300)
an AWD interrupt is generated and the output pin connected to LED1 is toggled. The
LED will bright as long as the AWD interrupt is generated which means that the 
converted value of regular ADC channel14 is outside the range limited by high and 
low analog watchdog thresholds.
The ADC1 clock is set to 14 MHz.


Directory contents
==================
platform_config.h  Evaluation board specific configuration file
stm32f10x_conf.h   Library Configuration file
stm32f10x_it.c     Interrupt handlers
stm32f10x_it.h     Interrupt handlers header file
main.c             Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1 led connected to PC.06 pin
 
 + STM3210E-EVAL
    - Use LD1 led connected to PF.06 pin

 - Connect a variable power supply 0-3.3V to ADC Channel14 mapped on pin PC.04
   (potentiometer RV1 on STM3210B-EVAL and STM3210E-EVAL boards) 

         
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_adc.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
