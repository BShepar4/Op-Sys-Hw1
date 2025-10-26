Tackles the producer consumer problem using two seperate processes

Program initializes shared memory and semaphores before rapidly printing out a very long list of integers. Behind the scenes, the integers are being sourced
from one process and printed by another, demonstrating a solution to the producer consumer problem

Executed results come in the form of a very long ascending list of integers 

3 semaphores are used, one to track if the memory is full, one to check if it is empty, and one to check if a process is already in the memory to enforce mutual exclusion
Shared memory is set to hold integer values and given enough space to do so
