%{
#include "stdafx.h"
#include "memory.h"
#include "ctype.h"

#define YY_NAMESPACE	ParserForAVMap		// force closing namespace in 'skel'

namespace YY_NAMESPACE {

typedef struct tagMAPCOORD {
	POINTL	pt;		// bottom left
	SIZEL	sz;		// width, height
	long	scale;
	} MAPCOORD;

#define ZEROINIT( obj )	memset( &(obj), 0x00, sizeof( obj ) )

#ifdef __AFXWIN_H__
	#define DC( arg )
#endif

%}
%union {
	int			l;
	MAPCOORD	c;
	}
%token	<l>	DIGIT DELIMITER EOL
%type	<c> M100000 M50000 M25000 M10000
%%
Map : MapName EOL
	;
MapName		:	M100000
		{ mapCoord = $1; DC( $1 ); }
	| M50000
		{ mapCoord = $1; DC( $1 ); }
	| M25000
		{ mapCoord = $1; DC( $1 ); }
	| M10000
		{ mapCoord = $1; DC( $1 ); }
	;
M100000		:	DIGIT DIGIT DIGIT DIGIT
	{
		ZEROINIT( $$ );
		int	row = $1 * 10 + $2;
		int	col = $3 * 10 + $4;
		if( row < 1 )
			yyerror( "Invalid row" );
		if( col < 1 )
			yyerror( "Invalid col" );
		$$.sz.cx = 1800;
		$$.sz.cy = 1200;
		$$.pt.x = 34200 + ( col - 1 )  * $$.sz.cx;
		$$.pt.y = 198000 - row * $$.sz.cy;
		$$.scale = 100000;
	}
	;
M50000		:	 M100000 DELIMITER DIGIT
	{
		ZEROINIT( $$ );
		if( $3 < 1 || $3 > 3 )
			yyerror( "Invalid quadrant" );
		$$.pt.x = $1.pt.x;
		$$.pt.y = $1.pt.y;
		$$.sz.cx = $1.sz.cx / 2;
		$$.sz.cy = $1.sz.cy / 2;
		if( 2 == $3 || 4 == $3 )
			$$.pt.x += $$.sz.cx;
		if( 1 == $3 || 2 == $3 )
			$$.pt.y += $$.sz.cy;
		$$.scale = $1.scale / 2;
	}
	;
M25000		:	M50000 DIGIT
	{
		ZEROINIT( $$ );
		if( $2 < 1 || $2 > 3 )
			yyerror( "Invalid quadrant" );
		$$.pt.x = $1.pt.x;
		$$.pt.y = $1.pt.y;
		$$.sz.cx = $1.sz.cx / 2;
		$$.sz.cy = $1.sz.cy / 2;
		if( 2 == $2 || 4 == $2 )
			$$.pt.x += $$.sz.cx;
		if( 1 == $2 || 2 == $2 )
			$$.pt.y += $$.sz.cy;
		$$.scale = $1.scale / 2;
	}
	;
M10000		:	M25000 DIGIT
	{
		ZEROINIT( $$ );
		if( $2 < 1 || $2 > 3 )
			yyerror( "Invalid quadrant" );
		$$.pt.x = $1.pt.x;
		$$.pt.y = $1.pt.y;
		$$.sz.cx = $1.sz.cx / 2;
		$$.sz.cy = $1.sz.cy / 2;
		if( 2 == $2 || 4 == $2 )
			$$.pt.x += $$.sz.cx;
		if( 1 == $2 || 2 == $2 )
			$$.pt.y += $$.sz.cy;
		$$.scale = $1.scale / 2;
	}
	;
%%

MAPCOORD	mapCoord;
char *pStr;

int yyparse( void );

BOOL ParseMapName( LPCTSTR lpszMapName, GEOPOINT& rPt, GEOSIZE& rSz, long& rScale ) {
	pStr = (char*) lpszMapName;
	ZEROINIT( mapCoord );
	if( yyparse() ) {
		rPt.X = mapCoord.pt.x;
		rPt.Y = mapCoord.pt.y;
		rPt.Z = 0;
		rSz.dX = mapCoord.sz.cx;
		rSz.dY = mapCoord.sz.cy;
		rScale = mapCoord.scale;
		return TRUE;
	}
	return FALSE;
}

#ifndef __AFXWIN_H__
void _DC( long coord ) {
	long	h, m, s;
	s = coord % 60; coord /= 60;
	m = coord % 60; coord /= 60;
	h = coord;
	cout << h << "ø" << m << "'" << s << "\"";
}

void DC( MAPCOORD& m ) {
	cout << "1:" << m.scale ;
	cout << "["; _DC( m.pt.x ); cout << ','; _DC( m.pt.y ); cout << ']';
	cout << "["; _DC( m.sz.cx ); cout << ','; _DC( m.sz.cy ); cout << ']';
	cout << endl;
}
#endif // !__AFXWIN_H__

void yyerror( char* pszMsg1, char* pszMsg2 = NULL) {
}

int yylex()
{
	char	c;
	int		nChars = 0;
	yylval.l = 0;
	int		sts;
	while( *pStr ) {
		c = *pStr++;
		if( isdigit( c ) ) {
			yylval.l = (long) ( c - '0' );
			sts = DIGIT;
		} else {
			sts = DELIMITER;
		}
		return sts;
	}
	return EOL;
}
