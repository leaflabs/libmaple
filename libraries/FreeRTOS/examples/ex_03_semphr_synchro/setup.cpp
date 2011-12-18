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
static void vLEDTask(void* pvParameters);
static void irq_button(void);

/* Global Variables */
xSemaphoreHandle xSemaphore;

/**
 * The main function.
 */
void setup( void )
{
    // Set up the LED to steady on
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, HIGH);

    // Setup the button as input
    pinMode(BOARD_BUTTON_PIN, INPUT);
    digitalWrite(BOARD_BUTTON_PIN, HIGH);

    // Wait until the user is watching
    SerialUSB.begin();
    SerialUSB.println("Press any key to continue");
    SerialUSB.read();
    SerialUSB.println("FreeRTOS Task Syncrhonization example #03");
    
    /* Get called when the button is pressed */
    attachInterrupt(BOARD_BUTTON_PIN,irq_button,FALLING);

    /* Create the Semaphore for synchronization between UART and LED task */
    vSemaphoreCreateBinary( xSemaphore)
    
    /* Add the only task to the scheduler */
    xTaskCreate(vLEDTask, (const signed char*)"LED", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    
    /* Start the scheduler. */
    vTaskStartScheduler();
}

/**
 * The LEDs task function.
 * It waits the semaphore is given, then takes it and update the LEDs
 * \param pvParameters NULL is passed, unused here.
 */
static void vLEDTask(void* pvParameters)
{
    uint16_t leds_state = 0;
    
    /* Infinite loop */
    while(1)
    {
        /* Increment the LED state */
        leds_state ++;
        /* Block until the semaphore is given */
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        /* update the LEDs and loop */
	toggleLED();
    }
}

/**
 * The irq callback function called when the button is pressed 
 * It gives the semaphore.
 */
static void irq_button(void)
{
    static portBASE_TYPE xHigherPriorityTaskWoken;
    /* Give the semaphore */
    xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);
}
// vim:cin:ai:sts=4 sw=4
