// Konstantendefinitionen für ErweiterungsRessourcen
// File: KOMPDEF.H

#if !defined(_KOMPDEF_H)
#define _KOMPDEF_H

#include <pshpack1.h>

// Funktionen Trias zu Kompakt;

typedef bool (CALLBACK * KOMPAKTINITPROC)( DWORD, HWND); //Open Kompakt
typedef bool (CALLBACK * KOMPAKTUNLOADPROC)(void);	//Close Kompakt
typedef bool (CALLBACK * KOMPAKTCOMMANDPROC)(short, HWND);	//Command Kompakt

// GewNr in Kompakt (Kataster) anzeigen
typedef bool (CALLBACK * KOMPAKTCOMMANDWINPROC)( HWND, char *);	//Command Kompakt- 1 Gew

//// GewLaenge aus Kataster
typedef long (CALLBACK * KOMPAKTKATASTERGETPROC)( char *, long, long);

//// GewLaenge in Kompakt Kataster korrigieren
typedef long (CALLBACK * KOMPAKTKATASTERMODPROC)( char *,long);

//// GewNr in Kompakt Kataster anlegen
typedef long (CALLBACK * KOMPAKTKATASTERADDPROC)( char *, char *, long);

//// Ueber GewNr in Kompakt Name holen
typedef char* (CALLBACK * KOMPAKTKATASTERNAMEPROC)( char *);


//	Menu_Button
//---Leistungen ( HoleLeistungVonKompakt )
const short KP_UNTERHALTUNG	= 1;
const short KP_AUSSCHREIBUNG	= 2;
const short KP_AUFTRAG		= 3;
const short KP_AUFMASS	 	= 4;
//---
const short KP_HYDRAULIK 	= 5;
//------------
const short KP_OEKOLOGIE	= 6;
const short KP_BAUWERKE		= 7;
const short KP_RECHTE		= 8;
//-----Command-------------------------------
const short KP_KATASTER	 	= 9;
const short KP_VERBAND	 	= 10;
const short KP_PROJEKTE	 	= 11;
const short KP_TRIAS		= 12;
const short KP_BAUWZUKOMPAKT	= 13;

const short KP_KOMPAKT		= 14;
const short KP_KOMPAKTABGLEICH		= 15;

// KompaktobjektklassenSchlüssel
static char KompaktIdentifikatorTabelle [] = "aaaabbbc"; 



// HERKUNFT der Leistungen
const int cLeistungenUnterhaltung = 1;
const int cLeistungenAusschreibung = 2;
const int cLeistungenAuftrag = 3;
const int cLeistungenAufmass = 4;

//Definitionen zur Hydraulik
// HERKUNFT der Hydraulik-Problematik
const int cHydraulikHochwasser  = 5;
const int cKilometrierung	= 6;

//Definitionen zur Oekologie
// HERKUNFT der Oekologie-Problematik
const int cSensibilitaetsStufe  = 7;

//Definitionen zu Bauwerken
const int cBauwerkeIdent  = 8;


// Zuordnung der Leistungen
const int cLeistZuordnungRandStreifen       = 100;
const int cLeistZuordnungBoeschungLinks     = 210;
const int cLeistZuordnungBoeschungRechts    = 230;
const int cLeistZuordnungBoeschungBeide     = 250;
const int cLeistZuordnungBoeschungTeilprofil= 270;
const int cLeistZuordnungSohlkrautung       = 300;
const int cLeistZuordnungGrundraeumung      = 350;
const int cLeistZuordnungStundenStueckLohn  = 400;

// Zuordnung der HydraulikProblematik
const int cUeberschwemmungsPunkt	    = 510;
const int cUeberschwemmungsGebiet	    = 520;


// Zuordnung der OekologieProblematik
const int cSensibilitaetsStufe1		    = 610;
const int cSensibilitaetsStufe2		    = 620;
const int cSensibilitaetsStufe3		    = 630;

// Zuordnung Bauwerke
const int cBauwerkeSchoepfwerke = 1;
const int cBauwerkeStauanlagen = 2;
const int cBauwerkeRechte = 3;
const int cBauwerkeKreuzungen = 4;
const int cBauwerkeSohlbauwerke = 5;
const int cBauwerkeSchaechte = 6;
const int cBauwerkeOekologie1 = 7;
const int cBauwerkeRohrleitungen = 8;
const int cBauwerkeDurchlaesse = 9;
const int cBauwerkeOekologie2 = 10;
const int cBauwerkeBebauungLinks = 11;
const int cBauwerkeBebauungRechts = 12;
const int cBauwerkeEinmuendung = 13;
const int cBauwerkeUnbekannt = 99;


