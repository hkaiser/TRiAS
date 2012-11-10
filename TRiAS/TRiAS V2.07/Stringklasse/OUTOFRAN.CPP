// outofrange -- outofrange members
#include <bool.h>
#include <exceptio.hpp>

// construct an outofrange
outofrange :: outofrange (const char *what, const char *where, const char *why)
	    : xlogic (what, where, why)
{
}

// destruct an outofrange
outofrange :: ~outofrange (void)
{
}

// throw an outofrange
void outofrange :: do_raise (void)
{
	_RAISE(*this);
}

