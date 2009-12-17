/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the BKP Tamper Example.
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
This example shows how to write/read data to/from Backup data registers and 
demonstrates the Tamper detection feature.

The associated firmware performs the following:
1. It configures the ANTI_TAMP pin to be active low, and enables the Tamper interrupt.
2. It writes the data to all Backup data registers, then check whether the data were
correctly written. If yes, the LED connected to GPIO_LED Pin 6 turns on, otherwise
the LED connected to GPIO_LED Pin7 turns on.
3. On applying a low level on the ANTI_TAMP pin (PC.13), the Backup data registers
are reset and the Tamper interrupt is generated. The corresponding ISR then checks
whether the Backup data registers are cleared. If yes, the LED connected to
GPIO_LED Pin8 turns on, otherwise the LED connected to GPIO_LED Pin9 turns on.


Directory contents
==================
platform_config.h  Evaluation board specific configuration file
stm32f10x_conf.h   Library Configuration file
stm32f10x_it.h     Interrupt handlers header file
stm32f10x_it.c     Interrupt handlers
main.c             Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins
    - Use the Tamper push-button connected to pin PC.13
     
 + STM3210E-EVAL
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - Use the Tamper push-button connected to pin PC.13
    
    
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_pwr.c
  + stm32f10x_bkp.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  
- Link all compiled files and load your image into target memory
- Run the example
   
******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
