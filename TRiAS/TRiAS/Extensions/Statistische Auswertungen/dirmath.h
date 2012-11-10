////////////////////////////////////////////////////////////////////////
//	Definitionen für GeoStatistik
//	File:DIRMATH.H
///////////////////////////////////////////////////////////////////////

#if !defined(_DIRMATH_H)
#define _DIRMATH_H

//Allgemeine define-Anweisungen

class IDMTree;

#define TEXTLEN 32

#define MAXKOORD	1000000000
#define MCODESIZE	40
#define MAXTPROJECT	25
#define MAXFCTNAME	50
#define MAXSTRING	128
#define MAXRECORD	512
#define MAXDBSTRING	37
#define MAXOBJECTS	300
#define MAXSECONDS	3000
#define MAXDIFFSECONDS 5000

//DatenBankInformationen
#define DBSicht 		0
#define DBObjektKlasse		1
#define DBMerkmalsCode		2
#define DBTeilProjekte		3
#define DBdBaseDaten 		4
#define DBSachDaten		5



//	Einheiten
#define QuadratMeter		1
#define Hektar			10000
#define QuadratKiloMeter	1000000

#define Meter			1
#define KiloMeter		1000

//LängenMaß ( Registrierung )
#define LM_Default	0
#define LM_Meter	1
#define LM_KiloMeter	2

//FlächenMaß ( Registrierung )
#define FLM_Default		0
#define FLM_QuadratMeter	1
#define FLM_Hektar		2
#define FLM_QuadratKiloMeter	3

//Objektnummer-Registrierung	
#define ON_Default		0
#define ON_Anzeige		1

#define CNTGITYP 4	// GiTypen einer Oklasse ( z.Zt. P,L,F,T )

const double Pi = 3.14159;
const double MaxDouble = 111111111111.0;
const double Genauigkeit = 1000.0;
const short MaxIntervall = 250;
const short MaxParam = 30;
const short MaxString = 2014;
const short ObjectGrenze = USHRT_MAX/sizeof(long);
const short ST_MAXOBJECTS = 10000;

//Mathematische Vergleichsoperationen
#define GOKleiner 		0
#define GOKleinerGleich		1
#define GOGleich		2
#define GOUnGleich		3
#define GOGroesser 		4
#define GOGroesserGleich	5


// Arten von Objektklassen
#define OKlAttribut		0	//Sicht
#define OKlAttributSegment	1	//Segment der Sicht
#define OKlGeometrieTyp		2	//GIKlasse aus OR
#define OKlObjectContainer	3	//O-Folge aus OR
#define OKlObjectRelation	4	//O-Folge aus OR
#define OKlDataBase		5	//DB
#define OKlParameter		6	//Sicht
#define OKlAttributWindow	7	//O-Folge aus OR



// Fehlerarten bei der GeometrieKlassenBildung
#define GKlIgnore		0
#define GKlKeineObjekte		1
#define GKlKriteriumFalsch	2
#define GKlAbgebrochen		3

//--------------------------Test--------------------

typedef struct GIEXTREMUM {
	long lObjCount;
	double rMinimum;
	double rMaximum;
	double rMedianWert;
	double rMittelWert;
	double rSumme;
} GIEXTREMUM;


typedef struct IDGITYP {
//-----------Counter---------
	long lCount;
	long lPoint;
	long lLine;
	long lArea;
	long lComplex;
	long lText;
	long lNoname;
//-----------Geometrietyp------
	short iITyp;
//-----------Container----------
	long lXmin;
	long lXmax;
	long lYmin;
	long lYmax;
//-----------GI-Eigenschaften----
	double rPolyLen;
	double rPolyLenMax;
	double rPolyLenMin;
	double rPolyLenMedian;
	double rPolyLenMittel;
	double rArea;
	double rAreaMax;
	double rAreaMin;
	double rAreaMedian;
	double rAreaMittel;
	long lMCode;
	class OBJTree *pObj;
} IDGITYP;

//ObjektStruktur
typedef struct OBJECTTYP {
//-----------Klasse------------
	long lIdent;
	long lMCode;
//-----------Fensterhandle------
	long lIntervall;
//-----------Geometrietyp------
	short iGITyp;
//-----------Container----------
	long lXmin;
	long lXmax;
	long lYmin;
	long lYmax;
//-----------GI-Eigenschaften----
	double rPolyLen;
	double rArea;
} OBJECTTYP;

//-----------------------------------------------------
//-------------------------GI-Test/Wertvergleich-----------------
typedef struct GICLASS {
	long lGroupNr;
	long lEinheit;
	long lOperate1;
	long lOperate2;
	short iGiTyp;
	long lCount;
//-----------Container----------
	long lXmin;
	long lXmax;
	long lYmin;
	long lYmax;
//------------------------------
	long IDNr;
	long MCode;
	double rVglWert1;
	double rVglWert2;
//-----------GI-Eigenschaften----
	double rKumul;
	double rKumulMax;
	double rKumulMin;
	class OBJTree *pObj;
} GICLASS;
//----------------------------------------------------
//-------------------------GI-Extrema-Wertevergleich-----------------


