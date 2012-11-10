# define U(x) x
# define NLSTATE yy2previous=YYNEWLINE
# define BEGIN yy2bgin = yy2svec + 1 +
# define INITIAL 0
# define YYLERR yy2svec
# define YYSTATE (yy2estate-yy2svec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yy2out)
# define input() (((yy2tchar=yy2sptr>yy2sbuf?U(*--yy2sptr):getc(yy2in))==10?(yy2lineno++,yy2tchar):yy2tchar)==EOF?0:yy2tchar)
# define unput(c) {yy2tchar= (c);if(yy2tchar=='\n')yy2lineno--;*yy2sptr++=yy2tchar;}
# define yy2more() (yy2morfg=1)
# define ECHO yy2error( "%s",yy2text)
# define REJECT { nstr = yy2reject(); goto yy2fussy;}
int yy2leng; extern char yy2text[];
int yy2morfg;
extern char *yy2sptr, yy2sbuf[];
int yy2tchar;
#if defined(__cplusplus)
extern "C" {
#endif
	#include <stdio.h>
#if defined(__cplusplus)
#if defined(_MSC_VER)
#pragma warning (disable:4102)
#endif
}
#endif
FILE *yy2in = NULL;
extern int yy2lineno;
struct yy2svf { 
	struct yy2work *yy2stoff;
	struct yy2svf *yy2other;
	int *yy2stops;};
struct yy2svf *yy2estate;
extern struct yy2svf yy2svec[], *yy2bgin;

extern "C" {
	#include <windows.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>

	#include "yvisidl.h"
}

#include <commonvu.hxx>

#include <errcodes.hxx>
#include "yy2stype.hxx"

struct keyentry {               /* Tabelleneintrag fuer reservierte Worte */
	int  lx;
	char *id;
};

extern YYSTYPE (*pyy2lval);
void yy2error (ErrCode, ...);
void yy2error (const char *, ...);

/* reservierte Worte, die vom Scanner identifiziert werden */
struct keyentry keywords[] = 
{
	{	T_VIEW, "VIEW"				},
	{	T_DEFAULT, "DEFAULT"		},
	{	T_PRIORITY, "PRIORITY"		},
	{	T_TYPE, "TYPE"				},
	{	T_MAINCOLOR, "MAINCOLOR"	},
	{	T_SIZE, "SIZE"				},
	{	T_WIDTH, "WIDTH"			},
	{	T_FILLCOLOR, "FILLCOLOR"	},
	{	T_IDENT, "IDENT"			},
	{	T_PUNKT, "COORDPAIR"		},
	{	T_LINIE, "LINE"				},
	{	T_FLAECHE, "AREA"			},
	{	T_TEXT, "X"					},
	{	T_TTYP, "Y"					},
	{	T_TROT, "ROTATION"			},
	{	T_EQUAL, "EQUAL"			},
	{	T_MCODE, "GENERALINFO"		},
	{	T_DESC, "BESCHREIBUNG"		},
	{	T_MAINCOLORC, "MSBH"		},
	{	T_FILLCOLORC, "FSBH"		},
	{	T_TVCS, "Z"					},
	{	T_TLEGINFO, "LG"			},
	{	T_TLEGHEAD, "LH"			},		/* Zwischenüberschrift in Legende */
	{	T_TAGGED, "KENNZEICHEN"		},
	{	T_OKS, "OKS"				},
	{	T_STARTVIEW, "SVIEW"		},
	{	T_UPPERSCALE, "USCALE"		},
	{	T_LOWERSCALE, "LSCALE"		},
	{	T_LOCATABLE, "LOCATABLE"	},
	{	T_VISIBLE, "VISIBLE"		},
	{	T_GEOMETRY, "GEOMETRY"		},
//	{	T_OBJPROPTOSHOW, "OBJPROP"	},
	{	0, NULL						},
};

#undef YYLMAX		// max. Stringlänge
#define YYLMAX	2048

#undef output
#define output(x)

#define RBRACE	'}'

