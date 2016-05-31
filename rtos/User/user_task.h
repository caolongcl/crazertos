#ifndef __TASK_H__
#define __TASK_H__

#include "portmacro.h"

#include "led.h"
#include "uart.h"

#define tskIDLE_PRIORITY			( ( UBaseType_t ) 0U )

/*-----------------------------------------------------------------------*/

/* led task */
#define ledSTACK_SIZE		        configMINIMAL_STACK_SIZE
#define ledNUMBER_OF_LEDS	        ( 4 )
#define ledFLASH_RATE_BASE	        ( ( TickType_t ) 333 )
#define ledFLASH_TASK_PRIORITY	    ( tskIDLE_PRIORITY + 1 )

void vStartLEDFlashTasks( UBaseType_t uxPriority );
/*-----------------------------------------------------------------------*/

#endif