// Administrative Flaechen
//--Flächen
const short cAlleFlaechen = 0;
const short cGemeindenFlaeche = 1;
const short cBehoerdenFlaeche= 2;
const short cSchaubezirkFlaeche= 3;
const short cEinzugsgebietsFlaeche= 4;

// wieder offen von Kompakt ???
const short cEigentuemerFlaeche= 5;
const short cNutzerFlaeche= 6;
const short cOekologieFlaeche= 7;
const short cBebauungsFlaeche= 8;

//sGemeindenFlaeche= 'Gemeinde';
//sBehoerdenFlaeche= 'Behörde';
//sSchaubezirkFlaeche= 'Schaubezirk';
//sEigentuemerFlaeche= 'Eigentümer';
//sNutzerFlaeche= 'Nutzer';
//sEinzugsgebietsFlaeche= 'Einzugsgebiet';
//sOekologieFlaeche= 'Ökologie';
//sBebauungsFlaeche= 'Bebauung';

#if !defined (_LEISTUNG_DEFINED)	// in triasdef.h
#define  _LEISTUNG_DEFINED

enum LeistParm {
	Leist_Links,
	Leist_Rechts,
	Leist_Beide,
	Leist_Mitte
	};
#endif

//Leistungen
typedef struct tagLEISTUNGEN {
	DWORD dwSize;
	short iIdentNrHerkunft;
	short iIdentNrZuordnung;
	short iLinksRechtsMitte;
	LPSTR pcGewaesserNr;
	LPSTR pcLeistung;
	long  lBeginn;
	long  lEnde;
	long  lMeterOffen;
	double dKostetDM;
	short iRechnungsNr;
	LPSTR pcZuordnung;
 // Legende
	LPSTR pcKurzText;
	LPSTR pcLangText;
	LPSTR pcComment;
} LEISTUNGEN;

//Koordinaten
typedef struct tagKOORDINATEN {
	DWORD dwSize;
	LPSTR pcGewaesserNr;
	long lStation;
	LPSTR pcHochWert;
	LPSTR pcRechtsWert;
	long lIdent;
	long lAbstand;
	long lError;
} KOORDINATEN;


//Bauwerke
typedef struct tagBAUWERKE {
	DWORD dwSize;
	short iIdentNrZuordnung;
	LPSTR pcBauwerksBezeichnung;
	LPSTR pcGewaesserNr;
	long  lBeginn;
	long  lEnde;
	long lHoch;
	long lRechts;
	long lAnlageNr;
//----------------------------
	double dBauwHoehe;
	double dWasserSpDiff;
	LPSTR pcBezeichner1;
	LPSTR pcBezeichner2;
	long lObjectIdent;
} BAUWERKE;

//Gewaesser
typedef struct tagGEWAESSER {
	DWORD dwSize;
	LPSTR pcGewaesserNr;
	LPSTR pcGewaesserName;
	long  lBeginn;
	long  lEnde;
} GEWAESSER;



//Hydraulik
typedef struct tagHYDRAULIK {
	DWORD dwSize;
	LPSTR pcGewaesserNr;
	long  lPos;
	double  dHoehe;
} HYDRAULIK;




// Flaechen an Abschnitten

typedef struct tagFLAECHENANABSCHNITTEN {
	DWORD dwSize;
	short  iIdentNr; // 2   Flächenart
	LPSTR  pcGewaesserNr;     // 4
	long  lBeginn; //4
	long  lEnde; //4
	short iLinksRechtsBeide; // 2   0: links  1: rechts  2: beide
	double dQuadratMeter;	// FlaechenGroesse
	LPSTR pObjektKlasse;
	LPSTR pObjektBezeichnung;

} FLAECHENANABSCHNITTEN;


// Maltes Fehlermeldungen
const long cGewaesserNummerFalsch = -1;
const long cGewaesserZuKurz = -2;
const long cGewaesserZuLang = -3;
const long cKoordinatenFalsch = -4;
const long cStationFalsch = -5;
const long cMultiGewaesser = -6;
const long cKoordinatenAnfrageFalsch = -7;
const long cGewaesserNichtVorhanden = -8;
const long cFehlerhafteDaten = -9;

