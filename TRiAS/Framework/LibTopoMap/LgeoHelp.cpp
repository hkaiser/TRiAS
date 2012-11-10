#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// various outpustream formatting

ostream& os_format_dms( ostream& os, double dms ) {
	double	d, m, s;
	bool	bNeg = dms < 0 ? true : false;
	dms = fabs( dms );
	dms /= 3600; d = floor( dms ); dms = ( dms - d ) * 3600;
	dms /= 60;   m = floor( dms ); dms = ( dms - m ) * 60;
	s = dms;
	if( bNeg ) {
		os << '-';
	}
	os.width(2); os.fill('0'); os << d << '°';
	os.width(2); os.fill('0'); os << m << '\'';
	os.flags( os.flags() | ios::fixed ); os.precision(4);
	os.width(2); os.fill('0'); os << s << '\"';
	return os;
}

OMANIP(double) DMS( double c )
	{ return OMANIP(double)(os_format_dms, c); }

ostream& os_format_dms(ostream& os, tagDMSFORMAT fmt) {
	double	dms = fmt.val;
	double	d, m, s;
	bool	bNeg = dms < 0 ? true : false;
	dms = fabs( dms );
	dms /= 3600; d = floor( dms ); dms = ( dms - d ) * 3600;
	dms /= 60;   m = floor( dms ); dms = ( dms - m ) * 60;
	s = dms;
	if( bNeg ) {
		os << '-';
	}
//	long d, m, s;
//	s = fmt.val % 60; fmt.val /= 60;
//	m = fmt.val % 60; fmt.val /= 60;
//	d = fmt.val;

	for( char* p = (char*) fmt.pszFormat; *p; p++ ) {
		if( '$' != *p )
			os << *p;
		else {
			++p;
			os.width(2);
			os.fill('0');
			if( !*p )
				break;
			if( 'd' == *p )
				os << d;
			else if( 'm' == *p )
				os << m;
			else if( 's' == *p ) {
				os.flags( os.flags() | ios::fixed ); os.precision(fmt.prec);
				os << s;
			}
			else if( '$' == *p )
				os << '$';
			else
				os << '$' << *p;
		}
	}
	return os;
}

OMANIP(tagDMSFORMAT) DMS( LPCTSTR pszFormat, double coord, int prec ) {
	tagDMSFORMAT	fmt;
	fmt.pszFormat = pszFormat;
	fmt.val = coord;
	fmt.prec = prec;
	return OMANIP(tagDMSFORMAT) (os_format_dms, fmt);
}

#include <io.h> // _access

BOOL MatchMapName( LPCTSTR lpszMapIdent, LPCTSTR lpszFileName ) {
	CString	strMapIdent( lpszMapIdent );
	CString	strFileName;
	::AfxExtractSubString( strFileName, lpszFileName, 0, '.' );
	int	mapLen = strMapIdent.GetLength();
	int	fileLen = strFileName.GetLength();
	for( ; mapLen && fileLen; ) {
		mapLen--;
		fileLen--;
		if( iswalnum(strMapIdent[mapLen]) && ( towlower( strMapIdent[mapLen] ) != towlower( strFileName[fileLen] ) ) )
			return FALSE;
	}
	if( 0 == fileLen )
		return FALSE;
	
	UINT	nOldErrMode = ::SetErrorMode( SEM_FAILCRITICALERRORS );
	BOOL bFound = 0 == _access( lpszFileName, 04 ) ? TRUE : FALSE;
	::SetErrorMode( nOldErrMode );
	return bFound;
}

static CString	DoMatch( LPCTSTR lpszName, LPCTSTR *lpszPatterns ) {
	CRex	rex;
	for( LPCTSTR *pCp = lpszPatterns; *pCp; pCp++ ) {
		rex.Compile( *pCp );
		if( rex.Compare( lpszName ) ) {
			return rex.Found( 1 );
		}
	}
	return "";
}

namespace ParserForASMap {
	static LPCTSTR	szMatch[] = {
		_T(".*\\([a-z]_[1-9]\\{1,2\\}_[0-9]\\{1,3\\}_[a-d]_[a-d]_[1-4]\\)"),
		_T(".*\\([a-z]_[1-9]\\{1,2\\}_[0-9]\\{1,3\\}_[a-d]_[a-d]\\)"),
		_T(".*\\([a-z]_[1-9]\\{1,2\\}_[0-9]\\{1,3\\}_[a-d]\\)"),
		_T(".*\\([a-z]_[1-9]\\{1,2\\}_[0-9]\\{1,3\\}\\)"),
		_T(".*\\([a-z]_[1-9]\\{1,2\\}\\)"),
		NULL
	};

	BOOL IsMapName( LPCTSTR lpszName, CString& strRealName ) {
		CString strMapName;
		for( LPCTSTR cp = lpszName; *cp; ++cp )
			strMapName += iswalnum( (wint_t) *cp ) ? *cp : '_';
		strMapName.MakeLower();
		strRealName = DoMatch( strMapName, szMatch );
		if( strRealName.IsEmpty() )
			return FALSE;
		int nDelim = 0;
		for( int i = 0; i < strRealName.GetLength(); i++ ) {
			if( !isalnum( strRealName[i] ) ) {
				strRealName.SetAt( i, '-' );
				nDelim++;
				continue;
			}
			else
				if( 0 == nDelim || 3 == nDelim )
					strRealName.SetAt( i, toupper( strRealName[i] ) );
		}
		return TRUE;
	}
}

