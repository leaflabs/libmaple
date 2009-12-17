/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the NVIC CM3 Low Power Example.
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
This example describes how to use the NVIC firmware library to demonstrate the 
Cortex-M3 low power modes capabilities (WFE and WFI). 

This example uses three EXTI lines(Wakeup button EXTI Line, Key button EXTI Line
& Tamper button EXTI Line)to generate interrupts and event on each falling edge.
The Wakeup button EXTI Line and Tamper button EXTI Line are configured in 
interrupt mode and the Key button EXTI Line in event mode. The user has to select
which low power mode would execute through a five define in the main code.

These choices are:

   - Wait For Interrupt (WFI) Sleep On Exit: in this mode the WFI instruction is
    excecuted automatically on an exception Return. The exception will be executed
    if has enough priority to run and the core will return in the WFI mode. 
    To run this behaviour proceed as following:
      
      * Choose the #WFISLEEPONEXIT define and comment others defines
      * run the example
      * The Wakeup button EXTI Line toggles LD4.
      * Push the Tamper button, the SLEEPONEXIT function is selected
      Any edge on the Wakeup button EXTI Line or Tamper button EXTI Line will 
      execute the EXTI interrupt, when exit from the ISR the core will enter WFI
      mode. Any time you push the Wakeup button the core exit from WFI mode, 
      LD4 is toggled then the  core enters again in WFI mode.
      This behavior is repeated in an infinite loop.

    - Wait For Interrupt (WFI) Sleep Now: in this mode the WFI instruction is 
      excecuted directly. To run this behaviour proceed as following:

      * Choose the #WFISLEEPNOW define and comment others defines
      * run the example
      * The Tamper button EXTI Line will toggle LD1 and put the core in the WFI mode.  
      * To wakeup the Core use the Wakeup button that will toggle the LD3.
      This behavior is repeated in an infinite loop.
  
   - Wait For Event (WFE) SEV ON PEND: in this mode the WFE instruction is excecuted
     directly and the main instruction stream (execution priority) is boosted by the
     register PRIMASK (main priority = 0).
     To run this behaviour proceed as following:

     * Choose the #WFESEVONPEND define and comment others defines
     * run the example
     * The Tamper button EXTI Line will boost the execution priority to 0 (no 
       interrupt will be  executed after due to the priority boosting), toggle 
       LD1 and put the core in WFE mode. 
     * To wakeUp the Core use the Wakeup button that will not toggle the LD3 but
       will only wakeup the core from the WFE (SEV ON PEND). 
       This EXTI Line interrupt has passed from unpended state to a pended state 
       which wakeup the core from the WFE.
     * To wakeup the core also you can use theTamper button configured in event
       mode.
     * if the #RTC_Alarm_WFEWakeUp define is enabled, the RTC alarm will wakeUp 
       the Core after 6 seconds (if none of Tamper button EXTI Line and Key 
       button EXTI Line was used before this delay to wakeUp the Core)
  
   - Wait For Event (WFE) SEV ON EVENT: in this mode the WFE instruction is 
     excecuted directly. To run this behaviour proceed as following:

    * Choose the #WFESEVONEVENT define and comment others defines
    * run the example
    * The Tamper button EXTI Line will toggle LD1 and put the core in the WFE mode. 
    * To wakeup the Core use the Wakeup button that will toggle the LD3.
    * To wakeup the core also you can use the Key button configured in event mode.
    * if the #RTC_Alarm_WFEWakeUp define is enabled, the RTC alarm will wakeUp 
      the Core after 6 seconds (if none of Tamper button EXTI Line and Key button
      EXTI Line was used before this delay to wakeup the Core)
      This behavior is repeated in an infinite loop.

LD4 is toggled to indicate whether the MCU is in RUN or in low power mode.

Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Interrupt handlers header file
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins
    - Use the Key push-button connected to pin PB.09 (EXTI Line9).
    - Use the Wakeup push-button connected to pin PA.00 (EXTI Line0).
    - Use the Tamper push-button connected to pin PC.13 (EXTI Line13).     

 + STM3210E-EVAL
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - Use the Key push-button connected to pin PG.08 (EXTI Line8).
    - Use the Wakeup push-button connected to pin PA.00 (EXTI Line0).
    - Use the Tamper push-button connected to pin PC.13 (EXTI Line13). 
       
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_exti.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_rtc.c
  + stm32f10x_pwr.c
  + stm32f10x_bkp.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
