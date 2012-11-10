// strfis -- string :: find(const char *, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// find leftmost substring in a string
size_t string :: find (const char *s, size_t p0, size_t n) const
{
	if (n == 0 || n == NPOS && (n = strlen(s)) == 0)
		return (0);
		
size_t nmax;

	if (p0 < m_iLen && n <= (nmax = m_iLen - p0)) {
	// find non-null substring in string
	const char *t, *u;
	
		for (nmax -= n - 1, u = m_pPtr + p0;
		     (t = (const char *)memchr(u, *s, nmax)) != 0;
		     nmax -= t - u + 1, u = t + 1)
		{
			if (memcmp (t, s, n) == 0)
				return (t - m_pPtr);
		}
	}
	
return (NPOS);
}

