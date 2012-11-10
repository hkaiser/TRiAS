
// ASCII-Format: Analyse, Put etc. --------------------------------------------
// File: ASCPARS.Y

#include "ascimpp.hpp"

#include <hdrentrx.hxx>
#include <errinstx.hxx>

#if defined(_MSC_VER)
#pragma warning (disable: 4101)	// unreferenced local variable
#pragma warning (disable: 4102)	// unreferenced label
#endif

#include "ascpars.h"
#include "ascerrs.h"

#include "input.h"

#define GUID_CCH	39

// Informationsfelder ---------------------------------------------------------
LONG on = 0;						// Objektnummer
ULONG id;							// Identifikator
long sta[2] = { E_OBJEKT, 0 };		// Status
long mi[MAXMI] = { MAXMI, 0, };		// Merkmalsinformation

char guid[GUID_CCH];		// ObjektGuid

#if defined(_NO_CONVERSION_ASC)
long gxi[MAXGI];					// Geometrieinformation
long gyi[MAXGI];
#else
double gxi[MAXGI];					// Geometrieinformation
double gyi[MAXGI];
#endif // _NO_CONVERSION_ASC

long lgi = -1;						// Anzahl der Koordinatenpaare
long maxgi = MAXGI;

long *curr_mi = &mi[-1];			// Merkmalsfeldzeiger 
char *curr_mi_text = (char *)&mi[5];	// Merkmalsfeldzeiger fuer Text

int mi_count = 3;					// Zähler der I*4 Merkmalsfelder

// sonstige Variablen ---------------------------------------------------------
int koord_paare;		// Anzahl der einzulesenden Koordinatenpaare
int mi_werte = 0;		// Anzahl der einzulesenden Merkmalswerte
int mi_length;			// Laenge der Merkmalswerte
int satz_nr = 0;		// Nummer des Objektes im ASCII-File
int objekt_nr = 0;		// Nummer des Satzes im ASCII-File

// globale Daten --------------------------------------------------------------
long eps = -1;			// Testtoleranz 

long lTextObjMCode;		// MerkmalsCode, an dem bei Textobjekten der Text hängt

bool r_flag = true;		// Relationen ignorieren
bool d_flag = true;		// Identifikator dezimal/hexadezimal
bool md_flag = true;		// Merkmale dezimal/hexadezimal
bool g_flag = true;		// Geometrie immer importieren
bool m_flag = true;		// Merkmale importieren

// TransformationsParameter ---------------------------------------------------
double Koeff11 = 1.0;
double Koeff12 = 0.0;
double Koeff21 = 0.0;
double Koeff22 = 1.0;
double OffsetX = 0.0;
double OffsetY = 0.0;

FILE *fpProt = NULL;		// Protokolldatei

// lokale Daten ---------------------------------------------------------------
static char comment[STRINGLEN+1];
static char header[STRINGLEN+1];

// Schlüssel für DB-Header (Leerzeichen sind signifikant !) -------------------
char Koeff11Key[17] = 	"Koeff11         ";
char Koeff12Key[17] = 	"Koeff12         ";
char Koeff21Key[17] = 	"Koeff21         ";
char Koeff22Key[17] = 	"Koeff22         ";
char OffsetXKey[17] = 	"OffsetX         ";
char OffsetYKey[17] = 	"OffsetY         ";
char PbdNameKey[17] = 	"PBD-NAME        ";
char VerschnittKey[17] = 	"Verschnitt      ";
char ZeitKey[17] = 	"Erstellungsdatum";
char DBStatusKey[17] = 	"DB-STATUS       ";
char ScaleKey[17] =   	"Scale           ";
char OffsetKey[17] =  	"Offset          ";
char ObjVisInfoMCode[17] =	"ObjVisInfoMCode ";
char TextObjMCode[17] = "TextObjMCode    ";
char IdentBase[17] =	"IdentBase       ";
char MCodeBase[17] = 	"MCodeBase       ";
char UniqueIdent[17] =	"Unique Ident    ";
char OldUniqueIdent[17] =	"Old Unique Ident";

bool fFirstIdent = true;
bool fFirstMCode = true;

int first = 0;		// werden zur Zeit nicht verwendet
int last = 0;

// Scale/Offset verwalten
static bool fWasScaleProject = false;
static bool fWasOffsetProject = false;
static bool fWriteOffsetProject = false;
static bool fWriteScaleProject = false;	

static bool fWasScale = false;
static bool fWasOffset = false;
static bool fWriteOffset = false;
static bool fWriteScale = false;	

// ZählerVariablen ------------------------------------------------------------
long g_lPoints = 0;
long g_lLines = 0;
long g_lAreas = 0;
long g_lTexts = 0;
long g_lKomplex = 0;

long g_lWithErrors = 0;
long g_lNotImported = 0;
long g_lTime = 0;

// Verwalten des MCodes für den Unique Ident ---------------------------------
unsigned long g_ulUniqueId = 0L;
unsigned long g_ulOrgUniqueId = 0L;
unsigned long g_ulOldUniqueId = 0L;

///////////////////////////////////////////////////////////////////////////////
// MerkmalsCodes für Objektklassenabgleich
bool g_fImportObj = true;				// Objekt vollständig importieren (default)

bool g_fAbglGeom = false;				// Geometrie abgleichen
bool g_fAbglAttr = false;				// Attribute abgleichen

bool g_fAbglOks = false;				// Objektklasse abgleichen
unsigned long g_ulOksFromAttr = 0L;		// Objektklasse hier entnehmen

unsigned long g_ulOksToAttr = 0L;		// bisherige Oks hier ablegen

///////////////////////////////////////////////////////////////////////////////
// aktuelle Datenquelle
HPROJECT g_hPr = NULL;

///////////////////////////////////////////////////////////////////////////////
// Map der vordefinierten MCodes (Merkmalsbeschreibungen)
// Zuordnung der MCodes in dieser Datei zu MCodes in der Zieldatenquelle
CMCodeMap g_MCodes;

typedef union  {
	STRING_TOKEN strtok;
	NUMBER_TOKEN numtok;
	FLOAT_TOKEN flttok;
} YYSTYPE;
#define YYSUNION /* %union occurred */
#define T_STRING 257
#define T_MISTRING 258
#define T_INTEGER 259
#define T_PSATZ 260
#define T_LSATZ 261
#define T_FSATZ 262
#define T_DSATZ 263
#define T_GSATZ 264
#define T_MSATZ 265
#define T_RSATZ 266
#define T_TSATZ 267
#define T_WSATZ 268
#define T_ESATZ 269
#define T_IDENT 270
#define T_BSATZ 271
#define T_ISATZ 272
#define T_CSATZ 273
#define T_VSATZ 274
#define T_HRELSATZ 275
#define T_KRELSATZ 276
#define T_BRELSATZ 277
#define T_KOSATZ 278
#define T_HEXINTEGER 279
#define T_ABGLEICH 280
#define T_IMPORT 281
#define T_KSATZ 282
#define T_HSATZ 283
#define T_OFFSET 284
#define T_SCALE 285
#define T_ENTRY 286
#define T_PBDNAME 287
#define T_ENTRYROSYS 288
#define T_ENTRYRO 289
#define T_ENTRYSYS 290
#define T_FLOAT 291
YYSTYPE yylval, yyval;
#define YYERRCODE 256


#define YYACCEPT        return(0)
#define YYABORT         return(1)

void yyerror (char *string) 
{
ERROR_PARAMETER param;

	param.iLineNumber = yylineno;
	param.pString = string;
	param.pFile = cbInFile;
	db_error (ESYNTX, ASCPARSER, (DWORD)&param);
}

int db_error (int iError, int iRoutine, DWORD dwData)
{
int R = EOKAY;

	DEX_SetError (R, iRoutine, iError, (void *)dwData);

return R;
}

// Headerverwaltung -----------------------------------------------------------
static 
bool GetAllKoeffs (HPROJECT hPr)
{
	Koeff11 = HeaderEntryX(Koeff11Key, hPr).EntryDouble(1.0);
	Koeff12 = HeaderEntryX(Koeff12Key, hPr).EntryDouble(0.0);
	Koeff21 = HeaderEntryX(Koeff21Key, hPr).EntryDouble(0.0);
	Koeff22 = HeaderEntryX(Koeff22Key, hPr).EntryDouble(1.0);
	OffsetX = HeaderEntryX(OffsetXKey, hPr).EntryDouble(0.0);
	OffsetY = HeaderEntryX(OffsetYKey, hPr).EntryDouble(0.0);

// wieder invertieren
	if (EvalKoeffs (&Koeff11, &Koeff12, &Koeff21, &Koeff22) != EOKAY)
		return false;

	return true;
}

