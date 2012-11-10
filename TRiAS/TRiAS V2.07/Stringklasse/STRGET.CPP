// strget -- string :: get_at (size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// get element of a string
char string :: get_at (size_t p0) const
{
	if (m_iLen <= p0) _Xran();
	
return (m_pPtr[p0]);
}
