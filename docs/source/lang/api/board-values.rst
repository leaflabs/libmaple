.. _lang-board-values:

Board-Specific Values
=====================

There are a number of board-specific values: constants or variables
which are different depending on which LeafLabs board you have.  The
exact values for each board are given in your :ref:`board's hardware
documentation <index-boards>`.

This page lists and documents the board-specific values.  You should
use these when appropriate in your own programs.  This will help make
it easier to share your code with other people who have different
boards.  Some example usages are given :ref:`below
<lang-board-values-examples>`.

The actual values for each board are given in the :ref:`Board Hardware
Documentation <index-boards>`.

.. contents:: Contents
   :local:

Constants
---------

- ``CYCLES_PER_MICROSECOND``: Number of CPU cycles per microsecond on
  your board.

- ``CLOCK_SPEED_MHZ``: Clock speed of your board, in megahertz
  (MHz). This is the same as ``CYCLES_PER_MICROSECOND``.

- ``CLOCK_SPEED_HZ``: Clock speed of your board, in hertz (Hz).  This
  is the same as ``CLOCK_SPEED_MHZ`` × 1,000,000.

- ``SYSTICK_RELOAD_VAL``: Value used when reloading the :ref:`systick`
  timer's counter [#fmillis]_.

.. _lang-board-values-but:

