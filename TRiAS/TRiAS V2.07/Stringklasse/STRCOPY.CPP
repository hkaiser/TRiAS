// strcopy -- string::copy (const char *, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// copy a string to a char array
size_t string :: copy (char *s, size_t n, size_t p0)
{
	if (m_iLen < p0) _Xran();
	if (m_iLen - p0 < n)
		n = m_iLen - p0;
		
	memcpy (s, m_pPtr + p0, n);
	
return n;
}
