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

#include "libmaple.h"
#include <sys/stat.h>

/* _end is set in the linker command file */
extern caddr_t _end;

void uart_send(const char*str);

/*
 * sbrk -- changes heap size size. Get nbytes more
 *         RAM. We just increment a pointer in what's
 *         left of memory on the board.
 */
caddr_t _sbrk(int nbytes) {
    static caddr_t heap_ptr = NULL;
    caddr_t        base;

    if (heap_ptr == NULL) {
        heap_ptr = (caddr_t)&_end;
    }

    if ((STACK_TOP - (unsigned int)heap_ptr) >= 0) {
        base = heap_ptr;
        heap_ptr += nbytes;
        return (base);
    } else {
        uart_send("heap full!\r\n");
        return ((caddr_t)-1);
    }
}

int _open(const char *path, int flags, ...) {
    return 1;
}

int _close(int fd) {
    return 0;
}

int _fstat(int fd, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int fd) {
    return 1;
}

int isatty(int fd) {
    return 1;
}

int _lseek(int fd, off_t pos, int whence) {
    return -1;
}

unsigned char getch(void) {
//    while (!(USART2->SR & USART_FLAG_RXNE));
//    return USART2->DR;
    return 0;
}


int _read(int fd, char *buf, size_t cnt) {
    *buf = getch();

    return 1;
}

void putch(unsigned char c) {
//    if (c == '\n') putch('\r');

//    while (!(USART2->SR & USART_FLAG_TXE));
//    USART2->DR = c;
}

void cgets(char *s, int bufsize) {
    char *p;
    int c;
    int i;

    for (i = 0; i < bufsize; i++) {
        *(s+i) = 0;
    }
//    memset(s, 0, bufsize);

    p = s;

    for (p = s; p < s + bufsize-1;) {
        c = getch();
        switch (c) {
        case '\r' :
        case '\n' :
            putch('\r');
            putch('\n');
            *p = '\n';
            return;

        case '\b' :
            if (p > s) {
                *p-- = 0;
                putch('\b');
                putch(' ');
                putch('\b');
            }
            break;

        default :
            putch(c);
            *p++ = c;
            break;
        }
    }
    return;
}

int _write(int fd, const char *buf, size_t cnt) {
    int i;
//    uart_send("_write\r\n");

    for (i = 0; i < cnt; i++)
        putch(buf[i]);

    return cnt;
}

/* Override fgets() in newlib with a version that does line editing */
char *fgets(char *s, int bufsize, void *f) {
//    uart_send("fgets\r\n");
    cgets(s, bufsize);
    return s;
}
