# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO printf( "%s",yytext)
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
#include "dqllx.htp"
#include <commonvu.hxx>
#include <containr.hxx>

static char SccsId[] = "uve Potsdam GmbH: %W%  %E%";

extern "C" {
	#include <ctype.h>
	#include "dql.h"
//	#include "winio.h"		// fputchar (), puts ()
	#include "ytab.h"
	#include <time.h>

        #include "komplexr.hr"
}

#include <clipbrd.hxx>  		// ClipBoard-Klasse
#include <ristypes.hxx>		 	// Koord
#include <geo_obj.hxx>
#include <dbasekey.hxx>

#include "yystype.hxx"
#include <dbtools.hxx>			// GetEditName ()
#include <ixtensn.hxx>          // Interfaces einer Erweiterung
#include <xtencunk.hxx>         // InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include "komplexr.hxx"		 	// KomplexrExtension

// LEX - RetVal definieren
extern YYSTYPE (*pyylval);
extern KomplexrExtension *pKE;
extern ResourceFile *pRF;
extern RMode actRechMode;
extern pchar pScriptName;	   	// Dateiname des akt. Scriptes
extern pWindow pW;			  	// Zeiger auf Hauptfenster
extern Bool DataFromED;		 	// Daten von Editor

// Neudefinition der LEX - I/O Routinen für WINIO
#undef output
#undef input
#undef ECHO

// #define output(c) fputchar(c)
#define output(c)
#define input() ((yytchar=yysptr>yysbuf?U(*--yysptr): \
				  (ActChar<ScriptEnd?*ActChar++:0))=='\n'? \
				  (yylineno++,LineBeg=ActChar,yytchar):yytchar)
// #define ECHO puts(yytext)
#define ECHO

// Globaler Buffer für Script -------------------------------------------------
const char *ScriptBuff = NULL;
const char *ScriptEnd;		  // ScriptEnde
const char *ActChar;			// nächstes einzulesendes Zeichen
const char *LineBeg;			// letzter ZeilenBeginn
const short ExprSize = 256;

/* Variablendefinitionen */
SYS_VAR system_var[] = {        /* Systemvariablen */
        {       "pagenum", 1    },      /* aktuelle Seitennummer */
        {       "linenum", 0    },      /* aktuelle Zeile auf Seite */
        {       "tuplenum", 0   },      /* aktuelle Datensatznummer */
        {       "colnum", 0     },      /* aktuelle Spaltennummer */
        {       NULL, 0 },
};

/* Systemkonstantenberechnungsfunktionen */
short Year (void), Month (void), Day (void), W_day (void);
short Y_day (void), Hour (void), Minute (void), Second (void);

SYS_CONST system_const[] = {  /* Systemkonstanten */
        {       "year", Year            },
        {       "month", Month          },
        {       "day", Day              },
        {       "m_day", Day            },
        {       "w_day", W_day          },
        {       "y_day", Y_day          },
        {       "hour", Hour            },
        {       "minute", Minute        },
        {       "second", Second        },
        {       NULL, NULL              }
};

/* reservierte Worte, die vom Scanner identifiziert werden */
KEYWORD SearchKeys[] = {
// Suchspezifikation
		{	   SEARCH, "search"		},
		{	   DBASE, "dbase"		  },
		{	   WINDOW, "window"		},
//	  {	   UMKREIS, "circumference"		},
//	  {	   UMRING, "buffer"		},
		{	   VIEW, "view"			},
		{	   SELECT, "select"		},
		{	   RECORDS, "records"	  },
		{	   WHERE, "where"		  },
		{	   USE, "use"			  },
		{	   KEY, "key"			  },
		{	   UNIQUE, "unique"		},
		{	   OBJECTS, "objects"	  },
		{	   IS, "is"				},
		{	   AS, "as"				},
		{	   SELECTED, "selected"	},
		{	   GROUP, "group"		  },
		{	   TEMP, "temporary"	   },
		{	   RELATION, "relation"	},
		{	   DEFAULT, "default"	  },
		{	   IDENTLIST, "identlist"  },
		{	   0, ""				   },
};

