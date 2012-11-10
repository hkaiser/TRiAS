/* ASCII-Format: Analyse, Put etc.                              */
/* File: ASCPARS.Y                                              */

#if defined(sccs)
static char SccsId[] = "ASCPARS: %W%	%E%";
#endif

#include "StdAfx.h"

#include "ascbna.h"
#include "ascerrs.h"

#include "input.h"

// Prototyp von yylex / yyparse
int yylex (void);
int yyparse (void);

// #define yyerrok errfl = 0

/* Informationsfelder */
long on = 0;                    /* Objektnummer */
//long id;                        /* Identifikator */
char cbOKS[64];					// Objektklassenschlüssel
long sta[2] = { E_OBJEKT, 0 };  /* Status */
long mi[MAXMI] = { MAXMI, 0, }; /* Merkmalsinformation */
double gxi[MAXGI];                /* Geometrieinformation */
double gyi[MAXGI];
long lgi = -1;                  /* Anzahl der Koordinatenpaare */
long maxgi = MAXGI;

long *curr_mi = &mi[-1];         /* Merkmalsfeldzeiger */
char *curr_mi_text = (char *)&mi[5]; /* Merkmalsfeldzeiger fuer Text */

int mi_count = 3;               /* Zaehler der I*4 Merkmalsfelder */

/* sonstige Variablen */
int koord_paare;                /* Anzahl der einzulesenden Koordinatenpaare */
int mi_werte = 0;               /* Anzahl der einzulesenden Merkmalswerte */
int mi_length;                  /* Laenge der Merkmalswerte */
int satz_nr = 0;                /* Nummer des Objektes im ASCII-File */
int objekt_nr = 0;              /* Nummer des Satzes im ASCII-File */

/* globale Daten */
long eps = -1;                  /* Testtoleranz */

long lTextObjMCode = TEXTOBJMCODE;	// MerkmalsCode, an dem bei Textobjekten der Text hängt

extern int r_flag;		// Relationen ignorieren
extern int d_flag;

/* lokale Daten */
static char comment[STRINGLEN+1];
static short fFirstIdent = TRUE;

char *UniqueIdentKey = 	"Unique Ident    ";
char *IdentBase =	"IdentBase       ";


typedef union  {
	STRING_TOKEN strtok;
	NUMBER_TOKEN numtok;
	FLOAT_TOKEN flttok;
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define T_STRING 257
#define T_MISTRING 258
#define T_INTEGER 259
#define T_PSATZ 260
#define T_LSATZ 261
#define T_FSATZ 262
#define T_DSATZ 263
#define T_GSATZ 264
#define T_MSATZ 265
#define T_RSATZ 266
#define T_TSATZ 267
#define T_WSATZ 268
#define T_ESATZ 269
#define T_IDENT 270
#define T_BSATZ 271
#define T_ISATZ 272
#define T_CSATZ 273
#define T_VSATZ 274
#define T_HRELSATZ 275
#define T_KRELSATZ 276
#define T_BRELSATZ 277
#define T_KOSATZ 278
#define T_HEXINTEGER 279
#define T_KSATZ 280
#define T_HSATZ 281
#define T_OFFSET 282
#define T_SCALE 283
#define T_ENTRY 284
#define T_PBDNAME 285
#define T_ENTRYROSYS 286
#define T_ENTRYRO 287
#define T_ENTRYSYS 288
#define T_FLOAT 289
YYSTYPE yylval, yyval;
#define YYERRCODE 256


#define YYACCEPT        return(0)
#define YYABORT         return(1)

void yyerror (char *string) 
{
	fprintf (stderr, "Zeile %d: %s\n", yylineno, string);
}

int cdecl db_error (int ec, int rc, ...)
{
	fprintf (stderr, "Zeile %d: Fehler %d in Routine %d\n", yylineno, ec, rc);

return ec;
}

#include <stdio.h>
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

short yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  -1, 7,
  280, 74,
  281, 74,
  -2, 18,
  0,
};

#define YYNPROD 81
#define YYLAST 340

