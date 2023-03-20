
This code is an implementation of tasks with different priorities in FreeRTOS. The tasks are created with the following priorities:

task1_TASK_PRIORITY: Idle priority + 1
LPT_TASK_PRIORITY: Idle priority + 1
MPT_TASK_PRIORITY: Idle priority + 2
HPT_TASK_PRIORITY: Idle priority + 3
The MPT task runs continuously with a task delay, while the HPT and LPT tasks wait for a semaphore. A binary semaphore is created and is released only when Task1 completes 10 iterations.

The program uses the printf statement to print the count value. Only the HPT task receives the semaphore, and once it receives it, it keeps on printing "This is from HPT."

Implementation
The implementation consists of the following four tasks:

Task1
Task1 increments the count x until it reaches 10. Once x reaches 10, Task1 gives the semaphore, and the other tasks can proceed.

Task2
Task2 has the lowest priority among all the tasks and does nothing except delay for a second and flushes the standard output.

Task3
Task3 has a medium priority and runs continuously with a task delay. It prints the message "MPT called" and flushes the standard output.

Task4
Task4 has the highest priority and waits for the semaphore. Once it receives the semaphore, it prints the message "HPT called" and flushes the standard output. It also delays for a second before looping back to wait for the semaphore.

Dependencies
The following libraries are required to run this code:

FreeRTOS
task.h
semphr.h
stdio.h
How to Run
Install the required libraries and tools.
Copy the code into a C file.
Compile and run the code on the target device.
Observe the output in the standard output.
Note: The code is written for FreeRTOS, and it may require some modifications to run on other RTOSs.
