// strinc -- string :: insert(size_t, char, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// insert a repeated char into a string
string &string :: insert (size_t p0, char ch, size_t nr)
{
	if (m_iLen < p0) _Xran();
	if (NPOS - m_iLen <= nr) _Xlen();
	
size_t n;

	if (0 < nr && _Grow (n = m_iLen + nr)) {
	// insert to make non-empty string
		memmove (m_pPtr + p0 + nr, m_pPtr + p0, m_iLen - p0);
		memset (m_pPtr + p0, ch, nr);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}

