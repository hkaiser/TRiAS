// strinx -- string :: insert(size_t, const string &, size_t, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// insert a substring into a string
string &string :: insert (size_t p0, const string &str, size_t pos, size_t ns)
{
	if (m_iLen < p0 || str.length() < pos) _Xran();
	
size_t n = str.length() - pos;

	if ( n < ns) ns = n;
	if (NPOS - m_iLen <= ns) _Xlen();

	if (0 < ns && _Grow (n = m_iLen + ns)) {
	// insert to make non-empty string
		memmove (m_pPtr + p0 + ns, m_pPtr + p0, m_iLen - p0);
		memcpy (m_pPtr + p0, &str.c_str()[pos], ns);
		m_pPtr[m_iLen = n] = '\0';
	}
	
return (*this);
}

