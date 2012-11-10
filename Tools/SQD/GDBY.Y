%{
// Grammatik für GDB-SchnittstellenEingabe
// File: GDB.Y

#include "stdafx.h"

#include "gdb.h"

#include "dgeoobj.hxx"
#include "yystype.hxx"
#include "hashtabs.hxx"

#pragma warning(disable: 4102)

//  Parameter -----------------------------------------------------------------
long ActEnum = 0;
long ActEnum2 = 0;
long ActStufe = 1;
long ActEbene = 1;
long ActStrichModus = 1;
long ActStrichDicke = 4;

// Container der Eingabedaten -------------------------------------------------
double XMin = DBL_MAX;
double XMax = 0.0;
double YMin = DBL_MAX;
double YMax = 0.0;

extern int r_flag;	// Geometrie immer mit speichern

double XPKoord = 0.0;
double YPKoord = 0.0;

// KreisParameter -------------------------------------------------------------
static double Winkel = 0.0, Radius = 0.0;
static char *KCode;
static char *KText = NULL;

// PunktAttribute -------------------------------------------------------------
static double XKoord = -1.0;
static double YKoord = -1.0;
static char PunktKennzeichen[5];
static long PunktNummer = 0;
static char *PName = NULL;
static char *PCode = NULL;
static char *PText = NULL;

// TextAttribute --------------------------------------------------------------
static char *Text = NULL;
static double THoehe = -1.0;
static double TLaenge = -1.0;
static double TModus = -1.0;	// TextModus
static int TRicht = 'M';	// Ausrichtung
static char *TCode = NULL;
static double TSWinkel = 0.0;

// Bogen und KreisAttribute ---------------------------------------------------
static double XMKoord = -1.0;
static double YMKoord = -1.0;
static double XKKoord = -1.0;
static double YKKoord = -1.0;
static double KRadius = 0.0;
static char *BCode = NULL;
static char *BText = NULL;

// Linienattribute ------------------------------------------------------------
static double LMWert = -1.0;
static char *LCode;
static char *LText = NULL;

// Flächenattribute -----------------------------------------------------------
static double XFKoord = -1.0;
static double YFKoord = -1.0;
static double SWinkel = -1.0;
static double SAbstand = -1.0;
static char *FText = NULL;
static char *FCode = NULL;
static char *FName = NULL;
static char PTCode [PointerSize];

int yylineno = 1;

extern FILE *yyout;			// AusgabeDatei
extern GDBElementTab *pGDBElemente;	// bereits ausgegebene GDBElemente

extern int k_flag;	// Kreise als Linien/Flächen

// lokale Prototypen ----------------------------------------------------------
void InitParams (void);
void CopyParams (DParam *);

// statische Daten ------------------------------------------------------------
char *TrennSatz = "; --------------------------------------"
		  "---------------------------------------\n";
%}

%start 	GDBDatei

%token	<FloatToken()>		ASCIIREAL

%token	<LongToken()>		INTEGER 
%token	<LongToken()>		PUNKT LINIE KREIS BOGEN POLYGON T_TEXT FLAECHE
%token	<LongToken()>		PUNKTKOORD SYMBOL
%token	<LongToken()>		PUNKT1 LINIE1 KREIS1 BOGEN1 POLYGON1 TEXT1
%token	<LongToken()>		PUNKTKOORD1 FLAECHE1 SYMBOL1
%token	<LongToken()>		PNRSATZ OSSATZ

%token	<FloatToken()>		XSATZ YSATZ RADIUS WINKEL SWINKEL

%token	NSATZ NAMSATZ FLDSATZ SASATZ FLASATZ 
%token	HSATZ ASATZ MSATZ CODESATZ SARSATZ FSATZ SSATZ
%token  X1SATZ Y1SATZ X2SATZ Y2SATZ STTSATZ

%token	<StringToken()>		TXTSATZ PKZSATZ CODE POINTER

%token	IDENT KOMMENTAR
%token	ENUM EB SM ST ENUMI
%token	SICADREAL

%type	<DPunktToken()>		PunktElement PunktFormElement PunktKoordinaten

%type	<DLinieToken()>		LinienElement LinienFormElement Polygon Bogen
%type	<DLinieToken()>		SubLinienElement SubLinienFormElement 
%type	<DLinieToken()>		SubPolygon SubBogen SubKreis

%type	<DPunktToken()>		SubPunktFormElement SubPunktElement SubPunktKoordinaten

%%

GDBDatei:	GDBElemente
	;

GDBElemente:	GDBElement
		{
/* --> GDBElement */
		/* DGeoObj ausgeben */	
			if ((&$<DGeoObjToken()>1) -> OutPut())
				fprintf (yyout, TrennSatz);	// TrennSatz einfügen
		}
	|	GDBElemente GDBElement 
		{
/* --> GDBElemente GDBElement */
			if ((&$<DGeoObjToken()>2) -> OutPut())
				fprintf (yyout, TrennSatz);	// TrennSatz einfügen
		}
	;

