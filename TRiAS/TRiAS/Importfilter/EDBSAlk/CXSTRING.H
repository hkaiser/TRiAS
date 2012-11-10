#ifndef _CXSTRING_H_
#define _CXSTRING_H_

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

class CxString : public CString
{
public:
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
	int			MessageBox( CWnd*, const char* = NULL, int = MB_OK );

//	void		Trimm();
//	void		LTrimm();
	void		TrimAll();
	void		Transform(short sCodePage);

	int			AnzahlZiffern();
	int			AnzahlHexZiffern();

	int			Replace( const char*, const char* );

	BOOL		Teilen( CString&, CString&, char = ',', BOOL = TRUE );
	BOOL		Teilen( CString&, CString&, const char*, BOOL = TRUE );
	int			GetPrivateProfileString( const char*, const char*, const char*,
							int, const char* );
	BOOL		WritePrivateProfileString( const char*, const char*, const char* );
	BOOL		LoadString( UINT nID ) { return CString::LoadString( nID ); }
	BOOL		LoadString( UINT nID, BOOL fromApp );

	long		Long();
	unsigned long xtoul();
	double		Double();
};

#endif // _CXSTRING_H_