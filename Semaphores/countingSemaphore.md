Create for task with the priority as follows

a. /* Priorities at which the tasks are created. */

Task1 with priority tskIDLE_PRIORITY + 1
HPT with priority tskIDLE_PRIORITY + 4
MPT with priority tskIDLE_PRIORITY + 3
LPT with priority tskIDLE_PRIORITY + 2
Implement the application as follows

Create a binary counting Semaphore with 5 available 5 and let HPT and LPT waiting for Semaphore. The high HPT
is getting 2 semaphore and printing count as1 MPT is working because no semaphore is required for MPT Switched
to LPT which required semaphore .Switch to normal Task1 which runs for loop delay and print for 5 times Again
back to MPT (depends on task delay set) HPT is getting semaphore and printing count as 2. Routine continues till
consumes all 5semaphores. When semaphores are completed only MPT is working continuously.
Total consumption HPT-4 and LPT -1 (Depend on task delay used in each tasks).
Use proper printf statements to visualise the output