short yyact[] = {
      59,      18,     119,     110,     154,      29,      30,      31,
      20,      25,      23,      24,      26,      71,     139,     123,
      32,      27,      28,     122,     113,      92,      91,      22,
      88,      19,      53,      52,      54,      58,      57,      55,
      56,      18,      19,       6,      77,      29,      30,      31,
      20,      25,      23,      24,      26,     101,      73,      99,
      32,      27,      28,     103,      34,      67,      49,      22,
     117,      19,       6,      29,      30,      31,      46,      43,
      75,      63,      76,     100,      62,     165,      32,     104,
      68,      69,      66,      61,     164,     163,      60,     152,
     151,     150,     137,     131,     130,     129,     108,     107,
     106,      84,      64,     148,     146,     166,     127,     126,
     125,     124,      97,      96,      95,      94,      93,      90,
      21,      87,      83,      36,       5,     136,      72,      48,
      45,      42,     135,      35,     167,     134,     161,     160,
     159,     158,     157,     156,     153,     145,     144,     143,
     142,     141,     140,     138,     133,     132,     128,     121,
     116,     115,     114,     112,     109,     105,     102,      79,
      98,      78,      74,      51,      50,      40,      86,      37,
       7,       3,      80,      81,      39,      85,      38,      89,
      82,     155,      70,      47,      44,      41,      33,      65,
      17,      16,       4,       2,       8,      14,      15,      13,
      12,      11,      10,       9,       1,     111,       0,       0,
       0,       0,       0,       0,      79,     118,       0,       0,
     120,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,     162,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,      88,      73,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,      84,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,     149,     147,
};

short yypact[] = {
    -223,   -1000,    -217,    -255,    -246,   -1000,     139,   -1000,
   -1000,   -1000,    -205,    -206,    -214,   -1000,   -1000,   -1000,
   -1000,   -1000,     138,     137,    -256,    -181,    -191,    -169,
    -203,    -243,     136,    -193,    -238,   -1000,   -1000,   -1000,
   -1000,   -1000,     135,    -255,   -1000,   -1000,    -255,   -1000,
   -1000,    -205,   -1000,    -170,    -206,   -1000,    -265,    -214,
   -1000,    -154,   -1000,   -1000,    -267,    -268,    -155,    -156,
    -157,    -158,    -159,     134,    -212,     132,    -208,     131,
    -171,    -172,    -173,     130,   -1000,   -1000,      -7,     129,
   -1000,    -269,   -1000,     128,     127,     126,   -1000,   -1000,
    -255,   -1000,      46,   -1000,   -1000,   -1000,      -8,   -1000,
   -1000,   -1000,     125,    -270,    -274,    -160,    -161,    -162,
    -163,     124,   -1000,    -174,    -175,    -176,   -1000,     123,
     122,   -1000,      44,    -177,     121,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,    -275,     120,     119,     118,     117,     116,
   -1000,     115,      82,      81,   -1000,   -1000,    -178,    -179,
    -180,     114,   -1000,    -285,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,   -1000,     113,   -1000,     112,     111,     110,
     109,   -1000,     108,    -201,   -1000,   -1000,   -1000,   -1000,
   -1000,   -1000,    -182,    -183,    -190,    -164,     106,   -1000,
};

short yypgo[] = {
       0,     180,     104,     107,     179,     178,     177,     176,
     175,     174,     173,     151,     172,     153,     171,     170,
     115,     169,     168,     167,     166,     165,     164,     163,
     113,     112,     111,     162,     161,     160,     106,     150,
     105,     110,
};

short yyr1[] = {
       0,       1,       1,      14,      14,      14,      14,      14,
      16,      16,       3,       3,       3,       3,       3,       3,
       3,       3,       3,       3,       3,       3,      12,      12,
      12,      12,      12,      12,      12,      12,      21,      21,
      22,      22,      23,      23,      10,      10,      13,       4,
      28,       4,       4,       4,       4,       4,       4,       4,
       4,       2,       2,       2,       2,      17,      17,      18,
       5,       6,       7,      24,      29,      29,      30,      25,
      31,      31,      32,      26,       8,       8,       8,      19,
      19,       9,      15,      15,      11,      27,      27,      33,
      20,
};

short yyr2[] = {
       0,       2,       1,       1,       2,       2,       3,       1,
       1,       2,       1,       1,       2,       2,       2,       1,
       1,       1,       1,       1,       1,       2,       7,       5,
       5,       5,       5,       5,       4,       3,       1,       2,
       1,       2,       1,       2,       3,       3,       2,       5,
       0,      12,       6,       5,       6,       3,       4,       4,
       3,       1,       1,       1,       1,       3,       3,       3,
       6,       6,       6,       3,       1,       2,       1,       3,
       1,       2,       1,       3,       5,       4,       3,       1,
       1,       2,       1,       2,       2,       1,       2,       2,
       2,
};

