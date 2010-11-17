.. _arduino-map:

map(value, fromLow, fromHigh, toLow, toHigh)
============================================

Description
-----------

Re-maps a number from one range to another. That is, a **value** of
**fromLow** would get mapped to **toLow**, a value of **fromHigh**
to **toHigh**, values in-between to values in-between, etc.



Does not constrain values to within the range, because out-of-range
values are sometimes intended and useful. The constrain() function
may be used either before or after this function, if limits to the
ranges are desired.



Note that the "lower bounds" of either range may be larger or
smaller than the "upper bounds" so the map() function may be used
to reverse a range of numbers, for example



``y = map(x, 1, 50, 50, 1);``



The function also handles negative numbers well, so that this
example



``y = map(x, 1, 50, 50, -100);``



is also valid and works well.



The map() function uses integer math so will not generate
fractions, when the math might indicate that it should do so.
Fractional remainders are truncated, and are not rounded or
averaged.



Parameters
----------

value: the number to map



fromLow: the lower bound of the value's current range



fromHigh: the upper bound of the value's current range



toLow: the lower bound of the value's target range



toHigh: the upper bound of the value's target range



Returns
-------

The mapped value.



Example
-------

::

    /* Map an analog value to 8 bits (0 to 255) */
    void setup() {}
    
    void loop()
    {
      int val = analogRead(0);
      val = map(val, 0, 1023, 0, 255);
      analogWrite(9, val);
    }



Appendix
~~~~~~~~

For the mathematically inclined, here's the whole function



::

    long map(long x, long in_min, long in_max, long out_min, long out_max)
    {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }



See Also
--------


-  `constrain <http://arduino.cc/en/Reference/Constrain>`_\ ()


.. include:: cc-attribution.txt