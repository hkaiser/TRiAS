// Spezielle Klasse fuer YACC - Stack
// File: YYSTYPE.HXX

#if !defined(_YYSTYPE_HXX)
#define _YYSTYPE_HXX

// TypEnumeration-Variablen fr Ausgabeger„t und Ausgabeform
enum DeviceType { DTUnknown, DTWindow, DTPrinter, };
enum OutputType { OTUnknown, OTSheet, OTGraphics, OTObjList, };

// Diese Klasse ist nichts weiter als ein verstecktes faules kopieren,
// bei dem darauf geachtet wird, daá alle dynamisch erzeugten Objekte
// ordentlich freigegeben werden.

class YYSTYPE {
public:
	enum YYSType { 	YYUnknown, 
			YYLong, 	// LongZahl 
			YYDouble, 	// DoubleZahl
			YYString,	// ZeichenKette
		// benutzdefinierte Typen
			YYDGeoObj,
			YYDPunkt,	// Double-KoordinatenWert
			YYDLinie,
			YYDFlaeche,
			YYDText,
			YYDSymbol,
			YYDParams,	// SICAD-Eigenschaften
	};

private:
	void *_pItem;		// eigentlicher Wert
	short _LineNum;		// ZeilenNummer
	YYSType _YYSType;	// AKTUELLER StackTyp

	void TypeClash (YYSType);
	void Delete (void);	// angeh„ngtes Objekt l”schen

public:
// Konstruktor
		YYSTYPE (void);			// Default Konstruktor
		YYSTYPE (void *pNew, YYSType T = YYUnknown, short LineNum = 0);
						// StandardKonstruktor
		YYSTYPE (YYSTYPE &);		// CopyKonstruktor

// Zuweisungsoperator
	YYSTYPE &operator= (YYSTYPE &);

	char *YYSTypeStr (YYSType);

// berprfen, ob Token existiert+
	Bool hasToken (void) { return _pItem != NULL; }

// Zugriffsoperatoren auf konkrete DatenTypen bzw. Strukturelemente
// des >> konkreten << YACC - Stacks mssen hier definiert werden
	short &LineNum (void) { return _LineNum; }	// ZeilenNummer

// Zugriffsoperatoren auf echte Werte, nicht Pointer
	double &FloatToken (void);
	long &LongToken (void);
	char *StringToken (void);

	DGeoObj &DGeoObjToken (void);
	DPunkt &DPunktToken (void);
	DLinie &DLinieToken (void);
	DFlaeche &DFlaecheToken (void);
	DText &DTextToken (void);
	DSymbol &DSymbolToken (void);

	DParam &DParamToken (void);

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
