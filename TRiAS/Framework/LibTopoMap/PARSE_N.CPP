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

typedef union  {
	int			l;
	MAPCOORD	c;
	} YYSTYPE;
#define YYSUNION /* %union occurred */
#define PREFIX_CC 257
#define PREFIX_C 258
#define PREFIX_L 259
#define QUAD_SW 260
#define QUAD_SO 261
#define QUAD_NO 262
#define QUAD_NW 263
#define NUMBER 264
#define DELIMITER 265
#define EOL 266
YYSTYPE yylval, yyval;
#define YYERRCODE 256


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

#include <stdio.h>
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

int yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  0,
};

#define YYNPROD 16
#define YYLAST 22

int yyact[] = {
       8,       9,      10,      12,      13,      11,       6,      11,
      18,      19,      21,      20,       2,       1,       7,      14,
      15,      16,       5,       4,       3,      17,
};

int yypact[] = {
    -257,   -1000,    -263,   -1000,   -1000,   -1000,    -261,   -1000,
    -259,    -259,    -259,   -1000,   -1000,    -252,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
};

int yypgo[] = {
       0,      21,      20,      19,      18,       6,      14,      13,
      12,
};

int yyr1[] = {
       0,       7,       8,       8,       8,       8,       8,       2,
       3,       4,       5,       6,       1,       1,       1,       1,
};

int yyr2[] = {
       0,       2,       1,       1,       1,       1,       1,       2,
       2,       2,       1,       3,       1,       1,       1,       1,
};

int yychk[] = {
   -1000,      -7,      -8,      -2,      -3,      -4,      -5,      -6,
     257,     258,     259,     264,     266,     265,      -5,      -5,
      -5,      -1,     260,     261,     263,     262,
};

int yydef[] = {
       0,      -2,       0,       2,       3,       4,       5,       6,
       0,       0,       0,      10,       1,       0,       7,       8,
       9,      11,      12,      13,      14,      15,
};


const int *yyxi;
/*****************************************************************/
/* PCYACC LALR parser driver routine -- a table driven procedure */
/* for recognizing sentences of a language defined by the        */
/* grammar that PCYACC analyzes. An LALR parsing table is then   */
/* constructed for the grammar and the skeletal parser uses the  */
/* table when performing syntactical analysis on input source    */
/* programs. The actions associated with grammar rules are       */
/* inserted into a switch statement for execution.               */
/*****************************************************************/


#ifndef YYMAXDEPTH
#define YYMAXDEPTH 200
#endif
#ifndef YYREDMAX
#define YYREDMAX 1000
#endif
#define PCYYFLAG -1000
#define WAS0ERR 0
#define WAS1ERR 1
#define WAS2ERR 2
#define WAS3ERR 3
#define yyclearin pcyytoken = -1
#define yyerrok   pcyyerrfl = 0
YYSTYPE yyv[YYMAXDEPTH];     /* value stack, ( YYSTYPE explicit or %union ) */
int pcyyerrct = 0;           /* error count */
int pcyyerrfl = 0;           /* error flag */
int redseq[YYREDMAX];
int redcnt = 0;
int pcyytoken = -1;          /* input token */


int yylex( void );


