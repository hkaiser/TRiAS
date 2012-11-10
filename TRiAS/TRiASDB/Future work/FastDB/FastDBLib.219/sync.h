//-< SYNC.H >--------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 20-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Intertask synchonization primitives
//-------------------------------------------------------------------*--------*

#ifndef __SYNC_H__
#define __SYNC_H__

class dbSystem { 
  public:
    static unsigned getCurrentTimeMsec();
};

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
#ifdef PHAR_LAP
	return 1;
#else
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
#endif
    }
};
    
class dbInitializationMutex { 
    HANDLE m;
  public: 
    enum initializationStatus { 
	InitializationError, 
	AlreadyInitialized,
	NotYetInitialized
    };
    initializationStatus initialize(char const* name) { 
	initializationStatus status;
	m = CreateMutex(NULL, true, name);
	if (GetLastError() == ERROR_ALREADY_EXISTS) { 
	    status = WaitForSingleObject(m, INFINITE) == WAIT_OBJECT_0 
		   ? AlreadyInitialized : InitializationError;
	    ReleaseMutex(m);
	} else if (m != NULL) { 
	    status = NotYetInitialized;
	} else { 
	    status = InitializationError;
	}
	return status;
    }
    void done() { 
	ReleaseMutex(m);
    }
    bool close() {
	CloseHandle(m);
	return false;
    }
    void erase() { 
	close();
    }
};


const int dbMaxSemValue = 1000000;


class dbSemaphore { 
  protected:
    HANDLE s;
  public:
    bool wait(unsigned msec = INFINITE) { 
	int rc = WaitForSingleObject(s, msec);
	assert(rc == WAIT_OBJECT_0 || rc == WAIT_TIMEOUT);
	return rc == WAIT_OBJECT_0;
    }
    void signal(unsigned inc = 1) {
	if (inc != 0) { 
	    ReleaseSemaphore(s, inc, NULL);
	}
    }
    void reset() { 
	while (WaitForSingleObject(s, 0) == WAIT_OBJECT_0);
    }    
    bool open(char const* name, unsigned initValue = 0) {
	s = CreateSemaphore(NULL, initValue, dbMaxSemValue, name);
	return s != NULL; 
    }
    void close() {
	CloseHandle(s);
    }
    void erase() { 
	close();
    }
};

class dbEvent { 
  protected:
    HANDLE e;
  public:
    bool wait(unsigned msec = INFINITE) { 
	int rc = WaitForSingleObject(e, msec);
	assert(rc == WAIT_OBJECT_0 || rc == WAIT_TIMEOUT);
	return rc == WAIT_OBJECT_0;
    }
    void signal() {
	SetEvent(e);
    }
    void reset() {
	ResetEvent(e);
    }
    bool open(char const* name, bool signaled = false) {
	e = CreateEvent(NULL, true, signaled, name);
	return e != NULL; 
    }
    void close() {
	CloseHandle(e);
    }
    void erase() { 
	close();
    }
};

class dbLocalSemaphore : public dbSemaphore { 
  public:
    void wait(dbMutex& mutex) { 
	mutex.unlock();
	int rc = WaitForSingleObject(s, INFINITE);
	assert(rc == WAIT_OBJECT_0);
	mutex.lock();
    }    
    bool open(unsigned initValue = 0) {
	return dbSemaphore::open(NULL, initValue);
    }
};

