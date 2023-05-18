/*

NAME         

       pthread_join - join with a terminated thread

SYNOPSIS         

       #include <pthread.h>

       int pthread_join(pthread_t thread, void **retval);

       Compile and link with -pthread.

DESCRIPTION         

       The pthread_join() function waits for the thread specified by thread
       to terminate.  If that thread has already terminated, then
       pthread_join() returns immediately.  The thread specified by thread
       must be joinable.

       If retval is not NULL, then pthread_join() copies the exit status of
       the target thread (i.e., the value that the target thread supplied to
       pthread_exit(3)) into the location pointed to by retval.  If the
       target thread was canceled, then PTHREAD_CANCELED is placed in the
       location pointed to by retval.

       If multiple threads simultaneously try to join with the same thread,
       the results are undefined.  If the thread calling pthread_join() is
       canceled, then the target thread will remain joinable (i.e., it will
       not be detached).

RETURN VALUE        

       On success, pthread_join() returns 0; on error, it returns an error
       number.

*/

#ifndef __thread_h
#define __thread_h
 
#include <pthread.h>
#include <signal.h>
 
class Thread
{
public:
    Thread(int ( * const entry)(int), int arg) {
	if(pthread_create(&thread, 0, (void*(*)(void*))entry, (void *)arg))
	    thread = 0;
    }
    ~Thread() {}
 
    int join(int * status) { return pthread_join(thread, (void **)status); }
    //friend void exit(int status = 0) { pthread_exit((void *) status); }
 
private:
    pthread_t thread;
};
 
#endif