namespace ParserForAVMap {
	static LPCTSTR szMatch[] = {
		_T(".*\\([01][0-9][01][0-9]_[1-4]\\{1,3\\}\\)"),
		_T(".*\\([01][0-9][01][0-9]\\)"),
		NULL
	};
	BOOL IsMapName( LPCTSTR lpszName, CString& strRealName ) {
		CString strMapName;
		for( LPCTSTR cp = lpszName; *cp; ++cp )
			strMapName += iswalnum( (wint_t) *cp ) ? *cp : '_';
		strMapName.MakeLower();
		strRealName = DoMatch( strMapName, szMatch );
		if( strRealName.IsEmpty() )
			return FALSE;
		return TRUE;
	}
}

namespace ParserForNMap {
	static LPCTSTR szMatch[] = {
		_T(".*\\([1-8][0-9][0-5][0-9]_[ns][ow]\\)"),			// 1:10.000
		_T(".*\\([c][c][1-8][0-9][0-5][0-9]\\)"),				// 1:200.000
		_T(".*\\([c][1-8][0-9][0-5][0-9]\\)"),					// 1:100.000
		_T(".*\\([l][1-8][0-9][0-5][0-9]_*\\)"),					// 1:50.000
		_T(".*\\([1-8][0-9][0-5][0-9]\\)"),						// 1:25.000
		NULL
	};
	BOOL IsMapName( LPCTSTR lpszName, CString& strRealName ) {
		CString strMapName;
		for( LPCTSTR cp = lpszName; *cp; ++cp )
			strMapName += iswalnum( (wint_t) *cp ) ? *cp : '_';
		strMapName.MakeLower();
		strRealName = DoMatch( strMapName, szMatch );
		if( strRealName.IsEmpty() )
			return FALSE;
		return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////
// 
//	TOPOMAPTYPE	BOOL			COORDTYPE	LPCTSTR		LPCTSTR			LPCTSTR
//	m_mtType	m_bHaveParser	m_coordType	m_strCtf	m_strShortName	m_strLongName;

MAPTYPE	mapTypes[] = {
	{ MPT_UNKNOWN,		FALSE,	COORD_XY,	_T("DEFAULT"),	_T("UNK"),		_T("unbekannter Blattschnitt") },
	{ MPT_AS,			TRUE,	COORD_DMS,	_T("KRGEOD"),	_T("AS"),		_T("topographische Karte AS") },
	{ MPT_AS_L,			TRUE,	COORD_DMS,	_T("KRGEOD"),	_T("AS_L"),		_T("topographische Karte AS (Layer)") },
	{ MPT_AV,			TRUE,	COORD_DMS,	_T("BEGEOD"),	_T("AV"),		_T("topographische Karte AV") },
	{ MPT_N,			TRUE,	COORD_DMS,	_T("BEGEOD"),	_T("N"),		_T("topographische Karte N") },
	{ MPT_N_L,			TRUE,	COORD_DMS,	_T("BEGEOD"),	_T("N_L"),		_T("topographische Karte N (Layer)") },
	{ MPT_BESSELGK,		FALSE,	COORD_GK,	_T("BESSELGK"),	_T("USRBEGK"),	_T("nutzerdef. Koordinaten Bessel / Gauß-Krüger") },
	{ MPT_BEGEOD,		FALSE,	COORD_DMS,	_T("BEGEOD"),	_T("USRBEGD"), 	_T("nutzerdef. Koordinaten Bessel / geodätisch") },
	{ MPT_KRASSGK,		FALSE,	COORD_GK,	_T("KRASSGK"),	_T("USRKRGK"),	_T("nutzerdef. Koordinaten Krassowski / Gauß-Krüger") },
	{ MPT_KRGEOD,		FALSE,	COORD_DMS,	_T("KRGEOD"),	_T("USRKRGD"), 	_T("nutzerdef. Koordinaten Krassowski / geodätisch") },
	{ MPT_SOE1,			FALSE,	COORD_XY,	_T("DEFAULT"),	_T("SOE1"),		_T("Soldner-Koordinatensystem (Berlin)") },
	{ MPT_INVALID, FALSE, COORD_XY, NULL, NULL, NULL }
};

const MAPTYPE	*GetTypeFromType( TOPOMAPTYPE mapType ) {
	for( MAPTYPE *pType = mapTypes; MPT_INVALID != pType->m_mtType; pType++ )
		if( mapType == pType->m_mtType )
			return pType;
	return NULL;
}

const MAPTYPE	*GetTypeFromName( LPCTSTR strShortName ) {
	for( MAPTYPE *pType = mapTypes; MPT_INVALID != pType->m_mtType; pType++ )
		if( *strShortName == *pType->m_strShortName && 0 == strcmp( strShortName, pType->m_strShortName ) )
			return pType;
	return NULL;
}
