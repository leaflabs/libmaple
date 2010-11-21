.. highlight:: c++

.. _language:

==========================
 Maple Language Reference
==========================

The Maple can be programmed in the `Wiring
<http://www.wiring.org.co/reference/>`_ language, which is the same
language used to program the `Arduino <http://arduino.cc/>`_ boards.

C or C++ programmers curious about the differences between the Wiring
language and C++ may wish to skip to the
:ref:`arduino_c_for_c_hackers`.

.. contents:: Contents
   :local:

Unique Maple Additions
----------------------

.. _language-assert:

``ASSERT(...)``
    The ``ASSERT()`` function can be very useful for basic program
    debugging. The function accepts a boolean; for example::

      ASSERT(state == WAIT);

    zero is false and any other number is true. If the boolean is true
    the assertion passes and the program continues as usual. If it is
    false, the assertion fails: the program is halted, debug
    information is printed to USART2, and the status LED begins to
    throb in intensity (it's noticeably different from blinking). The
    debug information is printed at 9600 baud and consists of the
    filename and line number where the particular assertion failed.

    Including assertions in a program increases the program size. When
    using libmaple **from the command line only**, they can be
    disabled by making the definition ::

      #define DEBUG_LEVEL DEBUG_NONE

    before including either wirish or libmaple. In this case, all
    assertions will pass without any lost clock cycles.  Note that
    this will **not work in the IDE**; even with this definition,
    assertions will still be enabled.

.. _language-arduino-docs:

Maple Language Reference
------------------------

+-------------------------------------------------+----------------------------------------------+---------------------------------------------------+
| Structure                                       | Variables                                    | Functions                                         |
|                                                 |                                              |                                                   |
+=================================================+==============================================+===================================================+
|* :ref:`setup() <arduino-setup>`                 |**Constants**                                 |**Digital I/O**                                    |
|                                                 |                                              |                                                   |
|* :ref:`loop() <arduino-loop>`                   |* :ref:`HIGH <arduino-constants-high>` |      |* :ref:`pinMode() <arduino-pinmode>`               |
|                                                 |  :ref:`LOW <arduino-constants-low>`          |                                                   |
|                                                 |                                              |* :ref:`digitalWrite() <arduino-digitalwrite>`     |
|**Control Structures**                           |* :ref:`INPUT <arduino-constants-input>` |    |                                                   |
|                                                 |  :ref:`OUTPUT <arduino-constants-output>`    |* :ref:`digitalRead() <arduino-digitalread>`       |
|* :ref:`if <arduino-if>`                         |                                              |                                                   |
|                                                 |* :ref:`true <arduino-constants-true>` |      |                                                   |
|* :ref:`if...else <arduino-else>`                |  :ref:`false <arduino-constants-false>`      |**Analog I/O**                                     |
|                                                 |                                              |                                                   |
|* :ref:`for <arduino-for>`                       |* :ref:`integer constants                     |* :ref:`analogRead() <arduino-analogread>`         |
|                                                 |  <arduino-constants-integers>`               |                                                   |
|* :ref:`switch/case <arduino-switchcase>`        |                                              |* :ref:`pwmWrite() <wirish-pwmwrite>`              |
|                                                 |* :ref:`floating point constants              |  (:ref:`analogWrite() <arduino-analogwrite>` is   |
|* :ref:`while <arduino-while>`                   |  <arduino-constants-fp>`                     |  also available, though its use is discouraged)   |
|                                                 |                                              |                                                   |
|* :ref:`do...while <arduino-dowhile>`            |                                              |                                                   |
|                                                 |**Data Types**                                |**Advanced I/O**                                   |
|* :ref:`break <arduino-break>`                   |                                              |                                                   |
|                                                 | The size of each datatype, in bytes, is      |* tone(): TODO                                     |
|* :ref:`continue <arduino-continue>`             | given in parentheses where appropriate.      |                                                   |
|                                                 |                                              |* noTone(): TODO                                   |
|* :ref:`return <arduino-return>`                 | *Note*: The ``word`` type is (deliberately)  |                                                   |
|                                                 | :ref:`not supported <language-no-word>`.     |* shiftOut(): TODO                                 |
|* :ref:`goto <arduino-goto>`                     |                                              |                                                   |
|                                                 |* :ref:`void <arduino-void>`                  |* pulseIn(): TODO                                  |
|                                                 |                                              |                                                   |
|**Further syntax**                               |* :ref:`boolean <arduino-boolean>` (1 byte)   |                                                   |
|                                                 |                                              |**Time**                                           |
|* :ref:`; <arduino-semicolon>` (semicolon)       |* :ref:`char <arduino-char>` (1 byte)         |                                                   |
|                                                 |                                              |* :ref:`millis() <arduino-millis>`                 |
|* :ref:`{} <arduino-braces>` (curly braces)      |* :ref:`unsigned char                         |                                                   |
|                                                 |  <arduino-unsignedchar>` (1 byte)            |* :ref:`micros() <arduino-micros>`                 |
|* :ref:`// <arduino-comments-singleline>`        |                                              |                                                   |
|  (single line comment)                          |* :ref:`byte <arduino-byte>` (1 byte)         |* :ref:`delay() <arduino-delay>`                   |
|                                                 |                                              |                                                   |
|* :ref:`/\* \*/                                  |* :ref:`int <arduino-int>` (4 bytes)          |* :ref:`delayMicroseconds()                        |
|  <arduino-comments-multiline>`                  |                                              |  <arduino-delaymicroseconds>`                     |
|  (multi-line comment)                           |* :ref:`unsigned int <arduino-unsignedint>`   |                                                   |
|                                                 |  (4 bytes)                                   |                                                   |
|* :ref:`#define <arduino-define>`                |                                              |**Math**                                           |
|                                                 |* :ref:`long <arduino-long>` (8 bytes)        |                                                   |
|* :ref:`#include <arduino-include>`              |                                              |* :ref:`min() <arduino-min>`                       |
|                                                 |* :ref:`unsigned long <arduino-unsignedlong>` |                                                   |
|                                                 |  (8 bytes)                                   |* :ref:`max() <arduino-max>`                       |
|**Arithmetic Operators**                         |                                              |                                                   |
|                                                 |* :ref:`float <arduino-float>` (4 bytes)      |* :ref:`abs() <arduino-abs>`                       |
|* :ref:`= <arduino-assignment>`                  |                                              |                                                   |
|  (assignment operator)                          |* :ref:`double <arduino-double>` (8 bytes)    |* :ref:`constrain() <arduino-constrain>`           |
|                                                 |                                              |                                                   |
|* :ref:`+ <arduino-arithmetic>` (addition)       |* :ref:`string <arduino-string>`              |* :ref:`map() <arduino-constrain>`                 |
|                                                 |                                              |                                                   |
|* :ref:`- <arduino-arithmetic>`                  |* :ref:`array <arduino-array>`                |* :ref:`pow() <arduino-pow>`                       |
|  (subtraction)                                  |                                              |                                                   |
|                                                 |* Also provided: ``int8``, ``int16``,         |* :ref:`sqrt() <arduino-sqrt>`                     |
|* :ref:`* <arduino-arithmetic>`                  |  ``int32``, ``int64``, and their unsigned    |                                                   |
|  (multiplication)                               |  counterparts ``uint8``, ``uint16``,         |                                                   |
|                                                 |  ``uint32``, ``uint64``.                     |**Trigonometry**                                   |
|* :ref:`/ <arduino-arithmetic>` (division)       |                                              |                                                   |
|                                                 |                                              |* :ref:`sin() <arduino-sin>`                       |
|* :ref:`% <arduino-modulo>` (modulo)             |**Conversion**                                |                                                   |
|                                                 |                                              |* :ref:`cos() <arduino-cos>`                       |
|                                                 |* :ref:`char() <arduino-charcast>`            |                                                   |
|**Comparison Operators**                         |                                              |* :ref:`tan() <arduino-tan>`                       |
|                                                 |* :ref:`byte() <arduino-bytecast>`            |                                                   |
|* :ref:`== <arduino-comparison>` (equal to)      |                                              |                                                   |
|                                                 |* :ref:`int() <arduino-intcast>`              |**Random Numbers**                                 |
|* :ref:`\!= <arduino-comparison>`                |                                              |                                                   |
|  (not equal to)                                 |* :ref:`long() <arduino-longcast>`            |* :ref:`randomSeed() <arduino-randomseed>`         |
|                                                 |                                              |                                                   |
|* :ref:`< <arduino-comparison>` (less than)      |* :ref:`float() <arduino-floatcast>`          |* :ref:`random() <arduino-random>`                 |
|                                                 |                                              |                                                   |
|* :ref:`> <arduino-comparison>`                  |* :ref:`double() <arduino-doublecast>`        |                                                   |
|  (greater than)                                 |                                              |**Bits and Bytes**                                 |
|                                                 |                                              |                                                   |
|* :ref:`<= <arduino-comparison>`                 |**Variable Scope & Qualifiers**               |* :ref:`lowByte() <arduino-lowbyte>`               |
|  (less than or equal to)                        |                                              |                                                   |
|                                                 |* :ref:`variables <arduino-variables>`,       |* :ref:`highByte() <arduino-highbyte>` is          |
|* :ref:`>= <arduino-comparison>`                 |  :ref:`scope <arduino-variables-scope>`      |  provided, though its use is discouraged.         |
|  (greater than or equal to)                     |                                              |                                                   |
|                                                 |* :ref:`static <arduino-static>`              |* :ref:`bitRead() <arduino-bitread>`               |
|                                                 |                                              |                                                   |
|**Boolean Operators**                            |* :ref:`volatile <arduino-volatile>`          |* :ref:`bitWrite() <arduino-bitwrite>`             |
|                                                 |                                              |                                                   |
|* :ref:`&& <arduino-boolean-and>` (and)          |* :ref:`const <arduino-const>`                |* :ref:`bitSet() <arduino-bitset>`                 |
|                                                 |                                              |                                                   |
|* :ref:`|| <arduino-boolean-or>` (or)            |                                              |* :ref:`bitClear() <arduino-bitclear>`             |
|                                                 |**Utilities**                                 |                                                   |
|* :ref:`\! <arduino-boolean-not>` (not)          |                                              |* :ref:`bit() <arduino-bit>`                       |
|                                                 |* :ref:`sizeof() <arduino-sizeof>`            |                                                   |
|                                                 |  (``sizeof`` operator)                       |                                                   |
|**Pointer Access Operators**                     |                                              |**External Interrupts**                            |
|                                                 |                                              |                                                   |
|* :ref:`* dereference operator                   |                                              |* :ref:`Reference Page <external-interrupts>`      |
|  <arduino-pointer>`                             |                                              |                                                   |
|                                                 |                                              |* :ref:`attachInterrupt()                          |
|* :ref:`& reference operator                     |                                              |  <arduino-attachinterrupt>`                       |
|  <arduino-pointer>`                             |                                              |                                                   |
|                                                 |                                              |* :ref:`detachInterrupt()                          |
|                                                 |                                              |  <arduino-detachinterrupt>`                       |
|**Bitwise Operators**                            |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`& <arduino-bitwisemath-and>`             |                                              |**Interrupts**                                     |
|  (bitwise and)                                  |                                              |                                                   |
|                                                 |                                              |* interrupts(): TODO                               |
|* :ref:`| <arduino-bitwisemath-or>`              |                                              |                                                   |
|  (bitwise or)                                   |                                              |* noInterrupts(): TODO                             |
|                                                 |                                              |                                                   |
|* :ref:`^ <arduino-bitwisemath-xor>`             |                                              |                                                   |
|  (bitwise xor)                                  |                                              |**Communication**                                  |
|                                                 |                                              |                                                   |
|* :ref:`~ <arduino-bitwisemath-not>`             |                                              |* :ref:`SerialUSB <wirish-serialusb>`              |
|  (bitwise not)                                  |                                              |                                                   |
|                                                 |                                              |* :ref:`Serial <arduino-serial>`                   |
|* :ref:`\<\< <arduino-bitshift>`                 |                                              |                                                   |
|  (shift left)                                   |                                              |**Looking for something else?**                    |
|                                                 |                                              |                                                   |
|* :ref:`>> <arduino-bitshift>`                   |                                              | See the :ref:`libraries` page for interfacing with|
|  (shift right)                                  |                                              | particular types of hardware. Try the list of     |
|                                                 |                                              | `community-contributed code` .  Maple links       |
|                                                 |                                              | against `newlib` and allows the use of any of its |
|**Compound Operators**                           |                                              | functions; see its documentation for more details.|
|                                                 |                                              |                                                   |
|* :ref:`++ <arduino-increment>`                  |                                              |                                                   |
|  (increment)                                    |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`- - <arduino-increment>`                 |                                              |                                                   |
|  (decrement)                                    |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`+= <arduino-arithmeticcompound>`         |                                              |                                                   |
|  (compound add)                                 |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`-=                                       |                                              |                                                   |
|  <arduino-arithmeticcompound>` (compound        |                                              |                                                   |
|  subtract)                                      |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`*=                                       |                                              |                                                   |
|  <arduino-arithmeticcompound>` (compound        |                                              |                                                   |
|  multiply)                                      |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`/=                                       |                                              |                                                   |
|  <arduino-arithmeticcompound>` (compound        |                                              |                                                   |
|  divide)                                        |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`&=                                       |                                              |                                                   |
|  <arduino-arithmeticcompound>` (compound        |                                              |                                                   |
|  bitwise and)                                   |                                              |                                                   |
|                                                 |                                              |                                                   |
|* :ref:`|=                                       |                                              |                                                   |
|  <arduino-arithmeticcompound>` (compound        |                                              |                                                   |
|  bitwise or)                                    |                                              |                                                   |
|                                                 |                                              |                                                   |
+-------------------------------------------------+----------------------------------------------+---------------------------------------------------+

