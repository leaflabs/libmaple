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

    before including either wirish.h or libmaple.h. In this case, all
    assertions will pass without any lost clock cycles.  Note that
    this will **not work in the IDE**; even with this definition,
    assertions will still be enabled.

.. _language-lang-docs:

Maple Language Reference
------------------------

+--------------------------------------------+----------------------------------------------+---------------------------------------------------+
| Structure                                  | Variables                                    | Functions                                         |
|                                            |                                              |                                                   |
+============================================+==============================================+===================================================+
|* :ref:`setup() <lang-setup>`               |**Constants**                                 |**Digital I/O**                                    |
|                                            |                                              |                                                   |
|* :ref:`loop() <lang-loop>`                 |* :ref:`HIGH <lang-constants-high>` |         |* :ref:`pinMode() <lang-pinmode>`                  |
|                                            |  :ref:`LOW <lang-constants-low>`             |                                                   |
|                                            |                                              |* :ref:`digitalWrite() <lang-digitalwrite>`        |
|**Control Structures**                      |* :ref:`INPUT <lang-constants-input>` |       |                                                   |
|                                            |  :ref:`OUTPUT <lang-constants-output>`       |* :ref:`digitalRead() <lang-digitalread>`          |
|* :ref:`if <lang-if>`                       |                                              |                                                   |
|                                            |* :ref:`true <lang-constants-true>` |         |                                                   |
|* :ref:`if...else <lang-else>`              |  :ref:`false <lang-constants-false>`         |**Analog I/O**                                     |
|                                            |                                              |                                                   |
|* :ref:`for <lang-for>`                     |* :ref:`integer constants                     |* :ref:`analogRead() <lang-analogread>`            |
|                                            |  <lang-constants-integers>`                  |                                                   |
|* :ref:`switch/case <lang-switchcase>`      |                                              |* :ref:`pwmWrite() <lang-pwmwrite>`                |
|                                            |* :ref:`floating point constants              |  (:ref:`analogWrite() <lang-analogwrite>` is      |
|* :ref:`while <lang-while>`                 |  <lang-constants-fp>`                        |  also available, though its use is discouraged)   |
|                                            |                                              |                                                   |
|* :ref:`do...while <lang-dowhile>`          |                                              |                                                   |
|                                            |**Data Types**                                |**Advanced I/O**                                   |
|* :ref:`break <lang-break>`                 |                                              |                                                   |
|                                            | The size of each datatype, in bytes, is      |* tone(): TODO                                     |
|* :ref:`continue <lang-continue>`           | given in parentheses where appropriate.      |                                                   |
|                                            |                                              |* noTone(): TODO                                   |
|* :ref:`return <lang-return>`               | *Note*: The ``word`` type is (deliberately)  |                                                   |
|                                            | :ref:`not supported <language-no-word>`.     |* shiftOut(): TODO                                 |
|* :ref:`goto <lang-goto>`                   |                                              |                                                   |
|                                            |* :ref:`void <lang-void>`                     |* pulseIn(): TODO                                  |
|                                            |                                              |                                                   |
|**Further syntax**                          |* :ref:`boolean <lang-boolean>` (1 byte)      |                                                   |
|                                            |                                              |**Time**                                           |
|* :ref:`; (semicolon) <lang-semicolon>`     |* :ref:`char <lang-char>` (1 byte)            |                                                   |
|                                            |                                              |* :ref:`millis() <lang-millis>`                    |
|* :ref:`{} (curly braces) <lang-braces>`    |* :ref:`unsigned char                         |                                                   |
|                                            |  <lang-unsignedchar>` (1 byte)               |* :ref:`micros() <lang-micros>`                    |
|* :ref:`// (single-line comment)            |                                              |                                                   |
|  <lang-comments-singleline>`               |* :ref:`byte <lang-byte>` (1 byte)            |* :ref:`delay() <lang-delay>`                      |
|                                            |                                              |                                                   |
|* :ref:`/\* \*/ (multi-line comment)        |* :ref:`int <lang-int>` (4 bytes)             |* :ref:`delayMicroseconds()                        |
|  <lang-comments-multiline>`                |                                              |  <lang-delaymicroseconds>`                        |
|                                            |* :ref:`unsigned int <lang-unsignedint>`      |                                                   |
|* :ref:`#define <lang-define>`              |  (4 bytes)                                   |                                                   |
|                                            |                                              |**Math**                                           |
|* :ref:`#include <lang-include>`            |* :ref:`long <lang-long>` (8 bytes)           |                                                   |
|                                            |                                              |* :ref:`min() <lang-min>`                          |
|                                            |* :ref:`unsigned long <lang-unsignedlong>`    |                                                   |
|**Arithmetic Operators**                    |  (8 bytes)                                   |* :ref:`max() <lang-max>`                          |
|                                            |                                              |                                                   |
|* :ref:`= <lang-assignment>`                |* :ref:`float <lang-float>` (4 bytes)         |* :ref:`abs() <lang-abs>`                          |
|  (assignment operator)                     |                                              |                                                   |
|                                            |* :ref:`double <lang-double>` (8 bytes)       |* :ref:`constrain() <lang-constrain>`              |
|* :ref:`+ <lang-arithmetic>` (addition)     |                                              |                                                   |
|                                            |* :ref:`string <lang-string>`                 |* :ref:`map() <lang-constrain>`                    |
|* :ref:`- <lang-arithmetic>`                |                                              |                                                   |
|  (subtraction)                             |* :ref:`array <lang-array>`                   |* :ref:`pow() <lang-pow>`                          |
|                                            |                                              |                                                   |
|* :ref:`* <lang-arithmetic>`                |* See also: :ref:`built-in types reference    |* :ref:`sqrt() <lang-sqrt>`                        |
|  (multiplication)                          |  <lang-types>`.                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`/ <lang-arithmetic>` (division)     |                                              |**Trigonometry**                                   |
|                                            |**Conversion**                                |                                                   |
|* :ref:`% <lang-modulo>` (modulo)           |                                              |* :ref:`sin() <lang-sin>`                          |
|                                            |* :ref:`char() <lang-charcast>`               |                                                   |
|                                            |                                              |* :ref:`cos() <lang-cos>`                          |
|**Comparison Operators**                    |* :ref:`byte() <lang-bytecast>`               |                                                   |
|                                            |                                              |* :ref:`tan() <lang-tan>`                          |
|* :ref:`== <lang-comparison>` (equal to)    |* :ref:`int() <lang-intcast>`                 |                                                   |
|                                            |                                              |                                                   |
|* :ref:`\!= <lang-comparison>`              |* :ref:`long() <lang-longcast>`               |**Random Numbers**                                 |
|  (not equal to)                            |                                              |                                                   |
|                                            |* :ref:`float() <lang-floatcast>`             |* :ref:`randomSeed() <lang-randomseed>`            |
|* :ref:`< <lang-comparison>` (less than)    |                                              |                                                   |
|                                            |* :ref:`double() <lang-doublecast>`           |* :ref:`random() <lang-random>`                    |
|* :ref:`> <lang-comparison>`                |                                              |                                                   |
|  (greater than)                            |                                              |                                                   |
|                                            |**Variable Scope & Qualifiers**               |**Bits and Bytes**                                 |
|* :ref:`<= <lang-comparison>`               |                                              |                                                   |
|  (less than or equal to)                   |* :ref:`variables <lang-variables>`,          |* :ref:`lowByte() <lang-lowbyte>`                  |
|                                            |  :ref:`scope <lang-variables-scope>`         |                                                   |
|* :ref:`>= <lang-comparison>`               |                                              |* :ref:`highByte() <lang-highbyte>` is             |
|  (greater than or equal to)                |* :ref:`static <lang-static>`                 |  provided, though its use is discouraged.         |
|                                            |                                              |                                                   |
|                                            |* :ref:`volatile <lang-volatile>`             |* :ref:`bitRead() <lang-bitread>`                  |
|**Boolean Operators**                       |                                              |                                                   |
|                                            |* :ref:`const <lang-const>`                   |* :ref:`bitWrite() <lang-bitwrite>`                |
|* :ref:`&& <lang-boolean-and>` (and)        |                                              |                                                   |
|                                            |                                              |* :ref:`bitSet() <lang-bitset>`                    |
|* :ref:`|| <lang-boolean-or>` (or)          |**Utilities**                                 |                                                   |
|                                            |                                              |* :ref:`bitClear() <lang-bitclear>`                |
|* :ref:`\! <lang-boolean-not>` (not)        |* :ref:`sizeof() <lang-sizeof>`               |                                                   |
|                                            |  (``sizeof`` operator)                       |* :ref:`bit() <lang-bit>`                          |
|                                            |                                              |                                                   |
|**Pointer Operators**                       |                                              |                                                   |
|                                            |                                              |**External Interrupts**                            |
|* :ref:`* dereference operator              |                                              |                                                   |
|  <lang-pointer>`                           |                                              |* :ref:`Reference Page <external-interrupts>`      |
|                                            |                                              |                                                   |
|* :ref:`& reference operator                |                                              |* :ref:`attachInterrupt()                          |
|  <lang-pointer>`                           |                                              |  <lang-attachinterrupt>`                          |
|                                            |                                              |                                                   |
|                                            |                                              |* :ref:`detachInterrupt()                          |
|**Bitwise Operators**                       |                                              |  <lang-detachinterrupt>`                          |
|                                            |                                              |                                                   |
|* :ref:`& <lang-bitwisemath-and>`           |                                              |                                                   |
|  (bitwise and)                             |                                              |**Interrupts**                                     |
|                                            |                                              |                                                   |
|* :ref:`| <lang-bitwisemath-or>`            |                                              |* interrupts(): TODO                               |
|  (bitwise or)                              |                                              |                                                   |
|                                            |                                              |* noInterrupts(): TODO                             |
|* :ref:`^ <lang-bitwisemath-xor>`           |                                              |                                                   |
|  (bitwise xor)                             |                                              |                                                   |
|                                            |                                              |**Communication**                                  |
|* :ref:`~ <lang-bitwisemath-not>`           |                                              |                                                   |
|  (bitwise not)                             |                                              |* :ref:`SerialUSB <lang-serialusb>`                |
|                                            |                                              |                                                   |
|* :ref:`\<\< <lang-bitshift>`               |                                              |* :ref:`Serial <lang-serial>`                      |
|  (shift left)                              |                                              |                                                   |
|                                            |                                              |**Looking for something else?**                    |
|* :ref:`>> <lang-bitshift>`                 |                                              |                                                   |
|  (shift right)                             |                                              | See the :ref:`libraries` page for interfacing with|
|                                            |                                              | particular types of hardware.  Maple links        |
|                                            |                                              | against `newlib <http://sourceware.org/newlib/>`_ |
|**Compound Operators**                      |                                              | and allows the use of any of its functions; see   |
|                                            |                                              | its documentation for more details.               |
|* :ref:`++ <lang-increment>`                |                                              |                                                   |
|  (increment)                               |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`- - <lang-increment>`               |                                              |                                                   |
|  (decrement)                               |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`+= <lang-arithmeticcompound>`       |                                              |                                                   |
|  (compound add)                            |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`-=                                  |                                              |                                                   |
|  <lang-arithmeticcompound>` (compound      |                                              |                                                   |
|  subtract)                                 |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`*=                                  |                                              |                                                   |
|  <lang-arithmeticcompound>` (compound      |                                              |                                                   |
|  multiply)                                 |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`/=                                  |                                              |                                                   |
|  <lang-arithmeticcompound>` (compound      |                                              |                                                   |
|  divide)                                   |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`&=                                  |                                              |                                                   |
|  <lang-arithmeticcompound>` (compound      |                                              |                                                   |
|  bitwise and)                              |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`|=                                  |                                              |                                                   |
|  <lang-arithmeticcompound>` (compound      |                                              |                                                   |
|  bitwise or)                               |                                              |                                                   |
|                                            |                                              |                                                   |
|                                            |                                              |                                                   |
+--------------------------------------------+----------------------------------------------+---------------------------------------------------+

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
