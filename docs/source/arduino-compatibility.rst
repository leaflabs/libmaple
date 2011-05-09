.. highlight:: cpp

.. _arduino-compatibility:

=============================
 Maple-Arduino Compatibility
=============================

.. contents:: Contents
   :local:

Overview
--------

The biggest difference between the Maple and most Arduino boards is
that the Maple uses a 32-bit ARM Cortex-M3 architecture chip, while
the Arduinos have 8-bit Atmel AVR chips. The different instruction set
means that machine code (which makes up executable binary program) is
incompatible between the two, and a different compiler (actually just
a different version of `gcc <http://gcc.gnu.org/>`_) is required.

The compiler for the regular Arduino IDE is the popular `avr-gcc
<http://www.nongnu.org/avr-libc/>`_ package; the compiler for the
Maple version of the IDE is CodeSourcery's edition of gcc for the ARM
EABI target (:command:`arm-non-eabi-gcc`).  A (preliminary) reference
on :ref:`using arm-none-eabi-gcc <arm-gcc>` is available.

The bitwidth of the processor means that the Maple can process 32-bit
operations (like adding two 32-bit integers) in a single instruction,
while an Arduino processor would have to split up large operations
into several smaller ones. In a lot of cases 8-bit operations are
plenty (integers 0-255, single characters of text, etc.), but if
you're dealing with higher resolution data, the speed up could be
significant.

A trade-off is that code could be larger as well; program instructions
and memory locations can be up to 32 bits each.  However, removal of
extra instructions and fancy packing together of simple instructions
means that programs aren't much larger (or are even smaller).

Header Numbering and Incompatibilities
--------------------------------------

.. FIXME [Maple-specific values]

The numbering of headers is different; on the Maple each GPIO has a
unique number: 0, 1, 2, all the way up to 37 (actually, there are
:ref:`a few more <jtag>`...). On the Arduino, the analog pins are
numbered separately (A0-A5) from the digital pins (D0\ -D13).

The incompatible hardware differences are:

* :ref:`I2C <i2c>` **port**: on most Arduinos, the |i2c| port is Analog
  Input 4 (SDA) and Analog Input 5 (SCL); on the Maple, |i2c| port 1
  is D5 (SCL) and D9 (SDA), and |i2c| port 2 is D29 (SCL) and D30
  (SDA).

  It should be possible to skywire, sacrificing signal quality (due to
  increased capacitance). Alternatively, |i2c| can be bit-banged
  reasonably well in software. This peripheral could potentially be
  rerouted internally, but we haven't looked into it.

* :ref:`PWM <pwm>` **on D10**: all the other standard Arduino PWM
  headers have PWM functionality on the Maple (D2,D3,D6,D9,D11), but
  not D10.

* **No External Voltage Reference**: The Arduino has an AREF pin which
  allows the use of an external ADC voltage reference; the Maple has
  an extra GPIO pin (D14) with PWM capability in this spot, and does
  not allow an external voltage reference to be configured.

* **EEPROM**: the Maple does not have any internal EEPROM. This
  functionality can be emulated with regular persistent flash memory,
  or with an external EEPROM chip.

* **ISP Programming**: the Maple does not use an ISP/ICSP bus for
  debugging; it uses :ref:`JTAG <jtag>`.


Software Language/Library Changes
---------------------------------

With :ref:`a few exceptions <language-missing-features>`, the entire
Wiring/Arduino language is supported.  However, there are some subtle
differences, most of which are improvements:

* **32-bit integers**: many standard functions either expect or return
  full 32-bit (4 byte) integer values instead of the regular 16-bit (2
  byte) Arduino values.

* **64-bit doubles**: The :ref:`double <lang-double>` type is a full
  double-precision floating point type on the Maple; it is a
  single-precision floating point value on the Arduino.

* :ref:`pinMode() <lang-pinmode>` **types**: any :ref:`GPIO <gpio>`
  (including analog pins) can be configured into one of the following
  modes with a single call to ``pinMode()``: ``OUTPUT``,
  ``OUTPUT_OPEN_DRAIN``, ``INPUT_FLOATING``, ``INPUT_PULLUP``,
  ``INPUT_PULLDOWN``. Additionally, the PWM pins (labeled "PWM" on the
  silkscreen) can be configured in ``PWM`` and ``PWM_OPEN_DRAIN``
  modes, and the analog input pins (labeled "AIN") can be configured
  in ``INPUT_ANALOG`` mode. See the :ref:`GPIO documentation <gpio>`
  for more information.

* :ref:`Serial port <lang-serial>` **syntax**: like the `Arduino Mega
  <http://arduino.cc/en/Main/ArduinoBoardMega>`_, the Maple has
  multiple :ref:`USART ports <lang-serial>`.  By default, ``Serial``
  is not mapped to any of them.  Use ``Serial1`` through ``Serial3``
  instead.

