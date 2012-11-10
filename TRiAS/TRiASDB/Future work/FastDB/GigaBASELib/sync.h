//-< SYNC.H >--------------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update:  8-Feb-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Intertask synchonization primitives
//-------------------------------------------------------------------*--------*

#ifndef __SYNC_H__
#define __SYNC_H__

#ifdef _WIN32
class dbMutex { 
    CRITICAL_SECTION cs;
  public:
    dbMutex() { 
	InitializeCriticalSection(&cs);
    }
    ~dbMutex() { 
	DeleteCriticalSection(&cs);
    }
    void lock() { 
	EnterCriticalSection(&cs);
    }
    void unlock() { 
	LeaveCriticalSection(&cs);
    }
};

#define thread_proc WINAPI

class dbThread { 
    HANDLE h;
  public:
    void create(void (thread_proc* f)(void*), void* arg) { 
	DWORD threadid;
	h = CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(f), arg,
			 0, &threadid);
    }
    void join() { 
	WaitForSingleObject(h, INFINITE);
	CloseHandle(h);
	h = NULL;
    }
    void detach() { 
	if (h != NULL) { 
	    CloseHandle(h);
	    h = NULL;
	}
    }	
    dbThread() { 
	h = NULL; 
    }
    ~dbThread() { 
	if (h != NULL) { 
	    CloseHandle(h);
	}
    }
    static int numberOfProcessors() { 
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
    }
};
    
const int dbMaxSemValue = 1000000;


class dbSemaphore { 
    HANDLE s;
  public:
    void wait(dbMutex& mutex) { 
	mutex.unlock();
	int rc = WaitForSingleObject(s, INFINITE);
	assert(rc == WAIT_OBJECT_0);
	mutex.lock();
    }
    void signal(unsigned inc = 1) {
	if (inc != 0) { 
	    ReleaseSemaphore(s, inc, NULL);
	}
    }
    void open(unsigned initValue = 0) {
	s = CreateSemaphore(NULL, initValue, dbMaxSemValue, NULL);
	assert(s != NULL); 
    }
    void close() {
	CloseHandle(s);
    }
};

class dbEvent { 
    HANDLE e;
  public:
    void wait(dbMutex& mutex) { 
	mutex.unlock();
	int rc = WaitForSingleObject(e, INFINITE);
	assert(rc == WAIT_OBJECT_0);
	mutex.lock();
    }
    void signal() {
	SetEvent(e);
    }
    void reset() {
	ResetEvent(e);
    }
    void open(bool initValue = false) { 
	e = CreateEvent(NULL, true, initValue, NULL);
    }
    void close() {
	CloseHandle(e);
    }
};

template<class T>
class dbThreadContext { 
    int index;
  public:
    T* get() { 
	return (T*)TlsGetValue(index);
    }
    void set(T* value) { 
	TlsSetValue(index, value);
    }
    dbThreadContext() { 
	index = TlsAlloc();
	assert(index != TLS_OUT_OF_INDEXES);
    }
    ~dbThreadContext() { 
	TlsFree(index);
    }
};

#else // Unix

#define thread_proc

#ifdef PTHREADS

#include <unistd.h>
#include <pthread.h>

class dbMutex { 
    friend class dbEvent;
    friend class dbSemaphore;
    pthread_mutex_t cs;
  public:
    dbMutex() { 
	pthread_mutex_init(&cs, NULL);
    }
    ~dbMutex() { 
	pthread_mutex_destroy(&cs);
    }
    void lock() { 
	pthread_mutex_lock(&cs);
    }
    void unlock() { 
	pthread_mutex_unlock(&cs);
    }
};

class dbThread { 
    pthread_t thread;
  public:
    void create(void (thread_proc* f)(void*), void* arg) { 
	pthread_create(&thread, NULL, (void*(*)(void*))f, arg);
    }
    void join() { 
	void* result;
	pthread_join(thread, &result);
    }
    void detach() { 
	pthread_detach(thread);
    }
    static int numberOfProcessors();
};