/* ElementSatz in der GDB-Schnittstelle ------------------------------------ */
GDBElement:	PunktFormElement
	|	LinienFormElement
	|	FlaechenFormElement
	|	Kreis
	|	TextElement
	|	SymbolElement
	;

PunktFormElement:
		PunktElement
	|	PunktKoordinaten
	;

SubPunktFormElement:
		SubPunktElement
		{
/* --> SubPunktElement */
			(&$<DGeoObjToken()>1) -> OutPut();
		}
	|	SubPunktKoordinaten
		{
/* --> SubPunktKoordinaten */
			(&$<DGeoObjToken()>1) -> OutPut();
		}
	;

LinienFormElement:
		LinienElement
	|	Polygon
	|	Bogen
	;

SubLinienFormElement:
		SubLinienElement
		{
/* --> SubLinienFormElement */
			(&$<DGeoObjToken()>1) -> OutPut();
		}
	|	SubPolygon
		{
/* --> SubPolygon */
			(&$<DGeoObjToken()>1) -> OutPut();
		}
	|	SubBogen
		{
/* --> SubBogen */
			(&$<DGeoObjToken()>1) -> OutPut();
		}
	|	SubKreis
	|	SubTextElement
		{
/* --> SubTextElement */
			(&$<DGeoObjToken()>1) -> OutPut();
		}
	;

FlaechenFormElement:
		FlaechenElementKopf SubLinienFormElemente
		{
/* --> FlaechenElementKopf SubLinienFormElemente */
		DFlaeche *pFL;
		DPunkt *pFirst, *pLast;

			if ($<DGeoObjToken()>2.isA() == DGeoObj :: DGT_Linie) {
			// bisher ist Objekt noch Linie (nur eine Kontur)
				pFL = new DFlaeche();
			DLinie *pDL = &$<DLinieToken()>2;

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pDL -> _pDPL -> FirstDPunkt();
				pLast = pDL -> _pDPL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				pFL -> AddGeoObj (pDL);		// DLinie umhängen
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen
			} else {
			// Objekt ist bereits Fläche
				pFL = new DFlaeche ($<DFlaecheToken()>2);

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pFL -> FirstDPunkt();
				pLast = pFL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen
			}

			pFL -> SetParams (&$<DParamToken()>1);
			pFL -> SetFlaechenParams (XFKoord, YFKoord, SWinkel, SAbstand);
			pFL -> SetCode (FCode);
			pFL -> SetText (FText);
			pFL -> SetName (FName);
			pFL -> SetPointer (PTCode);

			YYSTACK (pFL, YYDFlaeche);

		// Speicher wieder freigeben
			delete pFirst;
			delete pLast;
		}
	|	FlaechenElementKopf MFlaechenElementParameter SubLinienFormElemente
		{
/* --> FlaechenElementKopf MFlaechenElementParameter SubLinienFormElemente */
		DFlaeche *pFL;
		DPunkt *pFirst, *pLast;
		int DGType = $<DGeoObjToken()>3.isA();

			if (DGType == DGeoObj :: DGT_Linie) {
			// bisher ist Objekt noch Linie (nur eine Kontur)
				pFL = new DFlaeche();
			DLinie *pDL = &$<DLinieToken()>3;

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pDL -> _pDPL -> FirstDPunkt();
				pLast = pDL -> _pDPL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				pFL -> AddGeoObj (pDL);		// DLinie umhängen
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen

			} else if (DGType == DGeoObj :: DGT_Flaeche) {
			// Objekt ist bereits Fläche
				pFL = new DFlaeche ($<DFlaecheToken()>3);

			// bei Bedarf Flächenkontur schlieáen
				pFirst = pFL -> FirstDPunkt();
				pLast = pFL -> LastDPunkt();

				if (!pFirst || !pLast) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				if (!(*pFirst == *pLast))
					pFL -> AddGeoObj (pFirst);	// Kontur schlieáen
			}

			pFL -> SetParams (&$<DParamToken()>1);
			pFL -> SetFlaechenParams (XFKoord, YFKoord, SWinkel, SAbstand);
			pFL -> SetCode (FCode);
			pFL -> SetText (FText);
			pFL -> SetName (FName);
			pFL -> SetPointer (PTCode);

			YYSTACK (pFL, YYDFlaeche);

		// Speicher wieder freigeben
			delete pFirst;
			delete pLast;
		}
	;

/* Linienfolge einer Fläche. Die einzelnen Linien müssen u.U. gedreht werden,
   so daá eine geschlossene Kontur entsteht (wird in AddGeoObj gemacht)
 */
