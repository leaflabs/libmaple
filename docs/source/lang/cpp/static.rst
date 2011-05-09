.. highlight:: cpp

.. _lang-static:

``static``
==========

The ``static`` keyword can be used to create variables that are
visible to only one function. However, unlike local variables that get
created and destroyed every time a function is called, ``static``
variables persist beyond the function call, preserving their data
between function calls.

Variables declared as ``static`` will only be created and initialized
the first time a function is called.

.. note:: This is only one use of the ``static`` keyword in C++.  It
   has some other important uses that are not documented here; consult
   a reliable C++ reference for details.

Example
-------

One use case for ``static`` variables is implementing counters that
last longer than the functions which need them, but shouldn't be
shared to other functions.  Here's an example::

    void setup() {
        SerialUSB.begin();
    }

    void loop() {
        int reading;
        if (timeToReadSensors()) {
            reading = readSensors();
        }
        // do something with reading
    }

    int readSensors() {
        static int numSensorReadings = 0;
        numSensorReadings++;
        if (numSensorReadings % 100 == 0) {
            SerialUSB.print("just got to another 100 sensor readings");
        }
        return analogRead(...);
    }

In this example, the static variable ``numSensorReadings`` is
initialized to zero the first time ``readSensors()`` is called, and
then incremented, so it starts out at one.  Subsequent calls to
``readSensors()`` won't reset ``numSensorReadings`` to zero, because
it was declared ``static``.  Thus, ``numSensorReadings`` is a count of
the number of times that ``readSensors()`` has been called.

.. include:: /arduino-cc-attribution.txt
