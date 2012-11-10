// Initialisierung und Abschluss des Parserlaufes
// File: INITPARS.CXX

#include "visobjp.hxx"

#include <strdupx.hxx>

#define YYMAXDEPTH 150

#include "yy1stype.hxx"
#include "yy2stype.hxx"

#include "uidobj.hxx"
#include "uidobj.inl"

extern YYSTYPE *yy1v;		// YACC - Stack
extern YYSTYPE *pyy1val;	// aktualles YACC - Token
extern YYSTYPE *pyy1lval;	// aktuelles LEX - Token

extern YYSTYPE *yy2v;		// YACC - Stack
extern YYSTYPE *pyy2val;	// aktualles YACC - Token
extern YYSTYPE *pyy2lval;	// aktuelles LEX - Token

extern int yy1lineno;		// ZeilenNummer

extern CUIdentObjects *g_pUIObjs;	// Baum mit UIdents <--> (lONr's, iOType's)

void yy1error (enum ErrCode, ...);
void yy2error (enum ErrCode, ...);
void InitYY2Vars (void);

bool InitYY1Parse (void) 
{
// YACC - Stack anlegen
	yy1v = new YYSTYPE [YYMAXDEPTH];
	pyy1val = new YYSTYPE;
	pyy1lval = new YYSTYPE;
	if (yy1v == NULL || pyy1val == NULL || pyy1lval == NULL) {
	// wieder aufräumen
		if (yy1v) delete [YYMAXDEPTH] yy1v;
		if (pyy1val) delete pyy1val;
		if (pyy1lval) delete pyy1lval;

	// Fehlermeldung und raus
		yy1error (EC_NOMEMORY);
		return false;
	}
	yy1lineno = 0;
		
return true;
}


void EndYY1Parse (void)
{
// Speicher wieder freigeben
	if (yy1v) delete [YYMAXDEPTH] yy1v;
	if (pyy1val) delete pyy1val;
	if (pyy1lval) delete pyy1lval;
}


bool InitYY2Parse (void) 
{
int iResult;

// YACC - Stack anlegen
	yy2v = new YYSTYPE [YYMAXDEPTH];
	pyy2val = new YYSTYPE;
	pyy2lval = new YYSTYPE;
	g_pUIObjs = new CUIdentObjects;
	if (yy2v == NULL || pyy2val == NULL || pyy2lval == NULL || g_pUIObjs == NULL) 
	{
	// wieder aufräumen
		if (yy2v) delete [YYMAXDEPTH] yy2v;
		if (pyy2val) delete pyy2val;
		if (pyy2lval) delete pyy2lval;
        	if (g_pUIObjs) delete g_pUIObjs;
        	
	// Fehlermeldung und raus
		yy2error (EC_NOMEMORY);
	}

	InitYY2Vars();
	iResult = yy2parse ();

// Speicher wieder freigeben
	delete g_pUIObjs;			// UIdentBaum freigeben
	delete pyy2lval;		// diese Pointer müssen gültig sein
	delete pyy2val;			// sonst wären wir nicht hier
	delete [YYMAXDEPTH] yy2v;

return iResult;
}

