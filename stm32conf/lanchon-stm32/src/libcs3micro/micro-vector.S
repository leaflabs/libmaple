/* Vector table for micro
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
	.globl	__cs3_interrupt_vector_micro
	.type	__cs3_interrupt_vector_micro, %object
__cs3_interrupt_vector_micro:
	.long	__cs3_stack
	.long	__cs3_reset
	.long	__cs3_isr_nmi
	.long	__cs3_isr_hard_fault
	.long	__cs3_isr_mpu_fault
	.long	__cs3_isr_bus_fault
	.long	__cs3_isr_usage_fault
	.long	__cs3_isr_reserved_7
	.long	__cs3_isr_reserved_8
	.long	__cs3_isr_reserved_9
	.long	__cs3_isr_reserved_10
	.long	__cs3_isr_svcall
	.long	__cs3_isr_debug
	.long	__cs3_isr_reserved_13
	.long	__cs3_isr_pendsv
	.long	__cs3_isr_systick
	.long	__cs3_isr_external_0
	.long	__cs3_isr_external_1
	.long	__cs3_isr_external_2
	.long	__cs3_isr_external_3
	.long	__cs3_isr_external_4
	.long	__cs3_isr_external_5
	.long	__cs3_isr_external_6
	.long	__cs3_isr_external_7
	.long	__cs3_isr_external_8
	.long	__cs3_isr_external_9
	.long	__cs3_isr_external_10
	.long	__cs3_isr_external_11
	.long	__cs3_isr_external_12
	.long	__cs3_isr_external_13
	.long	__cs3_isr_external_14
	.long	__cs3_isr_external_15
	.long	__cs3_isr_external_16
	.long	__cs3_isr_external_17
	.long	__cs3_isr_external_18
	.long	__cs3_isr_external_19
	.long	__cs3_isr_external_20
	.long	__cs3_isr_external_21
	.long	__cs3_isr_external_22
	.long	__cs3_isr_external_23
	.long	__cs3_isr_external_24
	.long	__cs3_isr_external_25
	.long	__cs3_isr_external_26
	.long	__cs3_isr_external_27
	.long	__cs3_isr_external_28
	.long	__cs3_isr_external_29
	.long	__cs3_isr_external_30
	.long	__cs3_isr_external_31
	.size	__cs3_interrupt_vector_micro, . - __cs3_interrupt_vector_micro
