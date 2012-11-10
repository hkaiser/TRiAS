%{
// Syntaxbeschreibung einer raumbezogenen Anfragesprache 
// File: DQL.Y

#include "dqly.htp"			 	// Klassen-Selektion
#include <commonvu.hxx>
#include <containr.hxx>

extern "C" {
	#include <ctype.h>		 	// isdigit ()
	#include "dql.h"
}

#include <ristypes.hxx>		 	// Koord
#include <geo_obj.hxx>		  	// ObjContainer
#include <objfeld.hxx>		  	// ObjNummer

#include <relation.hxx>
#include <dbliste.hxx>
#include <dbasprof.hxx>		 	// DBaseProFile
#include <dbasekey.hxx>

#include "yystype.hxx"
#include "groups.hxx"
#include "rechstat.hxx"
#include "tools.hxx"			// GetMiText ()
#include <ixtensn.hxx>          // Interfaces einer Erweiterung
#include <xtencunk.hxx>         // InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include "komplexr.hxx"		 	// KomplexrExtension
#include "expexpr.hxx"		  	// ExpandParams ()
#include "dqlyfct.hxx"		  	// AddRelation ()

// Konstanten, Definitionen etc. ----------------------------------------------
const short SIGHTNAMESIZE = 80;
const char ExprOperator [] = " .AND. ";				 // zur Kopplung der Expression
const int BeginExpr = '{';	  // Separatoren in dBase-Expressions
const int EndExpr = '}';

// globale Variablen ----------------------------------------------------------
extern CodeBase *pCB;		   // CodeBaseKlasse
extern long ActCount;
extern short GroupCount;		// Gruppenzähler
extern RechercheStatus *pRStat; // Zähler
extern ResourceFile *pRF;
extern KomplexrExtension *pKE;

extern KEYWORD *keywords;
extern KEYWORD SearchKeys[], ReportKeys[];

// lokale Variablen
Bool fSyntaxTestOnly = False;   // Actions ausführen

// DBaseFiles enthält alle dbf-Dateien, die durch USE deklariert sind
Bool DefaultDataBase = False;   // Datenbanken sind default
Bool DefaultRelation = False;   // Relationen aus Projekt-INI-Datei
DBaseFiles *pDBFs = NULL;

// Groups enthält die Beschreibung aller Klassifikationsgruppen
Groups *pGs = NULL;

// Bufferbereich, in dem die ParameterExpansion durchgeführt wird
const short EXPRBUFFSIZE = 4096;		// Größe des ExprBuffers
char *pExprBuff = NULL;

// Speicherbereiche für DBaseExpressions, die RechercheKriterien festlegen
static char *pGlobalExpr = NULL;
static char *pLocalExpr = NULL;

static KeyFilter *pGlobalKF = NULL;
static KeyFilter *pLocalKF = NULL;

// Liste der relationen zwischen den DBasedateien
RelationList *pGlobalRL = NULL;
RelationList *pLocalRL = NULL;

Bool wasGIWindow = FALSE;
Bool wasIdFilter = FALSE;
Bool groupActive = FALSE;

//  lokale Funktion(en)
inline
long DtoL (double D) { return long (D + 0.5); } //  konvertiere Double in Long

// lokale Funktionen --------------------------------------------------------
static ErrCode FilterDBaseExpression (KeyFilter &, char *, RelationList *,
									  long = -1, Bool = FALSE);
static Bool FilterWithTag (DataIndex &, DBaseObjNummer &, 
						   KeyFilter &, long *, char **, short, Bool, char *,
						   RelationList *);
static Bool FilterWithoutTag (DataIndex &, DBaseObjNummer &, KeyFilter &,
							  long *, char **, short, Bool, RelationList *,
							  char * pExprBuff);
static pchar ExpandDBaseExpression (long ONr, pchar pExpr);						   
static Bool GetMerkmalsValue (long lONr, long lMCode, char *pBuffer, short iLen);

// importierte Funktionen --------------------------------------------------
int ExtDBError (int Error, int Routine, Bool = True);  // im Lex impl.
%}

%start DQLScript

%token  SEARCH DBASE WINDOW RECORDS
%token  VIEW IDENT SELECT WHERE USE ON OBJECTS
%token  GRAPHICS SHEET PRINTER ININ CLASSIFICATION
%token  AS SELECTED FOR OBJLIST GROUP IDENDTLIST
%token  DEFAULT IS KEY UNIQUE TEMP RELATION

%token  <StringToken()>		 STRING DBASEEXPR

%token  <LongToken()>		   INTEGER

%token  <FloatToken()>		  FLOAT

/*%type		<FloatToken()>		  NumValue */

%type   <ObjContToken()>		FensterSpezifikation

%type   <GeoDBKeyToken()>	   GeoDBKeySpez

%type   <DBaseKeyToken()>	   RedDBaseKeySpez DBaseKeySpez TagSpezifikation

%type   <LongToken()>		   GroupHead

%type   <MasterTermToken()>	 MasterTerm

%type   <SlaveTermToken()>	  SlaveTerm

/* ReportGenerator - Tokens */
%token  REPORT LINES COLUMNS ALL FROM TO BIG PAGE TUPLE
%token  FOR_ONE FOR_ALL HEAD TAIL FORMAT NUMBER TUPLES
%token  VARI VARF VARS LASTI VALUEI NEXTI LASTF VALUEF NEXTF
%token  LASTS VALUES NEXTS NEW LINE COL BATCH PROC CALL
%token  SYSTEM_VAR SYSTEM_CONST PRINT DECLARATION
%token  LINEBEGIN LINEEND IF ELSE IDENTLIST

%token  TERMINAL DATE TIME SPACE

%token  '{' '}' ';' '+' '-' '(' ')' '*' '/' '%' ','

%right EQU

%left OROR
%left ANDAND
%left UNOT
%left LT GT NE LE GE EQ

%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%%

/* Ganzes Script ------------------------------------------------------------*/
DQLScript:	  SuchScript 
				{	   
				/* DefaultAusgabe organisieren (ObjektListe im Fenster)
				   Objfeld komprimieren (DBaseSätze, die Invalid sind werden
				   gelöscht).*/
					if (! fSyntaxTestOnly) {
						if (pKE -> OF ().Compact () != 0) {

						// Abspeichern, was im StandardFall zu machen ist
							if (pGs -> Count() != 0)
								pKE -> RStatus () = (RSToDo)OTClassification;
							else
								pKE -> RStatus () = (RSToDo)OTObjList;
						} else {
							DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
						}
						DELETE_OBJ (pGs);
					}
				}
		|	   SuchScript AusgabeStatement 
				{
					if (! fSyntaxTestOnly)
						DELETE_OBJ (pGs);
				}
		|	   error
				{
					ExtDBError (RC_DQLParser, EC_UncompleteScript);
					YYABORT;
				}
		;

