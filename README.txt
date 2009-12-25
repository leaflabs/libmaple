/* Temporary file for notes to myself. */
/* Known Errors:
 * Schematic: PB9 is mislabeled as TIM3_CH4: should be TIM4_CH4
 * Silkscreen: D2  is incorrectly marked as not having PWM capability. It does.
 * Silkscreen: D10 is incorrectly marked as having PWM capability. It does not.
 *
 * D15 is mapped to pin number 38. This is to retain compatiblity with the
 * Arduino API, where digitalWrite() on pins 14-19 map to analog A0-A5
 *
 *
 * TODO:
 * Using OSC32_IN/OSC32_OUT pins as GPIO ports PC14/PC15 152/995
 * Runtime check for AF collisions on pins (eg serial and pwm).
 * */

/* 51 GPIOs in general
 *
 * Reserved Pins:         Function
 * PA11                   USBDM
 * PA12                   USBDP
 * PA13                   JTMS-SWDAT
 * PA14                   JTCK-SWCLK
 * PA15                   JTDI
 * PB2                    BOOT1
 * PB3                    JTDO
 * PB4                    JTRST
 * PC11                   USB_P
 * PC12                   DISC
 * PD0                    OSC_IN
 * PD1                    OSC_OUT
 *
 * */
/* Pin           STM32 PIN   ADC     Timer          I2C        UART        SPI          F/T
 * D0/A6         PA3         ADC3    TIM2_CH4       -          USART2_RX   -            -
 * D1/A7         PA2         ADC2    TIM2_CH3       -          USART2_TX   -            -
 * D2/A8         PA0         ADC0    TIM2_CH1_ETR   -          USART2_CTS  -            -
 * D3/A9         PA1         ADC1    TIM2_CH2       -          USART2_RTS  -            -
 * D4            PB5         -       -              ISC1_SMBA  -           -            -
 * D5            PB6         -       TIM4_CH1       I2C1_SCL   -           -            Y
 * D6            PA8         -       TIM1_CH1       -          USART1_CK   -            Y
 * D7            PA9         -       TIM1_CH2       -          USART1_TX   -            Y
 * D8            PA10        -       TIM1_CH3       -          USART1_RX   -            Y
 * D9            PB7         -       TIM4_CH2       I2C1_SDA   -           -            Y
 * D10/A10       PA4         ADC4    -              -          USART2_CK   SPI1_NSS     -
 * D11/A11       PA7         ADC7    TIM3_CH2       -          -           SPI1_MOSI    -
 * D12/A12       PA6         ADC6    TIM3_CH1       -          -           SPI1_MISO    -
 * D13/A13       PA5         ADC5    -              -          -           SPI1_SCK     -
 * --------------------------------------------------------------------------------------
 * D14/A0        PC0         ADC10   -              -          -           -            -
 * D15/A1        PC1         ADC11   -              -          -           -            -
 * D16/A2        PC2         ADC12   -              -          -           -            -
 * D17/A3        PC3         ADC13   -              -          -           -            -
 * D18/A4        PC4         ADC14   -              -          -           -            -
 * D19/A5        PC5         ADC15   -              -          -           -            -
 * --------------------------------------------------------------------------------------
 * D20/EXT1      PC13        -       -              -          -           -            -
 * D21/EXT2      PC14        -       -              -          -           -            -
 * D22/EXT3      PC15        -       -              -          -           -            -
 * D23/EXT4      PB9         -       TIM4_CH4       -          -           -            Y
 * D24/EXT5      PD2         -       TIM3_ETR       -          -           -            Y
 * D25/EXT6      PC10        -       -              -          -           -            Y
 * D26/EXT7/A14  PB0         ADC8    TIM3_CH3       -          -           -            -
 * D27/EXT8/A15  PB1         ADC9    TIM3_CH4       -          -           -            -
 * D28/EXT9      PB10        -       -              I2C2_SCL   USART3_TX   -            Y
 * D29/EXT10     PB11        -       -              I2C2_SDA   USART3_RX   -            Y
 * D30/EXT11     PB12        -       TIM1_BKIN      I2C2_SMBAL USART3_CK   SPI2_NSS     Y
 * D31/EXT12     PB13        -       TIM1_CH1N      -          USART3_CTS  SPI2_SCK     Y
 * D32/EXT13     PB14        -       TIM1_CH2N      -          USART3_RTS  SPI2_MISO    Y
 * D33/EXT14     PB15        -       TIM1_CH3N      -          -           SPI2_MOSI    Y
 * D34/EXT15     PC6         -       -              -          -           -            Y
 * D35/EXT16     PC7         -       -              -          -           -            Y
 * D36/EXT17     PC8         -       -              -          -           -            Y
 * D37/EXT18     PC9         -       -              -          -           -            Y
 * --------------------------------------------------------------------------------------
 * Note: Silkscreen is marked D15
 * D38           PB8         0    TIM4_CH3          -          -           -            Y
 *
 * */

