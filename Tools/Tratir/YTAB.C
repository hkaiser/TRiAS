/* ATLAS*GIS-ASCII-Format: Analyse                              */
/* File: ATLPARS.Y                                              */

#if defined(sccs)
static char SccsId[] = "ATLPARS: %W%    %E%";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atlpars.h"
#include "atlerrs.h"

/* Informationsfelder */
long on = 0;                    /* Objektnummer */
long Znr = 0;			/* Z„hlnummer BO */
long id = 0;                    /* Identifikator */
char ID[IDLEN];
long lgi = -1;                  /* Anzahl der Koordinatenpaare */
double *gxi;              	/* Geometrieinformation */
double *gyi;

/* sonstige Variablen */
int koord_paare;                /* Anzahl der einzulesenden Koordinatenpaare */
long mi_code = 51100000;        /* Merkmalscode von name2 */
long u_code = DEFAULTUNIQUEIDENT; /* Merkmalscode fr Unique Ident */
int mi_werte = 1;               /* Anzahl der Merkmalswerte */
int mi_length;                  /* Laenge der Merkmalswerte */
char mi_typ = 'A';              /* Merkmalstyp */
int satz_nr = 0;                /* Nummer des Objektes im ASCII-File */
int objekt_nr = 0;              /* Nummer des Satzes im ASCII-File */
char name1[STRINGLEN+1];        /* name1 aus ATLAS-Austauschdatei */
char txt[STRINGLEN+1];          /* name2 aus ATLAS-Datei, Objektname */
char uident[STRINGLEN+1];	/* Unique Ident aus Atlas-Datei */
char name4[STRINGLEN+1];	/* Name4 (#HK930510) */
long name4_code = DEFAULTNAME4;	// MCode fr Name4

/* globale Daten */
long eps = 0;                   /* Testtoleranz */

// #define min(x,y) (((x)>(y))?(y):(x))

/* lokale Daten */
int hcpkt = 0;

typedef union  {
	struct tagSTRINGTOKEN strtok;
	struct tagNUMBERTOKEN numtok;
	struct tagFLOATTOKEN flttok;
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define T_STRING 257
#define T_STERN 258
#define T_LBDA 259
#define T_PHI 260
#define T_INT 261
#define T_FLOAT 262
YYSTYPE yylval, yyval;
#define YYERRCODE 256
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

short yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  0,
};

#define YYNPROD 19
#define YYLAST 44

short yyact[] = {
      13,      14,      38,      31,      29,      21,      37,      32,
      30,      22,      19,      43,      39,      41,      20,       7,
       8,      35,      33,      26,      24,      18,      16,      15,
      12,      11,      44,      42,      40,      36,      34,      28,
      27,      25,       5,      10,      17,       6,       4,       9,
       3,       2,       1,      23,
};

short yypact[] = {
   -1000,   -1000,    -242,   -1000,    -242,   -1000,    -261,     -21,
     -22,   -1000,    -261,   -1000,     -23,   -1000,   -1000,    -247,
    -252,   -1000,    -261,     -24,      23,     -25,      22,      21,
    -253,   -1000,    -254,   -1000,   -1000,     -26,      20,     -27,
      19,    -255,   -1000,    -249,   -1000,      18,     -31,      17,
   -1000,    -250,   -1000,      16,   -1000,
};

short yypgo[] = {
       0,      42,      24,      41,      40,      38,      34,      37,
      35,      25,
};

short yyr1[] = {
       0,       3,       1,       4,       5,       5,       6,       7,
       7,       7,       7,       7,       7,       7,       8,       8,
       9,       2,       2,
};

short yyr2[] = {
       0,       0,       2,       1,       1,       2,       2,       8,
      10,       6,       4,       8,       6,       4,       1,       2,
       4,       1,       1,
};

short yychk[] = {
   -1000,      -1,      -3,      -4,      -5,      -6,      -7,     257,
     258,      -6,      -8,      -9,      -2,     261,     262,      44,
      44,      -9,      44,     257,     261,     257,     261,      -2,
      44,      10,      44,      10,      10,     257,     261,     257,
     261,      44,      10,      44,      10,     261,     257,     261,
      10,      44,      10,     261,      10,
};

short yydef[] = {
       1,      -2,       0,       2,       3,       4,       0,       0,
       0,       5,       6,      14,       0,      17,      18,       0,
       0,      15,       0,       0,       0,       0,       0,       0,
       0,      10,       0,      13,      16,       0,       0,       0,
       0,       0,       9,       0,      12,       0,       0,       0,
       7,       0,      11,       0,       8,
};

