/*****************************************************************************
  *
  * FreeRTOS Intertask Communication example #02
  *
  * Based on code from:
  * http://senstools.gforge.inria.fr/doku.php?id=os:freertos:examples#intertask_communication  
  *
  * Ported to Maple by maniacbug <maniacbug@ymail.com>
  *
  * The second example is a simple application that consists of two tasks 
  * running concurrently and communicating with each other. The goal is to show 
  * how to make a task send data to another using a queue. 
  *
  * In this design, there are two tasks. The first, called 'Temperature' is 
  * really similar to the homonym from the previous example, but instead of 
  * printing the measure value every time it reads the sensor, it will send 
  * the data to the other task, called 'Print'. This task will just wait 
  * until some data arrives, and print it on the USB Serial link.
  *
  * The 'Print' task enters its infinite loop where it waits for data to be 
  * available on the queue, and prints it each time it reads some. The 
  * 'Temperature' task starts the sampling, and enters the loop where it 
  * reads the measure value, places it in the queue, and waits for a given 
  * time.
  * 
  * See .cpp files for the code (PDE is just here to appease the IDE).
  */

#include "MapleFreeRTOS.h"
// vim:cin:ai:sts=4 sw=4 ft=cpp
