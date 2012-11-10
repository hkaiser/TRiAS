#if defined(__cplusplus) 
extern "C" { 
#endif
# include <stdio.h>
#if defined(__cplusplus) 
} 
#endif
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# undef LEXDEBUG 
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

static char SccsId[] = "uve FEZ: %W%  %E%";

#if defined(__cplusplus)
extern "C" {
#endif
	#include <windows.h>

	#include <stdlib.h>
	#include <ctype.h>
	#include <string.h>

	#include "report.h"
	#include "winio.h"
#ifdef unix
	#include "y.tab.h"
#endif
#ifdef msdos
	#include "ytab.h"
#endif
#if defined(__cplusplus)
}
#endif

// Neudefinition der LEX - I/O Routinen fr WINIO
# undef output
# undef input
# define output(c) fputchar(c)
# define input() ((yytchar=yysptr>yysbuf?U(*--yysptr): \
		  (ActChar<ScriptEnd?*ActChar++:0))==10? \
		  (yylineno++,yytchar):yytchar)

// Globaler Buffer fr Script -------------------------------------------------
char *Script = NULL;
char *ScriptEnd;		// ScriptEnde
char *ActChar;			// n„chstes einzulesendes Zeichen

struct keyentry {               /* Tabelleneintrag fuer reservierte Worte */
        int  lx;
        char *id;
};

/* reservierte Worte, die vom Scanner identifiziert werden */
struct keyentry keywords[] = {
        {       REPORT, "report"        },
        {       DECLARATION, "declaration"      },
        {       CALL, "call"            },
        {       PROC, "proc"            },
        {       HEAD, "head"            },
        {       TAIL, "foot"            },
        {       TUPLES, "tuples"        },
        {       LINES, "lines"          },
        {       COLUMNS, "columns"      },
        {       ALL, "all"              },
        {       FROM, "from"            },
        {       TO, "to"                },
        {       BIG, "big"              },
        {       PAGE, "page"            },
        {       TUPLE, "tuple"          },
        {       FOR_ONE, "for_one"      },
        {       FOR_ALL, "for_all"      },
        {       FORMAT, "format"        },
        {       VARI, "var_i"           },
        {       VARF, "var_f"           },
        {       VARS, "var_s"           },
        {       NEW, "new"              },
        {       LINE, "line"            },
        {       COL, "col"              },
        {       SPACE, "space"          },
        {       BATCH, "batch"          },
        {       LASTI, "last_i"         },
        {       VALUEI, "value_i"       },
        {       NEXTI, "next_i"         },
        {       LASTF, "last_f"         },
        {       VALUEF, "value_f"       },
        {       NEXTF, "next_f"         },
        {       LASTS, "last_s"         },
        {       VALUES, "value_s"       },
        {       NEXTS, "next_s"         },
        {       REAL, "real"            },
        {       TERMINAL, "terminal"    },
        {       DATE, "date"            },
        {       TIME, "time"            },
        {       PRINT, "print"          },
        {       LINEBEGIN, "linebegin"  },
        {       LINEEND, "lineend"      },
        {       IF, "if"                },
        {       ELSE, "else"            },
        {       0, ""                   },
};

int  tot_errs = 0;       /* total errors encountered */

long act_seek;

# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
seek();
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
                {
                        /* Integer */
			yylval.numtok.value = atol (yytext);
//                      sscanf (yytext, "%d", &yylval.numtok.value);
                        yylval.numtok.numline = yylineno;
                        return (NUMBER);
                        }
break;
case 2:
   case 3:
   case 4:
             {
                        /* Real Number */
			yylval.realtok.value = atof (yytext);
//                      sscanf (yytext, "%f", &yylval.realtok.value);
                        yylval.realtok.numline = yylineno;
                        return (REAL_NUMBER);
                        }
break;
case 5:
                   case 6:
                   {
                        /* String */
                        register unsigned char scope_char = *yytext;
                        register char *cptr;

                        strncpy (yylval.strtok.str, yytext+1, MAXSTRING);
                        if ((cptr = strchr (yylval.strtok.str, scope_char)) != NULL)
                                *cptr = '\0';
                        yylval.strtok.strline = yylineno;
                        return (STRING);
                        }
