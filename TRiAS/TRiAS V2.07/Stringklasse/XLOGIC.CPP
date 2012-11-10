// xlogic -- xlogic members
#include <bool.h>
#include <exceptio.hpp>

// construct an xlogic
xlogic :: xlogic (const char *what, const char *where, const char *why)
	: xmsg (what, where, why)
{
}

// destruct an xlogic
xlogic :: ~xlogic (void)
{
}

// throw an xlogic
void xlogic :: do_raise (void)
{
	_RAISE(*this);
}