* **16-bit** :ref:`PWM <pwm>`: Arduino boards support 8-bit PWM, which
  means that calls to :ref:`analogWrite() <lang-analogwrite>` take
  values between 0 (always off) and 255 (always on).  The Maple
  supports 16-bit PWM, so the corresponding values should be between 0
  (always off) and 65535 (always on).

* **12-bit** :ref:`ADC <adc>`: Arduino boards support 10-bit ADC, which
  means that calls to :ref:`analogRead() <lang-analogread>` will
  return values between 0 and 1023.  The Maple supports 12-bit ADC, so
  the same call will instead return values between 0 and 4095.

Shield and Device Compatibility
-------------------------------

.. list-table::
   :header-rows: 1

   * - Shield/Device
     - Compatible?
     - Notes

   * - Ethernet shield
     - Yes!
     - Tested; no library yet

   * - WiFi Shield
     - Yes!
     - Tested; preliminary library support

   * - MIDI shield
     - Yes!
     - Tested; no library yet

   * - XBee shield
     - Unknown
     -

   * - Bluetooth shield
     - Unknown
     - Some Bluetooth <-> UART boards have been tested and are known
       to work.

   * - Cellular shield
     - Unknown
     -

Library Porting Status
----------------------

The state of currently ported Arduino libraries is the
:ref:`libraries`.

.. TODO Update as libraries are ported.

.. list-table::
   :header-rows: 1


   * - Library
     - Ported?
     - Notes

   * - Wire
     - Preliminary
     - In progress; see :ref:`library reference <libraries-wire>`.

   * - LiquidCrystal
     - **Yes**
     - :ref:`Included since IDE 0.0.7 <libraries-liquid-crystal>`

   * - Ethernet
     - Not yet
     - Planned

   * - EEPROM
     - (Unsupported) third-party emulation
     - The Maple doesn't have EEPROM; it uses flash instead.  There is
       an `EEPROM emulation library
       <http://akb77.com/g/mcu/maple-eeprom-emulation-library/>`_ by
       `x893 <http://akb77.com/g/>`_, but we haven't tested it.

   * - Firmata
     - Not yet
     - Planned

   * - Matrix
     - Not yet
     - Planned

   * - Servo
     - **Yes**
     - :ref:`Included since IDE 0.0.9 <libraries-servo>`

   * - SoftwareSerial
     - Not yet
     - Planned

   * - Sprite
     - Not yet
     - Planned

   * - Stepper
     - Not yet
     - Planned

Sketch and Library Porting HOWTO
--------------------------------

In addition to the suggestions in this section, you may find many of
the individual :ref:`language reference <language>` pages useful.  As
appropriate, these have "Arduino Compatibility" sections; one good
example is the :ref:`analogWrite() <lang-analogwrite-compatibility>`
function.

- Check the hardware and header differences above, and see if your
  project or shield needs to be modified (eg, add 3.3V level
  converters or reroute PWM to header D10).

- Check for ported library functionality. We intend to port all of the
  core and popular libraries (like Wire, Ethernet, and the LCD screen
  driver), but this task is not yet finished. (:ref:`Patches are
  welcome! <libmaple-contributing>`).

- Check for peripheral conflicts; changing the configuration of timers
  and bus speeds for a feature on one header may impact all the
  features on that hardware "port".  For example, changing the timer
  prescaler to do long PWM pulses could impact |i2c| communications on
  nearby headers.

- Rewrite any low-level code. This could potentially be very
  difficult, but hopefully you've used the Arduino libraries to
  abstract away the registers and other hardware-specific
  details. Your sketch probably doesn't have any low-level code; a
  library which wraps a particular peripheral very well may.  Some
  help is available in the :ref:`arm-gcc` reference.

- Redeclare variable sizes if necessary: generics like ``int`` will
  probably work unless you depend on side-effects like rollover.

- Check every ``pinMode()``: the Maple has more modes for GPIO
  pins. For example, make sure to set analog pins to ``INPUT_ANALOG``
  before reading and PWM pins to ``PWM`` before writing.  The full set
  of pin modes is documented in the :ref:`lang-pinmode` reference.

- Modify PWM writes: ``pinMode()`` must be set to ``PWM``, the
  frequency of the PWM pulse configured, and the duty cycle written
  with up to 16-bit resolution.

- Modify ADC reads: :ref:`lang-analogread` takes the full pin number
  (not 0-5) and returns a full 12-bit reading. The ADC pin must have
  its ``pinMode()`` set to ``INPUT_ANALOG``.

- Possibly convert all Serial-over-USB communications to use
  :ref:`lang-serialusb` instead of a USART :ref:`serial port
  <lang-serial>`. The Maple has a dedicated USB port which is not
  connected to the USART TX/RX pins in any way.

- Check timing: Maple clock cycles are just 13.9 nanoseconds, though
  the peripheral bus speeds (which limit GPIO output) are clocked
  slower.
