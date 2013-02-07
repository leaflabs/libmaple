/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010, 2011, 2012 LeafLabs, LLC.
 * Copyright (c) 2013 Manuel Odendahl <wesen@ruinwesen.com>
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
 * @file libmaple/stm32f1/flash.c
 * @brief STM32F1 Flash writing support.
 */

#include "flash.h"

#define FLASH_KEY1     0x45670123
#define FLASH_KEY2     0xCDEF89AB

void flash_unlock() {
    FLASH_BASE->KEYR = FLASH_KEY1;
    FLASH_BASE->KEYR = FLASH_KEY2;
}

void flash_lock() {
    FLASH_BASE->CR = 0x00000080;
}

static inline void flash_wait_busy() {
    while (FLASH_BASE->SR & FLASH_SR_BSY) {
        ;
    }
}

uint8 flash_erase_page(uint32 page_address) {
    uint32 rwm_val = FLASH_BASE->CR;
    rwm_val |= FLASH_CR_PER;
    FLASH_BASE->CR = rwm_val;

    flash_wait_busy();

    FLASH_BASE->AR = page_address;
    FLASH_BASE->CR = FLASH_CR_STRT | FLASH_CR_PER;
    flash_wait_busy();

    rwm_val = 0x00;
    FLASH_BASE->CR = rwm_val;

    return 1;
}

uint8 flash_erase_pages(uint32 page_address, uint16 n) {
    while (n-- > 0) {
        if (!flash_erase_page(page_address + 0x800 * n)) {
            return 0;
        }
    }
    return 1;
}

uint8 flash_write_word(uint32 address, uint32 word) {
    uint16 *flash_address = (uint16 *)address;
    uint32 lh = (uint32)word & 0xFFFF;
    uint32 hh = ((uint32)word & 0xFFFF0000) >> 16;

    uint32 rwm_val = FLASH_BASE->CR;
    FLASH_BASE->CR = FLASH_CR_PG;

    flash_wait_busy();
    *(flash_address + 0x01) = (uint16)hh;
    flash_wait_busy();
    *flash_address = (uint16)lh;
    flash_wait_busy();

    rwm_val &= 0xFFFFFFFE;
    FLASH_BASE->CR = rwm_val;

    if (*(uint32 *)address != word) {
        return 0;
    }

    return 1;
}
