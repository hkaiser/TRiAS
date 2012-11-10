// Datendeklarationen fuer ExportFunktionen
// File: IMPEXP.HXX

#if !defined(_IMPEXP_HXX)
#define _IMPEXP_HXX

#if !defined(EXPORT02)
#define EXPORT02
#endif

#if !defined(_TRIAS02_ENTRY)
#define _TRIAS02_ENTRY
#endif

#pragma pack(1)

// Datenstruktur, die zur Übergabe der Merkmalsinformationen eines Objektes
// verwendet wird
typedef struct tagMFELD {
	long MCode;		// MerkmalsCode
	char *MText;		// Merkmalswert als Text
	short MTyp;		// Merkmalstyp
	void *MWert;		// MerkmalsWert != NULL bei Double oder Int
} MFELD;

typedef struct tagGSTRUCT {
	long Id;		// Identifikator
	long ON;		// ObjektNummer
	short Typ;		// OT_PUNKT, OT_KANTE, OT_FLAECHE, OT_TEXT
	long GSize;		// Anzahl der Stützpunkte
	double *x;		// X-Feld
	double *y;		// Y-Feld
	long *cnt;		// Anzahl der Stützpunkte in Konturen
} GSTRUCT;

typedef struct tagRSTRUCT {
	long RCode;		// RelationsCode;
	short RTyp;		// RelationsTyp RT_BEGLEIT, RT_GLEICHR, RT_KOMPLEX
	long RON;		// beteiligtes Objekte
} RSTRUCT;

// Typ der zu rufenden Importfunktion
enum ImportFunc {
	ICFHeader, 		// Import der HeaderInformation
	ICFDescription, 	// Import einer Beschreibungsinfo
	ICFData, 		// Import eines Objektes
	ICFTrailer, 		// Import der abschlieáenden Info's
};

#pragma pack()

// Schichtbeschreibung --------------------------------------------------------
class VisInfo;

class IdentDescription {
private:
	long _Ident;
	char *_Text;
	VisInfo *_pVI;

public:
// Konstruktoren/Destruktor
_TRIAS02_ENTRY EXPORT02 IdentDescription (long, char *, VisInfo *, HPALETTE);
_TRIAS02_ENTRY EXPORT02 IdentDescription (IdentDescription &);
_TRIAS02_ENTRY EXPORT02 ~IdentDescription (void);

// sonstige Member
	long & ID (void) { return _Ident; }
	pchar & KurzText (void) { return _Text; }
	VisInfo & VisInfoObj (void) { return *_pVI; }

// Friend-Funktionen
friend int CompareIDs (void *pObj1, void *pObj2); // KeyCompare-Funktion
friend void* GetID (void *pObj);		  // GetKey-Funktion
};

// Merkmalsbeschreibung -------------------------------------------------------
class MerkmalDescription {
private:
	long _MCode;		// MerkmalsCode
	char *_Text;		// KurzText
	short _MTyp;		// 'I', 'A', 'F'
	short _MLen;		// Länge des Merkmalstextes
	short _MDecLen;		// Anzahl der Nachkommastellen für Typ 'F'
public:
// Konstruktoren/Destruktor
_TRIAS02_ENTRY EXPORT02 MerkmalDescription (long MCode, char *Text, short MTyp, short MLen);
_TRIAS02_ENTRY EXPORT02 MerkmalDescription (MerkmalDescription &);
_TRIAS02_ENTRY EXPORT02 ~MerkmalDescription (void);

// sonstige Member
	long & MCode (void) { return _MCode; }
	pchar & Text (void) { return _Text; }
	short & MTyp (void) { return _MTyp; }
	short & MLen (void) { return _MLen; }
	short & MDecLen (void) { return _MDecLen; }

// Friend-Funktionen
friend int CompareMDs (void *pObj1, void *pObj2); // KeyCompare-Funktion
friend void* GetMD (void *pObj);		  // GetKey-Funktion
};

	
// Ausgabemode bei existierender Datei (DB)
enum OutMode {
	OMOverwrite,		// Ausgabedatei wird überschrieben
	OMConcatinate,
};

enum ImportCapability {
	IC_Container,	// kann Container aller Eingabedaten bestimmen
};

enum ExportCapability {
	EC_Merkmale,		// liefert Anzahl der exportierbaren Merkmalswerte
	EC_IdentDescription,	// IdentBeschreibung soll geliefert werden
	EC_MerkmalDescription,	// MerkmalsBeschreibung soll geliefert werden
	EC_Relationen,			// liefert, ob Relationen unterstützt werden
	EC_NoConvertCoords,		// wenn gesetzt, dann Koordinaten nicht voll konvertieren
};

extern "C" {
// ExportFunktionen
	typedef ErrCode (WINAPI *EXPENDFUNC)(OFSTRUCT &);
	typedef ErrCode (WINAPI *EXPFUNC)(OFSTRUCT &, const char *);
	typedef ErrCode (WINAPI *EXPBEGFUNC)(char *, OFSTRUCT &, bool, HWND);
	typedef ErrCode (WINAPI *EXPDATAFUNC)(OFSTRUCT &, GSTRUCT &, MFELD *, RSTRUCT *, char *);
	typedef ErrCode (WINAPI *EXPDESCFUNC)(OFSTRUCT &, const char *, const char *);
	typedef ErrCode (WINAPI *EXPDESCFUNCEX)(OFSTRUCT &, const char *, const char *, DWORD);
	typedef ErrCode (WINAPI *EXPTRAILFUNC)(OFSTRUCT &, const char *);
	typedef short (WINAPI *EXPCAPSFUNC)(ExportCapability);
	typedef ErrCode (WINAPI *EXPIDENTDESCFUNC) (IdentDescription &);
	typedef ErrCode (WINAPI *EXPMERKMALDESCFUNC) (MerkmalDescription &);

// ImportFunktionen
	typedef ErrCode (*IMPCALLBACK)(ImportFunc, ...);
	typedef ErrCode (WINAPI *IMPBEGFUNC)(char *, IMPCALLBACK);
	typedef ErrCode (WINAPI *IMPABRTFUNC)(int);
}

#endif // IMPEXP_HXX

