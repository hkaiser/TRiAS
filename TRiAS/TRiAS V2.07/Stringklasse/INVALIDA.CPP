// invalidargument -- invalidargument members
#include <bool.h>
#include <exceptio.hpp>

// construct an invalidargument
invalidargument :: invalidargument (const char *what, const char *where, const char *why)
		 : xlogic (what, where, why)
{
}

// destruct an invalidargument
invalidargument :: ~invalidargument (void)
{
}

// throw an invalidargument
void invalidargument :: do_raise (void)
{
	_RAISE(*this);
}

