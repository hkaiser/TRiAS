#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// Dispatcher

const AFX_DATADEF ASC_PARSERMAP CAscParserBase::parserMap =
{
#ifdef _AFXDLL
	&CAscParserBase::_GetBaseParserMap,
#else
	NULL,
#endif
	&CAscParserBase::_mapEntries[0]
};

#ifdef _AFXDLL
const ASC_PARSERMAP* CAscParserBase::_GetBaseParserMap()
	{ return NULL; }
#endif

const ASC_PARSERMAP* CAscParserBase::GetParserMap() const
	{ return &CAscParserBase::parserMap; }

const ASC_PARSERMAP_ENTRY CAscParserBase::_mapEntries[] =
	{ { NULL, 0, NULL } };

static const ASC_PARSERMAP_ENTRY *FindMapEntry( const ASC_PARSERMAP *pMap, LPCTSTR lpszEntry )
{
	register const ASC_PARSERMAP_ENTRY *pEntry = pMap->lpEntries;
	if( NULL == lpszEntry )
		return NULL;
	register char firstChar = *lpszEntry;
	while( pEntry->ap_TagName )
	{
		if( *pEntry->ap_TagName == firstChar && 0 == strcmp( pEntry->ap_TagName, lpszEntry ) )
			return pEntry;
		pEntry++;
	}
	return NULL;
}

static const BOOL DispatchTag( CAscParserBase* pTarget, const ASC_PARSERMAP_ENTRY *pEntry, void* p1, void* p2, void* p3 )
{
	ASSERT( NULL != pEntry );

	BOOL	bResult = TRUE;
	union	ParserMapFunctions	pmf;

	pmf.pfn = pEntry->ap_TagFunc;

	switch( pEntry->ap_Sig )
	{
	case AscTag_vs :
		(pTarget->*pmf.pfn_vs)((LPCTSTR)p1);
		break;
	case AscTag_vss :
		(pTarget->*pmf.pfn_vss)((LPCTSTR)p1,(LPCTSTR)p2);
		break;
	case AscTag_vwwi :
		(pTarget->*pmf.pfn_vwwi)(*((DWORD*)p1),*((DWORD*)p2),*((int*)p3));
		break;
	case AscTag_vws :
		(pTarget->*pmf.pfn_vws)(*((DWORD*)p1),(LPCTSTR)p2);
		break;
	case AscTag_vdd :
		(pTarget->*pmf.pfn_vdd)(*((double*)p1),*((double*)p2));
		break;
	default :
		ASSERT( FALSE );
		bResult = FALSE;
		break;
	}
	return bResult;
}

////////////////////////////////////////////////////////////////////////
// Helfer zur Behandlung der Headerzeilen

class CHeaderLines : public CObject
{
	CStringArray	m_strEntries;
	CStringArray	m_strValues;
	CPtrArray		m_ptrArray;
public:
	CHeaderLines();
	virtual ~CHeaderLines();
	void	Add( const ASC_PARSERMAP_ENTRY *pEntry, LPCTSTR lpszE, LPCTSTR lpszV );
	void	Emit( CAscParserBase *pParser, const ASC_PARSERMAP_ENTRY* );
	int	IdentBase();
	int	MCodeBase();
};

typedef struct tagHEADERLINE {
	LPCTSTR	szEntry;
	LPCTSTR	szValue;
	const ASC_PARSERMAP_ENTRY* pEntry;
} HEADERLINE;

static HEADERLINE hdrLines[] = {
	{ "Scale", "1.0 0.0 0.0 1.0", NULL },
	{ "Offset", "0.0 0.0", NULL },
	{ "IdentBase", "16", NULL },
	{ "MCodeBase", "10", NULL },
	{ NULL, NULL, NULL }
};

int CHeaderLines::IdentBase()
	{ return atoi( m_strValues[2] ); }

int CHeaderLines::MCodeBase()
	{ return atoi( m_strValues[3] ); }

CHeaderLines::CHeaderLines()
{
	for( HEADERLINE *hl = hdrLines; hl->szEntry; hl++ )
	{
		m_strEntries.Add( hl->szEntry );
		m_strValues.Add( hl->szValue );
		m_ptrArray.Add( (void*) NULL );
	}
}

