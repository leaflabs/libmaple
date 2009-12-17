/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the PWR STANDBY Example.
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
This example shows how to enters the system to STANDBY mode and wake-up from this
mode using: external RESET, RTC Alarm or WKUP pin.

In the associated software, the system clock is set to 72 MHz, an EXTI line
is configured to generate an interrupt on falling edge and the SysTick is programmed
to generate an interrupt each 250 ms. In the SysTick interrupt handler, a led 
connected to GPIO_LED Pin6(LD1) is toggled, this is used to indicate whether the MCU is 
in STANDBY or RUN mode.
When a falling edge is detected on the EXTI line an interrupt is generated. In the 
EXTI handler routine the RTC is configured to generate an Alarm event in 3 second
then the system enters STANDBY mode causing the LD1 to stop toggling. 
A rising edge on WKUP pin or an external RESET will wake-up the system from
STANDBY. If within 3 second neither rising edge on WKUP pin nor external RESET
are generated, the RTC Alarm will wake-up the system. 
After wake-up from STANDBY mode, program execution restarts in the same way as after
a RESET, the LD1 restarts toggling, GPIO_LED Pin6 is set to high level and the RTC
configuration (clock source, enable, prescaler,...) is kept. As result there is no
need to configure the RTC.

Two leds connected to GPIO_LED Pin6(LD1) and Pin7(LD2) pins are used to monitor
the system state as following:
 - LD1 toggling: system in RUN mode
 - LD1 off / LD2 off: system in STANDBY mode
 - LD2 on: system resumed from STANDBY mode

 
Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Header for stm32f10x_it.c
main.c               Main program
main.h               Header for main.c


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1 and LD2 leds connected respectively to PC.06 and PC.07 pins    
    - Use the Key push-button connected to pin PB.09 (EXTI Line9).
    - Use the Wakep push-button connected to WKUP(PA.00) pin
         
 + STM3210E-EVAL
    - Use LD1 and LD2 leds connected respectively to PF.06 and PF.07 pins
    - Use the Key push-button connected to pin PG.08 (EXTI Line8).
    - Use the Wakep push-button connected to WKUP(PA.00) pin
      Note: the jumper JP4 must be not fit to be able to use the Wakeup push-button

     
   
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_nvic.c
  + stm32f10x_rcc.c
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rtc.c  
  + stm32f10x_pwr.c  
  + stm32f10x_bkp.c
  + stm32f10x_exti.c
  + stm32f10x_flash.c
  + stm32f10x_systick.c             
- Link all compiled files and load your image into target memory
- Run the example in standalone mode (without debugger connection)

NOTE: For power consumption measurement in STANDBY mode, you have to replace
      jumper JP9 in the STM3210B-EVAL board or JP12 in the STM3210E-EVAL board
      by an ampermeter.


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
