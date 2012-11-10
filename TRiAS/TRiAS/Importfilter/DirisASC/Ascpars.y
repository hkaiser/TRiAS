%{

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

%}

%start  AsciiDatei

%union {
	STRING_TOKEN strtok;
	NUMBER_TOKEN numtok;
	FLOAT_TOKEN flttok;
}

%token  <strtok>        T_STRING T_MISTRING

%token  <numtok>        T_INTEGER T_PSATZ T_LSATZ T_FSATZ T_DSATZ
%token  <numtok>        T_GSATZ T_MSATZ T_RSATZ T_TSATZ T_WSATZ
%token  <numtok>        '\n' T_ESATZ T_IDENT T_BSATZ T_ISATZ T_CSATZ
%token	<numtok>		T_VSATZ T_HRELSATZ T_KRELSATZ T_BRELSATZ
%token	<numtok>		T_KOSATZ T_HEXINTEGER 

%token	<strtok>		T_ABGLEICH
%token	<numtok>		T_IMPORT

%token  <strtok>        T_KSATZ T_HSATZ T_OFFSET T_SCALE T_ENTRY
%token  <strtok>        T_PBDNAME T_ENTRYROSYS T_ENTRYRO T_ENTRYSYS

%token  <flttok>        T_FLOAT

%type   <numtok>        ElementarObjektTyp ElementSatz IdentifikatorSatz
%type   <numtok>        IntegerMerkmalsSatz FloatMerkmalsSatz StringMerkmalsSatz
%type   <numtok>        RelationsSatz TrennSatz GeometrieSatz KommentarSatz
%type   <numtok>        BeschreibungsSatz HeaderSatz AsciiDateiKoerper
%type   <numtok>        KommentarSaetze ElementSaetze TextObjektSatz
%type	<numtok>		SteuerSatz RelationsTyp

%%

AsciiDatei:     AsciiDateiKoerper EndeSatz
	|       AsciiDateiKoerper
		{
			if (satz_nr > 0 && end_previous_object ())
				YYACCEPT;
			db_error (ENOEND, ASCPARSER, $1.num_line);
			YYACCEPT;
		}
	;

AsciiDateiKoerper:
		HeaderSatz
	|	HeaderSatz ElementSaetze
	|	KommentarSaetze HeaderSatz
	|	KommentarSaetze HeaderSatz ElementSaetze
	|	ElementSatz 
		{
			db_error (ENOHD, ASCPARSER, $1.num_line);
			YYABORT;
		}
	;

ElementSaetze:  
		ElementSatz 
	|	ElementSaetze ElementSatz 
	;

ElementSatz:    
		BeschreibungsSatz
	|	IdentifikatorSatz
	|	IntegerMerkmalsSatz IntegerWertSaetze
	|	FloatMerkmalsSatz FloatWertSaetze
	|	StringMerkmalsSatz StringWertSaetze
	|	RelationsSatz
	|	GeometrieSatz 
	|	TrennSatz
	|	KommentarSatz
	|	TextObjektSatz
	|	TextObjektSatz StringWertSaetze
	|	SteuerSatz
	|       error '\n'
		{
			yyerrok;
			db_error (EBADRC, ASCPARSER, $2.num_line);
		}
	;

