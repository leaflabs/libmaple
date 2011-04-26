.. highlight:: c++

.. _language:

==========================
 Maple Language Reference
==========================

The Maple can be programmed in the `Wiring
<http://www.wiring.org.co/reference/>`_ language, which is the same
language used to program the `Arduino <http://arduino.cc/>`_ boards.

.. TODO [0.2.0?] Wiring tutorial

C or C++ programmers curious about the differences between the Wiring
language and C++ may wish to skip to the
:ref:`arduino_c_for_c_hackers`.

.. contents:: Contents
   :local:

.. admonition:: **Looking for Something Else?**

   - See the :ref:`libraries` for extra built-in libraries for dealing
     with different kinds of hardware.

   - If you're looking for something from the C standard library (like
     ``atoi()``, for instance): the :ref:`CodeSourcery GCC compiler
     <arm-gcc>` used to compile your programs is configured to link
     against `newlib <http://sourceware.org/newlib/>`_, and allows the
     use of any of its header files.  However, dynamic memory allocation
     (``malloc()``, etc.) is not available.

   - If you're looking for pointers to low-level details, see this page's
     :ref:`Recommended Reading <language-recommended-reading>`.

.. _language-lang-docs:

Maple Language Reference
------------------------

The following table summarizes the most important core language
features.  An exhaustive index is available at the
:ref:`language-index`.

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
|* :ref:`if/else <lang-if>`                  |                                              |                                                   |
|                                            |* :ref:`true <lang-constants-true>` |         |* :ref:`togglePin() <lang-togglepin>`              |
|* :ref:`for <lang-for>`                     |  :ref:`false <lang-constants-false>`         |                                                   |
|                                            |                                              |* :ref:`toggleLED() <lang-toggleled>`              |
|* :ref:`switch/case <lang-switchcase>`      |* :ref:`Constants                             |                                                   |
|                                            |  <lang-constants>` (:ref:`integers           |* :ref:`isButtonPressed() <lang-isbuttonpressed>`  |
|* :ref:`while <lang-while>`                 |  <lang-constants-integers>`, :ref:`floating  |                                                   |
|                                            |  point <lang-constants-fp>`)                 |* :ref:`waitForButtonPress()                       |
|* :ref:`do...while <lang-dowhile>`          |                                              |  <lang-waitforbuttonpress>`                       |
|                                            |* :ref:`Board-specific values                 |                                                   |
|* :ref:`break <lang-break>`                 |  <lang-board-values>`                        |**Analog I/O**                                     |
|                                            |                                              |                                                   |
|* :ref:`continue <lang-continue>`           |**Data Types**                                |* :ref:`analogRead() <lang-analogread>`            |
|                                            |                                              |                                                   |
|* :ref:`return <lang-return>`               | The size of each datatype, in bytes, is      |* :ref:`pwmWrite() <lang-pwmwrite>`                |
|                                            | given in parentheses where appropriate.      |  (:ref:`analogWrite() <lang-analogwrite>` is      |
|* :ref:`goto <lang-goto>`                   |                                              |  also available, though its use is discouraged)   |
|                                            | *Note*: The ``word`` type is (deliberately)  |                                                   |
|                                            | :ref:`not supported <language-no-word>`.     |                                                   |
|**Further syntax**                          |                                              |**Advanced I/O**                                   |
|                                            |* :ref:`void <lang-void>`                     |                                                   |
|* :ref:`; (semicolon) <lang-semicolon>`     |                                              |* tone(): TODO                                     |
|                                            |* :ref:`boolean <lang-boolean>` (1 byte)      |                                                   |
|* :ref:`{} (curly braces)                   |                                              |* noTone(): TODO                                   |
|  <lang-curly-braces>`                      |* :ref:`char <lang-char>` (1 byte)            |                                                   |
|                                            |                                              |* :ref:`shiftOut() <lang-shiftout>`                |
|* :ref:`// (single-line comment)            |* :ref:`unsigned char                         |                                                   |
|  <lang-comments-singleline>`               |  <lang-unsignedchar>` (1 byte)               |* pulseIn(): TODO                                  |
|                                            |                                              |                                                   |
|* :ref:`/\* \*/ (multi-line comment)        |* :ref:`byte <lang-byte>` (1 byte)            |                                                   |
|  <lang-comments-multiline>`                |                                              |**Time**                                           |
|                                            |* :ref:`int <lang-int>` (4 bytes)             |                                                   |
|* :ref:`#define <lang-define>`              |                                              |* :ref:`millis() <lang-millis>`                    |
|                                            |* :ref:`unsigned int <lang-unsignedint>`      |                                                   |
|* :ref:`#include <lang-include>`            |  (4 bytes)                                   |* :ref:`micros() <lang-micros>`                    |
|                                            |                                              |                                                   |
|                                            |* ``long`` (4 bytes), synonym for :ref:`int   |* :ref:`delay() <lang-delay>`                      |
|**Arithmetic Operators**                    |  <lang-int>`                                 |                                                   |
|                                            |                                              |* :ref:`delayMicroseconds()                        |
|* :ref:`= <lang-assignment>`                |* ``unsigned long`` (4 bytes), synonym for    |  <lang-delaymicroseconds>`                        |
|  (assignment)                              |  :ref:`unsigned int <lang-unsignedint>`      |                                                   |
|                                            |                                              |                                                   |
|* :ref:`+ <lang-arithmetic>` (addition)     |* :ref:`long long <lang-longlong>` (8 bytes)  |**Math**                                           |
|                                            |                                              |                                                   |
|* :ref:`- <lang-arithmetic>`                |* :ref:`unsigned long                         |* :ref:`min() <lang-min>`                          |
|  (subtraction)                             |  long <lang-unsignedlonglong>` (8 bytes)     |                                                   |
|                                            |                                              |* :ref:`max() <lang-max>`                          |
|* :ref:`* <lang-arithmetic>`                |* :ref:`float <lang-float>` (4 bytes)         |                                                   |
|  (multiplication)                          |                                              |* :ref:`abs() <lang-abs>`                          |
|                                            |* :ref:`double <lang-double>` (8 bytes)       |                                                   |
|* :ref:`/ <lang-arithmetic>` (division)     |                                              |* :ref:`constrain() <lang-constrain>`              |
|                                            |* :ref:`strings <lang-string>`                |                                                   |
|* :ref:`% <lang-modulo>` (modulo)           |                                              |* :ref:`map() <lang-map>`                          |
|                                            |* :ref:`arrays <lang-array>`                  |                                                   |
|                                            |                                              |* :ref:`pow() <lang-pow>`                          |
|**Comparison Operators**                    |* :ref:`enum <lang-enum>`                     |                                                   |
|                                            |                                              |* :ref:`sqrt() <lang-sqrt>`                        |
|* :ref:`== <lang-comparison>` (equal to)    |* :ref:`numeric types <lang-built-in-types>`  |                                                   |
|                                            |                                              |                                                   |
|* :ref:`\!= <lang-comparison>`              |**Conversion**                                |**Trigonometry**                                   |
|  (not equal to)                            |                                              |                                                   |
|                                            |* :ref:`char() <lang-charcast>`               |* :ref:`sin() <lang-sin>`                          |
|* :ref:`< <lang-comparison>` (less than)    |                                              |                                                   |
|                                            |* :ref:`byte() <lang-bytecast>`               |* :ref:`cos() <lang-cos>`                          |
|* :ref:`> <lang-comparison>`                |                                              |                                                   |
|  (greater than)                            |* :ref:`int() <lang-intcast>`                 |* :ref:`tan() <lang-tan>`                          |
|                                            |                                              |                                                   |
|* :ref:`<= <lang-comparison>`               |* :ref:`long() <lang-longcast>`               |                                                   |
|  (less than or equal to)                   |                                              |**Random Numbers**                                 |
|                                            |* :ref:`float() <lang-floatcast>`             |                                                   |
|* :ref:`>= <lang-comparison>`               |                                              |* :ref:`randomSeed() <lang-randomseed>`            |
|  (greater than or equal to)                |* :ref:`double() <lang-doublecast>`           |                                                   |
|                                            |                                              |* :ref:`random() <lang-random>`                    |
|                                            |                                              |                                                   |
|**Boolean Operators**                       |**Variable Scope & Qualifiers**               |                                                   |
|                                            |                                              |**Bits and Bytes**                                 |
|* :ref:`&& <lang-boolean-and>` (and)        |* :ref:`variables <lang-variables>`,          |                                                   |
|                                            |  :ref:`scope <lang-variables-scope>`         |* :ref:`lowByte() <lang-lowbyte>`                  |
|* :ref:`|| <lang-boolean-or>` (or)          |                                              |                                                   |
|                                            |* :ref:`static <lang-static>`                 |* :ref:`highByte() <lang-highbyte>` is             |
|* :ref:`\! <lang-boolean-not>` (not)        |                                              |  provided, though its use is discouraged.         |
|                                            |* :ref:`volatile <lang-volatile>`             |                                                   |
|                                            |                                              |* :ref:`bitRead() <lang-bitread>`                  |
|**Pointer Operators**                       |* :ref:`const <lang-const>`                   |                                                   |
|                                            |                                              |* :ref:`bitWrite() <lang-bitwrite>`                |
|* :ref:`* dereference operator              |                                              |                                                   |
|  <lang-pointer>`                           |**Utilities**                                 |* :ref:`bitSet() <lang-bitset>`                    |
|                                            |                                              |                                                   |
|* :ref:`& reference operator                |* :ref:`sizeof() <lang-sizeof>`               |* :ref:`bitClear() <lang-bitclear>`                |
|  <lang-pointer>`                           |                                              |                                                   |
|                                            |                                              |* :ref:`bit() <lang-bit>`                          |
|                                            |                                              |                                                   |
|**Bitwise Operators**                       |                                              |                                                   |
|                                            |                                              |**External Interrupts**                            |
|* :ref:`& <lang-bitwisemath-and>`           |                                              |                                                   |
|  (bitwise and)                             |                                              |* :ref:`Reference Page <external-interrupts>`      |
|                                            |                                              |                                                   |
|* :ref:`| <lang-bitwisemath-or>`            |                                              |* :ref:`attachInterrupt()                          |
|  (bitwise or)                              |                                              |  <lang-attachinterrupt>`                          |
|                                            |                                              |                                                   |
|* :ref:`^ <lang-bitwisemath-xor>`           |                                              |* :ref:`detachInterrupt()                          |
|  (bitwise xor)                             |                                              |  <lang-detachinterrupt>`                          |
|                                            |                                              |                                                   |
|* :ref:`~ <lang-bitwisemath-not>`           |                                              |                                                   |
|  (bitwise not)                             |                                              |**Interrupts**                                     |
|                                            |                                              |                                                   |
|* :ref:`\<\< <lang-bitshift>`               |                                              |* :ref:`interrupts() <lang-interrupts>`            |
|  (shift left)                              |                                              |                                                   |
|                                            |                                              |* :ref:`noInterrupts() <lang-nointerrupts>`        |
|* :ref:`>> <lang-bitshift>`                 |                                              |                                                   |
|  (shift right)                             |                                              |                                                   |
|                                            |                                              |**Communication**                                  |
|                                            |                                              |                                                   |
|**Compound Operators**                      |                                              |* :ref:`SerialUSB <lang-serialusb>`                |
|                                            |                                              |                                                   |
|* :ref:`++ <lang-increment>`                |                                              |* :ref:`Serial <lang-serial>`                      |
|  (increment)                               |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`- - <lang-increment>`               |                                              |                                                   |
|  (decrement)                               |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`+= <lang-compoundarithmetic>`       |                                              |                                                   |
|  (compound add)                            |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`-=                                  |                                              |                                                   |
|  <lang-compoundarithmetic>` (compound      |                                              |                                                   |
|  subtract)                                 |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`*=                                  |                                              |                                                   |
|  <lang-compoundarithmetic>` (compound      |                                              |                                                   |
|  multiply)                                 |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`/=                                  |                                              |                                                   |
|  <lang-compoundarithmetic>` (compound      |                                              |                                                   |
|  divide)                                   |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`&=                                  |                                              |                                                   |
|  <lang-compoundbitwise>` (compound         |                                              |                                                   |
|  bitwise and)                              |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`|=                                  |                                              |                                                   |
|  <lang-compoundbitwise>` (compound         |                                              |                                                   |
|  bitwise or)                               |                                              |                                                   |
|                                            |                                              |                                                   |
|**Keywords**                                |                                              |                                                   |
|                                            |                                              |                                                   |
|* :ref:`C++ Keywords <lang-keywords>`       |                                              |                                                   |
|                                            |                                              |                                                   |
|                                            |                                              |                                                   |
+--------------------------------------------+----------------------------------------------+---------------------------------------------------+

