/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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

#include "Print.h"

#include <cstdio>
#include <climits>
#include <cstring>

// We'll allocate character buffers of size INT_BUF_SIZE to hold the
// string representations of numbers; this value ensures that they're
// big enough to accomodate the biggest integral value + null byte.
//
// E.g., consider -(2^63-1) = -9223372036854775807, which is 20
// characters long, including the minus sign.  The other edge cases
// are similar.
//
// (Nonetheless, use snprintf everywhere, just in case of error).
#define INT_BUF_SIZE 21

// An IEEE-754 double buys you about 16 digits of precision; there's
// the possibility of minus signs, a decimal point, 'e+'/'e-', etc.
// While the Right Thing is to follow Steele and White, I'm just going
// to double what I consider a safe number of bytes and hope for the
// best.
#define DOUBLE_BUF_SIZE 40

static void fillBase(char *buf, int buf_size, int64 n,
                     uint8 n_real_bits, int base);
static void fillBinary(char *buf, int64 n, int start_bit);
static char baseToFmtSpec(int base);

void Print::write(const char *str) {
    for (const char *c = str; *c != '\0'; c++) {
        write(*c);
    }
}

void Print::write(void *buffer, uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        write(*((uint8*)buffer + i));
    }
}

void Print::print(char c) {
    print((uint8) c);
}

void Print::print(const char str[]) {
    write(str);
}

void Print::print(uint8 b) {
    write(b);
}

void Print::print(int32 n) {
    print(n, DEC);
}

void Print::print(uint32 n) {
    print((uint64) n);
}

void Print::print(int64 n) {
    print(n, DEC);
}

void Print::print(uint64 n) {
    char buf[INT_BUF_SIZE];
    snprintf(buf, INT_BUF_SIZE, "%llu", n);
    write(buf);
}

void Print::print(int32 n, int base) {
    // Worst case: sign bit set && base == BIN: 32 bytes for digits +
    // 1 null (base == BIN means no minus sign).
    char buf[33];
    fillBase(buf, sizeof(buf), (int64)n, 32, base);
    write(buf);
}

void Print::print(int64 n, int base) {
    // As above, but now 64 bytes for bits + 1 null
    char buf[65];
    fillBase(buf, sizeof(buf), n, 64, base);
    write(buf);
}

void Print::print(double n) {
    char buf[DOUBLE_BUF_SIZE];
    // This breaks strict compliance with the Arduino library behavior
    // (which is equivalent to using "%.2f"), but that's really not
    // enough.  According to Stroustrup, "%f" without precision is
    // equivalent to ".6f", which is much better.
    snprintf(buf, DOUBLE_BUF_SIZE, "%f", n);
    write(buf);
}

void Print::println(void) {
    print("\r\n");
}

void Print::println(char c) {
    print(c);
    println();
}

void Print::println(const char c[]) {
    print(c);
    println();
}

void Print::println(uint8 b) {
    print(b);
    println();
}

void Print::println(int32 n) {
    print(n);
    println();
}

void Print::println(uint32 n) {
    print(n);
    println();
}

void Print::println(int64 n) {
    print(n);
    println();
}

void Print::println(uint64 n) {
    print(n);
    println();
}

void Print::println(int32 n, int base) {
    print(n, base);
    println();
}

void Print::println(int64 n, int base) {
    print(n, base);
    println();
}

void Print::println(double n) {
    print(n);
    println();
}

// -- Auxiliary functions -----------------------------------------------------

static void fillBase(char *buf, int buf_size, int64 n,
                     uint8 n_real_bits, int base) {
    if (base == BIN) {
        fillBinary(buf, n, n_real_bits - 1);
    } else {
        char spec = baseToFmtSpec(base);
        char fmt[5];

        if (base == BYTE)
            n = (uint8)n;

        if (n_real_bits == 32) {
            snprintf(fmt, sizeof(fmt), "%%l%c", spec);
            snprintf(buf, buf_size, fmt, (int32)n);
        } else {
            snprintf(fmt, sizeof(fmt), "%%ll%c", spec);
            snprintf(buf, buf_size, fmt, n);
        }
    }
}

// Assumes sizeof(buf) > start_bit.
static void fillBinary(char *buf, int64 n, int start_bit) {
    int b = 0;                // position in buf
    int i = start_bit;        // position in n's bits
    while(!(n & (1 << i))) {
        i--;
    }
    for(; i >= 0; i--) {
        buf[b++] = '0' + ((n >> i) & 0x1);
    }
    buf[b] = '\0';
}

static char baseToFmtSpec(int base) {
    switch (base) {
    case DEC:
        return 'd';
    case HEX:
        return 'x';
    case OCT:
        return 'o';
    case BYTE:
        return 'd';
    default:
        // Shouldn't happen, but give a sensible default
        return 'd';
    }
}
