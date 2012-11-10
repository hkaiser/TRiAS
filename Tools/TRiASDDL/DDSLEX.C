/* Scanner fuer DDSP                                            */
/* File: DDSLEX.C               last update: 17. Mai 1989       */

#if defined(sccs)
static char SccsId[] = "%W%	%E%";
#endif

#include "StdAfx.h"

#ifdef unix
#include "y.tab.h"
#endif
#if defined(msdos) || defined(WIN32)
#include "ytab.h"
#endif

#include "ddspprot.h"		// Prototypen

extern FILE *schema;            /* Eingabefile */
extern char fnin[];				/* Schemafilename */

extern int yydebug;
extern int yychar;

struct keyentry {               /* Tabelleneintrag fuer reservierte Worte */
	int  lx;
	char *id;
};

/* reservierte Worte, die vom Scanner identifiziert werden */
struct keyentry keywords[] = {
	{ T_CHAR, "char"  },
	{ T_CONTAINS, "contain"   },
	{ T_CONTAINS, "contains"  },
	{ T_DATA, "data"  },
	{ T_DATABASE, "database"  },
	{ T_DB_ADDR, "db_addr"    },
	{ T_DOUBLE, "double"      },
	{ T_FILE, "file"  },
	{ T_FILE, "files" },
	{ T_FLOAT, "float"        },
	{ T_INT, "int"    },
	{ T_LONG, "long"  },
	{ T_RECORD, "record"      },
	{ T_SHORT, "short"        },
	{ T_STRUCT, "struct"      },
	{ T_UNION, "union"        },
	{ T_UNIQUE, "unique"      },
	{ T_ONLY, "only"          },
	{ T_KEY, "key"            },
	{ T_AND, "and"            },
	{ T_BTREE, "btree"        },
	{ T_HTREE, "htree"        },
	{ T_CTREE, "ctree"        },
	{ T_QTREE, "qtree"        },
	{ T_BACKUP, "backup"      },
	{ T_TO, "to"              },
	{ T_ENABLE, "enable"      },
	{ T_DISABLE, "disable"    },
	{ T_VERSION, "version"	},
	{ T_EXTENSION, "extension"	},
	{ 0, "\0" }
};

#define MAXSTACK 20
int pbstack[MAXSTACK];   /* pushed back input stack */
int bp = -1;            /* pbstack pointer */
int ch = '\n';           /* Last input character */
int line = 0;           /* current input line number */
int tot_errs = 0;       /* total errors encountered */
extern int r_flag;      /* true if -v (verbose) option selected */

/* der eigentliche Scanner */

yylex()
{
	register int i;
	register int n;
	
	for (;;) {
		while (ch <= ' ') {
			while (ch == '\n') {
				++line;
				if ((ch = input()) == '#') {
					/* Zeile ignorieren */
					while ((ch = input()) == ' ')
						;
					if (isdigit(ch)) {
						n = 0;
						while (isdigit(ch)) {
							n= 10*n + ch - '0';
							ch = input();
						}
						line = n - 1;
					}
					while ((ch = input()) != '\n')
						;
				}
				else if (ch != '\n')
					unput(ch);
			}
			if (ch == EOF)
				return(EOF);
			ch = input();
		}
		if (isalpha(ch)) {
			/* Identifikator scannen */
			for (yylval.tstr.str[i=0] = ch;
			(ch = input()), (isalnum(ch)||ch == '_'); )
				if (i < NAMELEN -1)
					yylval.tstr.str[++i] = ch;
				yylval.tstr.str[++i] = '\0';
				
				/* ist ID ein reserviertes Wort ? */
				for (i = 0; keywords[i].lx ; i++) {
					if (!strcmp (keywords[i].id, yylval.tstr.str))
						break;
				}
				if (keywords[i].lx) {   /* ID ist Schluesselwort */
					yylval.tnum.numline = line;
					return (keywords[i].lx);
				}
				else {  /* ID ist nutzerdefinierter Name */
					yylval.tstr.strline = line;
					return (T_IDENT);
				}
		}
		else if (isdigit(ch)) {
			/* Token ist Zahl -> Konvertierung */
			yylval.tnum.num = 0;
			while (isdigit(ch)) {
				yylval.tnum.num = 10*yylval.tnum.num + ch - '0';
				ch = input();
			}
			yylval.tnum.numline = line;
			return (T_NUMBER);
		}
		else if (ch ==  '"' || ch == '\'') {
		int scope_char = ch;

			/* Token ist String */
			for (i = 0; (ch = input()) != scope_char; i++)
				yylval.tstr.str[i] = ch;
			yylval.tstr.str[i] = '\0';
			ch = input();
			yylval.tstr.strline = line;
			return(T_STRING);
		}
		else if (ch == '/') {
			if ((ch = input()) == '*') {
				/* Token ist Kommentaranfang */
				for (;;) {
					while ((ch = input()) != '*') {
						if (ch == '\n')
							++line;
					}
					if ((ch = input()) == '/')
						break;
					else
						unput(ch);
				}
				ch = input();
				continue;
			}
			else if ('/' == ch) {
			// C++ style comment
				while ((ch = input()) != '\n') 
					;
				++line;

				ch = input();
				continue;
			}
			else {
				unput(ch);
				ch = '/';
			}
		}

		yylval.tnum.num = ch;
		ch = input();
		yylval.tnum.numline = line;
		return (yylval.tnum.num);
	}
}


/* Eingabe des naechsten Zeichens */

input()
{
	register int c;
	
	if (bp >= 0)
		c = pbstack[bp--];
	else {
		c = getc (schema);
		if (c >= 'A' && c <= 'Z')
			/* Grossbuchstaben -> Kleinbuchstaben */
			c = c + 'a' - 'A';
	}
	return (c);
}

/* Zeichen in Eingabe zurueckgeben */

void unput (c)
register int c;
{
	if (++bp > MAXSTACK) {
		fprintf (stderr, "%s(%d): error: Überlauf des Rückstellpuffers der Eingabe\n", fnin, line);
		exit (1);
	}
	else
		pbstack[bp] = c;
}


/* Parser Syntaxfehler */

void yyerror (s)
char *s;
{
	dderror (s,line);
}


/* Datendefinitionsfehler */

void dderror (s,ln)
char *s;
int ln;
{
	++tot_errs;
	fprintf (stderr, "%s(%d): error: %s\n", fnin, ln, s);
}


/* Schwerwiegender Datendefinitionsfehler: Abbruch */

void abort(s)
char *s;
{
	fprintf (stderr, "%s(%d): fatal error: %s\n", fnin, line, s);
	exit(1);
}

