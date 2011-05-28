.. highlight:: cpp

.. _lang-disabledebugports:

disableDebugPorts()
===================

Used to disable the JTAG and Serial Wire debugging ports.

Library Documentation
---------------------

.. doxygenfunction:: disableDebugPorts

Example
-------

 ::

    void setup() {
        disableDebugPorts();
    }

    void loop() {
        // Now you can use the debug port pins (the pins on the JTAG
        // header on the Maple) as ordinary pins.
    }

See Also
--------

- :ref:`lang-enabledebugports`
- :ref:`Important erratum on Maple pin 43 <maple-nrst-pb4>`
