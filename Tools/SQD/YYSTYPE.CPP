// Memberfunktionen fuer die YACC - Stackklasse 
// File: YYSTYPE.CXX

#include "stdafx.h"

#include "gdb.h"

#include "dgeoobj.hxx"
#include "yystype.hxx"

// Konstruktoren der BasisKlasse ----------------------------------------------
YYSTYPE :: YYSTYPE (void) {

	_pItem = NULL;
	_LineNum = 0;
	_YYSType = YYUnknown;
}

YYSTYPE :: YYSTYPE (void *pNew, YYSType T, short LineNum) {

	_pItem = pNew; 
	_LineNum = LineNum;
	_YYSType = T;
}

YYSTYPE :: YYSTYPE (YYSTYPE &toCopy) {
// Objekt umsetzen
	_pItem = toCopy._pItem;
	_LineNum = toCopy._LineNum;
	_YYSType = toCopy._YYSType;

// Doppelpointer auf ein und das selbe Objekt verhindern
	toCopy._pItem = NULL;
	toCopy._YYSType = YYUnknown;
	toCopy._LineNum = -1;
}

// Destruktor -----------------------------------------------------------------
YYSTYPE :: ~YYSTYPE (void) {

	if (_pItem != NULL) {
		Delete ();
		_pItem = NULL;
	}
}

// Zuweisungsoperator ---------------------------------------------------------
YYSTYPE &YYSTYPE :: operator = (YYSTYPE &toAssign) {

// alten Wert beseitigen
	if (_pItem != NULL) 
		Delete ();	// angeh„ngte DatenStruktur freigeben

// neuen Wert setzen
	_pItem = toAssign._pItem;
	_LineNum = toAssign._LineNum;
	_YYSType = toAssign._YYSType;

// DoppelPointer auf ein und das selbe Objekt verhindern
	toAssign._pItem = NULL;
	toAssign._YYSType = YYUnknown;
	toAssign._LineNum = -1;

return *this;
}

// Konvertierungsoperatoren ---------------------------------------------------
double &YYSTYPE :: FloatToken (void) {

	if (_pItem != NULL) {
		if (_YYSType == YYDouble) return *(double *)_pItem;	// alles ok
		else {
			Delete ();		// neues Objekt da TypeClash
			TypeClash (YYDouble);
		}
	}
	_pItem = NULL;	// neue Variable anlegen
	_YYSType = YYDouble;

return *(double *)_pItem;
}


long &YYSTYPE :: LongToken (void) {

	if (_pItem) {
		if (_YYSType == YYLong) return *(long *)_pItem;
		else {
			Delete ();
			TypeClash (YYLong);
		}
	}
	_pItem = NULL;
	_YYSType = YYLong;

return *(long *)_pItem;
}

char * YYSTYPE :: StringToken (void) {

	if (_pItem) {
		if (_YYSType == YYString) {
		char *cptr = new char [strlen((const char *)_pItem)+1];

			if (cptr) 
				strcpy (cptr, (const char *)_pItem);
			return cptr;
		} else {
			Delete ();
			TypeClash (YYString);
		}
	}
	_pItem = NULL;		// neue Variable anlegen
	_YYSType = YYString;

return NULL;
}


// weitere, benutzerdefinierte YYStackKlassen ---------------------------------
DGeoObj &YYSTYPE :: DGeoObjToken (void) {

	if (_pItem) {
		if (_YYSType == YYDPunkt || 
		    _YYSType == YYDLinie ||
		    _YYSType == YYDFlaeche ||
		    _YYSType == YYDText ||
		    _YYSType == YYDSymbol) 
			return *(DGeoObj *)_pItem;
		else {
			Delete ();
			TypeClash (YYDGeoObj);
		}
	}
	_pItem = NULL;		// neue Variable anlegen
	_YYSType = YYDGeoObj;

return *(DGeoObj *)_pItem;
}

