.. highlight:: cpp

.. _lang-break:

``break``
=========

``break`` is used to exit from a :ref:`while <lang-while>`\ ,
:ref:`for <lang-for>`\ , or :ref:`do/while <lang-dowhile>` loop,
bypassing the normal loop condition.  It is also used to exit from a
:ref:`switch <lang-switchcase>` statement.


Example
-------

::

    for (x = 0; x < 255; x ++)
    {
        digitalWrite(PWMpin, x);
        sens = analogRead(sensorPin);
        if (sens > threshold){      // bail out on sensor detect
           x = 0;
           // this line of code means that we'll immediately exit
           // from the "for" loop:
           break;
        }
        delay(50);
    }

.. include:: /arduino-cc-attribution.txt
