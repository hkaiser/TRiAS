// strffs -- string :: find_first_of(const char *, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// find leftmost set memberin a string
size_t string :: find_first_of (const char *s, size_t p0, size_t n) const
{
	if (n == 0 || n == NPOS && (n = strlen(s)) == 0)
		return (0);
		
	if (p0 < m_iLen) {
	// find in non-nullstring
	const char *u = m_pPtr + m_iLen;
	
		for (const char *t = m_pPtr + p0; t < u; ++t) {
			if (memchr (s, *t, n) != 0)
				return (t - m_pPtr);
		}
	}
	
return (NPOS);
}

