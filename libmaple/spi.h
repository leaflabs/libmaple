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
 *  @brief libmaple serial peripheral interface (SPI) prototypes and declarations
 */

#ifndef _SPI_H_
#define _SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* peripheral addresses */
#define SPI1_BASE                   0x40013000
#define SPI2_BASE                   0x40003800

/* baud rate prescaler bits */
#define CR1_BR                      0x00000038
#define CR1_BR_PRESCALE_2           0x00000000
#define CR1_BR_PRESCALE_4           0x00000008
#define CR1_BR_PRESCALE_8           0x00000010
#define CR1_BR_PRESCALE_16          0x00000018
#define CR1_BR_PRESCALE_32          0x00000020
#define CR1_BR_PRESCALE_64          0x00000028
#define CR1_BR_PRESCALE_128         0x00000030
#define CR1_BR_PRESCALE_256         0x00000038

#define CR1_LSBFIRST                    BIT(7)     // data frame format
#define CR1_MSTR                        BIT(2)     // master selection
#define CR1_SSM                         BIT(9)     // software slave management
#define CR1_SSI                         BIT(8)     // internal slave select
#define CR1_SPE                         BIT(6)     // peripheral enable

/* Status register bits  */
#define SR_RXNE                         BIT(0)     // rx buffer not empty
#define SR_TXE                          BIT(1)     // transmit buffer empty
#define SR_BSY                          BIT(7)     // busy flag

typedef struct SPI {
   __io uint16 CR1;
   uint16 pad0;
   __io uint8 CR2;
   uint8 pad1[3];
   __io uint8 SR;
   uint8 pad2[3];
   __io uint16 DR;
   uint16 pad3;
   __io uint16 CRCPR;
   uint16 pad4;
   __io uint16 RXCRCR;
   uint16 pad5;
   __io uint16 TXCRCR;
   uint16 pad6;
} SPI;

enum {
   SPI_MSBFIRST         = 0,
   SPI_LSBFIRST         = BIT(7),
};

enum {
   SPI_PRESCALE_2       = (0x0 << 3),
   SPI_PRESCALE_4       = (0x1 << 3),
   SPI_PRESCALE_8       = (0x2 << 3),
   SPI_PRESCALE_16      = (0x3 << 3),
   SPI_PRESCALE_32      = (0x4 << 3),
   SPI_PRESCALE_64      = (0x5 << 3),
   SPI_PRESCALE_128     = (0x6 << 3),
   SPI_PRESCALE_256     = (0x7 << 3)
};

void spi_init(uint32 spi_num,
              uint32 prescale,
              uint32 endian,
              uint32 mode);
uint8 spi_tx_byte(uint32 spi_num, uint8 data);
uint8 spi_tx(uint32 spi_num, uint8 *buf, uint32 len);

static inline uint8 spi_rx(uint32 spi_num) {
   SPI *spi;

   ASSERT(spi_num == 1 || spi_num == 2);
   spi = (spi_num == 1) ? (SPI*)SPI1_BASE : (SPI*)SPI2_BASE;

   return spi->DR;
}

#ifdef __cplusplus
}
#endif

#endif

