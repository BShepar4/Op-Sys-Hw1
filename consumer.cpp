#include <iostream>

#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>          //These includes come from a linked website in the resources for using shared memory

#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>         //Includes come from a linked site in canvas for using semaphores

int main() {
    int mem2;                               //Generally following the same initializations from the producer file, to ensure that 
    const char * name = "/shared";          // everything is opened even if one runs before the other
    sem_t *sem_xclude;
    sem_t *sem_full;
    sem_t *sem_empty; 

    sem_xclude = sem_open("/exclusion", O_CREAT, 0666, 1);
    sem_full = sem_open("/full", O_CREAT, 0666, 0);
    sem_empty = sem_open("/empty", O_CREAT, 0666, 1);

    mem2 = shm_open(name, O_CREAT | O_RDWR, 0600); //Creating the memory 
    struct stat size;
    fstat(mem2, &size);
    if (size.st_size == 0) {
        ftruncate(mem2, 16);
    }  
    int *array = (int*) mmap(NULL, 16, PROT_READ | PROT_WRITE, MAP_SHARED, mem2, 0);

    while (true) {                      //Reads out the two values from the table and prints them, setting them back to zero 
        sem_wait(sem_full);             // afterwards. Also signals the needed semaphores
        sem_wait(sem_xclude);
        std::cout << array[0] << std::endl;
        array[0] = 0;
        std::cout << array[1] << std::endl;
        array[1] = 0;
        sem_post(sem_empty);
        sem_post(sem_xclude);
    }
    

    return 0;
}