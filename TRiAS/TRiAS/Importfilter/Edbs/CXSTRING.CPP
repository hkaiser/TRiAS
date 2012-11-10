/**************************************************************************/
/*	Erweiterte CString-Klasse                                             */
/*------------------------------------------------------------------------*/
/*	Zusätzliche Funktionen:                                               */
/*		printf      - Nachbildung von sprintf                             */
/*		MessageBox  - Den enthaltenen String als MessageBox ausgeben      */
/*		Trimm       - folgende Leerzeichen entfernen                      */
/*		LTrimm      - führende Leerzeichen entfernen                      */
/*		AllTrimm    - führende und folgende Leerzeichen entfernen         */
/*------------------------------------------------------------------------*/
/*	(c)	1995 Dr. Andreas Denkewitz                                        */
/*		unter Nutzung von Anregungen aus MS System Journal 03+04/94       */
/*                                                                        */
/*	Stand:    02/95                                                       */
/**************************************************************************/

//#include	<afxwin.h>
//#include	<lafx.h>
#include	"stdafx.h"

#include	"cxstring.h"
#include	<stdio.h>
#include	<stdarg.h>
#include	<math.h>
#include	<stdlib.h>
#include	<ctype.h>

int CxString :: printf( const char *fmt, ... )
{	char	buf[512];
	va_list	args;

	va_start( args, fmt );
	int		ret = vsprintf( buf, fmt, args );
	*this = buf;
	va_end( args );
	return ret;
}	// printf


void CxString :: Trimm()
{	while (( GetLength()) &&
	       ( GetAt( GetLength() - 1 ) == ' ' )) *this = Left( GetLength() - 1 );
}	// Trimm

void CxString :: LTrimm()
{	while (( GetLength()) &&
		   ( GetAt( 0 ) == ' ' )) *this = Right( GetLength() - 1 );
}	// LTrimm

void CxString :: AllTrimm()
{	Trimm();
	LTrimm();
}	// AllTrimm

BOOL CxString :: Teilen( CString& h, CString& r, const char* pat, BOOL trimmen )
{
	CxString	head = h;
	CxString	rest = r;
	BOOL		result = FALSE;

	ASSERT( AfxIsValidString( pat ));
	if ( *pat == '\0' )
	{
		head = *this;
		rest = "";

		if ( trimmen )
		{
			head.AllTrimm();
			rest.AllTrimm();
		}
		h = head;
		r = rest;
		return TRUE;
	}
	if ( *(pat + 1 ) == '\0' )
		return Teilen( h, r, *pat, trimmen );

	int			i = Find( pat );
	int			len = lstrlen( pat );

	if ( len >= GetLength())
		return FALSE;

	if ( i >= 0 )
	{	if ( i == 0 )	// pat steht am Anfang
		{
			head.Empty();
			rest = Mid( len );
		}
		else
		{
			head = Left( i );
			if (( i + len ) < GetLength())
				rest = Mid( i + len );
			else
				rest = "";
			result = TRUE;
	}	}
	else
	{	// pat nicht gefunden!
		head = *this;
		rest.Empty();
	}

	if ( trimmen )
	{	head.AllTrimm();
		rest.AllTrimm();
	}

	h = head;
	r = rest;
	return result;
}	// Teilen

BOOL CxString :: Teilen( CString& h, CString& r, char c, BOOL trimmen )
{	int			i = Find( c );
	CxString	head = h;
	CxString	rest = r;
	BOOL		result = FALSE;

	if ( i >= 0 )
	{	if ( i == 0 )	// c ist erstes Zeichen
		{	head.Empty();
			rest = Mid( 1 );
		}
		else
		{	head = Left( i );
			rest = Mid( i + 1 );
			result = TRUE;
	}	}
	else
	{	// Zeichen nicht gefunden!
		head = *this;
		rest.Empty();
	}

	if ( trimmen )
	{	head.AllTrimm();
		rest.AllTrimm();
	}

	h = head;
	r = rest;
	return result;
}	// Teilen