class dbLocalEvent : public dbEvent { 
  public:
    void wait(dbMutex& mutex) { 
	mutex.unlock();
	int rc = WaitForSingleObject(e, INFINITE);
	assert(rc == WAIT_OBJECT_0);
	mutex.lock();
    }
    bool open(bool signaled = false) {
	 return dbEvent::open(NULL, signaled);
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

template<class T>
class dbSharedObject { 
    T*     ptr;
    HANDLE h;
  public:

    bool open(char* name) { 
#ifdef NO_MMAP
	ptr = new T();
#else
	h = CreateFileMapping(INVALID_HANDLE_VALUE,
			      NULL, PAGE_READWRITE, 0, 
			      sizeof(T), name);
	if (h == NULL) { 
	    return false;
	}
	ptr = (T*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (ptr == NULL) { 
	    CloseHandle(h);
	    return false;
	}
#endif
	return true;
    }

    T* get() { return ptr; }

    void close() { 
#ifdef NO_MMAP
	delete[] ptr;
#else
	UnmapViewOfFile(ptr);
	CloseHandle(h);
#endif
    }
    void erase() { 
	close();
    }
};

typedef long sharedsem_t;

class dbGlobalCriticalSection { 
    HANDLE       event;
    sharedsem_t* count;

  public:
    void enter() { 
	if (InterlockedDecrement(count) != 0) { 
	    // another process is in critical section
	    int rc = WaitForSingleObject(event, INFINITE);
	    assert (rc == WAIT_OBJECT_0);
	}
    }

    void leave() { 
	if (InterlockedIncrement(count) <= 0) { 
	    // some other processes try to enter critical section
	    SetEvent(event);
	}
    }

    bool open(char const* name, long* count) { 
	this->count = count;
	event = OpenEvent(EVENT_ALL_ACCESS, FALSE, name);
	return event != NULL;
    }
    bool create(char const* name, long* count) { 
	this->count = count;
	*count = 1;
	event = CreateEvent(NULL, false, false, name);
	return event != NULL;
    }
    void close() { 
	CloseHandle(event);
    }
    void erase() { 
	close();
    }
};
	
    
#else // Unix

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define thread_proc

#ifndef NO_PTHREADS

#include <pthread.h>

class dbMutex { 
    friend class dbLocalEvent;
    friend class dbLocalSemaphore;
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
#if defined(_AIX)
	// At AIX threads are by default created detached
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_UNDETACHED);
	pthread_create(&thread, &attr, (void*(*)(void*))f, arg);
	pthread_attr_destroy(&attr);
#else
	pthread_create(&thread, NULL, (void*(*)(void*))f, arg);
#endif
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


class dbLocalEvent { 
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

class dbLocalSemaphore { 
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

class dbLocalSemaphore { 
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

class dbLocalEvent { 
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

#define INFINITE (~0U)
extern char const* keyFileDir; // default value: "/tmp/" 

class dbInitializationMutex { 
    int semid;
  public: 
    enum initializationStatus { 
	InitializationError, 
	AlreadyInitialized,
	NotYetInitialized
    };
    initializationStatus initialize(char const* name);
    void done(); 
    bool close();
    void erase();
};


class dbSemaphore { 
    int s;
  public:
    bool wait(unsigned msec = INFINITE);
    void signal(unsigned inc = 1);
    bool open(char const* name, unsigned initValue = 0);
    void reset();
    void close();
    void erase();
};

class dbEvent { 
    int e;
  public:
    bool wait(unsigned msec = INFINITE);
    void signal();
    void reset();
    bool open(char const* name, bool signaled = false);
    void close();
    void erase();
};

template<class T>
class dbSharedObject { 
    T*  ptr;
    int shm;
  public:

    bool open(char* name) { 
	char* fileName = name;
	if (*name != '/') { 
	    fileName = new char[strlen(name)+strlen(keyFileDir)+1];
	    sprintf(fileName, "%s%s", keyFileDir, name);
	}
	int fd = ::open(fileName, O_RDWR|O_CREAT, 0777);
	if (fd < 0) { 
	    if (fileName != name) { 
		delete[] fileName;
	    }
	    return false;
	} 
	::close(fd);
	int key = ftok(fileName, '0');
	if (fileName != name) { 
	    delete[] fileName;
	}
	if (key < 0) { 
	    return false;
	}
	shm = shmget(key, DOALIGN(sizeof(T), 4096), IPC_CREAT|0777);
	if (shm < 0) { 
	    return false;
	}
	ptr = (T*)shmat(shm, NULL, 0);
	return (ptr != (T*)-1);
    }

    T* get() { return ptr; }

    void close() { 
	shmdt((char*)ptr);
    }
    void erase() { 
	close();
	shmctl(shm, IPC_RMID, NULL);
    }  
};

#if defined(__osf__)

#include <errno.h>
typedef msemaphore sharedsem_t;

class dbGlobalCriticalSection { 
    sharedsem_t* sem;
  public:
    void enter() { 
	int rc;
	while ((rc = msem_lock(sem, 0)) < 0 && errno == EINTR);
	assert(rc == 0);
    }
    void leave() { 
	int rc = msem_unlock(sem, 0);
	assert(rc == 0);	
    }
    bool open(char const*, sharedsem_t* shr) { 
	sem = shr;
	return true;
    }
    bool create(char const*, sharedsem_t* shr) { 
	sem = shr;
	msem_init(shr, MSEM_UNLOCKED);
	return true;
    }
    void close() {}
    void erase() {
	msem_destroy(shr);
    }
};
	

#elif defined(__svr4__)

#include <synch.h>
#include <errno.h>
typedef sema_t sharedsem_t;

class dbGlobalCriticalSection { 
    sharedsem_t* sem;
  public:
    void enter() { 
	int rc;
	while ((rc = sema_wait(sem)) < 0 && errno == EINTR);
	assert(rc == 0);
    }
    void leave() { 
	int rc = sema_post(sem);
	assert(rc == 0);
    }
    bool open(char const*, sharedsem_t* shr) { 
	sem = shr;
	return true;
    }
    bool create(char const*, sharedsem_t* shr) { 
	sem = shr;
	return sema_init(shr, 1, USYNC_PROCESS, NULL) == 0;
    }
    void close() {}
    void erase() {
	sema_destroy(sem);
    }
};
	
#else

typedef long sharedsem_t;

class dbGlobalCriticalSection { 
    int          semid;
    sharedsem_t* count;

  public:
    void enter(); 
    void leave();
    bool open(char const* name, sharedsem_t* shr);
    bool create(char const* name, sharedsem_t* shr);
    void close() {}
    void erase();
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
	if (size > SMALL_BUF_SIZE) { 
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


