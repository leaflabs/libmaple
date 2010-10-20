.. _arduino-comparison:

Arduino/Processing Language Comparison
======================================

The Arduino language (based on Wiring) is implemented in C/C++, and
therefore has some differences from the Processing language, which
is based on Java.



Arrays
~~~~~~

*Arduino*
*Processing*
int bar[8];
bar[0] = 1;
int[] bar = new int[8];
bar[0] = 1;
int foo[] = { 0, 1, 2 };
int foo[] = { 0, 1, 2 };
*or*
int[] foo = { 0, 1, 2 };


Loops
~~~~~

*Arduino*
*Processing*
int i;
for (i = 0; i < 5; i++) { ... }
for (int i = 0; i < 5; i++) { ... }


Printing
~~~~~~~~

*Arduino*
*Processing*
Serial.println("hello world");
println("hello world");
int i = 5;
Serial.println(i);
int i = 5;
println(i);
int i = 5;
Serial.print("i = ");
Serial.print(i);
Serial.println();
int i = 5;
println("i = " + i);