SubLinienFormElemente:
		SubLinienFormElement 
	|	SubLinienFormElemente SubLinienFormElement
		{
/* --> SubLinienFormElemente SubLinienFormElement */
			if ($<DGeoObjToken()>1.isA() == DGeoObj :: DGT_Linie) {
			DLinie *pDL = new DLinie ($<DLinieToken()>1);

			// nächstes Objekt als DGeoObj anhängen, da hier auch
			// DText erlaubt ist (SubTextElement)
				if (pDL -> AddGeoObj (&$<DGeoObjToken()>2)) {
				// normales anhängen geglückt, kopieren und raus
					YYSTACK (pDL, YYDLinie);
					break;	// weiter
				}
			// aus Linie hier Fläche machen
			DFlaeche *pDF = new DFlaeche();

				if (!pDF) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				pDF -> AddGeoObj (pDL);	// Linie umhängen
			// neue Kontur anhängen
				pDF -> AddDLinie ($<DLinieToken()>2);
				YYSTACK (pDF, YYDFlaeche);
			} else {
			// SubLinienFormElement ist bereits Fläche
			DFlaeche *pDF = new DFlaeche ($<DFlaecheToken()>1);

				if ($<DGeoObjToken()>2.isA() == DGeoObj :: DGT_Linie) {
				// neues Objekt ist Linie
				DLinie *pDL = new DLinie ($<DLinieToken()>2);

					if (!pDF -> AddGeoObj (pDL)) {
					// neue Linie anhängen gescheitert
					// neue Kontur anhängen
						pDF -> AddDLinie (*pDL);
					}
				}

				YYSTACK (pDF, YYDFlaeche);
			}
		}
	;

/* Einzelelementsätze in der GDB-Schnittstelle ----------------------------- */
SymbolElement:	SymbolElementKopf MSymbolElementParameter
		{
		DSymbol *pSy = new DSymbol();

			YYSTACK (pSy, YYDSymbol);
		}
	;


PunktElement:	PunktElementKopf MPunktElementParameter
		{
/* --> PunktElementKopf MPunktElementParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&$<DParamToken()>1);

			YYSTACK (pDPt, YYDPunkt);
		}
	;

SubPunktElement:	
		SubPunktElementKopf MPunktElementParameter
		{
/* --> SubPunktElementKopf MPunktElementParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&$<DParamToken()>1);

			YYSTACK (pDPt, YYDPunkt);
		}
	;

LinienElement:	LinienElementKopf SubPunktFormElement SubPunktFormElement
		{
/* --> LinienElementKopf SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&$<DPunktToken()>2);
			pObj -> AddGeoObj (&$<DPunktToken()>3);
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		}
	|	LinienElementKopf MLinienElementParameter SubPunktFormElement SubPunktFormElement
		{
/* --> LinienElementKopf MLinienElementParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&$<DPunktToken()>3);
			pObj -> AddGeoObj (&$<DPunktToken()>4);
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		}
	;

SubLinienElement:	
		SubLinienElementKopf SubPunktFormElement SubPunktFormElement
		{
/* --> SubLinienElementKopf SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&$<DPunktToken()>2);
			pObj -> AddGeoObj (&$<DPunktToken()>3);
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		}
	|	SubLinienElementKopf MLinienElementParameter SubPunktFormElement SubPunktFormElement
		{
/* --> SubLinienElementKopf MLinienElementParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&$<DPunktToken()>3);
			pObj -> AddGeoObj (&$<DPunktToken()>4);
			pObj -> SetText (LText);
			pObj -> SetCode (LCode);

			YYSTACK (pObj, YYDLinie);
		}
	;

Kreis:		KreisKopf MKreisParameter 
		{
/* --> KreisKopf MKreisParameter  */
		DLinie *pObj = new DLinie ();
		DPunkt DPt (XKKoord+KRadius, YKKoord);

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&DPt);	// 1. Punkt
			pObj -> MakePolygon (XKKoord, YKKoord, XKKoord+KRadius, YKKoord);
			pObj -> AddGeoObj (&DPt);	// Kreis schlieáen
			pObj -> SetCode (KCode);
			pObj -> SetText (KText);

			if (!k_flag) {		// Kreis ist LinienObjekt
				YYSTACK (pObj, YYDLinie);
			} else {			// Kreis als Fläche
			DFlaeche *pFL = new DFlaeche();

				pFL -> AddGeoObj (pObj); // DLinie umhängen
				YYSTACK (pFL, YYDFlaeche);
			}
		}
	;

SubKreis:	SubKreisKopf MKreisParameter 
		{
/* --> SubKreisKopf MKreisParameter */
		DLinie *pObj = new DLinie ();
		DPunkt DPt (XKKoord+KRadius, YKKoord);

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&DPt);
			pObj -> MakePolygon (XKKoord, YKKoord, XKKoord+KRadius, YKKoord);
			pObj -> AddGeoObj (&DPt);	// Kreis schlieáen
			pObj -> SetCode (KCode);
			pObj -> SetText (KText);

			if (!k_flag) {		// Kreis ist LinienObjekt
				YYSTACK (pObj, YYDLinie);
			} else {			// Kreis als Fläche
			DFlaeche *pFL = new DFlaeche();

				pFL -> AddGeoObj (pObj); // DLinie umhängen
				YYSTACK (pFL, YYDFlaeche);
			}
		}
	;

