// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.04.2002 16:03:06 
//
// @doc
// @module bnapars.h | Declaration of the <c Cbnapars> class

#if !defined(_BNAPARS_H__31A16B7F_DD4F_4E78_A03E_04D1A9805F45__INCLUDED_)
#define _BNAPARS_H__31A16B7F_DD4F_4E78_A03E_04D1A9805F45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/* Objekttypen */
#define E_OBJEKT	1
#define K_OBJEKT	2
#define O_PUNKT		1
#define O_LINIE		2
#define O_FLAECHE	3
#define O_TEXTOBJEKT	4
#define O_TEXTOBJIND	5

/* Merkmalstypen */
#define	M_INTEGER	1
#define M_DOUBLE	3
#define M_TEXT		0

#define STRINGLEN 	_MAX_PATH
#define NAMELEN		32
#define BACKSLASH	'\\'

/* Datendeklarationen */
extern long eps;		/* Testtoleranz */
extern long on;			/* Objektnummer */
extern ULONG id;		/* Identifikator */
extern long sta[];		/* Status */
extern long mi[];		/* Merkmalsinformation */

#if defined(_NO_CONVERSION_BNA)
extern long gxi[];		// Geometrieinformation
extern long gyi[];
#else
extern double gxi[];		// Geometrieinformation
extern double gyi[];
#endif // _NO_CONVERSION_BNA

extern long lgi;		/* Anzahl der Koordinatenpaare */
extern long maxgi;		/* Feldgroesse Geometrie */

extern char guid[];		// ObjektGuid

extern int mi_count;		/* Zaehler der Merkmalswerte */

/* sonstige Variablen */
extern long koord_paare;		/* Anzahl der Stuetzpunkt eines EO's */
extern int mi_werte;		/* Anzahl der Merkmalswerte */
extern int satz_nr;		/* Satznummer in ASCII-Datei */

extern HPROJECT dbd;		/* Datenbankdeskriptor */
extern int first, last;		/* erster und letzter zu speichernder Satz */

extern long *curr_mi;		/* aktuelle Merkmalswerte */
extern char *curr_mi_text;

extern FILE *fpProt;		/* Protokolldatei */
//extern FILE *yyin;		// Eingabedatei

extern int yylineno;		/* Zeilennummer */

extern long lTextObjMCode;	// MerkmalsCode der Texte an Textobjekten

extern char cbInFile[_MAX_PATH];	// aktuelle EingabeDatei

/* Funktionsprototypen */
int error_skip_lines (char *, int);	/* Objekt ueberspringen, Fehler melden */
void skip_lines (char *);		/* Objekt ueberspricngen */
char *read_string (char *);		/* Rest der Zeile einlesen */
int next_line (void);
unsigned long MakeHex (unsigned long);

// DB-Header schreiben
bool GetHdFloat (HPROJECT hPr, const char *, double &);
bool GetHdULONG (HPROJECT hPr, const char *, unsigned long &);
bool PutHdFlt (HPROJECT hPr, double, char *, bool fForce = true, DWORD dwStyle = HEADER_NORMAL);
bool PutHdString (HPROJECT hPr, char *, char *, bool fForce = true, DWORD dwStyle = HEADER_NORMAL);
int EvalKoeffs (double *, double *, double *, double *);	// inverse Matrix berechnen
bool ImportHeader (LPCSTR pcKey, LPCSTR pcData, DWORD dwStyle = HEADER_NORMAL);

// Schnittstelle zum Parser/Scanner
void InitAllEnvironment (void);

// Kommandozeilenparameter ----------------------------------------------------
extern bool d_flag;		// Identifikator dezimal/hexadezimal
extern bool md_flag;	// Merkmale dezimal/hexadezimal
extern bool r_flag;		// Relationen ignorieren
extern bool g_flag;		// Geometrie importieren
extern bool m_flag;		// Merkmale importieren

// Schnittstelle zu Baum und Liste der Relationsverwaltung
int StoreInTree (long lONr, long lSatzNr);
long RetrieveFromTree (long lSatzNr);
void ResetTree (void);

int StoreInList (long lONr, long lRCode, long lRTyp);
int RetrieveNextFromList (long *plONr, long *plRCode, short *pRTyp);
long RelCount (void);
int ResetList (void);
void ClearList (void);

//void InitLexer (void);		// LEX initialisieren