# define TextTyp 2
# define LegInfo 4
# define LegInfoString 6
# define YYNEWLINE 10
yy2lex(){
int nstr; extern int yy2previous;
while((nstr = yy2look()) >= 0)
yy2fussy: switch(nstr){
case 0:
if(yy2wrap()) return(0); break;
case 1:
{
				BEGIN LegInfoString;
				return *yy2text;
			}
break;
case 2:
{     
			/* LegendenInfo wird ohne Prüfung als String gelesen */
			char *cptr = new char [YYLMAX];
			char *pBuff = cptr;
			char inchar;
			
				if (cptr == NULL)
					yy2error (EC_NOMEMORY);
				else {
					while ((inchar = input()) != RBRACE)
						*cptr++ = inchar;
					*cptr = '\0';
				}

				unput (RBRACE);	
				BEGIN 0;	/* wieder normal */

				LEXSTACK (pBuff, YYString, yy2lineno);
				return T_STRING;
			}
break;
case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		{
				return *yy2text;
			}
break;
case 12:
	{	/* Kommentar */
			register int ch;

				for (;;) {
					while ((ch = input()) != '*') {
//						if (ch == '\n')		// Zeilen werden bereits in 'input()' gezählt
//							++yy2lineno;
					}
					if ( (ch = input()) == '/')
						break;
					else
						unput(ch);
				}
			}
break;
case 13:
	{	/* Kommentar */
			register int ch;

				while ((ch = input()) != '\n')
					;
				unput(ch);
			}
break;
case 14:
		case 15:
		{
			int scope_char = yy2text[0];
			int inchar;
			char *cptr = new char [YYLMAX];
			char *pBuff = cptr;
			
				if (cptr == NULL)
					yy2error (EC_NOMEMORY);
				else {
					inchar = input();
					while (inchar != 0 && inchar != scope_char) {
						if (inchar == '\\') {
							inchar = input();
							if (0 == inchar)
								break;
						}
						*cptr++ = inchar;
						inchar = input();
					}
					*cptr = '\0';
				}

				BEGIN 0;

				OemToAnsi (pBuff, pBuff);
				LEXSTACK (pBuff, YYString, yy2lineno);
				return T_STRING;
			}
break;
case 16:
	case 17:
	{		/* HexZahl */
			long *pLNum = new long (strtoul (yy2text, NULL, 16));

				BEGIN 0;
				LEXSTACK (pLNum, YYLong, yy2lineno);
				return T_NUMBER;
			}
break;
case 18:
	{
			long *pLNum = new long (strtoul (yy2text, NULL, 16));

				BEGIN 0;
				LEXSTACK (pLNum, YYLong, yy2lineno);

				return (T_HEXNUMBER);
			}
break;
case 19:
	;
break;
case 20:
	{	/* Keyword */
			short iLen = strlen (yy2text);
			char *pIdent = new char [iLen+1];

				if (pIdent != NULL) {
					strcpy (pIdent, yy2text);
					strupr (pIdent);
				}
				
			/* ist ID ein reserviertes Wort ? */
				for (short i = 0; keywords[i].lx ; i++) {
					if (!strncmp (keywords[i].id, pIdent, iLen))
						break;
				}
				if (keywords[i].lx) {   /* ID ist Schluesselwort */
				// Besonderheit fuer T_TTYP
					if (keywords[i].lx == T_TTYP)
						BEGIN TextTyp;

				// Besonderheit fuer T_TLEGINFO
					if (keywords[i].lx == T_TLEGINFO)
						BEGIN LegInfo;

					LEXSTACK (pIdent, YYString, yy2lineno);
					return (keywords[i].lx);
				} 
				else {          /* kein Keyword --> Fehler */
					if (pIdent) delete pIdent;
					LEXSTACK (NULL, YYLong, yy2lineno);
					return (T_IDENT);
				}
			}
break;
case 21:
	{       /* Integerzahl */
			long *pLNum = new long (atol (yy2text));

				LEXSTACK (pLNum, YYLong, yy2lineno);
				return (T_NUMBER);
			}
break;
case 22:
	{       /* Integerzahl */
			long *pLNum = new long (strtoul (yy2text, NULL, 16));

				LEXSTACK (pLNum, YYLong, yy2lineno);
				return (T_HEXNUMBER);
			}
break;
case 23:
		;
break;
case -1:
break;
default:
yy2error("bad switch yy2look %d",nstr);
} return(0); }
/* end of yy2lex */

