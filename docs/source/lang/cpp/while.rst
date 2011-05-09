.. highlight:: cpp

.. _lang-while:

``while``
=========

Syntax
------

::

    while (expression) {
      // block of code
    }

Description
-----------

``while`` loops will repeat the statements inside their associated
block of code until the expression inside the parentheses becomes
:ref:`false <lang-constants-false>`. Something must change the tested
expressions' value, or the ``while`` loop will never exit.  This could
be in your code, such as an incremented variable, or an external
condition, such as testing a sensor.

Example
-------

::

    var = 0;
    while(var < 200) {
      // do something repetitive 200 times
      var++;
    }

.. include:: /arduino-cc-attribution.txt
