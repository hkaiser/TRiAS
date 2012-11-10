// Memberfunktionen fuer die YACC - Stackklasse 
// File: YYSTYPE.CXX

#include "pheader.h"

#include "yystype.htp"
#include <commonvu.hxx>
#include <containr.hxx>

extern "C" {
	#include "dql.h"
}

#include <ristypes.hxx>		 // Koord
#include <geo_obj.hxx>

#include <dbasekey.hxx>
#include <relation.hxx>
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
				Delete ();

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
				if (_YYSType == YYDouble) return *(double *)_pItem;	 // alles ok
				else {
						Delete ();			  // neues Objekt da TypeClash
						TypeClash (YYDouble);
				}
		}
		_pItem = NULL;  // neue Variable anlegen
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
				if (_YYSType == YYString || _YYSType == YYDBase) {
				char *cptr = new char [lstrlen((const char *)_pItem)+1];

						if (cptr) 
								lstrcpy (cptr, (const char *)_pItem);
						return cptr;
				} else {
						Delete ();
						TypeClash (YYString);
				}
		}
		_pItem = NULL;		  // neue Variable anlegen
		_YYSType = YYString;

return NULL;
}


ObjContainer &YYSTYPE :: ObjContToken (void) {
		if (_pItem) {
				if (_YYSType == YYObjContainer) return *(ObjContainer *)_pItem;
				else {
						Delete();
						TypeClash(YYObjContainer);
				}
		}
		_pItem = NULL;  // neue Variable anlegen
		_YYSType = YYObjContainer;

return *(ObjContainer *)_pItem;
}

DeviceType &YYSTYPE :: DevTypeToken (void) {
		if (_pItem) {
				if (_YYSType == YYDevice) return *(DeviceType *)_pItem;
				else {
						Delete();
						TypeClash (YYDevice);
				}
		}
		_pItem = new DeviceType (DTUnknown);	// neue Variable anlegen
		_YYSType = YYDevice;

return *(DeviceType *)_pItem;
}

OutputType &YYSTYPE :: OutTypeToken (void) {
		if (_pItem) {
				if (_YYSType == YYOutput) return *(OutputType *)_pItem;
				else {
						Delete();
						TypeClash (YYOutput);
				}
		}
		_pItem = new OutputType (OTUnknown);	// neue Variable anlegen
		_YYSType = YYOutput;

return *(OutputType *)_pItem;
}

DBaseKey &YYSTYPE :: DBaseKeyToken (void) {
		if (_pItem) {
				if (_YYSType == YYDBaseKey) return *(DBaseKey *)_pItem;
				else {
						Delete();
						TypeClash (YYDBaseKey);
				}
		}
		_pItem = NULL;  // neue Variable anlegen
		_YYSType = YYDBaseKey;

return *(DBaseKey *)_pItem;
}

GeoDBKey &YYSTYPE :: GeoDBKeyToken (void) {
		if (_pItem) {
				if (_YYSType == YYGeoDBKey) return *(GeoDBKey *)_pItem;
				else {
						Delete();
						TypeClash (YYGeoDBKey);
				}
		}
		_pItem = NULL;  // neue Variable anlegen
		_YYSType = YYGeoDBKey;

return *(GeoDBKey *)_pItem;
}

MasterTerm &YYSTYPE :: MasterTermToken (void) {
		if (_pItem) {
				if (_YYSType == YYMasterTerm) return *(MasterTerm *)_pItem;
				else {
						Delete();
						TypeClash (YYMasterTerm);
				}
		}
		_pItem = NULL;  // neue Variable anlegen
		_YYSType = YYMasterTerm;

return *(MasterTerm *)_pItem;
}

SlaveTerm &YYSTYPE :: SlaveTermToken (void) {
		if (_pItem) {
				if (_YYSType == YYSlaveTerm) return *(SlaveTerm *)_pItem;
				else {
						Delete();
						TypeClash (YYSlaveTerm);
				}
		}
		_pItem = NULL;  // neue Variable anlegen
		_YYSType = YYSlaveTerm;

return *(SlaveTerm *)_pItem;
}

#if 0
KeyFilter &YYSTYPE :: KeyFilterToken (void) {
		if (_pItem) {
				if (_YYSType == YYKeyFilter) return *(KeyFilter *)_pItem;
				else {
						Delete();
						TypeClash (YYKeyFilter);
				}
		}
		_pItem = NULL;  // neue Variable anlegen
		_YYSType = YYKeyFilter;

return *(KeyFilter *)_pItem;
}
#endif

// ----------------------------------------------------------------------------
// Fehlermeldung ausgeben
char *YYSTYPE :: YYStypeStr (YYSType T) {
		switch (T) {
		case YYLong:			return "Long";
		case YYDouble:		  return "Double";
		case YYString:		  return "String";
		case YYDBase:		   return "DBaseExpression";
		case YYSysVar:		  return "SysVariable";
		case YYObjContainer:	return "ObjContainer";
		case YYDevice:		  return "Device";
		case YYOutput:		  return "OutputMode";
		case YYDBaseKey:		return "DBaseKey";
		case YYGeoDBKey:		return "GeoDBKey";
		case YYMasterTerm:	  return "MasterTerm";
		case YYSlaveTerm:	   return "SlaveTerm";
		case YYUnknown:
		default:				return "Unbekannt";
		}
}

void YYSTYPE :: TypeClash (YYSType ordered) {
char OutString[50];
		wsprintf (OutString, "TypeClash: %s -> %s.\n", YYStypeStr (_YYSType), 
													   YYStypeStr (ordered));
		r_error (OutString, _LineNum);
}

void YYSTYPE :: Delete (void) {

		if (_pItem) switch (_YYSType) {
		case YYLong:			// ohne Destruktor freigeben
		case YYDouble:
		case YYString:
		case YYOutput:
		case YYDevice:
		case YYSysVar:
		case YYDBase:
		default:
				delete _pItem; 
				break;

		case YYObjContainer:
				delete (ObjContainer *)_pItem;
				break;

		case YYDBaseKey:
				delete (DBaseKey *)_pItem;
				break;

		case YYGeoDBKey:
				delete (GeoDBKey *)_pItem;
				break;

		case YYMasterTerm:
				delete (MasterTerm *)_pItem;
				break;

		case YYSlaveTerm:
				delete (SlaveTerm *)_pItem;
				break;

		case YYUnknown:
				break;
		}
		_pItem = NULL;
}
