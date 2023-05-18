/*
NAME         
       sem_init - initialize an unnamed semaphore

SYNOPSIS         

       #include <semaphore.h>

       int sem_init(sem_t *sem, int pshared, unsigned int value);

       Link with -pthread.

DESCRIPTION         

       sem_init() initializes the unnamed semaphore at the address pointed
       to by sem.  The value argument specifies the initial value for the
       semaphore.

       The pshared argument indicates whether this semaphore is to be shared
       between the threads of a process, or between processes.

       If pshared has the value 0, then the semaphore is shared between the
       threads of a process, and should be located at some address that is
       visible to all threads (e.g., a global variable, or a variable
       allocated dynamically on the heap).

       If pshared is nonzero, then the semaphore is shared between
       processes, and should be located in a region of shared memory (see
       shm_open(3), mmap(2), and shmget(2)).  (Since a child created by
       fork(2) inherits its parent's memory mappings, it can also access the
       semaphore.)  Any process that can access the shared memory region can
       operate on the semaphore using sem_post(3), sem_wait(3), and so on.

       Initializing a semaphore that has already been initialized results in
       undefined behavior.

RETURN VALUE         

       sem_init() returns 0 on success; on error, -1 is returned, and errno
       is set to indicate the error.
*/


#ifndef __semaphore_h
#define __semaphore_h
 
#include <semaphore.h>
 
class Semaphore
{
public:						   	
    Semaphore(int i = 1) { sem_init(&sem, 0, i); } //arg 0: endereço do semaforo arg1: com que vai compartilhar arg3:valor inicial(se não especificar é 1)
    ~Semaphore() { sem_destroy(&sem); }
 
    void p() { sem_wait(&sem); }
    void v() { sem_post(&sem); }
 
    operator int()
    {
        int ret;
        sem_getvalue(&sem, &ret);
        return ret;
    }
 
private:
    sem_t sem;
};
 
#endif
