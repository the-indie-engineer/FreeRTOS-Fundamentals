/*
    FreeRTOS V8.0.0 - Copyright (C) 2014 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>! NOTE: The modification to the GPL is included to allow you to distribute
    >>! a combined work that includes FreeRTOS without being obliged to provide
    >>! the source code for proprietary components outside of the FreeRTOS
    >>! kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/******************************************************************************
 * NOTE 1: The Win32 port is a simulation (or is that emulation?) only!  Do not
 * expect to get real time behaviour from the Win32 port or this demo
 * application.  It is provided as a convenient development and demonstration
 * test bed only.  This was tested using Windows XP on a dual core laptop.
 *
 * Windows will not be running the FreeRTOS simulator threads continuously, so
 * the timing information in the FreeRTOS+Trace logs have no meaningful units.
 * See the documentation page for the Windows simulator for an explanation of
 * the slow timing:
 * http://www.freertos.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 * - READ THE WEB DOCUMENTATION FOR THIS PORT FOR MORE INFORMATION ON USING IT -
 *
 * NOTE 2:  This project provides two demo applications.  A simple blinky style
 * project, and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting in main.c is used to select
 * between the two.  See the notes on using mainCREATE_SIMPLE_BLINKY_DEMO_ONLY
 * in main.c.  This file implements the simply blinky style version.
 *
 * NOTE 3:  This file only contains the source code that is specific to the
 * basic demo.  Generic functions, such FreeRTOS hook functions, are defined
 * in main.c.
 ******************************************************************************
 *
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Priorities at which the tasks are created. */
//#define task1_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define task2_TASK_PRIORITY		( tskIDLE_PRIORITY)
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

			/* Start the two tasks as described in the comments at the top of this
		file. */
	xSemaphore1= xSemaphoreCreateBinary();

		xTaskCreate(Task1,					/* The function that implements the task. */
					"Task1_Debug", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
					configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
					task1_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
					task1_TASK_PRIORITY, 		/* The priority assigned to the task. */
					xHandle1 );									/* The task handle is not required, so NULL is passed. */

		xTaskCreate(Task2,					/* The function that implements the task. */
							"Task2_Debug", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
							configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
							task2_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
							LPT_TASK_PRIORITY, 		/* The priority assigned to the task. */
							xHandle2 );									/* The task handle is not required, so NULL is passed. */

		xTaskCreate(Task3,					/* The function that implements the task. */
									"Task3_Debug", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
									configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
									task3_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
									MPT_TASK_PRIORITY, 		/* The priority assigned to the task. */
									xHandle3 );									/* The task handle is not required, so NULL is passed. */

		xTaskCreate(Task4,					/* The function that implements the task. */
											"Task4_Debug", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
											configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
											task4_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
											HPT_TASK_PRIORITY, 		/* The priority assigned to the task. */
											xHandle4 );									/* The task handle is not required, so NULL is passed. */


		/* Start the tasks and timer running. */
		vTaskStartScheduler();


	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for( ;; );
}
/*-----------------------------------------------------------*/

static void Task1( pvParameters )
{
	while(1)
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */

		if(x==10)
		xSemaphoreGive(xSemaphore1);
		printf("x = %d \r\n",x);
		x++;
		vTaskDelay(1000);
		fflush( stdout );

		/* Send to the queue - causing the queue receive task to unblock and
		toggle the LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */

	}
}

static void Task2( pvParameters )
{
	while(1)
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		/*if( xSemaphoreTake( xSemaphore, 10 ) == pdTRUE )
				 {

				printf( "%LP\r\n", item);
				 }*/
		vTaskDelay(1000);
		fflush( stdout );




		/* Send to the queue - causing the queue receive task to unblock and
		toggle the LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */

	}
}

static void Task3( pvParameters )
{
	while(1)
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */

		printf("MPT called\r\n");
		vTaskDelay(1000);
		fflush( stdout );




		/* Send to the queue - causing the queue receive task to unblock and
		toggle the LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */

	}
}

static void Task4( pvParameters )
{
	while(1)
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */

		if( xSemaphoreTake( xSemaphore1, 10 ) == pdTRUE )
				 {

				printf( "HPT called\r\n");
				 }
		vTaskDelay(1000);
		fflush( stdout );




		/* Send to the queue - causing the queue receive task to unblock and
		toggle the LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */

	}
}
/*-----------------------------------------------------------*/



