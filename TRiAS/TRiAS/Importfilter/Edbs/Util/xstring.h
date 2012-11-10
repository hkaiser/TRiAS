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

#ifndef _CXSTRING_H_
#define _CXSTRING_H_

class CxString : public CString
{
public:
	long FormatedLong();
	BOOL TestDate();
	// Konstruktoren
				CxString() : CString()								{}
				CxString( const CString& s ) : CString( s )			{}
				CxString( char c, int n = 1 ) : CString( c, n )		{}
				CxString( const char* p ) : CString( p )			{}
				CxString( const char* p, int n ) : CString( p, n )	{}
	// ohne die speziellen _NEARDATA - Definitionen
	char operator[](int nIndex) const
		{ return CString::GetAt( nIndex ); }
	operator const char*() const
		{ return CString::operator const char*(); }
	
	// Zuweisungen
	const CxString& operator= ( const CString& str )
		{ CString::operator= ( str ); return *this; }
	const CxString& operator= ( const CxString& str )
		{ CString::operator= ( (CString&)str ); return *this; }
	const CxString& operator= ( char c )
		{ CString::operator= ( c ); return *this; }
	const CxString& operator= ( const char* p )
		{ CString::operator= ( p ); return *this; }

	// Zuweisung mit Erweiterung
	const CxString& operator+= ( const CString& s )
		{ CString::operator+=( s ); return *this; }
	const CxString& operator+= ( char c )
		{ CString::operator+=( c ); return *this; }
	const CxString& operator+= ( const char* p )
		{ CString::operator+=( p ); return *this; }

//	friend CxString AFXAPI operator+(const CString& string1, const CString& string2)
//	friend CxString AFXAPI operator+(const CString& string, char ch);
//	friend CxString AFXAPI operator+(char ch, const CString& string);
//	friend CxString AFXAPI operator+(const CString& string, const char* psz);
//	friend CxString AFXAPI operator+(const char* psz, const CString& string);


	// Zusätzlich
	int			printf( const char *fmt, ... );
	int			AppendF( const char*, short );
	int			AppendF( int, short );
	int			AppendF( long, short );
	int			AppendF( unsigned long, short );
	int			AppendF( CTime&, short );
	int			AppendF( CTimeSpan&, short );
	int			AppendF( float, short, short );
	int			AppendF( double, short, short );

	int			AppendFormated( int, short );
	int			AppendFormated( long, short );
	int			AppendFormated( float, short, short, short );
	int			AppendFormated( double, short, short, short );

	void		FormatZahl( short );
//	int			MessageBox( int type = MB_OK, const char *cap = NULL )
//		{ return MessageBox( NULL, (const char *&)(*this), cap, type ); }

	CString		Trimm();
	CString		LTrimm();
	CString		AllTrimm();
	BOOL		Teilen( CString&, CString&, char = ',', BOOL = TRUE );
	BOOL		Teilen( CString&, CString&, const char*, BOOL = TRUE );
	CString		RemoveChar( char );

	CTime		GetDate();

	int			GetProfileString( const char*, const char* );
	int			GetPrivateProfileString( const char*, const char*, const char* );
	BOOL		WriteProfileString( const char*, const char* );
	BOOL		WritePrivateProfileString( const char*, const char*, const char* );

	int			ReadChars( CFile*, short );

	BOOL		LoadString( UINT nID ) { return CString::LoadString( nID ); }
	BOOL		LoadString( UINT nID, BOOL fromApp );
	BOOL		FileExist();

	short		Short();
	long		Long();
	long		XLong();
	ULONG		ULong();
	ULONG		UXLong();
	float		Float();
	double		Double();
	double		FormatedDouble();
};

// einige nachgenutzte bzw. leicht abgewandelte Funktionen aus den MFC

void PASCAL _SmartSetWindowText(HWND hWndCtrl, LPCSTR lpszNew);
void AFXAPI DDX_TextDouble(CDataExchange* pDX, int nIDC, double& value, int dez = 2);
void AFXAPI DDX_TextLong(CDataExchange* pDX, int nIDC, long& value);

#endif	// _CXSTRING_H_
