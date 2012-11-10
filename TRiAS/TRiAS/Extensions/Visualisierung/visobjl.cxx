# define U(x) x
# define NLSTATE yy1previous=YYNEWLINE
# define BEGIN yy1bgin = yy1svec + 1 +
# define INITIAL 0
# define YYLERR yy1svec
# define YYSTATE (yy1estate-yy1svec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yy1out)
# define input() (((yy1tchar=yy1sptr>yy1sbuf?U(*--yy1sptr):getc(yy1in))==10?(yy1lineno++,yy1tchar):yy1tchar)==EOF?0:yy1tchar)
# define unput(c) {yy1tchar= (c);if(yy1tchar=='\n')yy1lineno--;*yy1sptr++=yy1tchar;}
# define yy1more() (yy1morfg=1)
# define ECHO ; // "%s",yy1text)
# define REJECT { nstr = yy1reject(); goto yy1fussy;}
int yy1leng; extern char yy1text[];
int yy1morfg;
extern char *yy1sptr, yy1sbuf[];
int yy1tchar;
extern int yy1lineno;
struct yy1svf { 
	struct yy1work *yy1stoff;
	struct yy1svf *yy1other;
	int *yy1stops;};
struct yy1svf *yy1estate;
extern struct yy1svf yy1svec[], *yy1bgin;

extern "C" {
	#include <windows.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>

	#include "yvisobj.h"
}

#include <commonvu.hxx>

#include <errcodes.hxx>
#include <attribs.hxx>

#include "yy1stype.hxx"

#if defined(_MSC_VER)
#pragma warning (disable: 4102)		// unreferenced label
#endif

#if !defined(true)
#define true (1)
#endif


// Neudefinition der LEX - I/O Routinen für WINIO
# undef output
# undef input
# undef ECHO

# define output(c) /*fputchar(c)*/
# define input() (yy1tchar=yy1sptr>yy1sbuf?U(*--yy1sptr): \
		  (pActChar<pBuffEnd?*pActChar++:0))

extern YYSTYPE (*pyy1lval);
void yy1error (ErrCode, ...);
void yy1error (const char *, ...);

char *pActChar;
char *pBuffEnd;

struct keyentry {               /* Tabelleneintrag fuer reservierte Worte */
	int  lx;
	char *id;
};

/* reservierte Worte, die vom Scanner identifiziert werden */
static struct keyentry keywords[] = {
	{	T_PRIORITY, "PRIORITY"	},
	{	T_TYPE, "TYPE"		},
	{	T_MAINCOLOR, "MAINCOLOR"	},
	{	T_SIZE, "SIZE"		},
	{	T_WIDTH, "WIDTH"	},
	{	T_FILLCOLOR, "FILLCOLOR"	},
	{	T_PUNKT, "COORDPAIR"	},
	{	T_LINIE, "LINE"		},
	{	T_FLAECHE, "AREA"	},
	{	T_TEXT, "X"	},
	{	T_TTYP, "Y"	},
	{	T_TROT, "ROTATION"	},
	{	T_TAGGED, "KENNZEICHEN"	},
	{	T_TESC,	"ORIENTATION"	},
	{	T_TVCS, "Z"		},
	{	T_LOCATABLE, "LOCATABLE" },
	{	T_VISIBLE, "VISIBLE" },
	{	0, NULL	},
};

#undef YYLMAX		// max. StringLaenge
#define YYLMAX	2048

