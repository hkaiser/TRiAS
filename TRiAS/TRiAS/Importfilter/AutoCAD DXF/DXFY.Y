/*
DXFY.Y
YACC-Spezifikation für den DXF-Import

Realisierung für AutoCAD-Version 12.

Wichtig:
	- Blockbearbeitung erfolgt entsprechend Nutzervorgaben
	- nutzerdefinierte Blöcke werden in Punkte konvertiert
	- alle Koordinaten werden als Weltkoordinaten betrachtet
	- alle unbekannten Headervariablen, Entities und Tabellen
	  werden überlesen
	- der Filter liest quasi nur die ihm bekannten Token, alles andere
	  wird ignoriert

Erarbeitet: J. Benkenstein			  begonnen am: 1. April 1992
										Stand vom: 21.10.1996 
									 überarbeitet: 27.04.98
*/
%{
#include "pheader.hpp"				//	prec. Header

#include <assert.h>					//	assert ()

#include "dxfimp.h"					//	Konstanten
#include "header.hpp"				//	Header
#include "lextypes.h"				//	lex-spezifische Typ-Definitionen
#include "rechstat.hpp"				//	RechStatus
#include "punktli.hpp"				//	Punkt
#include "tools.hpp"				//	Ausgabe-Funktionen
#include "dgeo_obj.hpp"				//	weitere Ausgabe-Funktionen
#include "layers.hpp"				//	CLayerBaum
#include "block.hpp"				//	CBlockTree

#pragma warning (disable: 4101 4102 )

extern "C" 
{
	#include "float.h"		// DBL_MAX
}

// Konstanten
static const int ValidVertex = 16;			// Vertex-Flag
static const int VKP_Vertex = 128;			// Vielflächennetz-Kontrollpunkt
static const int InValidFlag = -1;			// ungültiger Flagwert	
static const int iPolylineClosed = 1;		// Polylinie ist geschlossen
static const int iVielFlaechenNetz = 64;	
static const MaxAutoCadVersion = 1009;		//	AutoCAD Version 12

// Prototypen 
int yylex (void);
void yyerror (short ResourceID);
Bool CreateDGeoObj (DGeoTyp DGT, char *pLayerName, long lExpectedVertices = 0);
Bool CreateTextObject (char *pLayerName, long lExpectedVertices = 0);
Bool CreateSymbolObject (char *pLayerName, char *pBlockName, long lExpectedVertices = 0);
Bool EchteLinie (Punkt *pPt1, Punkt *pPt2);
Bool BildMasseOk (void);
Bool UserBlock (int iFlag);
Bool SystemBlock (int iFlag);
void IncCounter (long ObjNr = 0); 
BOOL ValidFlag (int);
Bool Output (DGeoObj *& pObj);			//	lokale Ausgabe-Funktion
Bool InsertBlock (char *pBlockName);	//	Block einfügen

// externe Variablen
extern double XMin;		 // Bildmaße
extern double YMin;
extern double XMax;
extern double YMax;
// KK000125 - LIMMIN/LIMMAX
extern double XLMin;		 // Bildmaße
extern double YLMin;
extern double XLMax;
extern double YLMax;
//
extern RechercheStatus *pRechStat;      // RechercheStatus
extern Params OptParams;
extern CLayerBaum *g_pLB;
extern CBlockTree *g_pBlockTree;

// lokale Variablen
static DGeoObj *l_pDGO = NULL;	
static CTextObject *l_pTextObject = NULL;
static CSymbolObject *l_pSymbolObject = NULL;
static Bool bInBlockSection = False;
static Bool bOutputNetzError = False;
static Bool bOutputVersionError = False;

//	Datentypen
struct tripel_struct {
	double real1;
	double real2;
	double real3;
};
struct {
	struct tripel_struct params_tripel;
	double params_real1;
	double params_real2;
	double params_real3;
	short params_integer;
} Params;		

// Inline-Funktionen
inline
void SetXCon (double X) { if (X < XMin) XMin = X; if (X > XMax) XMax = X; }
inline
void SetYCon (double Y) { if (Y < YMin) YMin = Y; if (Y > YMax) YMax = Y; }
// KK000125
inline
void SetXLCon (double X) { if (X < XLMin) XLMin = X; if (X > XLMax) XLMax = X; }
inline
void SetYLCon (double Y) { if (Y < YLMin) YLMin = Y; if (Y > YLMax) YLMax = Y; }

inline
void InitParams (void) { Params.params_real1 = Params.params_real2 = Params.params_real3 =
						 Params.params_tripel.real1 = Params.params_tripel.real2 = Params.params_tripel.real3 = 0.0; 
						 Params.params_integer = InValidFlag; }
inline
Bool EchteLinie (Punkt *pPt1, Punkt *pPt2)
{
	return ((pPt1 -> X () != pPt2 -> X ()) ||
			(pPt1 -> Y () != pPt2 -> Y ()));
			/* (pPt1 -> Z () != pPt2 -> Z ()); Höhe bisher nicht geprüft */
}
inline 
Bool BildMasseOk (void)
{
	return ((DBL_MIN != XMax) && (DBL_MIN != YMax) && (DBL_MAX != XMin) && (DBL_MAX != YMin));
}
inline
Bool ValidFlag (int fl)
{
	return 	((fl >= ValidVertex && fl != VKP_Vertex) || 
			/* fl == 1 ||*/ fl == 0 || fl == InValidFlag);
}
%}
%union {
	struct {
		double real1;
		double real2;
		double real3;
	} real_struct; 
	short integer;
	char *str_ptr;
	double real;				
};

