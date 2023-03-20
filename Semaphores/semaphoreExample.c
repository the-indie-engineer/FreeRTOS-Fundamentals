/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Priorities at which the tasks are created. */
#define task1_TASK_PRIORITY ( tskIDLE_PRIORITY + 1 )
#define LPT_TASK_PRIORITY ( tskIDLE_PRIORITY + 1 )
#define MPT_TASK_PRIORITY ( tskIDLE_PRIORITY + 2 )
#define HPT_TASK_PRIORITY ( tskIDLE_PRIORITY + 3 )


/* Values passed to the two tasks just to check the task parameter
functionality. */

#define task1_PARAMETER			( 0x11 )
#define task2_PARAMETER			( 0x22 )
#define task3_PARAMETER			( 0x22 )
#define task4_PARAMETER			( 0x22 )

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;
TaskHandle_t xHandle4 = NULL;

xSemaphoreHandle xSemaphore1;
int x=0;

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void Task1( int pvParameters );
static void Task2( int pvParameters );
static void Task3( int pvParameters );
static void Task4( int pvParameters );


/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/

void main_blinky( void )
{

	xSemaphore1= xSemaphoreCreateBinary();

		xTaskCreate(Task1,					
					"Task1_Debug", 									
					configMINIMAL_STACK_SIZE, 				
					task1_PARAMETER, 
					task1_TASK_PRIORITY, 		
					xHandle1 );									

		xTaskCreate(Task2,					
							"Task2_Debug", 									
							configMINIMAL_STACK_SIZE, 				
							task2_PARAMETER,
							xHandle2 );									

		xTaskCreate(Task3,					/* The function that implements the task. */
									"Task3_Debug", 									
									configMINIMAL_STACK_SIZE, 				
									task3_PARAMETER, 
									MPT_TASK_PRIORITY, 		
									xHandle3 );									

		xTaskCreate(Task4,					/* The function that implements the task. */
											"Task4_Debug", 									
											configMINIMAL_STACK_SIZE, 				
											task4_PARAMETER, 
											HPT_TASK_PRIORITY, 		
											xHandle4 );									


		/* Start the tasks and timer running. */
		vTaskStartScheduler();


	for( ;; );
}
/*-----------------------------------------------------------*/

static void Task1( pvParameters )
{
	while(1)
	{
		
		if(x==10)
		xSemaphoreGive(xSemaphore1);
		printf("x = %d \r\n",x);
		x++;
		vTaskDelay(1000);
		fflush( stdout );

	}
}

static void Task2( pvParameters )
{
	while(1)
	{
		
		vTaskDelay(1000);
		fflush( stdout );


	}
}

static void Task3( pvParameters )
{
	while(1)
	{
		
		printf("MPT called\r\n");
		vTaskDelay(1000);
		fflush( stdout );


	}
}

static void Task4( pvParameters )
{
	while(1)
	{
		if( xSemaphoreTake( xSemaphore1, 10 ) == pdTRUE )
				 {

				printf( "HPT called\r\n");
				 }
		vTaskDelay(1000);
		fflush( stdout );


	}
}
/*-----------------------------------------------------------*/