BeschreibungsSatz:
		T_DSATZ T_SCALE T_FLOAT T_FLOAT T_FLOAT T_FLOAT '\n'
		{
			if (!toWriteScale()) 
				break;

			Koeff11 = $3.fltnum;
			Koeff12 = $4.fltnum;
			Koeff21 = $5.fltnum;
			Koeff22 = $6.fltnum;
			if (EvalKoeffs (&$3.fltnum, &$4.fltnum, &$5.fltnum, &$6.fltnum) != EOKAY)
				YYABORT;

			if (DEX_GetTRiASDataSourceEx (g_hPr)) {
			// evtl. DatenquellenHeader schreiben
				PutHdFlt (g_hPr, $3.fltnum, Koeff11Key, true, HEADER_SYSTEMRO);
				PutHdFlt (g_hPr, $4.fltnum, Koeff12Key, true, HEADER_SYSTEMRO);
				PutHdFlt (g_hPr, $5.fltnum, Koeff21Key, true, HEADER_SYSTEMRO);
				PutHdFlt (g_hPr, $6.fltnum, Koeff22Key, true, HEADER_SYSTEMRO);
			}

		// jetzt Projekt behandeln
			if (!toWriteScaleProject()) 
				break;

			PutHdFlt (HACTPROJECT, $3.fltnum, Koeff11Key, true, HEADER_SYSTEMRO);
			PutHdFlt (HACTPROJECT, $4.fltnum, Koeff12Key, true, HEADER_SYSTEMRO);
			PutHdFlt (HACTPROJECT, $5.fltnum, Koeff21Key, true, HEADER_SYSTEMRO);
			PutHdFlt (HACTPROJECT, $6.fltnum, Koeff22Key, true, HEADER_SYSTEMRO);
		}
	|       T_DSATZ T_OFFSET T_FLOAT T_FLOAT '\n'
		{

		// evtl. DatenquellenHeader schreiben
			if (!toWriteOffset()) 
				break;

			OffsetX = $3.fltnum;
			OffsetY = $4.fltnum;
			if (DEX_GetTRiASDataSourceEx(g_hPr)) {
				PutHdFlt (g_hPr, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
				PutHdFlt (g_hPr, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
			}

		// jetzt Projekt behandeln
			if (!toWriteOffsetProject()) 
				break;
			
			PutHdFlt (HACTPROJECT, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
			PutHdFlt (HACTPROJECT, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
		}
	|       T_DSATZ T_ENTRYROSYS T_STRING T_STRING '\n'
		{
			if (!ImportHeader ($3.string, $4.string, HEADER_SYSTEMRO))
				YYABORT;
		}
	|       T_DSATZ T_ENTRYRO T_STRING T_STRING '\n'
		{
			if (!ImportHeader ($3.string, $4.string, HEADER_READONLY))
				YYABORT;
		}
	|       T_DSATZ T_ENTRYSYS T_STRING T_STRING '\n'
		{
			if (!ImportHeader ($3.string, $4.string, HEADER_SYSTEM))
				YYABORT;
		}
	|       T_DSATZ T_ENTRY T_STRING T_STRING '\n'
		{
			if (!ImportHeader ($3.string, $4.string, HEADER_NORMAL))
				YYABORT;
		}
	|       T_DSATZ T_PBDNAME T_STRING '\n'
		{
			PutHdString (g_hPr, $3.string, PbdNameKey, false, HEADER_SYSTEMRO);
		}
	|       T_DSATZ error '\n'
		{
			yyerrok;
			db_error (EBADRC, ASCPARSER, $3.num_line);
		}                       
	;

IntegerWertSaetze:
		IntegerWertSatz
	|       IntegerWertSaetze IntegerWertSatz
	;

FloatWertSaetze:
		FloatWertSatz
	|       FloatWertSaetze FloatWertSatz
	;

StringWertSaetze:
		StringWertSatz
	|       StringWertSaetze StringWertSatz
	;

GeometrieSatz:  T_GSATZ PunktKoordinaten '\n'
	|       T_GSATZ error '\n'
		{
			yyerrok;
			db_error (EKOORD, ASCPARSER, $3.num_line);
		}
	;

HeaderSatz:     T_HSATZ '\n'
		{
		// aktive Datenquelle bsorgen
			g_hPr = DEX_GetDataSourceHandle();
			_ASSERTE(NULL != g_hPr);

		// Standardwerte in DB-Header setzen
//			strcpy (header, $1.string);     

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
		}
	;

IdentifikatorSatz:
		ElementarObjektTyp T_INTEGER T_INTEGER T_INTEGER T_STRING '\n'
		{
			if (!d_flag) 	// Ident ist Hexadezimal
				$3.intnum = MakeHex ($3.intnum);

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
			if (($1.intnum == O_PUNKT && $4.intnum != 1)
			 || ($1.intnum == O_LINIE && $4.intnum < 2)) {
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}
		/* Naechstes Objekt beginnen */
			init_new_object ();
			strcpy (guid, $5.string);

		/* Objektparameter setzen */
			satz_nr = $2.intnum;            /* lfde Nummer in ASCII-Datei */
			sta[1] = $1.intnum;     /* Objekttyp */
			koord_paare = $4.intnum; /* Stuetzpunktanzahl */
			{
			// Ident existiert evtl. bereits in Zuordnungstabelle
				ltoa ($3.intnum, header, d_flag ? 10 : 16);

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
		}
	|	ElementarObjektTyp T_INTEGER T_INTEGER T_INTEGER '\n'
		{
			if (!d_flag) 	// Ident ist Hexadezimal
				$3.intnum = MakeHex ($3.intnum);

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
			if (($1.intnum == O_PUNKT && $4.intnum != 1)
			 || ($1.intnum == O_LINIE && $4.intnum < 2)) {
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}
		/* Naechstes Objekt beginnen */
			init_new_object ();

		/* Objektparameter setzen */
			satz_nr = $2.intnum;            /* lfde Nummer in ASCII-Datei */
			sta[1] = $1.intnum;     /* Objekttyp */
			koord_paare = $4.intnum; /* Stuetzpunktanzahl */
			{
			// Ident existiert evtl. bereits in Zuordnungstabelle
				ltoa ($3.intnum, header, d_flag ? 10 : 16);

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
		}
	|	ElementarObjektTyp T_INTEGER T_HEXINTEGER T_INTEGER T_STRING '\n'
		{
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
		}
	|	ElementarObjektTyp T_INTEGER T_HEXINTEGER T_INTEGER '\n'
		{
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
		}
	|	ElementarObjektTyp T_INTEGER T_STRING T_INTEGER T_STRING '\n'
		{
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
			if (($1.intnum == O_PUNKT && $4.intnum != 1)
			 || ($1.intnum == O_LINIE && $4.intnum < 2)) {
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}

		/* Naechstes Objekt beginnen */
			init_new_object ();
			strcpy (guid, $5.string);

		/* Objektparameter setzen */
			satz_nr = $2.intnum;		/* lfde Nummer in ASCII-Datei */
			sta[1] = $1.intnum;			/* Objekttyp */
			koord_paare = $4.intnum;	/* Stuetzpunktanzahl */
			{
			// Ident existiert evtl. bereits in Zuordnungstabelle
			long lIdent = 0L;
			HRESULT hr = IdentFromClassX (g_hPr, $3.string, (ULONG *)&lIdent);

				if (S_OK == hr) {// existiert bereits als Ident
					id = lIdent;
					break;
				}

				if (S_FALSE == hr) {
				ErrCode RC = IdentIsDefined(lIdent);

					if (RC != EC_OKAY && !DEX_isIdentUsedEx(g_hPr, lIdent)) 
					// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
						hr = IdentFromClassX (g_hPr, $3.string, (ULONG *)&lIdent, true);
				}
				if (FAILED(hr) || 0 == lIdent) 
					break;			// abbrechen

			// hier ist der neue Ident
				id = lIdent;
			}
		}
	|	ElementarObjektTyp T_INTEGER T_STRING T_INTEGER '\n'
		{
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
			if (($1.intnum == O_PUNKT && $4.intnum != 1)
			 || ($1.intnum == O_LINIE && $4.intnum < 2)) {
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}

		/* Naechstes Objekt beginnen */
			init_new_object ();

		/* Objektparameter setzen */
			satz_nr = $2.intnum;		/* lfde Nummer in ASCII-Datei */
			sta[1] = $1.intnum;			/* Objekttyp */
			koord_paare = $4.intnum;	/* Stuetzpunktanzahl */
			{
			// Ident existiert evtl. bereits in Zuordnungstabelle
			long lIdent = 0L;
			HRESULT hr = IdentFromClassX (g_hPr, $3.string, (ULONG *)&lIdent);

				if (S_OK == hr) {// existiert bereits als Ident
					id = lIdent;
					break;
				}

				if (S_FALSE == hr) {
				ErrCode RC = IdentIsDefined(lIdent);

					if (RC != EC_OKAY && !DEX_isIdentUsedEx(g_hPr, lIdent)) 
					// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
						hr = IdentFromClassX (g_hPr, $3.string, (ULONG *)&lIdent, true);
				}
				if (FAILED(hr) || 0 == lIdent) 
					break;			// abbrechen

			// hier ist der neue Ident
				id = lIdent;
			}
		}
	|       ElementarObjektTyp error '\n'
		{
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
			switch ((int)$1.intnum) {
			case O_PUNKT:
				error_skip_lines ("PLFB", EPKTID); break;
			case O_LINIE:
				error_skip_lines ("PLFB", ELINID); break;
			case O_FLAECHE:
				error_skip_lines ("PLFB", EFLID); break;
			}
		}
	|	T_KOSATZ T_INTEGER T_INTEGER T_STRING '\n'
		{
			if (!d_flag) 	// Ident ist Hexadezimal
				$3.intnum = MakeHex ($3.intnum);

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
			strcpy (guid, $4.string);

		/* Objektparameter setzen */
			satz_nr = $2.intnum;	/* lfde Nummer in ASCII-Datei */
			id = $3.intnum;		/* Identifikator */
			sta[0] = K_OBJEKT;	
			sta[1] = 0;		/* Objekttyp */
			koord_paare = 0;	/* Stuetzpunktanzahl */
		}
	|	T_KOSATZ T_INTEGER T_INTEGER '\n'
		{
			if (!d_flag) 	// Ident ist Hexadezimal
				$3.intnum = MakeHex ($3.intnum);

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
			satz_nr = $2.intnum;	/* lfde Nummer in ASCII-Datei */
			id = $3.intnum;		/* Identifikator */
			sta[0] = K_OBJEKT;	
			sta[1] = 0;		/* Objekttyp */
			koord_paare = 0;	/* Stuetzpunktanzahl */
		}
	|	T_KOSATZ T_INTEGER T_HEXINTEGER T_STRING '\n'
		{
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
		}
	|	T_KOSATZ T_INTEGER T_HEXINTEGER '\n'
		{
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
		}
	|	T_KOSATZ error '\n'
		{
		/* Vorhergehendes EO bearbeiten */
			if (satz_nr > 0 && end_previous_object ())
				YYACCEPT;
			
			guid[0] = '\0';
			yyerrok;
			error_skip_lines ("PLFB", EFKID);
		}
	;

ElementarObjektTyp:
		T_PSATZ         /* Punkt */
		{       $$.intnum = O_PUNKT;    }
	|       T_LSATZ         /* Linie */
		{       $$.intnum = O_LINIE;    }
	|       T_FSATZ         /* Flaeche */
		{       $$.intnum = O_FLAECHE;  }
	|	T_BSATZ		/* TextObjekt */
		{	$$.intnum = O_TEXTOBJEKT;	}
	;

TextObjektSatz:	T_ISATZ T_STRING '\n'
		{
		int Len = strlen ($2.string);
		long wf = 0;

			curr_mi = &curr_mi[mi_count];
			mi_count = 3;
			curr_mi_text = (char *)&curr_mi[3];

			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
			curr_mi[1] = M_TEXT;

		// wie normalen Merkmalswert behandeln
			if (!strncmp ($2.string, "@@", 2)) {
				Len -= 2;
				strncpy (curr_mi_text, $2.string+2, 78);
				curr_mi_text[min(78, Len)] = '\0';

			// Status korrigieren
				sta[1] = O_TEXTOBJIND;
			} else {
				strncpy (curr_mi_text, $2.string, 78);
				curr_mi_text[min(78, Len)] = '\0';
			}

			curr_mi_text += Len;
			wf = (Len + (sizeof(long)-1))/sizeof(long);

			mi[1] += wf + 3;
			curr_mi[2] = wf;		// Wiederholungsfaktor
			mi_count += wf;
		}
	|	T_ISATZ T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];

			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
			curr_mi[1] = M_TEXT;
			curr_mi[2] = -1;		// WF
			curr_mi[3] = $2.intnum;		// MCode

			mi[1] += 4;
			mi_count = 4;

		// Status korrigieren
			sta[1] = O_TEXTOBJIND;
		}
	;

SteuerSatz:	T_CSATZ T_VSATZ '\n'
		{
		}
	|	T_CSATZ T_ABGLEICH '\n'
		{
		// AbgleichsOption
			g_fImportObj = false;		// nur Abgleich

			switch ($2.string[0]) {
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
		}
	|	T_CSATZ T_IMPORT '\n'
		{
		// ImportOption
			g_fImportObj = true;		// C I: doch wieder importieren
		}
	|	T_CSATZ T_ABGLEICH T_INTEGER '\n'
		{
			g_fImportObj = false;		// nur Abgleich

			switch ($2.string[0]) {
			case 'O':		/* Abgleich OKS */
				{
					switch ($2.string[1]) {
					case 'R':	/* C AOR MCode: neue Objektklasse aus einem der angehängten Merkmale */
						g_ulOksFromAttr = $3.intnum;
						g_fAbglOks = true;
						break;

					case 'S':	/* C AOS MCode: Bisherige Objektklasse als Merkmal wegschreiben */
						g_ulOksToAttr = $3.intnum;
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
		}
	;

IntegerMerkmalsSatz:
		T_MSATZ T_INTEGER T_INTEGER 'I' T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];
			curr_mi[1] = M_INTEGER;         /* Integermerkmale */
			mi_werte = $3.intnum;		/* Anzahl der I*4 - Werte */

labelMerkmal: ;
			if (!md_flag) 	// MCode ist Hexadezimal
				$2.intnum = MakeHex ($2.intnum);

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
			if ((ULONG)$2.intnum == g_ulUniqueId && g_ulUniqueId != g_ulOrgUniqueId) 
				$2.intnum = (LONG)g_ulOrgUniqueId;
			else {
			// ggf. muß der MCode auf die Zieldatenquelle gemappt werden
			CMCodeMap::iterator it = g_MCodes.find ($2.intnum);

				if (it != g_MCodes.end())
					$2.intnum = (*it).second;		// entspricht diesem MCode in der Zieldatenquelle
			}

			curr_mi[0] = $2.intnum; /* Merkmalskode */
			curr_mi[2] = 0;         /* Wiederholungsfaktor loeschen */
			mi[1] += 3;
			mi_count = 3;
			mi_length = $5.intnum;  /* Laenge der Werte */
		}
	;

FloatMerkmalsSatz:
		T_MSATZ T_INTEGER T_INTEGER 'F' T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];
			curr_mi[1] = M_DOUBLE;          /* Floatpointmerkmale */
			mi_werte = $3.intnum; //*(sizeof(double)/sizeof(long));

			goto labelMerkmal;   /* weiter wie fuer M_INTEGER */
		}
	;

StringMerkmalsSatz:
		T_MSATZ T_INTEGER T_INTEGER 'A' T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];
			curr_mi[1] = M_TEXT;            /* Textmerkmale */
			curr_mi_text = (char *)&curr_mi[3];
			mi_werte = ($5.intnum + (sizeof(long)-1))/sizeof(long);

			goto labelMerkmal;   /* weiter wie fuer M_INTEGER */
		}
	;

IntegerWertSatz:
		T_WSATZ IntegerWerte '\n'
	;

IntegerWerte:   IntegerWert
	|       IntegerWerte IntegerWert
	;

IntegerWert:    T_INTEGER
		{ 
		// Plausibilitätskontrolle 
			if (mi_count -3 >= mi_werte) {
			// Merkmal ueberspringen
				error_skip_lines ("PLFMRG", EMCNT);
				break;
			}
			curr_mi[mi_count++] = $1.intnum;
			mi[1]++;
			curr_mi[2]++;
		}
	;

FloatWertSatz:  T_WSATZ FloatWerte '\n'
	;

FloatWerte:     FloatWert
	|       FloatWerte FloatWert
	;

FloatWert:      T_FLOAT
		{
		register int item_size = sizeof(double)/sizeof(long);

		// Plausibilitätskontrolle
			if ((mi_count -3)/(sizeof(double)/sizeof(long)) >= (size_t)mi_werte) 
			{
			// Merkmal ueberspringen
				error_skip_lines ("PLFMRG", EMCNT);
				break;
			}
			
			*((double *)(&curr_mi[mi_count])) = $1.fltnum;
			mi[1] += item_size;
			curr_mi[2]++;           // += item_size;
			mi_count += item_size;
		}
	;

StringWertSatz: T_WSATZ T_STRING '\n'
		{
		register int length = 0;

		// Plausibilitaetskontrolle
			if (mi_length <= 0) {
			// Zu viele Merkmalssaetze
//				error_skip_lines ("PLFRMG", EMCNT);
//				break;
				mi_length = strlen($2.string);
			}

			strncpy (curr_mi_text, $2.string, 78);
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
		}
	;

RelationsSatz:  T_RSATZ RelationsTyp T_INTEGER T_INTEGER '\n'
		{
			if (r_flag) {	// Relationen nicht ignorieren
			long lON = RetrieveFromTree ($4.intnum);

				if (lON != -1)	// Satz existiert wirklich: Relation aufbauen
					StoreInList (lON, $3.intnum, $2.intnum);
			}
		}
	|	T_RSATZ T_BRELSATZ T_INTEGER '\n'
		{
			if (r_flag) {	// Relationen nicht ignorieren
			long ONr = RetrieveFromTree ($3.intnum);

				if (ONr != -1)	// Relation aufbauen
					StoreInList (ONr, $2.intnum, RTBegleitO);
			}
		}
	|       T_RSATZ error '\n'
		{
			yyerrok;
			db_error (EBREL, ASCPARSER, $3.num_line);
		}
	;

RelationsTyp:	T_HRELSATZ
		{	$$.intnum = RTGleich;	}
	|	T_KRELSATZ
		{	$$.intnum = RTKomplexU;	}
	;

TrennSatz:      T_TSATZ '\n'
	;

KommentarSaetze:
		KommentarSatz 
	|	KommentarSaetze KommentarSatz
	;

KommentarSatz:  T_KSATZ '\n'
		{
		int iToCopy = min(strlen($1.string), sizeof(comment)-1);

			strncpy (comment, $1.string, iToCopy);
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
		}
	;

PunktKoordinaten:
		PunktKoordinate
	|	PunktKoordinaten PunktKoordinate
	;

PunktKoordinate:
		T_FLOAT T_FLOAT
		{
		// Plausibilitaetskontrolle
			if (lgi +1 >= koord_paare) {
				error_skip_lines ("PLFB", EGCNT);	// nächsten Id-Satz suchen
				break;
			}

		// Koordinatenpaar abspeichern, Zaehler weitersetzen
#if defined(_NO_CONVERSION_ASC)
			$1.fltnum -= OffsetX;
			$2.fltnum -= OffsetY;
			gxi[++lgi] = (long)($1.fltnum * Koeff11 + $2.fltnum * Koeff12);
			gyi[lgi] = (long)($1.fltnum * Koeff21 + $2.fltnum * Koeff22);
#else
			gxi[++lgi] = $1.fltnum;
			gyi[lgi] = $2.fltnum;
#endif // _NO_CONVERSION_ASC
		}
	;

EndeSatz:       T_ESATZ '\n'
		{
			if (satz_nr > 0 && end_previous_object ())
				YYACCEPT;
		}
	;

%%

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