%token <integer>		FLAG0
%token <integer>		FLAG1
%token <integer>		VERTEX_COUNT
%token <real>			KOORD
%token <real>			KOORD_X
%token <real>			KOORD_Y
%token <real>			KOORD_Z				
%token <real>			FLOAT
%token <real>			FLOAT1
%token <real>			FLOAT2
%token <real>			FLOAT4
%token <real>			FLOAT5
%token <real>			WINKEL0
%token <real>			WINKEL1
%token <str_ptr>		TEXT0
%token <str_ptr>		LAYER_NAME
%token <str_ptr>		NAME

%type <real_struct>		Tripel
%type <real_struct>		CoordPair
%type <real_struct>		LWVertices

%token <str_ptr>		WINKEL 
%token <str_ptr>		TEXT_HOEHE

%token ANFANG SECTION END_SECT END_OF_FILE ENTITIES HEADER BLOCKS TABLES
%token VERSION EXT_MIN EXT_MAX LAST_EDIT LEX_ERROR ENTITIES LINE
%token LINE POLY_LINE VERTEX SEQEND CIRCLE ARC TEXT_ELEM POINT 
%token INSERT TRACE_ELEM SOLID SHAPE ATTRIB LIM_MIN LIM_MAX
%token BLOCK ENDBLK LWPOLY_LINE 

%start DXF_File

%%
DXF_File:   Sections
		;

Sections:	Section
		|	Sections Section
		;

Section:	HeaderSect
		|	EntitySect
		|	BlockSect
		|	TablesSect
		|	EmptySect
		|	Ende
		|	Error
		;

Error:	    error
			{  
			   yyclearin; 		
			   // return False;
			}
		|	LEX_ERROR
			{
			   return FALSE;			// Fehler bereits ausgegeben
			}		
		;

Ende:	   	END_OF_FILE
			{   // Ende
				if (pRechStat)
					pRechStat -> SetValue (OptParams.MaxLineNr);
				return OptParams.BildMasseOk ? True : -1;
			}
		;

TablesSect: SECTION TABLES END_SECT
		;

EmptySect:	SECTION END_SECT
		;

