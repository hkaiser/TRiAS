// strput -- string :: put_at (size_t, char ch)
#include <bool.h>
#include <string.h>
#include <tstring.hpp>

// put element to a string
void string :: put_at (size_t p0, char ch) 
{
	if (m_iLen <= p0) _Xran();
	else if (m_iLen == p0)
		append (ch);
	else
		m_pPtr[p0] = ch;
}
