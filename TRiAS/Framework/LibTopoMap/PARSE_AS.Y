%{
#include "stdafx.h"
#include "memory.h"
#include "ctype.h"

#define YY_NAMESPACE	ParserForASMap		// force closing namespace in 'skel'

namespace YY_NAMESPACE {


typedef struct tagMAPCOORD {
	POINTL	pt;		// bottom left
	SIZEL	sz;		// width, height
	long	scale;
	} MAPCOORD;

#define ZEROINIT( obj )	memset( &(obj), 0x00, sizeof( obj ) )

// #define CONSOLE

#ifdef CONSOLE
	#include "iostream.h"
#else
	#define DC( arg )
#endif

%}
%union {
	int			l;
	MAPCOORD	c;
	}
%token	<l>	UC_LETTER LC_LETTER NUMBER DELIMITER EOL
%type	<c> M1000000 M100000 M50000 M25000 M10000
%%
Map : MapName EOL
	;
MapName		:	M1000000
		{ mapCoord = $1; DC( $1 ); }
	| M100000
		{ mapCoord = $1; DC( $1 ); }
	| M50000
		{ mapCoord = $1; DC( $1 ); }
	| M25000
		{ mapCoord = $1; DC( $1 ); }
	| M10000
		{ mapCoord = $1; DC( $1 ); }
	;
M1000000	:	UC_LETTER DELIMITER NUMBER
	{
		ZEROINIT( $$ );
		if( $1 + 'A' >= 'A' && $1 + 'A' <= 'W' ) {
			$$.sz.cx = 21600;
			$$.sz.cy = 14400;
			$$.scale = 1000000;
			$$.pt.x = ( 6 * ( $3 - 1 ) - 180 ) * 3600;
			$$.pt.y = ( 4 * $1 ) * 3600;
		}
	}
	;
M100000		:	M1000000 DELIMITER NUMBER
	{
		$3 -= 1;
		ZEROINIT( $$ );
		if( $3 < 144 )
		{
			$$.sz.cx = $1.sz.cx / 12;
			$$.sz.cy = $1.sz.cy / 12;
			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 12 );
			$$.pt.y = $1.pt.y + 11 * $$.sz.cy - $$.sz.cy * ( $3 / 12 );
			$$.scale = $1.scale / 10;
		}
	}
	;
M50000		:	M100000 DELIMITER UC_LETTER
	{
		ZEROINIT( $$ );
		if( $3 < 4 )
		{
			$$.sz.cx = $1.sz.cx / 2;
			$$.sz.cy = $1.sz.cy / 2;
			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 2 );
			$$.pt.y = $1.pt.y + $$.sz.cy - ( $$.sz.cy * ( $3 / 2 ) );
			$$.scale = $1.scale / 2;
		}
	}
	;
M25000		:	M50000 DELIMITER LC_LETTER
	{
		ZEROINIT( $$ );
		if( $3 < 4 )
		{
			$$.sz.cx = $1.sz.cx / 2;
			$$.sz.cy = $1.sz.cy / 2;
			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 2 );
			$$.pt.y = $1.pt.y + $$.sz.cy - ( $$.sz.cy * ( $3 / 2 ) );
			$$.scale = $1.scale / 2;
		}
	}
	;
M10000		:	M25000 DELIMITER NUMBER
	{
		$3 -= 1;
		ZEROINIT( $$ );
		if( $3 < 4 )
		{
			$$.sz.cx = $1.sz.cx / 2;
			$$.sz.cy = $1.sz.cy / 2;
			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 2 );
			$$.pt.y = $1.pt.y + $$.sz.cy - ( $$.sz.cy * ( $3 / 2 ) );
			$$.scale = 10000;
		}
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

#ifndef __AFXWIN_H__		// console/test mode
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

int yylex() {
	char	c;
	yylval.l = 0;
	int		sts;
	while( *pStr ) {
		c = *pStr++;
		if( !isalnum( c ) ) {
			sts = DELIMITER;
		} else if( c >= 'A' && c <= 'Z' ) {
			yylval.l = (long) ( c - 'A' ); sts = UC_LETTER;
		} else if( c >= 'a' && c <= 'z' ) {
			yylval.l = (long) ( c - 'a' ); sts = LC_LETTER;
		} else {
			while( c ) {
				yylval.l *= 10;
				yylval.l += (long) ( c - '0' );
				c = *pStr++;
				if( c < '0' || c > '9' ) {
					pStr--;
					break;
				}
			}
			sts = NUMBER;
		}
		return sts;
	}
	return EOL;
}