HeaderSect:	HeaderAnf HeaderElemente END_SECT
			{
				Header HD;
				if (! HD.GetScaleAndOffset ())	// können aber nicht ausgegegben
					return False;				// werden
			// 	Scale und Offset ggf.ausgeben	
				if (!OptParams.BildMasseOk)		// Matrix vorhanden ?
				{	// nein
					if (BildMasseOk ())		// die ermittelten XMax usw. sind Ok
					{
						if (! HD.OutScaleAndOffset ())	// können aber nicht ausgegegben
							return False;				// werden
						OptParams.BildMasseOk = True;
						ResString strImpText (ResID (IDS_IMPORTTEXT, &g_pTE -> RF ()), 80);
						if (pRechStat)		// Importtext ausgeben
							pRechStat -> _ActionText.SetText ((char *)strImpText.Addr ());
					}
				}					
			}
		| 	HeaderAnf END_SECT
			{	// leere Section: Checklauf zur Bestimmung der Bildmaße ggf. durchführen
				// Scale und Offset ggf. ausgeben	
			}
		;

HeaderAnf:	SECTION HEADER
		;

HeaderElemente: 
			HeaderElement			 
		|	HeaderElemente HeaderElement
		;

HeaderElement:	
			Version
		|	MinExt
		|	MaxExt
		|	LastEdit
		|	Error
		;

Version:	VERSION TEXT0
			{
				// Version prüfen
				if ($2 && (strlen ($2) > 2) && (atoi ($2+2) > MaxAutoCadVersion) &&
					!bOutputVersionError)
				{
					bOutputVersionError = True;		//	diese Meldung nicht noch einmal

				//	Anfrage an Nutzer, ob weiter gemacht werden soll ?
					:: MessageBeep (MB_OK);					
					ResString strCaption (ResID (IDS_PARSERERRORCAP, & g_pTE -> RF ()), 20);
					ResString strText (ResID (IDS_ACAD_VERSION, & g_pTE -> RF ()), 200);																					
					MessBox MB (strCaption.Addr (), strText.Addr (), g_pTE -> MWind ());
					MB.SetType (YesNoButtons | QuestionMarkIcon);
					if (NoReply == MB.Show ())
					{
						DELETE_VEC ($2);
						return False;
					}
				}

				DELETE_VEC ($2);
			}
		;

MinExt:   	EXT_MIN Tripel
			{
				SetXCon ($2.real1);
				SetYCon ($2.real2);
			}
		|	LIM_MIN Tripel
			{
				SetXLCon ($2.real1);
				SetYLCon ($2.real2);
			}
		;

MaxExt:   	EXT_MAX Tripel
			{
				SetXCon ($2.real1);
				SetYCon ($2.real2);
			}
		|	LIM_MAX Tripel			
			{
				SetXLCon ($2.real1);
				SetYLCon ($2.real2);
			}
		;

LastEdit: 	LAST_EDIT FLOAT
			{
				// evtl. julianische(s) Zeit/Datum ausgeben 
			}
		;

Tripel:		CoordPair		
		|	KOORD_X KOORD_Y KOORD_Z
			{
				$$.real1 = $1 + OptParams.XOffset;
				$$.real2 = $2 + OptParams.YOffset;
				$$.real3 = $3;
				if (!OptParams.BildMasseOk)
				{
					SetXCon ($$.real1);
					SetYCon ($$.real2);
					// IncCounter ();					
				}
			}
		;

CoordPair:	KOORD_X KOORD_Y
			{
				$$.real1 = $1 + OptParams.XOffset;
				$$.real2 = $2 + OptParams.YOffset;
				if (!OptParams.BildMasseOk)
				{
					SetXCon ($$.real1);
					SetYCon ($$.real2);					
					// IncCounter ();
				}
				$$.real3 = DBL_MAX;
			}
		;

BlockSect:	BlockAnf END_SECT
			{//	ohne Blöcke	
				bInBlockSection = False;
			}
		|	BlockAnf Blocks END_SECT
			{//	mit Blöcken
				bInBlockSection = False;
			}
		;

BlockAnf:	SECTION BLOCKS 
			{
				bInBlockSection = TRUE;
			}
		;

Blocks:		Block
		|	Blocks Block
		;