.. _language-missing-features:

Missing Arduino Features
------------------------

Stub TODO: fill in other missing features

**analogReference()**

    It is not possible to implement this function on the Maple
    hardware.  It will be possible on the upcoming Maple Native.

.. _language-no-word:

**word**

    Readers familiar with the Arduino environment may notice that the
    ``word`` datatype is missing from the above table's list of data
    types.  We chose **not to provide** the ``word`` data type on the
    Maple.  If you want a 16-bit unsigned integer, use the ``uint16``
    type instead.

    While the Maple has 32-bit words, the word size on an Arduino
    board is only 16 bits, and code that uses the ``word`` type is
    likely to rely on that fact.

    By not supporting ``word``, you'll get a compile error when
    porting Arduino code to the Maple instead of potentially weird,
    hard-to-debug runtime behavior.

    If you really must have ``word``, you can include the following
    ``typedef`` in your program::

        typedef uint16 word;

.. _our reference page: http://leaflabs.com/docs/external-interrupts/

.. _newlib: http://sourceware.org/newlib/

.. _arduino_c_for_c_hackers:

Note for C/C++ Programmers
--------------------------

This is a note for programmers comfortable with C or C++ (although,
you C programmers should remember that `C++ is not a superset of C
<http://en.wikipedia.org/wiki/Compatibility_of_C_and_C%2B%2B>`_) who
want a better understanding of the differences between C++ and the
Wiring language.  The good news is that the differences are relatively
few; Wiring is just a thin wrapper around C++.

