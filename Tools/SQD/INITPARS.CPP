// Initialisierung und Abschluss des Parserlaufes
// File: INITPARS.CXX

#include "stdafx.h"

#include "gdb.h"
#define YYMAXDEPTH 150

#include "dgeoobj.hxx"
#include "yystype.hxx"
#include "hashtabs.hxx"

extern YYSTYPE *yyv;		// YACC - Stack
extern YYSTYPE *pyyval;		// aktualles YACC - Token
extern YYSTYPE *pyylval;	// aktuelles LEX - Token

GDBElementTab *pGDBElemente;

int InitYYParse (void) {
int Result;

// YACC - Stack anlegen
	yyv = new YYSTYPE [YYMAXDEPTH];
	pyyval = new YYSTYPE;
	pyylval = new YYSTYPE;
	if (yyv == NULL || pyyval == NULL || pyylval == NULL) {
	// wieder aufrÑumen
		if (yyv) delete [] yyv;
		if (pyyval) delete pyyval;
		if (pyylval) delete pyylval;
	// Fehlermeldung und raus
		r_abort ("Kein Speicherplatz.");
	}
// HashTabelle anlegen
	pGDBElemente = new GDBElementTab ();
	if (pGDBElemente == NULL) {
		delete [] yyv;
		delete pyyval;
		delete pyylval;
		r_abort ("Kein Speicherplatz.");
	}

	Result = yyparse ();

// Speicher wieder freigeben
//	delete pGDBElemente;
	delete pyylval;			// diese Pointer mÅssen gÅltig sein
	delete pyyval;			// sonst wÑren wir nicht hier
//	delete [] yyv;

return Result;
}