int yy2vstop[] ={
0,
/* actions for state 0 */
19,
0,
/* actions for state 1 */
19,
0,
/* actions for state 2 */
19,
0,
/* actions for state 3 */
19,
0,
/* actions for state 4 */
19,
0,
/* actions for state 5 */
19,
0,
/* actions for state 6 */
19,
0,
/* actions for state 7 */
19,
0,
/* actions for state 8 */
23,
0,
/* actions for state 9 */
19,
23,
0,
/* actions for state 10 */
14,
23,
0,
/* actions for state 11 */
10,
23,
0,
/* actions for state 12 */
15,
23,
0,
/* actions for state 13 */
6,
23,
0,
/* actions for state 14 */
7,
23,
0,
/* actions for state 15 */
23,
0,
/* actions for state 16 */
8,
23,
0,
/* actions for state 17 */
23,
0,
/* actions for state 18 */
21,
22,
23,
0,
/* actions for state 19 */
21,
22,
23,
0,
/* actions for state 20 */
11,
23,
0,
/* actions for state 21 */
9,
23,
0,
/* actions for state 22 */
5,
23,
0,
/* actions for state 23 */
20,
22,
23,
0,
/* actions for state 24 */
20,
23,
0,
/* actions for state 25 */
3,
23,
0,
/* actions for state 26 */
4,
23,
0,
/* actions for state 27 */
21,
22,
23,
0,
/* actions for state 28 */
1,
3,
23,
0,
/* actions for state 29 */
2,
23,
0,
/* actions for state 30 */
2,
19,
23,
0,
/* actions for state 31 */
2,
14,
23,
0,
/* actions for state 32 */
2,
10,
23,
0,
/* actions for state 33 */
2,
15,
23,
0,
/* actions for state 34 */
2,
6,
23,
0,
/* actions for state 35 */
2,
7,
23,
0,
/* actions for state 36 */
2,
23,
0,
/* actions for state 37 */
2,
8,
23,
0,
/* actions for state 38 */
2,
23,
0,
/* actions for state 39 */
2,
21,
22,
23,
0,
/* actions for state 40 */
2,
21,
22,
23,
0,
/* actions for state 41 */
2,
11,
23,
0,
/* actions for state 42 */
2,
9,
23,
0,
/* actions for state 43 */
2,
5,
23,
0,
/* actions for state 44 */
2,
20,
22,
23,
0,
/* actions for state 45 */
2,
20,
23,
0,
/* actions for state 46 */
2,
3,
23,
0,
/* actions for state 47 */
2,
4,
23,
0,
/* actions for state 48 */
19,
0,
/* actions for state 49 */
21,
22,
0,
/* actions for state 50 */
22,
0,
/* actions for state 51 */
12,
0,
/* actions for state 52 */
13,
0,
/* actions for state 54 */
20,
22,
0,
/* actions for state 55 */
20,
0,
/* actions for state 58 */
18,
0,
/* actions for state 59 */
17,
18,
0,
/* actions for state 60 */
16,
18,
0,
0};
# define YYTYPE char
struct yy2work { YYTYPE verify, advance; } yy2crank[] ={
0,0,	0,0,	1,9,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,10,	1,0,	
0,0,	10,49,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,11,	
10,49,	0,0,	1,12,	0,0,	
1,13,	1,14,	1,15,	0,0,	
1,16,	1,17,	0,0,	0,0,	
1,18,	1,19,	1,20,	1,20,	
1,20,	1,20,	1,20,	1,20,	
1,20,	1,20,	1,20,	1,21,	
1,22,	2,0,	1,23,	18,52,	
0,0,	0,0,	1,24,	0,0,	
18,53,	0,0,	0,0,	0,0,	
1,25,	51,51,	51,51,	51,51,	
51,51,	51,51,	51,51,	51,51,	
51,51,	51,51,	51,51,	0,0,	
0,0,	2,11,	0,0,	0,0,	
2,12,	1,25,	2,13,	2,14,	
2,15,	19,54,	0,0,	2,17,	
28,57,	40,54,	2,18,	0,0,	
2,20,	2,20,	2,20,	2,20,	
2,20,	2,20,	2,20,	2,20,	
2,20,	2,21,	2,22,	3,0,	
2,23,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
1,26,	19,54,	1,27,	0,0,	
28,58,	40,54,	0,0,	0,0,	
0,0,	0,0,	0,0,	3,11,	
0,0,	0,0,	3,12,	0,0,	
3,13,	3,14,	3,15,	0,0,	
0,0,	3,17,	0,0,	0,0,	
3,18,	3,28,	3,20,	3,20,	
3,20,	3,20,	3,20,	3,20,	
3,20,	3,20,	3,20,	3,21,	
3,22,	4,0,	3,23,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	2,26,	0,0,	
2,27,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	4,11,	0,0,	0,0,	
4,12,	0,0,	4,13,	4,14,	
4,15,	0,0,	0,0,	4,17,	
0,0,	0,0,	4,18,	4,28,	
4,20,	4,20,	4,20,	4,20,	
4,20,	4,20,	4,20,	4,20,	
4,20,	4,21,	4,22,	5,0,	
4,23,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
3,26,	0,0,	3,27,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	5,11,	
0,0,	0,0,	5,12,	0,0,	
5,13,	5,14,	5,15,	0,0,	
0,0,	5,17,	0,0,	0,0,	
5,18,	0,0,	5,20,	5,20,	
5,20,	5,20,	5,20,	5,20,	
5,20,	5,20,	5,20,	5,21,	
5,22,	6,0,	5,23,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	4,26,	0,0,	
4,27,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	6,11,	0,0,	0,0,	
6,12,	0,0,	6,13,	6,14,	
6,15,	0,0,	0,0,	6,17,	
0,0,	0,0,	6,18,	0,0,	
6,20,	6,20,	6,20,	6,20,	
6,20,	6,20,	6,20,	6,20,	
6,20,	6,21,	6,22,	7,30,	
6,23,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	7,31,	
7,0,	0,0,	0,0,	0,0,	
5,29,	0,0,	5,27,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
7,32,	0,0,	0,0,	7,33,	
0,0,	7,34,	7,35,	7,36,	
0,0,	7,37,	7,38,	0,0,	
0,0,	7,39,	7,40,	7,41,	
7,41,	7,41,	7,41,	7,41,	
7,41,	7,41,	7,41,	7,41,	
7,42,	7,43,	8,0,	7,44,	
0,0,	0,0,	6,29,	7,45,	
6,27,	0,0,	0,0,	0,0,	
0,0,	7,46,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	8,32,	0,0,	
0,0,	8,33,	7,46,	8,34,	
8,35,	8,36,	0,0,	0,0,	
8,38,	0,0,	0,0,	8,39,	
0,0,	8,41,	8,41,	8,41,	
8,41,	8,41,	8,41,	8,41,	
8,41,	8,41,	8,42,	8,43,	
0,0,	8,44,	16,50,	16,50,	
16,50,	16,50,	16,50,	16,50,	
16,50,	16,50,	16,50,	16,50,	
0,0,	7,47,	0,0,	7,48,	
0,0,	0,0,	0,0,	16,51,	
16,51,	16,51,	16,51,	16,51,	
16,51,	0,0,	0,0,	25,56,	
25,56,	25,56,	25,56,	25,56,	
25,56,	25,56,	25,56,	25,56,	
25,56,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
25,56,	25,56,	25,56,	25,56,	
25,56,	25,56,	0,0,	16,51,	
16,51,	16,51,	16,51,	16,51,	
16,51,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	8,47,	
0,0,	8,48,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
25,56,	25,56,	25,56,	25,56,	
25,56,	25,56,	0,0,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	0,0,	0,0,	0,0,	
0,0,	24,56,	0,0,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	24,56,	24,56,	24,56,	
24,56,	46,56,	46,56,	46,56,	
46,56,	46,56,	46,56,	46,56,	
46,56,	46,56,	46,56,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	46,56,	46,56,	
46,56,	46,56,	46,56,	46,56,	
54,59,	54,59,	54,59,	54,59,	
54,59,	54,59,	54,59,	54,59,	
54,59,	54,59,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	54,59,	54,59,	54,59,	
54,59,	54,59,	54,59,	0,0,	
0,0,	0,0,	46,56,	46,56,	
46,56,	46,56,	46,56,	46,56,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
0,0,	54,59,	54,59,	54,59,	
54,59,	54,59,	54,59,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	57,60,	57,60,	57,60,	
57,60,	57,60,	57,60,	57,60,	
57,60,	57,60,	57,60,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	57,60,	57,60,	
57,60,	57,60,	57,60,	57,60,	
0,0,	0,0,	0,0,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	58,61,	
58,61,	58,61,	58,61,	58,61,	
58,61,	58,61,	58,61,	58,61,	
58,61,	0,0,	57,60,	57,60,	
57,60,	57,60,	57,60,	57,60,	
58,61,	58,61,	58,61,	58,61,	
58,61,	58,61,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
58,61,	58,61,	58,61,	58,61,	
58,61,	58,61,	0,0,	0,0,	
0,0};
struct yy2svf yy2svec[] ={
0,	0,	0,
yy2crank+-1,	0,		yy2vstop+1,		/* state 0 */
yy2crank+-51,	yy2svec+1,	yy2vstop+3,		/* state 1 */
yy2crank+-101,	yy2svec+1,	yy2vstop+5,		/* state 2 */
yy2crank+-151,	yy2svec+1,	yy2vstop+7,		/* state 3 */
yy2crank+-201,	yy2svec+1,	yy2vstop+9,		/* state 4 */
yy2crank+-251,	yy2svec+1,	yy2vstop+11,		/* state 5 */
yy2crank+-310,	0,		yy2vstop+13,		/* state 6 */
yy2crank+-360,	yy2svec+7,	yy2vstop+15,		/* state 7 */
yy2crank+0,	0,		yy2vstop+17,		/* state 8 */
yy2crank+4,	0,		yy2vstop+19,		/* state 9 */
yy2crank+0,	0,		yy2vstop+22,		/* state 10 */
yy2crank+0,	0,		yy2vstop+25,		/* state 11 */
yy2crank+0,	0,		yy2vstop+28,		/* state 12 */
yy2crank+0,	0,		yy2vstop+31,		/* state 13 */
yy2crank+0,	0,		yy2vstop+34,		/* state 14 */
yy2crank+374,	0,		yy2vstop+37,		/* state 15 */
yy2crank+0,	0,		yy2vstop+39,		/* state 16 */
yy2crank+21,	0,		yy2vstop+42,		/* state 17 */
yy2crank+5,	yy2svec+16,	yy2vstop+44,		/* state 18 */
yy2crank+0,	yy2svec+16,	yy2vstop+48,		/* state 19 */
yy2crank+0,	0,		yy2vstop+52,		/* state 20 */
yy2crank+0,	0,		yy2vstop+55,		/* state 21 */
yy2crank+0,	0,		yy2vstop+58,		/* state 22 */
yy2crank+438,	0,		yy2vstop+61,		/* state 23 */
yy2crank+399,	yy2svec+24,	yy2vstop+65,		/* state 24 */
yy2crank+0,	0,		yy2vstop+68,		/* state 25 */
yy2crank+0,	0,		yy2vstop+71,		/* state 26 */
yy2crank+8,	yy2svec+16,	yy2vstop+74,		/* state 27 */
yy2crank+0,	0,		yy2vstop+78,		/* state 28 */
yy2crank+0,	0,		yy2vstop+82,		/* state 29 */
yy2crank+0,	yy2svec+10,	yy2vstop+85,		/* state 30 */
yy2crank+0,	0,		yy2vstop+89,		/* state 31 */
yy2crank+0,	0,		yy2vstop+93,		/* state 32 */
yy2crank+0,	0,		yy2vstop+97,		/* state 33 */
yy2crank+0,	0,		yy2vstop+101,		/* state 34 */
yy2crank+0,	0,		yy2vstop+105,		/* state 35 */
yy2crank+0,	yy2svec+16,	yy2vstop+109,		/* state 36 */
yy2crank+0,	0,		yy2vstop+112,		/* state 37 */
yy2crank+0,	yy2svec+18,	yy2vstop+116,		/* state 38 */
yy2crank+9,	yy2svec+16,	yy2vstop+119,		/* state 39 */
yy2crank+0,	yy2svec+16,	yy2vstop+124,		/* state 40 */
yy2crank+0,	0,		yy2vstop+129,		/* state 41 */
yy2crank+0,	0,		yy2vstop+133,		/* state 42 */
yy2crank+0,	0,		yy2vstop+137,		/* state 43 */
yy2crank+0,	yy2svec+24,	yy2vstop+141,		/* state 44 */
yy2crank+513,	yy2svec+24,	yy2vstop+146,		/* state 45 */
yy2crank+0,	0,		yy2vstop+150,		/* state 46 */
yy2crank+0,	0,		yy2vstop+154,		/* state 47 */
yy2crank+0,	yy2svec+10,	yy2vstop+158,		/* state 48 */
yy2crank+0,	yy2svec+16,	yy2vstop+160,		/* state 49 */
yy2crank+25,	yy2svec+16,	yy2vstop+163,		/* state 50 */
yy2crank+0,	0,		yy2vstop+165,		/* state 51 */
yy2crank+0,	0,		yy2vstop+167,		/* state 52 */
yy2crank+536,	0,		0,			/* state 53 */
yy2crank+0,	yy2svec+24,	yy2vstop+169,		/* state 54 */
yy2crank+574,	yy2svec+24,	yy2vstop+172,		/* state 55 */
yy2crank+597,	0,		0,			/* state 56 */
yy2crank+635,	0,		0,			/* state 57 */
yy2crank+0,	yy2svec+54,	yy2vstop+174,		/* state 58 */
yy2crank+0,	yy2svec+57,	yy2vstop+176,		/* state 59 */
yy2crank+0,	yy2svec+58,	yy2vstop+179,		/* state 60 */
0,	0,	0};
struct yy2work *yy2top = yy2crank+737;
struct yy2svf *yy2bgin = yy2svec+1;
char yy2match[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,'+' ,01  ,'+' ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'X' ,'G' ,'G' ,01  ,01  ,01  ,01  ,'G' ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'X' ,'G' ,'G' ,01  ,01  ,01  ,01  ,01  ,
0};
char yy2extra[] ={
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
#undef LEXDEBUG
int yy2lineno =1;
#define YYU(x) x
#define NLSTATE yy2previous=YYNEWLINE
char yy2text[YYLMAX];
struct yy2svf *yy2lstate [YYLMAX], **yy2lsp, **yy2olsp;
char yy2sbuf[YYLMAX];
char *yy2sptr = yy2sbuf;
int *yy2fnd;
extern struct yy2svf *yy2estate;
int yy2previous = YYNEWLINE;
int yy2look(void){
	register struct yy2svf *yy2state, **lsp;
	register struct yy2work *yy2t;
	struct yy2svf *yy2z;
	int yy2ch;
	struct yy2work *yy2r;
#if defined(LEXDEBUG)
	int debug;
#endif
	char *yy2lastch;
	/* start off machines */
#if defined(LEXDEBUG)
	debug = 0;
#endif
	if (!yy2morfg)
		yy2lastch = yy2text;
	else {
		yy2morfg=0;
		yy2lastch = yy2text+yy2leng;
		}
	for(;;){
		lsp = yy2lstate;
		yy2estate = yy2state = yy2bgin;
		if (yy2previous==YYNEWLINE) yy2state++;
		for (;;){
#if defined(LEXDEBUG)
			if(debug)yy2error("state %d\n",yy2state-yy2svec-1);
#endif
			yy2t = yy2state->yy2stoff;
			if(yy2t == yy2crank){		/* may not be any transitions */
				yy2z = yy2state->yy2other;
				if(yy2z == 0)break;
				if(yy2z->yy2stoff == yy2crank)break;
				}
			*yy2lastch++ = yy2ch = input();
		tryagain:
#if defined(LEXDEBUG)
			if(debug){
				yy2error("char ");
				allprint(yy2ch);
				putchar('\n');
				}
#endif
			yy2r = yy2t;
			if (yy2t > yy2crank){
				yy2t = yy2r + yy2ch;
				if (yy2t <= yy2top && yy2t->verify+yy2svec == yy2state){
					if(yy2t->advance+yy2svec == YYLERR)	/* error transitions */
						{unput(*--yy2lastch);break;}
					*lsp++ = yy2state = yy2t->advance+yy2svec;
					goto contin;
					}
				}
#if defined(YYOPTIM)
			else if(yy2t < yy2crank) {		/* r < yy2crank */
				yy2t = yy2r = yy2crank+(yy2crank-yy2t);
#if defined(LEXDEBUG)
				if(debug)yy2error("compressed state\n");
#endif
				yy2t = yy2t + yy2ch;
				if(yy2t <= yy2top && yy2t->verify+yy2svec == yy2state){
					if(yy2t->advance+yy2svec == YYLERR)	/* error transitions */
						{unput(*--yy2lastch);break;}
					*lsp++ = yy2state = yy2t->advance+yy2svec;
					goto contin;
					}
				yy2t = yy2r + YYU(yy2match[yy2ch]);
#if defined(LEXDEBUG)
				if(debug){
					yy2error("try fall back character ");
					allprint(YYU(yy2match[yy2ch]));
					putchar('\n');
					}
#endif
				if(yy2t <= yy2top && yy2t->verify+yy2svec == yy2state){
					if(yy2t->advance+yy2svec == YYLERR)	/* error transition */
						{unput(*--yy2lastch);break;}
					*lsp++ = yy2state = yy2t->advance+yy2svec;
					goto contin;
					}
				}
			if ((yy2state = yy2state->yy2other) && (yy2t= yy2state->yy2stoff) != yy2crank){
#if defined(LEXDEBUG)
				if(debug)yy2error("fall back to state %d\n",yy2state-yy2svec-1);
#endif
				goto tryagain;
				}
#endif
			else
				{unput(*--yy2lastch);break;}
		contin:
#if defined(LEXDEBUG)
			if(debug){
				yy2error("state %d char ",yy2state-yy2svec-1);
				allprint(yy2ch);
				putchar('\n');
				}
#endif
			;
			}
#if defined(LEXDEBUG)
		if(debug){
			yy2error("stopped at %d with ",*(lsp-1)-yy2svec-1);
			allprint(yy2ch);
			putchar('\n');
			}
#endif
		while (lsp-- > yy2lstate){
			*yy2lastch-- = 0;
			if (*lsp != 0 && (yy2fnd= (*lsp)->yy2stops) && *yy2fnd > 0){
				yy2olsp = lsp;
				if(yy2extra[*yy2fnd]){		/* must backup */
					while(yy2back((*lsp)->yy2stops,-*yy2fnd) != 1 && lsp > yy2lstate){
						lsp--;
						unput(*yy2lastch--);
						}
					}
				yy2previous = YYU(*yy2lastch);
				yy2lsp = lsp;
				yy2leng = yy2lastch-yy2text+1;
				yy2text[yy2leng] = 0;
#if defined(LEXDEBUG)
				if(debug){
					yy2error("\nmatch ");
					sprint(yy2text);
					yy2error(" action %d\n",*yy2fnd);
					}
#endif
				return(*yy2fnd++);
				}
			unput(*yy2lastch);
			}
		if (yy2text[0] == 0  /* && feof(yy2in) */)
			{
			yy2sptr=yy2sbuf;
			return(0);
			}
		yy2previous = yy2text[0] = input();
		if (yy2previous>0)
			output(yy2previous);
		yy2lastch=yy2text;
#if defined(LEXDEBUG)
		if(debug)putchar('\n');
#endif
		}
	}
int yy2back (int *p, int m) {
	if (p==0) 
		return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
int yy2input(void){
	return(input());
}
void yy2output(int c){
	output(c);
}
void yy2unput(int c) {
	unput(c);
}
int yy2wrap(void){
	return(1);
}