//-----------------------------------------------------

typedef struct IDPOINT {
	IDMTree *pID;
	long Number;
} IDPOINT;

typedef struct TYPVECTOR {
	long *pOBJ;
	short GiTyp;
} TYPVECTOR;

typedef struct OBJPOINT {
	IExtendTopRel2 *m_pTop;
	OBJTree *pOBJ;
	class IdentInformation *pStatus;
	class CoordTransX *pCTF;
	long lRange;
	long lCount;
	long lBezObj;
	short GiTyp;
} OBJPOINT;

typedef struct IDGIPOINT {
	IDGITYP *pIDGI;
	class IdentInformation *pStatus;
	long lRange;
	long lCount;
	short GiTyp;
	short isMKode;
} IDGIPOINT;

// DtoA-Modifikation
char * PASCAL ST_DtoA (char _far *, char _far *, double);

//Aufbereitung L,B
char * PASCAL ST_NoMtoA ( char _far *, Bool, double, double, CoordTransX *);


//Versuch - Compare
extern "C" Bool PASCAL _XTENSN_EXPORT CompareMinMax (long , long, DWORD );



//---------------SichtInformationen------------------
//Identifikatoren einer Sicht nach GI-Typ
extern "C" Bool PASCAL _XTENSN_EXPORT FillIdOTypListBox (long , DWORD, void *);

//Identifikatoren einer Sicht nach GI-Typ
extern "C" Bool PASCAL _XTENSN_EXPORT GetIdentGiTyp (long , DWORD, void *);

//Merkmalskode einer GeoDB in ListBox
extern "C" Bool PASCAL _XTENSN_EXPORT FillMKListBox (long , Bool, void *);

// Enumerationsfunktionen in Sicht


//Zählen von Objekten pro Identifikator oder Merkmalskode in Sicht
extern "C" Bool PASCAL _XTENSN_EXPORT GetIdentsDate ( long , Bool , DWORD dCTF, void *);
//Einfaches Zählen von Objekten pro Identifikator oder Merkmalskode in Sicht
extern "C" Bool PASCAL _XTENSN_EXPORT GetObjIdent ( long , Bool , DWORD dCTF, void *);

//Zählen von ObjKlassen,Sichten
extern "C" Bool PASCAL _XTENSN_EXPORT NumerationDB ( char *, Bool, void *);

//Zählen von MCodes
extern "C" Bool PASCAL _XTENSN_EXPORT NumerationMK ( long, Bool, void *);

//Speichern von IdentsLongKey ( Objektbaum ) 
extern "C" Bool PASCAL _XTENSN_EXPORT NumerateIdents ( long , Bool , void * );

//Speichern von IdentsLongKey ( Objektbaum ) 
extern "C" Bool PASCAL _XTENSN_EXPORT NumerateObjects ( long , short , void * );

//Speichern von IdentsLongKey ( Objekte + GiTyp in Vektor ) 
extern "C" Bool PASCAL _XTENSN_EXPORT SearchObjects ( long , short , void * );

//Speichern von IdentsLongKey ( Objekte + mit MKode in IDGITYP ) 
extern "C" Bool PASCAL _XTENSN_EXPORT SearchObjectsWithMK ( long , short , void * );

//Speichern von F+L-Objekten mit FL-Größe und LinienLaenge ( Objektbaum ) 
extern "C" Bool PASCAL _XTENSN_EXPORT EnumFL_ObjectsWithAL ( long , Bool , void * );
extern "C" Bool PASCAL _XTENSN_EXPORT EnumFLObjectsWithAL ( long , Bool , void * );

//Speichern von Objekten mit Container,FL-Größe und LinienLaenge ( Objektbaum ) 
extern "C" Bool PASCAL _XTENSN_EXPORT EnumObjectsWithAL ( long , Bool , void * );
extern "C" Bool PASCAL _XTENSN_EXPORT Enum_ObjectsWithAL ( long , Bool , void * );

//Speichern von best. GI-Objekten mit Container,FL-Größe und LinienLaenge ( Objektbaum ) 
extern "C" Bool PASCAL _XTENSN_EXPORT EnumObjectsWithTyp ( long , Bool , void * );
//Speichern von best. GI-Objekten ohne Parameter ( Objektbaum ) 
extern "C" Bool PASCAL _XTENSN_EXPORT EnumOnlyObjects ( long , Bool , void * );

//Speichern von Objekten mit Container,FL-Größe und LinienLaenge ( Objektbaum + Statusfenster) 
extern "C" Bool PASCAL _XTENSN_EXPORT EnumObjectsWithStatus ( long , Bool , void * );

