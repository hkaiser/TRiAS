// strrfis -- string :: rfind(const char *, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// find rightmost substring in a string
size_t string :: rfind (const char *s, size_t p0, size_t n) const
{
	if (n == 0 || n == NPOS && (n = strlen(s)) == 0)
		return (0);
		
	if (n <= m_iLen) {
	// find rightmost substring in string
		for (const char *t = m_pPtr + (p0 < m_iLen - n ? p0 : m_iLen - n);
		     /* until break or return */;
		     --t)
		{
			if (*t == *s && memcmp (t, s, n) == 0)
				return (t - m_pPtr);
			else if (t == m_pPtr)
				break;
		}
	}
	
return (NPOS);
}

