// strcos -- string :: compare(const char *, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// compare an NTBS to a string
int string :: compare (const char *s, size_t p0, size_t ns) const
{
	if (m_iLen < p0) _Xran();

size_t n = m_iLen - p0;
		
	if (ns == NPOS) ns = strlen(s);
	
size_t ans = memcmp (m_pPtr + p0, s, n < ns ? n : ns);

	return (ans != 0 ? ans : n < ns ? -1 : n == ns ? 0 : +1);
}