break;
case 7:
                   {
                        /* Identifier, Keyword etc. */
                        register int i;

                        strncpy (yylval.strtok.str, yytext, NAMELEN);
                        /* ist ID ein reserviertes Wort ? */
                        for (i = 0; keywords[i].lx ; i++) {
                                if (!strcmp (keywords[i].id, yylval.strtok.str))
                                        break;
                        }
                        if (keywords[i].lx) {   /* ID ist Schluesselwort */
                                yylval.strtok.strline = yylineno;
                                return (keywords[i].lx);
                        }
                        /* ist ID eine Systemvariable ? */
                        for (i = 0; system_var[i].var_name; ++i) {
                                if (!strcmp (system_var[i].var_name,
                                                        yylval.strtok.str))
                                        break;
                        }
                        if (system_var[i].var_name) {   /* ID ist Systemvar */
                                yylval.numtok.value = system_var[i].var_wert;
                                yylval.numtok.index = i;
                                yylval.numtok.numline = yylineno;
                                return (SYSTEM_VAR);
                        }
                        /* ist ID Systemkonstante ? */
                        for (i = 0; system_const[i].const_name; ++i) {
                                if (!strcmp (system_const[i].const_name,
                                                        yylval.strtok.str))
                                        break;
                        }
                        if (system_const[i].const_name) {       /* ID ist Sys.const */
                                yylval.numtok.value =
                                                (*system_const[i].const_wert)();
                                yylval.numtok.index = i;
                                yylval.numtok.numline = yylineno;
                                return (SYSTEM_CONST);
                        }
                        else {
                        /* Ansonsten ist ID nutzerdefinierter Name */
                                yylval.strtok.strline = yylineno;
                                return (IDENT);
                        }
                        }
break;
case 8:
                     {
                        /* Neue Zeilennummer (Zeile ignorieren) */
                        register int n = 0;
                        register int ch;

	                        while ((ch = input ()) == ' ')
        	                        ;
                	        if (isdigit(ch)) {
                        	        n = 0;
                                	while (isdigit(ch)) {
                                        	n= 10*n + ch - '0';
	                                        ch = input ();
        	                        }
                	                yylineno = n - 1;
                        	}
	                        while ((ch = input ()) != '\n')
        	                        ;
                        }
break;
case 9:
                 return (OROR);
break;
case 10:
                 return (ANDAND);
break;
case 11:
                 return (NE);
break;
case 12:
                 return (LE);
break;
case 13:
                 return (GE);
break;
case 14:
                 return (EQ);
break;
case 15:
                    return (LT);
break;
case 16:
                    return (GT);
break;
case 17:
                    return (UNOT);
break;
case 18:
                    return (EQU);
break;
case 19:
                   comment ("*/");
break;
case 20:
		comment ("\n");
break;
case 21:
               ;
break;
case 22:
                      return (*yytext);
break;
case -1:
break;
default:
r_abort("bad switch yylook");
} return(0); }
/* end of yylex */

/* Feststellen der aktuellen Position */

long prev_seek;  /* previous seek */

long yytell (register int which) {

        switch (which) {
        case 1:         return (act_seek);
        case 0:         return (prev_seek);
        case -1:        return ((ActChar - Script) - (yysptr-yysbuf));
        }
}

static void seek (void)
{
        prev_seek = act_seek;
        act_seek = (ActChar - Script) - (yysptr-yysbuf);
}

/* Neu Positionieren */
void yyseek (long new_seek) {

	ActChar = Script + new_seek;
}


/* Parser Syntaxfehler */
void yyerror (char *s) {

        r_error (s, yylineno);
}


/* Formatdefinitionsfehler */
void r_error (char *s, int ln) {
char ErrOut[256];

        ++tot_errs;
	wsprintf (ErrOut, "Zeile %d: %s", ln, s);
	MessageBox (NULL, ErrOut, "Report -- Fehler", MB_OK);
}


/* Schwerwiegender Formatdefinitionsfehler: Abbruch */
void r_abort (char *s) {
char ErrOut[256];

	wsprintf (ErrOut, "Zeile %d: Abbruch - %s", yylineno, s);
	MessageBox (NULL, ErrOut, "Report -- Abbruch", MB_OK);

/* Abbrechen des Compilerlaufes */
}