DSymbol &YYSTYPE :: DSymbolToken (void) {

	if (_pItem) {
		if (_YYSType == YYDSymbol) 
			return *(DSymbol *)_pItem;
		else {
			Delete ();
			TypeClash (YYDSymbol);
		}
	}
	_pItem = NULL;		// neue Variable anlegen
	_YYSType = YYDSymbol;

return *(DSymbol *)_pItem;
}


DPunkt &YYSTYPE :: DPunktToken (void) {

	if (_pItem) {
		if (_YYSType == YYDPunkt) 
			return *(DPunkt *)_pItem;
		else {
			Delete ();
			TypeClash (YYDPunkt);
		}
	}
	_pItem = NULL;		// neue Variable anlegen
	_YYSType = YYDPunkt;

return *(DPunkt *)_pItem;
}

DLinie &YYSTYPE :: DLinieToken (void) {

	if (_pItem) {
		if (_YYSType == YYDLinie) 
			return *(DLinie *)_pItem;
		else {
			Delete ();
			TypeClash (YYDLinie);
		}
	}
	_pItem = NULL;		// neue Variable anlegen
	_YYSType = YYDLinie;

return *(DLinie *)_pItem;
}

DFlaeche &YYSTYPE :: DFlaecheToken (void) {

	if (_pItem) {
		if (_YYSType == YYDFlaeche) 
			return *(DFlaeche *)_pItem;
		else {
			Delete ();
			TypeClash (YYDFlaeche);
		}
	}
	_pItem = NULL;		// neue Variable anlegen
	_YYSType = YYDFlaeche;

return *(DFlaeche *)_pItem;
}

DText &YYSTYPE :: DTextToken (void) {

	if (_pItem) {
		if (_YYSType == YYDText) 
			return *(DText *)_pItem;
		else {
			Delete ();
			TypeClash (YYDText);
		}
	}
	_pItem = NULL;		// neue Variable anlegen
	_YYSType = YYDText;

return *(DText *)_pItem;
}


// Stack-Typ, der SICAD-Eigenschaften eines Objektes enth„lt
DParam &YYSTYPE :: DParamToken (void) {

	if (_pItem) {
		if (_YYSType == YYDParams) 
			return *(DParam *)_pItem;
		else {
			Delete ();
			TypeClash (YYDParams);
		}
	}
	_pItem = NULL;
	_YYSType = YYDParams;

return *(DParam *)_pItem;
}

// ----------------------------------------------------------------------------
// Fehlermeldung ausgeben
char *YYSTYPE :: YYSTypeStr (YYSType T) {

	switch (T) {
	case YYLong:		return "Long";
	case YYDouble:		return "Double";
	case YYString:		return "String";
	case YYDGeoObj:		return "DGeoObj";
	case YYDPunkt:		return "DPunkt";
	case YYDLinie:		return "DLinie";
	case YYDFlaeche:	return "DFl„che";
	case YYDText:		return "DText";
	case YYDSymbol:		return "DSymbol";
	case YYDParams:		return "DParam";
	case YYUnknown:
	default:		return "Unbekannt";
	}
}

void YYSTYPE :: TypeClash (YYSType ordered) {
char OutString[50];

	sprintf (OutString, "TypeClash: %s -> %s.\n", YYSTypeStr (_YYSType), 
						     YYSTypeStr (ordered));
	r_error (OutString, _LineNum);
}

void YYSTYPE :: Delete (void) {

	switch (_YYSType) {
	case YYLong:		// ohne Destruktor freigeben
	case YYDouble:
	case YYString:
	case YYDParams:	
		delete _pItem; 
		break;

	case YYDPunkt:		// virtuellen Destruktor rufen
	case YYDLinie:
	case YYDFlaeche:
	case YYDText:
	case YYDSymbol:
	case YYDGeoObj:
		delete (DGeoObj *)_pItem;
		break;

	case YYUnknown:
	default:
		break;
	}
}