Bogen:		BogenKopf MBogenParameter SubPunktFormElement SubPunktFormElement
		{
/* --> BogenKopf MBogenParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

		// erster Punkt
		DPunkt DPt ($<DPunktToken()>3);
		double X0 = DPt.X();
		double Y0 = DPt.Y();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&DPt);	// erster Punkt
		// hier konvertierte Koordinaten einfügen
			pObj -> MakePolygon (XMKoord, YMKoord, X0, Y0, Winkel);
			pObj -> AddGeoObj (&$<DPunktToken()>4);	// letzter Punkt
			pObj -> SetCode (BCode);
			pObj -> SetText (BText);

			YYSTACK (pObj, YYDLinie);
		}
	;

SubBogen:	SubBogenKopf MBogenParameter SubPunktFormElement SubPunktFormElement
		{
/* --> SubBogenKopf MBogenParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

		// erster Punkt	
		DPunkt DPt ($<DPunktToken()>3);	
		double X0 = DPt.X();
		double Y0 = DPt.Y();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> AddGeoObj (&DPt);		// erster Punkt
		// hier konvertierte Koordinaten einfügen
			pObj -> MakePolygon (XMKoord, YMKoord, X0, Y0, Winkel);
			pObj -> AddGeoObj (&$<DPunktToken()>4);	// letzter Punkt
			pObj -> SetCode (BCode);
			pObj -> SetText (BText);

			YYSTACK (pObj, YYDLinie);
		}
	;

TextElement:	TextElementKopf MTextElementParameter
		{
/* --> TextElementKopf MTextElementParameter */
		DText *pObj = new DText (XKoord, YKoord);

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> SetTextParams (TRicht, Winkel, THoehe, 
					       TLaenge, TModus, TSWinkel);
			pObj -> SetText (Text);
			pObj -> SetCode (TCode);

			YYSTACK (pObj, YYDText);
		}
	;

SubTextElement:	SubTextElementKopf MTextElementParameter
		{
/* --> SubTextElementKopf MTextElementParameter */
		DText *pObj = new DText (XKoord, YKoord);

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> SetTextParams (TRicht, Winkel, THoehe, 
					       TLaenge, TModus, TSWinkel);
			pObj -> SetText (Text);
			pObj -> SetCode (TCode);

			YYSTACK (pObj, YYDText);
		}
	;

PunktKoordinaten:
		PunktKoordinatenKopf MPunktKoordinatenParameter
		{
/* --> PunktKoordinatenKopf MPunktKoordinatenParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&$<DParamToken()>1);
			pDPt -> SetPunktParams (PunktKennzeichen, PunktNummer);
			pDPt -> SetCode (PCode);
			pDPt -> SetText (PText);
			pDPt -> SetName (PName);

			YYSTACK (pDPt, YYDPunkt);
		}
	|	PunktKoordinatenKopf
		{
/* --> PunktKoordinatenKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		/* Koordinaten von bereits existierenden Punkt holen */
		DPunkt *pDPt = (DPunkt *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDPt == NULL) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
			pDPt -> SetParams (&$<DParamToken()>1);
			YYSTACK (pDPt, YYDPunkt);
		}
	;

SubPunktKoordinaten:
		SubPunktKoordinatenKopf MPunktKoordinatenParameter
		{
/* --> SubPunktKoordinatenKopf MPunktKoordinatenParameter */
			if (XKoord == -1.0 || YKoord == -1.0) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
		DPunkt *pDPt = new DPunkt (XKoord, YKoord);

			pDPt -> SetParams (&$<DParamToken()>1);
			pDPt -> SetPunktParams (PunktKennzeichen, PunktNummer);
			pDPt -> SetCode (PCode);
			pDPt -> SetText (PText);
			pDPt -> SetName (PName);

			YYSTACK (pDPt, YYDPunkt);
		}
	|	SubPunktKoordinatenKopf 
		{
/* --> SubPunktKoordinatenKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		/* Koordinaten von bereits existierenden Punkt holen */
		DPunkt *pDPt = (DPunkt *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDPt == NULL) {
				yyerror ("Fehlende Koordinatenangabe.");
				YYABORT;
			}
			pDPt -> SetParams (&$<DParamToken()>1);
			YYSTACK (pDPt, YYDPunkt);
		}
	;

Polygon:	PolygonKopf MPolygonParameter SubPunktFormElement SubPunktFormElement
		{
/* --> PolygonKopf MPolygonParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> SetText (LText);
			pObj -> AddGeoObj (&$<DPunktToken()>3);	// erster Punkt
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&$<DLinieToken()>2, AM_NoReverse);
			pObj -> AddGeoObj (&$<DPunktToken()>4);	// letzter Punkt

			YYSTACK (pObj, YYDLinie);
		}
	|	PolygonKopf MPolygonParameter
		{
/* --> PolygonKopf MPolygonParameter */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> SetText (LText);
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&$<DLinieToken()>2, AM_NoReverse);

			YYSTACK (pObj, YYDLinie);
		}
	|	PolygonKopf
		{
/* --> PolygonKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		/* kopieren der bereits existierenden Geometrie */
		DLinie *pDLi = (DLinie *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDLi == NULL) {
				yyerror ("Fehlende Geometrieinformation.");
				YYABORT;
			}
			pDLi -> SetParams (&$<DParamToken()>1);
			pDLi -> SetText (LText);
			YYSTACK (pDLi, YYDLinie);
		}
	;