KEYWORD ReportKeys[] = {
// ReportGenerator
		{	   REPORT, "report"		},
		{	   DECLARATION, "declaration"	  },
		{	   CALL, "call"			},
		{	   PROC, "proc"			},
		{	   HEAD, "head"			},
		{	   TAIL, "foot"			},
		{	   TUPLES, "tuples"		},
		{	   LINES, "lines"		  },
		{	   COLUMNS, "columns"	  },
		{	   ALL, "all"			  },
		{	   FROM, "from"			},
		{	   TO, "to"				},
		{	   BIG, "big"			  },
		{	   PAGE, "page"			},
		{	   TUPLE, "tuple"		  },
		{	   FOR_ONE, "for_one"	  },
		{	   FOR_ALL, "for_all"	  },
		{	   FORMAT, "format"		},
		{	   VARI, "var_i"		   },
		{	   VARF, "var_f"		   },
		{	   VARS, "var_s"		   },
		{	   NEW, "new"			  },
		{	   LINE, "line"			},
		{	   COL, "col"			  },
		{	   SPACE, "space"		  },
		{	   BATCH, "batch"		  },
		{	   LASTI, "last_i"		 },
		{	   VALUEI, "value_i"	   },
		{	   NEXTI, "next_i"		 },
		{	   LASTF, "last_f"		 },
		{	   VALUEF, "value_f"	   },
		{	   NEXTF, "next_f"		 },
		{	   LASTS, "last_s"		 },
		{	   VALUES, "value_s"	   },
		{	   NEXTS, "next_s"		 },
		{	   FLOAT, "real"		   },
		{	   TERMINAL, "terminal"	},
		{	   DATE, "date"			},
		{	   TIME, "time"			},
		{	   PRINT, "print"		  },
		{	   LINEBEGIN, "linebegin"  },
		{	   LINEEND, "lineend"	  },
		{	   IF, "if"				},
		{	   ELSE, "else"			},
// DQL
		{	   ON, "on"				},
		{	   AS, "as"				},
		{	   GRAPHICS, "graphics"	},
		{	   SHEET, "sheet"		  },
		{	   OBJLIST, "objlist"	  },
		{	   WINDOW, "window"		},
		{	   PRINTER, "printer"	  },
		{	   CLASSIFICATION, "classification"		},
		{	   REPORT, "report"		},

		{	   0, ""				   },
};

KEYWORD *keywords;

int  tot_errs = 0;	   /* total errors encountered */

long act_seek;

# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
			 {
						/* Integer */
						long *inVal = new long (atol (yytext));
						YYSTYPE tmpY (inVal, YYSTYPE :: YYLong, yylineno);

								(*pyylval) = tmpY;
								return (INTEGER);
						}
break;
case 2:
case 3:
case 4:
		  {
						/* Real Number */
						double *inVal = new double (atof (yytext));
						YYSTYPE tmpY (inVal, YYSTYPE :: YYDouble, yylineno);

								(*pyylval) = tmpY;
								return (FLOAT);
						}
break;
case 5:
				case 6:
				{
						/* String */
						register unsigned char scope_char = *yytext;
						register char *cptr;
						char *inVal = new char [lstrlen(yytext+1)+1];
								
								lstrcpy (inVal, yytext+1);
								if ((cptr = strchr (inVal, scope_char)) != NULL)
										*cptr = '\0';

						YYSTYPE tmpY (inVal, YYSTYPE :: YYString, yylineno);

								(*pyylval) = tmpY;
								return (STRING);
						}
break;
case 7:
			 {
						/* DBase-Expression */
						char *inVal = new char [lstrlen(yytext+1)+1];
						register char *cptr;
								
								lstrcpy (inVal, yytext+1);
								if ((cptr = strchr (inVal, '\'')) != NULL)
										*cptr = '\0';

						YYSTYPE tmpY (inVal, YYSTYPE :: YYDBase, yylineno);

								(*pyylval) = tmpY;
								return (DBASEEXPR);
						}