Block:		BlockKopf ENDBLK
		|	BlockKopf Entities ENDBLK
		;

BlockKopf:	BLOCK LAYER_NAME NAME Tripel FLAG0
			{
				if (OptParams.BildMasseOk)
				{
					if (!g_pBlockTree->CreateBlock ($3, $4.real1, $4.real2))
						return False;
				}
			
				DELETE_VEC ($2);
				DELETE_VEC ($3);
			}
		|	BLOCK LAYER_NAME NAME FLAG0 Tripel
			{
				if (OptParams.BildMasseOk)
				{
					if (!g_pBlockTree->CreateBlock ($3, $5.real1, $5.real2))
						return False;
				}

				DELETE_VEC ($2);
				DELETE_VEC ($3);
			}
		|	BLOCK NAME LAYER_NAME FLAG0 Tripel
			{
				if (OptParams.BildMasseOk)
				{
					if (!g_pBlockTree->CreateBlock ($2, $5.real1, $5.real2))
						return False;
				}

				DELETE_VEC ($2);
				DELETE_VEC ($3);
			}
		;

EntitySect:	 EntityAnf END_SECT
		|	EntityAnf Entities END_SECT
		;

EntityAnf:	SECTION ENTITIES
			{
				bInBlockSection = False;				
			}
		;

Entities:	Entity
		|	Entities Entity
		;

Entity:		Line
		|	Circle
		|	Point
		|	Arc
		|	Trace
		|	Solid
		|	Text
		|	Shape
		|	Insert
		|	PolyLine
		|	Error
		;

Line:		LINE LAYER_NAME Tripel Tripel
			{	// Line
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					DGeoTyp Type;
					if (EchteLinie ((Punkt *) &$3, (Punkt *) &$4))
						Type = DGT_Linie;
					else
						Type = DGT_Punkt;
					if (CreateDGeoObj (Type, $2) == False)
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False)
						return False;
					if (Type == DGT_Linie) 
					{
						if (l_pDGO -> AddPunkt ($4.real1, $4.real2) == False)
						{
							yyerror (IDS_SYSERROR);							
							return False;
						}
					}

				//	lokale Ausgabe-Funktion
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();					
				DELETE_VEC ($2);
			}
		;

Circle: 	CIRCLE LAYER_NAME Tripel FLOAT
			{  	// Circle 
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Flaeche, $2) == False)
						return False;
					if (l_pDGO -> MakePolygon ($4, $3.real1, $3.real2) == False)
						return False;
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();					
				DELETE_VEC ($2);
			}
		|	CIRCLE LAYER_NAME FLOAT Tripel 
			{  	// Circle 
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Flaeche, $2) == False)
						return False;
					if (l_pDGO -> MakePolygon ($3, $4.real1, $4.real2) == False)
						return False;
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();					
				DELETE_VEC ($2);
			}
		;  	

Point:		POINT LAYER_NAME Tripel
			{	// Point
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Punkt, $2) == False)
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False)
						return False;
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();					
				DELETE_VEC ($2);
			}
		;  	

Arc:		ArcKopf ArcParams
			{	// Arc ausgeben
				if (OptParams.BildMasseOk && l_pDGO)
				{
					if (l_pDGO -> MakePolygon (Params.params_real1, 
											 Params.params_tripel.real1, Params.params_tripel.real2,
											 Params.params_real2, Params.params_real3) == False)
						return False;
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();					
			}
		;

ArcKopf:	ARC LAYER_NAME	
			{//	ArcKopf
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Flaeche, $2) == False)
						return False;
					InitParams ();
				}
				DELETE_VEC ($2);
			}
		;

ArcParams:	ArcParam ArcParam ArcParam ArcParam
		;
			 
ArcParam:	Tripel
			{//	Zentrum-Koordinaten speichern
				Params.params_tripel.real1 = $1.real1;
				Params.params_tripel.real2 = $1.real2;
				Params.params_tripel.real3 = $1.real3;
			}
		|	FLOAT
			{//	Radius
				Params.params_real1 = $1;
			}
		|	WINKEL0
			{//	Startwinkel
				Params.params_real2 = $1;
			}
		|	WINKEL1
			{//	Stopwinkel
				Params.params_real3 = $1;
			}
		;
			