CHeaderLines::~CHeaderLines()
{
	m_strEntries.RemoveAll();
	m_strValues.RemoveAll();
	m_ptrArray.RemoveAll();
}

void CHeaderLines::Add( const ASC_PARSERMAP_ENTRY *pEntry, LPCTSTR lpszE, LPCTSTR lpszV )
{
	ASSERT( NULL != lpszE && NULL != lpszV && NULL != pEntry );
	int i = 0;
	for( HEADERLINE *hl = hdrLines; hl->szEntry; hl++, i++ )
	{
		if( *lpszE == *hl->szEntry && 0 == strcmp( lpszE, hl->szEntry ) )
			break;
	}
	if( hl->szEntry )
	{
		m_strEntries.SetAt( i, lpszE );
		m_strValues.SetAt( i, lpszV );
		m_ptrArray.SetAt( i, (void*) pEntry );
	}
	else
	{
		m_strEntries.Add( lpszE );
		m_strValues.Add( lpszV );
		m_ptrArray.Add( (void*) pEntry );
	}
}

static DWORD nil[] = { 0, 0, 0, 0 };

void CHeaderLines::Emit( CAscParserBase* pParser, const ASC_PARSERMAP_ENTRY* defEntry )
{
	CString	S1, S2;
	const	ASC_PARSERMAP_ENTRY	*pEntry;
	void *p1, *p2, *p3;
	p3 = (void*) nil;
	for( int i = 0; i < m_strEntries.GetSize(); i++ )
	{
		S1 = m_strEntries.GetAt( i );
		S2 = m_strValues.GetAt( i );
		p1 = (void*) (LPCTSTR) S1;
		p2 = (void*) (LPCTSTR) S2;
		if( NULL == ( pEntry = (const ASC_PARSERMAP_ENTRY*) m_ptrArray.GetAt( i ) ) )
			pEntry = defEntry;
		if( NULL == pEntry )
			continue;
		ASSERT( AscTag_vss == pEntry->ap_Sig );
		VERIFY( DispatchTag( pParser, pEntry, p1, p2, p3 ) );
	}
}

////////////////////////////////////////////////////////////////////////
// der Parser selbst

#define	CONT_EOL(c)		if( '\0' == (c) ) { continue; }
#define	WARN_EOL(c)		if( '\0' == (c) ) { Warning( W_UNEXPECTED_EOL, m_nLine, "" ); continue; }
#define	SKIPWS(p)		while( *(p) && isspace( *(p) ) ) { ++(p); }
#define	SEARCHWS(p)		while( *(p) && !isspace( *(p) ) ) { ++(p); }
#define	SEARCHCHAR(p,c)	while( *(p) && (c) != *(p) ){++(p);}

CAscParserBase::CAscParserBase()
	{ m_pIs = NULL; }

CAscParserBase::~CAscParserBase( )
	{ }

void CAscParserBase::Attach( istream& is )
{
	m_pIs = &is;
	m_pIs->unsetf( ios::skipws );
}

