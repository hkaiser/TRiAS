// strcoc -- string :: compare(char, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// compare a repeated char to a string
int string :: compare (char ch, size_t p0, size_t ns) const
{
	if (m_iLen < p0) _Xran();

size_t n = m_iLen - p0;
		
	for (const char *s = m_pPtr + p0, *t = s + (n < ns ? n : ns); s < t; ++s) {
		if (*s != ch)
			return (*(unsigned char *)s < (unsigned char)ch ? -1 : +1);
	}
				
return (n < ns ? -1 : n == ns ? 0 : +1);
}

