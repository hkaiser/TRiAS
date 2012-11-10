// Spezielle Klasse fuer YACC - Stack
// File: YYSTYPE.HXX

#if !defined(_YYSTYPE_HXX)
#define _YYSTYPE_HXX

// TypEnumeration-Variablen fr Ausgabeger„t und Ausgabeform
enum DeviceType { DTUnknown, DTWindow, DTPrinter, };
enum OutputType { 
		OTUnknown = 0, 
		OTObjList = RSObjList, 
		OTClassification = RSClassify, 
		OTSheet = 10, 
		OTGraphics = 11, 
	};

// Diese Klasse ist nichts weiter als ein verstecktes faules kopieren,
// bei dem darauf geachtet wird, daá alle dynamisch erzeugten Objekte
// ordentlich freigegeben werden.

class YYSTYPE {
public:
	enum YYSType { 	YYUnknown, 
			YYLong, 	// LongZahl 
			YYDouble, 	// DoubleZahl
			YYString,	// ZeichenKette
			YYDBase,	// DBaseExpression (ebenfalls StringToken)
			YYSysVar,	// SystemVariable des ReportGenerators
			YYObjContainer,	// FensterRechteck
			YYDevice,	// Ausgabeger„et
			YYOutput,	// Ausgabeform
			YYDBaseKey,	// DBaseSchlssel
			YYGeoDBKey,	// GeoDBSchlssel
			YYMasterTerm,	// RelationsBeschreibung
			YYSlaveTerm,	// dto.
	};

private:
	void *_pItem;		// eigentlicher Wert
	short _LineNum;		// ZeilenNummer
	YYSType _YYSType;	// AKTUELLER StackTyp

	void TypeClash (YYSType);
	void Delete (void);	// Objekt l”schen
	char *YYStypeStr (YYSType);

public:
// Konstruktor
		YYSTYPE (void);			// Default Konstruktor
		YYSTYPE (void *pNew, YYSType T = YYUnknown, short LineNum = 0);
						// StandardKonstruktor
		YYSTYPE (YYSTYPE &);		// CopyKonstruktor

// Zuweisungsoperator
	YYSTYPE &operator= (YYSTYPE &);

// Zugriffsoperatoren auf konkrete DatenTypen bzw. Strukturelemente
// des >> konkreten << YACC - Stacks mssen hier definiert werden
	short &LineNum (void) { return _LineNum; }	// ZeilenNummer

// Zugriffsoperatoren auf echte Werte, nicht Pointer
	double &FloatToken (void);
	long &LongToken (void);
	char * StringToken (void);
	ObjContainer &ObjContToken (void);
	DeviceType &DevTypeToken (void);
	OutputType &OutTypeToken (void);
	DBaseKey &DBaseKeyToken (void);
	GeoDBKey &GeoDBKeyToken (void);
	MasterTerm &MasterTermToken (void);
	SlaveTerm &SlaveTermToken (void);
//	KeyFilter &KeyFilterToken (void);

// Destruktor
		~YYSTYPE (void);	
};

#if !defined(NULL)
#define NULL	0
#endif

// setzen des YACCStacks (entspricht $$ = *e)
// e ist ein Pointer auf das neue Element, t ist der Typ des StackElementes
#define YYSTACK(e,t)	\
	{ YYSTYPE tmpY ((e), YYSTYPE::##t, yypvt[-1].LineNum()); yypv[1] = tmpY; }

#endif // _YYSTYPE_HXX

