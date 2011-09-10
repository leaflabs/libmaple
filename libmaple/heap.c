/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 Michael Hope <michaelh@juju.net.nz>
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
 *  @file heap.c
 *
 *  @brief Very simple allocate-only heap.
 */

#include "heap.h"

#define STACK_RESERVED_BYTES 1024

extern uint8 _end;
extern uint8 __stack_end;

/**
 * @brief Allocate a number of bytes from the heap.
 *
 * Result is word aligned.  Memory cannot be returned.
 *
 * @param nbytes  number of bytes to allocate
 * @return        start of the region, or NULL on OOM
 */
void *heap_alloc(uint32 nbytes) {
    /* This is a trial implementation.  It's equivalent to sbrk() and
       overlaps.  Lets hope Newlib's malloc() is never called.
    */

    /* Design-wise, returning NULL is poor.  It's better to halt the
       system here.
    */

    /* Would be nice to have a system mode and fault if you allocate
       memory past initial initialisation.
    */

    static uint8 *pbreak = &_end;

    uint8 *pnext = pbreak + ((nbytes + 3) & ~3);

    if (pnext >= &__stack_end - STACK_RESERVED_BYTES) {
        return NULL;
    }

    uint8 *pat = pbreak;
    pbreak = pnext;

    return pat;
}
