/*
 * This code creates four tasks with different priorities and uses a binary semaphore to control the execution order.
 * The priorities of the tasks are defined as follows:
 * - task1_TASK_PRIORITY: Lowest priority, used to release the semaphore after 10 iterations.
 * - LPT_TASK_PRIORITY: Same priority as task1, waits for the semaphore.
 * - MPT_TASK_PRIORITY: Medium priority, runs continuously with delay.
 * - HPT_TASK_PRIORITY: Highest priority, waits for the semaphore and prints a message when received.
 * 
 * Once the semaphore is received by HPT, it keeps on printing "This is from HPT".
 * The code uses printf statements to print debug information.
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define task1_TASK_PRIORITY ( tskIDLE_PRIORITY + 1 )
#define LPT_TASK_PRIORITY ( tskIDLE_PRIORITY + 1 )
#define MPT_TASK_PRIORITY ( tskIDLE_PRIORITY + 2 )
#define HPT_TASK_PRIORITY ( tskIDLE_PRIORITY + 3 )

#define task1_PARAMETER (0x11)
#define task2_PARAMETER (0x22)
#define task3_PARAMETER (0x22)
#define task4_PARAMETER (0x22)

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;
TaskHandle_t xHandle4 = NULL;

SemaphoreHandle_t xSemaphore1;
int x = 0;

static void Task1(int pvParameters);
static void Task2(int pvParameters);
static void Task3(int pvParameters);
static void Task4(int pvParameters);

void main_blinky(void)
{
    xSemaphore1 = xSemaphoreCreateBinary();

    xTaskCreate(Task1,
                "Task1_Debug",
                configMINIMAL_STACK_SIZE,
                task1_PARAMETER,
                task1_TASK_PRIORITY,
                xHandle1);

    xTaskCreate(Task2,
                "Task2_Debug",
                configMINIMAL_STACK_SIZE,
                task2_PARAMETER,
                LPT_TASK_PRIORITY,
                xHandle2);

    xTaskCreate(Task3,
                "Task3_Debug",
                configMINIMAL_STACK_SIZE,
                task3_PARAMETER,
                MPT_TASK_PRIORITY,
                xHandle3);

    xTaskCreate(Task4,
                "Task4_Debug",
                configMINIMAL_STACK_SIZE,
                task4_PARAMETER,
                HPT_TASK_PRIORITY,
                xHandle4);

    vTaskStartScheduler();

    for (;;);
}

static void Task1(int pvParameters)
{
    while (1)
    {
        if (x == 10)
            xSemaphoreGive(xSemaphore1);
        printf("x = %d \r\n", x);
        x++;
        vTaskDelay(1000);
        fflush(stdout);
    }
}

static void Task2(int pvParameters)
{
    while (1)
    {
        vTaskDelay(1000);
        fflush(stdout);
    }
}

static void Task3(int pvParameters)
{
    while (1)
    {
        printf("MPT called\r\n");
        vTaskDelay(1000);
        fflush(stdout);
    }
}

static void Task4(int pvParameters)
{
    while (1)
    {
        if (xSemaphoreTake(xSemaphore1, 10) == pdTRUE)
        {
            printf("HPT called\r\n");
            while (1)
            {
                printf("This is from HPT\r\n");
                vTaskDelay(1000);
                fflush(stdout);
            }
        }
        vTaskDelay(1000);
        fflush(stdout);
    }
}