Trace:		TRACE_ELEM LAYER_NAME Tripel Tripel Tripel Tripel
			{   // Trace
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Flaeche, $2) == False)
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False) // 1.
						return False;		
					if (l_pDGO -> AddPunkt ($4.real1, $4.real2) == False)	// 2.
						return False;
					if (l_pDGO -> AddPunkt ($5.real1, $5.real2) == False)	// 3.
						return False;
					if (l_pDGO -> AddPunkt ($6.real1, $6.real2) == False) // 4.
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False) // 1.
						return False;
					if (!Output (l_pDGO))
						return False;
				}			
				else
					IncCounter ();					
				DELETE_VEC ($2);
			}
		;  	

Solid:		SOLID LAYER_NAME Tripel Tripel Tripel 
			{	// Dreieck (Solid)
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Flaeche, $2) == False)
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False) // 1.
						return False;		
					if (l_pDGO -> AddPunkt ($4.real1, $4.real2) == False)	// 2.
						return False;
					if (l_pDGO -> AddPunkt ($5.real1, $5.real2) == False)	// 3.
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False) // 1.
						return False;
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();					
				DELETE_VEC ($2);
			}
		|	SOLID LAYER_NAME Tripel Tripel Tripel Tripel
			{	// Viereck (Solid): hier ist der 3. mit dem 1. Pkt. zu verbinden !
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Flaeche, $2) == False)
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False) // 1.
						return False;		
					if (l_pDGO -> AddPunkt ($4.real1, $4.real2) == False)	// 2.
						return False;
					if (l_pDGO -> AddPunkt ($6.real1, $6.real2) == False)	// 4.
						return False;
					if (l_pDGO -> AddPunkt ($5.real1, $5.real2) == False)	// 3.
						return False;
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False) // 1.
						return False;
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();					
				DELETE_VEC ($2);
			}
		;  	

Text:		TextKopf TextParams
			{	//	Text ausgeben
				if (OptParams.BildMasseOk && l_pTextObject)
				{
					if (!Output ((DGeoObj*&)l_pTextObject))
						return False;	
				}
				else
					IncCounter ();					
			}
		;

TextKopf:	TEXT_ELEM LAYER_NAME
			{	//	Textkopf
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					Bool bRet = CreateTextObject ($2);
					DELETE_VEC ($2);

				//	ggf. zurück
					if (!bRet)
					{
						yyerror (IDS_SYSERROR);
						return False;					
					}
				}
				else
				{
					DELETE_VEC ($2);
					IncCounter ();	
				}									
			}
		;

TextParams:		TextParam
			|	TextParams TextParam
			;

TextParam:	Tripel
			{	// Koordinate speichern
				if (OptParams.BildMasseOk && l_pTextObject)
					if (!l_pTextObject -> AddPunkt ($1.real1, $1.real2))
						return False;
			}				
		|	TEXT0
			{//	Wert speichern
				if (OptParams.BildMasseOk && l_pTextObject)
				{
					Bool bRet = l_pTextObject -> SetText ($1);
				
				//	Text löschen
					DELETE_VEC ($1);

					if (!bRet)
					{
						yyerror (IDS_SYSERROR);
						return False;
					}
				}
				else
					DELETE_VEC ($1);
			}				
		|	TEXT_HOEHE 
			{	// Höhe speichern
			  	if (OptParams.BildMasseOk && l_pTextObject && OptParams.m_bImpTextHoehe)
				{
					Bool bRet = l_pTextObject -> SetHoehe ($1);
					if (!bRet)
					{
						yyerror (IDS_SYSERROR);
						return False;
					}
				}
				else
					DELETE_VEC ($1);
			}				
		|	WINKEL0
			{	//	Winkel speichern
				if (OptParams.BildMasseOk && l_pTextObject && OptParams.m_bImpTextDrehWi)
					l_pTextObject -> SetWinkel ($1);					
			}				
		;
								
