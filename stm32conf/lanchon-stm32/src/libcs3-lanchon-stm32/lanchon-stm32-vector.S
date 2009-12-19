/* Vector table for STM32 (by Lanchon) */

	.section	".cs3.interrupt_vector"

	.globl	__cs3_interrupt_vector_lanchon_stm32
	.type	__cs3_interrupt_vector_lanchon_stm32, %object

__cs3_interrupt_vector_lanchon_stm32:
	.long	__cs3_stack
	.long	__cs3_reset
	.long	NMIException
	.long	HardFaultException
	.long	MemManageException
	.long	BusFaultException
	.long	UsageFaultException
	.long	__STM32ReservedException7
	.long	__STM32ReservedException8
	.long	__STM32ReservedException9
	.long	__STM32ReservedException10
	.long	SVCHandler
	.long	DebugMonitor
	.long	__STM32ReservedException13
	.long	PendSVC
	.long	SysTickHandler
	.long	WWDG_IRQHandler
	.long	PVD_IRQHandler
	.long	TAMPER_IRQHandler
	.long	RTC_IRQHandler
	.long	FLASH_IRQHandler
	.long	RCC_IRQHandler
	.long	EXTI0_IRQHandler
	.long	EXTI1_IRQHandler
	.long	EXTI2_IRQHandler
	.long	EXTI3_IRQHandler
	.long	EXTI4_IRQHandler
	.long	DMAChannel1_IRQHandler
	.long	DMAChannel2_IRQHandler
	.long	DMAChannel3_IRQHandler
	.long	DMAChannel4_IRQHandler
	.long	DMAChannel5_IRQHandler
	.long	DMAChannel6_IRQHandler
	.long	DMAChannel7_IRQHandler
	.long	ADC_IRQHandler
	.long	USB_HP_CAN_TX_IRQHandler
	.long	usb_lpIRQHandler
	.long	CAN_RX1_IRQHandler
	.long	CAN_SCE_IRQHandler
	.long	EXTI9_5_IRQHandler
	.long	TIM1_BRK_IRQHandler
	.long	TIM1_UP_IRQHandler
	.long	TIM1_TRG_COM_IRQHandler
	.long	TIM1_CC_IRQHandler
	.long	TIM2_IRQHandler
	.long	TIM3_IRQHandler
	.long	TIM4_IRQHandler
	.long	I2C1_EV_IRQHandler
	.long	I2C1_ER_IRQHandler
	.long	I2C2_EV_IRQHandler
	.long	I2C2_ER_IRQHandler
	.long	SPI1_IRQHandler
	.long	SPI2_IRQHandler
	.long	USART1_IRQHandler
	.long	USART2_IRQHandler
	.long	USART3_IRQHandler
	.long	EXTI15_10_IRQHandler
	.long	RTCAlarm_IRQHandler
	.long	USBWakeUp_IRQHandler

	.size	__cs3_interrupt_vector_lanchon_stm32, . - __cs3_interrupt_vector_lanchon_stm32
