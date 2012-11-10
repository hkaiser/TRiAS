/* Deklarationen fuer ASCPARSER					*/
/* File: ASCPARS.H						*/

#if !defined(_ASCPAS_H)
#define _ASCPAS_H

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

/* Yacc-Stacktypen */
typedef struct {	/* String-Token */
	short str_line;
	char string[STRINGLEN+1];
} STRING_TOKEN;

typedef struct {	/* Integer-Token */
	short num_line;
	long intnum;
} NUMBER_TOKEN;

typedef struct {	/* Float-Token */
	short flt_line;
	double fltnum;
} FLOAT_TOKEN;

/* Datendeklarationen */
extern long eps;		/* Testtoleranz */
extern long on;			/* Objektnummer */
extern ULONG id;		/* Identifikator */
extern long sta[];		/* Status */
extern long mi[];		/* Merkmalsinformation */

#if defined(_NO_CONVERSION_ASC)
extern long gxi[];		// Geometrieinformation
extern long gyi[];
#else
extern double gxi[];		// Geometrieinformation
extern double gyi[];
#endif // _NO_CONVERSION_ASC

extern long lgi;		/* Anzahl der Koordinatenpaare */
extern long maxgi;		/* Feldgroesse Geometrie */

extern char guid[];		// ObjektGuid

extern int mi_count;		/* Zaehler der Merkmalswerte */

/* sonstige Variablen */
extern int koord_paare;		/* Anzahl der Stuetzpunkt eines EO's */
extern int mi_werte;		/* Anzahl der Merkmalswerte */
extern int satz_nr;		/* Satznummer in ASCII-Datei */

extern HPROJECT dbd;		/* Datenbankdeskriptor */
extern int first, last;		/* erster und letzter zu speichernder Satz */

extern long *curr_mi;		/* aktuelle Merkmalswerte */
extern char *curr_mi_text;

extern FILE *fpProt;		/* Protokolldatei */
extern FILE *yyin;		// Eingabedatei

extern int yylineno;		/* Zeilennummer */

extern long lTextObjMCode;	// MerkmalsCode der Texte an Textobjekten

extern char cbInFile[_MAX_PATH];	// aktuelle EingabeDatei

/* Funktionsprototypen */
int end_previous_object (void);	/* Objekt bearbeiten */
void init_new_object (void);	/* Naechstes Objekt initialisieren */
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
int yyparse (void);
int yylex (void);
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

void InitLexer (void);		// LEX initialisieren

// Objekt erzeugen etc. -------------------------------------------------------
#if defined(_NO_CONVERSION_ASC)
bool CreateObject (LONG &rlONr, ULONG lIdent, long sta[], long mi[], long lgi, long gxi[], long gyi[]);
short AnalyzeAreaContures (long &lgi, long gxi[], long gyi[], long **pplCnt);
#else
bool CreateObject (LONG &rlONr, ULONG lIdent, long sta[], long mi[], long lgi, double gxi[], double gyi[]);
short AnalyzeAreaContures (long &lgi, double gxi[], double gyi[], long **pplCnt);
#endif // _NO_CONVERSION_ASC

bool CreateKomplexObject (HPROJECT hPr, LONG &rlONr, ULONG lIdent, long mi[]);
bool UpdateFeatures (HPROJECT hPr, LONG &rlONr, ULONG lIdent, long sta[], long mi[]);
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

///////////////////////////////////////////////////////////////////////////////
// Map der vordefinierten MCodes (Merkmalsbeschreibungen)
// Zuordnung der MCodes in dieser Datei zu MCodes in der Zieldatenquelle
typedef map<INT_PTR, INT_PTR, less<INT_PTR> > CMCodeMap;	
extern CMCodeMap g_MCodes;

#endif // _ASCPAS_H
