#ifndef _CSTRINGEX_H_
#define _CSTRINGEX_H_

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

class CStringEx : public CString
{
public:
	// Konstruktoren
	CStringEx() : CString()								{}
	CStringEx( const CString& s ) : CString( s )			{}
	CStringEx( char c, int n = 1 ) : CString( c, n )		{}
	CStringEx( const char* p ) : CString( p )			{}
	CStringEx( const char* p, int n ) : CString( p, n )	{}
	CStringEx( const int i );

	// ohne die speziellen _NEARDATA - Definitionen
	char operator[](int nIndex) const
		{ return CString::GetAt( nIndex ); }
	operator const char*() const
		{ return CString::operator const char*(); }
	
	// Zuweisungen
	const CStringEx& operator= ( const CString& str )
		{ CString::operator= ( str ); return *this; }
	const CStringEx& operator= ( const CStringEx& str )
		{ CString::operator= ( (CString&)str ); return *this; }
	const CStringEx& operator= ( char c )
		{ CString::operator= ( c ); return *this; }
	const CStringEx& operator= ( const char* p )
		{ CString::operator= ( p ); return *this; }

	// Zuweisung mit Erweiterung
	const CStringEx& operator+= ( const CString& s )
		{ CString::operator+=( s ); return *this; }
	const CStringEx& operator+= ( char c )
		{ CString::operator+=( c ); return *this; }
	const CStringEx& operator+= ( const char* p )
		{ CString::operator+=( p ); return *this; }

//	friend CStringEx AFXAPI operator+(const CString& string1, const CString& string2)
//	friend CStringEx AFXAPI operator+(const CString& string, char ch);
//	friend CStringEx AFXAPI operator+(char ch, const CString& string);
//	friend CStringEx AFXAPI operator+(const CString& string, const char* psz);
//	friend CStringEx AFXAPI operator+(const char* psz, const CString& string);


	// Zusätzlich
	int			printf( const char *fmt, ... );
	int			MessageBox( CWnd*, const char* = NULL, int = MB_OK );

//	void		Trimm();
//	void		LTrimm();
	void		TrimAll();
	void		Transform();

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

	int			Integer();
	long		Long();
	double		Double();
};

#endif // _CXSTRING_H_