/* Suchspezifikation ------------------------------------------------------- */
SuchScript:	 SEARCH '{'
				{
					if (fSyntaxTestOnly)
						yyignore;
					else {
					//  Variablen initialisieren
						pGs = new Groups;
						if (!pGs) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
						wasGIWindow = FALSE;
						wasIdFilter = FALSE;
					}
				}
					SuchSpezifikationen ClosingBrace
					{
						keywords = ReportKeys;
						/* jetzt folgt Report */
					}
		|	   error '{'
				{
					ExtDBError (RC_DQLParser, EC_UncompleteScript);
					YYABORT;
				}
		|	   SEARCH 
				{
				/* Variablen initialisieren */
					pGs = new Groups;
					if (!pGs) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					wasGIWindow = FALSE;
					wasIdFilter = FALSE;
				}
					SuchSpezifikation ';'
					{
						keywords = ReportKeys;
						/* jetzt folgt Report */
					}
		;

SuchSpezifikationen:	
				SuchSpezifikation
		|	   SuchSpezifikationen SuchSpezifikation
		;

SuchSpezifikation:
				SelectSpezifikation
		|	   AuftragsSpezifikation
		;

SelectSpezifikation:
				SELECT GebietsSpezifikation
		|	   SELECT SichtSpezifikation
		;

GebietsSpezifikation:
				WINDOW FensterSpezifikation ';'
				{
				//  GeometrieRecherche im Fenster durchführen
					if (pKE -> OF ().Count() == 0) {
					// Objfeld noch leer
						if (pKE -> doGeoRecherche ($2) != EC_OKAY)
							YYABORT;	// Fehler: raus
						wasGIWindow = TRUE;
					 } else {
					 // Objektmenge vorgegeben
					 // sorry, not implemented
					}
				}
		|	   WINDOW error ';'
				{
					ExtDBError (RC_DQLParser, EC_BadWindowSpec);
					YYABORT;
				}
		;

FensterSpezifikation:
				'(' error ClosingParanthesis
				{
						ExtDBError (RC_DQLParser, EC_BadWindowSpec);
						YYABORT;
				}
		|	   AS SELECTED
				{
					ObjContainer *plocRc = new ObjContainer (0L, 0L, 0L, 0L);
					if (!plocRc) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
				}
					DEX_GetActiveSelection (plocRc);
				//  Ymin, Ymax ggf. tauschen
					if (plocRc -> YMin () > plocRc -> YMax ()) {
						long Y = plocRc -> YMin ();
						plocRc -> YMin () = plocRc -> YMax ();
						plocRc -> YMax () = Y;
					}
					// Selektiertes Fenster liefern. (Default: aktueller Bildausschnitt)
					YYSTACK (plocRc, YYObjContainer);
				}
/*
		|
				'(' NumValue ',' NumValue ',' NumValue ',' NumValue ClosingParanthesis
				{ // ^Xmin	   ^Ymin		 ^Xmax		  ^Ymax
					// hier müssen die Koordinaten noch umger. werden
					ObjContainer *locRc = new ObjContainer (DtoL ($2), DtoL ($6),
															DtoL ($4), DtoL ($8));
					if (!locRc) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (locRc, YYObjContainer);
				}
*/
		;

SichtSpezifikation:	 
				VIEW STRING ';'
				{	   
				//  ObjFeld über Sicht Filtern
					if (pKE -> OF ().Count() == 0) {
					// noch keine Objekte selektiert
						if (wasGIWindow) {
						// keine Objekte aus Geometrie gefunden
							DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
							YYACCEPT;
						}
						if (pKE -> IdFilterNew ($2) != EC_OKAY)
							YYABORT;
					} else {
					// Objekte nachselektieren
						if (pKE -> IdFilter ($2) != EC_OKAY)
							YYABORT;
					}
					wasIdFilter = TRUE;
					if (pKE -> OF().Count() == 0) {
						DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
						YYACCEPT;
					}
				}
		|	   VIEW DEFAULT ';'
				{
					char SightBuffer [SIGHTNAMESIZE+1] = "";
					if (! DEX_GetActiveSight (SightBuffer)) {
						ExtDBError (RC_DQLParser, EC_BadInSpec);
						YYABORT;
					} else {
					/* ObjFeld über Sicht Filtern */
						if (pKE -> OF ().Count() == 0) {
						// noch keine Objekte selektiert
							if (wasGIWindow) {
							// keine Objekte aus Geometrie gefunden
								DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
								YYACCEPT;
							 }
							 if (pKE -> IdFilterNew (SightBuffer) != EC_OKAY)
								YYABORT;
						} else {
						// Objekte nachselektieren
							if (pKE -> IdFilter (SightBuffer) != EC_OKAY)
								YYABORT;
						}
						wasIdFilter = TRUE;
						if (pKE -> OF ().Count() == 0) {
							DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
							YYACCEPT;
						}
					}
				}
		|	   VIEW error ';'
				{
					ExtDBError (RC_DQLParser, EC_BadInSpec);
					YYABORT;
				}
		|	   OBJECTS AS SELECTED ';'
				{	   
				//  alles bis auf geg. Objekt aus ObjFeld entfernen
					long iCnt = DEX_ActiveObjectsCount();
					if (iCnt <= 0) {
						DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
						YYACCEPT;
					}

					long *pObjs = new long [iCnt];
					if (!pObjs) {
						DEX_Error (EC_NOMEMORY, RC_DQLParser);
						YYABORT;
					}
					iCnt = DEX_GetAllActiveObjects (pObjs);
					pKE -> OF ().EveryDelete ();		// leer machen

					ObjNummerCreator ONC (pKE -> OF ());
					for (long i = 0; i < iCnt; i++)
						pKE -> OF ().NewObj (ONC, pObjs [i]);
					DELETE_VEC (pObjs);
					wasGIWindow = TRUE;
				}
		|	   OBJECTS INTEGER ';'
				{
				// ein bestimmtes Objekt untersuchen
					pKE -> OF ().EveryDelete(); // Feld leeren
					ObjNummerCreator ONC (pKE -> OF ());
					pKE -> OF ().NewObj (ONC, $<LongToken()>2);
					wasGIWindow = TRUE;
				}
		|	   OBJECTS error ';'
				{
					ExtDBError (RC_DQLParser, EC_BadForSpec);
					YYABORT;
				}
		|	   IDENTLIST '(' IdentList ClosingParanthesis ';'
				{
				//  Objekte über ID-Liste filtern
					if (pKE -> OF ().Count() == 0) {
					//  noch keine Objekte selektiert
						DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
						YYACCEPT;
					} else {
					//  Objekte nachselektieren
						if (pKE -> IdFilterIdents () != EC_OKAY)
						   YYABORT;
					}
					wasIdFilter = TRUE;
					if (pKE -> OF ().Count() == 0) {
						DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
						YYACCEPT;
					}
				}
		|	   IDENTLIST error ';'
				{   // Listenkopffehler
					ExtDBError (RC_DQLParser, EC_BadIdentSpec);
					YYABORT;
				}
		;

IdentList:	  Ident
		|	   IdentList ',' Ident
		;

