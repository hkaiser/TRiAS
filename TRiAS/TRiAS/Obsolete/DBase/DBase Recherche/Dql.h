/* Header-File fuer report.y -- YACC-Stack-Definition u.a.      */
/* File: REPORT.H                                               */

#include <limits.h>

/* einige Konstantendefinitionen */
#define TRUE    1
#define FALSE   0
#define MAXPOS  SHRT_MAX

#define YYMAXDEPTH	150	// YACC -Stackgrî·e


/* Anzahl der signifikanten Zeichen eines Identifiers */
#define NAMELEN 32

// DefaultWerte ---------------------------------------------------------------
#define MAXSTRING       120     /* maximale Zeilenlaenge */
#define MAXVARS         100     /* Anzahl der internen Variablen */
#define MAXINPARS        20     /* max. Anzahl der Eingabezeilenfelder */
#define MAXSUBR          20     /* max. Anzahl von Prozeduren */

/* Tabelle der SchlÅsselworte */
typedef struct {
	short lx;		/* TokenNummer */
	char *id;		/* SchlÅsselwert */
} KEYWORD;
	
/* Tabelle der System-Variablen */
typedef struct {
        char *var_name;         /* Variablenname */
        short var_wert;           /* Wert */
} SYS_VAR;

/* Tabelle der Systemkonstanten */
typedef struct {
        char *const_name;
        short (*const_wert)(void);
} SYS_CONST;

/* Tabelle der Variablen */
typedef struct {
        char type;
        void *ptr;
} VARIABLE;

// externe Variablendeklarationen ---------------------------------------------

// extern int yylineno;            /* aktuelle Zeile in Script */
extern VARIABLE var_table[];    /* Variablentabelle */

/* Variablen fÅr Seiten- und Zeilenformatierung */
extern int Lines;       /* Anzahl der Druckzeilen einer Seite */
extern int AllLines;    /* physische LÑnge einer Seite */
extern int Columns;     /* Anzahl der Spalten einer Zeile */
extern int NewPage;     /* naechste Seitennummer */

extern int StartRPage;   /* erste auszugebende Seite */
extern int EndRPage;     /* letzte auszugebende Seite */
extern int StartRTuple;  /* erster auzugebender Datensatz */
extern int EndRTuple;    /* letzter auszugebender Datensatz */

extern int allow_tuple; /* Tuplenummer liegt in erlaubtem Bereich */
extern int was_allowed; /* Tuplenummer war einmal im erlaubten Bereich */

extern SYS_VAR system_var[];    	/* Systemvariablen */
extern SYS_CONST system_const[]; 	/* Systemkonstanten */

#define ActPage system_var[0].var_wert	/* AliasNames fÅr SystemVariablen */
#define ActLine system_var[1].var_wert
#define ActTuple system_var[2].var_wert
#define ActCol  system_var[3].var_wert

extern int NextPage;     /* naechste Seitennummer */

extern int m1val;        /* Zeilen bis einschlie·lich Headerzeile */
extern int m2val;        /* Freizeilen nach Headerzeile */
extern int m3val;        /* Freizeilen nach letzter Textzeile */
extern int m4val;        /* unteres Feld einschliesslich Fu·note */

extern char Header[];    /* Headerzeile */
extern char Footer[];    /* Fussnote */

extern char LineBegin[]; /* Text am Zeilenbeginn */
extern char LineEnd[];   /* Text am Zeilenende */
extern char OutLine[];	 /* eigentliche Informationszeile */

extern char *form_line;  /* Zeile, die formatiert wird */

/* Schleifenverarbeitung FOR_ALL */
extern long for_all_seek;
extern int for_all_flag;
extern int for_all_line;

/* Deklarations_Sektion */
extern int declaration;         /* TRUE waehrend Deklarationssektion */

// Unterprogrammstrukturen ----------------------------------------------------
typedef struct {
        long seek;	/* Anfangsseek der Subroutine */
        short line;	/* Anfangszeile der Subroutine */
        long ret_seek;  /* RÅcksprungseek */
        short ret_line;	/* RÅcksprungzeile */
} SUBROUTINE;

extern SUBROUTINE subroutines[];        /* Unterprogramme */
extern SUBROUTINE head;                 /* Kopfzeile */
extern SUBROUTINE foot;                 /* Fusszeile */

// Funktionsprototypen --------------------------------------------------------
// REPRTSYS.C
short  Year(void);
short  Month(void);
short  Day(void);
short  W_day(void);
short  Y_day(void);
short  Hour(void);
short  Minute(void);
short  Second(void);
// REPRTIO.C
void  out_string(char  *cptr);
int  new_page(void);
int  new_line(short  num);
int  skip(int  num);
int  put_head(void);
int  put_foot(void);
// DQLLX.C
int  yylex(void);
long  yytell(int  which);
static void  seek(void);
void  yyseek(long  new_seek);
void  yyerror(const char  *s);
void  r_error(char  *s,int  ln);
void  r_abort(char  *s);
void  comment(char  *mat);
short ActLineNumber (void);
short ActColumnNumber (void);
int  yylook(void);
int  yyback(int  *p,int  m);
int  yyinput(void);
void  yyoutput(int  c);
void  yyunput(int  c);
int  yywrap(void);
// INPUT.C
int  _yylexin(void);
int  lexin(VARIABLE *infeld);
int  _yylook(void);
int  _yyback(int  *p,int  m);
int  _yyinput(void);
void  _yyoutput(int  c);
void  _yyunput(int  c);
int  _yywrap(void);
// DQL.C
int  call(SUBROUTINE *subr);
int  yyparse(void);

//  Recherche-Status
enum RSToDo { RSUnknown, RSClassify, RSObjList, };
enum RMode { RMUnknown, RMFile, RMBuffer, RMClipboard, };