Shape:		SHAPE LAYER_NAME Tripel NAME
			{	// Shape (Symbol)
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (CreateDGeoObj (DGT_Punkt, $2) == False) 	
						return False;						
					if (l_pDGO -> AddPunkt ($3.real1, $3.real2) == False)
						return False;
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();	
				DELETE_VEC ($2);
				DELETE_VEC ($4);
			}
		;

Insert:		InsertElem
			{	
				if (OptParams.BildMasseOk && l_pSymbolObject)
				{
					if (!Output ((DGeoObj*&)l_pSymbolObject))
//						return False;
						break;	// KK991230
				}	
				else
					IncCounter ();								
			}
		|	InsertElem Attribs Seqend
			{	
				if (OptParams.BildMasseOk && l_pSymbolObject)
				{
					if (!Output ((DGeoObj*&)l_pSymbolObject))
//						return False;
						break;	// KK991230
				}
				else
					IncCounter ();	
			}
		;		

InsertElem:	InsertElemKopf InsertElemParams
		;

InsertElemKopf: 
			INSERT LAYER_NAME NAME
			{
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($2) && InsertBlock ($3))
				{
					if (!CreateSymbolObject ($2, $3))
						return False;							
				}								
				DELETE_VEC ($2);	
				DELETE_VEC ($3);
			}
		|   INSERT NAME LAYER_NAME
			{
				if (OptParams.BildMasseOk && g_pLB -> IsValid ($3) && InsertBlock ($2))
				{
					if (!CreateSymbolObject ($3, $2))
						return False;
				}								
				DELETE_VEC ($2);	
				DELETE_VEC ($3);
			}
		;

InsertElemParams:
			InsertElemParam
		|	InsertElemParams InsertElemParam
		;

InsertElemParam:
			Tripel
			{//	Einfügepunkt speichern
				if (OptParams.BildMasseOk && l_pSymbolObject)
				{
					l_pSymbolObject->XInsert () = $1.real1;
					l_pSymbolObject->YInsert () = $1.real2;
				}
			}
		|	WINKEL0
			{//	Symbol-Drehwinkel
				if (OptParams.BildMasseOk && l_pSymbolObject && 
					OptParams.m_bImpSymDrehWi)
					l_pSymbolObject -> SetWinkel ($1);
			}
		|	FLOAT1
			{//	X-Masstabsfaktor
				if (OptParams.BildMasseOk && l_pSymbolObject)
					l_pSymbolObject->XMasstab () = $1;
			}
		|	FLOAT2
			{// Y-Masstabsfaktor
				if (OptParams.BildMasseOk && l_pSymbolObject)
					l_pSymbolObject->YMasstab () = $1;
			}
		|	FLOAT5
			{// Zeilenabstand
				if (OptParams.BildMasseOk && l_pSymbolObject)
					l_pSymbolObject->ZeilenAbstand () = $1;
			}
		|	FLOAT4
			{// Spaltenabstand
				if (OptParams.BildMasseOk && l_pSymbolObject)
					l_pSymbolObject->SpaltenAbstand () = $1;
			}
		|	FLAG0
			{// Spalten
				if (OptParams.BildMasseOk && l_pSymbolObject)
					l_pSymbolObject->Spalten () = $1;
			}
		|	FLAG1
			{//	Zeilen
				if (OptParams.BildMasseOk && l_pSymbolObject)
					l_pSymbolObject->Zeilen () = $1;
			}
		;

Attribs:	  /* ohne Attribute */
		|	Attribs Attrib
		;

Attrib: 	ATTRIB LAYER_NAME Tripel TEXT0 NAME
			{	// Attrib: TEXT0 ist Merkmalswert und NAME Kurztext des Merkmals
				if (OptParams.BildMasseOk && OptParams.bImpMerkmale && l_pSymbolObject) 
				{
					if (l_pSymbolObject -> AddMerkmal ($5, $4) == False)
						return False;										
				}	
				DELETE_VEC ($2);	
				DELETE_VEC ($4);	
				DELETE_VEC ($5);	
			}
		;
			
