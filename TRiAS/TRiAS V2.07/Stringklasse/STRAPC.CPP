// strapc -- string::append(char, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// append repeated char to a string
string & string :: append (char ch, size_t nr)
{
	if (NPOS - m_iLen <= nr) _Xlen();

size_t n;

	if (0 < nr && _Grow (n = m_iLen + nr)) {	
	// append to make non-empty string
		memset (m_pPtr + m_iLen, ch, nr);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}