Some potentially better news is that the Maple can be programmed using
a :ref:`standard Unix toolchain <unix-toolchain>`, so if you'd rather
stick with :command:`gcc`, :command:`make`, and friends, you can.

A *sketch* is the IDE's notion of a project; it consists of one or
more files written in the Wiring language, which is mostly the same as
C++.  The major difference between the two is that in Wiring, it's not
necessary to declare global functions before they are used.  That is,
the following is valid Wiring, and ``f()`` returns ``5``::

  int f() {
    return g();
  }

  int g() {
    return 5;
  }

All of the files in a sketch share the same (global) namespace.  That
is, the behavior is as if all of a sketch's files were part of the
same translation unit, so they don't have to include one another in
order to access each other's definitions.  The only other major
difference between Wiring and C++ is that Wiring doesn't support
dynamically allocated memory -- that is, ``new`` and ``delete`` won't
work.  As of |today|, Maple only has 20 KB RAM, anyway, so it's
doubtful that static allocation is not what you want.

The Wiring language also does not require you to define your own
``main`` method (in fact, it forbids you from doing so).  Instead, you
are required to define two functions, ``setup`` and ``loop``, with
type signatures ::

  void setup(void);
  void loop(void);

Once a sketch is uploaded to a Maple and begins to run, ``setup()`` is
called once, and then ``loop()`` is called repeatedly.  The IDE
compilation process proceeds via a source-to-source translation from
the files in a sketch to C++.

