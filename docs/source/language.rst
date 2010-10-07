.. _language:

==========================
 Maple Language Reference
==========================

The Maple can be programmed in a mostly-complete subset of the the
`Wiring <http://www.wiring.org.co/reference/>`_ language, which is the
same language used to program the `Arduino <http://arduino.cc/>`_
boards.  The entire language will be supported in a future release.
Please see the extensive `language reference
<http://arduino.cc/en/Reference/HomePage>`_ on the Arduino webpage for
more information, or follow a direct link below.

Unique Maple Additions
----------------------

``ASSERT(...)``
    The ``ASSERT()`` function can be very useful for basic program
    debugging. The function accepts a boolean; for example:

      ``ASSERT(state == WAIT);``

    zero is false and any other number is true. If the boolean is true
    the assertion passes and the program continues as usual. If it is
    false, the assertion fails: the program is halted, debug
    information is printed to USART2, and the status LED begins to
    throb in intensity (it's noticeably different from blinking). The
    debug information is printed at 9600 baud and consists of the
    filename and line number where the particular assertion failed.

    Including assertions in a program increases the program size. When
    using libmaple **from the command line only**, they can be
    disabled by making the definition

      ``#define DEBUG_LEVEL DEBUG_NONE``

    before including either wirish or libmaple. In this case, all
    assertions will pass without any lost clock cycles.  Note that
    this will **not work in the IDE**; even with this definition,
    assertions will still be enabled.

Arduino Documentation Links
---------------------------

(This table was copied from http://arduino.cc/en/Reference/Extended).

+------------------------------------+------------------------------------+-----------------------------------------+
| Structure                          | Variables                          | Functions                               |
|                                    |                                    |                                         |
+====================================+====================================+=========================================+
|                                    |**Constants**                       |**Digital I/O**                          |
|* `setup()`_                        |                                    |                                         |
|                                    |* `HIGH`_ | `LOW`_                  |* `pinMode()`_                           |
|* `loop()`_                         |                                    |                                         |
|                                    |* `INPUT`_ | `OUTPUT`_              |* `digitalWrite()`_                      |
|                                    |                                    |                                         |
|**Control Structures**              |* `true`_ | `false`_                |* `digitalRead()`_                       |
|                                    |                                    |                                         |
|* `if`_                             |* `integer constants`_              |                                         |
|                                    |                                    |**Analog I/O**                           |
|* `if...else`_                      |* `floating point constants`_       |                                         |
|                                    |                                    |* `analogReference()`_                   |
|* `for`_                            |                                    |                                         |
|                                    |**Data Types**                      |* `analogRead()`_                        |
|* `switch/case`_                    |                                    |                                         |
|                                    |* `void`_                           |* `analogWrite()`_ - PWM                 |
|* `while`_                          |                                    |                                         |
|                                    |* `boolean`_                        |                                         |
|* `do...while`_                     |                                    |**Advanced I/O**                         |
|                                    |* `char`_                           |                                         |
|* `break`_                          |                                    |* `tone()`_                              |
|                                    |* `unsigned char`_                  |                                         |
|* `continue`_                       |                                    |* `noTone()`_                            |
|                                    |* `byte`_                           |                                         |
|* `return`_                         |                                    |* `shiftOut()`_                          |
|                                    |* `int`_                            |                                         |
|* `goto`_                           |                                    |* `pulseIn()`_                           |
|                                    |* `unsigned int`_                   |                                         |
|                                    |                                    |                                         |
|**Further syntax**                  |* `word`_                           |**Time**                                 |
|                                    |                                    |                                         |
|* `;`_ (semicolon)                  |* `long`_                           |* `millis()`_                            |
|                                    |                                    |                                         |
|* `{}`_ (curly braces)              |* `unsigned long`_                  |* `micros()`_                            |
|                                    |                                    |                                         |
|* `//`_ (single line comment)       |* `float`_                          |* `delay()`_                             |
|                                    |                                    |                                         |
|* `/\* \*/`_ (multi-line comment)   |* `double`_                         |* `delayMicroseconds()`_                 |
|                                    |                                    |                                         |
|* `#define`_                        |* `string`_                         |                                         |
|                                    |                                    |**Math**                                 |
|* `#include`_                       |* `array`_                          |                                         |
|                                    |                                    |* `min()`_                               |
|                                    |                                    |                                         |
|**Arithmetic Operators**            |**Conversion**                      |* `max()`_                               |
|                                    |                                    |                                         |
|* `=`_ (assignment operator)        |* `char()`_                         |* `abs()`_                               |
|                                    |                                    |                                         |
|* `+`_ (addition)                   |* `byte()`_                         |* `constrain()`_                         |
|                                    |                                    |                                         |
|* `-`_ (subtraction)                |* `int()`_                          |* `map()`_                               |
|                                    |                                    |                                         |
|* `*`_ (multiplication)             |* `word()`_                         |* `pow()`_                               |
|                                    |                                    |                                         |
|* `/`_ (division)                   |* `long()`_                         |* `sqrt()`_                              |
|                                    |                                    |                                         |
|* `%`_ (modulo)                     |* `float()`_                        |                                         |
|                                    |                                    |**Trigonometry**                         |
|                                    |                                    |                                         |
|**Comparison Operators**            |**Variable Scope & Qualifiers**     |* `sin()`_                               |
|                                    |                                    |                                         |
|* `==`_ (equal to)                  |* `variable scope`_                 |* `cos()`_                               |
|                                    |                                    |                                         |
|* `!=`_ (not equal to)              |* `static`_                         |* `tan()`_                               |
|                                    |                                    |                                         |
|* `<`_ (less than)                  |* `volatile`_                       |                                         |
|                                    |                                    |**Random Numbers**                       |
|* `>`_ (greater than)               |* `const`_                          |                                         |
|                                    |                                    |* `randomSeed()`_                        |
|* `<=`_ (less than or equal to)     |                                    |                                         |
|                                    |**Utilities**                       |* `random()`_                            |
|* `>=`_ (greater than or equal to)  |                                    |                                         |
|                                    |* `sizeof()`_ (sizeof operator)     |                                         |
|                                    |                                    |**Bits and Bytes**                       |
|**Boolean Operators**               |                                    |                                         |
|                                    |                                    |* `lowByte()`_                           |
|* `&&`_ (and)                       |                                    |                                         |
|                                    |                                    |* `highByte()`_                          |
|* `||`_ (or)                        |                                    |                                         |
|                                    |                                    |* `bitRead()`_                           |
|* `!`_ (not)                        |                                    |                                         |
|                                    |                                    |* `bitWrite()`_                          |
|                                    |                                    |                                         |
|**Pointer Access Operators**        |                                    |* `bitSet()`_                            |
|                                    |                                    |                                         |
|* `* dereference operator`_         |                                    |* `bitClear()`_                          |
|                                    |                                    |                                         |
|* `& reference operator`_           |                                    |* `bit()`_                               |
|                                    |                                    |                                         |
|                                    |                                    |                                         |
|**Bitwise Operators**               |                                    |**External Interrupts**                  |
|                                    |                                    |                                         |
|* `&`_ (bitwise and)                |                                    |For more information on external         |
|                                    |                                    |interrupts on Maple, see                 |
|* `|`_ (bitwise or)                 |                                    |`our reference page`_.                   |
|                                    |                                    |                                         |
|* `^`_ (bitwise xor)                |                                    |                                         |
|                                    |                                    |* `attachInterrupt()`_                   |
|* `~`_ (bitwise not)                |                                    |                                         |
|                                    |                                    |* `detachInterrupt()`_                   |
|* `<<`_ (shift left)                |                                    |                                         |
|                                    |                                    |                                         |
|* `>>`_ (shift right)               |                                    |**Interrupts**                           |
|                                    |                                    |                                         |
|                                    |                                    |* `interrupts()`_                        |
|**Compound Operators**              |                                    |                                         |
|                                    |                                    |* `noInterrupts()`_                      |
|* `++`_ (increment)                 |                                    |                                         |
|                                    |                                    |                                         |
|* `- -`_ (decrement)                |                                    |**Communication**                        |
|                                    |                                    |                                         |
|* `+=`_ (compound addition)         |                                    |* `Serial`_                              |
|                                    |                                    |                                         |
|* `-=`_ (compound subtraction)      |                                    |Looking for something else? See the      |
|                                    |                                    |:ref:`libraries` page for interfacing    |
|* `*=`_ (compound multiplication)   |                                    |with particular types of hardware. Try   |
|                                    |                                    |the list of `community-contributed       |
|* `/=`_ (compound division)         |                                    |code`_.  Maple links against `newlib`_   |
|                                    |                                    |and allows the use of any of its         |
|* `&=`_ (compound bitwise and)      |                                    |functions; see its documentation for more|
|                                    |                                    |details.                                 |
|* `|=`_ (compound bitwise or)       |                                    |                                         |
|                                    |                                    |                                         |
+------------------------------------+------------------------------------+-----------------------------------------+

.. _setup(): http://arduino.cc/en/Reference/Setup
.. _loop(): http://arduino.cc/en/Reference/Loop
.. _if: http://arduino.cc/en/Reference/If
.. _if...else: http://arduino.cc/en/Reference/Else
.. _for: http://arduino.cc/en/Reference/For
.. _switch/case: http://arduino.cc/en/Reference/SwitchCase
.. _while: http://arduino.cc/en/Reference/While
.. _do...while: http://arduino.cc/en/Reference/DoWhile
.. _break: http://arduino.cc/en/Reference/Break
.. _continue: http://arduino.cc/en/Reference/Continue
.. _return: http://arduino.cc/en/Reference/Return
.. _goto: http://arduino.cc/en/Reference/Goto

.. _;: http://arduino.cc/en/Reference/SemiColon
.. _{}: http://arduino.cc/en/Reference/Braces
.. _//: http://arduino.cc/en/Reference/Comments
.. _/\* \*/: http://arduino.cc/en/Reference/Comments
.. _#define: http://arduino.cc/en/Reference/Define
.. _#include: http://arduino.cc/en/Reference/Include

.. _=: http://arduino.cc/en/Reference/Assignment
.. _+: http://arduino.cc/en/Reference/Arithmetic
.. _-: http://arduino.cc/en/Reference/Arithmetic
.. _*: http://arduino.cc/en/Reference/Arithmetic
.. _/: http://arduino.cc/en/Reference/Arithmetic
.. _%: http://arduino.cc/en/Reference/Modulo

.. _==: http://arduino.cc/en/Reference/If
.. _!=: http://arduino.cc/en/Reference/If
.. _<: http://arduino.cc/en/Reference/If
.. _>: http://arduino.cc/en/Reference/If
.. _<=: http://arduino.cc/en/Reference/If
.. _>=: http://arduino.cc/en/Reference/If

.. _&&: http://arduino.cc/en/Reference/Boolean
.. _||: http://arduino.cc/en/Reference/Boolean
.. _!: http://arduino.cc/en/Reference/Boolean

.. _* dereference operator: http://arduino.cc/en/Reference/Pointer
.. _& reference operator: http://arduino.cc/en/Reference/Pointer

.. _&: http://arduino.cc/en/Reference/BitwiseAnd
.. _|: http://arduino.cc/en/Reference/BitwiseAnd
.. _^: http://arduino.cc/en/Reference/BitwiseAnd
.. _~: http://arduino.cc/en/Reference/BitwiseXorNot
.. _<<: http://arduino.cc/en/Reference/Bitshift
.. _>>: http://arduino.cc/en/Reference/Bitshift

.. _++: http://arduino.cc/en/Reference/Increment
.. FIXME can't freaking get two hyphens to show up! sphinx turns "--"
.. into an endash, whatever, fine, try to escape like "\-\-", that
.. ALSO becomes endash (!@#$), damn, well, maybe someone else is
.. eating my slash, try "\\-\\-", nope, that turns into a motherfing
.. \-\-. i hate everything.
.. _- -: http://arduino.cc/en/Reference/Increment
.. _+=: http://arduino.cc/en/Reference/IncrementCompound
.. _-=: http://arduino.cc/en/Reference/IncrementCompound
.. _*=: http://arduino.cc/en/Reference/IncrementCompound
.. _/=: http://arduino.cc/en/Reference/IncrementCompound
.. _&=: http://arduino.cc/en/Reference/BitwiseCompound
.. _|=: http://arduino.cc/en/Reference/BitwiseCompound

.. _HIGH: http://arduino.cc/en/Reference/Constants
.. _LOW: http://arduino.cc/en/Reference/Constants
.. _INPUT: http://arduino.cc/en/Reference/Constants
.. _OUTPUT: http://arduino.cc/en/Reference/Constants
.. _true: http://arduino.cc/en/Reference/Constants
.. _false: http://arduino.cc/en/Reference/Constants
.. _integer constants: http://arduino.cc/en/Reference/IntegerConstants
.. _floating point constants: http://arduino.cc/en/Reference/Fpconstants

.. _void: http://arduino.cc/en/Reference/Void
.. _boolean: http://arduino.cc/en/Reference/BooleanVariables
.. _char: http://arduino.cc/en/Reference/Char
.. _unsigned char: http://arduino.cc/en/Reference/UnsignedChar
.. _byte: http://arduino.cc/en/Reference/Byte
.. _int: http://arduino.cc/en/Reference/Int
.. _unsigned int: http://arduino.cc/en/Reference/UnsignedInt
.. _word: http://arduino.cc/en/Reference/Word
.. _long: http://arduino.cc/en/Reference/Long
.. _unsigned long: http://arduino.cc/en/Reference/UnsignedLong
.. _float: http://arduino.cc/en/Reference/Float
.. _double: http://arduino.cc/en/Reference/Double
.. _string: http://arduino.cc/en/Reference/String
.. _array: http://arduino.cc/en/Reference/Array

.. _char(): http://arduino.cc/en/Reference/CharCast
.. _byte(): http://arduino.cc/en/Reference/ByteCast
.. _int(): http://arduino.cc/en/Reference/IntCast
.. _word(): http://arduino.cc/en/Reference/WordCast
.. _long(): http://arduino.cc/en/Reference/LongCast
.. _float(): http://arduino.cc/en/Reference/FloatCast

.. _variable scope: http://arduino.cc/en/Reference/Scope
.. _static: http://arduino.cc/en/Reference/Static
.. _volatile: http://arduino.cc/en/Reference/Volatile
.. _const: http://arduino.cc/en/Reference/Const
.. _sizeof(): http://arduino.cc/en/Reference/Sizeof

.. _pinMode(): http://arduino.cc/en/Reference/PinMode
.. _digitalWrite(): http://arduino.cc/en/Reference/DigitalWrite
.. _digitalRead(): http://arduino.cc/en/Reference/DigitalRead

.. _analogReference(): http://arduino.cc/en/Reference/AnalogReference
.. _analogRead(): http://arduino.cc/en/Reference/AnalogRead
.. _analogWrite(): http://arduino.cc/en/Reference/AnalogWrite

.. _tone(): http://arduino.cc/en/Reference/Tone
.. _noTone(): http://arduino.cc/en/Reference/NoTone
.. _shiftOut(): http://arduino.cc/en/Reference/ShiftOut
.. _pulseIn(): http://arduino.cc/en/Reference/PulseIn

.. _millis(): http://arduino.cc/en/Reference/Millis
.. _micros(): http://arduino.cc/en/Reference/Micros
.. _delay(): http://arduino.cc/en/Reference/Delay
.. _delayMicroseconds(): http://arduino.cc/en/Reference/DelayMicroseconds

.. _min(): http://arduino.cc/en/Reference/Min
.. _max(): http://arduino.cc/en/Reference/Max
.. _abs(): http://arduino.cc/en/Reference/Abs
.. _constrain(): http://arduino.cc/en/Reference/Constrain

.. _map(): http://arduino.cc/en/Reference/Map
.. _pow(): http://arduino.cc/en/Reference/Pow
.. _sqrt(): http://arduino.cc/en/Reference/Sqrt

.. _sin(): http://arduino.cc/en/Reference/Sin
.. _cos(): http://arduino.cc/en/Reference/Cos
.. _tan(): http://arduino.cc/en/Reference/Tan

.. _randomSeed(): http://arduino.cc/en/Reference/RandomSeed
.. _random(): http://arduino.cc/en/Reference/Random

.. _lowByte(): http://arduino.cc/en/Reference/LowByte
.. _highByte(): http://arduino.cc/en/Reference/HighByte
.. _bitRead(): http://arduino.cc/en/Reference/BitRead
.. _bitWrite(): http://arduino.cc/en/Reference/BitWrite
.. _bitSet(): http://arduino.cc/en/Reference/BitSet
.. _bitClear(): http://arduino.cc/en/Reference/BitClear
.. _bit(): http://arduino.cc/en/Reference/Bit

.. _our reference page: http://leaflabs.com/docs/external-interrupts/
.. _attachInterrupt(): http://arduino.cc/en/Reference/AttachInterrupt
.. _detachInterrupt(): http://arduino.cc/en/Reference/DetachInterrupt

.. _interrupts(): http://arduino.cc/en/Reference/Interrupts
.. _noInterrupts(): http://arduino.cc/en/Reference/NoInterrupts

.. _Serial: http://arduino.cc/en/Reference/Serial
.. _community-contributed code: http://www.arduino.cc/playground/Main/GeneralCodeLibrary
.. _newlib: http://sourceware.org/newlib/

Recommended Reading
-------------------

* `newlib Documentation <http://sourceware.org/newlib/>`_
* STMicro documentation for STM32F103RB microcontroller:

    * `All documents <http://www.st.com/mcu/devicedocs-STM32F103RB-110.html>`_
    * `Datasheet (pdf) <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_
    * `Reference Manual (pdf) <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_
    * `Programming Manual (pdf) <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_ (assembly language and register reference)
