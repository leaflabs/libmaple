/* Exception handlers for STM32 (by Lanchon) */

#ifndef __STM32EXCEPTIONS_H
#define __STM32EXCEPTIONS_H

#if __cplusplus
extern "C"
{
#endif

/* Use a shared infinite loop for unexpected exceptions. */
/* #define SHARED_EXCEPTION_HANDLER */

/* Or use an external handler for unexpected exceptions. */
/* #define CUSTOM_EXCEPTION_HANDLER */

/* Or else use individual infinite loops when debugging,
 * or a shared infinite loop when not. */

#ifdef CUSTOM_EXCEPTION_HANDLER
	void unexpected_exception(const char* name, int address);
	#define DEFAULT_EXCEPTION_HANDLER(handler, name, number, address) unexpected_exception(name, address);
#endif