// Kommentar berlesen 
void comment (char *mat) {

	register int c = 1;
	register char *cp = mat;
	int lno = yylineno;

	while (*cp && c > 0) {
		if ((c = input ()) != *cp++)
			cp = mat;
	}
	if (c == 0) {
		yylineno = lno;
		r_abort ("EOF im Kommentar gelesen");
	}
}
int yyvstop[] ={
0,
/* actions for state 0 */
21,
0,
/* actions for state 1 */
21,
0,
/* actions for state 2 */
22,
0,
/* actions for state 3 */
21,
22,
0,
/* actions for state 4 */
21,
0,
/* actions for state 5 */
17,
22,
0,
/* actions for state 6 */
22,
0,
/* actions for state 7 */
22,
0,
/* actions for state 8 */
22,
0,
/* actions for state 9 */
22,
0,
/* actions for state 10 */
22,
0,
/* actions for state 11 */
22,
0,
/* actions for state 12 */
1,
22,
0,
/* actions for state 13 */
15,
22,
0,
/* actions for state 14 */
18,
22,
0,
/* actions for state 15 */
16,
22,
0,
/* actions for state 16 */
7,
22,
0,
/* actions for state 17 */
22,
0,
/* actions for state 18 */
8,
22,
0,
/* actions for state 19 */
11,
0,
/* actions for state 21 */
5,
0,
/* actions for state 22 */
10,
0,
/* actions for state 24 */
6,
0,
/* actions for state 26 */
1,
0,
/* actions for state 27 */
3,
0,
/* actions for state 28 */
19,
0,
/* actions for state 29 */
20,
0,
/* actions for state 30 */
2,
0,
/* actions for state 32 */
12,
0,
/* actions for state 33 */
14,
0,
/* actions for state 34 */
13,
0,
/* actions for state 35 */
7,
0,
/* actions for state 36 */
9,
0,
/* actions for state 38 */
2,
3,
0,
/* actions for state 41 */
4,
0,
/* actions for state 43 */
3,
0,
/* actions for state 46 */
2,
0,
/* actions for state 48 */
2,
3,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
7,21,	0,0,	1,4,	1,5,	
21,0,	4,5,	4,5,	24,0,	
7,21,	7,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,6,	1,7,	
4,5,	0,0,	0,0,	1,8,	
1,9,	7,22,	8,23,	0,0,	
1,10,	0,0,	7,21,	1,11,	
1,12,	1,13,	7,21,	2,6,	
12,29,	2,19,	0,0,	7,21,	
2,8,	12,30,	0,0,	0,0,	
0,0,	1,14,	1,15,	1,16,	
2,11,	2,12,	1,17,	6,20,	
9,24,	1,17,	14,33,	15,34,	
7,21,	13,31,	16,35,	7,21,	
9,24,	9,0,	2,14,	2,15,	
2,16,	10,26,	27,31,	10,27,	
10,27,	10,27,	10,27,	10,27,	
10,27,	10,27,	10,27,	10,27,	
10,27,	0,0,	0,0,	13,32,	
13,32,	28,38,	28,38,	0,0,	
0,0,	9,24,	0,0,	0,0,	
27,32,	27,32,	9,25,	39,45,	
39,45,	0,0,	9,24,	0,0,	
0,0,	0,0,	0,0,	9,24,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	1,18,	18,37,	13,32,	
13,32,	28,38,	28,38,	0,0,	
9,24,	0,0,	0,0,	9,24,	
27,32,	27,32,	0,0,	39,45,	
39,45,	0,0,	2,18,	11,28,	
11,28,	11,28,	11,28,	11,28,	
11,28,	11,28,	11,28,	11,28,	
11,28,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
0,0,	0,0,	0,0,	0,0,	
17,36,	0,0,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
31,39,	31,39,	31,39,	31,39,	
31,39,	31,39,	31,39,	31,39,	
31,39,	31,39,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	32,41,	0,0,	32,41,	
31,40,	31,40,	32,42,	32,42,	
32,42,	32,42,	32,42,	32,42,	
32,42,	32,42,	32,42,	32,42,	
38,43,	0,0,	38,43,	0,0,	
0,0,	38,44,	38,44,	38,44,	
38,44,	38,44,	38,44,	38,44,	
38,44,	38,44,	38,44,	0,0,	
0,0,	40,46,	0,0,	40,46,	
31,40,	31,40,	40,47,	40,47,	
40,47,	40,47,	40,47,	40,47,	
40,47,	40,47,	40,47,	40,47,	
41,42,	41,42,	41,42,	41,42,	
41,42,	41,42,	41,42,	41,42,	
41,42,	41,42,	43,44,	43,44,	
43,44,	43,44,	43,44,	43,44,	
43,44,	43,44,	43,44,	43,44,	
45,48,	0,0,	45,48,	0,0,	
0,0,	45,49,	45,49,	45,49,	
45,49,	45,49,	45,49,	45,49,	
45,49,	45,49,	45,49,	46,47,	
46,47,	46,47,	46,47,	46,47,	
46,47,	46,47,	46,47,	46,47,	
46,47,	48,49,	48,49,	48,49,	
48,49,	48,49,	48,49,	48,49,	
48,49,	48,49,	48,49,	0,0,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+-1,	0,		yyvstop+1,		/* state 0 */
yycrank+-18,	yysvec+1,	yyvstop+3,		/* state 1 */
yycrank+0,	0,		yyvstop+5,		/* state 2 */
yycrank+4,	0,		yyvstop+7,		/* state 3 */
yycrank+0,	yysvec+4,	yyvstop+10,		/* state 4 */
yycrank+6,	0,		yyvstop+12,		/* state 5 */
yycrank+-7,	0,		yyvstop+15,		/* state 6 */
yycrank+4,	0,		yyvstop+17,		/* state 7 */
yycrank+-67,	0,		yyvstop+19,		/* state 8 */
yycrank+35,	0,		yyvstop+21,		/* state 9 */
yycrank+95,	0,		yyvstop+23,		/* state 10 */
yycrank+10,	0,		yyvstop+25,		/* state 11 */
yycrank+27,	yysvec+10,	yyvstop+27,		/* state 12 */
yycrank+9,	0,		yyvstop+30,		/* state 13 */
yycrank+10,	0,		yyvstop+33,		/* state 14 */
yycrank+13,	0,		yyvstop+36,		/* state 15 */
yycrank+105,	0,		yyvstop+39,		/* state 16 */
yycrank+2,	0,		yyvstop+42,		/* state 17 */
yycrank+0,	0,		yyvstop+44,		/* state 18 */
yycrank+0,	0,		yyvstop+47,		/* state 19 */
yycrank+-2,	yysvec+7,	0,			/* state 20 */
yycrank+0,	0,		yyvstop+49,		/* state 21 */
yycrank+0,	0,		yyvstop+51,		/* state 22 */
yycrank+-5,	yysvec+9,	0,			/* state 23 */
yycrank+0,	0,		yyvstop+53,		/* state 24 */
yycrank+0,	yysvec+11,	0,			/* state 25 */
yycrank+36,	yysvec+10,	yyvstop+55,		/* state 26 */
yycrank+29,	yysvec+11,	yyvstop+57,		/* state 27 */
yycrank+0,	0,		yyvstop+59,		/* state 28 */
yycrank+0,	0,		yyvstop+61,		/* state 29 */
yycrank+180,	0,		yyvstop+63,		/* state 30 */
yycrank+202,	0,		0,			/* state 31 */
yycrank+0,	0,		yyvstop+65,		/* state 32 */
yycrank+0,	0,		yyvstop+67,		/* state 33 */
yycrank+0,	0,		yyvstop+69,		/* state 34 */
yycrank+0,	yysvec+17,	yyvstop+71,		/* state 35 */
yycrank+0,	0,		yyvstop+73,		/* state 36 */
yycrank+217,	0,		0,			/* state 37 */
yycrank+39,	yysvec+31,	yyvstop+75,		/* state 38 */
yycrank+234,	0,		0,			/* state 39 */
yycrank+244,	0,		0,			/* state 40 */
yycrank+0,	yysvec+41,	yyvstop+78,		/* state 41 */
yycrank+254,	0,		0,			/* state 42 */
yycrank+0,	yysvec+43,	yyvstop+80,		/* state 43 */
yycrank+269,	0,		0,			/* state 44 */
yycrank+279,	0,		0,			/* state 45 */
yycrank+0,	yysvec+46,	yyvstop+82,		/* state 46 */
yycrank+289,	0,		0,			/* state 47 */
yycrank+0,	yysvec+48,	yyvstop+84,		/* state 48 */
0,	0,	0};
struct yywork *yytop = yycrank+346;
struct yysvf *yybgin = yysvec+1;
char yymatch[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,'"' ,01  ,01  ,01  ,01  ,047 ,
01  ,01  ,01  ,'+' ,01  ,'+' ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'D' ,'D' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,'A' ,
01  ,'A' ,'A' ,'A' ,'D' ,'D' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] ={
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
#undef LEXDEBUG
int yylineno =1;
#define YYU(x) x
#define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
int yylook(void){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych;
	struct yywork *yyr;
#if defined(LEXDEBUG)
	int debug;
#endif
	char *yylastch;
	/* start off machines */
#if defined(LEXDEBUG)
	debug = 0;
#endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
#if defined(LEXDEBUG)
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
#endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
#if defined(LEXDEBUG)
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
#endif
			yyr = yyt;
			if (yyt > yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
#if defined(YYOPTIM)
			else if(yyt < yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
#if defined(LEXDEBUG)
				if(debug)fprintf(yyout,"compressed state\n");
#endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
#if defined(LEXDEBUG)
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
#endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
#if defined(LEXDEBUG)
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
#endif
				goto tryagain;
				}
#endif
			else
				{unput(*--yylastch);break;}
		contin:
#if defined(LEXDEBUG)
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
#endif
			;
			}
#if defined(LEXDEBUG)
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
#endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
#if defined(LEXDEBUG)
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
#endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
#if defined(LEXDEBUG)
		if(debug)putchar('\n');
#endif
		}
	}
int yyback (int *p, int m) {
	if (p==0) 
		return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
int yyinput(void){
	return(input());
}
void yyoutput(int c){
	output(c);
}
void yyunput(int c) {
	unput(c);
}
int yywrap(void){
	return(1);
}