BOOL CAscParserBase::Parse( )
{
	ASSERT( NULL != m_pIs );
	if( NULL == m_pIs || !m_pIs->good() ) {
		Error( E_BADINPUT, -1, NULL );
		return FALSE;
	}

	char	buf[nMaxAscLineLength];
	register char *pC, c;
	char	*pS;

	CString		S1, S2;
	void		*p1, *p2, *p3;
	const		ASC_PARSERMAP_ENTRY	*pEntry, *pEntry2;
	char		tag[2];

	CHeaderLines	hdrLines;
	int				nObjects = 0;

	tag[1] = '\0';
	m_nChars = 0;
	m_nLine = 0;
	int iBase = 10;
	int	mBase = 10;
	DWORD	ident, objNum, mcode;
	int		nCoords = 0;
	int		nMcodeChars = 0;
	double	X, Y;

	while( !m_pIs->eof() ) {
		m_pIs->getline( buf, nMaxAscLineLength );
		m_nChars += strlen( buf );
		m_nLine++;
_DoParseBuffer:
		pC = buf; SKIPWS( pC ); CONT_EOL( *pC );
		*tag = *pC++;
		if( 'E' == *tag )			// Yups... :-)
			break;
		CONT_EOL( *pC ); SKIPWS(pC);
		CONT_EOL( *pC );			// ein Tag mit nichts darhinnen

		if( NULL == ( pEntry = FindMapEntry( GetParserMap(), tag ) ) )
			continue;				// ein Tag, welches die Welt nicht braucht

		p1 = p2 = p3 = (void*) nil;	// keine NULL-Zeiger

		if( 'G' == *tag ) {			// 'G' kommt am h‰ufigsten vor, muﬂ am schnellsten gefunden werden
			while( *pC ) {
				if( nCoords-- < 0 )
					Warning( W_UNEXPECTED_COORD, m_nLine, buf );
				pS = pC; SEARCHWS(pC); WARN_EOL(*pC); X = atof( pS ); SKIPWS(pC); WARN_EOL(*pC);
				pS = pC; Y = atof( pS ); 
				p1 = (void*) &X;
				p2 = (void*) &Y;
				if( !DispatchTag( this, pEntry, p1, p2, p3 ) ) {
					Error( E_INTERNAL, m_nLine, pC );
					return FALSE;
				}
				SEARCHWS(pC); SKIPWS(pC);
			}
			continue;				// ‰uﬂeren Dispatcher ¸bergehen
		} else if( 'M' == *tag ) {
			pS = pC; SEARCHWS(pC); WARN_EOL(*pC); mcode = strtol( pS, pC, mBase );
			SKIPWS(pC); WARN_EOL(*pC);		// 1
			SEARCHWS(pC); WARN_EOL(*pC);
			SKIPWS(pC); WARN_EOL(*pC);		// A
			SEARCHWS(pC); WARN_EOL(*pC);
			SKIPWS(pC); WARN_EOL(*pC);		// 
			pS = pC; SEARCHWS(pC); nMcodeChars = strtol( pS, pC );
			S1.Empty();
			while( nMcodeChars > 0 ) {
				m_pIs->getline( buf, nMaxAscLineLength );
				m_nLine++;
				pC = buf; SKIPWS( pC ); WARN_EOL( *pC );
				if( 'W' != ( *tag = *pC++ ) ) {
					Warning( W_UNEXPECTED_TOKEN, m_nLine, buf );
					goto _DoParseBuffer;
				}
				WARN_EOL( *pC );
				SEARCHWS( pC ); SKIPWS( pC ); WARN_EOL( *pC );
				c = *pC;
				if( '\'' == c || '\"' == c )
					{ WARN_EOL(*++pC); }
				else
					{ c = '\0'; }
				pS = pC;
				SEARCHCHAR( pC, '\0' );
				if( '\0' != c )
					--pC;
				if( *pC != c )
					Warning( W_MISSINGQUOTE, m_nLine, buf );
				S1 += CString( pS, pC - pS );
				nMcodeChars -= (pC - pS);
				if( nMcodeChars  < 0 )
					Warning( W_INVALID_CHARCOUNT, m_nLine, buf );
			}
			p1 = (void*) &mcode;
			p2 = (void*) (LPCTSTR) S1;
			goto _DoDispatch;		// *pTag wurde ge‰ndert; nochmaligen Vergleich verhindern!!!
		} else if( ';' == *tag ) {
			p1 = (void*) pC;
		} else if( 'P' == *tag || 'L' == *tag || 'F' == *tag || 'B' == *tag ) {
			if( 0 == nObjects++ ) {
				hdrLines.Emit( this, FindMapEntry( GetParserMap(), "D" ) );
				iBase = hdrLines.IdentBase();
				mBase = hdrLines.MCodeBase();
			}
			if( nCoords > 0 )
				Warning( W_INVALID_COORDCOUNT, m_nLine, buf );
			pS = pC;
			SEARCHWS(pC); WARN_EOL(*pC);
			objNum = strtol( pS, pC );
			SKIPWS(pC); WARN_EOL(*pC);
			pS = pC;
			SEARCHWS(pC); WARN_EOL(*pC);
			if( '\"' == *pS || '\'' == *pS ) {
				WARN_EOL(*++pS);
			}
			if( '\"' == *(pC - 1) || '\'' == *(pC - 1) )
				ident = strtol( pS, pC - 1, iBase );
			else
				ident = strtol( pS, pC, iBase );
			SKIPWS(pC); WARN_EOL(*pC);
			pS = pC;
			SEARCHWS(pC);
			nCoords = strtol( pS, pC );
			p1 = (void*) &ident;
			p2 = (void*) &objNum;
			p3 = (void*) &nCoords;
		} else if( 'D' == *tag ) {
			pS = pC;
			SEARCHWS(pC); SKIPWS( pC ); CONT_EOL(*pC);
			if( '\"' != *pC ) {
				Warning( W_MISSINGQUOTE, m_nLine, pC );	// versuchen nach Leerzeichen zu trennen
				pS = pC++;
				SEARCHWS( pC );
				S1 = CString( pS, pC - pS );
				p1 = (void*) (LPCTSTR) S1;
				SKIPWS( pC );
				if( '\0' != *pC )
					S2 = pC;
				else
					S2.Empty();
				p2 = (void*) (LPCTSTR) S2;
				goto _DoDispatch;						// vielleicht kˆnnen andere was damit anfangen
			}
			S1 = CString( pS, pC - pS );
			S1.TrimRight();
			pEntry2 = FindMapEntry( GetParserMap(), S1 );

			WARN_EOL(*++pC);							// jetzt werden die Fehler aber FEHLER
			pS = pC;
			SEARCHCHAR( pC, '\"' ); WARN_EOL(*pC);
			S1 = CString( pS, pC - pS );
			S1.TrimRight();
			WARN_EOL( *++pC );
			SEARCHCHAR( pC, '\"' ); WARN_EOL(*pC);
			WARN_EOL( *++pC );
			pS = pC;
			SEARCHCHAR( pC, '\"' );						// fehlendes dQuote am Ende ist ertr‰glich...
			S2 = CString( pS, pC - pS );
			S2.TrimRight();
			p1 = (void*) (LPCTSTR) S1;
			p2 = (void*) (LPCTSTR) S2;
			if( NULL != pEntry2 )
				pEntry = pEntry2;
			hdrLines.Add( pEntry, S1, S2 );
			continue;
		} else if( 'H' == *tag ) {
			p1 = (void*) pC;
		}
_DoDispatch:
		if( !DispatchTag( this, pEntry, p1, p2, p3 ) ) {
			Error( E_INTERNAL, m_nLine, pC );
			return FALSE;
		}
	}
	return TRUE;
}

