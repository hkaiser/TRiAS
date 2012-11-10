// strrem -- string::remove(size_t, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// remove a substring
string &string :: remove (size_t p0, size_t nr)
{
	if (m_iLen < p0) _Xran();
	if (m_iLen - p0 < nr) nr = m_iLen - p0;
	
	if (0 < nr) {
	// remove the substring
		memmove (m_pPtr + p0, m_pPtr + p0 + nr, m_iLen - p0 - nr);
	
	size_t n = m_iLen - nr;
	
		if (_Grow (n)) m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}