short yychk[] = {
   -1000,      -1,     -14,     -13,     -15,      -3,     281,     -11,
     -12,      -4,      -5,      -6,      -7,      -8,     -10,      -9,
     -17,     -18,     256,     280,     263,      -2,     278,     265,
     266,     264,     267,     272,     273,     260,     261,     262,
     271,     -20,     269,     -16,      -3,     -11,     -13,     -11,
      10,     -21,     -24,     268,     -22,     -25,     268,     -23,
     -26,     268,      10,      10,     283,     282,     284,     287,
     288,     286,     285,     256,     259,     256,     259,     256,
     259,     -19,     277,     256,     275,     276,     -27,     256,
     -33,     289,      10,     257,     259,     274,      10,      -3,
     -16,     -24,     -29,     -30,     259,     -25,     -31,     -32,
     289,     -26,     257,     289,     289,     257,     257,     257,
     257,     257,      10,     259,     279,     257,      10,     259,
     279,      10,     259,     259,     259,      10,      10,     -33,
      10,     289,      10,      10,      10,      10,     -30,      10,
     -32,      10,     289,     289,     257,     257,     257,     257,
      10,     259,     259,     259,      10,      10,      73,      70,
      65,     259,      10,     289,      10,      10,      10,      10,
      10,      10,      10,     257,      10,     257,     259,     259,
     259,      10,     289,     -28,      10,      10,      10,      10,
      10,      10,      -2,     259,     259,     259,     257,      10,
};

