// Konstantendefinitionen für ErweiterungsRessourcen
// File: TRIASDEF.H

#if !defined(_TRIASDEF_H)
#define _TRIASDEF_H

#include "KOMPDEF.H"

// TRiAS 3.0 Standardsicht

#if _MSC_VER >= 1100
static char KompaktDefaultVisInfo[] = "__DefaultVisInfo__";
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheDatenQuellen ( char *, Bool , void *pData);
#endif

//Arbeitsprotokoll
#define KP_Default		0


//TRIAS - Header
const short HEADERKEYSIZE	= 16;
const short HEADERSIZE		= 512;
const short TEXTLEN 		= 32;
// Leistung
const short SCHRITTWEITE	= 30;
//Ereignisse
const short PUFFERZONE = 10;

//ParameterEinstellung
// Validation von ObjektKlassen
const short OC_TEMPORAER	= 0;
const short OC_ANLEGEN		= 1;
const short OC_LOESCHEN		= 2;
const short OC_DEKLARIEREN	= 3;
const short OC_DEFINIEREN	= 4;

//ParameterDefinition
const short PM_GEWAESSER	= 1;
const short PM_BAUWERKE		= 2;
const short PM_HYDRAULIK	= 3;
const short PM_FLAECHEN		= 4;
const short PM_LEISTUNGEN	= 5;

//GewaesserUebersicht
const short KP_NOTHING 		= 0;
const short KP_ALL 		= 1;
const short KP_PART 		= 2;

//ListenParameter fuer TRiASGewaesser
const short PM_ALLEGEWAESSER	= 0;
const short PM_NURKATASTER	= 1;
const short PM_NURGRAPHIK	= 2;
const short PM_LAENGENDIFF	= 3;
const short PM_MULTIOBJEKTE	= 4;
const short PM_SOLOKATASTER	= 5;
const short PM_SOLOGRAPHIK	= 6;


class KP_LATree;
class TR_OCLTree;
class KPTree;
class BauwerkeStatistik;
class TR_IDMTree;
class TR_IDOTree;
class DATACLList;


//Fuer BauwerksUebernahme
typedef struct tagBAUWERKSINPUT {
	KPTree  *pGew;
	TR_OCLTree  *pIdent;
	long lCount;
} BAUWERKSINPUT;

//Fuer Enumeration von ObjektKlassen
typedef struct tagOBJCLSRECHERCHE {
	MultiSelListBox *pListBox;
	long  lIdent;
} OBJCLSRECHERCHE;

//Fuer Tauschen von Merkmalen
typedef struct tagMERKMALSWECHSEL {
	long  lMCodeV1;
	long  lMCodeV2;
	long  lMCodeZ1;
	long  lMCodeZ2;
} MERKMALSWECHSEL;


//Fuer Enumeration von TR_Objekten in Gew.Klassen
typedef struct tagGEWAESSERKLASSE {
	DWORD dwSize;
	TR_OCLTree *pTRGew;
	short iTyp;
	ulong  lGewCode;
	ulong  lGewNrCode;
	char *pGewNr;
} GEWAESSERKLASSE;

//Fuer Enumeration von Merkmalen
typedef struct tagMERKMALSDEFINITION {
	DWORD dwSize;
	ulong lNummer;
	LPSTR pNummer;
	ulong lName;
	LPSTR pName;
	ulong lStartPunkt;
	long lCount;
	long lRefCount;
	class CStatus *pStatus;
} MERKMALSDEFINITION;

//Fuer Enumeration von bestimmten Merkmalen
typedef struct tagMERKMALSRECHERCHE {
	DWORD dwSize;
	long *pObj;
	LPSTR pMWert;
	long lMCode;
	TR_OCLTree *pClass;
} MERKMALSRECHERCHE;


#if !defined (_LEISTUNG_DEFINED)	// in kompdef.h
#define  _LEISTUNG_DEFINED

