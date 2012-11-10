// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 13.06.2001 18:30:26 
//
// @doc
// @module DLibWrapper.h | Declaration of the ATL ODP wrapper
// (eigene Implementationen f¸r AtlTrace etc.)

#if !defined(_DLIBWRAPPER_H__857E6B78_6DFF_48D6_A54F_588FEBB8CBDF__INCLUDED_)
#define _DLIBWRAPPER_H__857E6B78_6DFF_48D6_A54F_588FEBB8CBDF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(USE_DLIB) && defined(_OVERLOAD_ATLTRACE)

#include <crtdbg.h>

#undef ATLTRACE
#undef ATLTRACE2

#define ATLTRACE	CAtlTrace(__FILE__, __LINE__)
#define ATLTRACE2	CAtlTrace2(__FILE__, __LINE__)

class CAtlTrace
{
public:
	CAtlTrace(const char *pcFile, int iLine) :
		m_iLine(iLine)
	{
		strcpy(m_cbFile, pcFile);
	}
	void __cdecl operator() (const char *lpszFormat, ...)
	{
		va_list args;
		va_start(args, lpszFormat);

		int nBuf;
		char szBuffer[512];

		nBuf = _vsnprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);
		_ASSERTE(nBuf < sizeof(szBuffer)); //Output truncated as it was > sizeof(szBuffer)

	// ggf. abschlieﬂendes '\n' abschneiden
	int iLen = strlen(szBuffer);

		if ('\n' == szBuffer[iLen-1])
			szBuffer[iLen-1] = '\0';
					
		D_OUTF1_EX(m_cbFile, m_iLine, 1, "%s", szBuffer);
		va_end(args);
	}

protected:
	char m_cbFile[260];
	int m_iLine;
};

class CAtlTrace2 :
	public CAtlTrace
{
public:
	CAtlTrace2(const char *pcFile, int iLine) :
		CAtlTrace(pcFile, iLine)
	{
	}
	void __cdecl operator()(unsigned long category, int level, const char *lpszFormat, ...)
	{
		if (category & ATL_TRACE_CATEGORY && level <= ATL_TRACE_LEVEL)
		{
			va_list args;
			va_start(args, lpszFormat);

		int nBuf;
		char szBuffer[512];

			nBuf = _vsnprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);
			_ASSERTE(nBuf < sizeof(szBuffer)); //Output truncated as it was > sizeof(szBuffer)

		// ggf. abschlieﬂendes '\n' abschneiden
		int iLen = strlen(szBuffer);

			if ('\n' == szBuffer[iLen-1])
				szBuffer[iLen-1] = '\0';
						
			D_OUTF1_EX(m_cbFile, m_iLine, level, "ATL: %s", szBuffer);
			va_end(args);
		}
	}
};

#endif // defined(USE_DLIB) && defined(_OVERLOAD_ATLTRACE)

#endif // !defined(_DLIBWRAPPER_H__857E6B78_6DFF_48D6_A54F_588FEBB8CBDF__INCLUDED_)
