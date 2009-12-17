/* ISRs for arm
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

	.arch armv4t
	.arm

#if defined (L_arm_isr_interrupt)
	.globl	__cs3_isr_interrupt
	.type	__cs3_isr_interrupt, %function
__cs3_isr_interrupt:
	b .
	.size	__cs3_isr_interrupt, . - __cs3_isr_interrupt

	.weak	__cs3_isr_undef
	.globl	__cs3_isr_undef
	.set	__cs3_isr_undef, __cs3_isr_interrupt
	.weak	__cs3_isr_swi
	.globl	__cs3_isr_swi
	.set	__cs3_isr_swi, __cs3_isr_interrupt
	.weak	__cs3_isr_pabort
	.globl	__cs3_isr_pabort
	.set	__cs3_isr_pabort, __cs3_isr_interrupt
	.weak	__cs3_isr_dabort
	.globl	__cs3_isr_dabort
	.set	__cs3_isr_dabort, __cs3_isr_interrupt
	.weak	__cs3_isr_reserved
	.globl	__cs3_isr_reserved
	.set	__cs3_isr_reserved, __cs3_isr_interrupt
	.weak	__cs3_isr_irq
	.globl	__cs3_isr_irq
	.set	__cs3_isr_irq, __cs3_isr_interrupt
	.weak	__cs3_isr_fiq
	.globl	__cs3_isr_fiq
	.set	__cs3_isr_fiq, __cs3_isr_interrupt
#endif /* interrupt */
