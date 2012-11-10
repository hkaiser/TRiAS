#include	"stdafx.h"

#ifdef LAFX_WINF_SEG
#pragma code_seg(LAFX_WINF_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define new DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

#ifndef	WIN32
#define	_tcsinc(p)	(++p)
#endif

static LPCTSTR pszMinus = "-";

static BOOL LAfxExtractPart( LPTSTR& pStart, LPTSTR& pEnd, int iSubString, TCHAR chSep, BOOL& bMinus )
{
	while (iSubString--)
	{
		pStart = _tcschr(pStart, chSep);
		if (pStart == NULL)
			return FALSE;
		pStart = _tcsinc( pStart );       // point past the separator
	}
	bMinus = FALSE;
	if( !_tcscmp( pStart, pszMinus ) )
	{
		bMinus = TRUE;
		pStart = _tcsinc( pStart );
	}
	pEnd = _tcschr(pStart, chSep);
	if( NULL == pEnd )
		pEnd = _tcschr( pStart, '\0' );
	return pEnd > pStart;
}

BOOL AFX_EXT_API LAfxExtractSubDouble(double& rResult, LPCTSTR lpszFullString, int iSubString, TCHAR chSep)
{
	if (lpszFullString == NULL)
		return FALSE;

	BOOL	bMinus;
	LPTSTR	pStart = (LPTSTR) lpszFullString;
	LPTSTR	pEnd;

	if( !LAfxExtractPart( pStart, pEnd, iSubString, chSep, bMinus ) )
		return FALSE;

	rResult = _tcstod( pStart, &pEnd );
	rResult = bMinus ? -rResult : rResult;
	return TRUE;
}

BOOL AFX_EXT_API LAfxExtractSubLong(long& rResult, LPCTSTR lpszFullString, int iSubString, TCHAR chSep)
{
	if (lpszFullString == NULL)
		return FALSE;

	BOOL	bMinus;
	LPTSTR	pStart = (LPTSTR) lpszFullString;
	LPTSTR	pEnd;

	if( !LAfxExtractPart( pStart, pEnd, iSubString, chSep, bMinus ) )
		return FALSE;

	rResult = _tcstol( pStart, &pEnd, 10 );
	rResult = bMinus ? -rResult : rResult;
	return TRUE;
}

static LPCTSTR pszNull = "0";
static LPCTSTR pszLX = "x";
static LPCTSTR pszBX = "X";

BOOL AFX_EXT_API LAfxExtractSubHex(long& rResult, LPCTSTR lpszFullString, int iSubString, TCHAR chSep)
{
	if (lpszFullString == NULL)
		return FALSE;

	BOOL	bMinus;
	LPTSTR	pStart = (LPTSTR) lpszFullString;
	LPTSTR	pEnd;

	if( !LAfxExtractPart( pStart, pEnd, iSubString, chSep, bMinus ) )
		return FALSE;

	if( !_tcscmp( pStart, pszNull ) && ( !_tcscmp( _tcsinc( pStart ), pszLX ) || !_tcscmp( _tcsinc( pStart ), pszBX ) ) )
	{
		pStart = _tcsinc( pStart );
		pStart = _tcsinc( pStart );
	}

	if( !( pEnd > pStart ) )
		return FALSE;

	rResult = _tcstol( pStart, &pEnd, 16 );
	rResult = bMinus ? -rResult : rResult;
	return TRUE;
}

BOOL AFX_EXT_API LAfxExtractSubBase(long& rResult, int iBase, LPCTSTR lpszFullString, int iSubString, TCHAR chSep)
{
	if (lpszFullString == NULL)
		return FALSE;

	BOOL	bMinus;
	LPTSTR	pStart = (LPTSTR) lpszFullString;
	LPTSTR	pEnd;

	if( !LAfxExtractPart( pStart, pEnd, iSubString, chSep, bMinus ) )
		return FALSE;

	rResult = _tcstol( pStart, &pEnd, iBase );
	rResult = bMinus ? -rResult : rResult;
	return TRUE;
}