.. _language-assert:

``ASSERT(...)``
---------------

The ``ASSERT()`` function can be very useful for basic program
debugging. It accepts a boolean; for example::

  ASSERT(state == WAIT);

Zero is false and any other number is true. If the boolean is true, the
assertion passes and the program continues as usual. If it is false,
the assertion fails: the program is halted, debug information is
printed to USART2, and the status LED begins to throb in intensity
(it's noticeably different from blinking). The debug information is
printed at 9600 baud and consists of the filename and line number
where the particular assertion failed.

Including assertions in a program increases the program size. When
using libmaple **from the command line only**, they can be disabled by
making the definition ::

  #define DEBUG_LEVEL DEBUG_NONE

before including either wirish.h or libmaple.h. In this case, all
assertions will pass without any lost clock cycles.  Note that this
will **not work in the IDE**; even with this definition, assertions
will still be enabled.

.. _language-missing-features:

Missing Arduino Features
------------------------

.. _langage-missing-analogreference:

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

Unimplemented Arduino Features
------------------------------

The following Wiring/Arduino features are currently unimplemented on
the Maple.

- `tone() <http://www.arduino.cc/en/Reference/Tone>`_
- `noTone() <http://www.arduino.cc/en/Reference/NoTone>`_
- `pulseIn() <http://www.arduino.cc/en/Reference/PulseIn>`_
- `String <http://arduino.cc/en/Reference/StringObject>`_

.. _our reference page: http://leaflabs.com/docs/external-interrupts/

.. _newlib: http://sourceware.org/newlib/

.. _cpp-for-maple:

C++ for Maple
--------------

If you haven't programmed in C++, or if you just need to jog your
memory, you may want to check out our :ref:`Language Index
<language-index>`.  It provides some introductory coverage of
programming ideas and C++.

.. _arduino_c_for_c_hackers:

Note for C/C++ Hackers
----------------------

This is a note for programmers comfortable with C or C++ who want a
better understanding of the differences between C++ and the Wiring
language.  

The good news is that the differences are relatively few; Wiring is
just a thin wrapper around C++.  Some potentially better news is that
the Maple can be programmed using a :ref:`standard Unix toolchain
<unix-toolchain>`, so if you'd rather stick with :command:`gcc`,
:command:`make`, and friends, you can.  If you're using the Unix
toolchain and want to skip past the Wiring conveniences and get
straight to registers, you are encouraged to move on to the
:ref:`libmaple` documentation.

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
``main`` method (in fact, we currently forbid you from doing so).
Instead, you are required to define two functions, ``setup`` and
``loop``, with type signatures ::

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
<http://www.retrologic.com/jargon/B/Bad-and-Wrong.html>`_.  In the
future, we'll do this correctly, using a better parser.  Until then,
you have our apologies.)  The order in which the individual sketch
files are concatenated is not defined; it is unwise to write code that
depends on a particular ordering.

