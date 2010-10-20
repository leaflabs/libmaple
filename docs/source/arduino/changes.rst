.. _arduino-changes:

Changes
=======

This page lists major changes to the Arduino core, libraries, and
environment. For details, see the
`release notes <http://arduino.cc/en/Main/ReleaseNotes>`_.



Changes in Arduino 0017
~~~~~~~~~~~~~~~~~~~~~~~


-  **Environment**: The code base for the Arduino development
   environment was largely re-written to bring it back into sync with
   Processing (1.0.3). The main differences include support for
   multiple sketch windows open simultaneously and a dedicated window
   for the serial monitor.
   

-  **Icons**: The icons and about images were updated.
   

-  **Arduino.app**: The Mac OS X version of Arduino is now a .app
   file packaged in a .dmg.
   

-  **Libraries**: Support was added for third-party libraries in
   the *SKETCHBOOK*/libraries directory. This allows user-installed
   libraries to persist across upgrades of the Arduino software.
   

-  **Servo**: The servo library was rewritten to allow support for
   up to 12 servos (on any pins) and up to 48 on the Mega.
   

-  **LiquidCrystal**: The begin(), cursor(), noCursor(), blink(),
   noBlink(), display(), noDisplay(), scrollDisplayLeft(),
   scrollDisplayRight(), autoscroll(), noAutoscroll(), leftToRight(),
   rightToLeft(), and createChar() functions were added.



Changes in Arduino 0016
~~~~~~~~~~~~~~~~~~~~~~~


-  New functions for writing a string, write(str), or buffer,
   write(buf, len), were added to the Print, Serial, and Ethernet
   library Client and Server classes.



Changes in Arduino 0015
~~~~~~~~~~~~~~~~~~~~~~~


-  Support for the Arduino Mega.



Changes in Arduino 0013
~~~~~~~~~~~~~~~~~~~~~~~


-  Support for printing floats was added to the Print, Serial, and
   Ethernet library Client and Server classes.
   

-  The word type and word(), bitRead(), bitWrite(), bitSet(),
   bitClear(), bit(), lowByte(), and highByte() functions were added.



Changes in Arduino 0012
~~~~~~~~~~~~~~~~~~~~~~~


-  Added the Firmata library, which provides a standard protocol
   for serial communication.
   

-  Added Ethernet library.
   

-  Added Servo library.
   

-  Added LiquidCrystal library.


