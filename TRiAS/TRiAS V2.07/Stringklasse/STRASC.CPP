// strasc -- string::assign(char, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// assign a repeated char to a string
string &string :: assign (char ch, size_t n)
{
	if (n == NPOS) _Xlen();
	if (_Grow (n, 1)) {	// copy non-empty string
		memset (m_pPtr, ch, n);
		m_pPtr[m_iLen = n] = '\0'; 
	}
	
return (*this);
}

