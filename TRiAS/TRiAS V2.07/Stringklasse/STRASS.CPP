// strass -- string::assign(const char *, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// assign a NTBS to a string
string &string :: assign (const char *s, size_t n)
{
	if (n == NPOS) n = strlen(s);
	if (_Grow (n, 1)) {	// copy non-empty string
		memcpy (m_pPtr, s, n);
		m_pPtr[m_iLen = n] = '\0'; 
	}
	
return (*this);
}