Seqend:		SEQEND	
		|	SEQEND LAYER_NAME
			{	// Seqend
				DELETE_VEC ($2);					
			}
		;		
			
PolyLine:	PolyLineKopf Vertices Seqend
			{ // PolyLine	
				if (OptParams.BildMasseOk && l_pDGO)
				{
					if (l_pDGO -> isA () == DGT_Flaeche)		// Linie schließen ?
					{
					//	letztes Segment
						if (!l_pDGO -> AddFirstPunkt (
							ValidFlag (Params.params_integer) ? Params.params_real1 : 0)) 
						{
							return False;		
						}
					}					
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();	
			}
		|	LWPolyLineKopf LWVertices 
			{ // LWPolyLine	
				if (OptParams.BildMasseOk && l_pDGO)
				{
					if (l_pDGO -> isA () == DGT_Flaeche)		// Linie schließen ?
					{
						if (!l_pDGO -> AddFirstPunkt()) 
							return False;		
					}					
					if (!Output (l_pDGO))
						return False;
				}
				else
					IncCounter ();	
			}
		;
			
PolyLineKopf: 
			POLY_LINE LAYER_NAME
			{	// PolyLine
			  	if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (!CreateDGeoObj(DGT_Linie, $2))
						return False;			  	
				}
			  	DELETE_VEC ($2);					
			}					
		|	POLY_LINE LAYER_NAME FLAG0
			{	// PolyLine
			  	if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if ($3 & iVielFlaechenNetz)
					{
					//	wird hier nicht behandelt
					//	ggf. Fehlermeldung ausgeben
						if (!bOutputNetzError)
						{
							bOutputNetzError = True;
							yyerror (IDS_CAN_NOT_IMP_NETZ);
						}
					}
					else
					{
			  			DGeoTyp Type = ($3 & iPolylineClosed) ? DGT_Flaeche : DGT_Linie;
			  			if (CreateDGeoObj (Type, $2) == False)
							return False;
					}						
				}
			   	DELETE_VEC ($2);					
			}		
		;

LWPolyLineKopf:
			LWPOLY_LINE LAYER_NAME VERTEX_COUNT 
			{	// LWPolyLine
			  	if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if (!CreateDGeoObj(DGT_Linie, $2, $3))
						return False;			  	
				}
			  	DELETE_VEC ($2);					
			}
		|	LWPOLY_LINE LAYER_NAME VERTEX_COUNT FLAG0
			{	// LWPolyLine
			  	if (OptParams.BildMasseOk && g_pLB -> IsValid ($2))
				{
					if ($4 & iVielFlaechenNetz)
					{
					//	wird hier nicht behandelt
					//	ggf. Fehlermeldung ausgeben
						if (!bOutputNetzError)
						{
							bOutputNetzError = True;
							yyerror (IDS_CAN_NOT_IMP_NETZ);
						}
					}
					else {
			  		DGeoTyp Type = ($4 & iPolylineClosed) ? DGT_Flaeche : DGT_Linie;
			  		
						if (!CreateDGeoObj (Type, $2, $3))
							return False;
					}						
				}
			   	DELETE_VEC ($2);					
			}
		;

Vertices:	Vertex
		|	Vertices Vertex
			;

Vertex:		VertexKopf VertexParams
			{//	Stützpunkt-Parameter auswerten und ausgeben
			 // Stützpunkt: mit optionaler folgender Ausbuchtung (wenn != 0)
			 // wenn Flag <= 8, dann Anpassungspunkt u. weglassen
				if (ValidFlag (Params.params_integer) && OptParams.BildMasseOk && l_pDGO)
				{
					if (! l_pDGO -> AddBogen (Params.params_tripel.real1, Params.params_tripel.real2, 
											  Params.params_real1))
						return False;
				}
			}
		;