// Objekt erzeugen etc. -------------------------------------------------------
#if defined(_NO_CONVERSION_BNA)
bool CreateObject (LONG &rlONr, ULONG lIdent, long sta[], long mi[], long lgi, long gxi[], long gyi[]);
short AnalyzeAreaContures (long &lgi, long gxi[], long gyi[], long **pplCnt);
#else
bool CreateObject (LONG &rlONr, ULONG lIdent, long sta[], long mi[], long lgi, double gxi[], double gyi[]);
short AnalyzeAreaContures (long &lgi, double gxi[], double gyi[], long **pplCnt);
#endif // _NO_CONVERSION_BNA

bool CreateKomplexObject (HPROJECT hPr, LONG &rlONr, ULONG lIdent, long mi[]);
bool UpdateFeatures (LONG &rlONr, ULONG lIdent, long sta[], long mi[]);
long FindObject (LONG lMCode, LPCSTR pcUIdent);


bool CreateFeatures (LONG rlONr, long mi[], ULONG lIdent, ULONG lMCodeIgnore = 0L);
short RetrieveText (ULONG lMCode, long mi[], char **ppText, bool fConvert = false, bool fMarkAsWritten = true);
char *FindMWert (ULONG lMCode, long pMInfo[], short *plLen, bool fMarkAsWritten = true);
bool WriteTextMerkmal (LONG lONr, ULONG lMCode, char cbBuffer[], int iLen);

bool CreateRelation (LONG lPONr, LONG lSONr, ULONG lRCode, short iRTyp);

int db_error (int iError, int iRoutine, DWORD dwData);

// ZählerVariablen ------------------------------------------------------------
extern long g_lPoints;
extern long g_lLines;
extern long g_lAreas;
extern long g_lTexts;
extern long g_lWithErrors;
extern long g_lNotImported;
extern long g_lTime;
extern long g_lKomplex;

///////////////////////////////////////////////////////////////////////////////
// Flags/MerkmalsCodes für Abgleich
extern bool g_fImportObj;				// Objekt vollständig importieren (default)
extern bool g_fAbglGeom;				// Geometrie abgleichen
extern bool g_fAbglAttr;				// Attribute abgleichen
extern bool g_fAbglOks;					// Objektklasse abgleichen
extern unsigned long g_ulOksFromAttr;	// Objektklasse hier entnehmen
extern unsigned long g_ulOksToAttr;		// bisherige Oks hier ablegen

// PolyGIS
// BNAHeaderSatz
#define POLYBNANAME1		0
#define POLYBNANAME2		1
#define POLYBNAID			2
#define POLYBNALAYER		3
#define POLYBNAKOORD		4

// DATHeaderSatz
#define POLYDATNAME1		3
#define POLYDATNAME2		4
#define POLYDATID			2
#define POLYDATLAYER		1

// Alte PunktStruktur
#define POLYDATPOINTNAME1		11
#define POLYDATPOINTNAME2		12
#define POLYDATPOINTID			10

#define POLYDATNOTHING		-1

// GCA-Struktur
#define GCAFIELDCOUNT	9


// Unterthemen - PolyGISWandler
#define STANDARD				0
#define IMPORT					1
#define IMPORTSTANDARDKLASSEN	2
#define IMPORTMEMOKLASSEN		3
#define IMPORTSTANDARDDAT		4
#define IMPORTPUNKTDAT			5
#define EXPORT					6


////////////Import-Modi ///////////////////////////////////////////////////////

#define BNAIMPORT	0
#define DATIMPORT	1
#define GPSIMPORT	2
#define GCAIMPORT	3

///////////////////////////////////////////////////////////////////////////////
// OKSTree
int StoreInOKSTree (const char *pLayerName, DWORD dwObjType, HPROJECT hPr, 
	bool fImportAttributes);
void ResetOKSTree (void);
//int RetrieveFromOKSTree (const char *pKey); 
//int RetrieveAbgleichFromOKSTree (const char *pKey); 
//int RetrieveAbgleichOKSTree (void); 

///////////////////////////////////////////////////////////////////////////////
// BNATree
bool StoreInKeyTree (const char *, const char *);
void ResetKeyTree (void);
char const *RetrieveFromKeyTree (const char *pKey); 

///////////////////////////////////////////////////////////////////////////////
// MemoTree
int StoreInMemoTree (char const *);
void ResetMemoTree (void);
int RetrieveFromMemoTree (char const *); 

///////////////////////////////////////////////////////////////////////////////
// sonstige Helperfunktionen
ULONG ClassIsDefined (char const *pLayerName, HPROJECT hPr = NULL);

#endif // !defined(_BNAPARS_H__31A16B7F_DD4F_4E78_A03E_04D1A9805F45__INCLUDED_)
