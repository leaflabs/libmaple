/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/flash.h
 * @brief Flash support.
 */

#ifndef _LIBMAPLE_FLASH_H_
#define _LIBMAPLE_FLASH_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>

#define FLASH_WAIT_STATE_0              0x0
#define FLASH_WAIT_STATE_1              0x1
#define FLASH_WAIT_STATE_2              0x2
#define FLASH_WAIT_STATE_3              0x3
#define FLASH_WAIT_STATE_4              0x4
#define FLASH_WAIT_STATE_5              0x5
#define FLASH_WAIT_STATE_6              0x6
#define FLASH_WAIT_STATE_7              0x7

/* The series header must define FLASH_SAFE_WAIT_STATES, the smallest
 * number of wait states that it is safe to use when the MCU clock is
 * at its fastest rate (not considering overclocking). */
#include <series/flash.h>

/*
 * Setup routines
 */

void flash_enable_prefetch(void);
void flash_set_latency(uint32 wait_states);

#ifdef __cplusplus
}
#endif

#endif
