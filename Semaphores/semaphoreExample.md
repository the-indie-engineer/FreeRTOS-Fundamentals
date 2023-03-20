
This code is an implementation of tasks with different priorities in FreeRTOS. The tasks are created with the following priorities:

task1_TASK_PRIORITY: Idle priority + 1

LPT_TASK_PRIORITY: Idle priority + 1

MPT_TASK_PRIORITY: Idle priority + 2

HPT_TASK_PRIORITY: Idle priority + 3

The MPT task runs continuously with a task delay, while the HPT and LPT tasks wait for a semaphore. A binary semaphore is created and is released only when Task1 completes 10 iterations.

The program uses the printf statement to print the count value. Only the HPT task receives the semaphore, and once it receives it, it keeps on printing "This is from HPT."

<h2>Implementation</h2>
The implementation consists of the following four tasks:

<h2>Task1</h2>
Task1 increments the count x until it reaches 10. Once x reaches 10, Task1 gives the semaphore, and the other tasks can proceed.

<h2>Task2</h2>
Task2 has the lowest priority among all the tasks and does nothing except delay for a second and flushes the standard output.

<h2>Task3</h2>
Task3 has a medium priority and runs continuously with a task delay. It prints the message "MPT called" and flushes the standard output.

<h2>Task4</h2>
Task4 has the highest priority and waits for the semaphore. Once it receives the semaphore, it prints the message "HPT called" and flushes the standard output. It also delays for a second before looping back to wait for the semaphore.

<h2>Dependencies<h2>
The following libraries are required to run this code:

<h2>FreeRTOS</h2>
  
task.h
semphr.h
stdio.h
  
<h2>How to Run</h2>
  
Install the required libraries and tools.
  
Copy the code into a C file.
  
Compile and run the code on the target device.
  
Observe the output in the standard output.
  
Note: The code is written for FreeRTOS, and it may require some modifications to run on other RTOSs.
