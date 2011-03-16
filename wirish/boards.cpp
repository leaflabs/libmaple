#include "boards.h"

// think of the poor column numbers
#define ADCx ADC_INVALID
#define TIMERx TIMER_INVALID

#if defined(BOARD_maple)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    /* D0/PA3 */
    {GPIOA,  3,    3, TIMER2_CH4_CCR, TIMER2,      4, AFIO_EXTI_PA},
    /* D1/PA2 */
    {GPIOA,  2,    2, TIMER2_CH3_CCR, TIMER2,      3, AFIO_EXTI_PA},
    /* D2/PA0 */
    {GPIOA,  0,    0, TIMER2_CH1_CCR, TIMER2,      1, AFIO_EXTI_PA},
    /* D3/PA1 */
    {GPIOA,  1,    1, TIMER2_CH2_CCR, TIMER2,      2, AFIO_EXTI_PA},
    /* D4/PB5 */
    {GPIOB,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D5/PB6 */
    {GPIOB,  6, ADCx, TIMER4_CH1_CCR, TIMER4,      1, AFIO_EXTI_PB},
    /* D6/PA8 */
    {GPIOA,  8, ADCx, TIMER1_CH1_CCR, TIMER1,      1, AFIO_EXTI_PA},
    /* D7/PA9 */
    {GPIOA,  9, ADCx, TIMER1_CH2_CCR, TIMER1,      2, AFIO_EXTI_PA},
    /* D8/PA10 */
    {GPIOA, 10, ADCx, TIMER1_CH3_CCR, TIMER1,      3, AFIO_EXTI_PA},
    /* D9/PB7 */
    {GPIOB,  7, ADCx, TIMER4_CH2_CCR, TIMER4,      2, AFIO_EXTI_PB},
    /* D10/PA4 */
    {GPIOA,  4,    4,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D11/PA7 */
    {GPIOA,  7,    7, TIMER3_CH2_CCR, TIMER3,      2, AFIO_EXTI_PA},
    /* D12/PA6 */
    {GPIOA,  6,    6, TIMER3_CH1_CCR, TIMER3,      1, AFIO_EXTI_PA},
    /* D13/PA5 */
    {GPIOA,  5,    5,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D14/PB8 */
    {GPIOB,  8, ADCx, TIMER4_CH3_CCR, TIMER4,      3, AFIO_EXTI_PB},

    /* Little header */

    /* D15/PC0 */
    {GPIOC,  0,   10,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D16/PC1 */
    {GPIOC,  1,   11,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D17/PC2 */
    {GPIOC,  2,   12,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D18/PC3 */
    {GPIOC,  3,   13,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D19/PC4 */
    {GPIOC,  4,   14,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D20/PC5 */
    {GPIOC,  5,   15,              0, TIMERx, TIMERx, AFIO_EXTI_PC},

    /* External header */

    /* D21/PC13 */
    {GPIOC, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D22/PC14 */
    {GPIOC, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D23/PC15 */
    {GPIOC, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D24/PB9 */
    {GPIOB,  9, ADCx, TIMER4_CH4_CCR, TIMER4,      4, AFIO_EXTI_PB},
    /* D25/PD2 */
    {GPIOD,  2, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D26/PC10 */
    {GPIOC, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D27/PB0 */
    {GPIOB,  0,    8, TIMER3_CH3_CCR, TIMER3,      3, AFIO_EXTI_PB},
    /* D28/PB1 */
    {GPIOB,  1,    9, TIMER3_CH4_CCR, TIMER3,      4, AFIO_EXTI_PB},
    /* D29/PB10 */
    {GPIOB, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D30/PB11 */
    {GPIOB, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D31/PB12 */
    {GPIOB, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D32/PB13 */
    {GPIOB, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D33/PB14 */
    {GPIOB, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D34/PB15 */
    {GPIOB, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D35/PC6 */
    {GPIOC,  6, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D36/PC7 */
    {GPIOC,  7, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D37/PC8 */
    {GPIOC,  8, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D38/PC9 (BUT) */
    {GPIOC,  9, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC}
};

#elif defined(BOARD_maple_native)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    /* Top header */

    /* D0/PB10 */
    {GPIOB, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D1/PB2 */
    {GPIOB,  2, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D2/PB12 */
    {GPIOB, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D3/PB13 */
    {GPIOB, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D4/PB14 */
    {GPIOB, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D5/PB15 */
    {GPIOB, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D6/PC0 */
    {GPIOC,  0,   10,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D7/PC1 */
    {GPIOC,  1,   11,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D8/PC2 */
    {GPIOC,  2,   12,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D9/PC3 */
    {GPIOC,  3,   13,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D10/PC4 */
    {GPIOC,  4,   14,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D11/PC5 */
    {GPIOC,  5,   15,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D12/PC6 */
    {GPIOC,  6, ADCx, TIMER8_CH1_CCR, TIMER8,      1, AFIO_EXTI_PC},
    /* D13/PC7 */
    {GPIOC,  7, ADCx, TIMER8_CH2_CCR, TIMER8,      2, AFIO_EXTI_PC},
    /* D14/PC8 */
    {GPIOC,  8, ADCx, TIMER8_CH3_CCR, TIMER8,      3, AFIO_EXTI_PC},
    /* D15/PC9 */
    {GPIOC,  9, ADCx, TIMER8_CH4_CCR, TIMER8,      4, AFIO_EXTI_PC},
    /* D16/PC10 */
    {GPIOC, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D17/PC11 */
    {GPIOC, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D18/PC12 */
    {GPIOC, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D19/PC13 */
    {GPIOC, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D20/PC14 */
    {GPIOC, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D21/PC15 */
    {GPIOC, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D22/PA8 */
    {GPIOA,  8, ADCx, TIMER1_CH1_CCR, TIMER1,      1, AFIO_EXTI_PA},
    /* D23/PA9 */
    {GPIOA,  9, ADCx, TIMER1_CH2_CCR, TIMER1,      2, AFIO_EXTI_PA},
    /* D24/PA10 */
    {GPIOA, 10, ADCx, TIMER1_CH3_CCR, TIMER1,      3, AFIO_EXTI_PA},
    /* D25/PB9 */
    {GPIOB,  9, ADCx, TIMER4_CH4_CCR, TIMER4,      4, AFIO_EXTI_PB},

    /* Bottom header */

    /* D26/PD2 */
    {GPIOD,  2, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D27/PD3 */
    {GPIOD,  3, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D28/PD6 */
    {GPIOD,  6, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D29/PG11 */
    {GPIOG, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D30/PG12 */
    {GPIOG, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D31/PG13 */
    {GPIOG, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D32/PG14 */
    {GPIOG, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D33/PG8 */
    {GPIOG,  8, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D34/PG7 */
    {GPIOG,  7, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D35/PG6 */
    {GPIOG,  6, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D36/PB5 */
    {GPIOB,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D37/PB6 */
    {GPIOB,  6, ADCx, TIMER4_CH1_CCR, TIMER4,      1, AFIO_EXTI_PB},
    /* D38/PB7 */
    {GPIOB,  7, ADCx, TIMER4_CH2_CCR, TIMER4,      2, AFIO_EXTI_PB},
    /* D39/PF6 */
    {GPIOF,  6,    4,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D40/PF7 */
    {GPIOF,  7,    5,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D41/PF8 */
    {GPIOF,  8,    6,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D42/PF9 */
    {GPIOF,  9,    7,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D43/PF10 */
    {GPIOF, 10,    8,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D44/PF11 */
    {GPIOF, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D45/PB1 */
    {GPIOB,  1,    9, TIMER3_CH4_CCR, TIMER3,      4, AFIO_EXTI_PB},
    /* D46/PB0 */
    {GPIOB,  0,    8, TIMER3_CH3_CCR, TIMER3,      3, AFIO_EXTI_PB},
    /* D47/PA0 */
    {GPIOA,  0,    0, TIMER5_CH1_CCR, TIMER5,      1, AFIO_EXTI_PA},
    /* D48/PA1 */ /* FIXME (?)
       What about D48--D50 also being TIMER2_CH[234]? */
    {GPIOA,  1,    1, TIMER5_CH2_CCR, TIMER5,      2, AFIO_EXTI_PA},
    /* D49/PA2 */
    {GPIOA,  2,    2, TIMER5_CH3_CCR, TIMER5,      3, AFIO_EXTI_PA},
    /* D50/PA3 */
    {GPIOA,  3,    3, TIMER5_CH4_CCR, TIMER5,      4, AFIO_EXTI_PA},
    /* D51/PA4 */
    {GPIOA,  4,    4,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D52/PA5 */
    {GPIOA,  5,    5,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D53/PA6 */
    {GPIOA,  6,    6, TIMER3_CH1_CCR, TIMER3,      1, AFIO_EXTI_PA},
    /* D54/PA7 */
    {GPIOA,  7,    7, TIMER3_CH2_CCR, TIMER3,      2, AFIO_EXTI_PA},

    /* Right (triple) header */

    /* D55/PF0 */
    {GPIOF,  0, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D56/PD11 */
    {GPIOD, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D57/PD14 */
    {GPIOD, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D58/PF1 */
    {GPIOF,  1, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D59/PD12 */
    {GPIOD, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D60/PD15 */
    {GPIOD, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D61/PF2 */
    {GPIOF,  2, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D62/PD13 */
    {GPIOD, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D63/PD0 */
    {GPIOD,  0, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D64/PF3 */
    {GPIOF,  3, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D65/PE3 */
    {GPIOE,  3, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D66/PD1 */
    {GPIOD,  1, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D67/PF4 */
    {GPIOF,  4, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D68/PE4 */
    {GPIOE,  4, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D69/PE7 */
    {GPIOE,  7, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D70/PF5 */
    {GPIOF,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D71/PE5 */
    {GPIOE,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D72/PE8 */
    {GPIOE,  8, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D73/PF12 */
    {GPIOF, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D74/PE6 */
    {GPIOE,  6, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D75/PE9 */
    {GPIOE,  9, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D76/PF13 */
    {GPIOF, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D77/PE10 */
    {GPIOE, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D78/PF14 */
    {GPIOF, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D79/PG9 */
    {GPIOG,  9, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D80/PE11 */
    {GPIOE, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D81/PF15 */
    {GPIOF, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PF},
    /* D82/PG10 */
    {GPIOG, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D83/PE12 */
    {GPIOE, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D84/PG0 */
    {GPIOG,  0, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D85/PD5 */
    {GPIOD,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D86/PE13 */
    {GPIOE, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D87/PG1 */
    {GPIOG,  1, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D88/PD4 */
    {GPIOD,  4, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D89/PE14 */
    {GPIOE, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D90/PG2 */
    {GPIOG,  2, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D91/PE1 */
    {GPIOE,  1, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D92/PE15 */
    {GPIOE, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D93/PG3 */
    {GPIOG,  3, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D94/PE0 */
    {GPIOE,  0, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PE},
    /* D95/PD8 */
    {GPIOD,  8, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D96/PG4 */
    {GPIOG,  4, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D97/PD9 */
    {GPIOD,  9, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D98/PG5 */
    {GPIOG,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PG},
    /* D99/PD10 */
    {GPIOD, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD}
};

#elif defined(BOARD_maple_mini)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    /* D0/PB11 */
    {GPIOB, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D1/PB10 */
    {GPIOB, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D2/PB2 */
    {GPIOB,  2, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D3/PB0 */
    {GPIOB,  0,    8, TIMER3_CH3_CCR, TIMER3,      3, AFIO_EXTI_PB},
    /* D4/PA7 */
    {GPIOA,  7,    7, TIMER3_CH2_CCR, TIMER3,      2, AFIO_EXTI_PA},
    /* D5/PA6 */
    {GPIOA,  6,    6, TIMER3_CH1_CCR, TIMER3,      1, AFIO_EXTI_PA},
    /* D6/PA5 */
    {GPIOA,  5,    5,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D7/PA4 */
    {GPIOA,  4,    4,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D8/PA3 */
    {GPIOA,  3,    3, TIMER2_CH4_CCR, TIMER2,      4, AFIO_EXTI_PA},
    /* D9/PA2 */
    {GPIOA,  2,    2, TIMER2_CH3_CCR, TIMER2,      3, AFIO_EXTI_PA},
    /* D10/PA1 */
    {GPIOA,  1,    1, TIMER2_CH2_CCR, TIMER2,      2, AFIO_EXTI_PA},
    /* D11/PA0 */
    {GPIOA,  0,    0, TIMER2_CH1_CCR, TIMER2,      1, AFIO_EXTI_PA},
    /* D12/PC15 */
    {GPIOC, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D13/PC14 */
    {GPIOC, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D14/PC13 */
    {GPIOC, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D15/PB7 */
    {GPIOB,  7, ADCx, TIMER4_CH2_CCR, TIMER4,      2, AFIO_EXTI_PB},
    /* D16/PB6 */
    {GPIOB,  6, ADCx, TIMER4_CH1_CCR, TIMER4,      1, AFIO_EXTI_PB},
    /* D17/PB5 */
    {GPIOB,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D18/PB4 */
    {GPIOB,  4, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D19/PB3 */
    {GPIOB,  3, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D20/PA15 */
    {GPIOA, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D21/PA14 */
    {GPIOA, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D22/PA13 */
    {GPIOA, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D23/PA12 */
    {GPIOA, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D24/PA11 */
    {GPIOA, 11, ADCx, TIMER1_CH4_CCR, TIMER1,      4, AFIO_EXTI_PA},
    /* D25/PA10 */
    {GPIOA, 10, ADCx, TIMER1_CH3_CCR, TIMER1,      3, AFIO_EXTI_PA},
    /* D26/PA9 */
    {GPIOA,  9, ADCx, TIMER1_CH2_CCR, TIMER2,      2, AFIO_EXTI_PA},
    /* D27/PA8 */
    {GPIOA,  8, ADCx, TIMER1_CH1_CCR, TIMER1,      1, AFIO_EXTI_PA},
    /* D28/PB15 */
    {GPIOB, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D29/PB14 */
    {GPIOB, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D30/PB13 */
    {GPIOB, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D31/PB12 */
    {GPIOB, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D32/PB8 */
    {GPIOB,  8, ADCx, TIMER4_CH3_CCR, TIMER4,      3, AFIO_EXTI_PB},
    /* D33/PB1 */
    {GPIOB,  1,    9, TIMER3_CH4_CCR, TIMER3,      4, AFIO_EXTI_PB},
};

#elif defined(BOARD_maple_RET6)

PinMapping PIN_MAP[NR_GPIO_PINS] = {
    /* D0/PA3 */
    {GPIOA,  3,    3, TIMER2_CH4_CCR, TIMER2,      4, AFIO_EXTI_PA},
    /* D1/PA2 */
    {GPIOA,  2,    2, TIMER2_CH3_CCR, TIMER2,      3, AFIO_EXTI_PA},
    /* D2/PA0 */
    {GPIOA,  0,    0, TIMER2_CH1_CCR, TIMER2,      1, AFIO_EXTI_PA},
    /* D3/PA1 */
    {GPIOA,  1,    1, TIMER2_CH2_CCR, TIMER2,      2, AFIO_EXTI_PA},
    /* D4/PB5 */
    {GPIOB,  5, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D5/PB6 */
    {GPIOB,  6, ADCx, TIMER4_CH1_CCR, TIMER4,      1, AFIO_EXTI_PB},
    /* D6/PA8 */
    {GPIOA,  8, ADCx, TIMER1_CH1_CCR, TIMER1,      1, AFIO_EXTI_PA},
    /* D7/PA9 */
    {GPIOA,  9, ADCx, TIMER1_CH2_CCR, TIMER1,      2, AFIO_EXTI_PA},
    /* D8/PA10 */
    {GPIOA, 10, ADCx, TIMER1_CH3_CCR, TIMER1,      3, AFIO_EXTI_PA},
    /* D9/PB7 */
    {GPIOB,  7, ADCx, TIMER4_CH2_CCR, TIMER4,      2, AFIO_EXTI_PB},
    /* D10/PA4 */
    {GPIOA,  4,    4,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D11/PA7 */
    {GPIOA,  7,    7, TIMER3_CH2_CCR, TIMER3,      2, AFIO_EXTI_PA},
    /* D12/PA6 */
    {GPIOA,  6,    6, TIMER3_CH1_CCR, TIMER3,      1, AFIO_EXTI_PA},
    /* D13/PA5 */
    {GPIOA,  5,    5,              0, TIMERx, TIMERx, AFIO_EXTI_PA},
    /* D14/PB8 */
    {GPIOB,  8, ADCx, TIMER4_CH3_CCR, TIMER4,      3, AFIO_EXTI_PB},

    /* Little header */

    /* D15/PC0 */
    {GPIOC,  0,   10,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D16/PC1 */
    {GPIOC,  1,   11,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D17/PC2 */
    {GPIOC,  2,   12,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D18/PC3 */
    {GPIOC,  3,   13,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D19/PC4 */
    {GPIOC,  4,   14,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D20/PC5 */
    {GPIOC,  5,   15,              0, TIMERx, TIMERx, AFIO_EXTI_PC},

    /* External header */

    /* D21/PC13 */
    {GPIOC, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D22/PC14 */
    {GPIOC, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D23/PC15 */
    {GPIOC, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D24/PB9 */
    {GPIOB,  9, ADCx, TIMER4_CH4_CCR, TIMER4,      4, AFIO_EXTI_PB},
    /* D25/PD2 */
    {GPIOD,  2, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PD},
    /* D26/PC10 */
    {GPIOC, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PC},
    /* D27/PB0 */
    {GPIOB,  0,    8, TIMER3_CH3_CCR, TIMER3,      3, AFIO_EXTI_PB},
    /* D28/PB1 */
    {GPIOB,  1,    9, TIMER3_CH4_CCR, TIMER3,      4, AFIO_EXTI_PB},
    /* D29/PB10 */
    {GPIOB, 10, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D30/PB11 */
    {GPIOB, 11, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D31/PB12 */
    {GPIOB, 12, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D32/PB13 */
    {GPIOB, 13, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D33/PB14 */
    {GPIOB, 14, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D34/PB15 */
    {GPIOB, 15, ADCx,              0, TIMERx, TIMERx, AFIO_EXTI_PB},
    /* D35/PC6 */
    {GPIOC,  6, ADCx, TIMER8_CH1_CCR, TIMER8,      1, AFIO_EXTI_PC},
    /* D36/PC7 */
    {GPIOC,  7, ADCx, TIMER8_CH1_CCR, TIMER8,      2, AFIO_EXTI_PC},
    /* D37/PC8 */
    {GPIOC,  8, ADCx, TIMER8_CH1_CCR, TIMER8,      3, AFIO_EXTI_PC},
    /* D38/PC9 (BUT) */
    {GPIOC,  9, ADCx, TIMER8_CH1_CCR, TIMER8,      4, AFIO_EXTI_PC}
};

#else

#error "Board type has not been selected correctly."

#endif
