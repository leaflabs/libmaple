/**
 * \file setup.cpp 
 */
#include <stdio.h>
#include <io.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <WProgram.h>

/* Scheduler includes. */
#include "MapleFreeRTOS.h"

/* Declarations */
static void vLEDTask(void* pvParameters);
static void vTempTask(void* pvParameters);

/* Pins used */
const int sensor_pin = 12;

/**
 * The setup function.
 */
void setup( void )
{
    // Set up the LED to steady on
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, HIGH);

    // Setup the button as input
    pinMode(BOARD_BUTTON_PIN, INPUT);
    digitalWrite(BOARD_BUTTON_PIN, HIGH);

    SerialUSB.begin();
    SerialUSB.println("Press any key to begin");
    SerialUSB.read();
    SerialUSB.println("FreeRTOS Simple Multitask example #01");

    pinMode(sensor_pin,INPUT_ANALOG);

    /* Add the two tasks to the scheduler */
    xTaskCreate(vLEDTask, (const signed char*)"LED", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    xTaskCreate(vTempTask, (const signed char*)"Temperature", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    
    /* Start the scheduler. */
    vTaskStartScheduler();
}

void loop(void)
{
}

/**
 * The LED task function.
 * It increments a variable and displays its value on the 3 LEDs,
 * then waits for a given delay and start over again.
 * \param pvParameter NULL is passed as parameter.
 */
static void vLEDTask(void* pvParameters)
{
    /* The LEDs are updated every 200 ticks, about 200 ms */
    const portTickType blinkDelay = 200;
    
    /* Infinite loop */
    while (1)
    {
	toggleLED();
        
        /* Block the task for the defined time */
        vTaskDelay(blinkDelay);
    }
}
/**
 * The analog measurement task function.
 * It reads the analog value from sensor pin and print it
 * on the serial port.
 * \param pvParameters NULL is passed, unused here.
 */
static void vTempTask(void* pvParameters)
{
    uint16_t samplecount = 0;
    portTickType xLastWakeTime = xTaskGetTickCount();
    /* The display period is 1000 ticks, about 1s */
    const portTickType xWakePeriod = 1000;
    
    /* Infinite loop */
    while(1)
    {
        /* Read the sensor and increment the sample count */
        samplecount++;
        
        /* Print the result on the uart port */
        //iprintf("Sample #%u: reading = %u\r\n", samplecount, analogRead(sensor_pin));
	SerialUSB.print("Sample #");
	SerialUSB.print(samplecount);
	SerialUSB.print(": reading = ");
	SerialUSB.println(analogRead(sensor_pin));

        /* Block until xWakePeriod ticks since previous call */
        vTaskDelayUntil(&xLastWakeTime, xWakePeriod);
    }
}
// vim:cin:ai:sts=4 sw=4
