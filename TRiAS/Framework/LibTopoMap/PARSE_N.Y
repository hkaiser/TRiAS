%{
#include "stdafx.h"

#ifdef __AFXWIN_H__
	#define DC( arg )
#endif

#include "memory.h"
#include "ctype.h"

#define YY_NAMESPACE	ParserForNMap

namespace YY_NAMESPACE {

typedef struct tagMAPCOORD {
	POINTL	pt;		// bottom left
	SIZEL	sz;		// width, height
	long	scale;
	} MAPCOORD;

#define ZEROINIT( obj )	memset( &(obj), 0x00, sizeof( obj ) )

%}
%union {
	int			l;
	MAPCOORD	c;
	}
%token		PREFIX_CC PREFIX_C PREFIX_L
%token		QUAD_SW QUAD_SO QUAD_NO QUAD_NW 
%token	<l>	NUMBER DELIMITER EOL
%type	<l>	QUADRANT
%type	<c> M200000 M100000 M50000 M25000 M10000
%%
Map : MapName EOL
	;
MapName		:	M200000
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
/*
M200000	:	PREFIX_CC DELIMITER M25000
	{
		ZEROINIT( $$ );
		if( ( 0 == ( ( $3.pt.x + 2400 ) % 4800 ) ) && ( 0 == ( $3.pt.y % 2880 ) ) )
		{
			$$.scale = 200000;
			$$.sz.cx = 8 * $3.sz.cx;
			$$.sz.cy = 8 * $3.sz.cy;
			$$.pt = $3.pt;
		}
		else
			yyerror( "nicht im Raster" );
	}
	;
*/
M200000	:	PREFIX_CC M25000
	{
		ZEROINIT( $$ );
		if( ( 0 == ( ( $2.pt.x + 2400 ) % 4800 ) ) && ( 0 == ( $2.pt.y % 2880 ) ) )
		{
			$$.scale = 200000;
			$$.sz.cx = 8 * $2.sz.cx;
			$$.sz.cy = 8 * $2.sz.cy;
			$$.pt = $2.pt;
		}
		else
			yyerror( "nicht im Raster" );
	}
	;
/*
M100000		:	PREFIX_C DELIMITER M25000
	{
		ZEROINIT( $$ );
		if( 0 == $3.pt.x % 2400 && 0 == $3.pt.y % 1440 )
		{
			$$.scale = 100000;
			$$.sz.cx = 4 * $3.sz.cx;
			$$.sz.cy = 4 * $3.sz.cy;
			$$.pt = $3.pt;
		}
		else
			yyerror( "nicht im Raster" );
	}
	;
*/
M100000		:	PREFIX_C M25000
	{
		ZEROINIT( $$ );
		if( 0 == $2.pt.x % 2400 && 0 == $2.pt.y % 1440 )
		{
			$$.scale = 100000;
			$$.sz.cx = 4 * $2.sz.cx;
			$$.sz.cy = 4 * $2.sz.cy;
			$$.pt = $2.pt;
		}
		else
			yyerror( "nicht im Raster" );
	}
	;
/*
M50000		:	PREFIX_L DELIMITER M25000
	{
		ZEROINIT( $$ );
		if( 0 == $3.pt.x % 1200 && 0 == $3.pt.y % 720 )
		{
			$$.sz.cx = 2 * $3.sz.cx;
			$$.sz.cy = 2 * $3.sz.cy;
			$$.pt = $3.pt;
			$$.scale = 50000;
		}
		else
			yyerror( "nicht im Raster" );
	}
	;
*/
M50000		:	PREFIX_L M25000
	{
		ZEROINIT( $$ );
		if( 0 == $2.pt.x % 1200 && 0 == $2.pt.y % 720 )
		{
			$$.sz.cx = 2 * $2.sz.cx;
			$$.sz.cy = 2 * $2.sz.cy;
			$$.pt = $2.pt;
			$$.scale = 50000;
		}
		else
			yyerror( "nicht im Raster" );
	}
	;
M25000		:	NUMBER
	{
		ZEROINIT( $$ );
		$$.sz.cx = 600;
		$$.sz.cy = 360;
		$$.pt.x = 20400; $$.pt.x += ( $1 % 100 ) * $$.sz.cx;
		$$.pt.y = 201240; $$.pt.y -= ( $1 / 100 ) * $$.sz.cy;
		$$.scale = 25000;
	}
	;
M10000		:	M25000 DELIMITER QUADRANT
	{
		ZEROINIT( $$ );
		$$.scale = 10000;
		$$.sz.cx = $1.sz.cx / 2;
		$$.sz.cy = $1.sz.cy / 2;
		switch( $3 )
		{
		case 0 :
			$$.pt.x = $1.pt.x;
			$$.pt.y = $1.pt.y;
			break;
		case 1 :
			$$.pt.x = $1.pt.x + $$.sz.cx;
			$$.pt.y = $1.pt.y;
			break;
		case 2 :
			$$.pt.x = $1.pt.x + $$.sz.cx;
			$$.pt.y = $1.pt.y + $$.sz.cy; 
			break;
		case 3 :
			$$.pt.x = $1.pt.x;
			$$.pt.y = $1.pt.y + $$.sz.cy; 
			break;
		}
	}
	;
QUADRANT	:	QUAD_SW
		{ $$ = 0; }
	|	QUAD_SO
		{ $$ = 1; }
	|	QUAD_NW
		{ $$ = 2; }
	|	QUAD_NO
		{ $$ = 3; }
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
#endif // CONSOLE

void yyerror( char* pszMsg1, char* pszMsg2 = NULL ) {
#ifdef CONSOLE
	cerr << pszMsg1 << endl;
	if( NULL != pszMsg2 )
		cerr << pszMsg2 << endl;
#endif
}

int yylex() {
	char	c;
	yylval.l = 0;
	while( *pStr ) {
		c = *pStr++;
		
		if( isdigit( c ) ) {
			yylval.l = 0;
			while( c ) {
				yylval.l *= 10;
				yylval.l += (long) ( c - '0' );
				c = *pStr++;
				if( c < '0' || c > '9' ) {
					pStr--;
					break;
				}
			}
			return NUMBER;
		} else {
			switch( c ) {
			case 'c' :
			case 'C' :
				if( 'C' == *pStr || 'c' == *pStr ) { ++pStr; return PREFIX_CC; }
				return PREFIX_C;
			case 'l' :
			case 'L' :
				return PREFIX_L;
			case 'n' :
			case 'N' :
				if( 'O' == *pStr || 'o' == *pStr ) { ++pStr; return QUAD_NO; }
				if( 'W' == *pStr || 'w' == *pStr ) { ++pStr; return QUAD_NW; }
			case 's' :
			case 'S' :
				if( 'O' == *pStr || 'o' == *pStr ) { ++pStr; return QUAD_SO; }
				if( 'W' == *pStr || 'w' == *pStr ) { ++pStr; return QUAD_SW; }
			default :
				while( c ) {
					c = *pStr++;
					if( isalnum(c) ) {
						pStr--;
						break;
					}
				}
				return DELIMITER;
			}
		}
	}
	return EOL;
}
