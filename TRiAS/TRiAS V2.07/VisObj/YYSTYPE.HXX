// Diese Klasse ist nichts weiter als ein verstecktes faules kopieren,
// bei dem darauf geachtet wird, daá alle dynamisch erzeugten Objekte
// ordentlich freigegeben werden.

#if !defined(_YYSTYPE_HXX)
#define _YYSTYPE_HXX

class YYSTYPE {
public:
	enum YYSType { 	YYUnknown, 
			YYLong, 	// LongZahl 
			YYString,	// ZeichenKette
	};

private:
	void *m_pItem;		// eigentlicher Wert
	short m_iLineNum;	// ZeilenNummer
	YYSType m_enYYSType;	// AKTUELLER StackTyp

	void TypeClash (YYSType);
	void Delete (void);	// angehängtes Objekt löschen

public:
// Konstruktor
		YYSTYPE (void);			// Default Konstruktor
		YYSTYPE (void *pNew, YYSType T = YYUnknown, short LineNum = 0);
						// StandardKonstruktor
		YYSTYPE (YYSTYPE &);		// CopyKonstruktor

// Zuweisungsoperator
	YYSTYPE &operator= (YYSTYPE &);

	char *YYSTypeStr (YYSType);

// überprüfen, ob Token existiert+
	bool hasToken (void) { return m_pItem != NULL; }

// Zugriffsoperatoren auf konkrete DatenTypen bzw. Strukturelemente
// des >> konkreten << YACC - Stacks müssen hier definiert werden
	short &LineNum (void) { return m_iLineNum; }	// ZeilenNummer

// Zugriffsoperatoren auf echte Werte, nicht Pointer
	long &LongToken (void);
	char *StringToken (void);

// Destruktor
		~YYSTYPE (void);	
};


#endif // _YYSTYPE_HXX
