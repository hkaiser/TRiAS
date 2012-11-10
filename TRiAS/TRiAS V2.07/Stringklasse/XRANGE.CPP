// xrange -- xrange members
#include <bool.h>
#include <exceptio.hpp>

// construct an xrange
xrange :: xrange (const char *what, const char *where, const char *why)
	: xruntime (what, where, why)
{
}

// destruct an xrange
xrange :: ~xrange (void)
{
}

// throw an xrange
void xrange :: do_raise (void)
{
	_RAISE(*this);
}