DWORD CAscParserBase::strtol( LPCTSTR lpsz, int b ) {
	DWORD val = 0;
	register LPCTSTR p = lpsz;
	register char c;
	for( ; *p && isspace( *p ); p++ )
		;
	if( *p && '0' == *p && *(p+1) && ( 'x' == *(p+1) || 'X' == *(p+1 ) ) ) {
		b = 16;
		p += 2;
	}
	for( ; c = *p; p++ ) {
		if( 16 == b ) {
			if( c >= 'A' && c < 'G' )
				{ c -= 'A'; c += '9' + 1; }
			else if( c >= 'a' && c < 'f' )
				{ c -= 'a'; c += '9' + 1; }
		}
		c -= '0';
		if( c > b )
			break;
		val *= b;
		val += c;
	}
	return val;
}

DWORD CAscParserBase::strtol( LPCTSTR lpszS, LPCTSTR lpszE, int b ) {
	DWORD val = 0;
	register LPCTSTR p = lpszS;
	register char c;
	for( ; *p && p != lpszE && isspace( *p ); p++ )
		;
	if( *p && '0' == *p && *(p+1) && ( 'x' == *(p+1) || 'X' == *(p+1 ) ) ) {
		b = 16;
		p += 2;
	}
	for( ; ( c = *p ) && p != lpszE; p++ ) {
		if( 16 == b ) {
			if( c >= 'A' && c < 'G' )
				{ c -= 'A'; c += '9' + 1; }
			else if( c >= 'a' && c < 'f' )
				{ c -= 'a'; c += '9' + 1; }
		}
		c -= '0';
		if( c > b )
			break;
		val *= b;
		val += c;
	}
	return val;
}

void CAscParserBase::Warning( PARSERWARN wrn, int line, LPCTSTR restLine ) {
	CString	S;
	S.Format( "ASC Parser: Warning %d, line %d, [%s]", wrn, line, restLine );
	::AfxMessageBox( S );
}

void CAscParserBase::Error( PARSERERROR err, int line, LPCTSTR restLine ) {
	CString	S;
	S.Format( "ASC Parser: Error %d, line %d, [%s]", err, line, restLine );
	::AfxMessageBox( S );
}

