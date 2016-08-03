/*****************************************************************************
  *
  * FreeRTOS Task Syncrhonization example #03
  *
  * Based on code from:
  * http://senstools.gforge.inria.fr/doku.php?id=os:freertos:examples#task_synchronization 
  *
  * Ported to Maple by maniacbug <maniacbug@ymail.com>
  *
  * The third example is a simple application consisting of a single task that
  * synchronizes with an interrupt service routine. The goal is to show how to
  * use interrupts to synchronize FreeRTOS tasks.
  *
  * In this design, there is a single task, called 'LED' that will update the
  * LEDs every time a the Button is pressed.  The button pin is registered
  * as an external intterupt, so an interrupt service routine will be called
  * each time the button is pressed. This example shows how to synchronize 
  * the task with the callback function being called.
  *  
  * See .cpp files for the code (PDE is just here to appease the IDE).
  */

#include "MapleFreeRTOS.h"
// vim:cin:ai:sts=4 sw=4 ft=cpp
