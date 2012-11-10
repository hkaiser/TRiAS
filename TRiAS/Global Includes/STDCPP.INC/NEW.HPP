// new standard header
#ifndef _NEW_
#define _NEW_

#include <exceptio.hpp>

// class xalloc
class xalloc : public xruntime {
public:
		xalloc (const char * = 0, const char * = 0, const char * = 0);
	virtual ~xalloc (void);
	
protected:
virtual void do_raise (void);
};

// function and object declarations
fvoid_t *set_new_handler (fvoid_t *);
void operator delete (void *);
void *operator new (size_t);
inline void *operator new (size_t, void *_P) { return (_P); }

#ifdef _HAS_ARRAY_NEW
void operator delete[] (void *);
void *operator new[] (size_t);
inline void *operator new[] (size_t, void *_P) { return (_P); }
#endif // _HAS_ARRAY_NEW

extern fvoid_t (*_New_hand);

#endif // _NEW_