- ``BOARD_BUTTON_PIN``: Pin connected to the built-in button (labeled
  "BUT" on your board's silkscreen).

.. _lang-board-values-led:

- ``BOARD_LED_PIN``: Pin connected to the built-in LED.

- ``BOARD_NR_GPIO_PINS``: Total number of :ref:`GPIO pins <gpio>` that
  are broken out to headers.  Some of these might already be connected
  to external hardware (like the built-in LED and button).  To find
  out if a pin is in use, see :ref:`boardUsesPin()
  <lang-boardusespin>` (and also :ref:`boardUsedPins
  <lang-board-values-used-pins>`).

.. _lang-board-values-nr-pwm-pins:

- ``BOARD_NR_PWM_PINS``: Total *number* of GPIO pins that can be used
  for :ref:`PWM <pwm>`.  The actual *pins* that can do PWM are in the
  :ref:`boardPWMPins <lang-board-values-pwm-pins>` array.

.. _lang-board-values-nr-adc-pins:

- ``BOARD_NR_ADC_PINS``: Total number of GPIO pins that can be used
  for :ref:`analog-to-digital conversion <adc>`.  The actual pins that
  can do ADC conversion are in the :ref:`boardADCPins
  <lang-board-values-adc-pins>` array.

.. _lang-board-values-nr-used-pins:

- ``BOARD_NR_USED_PINS``: Total number of GPIO pins that are already
  connected to some external hardware (like a built-in LED) on the
  board.  The actual pins that that are already used are in the
  :ref:`boardUsedPins <lang-board-values-used-pins>` array.  To see if
  a pin is already in use, use the :ref:`boardUsesPin()
  <lang-boardusespin>` function.

.. _lang-board-values-usart:

- :ref:`USART <usart>` (serial port) related constants:

    * ``BOARD_USART1_TX_PIN``, ``BOARD_USART2_TX_PIN``, ``BOARD_USART3_TX_PIN``:
      TX pins for the 3 USARTS.

    * ``BOARD_USART1_RX_PIN``, ``BOARD_USART2_RX_PIN``, ``BOARD_USART3_RX_PIN``:
      RX pins for the 3 USARTS.

    * ``BOARD_UART4_TX_PIN``, ``BOARD_UART5_TX_PIN``: TX pins for
      UARTs 4 and 5 (high-density boards like Maple Native only).

    * ``BOARD_UART4_RX_PIN``, ``BOARD_UART5_RX_PIN``: RX pins for
      UARTs 4 and 5 (high-density boards like Maple Native only).

    * ``BOARD_NR_USARTS``: Number of serial ports on the board.  This
      number includes UARTs 4 and 5 if they are available.

- :ref:`SPI <spi>` related constants:

    * ``BOARD_SPI1_NSS_PIN``, ``BOARD_SPI1_MOSI_PIN``,
      ``BOARD_SPI1_MISO_PIN``, ``BOARD_SPI1_SCK_PIN``: SPI1
      peripheral's NSS, MOSI, MISO, and SCK pins, respectively.

    * ``BOARD_SPI2_NSS_PIN``, ``BOARD_SPI2_MOSI_PIN``,
      ``BOARD_SPI2_MISO_PIN``, ``BOARD_SPI2_SCK_PIN``: SPI2
      peripheral's NSS, MOSI, MISO, and SCK pins, respectively.

    * ``BOARD_SPI3_NSS_PIN``, ``BOARD_SPI3_MOSI_PIN``,
      ``BOARD_SPI3_MISO_PIN``, ``BOARD_SPI3_SCK_PIN``: SPI3
      peripheral's NSS, MOSI, MISO, and SCK pins, respectively
      (available on high-density devices like Maple Native and Maple
      RET6 edition only).

    * ``BOARD_NR_SPI``: Number of SPI peripherals on the board.

.. _lang-board-values-debug:

- Debug (JTAG, SW-Debug) related constants: ``BOARD_JTMS_SWDIO_PIN``,
  ``BOARD_JTCK_SWCLK_PIN``, ``BOARD_JTDI_PIN``, ``BOARD_JTDO_PIN``,
  and ``BOARD_NJTRST_PIN``.

  These constants are the pin numbers for :ref:`GPIOs <gpio>` used by
  the :ref:`jtag` and Serial-Wire Debug peripherals.  Except for the
  Maple Mini, these pins are usually reserved for special purposes by
  default (i.e., they are in :ref:`boardUsedPins
  <lang-board-values-used-pins>`).  However, they can be used as
  ordinary GPIOs if you call the :ref:`lang-disabledebugports`
  function.  (Be careful with this on the Maple, as writing to
  ``BOARD_NJTRST_PIN`` may cause your board to reset!).

.. _lang-board-values-pwm-pins:

.. _lang-board-values-adc-pins:

.. _lang-board-values-used-pins:

Pin Arrays
----------

Some :ref:`arrays <lang-array>` of pin numbers are available which you
can use to find out certain important information about a given pin.

- ``boardPWMPins``: Pin numbers of each pin capable of :ref:`PWM
  <pwm>` output, using :ref:`pwmWrite() <lang-pwmwrite>`.  The total
  number of these pins is :ref:`BOARD_NR_PWM_PINS
  <lang-board-values-nr-pwm-pins>`.

- ``boardADCPins``: Pin numbers of each pin capable of :ref:`ADC
  <adc>` conversion, using :ref:`analogRead() <lang-analogread>`.  The
  total number of these pins is :ref:`BOARD_NR_ADC_PINS
  <lang-board-values-nr-adc-pins>`.

- ``boardUsedPins``: Pin numbers of each pin that, by default, is used
  for some special purpose by the board.  The total number of these
  pins is :ref:`BOARD_NR_USED_PINS <lang-board-values-nr-used-pins>`.
  To check if a pin is used for a special purpose, use
  :ref:`boardUsesPin() <lang-boardusespin>`.

.. _lang-board-values-examples:

Examples
--------

:ref:`BOARD_LED_PIN <lang-board-values-led>` On the Maple, the
built-in LED is connected to pin 13.  On the Maple Mini, however, it
is connected to pin 33.  You can write a "blinky" program that works
on all LeafLabs boards using ``BOARD_LED_PIN`` and :ref:`toggleLED()
<lang-toggleled>`::

    void setup() {
        pinMode(BOARD_LED_PIN, OUTPUT);
    }

    void loop() {
        toggleLED();
        delay(100);
    }

:ref:`BOARD_BUTTON_PIN <lang-board-values-but>`: Similarly, you can
write a single program that prints a message whenever the button is
pressed which will work on all LeafLabs boards using
``BOARD_BUTTON_PIN`` and :ref:`isButtonPressed()
<lang-isbuttonpressed>`::

    void setup() {
        pinMode(BOARD_BUTTON_PIN, INPUT);
    }

    void loop() {
        if (isButtonPressed()) {
            SerialUSB.println("You pressed the button!");
        }
    }

See Also
--------

- :ref:`lang-boardusespin`
- :ref:`lang-isbuttonpressed`
- :ref:`lang-waitforbuttonpress`
- :ref:`lang-pinmode`
- :ref:`lang-toggleled`
- :ref:`lang-analogread`
- :ref:`lang-pwmwrite`
- :ref:`lang-enabledebugports`
- :ref:`lang-disabledebugports`

.. rubric:: Footnotes

.. [#fmillis] In order for :ref:`lang-millis` to work properly, this
   must be ``CYCLES_PER_MICROSECOND`` × 1,000 - 1.
