.. _arduino-bitwiseand:

Bitwise AND (&), Bitwise OR (\|), Bitwise XOR (^)
=================================================

Bitwise AND (&)
---------------

The bitwise operators perform their calculations at the bit level
of variables. They help solve a wide range of common programming
problems. Much of the material below is from an excellent tutorial
on bitwise math wihch may be found
`here. <http://www.arduino.cc/playground/Code/BitMath>`_



Description and Syntax
----------------------

Below are descriptions and syntax for all of the operators. Further
details may be found in the referenced tutorial.



Bitwise AND (&)
---------------

The bitwise AND operator in C++ is a single ampersand, &, used
between two other integer expressions. Bitwise AND operates on each
bit position of the surrounding expressions independently,
according to this rule: if both input bits are 1, the resulting
output is 1, otherwise the output is 0. Another way of expressing
this is:



::

        0  0  1  1    operand1
        0  1  0  1    operand2
        ----------
        0  0  0  1    (operand1 & operand2) - returned result



In Arduino, the type int is a 16-bit value, so using & between two
int expressions causes 16 simultaneous AND operations to occur. In
a code fragment like:



::

        int a =  92;    // in binary: 0000000001011100
        int b = 101;    // in binary: 0000000001100101
        int c = a & b;  // result:    0000000001000100, or 68 in decimal.



Each of the 16 bits in a and b are processed by using the bitwise
AND, and all 16 resulting bits are stored in c, resulting in the
value 01000100 in binary, which is 68 in decimal.



One of the most common uses of bitwise AND is to select a
particular bit (or bits) from an integer value, often called
masking. See below for an example



Bitwise OR (\|)
---------------

The bitwise OR operator in C++ is the vertical bar symbol, \|. Like
the & operator, \| operates independently each bit in its two
surrounding integer expressions, but what it does is different (of
course). The bitwise OR of two bits is 1 if either or both of the
input bits is 1, otherwise it is 0. In other words:



::

        0  0  1  1    operand1
        0  1  0  1    operand2
        ----------
        0  1  1  1    (operand1 | operand2) - returned result



Here is an example of the bitwise OR used in a snippet of C++
code:



::

        int a =  92;    // in binary: 0000000001011100
        int b = 101;    // in binary: 0000000001100101
        int c = a | b;  // result:    0000000001111101, or 125 in decimal.



Example Program
---------------

A common job for the bitwise AND and OR operators is what
programmers call Read-Modify-Write on a port. On microcontrollers,
a port is an 8 bit number that represents something about the
condition of the pins. Writing to a port controls all of the pins
at once.



PORTD is a built-in constant that refers to the output states of
digital pins 0,1,2,3,4,5,6,7. If there is 1 in an bit position,
then that pin is HIGH. (The pins already need to be set to outputs
with the pinMode() command.) So if we write ``PORTD = B00110001;``
we have made pins 2,3 & 7 HIGH. One slight hitch here is that we
*may* also have changeed the state of Pins 0 & 1, which are used by
the Arduino for serial communications so we may have interfered
with serial communication.



::

         Our algorithm for the program is:


-  Get PORTD and clear out only the bits corresponding to the pins
   we wish to control (with bitwise AND).
-  Combine the modified PORTD value with the new value for the pins
   under control (with biwise OR).



::

    int i;     // counter variable
    int j;
    
    void setup(){
    DDRD = DDRD | B11111100; // set direction bits for pins 2 to 7, leave 0 and 1 untouched (xx | 00 == xx)
    // same as pinMode(pin, OUTPUT) for pins 2 to 7
    Serial.begin(9600);
    }
    
    void loop(){
    for (i=0; i<64; i++){
    
    PORTD = PORTD & B00000011;  // clear out bits 2 - 7, leave pins 0 and 1 untouched (xx & 11 == xx)
    j = (i << 2);               // shift variable up to pins 2 - 7 - to avoid pins 0 and 1
    PORTD = PORTD | j;          // combine the port information with the new information for LED pins
    Serial.println(PORTD, BIN); // debug to show masking
    delay(100);
       }
    }



Bitwise XOR (^)
---------------

There is a somewhat unusual operator in C++ called bitwise
EXCLUSIVE OR, also known as bitwise XOR. (In English this is
usually pronounced "eks-or".) The bitwise XOR operator is written
using the caret symbol ^. This operator is very similar to the
bitwise OR operator \|, only it evaluates to 0 for a given bit
position when both of the input bits for that position are 1:



::

        0  0  1  1    operand1
        0  1  0  1    operand2
        ----------
        0  1  1  0    (operand1 ^ operand2) - returned result



Another way to look at bitwise XOR is that each bit in the result
is a 1 if the input bits are different, or 0 if they are the same.



Here is a simple code example:



::

        int x = 12;     // binary: 1100
        int y = 10;     // binary: 1010
        int z = x ^ y;  // binary: 0110, or decimal 6



The ^ operator is often used to toggle (i.e. change from 0 to 1, or
1 to 0) some of the bits in an integer expression. In a bitwise OR
operation if there is a 1 in the mask bit, that bit is inverted; if
there is a 0, the bit is not inverted and stays the same. Below is
a program to blink digital pin 5.



::

    // Blink_Pin_5
    // demo for Exclusive OR
    void setup(){
    DDRD = DDRD | B00100000; // set digital pin five as OUTPUT 
    Serial.begin(9600);
    }
    
    void loop(){
    PORTD = PORTD ^ B00100000;  // invert bit 5 (digital pin 5), leave others untouched
    delay(100);
    }



See Also


-  `&& <http://arduino.cc/en/Reference/Boolean>`_ (Boolean AND)
-  `\|\| <http://arduino.cc/en/Reference/Boolean>`_ (Boolean OR)

