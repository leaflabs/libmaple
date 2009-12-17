/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the PWR STOP Example.
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
This example shows how to enter the system to STOP mode and wake-up using EXTI
Line interrupts. The EXTI Line sources are PB.09/PG.08 and RTC Alarm.

The EXTI line9/8 is configured to generate interrupt on falling edge.
The EXTI line17(RTC Alarm) is configured to generate interrupt on rising edge and
the RTC time base is set to 1 second using the external low speed oscillator(LSE).

The system clock is set to 72 MHz using the external high speed oscillator(HSE).

The system enters and exits STOP mode as following:
After 2 second from system start-up, the RTC is configured to generate an Alarm
event in 3 second then the system enters STOP mode. To wake-up from STOP mode you
have to apply a rising edge on EXTI line9/8, otherwise the  RTC Alarm will wake-up
the system within 3 second. After exit from STOP the system clock is reconfigured
to its previous state (as HSE and PLL are disabled in STOP mode).
Then after a delay the system will enter again in STOP mode and exit in the way
described above. This behavior is repeated in an infinite loop.

Four leds connected to GPIO_LED Pin6(LD1), Pin7(LD2) and Pin8(LD3) are used to
monitor the system state as following:
 - LD1 on: system in RUN mode
 - LD1 off: system in STOP mode
 - LD2 is toggled if EXTI Line9/8 is used to exit from STOP 
 - LD3 is toggled if EXTI line17(RTC Alarm) is used to exit from STOP 


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
    - Use LD1, LD2 and LD3 leds connected respectively to PC.06, PC.07 and PC.08 pins
    - Use the Key push-button connected to pin PB.09 (EXTI Line9).
         
 + STM3210E-EVAL
    - Use LD1, LD2 and LD3 leds connected respectively to PF.06, PF0.7 and PF.08 pins
    - Use the Key push-button connected to pin PG.08 (EXTI Line8).

   
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
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

NOTE: For power consumption measurement in STOP mode you have to: 
1. Modify the example to configure all unused GPIO port pins in Analog Input mode
   (floating input trigger OFF). Refer to GPIO\IOToggle example for more details. 
2. Replace jumper JP9 in the STM3210B-EVAL board or JP12 in the STM3210E-EVAL
   board by an ampermeter.

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
