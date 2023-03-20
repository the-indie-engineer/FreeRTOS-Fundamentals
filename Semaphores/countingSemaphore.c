/* The program creates a binary counting semaphore with 5 available units and initializes it with 5 units. The semaphore is used by HPT and LPT tasks to wait for the semaphore, while MPT and Task1 tasks use the semaphore to perform some operations.

The HPT task waits for the semaphore twice, taking 2 units, and prints a message with the count value each time it takes the semaphore.

The MPT task tries to take the semaphore every 1 second and prints a message indicating whether the semaphore was taken or not.

The LPT task waits for the semaphore once and prints a message when it takes it.

The Task1 task runs a loop with a 1 second delay, printing a message at each iteration. After 5 iterations, it terminates.

When the program starts, all tasks are created with their respective priorities. The HPT and LPT tasks wait for the semaphore, while MPT and Task1 tasks start executing immediately.

When MPT takes the semaphore, it prints a message indicating that it succeeded. When Task1 runs, it prints a message 5 times and then terminates. When HPT takes the semaphore twice, it prints a message with the count value each time. When LPT takes
*/

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xSemaphore;

void HPT_Task(void *pvParameters) {
    int count = 0;
    while (count < 2) {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            count++;
            printf("HPT: Semaphore taken, count=%d\n", count);
        }
    }
    printf("HPT: Done\n");
    vTaskDelete(NULL);
}

void MPT_Task(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xSemaphore, pdMS_TO_TICKS(500)) == pdTRUE) {
            printf("MPT: Semaphore taken\n");
        } else {
            printf("MPT: Semaphore not taken\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void LPT_Task(void *pvParameters) {
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        printf("LPT: Semaphore taken\n");
    }
    printf("LPT: Done\n");
    vTaskDelete(NULL);
}

void Task1(void *pvParameters) {
    for (int i = 0; i < 5; i++) {
        printf("Task1: Loop %d\n", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    printf("Task1: Done\n");
    vTaskDelete(NULL);
}

int main(void) {
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);
    xSemaphoreGive(xSemaphore);
    xSemaphoreGive(xSemaphore);
    xSemaphoreGive(xSemaphore);
    xSemaphoreGive(xSemaphore);

    xTaskCreate(HPT_Task, "HPT", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 4, NULL);
    xTaskCreate(MPT_Task, "MPT", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(LPT_Task, "LPT", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(Task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();
    return 0;
}
