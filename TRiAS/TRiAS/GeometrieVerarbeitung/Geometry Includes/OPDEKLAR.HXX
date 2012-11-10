// Allgemeine Deklarationen für "Objektoperationen mit GeoObjekten"
// File: OPDEKLAR.HXX
// W. Mörtl

#ifndef _OPDEKLAR_HXX
#define _OPDEKLAR_HXX



// ********************************************************************************************
// Versionskontrolle
#define REGOPERATPROPACT_VERSION_1_0_0		100
#define REGOPERATPROPACT_VERSION_1_0_1		101
#define REGOPERATPROPACT_VERSION_1_0_2		102
#define REGOPERATPROPACT_ACTVERSION			REGOPERATPROPACT_VERSION_1_0_2
#define REGOPERATPROPACT_SIGNATURE			0x41504F52		// "ROPA"			

#define LINESPLITPROPACT_VERSION_1_0_0		100
#define LINESPLITPROPACT_VERSION_1_0_1		101
#define LINESPLITPROPACT_VERSION_1_0_2		102
#define LINESPLITPROPACT_VERSION_1_0_3		103
#define LINESPLITPROPACT_ACTVERSION			LINESPLITPROPACT_VERSION_1_0_3
#define LINESPLITPROPACT_SIGNATURE			0x4150534C		// "LSPA"

#define SETSOPERATPROPACT_VERSION_1_0_0		100
#define SETSOPERATPROPACT_VERSION_1_0_1		101
#define SETSOPERATPROPACT_VERSION_1_0_2		102
#define SETSOPERATPROPACT_ACTVERSION		SETSOPERATPROPACT_VERSION_1_0_2
#define SETSOPERATPROPACT_SIGNATURE			0x41504F53		// "SOPA"

#define AREABUILDPROPACT_VERSION_1_0_0		100
#define AREABUILDPROPACT_VERSION_1_0_1		101
#define AREABUILDPROPACT_VERSION_1_0_2		102
#define AREABUILDPROPACT_ACTVERSION			AREABUILDPROPACT_VERSION_1_0_2
#define AREABUILDPROPACT_SIGNATURE			0x41504241		// "ABPA"

#define OPTIONSPROPACT_VERSION_1_0_0		100
#define OPTIONSPROPACT_VERSION_1_0_1		101
#define OPTIONSPROPACT_ACTVERSION			OPTIONSPROPACT_VERSION_1_0_1
#define OPTIONSPROPACT_SIGNATURE			0x4150504F		// "OPPA"

#define MINOR_VERSION_MASK					0xff

// ********************************************************************************************
// Struktur für Datenübergabe der Routine MerkmaleKopieren()
struct DatKop
{
	long lONr1, lONr2;	// Nummer des Quell- bzw. Zielobjektes
	string sUISubst;	// Text, durch den der bisherige UniqueIdent ersetzt wird
	bool bOverWrite;	// alten Merkmalstext überschreiben (true) bzw. neuen Text anhängen (false)
	bool bGeoErr;		// Merkmalstext von "Geometriefehler" wird kopiert (true)
//	bool bClear;		// Merkmalstext von "Bereinigter Geometriefehler" wird kopiert (true)	#WM021210
//	bool bSect;			// Merkmalstext von "Verschnitt" wird kopiert (true)					#WM021210
	DWORD dwFeat;		// Angabe dazu, welche Merkmal kopiert werden sollen
};


// ********************************************************************************************
// mögliche Objektoperationen
enum ObjOp
{
	EINZOBJ,		// Schnitt eines einzelnen Objektes
	IDGRUPP,		// Schnitt aller Objekte einer Identifikatorgruppe
	ALLOBJ,			// Schnitt aller Objekte einer Sicht
	VEREINIGUNG,	// Vereinigung mehrerer Flächen bzw. zweier Linien
	DURCHSCHNITT,	// Durchschnitt mehrerer Flächen
	SUBTRAKTION,    // Exklusiv-Oder zwischen 2 Flächen
	SPLITTING,		// Liniensplittung
	GEMKONTUR,		// gemeinsame Konturabschnitte zweier Flächen
	LEER			// noch keine Operation ausgewählt
};


// Optionen für Objektoperationen
#define FEAT	0x01	// Merkmale der Originalobjekte sollen übernommen werden (true)
#define DELET	0x02	// Originalobjekte sollen gelöscht werden (true)
#define MARK	0x04	// Originalobjekte sollen markiert werden (true)
#define SHNEW	0x08	// neue Objekte sollen angezeigt werden (true)
#define SHORIG	0x10	// Originalobjekte sollen angezeigt werden (true)

	
// ******************************************************************************************
// Konstantendefinitionen
const short iZug = 10;			// Zugabe in Millimeter für Rechteck beim Löschen von Objekten

// Parameter für default-Toleranz bei Linienvereinigung
const double MinExt = 100;		// minimale Ausdehnung in x- bzw. y-Richtung
const double dLowFuzzy = 0.01;	// Fuzzy für obige Ausdehnung
const int FuzzyVal = 10000;		// Divisor zur Berechnung der Fuzzy-Toleranz
const double dFuzzyVal = 0.005;	// default-Fuzzy-Toleranz soll 0,5% von der maximalen
								// Containerseite sein

const string sUnionName = "Vereinigtes Objekt";		// default-Name für ErgebnisObjektklasse bei
													// ObjektVereinigung
const string sMeaningName = "Durchschnittsobjekt";	// default-Name für ErgebnisObjektklasse bei
													// ObjektDurchschnitt

#endif  // _OPDEKLAR_HXX