#if defined(_SC_NPROCESSORS_ONLN) 
inline int dbThread::numberOfProcessors() { 
    return sysconf(_SC_NPROCESSORS_ONLN); 
}
#elif defined(__linux__)
#include <linux/smp.h>
inline int dbThread::numberOfProcessors() { return smp_num_cpus; }
#elif defined(__FreeBSD__)
#include <sys/sysctl.h>
inline int dbThread::numberOfProcessors() { 
    int mib[2],ncpus=0;
    size_t len=sizeof(ncpus);
    mib[0]= CTL_HW;
    mib[1]= HW_NCPU;
    sysctl(mib,2,&ncpus,&len,NULL,0);
    return ncpus; 
}
#else
#warning Do not know how to detect number of processors: assuming 1 
inline int dbThread::numberOfProcessors() { return 1; }
#endif

class dbEvent { 
    pthread_cond_t   cond;
    int              signaled;
  public:
    void wait(dbMutex& mutex) { 
	while (!signaled) { 
	    pthread_cond_wait(&cond, &mutex.cs);
	}
    }
    void signal() {
	signaled = true;
	pthread_cond_broadcast(&cond);
    }
    void reset() {
	signaled = false;
    }
    void open(bool initValue = false) { 
	signaled = initValue;
	pthread_cond_init(&cond, NULL);
    }
    void close() {
	pthread_cond_destroy(&cond);
    }
};

class dbSemaphore { 
    pthread_cond_t   cond;
    int              count;
  public:
    void wait(dbMutex& mutex) { 
	while (count == 0) { 
	    pthread_cond_wait(&cond, &mutex.cs);
	}
	count -= 1;
    }
    void signal(unsigned inc = 1) {
	count += inc;
	if (inc > 1) { 
	    pthread_cond_broadcast(&cond);
	} else if (inc == 1) { 
	    pthread_cond_signal(&cond);
	}
    }
    void open(unsigned initValue = 0) { 
	pthread_cond_init(&cond, NULL);
	count = initValue;
    }
    void close() {
	pthread_cond_destroy(&cond);
    }
};

template<class T> 
class dbThreadContext { 
    pthread_key_t key;
  public:
    T* get() { 
	return (T*)pthread_getspecific(key);
    }
    void set(T* value) { 
	pthread_setspecific(key, value);
    }
    dbThreadContext() { 
        pthread_key_create(&key, NULL);
    }
    ~dbThreadContext() { 
	pthread_key_delete(key);
    }
};

#else

class dbMutex { 
   public:
    void lock() {}
    void unlock() {}
};

class dbThread { 
  public:
    void create(void (thread_proc* f)(void*), void* arg) { f(arg); }
    void join() {}
    void detach() {}
    static int numberOfProcessors() { return 1; }
};

class dbSemaphore { 
    int count;
  public:
    void wait(dbMutex&) { 
	assert (count > 0);
	count -= 1;
    }
    void signal(unsigned inc = 1) {
	count += inc;
    }
    void open(unsigned initValue = 0) {
	count = initValue;
    }
    void close() {}
};

class dbEvent { 
    bool signaled;
  public:
    void wait(dbMutex&) { 
	assert(signaled);
    }
    void signal() {
	signaled = true;
    }
    void reset() {
	signaled = false;
    }
    void open(bool initValue = false) {
	signaled = initValue;
    }
    void close() {}
};

template<class T>
class dbThreadContext { 
    T* value;
  public:
    T* get() { 
	return value;
    }
    void set(T* value) { 
	this->value = value;
    }
    dbThreadContext() { value = NULL; }
};


#endif

#endif

class dbCriticalSection { 
  private:
    dbMutex& mutex;
  public:
    dbCriticalSection(dbMutex& guard) : mutex(guard) {
	mutex.lock();
    }
    ~dbCriticalSection() { 
	mutex.unlock();
    }
};

#define SMALL_BUF_SIZE 1024

class dbSmallBuffer { 
  protected:
    char* buf;
    char  smallBuf[SMALL_BUF_SIZE];

  public:
    dbSmallBuffer(size_t size) { 
	if (size > sizeof(smallBuf)) { 
	    buf = new char[size];
	} else { 
	    buf = smallBuf;
	}
    }

    operator char*() { return buf; }
    char* base() { return buf; }

    ~dbSmallBuffer() { 
	if (buf != smallBuf) { 
	    delete[] buf;
	}
    }
};
	
#endif
