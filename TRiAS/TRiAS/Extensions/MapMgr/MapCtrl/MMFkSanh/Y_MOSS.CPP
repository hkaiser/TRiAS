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
typedef union  {
	double	v;
	C		c;
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define EOL 257
#define EMBEDDINGS 258
#define UORMIN 259
#define UORMAX 260
#define CONTROLPOINTS 261
#define POINTPAIR 262
#define FILEPOINT 263
#define WORLDPOINT 264
#define COORDVAL 265
YYSTYPE yylval, yyval;
#define YYERRCODE 256


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

#define YYNPROD 15
#define YYLAST 41

int yyact[] = {
      27,      21,      23,      10,      20,       8,       9,       7,
       8,       9,       7,       2,      14,      25,      28,      16,
      15,      12,       4,      13,       6,       5,      11,       3,
       1,      19,      17,      22,       0,       0,       0,      18,
       0,       0,       0,       0,       0,      24,       0,       0,
      26,
};

int yypact[] = {
    -247,   -1000,    -251,    -254,   -1000,   -1000,   -1000,    -250,
     -25,     -25,   -1000,   -1000,   -1000,    -250,    -259,   -1000,
    -264,   -1000,   -1000,    -262,     -25,     -31,   -1000,     -25,
   -1000,    -265,   -1000,     -27,   -1000,
};

int yypgo[] = {
       0,      16,      27,      25,      24,      23,      18,      21,
      20,      17,      19,
};

int yyr1[] = {
       0,       4,       5,       5,       6,       6,       6,       7,
       8,       9,       9,      10,       3,       2,       1,
};

int yyr2[] = {
       0,       3,       2,       1,       1,       1,       2,       2,
       2,       1,       2,       3,       2,       2,       5,
};

int yychk[] = {
   -1000,      -4,     258,      -5,      -6,      -7,      -8,     261,
     259,     260,     257,      -6,      -9,     -10,     262,      -1,
      40,      -1,      -9,      -3,     263,     265,      -2,     264,
      -1,      44,      -1,     265,      41,
};

int yydef[] = {
       0,      -2,       0,       0,       3,       4,       5,       0,
       0,       0,       1,       2,       6,       9,       0,       7,
       0,       8,      10,       0,       0,       0,      11,       0,
      12,       0,      13,       0,      14,
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
		
case 1:{
		m_state = true;
	} break;
case 7:{
		m_pC->insert( _T("min"), GEOPOINT( yypvt[-0].c.X, yypvt[-0].c.Y ) );
	} break;
case 8:{
		m_pC->insert( _T("max"), GEOPOINT( yypvt[-0].c.X, yypvt[-0].c.Y ) );
	} break;
case 11:{
		m_pG->push_back( GCP( GEOPOINT(yypvt[-0].c.X,yypvt[-0].c.Y), GEOPOINT(yypvt[-1].c.X,yypvt[-1].c.Y) ) );
	} break;
case 12:{
		yyval.c = yypvt[-0].c;
	} break;
case 13:{
		yyval.c = yypvt[-0].c;
	} break;
case 14:{
		yyval.c.X = yypvt[-3].v; yyval.c.Y = yypvt[-1].v;
	} break;
          }
    goto enstack;
}

#ifdef YY_NAMESPACE
} 	// close namespace
#endif
