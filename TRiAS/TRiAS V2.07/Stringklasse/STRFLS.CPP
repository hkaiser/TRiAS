// strfls -- string :: find_last_of(const char *, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// find rightmost set member in a string
size_t string :: find_last_of (const char *s, size_t p0, size_t n) const
{
	if (n == 0 || n == NPOS && (n = strlen(s)) == 0)
		return (0);
		
	if (0 < m_iLen) {
	// find rightmost substring in string
		for (const char *t = m_pPtr + (p0 < m_iLen ? p0 : m_iLen - 1);
		     /* until break or return */;
		     --t)
		{
			if (memchr (s, *t, n) != 0)
				return (t - m_pPtr);
			else if (t == m_pPtr)
				break;
		}
	}
	
return (NPOS);
}

