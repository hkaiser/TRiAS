// GeometrieObjekte, die beim Einlesen der SICAD - Daten entstehen ------------
// File: DGEOOBJ.HXX

#if !defined(_DGEOOBJ_HXX)
#define _DGEOOBJ_HXX

enum AppMode {
	AM_NoSense = 0,
	AM_NoReverse = 1,
	AM_Reverse = 2,
};	// Mode, in dem Linien angehÑngt werden

class DParam {
public:
	long _Enum;
	long _Enum2;
	long _Ebene;
	long _Stufe;
	long _StrichModus;
	long _StrichDicke;
};

class DGeoObj {
public:
	enum DGeoTyp { 
		DGT_Unknown, 
		DGT_Punkt, 
		DGT_Linie, 
		DGT_Flaeche, 
		DGT_Text, 
		DGT_Symbol,
	};

protected:
	int _DGT;

	DParam *_pDPar;

	char *_Code;			// Code fÅr DB-Ankopplung
	char *_Text;			// zugehîriger Text
	char *_Name;			// Name des Objektes

	long _RelSatz;			// evtl. Begleitobjekt

public:
// Konstruktor/Destruktor
		DGeoObj (DGeoTyp DGT, DParam *pDPar = NULL);
		DGeoObj (DGeoObj &);
virtual		~DGeoObj (void);

virtual	Bool OutPut (void) = 0;			// generische Ausgabefunktion
virtual Bool AddGeoObj (DGeoObj *, AppMode = AM_NoSense) = 0;	// generische Erweiterung der 
						// ObjektGeometrie
virtual DGeoObj * Copy (void) = 0;		// kopiert Geometrie

	int isA (void) { return _DGT; }

// Zugriff auf GeoObj-Eigenschaften
	long Ebene (void) { if (_pDPar) return _pDPar->_Ebene; else return 1L; }
	long Stufe (void) { if (_pDPar) return _pDPar->_Stufe; else return 1L; }
	long Enum (void) { if (_pDPar) return _pDPar->_Enum; else return -1L; }
	long Enum2 (void) { if (_pDPar) return _pDPar->_Enum2; else return -1L; }
	long StrichModus (void) { if (_pDPar) return _pDPar->_StrichModus; else return 1L; }
	long StrichDicke (void) { if (_pDPar) return _pDPar->_StrichDicke; else return 1L; }
	void SetParams (DParam *pDParams);

	void SetText (char *);
	void SetName (char *);

// Zugriff auf Code fÅr DB-Ankopplung 
	void SetCode (char *pCode);

	long RelSatz (void) { return _RelSatz; }
};

// ----------------------------------------------------------------------------
class DPunkt : public DGeoObj {
protected:
	double _X, _Y;
	char _PunktKennzeichen[4];
	long _PunktNummer;

public:
	Bool OutPut (void);
	Bool AddGeoObj (DGeoObj *, AppMode = AM_NoSense);

// Konstruktor 
		DPunkt (void);		// default
		DPunkt (double X, double Y);
		DPunkt (DPunkt &DPt);	// CopyConstructor

		~DPunkt (void);

// sonstige Member
	double X (void) { return _X; }
	double Y (void) { return _Y; }

	void SetPunktParams (char *PKZ, long PNR);

	Bool operator== (DPunkt &);	// Geometrievergleich mit anderem Punkt
	DGeoObj *Copy (void);		// macht echte Kopie der Geometrie
};

class DSymbol : public DGeoObj {
public:
	Bool OutPut (void) { return FALSE; }
	Bool AddGeoObj (DGeoObj *, AppMode = AM_NoSense) { return TRUE; }

// Konstruktor 
		DSymbol (void) : DGeoObj (DGT_Symbol) {}	// default
		~DSymbol (void) {}

	DGeoObj *Copy (void);/* { return new DSymbol; }*/	// macht echte Kopie der Geometrie
};


#define TV_CentreAlign	0x0100
#define TV_RightAlign	0x0200


class DText : public DPunkt {
protected:
	double _Winkel;
	double _THoehe;
	double _TLaenge;
	int _TRicht;
	double _TModus;
	double _TSWinkel;

public:
// Konstruktor
		DText (void);		// default
		DText (double X, double Y);
		DText (DText &DTxt);

		~DText (void);

// sonstige Member
	void SetTextParams (int, double, double, double, double, double);
	Bool OutPut (void);		// Ausgabe
};


// ----------------------------------------------------------------------------
class DLinie;			// nur deklarieren
class DPunktListe : public CListContainer {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		DPunktListe (void);
		~DPunktListe (void);

// Liste modifizieren
	Bool AddDPunkt (DPunkt &);
	DPunkt *LastDPunkt (void);
	DPunkt *FirstDPunkt (void);

	DPunktListe *Copy (void);
};
DeclareLock (DPunktListe, DPunkt);

class DLinie : public DGeoObj {
public:
	DPunktListe *_pDPL;		// Liste der StÅtzpunkte

	Bool OutPut (void);
	Bool AddGeoObj (DGeoObj *, AppMode = AM_NoSense);
	Bool MakePolygon (double, double, double, double, double = 360.0, int = 4);
		// Approximation eines Kreisbogens durch LinienStÅcke
		// Default: Vollkreis mit 4¯ - Segmenten

// Konstruktor
		DLinie (void);		// default
		DLinie (DLinie &DLi);	// CopyConstructor

	long Count (void) { return _pDPL -> Count(); }	// StÅtzpunktanzahl liefern
friend Bool Append (DPunktListe &, CRing &, Bool = TRUE);
friend Bool AppendReverse (DPunktListe &, CRing &, Bool = TRUE);

		~DLinie (void);

	DGeoObj *Copy (void);
};

// ----------------------------------------------------------------------------
class DLinienListe : public CListContainer {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		DLinienListe (void);
		~DLinienListe (void);

// sonstige Member
	Bool AddDLinie (DLinie &);
	Bool AddDLinie (void);

	DPunkt *FirstDPunkt (void);
	DPunkt *LastDPunkt (void);
	Bool AddGeoObj (DGeoObj *);

	DLinienListe *Copy (void);
};
DeclareLock (DLinienListe, DLinie);

// const int NUMLISTEN = 10;	// max. Anzahl der Innenkonturen

class DFlaeche : public DGeoObj {
public:
	DLinienListe *_pDLL;		// ListContainer der Linien
// 	DLinie *_pDLi[NUMLISTEN];	// Liste (Feld) der Polygone
	int _NumListen;		// Anzahl der DPunktListen

	double _XKoord;			// Bezugskoordinaten
	double _YKoord;
	double _SWinkel;		// Schraffurwinkel
	double _SAbstand;		// Schraffurabstand
	char _Pointer [PointerSize];	// dBase-Ankopplung

	Bool OutPut (void);
	Bool AddGeoObj (DGeoObj *, AppMode = AM_NoSense);
	void SetFlaechenParams (double, double, double, double);
	void SetPointer (char Pointer [PointerSize]);
	char *GetPointer (char Pointer [PointerSize]);

// Konstruktor
		DFlaeche (void);	// default
		DFlaeche (DFlaeche &);	// CopyConstructor

		~DFlaeche (void);

// sonstige Member
	long Count (int i = -1);
	Bool AddDLinie (DLinie &);	// neue Kontur erîffnen
	DPunkt *FirstDPunkt (void);
	DPunkt *LastDPunkt (void);

	DGeoObj *Copy (void);
};

#endif // _DGEOOBJ_HXX

