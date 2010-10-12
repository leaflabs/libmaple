.. _gpio:

======
 GPIO
======

The Maple features 38 ready-to-use general purpose input/output (GPIO)
pins for digital input/output, numbered D0 through D37.  These numbers
correspond to the numeric values next to each header on the Maple
silkscreen.

Many of these pins may additionally be used for special features or
peripheral functions.  This page documents those capabilities, by pin.

The current and voltage limitations have not been copied over from the
STM32 datasheet (see the :ref:`Recommended Reading
<gpio-recommended-reading>` for a link).  In particular, a number of
GPIO pins are 5v tolerant (which means that applying 5v to a pin and
reading it as input or allowing it to drain to ground will not damage
that pin), while some are not.

.. contents:: Contents
   :local:

.. _pin-mapping-mega-table:

Pin Mapping Mega Table
----------------------

This huge reference table shows the available functionality on every
GPIO pin, by peripheral type. The "STM32" column refers to the port
and number that the header is connected to on the microcontroller.
The "5v?" column documents whether or not the pin is 5v tolerant (see
above).

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

``OUTPUT``

    Basic digital output: when the pin set high the voltage is held at
    +3.3V (|vcc|) and when set low it is pulled down to ground.

``OUTPUT_OPEN_DRAIN``

    In open drain mode, the pin indicates "low" by accepting current
    flow to ground and "high" by providing increased impedance. An
    example use would be to connect a pin to a bus line (which is
    pulled up to a positive voltage by a separate supply through a
    large resistor). When the pin is high, not much current flows
    through to ground and the line stays at positive voltage; when the
    pin is low the bus "drains" to ground with a small amount of
    current constantly flowing through the large resistor from the
    external supply. In this mode no current is ever actually
    *sourced* from the pin.

``INPUT`` (or ``INPUT_FLOATING``)

    Basic digital input. The pin voltage is sampled; when it is closer
    to 3.3V (|vcc|) the pin status is high, and when it is closer to
    0V (ground) it is low. If no external circuit is pulling the pin
    voltage to high or low, it will tend to randomly oscillate and be
    very sensitive to noise (e.g., a breath of air across the pin will
    cause the state to flip).

``INPUT_PULLUP``

    The state of the pin in this mode is reported the same way as with
    INPUT, but the pin voltage is gently "pulled up" towards
    +3.3V. This means the state will be high unless an external device
    is specifically pulling the pin down to ground, in which case the
    "gentle" pull up will not effect the state of the input.

``INPUT_PULLDOWN``

    The state of the pin in this mode is reported the same way as with
    INPUT, but the pin voltage is gently "pulled down" towards
    0V. This means the state will be low unless an external device is
    specifically pulling the pin up to 3.3V, in which case the
    "gentle" pull down will not effect the state of the input.

``INPUT_ANALOG``

    This is a special mode for when the pin will be used for analog
    (not digital) reads. See the :ref:`ADC <adc>` page.

``PWM``

    This is a special mode for when the pin will be used for PWM
    output (a special case of digital output). See the :ref:`PWM
    <pwm>` page.

.. TODO PWM_OPEN_DRAIN needs documentation

Function Reference
------------------

``pinMode(pin_number, MODE)``

    Usually called from within `setup()`_ to configure the pin. MODE
    is one of the set listed :ref:`above <gpio-modes>`.

``digitalRead(pin_number)``

    Returns ``HIGH`` (|vcc|) or ``LOW`` (0V).

``digitalWrite(pin_number, value)``

    Sets the pin to ``HIGH`` or ``LOW``.

.. _gpio-recommended-reading:

Recommended Reading
-------------------

STMicro documentation for STM32F103RB microcontroller:

  * `All <http://www.st.com/mcu/devicedocs-STM32F103RB-110.html>`_
  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
