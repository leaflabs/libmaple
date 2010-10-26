.. highlight:: cpp

.. _arduino-variables:

Variables
---------

A variable is a way of naming and storing a value for later use by
the program, such as data from a sensor or an intermediate value
used in a calculation.



Declaring Variables
^^^^^^^^^^^^^^^^^^^

Before they are used, all variables have to be declared. Declaring
a variable means defining its type, and optionally, setting an
initial value (initializing the variable). Variables do not have to
be initialized (assigned a value) when they are declared, but it is
often useful.



::

    int inputVariable1;
    int inputVariable2 = 0;     // both are correct



Programmers should consider the size of the numbers they wish to
store in choosing variable types. Variables will
`roll over <#VariableRollover>`_ when the value stored exceeds the
space assigned to store it. See below for an example.



Variable Scope
^^^^^^^^^^^^^^

Another important choice that programmers face is where to declare
variables. The specific place that variables are declared
influences how various functions in a program will *see* the
variable. This is called variable
`scope <http://arduino.cc/en/Reference/Scope>`_.



Initializing Variables
^^^^^^^^^^^^^^^^^^^^^^

Variables may be *initialized* (assigned a starting value) when
they are declared or not. It is always good programming practice
however to double check that a variable has valid data in it,
before it is accessed for some other purpose.



Example:

::

     int calibrationVal = 17;  // declare calibrationVal and set initial value



Variable Rollover
^^^^^^^^^^^^^^^^^

When variables are made to exceed their maximum capacity they "roll
over" back to their minimum capacity, note that this happens in
both directions.



::

       int x
       x = -32,768;
       x = x - 1;       // x now contains 32,767 - rolls over in neg. direction



::

       x = 32,767;
       x = x + 1;       // x now contains -32,768 - rolls over



Using Variables
^^^^^^^^^^^^^^^

Once variables have been declared, they are used by setting the
variable equal to the value one wishes to store with the
`assignment operator <http://arduino.cc/en/Reference/Assignment>`_
(single equal sign). The assignment operator tells the program to
put whatever is on the right side of the equal sign into the
variable on the left side.



::

    inputVariable1 = 7;             // sets the variable named inputVariable1 to 7
    inputVariable2 = analogRead(2); // sets the variable named inputVariable2 to the 
                                    // (digitized) input voltage read from analog pin #2



Examples
^^^^^^^^

::

     int lightSensVal;
       char currentLetter;
       unsigned long speedOfLight = 186000UL;
       char errorMessage = {"choose another option"}; // see string 



Once a variable has been set (assigned a value), you can test its
value to see if it meets certain conditions, or you can use its
value directly. For instance, the following code tests whether the
inputVariable2 is less than 100, then sets a delay based on
inputVariable2 which is a minimum of 100:



::

    if (inputVariable2 < 100)
    {
      inputVariable2 = 100;
    }
    
    delay(inputVariable2);



This example shows all three useful operations with variables. It
tests the variable ( ``if (inputVariable2 < 100)`` ), it sets the
variable if it passes the test ( ``inputVariable2 = 100`` ), and it
uses the value of the variable as an input parameter to the delay()
function (``delay(inputVariable2)`` )



**Style Note:** You should give your variables descriptive names,
so as to make your code more readable. Variable names like
**tiltSensor** or **pushButton** help you (and anyone else reading
your code) understand what the variable represents. Variable names
like **var** or **value**, on the other hand, do little to make
your code readable.



You can name a variable any word that is not already one of the
`keywords <http://arduino.cc/en/Reference/Keywords?action=edit>`_`? <http://arduino.cc/en/Reference/Keywords?action=edit>`_
in Arduino. Avoid beginning variable names with numeral
characters.



Some variable types
^^^^^^^^^^^^^^^^^^^


-  `char <http://arduino.cc/en/Reference/Char>`_
-  `byte <http://arduino.cc/en/Reference/Byte>`_
-  `int <http://arduino.cc/en/Reference/Int>`_
-  `unsigned int <http://arduino.cc/en/Reference/UnsignedInt>`_
-  `long <http://arduino.cc/en/Reference/Long>`_
-  `unsigned long <http://arduino.cc/en/Reference/UnsignedLong>`_
-  `float <http://arduino.cc/en/Reference/Float>`_
-  `double <http://arduino.cc/en/Reference/Double>`_



Variable Scope
^^^^^^^^^^^^^^


-  `Variable Scope <http://arduino.cc/en/Reference/scope>`_