break;
case 8:
				{
						/* Identifier, Keyword etc. */
						register int i;
						
						/* ist ID ein reserviertes Wort ? */
								if (keywords) {
								// Keywordfeld definiert
										for (i = 0; keywords[i].lx ; i++) {
												if (!strncmp (keywords[i].id, yytext, NAMELEN))
														break;
										}
										if (keywords[i].lx) {   /* ID ist Schluesselwort */
										char *inVal = new char [lstrlen(yytext)+1];
												lstrcpy (inVal, yytext);
										YYSTYPE tmpY (inVal, YYSTYPE :: YYString, yylineno);

												(*pyylval) = tmpY;
												return (keywords[i].lx);
										}
								}
						/* ist ID eine Systemvariable ? */
								for (i = 0; system_var[i].var_name; ++i) {
										if (!strncmp (system_var[i].var_name, yytext, NAMELEN))
												break;
								}
								if (system_var[i].var_name) {   /* ID ist Systemvar */
								long *inVal = new long (system_var[i].var_wert);
								YYSTYPE tmpY (inVal, YYSTYPE :: YYSysVar, yylineno);

										(*pyylval) = tmpY;
										return (SYSTEM_VAR);
								}
						/* ist ID Systemkonstante ? */
								for (i = 0; system_const[i].const_name; ++i) {
										if (!strncmp (system_const[i].const_name, yytext, NAMELEN))
												break;
								}
								if (system_const[i].const_name) {	   /* ID ist Sys.const */
								long *inVal = new long ((long)(*system_const[i].const_wert)());
								YYSTYPE tmpY (inVal, YYSTYPE :: YYLong, yylineno);

										(*pyylval) = tmpY;
										return (SYSTEM_CONST);
								}
								else {
						/* Ansonsten ist ID nutzerdefinierter Name */
								char *inVal = new char [lstrlen(yytext)+1];
										lstrcpy (inVal, yytext);
								YYSTYPE tmpY (inVal, YYSTYPE :: YYString, yylineno);

										(*pyylval) = tmpY;
										return (IDENT);
								}
						}
break;
case 9:
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
case 10:
			  return (OROR);
break;
case 11:
			  return (ANDAND);
break;
case 12:
			  return (NE);
break;
case 13:
			  return (LE);
break;
case 14:
			  return (GE);
break;
case 15:
			  return (EQ);
break;
case 16:
				 return (LT);
break;
case 17:
				 return (GT);
break;
case 18:
				 return (UNOT);
break;
case 19:
				 return (EQU);
break;
case 20:
				comment ("*/");
break;
case 21:
				comment ("\n");
break;
case 22:
	  ;
break;
case 23:
				   {   /* DBase-Expression mit Umlauten ? */
						if (yytext [0] == 96 /*'\`'*/) {
							char *inVal = new char [ExprSize];
							if (! inVal) {
								DEX_Error (RC_doRecherche, EC_NOMEMORY);
								YYSTYPE tmpY (NULL, YYSTYPE :: YYUnknown, yylineno);
								(*pyylval) = tmpY;
								return (*yytext);
							}

							pchar FirstChar = inVal;
							register char Ch;
							for (short i = 0; i < ExprSize; i++) {
								Ch = (char) input ();
								if (Ch  != '\'' && Ch != '\n' && (short) Ch != 0x01A)
									*inVal++ = Ch;
								else
									break;
							}
							if (Ch != '\'')
								DEX_Error (RC_doRecherche, EC_BaddBaseExpr);
							*inVal = '\0';

							YYSTYPE tmpY (FirstChar, YYSTYPE :: YYDBase, yylineno);
							(*pyylval) = tmpY;
							return (DBASEEXPR);
						}

						// Stackelement setzen (ZeilenNummer)
						YYSTYPE tmpY (NULL, YYSTYPE :: YYUnknown, yylineno);

								(*pyylval) = tmpY;
								return (*yytext);
						}
