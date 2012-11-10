// string -- string basic members
#include <bool.h>
#include <stdlib.h>
#include <string.h>

#include <tstring.hpp>

const size_t MIN_SIZE = 31;		// 2 ^ N -1

// grow a string as needed
_Bool string :: _Grow (size_t n, _Bool trim)
{
size_t osize = m_pPtr == 0 ? 0 : m_iRes;

	if (n == 0) {		// set up null string
		if (trim && MIN_SIZE < osize) 
			_Tidy (1);
		else if (m_pPtr != 0)
			m_pPtr[m_iLen = 0] = '\0';
		return (0);
	} 
	else if (n == osize || n < osize && !trim)
		return (1);
	else {
	// grow or alter the string
	size_t size = m_pPtr == 0 && n < m_iRes ? m_iRes : n;
	
		if ((size |= MIN_SIZE) == NPOS)
			--size;
	
	char *s;
	
		if ((s = (char *)realloc(m_pPtr, size +1)) == 0
		     && (s = (char *)realloc (m_pPtr, (size = n) +1)) == 0)
		     	_Nomemory();
		m_pPtr = s;
		m_iRes = size;
		return (1);
	}
}

// destroy any allocated string storage
void string :: _Tidy (_Bool constructed)
{
	if (constructed && m_pPtr != 0)
		free (m_pPtr);
	m_pPtr = 0, m_iLen = 0, m_iRes = 0;
}

	
	