enum LeistParm {
	Leist_Links,
	Leist_Rechts,
	Leist_Beide,
	Leist_Mitte
	};
#endif

//Fuer AbstandsBestimmungen
//GewObjektstruktur
typedef struct tagGEWSTRUKTUR {
	DWORD dwSize;
	long lONr;		// ObjektNummer	BezugsGewaesser
	long lLaenge;		// GewaesserLaenge
	long lStartPunkt;	// StartPunkt Gewaesser
	long lNewONr;		// neu erstellte ObjektNummer
	ulong lIdent;		// Identifikator
	long lObjectIdent;	//ObjectIdent = BauwerksIdent (Malte)
	short iLinksRechtsMitte;	// Position Leistungsart
	short iObjTyp;		// ObjektTyp (Punkt, Kante, Fläche, ...)
	short iFlags;		// Modi von ModGI
//
	long lCnt;		// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	double dHoehe;
	long lStation;
//
	KoOrd lGXA;		//Start-Punkt
	KoOrd lGYA;
	KoOrd lGXE;		//End-Punkt
	KoOrd lGYE;
//
	KoOrd lXA;		//Start-Punkt
	KoOrd lYA;
	KoOrd lXE;		//End-Punkt
	KoOrd lYE;
	double dDist;
//Merkmalsteil
	ulong lMCode;
	char *pMText;
	char *pSText;
// Leistungsschrittweiten 
	double dDefDist;
	double dRCDist;
} GEWSTRUKTUR;

// Aubau von speziellen Objektklassen
//Fuer Enumeration von TR_Objekten in Obj.Klassen
typedef struct tagOBJEKTKLASSENTYP {
	class TR_OBJTree *pOBJ;
	long lONr;
	short iTyp;
	ulong lMCode;
	LPSTR pMWert;
} OBJEKTKLASSENTYP;

/////////////////////////////////////////////////////////////////

typedef struct tagEREIGNISTYP {
	class TR_OCLTree *pBauw;
	class TR_OBJTree *pObj;
	long lONF;
	IExtendTopRel2 *pTop;
} EREIGNISTYP;

//////////////////////////////////////////////////////////////////
// Datenquellen
typedef struct tagKOMPAKTQELLEN {
	DWORD dwSize;
	ListBox *pC;
	DATACLList *pD;
	short iCount;
} KOMPAKTQUELLEN;
//////////////////////////////////////////////////////////////////

//Leistungen/Bauwerke - interne TRiAS-Struktur

typedef struct tagKOMPAKTDATEN {
	DWORD dwSize;
	short iIdentNrHerkunft;
	short iIdentNrZuordnung;
	short iLinksRechtsMitte;
	LPSTR pcGewaesserNr;
	long  lBeginn;
	long  lEnde;
// spezifisch Leistungen
	LPSTR pcLeistung;
	long  lMeterOffen;
	double dKostetDM;
	short iRechnungsNr;
	LPSTR pcZuordnung;
 // Legende
	LPSTR pcKurzText;
	LPSTR pcLangText;
	LPSTR pcComment;
//-------Bauwerke----------------------
	LPSTR pcBauwerksBezeichnung;
	long lHoch;
	long lRechts;
	long lAnlageNr;
	long lObjectIdent;
//----------------------------
	double dBauwHoehe;
	double dWasserSpDiff;
	LPSTR pcBezeichner1;
	LPSTR pcBezeichner2;
} KOMPAKTDATEN;

//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

DoublePair UmrechnungsFaktor (Punkt& , Punkt& , CoordTransX* );
void RealInDBKoord (double , double , KoOrd& , KoOrd& , CoordTransX* );
long * ObjectContainer ( long, short);

#if _MSC_VER >= 1100
	void DefineFeatureSet(PBDMERKMALEX *);
#endif

