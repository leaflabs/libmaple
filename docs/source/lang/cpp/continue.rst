.. highlight:: cpp

.. _lang-continue:

``continue``
============

The ``continue`` keyword skips the rest of the current iteration of a
:ref:`while <lang-while>`\ , :ref:`for <lang-for>`\ , or
:ref:`do/while <lang-dowhile>` loop. It continues by checking the
conditional expression of the loop, and proceeding with any subsequent
iterations.

Example
-------

::


    for (x = 0; x < 255; x ++) {
        if (x > 40 && x < 120) {      // create jump in values
            continue;   // skips the next two lines and goes to the
                        // beginning of the loop, with the next value of x
        }

        digitalWrite(PWMpin, x);
        delay(50);
    }

.. include:: /arduino-cc-attribution.txt
