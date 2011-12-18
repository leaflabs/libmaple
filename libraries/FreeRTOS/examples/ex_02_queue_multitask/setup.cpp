/**
 * \file setup.cpp 
 */
#include <stdio.h>
#include <io.h>
#include <signal.h>
#include <stdint.h>
#include <WProgram.h>

/* Scheduler includes. */
#include "MapleFreeRTOS.h"

/* Function Prototypes */
static void vPrintTask(void* pvParameters);
static void vTempTask(void* pvParameters);

/* Global Variables */
xQueueHandle xQueue;

const int sensor_pin = 12;

/**
 * The main function.
 */
void setup( void )
{
    // Setup the LED to steady on
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, HIGH);

    // Setup the button as input
    pinMode(BOARD_BUTTON_PIN, INPUT);
    digitalWrite(BOARD_BUTTON_PIN, HIGH);

    // Setup the sensor pin as an analog input
    pinMode(sensor_pin,INPUT_ANALOG);
    
    SerialUSB.begin();
    SerialUSB.println("Press any key to continue");
    SerialUSB.read();
    SerialUSB.println("FreeRTOS Intertask Communication example #02");

    /* Create the Queue for communication between the tasks */
    xQueue = xQueueCreate( 5, sizeof(uint16_t) );
    
    /* Add the two tasks to the scheduler */
    xTaskCreate(vPrintTask, (const signed char*)"Print", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    xTaskCreate(vTempTask, (const signed char*)"Temperature", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    
    /* Start the scheduler. */
    vTaskStartScheduler();
}

void loop( void )
{
}

/**
 * The Print task function.
 * It waits until a sensor value has been put in the queue,
 * and prints its value on the uart port.
 * \param pvParameter NULL is passed as parameter.
 */
static void vPrintTask(void* pvParameters)
{
    uint16_t temp_meas;
    uint16_t samplecount = 0;
    
    /* Infinite loop */
    while (1)
    {
        /* Wait until an element is received from the queue */
        if (xQueueReceive(xQueue, &temp_meas, portMAX_DELAY))
        {
            samplecount++;
            /* Print the result on the uart port */
	    //iprintf("Sample #%u: reading = %u\r\n", samplecount, temp_meas);
	    SerialUSB.print("Sample #");
	    SerialUSB.print(samplecount);
	    SerialUSB.print(": reading = ");
	    SerialUSB.println(temp_meas);
        }
    }
}

/**
 * The sensor measurement task function.
 * It reads the value from the sensor and puts it on the queue
 * \param pvParameters NULL is passed, unused here.
 */
static void vTempTask(void* pvParameters)
{
    portTickType xLastWakeTime = xTaskGetTickCount();
    
    /* The sample period is 1000 ticks, about 1s */
    const portTickType xWakePeriod = 1000;
    
    /* Infinite loop */
    while(1)
    {
        /* Read the sensor */
        uint16_t msb = analogRead(sensor_pin);
        
        /* Put the read value on the queue */
        xQueueSendToBack(xQueue, &msb, 0);
        
        /* Block until xWakePeriod(=1000) ticks since previous call */
        vTaskDelayUntil(&xLastWakeTime, xWakePeriod);
    }
}
// vim:cin:ai:sts=4 sw=4