Ident:		  INTEGER
				{   // Identifikator in ID-Liste speichern
					if (! pKE -> AddIdent ($<LongToken()>1))
						YYABORT;
				}
		|	   error
				{   // Identifiaktor-Fehler
					ExtDBError (RC_DQLParser, EC_BadIdentSpec);
					YYABORT;
				}
		;

AuftragsSpezifikation:
				WHERE WobeiBedingung
		;

/* Hier werden die DatenSätze aus der Datenbasis bzw. der relationalen
   Struktur gesucht, die der vorgegebenen Bedingung entsprechen. ----------- */
WobeiBedingung: 
				RelationaleBedingung
		;

RelationaleBedingung:
				RelationalHead Tabellen RelSpezifikationen ClosingBrace
				{
				/* Recherche anstrengen, wenn keine Gruppen definiert sind */
					if (pGs -> Count() == 0 && pGlobalKF) {
						pRStat -> SetGroupText ();
						if (FilterDBaseExpression (*pGlobalKF, pGlobalExpr, pGlobalRL) != EC_OKAY)
							YYABORT;
					 } else {
						if (pGlobalKF == NULL) {
							ExtDBError (RC_DQLParser, EC_NODBASECONNECT);
							YYABORT;
						}
					}
				/*  DBaseFileContainer freigeben */
					DELETE_OBJ (pDBFs);
					DELETE_VEC (pExprBuff);
					DELETE_VEC (pGlobalExpr);
					DELETE_VEC (pLocalExpr);
					DELETE_OBJ (pGlobalKF);
					DELETE_OBJ (pGlobalRL);
				}
		;

RelationalHead:
				DBASE '{'
				{
				/* DBaseFileContainer und DBaseExprBuff bilden */
					pDBFs = new DBaseFiles;
					if (pDBFs == NULL) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					if (pExprBuff == NULL)
						pExprBuff = new char [EXPRBUFFSIZE+1];
					if (pExprBuff == NULL) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
				/* Variablen initialisieren */
					pGlobalExpr = NULL;
					pLocalExpr = NULL;
				/* Flags initialisieren */
					groupActive = FALSE;
					pGs -> EveryDelete();	   // keine Gruppen
				}
		;

Tabellen:	   USE DateiSpezifikationen ';'
				{
					DefaultDataBase = False;
				}
		|	   USE DEFAULT ';'
				{   // alle dBase-Dateien aus Projekt-Ini lesen
					DefaultDataBase = True;
					if (! ReadAlldBaseFiles (pCB, pDBFs, pRF))
						YYABORT;
				}
		;

DateiSpezifikationen:
				DateiSpezifikation
		|	   DateiSpezifikation ',' DateiSpezifikationen
		|	   error
				{
					ExtDBError (RC_DQLParser, EC_BadFileSpec);
					YYABORT;
				}
		;

DateiSpezifikation:	 /* Dateiname einer DBase- (*.dbf) oder 
						   einer Katalog- (*.cat) Datei */
				STRING
				{
					if (! pDBFs -> AddDataIndex (pCB, $1)) {
						ExtDBError (RC_DQLParser, EC_NOFILE);
						YYABORT;
					}
				}
		;

/* Die folgende Anweisung erlaubt das Bilden von Objektgruppen, denen 
   ein neuer Identifikator zugewiesen werden muß, um eine Visualiserung 
   zu ermöglichen.
 */
RelSpezifikationen:
				RelSpezifikation
		|	   RelSpezifikationen RelSpezifikation
		;

RelSpezifikation:	   
				SatzSpezifikation
		|	   DBRelationsSpezifikation
		|	   GruppenSpezifikation
/*	  |	   ReportSelektion */
		;

/* Die SatzSpezifikation definiert die Auswahlkriterien für die zu einem
   GeoDBObjekt gehörenden DBaseSätze. KeyFilter beschreibt die Ankopplung 
   der DBaseSätze an die GeoDBObjekte und SatzFilter beschreibt ein 
   zusätzliches Auswahlkriterium zu Klassifikation 
 */
SatzSpezifikation:
				KeyFilter
		|	   SatzFilter
		|	   KeyFilter SatzFilter 
		;

GruppenSpezifikation:
				GroupHead SatzSpezifikation ClosingBrace
				{
				/* Recherche machen */
					KeyFilter *pKF;
					if (pLocalKF) {
					/* lokale KeyZuordnungsfunktion */
						pKF = pLocalKF;
					/* DBaseSätze aller Objekte löschen, um evtl. neue
					   KeyAnbindung zu ermöglichen */
						pKE -> OF ().DeleteDBaseRecordInfo ();
					} else {
						if (pGlobalKF) {
							pKF = pGlobalKF;
						} else {
							ExtDBError (RC_DQLParser, EC_NODBASECONNECT);
							YYABORT;
						}
					}

					char *pExpr = pLocalExpr ? pLocalExpr : pGlobalExpr;
					RelationList *pRel = pLocalRL ? pLocalRL : pGlobalRL;

				//  Gruppenanzeige im Status-Fenster akt.
					pRStat -> SetGroupText (++GroupCount);
					if (FilterDBaseExpression (*pKF, pExpr, pRel, $<LongToken()>1) != EC_OKAY)
						YYABORT;

				/* Ende einer GruppenAnweisung */
					groupActive = FALSE;
				/* Gruppenlokale Zuweisungsbedingung und RechercheExpression
				   rücksetzen */
					DELETE_VEC (pLocalExpr);
					DELETE_OBJ (pLocalKF);
					DELETE_OBJ (pLocalRL);
				}
		|	   GroupHead error ClosingBrace
				{
				// Ende der Gruppenanweisung
					groupActive = FALSE;

				// gruppenlokalen Speicher wieder freigeben
					DELETE_VEC (pLocalExpr);
					DELETE_OBJ (pLocalKF);
					DELETE_OBJ (pLocalRL);
					ExtDBError (RC_DQLParser, EC_BadGroupSpec);
					YYABORT;
				}
		;