static 
bool toWriteScaleProject ()
{
	if (fWasScaleProject) return false;

	fWasScaleProject = true;

	if (fWasOffsetProject)
		return fWriteScaleProject;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (HACTPROJECT, Koeff11Key, dTmp))
			fWriteOffsetProject = true;
		else {
			fWriteOffsetProject = false;
			GetAllKoeffs(HACTPROJECT);
		}
		return fWriteOffsetProject;
	}
}

static 
bool toWriteOffsetProject ()
{
	if (fWasOffsetProject) return false;

	fWasOffsetProject = true;

	if (fWasScaleProject)
		return fWriteOffsetProject;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (HACTPROJECT, Koeff11Key, dTmp))
			fWriteScaleProject = true;
		else {
			fWriteScaleProject = false;
			GetAllKoeffs (HACTPROJECT);
		}
		return fWriteScaleProject;
	}
}

static 
bool toWriteScale ()
{
	if (fWasScale) return false;

	fWasScale = true;

	if (!DEX_GetTRiASDataSourceEx(g_hPr))
		return true;		// keine TRiAS-GeoDB

	if (fWasOffset)
		return fWriteScale;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (g_hPr, Koeff11Key, dTmp))
			fWriteOffset = true;
		else {
			fWriteOffset = false;
			GetAllKoeffs(g_hPr);
		}
		return fWriteOffset;
	}
}

static 
bool toWriteOffset ()
{
	if (fWasOffset) return false;

	fWasOffset = true;

	if (!DEX_GetTRiASDataSourceEx(g_hPr))
		return true;		// keine TRiAS-GeoDB

	if (fWasScale)
		return fWriteOffset;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (g_hPr, Koeff11Key, dTmp))
			fWriteScale = true;
		else {
			fWriteScale = false;
			GetAllKoeffs (g_hPr);
		}
		return fWriteScale;
	}
}

void InitAllEnvironment (void)
{
	on = 0;			// Objektnummer
	lgi = -1;		// Anzahl der Koordinatenpaare
	maxgi = MAXGI;

	curr_mi = &mi[-1];	// Merkmalsfeldzeiger */
	curr_mi_text = (char *)&mi[5];	// Merkmalsfeldzeiger fuer Text

	mi_count = 3;		// Zähler der I*4 Merkmalsfelder

// sonstige Variablen ---------------------------------------------------------
	mi_werte = 0;		// Anzahl der einzulesenden Merkmalswerte
	satz_nr = 0;		// Nummer des Objektes im ASCII-File
	objekt_nr = 0;		// Nummer des Satzes im ASCII-File

	guid[0] = '\0';		// ObjektGuid
	
// globale Daten --------------------------------------------------------------
	eps = -1;			// Testtoleranz 

	d_flag = true;		// Identifikator dezimal
	md_flag = true;		// Merkmale dezimal

// Abgleichsparameter
	g_fImportObj = true;		// Objekt standardmäßig vollständig importieren

	g_fAbglGeom = false;		// Geometrie abgleichen
	g_fAbglAttr = false;		// Attribute abgleichen

	g_fAbglOks = false;			// Objektklasse abgleichen
	g_ulOksFromAttr = 0L;		// Objektklasse hier entnehmen

	g_ulOksToAttr = 0L;		// bisherige Oks hier ablegen

// TransformationsParameter ---------------------------------------------------
	Koeff11 = 1.0;
	Koeff12 = 0.0;
	Koeff21 = 0.0;
	Koeff22 = 1.0;
	OffsetX = 0.0;
	OffsetY = 0.0;

	fFirstIdent = true;
	fFirstMCode = true;

// Scale/Offset verwalten
	fWasScaleProject = false;
	fWasOffsetProject = false;
	fWriteOffsetProject = false;
	fWriteScaleProject = false;	

	fWasScale = false;
	fWasOffset = false;
	fWriteOffset = false;
	fWriteScale = false;	

	InitLexer();		// LEX rücksetzen
	yylineno = 0;

// Unique IdentMCodes rücksetzen
	g_ulOrgUniqueId = g_ulOldUniqueId = g_ulUniqueId = 0L;
}

