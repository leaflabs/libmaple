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

#ifndef _PRINT_H_
#define _PRINT_H_

#include "libmaple_types.h"

#define DEC   10
#define HEX   16
#define OCT    8
#define BIN    2
#define BYTE   0                // yuck

class Print {
 public:
    virtual void write(uint8) = 0;
    virtual void write(const char *str);
    virtual void write(void *buf, uint32 size);

    void print(char);
    void print(const char[]);
    void print(uint8);
    void print(int32);
    void print(uint32);
    void print(int64);
    void print(uint64);
    void print(int32, int);
    void print(int64, int);
    void print(double);

    void println(void);
    void println(char);
    void println(const char[]);
    void println(uint8);
    void println(int32);
    void println(uint32);
    void println(int64);
    void println(uint64);
    void println(int32, int);
    void println(int64, int);
    void println(double);
};

#endif