This translation process first concatenates the sketch files, then
parses the result to produce a list of all functions defined in the
global scope.  (We borrow this stage from the Arduino IDE, which in
turn borrows it from Wiring.  It uses regular expressions to parse
C++, which is, of course, `Bad and Wrong
<http://www.retrologic.com/jargon/B/Bad-and-Wrong.html>`_.  An
upcoming rewrite of the IDE performs this preprocessing step
correctly, using a real parser.  Until then, you have our apologies.)
The order in which the individual sketch files are concatenated is not
defined; it is unwise to write code that depends on a particular
ordering.

The concatenated sketch files are then appended onto a file which
includes `WProgram.h
<http://github.com/leaflabs/libmaple/blob/master/wirish/WProgram.h>`_
(which includes the wirish and libmaple libraries, and declares
``setup()`` and ``loop()``), and then provides declarations for all
the function definitions found in the previous step.  At this point,
we have a file that is a valid C++ translation unit, but lacks a
``main()`` method.  The final step of compilation provides this
method, which behaves roughly like::

  int main(void) {
    setup();
    while (true) loop();
  }

(The truth is a little bit more complicated, but not by much).

As an example, consider a sketch with two files.  The first file
contains ``setup()`` and ``loop()``::

  int the_pin;

  void setup() {
    the_pin = choose_a_pin();
    pinMode(the_pin, OUTPUT);
  }

  void loop() {
    static int toggle = 0;
    toggle ^= 1;
    digitalWrite(the_pin, toggle);
  }

