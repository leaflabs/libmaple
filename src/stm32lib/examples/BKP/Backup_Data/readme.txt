/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the BKP Backup_Data Example.
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
This example shows how to store user data in the Backup data registers.
As the Backup (BKP) domain still powered by VBAT when VDD is switched off, its
contents are not lost if a battery is connected to VBAT pin.

The program behaves as follows:
1. After startup the program checks if the board has been powered up. If yes, 
the values in the BKP data registers are checked:
   – if a battery is connected to the VBAT pin, the values in the BKP data registers
     are retained
   – if no battery is connected to the VBAT pin, the values in the BKP data registers
     are lost
2. After an external reset, the BKP data registers’ contents are not checked.

Four LEDs connected to the GPIO_LED Pin6 (LD1), Pin7 (LD2), Pin8 (LD3) and Pin9 (LD4)
are used to monitor the system state as follows:
1. LD3 on / LD1 on: a Power On Reset occurred and the values in the BKP data
   registers are correct
2. LD3 on / LD2 on: a Power On Reset occurred and the values in the BKP data
   registers are not correct or they have not yet been programmed (if it is the
   first time the program is executed)
3. LD3 off / LD1 off / LD2 off: no Power On Reset occurred
4. LD4 on: program running


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
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins
    - Use 3V battery on VBAT pin (set jumper JP11 in position 1-2)  
     
 + STM3210E-EVAL
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - Use 3V battery on VBAT pin (set jumper JP1 in position 1-2)      

    
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
- Run the example in standalone mode (without debugger connection)
- Power on/off the board and check that the BKP contents are not lost
   
******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
