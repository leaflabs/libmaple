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
 * @brief libmaple serial peripheral interface (SPI) definitions
 *
 * Initial implementation for the SPI interface.
 *
 * This driver implements only the bare essentials of a polling driver at the
 * moment. Master mode only, 8-bit data frames, and polling.
 *
 * The caller is responsible for controlling the chip select line.
 *
 * TODO: interrupt based driver, DMA.
 *
 */

#include "libmaple.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"

typedef struct spi_dev {
   SPI *base;
   GPIO_Port *port;
   uint8 sck_pin;
   uint8 miso_pin;
   uint8 mosi_pin;
} spi_dev;

static const spi_dev spi_dev1 = {
   .base     = (SPI*)SPI1_BASE,
   .port     = GPIOA_BASE,
   .sck_pin  = 5,
   .miso_pin = 6,
   .mosi_pin = 7
};

static const spi_dev spi_dev2 = {
   .base     = (SPI*)SPI2_BASE,
   .port     = GPIOB_BASE,
   .sck_pin  = 13,
   .miso_pin = 14,
   .mosi_pin = 15
};

static void spi_gpio_cfg(const spi_dev *dev);

/**
 * @brief Initialize a spi peripheral
 * @param spi_num which spi to turn on, SPI1 or SPI2?
 * @param prescale prescale factor on the input clock.
 * @param endian data frame format (LSBFIRST?)
 * @param mode SPI mode number
 */
void spi_init(uint32 spi_num,
              uint32 prescale,
              uint32 endian,
              uint32 mode) {
   ASSERT(spi_num == 1 || spi_num == 2);
   ASSERT(mode < 4);

   SPI *spi;
   uint32 cr1 = 0;

   switch (spi_num) {
   case 1:
      /* limit to 18 mhz max speed  */
      ASSERT(prescale != CR1_BR_PRESCALE_2);
      spi = (SPI*)SPI1_BASE;
      rcc_enable_clk_spi1();
      spi_gpio_cfg(&spi_dev1);
      break;
   case 2:
      spi = (SPI*)SPI2_BASE;
      rcc_enable_clk_spi2();
      spi_gpio_cfg(&spi_dev2);
      break;
   }

   cr1 = prescale | endian | mode | CR1_MSTR | CR1_SSI | CR1_SSM;
   spi->CR1 = cr1;

   /* Peripheral enable */
   spi->CR1 |= CR1_SPE;
}


/**
 * @brief SPI synchronous 8-bit write, blocking.
 * @param spi_num which spi to send on
 * @return data shifted back from the slave
 */
uint8 spi_tx_byte(uint32 spi_num, uint8 data) {
   SPI *spi;

   ASSERT(spi_num == 1 || spi_num == 2);

   spi = (spi_num == 1) ? (SPI*)SPI1_BASE : (SPI*)SPI2_BASE;

   spi->DR = data;

   while (!(spi->SR & SR_TXE) ||
           (spi->SR & SR_BSY))
      ;

   return spi->DR;
}

uint8 spi_tx(uint32 spi_num, uint8 *buf, uint32 len) {
   SPI *spi;
   uint32 i = 0;
   uint8 rc;

   ASSERT(spi_num == 1 || spi_num == 2);
   spi = (spi_num == 1) ? (SPI*)SPI1_BASE : (SPI*)SPI2_BASE;

   if (!len) {
      return 0;
   }

   while (i < len) {
      spi->DR = buf[i];
      while (!(spi->SR & SR_TXE) ||
              (spi->SR & SR_BSY) ||
             !(spi->SR & SR_RXNE))
         ;
      rc = spi->DR;
      i++;
   }
   return rc;
}

static void spi_gpio_cfg(const spi_dev *dev) {
   gpio_set_mode(dev->port, dev->sck_pin, GPIO_MODE_AF_OUTPUT_PP);
   gpio_set_mode(dev->port, dev->miso_pin, GPIO_MODE_AF_OUTPUT_PP);
   gpio_set_mode(dev->port, dev->mosi_pin, GPIO_MODE_AF_OUTPUT_PP);
}
