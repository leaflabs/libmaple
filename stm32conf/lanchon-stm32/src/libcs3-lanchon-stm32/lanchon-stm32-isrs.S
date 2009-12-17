/* ISRs for STM32 (by Lanchon) */

	.thumb

#if defined (L_lanchon_stm32_isr_interrupt)

	.globl	__STM32DefaultExceptionHandler
	.type	__STM32DefaultExceptionHandler, %function

__STM32DefaultExceptionHandler:
	b .

	.size	__STM32DefaultExceptionHandler, . - __STM32DefaultExceptionHandler

	.weak	NMIException
	.globl	NMIException
	.set	NMIException, __STM32DefaultExceptionHandler
	.weak	HardFaultException
	.globl	HardFaultException
	.set	HardFaultException, __STM32DefaultExceptionHandler
	.weak	MemManageException
	.globl	MemManageException
	.set	MemManageException, __STM32DefaultExceptionHandler
	.weak	BusFaultException
	.globl	BusFaultException
	.set	BusFaultException, __STM32DefaultExceptionHandler
	.weak	UsageFaultException
	.globl	UsageFaultException
	.set	UsageFaultException, __STM32DefaultExceptionHandler
	.weak	__STM32ReservedException7
	.globl	__STM32ReservedException7
	.set	__STM32ReservedException7, __STM32DefaultExceptionHandler
	.weak	__STM32ReservedException8
	.globl	__STM32ReservedException8
	.set	__STM32ReservedException8, __STM32DefaultExceptionHandler
	.weak	__STM32ReservedException9
	.globl	__STM32ReservedException9
	.set	__STM32ReservedException9, __STM32DefaultExceptionHandler
	.weak	__STM32ReservedException10
	.globl	__STM32ReservedException10
	.set	__STM32ReservedException10, __STM32DefaultExceptionHandler
	.weak	SVCHandler
	.globl	SVCHandler
	.set	SVCHandler, __STM32DefaultExceptionHandler
	.weak	DebugMonitor
	.globl	DebugMonitor
	.set	DebugMonitor, __STM32DefaultExceptionHandler
	.weak	__STM32ReservedException13
	.globl	__STM32ReservedException13
	.set	__STM32ReservedException13, __STM32DefaultExceptionHandler
	.weak	PendSVC
	.globl	PendSVC
	.set	PendSVC, __STM32DefaultExceptionHandler
	.weak	SysTickHandler
	.globl	SysTickHandler
	.set	SysTickHandler, __STM32DefaultExceptionHandler
	.weak	WWDG_IRQHandler
	.globl	WWDG_IRQHandler
	.set	WWDG_IRQHandler, __STM32DefaultExceptionHandler
	.weak	PVD_IRQHandler
	.globl	PVD_IRQHandler
	.set	PVD_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TAMPER_IRQHandler
	.globl	TAMPER_IRQHandler
	.set	TAMPER_IRQHandler, __STM32DefaultExceptionHandler
	.weak	RTC_IRQHandler
	.globl	RTC_IRQHandler
	.set	RTC_IRQHandler, __STM32DefaultExceptionHandler
	.weak	FLASH_IRQHandler
	.globl	FLASH_IRQHandler
	.set	FLASH_IRQHandler, __STM32DefaultExceptionHandler
	.weak	RCC_IRQHandler
	.globl	RCC_IRQHandler
	.set	RCC_IRQHandler, __STM32DefaultExceptionHandler
	.weak	EXTI0_IRQHandler
	.globl	EXTI0_IRQHandler
	.set	EXTI0_IRQHandler, __STM32DefaultExceptionHandler
	.weak	EXTI1_IRQHandler
	.globl	EXTI1_IRQHandler
	.set	EXTI1_IRQHandler, __STM32DefaultExceptionHandler
	.weak	EXTI2_IRQHandler
	.globl	EXTI2_IRQHandler
	.set	EXTI2_IRQHandler, __STM32DefaultExceptionHandler
	.weak	EXTI3_IRQHandler
	.globl	EXTI3_IRQHandler
	.set	EXTI3_IRQHandler, __STM32DefaultExceptionHandler
	.weak	EXTI4_IRQHandler
	.globl	EXTI4_IRQHandler
	.set	EXTI4_IRQHandler, __STM32DefaultExceptionHandler
	.weak	DMAChannel1_IRQHandler
	.globl	DMAChannel1_IRQHandler
	.set	DMAChannel1_IRQHandler, __STM32DefaultExceptionHandler
	.weak	DMAChannel2_IRQHandler
	.globl	DMAChannel2_IRQHandler
	.set	DMAChannel2_IRQHandler, __STM32DefaultExceptionHandler
	.weak	DMAChannel3_IRQHandler
	.globl	DMAChannel3_IRQHandler
	.set	DMAChannel3_IRQHandler, __STM32DefaultExceptionHandler
	.weak	DMAChannel4_IRQHandler
	.globl	DMAChannel4_IRQHandler
	.set	DMAChannel4_IRQHandler, __STM32DefaultExceptionHandler
	.weak	DMAChannel5_IRQHandler
	.globl	DMAChannel5_IRQHandler
	.set	DMAChannel5_IRQHandler, __STM32DefaultExceptionHandler
	.weak	DMAChannel6_IRQHandler
	.globl	DMAChannel6_IRQHandler
	.set	DMAChannel6_IRQHandler, __STM32DefaultExceptionHandler
	.weak	DMAChannel7_IRQHandler
	.globl	DMAChannel7_IRQHandler
	.set	DMAChannel7_IRQHandler, __STM32DefaultExceptionHandler
	.weak	ADC_IRQHandler
	.globl	ADC_IRQHandler
	.set	ADC_IRQHandler, __STM32DefaultExceptionHandler
	.weak	USB_HP_CAN_TX_IRQHandler
	.globl	USB_HP_CAN_TX_IRQHandler
	.set	USB_HP_CAN_TX_IRQHandler, __STM32DefaultExceptionHandler
	.weak	USB_LP_CAN_RX0_IRQHandler
	.globl	USB_LP_CAN_RX0_IRQHandler
	.set	USB_LP_CAN_RX0_IRQHandler, __STM32DefaultExceptionHandler
	.weak	CAN_RX1_IRQHandler
	.globl	CAN_RX1_IRQHandler
	.set	CAN_RX1_IRQHandler, __STM32DefaultExceptionHandler
	.weak	CAN_SCE_IRQHandler
	.globl	CAN_SCE_IRQHandler
	.set	CAN_SCE_IRQHandler, __STM32DefaultExceptionHandler
	.weak	EXTI9_5_IRQHandler
	.globl	EXTI9_5_IRQHandler
	.set	EXTI9_5_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TIM1_BRK_IRQHandler
	.globl	TIM1_BRK_IRQHandler
	.set	TIM1_BRK_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TIM1_UP_IRQHandler
	.globl	TIM1_UP_IRQHandler
	.set	TIM1_UP_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TIM1_TRG_COM_IRQHandler
	.globl	TIM1_TRG_COM_IRQHandler
	.set	TIM1_TRG_COM_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TIM1_CC_IRQHandler
	.globl	TIM1_CC_IRQHandler
	.set	TIM1_CC_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TIM2_IRQHandler
	.globl	TIM2_IRQHandler
	.set	TIM2_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TIM3_IRQHandler
	.globl	TIM3_IRQHandler
	.set	TIM3_IRQHandler, __STM32DefaultExceptionHandler
	.weak	TIM4_IRQHandler
	.globl	TIM4_IRQHandler
	.set	TIM4_IRQHandler, __STM32DefaultExceptionHandler
	.weak	I2C1_EV_IRQHandler
	.globl	I2C1_EV_IRQHandler
	.set	I2C1_EV_IRQHandler, __STM32DefaultExceptionHandler
	.weak	I2C1_ER_IRQHandler
	.globl	I2C1_ER_IRQHandler
	.set	I2C1_ER_IRQHandler, __STM32DefaultExceptionHandler
	.weak	I2C2_EV_IRQHandler
	.globl	I2C2_EV_IRQHandler
	.set	I2C2_EV_IRQHandler, __STM32DefaultExceptionHandler
	.weak	I2C2_ER_IRQHandler
	.globl	I2C2_ER_IRQHandler
	.set	I2C2_ER_IRQHandler, __STM32DefaultExceptionHandler
	.weak	SPI1_IRQHandler
	.globl	SPI1_IRQHandler
	.set	SPI1_IRQHandler, __STM32DefaultExceptionHandler
	.weak	SPI2_IRQHandler
	.globl	SPI2_IRQHandler
	.set	SPI2_IRQHandler, __STM32DefaultExceptionHandler
	.weak	USART1_IRQHandler
	.globl	USART1_IRQHandler
	.set	USART1_IRQHandler, __STM32DefaultExceptionHandler
	.weak	USART2_IRQHandler
	.globl	USART2_IRQHandler
	.set	USART2_IRQHandler, __STM32DefaultExceptionHandler
	.weak	USART3_IRQHandler
	.globl	USART3_IRQHandler
	.set	USART3_IRQHandler, __STM32DefaultExceptionHandler
	.weak	EXTI15_10_IRQHandler
	.globl	EXTI15_10_IRQHandler
	.set	EXTI15_10_IRQHandler, __STM32DefaultExceptionHandler
	.weak	RTCAlarm_IRQHandler
	.globl	RTCAlarm_IRQHandler
	.set	RTCAlarm_IRQHandler, __STM32DefaultExceptionHandler
	.weak	USBWakeUp_IRQHandler
	.globl	USBWakeUp_IRQHandler
	.set	USBWakeUp_IRQHandler, __STM32DefaultExceptionHandler

#endif /* L_lanchon_stm32_isr_interrupt */
