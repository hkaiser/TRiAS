// strapx -- string::append (const string &, size_t, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// append a substring to a string
string & string :: append (const string &str, size_t pos, size_t ns)
{
	if (str.length() < pos) _Xran();

size_t n = str.length() - pos;

	if (n < ns) ns = n;
	if (NPOS - m_iLen <= ns) _Xlen();

	if (0 < ns && _Grow (n = m_iLen + ns)) {	
	// append to make non-empty string
		memcpy (m_pPtr + m_iLen, &str.c_str()[pos], ns);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}
