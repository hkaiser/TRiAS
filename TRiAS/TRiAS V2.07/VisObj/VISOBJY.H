// HeaderDatei fuer VISOBJY.Y
// File: VISOBJY.H

#define STRINGLEN	20

// Yacc-Stacktypen ------------------------------------------------------------
typedef struct {	/* String-Token */
	long str_line;
	char string[STRINGLEN+1];
} STRING_TOKEN;

typedef struct {	/* Integer-Token */
	long num_line;
	long intnum;
} NUMBER_TOKEN;

// Funktionsdeklarationen -----------------------------------------------------
// short yy1parse (long lGlobONr, VisInfo *& pGlobVI);
int  yy1lex(void);
int  yy1look(void);
int  yy1back(int  *p,int  m);
int  yy1input(void);
void  yy1output(int  c);
void  yy1unput(int  c);
int  yy1wrap(void);

extern char *pActChar;	// LEX-EingabeBuffer
extern char *pBuffEnd;