VertexKopf: VERTEX
			{//	Stützpunkt-Parameter rücksetzen
				InitParams ();
			}
		|	VERTEX LAYER_NAME
			{//	Stützpunkt-Parameter rücksetzen
				InitParams ();
				DELETE_VEC ($2);						
			}
		;	

VertexParams: 
			VertexParam
		|	VertexParams VertexParam
		;

VertexParam:  
			Tripel
			{//	Stützpunkt-Koordinaten speichern
				Params.params_tripel.real1 = $1.real1;
				Params.params_tripel.real2 = $1.real2;
				Params.params_tripel.real3 = $1.real3;
			}
		|	FLOAT2
			{//	opt. Ausbuchtung des Stützpunktes
				Params.params_real1 = $1;
			}
		|	FLAG0
			{//	Stützpunkt ist Anpassungspunkt
				Params.params_integer = $1;
			}
		;

LWVertices:	CoordPair
			{//	Stützpunkt-Parameter auswerten und ausgeben
				if (OptParams.BildMasseOk && l_pDGO)
				{
					if (!l_pDGO -> AddBogen ($1.real1, $1.real2))
						return False;
				}
			}
		|	LWVertices CoordPair
			{//	Stützpunkt-Parameter auswerten und ausgeben
				if (OptParams.BildMasseOk && l_pDGO)
				{
					if (!l_pDGO -> AddBogen ($2.real1, $2.real2))
						return False;
				}
			}
		;
						
%%
Bool CreateDGeoObj (DGeoTyp DGT, char *pLayerName, long lExpectedVertices)
{
	if (!pLayerName)
	{
		yyerror (IDS_SYSERROR);
		return False;				
	}
	l_pDGO = new DGeoObj;
	if (l_pDGO && l_pDGO -> Init (DGT, pLayerName, lExpectedVertices))
		return True;
	else
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
}

//	Text-Objekt erzeugen
Bool CreateTextObject (char *pLayerName, long lExpectedVertices)
{
//	prüfe Parameter
	if (!pLayerName || !*pLayerName)
		return False;

//	neues Objekt erzeugen
	l_pTextObject = new CTextObject;
	if (l_pTextObject && l_pTextObject->Init (DGT_Text, pLayerName, lExpectedVertices))
		return True;
	else
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
}

//	Insertobjekt erzeugen (Symbol, long lExpectedVertices)
Bool CreateSymbolObject (char *pLayerName, char *pBlockName, long lExpectedVertices)
{
//	prüfe Parameter
	if (!pLayerName || !*pLayerName || !pBlockName || !*pBlockName)
		return False;

//	neues Objekt erzeugen
	l_pSymbolObject = new CSymbolObject;
	if (l_pSymbolObject && l_pSymbolObject->Init(DGT_Symbol, pLayerName, lExpectedVertices) &&
		l_pSymbolObject->SetBlockName (pBlockName))
		return True;
	else
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
}

//	lokale Ausgabe-Funktion
Bool Output (DGeoObj *& pObj)
{
//	prüfe Parameter
	assert (NULL != pObj);

	if (NULL == pObj)
		return False;

	Bool bRet = False;			//	noch nichts getan

	if (bInBlockSection)
	{
		assert (NULL != g_pBlockTree);
		bRet = g_pBlockTree -> AddObject (pObj);
		IncCounter ();

	//	altes DGeoObj wird hier nicht gelöscht
		pObj = NULL;
	}
	else
	{
		bRet = pObj -> Output () != 0;
		DELETE_OBJ (pObj);		/* Objekt wieder freigeben */		
	}

	return bRet;
}

//	Block einfügen ?? 
Bool InsertBlock (char *pBlockName)
{
	if (!pBlockName || !*pBlockName)
		return False;

	Bool bIsUserBlock = pBlockName [0] != '*';
	if (bIsUserBlock)		//	diese Blöcke werden immer importiert
		return True;

//	hier entscheidet die Nutzereinstellung
	return OptParams.m_bImpSystemBlocks;
}
	