//Speichern von Objekten mit Container,FL-Größe und LinienLaenge ( Objektbaum + Statusfenster,Topologie FObject) 
extern "C" Bool PASCAL _XTENSN_EXPORT EnumObjectsWithTopo ( long , Bool , void * );

//----- objektbezogene Funktionen --------------         
//----------------------------------------------
//	Liefern eines ObjectContainers
long *ObjectContainer ( long , short );

//	Liefern logischer Werte für ObjectType ( OT_... zu OT..)
short LogObjectType ( long );

//	Suchen Merkmal in Objekt ( MK,ON) 
Bool ExistMCodeInObject ( short, long , long );

//Liefern von Maximum/Minimum aus OR-Fenster(ab 18.11.94 ObjektBaum)
long *GetExtremum ( void *);
            
//Bestimmen des Mittelwertes aus Objektbaum
double *MittelWertBerechnung ( OBJTree *pObj, long *pMCode = NULL);
            
//Bestimmen des Medianwertes aus Objektbaum
double *MedianWertBestimmung ( long Count, OBJTree *pObj, long *pMCode = NULL);

//Zusammenstellen des TextBuffers für Mittelwert
char *WerteInBuffer ( double *, double *);

//Sortieren von double/long
void QuickSort ( double *pWERT, long *pON, short i, short r );

//Pfad modifizieren
void KurzerPfad ( int, char* );

//-------------Recherchekriterien ( Werteraum)--------------
//------Recherche aus Sicht----------
Bool isAttribut ( short );
//------Recherche aus Sichtausschnitt ( Pfeil,Lupe)
Bool isAttributSegment ( short );
//------Recherche aus SichtFenster ( ORFenster..)
Bool isAttributWindow ( short );
//------Recherche aus Sicht/Parameteranalyse
Bool isObjParameter ( short );
//------Recherche aus Objektcontainer
Bool isObjContainer ( short );
//------Recherche aus Flächenobjekt
Bool isObjRelation ( short );
//------Recherche Geometrieklassifikation
Bool isGeometrieTyp ( short );
//------Recherche aus gesamter Datenbank
Bool isDataBase ( short );

// Objektklassenbezogene Funktionen
//---------------------------------
// Aufbau eines Objektklassenbaums ( IDMTree)
short AddObjectClassInTree ( short, IDMTree *);

// Untersetzen von Idents eines Objektklassenbaums ( IDMTree)
void DefineObjectClassInTree (short,long , IDMTree *, CoordTransX *);

// Füllen der ObjektKlassenListe über Objekte : GI-Typ im Komplex
Bool StoreIDList ( ResourceFile *, long , void *, short);  

// Füllen der ObjektKlassenListe nach Geometriekriterien
Bool StoreGIKlassList ( long, void *, short, double, double , char *, long);  

// Füllen der ObjektKlassenListe über Objekte : GI-Typ einzeln   
Bool StoreObjKlassList ( ResourceFile *, long, void *, short );

// Funktionen über IDGITYP-Struktur
//	"Löschen" der Struktur
void SetZero ( struct IDGITYP *);

//	Zählen von Objekten in einer Klasse
long CountObjectsFromStruct ( struct IDGITYP *);

//	Kumulieren von Strukturen
void KumulIdent ( struct IDGITYP *, struct IDGITYP *);

//	Kumulieren von ObjStrukturen(Fl,Lin,Min,Max)
void CumulateObjects ( struct IDGITYP *, struct IDGITYP *);

// Durchsuchen einer Objektkette nach Mkode ( Wertebestimmung )
short SearchObjectMCode ( short Flag, OBJTree * pOBJ, struct IDGITYP *p);

//------------OBJECTTYP-Struktur
//	"Löschen" der Struktur
void SetObjZero ( struct OBJECTTYP *);

//------------GICLASS-Struktur
//	"Löschen" der Struktur
void SetGIKlassZero ( struct GICLASS *);

//	"Finden" des Objektes durch GI-VergleichsWerte
Bool Operate ( double, long, double);


//------------GIEXTREMUM-Struktur
//	"Löschen" der Struktur
void SetExtremumZero ( struct GIEXTREMUM *);


//	Anzeigen der GI-Recherche in HELPTEXT
char * ShowSearchScript ( double, long, long, double );  

//	Prüfen der UnGleichung auf Richtigkeit ( W1 = W2 )
Bool TestW1GleichW2 ( long Op1, long Op2 );

// 	Prüfen der UnGleichung auf Richtigkeit ( W1 < W2 )
Bool TestW1KleinerW2 ( long Op1, long Op2 );

// 	Prüfen der UnGleichung auf Richtigkeit ( W1 > W2 )
Bool TestW1GroesserW2 ( long Op1, long Op2 );

