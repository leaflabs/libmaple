/* Vector table for STM32 (by Lanchon) */

	.section	".cs3.interrupt_vector"

	.globl	__cs3_interrupt_vector_lanchon_stm32
	.type	__cs3_interrupt_vector_lanchon_stm32, %object

__cs3_interrupt_vector_lanchon_stm32:
	.long	__cs3_stack
	.long	__cs3_reset
