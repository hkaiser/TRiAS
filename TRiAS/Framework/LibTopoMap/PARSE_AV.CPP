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

typedef union  {
	int			l;
	MAPCOORD	c;
	} YYSTYPE;
#define YYSUNION /* %union occurred */
#define DIGIT 257
#define DELIMITER 258
#define EOL 259
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

#define YYNPROD 10
#define YYLAST 15

int yyact[] = {
       8,       9,      15,      14,      13,      12,      11,      10,
       7,       2,       1,       6,       5,       4,       3,
};

int yypact[] = {
    -249,   -1000,    -259,    -257,    -250,    -251,   -1000,    -252,
   -1000,    -253,   -1000,   -1000,    -254,   -1000,    -255,   -1000,
};

int yypgo[] = {
       0,      14,      13,      12,      11,      10,       9,
};

int yyr1[] = {
       0,       5,       6,       6,       6,       6,       1,       2,
       3,       4,
};

int yyr2[] = {
       0,       2,       1,       1,       1,       1,       4,       3,
       2,       2,
};

int yychk[] = {
   -1000,      -5,      -6,      -1,      -2,      -3,      -4,     257,
     259,     258,     257,     257,     257,     257,     257,     257,
};

int yydef[] = {
       0,      -2,       0,       2,       3,       4,       5,       0,
       1,       0,       8,       9,       0,       7,       0,       6,
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
case 6:{
		ZEROINIT( yyval.c );
		int	row = yypvt[-3].l * 10 + yypvt[-2].l;
		int	col = yypvt[-1].l * 10 + yypvt[-0].l;
		if( row < 1 )
			yyerror( "Invalid row" );
		if( col < 1 )
			yyerror( "Invalid col" );
		yyval.c.sz.cx = 1800;
		yyval.c.sz.cy = 1200;
		yyval.c.pt.x = 34200 + ( col - 1 )  * yyval.c.sz.cx;
		yyval.c.pt.y = 198000 - row * yyval.c.sz.cy;
		yyval.c.scale = 100000;
	} break;
case 7:{
		ZEROINIT( yyval.c );
		if( yypvt[-0].l < 1 || yypvt[-0].l > 3 )
			yyerror( "Invalid quadrant" );
		yyval.c.pt.x = yypvt[-2].c.pt.x;
		yyval.c.pt.y = yypvt[-2].c.pt.y;
		yyval.c.sz.cx = yypvt[-2].c.sz.cx / 2;
		yyval.c.sz.cy = yypvt[-2].c.sz.cy / 2;
		if( 2 == yypvt[-0].l || 4 == yypvt[-0].l )
			yyval.c.pt.x += yyval.c.sz.cx;
		if( 1 == yypvt[-0].l || 2 == yypvt[-0].l )
			yyval.c.pt.y += yyval.c.sz.cy;
		yyval.c.scale = yypvt[-2].c.scale / 2;
	} break;
case 8:{
		ZEROINIT( yyval.c );
		if( yypvt[-0].l < 1 || yypvt[-0].l > 3 )
			yyerror( "Invalid quadrant" );
		yyval.c.pt.x = yypvt[-1].c.pt.x;
		yyval.c.pt.y = yypvt[-1].c.pt.y;
		yyval.c.sz.cx = yypvt[-1].c.sz.cx / 2;
		yyval.c.sz.cy = yypvt[-1].c.sz.cy / 2;
		if( 2 == yypvt[-0].l || 4 == yypvt[-0].l )
			yyval.c.pt.x += yyval.c.sz.cx;
		if( 1 == yypvt[-0].l || 2 == yypvt[-0].l )
			yyval.c.pt.y += yyval.c.sz.cy;
		yyval.c.scale = yypvt[-1].c.scale / 2;
	} break;
case 9:{
		ZEROINIT( yyval.c );
		if( yypvt[-0].l < 1 || yypvt[-0].l > 3 )
			yyerror( "Invalid quadrant" );
		yyval.c.pt.x = yypvt[-1].c.pt.x;
		yyval.c.pt.y = yypvt[-1].c.pt.y;
		yyval.c.sz.cx = yypvt[-1].c.sz.cx / 2;
		yyval.c.sz.cy = yypvt[-1].c.sz.cy / 2;
		if( 2 == yypvt[-0].l || 4 == yypvt[-0].l )
			yyval.c.pt.x += yyval.c.sz.cx;
		if( 1 == yypvt[-0].l || 2 == yypvt[-0].l )
			yyval.c.pt.y += yyval.c.sz.cy;
		yyval.c.scale = yypvt[-1].c.scale / 2;
	} break;
          }
    goto enstack;
}

#ifdef YY_NAMESPACE
} 	// close namespace
#endif