break;
case -1:
break;
default:
yyerror("Interner Fehler im LEX !");
} return(0); }
/* end of yylex */

/* Feststellen der aktuellen Position */

long prev_seek;  /* previous seek */

long yytell (register int which) {

		switch (which) {
		case 1:		 return (act_seek);
		case 0:		 return (prev_seek);
		case -1:		return ((ActChar - ScriptBuff) - (yysptr-yysbuf));
		}
		
		return 0;
}

static void seek (void)
{
		prev_seek = act_seek;
		act_seek = (ActChar - ScriptBuff) - (yysptr-yysbuf);
}

/* Neu Positionieren */
void yyseek (long new_seek) {
	ActChar = ScriptBuff + new_seek;
}

/* Parser Syntaxfehler */
void yyerror (const char *pError) {
	r_error ((char *)pError, yylineno);
}

/* Formatdefinitionsfehler */
void r_error (char *pErrorText, int LineNr) {
	const short InBufferSize = 128;
	char *pCmd = new char [_MAX_PATH * 2];
	char *pCmdHelp = new char [_MAX_PATH];
	char *pInBuff = new char [InBufferSize];
	char *pErrText = new char [128];

	if (!pCmd || !pCmdHelp || !pInBuff || !pErrText)
	{
		DEX_Error (RC_doRecherche, EC_NOMEMORY);
		return;
	}

//	alle Zeiger init.
	*pCmd = '\0';
	*pCmdHelp = '\0';
	*pErrText = '\0';
	*pInBuff = '\0';

	++tot_errs;
	char ModeCh = ' ';
	pchar pScript = NULL;
	switch (actRechMode) {
		case RMFile:
			pScript = pScriptName;
		break;
		case RMBuffer: {
		//  shreibe Script ins ClipBoard
			CClipboard DCB;			   		// Clipboard-Objekt
			DCB.Clear ();				   	// Inhalt des Clipboards löschen
			DCB.Insert (ScriptBuff);		// Inhalt kopieren
		}
		case RMClipboard:
			ModeCh = 'c';
		break;
		case RMUnknown:
		default: {
			DEX_Error (RC_doRecherche, EC_SYSERROR);
			DELETE_VEC (pCmd);
			DELETE_VEC (pCmdHelp);
			DELETE_VEC (pInBuff);
			DELETE_VEC (pErrText);
			return;
		}
	}

//  wenn Daten vom Editor
	if (DataFromED)
		ModeCh = 'k';

//  Fehlermeldung ggf. ausgeben
	if (pErrorText && *pErrorText && LineNr) {
		ResString ErrorText (ResID (IDS_SYNTAXERROR, pRF), 30);
		wsprintf (pErrText, ErrorText.Addr (), pErrorText, LineNr);
		// OutputError (lpCmd);	--> wird vom Editor ausgegeben
	}

//  TRIAS-ED starten
	if (pKE && (!pScript || !*pScript))	 // richtigen Pfad für TRIAS-ED einstellen
		pKE -> SetScriptPfad ();

	if (pScript && *pScript)
		wsprintf (pCmdHelp, "%s %s -p%ld -%c", GetEditName (pInBuff, InBufferSize -1),
											   pScript, yytell (-1), ModeCh);
	else
		wsprintf (pCmdHelp, "%s -p%ld -%c", 	GetEditName (pInBuff, InBufferSize - 1),
												yytell (-1), ModeCh);

//	Kommando-Zeile vervollst.
	lstrcpy (pCmd, pCmdHelp);
	if (pErrText)
		lstrcat (pCmd, pErrText);

//	Speicher freigeben
	DELETE_VEC (pCmdHelp);
	DELETE_VEC (pInBuff);
	DELETE_VEC (pErrText);

	RunTriasEdit (pW, pCmd, SW_SHOWNORMAL);

	DELETE_VEC (pCmd);
}