SubPolygon:	SubPolygonKopf MPolygonParameter SubPunktFormElement SubPunktFormElement
		{
/* --> SubPolygonKopf MPolygonParameter SubPunktFormElement SubPunktFormElement */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> SetText (LText);
			pObj -> AddGeoObj (&$<DPunktToken()>3);	// erster Punkt
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&$<DLinieToken()>2, AM_NoReverse);
		// letzter Punkt
			pObj -> AddGeoObj (&$<DPunktToken()>4);	// letzter Punkt

			YYSTACK (pObj, YYDLinie);
		}
	|	SubPolygonKopf MPolygonParameter
		{
/* --> SubPolygonKopf MPolygonParameter */
		DLinie *pObj = new DLinie ();

			pObj -> SetParams (&$<DParamToken()>1);
			pObj -> SetText (LText);
		// hier Polygon-Koordinaten einfügen
			pObj -> AddGeoObj (&$<DLinieToken()>2, AM_NoReverse);

			YYSTACK (pObj, YYDLinie);
		}
	|	SubPolygonKopf
		{
/* --> SubPolygonKopf */
		// wenn Geometrie nicht gespeichert wird, dann Fehler melden
			if (!r_flag) {
				yyerror ("Fehlende Geometrieinformation, verwenden Sie '-r'.");
				YYABORT;
			}

		// kopieren der bereits existierenden Geometrie 
		DLinie *pDLi = (DLinie *)pGDBElemente -> GetDGeoObj (ActEnum, ActEnum2);

			if (pDLi == NULL) {
				yyerror ("Fehlende Geometrieinformation.");
				YYABORT;
			}
			pDLi -> SetParams (&$<DParamToken()>1);
			pDLi -> SetText (LText);

			YYSTACK (pDLi, YYDLinie);
		}
	;

/* Aufschlüsselung der Einzelelementsätze ---------------------------------- */
/* SY - Symbol */
SymbolElementKopf:
		SYMBOL1 MKopfParameter '\n'
	;


MSymbolElementParameter:
		SymbolElementParameter
	|	MSymbolElementParameter SymbolElementParameter
	;

SymbolElementParameter:
		NAMSATZ '\n'
	|	XSATZ KoordinatenWert '\n'
	|	YSATZ KoordinatenWert '\n'
	|	WINKEL KoordinatenWert '\n'
	|	TXTSATZ '\n'
	|	CODESATZ '\n'
	|	OSSATZ INTEGER '\n'
	;


/* PK - Punkt */
PunktElementKopf:
		PUNKT1
		{
/* --> PUNKT1 */	
			InitParams ();		
		}
			MKopfParameter '\n'
			{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktParameter initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
			}
	;

TextElementKopf:
		TEXT1
		{	
/* --> TEXT1 */
			InitParams ();		
		}
			MKopfParameter '\n'
			{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// Parameter initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				TLaenge = -1.0;
				THoehe = -1.0;
				TRicht = 'M';
				TModus = -1.0;
				Winkel = 0.0;
				TSWinkel = 0.0;
				Text = NULL;
				TCode = NULL;
			}
	;

SubTextElementKopf:
		T_TEXT
		{	
/* --> T_TEXT */
			InitParams ();		
		}
			MKopfParameter '\n'
			{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = $<LongToken()>1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// Parameter initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				TLaenge = -1.0;
				THoehe = -1.0;
				TRicht = 'M';
				TModus = -1.0;
				Winkel = 0.0;
				TSWinkel = 0.0;
				Text = NULL;
				TCode = NULL;
			}
	;

MTextElementParameter:
		TextElementParameter
	|	MTextElementParameter TextElementParameter
	|	error
	;

TextElementParameter:
		XSATZ KoordinatenWert '\n'
		{
/* --> XSATZ KoordinatenWert '\n' */
			XKoord = $<FloatToken()>2;
			SetXCont (XKoord);
		}
	|	YSATZ KoordinatenWert '\n'
		{
/* --> YSATZ KoordinatenWert '\n' */
			YKoord = $<FloatToken()>2;
			SetYCont (YKoord);
		}
	|	NSATZ KoordinatenWert '\n'
		{	TLaenge = $<FloatToken()>2;	}
	|	HSATZ KoordinatenWert '\n'
		{	THoehe = $<FloatToken()>2;	}
	|	WINKEL KoordinatenWert '\n'
		{
		/* WSatz */	Winkel = $<FloatToken()>2;	
		}
	|	SWINKEL KoordinatenWert '\n'
		{
		/* SWISatz */	TSWinkel = $<FloatToken()>2;	
		}
	|	ASATZ IDENT '\n'
		{
		char *cptr = $<StringToken()>2;

			if (cptr) {
				TRicht = *cptr;
				delete cptr;
			}
		}
	|	MSATZ KoordinatenWert '\n'
		{	TModus = $<FloatToken()>2;	}
	|	TXTSATZ '\n'
		{	Text = $<StringToken()>1;	}
	|	CODESATZ '\n'
		{
			TCode = $<StringToken()>1;
		}
	|	error '\n'
	;