The concatenated sketch files are then appended onto a file which
includes `WProgram.h
<https://github.com/leaflabs/libmaple/blob/master/wirish/WProgram.h>`_
(which includes the wirish and libmaple libraries, and declares
``setup()`` and ``loop()``), and then provides declarations for all
the function definitions found in the previous step.  At this point,
we have a file that is a valid C++ translation unit, but lacks
``main()``.  The final step of compilation provides ``main()``, which
behaves roughly like::

  int main(void) {
    // Call libmaple's built-in initialization routines
    init();

    // Perform the user's initialization
    setup();

    // Call user loop() forever.
    while (true) {
        loop(); 
    }
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
    togglePin(the_pin);
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
    togglePin(the_pin);
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
    togglePin(the_pin);
  }

  int choose_a_pin(void);

  int choose_a_pin() {
     return random(5, 15);
  }

  int main() {
    init();
    setup();
    while (true) loop();
  }

.. _language-recommended-reading:

Recommended Reading
-------------------

* :ref:`libmaple Documentation <libmaple>`
* Your board's :ref:`Board Hardware Documentation <index-boards>` page
* ST Documentation:
    * Reference Manual `RM0008
      <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_
      (PDF).  This is the most important reference work on the STM32
      line, and covers the low-level hardware capabilities and
      interfaces in great detail.
    * `Programming Manual
      <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_
      (PDF). This is an assembly language and register reference for
      the STM32 line.
* ARM Documentation:
    * `Cortex-M3 Technical Reference Manual, Revision r1p1
      <http://infocenter.arm.com/help/topic/com.arm.doc.ddi0337e/DDI0337E_cortex_m3_r1p1_trm.pdf>`_
      (PDF).  This ARM manual specifies much of the the Cortex M3
      Architecture, including instruction timings.
* `newlib Documentation <http://sourceware.org/newlib/>`_
