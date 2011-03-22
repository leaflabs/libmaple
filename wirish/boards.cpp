#include "boards.h"

// For concision
#define ADCx ADC_INVALID

#if defined(BOARD_maple)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    {GPIOA,  3,    3, TIMER2, 4, AFIO_EXTI_PA}, /* D0/PA3 */
    {GPIOA,  2,    2, TIMER2, 3, AFIO_EXTI_PA}, /* D1/PA2 */
    {GPIOA,  0,    0, TIMER2, 1, AFIO_EXTI_PA}, /* D2/PA0 */
    {GPIOA,  1,    1, TIMER2, 2, AFIO_EXTI_PA}, /* D3/PA1 */
    {GPIOB,  5, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D4/PB5 */
    {GPIOB,  6, ADCx, TIMER4, 1, AFIO_EXTI_PB}, /* D5/PB6 */
    {GPIOA,  8, ADCx, TIMER1, 1, AFIO_EXTI_PA}, /* D6/PA8 */
    {GPIOA,  9, ADCx, TIMER1, 2, AFIO_EXTI_PA}, /* D7/PA9 */
    {GPIOA, 10, ADCx, TIMER1, 3, AFIO_EXTI_PA}, /* D8/PA10 */
    {GPIOB,  7, ADCx, TIMER4, 2, AFIO_EXTI_PB}, /* D9/PB7 */
    {GPIOA,  4,    4,   NULL, 0, AFIO_EXTI_PA}, /* D10/PA4 */
    {GPIOA,  7,    7, TIMER3, 2, AFIO_EXTI_PA}, /* D11/PA7 */
    {GPIOA,  6,    6, TIMER3, 1, AFIO_EXTI_PA}, /* D12/PA6 */
    {GPIOA,  5,    5,   NULL, 0, AFIO_EXTI_PA}, /* D13/PA5 (LED) */
    {GPIOB,  8, ADCx, TIMER4, 3, AFIO_EXTI_PB}, /* D14/PB8 */

    /* Little header */

    {GPIOC,  0,   10,   NULL, 0, AFIO_EXTI_PC}, /* D15/PC0 */
    {GPIOC,  1,   11,   NULL, 0, AFIO_EXTI_PC}, /* D16/PC1 */
    {GPIOC,  2,   12,   NULL, 0, AFIO_EXTI_PC}, /* D17/PC2 */
    {GPIOC,  3,   13,   NULL, 0, AFIO_EXTI_PC}, /* D18/PC3 */
    {GPIOC,  4,   14,   NULL, 0, AFIO_EXTI_PC}, /* D19/PC4 */
    {GPIOC,  5,   15,   NULL, 0, AFIO_EXTI_PC}, /* D20/PC5 */

    /* External header */

    {GPIOC, 13, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D21/PC13 */
    {GPIOC, 14, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D22/PC14 */
    {GPIOC, 15, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D23/PC15 */
    {GPIOB,  9, ADCx, TIMER4, 4, AFIO_EXTI_PB}, /* D24/PB9 */
    {GPIOD,  2, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D25/PD2 */
    {GPIOC, 10, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D26/PC10 */
    {GPIOB,  0,    8, TIMER3, 3, AFIO_EXTI_PB}, /* D27/PB0 */
    {GPIOB,  1,    9, TIMER3, 4, AFIO_EXTI_PB}, /* D28/PB1 */
    {GPIOB, 10, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D29/PB10 */
    {GPIOB, 11, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D30/PB11 */
    {GPIOB, 12, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D31/PB12 */
    {GPIOB, 13, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D32/PB13 */
    {GPIOB, 14, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D33/PB14 */
    {GPIOB, 15, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D34/PB15 */
    {GPIOC,  6, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D35/PC6 */
    {GPIOC,  7, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D36/PC7 */
    {GPIOC,  8, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D37/PC8 */
    {GPIOC,  9, ADCx,   NULL, 0, AFIO_EXTI_PC}  /* D38/PC9 (BUT) */
};

#elif defined(BOARD_maple_native)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    /* Top header */

    {GPIOB, 10, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D0/PB10 */
    {GPIOB,  2, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D1/PB2 */
    {GPIOB, 12, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D2/PB12 */
    {GPIOB, 13, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D3/PB13 */
    {GPIOB, 14, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D4/PB14 */
    {GPIOB, 15, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D5/PB15 */
    {GPIOC,  0,   10,   NULL, 0, AFIO_EXTI_PC}, /* D6/PC0 */
    {GPIOC,  1,   11,   NULL, 0, AFIO_EXTI_PC}, /* D7/PC1 */
    {GPIOC,  2,   12,   NULL, 0, AFIO_EXTI_PC}, /* D8/PC2 */
    {GPIOC,  3,   13,   NULL, 0, AFIO_EXTI_PC}, /* D9/PC3 */
    {GPIOC,  4,   14,   NULL, 0, AFIO_EXTI_PC}, /* D10/PC4 */
    {GPIOC,  5,   15,   NULL, 0, AFIO_EXTI_PC}, /* D11/PC5 */
    {GPIOC,  6, ADCx, TIMER8, 1, AFIO_EXTI_PC}, /* D12/PC6 */
    {GPIOC,  7, ADCx, TIMER8, 2, AFIO_EXTI_PC}, /* D13/PC7 */
    {GPIOC,  8, ADCx, TIMER8, 3, AFIO_EXTI_PC}, /* D14/PC8 */
    {GPIOC,  9, ADCx, TIMER8, 4, AFIO_EXTI_PC}, /* D15/PC9 */
    {GPIOC, 10, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D16/PC10 */
    {GPIOC, 11, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D17/PC11 */
    {GPIOC, 12, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D18/PC12 */
    {GPIOC, 13, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D19/PC13 */
    {GPIOC, 14, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D20/PC14 */
    {GPIOC, 15, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D21/PC15 */
    {GPIOA,  8, ADCx, TIMER1, 1, AFIO_EXTI_PA}, /* D22/PA8 */
    {GPIOA,  9, ADCx, TIMER1, 2, AFIO_EXTI_PA}, /* D23/PA9 */
    {GPIOA, 10, ADCx, TIMER1, 3, AFIO_EXTI_PA}, /* D24/PA10 */
    {GPIOB,  9, ADCx, TIMER4, 4, AFIO_EXTI_PB}, /* D25/PB9 */

    /* Bottom header */
    /* FIXME (?) What about D48--D50 also being TIMER2_CH[234]? */

    {GPIOD,  2, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D26/PD2 */
    {GPIOD,  3, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D27/PD3 */
    {GPIOD,  6, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D28/PD6 */
    {GPIOG, 11, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D29/PG11 */
    {GPIOG, 12, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D30/PG12 */
    {GPIOG, 13, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D31/PG13 */
    {GPIOG, 14, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D32/PG14 */
    {GPIOG,  8, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D33/PG8 */
    {GPIOG,  7, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D34/PG7 */
    {GPIOG,  6, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D35/PG6 */
    {GPIOB,  5, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D36/PB5 */
    {GPIOB,  6, ADCx, TIMER4, 1, AFIO_EXTI_PB}, /* D37/PB6 */
    {GPIOB,  7, ADCx, TIMER4, 2, AFIO_EXTI_PB}, /* D38/PB7 */
    {GPIOF,  6,    4,   NULL, 0, AFIO_EXTI_PF}, /* D39/PF6 */
    {GPIOF,  7,    5,   NULL, 0, AFIO_EXTI_PF}, /* D40/PF7 */
    {GPIOF,  8,    6,   NULL, 0, AFIO_EXTI_PF}, /* D41/PF8 */
    {GPIOF,  9,    7,   NULL, 0, AFIO_EXTI_PF}, /* D42/PF9 */
    {GPIOF, 10,    8,   NULL, 0, AFIO_EXTI_PF}, /* D43/PF10 */
    {GPIOF, 11, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D44/PF11 */
    {GPIOB,  1,    9, TIMER3, 4, AFIO_EXTI_PB}, /* D45/PB1 */
    {GPIOB,  0,    8, TIMER3, 3, AFIO_EXTI_PB}, /* D46/PB0 */
    {GPIOA,  0,    0, TIMER5, 1, AFIO_EXTI_PA}, /* D47/PA0 */
    {GPIOA,  1,    1, TIMER5, 2, AFIO_EXTI_PA}, /* D48/PA1 */
    {GPIOA,  2,    2, TIMER5, 3, AFIO_EXTI_PA}, /* D49/PA2 */
    {GPIOA,  3,    3, TIMER5, 4, AFIO_EXTI_PA}, /* D50/PA3 */
    {GPIOA,  4,    4,   NULL, 0, AFIO_EXTI_PA}, /* D51/PA4 */
    {GPIOA,  5,    5,   NULL, 0, AFIO_EXTI_PA}, /* D52/PA5 */
    {GPIOA,  6,    6, TIMER3, 1, AFIO_EXTI_PA}, /* D53/PA6 */
    {GPIOA,  7,    7, TIMER3, 2, AFIO_EXTI_PA}, /* D54/PA7 */

    /* Right (triple) header */

    {GPIOF,  0, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D55/PF0 */
    {GPIOD, 11, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D56/PD11 */
    {GPIOD, 14, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D57/PD14 */
    {GPIOF,  1, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D58/PF1 */
    {GPIOD, 12, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D59/PD12 */
    {GPIOD, 15, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D60/PD15 */
    {GPIOF,  2, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D61/PF2 */
    {GPIOD, 13, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D62/PD13 */
    {GPIOD,  0, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D63/PD0 */
    {GPIOF,  3, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D64/PF3 */
    {GPIOE,  3, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D65/PE3 */
    {GPIOD,  1, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D66/PD1 */
    {GPIOF,  4, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D67/PF4 */
    {GPIOE,  4, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D68/PE4 */
    {GPIOE,  7, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D69/PE7 */
    {GPIOF,  5, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D70/PF5 */
    {GPIOE,  5, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D71/PE5 */
    {GPIOE,  8, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D72/PE8 */
    {GPIOF, 12, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D73/PF12 */
    {GPIOE,  6, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D74/PE6 */
    {GPIOE,  9, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D75/PE9 */
    {GPIOF, 13, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D76/PF13 */
    {GPIOE, 10, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D77/PE10 */
    {GPIOF, 14, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D78/PF14 */
    {GPIOG,  9, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D79/PG9 */
    {GPIOE, 11, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D80/PE11 */
    {GPIOF, 15, ADCx,   NULL, 0, AFIO_EXTI_PF}, /* D81/PF15 */
    {GPIOG, 10, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D82/PG10 */
    {GPIOE, 12, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D83/PE12 */
    {GPIOG,  0, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D84/PG0 */
    {GPIOD,  5, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D85/PD5 */
    {GPIOE, 13, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D86/PE13 */
    {GPIOG,  1, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D87/PG1 */
    {GPIOD,  4, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D88/PD4 */
    {GPIOE, 14, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D89/PE14 */
    {GPIOG,  2, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D90/PG2 */
    {GPIOE,  1, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D91/PE1 */
    {GPIOE, 15, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D92/PE15 */
    {GPIOG,  3, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D93/PG3 */
    {GPIOE,  0, ADCx,   NULL, 0, AFIO_EXTI_PE}, /* D94/PE0 */
    {GPIOD,  8, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D95/PD8 */
    {GPIOG,  4, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D96/PG4 */
    {GPIOD,  9, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D97/PD9 */
    {GPIOG,  5, ADCx,   NULL, 0, AFIO_EXTI_PG}, /* D98/PG5 */
    {GPIOD, 10, ADCx,   NULL, 0, AFIO_EXTI_PD}  /* D99/PD10 */
};

#elif defined(BOARD_maple_mini)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    /* Top header */

    {GPIOB, 11, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D0/PB11 */
    {GPIOB, 10, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D1/PB10 */
    {GPIOB,  2, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D2/PB2 */
    {GPIOB,  0,    8, TIMER3, 3, AFIO_EXTI_PB}, /* D3/PB0 */
    {GPIOA,  7,    7, TIMER3, 2, AFIO_EXTI_PA}, /* D4/PA7 */
    {GPIOA,  6,    6, TIMER3, 1, AFIO_EXTI_PA}, /* D5/PA6 */
    {GPIOA,  5,    5,   NULL, 0, AFIO_EXTI_PA}, /* D6/PA5 */
    {GPIOA,  4,    4,   NULL, 0, AFIO_EXTI_PA}, /* D7/PA4 */
    {GPIOA,  3,    3, TIMER2, 4, AFIO_EXTI_PA}, /* D8/PA3 */
    {GPIOA,  2,    2, TIMER2, 3, AFIO_EXTI_PA}, /* D9/PA2 */
    {GPIOA,  1,    1, TIMER2, 2, AFIO_EXTI_PA}, /* D10/PA1 */
    {GPIOA,  0,    0, TIMER2, 1, AFIO_EXTI_PA}, /* D11/PA0 */
    {GPIOC, 15, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D12/PC15 */
    {GPIOC, 14, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D13/PC14 */
    {GPIOC, 13, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D14/PC13 */

    /* Bottom header */

    {GPIOB,  7, ADCx, TIMER4, 2, AFIO_EXTI_PB}, /* D15/PB7 */
    {GPIOB,  6, ADCx, TIMER4, 1, AFIO_EXTI_PB}, /* D16/PB6 */
    {GPIOB,  5, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D17/PB5 */
    {GPIOB,  4, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D18/PB4 */
    {GPIOB,  3, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D19/PB3 */
    {GPIOA, 15, ADCx,   NULL, 0, AFIO_EXTI_PA}, /* D20/PA15 */
    {GPIOA, 14, ADCx,   NULL, 0, AFIO_EXTI_PA}, /* D21/PA14 */
    {GPIOA, 13, ADCx,   NULL, 0, AFIO_EXTI_PA}, /* D22/PA13 */
    {GPIOA, 12, ADCx,   NULL, 0, AFIO_EXTI_PA}, /* D23/PA12 */
    {GPIOA, 11, ADCx, TIMER1, 4, AFIO_EXTI_PA}, /* D24/PA11 */
    {GPIOA, 10, ADCx, TIMER1, 3, AFIO_EXTI_PA}, /* D25/PA10 */
    {GPIOA,  9, ADCx, TIMER2, 2, AFIO_EXTI_PA}, /* D26/PA9 */
    {GPIOA,  8, ADCx, TIMER1, 1, AFIO_EXTI_PA}, /* D27/PA8 */
    {GPIOB, 15, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D28/PB15 */
    {GPIOB, 14, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D29/PB14 */
    {GPIOB, 13, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D30/PB13 */
    {GPIOB, 12, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D31/PB12 */
    {GPIOB,  8, ADCx, TIMER4, 3, AFIO_EXTI_PB}, /* D32/PB8 */
    {GPIOB,  1,    9, TIMER3, 4, AFIO_EXTI_PB}, /* D33/PB1 */
};

#elif defined(BOARD_maple_RET6)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    {GPIOA,  3,    3, TIMER2, 4, AFIO_EXTI_PA}, /* D0/PA3 */
    {GPIOA,  2,    2, TIMER2, 3, AFIO_EXTI_PA}, /* D1/PA2 */
    {GPIOA,  0,    0, TIMER2, 1, AFIO_EXTI_PA}, /* D2/PA0 */
    {GPIOA,  1,    1, TIMER2, 2, AFIO_EXTI_PA}, /* D3/PA1 */
    {GPIOB,  5, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D4/PB5 */
    {GPIOB,  6, ADCx, TIMER4, 1, AFIO_EXTI_PB}, /* D5/PB6 */
    {GPIOA,  8, ADCx, TIMER1, 1, AFIO_EXTI_PA}, /* D6/PA8 */
    {GPIOA,  9, ADCx, TIMER1, 2, AFIO_EXTI_PA}, /* D7/PA9 */
    {GPIOA, 10, ADCx, TIMER1, 3, AFIO_EXTI_PA}, /* D8/PA10 */
    {GPIOB,  7, ADCx, TIMER4, 2, AFIO_EXTI_PB}, /* D9/PB7 */
    {GPIOA,  4,    4,   NULL, 0, AFIO_EXTI_PA}, /* D10/PA4 */
    {GPIOA,  7,    7, TIMER3, 2, AFIO_EXTI_PA}, /* D11/PA7 */
    {GPIOA,  6,    6, TIMER3, 1, AFIO_EXTI_PA}, /* D12/PA6 */
    {GPIOA,  5,    5,   NULL, 0, AFIO_EXTI_PA}, /* D13/PA5 (LED) */
    {GPIOB,  8, ADCx, TIMER4, 3, AFIO_EXTI_PB}, /* D14/PB8 */

    /* Little header */

    {GPIOC,  0,   10,   NULL, 0, AFIO_EXTI_PC}, /* D15/PC0 */
    {GPIOC,  1,   11,   NULL, 0, AFIO_EXTI_PC}, /* D16/PC1 */
    {GPIOC,  2,   12,   NULL, 0, AFIO_EXTI_PC}, /* D17/PC2 */
    {GPIOC,  3,   13,   NULL, 0, AFIO_EXTI_PC}, /* D18/PC3 */
    {GPIOC,  4,   14,   NULL, 0, AFIO_EXTI_PC}, /* D19/PC4 */
    {GPIOC,  5,   15,   NULL, 0, AFIO_EXTI_PC}, /* D20/PC5 */

    /* External header */

    {GPIOC, 13, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D21/PC13 */
    {GPIOC, 14, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D22/PC14 */
    {GPIOC, 15, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D23/PC15 */
    {GPIOB,  9, ADCx, TIMER4, 4, AFIO_EXTI_PB}, /* D24/PB9 */
    {GPIOD,  2, ADCx,   NULL, 0, AFIO_EXTI_PD}, /* D25/PD2 */
    {GPIOC, 10, ADCx,   NULL, 0, AFIO_EXTI_PC}, /* D26/PC10 */
    {GPIOB,  0,    8, TIMER3, 3, AFIO_EXTI_PB}, /* D27/PB0 */
    {GPIOB,  1,    9, TIMER3, 4, AFIO_EXTI_PB}, /* D28/PB1 */
    {GPIOB, 10, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D29/PB10 */
    {GPIOB, 11, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D30/PB11 */
    {GPIOB, 12, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D31/PB12 */
    {GPIOB, 13, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D32/PB13 */
    {GPIOB, 14, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D33/PB14 */
    {GPIOB, 15, ADCx,   NULL, 0, AFIO_EXTI_PB}, /* D34/PB15 */
    {GPIOC,  6, ADCx, TIMER8, 1, AFIO_EXTI_PC}, /* D35/PC6 */
    {GPIOC,  7, ADCx, TIMER8, 2, AFIO_EXTI_PC}, /* D36/PC7 */
    {GPIOC,  8, ADCx, TIMER8, 3, AFIO_EXTI_PC}, /* D37/PC8 */
    {GPIOC,  9, ADCx, TIMER8, 4, AFIO_EXTI_PC}  /* D38/PC9 (BUT) */
};

#else

#error "Board type has not been selected correctly."

#endif