int CxString :: GetPrivateProfileString( const char *sec, const char *ent,
				const char *def, int size, const char *file )
{	int		result = size;
	char	*text;

	ASSERT( def );
	ASSERT( file );

	if ( result <= 10 ) result = 10;
	text = GetBuffer( result );
	result = ::GetPrivateProfileString( sec, ent, def, text, result, file );
	ReleaseBuffer();
	return result;
}	// GetPrivateProfileString

BOOL CxString :: WritePrivateProfileString( const char *sec, const char *ent,
					const char *file )
{	BOOL	result;

	ASSERT( file );

	result = ::WritePrivateProfileString( sec, ent, m_pchData, file );
	return result;
}	// WritePrivateProfileString

int CxString :: AnzahlZiffern()
{	int			result = 0;
	char		*txt;

	txt = m_pchData;
	while ( txt )
	{	if ( *txt && isdigit( *txt ))	result++;
		else							txt = NULL;
		if ( txt )
		{	txt++;
			if ( *txt == '\0' )	txt = NULL;
	}	}
	return result;
}	// AnzahlZiffern

int CxString :: AnzahlHexZiffern()
{	int			result = 0;
	char		*txt;

	txt = m_pchData;
	while ( txt )
	{	if ( *txt && isxdigit( *txt ))	result++;
		else							txt = NULL;
		if ( txt )
		{	txt++;
			if ( *txt == '\0' )	txt = NULL;
	}	}
	return result;
}	// AnzahlHexZiffern

int CxString :: MessageBox( CWnd *parent, const char *cap, int type )
{	CString		caption;
	int			result;

	if ( cap )
		caption = cap;
	else
		caption = "Nachricht";

	if ( parent )
	{	ASSERT( parent -> IsKindOf( RUNTIME_CLASS( CWnd )));
		result = parent -> MessageBox( m_pchData, cap, type );
	}
	else
		result = ::MessageBox( NULL, m_pchData, cap, type );

	return result;
}	// MessageBox


int CxString :: Replace( const char* alt, const char* neu )
{
int		result;
CString	anfang, ende, Alt;

	ASSERT( alt );
	ASSERT( neu );

	anfang.Empty();
	ende.Empty();
	Alt = alt;

	result = Find( alt );
	if ( result >= 0 )
	{	if ( result )	anfang = Left( result );
		if (( result + Alt.GetLength()) < GetLength())
			ende = Mid( result + Alt.GetLength());
		*this = anfang;
		*this += neu;
		*this += ende;
	}

	return result;
}	// Replace

BOOL CxString :: LoadString( UINT nID, BOOL fromApp )
{
	if ( !fromApp )
		return CString::LoadString( nID );

	ASSERT( nID != 0 );
	TCHAR szBuffer[256];
//	UINT nSize = AfxLoadString( nID, szBuffer );
	ASSERT( AfxIsValidAddress( szBuffer, 256 ));	// Groß genug für 256 Zeichen?

#ifdef _DEBUG
//	if ( ::FindResource( AfxGetApp()->m_hInstance, MAKEINTRESOURCE(( nID>>4 )+1), RT_STRING) == NULL )
//	{	szBuffer[0] = '\0';
//		return 0;	// nicht gefunden
//	}
#endif	// _DEBUG

//HINSTANCE hInst = AfxGetApp()->m_hInstance;
//
//	hInst = AfxGetResourceHandle();
//	hInst = AfxGetInstanceHandle();
//	hInst = g_hInstance;

	UINT nSize = ::LoadString( g_hInstance, nID, szBuffer, 255 );
	if ( nSize == 0 )
		szBuffer[0] = '\0';
	AssignCopy( nSize,szBuffer );
	return nSize > 0;
}	// LoadString

long CxString :: Long()
{
	return atol( m_pchData );
}	// Long

double CxString :: Double()
{
	return atof( m_pchData );
}	// Double
