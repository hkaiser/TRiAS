// Spezielle Klasse fuer YACC - Stack -----------------------------------------
// File: YY1STYPE.HXX

#if !defined(_YY1STYPE_HXX)
#define _YY1STYPE_HXX

#include "yystype.hxx"

#define STRINGLEN	20

extern char *pActChar;	// LEX-EingabeBuffer
extern char *pBuffEnd;

#undef YYSTACK
// setzen des YACCStacks (entspricht $$ = *e)
// e ist ein Pointer auf das neue Element, t ist der Typ des StackElementes
#define YYSTACK(e,t)	\
	{ YYSTYPE tmpY ((e), YYSTYPE::##t, yy1pvt[-1].LineNum()); yy1pv[1] = tmpY; }

#undef LEXSTACK
// setzen des LEXStatcks (entspricht yylval = *e)
// e ist ein Pointer auf das neue Element, t ist der Typ des StackElementes
#define LEXSTACK(e,t,l)	\
	{ YYSTYPE tmpY ((e), YYSTYPE::##t, (l)); *pyy1lval = tmpY; }

// eigentliche ParserRoutinen -------------------------------------------------
bool InitYY1Parse (void);

// LEXER-Deklarationen --------------------------------------------------------
int  yy1lex(void);
int  yy1look(void);
int  yy1back(int  *p,int  m);
int  yy1input(void);
void  yy1output(int  c);
void  yy1unput(int  c);
int  yy1wrap(void);

extern YYSTYPE *pyy1lval;	// aktuelles LEX-Token

#endif // _YY1STYPE_HXX
