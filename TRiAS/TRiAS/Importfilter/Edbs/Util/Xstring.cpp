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

#include	<afxwin.h>
#include	<lafx.h>
#include	"stdafx.h"
#include	<ctype.h>

#include	"xstring.h"
#include	"stdio.h"
#include	"stdarg.h"

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif	// MAX_PTH

int CxString :: printf( const char *fmt, ... )
{	char	buf[512];
	va_list	args;

	va_start( args, fmt );
	int		ret = vsprintf( buf, fmt, args );
	*this += buf;
	va_end( args );
	return ret;
}	// printf


int CxString :: AppendF( const char *txt, short i )
{
	ASSERT( txt );

	CString	a = txt;

	if ( i > 0 )
	{
		while ( a.GetLength() < i )	a += ' ';
		if ( a.GetLength() > i )	a = a.Left( i );
	}
	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendF( int n, short i )
{
	CxString	a, t;
	a.printf( "%d", n );

	if ( i > 0 )
	{
		while ( a.GetLength() < i )
		{	t = " ";	t += a;	a = t;	}
	
		if ( a.GetLength() > i )
		{	a = "*";
			while ( a.GetLength() < i )	a += '*';
	}	}
	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendF( long n, short i )
{
	CxString	a, t;
	a.printf( "%ld", n );

	if ( i > 0 )
	{
		while ( a.GetLength() < i )
		{	t = " ";	t += a;	a = t;	}
	
		if ( a.GetLength() > i )
		{	a = "*";
			while ( a.GetLength() < i )	a += '*';
	}	}
	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendF( unsigned long n, short i )
{
	CxString	a, t;
	a.printf( "%u", n );

	if ( i > 0 )
	{
		while ( a.GetLength() < i )
		{	t = " ";	t += a;	a = t;	}
	
		if ( a.GetLength() > i )
		{	a = "*";
			while ( a.GetLength() < i )	a += '*';
	}	}
	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendF( CTime &t, short i )
{
	ASSERT( i );
	CString	a;

#if !defined(_AFXDLL) && !defined(_USRDLL)
	if ( i == 8 )		a = t.Format( "%d.%m.%y" );
	else if ( i == 10 )	a = t.Format( "%d.%m.%Y" );
	else if ( i == 4 )	a = t.Format( "%H:%M" );
	else if ( i == 18 )	a = t.Format( "%Y-%m-%d %H:%M:%S" );	// MFC:CTime
#else
	short	year;
	if (( i == 8 ) || ( i == 10 ))
	{
		if ( t.GetDay() < 10 )		printf( "0%d.", t.GetDay());
		else						printf( "%d.", t.GetDay());
		if ( t.GetMonth() < 10 )	printf( "0%d.", t.GetMonth());
		else						printf( "%d.", t.GetMonth());
		year = t.GetYear();
		if ( i == 8 )
		{	if ( year < 2000 )	year = year - 1900;
			else				year = year - 2000;
			if ( year < 10 ) 		printf( "0%d", year );
			else					printf( "%d", year );
		}
		else if ( i == 10 )
			printf( "%d", t.GetYear());
	}
	else if ( i == 4 )
	{
		if ( t.GetHour() < 10 )		printf( "0%d:", t.GetHour());
		else						printf( "%d:", t.GetHour());
		if ( t.GetMinute() < 10 )	printf( "0%d", t.GetMinute());
		else						printf( "%d", t.GetMinute());
	}
	else if ( i == 18 )
	{
//		a = t.Format( "%Y-%m-%d %H:%M:%S" );	// MFC:CTime
		printf( "%d-", t.GetYear());
		if ( t.GetMonth() < 10 )	printf( "0%d-", t.GetMonth());
		else						printf( "%d-", t.GetMonth());
		if ( t.GetDay() < 10 )		printf( "0%d ", t.GetDay());
		else						printf( "%d ", t.GetDay());
		if ( t.GetHour() < 10 )		printf( "0%d:", t.GetHour());
		else						printf( "%d:", t.GetHour());
		if ( t.GetMinute() < 10 )	printf( "0%d:", t.GetMinute());
		else						printf( "%d:", t.GetMinute());
		if ( t.GetSecond() < 10 )	printf( "0%d", t.GetSecond());
		else						printf( "%d", t.GetSecond());
	}
#endif //! DLL variant

	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendF( CTimeSpan &t, short i )
{
	ASSERT( i );
	CString	a;

	if ( t.GetTotalHours() < 10 )	printf( "0%d:", t.GetTotalHours());
	else							printf( "%d:", t.GetTotalHours());
	if ( t.GetMinutes() < 10 )		printf( "0%d", t.GetMinutes());
	else							printf( "%d", t.GetMinutes());

	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendF( float d, short i, short f )
{
	CxString	a, t;

	switch ( f )
	{
		case 1:
				a.printf( "%.1f", d );
				break;
		case 2:
				a.printf( "%.2f", d );
				break;
		case 3:
				a.printf( "%.3f", d );
				break;
		case 4:
				a.printf( "%.4f", d );
				break;
		case 0:
		default:
				a.printf( "%f", d );
				break;
	}

	if ( i > 0 )
	{
		while ( a.GetLength() < i )
		{
			t = " ";	t += a; a = t;
		}

		if ( a.GetLength() > i )
		{
			a = "*";
			while ( a.GetLength() < i )
				a += '*';
	}	}
	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendF( double d, short i, short f )
{
	CxString	a, t;

	switch ( f )
	{
		case 1:
				a.printf( "%.1lf", d );
				break;
		case 2:
				a.printf( "%.2lf", d );
				break;
		case 3:
				a.printf( "%.3lf", d );
				break;
		case 4:
				a.printf( "%.4lf", d );
				break;
		case 0:
				a.printf( "%.0lf", d );
				break;
		default:
				a.printf( "%lf", d );
				break;
	}

	if ( i > 0 )
	{
		while ( a.GetLength() < i )
		{
			t = " ";	t += a; a = t;
		}

		if ( a.GetLength() > i )
		{
			a = "*";
			while ( a.GetLength() < i )
				a += '*';
	}	}
	*this += a;
	return GetLength();
}	// AppendF

int CxString :: AppendFormated( int v, short l )
{	int	result = AppendF( v, l );
	FormatZahl( 0 );
	return result;
}

int CxString :: AppendFormated( long v, short l )
{	int	result = AppendF( v, l );
	FormatZahl( 0 );
	return result;
}

int CxString :: AppendFormated( float v, short l, short d, short x )
{	int	result = AppendF( v, l, d );
	FormatZahl( x );
	return result;
}

int CxString :: AppendFormated( double v, short l, short d, short x )
{	int	result = AppendF( v, l, d );
	FormatZahl( x );
	return result;
}

CString CxString :: Trimm()
{	while (( GetLength()) &&
	       ( GetAt( GetLength() - 1 ) == ' ' )) *this = Left( GetLength() - 1 );
	return *this;
}	// Trimm

CString CxString :: LTrimm()
{	while (( GetLength()) &&
		   ( GetAt( 0 ) == ' ' )) *this = Right( GetLength() - 1 );
	return *this;
}	// LTrimm

CString CxString :: AllTrimm()
{	Trimm();
	return LTrimm();
}	// AllTrimm

CString CxString::RemoveChar( char c )
{
	CxString	head, rest, temp;

	rest = *this;
	while ( !rest.IsEmpty())
	{
		rest.Teilen( head, rest, c );
		temp += head;
	}
	*this = temp;
	return *this;
}	// RemoveChar

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

CTime CxString :: GetDate()
{
	CTime	nulltime( 1997, 1, 1, 0, 0, 0 );
	short	tag, monat, jahr;
	char	t, h, z, j;

	if ( GetLength() < 8 ) return nulltime;
	if (( GetAt(2) == '.' ) && ( GetAt(5) == '.' ))	
	{
		tag = (GetAt(0) - '0') * 10 + (GetAt(1) - '0');
		monat = (GetAt(3) - '0') * 10 + (GetAt(4) - '0');
		t = GetAt(6);	h = GetAt(7);
		if ( GetLength() > 9 )
		{	z = GetAt(8);	j = GetAt(9);
			if (( z > '9' ) || ( z < '0' ) ||
				( j > '9' ) || ( j < '0' ))
			{	z = t - '0';	j = h - '0';
				t = 1;			h = 9;
				if ( z < 3 )
				{	t = 2; h = 0;
			}	}
			else
			{
				t -= '0';		h -= '0';
				z -= '0';		j -= '0';
		}	}
		else
		{	z = t - '0';	j = h - '0';
			t = 1;			h = 9;
			if ( z < 3 )
			{	t = 2; h = 0;
		}	}

		jahr = t * 1000 + h * 100 + z * 10 + j;
		if ( jahr < 1970 )	jahr = 1970;
		if ( jahr > 2037 )	jahr = 2037;

		return CTime( jahr, monat, tag, 23, 59, 59 );
	}

	return nulltime;
}	// GetDate

BOOL CxString::TestDate()
{
	short	tag, monat, jahr;
	char	t, h, z, j;

	if ( GetLength() < 8 ) return FALSE;
	if (( GetAt(2) == '.' ) && ( GetAt(5) == '.' ))	
	{
		tag = (GetAt(0) - '0') * 10 + (GetAt(1) - '0');
		monat = (GetAt(3) - '0') * 10 + (GetAt(4) - '0');
		t = GetAt(6);	h = GetAt(7);
		if ( GetLength() > 9 )
		{	z = GetAt(8);	j = GetAt(9);
			if (( z > '9' ) || ( z < '0' ) ||
				( j > '9' ) || ( j < '0' ))
			{	z = t - '0';	j = h - '0';
				t = 1;			h = 9;
				if ( z < 3 )
				{	t = 2; h = 0;
			}	}
			else
			{
				t -= '0';		h -= '0';
				z -= '0';		j -= '0';
		}	}
		else
		{	z = t - '0';	j = h - '0';
			t = 1;			h = 9;
			if ( z < 3 )
			{	t = 2; h = 0;
		}	}

		jahr = t * 1000 + h * 100 + z * 10 + j;
		if ( jahr < 1970 )	jahr = 1970;
		if ( jahr > 2037 )	jahr = 2037;

		return TRUE;
	}

	return FALSE;
}

int CxString :: GetProfileString( const char *section, const char *entry )
{
	CWinApp	*pApp = AfxGetApp();
	CString	temp;
	char	*txt;
	int		result = 0;

	ASSERT( pApp );

	txt = GetBuffer( MAX_PATH );
	temp = pApp -> GetProfileString( section, entry, txt );
	strcpy( txt, temp );
	ReleaseBuffer();
	result = GetLength();
	return result;
}	// GetProfileString

int CxString :: GetPrivateProfileString( const char *section, const char *entry, const char *file )
{
	char	*txt;
	int		result = 0;

	txt = GetBuffer( MAX_PATH );
	result = ::GetPrivateProfileString( section, entry, txt, txt, MAX_PATH - 1, file );
	ReleaseBuffer();
	return result;
}	// GetPrivateProfileString

BOOL CxString :: WriteProfileString( const char *section, const char *entry )
{
	BOOL	result = FALSE;

	CWinApp	*pApp = AfxGetApp();
	char	*txt;

	ASSERT( pApp );

	txt = GetBuffer( GetLength() + 1 );
	result = pApp -> WriteProfileString( section, entry, txt );
	ReleaseBuffer();
	return result;
}	// WriteProfileString

BOOL CxString :: WritePrivateProfileString( const char *section, const char *entry, const char *file )
{
	BOOL	result = FALSE;
	char	*txt;

	txt = GetBuffer( MAX_PATH );
	result = ::WritePrivateProfileString( section, entry, txt, file );
	ReleaseBuffer();
	return result;
}	// WritePrivateProfileString

int CxString :: ReadChars( CFile *file, short zahl )
{
	CString	temp;
	char	*txt;
	int		result = 0;

	txt = GetBuffer( MAX_PATH );

	TRY
	{	result = file -> Read( txt, zahl );
	}
	CATCH( CFileException, e )
	{	result = 0;
		#ifdef _DEBUG
			afxDump << "Kann aus Datei nicht lesen: " << e -> m_cause << "\n";
		#endif
	}
	END_CATCH

	txt[result] = '\0';
	ReleaseBuffer();

	return result;
}	// ReadChars

BOOL CxString :: LoadString( UINT nID, BOOL fromApp )
{
	if ( !fromApp )
		return CString::LoadString( nID );

	ASSERT( nID != 0 );
	TCHAR szBuffer[256];
	ASSERT( AfxIsValidAddress( szBuffer, 256 ));	// Groß genug für 256 Byte
	HINSTANCE hInst = AfxGetApp()->m_hInstance;
//	hInst = AfxGetResourceHandle();
//	hInst = AfxGetInstanceHandle();
//	hInst = g_hInstance;

//	UINT nSize = ::LoadString( g_hInstance, nID, szBuffer, 255 );
	UINT nSize = ::LoadString( hInst, nID, szBuffer, 255 );
	if ( nSize == 0 )
		szBuffer[0] = '\0';
	AssignCopy( nSize, szBuffer );
	return nSize > 0;
}	// LoadString

BOOL CxString :: FileExist()
{
	if ( IsEmpty())		return FALSE;

	BOOL			result = TRUE;
	CFileException	e;
	CString			name;
	CFile			file;

	name = m_pchData;
	file.Open( name, CFile::modeRead | CFile::shareDenyNone, &e );

	if ( e.m_cause != CFileException::none )	result = FALSE;
	else										file.Close();

	return result;
}

short CxString :: Short()
{
	return (short)atoi( m_pchData );
}	// Short

long CxString :: Long()
{
	return atol( m_pchData );
}	// Long

long CxString::FormatedLong()
{
	CxString	temp = *this;
	CString		kopf, bauch;

	bauch = kopf = temp;
	while ( !kopf.IsEmpty() && !bauch.IsEmpty())
	{
		temp.Teilen( kopf, bauch, '.' );
		temp = kopf;
		temp += bauch;
	}
	temp.Teilen( kopf, bauch, ',' );
	if ( !kopf.IsEmpty())
		temp = kopf;

	return temp.Long();
}

long CxString :: XLong()
{
	char	*stop;

	return strtol( m_pchData, &stop, 16 );
}	// Long

unsigned long CxString :: ULong()
{
	char	*stop;

	return strtoul( m_pchData, &stop, 10 );
}	// ULong

unsigned long CxString :: UXLong()
{
	char	*stop;

	return strtoul( m_pchData, &stop, 16 );
}	// UXLong

float CxString :: Float()
{
	return (float)atof( m_pchData );
}	// Float

double CxString :: Double()
{
	return atof( m_pchData );
}	// Double

double CxString::FormatedDouble()
{
	CxString	temp = *this;
	CString		kopf, bauch;

	bauch = kopf = temp;
	while ( !kopf.IsEmpty() && !bauch.IsEmpty())
	{
		temp.Teilen( kopf, bauch, '.' );
		temp = kopf;
		temp += bauch;
	}
	temp.Teilen( kopf, bauch, ',' );
	if ( !kopf.IsEmpty() && !bauch.IsEmpty())
	{
		temp = kopf;
		temp += '.';
		temp += bauch;
	}
	return temp.Double();
}	// FormatedDouble

void CxString :: FormatZahl( short dez )
{
	CString		ganz, bruch, rest, minus;
	CString		temp;

	Teilen( ganz, rest, '.' );
	if ( ganz.IsEmpty())	return;
	if ( ganz[0] == '-' )
	{
		minus = "-";
		ganz = ganz.Mid( 1 );
	}
	else
		minus.Empty();

	while ( !rest.IsEmpty() && isdigit( rest[0]))
	{
		bruch += rest[0];
		if ( rest.GetLength() > 1 )
			rest = rest.Mid( 1 );
		else
			rest.Empty();
	}
	if ( ganz.GetLength() > 12 )
	{
		temp = ganz.Left( ganz.GetLength() - 12 );
		temp += '.';
		temp += ganz.Mid( ganz.GetLength() - 12 );
		ganz = temp;
	}
	if ( ganz.GetLength() > 9 )
	{
		temp = ganz.Left( ganz.GetLength() - 9 );
		temp += '.';
		temp += ganz.Mid( ganz.GetLength() - 9 );
		ganz = temp;
	}
	if ( ganz.GetLength() > 6 )
	{
		temp = ganz.Left( ganz.GetLength() - 6 );
		temp += '.';
		temp += ganz.Mid( ganz.GetLength() - 6 );
		ganz = temp;
	}
	if ( ganz.GetLength() > 3 )
	{
		temp = ganz.Left( ganz.GetLength() - 3 );
		temp += '.';
		temp += ganz.Mid( ganz.GetLength() - 3 );
		ganz = temp;
	}
	while ( bruch.GetLength() < dez )	bruch += "0";
	if ( dez > 0 )
	{
		if ( bruch.GetLength() > dez )		bruch = bruch.Left( dez );
		ganz += ",";
		ganz += bruch;
	}
	if (( dez < 0 ) && ( bruch.GetLength() > 0 ))
	{
		if ( bruch.GetLength() > 6 )	bruch = bruch.Left( 6 );
		ganz += ",";
		ganz += bruch;
	}
	
	if ( !minus.IsEmpty())
		if (( atol( ganz ) == 0L ) && ( atol( rest ) == 0L ))
			minus.Empty();

	temp = minus;
	temp += ganz;
	temp += rest;
	*this = temp;
}	// FormatZahl


void PASCAL _SmartSetWindowText(HWND hWndCtrl, LPCSTR lpszNew)
{
	int nNewLen = lstrlen(lpszNew);
	char szOld[64];
	// fast check to see if text really changes (reduces flash in controls)
	if (nNewLen > sizeof(szOld) ||
		::GetWindowText(hWndCtrl, szOld, sizeof(szOld)) != nNewLen ||
		lstrcmp(szOld, lpszNew) != 0)
	{
		// change it
		::SetWindowText(hWndCtrl, lpszNew);
	}
}


void AFXAPI DDX_TextDouble(CDataExchange* pDX, int nIDC, double& value, int dez)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CxString	text;
	char		szT[64];

	if (pDX->m_bSaveAndValidate)
	{
		::GetWindowText(hWndCtrl, szT, sizeof(szT));
		text = szT;
		double d = text.FormatedDouble();

		value = d;
	}
	else
	{
		text.Empty();
		text.AppendF( value, -1, dez );
		text.FormatZahl( dez );
		_SmartSetWindowText(hWndCtrl, text);
	}
}	// DDX_TextDouble

void AFXAPI DDX_TextLong(CDataExchange* pDX, int nIDC, long& value)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CxString	text;
	char		szT[64];

	if (pDX->m_bSaveAndValidate)
	{
		::GetWindowText(hWndCtrl, szT, sizeof(szT));
		text = szT;
		long d = long( text.FormatedDouble());

		value = d;
	}
	else
	{
		text.Empty();
		text.AppendF( value, -1 );
		text.FormatZahl( 0 );
		_SmartSetWindowText(hWndCtrl, text);
	}
}	// DDX_TextLong
