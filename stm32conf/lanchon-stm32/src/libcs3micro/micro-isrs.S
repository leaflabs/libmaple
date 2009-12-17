/* ISRs for micro
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

	.thumb

#if defined (L_micro_isr_interrupt)
	.globl	__cs3_isr_interrupt
	.type	__cs3_isr_interrupt, %function
__cs3_isr_interrupt:
	b .
	.size	__cs3_isr_interrupt, . - __cs3_isr_interrupt

	.weak	__cs3_isr_nmi
	.globl	__cs3_isr_nmi
	.set	__cs3_isr_nmi, __cs3_isr_interrupt
	.weak	__cs3_isr_hard_fault
	.globl	__cs3_isr_hard_fault
	.set	__cs3_isr_hard_fault, __cs3_isr_interrupt
	.weak	__cs3_isr_mpu_fault
	.globl	__cs3_isr_mpu_fault
	.set	__cs3_isr_mpu_fault, __cs3_isr_interrupt
	.weak	__cs3_isr_bus_fault
	.globl	__cs3_isr_bus_fault
	.set	__cs3_isr_bus_fault, __cs3_isr_interrupt
	.weak	__cs3_isr_usage_fault
	.globl	__cs3_isr_usage_fault
	.set	__cs3_isr_usage_fault, __cs3_isr_interrupt
	.weak	__cs3_isr_reserved_7
	.globl	__cs3_isr_reserved_7
	.set	__cs3_isr_reserved_7, __cs3_isr_interrupt
	.weak	__cs3_isr_reserved_8
	.globl	__cs3_isr_reserved_8
	.set	__cs3_isr_reserved_8, __cs3_isr_interrupt
	.weak	__cs3_isr_reserved_9
	.globl	__cs3_isr_reserved_9
	.set	__cs3_isr_reserved_9, __cs3_isr_interrupt
	.weak	__cs3_isr_reserved_10
	.globl	__cs3_isr_reserved_10
	.set	__cs3_isr_reserved_10, __cs3_isr_interrupt
	.weak	__cs3_isr_svcall
	.globl	__cs3_isr_svcall
	.set	__cs3_isr_svcall, __cs3_isr_interrupt
	.weak	__cs3_isr_debug
	.globl	__cs3_isr_debug
	.set	__cs3_isr_debug, __cs3_isr_interrupt
	.weak	__cs3_isr_reserved_13
	.globl	__cs3_isr_reserved_13
	.set	__cs3_isr_reserved_13, __cs3_isr_interrupt
	.weak	__cs3_isr_pendsv
	.globl	__cs3_isr_pendsv
	.set	__cs3_isr_pendsv, __cs3_isr_interrupt
	.weak	__cs3_isr_systick
	.globl	__cs3_isr_systick
	.set	__cs3_isr_systick, __cs3_isr_interrupt
	.weak	__cs3_isr_external_0
	.globl	__cs3_isr_external_0
	.set	__cs3_isr_external_0, __cs3_isr_interrupt
	.weak	__cs3_isr_external_1
	.globl	__cs3_isr_external_1
	.set	__cs3_isr_external_1, __cs3_isr_interrupt
	.weak	__cs3_isr_external_2
	.globl	__cs3_isr_external_2
	.set	__cs3_isr_external_2, __cs3_isr_interrupt
	.weak	__cs3_isr_external_3
	.globl	__cs3_isr_external_3
	.set	__cs3_isr_external_3, __cs3_isr_interrupt
	.weak	__cs3_isr_external_4
	.globl	__cs3_isr_external_4
	.set	__cs3_isr_external_4, __cs3_isr_interrupt
	.weak	__cs3_isr_external_5
	.globl	__cs3_isr_external_5
	.set	__cs3_isr_external_5, __cs3_isr_interrupt
	.weak	__cs3_isr_external_6
	.globl	__cs3_isr_external_6
	.set	__cs3_isr_external_6, __cs3_isr_interrupt
	.weak	__cs3_isr_external_7
	.globl	__cs3_isr_external_7
	.set	__cs3_isr_external_7, __cs3_isr_interrupt
	.weak	__cs3_isr_external_8
	.globl	__cs3_isr_external_8
	.set	__cs3_isr_external_8, __cs3_isr_interrupt
	.weak	__cs3_isr_external_9
	.globl	__cs3_isr_external_9
	.set	__cs3_isr_external_9, __cs3_isr_interrupt
	.weak	__cs3_isr_external_10
	.globl	__cs3_isr_external_10
	.set	__cs3_isr_external_10, __cs3_isr_interrupt
	.weak	__cs3_isr_external_11
	.globl	__cs3_isr_external_11
	.set	__cs3_isr_external_11, __cs3_isr_interrupt
	.weak	__cs3_isr_external_12
	.globl	__cs3_isr_external_12
	.set	__cs3_isr_external_12, __cs3_isr_interrupt
	.weak	__cs3_isr_external_13
	.globl	__cs3_isr_external_13
	.set	__cs3_isr_external_13, __cs3_isr_interrupt
	.weak	__cs3_isr_external_14
	.globl	__cs3_isr_external_14
	.set	__cs3_isr_external_14, __cs3_isr_interrupt
	.weak	__cs3_isr_external_15
	.globl	__cs3_isr_external_15
	.set	__cs3_isr_external_15, __cs3_isr_interrupt
	.weak	__cs3_isr_external_16
	.globl	__cs3_isr_external_16
	.set	__cs3_isr_external_16, __cs3_isr_interrupt
	.weak	__cs3_isr_external_17
	.globl	__cs3_isr_external_17
	.set	__cs3_isr_external_17, __cs3_isr_interrupt
	.weak	__cs3_isr_external_18
	.globl	__cs3_isr_external_18
	.set	__cs3_isr_external_18, __cs3_isr_interrupt
	.weak	__cs3_isr_external_19
	.globl	__cs3_isr_external_19
	.set	__cs3_isr_external_19, __cs3_isr_interrupt
	.weak	__cs3_isr_external_20
	.globl	__cs3_isr_external_20
	.set	__cs3_isr_external_20, __cs3_isr_interrupt
	.weak	__cs3_isr_external_21
	.globl	__cs3_isr_external_21
	.set	__cs3_isr_external_21, __cs3_isr_interrupt
	.weak	__cs3_isr_external_22
	.globl	__cs3_isr_external_22
	.set	__cs3_isr_external_22, __cs3_isr_interrupt
	.weak	__cs3_isr_external_23
	.globl	__cs3_isr_external_23
	.set	__cs3_isr_external_23, __cs3_isr_interrupt
	.weak	__cs3_isr_external_24
	.globl	__cs3_isr_external_24
	.set	__cs3_isr_external_24, __cs3_isr_interrupt
	.weak	__cs3_isr_external_25
	.globl	__cs3_isr_external_25
	.set	__cs3_isr_external_25, __cs3_isr_interrupt
	.weak	__cs3_isr_external_26
	.globl	__cs3_isr_external_26
	.set	__cs3_isr_external_26, __cs3_isr_interrupt
	.weak	__cs3_isr_external_27
	.globl	__cs3_isr_external_27
	.set	__cs3_isr_external_27, __cs3_isr_interrupt
	.weak	__cs3_isr_external_28
	.globl	__cs3_isr_external_28
	.set	__cs3_isr_external_28, __cs3_isr_interrupt
	.weak	__cs3_isr_external_29
	.globl	__cs3_isr_external_29
	.set	__cs3_isr_external_29, __cs3_isr_interrupt
	.weak	__cs3_isr_external_30
	.globl	__cs3_isr_external_30
	.set	__cs3_isr_external_30, __cs3_isr_interrupt
	.weak	__cs3_isr_external_31
	.globl	__cs3_isr_external_31
	.set	__cs3_isr_external_31, __cs3_isr_interrupt
#endif /* interrupt */