SubPunktElementKopf:
		PUNKT
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = $<LongToken()>1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktKoordinaten initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
			}
	;

MPunktElementParameter:
		PunktElementParameter
	|	MPunktElementParameter PunktElementParameter
	|	error
	;

PunktElementParameter:	
		XSATZ KoordinatenWert '\n'
		{
			XKoord = $<FloatToken()>2;
			SetXCont (XKoord);
		}
	|	YSATZ KoordinatenWert '\n'
		{
			YKoord = $<FloatToken()>2;
			SetYCont (YKoord);
		}
	;

/* LI - Linie */
LinienElementKopf:
		LINIE1
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

				LMWert = -1.0;
				LText = NULL;
				LCode = NULL;
			}
	;

SubLinienElementKopf:
		LINIE 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = $<LongToken()>1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

				LMWert = -1.0;
				LText = NULL;
				LCode = NULL;
			}
	;

MLinienElementParameter:
		LinienElementParameter
	|	MLinienElementParameter LinienElementParameter
	;

LinienElementParameter:
		MSATZ KoordinatenWert '\n'
		{	LMWert = $<FloatToken()>2;	}
	|	CODESATZ '\n'
		{
			LCode = $<StringToken()>1;
		}
	|	TXTSATZ '\n'
		{	LText = $<StringToken()>1;	}
	|	SASATZ KoordinatenWert '\n'
	|	OSSATZ INTEGER '\n'
	|	error '\n'
	;

/* FL - Fläche */
FlaechenElementKopf:
		FLAECHE1 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// Parameter initialisieren
				XFKoord = -1.0;
				YFKoord = -1.0;
				SWinkel = -1.0;
				SAbstand = -1.0;
				FText = NULL;
				FName = NULL;
				FCode = NULL;
				memset (PTCode, '\0', PointerSize);
			}
	;

MFlaechenElementParameter:
		FlaechenElementParameter
	|	MFlaechenElementParameter FlaechenElementParameter
	;

FlaechenElementParameter:
		NAMSATZ '\n'
		{	FName = $<StringToken()>1;	}
	|	XSATZ KoordinatenWert '\n'
		{
			XFKoord = $<FloatToken()>2;
			SetXCont (XFKoord);
		}
	|	YSATZ KoordinatenWert '\n'
		{
			YFKoord = $<FloatToken()>2;
			SetYCont (YFKoord);
		}
	|	WINKEL KoordinatenWert '\n'
		{	SWinkel = $<FloatToken()>2;	}
	|	SASATZ KoordinatenWert '\n'
		{	SAbstand = $<FloatToken()>2;	}
	|	FLASATZ KoordinatenWert '\n'	/* ignore */
	|	CODESATZ '\n'
		{
			FCode = $<StringToken()>1;
		}
	|	POINTER '\n'
		{ /* Pointer */
		char *cptr = $<StringToken()>1;

			if (cptr) {
				strncpy (PTCode, cptr, PointerSize-1);
				delete cptr;
			}
		}
	|	TXTSATZ '\n'
		{	FText = $<StringToken()>1;	}
	|	HSATZ KoordinatenWert '\n'
	|	PKZSATZ IDENT '\n' 
	|	PNRSATZ INTEGER '\n'
	|	error '\n'
	;

/* KR - Kreis */
KreisKopf:	KREIS1 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// KreisParameter initialisieren
				XKKoord = -1.0;
				YKKoord = -1.0;
				KRadius = 0.0;
				KText = NULL;
				KCode = NULL;
			}
	;

SubKreisKopf:	KREIS 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = $<LongToken()>1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// KreisParameter initialisieren
				XKKoord = -1.0;
				YKKoord = -1.0;
				KRadius = 0.0;
				KText = NULL;
				KCode = NULL;
			}
	;

MKreisParameter:
		KreisParameter
	|	MKreisParameter KreisParameter
	;

KreisParameter:
		XSATZ KoordinatenWert '\n'
		{
			XKKoord = $<FloatToken()>2;
			SetXCont (XKKoord);
		}
	|	YSATZ KoordinatenWert '\n'
		{
			YKKoord = $<FloatToken()>2;
			SetYCont (YKKoord);
		}
	|	RADIUS KoordinatenWert '\n'
		{	KRadius = $<FloatToken()>2;	}
	|	TXTSATZ '\n'
		{	KText = $<StringToken()>1;	}
	|	CODESATZ '\n'
		{
			KCode = $<StringToken()>1;
		}
	| 	error '\n'
	;

/* BO - Bogen */
BogenKopf:	BOGEN1 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// BogenParameter initialisieren
				XMKoord = -1.0;
				YMKoord = -1.0;
				Winkel = 0.0;
				Radius = 0.0;
				BText = NULL;
				BCode = NULL;
			}
	;

SubBogenKopf:	BOGEN 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = $<LongToken()>1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// BogenParameter initialisieren
				XMKoord = -1.0;
				YMKoord = -1.0;
				Winkel = 0.0;
				Radius = 0.0;
				BText = NULL;
				BCode = NULL;
			}
	;

MBogenParameter:
		BogenParameter 
	|	MBogenParameter BogenParameter
	;

