.. highlight:: cpp

.. _lang-enabledebugports:

enableDebugPorts()
==================

Used to enable the JTAG and Serial Wire debugging ports.

Library Documentation
---------------------

.. doxygenfunction:: enableDebugPorts

Example
-------

 ::

    void setup() {
        enableDebugPorts();
        // Now you can debug using JTAG and SW-Debug
    }

    void loop() {
    }

See Also
--------

* :ref:`lang-disabledebugports`
