/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the DAC dual mode sine wave example.
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
This example describes how to use DAC dual channel mode with DMA to generate sine
waves on both DAC channels outpouts.

Both DAC channels conversions are configured to be triggered by TIM8 TRGO triggers
and without noise/triangle wave generation. 12bit right data alignement is selected
since we choose to acces DAC_DHR12RD register. DMA2 channel4 is configured to
transfer continuously, word by word, a 32-word buffer to the dual DAC register
DAC_DHR12RD.

The transfered 32buffer is made to have a sine wave generation on each DAC channel 
output. Both DAC channels are then enabled. Only DAC channel2 DMA capability is enabled.

Once TIM8 is enabled, each TIM8 TRGO update event generate a DMA request which
transfer data to the dual DAC register and DAC conversion is started. The sine
waves can be visualized by connecting both PA.04 and PA.05 pins to an oscilloscope.


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

 - Connect PA.04 and PA.05 pins to an oscilloscope

    
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  + stm32f10x_dac.c
  + stm32f10x_dma.c
  + stm32f10x_tim.c
  
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