short *yyxi;
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
      
      case 1:{			
      			print_hdr (u_code);	// KopfSatz schreiben
      		} break;
      case 2:{
      			print_trailer ();	// EndeSatz schreiben
      		} break;
      case 6:{
      			save_object();
      		} break;
      case 7:{       
      			on++;
      			if (y_flag) {
      				if (d_flag)	id = atol (yypvt[-7].strtok.string);
      				else		id = xtol (yypvt[-7].strtok.string);
      			} else {
      				strcpy (ID, yypvt[-7].strtok.string);
      			}
      			strncpy (txt, yypvt[-5].strtok.string, STRINGLEN);
      			strncpy (name1, yypvt[-7].strtok.string, STRINGLEN);
      			koord_paare = yypvt[-1].numtok.intnum;
      // neu: 15.3.92(KK): UNIQUE ident ist unter '$5.string' verfügbar
      			strncpy (uident, yypvt[-3].strtok.string, STRINGLEN);
      			name4[0] = '\0';
      			init_new_object();
      		} break;
      case 8:{       
      			on++;
      			if (y_flag) {
      				if (d_flag)	id = atol (yypvt[-9].strtok.string);
      				else		id = xtol (yypvt[-9].strtok.string);
      			} else {
      				strcpy (ID, yypvt[-9].strtok.string);
      			}
      			strncpy (txt, yypvt[-7].strtok.string, STRINGLEN);
      			strncpy (name1, yypvt[-9].strtok.string, STRINGLEN);
      			koord_paare = yypvt[-1].numtok.intnum;
      			strncpy (uident, yypvt[-5].strtok.string, STRINGLEN);
      			strncpy (name4, yypvt[-3].strtok.string, STRINGLEN);
      			init_new_object();
      		} break;
      case 9:{       
      			on++;
      			if (y_flag) {
      				if (d_flag)	id = atol (yypvt[-5].strtok.string);
      				else		id = xtol (yypvt[-5].strtok.string);
      			} else {
      				strcpy (ID, yypvt[-5].strtok.string);
      			}
      			strncpy (txt,yypvt[-3].strtok.string,STRINGLEN);
      			strncpy (name1,yypvt[-5].strtok.string,STRINGLEN);
      			koord_paare = yypvt[-1].numtok.intnum;
      			name4[0] = '\0';
      			init_new_object();
      		} break;
      case 10:{       
      			on++;
      			if (y_flag) {
      				if (d_flag)	id = atol (yypvt[-3].strtok.string);
      				else		id = xtol (yypvt[-3].strtok.string);
      			} else {
      				strcpy (ID, yypvt[-3].strtok.string);
      			}
      			strncpy (name1,yypvt[-3].strtok.string,STRINGLEN);
      			txt[0]='\0';
      			koord_paare = yypvt[-1].numtok.intnum;
      			name4[0] = '\0';
      			init_new_object();
      		} break;
      case 11:{                            
      			on++;
      			strncpy (txt,yypvt[-5].strtok.string,STRINGLEN);
      // neu: 15.3.92(KK): UNIQUE ident ist unter '$5.string' verfügbar
      			strncpy (uident, yypvt[-3].strtok.string,STRINGLEN);
      			koord_paare = yypvt[-1].numtok.intnum;
      			name4[0] = '\0';
      			init_new_object();
      		} break;
      case 12:{       
      			on++;
      			strncpy (txt,yypvt[-3].strtok.string,STRINGLEN);
      			koord_paare = yypvt[-1].numtok.intnum;
      			name4[0] = '\0';
      			init_new_object();
      		} break;
      case 13:{       
      			on++;
      			txt[0]='\0';
      			koord_paare = yypvt[-1].numtok.intnum;
      			name4[0] = '\0';
      			init_new_object();
      		} break;
      case 16:{
      			lgi += 1;
      			gyi[lgi] = yypvt[-1].flttok.fltnum;
      			gxi[lgi] = yypvt[-3].flttok.fltnum;
      		} break;
      case 17:{
      			yyval.flttok.fltnum = (double)yypvt[-0].numtok.intnum;
      		} break;
      case 18:{
      			yyval.flttok.fltnum = yypvt[-0].flttok.fltnum;
      		} break;    }
    goto enstack;
}
