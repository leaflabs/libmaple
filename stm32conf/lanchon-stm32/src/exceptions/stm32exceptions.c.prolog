/* Exception handlers for STM32 (by Lanchon)
 *
 * This code is meant to handle exceptions that the application does not expect.
 * Handlers that are part of the application should be defined elsewhere. */

#include "stm32exceptions.h"

#ifndef CUSTOM_EXCEPTION_HANDLER
	#ifdef DEBUG
		/* Use individual infinite loops to ease debugging. */
		#define DEFAULT_EXCEPTION_HANDLER(handler, name, number, address) while (1);
	#else
		/* Avoid individual infinite loops when not debugging. */
		#define SHARED_EXCEPTION_HANDLER
	#endif
#endif

/* Undefined handlers will default to a shared infinite loop (see lanchon-stm32-isrs.S). */
#ifndef SHARED_EXCEPTION_HANDLER

