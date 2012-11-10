// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/01/1998 09:10:03 AM
//
// @doc
// @module FormatString.cpp | Formatfunktion für 'string'

#include "idntsdbp.hxx"

#include <stdio.h>
#include <stdarg.h>
#define _TRIAS02_ENTRY
#include <FormatString.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
// CString formatting
#define TCHAR_ARG   TCHAR
#define WCHAR_ARG   WCHAR
#define CHAR_ARG    char
#define DOUBLE_ARG  double

#define FORCE_ANSI      0x10000
#define FORCE_UNICODE   0x20000

///////////////////////////////////////////////////////////////////////////////////////////////
// Pendant zu wsprintf() für string-Parameter;
// die in beliebiger Anzahl übergebenen Parameter werden auf den Stack gelegt
void __cdecl Format (string& rStr, LPCTSTR lpszFormat, ...)
{
va_list argList;

	va_start(argList, lpszFormat);
	FormatV(rStr, lpszFormat, argList);
	va_end(argList);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Pendant zu wsprintf() für string-Parameter;
// im Unterschied zu Format() werden hier die übergebenen Parameter auf den Stack erwartet;
// der Hauptteil dieser Routine beschäftigt sich damit, die Zeichenanzahl für den char*-Puffer
// pTmp zu ermitteln, der dann nur noch an die Bibliotheksfunktion _vstprintf() übergeben wird
void FormatV (string& rStr, LPCTSTR lpszFormat, va_list argList)
{
va_list argListSave = argList;

// make a guess at the maximum length of the resulting string
int nMaxLen = 0;

	for (LPCTSTR lpsz = lpszFormat; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
	{
		// handle '%' character, but watch out for '%%'
		if (*lpsz != '%' || *(lpsz = _tcsinc(lpsz)) == '%')
		{
			nMaxLen += _tclen(lpsz);
			continue;
		}

	int nItemLen = 0;

	// handle '%' character with format
	int nWidth = 0;

		for (; *lpsz != '\0'; lpsz = _tcsinc(lpsz))
		{
			// check for valid flags
			if (*lpsz == '#')
				nMaxLen += 2;   // for '0x'
			else if (*lpsz == '*')
				nWidth = va_arg(argList, int);
			else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0' ||
				*lpsz == ' ')
				;
			else // hit non-flag character
				break;
		}
		// get width and skip it
		if (nWidth == 0)
		{
			// width indicated by
			nWidth = _ttoi(lpsz);
			for (; *lpsz != '\0' && _istdigit(*lpsz); lpsz = _tcsinc(lpsz))
				;
		}
		TX_ASSERT (nWidth >= 0);

	int nPrecision = 0;

		if (*lpsz == '.')
		{
			// skip past '.' separator (width.precision)
			lpsz = _tcsinc(lpsz);

			// get precision and skip it
			if (*lpsz == '*')
			{
				nPrecision = va_arg(argList, int);
				lpsz = _tcsinc(lpsz);
			}
			else
			{
				nPrecision = _ttoi(lpsz);
				for (; *lpsz != '\0' && _istdigit(*lpsz); lpsz = _tcsinc(lpsz))
					;
			}
			TX_ASSERT (nPrecision >= 0);
		}

	// should be on type modifier or specifier
	int nModifier = 0;

		switch (*lpsz)
		{
		// modifiers that affect size
		case 'h':
			nModifier = FORCE_ANSI;
			lpsz = _tcsinc(lpsz);
			break;
		case 'l':
			nModifier = FORCE_UNICODE;
			lpsz = _tcsinc(lpsz);
			break;

		// modifiers that do not affect size
		case 'F':
		case 'N':
		case 'L':
			lpsz = _tcsinc(lpsz);
			break;
		}

		// now should be on specifier
		switch (*lpsz | nModifier)
		{
		// single characters
		case 'c':
		case 'C':
			nItemLen = 2;
			va_arg(argList, TCHAR_ARG);
			break;
		case 'c'|FORCE_ANSI:
		case 'C'|FORCE_ANSI:
			nItemLen = 2;
			va_arg(argList, CHAR_ARG);
			break;
		case 'c'|FORCE_UNICODE:
		case 'C'|FORCE_UNICODE:
			nItemLen = 2;
			va_arg(argList, WCHAR_ARG);
			break;

		// strings
		case 's':
			{
			LPCTSTR pstrNextArg = va_arg(argList, LPCTSTR);

				if (pstrNextArg == NULL)
				   nItemLen = 6;  // "(null)"
				else
				{
				   nItemLen = lstrlen(pstrNextArg);
				   nItemLen = max(1, nItemLen);
				}
				break;
			}

		case 'S':
			{
#ifndef _UNICODE
			LPWSTR pstrNextArg = va_arg(argList, LPWSTR);

				if (pstrNextArg == NULL)
				   nItemLen = 6;  // "(null)"
				else
				{
				   nItemLen = wcslen(pstrNextArg);
				   nItemLen = max(1, nItemLen);
				}
#else
			LPCSTR pstrNextArg = va_arg(argList, LPCSTR);

				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = lstrlenA(pstrNextArg);
				   nItemLen = max(1, nItemLen);
				}
#endif
				break;
			}

		case 's'|FORCE_ANSI:
		case 'S'|FORCE_ANSI:
			{
			LPCSTR pstrNextArg = va_arg(argList, LPCSTR);

				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = lstrlenA(pstrNextArg);
				   nItemLen = max(1, nItemLen);
				}
				break;
			}

		case 's'|FORCE_UNICODE:
		case 'S'|FORCE_UNICODE:
			{
			LPWSTR pstrNextArg = va_arg(argList, LPWSTR);

				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = wcslen(pstrNextArg);
				   nItemLen = max(1, nItemLen);
				}
				break;
			}
		}

		// adjust nItemLen for strings
		if (nItemLen != 0)
		{
			nItemLen = max(nItemLen, nWidth);
			if (nPrecision != 0)
				nItemLen = min(nItemLen, nPrecision);
		}
		else
		{
			switch (*lpsz)
			{
			// integers
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				va_arg(argList, int);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			case 'e':
			case 'f':
			case 'g':
			case 'G':
				va_arg(argList, DOUBLE_ARG);
				nItemLen = 128;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			case 'p':
				va_arg(argList, void*);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			// no output
			case 'n':
				va_arg(argList, int*);
				break;

			default:
				TX_ASSERT (false);  // unknown formatting option
				break;
			}
		}

		// adjust nMaxLen for output nItemLen
		nMaxLen += nItemLen;
	} // for


TCHAR* pTmp = NULL;

	try { pTmp = new TCHAR[nMaxLen+1]; } catch(...) {}

	if (NULL != pTmp)
	{
	int iLen = _vstprintf(pTmp, lpszFormat, argListSave);

		TX_ASSERT (iLen <= nMaxLen);
		rStr = pTmp;
		delete [] pTmp;
	}

	va_end(argListSave);

} // FormatV
