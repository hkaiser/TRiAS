// Spezielle Klasse fuer YACC - Stack -----------------------------------------
// File: YY2STYPE.HXX

#if !defined(_YY2STYPE_HXX)
#define _YY2STYPE_HXX

#include "yystype.hxx"

#undef YYSTACK
// setzen des YACCStacks (entspricht $$ = *e)
// e ist ein Pointer auf das neue Element, t ist der Typ des StackElementes
#define YYSTACK(e,t)	\
	{ YYSTYPE tmpY ((e), YYSTYPE::##t, yy2pvt[-1].LineNum()); yy2pv[1] = tmpY; }

#undef LEXSTACK
// setzen des LEXStatcks (entspricht yylval = *e)
// e ist ein Pointer auf das neue Element, t ist der Typ des StackElementes
#define LEXSTACK(e,t,l)	\
	{ YYSTYPE tmpY ((e), YYSTYPE::##t, (l)); *pyy2lval = tmpY; }

// eigentliche ParserRoutinen -------------------------------------------------
bool InitYY2Parse (void);
int yy2parse (void);

// LEXER-Deklarationen --------------------------------------------------------
int  yy2lex(void);
int  yy2look(void);
int  yy2back(int  *p,int  m);
int  yy2input(void);
void  yy2output(int  c);
void  yy2unput(int  c);
int  yy2wrap(void);

extern YYSTYPE *pyy2lval;	// aktuelles LEX-Token

#endif // _YY2STYPE_HXX
