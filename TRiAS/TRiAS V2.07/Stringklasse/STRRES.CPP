// strres -- string::replace(size_t, size_t, const char *, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// replace with an NTBS char in a string
string &string :: replace (size_t p0, size_t n0, const char *s, size_t ns)
{
	if (m_iLen < p0) _Xran();
	if (ns == NPOS) ns = strlen(s);
	if (NPOS - ns <= m_iLen - n0) _Xlen();
	
size_t nm = m_iLen - n0 - p0;
size_t n;

	if (ns < n0)
		memmove (m_pPtr + p0 + ns, m_pPtr + p0 + n0, nm);
	if ((0 < ns || 0 < n0) && _Grow (n = m_iLen + ns - n0)) {
	// replace to make non-empty string
		if (n0 < ns)
			memmove (m_pPtr + p0 + ns, m_pPtr + p0 + n0, nm);
		memcpy (m_pPtr + p0, s, ns);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}
