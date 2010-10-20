.. _arduino-else:

if / else
=========

**if/else** allows greater control over the flow of code than the
basic **if** statement, by allowing multiple tests to be grouped
together. For example, an analog input could be tested and one
action taken if the input was less than 500, and another action
taken if the input was 500 or greater. The code would look like
this:



::

    if (pinFiveInput < 500)
    {
      // action A
    }
    else
    {
      // action B
    }



**else** can proceed another **if** test, so that multiple,
mutually exclusive tests can be run at the same time.



Each test will proceed to the next one until a true test is
encountered. When a true test is found, its associated block of
code is run, and the program then skips to the line following the
entire if/else construction. If no test proves to be true, the
default **else** block is executed, if one is present, and sets the
default behavior.



Note that an **else if** block may be used with or without a
terminating **else** block and vice versa. An unlimited number of
such **else if** branches is allowed.



::

    if (pinFiveInput < 500)
    {
      // do Thing A
    }
    else if (pinFiveInput >= 1000)
    {
      // do Thing B
    }
    else
    {
      // do Thing C
    }

Another way to express branching, mutually exclusive tests, is with
the `switch case <http://arduino.cc/en/Reference/SwitchCase>`_
statement.



See also:
---------

`switch case <http://arduino.cc/en/Reference/SwitchCase>`_

