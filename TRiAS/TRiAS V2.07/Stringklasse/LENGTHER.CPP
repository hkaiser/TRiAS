// lenghterror -- lenghterror members
#include <bool.h>
#include <exceptio.hpp>

// construct an lenghterror
lengtherror :: lengtherror (const char *what, const char *where, const char *why)
	     : xlogic (what, where, why)
{
}

// destruct an lenghterror
lengtherror :: ~lengtherror (void)
{
}

// throw an lenghterror
void lengtherror :: do_raise (void)
{
	_RAISE(*this);
}

