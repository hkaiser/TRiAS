// badcast -- badcast members
#include <bool.h>
#include <exceptio.hpp>

// construct an badcast
badcast :: badcast (const char *what, const char *where, const char *why)
	 : xlogic (what, where, why)
{
}

// destruct an badcast
badcast :: ~badcast (void)
{
}

// throw an badcast
void badcast :: do_raise (void)
{
	_RAISE(*this);
}

