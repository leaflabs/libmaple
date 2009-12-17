/* Vector table for arm
 *
 * Version:Sourcery G++ 4.2-84
 * BugURL:https://support.codesourcery.com/GNUToolchain/
 *
 *  Copyright 2007 CodeSourcery.
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply. */

	.section	".cs3.interrupt_vector"
	.globl	__cs3_interrupt_vector_arm
	.type	__cs3_interrupt_vector_arm, %object
__cs3_interrupt_vector_arm:
	.arch armv4
	.arm
	ldr pc, [pc, #24] @ reset
	ldr pc, [pc, #24] @ undef
	ldr pc, [pc, #24] @ swi
	ldr pc, [pc, #24] @ pabort
	ldr pc, [pc, #24] @ dabort
	ldr pc, [pc, #24] @ reserved
	ldr pc, [pc, #24] @ irq
	ldr pc, [pc, #24] @ fiq
	.long	__cs3_reset
	.long	__cs3_isr_undef
	.long	__cs3_isr_swi
	.long	__cs3_isr_pabort
	.long	__cs3_isr_dabort
	.long	__cs3_isr_reserved
	.long	__cs3_isr_irq
	.long	__cs3_isr_fiq
	.size	__cs3_interrupt_vector_arm, . - __cs3_interrupt_vector_arm