BogenParameter:
		XSATZ KoordinatenWert '\n'
		{
			XMKoord = $<FloatToken()>2;
			SetXCont (XMKoord);
		}
	|	YSATZ KoordinatenWert '\n'
		{
			YMKoord = $<FloatToken()>2;
			SetYCont (YMKoord);
		}
	|	RADIUS KoordinatenWert '\n'
		{	Radius = $<FloatToken()>2;	}
	|	WINKEL KoordinatenWert '\n'
		{	Winkel = $<FloatToken()>2;	}
	|	TXTSATZ '\n'
		{	BText = $<StringToken()>1;	}
	|	CODESATZ '\n'
		{
			BCode = $<StringToken()>1;
		}
	|	error '\n'
	;

/* PG - PunktKoordinate */
PunktKoordinatenKopf:
		PUNKTKOORD1 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;
	
				ActStufe = 1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktKoordinaten initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				PText = NULL;
				PName = NULL;
				strnset (PunktKennzeichen, '\0', 5);
				PunktNummer = 0L;
				PCode = NULL;
		}
	;

SubPunktKoordinatenKopf:
		PUNKTKOORD 
		{	InitParams ();		}
			MKopfParameter '\n'
			{
			DParam *pD = new DParam;

				ActStufe = $<LongToken()>1;
				CopyParams (pD);

				YYSTACK (pD, YYDParams);

			// PunktKoordinaten initialisieren
				XKoord = -1.0;
				YKoord = -1.0;
				PText = NULL;
				PName = NULL;
				strnset (PunktKennzeichen, '\0', 5);
				PunktNummer = 0L;
				PCode = NULL;
			}
	;

MPunktKoordinatenParameter:
		PunktKoordinatenParameter 
	|	MPunktKoordinatenParameter PunktKoordinatenParameter
	;

PunktKoordinatenParameter:
		XSATZ KoordinatenWert '\n'
		{
			XKoord = $<FloatToken()>2;
			SetXCont (XKoord);
		}
	|	YSATZ KoordinatenWert '\n'
		{
			YKoord = $<FloatToken()>2;
			SetYCont (YKoord);
		}
	|	PKZSATZ IDENT '\n'
		{
		char *cptr = $<StringToken()>2;

			if (cptr) {
				strncpy (PunktKennzeichen, cptr, 4);
				delete cptr;
			}
		}
	|	PNRSATZ INTEGER '\n'
		{	PunktNummer = $<LongToken()>2;	} 
	|	TXTSATZ '\n'
		{	PText = $<StringToken()>1;	}
	|	CODESATZ '\n'
		{
			PCode = $<StringToken()>1;
		}
	|	WINKEL KoordinatenWert '\n'
	|	NAMSATZ '\n'
		{	PName = $<StringToken()>1;	}
	|	HSATZ KoordinatenWert '\n'
	|	SWINKEL INTEGER '\n'
	|	OSSATZ INTEGER '\n'
	|	error '\n'
	;

/* LY - Polygon */
PolygonKopf:
		POLYGON1 
		{	
/* --> POLYGON1 */
			InitParams ();		
		}
			MKopfParameter '\n'
			{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = 1;
				CopyParams (pD);
				LText = NULL;

				YYSTACK (pD, YYDParams);
			}
	;

SubPolygonKopf:
		POLYGON 
		{	
/* --> POLYGON */
			InitParams ();		
		}
			MKopfParameter '\n'
			{
/* --> MKopfParameter '\n' */
			DParam *pD = new DParam;

				ActStufe = $<LongToken()>1;
				CopyParams (pD);
				LText = NULL;

				YYSTACK (pD, YYDParams);
			}
	;

PolygonParameter:
		NAMSATZ '\n'
		{	YYSTACK (NULL, YYUnknown);	}
	|	NSATZ INTEGER '\n'
		{	YYSTACK (NULL, YYUnknown);	}
	|	TXTSATZ '\n'
		{	LText = $<StringToken()>1;	
			YYSTACK (NULL, YYUnknown);	}
	|	StuetzPunktFeld 
		{
		DLinie *pDLi = new DLinie ();
		
			if (!pDLi -> AddGeoObj (&$<DGeoObjToken()>1)) {
				yyerror ("Kein Speicherplatz.");
				YYABORT;
			}
			YYSTACK (pDLi, YYDLinie);
		}
	|	SASATZ KoordinatenWert '\n'
	|	error '\n'
	;

