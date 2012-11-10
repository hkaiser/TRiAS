// overflow -- overflow members
#include <bool.h>
#include <exceptio.hpp>

// construct an overflow
overflow :: overflow (const char *what, const char *where, const char *why)
	  : xruntime (what, where, why)
{
}

// destruct an overflow
overflow :: ~overflow (void)
{
}

// throw an overflow
void overflow :: do_raise (void)
{
	_RAISE(*this);
}