int yyparse( )
{
  int statestack[YYMAXDEPTH]; /* state stack */
  int      j, m;              /* working index */
  YYSTYPE *yypvt;
  int      tmpstate, *yyps, n;
  YYSTYPE *yypv;
#ifdef YYDEBUG
  int tmptoken = -1;
#endif


  tmpstate = 0;
  pcyytoken = -1;
  pcyyerrct = 0;
  pcyyerrfl = 0;
  yyps = &statestack[-1];
  yypv = &yyv[-1];


  enstack:    /* push stack */
#ifdef YYDEBUG
    printf("at state %d, next token %d\n", tmpstate, tmptoken);
#endif
    if (++yyps - &statestack[YYMAXDEPTH-1] > 0) {
      yyerror("pcyacc internal stack overflow");
      return(1);
    }
    *yyps = tmpstate;
    ++yypv;
    *yypv = yyval;


  newstate:
    n = yypact[tmpstate];
    if (n <= PCYYFLAG) goto defaultact; /*  a simple state */


    if (pcyytoken < 0) if ((pcyytoken=yylex()) < 0) pcyytoken = 0;
    if ((n += pcyytoken) < 0 || n >= YYLAST) goto defaultact;


    if (yychk[n=yyact[n]] == pcyytoken) { /* a shift */
#ifdef YYDEBUG
      tmptoken  = pcyytoken;
#endif
      pcyytoken = -1;
      yyval = yylval;
      tmpstate = n;
      if (pcyyerrfl > 0) --pcyyerrfl;
      goto enstack;
    }


  defaultact:


    if ((n=yydef[tmpstate]) == -2) {
      if (pcyytoken < 0) if ((pcyytoken=yylex())<0) pcyytoken = 0;
      for (yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=tmpstate); yyxi += 2);
      while (*(yyxi+=2) >= 0) if (*yyxi == pcyytoken) break;
      if ( (n=yyxi[1]) < 0 ) { /* an accept action */
#ifdef YYTFLAG
          yytfilep = fopen(yytfilen, "w");
          if (yytfilep == NULL) {
            fprintf(stderr, "Can't open t file: %s\n", yytfilen);
            return(0);          }
          for (ti=redcnt-1; ti>=0; ti--) {
            tj = svdprd[redseq[ti]];
            while (strcmp(svdnams[tj], "$EOP"))
              fprintf(yytfilep, "%s ", svdnams[tj++]);
            fprintf(yytfilep, "\n");
          }
          fclose(yytfilep);
#endif
        return (0); /* EOF return ok */

      }
    }


    if (n == 0) {        /* error situation */
      switch (pcyyerrfl) {
        case WAS0ERR:          /* an error just occurred */
          yyerror("syntax error");
            ++pcyyerrct;
        case WAS1ERR:
        case WAS2ERR:           /* try again */
          pcyyerrfl = 3;
	   /* find a state for a legal shift action */
          while (yyps >= statestack) {
	     n = yypact[*yyps] + YYERRCODE;
	     if (n >= 0 && n < YYLAST && yychk[yyact[n]] == YYERRCODE) {
	       tmpstate = yyact[n];  /* simulate a shift of "error" */
	       goto enstack;
            }
	     n = yypact[*yyps];


	     /* the current yyps has no shift on "error", pop stack */
#ifdef YYDEBUG
            printf("error: pop state %d, recover state %d\n", *yyps, yyps[-1]);
#endif
	     --yyps;
	     --yypv;
	   }


	   yyabort:
#ifdef YYTFLAG
              yytfilep = fopen(yytfilen, "w");
              if (yytfilep == NULL) {
                fprintf(stderr, "Can't open t file: %s\n", yytfilen);
                return(1);              }
              for (ti=1; ti<redcnt; ti++) {
                tj = svdprd[redseq[ti]];
                while (strcmp(svdnams[tj], "$EOP"))
                  fprintf(yytfilep, "%s ", svdnams[tj++]);
                fprintf(yytfilep, "\n");
              }
              fclose(yytfilep);
#endif
	     return(1);


	 case WAS3ERR:  /* clobber input char */
#ifdef YYDEBUG
          printf("error: discard token %d\n", pcyytoken);
#endif
          if (pcyytoken == 0) goto yyabort; /* quit */
	   pcyytoken = -1;
	   goto newstate;      } /* switch */
    } /* if */


    /* reduction, given a production n */
#ifdef YYDEBUG
    printf("reduce with rule %d\n", n);