The second file contains the (not very useful) implementation for
``choose_a_pin()``::

  int choose_a_pin() {
     return random(5, 15);
  }

Then the results of the concatenation process might be ::

  int the_pin;

  void setup() {
    the_pin = choose_a_pin();
    pinMode(the_pin, OUTPUT);
  }

  void loop() {
    static int toggle = 0;
    toggle ^= 1;
    digitalWrite(the_pin, toggle);
  }

  int choose_a_pin(void);

  int choose_a_pin() {
     return random(5, 15);
  }

Which could plausibly be turned into the final source file ::

  #include "WProgram.h"

  void setup(void);
  void loop(void);
  int choose_a_pin(void);

  int the_pin;

  void setup() {
    the_pin = choose_a_pin();
    pinMode(the_pin, OUTPUT);
  }

  void loop() {
    static int toggle = 0;
    toggle ^= 1;
    digitalWrite(the_pin, toggle);
  }

  int choose_a_pin(void);

  int choose_a_pin() {
     return random(5, 15);
  }

  int main() {
    setup();
    while (true) loop();
  }

(Recall that it's legal C++ for a function to be declared multiple
times, as long as it's defined exactly once).


Recommended Reading
-------------------

* `newlib Documentation <http://sourceware.org/newlib/>`_
* STMicro documentation for STM32F103RB microcontroller:

    * `All documents <http://www.st.com/mcu/devicedocs-STM32F103RB-110.html>`_
    * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
    * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
    * `Programming Manual <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_ (assembly language and register reference)
