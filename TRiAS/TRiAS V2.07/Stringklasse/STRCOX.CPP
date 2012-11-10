// strcox -- string :: compare(const string &, size_t, size_t)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// compare an NTBS to a string
int string :: compare (const string &str, size_t p0, size_t ns) const
{
	if (m_iLen < p0) _Xran();

size_t n = m_iLen - p0;
		
	if (str.length() < ns) ns = str.length();
	
size_t ans = memcmp (m_pPtr + p0, str.c_str(), n < ns ? n : ns);

	return (ans != 0 ? ans : n < ns ? -1 : n == ns ? 0 : +1);
}

