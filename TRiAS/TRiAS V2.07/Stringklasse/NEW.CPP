// new -- operator new support functions

#include <bool.h>
#include <new.hpp>

static xalloc nomem ("no memory");

// default new handler -- raise xalloc
static void new_handler (void)
{
	nomem.raise();
}

// construct an xalloc
xalloc :: xalloc (const char *what, const char *where, const char *why)
	: xruntime (what, where, why, 0)
{
}

// destruct an xalloc
xalloc :: ~xalloc (void)
{
}

// throw an xalloc
void xalloc :: do_raise (void)
{
	_RAISE(*this);
}

fvoid_t *_New_hand = &new_handler;

// point at new handler
fvoid_t *set_new_handler (fvoid_t *pnew)
{
fvoid_t *pold = _New_hand;

	_New_hand = pnew;
	
return pold;
}

// report out of memory
void _Nomemory (void)
{
	nomem.raise();
}

