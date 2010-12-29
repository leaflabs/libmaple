/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Michael Hope.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *****************************************************************************/

/**
 *  @file iwdg.h
 *
 *  @brief Independent watchdog support
 */

#ifndef _IWDG_H_
#define _IWDG_H_

#ifdef __cplusplus
extern "C"{
#endif

#define IWDG_BASE               0x40003000
#define IWDG_KR                 (IWDG_BASE + 0x0)
#define IWDG_PR                 (IWDG_BASE + 0x4)
#define IWDG_RLR                (IWDG_BASE + 0x8)
#define IWDG_SR                 (IWDG_BASE + 0xC)

enum {
    IWDG_PRE_4,
    IWDG_PRE_8,
    IWDG_PRE_16,
    IWDG_PRE_32,
    IWDG_PRE_64,
    IWDG_PRE_128,
    IWDG_PRE_256
};

void iwdg_init(uint8 prescaler, uint16 reload);
void iwdg_feed(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
