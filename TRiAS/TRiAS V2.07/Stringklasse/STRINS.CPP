// strins -- string :: insert(size_t, const char *, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// insert a NTBS into a string
string &string :: insert (size_t p0, const char *s, size_t ns)
{
	if (m_iLen < p0) _Xran();
	if (ns == NPOS) ns = strlen(s);
	if (NPOS - m_iLen <= ns) _Xlen();
	
size_t n;

	if (0 < ns && _Grow (n = m_iLen + ns)) {
	// insert to make non-empty string
		memmove (m_pPtr + p0 + ns, m_pPtr + p0, m_iLen - p0);
		memcpy (m_pPtr + p0, s, ns);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}

