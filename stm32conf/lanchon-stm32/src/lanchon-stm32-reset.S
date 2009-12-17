/* Reset code for STM32 (by Lanchon)
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

#if defined(__thumb2__) || defined(__ARM_ARCH_6M__)
#define THUMB 1
	.thumb
	.thumb_func
#else
	.arm
#endif
	.section .cs3.reset,"x",%progbits
	.globl __cs3_reset_lanchon_stm32
	.type	__cs3_reset_lanchon_stm32, %function
__cs3_reset_lanchon_stm32:
	.fnstart
#if THUMB
	ldr	r0,=_start
	bx	r0
#else
	b	_start
#endif
	.pool
	.cantunwind
	.fnend
	.size	__cs3_reset_lanchon_stm32,.-__cs3_reset_lanchon_stm32
