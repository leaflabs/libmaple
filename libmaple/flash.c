/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * ****************************************************************************/

#include "libmaple.h"
#include "flash.h"

#define ACR_PRFTBE                ((uint32)0xFFFFFFEF)
#define ACR_PRFTBE_ENABLE ((uint32)0x00000010)  /* FLASH Prefetch Buffer Enable */
#define ACR_PRFTBE_DISABLE ((uint32)0x00000000)  /* FLASH Prefetch Buffer Disable */

#define ACR_LATENCY               ((uint32)0x00000038)
#define ACR_LATENCY_0                ((uint32)0x00000000)  /* FLASH Zero Latency cycle */
#define ACR_LATENCY_1                ((uint32)0x00000001)  /* FLASH One Latency cycle */
#define ACR_LATENCY_2                ((uint32)0x00000002)  /* FLASH Two Latency cycles */

void flash_enable_prefetch(void) {
   uint32 acr = __read(FLASH_ACR);

   acr &= ACR_PRFTBE;
   acr |= ACR_PRFTBE_ENABLE;

   __write(FLASH_ACR, acr);
}

void flash_set_latency(void) {
   uint32 acr = __read(FLASH_ACR);

   acr &= ACR_LATENCY;
   acr |= ACR_LATENCY_2;

   __write(FLASH_ACR, acr);
}
