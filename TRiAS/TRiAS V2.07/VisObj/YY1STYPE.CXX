// Memberfunktionen fuer die YACC - Stackklasse 
// File: YYSTYPE.CXX

#include "visobjp.hxx"

#include "visobj.h"
#include "yy2stype.hxx"


int yy2error (const char *, ...);

// Konstruktoren der BasisKlasse ----------------------------------------------
YYSTYPE :: YYSTYPE (void) 
{
	m_pItem = NULL;
	m_iLineNum = 0;
	m_enYYSType = YYUnknown;
}

YYSTYPE :: YYSTYPE (void *pNew, YYSType T, short LineNum) 
{
	m_pItem = pNew; 
	m_iLineNum = LineNum;
	m_enYYSType = T;
}

YYSTYPE :: YYSTYPE (YYSTYPE &toCopy) 
{
// Objekt umsetzen
	m_pItem = toCopy.m_pItem;
	m_iLineNum = toCopy.m_iLineNum;
	m_enYYSType = toCopy.m_enYYSType;

// Doppelpointer auf ein und das selbe Objekt verhindern
	toCopy.m_pItem = NULL;
	toCopy.m_iLineNum = -1;
	toCopy.m_enYYSType = YYUnknown;
}

// Destruktor -----------------------------------------------------------------
YYSTYPE :: ~YYSTYPE (void) 
{
	if (m_pItem != NULL) Delete ();
}

// Zuweisungsoperator ---------------------------------------------------------
YYSTYPE &YYSTYPE :: operator = (YYSTYPE &toAssign) 
{
// alten Wert beseitigen
	if (m_pItem != NULL) 
		Delete ();	// angehängte DatenStruktur freigeben

// neuen Wert setzen
	m_pItem = toAssign.m_pItem;
	m_iLineNum = toAssign.m_iLineNum;
	m_enYYSType = toAssign.m_enYYSType;

// DoppelPointer auf ein und das selbe Objekt verhindern
	toAssign.m_pItem = NULL;
	toAssign.m_enYYSType = YYUnknown;
	toAssign.m_iLineNum = -1;

return *this;
}

// Konvertierungsoperatoren ---------------------------------------------------
long &YYSTYPE :: LongToken (void) 
{
	if (m_pItem) {
		if (m_enYYSType == YYLong) return *(long *)m_pItem;
		else {
			Delete ();
			TypeClash (YYLong);
		}
	}
	m_pItem = NULL;
	m_enYYSType = YYLong;

return *(long *)m_pItem;
}

char * YYSTYPE :: StringToken (void) 
{
	if (m_pItem) {
		if (m_enYYSType == YYString) {
		char *cptr = new char [strlen((const char *)m_pItem)+1];

			if (cptr) strcpy (cptr, (const char *)m_pItem);
			return cptr;
		} else {
			Delete ();
			TypeClash (YYString);
		}
	}
	m_pItem = NULL;		// neue Variable anlegen
	m_enYYSType = YYString;

return NULL;
}


// ----------------------------------------------------------------------------
// Fehlermeldung ausgeben
char *YYSTYPE :: YYSTypeStr (YYSType T) 
{
	switch (T) {
	case YYLong:		return "Long";
	case YYString:		return "String";
	case YYUnknown:
	default:		return "Unbekannt";
	}
}

void YYSTYPE :: TypeClash (YYSType ordered) 
{
char chOutString[50];

	wsprintf (chOutString, ResString (ResID (IDS_TYPECLASH, &pTE -> RF()), 50), 
		  m_iLineNum, YYSTypeStr (m_enYYSType), YYSTypeStr (ordered));
	yy2error (chOutString, m_iLineNum);
}

void YYSTYPE :: Delete (void) 
{
	switch (m_enYYSType) {
	case YYLong:		// ohne Destruktor freigeben
	case YYString:
		delete m_pItem; 
		m_pItem = NULL;
		break;

	case YYUnknown:
	default:
		break;
	}
}

