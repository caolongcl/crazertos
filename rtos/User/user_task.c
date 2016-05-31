#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo program include files. */
#include "user_task.h"
#include "board.h"

static volatile UBaseType_t uxFlashTaskNumber = 0;

/* The task that is created three times. */
static portTASK_FUNCTION_PROTO( vLEDFlashTask, pvParameters );

static volatile uint8_t led_value = 0;

/*-----------------------------------------------------------*/

void vStartLEDFlashTasks( UBaseType_t uxPriority )
{
    BaseType_t xLEDTask;

	/* Create the three tasks. */
	for( xLEDTask = 0; xLEDTask < ledNUMBER_OF_LEDS; ++xLEDTask )
	{
		/* Spawn the task. */
		xTaskCreate( vLEDFlashTask, "LEDx", ledSTACK_SIZE, NULL, uxPriority, ( TaskHandle_t * ) NULL );
	}
}
/*-----------------------------------------------------------*/

static portTASK_FUNCTION( vLEDFlashTask, pvParameters )
{
    TickType_t xFlashRate, xLastFlashTime;
    UBaseType_t uxLED;

	/* The parameters are not used. */
	( void ) pvParameters;

	/* Calculate the LED and flash rate. */
	portENTER_CRITICAL();
	{
		/* See which of the eight LED's we should use. */
		uxLED = uxFlashTaskNumber;

		/* Update so the next task uses the next LED. */
		uxFlashTaskNumber++;
	}
	portEXIT_CRITICAL();

	xFlashRate = ledFLASH_RATE_BASE + ( ledFLASH_RATE_BASE * ( TickType_t ) uxLED );
	xFlashRate /= portTICK_PERIOD_MS;

	/* We will turn the LED on and off again in the delay period, so each
	delay is only half the total period. */
	xFlashRate /= ( TickType_t ) 2;

	/* We need to initialise xLastFlashTime prior to the first call to 
	vTaskDelayUntil(). */
	xLastFlashTime = xTaskGetTickCount();

	for(;;)
	{
		/* Delay for half the flash period then turn the LED on. */
		vTaskDelayUntil( &xLastFlashTime, xFlashRate );
		led_troggle( uxLED );

		/* Delay for half the flash period then turn the LED off. */
		vTaskDelayUntil( &xLastFlashTime, xFlashRate );
		led_troggle( uxLED );
	}
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */

/*-----------------------------------------------------------*/

void led_set( unsigned portBASE_TYPE uxLED,signed portBASE_TYPE xValue)
{
	vTaskSuspendAll();
	{
		if( uxLED < ledNUMBER_OF_LEDS )
		{
			led_value &= ~((uint8_t)(1<<uxLED));
            led_value |=  ((uint8_t)(xValue<<uxLED));
            led_reflash(led_value);
		}	
	}
	xTaskResumeAll();
}
/*-----------------------------------------------------------*/

void led_troggle( unsigned portBASE_TYPE uxLED )
{
	vTaskSuspendAll();
	{
        if( uxLED < ledNUMBER_OF_LEDS )
        {
            led_value ^= (uint8_t)(1<<uxLED);
            led_reflash(led_value);
        }
	}
	xTaskResumeAll();
}
/*-----------------------------------------------------------*/