# define TextTyp 2
# define YYNEWLINE 10
yy1lex(){
int nstr; extern int yy1previous;
while((nstr = yy1look()) >= 0)
yy1fussy: switch(nstr){
case 0:
if(yy1wrap()) return(0); break;
case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		{
				return *yy1text;
			}
break;
case 8:
		case 9:
		{
			int scope_char = yy1text[0];
			int inchar;
			char *cptr = new char [YYLMAX];
			char *pBuff = cptr;
			
				if (cptr == NULL)
					yy1error (EC_NOMEMORY);
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
				LEXSTACK (pBuff, YYString, yy1lineno);
				return T_STRING;
			}
break;
case 10:
                {       /* Integerzahl */
			long *pLNum = new long (atol (yy1text));

				LEXSTACK (pLNum, YYLong, yy1lineno);
				return (T_NUMBER);
			}
break;
case 11:
	case 12:
	{		/* HexZahl */
			long *pLNum = new long (strtoul (yy1text, NULL, 16));

				BEGIN 0;
				LEXSTACK (pLNum, YYLong, yy1lineno);
				return T_NUMBER;
			}
break;
case 13:
                 ;
break;
case 14:
                   {	/* Keyword */
			short iLen = strlen (yy1text);
			char *pIdent = new char [iLen+1];

				if (pIdent != NULL) {
					strcpy (pIdent, yy1text);
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

					LEXSTACK (pIdent, YYString, yy1lineno);
					return (keywords[i].lx);
				} 
				else {          /* kein Keyword --> Fehler */
					if (pIdent) delete pIdent;
					LEXSTACK (NULL, YYLong, yy1lineno);
					return (T_IDENT);
				}
			}
break;
case 15:
		{	/* Kommentar */
			register int ch;

                                for (;;) {
                                        while ((ch = input()) != '*') {
                                                if (ch == '\n')
                                                        ++yy1lineno;
                                        }
                                        if ( (ch = input()) == '/')
                                                break;
                                        else
                                                unput(ch);
                                }
                        }
break;
case 16:
		{	/* Kommentar */
			register int ch;

				while ((ch = input()) != '\n')
					;
				unput(ch);
			}
break;
case 17:
                     {       /* Zeilen zaehlen */
				yy1lineno++;
			}
break;
case 18:
                      ;
break;
case -1:
break;
default:
; //"bad switch yy1look %d",nstr);
} return(0); }
/* end of yy1lex */