//Suchen von Leerzeichen in Textfeld
Bool SucheLeerZeichen ( char *);

//---------------ObjectPropertyFunctions--------------------------------

//extern "C" LPSTR FAR PASCAL DtoA (LPSTR String, LPSTR Format, double Wert);

double GetFlaechenParams (long lONr, CoordTransX *pCTF, double *pdX = NULL, double *pdY = NULL );
double GetFlaechenUmfang (long lONr, CoordTransX *pCTF);
double GetFlaechenUmrandung (long lONr, CoordTransX *pCTF);
double GetFlaechenRadius (long lONr, CoordTransX *pCTF);
short GetPunktParams (long lONr, double *pdX, double *pdY);
double GetLinienParams (long lONr, CoordTransX *pCTF, double *pdX = NULL, double *pdY = NULL);
Bool GetFlaechenPunkt (long lONr, CoordTransX *pCTF, double *pdX , double *pdY );
Bool GetContainerPunkt (IExtendTopRel2* pTop,long lONr, CoordTransX *pCTF, double *pdX , double *pdY );
void ModFlaechenPunkt (IExtendTopRel2 *pTop,CoordTransX *pCTF, long lONr, double *pdX , double *pdY );
bool SetFlaechenPunkt ( IExtendTopRel2 *pTop, long lONr,IObjektGeometrie *pIOG2, IInitObjektGeometrie *pInitOG1, long *lX , long *lY );
bool TestFlaechenPunkt ( IExtendTopRel2 *pTop, IObjektGeometrie *pIOG2, IInitObjektGeometrie *pInitOG1, long lX , long lY );
bool BildeFlaechenPunkt (IExtendTopRel2* pTop, IObjektGeometrie *pIOG2, IInitObjektGeometrie *pInitOG1,short iFlag,long lTeiler, long lAP, long lEP, long *lX, long *lY);
Bool GetLinienPunkt (long lONr, CoordTransX *pCTF, double *pdX , double *pdY );
//------------Koordinaten holen
Bool HoleFlaechenInformation (long lONr, CoordTransX *pCTF, long lCnt, short iKCnt, double *pX , double *pY , long *pK, bool iVFlag);
Bool HoleLinienInformation (long lONr, CoordTransX *pCTF, long lCnt, double *pX , double *pY );

double GetAreaObject ( double *pX, double *pY, long * pK,
		       long Count, short Kount ,double *SX, double *SY );

double GetAreaObjectPart ( double *pX, double *pY, long K,
		       double *SX, double *SY );

void GetAreaObjectPoint ( double *pX, double *pY, long * pK,
		       long Count, short Kount ,double *SX, double *SY );

void GetAreaObjectPointPart ( double *pX, double *pY, long K,
		       double *SX, double *SY );


double GetPolyLen ( CoordTransX *pCTF, double *pX, double *pY, long Count,
		       double *SX, double *SY );

void SetCoordinate ( double *pX, double *pY, CoordTransX *pCTF);

short GetNumberSecObjects ( long lONr );
short GetSecObjects ( long lONr, long* pObj );
long GetDescriptObject ( long lONr );

extern "C" Bool PASCAL _XTENSN_EXPORT  DelStatObjects(long lONr, Bool, void *pData);


//--------Relationen-------------
// Liefert Sekundärobjekte eines Komplexes
extern "C" Bool PASCAL _XTENSN_EXPORT  SecObjects(long lONr, long IRCode, short iRTyp, void *pData);
//	Liefert die Anzahl aller Sekundärobjekte eines Komplexes
extern "C" Bool PASCAL _XTENSN_EXPORT  NumberSecObjects(long lONr, long IRCode, short iRTyp, void *pData);
//	Liefert Begleitobjekt
extern "C" Bool PASCAL _XTENSN_EXPORT  DescriptObject(long lONr, long IRCode, short iRTyp, void *pData);
//--------------------------------------------------------------------------

// Virtuelle Funktionen, die bei bestimmten Events gerufen werden -------------

extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenInhalt (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenUmfang (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenUmrandung (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenRadius (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenDifferenz (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPLinienLaenge (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPReferenzPunktX (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPReferenzPunktY (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPBegleitText (long lONr, char *pBuffer, short iLen);
extern "C" char * _XTENSN_EXPORT PASCAL OPSchwerPunktX (long lONr, char *pBuffer, short iLen, DWORD pExt);
extern "C" char * _XTENSN_EXPORT PASCAL OPSchwerPunktY (long lONr, char *pBuffer, short iLen, DWORD pExt);
//
extern "C" char * _XTENSN_EXPORT PASCAL OPBegleitObjekt (long lONr, char *pBuffer, short iLen);

//
//	Schlüssel Datenbankheader
long GetHeaderMCode ( ResID resID );

#endif	//_DIRMATH_H
