#include "stm32f10x_rcc.h"
#include "usart.h"

static inline void usart_putc(usart_port *port, uint8_t ch) {
    port->DR = ch;

    /* Wait till TXE = 1 */
    while ((port->SR & USART_TXE) == 0)
        ;
}

int32_t usart_init(uint8_t usart_num) {
    ASSERT((usart_num < NR_USARTS) && (usart_num > 0));
    usart_port *port;
    uint32_t clk_speed;

    switch (usart_num) {
    case 1:
        port = USART1_BASE;
        clk_speed = USART1_CLK;
        break;
    case 2:
        port = USART2_BASE;
        clk_speed = USART2_CLK;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        break;
    case 3:
        port = USART3_BASE;
        break;
    default:
        /* should never get here  */
        ASSERT(0);
    }
    uint32_t baud = 9600;
    uint32_t usartdiv = clk_speed / baud;

    /* Set baud rate  */
    port->BRR = BIT_MASK_SHIFT(B9600_MANTISSA, 4) | B9600_FRACTION;

    /* Enable the USART and set 8n1 (M bit clear) enable transmitter*/
    port->CR1 = USART_UE | USART_TE;

    return 0;
}
