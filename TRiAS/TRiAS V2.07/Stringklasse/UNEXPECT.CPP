// unexpected -- unexpected support functions
#include <bool.h>
#include <exceptio.hpp>

static fvoid_t *unexpected_handler = &std_terminate;

// store unexpected handler pointer, return old
fvoid_t *set_unexpected (fvoid_t *pnew)
{
fvoid_t *pold = unexpected_handler;

	unexpected_handler = pnew;

return (pold);
}


// call unexpected handler or terminate
void std_unexpected (void)
{
	if (unexpected_handler) 
		(*unexpected_handler)();
	std_terminate();
}
