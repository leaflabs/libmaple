.. _arduino-sizeof:

sizeof
======

Description
-----------

The sizeof operator returns the number of bytes in a variable type,
or the number of bytes occupied by an array.



Syntax
------

sizeof(variable)



Parameters
----------

variable: any variable type or array (e.g. int, float, byte)



Example code
------------

The sizeof operator is useful for dealing with arrays (such as
strings) where it is convenient to be able to change the size of
the array without breaking other parts of the program.



This program prints out a text string one character at a time. Try
changing the text phrase.



::

    char myStr[] = "this is a test";
    int i;
    
    void setup(){
      Serial.begin(9600);
    }
    
    void loop() { 
      for (i = 0; i < sizeof(myStr) - 1; i++){
        Serial.print(i, DEC);
        Serial.print(" = ");
        Serial.println(myStr[i], BYTE);
      }
    }
    

Note that sizeof returns the total number of bytes. So for larger
variable types such as ints, the for loop would look something like
this.



::

    for (i = 0; i < (sizeof(myInts)/sizeof(int)) - 1; i++) {
      // do something with myInts[i]
    }