MPolygonParameter:
		PolygonParameter
		{
			if ($<hasToken()>1) {
			DLinie *pDLi = new DLinie ();
		
				if (!pDLi -> AddGeoObj (&$<DGeoObjToken()>1)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			}
		}
	|	MPolygonParameter PolygonParameter
		{
			if ($<hasToken()>1) {
			DLinie *pDLi = new DLinie ();
		
				if (!pDLi -> AddGeoObj (&$<DGeoObjToken()>1)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			}
			if ($<hasToken()>2) {
			DLinie *pDLi = new DLinie ();
		
				if (!pDLi -> AddGeoObj (&$<DGeoObjToken()>2)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			}
		}
	;


StuetzPunktFeld:
		FeldKopf 
		{
/* --> FeldKopf */
		DPunkt *pDPt = new DPunkt (XPKoord, YPKoord);

			YYSTACK (pDPt, YYDPunkt);
		}
			FeldWerte
		{
/* --> FeldWerte */
		// Feldkopf ist noch Punkt
		DLinie *pDLi = new DLinie();
			
			if (!pDLi -> AddGeoObj (&$<DGeoObjToken()>2)) {
				yyerror ("Kein Speicherplatz.");
				YYABORT;
			}
			if (!pDLi -> AddGeoObj (&$<DGeoObjToken()>3, AM_NoReverse)) {
				yyerror ("Kein Speicherplatz.");
				YYABORT;
			}

			YYSTACK (pDLi, YYDLinie);
		}
	|	FeldKopf
		{
/* --> FeldKopf */
		DPunkt *pDPt = new DPunkt(XPKoord, YPKoord);

			YYSTACK (pDPt, YYDPunkt);
		}
	|	FLDSATZ '\n'
		{
/* --> FLDSATZ '\n' */
		DPunkt *pDPt = new DPunkt();	// leerer Punkt
		
			YYSTACK (pDPt, YYDPunkt);
		}
	;

FeldKopf:	FLDSATZ KoordinatenWert '\n'
		{	
/* --> FLDSATZ KoordinatenWert '\n' */
			XPKoord = $<FloatToken()>2;
			SetXCont (XPKoord);
		}
			KoordinatenWert '\n'
			{
/* --> KoordinatenWert */
				YPKoord = $<FloatToken()>5;
				SetYCont (YPKoord);
			}
	;

FeldWerte:	FeldWert
		{
/* --> FeldWert */
		DPunkt *pDPt = new DPunkt(XPKoord, YPKoord);

			YYSTACK (pDPt, YYDPunkt);
		}
	| 	FeldWerte FeldWert
		{
/* --> FeldWerte FeldWert */
		DPunkt *pDPt = new DPunkt (XPKoord, YPKoord);

			if ($<DGeoObjToken()>1.isA() == DGeoObj :: DGT_Linie) {
			// Objekt ist bereits Linie
			DLinie *pDLi = new DLinie ($<DLinieToken()>1);
						
				if (!pDLi -> AddGeoObj (pDPt)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				YYSTACK (pDLi, YYDLinie);
			} else {
			// Objekt ist noch Punkt
			DLinie *pDLi = new DLinie();
			
				if (!pDLi -> AddGeoObj (&$<DGeoObjToken()>1)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}
				if (!pDLi -> AddGeoObj (pDPt)) {
					yyerror ("Kein Speicherplatz.");
					YYABORT;
				}

				YYSTACK (pDLi, YYDLinie);
			}	
		}
	;

FeldWert:	KoordinatenWert '\n' 
		{	
/* --> KoordinatenWert '\n' */
			XPKoord = $<FloatToken()>1;
			SetXCont (XPKoord);
		}
			KoordinatenWert '\n'
			{
/* --> KoordinatenWert '\n' */
				YPKoord = $<FloatToken()>4;
				SetYCont (YPKoord);
			}
	;
	
/* allgemeine NichtTerminale Token ----------------------------------------- */
MKopfParameter:
		KopfParameter
	|	MKopfParameter KopfParameter
	;

KoordinatenWert:
		SICADREAL ASCIIREAL
		{
		double d = $<FloatToken()>2;
		double *tmpVal = new double (d);

			YYSTACK (tmpVal, YYDouble);
		}
	|	ASCIIREAL
	|	SICADREAL
	|	INTEGER
		{
		double d = (double)$<LongToken()>1;
		double *tmpVal = new double (d);

			YYSTACK (tmpVal, YYDouble);
		}
	;

KopfParameter:
		ENUM '=' INTEGER
		{	
			ActEnum = $<LongToken()>3;
			ActEnum2 = 0;
		}
	|	ENUM '=' INTEGER '/' INTEGER
		{
			ActEnum = $<LongToken()>3;
			ActEnum2 = $<LongToken()>5;
		}
	|	ENUMI '=' INTEGER
		{	/* sorry, not implemented */	}
	|	EB '=' INTEGER
		{	ActEbene = $<LongToken()>3;	}
	|	SM '=' INTEGER
		{	ActStrichModus = $<LongToken()>3;	}
	|	ST '=' INTEGER
		{	ActStrichDicke = $<LongToken()>3;	}
	;

%%

// Standards setzen -----------------------------------------------------------
void InitParams (void) {

	ActStufe = 1;	
	ActEbene = 1;
	ActStrichModus = 1;
	ActStrichDicke = 4;
	ActEnum = 0;
	ActEnum2 = 0;
}

void CopyParams (DParam *pD) {

	pD -> _Stufe = ActStufe;	
	pD -> _Ebene = ActEbene;
	pD -> _Enum = ActEnum;
	pD -> _Enum2 = ActEnum2;
	pD -> _StrichModus = ActStrichModus;
	pD -> _StrichDicke = ActStrichDicke;
}
