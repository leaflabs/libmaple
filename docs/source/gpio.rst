.. _gpio:

GPIO
====

The Maple features 38 ready-to-use general purpose input/output (GPIO)
pins for digital input/output, numbered D0 through D37.  These numbers
correspond to the numeric values next to each header on the Maple
silkscreen.

Many of these pins may additionally be used for special features or
peripheral functions.  This page documents those capabilities, by pin.

The current and voltage limitations have been copied over from the
STM32 datasheet (see the :ref:`Recommended Reading
<gpio-recommended-reading>` for a link).  In particular, a number of
GPIO pins are 5V tolerant (which means that applying 5 volts to a pin
and reading it as input or allowing it to drain to ground will not
damage that pin), while some are not.

.. contents:: Contents
   :local:

.. _pin-mapping-mega-table:

Pin Mapping Mega Table
----------------------

This table shows the available functionality on every GPIO pin, by
peripheral type. The "STM32" column refers to the port and number that
the header is connected to on the microcontroller.  The "5V?" column
documents whether or not the pin is 5 volt tolerant (see above).

.. TODO silkscreen pictures which let you know what each abbreviation
.. means, with links to the relevant documentation.

.. csv-table::
   :header: "Pin", "STM32", ":ref:`ADC <adc>`", ":ref:`Timer <timers>`", ":ref:`I2C <i2c>`", ":ref:`UART <usart>`", ":ref:`SPI <spi>`", "5v?"

   "D0",  "PA3",  "ADC3",  "TIM2_CH4",     "-",          "USART2_RX",  "-",         "No"
   "D1",  "PA2",  "ADC2",  "TIM2_CH3",     "-",          "USART2_TX",  "-",         "No"
   "D2",  "PA0",  "ADC0",  "TIM2_CH1_ETR", "-",          "USART2_CTS", "-",         "No"
   "D3",  "PA1",  "ADC1",  "TIM2_CH2",     "-",          "USART2_RTS", "-",         "No"
   "D4",  "PB5",  "-",     "-",            "ISC1_SMBA",  "-",          "-",         "No"
   "D5",  "PB6",  "-",     "TIM4_CH1",     "I2C1_SCL",   "-",          "-",         "Yes"
   "D6",  "PA8",  "-",     "TIM1_CH1",     "-",          "USART1_CK",  "-",         "Yes"
   "D7",  "PA9",  "-",     "TIM1_CH2",     "-",          "USART1_TX",  "-",         "Yes"
   "D8",  "PA10", "-",     "TIM1_CH3",     "-",          "USART1_RX",  "-",         "Yes"
   "D9",  "PB7",  "-",     "TIM4_CH2",     "I2C1_SDA",   "-",          "-",         "Yes"
   "D10", "PA4",  "ADC4",  "-",            "-",          "USART2_CK",  "SPI1_NSS",  "No"
   "D11", "PA7",  "ADC7",  "TIM3_CH2",     "-",          "-",          "SPI1_MOSI", "No"
   "D12", "PA6",  "ADC6",  "TIM3_CH1",     "-",          "-",          "SPI1_MISO", "No"
   "D13", "PA5",  "ADC5",  "-",            "-",          "-",          "SPI1_SCK",  "No"
   "D14", "PB8",  "-",     "TIM4_CH3",     "-",          "-",          "-",         "Yes"
   "D15", "PC0",  "ADC10", "-",            "-",          "-",          "-",         "No"
   "D16", "PC1",  "ADC11", "-",            "-",          "-",          "-",         "No"
   "D17", "PC2",  "ADC12", "-",            "-",          "-",          "-",         "No"
   "D18", "PC3",  "ADC13", "-",            "-",          "-",          "-",         "No"
   "D19", "PC4",  "ADC14", "-",            "-",          "-",          "-",         "No"
   "D20", "PC5",  "ADC15", "-",            "-",          "-",          "-",         "No"
   "D21", "PC13", "-",     "-",            "-",          "-",          "-",         "No"
   "D22", "PC14", "-",     "-",            "-",          "-",          "-",         "No"
   "D23", "PC15", "-",     "-",            "-",          "-",          "-",         "No"
   "D24", "PB9",  "-",     "TIM4_CH4",     "-",          "-",          "-",         "Yes"
   "D25", "PD2",  "-",     "TIM3_ETR",     "-",          "-",          "-",         "Yes"
   "D26", "PC10", "-",     "-",            "-",          "-",          "-",         "Yes"
   "D27", "PB0",  "ADC8",  "TIM3_CH3",     "-",          "-",          "-",         "No"
   "D28", "PB1",  "ADC9",  "TIM3_CH4",     "-",          "-",          "-",         "No"
   "D29", "PB10", "-",     "-",            "I2C2_SCL",   "USART3_TX",  "-",         "Yes"
   "D30", "PB11", "-",     "-",            "I2C2_SDA",   "USART3_RX",  "-",         "Yes"
   "D31", "PB12", "-",     "TIM1_BKIN",    "I2C2_SMBAL", "USART3_CK",  "SPI2_NSS",  "Yes"
   "D32", "PB13", "-",     "TIM1_CH1N",    "-",          "USART3_CTS", "SPI2_SCK",  "Yes"
   "D33", "PB14", "-",     "TIM1_CH2N",    "-",          "USART3_RTS", "SPI2_MISO", "Yes"
   "D34", "PB15", "-",     "TIM1_CH3N",    "-",          "-",          "SPI2_MOSI", "Yes"
   "D35", "PC6",  "-",     "-",            "-",          "-",          "-",         "Yes"
   "D36", "PC7",  "-",     "-",            "-",          "-",          "-",         "Yes"
   "D37", "PC8",  "-",     "-",            "-",          "-",          "-",         "Yes"

.. _gpio-modes:

GPIO Modes
----------

.. doxygenenum:: WiringPinMode

Function Reference
------------------

- :ref:`pinMode() <lang-pinmode>`

- :ref:`digitalRead() <lang-digitalread>`

- :ref:`digitalWrite() <lang-digitalwrite>`

- :ref:`analogRead() <lang-analogread>`

- :ref:`pwmWrite() <lang-pwmwrite>` (Maple's equivalent to
  ``analogWrite()``; see the :ref:`analogWrite() reference
  <lang-analogwrite>` for differences from the Arduino version).

.. _gpio-recommended-reading:

Recommended Reading
-------------------

STMicro documentation for STM32F103RB microcontroller:

  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
