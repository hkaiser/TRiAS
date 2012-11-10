// terminate -- terminate support functions
#include <bool.h>
#include <stdlib.h>
#include <exceptio.hpp>

static fvoid_t *terminate_handler = &abort;

// store terminate handler pointer, return old
fvoid_t *set_terminate (fvoid_t *pnew)
{
fvoid_t *pold = terminate_handler;

	terminate_handler = pnew;

return (pold);
}

// call terminate handler or abort
void std_terminate (void)
{
	if (terminate_handler) 
		(*terminate_handler)();
	abort();
}
