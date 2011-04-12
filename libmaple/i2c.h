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
 *  @brief libmaple i2c header
 */

#ifndef _I2C_H_
#define _I2C_H_

typedef struct i2c_reg_map {
    __io uint32 CR1;
    __io uint32 CR2;
    __io uint32 OAR1;
    __io uint32 OAR2;
    __io uint32 DR;
    __io uint32 SR1;
    __io uint32 SR2;
    __io uint32 CCR;
    __io uint32 TRISE;
} i2c_reg_map;

typedef enum i2c_state {
    I2C_STATE_IDLE,
    I2C_STATE_XFER_DONE,
    I2C_STATE_BUSY,
    I2C_STATE_ERROR             = -1
} i2c_state;

typedef struct i2c_msg {
    uint16 addr;
#define I2C_MSG_READ            0x1
#define I2C_MSG_10BIT_ADDR      0x2
    uint16 flags;
    uint16 length;
    uint16 xferred;
    uint8 *data;
} i2c_msg;

typedef struct i2c_dev {
    i2c_reg_map *regs;
    gpio_dev *gpio_port;
    uint8 sda_pin;
    uint8 scl_pin;
    uint8 clk_line;
    uint8 ev_nvic_line;
    uint8 er_nvic_line;
    volatile uint8 state;
    uint16 msgs_left;
    i2c_msg *msg;
} i2c_dev;

extern i2c_dev* const I2C1;
extern i2c_dev* const I2C2;

#define I2C1_BASE               (i2c_reg_map*)0x40005400
#define I2C2_BASE               (i2c_reg_map*)0x40005800

/* i2c enable options */
#define I2C_FAST_MODE           0x1             // 400 khz
#define I2C_DUTY_16_9           0x2             // 16/9 duty ratio

/* Control register 1 bits */
#define I2C_CR1_SWRST           BIT(15)         // Software reset
#define I2C_CR1_ALERT           BIT(13)         // SMBus alert
#define I2C_CR1_PEC             BIT(12)         // Packet error checking
#define I2C_CR1_POS             BIT(11)         // Acknowledge/PEC position
#define I2C_CR1_ACK             BIT(10)         // Acknowledge enable
#define I2C_CR1_START           BIT(8)          // Start generation
#define I2C_CR1_STOP            BIT(9)          // Stop generation
#define I2C_CR1_PE              BIT(0)          // Peripheral Enable

/* Control register 2 bits */
#define I2C_CR2_LAST            BIT(12)         // DMA last transfer
#define I2C_CR2_DMAEN           BIT(11)         // DMA requests enable
#define I2C_CR2_ITBUFEN         BIT(10)         // Buffer interrupt enable
#define I2C_CR2_ITEVTEN         BIT(9)          // Event interupt enable
#define I2C_CR2_ITERREN         BIT(8)          // Error interupt enable
#define I2C_CR2_FREQ            0xFFF           // Peripheral input frequency

/* Clock control register bits */
#define I2C_CCR_FS              BIT(15)         // Fast mode selection
#define I2C_CCR_DUTY            BIT(14)         // 16/9 duty ratio
#define I2C_CCR_CCR             0xFFF           // Clock control bits

/* Status register 1 bits  */
#define I2C_SR1_SB              BIT(0)          // Start bit
#define I2C_SR1_ADDR            BIT(1)          // Address sent/matched
#define I2C_SR1_BTF             BIT(2)          // Byte transfer finished
#define I2C_SR1_ADD10           BIT(3)          // 10-bit header sent
#define I2C_SR1_STOPF           BIT(4)          // Stop detection
#define I2C_SR1_RXNE            BIT(6)          // Data register not empty
#define I2C_SR1_TXE             BIT(7)          // Data register empty
#define I2C_SR1_BERR            BIT(8)          // Bus error
#define I2C_SR1_ARLO            BIT(9)          // Arbitration lost
#define I2C_SR1_AF              BIT(10)         // Acknowledge failure
#define I2C_SR1_OVR             BIT(11)         // Overrun/underrun
#define I2C_SR1_PECERR          BIT(12)         // PEC Error in reception
#define I2C_SR1_TIMEOUT         BIT(14)         // Timeout or Tlow error
#define I2C_SR1_SMBALERT        BIT(15)         // SMBus alert