bool ImportHeader (LPCSTR pcKey, LPCSTR pcData, DWORD dwStyle)
{
char KeyString[17];
int len;

	memset (KeyString, ' ', 16);
	KeyString[16] = '\0';

	strncpy (KeyString, pcKey, 16);
	if ((len = strlen (KeyString)) < 16)
		KeyString[len] = ' ';

	if (!strcmp (KeyString, ScaleKey)) {
	// zuerst in Datenquelle nachsehen
		if (!toWriteScale()) 
			return true;

	// ScaleZeile als Entry
	double f11, f12, f21, f22;

		sscanf (pcData, "%lf%lf%lf%lf", &f11, &f12, &f21, &f22);
		Koeff11 = f11;
		Koeff12 = f12;
		Koeff21 = f21;
		Koeff22 = f22;
		if (EvalKoeffs (&f11, &f12, &f21, &f22) != EOKAY)
			return false;

		if (DEX_GetTRiASDataSourceEx(g_hPr)) {
			PutHdFlt (g_hPr, f11, Koeff11Key, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, f12, Koeff12Key, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, f21, Koeff21Key, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, f22, Koeff22Key, true, HEADER_SYSTEMRO);
		}

	// evtl. auch im Projekt testen
		if (!toWriteScaleProject()) 
			return true;

		PutHdFlt (HACTPROJECT, f11, Koeff11Key, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, f12, Koeff12Key, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, f21, Koeff21Key, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, f22, Koeff22Key, true, HEADER_SYSTEMRO);
		return true;
	} 
	if (!strcmp (KeyString, OffsetKey)) {
	// OffsetZeile als Entry
		if (!toWriteOffset()) 
			return true;

		sscanf (pcData, "%lf%lf", &OffsetX, &OffsetY);

		if (DEX_GetTRiASDataSourceEx(g_hPr)) {
			PutHdFlt (g_hPr, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
		}

	// evtl. auch in Projekt schreiben
		if (!toWriteOffsetProject()) 
			return true;

		PutHdFlt (HACTPROJECT, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
		return true;
	}

// Zahlenbasis für Identifikator einstellen evtl. aus Header
	if (!strcmp (KeyString, IdentBase)) {
	ULONG ulIdBase = 10;

		if (!GetHdULONG (g_hPr, IdentBase, ulIdBase)) 
			d_flag = (atoi (pcData) == 10) ? true : false;
		else
			d_flag = (ulIdBase == 10) ? true : false;
	}

// Zahlenbasis für Merkmale einstellen (Hex hat Vorrang)
	if (md_flag && !strcmp (KeyString, MCodeBase)) 
		md_flag = (atoi (pcData) == 10);

// spezielle Auswertung des UniqueIdents
	if (!strcmp (KeyString, UniqueIdent)) {
		g_ulUniqueId = strtoul (pcData, NULL, 10);

	unsigned long ulVal = 0;

		g_ulOrgUniqueId = g_ulUniqueId;
		if (GetHdULONG (g_hPr, UniqueIdent, ulVal) && 0 != ulVal)
			g_ulOrgUniqueId = ulVal;
	}

// ansonsten normale Behandlung
	PutHdString (g_hPr, (char *)pcData, (char *)pcKey, false, dwStyle);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// nachsehen, ob es diesen Ident schon gibt
ErrCode IdentIsDefined (long lIdent)
{
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = NULL;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 0;

// PBD-Info holen
	return DEX_GetPBDDataEx (g_hPr, pbdData);
}

///////////////////////////////////////////////////////////////////////////////
// UIdentMCodes sicherstellen
void EnsureUIdentMCodes()
{
char cbBuffer[64];

	if (0L == g_ulUniqueId) {
		if (md_flag) 
			g_ulOrgUniqueId = g_ulUniqueId = 51200000L;
		else
			g_ulOrgUniqueId = g_ulUniqueId = 0x51200000L;

		ultoa (g_ulUniqueId, cbBuffer, 10);
		PutHdString (g_hPr, cbBuffer, UniqueIdent, true, HEADER_SYSTEMRO);
	}

	if (0L == g_ulOldUniqueId) {
		if (md_flag) 
			g_ulOldUniqueId = 51300000L;
		else
			g_ulOldUniqueId = 0x51300000L;

		ultoa (g_ulOldUniqueId, cbBuffer, 10);
		PutHdString (g_hPr, cbBuffer, OldUniqueIdent, true, HEADER_SYSTEMRO);
	}
}

#include <stdio.h>
FILE *yytfilep;
char *yytfilen;
int yytflag = 0;
int svdprd[2];
char svdnams[2][2];

short yyexca[] = {
  -1, 1,
  0, -1,
  -2, 0,
  -1, 7,
  282, 80,
  283, 80,
  -2, 18,
  0,
};

#define YYNPROD 87
#define YYLAST 339

short yyact[] = {
      60,      18,     125,     113,     166,      29,      30,      31,
      20,      25,      23,      24,      26,      72,     148,     129,
      32,      27,      28,     128,     116,      95,      94,      22,
      91,      19,       6,      19,      54,      53,      58,      59,
      55,      56,      57,      18,      34,      49,      46,      29,
      30,      31,      20,      25,      23,      24,      26,      78,
      74,     106,      32,      27,      28,      79,      80,      43,
     104,      22,     102,     123,      68,      19,       6,     120,
      76,      64,      77,      62,      63,     107,      61,     164,
     163,     162,     145,     137,     136,     135,     103,      69,
      70,      67,     111,     110,     109,      87,      65,     159,
     157,     155,     141,     139,     133,     132,     131,     130,
     100,      99,      98,      97,      96,      93,      90,      86,
      36,       5,     144,      73,      48,      45,      42,     143,
      35,      47,     142,     173,     172,     171,     170,     169,
     168,     167,     165,     161,     160,     153,     152,     151,
     150,     149,      50,     147,     146,     134,     127,     122,
     119,     118,     117,     115,      82,     112,     108,     105,
     101,      81,      75,      52,      51,      40,       3,      83,
      84,      89,      88,      38,      92,      37,       7,      92,
      85,      71,      39,      44,      41,      33,      66,      17,
      16,       4,       2,       8,      14,      15,      13,      12,
      11,      10,       9,     114,      21,       1,       0,       0,
       0,       0,       0,       0,      82,     124,       0,       0,
     126,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,      91,      74,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,      87,       0,       0,       0,
     121,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,       0,     158,     156,
     154,     140,     138,
};

short yypact[] = {
    -221,   -1000,    -233,    -255,    -257,   -1000,     139,   -1000,
   -1000,   -1000,    -213,    -230,    -231,   -1000,   -1000,   -1000,
    -231,   -1000,     138,     137,    -256,    -189,    -191,    -173,
    -196,    -243,     136,    -193,    -227,   -1000,   -1000,   -1000,
   -1000,   -1000,     135,    -255,   -1000,   -1000,    -255,   -1000,
   -1000,    -213,   -1000,    -174,    -230,   -1000,    -267,    -231,
   -1000,    -156,    -231,   -1000,   -1000,    -269,    -270,    -157,
    -158,    -159,    -160,    -161,     134,    -201,     133,    -210,
     132,    -175,    -176,    -177,     131,   -1000,   -1000,      -7,
     129,   -1000,    -271,   -1000,     128,     127,     126,      53,
     125,   -1000,   -1000,    -255,   -1000,      49,   -1000,   -1000,
   -1000,      -8,   -1000,   -1000,   -1000,     124,    -272,    -276,
    -162,    -163,    -164,    -165,     123,   -1000,    -182,    -183,
    -184,   -1000,      81,      80,   -1000,      41,    -185,     122,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
   -1000,     121,   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
    -277,     119,     118,     117,     116,     115,   -1000,      79,
      78,      77,     114,   -1000,     113,   -1000,    -186,    -187,
    -188,     112,   -1000,   -1000,    -287,   -1000,   -1000,   -1000,
   -1000,   -1000,     111,   -1000,     110,   -1000,     109,   -1000,
   -1000,   -1000,     108,     107,     106,   -1000,     105,   -1000,
   -1000,   -1000,   -1000,   -1000,   -1000,   -1000,
};

short yypgo[] = {
       0,     181,     180,     104,     178,     177,     176,     175,
     174,     173,     172,     157,     171,     150,     170,     169,
     112,     168,     167,     166,     165,     164,     163,     113,
     110,     109,     108,     161,     160,     103,     153,     102,
     107,
};

short yyr1[] = {
       0,       1,       1,      14,      14,      14,      14,      14,
      16,      16,       3,       3,       3,       3,       3,       3,
       3,       3,       3,       3,       3,       3,       3,      12,
      12,      12,      12,      12,      12,      12,      12,      21,
      21,      22,      22,      23,      23,      10,      10,      13,
       4,       4,       4,       4,       4,       4,       4,       4,
       4,       4,       4,       4,       2,       2,       2,       2,
      17,      17,      18,      18,      18,      18,       5,       6,
       7,      24,      28,      28,      29,      25,      30,      30,
      31,      26,       8,       8,       8,      19,      19,       9,
      15,      15,      11,      27,      27,      32,      20,
};

short yyr2[] = {
       0,       2,       1,       1,       2,       2,       3,       1,
       1,       2,       1,       1,       2,       2,       2,       1,
       1,       1,       1,       1,       2,       1,       2,       7,
       5,       5,       5,       5,       5,       4,       3,       1,
       2,       1,       2,       1,       2,       3,       3,       2,
       6,       5,       6,       5,       6,       5,       3,       5,
       4,       5,       4,       3,       1,       1,       1,       1,
       3,       3,       3,       3,       3,       4,       6,       6,
       6,       3,       1,       2,       1,       3,       1,       2,
       1,       3,       5,       4,       3,       1,       1,       2,
       1,       2,       2,       1,       2,       2,       2,
};

short yychk[] = {
   -1000,      -1,     -14,     -13,     -15,      -3,     283,     -11,
     -12,      -4,      -5,      -6,      -7,      -8,     -10,      -9,
     -17,     -18,     256,     282,     263,      -2,     278,     265,
     266,     264,     267,     272,     273,     260,     261,     262,
     271,     -20,     269,     -16,      -3,     -11,     -13,     -11,
      10,     -21,     -24,     268,     -22,     -25,     268,     -23,
     -26,     268,     -23,      10,      10,     285,     284,     288,
     289,     290,     286,     287,     256,     259,     256,     259,
     256,     259,     -19,     277,     256,     275,     276,     -27,
     256,     -32,     291,      10,     257,     259,     274,     280,
     281,      10,      -3,     -16,     -24,     -28,     -29,     259,
     -25,     -30,     -31,     291,     -26,     257,     291,     291,
     257,     257,     257,     257,     257,      10,     259,     279,
     257,      10,     259,     279,      10,     259,     259,     259,
      10,      10,     -32,      10,     291,      10,      10,      10,
      10,     259,      10,      10,     -29,      10,     -31,      10,
     291,     291,     257,     257,     257,     257,      10,     259,
     259,     259,     257,      10,     257,      10,      73,      70,
      65,     259,      10,      10,     291,      10,      10,      10,
      10,      10,     257,      10,     257,      10,     257,      10,
      10,      10,     259,     259,     259,      10,     291,      10,
      10,      10,      10,      10,      10,      10,
};

short yydef[] = {
       0,      -2,       2,       3,       0,       7,       0,      -2,
      10,      11,       0,       0,       0,      15,      16,      17,
      19,      21,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,      52,      53,      54,
      55,       1,       0,       4,       8,      18,       5,      81,
      39,      12,      31,       0,      13,      33,       0,      14,
      35,       0,      20,      22,      82,       0,       0,       0,
       0,       0,       0,       0,       0,       0,       0,       0,
       0,       0,       0,       0,       0,      77,      78,       0,
       0,      83,       0,      79,       0,       0,       0,       0,
       0,      86,       9,       6,      32,       0,      66,      68,
      34,       0,      70,      72,      36,       0,       0,       0,
       0,       0,       0,       0,       0,      30,       0,       0,
       0,      46,       0,       0,      51,       0,       0,       0,
      76,      37,      84,      38,      85,      56,      57,      58,
      59,       0,      60,      65,      67,      69,      71,      73,
       0,       0,       0,       0,       0,       0,      29,       0,
       0,       0,       0,      48,       0,      50,       0,       0,
       0,       0,      75,      61,       0,      24,      25,      26,
      27,      28,       0,      41,       0,      43,       0,      45,
      47,      49,       0,       0,       0,      74,       0,      40,
      42,      44,      62,      63,      64,      23,
};

short *yyxi;
/*****************************************************************/
/* PCYACC LALR parser driver routine -- a table driven procedure */
/* for recognizing sentences of a language defined by the        */
/* grammar that PCYACC analyzes. An LALR parsing table is then   */
/* constructed for the grammar and the skeletal parser uses the  */
/* table when performing syntactical analysis on input source    */
/* programs. The actions associated with grammar rules are       */
/* inserted into a switch statement for execution.               */
/*****************************************************************/


#ifndef YYMAXDEPTH
#define YYMAXDEPTH 200
#endif
#ifndef YYREDMAX
#define YYREDMAX 1000
#endif
#define PCYYFLAG -1000
#define WAS0ERR 0
#define WAS1ERR 1
#define WAS2ERR 2
#define WAS3ERR 3
#define yyclearin pcyytoken = -1
#define yyerrok   pcyyerrfl = 0
YYSTYPE yyv[YYMAXDEPTH];     /* value stack */
int pcyyerrct = 0;           /* error count */
int pcyyerrfl = 0;           /* error flag */
int redseq[YYREDMAX];
int redcnt = 0;
int pcyytoken = -1;          /* input token */


yyparse()
{
  int statestack[YYMAXDEPTH]; /* state stack */
  int      j, m;              /* working index */
  YYSTYPE *yypvt;
  int      tmpstate, tmptoken, *yyps, n;
  YYSTYPE *yypv;


  tmpstate = 0;
  pcyytoken = -1;
#ifdef YYDEBUG
  tmptoken = -1;
#endif
  pcyyerrct = 0;
  pcyyerrfl = 0;
  yyps = &statestack[-1];
  yypv = &yyv[-1];


  enstack:    /* push stack */
#ifdef YYDEBUG
    printf("at state %d, next token %d\n", tmpstate, tmptoken);
#endif
    if (++yyps - &statestack[YYMAXDEPTH-1] > 0) {
      yyerror("pcyacc internal stack overflow");
      return(1);
    }
    *yyps = tmpstate;
    ++yypv;
    *yypv = yyval;


  newstate:
    n = yypact[tmpstate];
    if (n <= PCYYFLAG) goto defaultact; /*  a simple state */


    if (pcyytoken < 0) if ((pcyytoken=yylex()) < 0) pcyytoken = 0;
    if ((n += pcyytoken) < 0 || n >= YYLAST) goto defaultact;


    if (yychk[n=yyact[n]] == pcyytoken) { /* a shift */
#ifdef YYDEBUG
      tmptoken  = pcyytoken;
#endif
      pcyytoken = -1;
      yyval = yylval;
      tmpstate = n;
      if (pcyyerrfl > 0) --pcyyerrfl;
      goto enstack;
    }


  defaultact:


    if ((n=yydef[tmpstate]) == -2) {
      if (pcyytoken < 0) if ((pcyytoken=yylex())<0) pcyytoken = 0;
      for (yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=tmpstate); yyxi += 2);
      while (*(yyxi+=2) >= 0) if (*yyxi == pcyytoken) break;
      if ((n=yyxi[1]) < 0) { /* an accept action */
        if (yytflag) {
          int ti; int tj;
          yytfilep = fopen(yytfilen, "w");
          if (yytfilep == NULL) {
            fprintf(stderr, "Can't open t file: %s\n", yytfilen);
            return(0);          }
          for (ti=redcnt-1; ti>=0; ti--) {
            tj = svdprd[redseq[ti]];
            while (strcmp(svdnams[tj], "$EOP"))
              fprintf(yytfilep, "%s ", svdnams[tj++]);
            fprintf(yytfilep, "\n");
          }
          fclose(yytfilep);
        }
        return (0);
      }
    }


    if (n == 0) {        /* error situation */
      switch (pcyyerrfl) {
        case WAS0ERR:          /* an error just occurred */
          yyerror("syntax error");
          yyerrlab:
            ++pcyyerrct;
        case WAS1ERR:
        case WAS2ERR:           /* try again */
          pcyyerrfl = 3;
	   /* find a state for a legal shift action */
          while (yyps >= statestack) {
	     n = yypact[*yyps] + YYERRCODE;
	     if (n >= 0 && n < YYLAST && yychk[yyact[n]] == YYERRCODE) {
	       tmpstate = yyact[n];  /* simulate a shift of "error" */
	       goto enstack;
            }
	     n = yypact[*yyps];


	     /* the current yyps has no shift on "error", pop stack */
#ifdef YYDEBUG
            printf("error: pop state %d, recover state %d\n", *yyps, yyps[-1]);
#endif
	     --yyps;
	     --yypv;
	   }


	   yyabort:
            if (yytflag) {
              int ti; int tj;
              yytfilep = fopen(yytfilen, "w");
              if (yytfilep == NULL) {
                fprintf(stderr, "Can't open t file: %s\n", yytfilen);
                return(1);              }
              for (ti=1; ti<redcnt; ti++) {
                tj = svdprd[redseq[ti]];
                while (strcmp(svdnams[tj], "$EOP"))
                  fprintf(yytfilep, "%s ", svdnams[tj++]);
                fprintf(yytfilep, "\n");
              }
              fclose(yytfilep);
            }
	     return(1);


	 case WAS3ERR:  /* clobber input char */
#ifdef YYDEBUG
          printf("error: discard token %d\n", pcyytoken);
#endif
          if (pcyytoken == 0) goto yyabort; /* quit */
	   pcyytoken = -1;
	   goto newstate;      } /* switch */
    } /* if */


    /* reduction, given a production n */
#ifdef YYDEBUG
    printf("reduce with rule %d\n", n);
#endif
    if (yytflag && redcnt<YYREDMAX) redseq[redcnt++] = n;
    yyps -= yyr2[n];
    yypvt = yypv;
    yypv -= yyr2[n];
    yyval = yypv[1];
    m = n;
    /* find next state from goto table */
    n = yyr1[n];
    j = yypgo[n] + *yyps + 1;
    if (j>=YYLAST || yychk[ tmpstate = yyact[j] ] != -n) tmpstate = yyact[yypgo[n]];
    switch (m) { /* actions associated with grammar rules */
      
      case 2:{
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      			db_error (ENOEND, ASCPARSER, yypvt[-0].numtok.num_line);
      			YYACCEPT;
      		} break;
      case 7:{
      			db_error (ENOHD, ASCPARSER, yypvt[-0].numtok.num_line);
      			YYABORT;
      		} break;
      case 22:{
      			yyerrok;
      			db_error (EBADRC, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 23:{
      			if (!toWriteScale()) 
      				break;
      
			Koeff11 = yypvt[-4].flttok.fltnum;
      			Koeff12 = yypvt[-3].flttok.fltnum;
      			Koeff21 = yypvt[-2].flttok.fltnum;
      			Koeff22 = yypvt[-1].flttok.fltnum;
      			if (EvalKoeffs (&yypvt[-4].flttok.fltnum, &yypvt[-3].flttok.fltnum, &yypvt[-2].flttok.fltnum, &yypvt[-1].flttok.fltnum) != EOKAY)
      				YYABORT;
      
			if (DEX_GetTRiASDataSourceEx (g_hPr)) {
      			// evtl. DatenquellenHeader schreiben
      				PutHdFlt (g_hPr, yypvt[-4].flttok.fltnum, Koeff11Key, true, HEADER_SYSTEMRO);
      				PutHdFlt (g_hPr, yypvt[-3].flttok.fltnum, Koeff12Key, true, HEADER_SYSTEMRO);
      				PutHdFlt (g_hPr, yypvt[-2].flttok.fltnum, Koeff21Key, true, HEADER_SYSTEMRO);
      				PutHdFlt (g_hPr, yypvt[-1].flttok.fltnum, Koeff22Key, true, HEADER_SYSTEMRO);
      			}
      
		// jetzt Projekt behandeln
      			if (!toWriteScaleProject()) 
      				break;
      
			PutHdFlt (HACTPROJECT, yypvt[-4].flttok.fltnum, Koeff11Key, true, HEADER_SYSTEMRO);
      			PutHdFlt (HACTPROJECT, yypvt[-3].flttok.fltnum, Koeff12Key, true, HEADER_SYSTEMRO);
      			PutHdFlt (HACTPROJECT, yypvt[-2].flttok.fltnum, Koeff21Key, true, HEADER_SYSTEMRO);
      			PutHdFlt (HACTPROJECT, yypvt[-1].flttok.fltnum, Koeff22Key, true, HEADER_SYSTEMRO);
      		} break;
      case 24:{
      
		// evtl. DatenquellenHeader schreiben
      			if (!toWriteOffset()) 
      				break;
      
			OffsetX = yypvt[-2].flttok.fltnum;
      			OffsetY = yypvt[-1].flttok.fltnum;
      			if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      				PutHdFlt (g_hPr, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
      				PutHdFlt (g_hPr, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
      			}
      
		// jetzt Projekt behandeln
      			if (!toWriteOffsetProject()) 
      				break;
      			
      			PutHdFlt (HACTPROJECT, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
      			PutHdFlt (HACTPROJECT, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
      		} break;
      case 25:{
      			if (!ImportHeader (yypvt[-2].strtok.string, yypvt[-1].strtok.string, HEADER_SYSTEMRO))
      				YYABORT;
      		} break;
      case 26:{
      			if (!ImportHeader (yypvt[-2].strtok.string, yypvt[-1].strtok.string, HEADER_READONLY))
      				YYABORT;
      		} break;
      case 27:{
      			if (!ImportHeader (yypvt[-2].strtok.string, yypvt[-1].strtok.string, HEADER_SYSTEM))
      				YYABORT;
      		} break;
      case 28:{
      			if (!ImportHeader (yypvt[-2].strtok.string, yypvt[-1].strtok.string, HEADER_NORMAL))
      				YYABORT;
      		} break;
      case 29:{
      			PutHdString (g_hPr, yypvt[-1].strtok.string, PbdNameKey, false, HEADER_SYSTEMRO);
      		} break;
      case 30:{
      			yyerrok;
      			db_error (EBADRC, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 38:{
      			yyerrok;
      			db_error (EKOORD, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 39:{
      		// aktive Datenquelle bsorgen
      			g_hPr = DEX_GetDataSourceHandle();
      			_ASSERTE(NULL != g_hPr);
      
		// Standardwerte in DB-Header setzen
      //			strcpy (header, yypvt[-1].strtok.string);     
      
		IStorage *pIStg = NULL;
      
			if (DEX_GetDataSourceStorage (g_hPr, pIStg))
      				pIStg -> Release();
      			else {
      			time_t actTime;
      
				time (&actTime);
      				PutHdString (g_hPr, ctime (&actTime), ZeitKey, false);
      //				PutHdString ("ungeprüft", DBStatusKey);
      //				PutHdString ("Nein", VerschnittKey, false);
      			}
      
			if (DEX_GetDBVersionEx(g_hPr) >= 0x05000008L && DEX_GetTRiASDataSourceEx(g_hPr)) {
      				PutHdString (g_hPr, "99999000", ObjVisInfoMCode, false, HEADER_SYSTEMRO);
      				PutHdString (g_hPr, "99999100", TextObjMCode, false, HEADER_SYSTEMRO);
      			}
      			lTextObjMCode = 99999100L;
      	
      		// Flag initialisieren
      			fFirstIdent = true;
      			fFirstMCode = true;
      		} break;
      case 40:{
      			if (!d_flag) 	// Ident ist Hexadezimal
      				yypvt[-3].numtok.intnum = MakeHex (yypvt[-3].numtok.intnum);
      
	l_Ident_typ2:
      			if (fFirstIdent) {
      			// Zahlensystem für Header voreinstellen
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      					if (d_flag) PutHdString (g_hPr, "10", IdentBase, false, HEADER_SYSTEMRO);
      					else	    PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				}
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      				fFirstIdent = false;
      
			// wenn noch kein Unique Ident definiert ist, dann dieses hier tun
      				EnsureUIdentMCodes();
      			}
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      
		/* Pruefen, ob naechstes Objekt gespeichert werden soll */
      			if (first  != 0 && first > ++objekt_nr) {
      			/* Objekt noch nicht speichern, weiter */
      				skip_lines ("PLF");
      				satz_nr = 0;    /* Objekt bereits gespeichert */
      				break;          /* abbrechen */
      			}
      			if (last != 0 && last < objekt_nr)
      			/* keine Objekte mehr speichern */
      				YYACCEPT;
      		/* Plausibilitaetskontrolle */
      			if ((yypvt[-5].numtok.intnum == O_PUNKT && yypvt[-2].numtok.intnum != 1)
      			 || (yypvt[-5].numtok.intnum == O_LINIE && yypvt[-2].numtok.intnum < 2)) {
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      		/* Naechstes Objekt beginnen */
      			init_new_object ();
      			strcpy (guid, yypvt[-1].strtok.string);
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-4].numtok.intnum;            /* lfde Nummer in ASCII-Datei */
      			sta[1] = yypvt[-5].numtok.intnum;     /* Objekttyp */
      			koord_paare = yypvt[-2].numtok.intnum; /* Stuetzpunktanzahl */
      			{
      			// Ident existiert evtl. bereits in Zuordnungstabelle
      				ltoa (yypvt[-3].numtok.intnum, header, d_flag ? 10 : 16);
      
			long lIdent = 0L;
      			HRESULT hr = IdentFromClassX (g_hPr, header, (ULONG *)&lIdent);
      
				if (S_OK == hr) {	// existiert bereits als Ident
      					id = lIdent;
      					break;
      				}
      				if (S_FALSE == hr) {
      				ErrCode RC = IdentIsDefined(lIdent);
      
					if (RC != EC_OKAY && !DEX_isIdentUsedEx(g_hPr, lIdent)) 
      					// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
      						hr = IdentFromClassX (g_hPr, header, (ULONG *)&lIdent, true);
      				}
      				if (FAILED(hr) || 0 == lIdent) 
      					break;			// abbrechen
      
			// hier ist der neue Ident
      				id = lIdent;
      			}
      		} break;
      case 41:{
      			if (!d_flag) 	// Ident ist Hexadezimal
      				yypvt[-2].numtok.intnum = MakeHex (yypvt[-2].numtok.intnum);
      
	l_Ident:
      			if (fFirstIdent) {
      			// Zahlensystem für Header voreinstellen
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      					if (d_flag) PutHdString (g_hPr, "10", IdentBase, false, HEADER_SYSTEMRO);
      					else	    PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				}
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      				fFirstIdent = false;
      
			// wenn noch kein Unique Ident definiert ist, dann dieses hier tun
      				EnsureUIdentMCodes();
      			}
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      
		/* Pruefen, ob naechstes Objekt gespeichert werden soll */
      			if (first  != 0 && first > ++objekt_nr) {
      			/* Objekt noch nicht speichern, weiter */
      				skip_lines ("PLF");
      				satz_nr = 0;    /* Objekt bereits gespeichert */
      				break;          /* abbrechen */
      			}
      			if (last != 0 && last < objekt_nr)
      			/* keine Objekte mehr speichern */
      				YYACCEPT;
      		/* Plausibilitaetskontrolle */
      			if ((yypvt[-4].numtok.intnum == O_PUNKT && yypvt[-1].numtok.intnum != 1)
      			 || (yypvt[-4].numtok.intnum == O_LINIE && yypvt[-1].numtok.intnum < 2)) {
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-3].numtok.intnum;            /* lfde Nummer in ASCII-Datei */
      			sta[1] = yypvt[-4].numtok.intnum;     /* Objekttyp */
      			koord_paare = yypvt[-1].numtok.intnum; /* Stuetzpunktanzahl */
      			{
      			// Ident existiert evtl. bereits in Zuordnungstabelle
      				ltoa (yypvt[-2].numtok.intnum, header, d_flag ? 10 : 16);
      
			long lIdent = 0L;
      			HRESULT hr = IdentFromClassX (g_hPr, header, (ULONG *)&lIdent);
      
				if (S_OK == hr) {	// existiert bereits als Ident
      					id = lIdent;
      					break;
      				}
      				if (S_FALSE == hr) {
      				ErrCode RC = IdentIsDefined(lIdent);
      
					if (RC != EC_OKAY && !DEX_isIdentUsedEx(g_hPr, lIdent)) 
      					// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
      						hr = IdentFromClassX (g_hPr, header, (ULONG *)&lIdent, true);
      				}
      				if (FAILED(hr) || 0 == lIdent) 
      					break;			// abbrechen
      
			// hier ist der neue Ident
      				id = lIdent;
      			}
      		} break;
      case 42:{
      			if (d_flag && !fFirstIdent) {
      				yyerror("Inkonsistente Identifikator-Zahlenbasis");
      				YYABORT;
      			}
      			if (d_flag && fFirstIdent) {
      				d_flag = false;
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) 
      					PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      			}
      			goto l_Ident_typ2;
      		} break;
      case 43:{
      			if (d_flag && !fFirstIdent) {
      				yyerror("Inkonsistente Identifikator-Zahlenbasis");
      				YYABORT;
      			}
      			if (d_flag && fFirstIdent) {
      				d_flag = false;
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) 
      					PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      			}
      			goto l_Ident;
      		} break;
      case 44:{
      			if (fFirstIdent) {
      			// Zahlensystem für Header voreinstellen
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      					if (d_flag) PutHdString (g_hPr, "10", IdentBase, false, HEADER_SYSTEMRO);
      					else	    PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				}
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      				fFirstIdent = false;
      
			// wenn noch kein Unique Ident definiert ist, dann dieses hier tun
      				EnsureUIdentMCodes();
      			}
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      
		/* Pruefen, ob naechstes Objekt gespeichert werden soll */
      			if (first  != 0 && first > ++objekt_nr) {
      			/* Objekt noch nicht speichern, weiter */
      				skip_lines ("PLF");
      				satz_nr = 0;    /* Objekt bereits gespeichert */
      				break;          /* abbrechen */
      			}
      			if (last != 0 && last < objekt_nr)
      			/* keine Objekte mehr speichern */
      				YYACCEPT;
      
		/* Plausibilitaetskontrolle */
      			if ((yypvt[-5].numtok.intnum == O_PUNKT && yypvt[-2].numtok.intnum != 1)
      			 || (yypvt[-5].numtok.intnum == O_LINIE && yypvt[-2].numtok.intnum < 2)) {
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      
		/* Naechstes Objekt beginnen */
      			init_new_object ();
      			strcpy (guid, yypvt[-1].strtok.string);
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-4].numtok.intnum;		/* lfde Nummer in ASCII-Datei */
      			sta[1] = yypvt[-5].numtok.intnum;			/* Objekttyp */
      			koord_paare = yypvt[-2].numtok.intnum;	/* Stuetzpunktanzahl */
      			{
      			// Ident existiert evtl. bereits in Zuordnungstabelle
      			long lIdent = 0L;
      			HRESULT hr = IdentFromClassX (g_hPr, yypvt[-3].strtok.string, (ULONG *)&lIdent);
      
				if (S_OK == hr) {// existiert bereits als Ident
      					id = lIdent;
      					break;
      				}
      
				if (S_FALSE == hr) {
      				ErrCode RC = IdentIsDefined(lIdent);
      
					if (RC != EC_OKAY && !DEX_isIdentUsedEx(g_hPr, lIdent)) 
      					// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
      						hr = IdentFromClassX (g_hPr, yypvt[-3].strtok.string, (ULONG *)&lIdent, true);
      				}
      				if (FAILED(hr) || 0 == lIdent) 
      					break;			// abbrechen
      
			// hier ist der neue Ident
      				id = lIdent;
      			}
      		} break;
      case 45:{
      			if (fFirstIdent) {
      			// Zahlensystem für Header voreinstellen
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      					if (d_flag) PutHdString (g_hPr, "10", IdentBase, false, HEADER_SYSTEMRO);
      					else	    PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				}
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      
				fFirstIdent = false;
      
			// wenn noch kein Unique Ident definiert ist, dann dieses hier tun
      				EnsureUIdentMCodes();
      			}
      
		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      
		/* Pruefen, ob naechstes Objekt gespeichert werden soll */
      			if (first  != 0 && first > ++objekt_nr) {
      			/* Objekt noch nicht speichern, weiter */
      				skip_lines ("PLF");
      				satz_nr = 0;    /* Objekt bereits gespeichert */
      				break;          /* abbrechen */
      			}
      			if (last != 0 && last < objekt_nr)
      			/* keine Objekte mehr speichern */
      				YYACCEPT;
      
		/* Plausibilitaetskontrolle */
      			if ((yypvt[-4].numtok.intnum == O_PUNKT && yypvt[-1].numtok.intnum != 1)
      			 || (yypvt[-4].numtok.intnum == O_LINIE && yypvt[-1].numtok.intnum < 2)) {
      			/* Punkt-EO und nicht ein Koordinatenpaar oder
      			   Linien-EO und weniger als zwei Koordinatenpaare */
      				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
      				break;
      			}
      
		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-3].numtok.intnum;		/* lfde Nummer in ASCII-Datei */
      			sta[1] = yypvt[-4].numtok.intnum;			/* Objekttyp */
      			koord_paare = yypvt[-1].numtok.intnum;	/* Stuetzpunktanzahl */
      			{
      			// Ident existiert evtl. bereits in Zuordnungstabelle
      			long lIdent = 0L;
      			HRESULT hr = IdentFromClassX (g_hPr, yypvt[-2].strtok.string, (ULONG *)&lIdent);
      
				if (S_OK == hr) {// existiert bereits als Ident
      					id = lIdent;
      					break;
      				}
      
				if (S_FALSE == hr) {
      				ErrCode RC = IdentIsDefined(lIdent);
      
					if (RC != EC_OKAY && !DEX_isIdentUsedEx(g_hPr, lIdent)) 
      					// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
      						hr = IdentFromClassX (g_hPr, yypvt[-2].strtok.string, (ULONG *)&lIdent, true);
      				}
      				if (FAILED(hr) || 0 == lIdent) 
      					break;			// abbrechen
      
			// hier ist der neue Ident
      				id = lIdent;
      			}
      		} break;
      case 46:{
      		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      
			guid[0] = '\0';
      
		/* Pruefen, ob naechstes Objekt gespeichert werden soll */
      			if (first  != 0 && first > ++objekt_nr) {
      			/* Objekt noch nicht speichern, weiter */
      				skip_lines ("PLFB");
      				satz_nr = 0;    /* Objekt bereits gespeichert */
      				break;          /* abbrechen */
      			}
      			if (last != 0 && last < objekt_nr)
      			/* keine Objekte mehr speichern */
      				YYACCEPT;
      		/* Fehler behandeln */
      			yyerrok;
      			switch ((int)yypvt[-2].numtok.intnum) {
      			case O_PUNKT:
      				error_skip_lines ("PLFB", EPKTID); break;
      			case O_LINIE:
      				error_skip_lines ("PLFB", ELINID); break;
      			case O_FLAECHE:
      				error_skip_lines ("PLFB", EFLID); break;
      			}
      		} break;
      case 47:{
      			if (!d_flag) 	// Ident ist Hexadezimal
      				yypvt[-2].numtok.intnum = MakeHex (yypvt[-2].numtok.intnum);
      
	l_KOIdent_typ2:
      			if (fFirstIdent) {
      			// Zahlensystem für Header voreinstellen
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      					if (d_flag) PutHdString (g_hPr, "10", IdentBase, false, HEADER_SYSTEMRO);
      					else	    PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				}
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      
			// wenn noch kein Unique Ident definiert ist, dann dieses hier tun
      				EnsureUIdentMCodes();
      				fFirstIdent = false;
      			}
      
		// KomplexObjekt
      		/* Vorhergehendes Objekt bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      			
      			++objekt_nr;
      
		/* Naechstes Objekt beginnen */
      			init_new_object ();
      			strcpy (guid, yypvt[-1].strtok.string);
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-3].numtok.intnum;	/* lfde Nummer in ASCII-Datei */
      			id = yypvt[-2].numtok.intnum;		/* Identifikator */
      			sta[0] = K_OBJEKT;	
      			sta[1] = 0;		/* Objekttyp */
      			koord_paare = 0;	/* Stuetzpunktanzahl */
      		} break;
      case 48:{
      			if (!d_flag) 	// Ident ist Hexadezimal
      				yypvt[-1].numtok.intnum = MakeHex (yypvt[-1].numtok.intnum);
      
	l_KOIdent:
      			if (fFirstIdent) {
      			// Zahlensystem für Header voreinstellen
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      					if (d_flag) PutHdString (g_hPr, "10", IdentBase, false, HEADER_SYSTEMRO);
      					else	    PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				}
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      
			// wenn noch kein Unique Ident definiert ist, dann dieses hier tun
      				EnsureUIdentMCodes();
      				fFirstIdent = false;
      			}
      
		// KomplexObjekt
      		/* Vorhergehendes Objekt bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      			
      			++objekt_nr;
      
		/* Naechstes Objekt beginnen */
      			init_new_object ();
      
		/* Objektparameter setzen */
      			satz_nr = yypvt[-2].numtok.intnum;	/* lfde Nummer in ASCII-Datei */
      			id = yypvt[-1].numtok.intnum;		/* Identifikator */
      			sta[0] = K_OBJEKT;	
      			sta[1] = 0;		/* Objekttyp */
      			koord_paare = 0;	/* Stuetzpunktanzahl */
      		} break;
      case 49:{
      			if (d_flag && !fFirstIdent) {
      				yyerror ("Inkonsistente Identifikator-Zahlenbasis.");
      				YYABORT;
      			}
      			if (d_flag && fFirstIdent) {
      				d_flag = false;
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) 
      					PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      			}
      			goto l_KOIdent_typ2;
      		} break;
      case 50:{
      			if (d_flag && !fFirstIdent) {
      				yyerror ("Inkonsistente Identifikator-Zahlenbasis.");
      				YYABORT;
      			}
      			if (d_flag && fFirstIdent) {
      				d_flag = false;
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) 
      					PutHdString (g_hPr, "16", IdentBase, false, HEADER_SYSTEMRO);
      				PutHdString (HACTPROJECT, "16", IdentBase, false, HEADER_SYSTEMRO);
      			}
      			goto l_KOIdent;
      		} break;
      case 51:{
      		/* Vorhergehendes EO bearbeiten */
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      			
      			guid[0] = '\0';
      			yyerrok;
      			error_skip_lines ("PLFB", EFKID);
      		} break;
      case 52:{       yyval.numtok.intnum = O_PUNKT;    } break;
      case 53:{       yyval.numtok.intnum = O_LINIE;    } break;
      case 54:{       yyval.numtok.intnum = O_FLAECHE;  } break;
      case 55:{	yyval.numtok.intnum = O_TEXTOBJEKT;	} break;
      case 56:{
      		int Len = strlen (yypvt[-1].strtok.string);
      		long wf = 0;
      
			curr_mi = &curr_mi[mi_count];
      			mi_count = 3;
      			curr_mi_text = (char *)&curr_mi[3];
      
			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
      			curr_mi[1] = M_TEXT;
      
		// wie normalen Merkmalswert behandeln
      			if (!strncmp (yypvt[-1].strtok.string, "@@", 2)) {
      				Len -= 2;
      				strncpy (curr_mi_text, yypvt[-1].strtok.string+2, 78);
      				curr_mi_text[min(78, Len)] = '\0';
      
			// Status korrigieren
      				sta[1] = O_TEXTOBJIND;
      			} else {
      				strncpy (curr_mi_text, yypvt[-1].strtok.string, 78);
      				curr_mi_text[min(78, Len)] = '\0';
      			}
      
			curr_mi_text += Len;
      			wf = (Len + (sizeof(long)-1))/sizeof(long);
      
			mi[1] += wf + 3;
      			curr_mi[2] = wf;		// Wiederholungsfaktor
      			mi_count += wf;
      		} break;
      case 57:{
      			curr_mi = &curr_mi[mi_count];
      
			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
      			curr_mi[1] = M_TEXT;
      			curr_mi[2] = -1;		// WF
      			curr_mi[3] = yypvt[-1].numtok.intnum;		// MCode
      
			mi[1] += 4;
      			mi_count = 4;
      
		// Status korrigieren
      			sta[1] = O_TEXTOBJIND;
      		} break;
      case 58:{
      		} break;
      case 59:{
      		// AbgleichsOption
      			g_fImportObj = false;		// nur Abgleich
      
			switch (yypvt[-1].strtok.string[0]) {
      			case 'O':	/* C AO: neue Objektklasse aus Objektklasse des zu importierenden Objektes */
      				g_ulOksFromAttr = 0L;
      				g_fAbglOks = true;
      				break;
      
			case 'G':	/* C AG: Verwenden der Geometrie des zu importierenden Objektes */
      				g_fAbglGeom = true;		// diese beiden schließen sich aus
      				g_fAbglAttr = false;
      				break;
      
			case 'A':	/* C AA: Verwenden der Attribute des zu importierenden Objektes */
      				g_fAbglGeom = false;	// diese beiden schließen sich aus
      				g_fAbglAttr = true;
      				break;
      
			default:
      				yyerror ("Fehlerhafter Abgleichsparameter.");
      				YYABORT;
      				break;
      			}
      		} break;
      case 60:{
      		// ImportOption
      			g_fImportObj = true;		// C I: doch wieder importieren
      		} break;
      case 61:{
      			g_fImportObj = false;		// nur Abgleich
      
			switch (yypvt[-2].strtok.string[0]) {
      			case 'O':		/* Abgleich OKS */
      				{
      					switch (yypvt[-2].strtok.string[1]) {
      					case 'R':	/* C AOR MCode: neue Objektklasse aus einem der angehängten Merkmale */
      						g_ulOksFromAttr = yypvt[-1].numtok.intnum;
      						g_fAbglOks = true;
      						break;
      
					case 'S':	/* C AOS MCode: Bisherige Objektklasse als Merkmal wegschreiben */
      						g_ulOksToAttr = yypvt[-1].numtok.intnum;
      						break;
      
					default:
      						yyerror ("Fehlerhafter Abgleichsparameter.");
      						YYABORT;
      						break;
      					}
      				}
      				break;
      
			default:
      				yyerror ("Fehlerhafter Abgleichsparameter.");
      				YYABORT;
      				break;
      			}
      		} break;
      case 62:{
      			curr_mi = &curr_mi[mi_count];
      			curr_mi[1] = M_INTEGER;         /* Integermerkmale */
      			mi_werte = yypvt[-3].numtok.intnum;		/* Anzahl der I*4 - Werte */
      
labelMerkmal: ;
      			if (!md_flag) 	// MCode ist Hexadezimal
      				yypvt[-4].numtok.intnum = MakeHex (yypvt[-4].numtok.intnum);
      
			if (fFirstMCode) {
      			// Zahlensystem für Header voreinstellen
      				if (DEX_GetTRiASDataSourceEx(g_hPr)) {
      					if (md_flag) PutHdString (g_hPr, "10", MCodeBase, false, HEADER_SYSTEMRO);
      					else	     PutHdString (g_hPr, "16", MCodeBase, false, HEADER_SYSTEMRO);
      				}
      				PutHdString (HACTPROJECT, "16", MCodeBase, false, HEADER_SYSTEMRO);
      				fFirstMCode = false;
      			}
      
		// wenn Unique Ident umgelegt werden muß
      			if ((ULONG)yypvt[-4].numtok.intnum == g_ulUniqueId && g_ulUniqueId != g_ulOrgUniqueId) 
      				yypvt[-4].numtok.intnum = (LONG)g_ulOrgUniqueId;
      			else {
      			// ggf. muß der MCode auf die Zieldatenquelle gemappt werden
      			CMCodeMap::iterator it = g_MCodes.find (yypvt[-4].numtok.intnum);
      
				if (it != g_MCodes.end())
      					yypvt[-4].numtok.intnum = (*it).second;		// entspricht diesem MCode in der Zieldatenquelle
      			}
      
			curr_mi[0] = yypvt[-4].numtok.intnum; /* Merkmalskode */
      			curr_mi[2] = 0;         /* Wiederholungsfaktor loeschen */
      			mi[1] += 3;
      			mi_count = 3;
      			mi_length = yypvt[-1].numtok.intnum;  /* Laenge der Werte */
      		} break;
      case 63:{
      			curr_mi = &curr_mi[mi_count];
      			curr_mi[1] = M_DOUBLE;          /* Floatpointmerkmale */
      			mi_werte = yypvt[-3].numtok.intnum; //*(sizeof(double)/sizeof(long));
      
			goto labelMerkmal;   /* weiter wie fuer M_INTEGER */
      		} break;
      case 64:{
      			curr_mi = &curr_mi[mi_count];
      			curr_mi[1] = M_TEXT;            /* Textmerkmale */
      			curr_mi_text = (char *)&curr_mi[3];
      			mi_werte = (yypvt[-1].numtok.intnum + (sizeof(long)-1))/sizeof(long);
      
			goto labelMerkmal;   /* weiter wie fuer M_INTEGER */
      		} break;
      case 68:{ 
      		// Plausibilitätskontrolle 
      			if (mi_count -3 >= mi_werte) {
      			// Merkmal ueberspringen
      				error_skip_lines ("PLFMRG", EMCNT);
      				break;
      			}
      			curr_mi[mi_count++] = yypvt[-0].numtok.intnum;
      			mi[1]++;
      			curr_mi[2]++;
      		} break;
      case 72:{
      		register int item_size = sizeof(double)/sizeof(long);
      
		// Plausibilitätskontrolle
      			if ((mi_count -3)/(sizeof(double)/sizeof(long)) >= (size_t)mi_werte) 
      			{
      			// Merkmal ueberspringen
      				error_skip_lines ("PLFMRG", EMCNT);
      				break;
      			}
      			
      			*((double *)(&curr_mi[mi_count])) = yypvt[-0].flttok.fltnum;
      			mi[1] += item_size;
      			curr_mi[2]++;           // += item_size;
      			mi_count += item_size;
      		} break;
      case 73:{
      		register int length = 0;
      
		// Plausibilitaetskontrolle
      			if (mi_length <= 0) {
      			// Zu viele Merkmalssaetze
      //				error_skip_lines ("PLFRMG", EMCNT);
      //				break;
      				mi_length = strlen(yypvt[-1].strtok.string);
      			}
      
			strncpy (curr_mi_text, yypvt[-1].strtok.string, 78);
      			curr_mi_text[min(78, mi_length)] = '\0';
      
			length += strlen (curr_mi_text);
      			mi_length -= length;
      			curr_mi_text += length;
      			
      			if (mi_length <= 0) {
      			// Merkmalswerte vollständig gelesen 
      			register int wf = 0;    // Laenge des Textes in I*4
      
				length = curr_mi_text - (char *)&curr_mi[3];
      				wf = (length + sizeof(long)-1)/sizeof(long);
      				if (0 == wf) wf = 1;
      				mi[1] += wf;
      				curr_mi[2] += wf;
      				mi_count += wf;
      			}
      		} break;
      case 74:{
      			if (r_flag) {	// Relationen nicht ignorieren
      			long lON = RetrieveFromTree (yypvt[-1].numtok.intnum);
      
				if (lON != -1)	// Satz existiert wirklich: Relation aufbauen
      					StoreInList (lON, yypvt[-2].numtok.intnum, yypvt[-3].numtok.intnum);
      			}
      		} break;
      case 75:{
      			if (r_flag) {	// Relationen nicht ignorieren
      			long ONr = RetrieveFromTree (yypvt[-1].numtok.intnum);
      
				if (ONr != -1)	// Relation aufbauen
      					StoreInList (ONr, yypvt[-2].numtok.intnum, RTBegleitO);
      			}
      		} break;
      case 76:{
      			yyerrok;
      			db_error (EBREL, ASCPARSER, yypvt[-0].numtok.num_line);
      		} break;
      case 77:{	yyval.numtok.intnum = RTGleich;	} break;
      case 78:{	yyval.numtok.intnum = RTKomplexU;	} break;
      case 82:{
      		int iToCopy = min(strlen(yypvt[-1].strtok.string), sizeof(comment)-1);
      
			strncpy (comment, yypvt[-1].strtok.string, iToCopy);
      			comment[iToCopy] = '\0';
      			
      		// ggf. verbirgt sich hinter diesem Kommentar eine MCode oder eine Klassen
      		// Zuordnung
      		HFEATURE lMCode = 0;
      		char cbClassBuffer[MAX_OKS_LENX];
      		char cbBuffer[_MAX_PATH];
      		char cbFormat[64];
      
			if (1 == sscanf (comment, " AttrDesc(%ld):", &lMCode)) {
      			char *pColon = strchr (comment, ':');
      			
      				_ASSERTE(NULL != pColon);
      
			int iNameLen = strlen(comment) - (pColon-comment) -2;
      
				wsprintf (cbFormat, "%%%dc", iNameLen);
      				if (1 == sscanf (pColon + 2, cbFormat, cbBuffer)) {
      					cbBuffer[iNameLen] = '\0';		// sauber abschließen
      
				CMCodeMap::iterator it = g_MCodes.find (lMCode);
      
					if (it == g_MCodes.end()) {
      					// noch nicht dagewesen
      					HFEATURE lDestMCode = DEX_GetMCodeFromFeatureNameEx(g_hPr, cbBuffer);
      
						if (0 != lDestMCode && -1 != lDestMCode) {
      						// Attribut ist in der Zieldatenquelle bekannt, also das
      						// dirtige Handle verwenden
      							g_MCodes.insert (CMCodeMap::value_type(lMCode, lDestMCode));
      						}
      						else {
      						// Attribut ist in der Zieldatenquelle noch nicht bekannt, 
      						// also dieses nachdefinieren
      						MAPMCODETOHANDLE MTH;
      						INT_PTR lMappedMCode = 0L;
      						BOOL fCreated = FALSE;
      
							INITSTRUCT(MTH, MAPMCODETOHANDLE);
      							MTH.lIdent = id;
      							MTH.lMCode = lMCode;
      							MTH.plHandle = &lMappedMCode;
      							MTH.fCreate = true;
      							MTH.pfCreated = &fCreated;
      							if (DEX_MapOrCreateMCodeToHandle(g_hPr, MTH) && 0L != lMappedMCode)
      								lDestMCode = lMappedMCode;
      
							if (NULL == lDestMCode)
      								lDestMCode = DEX_GetUniqueMCode();
      
						PBDMERKMALEX pbdData;
      						ErrInstall EI (WC_NOMERKMAL);
      						bool fMustImport = false;
      
							INITSTRUCT (pbdData, PBDMERKMALEX);
      							pbdData.pbdTyp = 'm';
      							pbdData.pbdCode = lDestMCode;
      							pbdData.ipbdMTyp = 'a';		// Objektmerkmal
      							pbdData.ipbdMLen = _MAX_PATH;
      							pbdData.lIdent = id;
      						
      						// Testen, ob dieser Eintrag bereits existiert
      							if (EC_OKAY != DEX_GetPBDDataEx (g_hPr, pbdData)) {
      							// jetzt Pbd schreiben
      								CharToOem(cbBuffer, cbBuffer);
      								pbdData.pbdKText = cbBuffer;
      								pbdData.pbdKTextLen = strlen(cbBuffer);
      								DEX_ModPBDDataEx (g_hPr, pbdData);
      
							// und MCode merken
      								if (lMCode != lDestMCode)
      									g_MCodes.insert (CMCodeMap::value_type(lMCode, lDestMCode));
      							}
      						}
      					}
      				}
      			}
      			else if (1 == sscanf (comment, " ClassDesc(%s):", cbClassBuffer)){
      			char *pColon = strchr (comment, ':');
      			
      				_ASSERTE(NULL != pColon);
      
			int iNameLen = strlen(comment) - (pColon-comment) -2;
      
				if (0 == iNameLen)
      					break;
      
				wsprintf (cbFormat, "%%%dc", iNameLen);
      				if (1 == sscanf (pColon + 2, cbFormat, cbBuffer)) {
      					cbBuffer[iNameLen] = '\0';		// sauber abschließen
      
				// versuchen Identifikator festzustellen
      				long lIdent = 0L;
      				HRESULT hr = IdentFromClassX (g_hPr, cbClassBuffer, (ULONG *)&lIdent);
      
					if (S_OK == hr) {	// existiert bereits als Ident
      						break;
      					}
      					if (S_FALSE == hr) {
      					// nur OKS konvertiert
      					ErrCode RC = IdentIsDefined(lIdent);
      
						if (RC != EC_OKAY && !DEX_isIdentUsedEx(g_hPr, lIdent)) 
      						// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
      							hr = IdentFromClassX (g_hPr, cbClassBuffer, (ULONG *)&lIdent, true);
      					}
      					if (FAILED(hr) || 0 == lIdent) {
      					// ansonsten versuchen über den Namen zu matchen
      						lIdent = DEX_GetIdentFromClassNameEx(g_hPr, cbBuffer);
      					}
      
				// OKS-->Identifikatorzuordnung erzeugen, Kurztext schreiben
      					if (0 != lIdent) {
      					MODOBJCLASSCODE MOCC;
      
						INITSTRUCT(MOCC, MODOBJCLASSCODE);
      						MOCC.ulIdent = lIdent;
      						MOCC.pcClass = cbClassBuffer;
      						MOCC.fOverWrite = false;
      						DEX_ModObjectClassCodeEx(g_hPr, MOCC);
      
					PBDDATA pbdData;
      
						CharToOem(cbBuffer, cbBuffer);
      						INITSTRUCT(pbdData, PBDDATA);
      						pbdData.pbdTyp = 'i';
      						pbdData.pbdCode = lIdent;
      						pbdData.pbdKText = cbBuffer;
      						pbdData.pbdKTextLen = strlen(cbBuffer);
      						DEX_ModPBDDataEx (g_hPr, pbdData);
      					}
      				}
      			}
      		} break;
      case 85:{
      		// Plausibilitaetskontrolle
      			if (lgi +1 >= koord_paare) {
      				error_skip_lines ("PLFB", EGCNT);	// nächsten Id-Satz suchen
      				break;
      			}
      
		// Koordinatenpaar abspeichern, Zaehler weitersetzen
#if defined(_NO_CONVERSION_ASC)
      			yypvt[-1].flttok.fltnum -= OffsetX;
      			yypvt[-0].flttok.fltnum -= OffsetY;
      			gxi[++lgi] = (long)(yypvt[-1].flttok.fltnum * Koeff11 + yypvt[-0].flttok.fltnum * Koeff12);
      			gyi[lgi] = (long)(yypvt[-1].flttok.fltnum * Koeff21 + yypvt[-0].flttok.fltnum * Koeff22);
#else
      			gxi[++lgi] = yypvt[-1].flttok.fltnum;
      			gyi[lgi] = yypvt[-0].flttok.fltnum;
#endif // _NO_CONVERSION_ASC
      		} break;
      case 86:{
      			if (satz_nr > 0 && end_previous_object ())
      				YYACCEPT;
      		} break;    }
    goto enstack;
}
