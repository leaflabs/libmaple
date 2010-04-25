
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

/**
 * @brief libmaple exception handlers. If MAPLE_DEBUG is set, then these
 * exceptions will ASSERT fail and call into the default _fail() light
 * blinking.
 */

#include "util.h"

void NMIException(void) {
   ASSERT(0);
   while(1)
      ;
}

void HardFaultException(void) {
   ASSERT(0);
   while(1)
      ;
}

void MemManageException(void) {
   ASSERT(0);
   while(1)
      ;
}

void BusFaultException(void) {
   ASSERT(0);
   while(1)
      ;
}

void UsageFaultException(void) {
   ASSERT(0);
   while(1)
      ;
}