GroupHead:	  GROUP INTEGER '{'
				{
				/* INTEGER ist der neue Identifikator, der allen Objekten
				   zugewiesen werden soll (fest), die die im weiteren
				   gegebenen Bedingungen erfüllen.
				 */
					long newIdent = $<LongToken()>2;
					if (pGs -> hasGroup (NULL, newIdent)) {
						ExtDBError (RC_DQLParser, WC_DOUBLEGROUP);
						YYABORT;
					}
					groupActive = TRUE;

				/*  Gruppenlokale Zuweisungsbedingung und RechercheExpression
					rücksetzen (für alle Fälle nochmal) */
					DELETE_VEC (pLocalExpr);
					DELETE_OBJ (pLocalKF);
					DELETE_OBJ (pLocalRL);

				//  neue Gruppe bilden
					pGs -> AddGroup (NULL, newIdent);

				//  Ident liefern
					long *newID = new long (newIdent);
					if (!newID) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (newID, YYLong);
				}
		|	   GROUP INTEGER STRING '{'
				{
				/* INTEGER ist der neue Identifikator, der allen Objekten
				   zugewiesen werden soll (temporär), die die im weiteren
				   gegebenen Bedingungen erfüllen, STRING ist der KurzText.
				 */
					long newIdent = $<LongToken()>2;
					char *cptr = $<StringToken()>3;

					if (cptr == NULL) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					if (pGs -> hasGroup (cptr, newIdent)) {
						ExtDBError (RC_DQLParser, WC_DOUBLEGROUP);
						DELETE_VEC (cptr);
						YYABORT;
					}
					groupActive = TRUE;

				/*  Gruppenlokale Zuweisungsbedingung und RechercheExpression
					rücksetzen (für alle Fälle nochmal) */
					DELETE_VEC (pLocalExpr);
					DELETE_OBJ (pLocalKF);
					DELETE_OBJ (pLocalRL);							

				//  neue Gruppe bilden
					pGs -> AddGroup (cptr, newIdent);

				//  neuen temp. Ident erzeugen
					PBDDATA Data;
					memset (&Data, '\0', sizeof (PBDDATA));	 // init.
					Data.dwSize = sizeof (PBDDATA);
					Data.pbdTyp = 'i';					  // Ident-Typ
					Data.pbdCode = newIdent;
					Data.pbdKText = cptr;
					Data.pbdTemp = True;		// ID soll temp. sein
					Data.pbdKTextLen = lstrlen (cptr);
					DEX_ModPBDData (Data);

				//  Ident liefern
					long *newID = new long (newIdent);
					if (!newID) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (newID, YYLong);

				//  Speicher freigeben
					DELETE_VEC (cptr);
				}
		|	   GROUP STRING '{'
				{
				/* STRING ist der Bezeichner eines neuen Identifikators, der
				   seinerseits aus einer Menge vordefinierter Identifikatoren
				   ausgewählt wird (temporär).
				 */
					char *cptr = $<StringToken()>2;
					if (cptr == NULL) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					long tempIdent = DEX_GetUniqueICode ();
					if (pGs -> hasGroup (cptr, tempIdent)) {
						ExtDBError (RC_DQLParser, WC_DOUBLEGROUP);
						DELETE_VEC (cptr);
						YYABORT;
					}
					groupActive = TRUE;
					DELETE_VEC (pLocalExpr);
					DELETE_OBJ (pLocalKF);
					DELETE_OBJ (pLocalRL);							

				//  neue Gruppe bilden
					pGs -> AddGroup (cptr, tempIdent);

				//  neuen temp. Ident erzeugen
					PBDDATA Data;
					memset (&Data, '\0', sizeof (PBDDATA));	 // init.
					Data.dwSize = sizeof (PBDDATA);
					Data.pbdTyp = 'i';					  // Ident-Typ
					Data.pbdCode = tempIdent;
					Data.pbdKText = cptr;
					Data.pbdTemp = True;		// ID soll temp. sein
					Data.pbdKTextLen = lstrlen (cptr);
					DEX_ModPBDData (Data);

				//  Ident liefern
					long *newID = new long (tempIdent);
					if (!newID) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (newID, YYLong);

				//  Speicher freigeben
					DELETE_VEC (cptr);
				}
		;

