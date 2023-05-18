#ifndef __mutex_h
#define __mutex_h
 
#include <pthread.h>
 
class Mutex
{
public:
    Mutex() {}
    ~Mutex() {}
 
    void lock() { pthread_mutex_lock(&mut); }
    bool try_lock() { return (pthread_mutex_trylock(&mut) == 0); } // true when succeeds.
    void unlock() { pthread_mutex_unlock(&mut); }
 
private:
    pthread_mutex_t mut;
};
 
#endif
