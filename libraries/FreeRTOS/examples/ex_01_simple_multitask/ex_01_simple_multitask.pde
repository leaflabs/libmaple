/*****************************************************************************
  *
  * FreeRTOS Simple Multitask example #01
  *
  * Based on code from:
  * http://senstools.gforge.inria.fr/doku.php?id=os:freertos:examples#simple_multitask 
  *
  * Ported to Maple by maniacbug <maniacbug@ymail.com>
  *
  * This first example is a simple application consisting of two independent 
  * tasks running concurrently. The goal is to show how to setup a multitask 
  * environment, define and create the tasks, start a preemptive scheduler, 
  * as well as to show some task time control functions. 
  *
  * In this design, there are two independent tasks: the first called ’LED’ 
  * just blinks the LEDs at a fixed rate, and the second called ’Temperature’ 
  * periodically checks a sensor for a measurement and displays the result 
  * on the USB Serial. Both tasks will run at the same priority, and the 
  * scheduler might preempt the tasks for letting the other one execute.
  *
  * See .cpp files for the code (PDE is just here to appease the IDE).
  */

#include "MapleFreeRTOS.h"
// vim:cin:ai:sts=4 sw=4 ft=cpp