//--------Leistungen/Bauwerke in Kompaktdaten------------
bool LeistungenInKompakt ( LEISTUNGEN *p, KOMPAKTDATEN *q);
bool BauwerkeInKompakt ( BAUWERKE *p, KOMPAKTDATEN *q);

extern "C" bool _XTENSN_EXPORT PASCAL  SetzeBauwerkeIdent( long, long );


// DtoA-Modifikation
char * PASCAL ST_DtoA (char _far *, char _far *, double);
//Strings doppeln
char *StrDuplicat ( char *);


//GewZuordnung TR-Klasse <=> GewKlasse
//Aufbau IDListe Sicht
extern "C"  Bool PASCAL _XTENSN_EXPORT FillIDListBox (long , Bool , void *);
// mehrere Datenquellen
extern "C"  Bool PASCAL _XTENSN_EXPORT FillFullIDListBox (long , Bool , void *);
//extern "C"  Bool PASCAL _XTENSN_EXPORT SucheMerkmalsKode (long , Bool , void *);
extern "C" BOOL PASCAL _XTENSN_EXPORT FillKPMCListBox (long , Bool , void *);

//Aufbau OKS-Ident
extern "C"  Bool PASCAL _XTENSN_EXPORT FillOKSListBox (long , Bool , void *);

//KompaktIdentifikator-Bildung
extern "C" long PASCAL _XTENSN_EXPORT KompaktIdentifikatorEx (char *,short,short);
extern "C" long PASCAL _XTENSN_EXPORT KompaktIdentifikator (char *,short,short);
extern "C" bool PASCAL _XTENSN_EXPORT KompaktProtokoll (char *, char *);


//KOMPMENU
extern "C"  Bool PASCAL _XTENSN_EXPORT FindeEinzelObjekt ( long lObj, Bool , void *pData);

//KOMPMEM
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheKompaktKlassen ( long Ident, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT StoreBauwIdentFeature ( long Ident,ulong lIDCode); 

extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwKlassen ( long Ident, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwEinzelKlassen ( long Ident, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheEinzelBauwerke ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumBauwerke ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheGewaesserObjekt ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheEinzelGewaesserObjekt ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwObjekt ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwEinzelObjekt ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT FindeTempObjekt ( long lObj, Bool , void *pData);

//COBJKOMP
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheObjekte ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT DeleteKompaktClass ( long Ident, Bool , void *pData);

//KOMPCLS
// Erfassen von FlaechenKlassen
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheFlaechen ( long Ident, DWORD Typ, void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheFlaechenObjekte ( long Ident, Bool , void *pData);

extern "C"  Bool PASCAL _XTENSN_EXPORT SucheTRiASKlassen ( long Ident, DWORD Typ, void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheTRiASObjekte ( long Ident, Bool , void *pData);

//KOMPHEAD
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumeriereObjekte ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT MindestensEinObjekt ( long Ident, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT ModifiziereObjekte ( long ONr, Bool , void *pData);

#if _MSC_VER >= 1100
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheKompaktDaten( HPROJECT hPr, Bool , void *pData);
#endif

//KOMPGEW
extern "C"  Bool PASCAL _XTENSN_EXPORT SetzeGewaesserObjekt ( long ONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT LoescheGewaesserObjekt ( long ONr, Bool , void *pData);

//KPSYMB
extern "C"  Bool PASCAL _XTENSN_EXPORT SelektierteObjekte ( long ONr, Bool , void *pData);


//KPWINOT
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumNachbarObjects ( long lONr, Bool , void *pData);
extern "C"  Bool PASCAL _XTENSN_EXPORT LoescheTRiASObjekte ( long lONr, Bool , void *pData);

//KOMPSIMU
extern "C"  char * PASCAL _XTENSN_EXPORT BauwerkeName ( short iZuo);

//KPBIGAR
extern "C"  Bool PASCAL _XTENSN_EXPORT DoppelnAttribut ( long ONr, Bool , void *pData);
#endif 	// _TRIASDEF_H
