//#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "gpio.h"
#include "Serial.h"
#include "wiring.h"

int SendChar (int ch)  {
    /* Write character to Serial Port     */
//    USART_SendData(USART2, (unsigned char) ch);
//    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
//        ;
//
//    //    while (!(USART2->SR & USART_FLAG_TXE));
//    return (ch);
}

void uart_send(const char* str) {
    while (*str != '\0') {
        SendChar(*str);
        str++;
    }
}


Serial::Serial() {
}

void Serial::write(uint8_t c) {
    SendChar(c);
}

void Serial::begin(uint32_t baud) {
 //   USART_InitTypeDef USART_InitStructure;

    /* Turn on the clock  */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

#if 0
    /* Configure USART2 Tx as alternate function push-pull */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART2 Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

    pinMode(1, GPIO_MODE_AF_OUTPUT_PP);
    pinMode(0, GPIO_MODE_INPUT_FLOATING);

    /* Enable USART2  */
//    USART_InitStructure.USART_BaudRate = baud;
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;
//    USART_InitStructure.USART_Parity = USART_Parity_No ;
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//    USART_Init(USART2, &USART_InitStructure);
//    USART_Cmd(USART2, ENABLE);
}

Serial Serial1;
