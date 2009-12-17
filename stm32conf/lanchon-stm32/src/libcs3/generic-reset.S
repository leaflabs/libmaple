/* Reset code for generic
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
	.globl __cs3_reset_generic
	.type	__cs3_reset_generic, %function
__cs3_reset_generic:
	.fnstart
#include <rdi-io.h>

	adr	r1, __cs3_heap_start_ptr
	mov	r0,#AngelSWI_Reason_HeapInfo
#if THUMB
	bkpt	0xAB
#else
	swi	0x123456
#endif
	cmp	r0,#0
	blt	2f
/* __cs3_heap_start contains
	[0] ?
	[4] zero or heap limit
	[8] zero or top of stack
	[12] ?  */
	ldr	r2, __cs3_heap_start_ptr

#if THUMB
	ldr	r1,=__cs3_stack
	mov	sp,r1
#else
	ldr	sp,=__cs3_stack
#endif
	ldr	r0,[r2,#8]	/* top of stack */
	cmp	r0, #0
#if THUMB
	beq	1f
	mov	sp,r0
1:
#else
	movne	sp,r0
#endif
	ldr	r1,=__cs3_heap_limit
	ldr	r0,[r2,#4]	/* heap limit */
	cmp	r0,#0
#if THUMB
	beq	1f
	str	r0,[r1]
1:
#else
	strne	r0,[r1]
#endif
	.word	 __cs3_heap_start
2:
#if THUMB
	ldr	r0,=__cs3_start_c
	bx	r0
#else
	b	__cs3_start_c
#endif
	.pool
	.cantunwind
	.fnend
	.align 2
__cs3_heap_start_ptr:
	.word __cs3_heap_start
	.size	__cs3_reset_generic,.-__cs3_reset_generic