int yy1vstop[] ={
0,
/* actions for state 0 */
13,
0,
/* actions for state 1 */
13,
0,
/* actions for state 2 */
13,
0,
/* actions for state 3 */
13,
0,
/* actions for state 4 */
18,
0,
/* actions for state 5 */
13,
18,
0,
/* actions for state 6 */
17,
0,
/* actions for state 7 */
8,
18,
0,
/* actions for state 8 */
6,
18,
0,
/* actions for state 9 */
9,
18,
0,
/* actions for state 10 */
18,
0,
/* actions for state 11 */
4,
18,
0,
/* actions for state 12 */
18,
0,
/* actions for state 13 */
10,
18,
0,
/* actions for state 14 */
7,
18,
0,
/* actions for state 15 */
5,
18,
0,
/* actions for state 16 */
3,
18,
0,
/* actions for state 17 */
14,
18,
0,
/* actions for state 18 */
1,
18,
0,
/* actions for state 19 */
2,
18,
0,
/* actions for state 20 */
10,
18,
0,
/* actions for state 21 */
13,
0,
/* actions for state 22 */
10,
0,
/* actions for state 23 */
15,
0,
/* actions for state 24 */
16,
0,
/* actions for state 25 */
14,
0,
/* actions for state 28 */
12,
0,
/* actions for state 29 */
11,
0,
0};
# define YYTYPE char
struct yy1work { YYTYPE verify, advance; } yy1crank[] ={
0,0,	0,0,	1,5,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,6,	1,7,	
0,0,	6,22,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,8,	
6,22,	0,0,	1,9,	0,0,	
1,10,	0,0,	0,0,	0,0,	
1,11,	1,12,	0,0,	13,24,	
1,13,	1,14,	0,0,	2,8,	
13,25,	0,0,	2,9,	0,0,	
2,10,	0,0,	0,0,	1,15,	
1,16,	2,12,	1,17,	0,0,	
2,13,	3,5,	1,18,	0,0,	
0,0,	0,0,	0,0,	0,0,	
1,18,	3,6,	3,7,	2,15,	
2,16,	0,0,	2,17,	11,23,	
11,23,	11,23,	11,23,	11,23,	
11,23,	11,23,	11,23,	11,23,	
11,23,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	21,27,	
0,0,	0,0,	3,8,	0,0,	
0,0,	3,9,	0,0,	3,10,	
0,0,	0,0,	0,0,	3,11,	
3,12,	0,0,	0,0,	3,13,	
3,21,	3,14,	3,14,	3,14,	
3,14,	3,14,	3,14,	3,14,	
3,14,	3,14,	3,15,	3,16,	
1,19,	3,17,	1,20,	21,28,	
4,8,	3,18,	0,0,	4,9,	
0,0,	4,10,	0,0,	3,18,	
0,0,	0,0,	4,12,	0,0,	
2,19,	4,13,	2,20,	4,14,	
4,14,	4,14,	4,14,	4,14,	
4,14,	4,14,	4,14,	4,14,	
4,15,	4,16,	0,0,	4,17,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	0,0,	
0,0,	0,0,	0,0,	3,19,	
0,0,	3,20,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
0,0,	4,19,	0,0,	4,20,	
18,26,	0,0,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
27,29,	27,29,	27,29,	27,29,	
27,29,	27,29,	27,29,	27,29,	
27,29,	27,29,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	27,29,	27,29,	27,29,	
27,29,	27,29,	27,29,	28,30,	
28,30,	28,30,	28,30,	28,30,	
28,30,	28,30,	28,30,	28,30,	
28,30,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
28,30,	28,30,	28,30,	28,30,	
28,30,	28,30,	0,0,	0,0,	
0,0,	27,29,	27,29,	27,29,	
27,29,	27,29,	27,29,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
28,30,	28,30,	28,30,	28,30,	
28,30,	28,30,	0,0,	0,0,	
0,0};
struct yy1svf yy1svec[] ={
0,	0,	0,
yy1crank+-1,	0,		yy1vstop+1,		/* state 0 */
yy1crank+-17,	yy1svec+1,	yy1vstop+3,		/* state 1 */
yy1crank+-64,	0,		yy1vstop+5,		/* state 2 */
yy1crank+-94,	yy1svec+3,	yy1vstop+7,		/* state 3 */
yy1crank+0,	0,		yy1vstop+9,		/* state 4 */
yy1crank+4,	0,		yy1vstop+11,		/* state 5 */
yy1crank+0,	0,		yy1vstop+14,		/* state 6 */
yy1crank+0,	0,		yy1vstop+16,		/* state 7 */
yy1crank+0,	0,		yy1vstop+19,		/* state 8 */
yy1crank+0,	0,		yy1vstop+22,		/* state 9 */
yy1crank+31,	0,		yy1vstop+25,		/* state 10 */
yy1crank+0,	0,		yy1vstop+27,		/* state 11 */
yy1crank+5,	0,		yy1vstop+30,		/* state 12 */
yy1crank+0,	yy1svec+11,	yy1vstop+32,		/* state 13 */
yy1crank+0,	0,		yy1vstop+35,		/* state 14 */
yy1crank+0,	0,		yy1vstop+38,		/* state 15 */
yy1crank+0,	0,		yy1vstop+41,		/* state 16 */
yy1crank+125,	0,		yy1vstop+44,		/* state 17 */
yy1crank+0,	0,		yy1vstop+47,		/* state 18 */
yy1crank+0,	0,		yy1vstop+50,		/* state 19 */
yy1crank+7,	yy1svec+11,	yy1vstop+53,		/* state 20 */
yy1crank+0,	yy1svec+6,	yy1vstop+56,		/* state 21 */
yy1crank+0,	yy1svec+11,	yy1vstop+58,		/* state 22 */
yy1crank+0,	0,		yy1vstop+60,		/* state 23 */
yy1crank+0,	0,		yy1vstop+62,		/* state 24 */
yy1crank+0,	yy1svec+18,	yy1vstop+64,		/* state 25 */
yy1crank+200,	0,		0,			/* state 26 */
yy1crank+223,	0,		0,			/* state 27 */
yy1crank+0,	yy1svec+27,	yy1vstop+66,		/* state 28 */
yy1crank+0,	yy1svec+28,	yy1vstop+68,		/* state 29 */
0,	0,	0};
struct yy1work *yy1top = yy1crank+325;
struct yy1svf *yy1bgin = yy1svec+1;
char yy1match[] ={
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
'G' ,'G' ,'G' ,01  ,01  ,01  ,01  ,'G' ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,'G' ,
'G' ,'G' ,'G' ,01  ,01  ,01  ,01  ,01  ,
0};
char yy1extra[] ={
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
#undef LEXDEBUG
int yy1lineno =1;
#define YYU(x) x
#define NLSTATE yy1previous=YYNEWLINE
char yy1text[YYLMAX];
struct yy1svf *yy1lstate [YYLMAX], **yy1lsp, **yy1olsp;
char yy1sbuf[YYLMAX];
char *yy1sptr = yy1sbuf;
int *yy1fnd;
extern struct yy1svf *yy1estate;
int yy1previous = YYNEWLINE;
int yy1look(void){
	register struct yy1svf *yy1state, **lsp;
	register struct yy1work *yy1t;
	struct yy1svf *yy1z;
	int yy1ch;
	struct yy1work *yy1r;
#if defined(LEXDEBUG)
	int debug;
#endif
	char *yy1lastch;
	/* start off machines */
#if defined(LEXDEBUG)
	debug = 0;
#endif
	if (!yy1morfg)
		yy1lastch = yy1text;
	else {
		yy1morfg=0;
		yy1lastch = yy1text+yy1leng;
		}
	for(;;){
		lsp = yy1lstate;
		yy1estate = yy1state = yy1bgin;
		if (yy1previous==YYNEWLINE) yy1state++;
		for (;;){
#if defined(LEXDEBUG)
			if(debug); //"state %d\n",yy1state-yy1svec-1);
#endif
			yy1t = yy1state->yy1stoff;
			if(yy1t == yy1crank){		/* may not be any transitions */
				yy1z = yy1state->yy1other;
				if(yy1z == 0)break;
				if(yy1z->yy1stoff == yy1crank)break;
				}
			*yy1lastch++ = yy1ch = input();
		tryagain:
#if defined(LEXDEBUG)
			if(debug){
				; //"char ");
				allprint(yy1ch);
				putchar('\n');
				}
#endif
			yy1r = yy1t;
			if (yy1t > yy1crank){
				yy1t = yy1r + yy1ch;
				if (yy1t <= yy1top && yy1t->verify+yy1svec == yy1state){
					if(yy1t->advance+yy1svec == YYLERR)	/* error transitions */
						{unput(*--yy1lastch);break;}
					*lsp++ = yy1state = yy1t->advance+yy1svec;
					goto contin;
					}
				}
#if defined(YYOPTIM)
			else if(yy1t < yy1crank) {		/* r < yy1crank */
				yy1t = yy1r = yy1crank+(yy1crank-yy1t);
#if defined(LEXDEBUG)
				if(debug); //"compressed state\n");
#endif
				yy1t = yy1t + yy1ch;
				if(yy1t <= yy1top && yy1t->verify+yy1svec == yy1state){
					if(yy1t->advance+yy1svec == YYLERR)	/* error transitions */
						{unput(*--yy1lastch);break;}
					*lsp++ = yy1state = yy1t->advance+yy1svec;
					goto contin;
					}
				yy1t = yy1r + YYU(yy1match[yy1ch]);
#if defined(LEXDEBUG)
				if(debug){
					; //"try fall back character ");
					allprint(YYU(yy1match[yy1ch]));
					putchar('\n');
					}
#endif
				if(yy1t <= yy1top && yy1t->verify+yy1svec == yy1state){
					if(yy1t->advance+yy1svec == YYLERR)	/* error transition */
						{unput(*--yy1lastch);break;}
					*lsp++ = yy1state = yy1t->advance+yy1svec;
					goto contin;
					}
				}
			if ((yy1state = yy1state->yy1other) && (yy1t= yy1state->yy1stoff) != yy1crank){
#if defined(LEXDEBUG)
				if(debug); //"fall back to state %d\n",yy1state-yy1svec-1);
#endif
				goto tryagain;
				}
#endif
			else
				{unput(*--yy1lastch);break;}
		contin:
#if defined(LEXDEBUG)
			if(debug){
				; //"state %d char ",yy1state-yy1svec-1);
				allprint(yy1ch);
				putchar('\n');
				}
#endif
			;
			}
#if defined(LEXDEBUG)
		if(debug){
			; //"stopped at %d with ",*(lsp-1)-yy1svec-1);
			allprint(yy1ch);
			putchar('\n');
			}
#endif
		while (lsp-- > yy1lstate){
			*yy1lastch-- = 0;
			if (*lsp != 0 && (yy1fnd= (*lsp)->yy1stops) && *yy1fnd > 0){
				yy1olsp = lsp;
				if(yy1extra[*yy1fnd]){		/* must backup */
					while(yy1back((*lsp)->yy1stops,-*yy1fnd) != 1 && lsp > yy1lstate){
						lsp--;
						unput(*yy1lastch--);
						}
					}
				yy1previous = YYU(*yy1lastch);
				yy1lsp = lsp;
				yy1leng = yy1lastch-yy1text+1;
				yy1text[yy1leng] = 0;
#if defined(LEXDEBUG)
				if(debug){
					; //"\nmatch ");
					sprint(yy1text);
					; //" action %d\n",*yy1fnd);
					}
#endif
				return(*yy1fnd++);
				}
			unput(*yy1lastch);
			}
		if (yy1text[0] == 0  /* && feof(yy1in) */)
			{
			yy1sptr=yy1sbuf;
			return(0);
			}
		yy1previous = yy1text[0] = input();
		if (yy1previous>0)
			output(yy1previous);
		yy1lastch=yy1text;
#if defined(LEXDEBUG)
		if(debug)putchar('\n');
#endif
		}
	}
int yy1back (int *p, int m) {
	if (p==0) 
		return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
int yy1input(void){
	return(input());
}
void yy1output(int c){
	output(c);
}
void yy1unput(int c) {
	unput(c);
}
int yy1wrap(void){
	return(1);
}
