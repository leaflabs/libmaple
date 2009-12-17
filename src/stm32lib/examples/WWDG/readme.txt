/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the WWDG Example.
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
This example shows how to update at regulate period the WWDG counter using the
Early Wakeup interrupt (EWI).

The WWDG timeout is set to 262 ms, the refresh window is set to 65 and the EWI is
enabled. When the WWDG counter reaches 64, the EWI is generated. In the WWDG ISR,
the counter is refreshed to prevent a WWDG reset and a specific GPIO pin is toggled.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the falling edge of the signal.
In the NVIC (nested vectored interrupt controller), the EXTI Line interrupt
vector is enabled with a priority equal to 0 and the WWDG interrupt vector is
enabled with a priority equal to 1 (EXTI IT > WWDG IT).

The EXTI Line is used to simulate a software failure: once the EXTI Line event occurs
(by pressing the Key push-button on the STM3210B-EVAL board), the corresponding
interrupt is served. In the ISR, the GPIO pin is reset and the EXTI Line pending 
bit is not cleared. So the CPU executes the EXTI Line ISR indefinitely and the 
WWDG ISR is never executed (the WWDG counter is not updated).
As a result, when the WWDG counter falls to 63, the WWDG reset occurs.
If the WWDG reset is generated, after the system resumes from reset, an other GPIO
is set.

If the EXTI Line event does not occur, the WWDG counter is indefinitely refreshed
in the WWDG ISR, and there is no WWDG reset.

In this example the system is clocked by HSE, the high-speed external clock (8 MHz).


Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Header for stm32f10x_it.c
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1 and LD2 leds connected respectively to PC.06 and PC.07 pins, and the
      KEY push button connected to PB.09 pin.
 
 + STM3210E-EVAL
    - Use LD1 and LD2 leds connected respectively to PF.06 and PF.07 pins, and the
      KEY push button connected to PG.08 pin.

    
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_wwdg.c
  + stm32f10x_flash.c
  + stm32f10x_exti.c  

- Link all compiled files and load your image into target memory
- Run the example in standalone mode (without debugger connection)

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
