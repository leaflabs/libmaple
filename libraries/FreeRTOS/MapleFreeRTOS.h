#ifndef __FREERTOS__
#define __FREERTOS__

#include "wirish.h"

extern "C" {
	#define GCC_ARMCM3
	#include "utility/FreeRTOS.h"
	#include "utility/task.h"
	#include "utility/queue.h"
	#include "utility/semphr.h"
}

#endif
