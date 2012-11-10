// strasx -- string::assign(const string &, size_t, size_t)
#include <bool.h>
#include <string.h>

#include <tstring.hpp>

// assign a substring to a string
string &string :: assign (const string &str, size_t pos, size_t ns)
{
	if (str.length() < pos) _Xran();
		
size_t n = str.length() - pos;

	if (ns < n) n = ns;
	if (this == &str)
		remove (pos + n), remove(0, pos);
	else if (_Grow (n, 1)) {	// copy non-empty string
		memcpy (m_pPtr, &str.c_str()[pos], n);
		m_pPtr[m_iLen = n] = '\0'; 
	}
	
return (*this);
}

