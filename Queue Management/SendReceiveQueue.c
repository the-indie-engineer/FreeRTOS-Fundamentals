Author: Thiruvarulselvan K
Date: 19.03.2023

#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define task1_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define task2_TASK_PRIORITY		( tskIDLE_PRIORITY)

#define task1_PARAMETER			( 0x11 )
#define task2_PARAMETER			( 0x22 )

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
QueueHandle_t xQueue1;
int item=22;


static void Task1( int pvParameters );
static void Task2( int pvParameters );

void queue_mgt( void )
{

			xQueue1= xQueueCreate(10, sizeof(int));

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
							task2_TASK_PRIORITY, 		
							xHandle2 );								

		for( ;; );
}
/*-----------------------------------------------------------*/

static void Task1( pvParameters )
{
	while(1)
	{
		
		if(xQueueSend(xQueue1, &item, portMAX_DELAY)==pdPASS)
		{
		printf( "%d pushed to queue\r\n", item);
		}
		vTaskDelay(1000);
		fflush( stdout );
		item--;
	}
}

static void Task2( pvParameters )
{
	while(1)
	{
		
		int x=0;
		if(xQueueReceive(xQueue1, &x, portMAX_DELAY)!=pdTRUE)
		{
		printf( "QueueFailure\r\n");
		}
		else
		{
			printf( "%d received from Queue\r\n",x);
		}
		vTaskDelay(1000);
		fflush( stdout );

	}
}