short yydef[] = {
       0,      -2,       2,       3,       0,       7,       0,      -2,
      10,      11,       0,       0,       0,      15,      16,      17,
      19,      20,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,      49,      50,      51,
      52,       1,       0,       4,       8,      18,       5,      75,
      38,      12,      30,       0,      13,      32,       0,      14,
      34,       0,      21,      76,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,      71,      72,       0,       0,
      77,       0,      73,       0,       0,       0,      80,       9,
       6,      31,       0,      60,      62,      33,       0,      64,
      66,      35,       0,       0,       0,       0,       0,       0,
       0,       0,      29,       0,       0,       0,      45,       0,
       0,      48,       0,       0,       0,      70,      36,      78,
      37,      79,      53,      54,      55,      59,      61,      63,
      65,      67,       0,       0,       0,       0,       0,       0,
      28,       0,       0,       0,      46,      47,       0,       0,
       0,       0,      69,       0,      23,      24,      25,      26,
      27,      39,      40,       0,      43,       0,       0,       0,
       0,      68,       0,       0,      42,      44,      56,      57,
      58,      22,       0,       0,       0,       0,       0,      41,
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
      
      case 2:{
      			if (satz_nr > 0) end_previous_object ();
      			db_error (ENOEND, ASCPARSER, yypvt[-0].numtok.num_line);
      			YYACCEPT;
      		} break;
      case 7:{
      			db_error (ENOHD, ASCPARSER, yypvt[-0].numtok.num_line);
      			YYABORT;
      		} break;
      case 21:{
      			yyerrok;
      			db_error (EBADRC, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 22:{
      			if (fphead)
      				fprintf (fphead, "D Scale %lf %lf %lf %lf\n", 
      						yypvt[-4].flttok.fltnum, yypvt[-3].flttok.fltnum,
      						yypvt[-2].flttok.fltnum, yypvt[-1].flttok.fltnum);
      
		} break;
      case 23:{
      			if (fphead)
      				fprintf (fphead, "D Offset %lf %lf\n", 
      							yypvt[-2].flttok.fltnum*dKoeff, 
      							yypvt[-1].flttok.fltnum*dKoeff);
      		} break;
      case 24:{
      			if (fphead) {
      			char KeyString[17];
      			short len;
      
				memset (KeyString, ' ', 16);
      				KeyString[16] = '\0';
      				strncpy (KeyString, yypvt[-2].strtok.string, 16);
      				if ((len = strlen (KeyString)) < 16)
      					KeyString[len] = ' ';
      				if (!strcmp (KeyString, UniqueIdentKey)) {
      				// Unique Ident gegeben
      					fprintf (fphead, "; D Entry \"%16.16s\" \"%s\"\n", KeyString, yypvt[-1].strtok.string);
      					if (lUIdent == -1L) {
      						lUIdent = atol (yypvt[-1].strtok.string);
      						if (lUIdent == 0)
      							lUIdent = -1L;
      					}
      				} if (!strcmp (KeyString, IdentBase)) {
      		 		// Zahlenbasis für Identifikator einstellen (Hex hat Vorrang)
      					if (d_flag) 
      						d_flag = (atoi (yypvt[-1].strtok.string) == 10);
      				} else
      					fprintf (fphead, "D Entry \"%16.16s\" \"%s\"\n", KeyString, yypvt[-1].strtok.string);
      			}
      		} break;
      case 25:{
      			if (fphead)
      				fprintf(fphead, "D EntryRo \"%16.16s\" \"%s\"\n", yypvt[-2].strtok.string, yypvt[-1].strtok.string);
      		} break;
      case 26:{
      			if (fphead)
      				fprintf(fphead, "D EntrySys \"%16.16s\" \"%s\"\n", yypvt[-2].strtok.string, yypvt[-1].strtok.string);
      		} break;
      case 27:{
      			if (fphead)
      				fprintf(fphead, "D EntryRoSys \"%16.16s\" \"%s\"\n", yypvt[-2].strtok.string, yypvt[-1].strtok.string);
      		} break;
      case 28:{
      			if (fphead)
      				fprintf (fphead, "D PbdName \"%s\"\n", yypvt[-1].strtok.string);
      		} break;
      case 29:{
      			yyerrok;
      			db_error (EBADRC, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 37:{
      			yyerrok;
      			db_error (EKOORD, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 38:{
      			fFirstIdent = TRUE;
      		} break;
      case 39:{
      			if (!d_flag) 	// Ident ist Hexadezimal
      				yypvt[-2].numtok.intnum = MakeHex (yypvt[-2].numtok.intnum);
      
	l_Ident:
      			if (fFirstIdent) fFirstIdent = FALSE;
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0) 
      				end_previous_object ();
      
		/* Plausibilitaetskontrolle */
      			if ((yypvt[-4].numtok.intnum == O_PUNKT && yypvt[-1].numtok.intnum != 1) ||
      				(yypvt[-4].numtok.intnum == O_LINIE && yypvt[-1].numtok.intnum < 2)) 
      			{
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-3].numtok.intnum;            /* lfde Nummer in ASCII-Datei */
      //			id = yypvt[-2].numtok.intnum;         /* Identifikator */
      			ultoa (yypvt[-2].numtok.intnum, cbOKS, d_flag ? 10 : 16);
      			sta[1] = yypvt[-4].numtok.intnum;     /* Objekttyp */
      			koord_paare = yypvt[-1].numtok.intnum; /* Stuetzpunktanzahl */
      		} break;
      case 40:{
      			if (d_flag && !fFirstIdent) {
      				fprintf (stderr, "\nInkonsistente Identifikator-Zahlenbasis ('-x' verwenden).\n");
      				YYABORT;
      			}
      			if (d_flag && fFirstIdent) 
      				d_flag = TRUE;
      			goto l_Ident;
      		} break;
      case 41:{
      			if (!d_flag) 	// Ident ist Hexadezimal
      				yypvt[-9].numtok.intnum = MakeHex (yypvt[-9].numtok.intnum);
      
	l_Ident_typ2:
      			if (fFirstIdent) fFirstIdent = FALSE;
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0) 
      				end_previous_object ();
      
		/* Plausibilitaetskontrolle */
      			if ((yypvt[-11].numtok.intnum == O_PUNKT && yypvt[-8].numtok.intnum != 1) ||
      				(yypvt[-11].numtok.intnum == O_LINIE && yypvt[-8].numtok.intnum < 2)) 
      			{
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-10].numtok.intnum;            /* lfde Nummer in ASCII-Datei */
      //			id = yypvt[-9].numtok.intnum;         /* Identifikator */
      			ultoa (yypvt[-9].numtok.intnum, cbOKS, d_flag ? 10 : 16);
      			sta[1] = yypvt[-11].numtok.intnum;     /* Objekttyp */
      			koord_paare = yypvt[-8].numtok.intnum; /* Stuetzpunktanzahl */
      		} break;
      case 42:{
      			if (d_flag && !fFirstIdent) {
      				fprintf (stderr, "\nInkonsistente Identifikator-Zahlenbasis ('-x' verwenden).\n");
      				YYABORT;
      			}
      			if (d_flag && fFirstIdent) 
      				d_flag = TRUE;
      			goto l_Ident_typ2;
      		} break;
      case 43:{
      		// Ident ist Hexadezimal
      			if (fFirstIdent) fFirstIdent = FALSE;
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0) 
      				end_previous_object ();
      
		/* Plausibilitaetskontrolle */
      			if ((yypvt[-4].numtok.intnum == O_PUNKT && yypvt[-1].numtok.intnum != 1) ||
      				(yypvt[-4].numtok.intnum == O_LINIE && yypvt[-1].numtok.intnum < 2)) 
      			{
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      
		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-3].numtok.intnum;            /* lfde Nummer in ASCII-Datei */
      //			id = lIdent;					/* Identifikator */
      			strcpy (cbOKS, yypvt[-2].strtok.string);
      			sta[1] = yypvt[-4].numtok.intnum;				/* Objekttyp */
      			koord_paare = yypvt[-1].numtok.intnum;		/* Stuetzpunktanzahl */
      		} break;
      case 44:{
      			if (fFirstIdent) fFirstIdent = FALSE;
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0) 
      				end_previous_object ();
      
		/* Plausibilitaetskontrolle */
      			if ((yypvt[-5].numtok.intnum == O_PUNKT && yypvt[-2].numtok.intnum != 1) ||
      				(yypvt[-5].numtok.intnum == O_LINIE && yypvt[-2].numtok.intnum < 2)) 
      			{
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      
		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-4].numtok.intnum;            /* lfde Nummer in ASCII-Datei */
      //			id = lIdent;					/* Identifikator */
      			strcpy (cbOKS, yypvt[-3].strtok.string);
      			sta[1] = yypvt[-5].numtok.intnum;				/* Objekttyp */
      			koord_paare = yypvt[-2].numtok.intnum;		/* Stuetzpunktanzahl */
      		} break;
      case 45:{
      		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0) 
      				end_previous_object ();
      
		/* Fehler behandeln */
      			yyerrok;
      			switch ((int)yypvt[-2].numtok.intnum) {
      			case O_PUNKT:
      				error_skip_lines ("PLFB", EPKTID); break;
      			case O_LINIE:
      				error_skip_lines ("PLFB", ELINID); break;
      			case O_FLAECHE:
      				error_skip_lines ("PLFB", EFLID); break;
      			}
      		} break;
      case 46:{
      			if (!d_flag) 	// Ident ist Hexadezimal
      				yypvt[-1].numtok.intnum = MakeHex (yypvt[-1].numtok.intnum);
      
	l_KOIdent:
      			if (fFirstIdent) fFirstIdent = FALSE;
      
		// KomplexObjekt
      		/* Vorhergehendes Objekt bearbeiten */
      			if (satz_nr > 0) end_previous_object ();
      			++objekt_nr;
      
		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-2].numtok.intnum;	/* lfde Nummer in ASCII-Datei */
      //			id = yypvt[-1].numtok.intnum;		/* Identifikator */
      			ultoa (yypvt[-1].numtok.intnum, cbOKS, d_flag ? 10 : 16);
      			sta[0] = K_OBJEKT;	
      			sta[1] = 0;		/* Objekttyp */
      			koord_paare = 0;	/* Stuetzpunktanzahl */
      		} break;
      case 47:{
      			if (d_flag && !fFirstIdent) {
      				fprintf (stderr, "\nInkonsistente Identifikator-Zahlenbasis ('-x' verwenden).\n");
      				YYABORT;
      			}
      			if (d_flag && fFirstIdent) 
      				d_flag = TRUE;
      			goto l_KOIdent;
      		} break;
      case 48:{
      		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0) end_previous_object ();
      			yyerrok;
      			error_skip_lines ("PLFB", EFKID);
      		} break;
      case 49:{       yyval.numtok.intnum = O_PUNKT;    } break;
      case 50:{       yyval.numtok.intnum = O_LINIE;    } break;
      case 51:{       yyval.numtok.intnum = O_FLAECHE;  } break;
      case 52:{	yyval.numtok.intnum = O_TEXTOBJEKT;	} break;
      case 53:{
      		short Len = strlen (yypvt[-1].strtok.string);
      		long wf = 0;
      
			curr_mi = &curr_mi[mi_count];
      			mi_count = 3;
      			curr_mi_text = (char *)&curr_mi[3];
      
			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
      			curr_mi[1] = M_TEXT;
      
		// wie normalen Merkmalswert behandeln
      			strncpy (curr_mi_text, yypvt[-1].strtok.string, 78);
      			curr_mi_text[min(78, Len)] = '\0';
      
			curr_mi_text += Len;
      			wf = (Len + (sizeof(long)-1))/sizeof(long);
      
			mi[1] += wf + 3;
      			curr_mi[2] = wf;		// Wiederholungsfaktor
      			mi_count += wf;
      		} break;
      case 54:{
      			curr_mi = &curr_mi[mi_count];
      
			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
      			curr_mi[1] = M_TEXT;
      			curr_mi[2] = -1;		// WF
      			curr_mi[3] = yypvt[-1].numtok.intnum;		// MCode
      
			mi[1]++;
      			mi_count += 4;
      
		// Status korrigieren
      			sta[1] = O_TEXTOBJIND;
      		} break;
      case 56:{
      			curr_mi = &curr_mi[mi_count];
      			curr_mi[1] = M_INTEGER;         /* Integermerkmale */
      			mi_werte = yypvt[-3].numtok.intnum;   /* Anzahl der I*4 - Werte */
      		merkmal: ;
      			curr_mi[0] = yypvt[-4].numtok.intnum; /* Merkmalskode */
      			curr_mi[2] = 0;         /* Wiederholungsfaktor loeschen */
      			mi[1] += 3;
      			mi_count = 3;
      			mi_length = yypvt[-1].numtok.intnum;  /* Laenge der Werte */
      		} break;
      case 57:{
      			curr_mi = &curr_mi[mi_count];
      			curr_mi[1] = M_DOUBLE;          /* Floatpointmerkmale */
      			mi_werte = yypvt[-3].numtok.intnum; //*(sizeof(double)/sizeof(long));
      			goto merkmal;   /* weiter wie fuer M_INTEGER */
      		} break;
      case 58:{
      			curr_mi = &curr_mi[mi_count];
      			curr_mi[1] = M_TEXT;            /* Textmerkmale */
      			curr_mi_text = (char *)&curr_mi[3];
      			mi_werte = (yypvt[-1].numtok.intnum + (sizeof(long)-1))/sizeof(long);
      			goto merkmal;   /* weiter wie fuer M_INTEGER */
      		} break;
      case 62:{
      		/* Plausibilitaetskontrolle */
      			if (mi_count -3 >= mi_werte) {
      			/* Merkmal ueberspringen */
      				error_skip_lines ("PLFMRG", EMCNT);
      				break;
      			}
      			curr_mi[mi_count++] = yypvt[-0].numtok.intnum;
      			mi[1]++;
      			curr_mi[2]++;
      		} break;
      case 66:{
      		register int item_size = sizeof(double)/sizeof(long);
      
		/* Plausibilitaetskontrolle */
      			if ((mi_count -3)/(sizeof(double)/sizeof(long)) >= (size_t)mi_werte) {
      			/* Merkmal ueberspringen */
      				error_skip_lines ("PLFMRG", EMCNT);
      				break;
      			}
      			*((double *)(&curr_mi[mi_count])) = yypvt[-0].flttok.fltnum;
      			mi[1] += item_size;
      			curr_mi[2]++;           // += item_size;
      			mi_count += item_size;
      		} break;
      case 67:{
      		register int length = 0;
      
			/* Plausibilitaetskontrolle */
      			if (mi_length <= 0) {
      			/* Zu viele Merkmalssaetze */
      				error_skip_lines ("PLFRMG", EMCNT);
      				break;
      			}
      
			strncpy (curr_mi_text, yypvt[-1].strtok.string, 78);
      			curr_mi_text[min(78, mi_length)] = '\0';
      			length += strlen (curr_mi_text);
      			mi_length -= length;
      			curr_mi_text += length;
      			if (mi_length <= 0) {
      			/* Merkmalswerte vollstaendig gelesen */
      			register int wf = 0;    /* Laenge des Textes in I*4 */
      
				length = curr_mi_text - (char *)&curr_mi[3];
      				wf = (length + sizeof(long)-1)/sizeof(long);
      				mi[1] += wf;
      				curr_mi[2] += wf;
      				mi_count += wf;
      			}
      		} break;
      case 70:{
      			yyerrok;
      			db_error (EBREL, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 71:{	yyval.numtok.intnum = GREL;	} break;
      case 72:{	yyval.numtok.intnum = OREL;	} break;
      case 76:{       strcpy (comment, yypvt[-1].strtok.string);    } break;
      case 79:{
      		/* Plausibilitaetskontrolle */
      			if (lgi +1 >= koord_paare) {
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      		/* Koordinatenpaar abspeichern, Zaehler weitersetzen */
      			{
      				gxi[++lgi] = yypvt[-1].flttok.fltnum * dKoeff;
      				gyi[lgi] = yypvt[-0].flttok.fltnum * dKoeff;
      			}
      		} break;
      case 80:{       if (satz_nr > 0) end_previous_object ();        } break;    }
    goto enstack;
}
