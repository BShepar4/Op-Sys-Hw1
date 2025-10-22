#include <iostream>

#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>          //These includes come from a linked website in the resources for using shared memory

#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>         //Includes come from a linked site in canvas for using semaphores

int main() {
    int mem;            //Initializing needed variables for the memory and for the semaphores
    const char * name = "/shared";
    sem_t *sem_xclude;
    sem_t *sem_full;
    sem_t *sem_empty; 

    sem_xclude = sem_open("/exclusion", O_CREAT, 0666, 1); //Declaring semaphores
    sem_full = sem_open("/full", O_CREAT, 0666, 0);
    sem_empty = sem_open("/empty", O_CREAT, 0666, 1);

    mem = shm_open(name, O_CREAT | O_RDWR, 0600); //Creating the memory 
    struct stat size;
    fstat(mem, &size); //Checking the size so it is only ever truncated once
    if (size.st_size == 0) { 
        ftruncate(mem, 16);
    }  
    int *array = (int*) mmap(NULL, 16, PROT_READ | PROT_WRITE, MAP_SHARED, mem, 0); //Making it accessible with this process

    int i = 0; //The producer will produce an ascending list of integers tracked with i

    while (true) { //Loops forever
        i++;
        sem_wait(sem_empty); //Waits until the memory is empty and then adds two numbers, filling it up before signalling consumer
        sem_wait(sem_xclude);

        array[0] = i;
        i++;
        array[1] = i;
        sem_post(sem_full);
        sem_post(sem_xclude);
    }

    return 0;


}