/* Status register 2 bits */
#define I2C_SR2_MSL             BIT(0)          // Master/slave
#define I2C_SR2_BUSY            BIT(1)          // Bus busy
#define I2C_SR2_TRA             BIT(2)          // Transmitter/receiver
#define I2C_SR2_GENCALL         BIT(4)          // General call address
#define I2C_SR2_SMBDEFAULT      BIT(5)          // SMBus device default address
#define I2C_SR2_SMBHOST         BIT(6)          // SMBus host header
#define I2C_SR2_DUALF           BIT(7)          // Dual flag
#define I2C_SR2_PEC             0xFF00          // Packet error checking register

#ifdef __cplusplus
extern "C" {
#endif

void i2c_master_enable(i2c_dev *dev, uint32 flags);
int32 i2c_master_xfer(i2c_dev *dev, i2c_msg *msgs, uint16 num);

/*
 * Low level register twiddling functions
 */

/**
 * @brief turn on an i2c peripheral
 * @param dev i2c device
 */
static inline void i2c_peripheral_enable(i2c_dev *dev) {
    dev->regs->CR1 |= I2C_CR1_PE;
}

/**
 * @brief turn off an i2c peripheral
 * @param dev i2c device
 */
static inline void i2c_peripheral_disable(i2c_dev *dev) {
    dev->regs->CR1 &= ~I2C_CR1_PE;
}

/**
 * @brief Fill transmit register
 * @param dev i2c device
 * @param byte byte to write
 */
static inline void i2c_write(i2c_dev *dev, uint8 byte) {
    dev->regs->DR = byte;
}


/**
 * @brief Set input clock frequency, in mhz
 * @param dev i2c
 * @param freq frequency in megahertz (2-36)
 */
static inline void i2c_set_input_clk(i2c_dev *dev, uint32 freq) {
    uint32 cr2 = dev->regs->CR2;
    cr2 &= ~I2C_CR2_FREQ;
    cr2 |= freq;
    dev->regs->CR2 = freq;
}


/**
 * @brief Set i2c clock control register. See RM008
 * @param dev i2c device
 * @return
 * @sideeffect
 */
static inline void i2c_set_clk_control(i2c_dev *dev, uint32 val) {
    uint32 ccr = dev->regs->CCR;
    ccr &= ~I2C_CCR_CCR;
    ccr |= val;
    dev->regs->CCR = ccr;
}

static inline void i2c_set_fast_mode(i2c_dev *dev) {
    dev->regs->CCR |= I2C_CCR_FS;
}

static inline void i2c_set_standard_mode(i2c_dev *dev) {
    dev->regs->CCR &= ~I2C_CCR_FS;
}

/**
 * @brief Set SCL rise time
 * @param
 */
static inline void i2c_set_trise(i2c_dev *dev, uint32 trise) {
    dev->regs->TRISE = trise;
}

static inline void i2c_start_condition(i2c_dev *dev) {
    uint32 cr1;
    while ((cr1 = dev->regs->CR1) & (I2C_CR1_START |
                                     I2C_CR1_STOP  |
                                     I2C_CR1_PEC)) {
        ;
    }
    dev->regs->CR1 |= I2C_CR1_START;
}

static inline void i2c_stop_condition(i2c_dev *dev) {
    uint32 cr1;
    while ((cr1 = dev->regs->CR1) & (I2C_CR1_START |
                                     I2C_CR1_STOP  |
                                     I2C_CR1_PEC)) {
        ;
    }
    dev->regs->CR1 |= I2C_CR1_STOP;
}

static inline void i2c_send_slave_addr(i2c_dev *dev, uint32 addr, uint32 rw) {
    dev->regs->DR = (addr << 1) | rw;
}

#define I2C_IRQ_ERROR              I2C_CR2_ITERREN
#define I2C_IRQ_EVENT              I2C_CR2_ITEVTEN
#define I2C_IRQ_BUFFER             I2C_CR2_ITBUFEN
static inline void i2c_enable_irq(i2c_dev *dev, uint32 irqs) {
    dev->regs->CR2 |= irqs;
}

static inline void i2c_disable_irq(i2c_dev *dev, uint32 irqs) {
    dev->regs->CR2 &= ~irqs;
}

static inline void i2c_enable_ack(i2c_dev *dev) {
    dev->regs->CR1 |= I2C_CR1_ACK;
}

static inline void i2c_disable_ack(i2c_dev *dev) {
    dev->regs->CR1 &= ~I2C_CR1_ACK;
}

#ifdef __cplusplus
}
#endif

#endif

