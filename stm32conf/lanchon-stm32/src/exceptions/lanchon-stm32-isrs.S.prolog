/* ISRs for STM32 (by Lanchon) */

	.thumb

#if defined (L_lanchon_stm32_isr_interrupt)

	.globl	__STM32DefaultExceptionHandler
	.type	__STM32DefaultExceptionHandler, %function

__STM32DefaultExceptionHandler:
	b .

	.size	__STM32DefaultExceptionHandler, . - __STM32DefaultExceptionHandler

