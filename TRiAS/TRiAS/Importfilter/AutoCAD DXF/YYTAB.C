
# line 16 "dxfy.y"
#include "pheader.hpp"
#include "lextypes.h"				// lex-spezifische Typ-Definitionen

extern "C" 
{
	#include "float.h"		// DBL_MAX
}

// Prototypen 
int yylex (void);
void yyerror (short ResourceID);

// externe Variablen
extern double XMin;		 // Bildmaße
extern double YMin;
extern double XMax;
extern double YMax;

# line 34 "dxfy.y"
typedef union  {
	struct {
		double real1;
		double real2;
		double real3;
	} real_struct; 
	short integer;
	char *str_ptr;
	double real;				
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define FLAG0 257
#define KOORD 258
#define FLOAT 259
#define WINKEL0 260
#define WINKEL1 261
#define TEXT0 262
#define LAYER_NAME 263
#define BLOCK_NAME 264
#define NAME 265
#define ANFANG 266
#define SECTION 267
#define END_SECT 268
#define END_OF_FILE 269
#define ENTITIES 270
#define HEADER 271
#define BLOCKS 272
#define TABLES 273
#define VERSION 274
#define EXT_MIN 275
#define EXT_MAX 276
#define LAST_EDIT 277
#define LEX_ERROR 278
#define LINE 279
#define POLY_LINE 280
#define VERTEX 281
#define SEQEND 282
#define CIRCLE 283
#define ARC 284
#define TEXT_ELEM 285
#define POINT 286
#define INSERT 287
#define TRACE_ELEM 288
#define SOLID 289
#define SHAPE 3
#define DLINE 3
#define DFACE 292
#define ATTRIB 293
#define SYMBOL_NAME 294
YYSTYPE yylval, yyval;
#define YYERRCODE 256

# line 191 "dxfy.y"


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

#define YYNPROD 37
#define YYLAST 81

int yyact[] = {
      15,      36,      46,      31,      48,      15,      38,      37,
      35,      41,      45,      43,      39,      34,      34,      51,
      49,      20,      27,      28,      29,      30,      16,      27,
      28,      29,      30,      16,      15,      42,      33,       9,
      21,       3,      32,      11,      18,      25,      24,      17,
      23,      14,      26,      22,      12,      13,      19,      10,
       8,       7,      16,      26,      40,       6,       5,       4,
       2,       1,       0,      44,       0,       0,       0,      47,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,      50,       0,
      52,
};

int yypact[] = {
    -228,   -1000,    -228,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,    -251,    -265,    -260,    -267,   -1000,   -1000,
   -1000,    -264,   -1000,    -256,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,    -253,    -247,    -247,    -249,   -1000,
    -266,   -1000,    -259,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,    -242,   -1000,   -1000,   -1000,   -1000,
    -247,    -243,    -247,   -1000,   -1000,
};

int yypgo[] = {
       0,      29,      57,      56,      33,      55,      54,      53,
      49,      48,      31,      47,      46,      32,      43,      40,
      38,      37,      35,      34,      30,
};

int yyr1[] = {
       0,       2,       3,       3,       4,       4,       4,       4,
       4,       4,      10,      10,       9,       7,       8,       5,
       5,      11,      12,      12,      13,      13,      13,      13,
      13,      14,      15,      16,      17,       1,       1,       6,
       6,      18,      19,      19,      20,
};

int yyr2[] = {
       0,       1,       1,       2,       1,       1,       1,       1,
       1,       1,       1,       1,       1,       2,       2,       3,
       2,       2,       1,       2,       1,       1,       1,       1,
       1,       2,       2,       2,       2,       2,       3,       2,
       3,       2,       1,       2,       4,
};

int yychk[] = {
   -1000,      -2,      -3,      -4,      -5,      -6,      -7,      -8,
      -9,     -10,     -11,     -18,     272,     273,     269,     256,
     278,     267,      -4,     -12,     268,     -13,     -14,     -15,
     -16,     -17,     -10,     274,     275,     276,     277,     268,
     -19,     -20,     279,     268,     268,     271,     270,     268,
     -13,     262,      -1,     258,      -1,     259,     268,     -20,
     263,     258,      -1,     258,      -1,
};

int yydef[] = {
       0,      -2,       1,       2,       4,       5,       6,       7,
       8,       9,       0,       0,       0,       0,      12,      10,
      11,       0,       3,       0,      16,      18,      20,      21,
      22,      23,      24,       0,       0,       0,       0,      31,
       0,      34,       0,      13,      14,      17,      33,      15,
      19,      25,      26,       0,      27,      28,      32,      35,
       0,      29,       0,      30,      36,
};

int *yyxi;
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
YYSTYPE yyv[YYMAXDEPTH];     /* value stack */
int pcyyerrct = 0;           /* error count */
int pcyyerrfl = 0;           /* error flag */
int redseq[YYREDMAX];
int redcnt = 0;
int pcyytoken = -1;          /* input token */


yyparse()
{
  int statestack[YYMAXDEPTH]; /* state stack */
  int      j, m;              /* working index */
  YYSTYPE *yypvt;
  int      tmpstate, tmptoken, *yyps, n;
  YYSTYPE *yypv;


  tmpstate = 0;
  pcyytoken = -1;
#ifdef YYDEBUG
  tmptoken = -1;
#endif
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
      if ((n=yyxi[1]) < 0) { /* an accept action */
        if (yytflag) {
          int ti; int tj;
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
        }
        return (0);
      }
    }


    if (n == 0) {        /* error situation */
      switch (pcyyerrfl) {
        case WAS0ERR:          /* an error just occurred */
          yyerror("syntax error");
          yyerrlab:
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
            if (yytflag) {
              int ti; int tj;
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
            }
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
      
      case 10:
# line 80 "dxfy.y"
      {  
      			   yyclearin; 		
      			} break;
      case 11:
# line 85 "dxfy.y"
      {
      			   return FALSE;			// Fehler bereits ausgegeben
      			} break;
      case 12:
# line 91 "dxfy.y"
      { 
      				// hier evtl. Ausgabe eines Ergebnis-Dialogs
      				return TRUE;
      			} break;
      case 15:
# line 104 "dxfy.y"
      {
      				// Scale und Offset ggf. ausgeben	
      			} break;
      case 16:
# line 109 "dxfy.y"
      {	// leere Section: Checklauf zur Bestimmung der Bildmaße ggf. durchführen
      				// Scale und Offset ggf. ausgeben	
      			} break;
      case 25:
# line 131 "dxfy.y"
      {
      				// Version ggf. in Dialog-Fenster ausgeben
      				if (yypvt[-0].str_ptr)
      					delete yypvt[-0].str_ptr;
      			} break;
      case 26:
# line 139 "dxfy.y"
      {	// Werte erstmal speichern
      				XMin = yypvt[-0].real_struct.real1;
      				YMin = yypvt[-0].real_struct.real2;
      			} break;
      case 27:
# line 146 "dxfy.y"
      {
      				// Werte erstmal speichern
      				XMax = yypvt[-0].real_struct.real1;
      				YMax = yypvt[-0].real_struct.real2;
      			} break;
      case 28:
# line 154 "dxfy.y"
      {
      				/* evtl. julianische(s) Zeit/Datum ausgeben */
      			} break;
      case 29:
# line 160 "dxfy.y"
      {
      				yyval.real_struct.real1 = yypvt[-1].real;
      				yyval.real_struct.real2 = yypvt[-0].real;
      				yyval.real_struct.real3 = DBL_MAX;
      			} break;
      case 30:
# line 166 "dxfy.y"
      {
      				yyval.real_struct.real1 = yypvt[-2].real;
      				yyval.real_struct.real2 = yypvt[-1].real;
      				yyval.real_struct.real3 = yypvt[-0].real;
      			} break;
      case 36:
# line 186 "dxfy.y"
      {
      				if (yypvt[-2].str_ptr)
      					delete (yypvt[-2].str_ptr);
      			} break;    }
    goto enstack;
}
