/**************************************************************************/
/*	Erweiterte CString-Klasse                                             */
/*------------------------------------------------------------------------*/
/*	Zus�tzliche Funktionen:                                               */
/*		printf      - Nachbildung von sprintf                             */
/*		MessageBox  - Den enthaltenen String als MessageBox ausgeben      */
/*		Trimm       - folgende Leerzeichen entfernen                      */
/*		LTrimm      - f�hrende Leerzeichen entfernen                      */
/*		AllTrimm    - f�hrende und folgende Leerzeichen entfernen         */
/*------------------------------------------------------------------------*/
/*	(c)	1995 Dr. Andreas Denkewitz                                        */
/*		unter Nutzung von Anregungen aus MS System Journal 03+04/94       */
/*                                                                        */
/*	Stand:    02/95                                                       */
/**************************************************************************/

#include	<afxwin.h>
#include	<lafx.h>
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
{	int		result;
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

long CxString :: Long()
{
	return atol( m_pchData );
}	// Long

double CxString :: Double()
{
	return atof( m_pchData );
}	// Double
