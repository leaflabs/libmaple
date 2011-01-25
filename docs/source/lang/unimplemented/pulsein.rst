.. _lang-pulsein:

pulseIn()
=========

Description
-----------

Reads a pulse (either HIGH or LOW) on a pin. For example, if
**value** is **HIGH**, **pulseIn()** waits for the pin to go
**HIGH**, starts timing, then waits for the pin to go **LOW** and
stops timing. Returns the length of the pulse in microseconds.
Gives up and returns 0 if no pulse starts within a specified time
out.



The timing of this function has been determined empirically and
will probably show errors in longer pulses. Works on pulses from 10
microseconds to 3 minutes in length.



Syntax
------

pulseIn(pin, value)
pulseIn(pin, value, timeout)



Parameters
----------

pin: the number of the pin on which you want to read the pulse.
(*int*)



value: type of pulse to read: either
`HIGH <http://arduino.cc/en/Reference/Constants>`_ or
`LOW <http://arduino.cc/en/Reference/Constants>`_. (*int*)



timeout (optional): the number of microseconds to wait for the
pulse to start; default is one second (*unsigned long*)



Returns
-------

the length of the pulse (in microseconds) or 0 if no pulse started
before the timeout (*unsigned long*)



Example
-------

::



    int pin = 7;
    unsigned long duration;

    void setup()
    {
      pinMode(pin, INPUT);
    }

    void loop()
    {
      duration = pulseIn(pin, HIGH);
    }




.. include:: /lang/cc-attribution.txt
