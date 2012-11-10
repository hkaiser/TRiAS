// straps -- string::append(const char *, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// append an NTBS to a string
string & string :: append (const char *s, size_t ns)
{
	if (ns == NPOS) ns = strlen(s);
	if (NPOS - m_iLen <= ns) _Xlen();

size_t n;

	if (0 < ns && _Grow (n = m_iLen + ns)) {
	// append to make non-empty string
		memcpy (m_pPtr + m_iLen, s, ns);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}
