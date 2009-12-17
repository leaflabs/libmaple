/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the RTC Calendar Example.
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
This example demonstrates and explains how to use the RTC peripheral. 
As an application example, it demonstrates how to setup the RTC peripheral, in terms
of prescaler and interrupts, to be used to keep time and to generate Second interrupt. 

The Low Speed External (LSE) clock is used as RTC clock source. 
The RTC clock can be output on the Tamper pin (PC.13). To enable this functionality,
uncomment the corresponding line: #define RTCClockOutput_Enable in the main.c file.

The RTC is in the backup (BKP) domain, still powered by VBAT when VDD is switched off,
so the RTC configuration is not lost if a battery is connected to the VBAT pin. 
A key value is written in backup data register1 (BKP_DR1) to indicate if the RTC
is already configured.

The program behaves as follows:
1. After startup the program checks the backup data register1 value:
    – register1 value not correct: (BKP_DR1 value is not correct or has not yet
      been programmed when the program is executed for the first time) the RTC is
      configured and the user is asked to set the time (entered on HyperTerminal).
    – register1 value correct: this means that the RTC is configured and the time
      is displayed on HyperTerminal.
2. When an External Reset occurs the BKP domain is not reset and the RTC configuration
   is not lost.
3. When power on reset occurs:
    – If a battery is connected to the VBAT pin: the BKP domain is not reset and
      the RTC configuration is not lost.
    – If no battery is connected to the VBAT pin: the BKP domain is reset and the
      RTC configuration is lost.

In the RTC interrupt service routine, a specific GPIO pin toggles every 1 s.
The C library printf function is retargeted to the USART1, that is, the printf
message is output to the HyperTerminal using USART1.

 
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
    - Use LD1 led connected to PC.06.
    - The USART1 signals (Rx, Tx) must be connected to a DB9 connector using a RS232
       transceiver.
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
       (CN6 on STM3210B-EVAL board) and PC serial port.
    - Hyperterminal configuration:
       - Word Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - flow control: None
    - Connect a 3V battery on Vbat pin (already mounted on STM3210B-EVAL board)   
 
 + STM3210E-EVAL
    - Use LD1 led connected to PF.06.
    - The USART1 signals (Rx, Tx) must be connected to a DB9 connector using a RS232
       transceiver.
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
       (CN12 on STM3210B-EVAL board) and PC serial port. 
    - Hyperterminal configuration:
       - Word Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - flow control: None
    - Connect a 3V battery on Vbat pin (already mounted on STM3210E-EVAL board)  
    
    
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_rtc.c
  + stm32f10x_bkp.c
  + stm32f10x_pwr.c
  + stm32f10x_nvic.c
  + stm32f10x_usart.c
  + stm32f10x_flash.c
  
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
