// strrec -- string::replace(size_t, size_t, char, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// replace with a repeated char in a string
string &string :: replace (size_t p0, size_t n0, char ch, size_t nr)
{
	if (m_iLen < p0) _Xran();
	if (m_iLen - p0 < n0) n0 = m_iLen - p0;
	if (NPOS - nr <= m_iLen - n0) _Xlen();
	
size_t nm = m_iLen - n0 - p0;
size_t n;

	if (nr < n0)
		memmove (m_pPtr + p0 + nr, m_pPtr + p0 + n0, nm);
	if ((0 < nr || 0 < n0) && _Grow (n = m_iLen + nr - n0)) {
	// replace to make non-empty string
		if (n0 < nr)
			memmove (m_pPtr + p0 + nr, m_pPtr + p0 + n0, nm);
		memset (m_pPtr + p0, ch, nr);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}
