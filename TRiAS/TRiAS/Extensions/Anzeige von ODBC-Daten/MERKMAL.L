%{       
/* 
Datei: Merkmal.l

Das Modul bestimmt den Typ des im Puffer übergebenen Merkmals.

Erarbeitet: J. Benkenstein				Stand vom 10.10.1995 
*/ 
#if defined(_MSC_VER)
#pragma warning (disable: 4102)		// unreferenced label
#endif

// 	lokale Variablen
static char *pFirstChar = NULL;		// zeigt auf 1. Zeichen des Merkmals

// Neudefinition der PCLEX - I/O Routinen für WINIO
#undef YY_OUTPUT
#undef YY_INPUT
#undef ECHO
#undef YY_FATAL_ERROR

#define ECHO
#define YY_OUTPUT
#define YY_FATAL_ERROR(msg) { DEX_Error (RC_OdbcExtLex, EC_SYSERROR); }
#define YY_INPUT(buf,result,max_size) \
	if (!pFirstChar || !*pFirstChar) \
		result = YY_NULL; \
	else if (lstrcpyn (buf, pFirstChar, min (max_size, strlen (pFirstChar)+1))) \
	{ \
		result = strlen (buf); \
		pFirstChar += result; \
	} \
	else \
	    YY_FATAL_ERROR(" ");

%}

ws 				[ \t]+
sign            [+-]
dezimal         [0-9]
integer         ({sign}?{dezimal}+)
real            ({integer}"."{dezimal}+)
realexp         ({real}"E"{integer})
date  			([1-2][0-9][0-9][0-9]"-"[0-2]?[0-9]"-"[0-3]?[0-9])
time			([0-2]?[0-9]":"[0-5]?[0-9]":"[0-5]?[0-9])
fraction 		("."[0-9]+)
time_stamp 		({date}{ws}{time}{fraction}?)

%%
{ws}			;
{time_stamp}	{ return SQL_TIMESTAMP;}	
{date}			{ return SQL_DATE;}	
{time}			{ return SQL_TIME;}	
{integer}	 	{ return SQL_INTEGER; }
{real} |
{realexp}		{ return SQL_DOUBLE; }
.				{ return SQL_CHAR; }
%%

int yylexr (char *pVal)
{
//	prüfe Parameter
	if (!pVal || !*pVal)
		return 0;
	
	pFirstChar = pVal;		// Lex-Puffer setzen
	yy_init = 1;			// Lex immer neu init.
	
	return yylex ();		// Lex rufen	
}





