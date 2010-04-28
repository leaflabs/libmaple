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
 * @brief HardwareSPI definitions
 */

#ifndef _HARDWARESPI_H_
#define _HARDWARESPI_H_

typedef enum SPIFrequency {
   SPI_18MHZ       = 0,
   SPI_9MHZ        = 1,
   SPI_4_5MHZ      = 2,
   SPI_2_25MHZ     = 3,
   SPI_1_125MHZ    = 4,
   SPI_562_500KHZ  = 5,
   SPI_281_250KHZ  = 6,
   SPI_140_625KHZ  = 7,
   MAX_SPI_FREQS   = 8,
} SPIFrequency;

class HardwareSPI {
   private:
      uint32 spi_num;

   public:
      HardwareSPI(uint32 spi_num);
      void begin(void);
      void begin(SPIFrequency freq, uint32 endianness, uint32 mode);
      uint8 send(uint8 data);
      uint8 send(uint8 *data, uint32 length);
      uint8 recv(void);
};

#endif