SatzFilter:	 WHERE DBASEEXPR ';'
				{
				/* Für alle Objekte mit Ihren Sätzen gegebene
				   DBaseExpr berechnen und auswerten. ggf. Satz
				   merken. Auch hier ist die Expr mit Objektmerkmalen
				   parametrisierbar.
				 */
					char *cptr = $<StringToken()>2;
					if (cptr == NULL) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					if (groupActive) {
					// lokale FilterExpression merken
						pLocalExpr = new char [lstrlen(cptr) +1];
						if (pLocalExpr)
							lstrcpy (pLocalExpr, cptr);
						else {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					 } else {
					// globale FilterExpression merken
						DELETE_VEC (pGlobalExpr);
						pGlobalExpr = new char [lstrlen(cptr) +1];
						if (pGlobalExpr)
							lstrcpy (pGlobalExpr, cptr);
						else {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					}
				//  Speicher wieder freigeben
					DELETE_VEC (cptr);
				}
		|	   WHERE error ';'
				{
					ExtDBError (RC_DQLParser, EC_BaddBaseExpr);
					YYABORT;
				}
		;

KeyFilter:	  KEY IS '[' GeoDBKeySpez ',' DBaseKeySpez ']' ';'
				{
				/* Ein DBaseSchlüssel, bestehend aus einem DBaseFeldnamen und
				   einem konkreten ObjektSchlüssel, wird definiert.
				 */
					if (groupActive) {   // innerhalb einer Gruppe
						pLocalKF = new KeyFilter (&$<GeoDBKeyToken()>4, &$<DBaseKeyToken()>6, FALSE);
						if (!pLocalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					} else {
						DELETE_OBJ (pGlobalKF);
						pGlobalKF = new KeyFilter (&$<GeoDBKeyToken()>4, &$<DBaseKeyToken()>6, FALSE);
						if (!pGlobalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					}
				}
		|	   KEY IS UNIQUE '[' GeoDBKeySpez ',' DBaseKeySpez ']' ';'
				{
				/* Ein DBaseSchlüssel, bestehend aus einem DBaseFeldnamen und
				   einem konkreten ObjektSchlüssel, wird definiert. Dabei wird
				   vorrausgesetzt, daß jedem GeometrieObjekt genau ein DBase-
				   Satz zugeordnet ist.
				 */
					if (groupActive) {  // innerhalb einer Gruppe
						pLocalKF = new KeyFilter (&$<GeoDBKeyToken()>5, &$<DBaseKeyToken()>7, TRUE);
						if (!pLocalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					} else {
						DELETE_OBJ (pGlobalKF);
						pGlobalKF = new KeyFilter (&$<GeoDBKeyToken()>5, &$<DBaseKeyToken()>7, TRUE);
						if (!pGlobalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					}
				}
		|	   KEY IS '[' RedDBaseKeySpez ']' ';'
				{
					if (groupActive) {   // innerhalb einer Gruppe
						pLocalKF = new KeyFilter (&$<DBaseKeyToken()>4, FALSE);
						if (!pLocalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					} else {
						DELETE_OBJ (pGlobalKF);
						pGlobalKF = new KeyFilter (&$<DBaseKeyToken()>4, FALSE);
						if (!pGlobalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					}
				}
		|	   KEY IS UNIQUE '[' RedDBaseKeySpez ']' ';'
				{
					if (groupActive) {  // innerhalb einer Gruppe
						pLocalKF = new KeyFilter (&$<DBaseKeyToken()>5, TRUE);
						if (!pLocalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					} else {
						DELETE_OBJ (pGlobalKF);
						pGlobalKF = new KeyFilter (&$<DBaseKeyToken()>5, TRUE);
						if (!pGlobalKF) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
					}
				}
		|	   KEY error ';'
				{
					ExtDBError (RC_DQLParser, EC_BadKeySpec);
					YYABORT;
				}
		;

/* Das NonTerminal GeoDBKeySpez repräsentiert den Anbindungsmechanismus
   der DBaseDaten an die Geometrieobjekte von der Seite der GeoDB. Es 
   besteht aus einem Ausdruck, aus dem der eigentliche Schlüssel ableitbar
   ist. 
   Der DBaseSchlüssel kann gegeben sein:
		. als MerkmalsCode (IntZahl) - der entsprechende Merkmalswert
		  des aktuell untersuchten Objektes enthält den Schlüssel;
		. als Parameter ($IntZahl) - der Schlüssel zu den DBaseDaten wird
		  in diesem Fall mit Hilfe der GeoDB-INI-Datei bestimmt. Die IntZahl 
		  gibt die Nummer des in der GeoDB-INI für dieses Objekt gegeben
		  Ausdruckes an, der den DBaseSchlüssel repräsentiert. 
 */
GeoDBKeySpez:   '%' INTEGER
				{
				/* Schlüssel zu DBaseSätzen ist über Parameter gegeben.
				   D.h. Die INTEGER-Zahl gibt die Nummer des Eintrages in
				   der GeoDB-INI an, die als Schlüssel zu der anzubindenden
				   DBaseDatei verwendet werden soll.
				 */
					GeoDBKey *pGDBKey = new GeoDBKey (DBKParameter, $<LongToken()>2);
					if (!pGDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pGDBKey, YYGeoDBKey);
				}
		|	   INTEGER
				{
				/* Schlüssel zu DBaseSätzen ist als MerkmalsCode gegeben.
				   Die INTEGER-Zahl wird als MerkmalsCode ausgewertet. Der 
				   entsprechende MerkmalsWert ist der Feldinhalt des Feldes in der DBaseDatei.
				 */
					GeoDBKey *pGDBKey = new GeoDBKey (DBKCode, $<LongToken()>1);
					if (!pGDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pGDBKey, YYGeoDBKey);
				}
		;

/* Das Nonterminal DBaseKeySpez repräsentiert den Anbindungsmechanismus der
   DBaseDaten an die Geometrieobjekte von der Seite der DBaseDaten. Es 
   definiert einen FeldNamen, unter dem der am GeometrieObjekt abgelegte DBase-
   Schlüssel in der DBaseDatei gespeichert ist.
 */
DBaseKeySpez:   STRING
				{
				/* Der FeldName in der DBaseDatei, der als SchlüsselFeld
				   verwendet werden soll ist direkt gegeben (als String).
				 */
					char *cptr = $<StringToken()>1;
					if (!cptr) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					DBaseKey *pDBKey = new DBaseKey (DBField, cptr);
					if (!pDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDBKey, YYDBaseKey);
					DELETE_VEC (cptr);
				}
		|	   INTEGER
				{
				/* Der FeldName in der DBaseDatei, der als SchlüsselFeld 
				   benutzt wird, ist als MerkmalsWert mit dem als INTEGER-
				   Zahl gegebenen MerkmalsCode am aktuellen Geometrie-
				   objekt abgelegt. */
					DBaseKey *pDBKey = new DBaseKey (DBCode, $<LongToken()>1);
					if (!pDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDBKey, YYDBaseKey);
				}
		|	   '%' INTEGER
				{
				/* Der FeldName in der DBaseDatei, der als SchlüsselFeld 
				   benutzt wird, ist als Parameter in der GeoDB-INI gegeben.
				   Damit ist eine Identifikatorbezogene Anbindung möglich.
				 */
					DBaseKey *pDBKey = new DBaseKey (DBParameter, $<LongToken()>2);
					if (!pDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDBKey, YYDBaseKey);
				}
		|	   TagSpezifikation
		;
		
RedDBaseKeySpez:   STRING
				{
				/* Der FeldName in der DBaseDatei, der als SchlüsselFeld
				   verwendet werden soll ist direkt gegeben (als String).
				 */
					char *cptr = $<StringToken()>1;
					if (!cptr) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					DBaseKey *pDBKey = new DBaseKey (DBField, cptr, True);	  // nur Expression geg.
					if (!pDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDBKey, YYDBaseKey);
					DELETE_VEC (cptr);
				}
		|	   '%' INTEGER
				{
				/* Der FeldName in der DBaseDatei, der als SchlüsselFeld 
				   benutzt wird, ist als Parameter in der GeoDB-INI gegeben.
				   Damit ist eine Identifikatorbezogene Anbindung möglich.
				 */
					DBaseKey *pDBKey = new DBaseKey (DBParameter, $<LongToken()>2, True);	   // nur Expr. geg.
					if (!pDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDBKey, YYDBaseKey);
				}
		;
		
TagSpezifikation:
				LT IDENT GT
				{
				/* Die Anbindung an die DBaseDaten erfolgt nicht über einen
				   FeldNamen, sondern über einen vordefinierten Tag in der
				   DBaseDatei.
				 */
					char TagName[30];
					char *cptr = $<StringToken()>2;
					if (cptr == NULL) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					wsprintf (TagName, "<%s>", cptr);
					DELETE_VEC (cptr);

					DBaseKey *pDBKey = new DBaseKey (DBTag, TagName);
					if (!pDBKey) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDBKey, YYDBaseKey);
				}
		;

DBRelationsSpezifikation:
				RELATION IS DEFAULT ';'
				{
					DefaultRelation = True;
				}
		|
				RELATION IS UNIQUE '[' MasterTerm ',' SlaveTerm ']' ';'
				{
				//  Relation aufbauen und in Container ablegen
					DefaultRelation = False;
					if (AddRelation ($<MasterTermToken()>5, $<SlaveTermToken()>7) !=
						EC_OKAY)
						YYABORT;
				}
		;

MasterTerm:	 IDENT ':' IDENT
				{
				// DB-Alias, FeldName
				MasterTerm *pMTerm = new MasterTerm ($<StringToken()>1, $<StringToken()>3);
					if (!pMTerm) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);

						YYABORT;
					}
					YYSTACK (pMTerm, YYMasterTerm);
				}
		|	   IDENT
				{
				// nur FeldName, DB ist default
					CTable t(*pDBFs);
					if (t.First()) {
						DataIndexLock l(t);
						MasterTerm *pMTerm = new MasterTerm (l -> alias.ptr(), $<StringToken()>1);
						if (!pMTerm) {
							DEX_Error (RC_DQLParser, EC_NOMEMORY);
							YYABORT;
						}
						YYSTACK (pMTerm, YYMasterTerm);
					} else {
						ExtDBError (RC_DQLParser, EC_NODBASEFILE);
						YYABORT;
					}
				}
		;

SlaveTerm:	  IDENT ':' TagSpezifikation
				{
				// SlaveDB-Alias und Tag
					SlaveTerm *pSTerm = new SlaveTerm ($<StringToken()>1, $<DBaseKeyToken()>3);
					if (!pSTerm) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pSTerm, YYSlaveTerm);
				}
		;

/*
ReportSelektion:
				SELECT EnumRelSelektionen ';'
				{
				// Für alle gemerkten DBaseSätze auszugebende Info
				// berechnen und als ReportEingabe abspeichern.
				// StandardSelektNamen verwenden.
				}
		|	   SELECT EnumRelSelektionen TO STRING ';'
				{
				// Für alle gemerkten Datensätze auszugebende Info
				// berechnen und als Reporteingabe unter dem gegebenen
				// Namen (STRING) abspeichern.
				}
		;

EnumRelSelektionen:
				EnumRelSelektion
		|	   EnumRelSelektion ',' EnumRelSelektionen
		|	   error
				{
					// ExtDBError (RC_DQLParser, );
					YYABORT;
				}
		;

EnumRelSelektion:
				DBASEEXPR	   // vorerst nur DBaseExpr
				{
					// Für alle selektierten DatenSätze diese Expression
					// berechnen und Resultat merken.
				}
		;
*/

/* Ausgabeformatierung ----------------------------------------------------- */
AusgabeStatement:
/*			  REPORT AusgabeSpezifikation '{' ReportScript ClosingBrace */
				REPORT
				{
						if (fSyntaxTestOnly)
							yyignore;
				}
						AusgabeSpezifikation ';'

/*			  REPORT '{' ReportScript ClosingBrace */
		|	   REPORT error '{'
				{
					ExtDBError (RC_DQLParser, EC_BadOutStat);
					YYABORT;
				}
		;

/* diverse HilfsKonstrukte zur FehlerBehandlung ---------------------------- */
ClosingBrace:   '}'
		|	   error
				{
					ExtDBError (RC_DQLParser, EC_SYNTAX);
					YYABORT;
				}
		;

ClosingParanthesis:	 
				')'
		|	   error
				{
					ExtDBError (RC_DQLParser, EC_SYNTAX);
					YYABORT;
				}
		;

/*
NumValue:	   INTEGER
				{
					double *pD = new double [1];
					if (!pD) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					*pD = (double) $<LongToken()>1;
					YYSTACK (pD, YYDouble);
				}
		|	   FLOAT
				{
					double *pD = new double [1];
					if (!pD) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					*pD = $<FloatToken()>1;
					YYSTACK (pD, YYDouble);
				}
		|	   error
				{
					ExtDBError (RC_DQLParser, EC_BadNumericFormat);
					YYABORT;
				}
		;
*/

/* Definition des AusgabeMediums ------------------------------------------- */
AusgabeSpezifikation:   
				ON AusgabeGeraet AS AusgabeForm
				{
					long Cnt = pKE -> OF ().Compact();
					switch ($<DevTypeToken()>2) {
						case DTWindow: {
							if ($<OutTypeToken()>4 == OTObjList ||
								$<OutTypeToken()>4 == OTClassification) {
								if (Cnt != 0) {
									if (pGs -> Count() != 0)
										pKE -> RStatus () = (RSToDo)OTClassification;
									else
										pKE -> RStatus () = (RSToDo)OTObjList;
								} else
									// kein Objekt gefunden
									DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
							}
						}
						break;
						case DTPrinter:
						case DTUnknown:
						default:
								break;
					}
				}
		|	   ON AusgabeGeraet
				{
				/* Standard: Objektliste im Fenster und auf Drucker */
				// Abspeichern, was im StandardFall zu machen ist
					if (pGs -> Count() != 0)
						pKE -> RStatus () = (RSToDo)OTClassification;
					else
						pKE -> RStatus () = (RSToDo)OTObjList;
				}
		|	   AS AusgabeForm
				{
				/* Standard: im Fenster */
					long Cnt = pKE -> OF ().Compact();
					switch ($<OutTypeToken()>2) {
						case OTObjList:
						case OTClassification:
							if (Cnt != 0)
								pKE -> RStatus () = (RSToDo)$<OutTypeToken()>2;
							else
								DEX_Error (RC_DQLParser, WC_RECHNOTFOUND);
						break;

						case OTGraphics:
						case OTSheet:
						case OTUnknown:
						default:
								break;
						}
				}
		;

AusgabeGeraet:  WINDOW
				{
					DeviceType *pDevType = new DeviceType (DTWindow);
					if (!pDevType) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDevType, YYDevice);
				}
/*
		|	   PRINTER
				{
					DeviceType *pDevType = new DeviceType (DTPrinter);
					if (!pDevType) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pDevType, YYDevice);
				}
*/
		|	   error
				{
					ExtDBError (RC_DQLParser, EC_BadOutDevice);
					YYABORT;
				}
		;

AusgabeForm:
/*
				SHEET		   // Tabellarische Ausgabe
				{
					OutputType *pOutType = new OutputType (OTSheet);
					if (!pOutType) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pOutType, YYOutput);
				}
		|	   GRAPHICS		// grafische Ausgabe
				{
					OutputType *pOutType = new OutputType (OTGraphics);
					if (!pOutType) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pOutType, YYOutput);
				}
		|
*/
				OBJLIST		 /* Ausgabe als ObjInfoListe */
				{
					OutputType *pOutType = new OutputType (OTObjList);
					if (!pOutType) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pOutType, YYOutput);
				}
		|	   CLASSIFICATION  /* Klassifikation entsprechend GruppenBildung */
				{
					OutputType *pOutType = new OutputType (OTClassification);
					if (!pOutType) {
						DEX_Error (RC_DQLParser, EC_NOMEMORY);
						YYABORT;
					}
					YYSTACK (pOutType, YYOutput);
				}
		|	   error
				{
					ExtDBError (RC_DQLParser, EC_BadOutForm);
					YYABORT;
				}
		;

/*
// ReportGeneratorSteuerung ------------------------------------------------
ReportScript:
		;
*/

%% 


// Filterung mit gegebenem Tag ------------------------------------------------
static Bool FilterWithTag (DataIndex &DI, DBaseObjNummer &ONr, 
						   KeyFilter &KF, long *MCodes, char **MStrs, 
						   short NumMCodes, Bool ORFlag, char *lpExpr,
						   RelationList *pRel) 
{
//  Filter initialisieren
	char *lpTagName = KF.TagName (ONr._ON, NumMCodes, MCodes, MStrs);
	char *lpKeyValue = KF.KeyValue (ONr._ON, NumMCodes, MCodes, MStrs);

	if (lpTagName == NULL || lpKeyValue == NULL) {
		DELETE_VEC (lpTagName);
		DELETE_VEC (lpKeyValue);
		return TRUE;
	}

	pCB -> tag_name_error = False;	  // keinen Tagnamen-Fehler erz.

	DB_Filter DBF (pCB, DI, ONr, lpTagName, lpKeyValue, lpExpr, pRel);
	Bool toDelete = FALSE;

	if (DBF.Result() == EC_OKAY) {
	// eigentliche Filterung
		if (DBF.Check (ORFlag, KF.isUnique()) != EC_OKAY) {
		// kein Satz gefunden oder Fehler
			toDelete = TRUE;
		}
	} else {
		// die Fehlermeldung hat CodeBase schon ausgegeben
		toDelete = TRUE;
	}

	pCB -> tag_name_error = True;

// Speicher wieder freigeben
	DELETE_VEC (lpTagName);
	DELETE_VEC (lpKeyValue);

	return toDelete;
}

// Filterung ohne gegebenen Tag -----------------------------------------------
static Bool FilterWithoutTag (DataIndex &DI, DBaseObjNummer &ONr, 
												  KeyFilter &KF, long *MCodes, char **MStrs, 
												  short NumMCodes, Bool ORFlag, RelationList *pRel,
												  char *pExprBuff) 
{
//  Filter initialisieren
	char *lpFieldName = KF.FieldName(ONr._ON, NumMCodes, MCodes, MStrs);
	char *lpFieldValue = KF.FieldValue(ONr._ON, NumMCodes, MCodes, MStrs);
	Bool toDelete = FALSE;
	
//	  prüfe Parameter	
	if ((lpFieldName == NULL) && (lpFieldValue == NULL))		// wenn nichts gegeben
	{
		DELETE_VEC (lpFieldValue);
		DELETE_VEC (lpFieldName);
		return TRUE;							// Objekt löschen
	}
		
		char *pExpr = NULL;			 
		if (KF.DBasekey().OnlyExpression () && lpFieldName)	   // nur Expression gegeben ?
		{   
		//	  Merkmale müssen ggf. durch aktuelle Werte ersetzt werden				
				pchar pTempExpr = ExpandDBaseExpression (ONr._ON, lpFieldName);		 
				if (pTempExpr == NULL)
				{				   
					DELETE_VEC (lpFieldValue);
					DELETE_VEC (lpFieldName);
					return TRUE;					
				}
		
		//  erzeuge gemeinsamen Expression
				pExpr = new char [lstrlen (pTempExpr) + lstrlen (pExprBuff) +		 
												  lstrlen (ExprOperator) + 1];												  
				if (!pExpr)				   
				{
					DELETE_VEC (lpFieldName);		   
					DELETE_VEC (pTempExpr);											   
					return TRUE;
				}									  
				
		//  Expression zusammenbauen				
				lstrcpy (pExpr, pExprBuff);
				lstrcat (pExpr, ExprOperator);																	
				lstrcat (pExpr, pTempExpr);				   
				DELETE_VEC (pTempExpr);											   
		}   

	pCB -> field_name_error = False;	// keinen Feldnamen-Fehler erz.
			
//	  geeigneten Konstruktor auswählen
		if (pExpr)
		{
				DB_Filter DBF (pCB, DI, ONr, NULL, NULL, pExpr, pRel);
				if (DBF.Result() == EC_OKAY) 
		{
				// eigentliche Filterung
						if (DBF.Check (ORFlag, KF.isUnique()) != EC_OKAY) 
								toDelete = TRUE;				// kein Satz gefunden oder Fehler
		} 
		else 
						toDelete = TRUE;					// Fehlermeldung ist bereits ausgegeben
		}
		else
		{			   
				if (lpFieldName && lpFieldValue)
				{
				DB_Filter DBF (pCB, DI, lpFieldName, lpFieldValue, ONr, pRel, pExprBuff);
				if (DBF.Result() == EC_OKAY) 
				{
						// eigentliche Filterung
								if (DBF.Check (ORFlag, KF.isUnique()) != EC_OKAY) 
										toDelete = TRUE;				// kein Satz gefunden oder Fehler
				} 
				else 
								toDelete = TRUE;					// Fehlermeldung ist bereits ausgegeben
				}
				else
						toDelete = TRUE;														
		}					   

	pCB -> field_name_error = True;			 // Fehelermeldung wieder aktivieren

//  Speicher wieder freigeben
	DELETE_VEC (lpFieldValue);
	DELETE_VEC (lpFieldName);
	DELETE_VEC (pExpr);

	return toDelete;
}

ErrCode FilterDBaseExpression (KeyFilter &KF, char *pExpr, RelationList *pRel,
							   long newID, Bool ORFlag) {
	CRing rOF (pKE -> OF ());			 // Navigator für ObjektFeld

	CTable tDI (*pDBFs);			 // Navigator für DataIndexDateien

//  Status-Anzeige init.
	ActCount = 0;
	pRStat -> SetMax (pKE -> OF ().Count ());

//  für alle Objekte DBaseDatenSätze zuordnen
	DBaseProFile PF;

	for (rOF.First(); rOF.Valid(); ) {

	//  Status-Zeile akt. und ggf. abbrechen
		pRStat -> SetValue (++ActCount);
		if (pRStat -> Break ())
			return EC_USERBREAK;

		Bool toDelete = FALSE;
		{
		DBaseObjNummerLock l(rOF);
		if (!l) {
			DEX_Error (EC_LOCKERROR, RC_DQLParser);
			continue;   // Fehler
		}

	//  wenn Klassifikation und Objekt schon klassifiziert ist, dann weiter
		if (newID != -1 && l -> _Id != -1) {
			if (!rOF.Next())
				break;		  // letztes Objekt: raus
			continue;		   // sonst weiter
		}

		long ONr = l -> _ON;					// ObjektNummer
		long Id = Id = DEX_GetObjIdent (ONr);   // Identifikator lesen

		pchar pParam = NULL;
		long *pMCodes = NULL;
		char **ppMStrs = NULL;
		short NumMCodes = 0;

	//  1. DBaseMerkmalsCodes aus *.ini holen
		NumMCodes = PF.ReadDBaseCodes (&pMCodes, &ppMStrs, Id);
		if (pMCodes == NULL)	  // keine DBaseMerkmale
			toDelete = TRUE;

	//  2. dBase-Expression für konkretes Objekt expandieren
		if (!toDelete && pExpr) {
			char *Out = ExpandParams (  ONr,	// ObjektNummer
										pMCodes, // MerkmalsCodes
										ppMStrs,  // evtl. Merkmalswerte
										NumMCodes,	  // Anzahl der MCodes
										pExprBuff,	  // expandierte Expr
										EXPRBUFFSIZE, // max. ZeilenLänge
										pExpr);  // geg. DBaseExpr

			 if (Out == NULL)
			// Fehler beim expandieren, entweder kein Merkmal
			// oder kein MerkmalsCode etc.
				toDelete = TRUE;
		}

	//  3. Filterung: //  Master bestimmen/prüfen
		if (! toDelete) {
			pchar pMasterField = NULL;
			Bool delMasterField = False;

			if (DefaultDataBase) {
				if (! pDBFs -> SetMaster (pCB, ppMStrs [0]))
					toDelete = True;
			} else {		// vorgegebene Master-Anbindung
				if (lstrcmp (pDBFs -> GetMaster (), strupr (ppMStrs[0])))
					toDelete = True;
			}

		//  ggf. RelationList aufbauen
			RelationList *pDefRel = NULL;	   //  Default-Relationen
			if (! toDelete) {
				if (DefaultRelation) {
					if (pMCodes[1] > 0) {	   // Masterfeld lesen
						if (GetMiText (pMCodes[1], ONr, pMasterField) != EC_OKAY) {
							delMasterField = True;
							toDelete = True;
						}
					} else {
						if (ppMStrs[1])
							pMasterField = ppMStrs[1];
						else
							toDelete = True;
					}
					if (! toDelete)
						if (! (pDefRel = CreateRelationList (pCB,
										pDBFs -> GetMaster (), pMasterField)))
							toDelete = True;
				}
			}

		//  Recherche durchführen
			if (!toDelete) {
				if (tDI.Find (pDBFs -> GetMaster ())) {
					DataIndexLock lDI(tDI);
					if (lDI) {
						if (KF.hasTag (ONr, NumMCodes, pMCodes, ppMStrs))
						//  Filterung mit Tag und DBaseExpression
							toDelete = FilterWithTag (*lDI, *l, KF, pMCodes,
									   ppMStrs, NumMCodes, ORFlag, pExprBuff,
									   DefaultRelation ? pDefRel : pRel);
						else	//  Filterung ohne Tag
							toDelete = FilterWithoutTag (*lDI, *l, KF, pMCodes,
									   ppMStrs, NumMCodes, ORFlag,
									   DefaultRelation ? pDefRel : pRel, pExprBuff);
					} else {
						DEX_Error (RC_DQLParser, EC_LOCKERROR);
						toDelete = TRUE;		 // weitere Objekte
					}
				} else {		// keinen Master gefunden
					DEX_Error (RC_DQLParser, EC_SYSERROR);
					toDelete = TRUE;	 // weitere Objekte
				}
			}

			if (delMasterField)
				DELETE_VEC (pMasterField);   // Default-MasterFeld
			DELETE_OBJ (pDefRel);			// Default-Relation
		}

	//  4.  Aufräumen
		DELETE_VEC (pMCodes);
		if (ppMStrs) {
			for (short i = 0; i < NumMCodes; i++)
				DELETE_VEC (ppMStrs[i]);
				DELETE_VEC (ppMStrs);
		}

	//  5. ggf. Identifikator setzen
		if (newID != -1 && l -> _Id == -1 && !toDelete)
			l -> _Id = newID;
		}	   // Lock aufheben

	//  6. Satz rauslöschen (wenn ArrayContainer leer ist oder bei Fehler)
		if (newID == -1L) {
			if (toDelete) {
				if (! rOF.Delete()) {
					DEX_Error (RC_DQLParser, EC_SYSERROR);
					return EC_SYSERROR;
				}
			} else {
				if (! rOF.Next())
					break;
			}
		} else {
			// Satz drinlassen, wenn Klassifikation gefordert ist
			if (! rOF.Next())
				break;
		}
	}	   // end_for

	return EC_OKAY;
}

//	  Merkmalswert lesen
Bool GetMerkmalsValue (long lONr, long lMCode, char *pBuffer, short iLen)
{
		if (lMCode != 0) 
		{
		// MerkmalsWert holen
				TARGETMERKMAL tm;

				tm.dwSize = sizeof(TARGETMERKMAL);
				tm.lTarget = lONr;			  // ObjektNummer
				tm.lMCode = lMCode;			 // MerkmalsCode
				tm.imaxLen = iLen;
				tm.pMText = pBuffer;			// kein Buffer: nur Test
				tm.iTTyp = TT_Objekt;
				DEX_GetTextMerkmal (tm);

				return tm.imaxLen > 0;
		}

		return FALSE;
}

//	  Expandiere DBase-Expression 
// dBase-Expression expandieren
pchar ExpandDBaseExpression (long ONr, pchar pExpr) 
{
//  prüfe Parameter
	if (!pExpr || !*pExpr)
				return NULL;

//  Variablen init.
	pchar pAct = pExpr;		 // akt. Zeichen
	pchar pBegin = pExpr;	   // Beginn des öffnenden Separators
	pchar pResult = NULL;	   // Zeiger auf Ergebnis
	pchar pTemp = NULL;		 // Puffer-Zeiger
	char Merkmal [_MAX_PATH] = "";  // akt. Merkmalswert
	short ActLen = 0;		   // Textlängen
	short OldLen = 0;

//  Expression expandieren
	for (; ; ) 
	{
	//  Beginn des 1./weiteren Parameters suchen
				pBegin = pAct;
				while (*pBegin && *pBegin != BeginExpr)
				pBegin++;
				if (!*pBegin)		   // Textende erreicht
				break;

	//  kopiere alle Zeichen bis zum Parameterbeginn
				ActLen = pBegin - pAct;
				pTemp = new char [(pResult ? lstrlen (pResult) : 0) + ActLen + sizeof (Merkmal) + 1];
				if (!pTemp) 
				{				   // wenn kein Speicher mehr
					DEX_Error (RC_ExpdBaseExpr, EC_NOMEMORY);   // Fehlermeldung ausgeben
					DELETE_VEC (pResult);		   // alten Wert ggf. löschen
					return NULL;				// zurück
				}
				*pTemp = '\0';
				if (pResult)
					lstrcpy (pTemp, pResult);	// alten Text kopieren
				DELETE_VEC (pResult);			   // und löschen
				pResult = pTemp;
				OldLen = pResult ? lstrlen (pResult) : 0;   // alte Länge merken
				memcpy (pResult + OldLen, pAct, ActLen); // neuen Text ans akt. Ende kop.
				*(pResult + OldLen + ActLen) = '\0';   // Textende setzen

	//  lese und speichere Merkmalswert
				long MKode = strtol (++pBegin, NULL, DEX_GetMkBase ());
				if (MKode && GetMerkmalsValue (ONr, MKode, Merkmal, sizeof (Merkmal)))
					lstrcat (pResult, Merkmal);
				// else				 
				// {
				//	DELETE (pResult);
				//	return NULL;
				// }
																
	//  akt. Zeiger neu setzen
				while (*pAct && *pAct != EndExpr)
				pAct++;
				if (*pAct)			  // wenn noch kein Textende erreicht,
				pAct++;			 // auf 1. Zeichen nach Separator
				else {				  // Syntax-Fehler
					DEX_Error (RC_ExpdBaseExpr, EC_SYNTAX);
					DELETE_VEC (pResult);
					return NULL;
				}
	}   //  end of while

//  ggf. letzten Zeichen kopieren
	ActLen = pBegin - pAct;
	if (ActLen > 0) 
	{
				pTemp = new char [(pResult ? lstrlen (pResult) : 0) + ActLen + 1];
				if (!pTemp) 
				{
					DELETE_VEC (pResult);
					DEX_Error (RC_ExpdBaseExpr, EC_NOMEMORY);
					return NULL;
				}
				*pTemp = '\0';
				if (pResult) 
					lstrcpy (pTemp, pResult);	  // alten Text kopieren
				DELETE_VEC (pResult);			   // und löschen
				pResult = pTemp;
				OldLen = pResult ? lstrlen (pResult) : 0;
				memcpy (pResult + OldLen, pAct, ActLen); // Rest kopieren
				*(pResult + OldLen + ActLen) = '\0';   // Ende-Kennung setzen
	}

	return pResult;
}
