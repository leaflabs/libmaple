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
 * @brief HardwareSPI "wiring-like" api for SPI
 */

/* NOTES:
 *
 * Speeds:
 * -----------------------------------
 * Interface num:     SPI1        SPI2
 * Bus                APB2        APB1
 * -----------------------------------
 * Prescaler         Frequencies
 * -----------------------------------
 * 2:                  N/A  18 000 000
 * 4:           18 000 000   9 000 000
 * 8:            9 000 000   4 500 000
 * 16:           4 500 000   2 250 000
 * 32:           2 250 000   1 125 000
 * 64:           1 125 000     562 500
 * 128:            562 500     281 250
 * 256:            281 250     140 625
 *
 * TODO: Do the complementary PWM outputs mess up SPI2?
 * */

#include "wirish.h"
#include "spi.h"
#include "HardwareSPI.h"

static const uint32 prescaleFactors[MAX_SPI_FREQS] = {
   SPI_PRESCALE_2,               // SPI_18MHZ
   SPI_PRESCALE_4,               // SPI_9MHZ
   SPI_PRESCALE_8,               // SPI_4_5MHZ
   SPI_PRESCALE_16,              // SPI_2_25MHZ
   SPI_PRESCALE_32,              // SPI_1_125MHZ
   SPI_PRESCALE_64,              // SPI_562_500KHZ
   SPI_PRESCALE_128,             // SPI_281_250KHZ
   SPI_PRESCALE_256,             // SPI_140_625KHZ
};

/**
 * @brief Initialize a SPI peripheral
 * @param freq frequency to run at, must one of the following values:
 *           - SPI_18MHZ
 *           - SPI_9MHZ
 *           - SPI_4_5MHZ
 *           - SPI_2_25MHZ
 *           - SPI_1_125MHZ
 *           - SPI_562_500KHZ
 *           - SPI_281_250KHZ
 *           - SPI_140_625KHZ
 * @param endianness endianness of the data frame, must be either LSBFIRST
 *           or MSBFIRST
 * @param mode SPI standard CPOL and CPHA levels
 */
void HardwareSPI::begin(SPIFrequency freq, uint32 endianness, uint32 mode) {
   uint32 spi_num    = this->spi_num;
   uint32 prescale;

   if ((freq >= MAX_SPI_FREQS)     ||
       !((endianness == LSBFIRST)  ||
         (endianness == MSBFIRST)) ||
       (mode >= 4)) {
      return;
   }

   if (spi_num == 1) {
      /* SPI1 is too fast for 140625  */
      if (freq == SPI_140_625KHZ) {
         return;
      }

      /* Turn off PWM on shared pins */
      timer_set_mode(3, 2, TIMER_DISABLED);
      timer_set_mode(3, 1, TIMER_DISABLED);
   }

   endianness = (endianness == LSBFIRST) ? SPI_LSBFIRST : SPI_MSBFIRST;
   prescale = (spi_num == 1) ? prescaleFactors[freq + 1] : prescaleFactors[freq];

   spi_init(spi_num, prescale, endianness, 0);
}

/**
 * @brief Initialize a SPI peripheral with a default speed of 1.125 MHZ, MSBFIRST,
 *      mode 0
 * @param mode SPI standard CPOL and CPHA levels
 */
void HardwareSPI::begin(void) {
   begin(SPI_1_125MHZ, MSBFIRST, 0);
}

/**
 * @brief send a byte out the spi peripheral
 * @param data byte to send
 */
uint8 HardwareSPI::send(uint8 data) {
   return spi_tx_byte(this->spi_num, data);
}

uint8 HardwareSPI::send(uint8 *buf, uint32 len) {
   return spi_tx(this->spi_num, buf, len);
}


/**
 * @brief read a byte from the spi peripheral
 * @return byte in the buffer
 */
uint8 HardwareSPI::recv(void) {
   return spi_rx(this->spi_num);
}

HardwareSPI::HardwareSPI(uint32 spi_num) {
   this->spi_num = spi_num;
}
