.. _arduino-dowhile:

do - while
==========

The **do** loop works in the same manner as the **while** loop,
with the exception that the condition is tested at the end of the
loop, so the **do** loop will *always* run at least once.



::

    do
    {
        // statement block
    } while (test condition);



Example
-------

::

    do
    {
      delay(50);          // wait for sensors to stabilize
      x = readSensors();  // check the sensors
    
    } while (x < 100);