/* Schwerwiegender Formatdefinitionsfehler: Abbruch */
void r_abort (char *s) {
	r_error (s, 0);
}

int ExtDBError (int Routine, int Error, Bool iStartED) {
	DEX_Error (Routine, Error);

	if (iStartED)
		r_error (NULL, 0);	  // starte TRIAS-ED

	return  Error;
}

// Kommentar überlesen 
void comment (char *mat) {

		register int c = 1;
		register char *cp = mat;
		int lno = yylineno;

		while (*cp && c != 0) {
				if ((c = input ()) != *cp++)
						cp = mat;
		}
		if (c == 0) {
				yylineno = lno;
				r_abort ("EOF im Kommentar gelesen");
		}
}

// die folgenden Funktionen liefern die aktuelle Zeile und -Spalte
short ActLineNumber (void) { return yylineno; }
short ActColumnNumber (void) { return ActChar - LineBeg; }

short Year (void) {         /* Jahr - 1900 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_year);
}

short Month (void) {        /* Monat 1..12 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_mon);
}

short Day (void) {          /* Tag im Monat 1..31 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_mday);
}

short W_day (void) {        /* Wochentag 0..6 (0: Sonntag) */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_wday);
}

short Y_day (void) {        /* Tag im Jahr 1..365 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_yday);
}

short Hour (void) {         /* Stunde 0..23 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_hour);
}

short Minute (void)  {      /* Minute 0..59 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_min);
}

short Second (void) {       /* Sekunde 0..59 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_sec);
}
int yyvstop[] ={
0,
/* actions for state 0 */
22,
0,
/* actions for state 1 */
22,
0,
/* actions for state 2 */
23,
0,
/* actions for state 3 */
22,
23,
0,
/* actions for state 4 */
22,
0,
/* actions for state 5 */
18,
23,
0,
/* actions for state 6 */
23,
0,
/* actions for state 7 */
23,
0,
/* actions for state 8 */
23,
0,
/* actions for state 9 */
23,
0,
/* actions for state 10 */
23,
0,
/* actions for state 11 */
23,
0,
/* actions for state 12 */
1,
23,
0,
/* actions for state 13 */
16,
23,
0,
/* actions for state 14 */
19,
23,
0,
/* actions for state 15 */
17,
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
23,
0,
/* actions for state 19 */
9,
23,
0,
/* actions for state 20 */
12,
0,
/* actions for state 22 */
5,
0,
/* actions for state 23 */
11,
0,
/* actions for state 25 */
6,
0,
/* actions for state 27 */
1,
0,
/* actions for state 28 */
3,
0,
/* actions for state 29 */
20,
0,
/* actions for state 30 */
21,
0,
/* actions for state 31 */
2,
0,
/* actions for state 33 */
13,
0,
/* actions for state 34 */
15,
0,
/* actions for state 35 */
14,
0,
/* actions for state 36 */
8,
0,
/* actions for state 38 */
7,
0,
/* actions for state 39 */
10,
0,
/* actions for state 41 */
2,
3,
0,
/* actions for state 44 */
4,
0,
/* actions for state 46 */
3,
0,
/* actions for state 49 */
2,
0,
/* actions for state 51 */
2,
3,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
0,0,	0,0,	1,4,	4,5,	
4,5,	22,0,	0,0,	4,5,	
22,0,	25,0,	0,0,	0,0,	
25,0,	0,0,	38,0,	0,0,	
0,0,	38,0,	0,0,	0,0,	
4,5,	22,0,	1,6,	1,7,	
0,0,	25,0,	4,5,	1,8,	
1,9,	8,24,	38,0,	0,0,	
1,10,	12,30,	0,0,	1,11,	
1,12,	1,13,	12,31,	2,6,	
0,0,	2,20,	0,0,	0,0,	
2,8,	0,0,	0,0,	0,0,	
0,0,	1,14,	1,15,	1,16,	
2,11,	2,12,	1,17,	6,21,	
14,34,	1,17,	15,35,	16,36,	
0,0,	7,22,	0,0,	29,41,	
29,41,	0,0,	2,14,	2,15,	
2,16,	7,22,	7,0,	0,0,	
9,25,	7,0,	42,48,	42,48,	
0,0,	0,0,	13,32,	0,0,	
9,25,	9,0,	0,0,	0,0,	
9,0,	1,18,	7,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	7,23,	29,41,	
29,41,	9,0,	0,0,	7,22,	
13,33,	13,33,	2,18,	7,22,	
0,0,	9,25,	42,48,	42,48,	
7,22,	0,0,	9,26,	0,0,	
0,0,	1,19,	9,25,	19,40,	
0,0,	0,0,	0,0,	9,25,	
0,0,	0,0,	0,0,	0,0,	
0,0,	7,22,	0,0,	0,0,	
7,22,	0,0,	2,19,	0,0,	
13,33,	13,33,	0,0,	0,0,	
9,25,	0,0,	10,27,	9,25,	
10,28,	10,28,	10,28,	10,28,	
10,28,	10,28,	10,28,	10,28,	
10,28,	10,28,	11,29,	11,29,	
11,29,	11,29,	11,29,	11,29,	
11,29,	11,29,	11,29,	11,29,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	0,0,	
0,0,	0,0,	0,0,	17,37,	
0,0,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	17,37,	
17,37,	17,37,	17,37,	18,38,	
28,32,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	18,38,	
18,0,	0,0,	0,0,	18,0,	
44,45,	44,45,	44,45,	44,45,	
44,45,	44,45,	44,45,	44,45,	
44,45,	44,45,	28,33,	28,33,	
18,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
18,38,	0,0,	0,0,	0,0,	
0,0,	18,39,	0,0,	0,0,	
0,0,	18,38,	0,0,	0,0,	
0,0,	0,0,	18,38,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	28,33,	28,33,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	18,38,	
0,0,	0,0,	18,38,	32,42,	
32,42,	32,42,	32,42,	32,42,	
32,42,	32,42,	32,42,	32,42,	
32,42,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
33,44,	0,0,	33,44,	32,43,	
32,43,	33,45,	33,45,	33,45,	
33,45,	33,45,	33,45,	33,45,	
33,45,	33,45,	33,45,	41,46,	
0,0,	41,46,	0,0,	0,0,	
41,47,	41,47,	41,47,	41,47,	
41,47,	41,47,	41,47,	41,47,	
41,47,	41,47,	0,0,	0,0,	
43,49,	0,0,	43,49,	32,43,	
32,43,	43,50,	43,50,	43,50,	
43,50,	43,50,	43,50,	43,50,	
43,50,	43,50,	43,50,	46,47,	
46,47,	46,47,	46,47,	46,47,	
46,47,	46,47,	46,47,	46,47,	
46,47,	48,51,	0,0,	48,51,	
0,0,	0,0,	48,52,	48,52,	
48,52,	48,52,	48,52,	48,52,	
48,52,	48,52,	48,52,	48,52,	
49,50,	49,50,	49,50,	49,50,	
49,50,	49,50,	49,50,	49,50,	
49,50,	49,50,	51,52,	51,52,	
51,52,	51,52,	51,52,	51,52,	
51,52,	51,52,	51,52,	51,52,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+-1,	0,		yyvstop+1,		/* state 0 */
yycrank+-18,	yysvec+1,	yyvstop+3,		/* state 1 */
yycrank+0,	0,		yyvstop+5,		/* state 2 */
yycrank+6,	0,		yyvstop+7,		/* state 3 */
yycrank+0,	yysvec+4,	yyvstop+10,		/* state 4 */
yycrank+6,	0,		yyvstop+12,		/* state 5 */
yycrank+-72,	0,		yyvstop+15,		/* state 6 */
yycrank+3,	0,		yyvstop+17,		/* state 7 */
yycrank+-83,	0,		yyvstop+19,		/* state 8 */
yycrank+104,	0,		yyvstop+21,		/* state 9 */
yycrank+114,	0,		yyvstop+23,		/* state 10 */
yycrank+3,	0,		yyvstop+25,		/* state 11 */
yycrank+44,	yysvec+10,	yyvstop+27,		/* state 12 */
yycrank+7,	0,		yyvstop+30,		/* state 13 */
yycrank+9,	0,		yyvstop+33,		/* state 14 */
yycrank+10,	0,		yyvstop+36,		/* state 15 */
yycrank+124,	0,		yyvstop+39,		/* state 16 */
yycrank+-246,	0,		yyvstop+42,		/* state 17 */
yycrank+3,	0,		yyvstop+44,		/* state 18 */
yycrank+0,	0,		yyvstop+46,		/* state 19 */
yycrank+0,	0,		yyvstop+49,		/* state 20 */
yycrank+-7,	yysvec+7,	0,			/* state 21 */
yycrank+0,	0,		yyvstop+51,		/* state 22 */
yycrank+0,	0,		yyvstop+53,		/* state 23 */
yycrank+-11,	yysvec+9,	0,			/* state 24 */
yycrank+0,	0,		yyvstop+55,		/* state 25 */
yycrank+0,	yysvec+11,	0,			/* state 26 */
yycrank+202,	yysvec+10,	yyvstop+57,		/* state 27 */
yycrank+7,	yysvec+11,	yyvstop+59,		/* state 28 */
yycrank+0,	0,		yyvstop+61,		/* state 29 */
yycrank+0,	0,		yyvstop+63,		/* state 30 */
yycrank+267,	0,		yyvstop+65,		/* state 31 */
yycrank+289,	0,		0,			/* state 32 */
yycrank+0,	0,		yyvstop+67,		/* state 33 */
yycrank+0,	0,		yyvstop+69,		/* state 34 */
yycrank+0,	0,		yyvstop+71,		/* state 35 */
yycrank+0,	yysvec+17,	yyvstop+73,		/* state 36 */
yycrank+-16,	yysvec+18,	0,			/* state 37 */
yycrank+0,	0,		yyvstop+75,		/* state 38 */
yycrank+0,	0,		yyvstop+77,		/* state 39 */
yycrank+304,	0,		0,			/* state 40 */
yycrank+18,	yysvec+32,	yyvstop+79,		/* state 41 */
yycrank+321,	0,		0,			/* state 42 */
yycrank+212,	0,		0,			/* state 43 */
yycrank+0,	yysvec+44,	yyvstop+82,		/* state 44 */
yycrank+331,	0,		0,			/* state 45 */
yycrank+0,	yysvec+46,	yyvstop+84,		/* state 46 */
yycrank+346,	0,		0,			/* state 47 */
yycrank+356,	0,		0,			/* state 48 */
yycrank+0,	yysvec+49,	yyvstop+86,		/* state 49 */
yycrank+366,	0,		0,			/* state 50 */
yycrank+0,	yysvec+51,	yyvstop+88,		/* state 51 */
0,	0,	0};
struct yywork *yytop = yycrank+423;
struct yysvf *yybgin = yysvec+1;
char yymatch[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,015 ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,015 ,01  ,01  ,01  ,01  ,01  ,
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
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
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
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
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
# ifdef LEXDEBUG
			if(debug)printf("state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				printf("char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)printf("compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					printf("try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)printf("fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				printf("state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			printf("stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
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
# ifdef LEXDEBUG
				if(debug){
					printf("\nmatch ");
					sprint(yytext);
					printf(" action %d\n",*yyfnd);
					}
# endif
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
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
int yyback(int *p, int m) {
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
int yyinput(void) {
	return(input());
}
void yyoutput(int c) {
	output(c);
}
void yyunput(int c) {
	unput(c);
}
int yywrap (void) {
	return 1;
}
