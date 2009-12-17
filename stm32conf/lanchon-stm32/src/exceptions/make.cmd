@echo off
setlocal

type lanchon-stm32-vector.S.prolog>lanchon-stm32-vector.S
type lanchon-stm32-isrs.S.prolog>lanchon-stm32-isrs.S
type lanchon-stm32-names.inc.prolog>lanchon-stm32-names.inc
type stm32exceptions.h.prolog>stm32exceptions.h
type stm32exceptions.c.prolog>stm32exceptions.c

set DO=call make-foreach

rem %DO% 00 - __cs3_stack
rem %DO% 04 - __cs3_reset
%DO% 08 e NMIException "NMI" "from the RCC Clock Security System"
%DO% 0C e HardFaultException "Hard Fault"
%DO% 10 e MemManageException "Memory Management"
%DO% 14 e BusFaultException "Bus Fault" "prefetch and memory access faults"
%DO% 18 e UsageFaultException "Usage Fault" "undefined instruction or illegal state faults"
%DO% 1C x
%DO% 20 x
%DO% 24 x
%DO% 28 x
%DO% 2C e SVCHandler "SVCall" "system service call via SWI instruction"
%DO% 30 e DebugMonitor "Debug Monitor"
%DO% 34 x
%DO% 38 e PendSVC "PendSVC" "pendable request for system service"
%DO% 3C e SysTickHandler "SysTick"
%DO% 40 i WWDG_IRQHandler "WWDG"
%DO% 44 i PVD_IRQHandler "PVD" "EXTI Line 16"
%DO% 48 i TAMPER_IRQHandler "Tamper"
%DO% 4C i RTC_IRQHandler "RTC"
%DO% 50 i FLASH_IRQHandler "Flash"
%DO% 54 i RCC_IRQHandler "RCC"
%DO% 58 i EXTI0_IRQHandler "EXTI Line 0"
%DO% 5C i EXTI1_IRQHandler "EXTI Line 1"
%DO% 60 i EXTI2_IRQHandler "EXTI Line 2"
%DO% 64 i EXTI3_IRQHandler "EXTI Line 3"
%DO% 68 i EXTI4_IRQHandler "EXTI Line 4"
%DO% 6C i DMAChannel1_IRQHandler "DMA Channel 1"
%DO% 70 i DMAChannel2_IRQHandler "DMA Channel 2"
%DO% 74 i DMAChannel3_IRQHandler "DMA Channel 3"
%DO% 78 i DMAChannel4_IRQHandler "DMA Channel 4"
%DO% 7C i DMAChannel5_IRQHandler "DMA Channel 5"
%DO% 80 i DMAChannel6_IRQHandler "DMA Channel 6"
%DO% 84 i DMAChannel7_IRQHandler "DMA Channel 7"
%DO% 88 i ADC_IRQHandler "ADC"
%DO% 8C i USB_HP_CAN_TX_IRQHandler "USB High Priority/CAN TX"
%DO% 90 i USB_LP_CAN_RX0_IRQHandler "USB Low Priority/CAN RX0"
%DO% 94 i CAN_RX1_IRQHandler "CAN RX1"
%DO% 98 i CAN_SCE_IRQHandler "CAN SCE"
%DO% 9C i EXTI9_5_IRQHandler "EXTI Lines 5-9"
%DO% A0 i TIM1_BRK_IRQHandler "TIM1 Break"
%DO% A4 i TIM1_UP_IRQHandler "TIM1 Update"
%DO% A8 i TIM1_TRG_COM_IRQHandler "TIM1 Trigger/Commutation"
%DO% AC i TIM1_CC_IRQHandler "TIM1 Capture/Compare"
%DO% B0 i TIM2_IRQHandler "TIM2"
%DO% B4 i TIM3_IRQHandler "TIM3"
%DO% B8 i TIM4_IRQHandler "TIM4"
%DO% BC i I2C1_EV_IRQHandler "I2C1 Event"
%DO% C0 i I2C1_ER_IRQHandler "I2C1 Error"
%DO% C4 i I2C2_EV_IRQHandler "I2C2 Event"
%DO% C8 i I2C2_ER_IRQHandler "I2C2 Error"
%DO% CC i SPI1_IRQHandler "SPI1"
%DO% D0 i SPI2_IRQHandler "SPI2"
%DO% D4 i USART1_IRQHandler "USART1"
%DO% D8 i USART2_IRQHandler "USART2"
%DO% DC i USART3_IRQHandler "USART3"
%DO% E0 i EXTI15_10_IRQHandler "EXTI Lines 10-15"
%DO% E4 i RTCAlarm_IRQHandler "RTC Alarm" "EXTI Line 17"
%DO% E8 i USBWakeUp_IRQHandler "USB Wake Up" "EXTI Line 18"

type lanchon-stm32-vector.S.epilog>>lanchon-stm32-vector.S
type lanchon-stm32-isrs.S.epilog>>lanchon-stm32-isrs.S
type lanchon-stm32-names.inc.epilog>>lanchon-stm32-names.inc
type stm32exceptions.h.epilog>>stm32exceptions.h
type stm32exceptions.c.epilog>>stm32exceptions.c