#endif
    if (yytflag && redcnt<YYREDMAX) redseq[redcnt++] = n;
    yyps -= yyr2[n];
    yypvt = yypv;
    yypv -= yyr2[n];
    yyval = yypv[1];
    m = n;
    /* find next state from goto table */
    n = yyr1[n];
    j = yypgo[n] + *yyps + 1;
    if (j>=YYLAST || yychk[ tmpstate = yyact[j] ] != -n) tmpstate = yyact[yypgo[n]];
    switch (m) { /* actions associated with grammar rules */
		
case 2:{ mapCoord = yypvt[-0].c; DC( yypvt[-0].c ); } break;
case 3:{ mapCoord = yypvt[-0].c; DC( yypvt[-0].c ); } break;
case 4:{ mapCoord = yypvt[-0].c; DC( yypvt[-0].c ); } break;
case 5:{ mapCoord = yypvt[-0].c; DC( yypvt[-0].c ); } break;
case 6:{ mapCoord = yypvt[-0].c; DC( yypvt[-0].c ); } break;
case 7:{
		ZEROINIT( yyval.c );
		if( ( 0 == ( ( yypvt[-0].c.pt.x + 2400 ) % 4800 ) ) && ( 0 == ( yypvt[-0].c.pt.y % 2880 ) ) )
		{
			yyval.c.scale = 200000;
			yyval.c.sz.cx = 8 * yypvt[-0].c.sz.cx;
			yyval.c.sz.cy = 8 * yypvt[-0].c.sz.cy;
			yyval.c.pt = yypvt[-0].c.pt;
		}
		else
			yyerror( "nicht im Raster" );
	} break;
case 8:{
		ZEROINIT( yyval.c );
		if( 0 == yypvt[-0].c.pt.x % 2400 && 0 == yypvt[-0].c.pt.y % 1440 )
		{
			yyval.c.scale = 100000;
			yyval.c.sz.cx = 4 * yypvt[-0].c.sz.cx;
			yyval.c.sz.cy = 4 * yypvt[-0].c.sz.cy;
			yyval.c.pt = yypvt[-0].c.pt;
		}
		else
			yyerror( "nicht im Raster" );
	} break;
case 9:{
		ZEROINIT( yyval.c );
		if( 0 == yypvt[-0].c.pt.x % 1200 && 0 == yypvt[-0].c.pt.y % 720 )
		{
			yyval.c.sz.cx = 2 * yypvt[-0].c.sz.cx;
			yyval.c.sz.cy = 2 * yypvt[-0].c.sz.cy;
			yyval.c.pt = yypvt[-0].c.pt;
			yyval.c.scale = 50000;
		}
		else
			yyerror( "nicht im Raster" );
	} break;
case 10:{
		ZEROINIT( yyval.c );
		yyval.c.sz.cx = 600;
		yyval.c.sz.cy = 360;
		yyval.c.pt.x = 20400; yyval.c.pt.x += ( yypvt[-0].l % 100 ) * yyval.c.sz.cx;
		yyval.c.pt.y = 201240; yyval.c.pt.y -= ( yypvt[-0].l / 100 ) * yyval.c.sz.cy;
		yyval.c.scale = 25000;
	} break;
case 11:{
		ZEROINIT( yyval.c );
		yyval.c.scale = 10000;
		yyval.c.sz.cx = yypvt[-2].c.sz.cx / 2;
		yyval.c.sz.cy = yypvt[-2].c.sz.cy / 2;
		switch( yypvt[-0].l )
		{
		case 0 :
			yyval.c.pt.x = yypvt[-2].c.pt.x;
			yyval.c.pt.y = yypvt[-2].c.pt.y;
			break;
		case 1 :
			yyval.c.pt.x = yypvt[-2].c.pt.x + yyval.c.sz.cx;
			yyval.c.pt.y = yypvt[-2].c.pt.y;
			break;
		case 2 :
			yyval.c.pt.x = yypvt[-2].c.pt.x + yyval.c.sz.cx;
			yyval.c.pt.y = yypvt[-2].c.pt.y + yyval.c.sz.cy; 
			break;
		case 3 :
			yyval.c.pt.x = yypvt[-2].c.pt.x;
			yyval.c.pt.y = yypvt[-2].c.pt.y + yyval.c.sz.cy; 
			break;
		}
	} break;
case 12:{ yyval.l = 0; } break;
case 13:{ yyval.l = 1; } break;
case 14:{ yyval.l = 2; } break;
case 15:{ yyval.l = 3; } break;
          }
    goto enstack;
}

#ifdef YY_NAMESPACE
} 	// close namespace
#endif
