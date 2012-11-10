// xdomain -- xdomain members
#include <bool.h>
#include <exceptio.hpp>

// construct an xdomain
xdomain :: xdomain (const char *what, const char *where, const char *why)
	 : xlogic (what, where, why)
{
}

// destruct an xdomain
xdomain :: ~xdomain (void)
{
}

// throw an xdomain
void xdomain :: do_raise (void)
{
	_RAISE(*this);
}

