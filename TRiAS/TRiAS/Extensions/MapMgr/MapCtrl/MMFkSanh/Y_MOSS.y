%{
#include "stdafx.h"
#define YY_NAMESPACE	MOSS
namespace YY_NAMESPACE {
typedef struct C {
	double	X;
	double	Y;
} C;
typedef struct CPair {
	C	file;
	C	world;
} CPair;
%}
%union {
	double	v;
	C		c;
}
%token	EOL
%token	EMBEDDINGS
%token	UORMIN UORMAX CONTROLPOINTS POINTPAIR FILEPOINT WORLDPOINT
%token	<v>	COORDVAL
%type	<c>	COORD WorldPoint FilePoint
%%
MOSS:			EMBEDDINGS Embeddings EOL
	{
		m_state = true;
	}
	;
Embeddings:		Embeddings Embedding
	|			Embedding
	;
Embedding:		UorMin
	|			UorMax
	|			CONTROLPOINTS PointPairs
	;
UorMin:			UORMIN COORD
	{
		m_pC->insert( _T("min"), GEOPOINT( $2.X, $2.Y ) );
	}
	;
UorMax:			UORMAX COORD
	{
		m_pC->insert( _T("max"), GEOPOINT( $2.X, $2.Y ) );
	}
	;
PointPairs:		PointPair
	|			PointPair PointPairs
	;
PointPair:		POINTPAIR FilePoint WorldPoint
	{
		m_pG->push_back( GCP( GEOPOINT($3.X,$3.Y), GEOPOINT($2.X,$2.Y) ) );
	}
	;
FilePoint:		FILEPOINT COORD
	{
		$$ = $2;
	}
	;
WorldPoint:		WORLDPOINT COORD
	{
		$$ = $2;
	}
	;
COORD:			'(' COORDVAL ',' COORDVAL ')'
	{
		$$.X = $2; $$.Y = $4;
	}
	;
%%

int yyparse( void );

LPCTSTR	m_str;
LPCTSTR	m_strPos;
map< CString, UINT > tokens;
CString	m_strLastToken;
CoordMap	*m_pC;
GCPList		*m_pG;
bool		m_state;

bool Parse( LPCTSTR lpszString, CoordMap &M, GCPList &L ) {
	m_str = m_strPos = lpszString;
	m_pC = &M;
	m_pG = &L;
	m_state = false;
	tokens.insert( _T("Embeddings:"), EMBEDDINGS );
	tokens.insert( _T("uor_min:"), UORMIN );
	tokens.insert( _T("uor_max:"), UORMAX );
	tokens.insert( _T("ControlPoints:"), CONTROLPOINTS );
	tokens.insert( _T("PointPair:"), POINTPAIR );
	tokens.insert( _T("File:"), FILEPOINT );
	tokens.insert( _T("World:"), WORLDPOINT );

	if( yyparse() ) {
		return m_state;
	}
	return false;
}

void yyerror( char* pszMsg1, char* pszMsg2 = NULL ) {
	CString	S;
	S.Format( _T("[%s] near <<%s>>, Pos %d"), pszMsg1, m_strLastToken, m_strPos - m_str );
#ifdef CONSOLE
	cerr << pszMsg1 << endl;
	if( NULL != pszMsg2 )
		cerr << pszMsg2 << endl;
#endif
}

int yylex() {
	LPCTSTR	sStart = NULL;
	TCHAR	c;
	while( *m_strPos ) {
		c = *m_strPos;
		if( _T('{') == c || _T('}') == c || iswspace( c ) ) {
			m_strPos++;
			continue;
		}
		if( _T('(') == c || _T(')') == c || _T(',') == c ) {
			m_strPos++;
			m_strLastToken = c;
			return c;
		}
		for( sStart = m_strPos; *m_strPos && !iswspace( *m_strPos ); m_strPos++ )
		{}
		CString	S( sStart, m_strPos - sStart );
		map< CString, UINT >::iterator i2 = tokens.find( S );
		if( tokens.end() != i2 ) {
			m_strLastToken = S;
			return (*i2).second;
		} else {
			yylval.v = atof( S );
			m_strLastToken = S;
			return COORDVAL;
		}
	}
	return EOL;
}
