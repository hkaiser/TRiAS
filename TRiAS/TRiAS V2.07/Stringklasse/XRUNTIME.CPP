// xruntime -- xruntime members
#include <bool.h>
#include <exceptio.hpp>

// construct an xruntime
xruntime :: xruntime (const char *what, const char *where, const char *why)
	  : xmsg (what, where, why)
{
}

// destruct an xruntime
xruntime :: ~xruntime (void)
{
}

// construct an xruntime, optional copy
xruntime :: xruntime (const char *what, const char *where, const char *why, _Bool fCopy)
	  : xmsg (what, where, why, fCopy)
{
}

// throw an xruntime
void xruntime :: do_raise (void)
{
	_RAISE(*this);
}