// KoordinatenFunktion ( in lIdent)
const long lfctGibKoordSystem = 0;
const long lfctGibKoordinate = 1;
const long lfctGibStation = 2;

//-------------------Neu 4.3.98----------------------------------

//// GewNr,Start+End in Kataster setzen
typedef bool (CALLBACK * KOMPAKTKATASTERSTRUCPROC) ( GEWAESSER *);

//// GewNr,Start+End aus Kataster holen
typedef bool (CALLBACK * KOMPAKTKATASTERHOLPROC) ( GEWAESSER *);


// Objekteigenschaft in Kompakt (Kataster) anzeigen
typedef bool (CALLBACK * KOMPAKTOBJPROPPROC)( HWND, BAUWERKE *);	//Command Kompakt-OE

// Neuen DatenPfad in Kompakt (Kataster) anzeigen
typedef bool (CALLBACK * KOMPAKTDATENPFADPROC)( char *);	

//-----------Enumerationen: von Kompakt zu Trias
typedef bool (CALLBACK * LEISTUNGPROC)( LEISTUNGEN *, DWORD dwData);
typedef bool (CALLBACK * ENUMLEISTUNGPROC)( short, LEISTUNGPROC, DWORD dwData);
typedef bool (CALLBACK * BAUWERKEPROC)( BAUWERKE *, DWORD dwData);
typedef bool (CALLBACK * ENUMBAUWERKEPROC)( short, BAUWERKEPROC, DWORD dwData);
typedef bool (CALLBACK * GEWAESSERPROC)( GEWAESSER * , DWORD dwData);
typedef bool (CALLBACK * ENUMGEWAESSERPROC)( short, GEWAESSERPROC, DWORD dwData);


//-----------Enumerationen: von Trias zu Kompakt 
typedef bool (CALLBACK * KOMPAKTGEWAESSERPROC)( short, GEWAESSER *, DWORD);
typedef bool (CALLBACK * KOMPAKTBAUWERKEPROC)( short, BAUWERKE *, DWORD);
typedef bool (CALLBACK * KOMPAKTFLAECHENPROC)( short, FLAECHENANABSCHNITTEN *, DWORD);


// Maltes Ereignisse
typedef bool (CALLBACK * KOMPAKTKATALOGPROC)( char *,char *, DWORD);

//KOMPDLL
extern "C"
bool _XTENSN_EXPORT PASCAL  UebergebeLeistungen( LEISTUNGEN *, DWORD );

extern "C"
bool _XTENSN_EXPORT PASCAL  UebergebeBauwerke( BAUWERKE *, DWORD );

extern "C"
bool _XTENSN_EXPORT PASCAL  UebergebeGewaesser( GEWAESSER *, DWORD );

extern "C"
bool _XTENSN_EXPORT PASCAL TRiASTest (DWORD, long lTest);

extern "C"
bool _XTENSN_EXPORT PASCAL  HoleTriasGewaesser( KOMPAKTGEWAESSERPROC pFct, DWORD p);

extern "C"
bool _XTENSN_EXPORT PASCAL  HoleTriasBauwerke( KOMPAKTBAUWERKEPROC pFct, DWORD p);

extern "C"
bool _XTENSN_EXPORT PASCAL  HoleTriasFlaechen( KOMPAKTFLAECHENPROC pFct, DWORD p, LPSTR GewNr, short iTyp);

extern "C"
bool _XTENSN_EXPORT PASCAL  HoleKoordinaten( HWND hWnd, KOORDINATEN *q, DWORD p);

extern "C"
bool _XTENSN_EXPORT PASCAL  ZeigeTopKarte ( HWND hWnd, KOORDINATEN *q, DWORD p);

//Wunsch von Malte
extern "C"
bool _XTENSN_EXPORT PASCAL HydraulikTest ( HYDRAULIK *, DWORD );

extern "C"
bool _XTENSN_EXPORT PASCAL  HoleKatalogItems( short iTyp,KOMPAKTKATALOGPROC pFct, DWORD p);

extern "C"
bool _XTENSN_EXPORT PASCAL  THoleKatalogProc( char *pKurz,char *pLang, DWORD p);

typedef bool (CALLBACK * ENUMKATALOGPROC)( short, KOMPAKTKATALOGPROC, DWORD dwData);


// Maltes Verzweiflung
typedef bool (CALLBACK * KOMPAKTMALTEPROC)( BAUWERKE *); //BauwerkeEintragen


#include <poppack.h>

#endif 	// _KOMPDEF_H
