/*
ARCY-Y
YACC-Spezifikation für die Arc/Info-TRIAS-Konvertierung.

Erarbeitet: J. Benkenstein              Stand vom 5.8. 1994
*/
%{

#include "pheader.h"

extern "C" {
	#include <limits.h>                 // DBL_MAX, LONG_MAX
//        #include <toolhelp.h>               // TIMERINFO
}

#include <filebuff.hxx>					// CFileBuffer

#include "tools.hxx"                    // TextObject
#define NOOPTPARAM
#include "optparam.hxx"                 // Params
#include "filepos.hxx"                  // PointEntries
#include "merkmal.hxx"                  // MerkmalsBaum
#include "rechstat.hxx"                 // RechercheStatus
#include "textconn.hxx"					// CDataInfoList

#pragma warning (disable: 4101 4102 )

//  Konstanten
const short SinglePrecL = 4;          	// Längen der Datentypen
const short DoublePrecL = 8;			// (inten)
const short SinglePrecLen = 14;			// Länge einer Real-Zahl bei Single/ 
const short DoublePrecLen = 24;			// Double-Precision (Ausgabe)
const short IntegerShortL = 2;			// short Integer-Zahl (intern)
const short IntegerDoubleL = 4;			// double Integer-Zahl
const short IntegerShortLen = 6;		// Länge der short Integer Zahl	
const short IntegerDoubleLen = 11;		// Länge der double Integer Zahl (Ausgabe)	
const short DateMLength = 8;

//  externe Variablen
extern FILE *yyin;                      // Eingabe-Datei
extern MerkmalsBaum *pMDT;              // Merkmalsbaum
extern PointEntries *pPE;               // Punkte-Tabelle
extern LineEntries *pLE;                // Linien-Tabelle
extern PalEntries *pPlE;                // Pal-Tabelle
extern long SecPos;                     // Datei-Position der 1. Arc-Koordinate
extern Params *pParams;                 // Parameterfeld
extern RechercheStatus *pRechStat;      // RechercheStatus
extern HWND __hWndM;
extern CTextDatInfoList *pTDI;			// OBDC-Info speichern

//  Prototypen
int yylex ();
Bool CreateTextObj (void);
Bool AddMerkmal (long AddFlag, long Laenge, pchar pMName = NULL, Bool UserIDFeld = False);
Bool ResetTables (void);
void OutKonvMess (DGeoTyp);

//  Variablen
short Result = True;
TextObject *pTO = NULL;                 // akt. GeoObjekt
long ActFieldCnt = LONG_MAX;            // akt. Feldanzahl
Bool PolyOut = True;                    // Ausgabe-Flags (alles ausgegeben)
Bool PointOut = True;
Bool LineOut = True;
Bool TellArcs = False;                  // Arc-Positionen nicht speichern
Bool bReadText = False;					// Lese-Text-Flag
%}
  
%union {
	struct {
		double real1;
		double real2;
		char *p_real_str;
	} real_struct;
	struct {
		long int1;
		long int2;
		long int3;
		char *str_ptr1;
	} int_struct;
	long integer;
	char *str_ptr;
	double real;                            
}

/* terminal symbols */
%token <real>			REAL
%token <integer>        INT 
%token <str_ptr>        TEXTVAL
%token <str_ptr>        USER_ID_FIELD
%token <str_ptr>        QSTRING  
%token <int_struct>		USER_FIELD_PARAMS
%token <int_struct>		PAT_FILE_NAME
%token <int_struct>  	AAT_FILE_NAME
%token <int_struct>		TIC_FILE_NAME
%token <int_struct>		BND_FILE_NAME
%token <int_struct>		OTHER_FILE_NAME

%token COVER_BEGIN COVER_ENDE IFO_BEGIN IFO_ENDE ARC CNT TXT PAL LAB TOL
%token ID_FIELD LENGTH FIRST_NODE LAST_NODE LEFT_POLY RIGHT_POLY
%token XMIN YMIN XMAX YMAX ID_TIC XTIC YTIC AREA PERIMETER 
%token EOL COMMAND PATH COMMAND_ENDE SIN_BEGIN SIN_ENDE
%token LOG_BEGIN LOG_ENDE TX_BEGIN LX_ERROR

%type <real_struct>      Punkt
%type <int_struct>       FieldDescription

%start Arc_File

%%
Arc_File:   COVER_BEGIN Sections COVER_ENDE
			{
				return True;
			}
			|
			COVER_BEGIN TEXTVAL Sections COVER_ENDE
			{
				return True;
			}
			;

Sections:     Section
			| Sections Section
			;

Section:      ArcSection
			| CentroidSection 
			| LabelSection
			| TextSection
			| PalSection
			| TolSection                                                            
			| InfoSection
			| SinSection
			| LogSection
			| TxSection
			| Error   
			;

Error:    	error
			{	         
				char Buffer [80] = "";
				wsprintf (Buffer, "Fehler in Zeile %ld !", pParams -> LineNr);
				MessBox MB ("Syntax-Fehler", Buffer, pRechStat);
				MB.SetType (OkayButton | ExclamationIcon);
				MB.Show ();
			  	// DEX_Error (RC_ArcTriasYacc, WC_UNKOWNTOKEN); 
				yyclearin; 
			}
			;

TxSection:	  TX_BEGIN EOL
			  {
				bReadText = False;        
				OutKonvMess (DGT_Unknown);
		      }
			| TX_BEGIN TxTexte EOL 
			  {
				bReadText = False;        
				OutKonvMess (DGT_Unknown);
			  }
			;
                                  
TxTexte:	  TxText
			| TxTexte TxText
			;
			
TxText:		  Punkt QSTRING
			  {
			  	if (pParams -> ImpTexte && lstrlen ($2) > 0)
				{                                        
					if (! CreateTextObj ())
						return False;
					pTO -> AddKoord ($1.real1, $1.real2);
					pTO -> AddText ($2); 
					pTO -> Output ();
                                        DELETE_OBJ (pTO);  /* Objekt wieder freigeben */
				}
			  }
			;
			
SinSection:   SIN_BEGIN SIN_ENDE
			;

LogSection:   LOG_BEGIN Commands LOG_ENDE
			;

Commands:     Command
			| Commands Command
			;

Command:      INT
			| COMMAND
			| PATH
			| COMMAND_ENDE
			;

ArcSection:   ARC EndeZeile
			| ARC Arcs EndeZeile
			{
				LineOut = False;
			}
			;

Arcs:         Arc
			| Arcs Arc
			;

Arc:          INT INT INT INT INT INT INT
			{   
				if (pParams -> ImpFlaechen || pParams -> ImpLinien)
				{
					if (!pLE) 
					{
						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
						return False;
					}
					if (! pLE -> AddNrCnt ($1, $7)) // Nummer und Anz. Punkte sp.
						return False;

					TellArcs = True;
				}                                       
			} ArcPunkte
			;

ArcPunkte:  Punkt
			{   
				if (pParams -> ImpFlaechen || pParams -> ImpLinien)
				{
					if (!pLE) 
					{
						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
						return False;
					}
					if (! pLE -> AddPos (SecPos))    // Datei-Position speichern
						return False;
					TellArcs = False;
				}                                       
			}
			| ArcPunkte Punkt
			;

Punkt:          REAL REAL
			{
				$$.real1 = $1;
				$$.real2 = $2;
			}
			;

EndeZeile:  EOL
			;

CentroidSection:
			  CNT EndeZeile
			| CNT CntPunkte EndeZeile
			;

CntPunkte:    CntPunkt
			| CntPunkte CntPunkt
			;

CntPunkt:     INT
			| INT Punkt
			;

LabelSection: LAB LabelEnde
			| LAB LabelPunkte LabelEnde
			{
				PointOut = False;
			}
			;

LabelEnde:    INT INT REAL REAL
			;

LabelPunkte:  LabelPunkt
			| LabelPunkte LabelPunkt
			;

LabelPunkt:   INT INT Punkt Punkt Punkt
			{
				if (pParams -> ImpPunkte) { 
					if (!pPE) {
						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
						return False;
					}
					if (! pPE -> AddEntry ($3.real1, $3.real2))
						return False;
				}
			}
			;

PalSection:   PAL EndeZeile
			| PAL PalEntries EndeZeile
			{              
				pParams -> PalExist = True;
				PolyOut = False;
			}
			;

PalEntries:   PalEntry
			| PalEntries PalEntry
			;

PalEntry:     INT Punkt Punkt
			{
				if (pParams -> ImpFlaechen)
				{
					if (! pPlE) {
						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
						return False;
					}
					if (! pPlE -> AddPalVektor ($1))        // Pal-Größe
						return False;
				}                                               
			}
			| INT INT INT
			{   
				if (pParams -> ImpFlaechen)
				{
					if (! pPlE) {
						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
						return False;
					}
					if (! pPlE -> AddPalEntry ($1))   // ArcID
						return False;
				}                                               
			}
			;

TolSection:   TOL EndeZeile
			| TOL TolEntries EndeZeile
			;

TolEntries:   TolEntry
			| TolEntries TolEntry
			;

TolEntry:     INT INT REAL
			;

TextSection:  TXT EndeZeile            
			  {
			  		bReadText = False;
			  		OutKonvMess (DGT_Unknown);
			  }
			| TXT Texte EndeZeile
			  {
			  		bReadText = False;        
			  		OutKonvMess (DGT_Unknown);
			  }	
			;

Texte:        Text
			| Texte Text
			;
			
Text: 		INT INT INT INT INT Punkt Punkt Punkt Punkt Punkt Punkt Punkt REAL TEXTVAL
			{   
				if (pParams -> ImpTexte && lstrlen ($14) > 0)
				{
					if (! CreateTextObj ())
						return False;
					pTO -> AddKoord ($6.real1, $8.real1);
					pTO -> AddText ($14); 
					pTO -> Output ();
                                        DELETE_OBJ (pTO);  /* Objekt wieder freigeben */
				}                                       
			}
			;                  

InfoSection:  IFO_BEGIN IFO_ENDE
			{
				if (!ResetTables ())
					return False;
			}
			| IFO_BEGIN I_Sections IFO_ENDE
			{
				if (!ResetTables ())
					return False;
			}
			;

I_Sections:   I_Section
			| I_Sections I_Section
			;

I_Section:	  BndSection
			| TicSection
			| SectionWithInfo Fields
			;       	
			     
SectionWithInfo:           
			  PAT_FILE_NAME 
			  {     
			  	if (!pMDT)
			  	{
					DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
					return False;
				}
				if (!(pMDT -> Reset () && pMDT -> ReadMerkmale ()))
					return False;			  	                 
				if (pMDT -> Cnt () = $1.int1)
				{
					ActFieldCnt = $1.int2;			  	
					pMDT -> _TableType = PatTable;
				}					
			  }
			| AAT_FILE_NAME
			  { 
			  	if (!pMDT)
			  	{
					DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
					return False;
				}
				if (!(pMDT -> Reset () && pMDT -> ReadMerkmale ()))
					return False;			  	                 
				if (pMDT -> Cnt () = $1.int1)
				{
					ActFieldCnt = $1.int2;			  	
					pMDT -> _TableType = AatTable;
				}					
			  } 
			| OTHER_FILE_NAME
			  {
				if (!pMDT || !pTDI)
			  	{
					DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
					return False;
				}
				if (!pMDT -> Reset ())
					return False;			  	                 
				if (pMDT -> Cnt () = $1.int1)
				{
					ActFieldCnt = $1.int2;			  				  
					pMDT -> _TableType = OtherTable;
				
			 	// Tabellen-Name ggf. speichern								
					if (pParams -> ImpTabellen)
					{     
						if (! pMDT -> StoreTableName ($1.str_ptr1) || 
							! pTDI -> SetMaster ($1.str_ptr1))
							return False;
					}
				}					
			  } 
			;                                           
			
FieldDescription:
			  INT INT INT INT INT INT INT INT INT INT INT INT
			{
				$$.int3 = $12;				// hat Feld Infos ?
				switch ((short) $7) {
					case 40:                        		// Float
					case 60:
					{       
						switch ($1)
						{
							case DoublePrecL:
								$$.int1 = DoublePrecLen;			// bei double Precision                                         
							break;
							case SinglePrecL:
							default: 
								$$.int1 = SinglePrecLen;			// Standard-Ausgabe-Länge	
							break;
						}							
					}                                                                 
					break;
					case 50:                        		// Integer
					{
						switch ($1)
						{
							case (IntegerShortL):
								$$.int1 = IntegerShortLen;
							break; 
							case (IntegerDoubleL):
							default:
								$$.int1 = IntegerDoubleLen;			// Standard-Ausgabe-Länge	
							break;
						}							
					}
					break;
					case 20:                        		// String
					case 30:
						$$.int1 = $1;
					break;
					case 10:                        		// Datum
						$$.int1 = DateMLength;
					break;
					default: {
						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
						return False;
					}
				}
			}
			;

Fields:       Field
			| Fields Field
			;

Field:        FIRST_NODE FieldDescription
			{       
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| LAST_NODE FieldDescription
			{    
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| LEFT_POLY FieldDescription
			{                    
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| RIGHT_POLY FieldDescription
			{                    
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| LENGTH FieldDescription
			{                    
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| AREA FieldDescription
			{   
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| PERIMETER FieldDescription
			{                    
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| ID_FIELD FieldDescription
			{                    
				if (! AddMerkmal ($2.int3, $2.int1))
					return False;
			}
			| USER_ID_FIELD FieldDescription
			{                    
				if (! AddMerkmal ($2.int3, $2.int1, pParams -> UserID ? $1 : NULL, True))
					return False;
			}
			| USER_FIELD_PARAMS
			{   
				short Len = 0;
				switch ((short) $1.int2) 
				{
					case 40:                        	// Float
					case 60:
					{       
						switch ($1.int1)
						{
							case DoublePrecL:
								Len = DoublePrecLen;			// bei double Precision                                         
							break;
							case SinglePrecL:
							default: 
								Len = SinglePrecLen;			// Standard-Ausgabe-Länge	
							break;
						}							
					}                                                                 
					break;
					case 50:                        // Integer
					{
						switch ($1.int1)
						{
							case (IntegerShortL):
								Len = IntegerShortLen;
							break; 
							case (IntegerDoubleL):
							default:
								Len = IntegerDoubleLen;			// Standard-Ausgabe-Länge	
							break;
						}							
					}
					break;
					case 20:                        // String
					case 30:
						Len = (short) $1.int1;
					break;
					case 10:                        // Datum
						Len = DateMLength;
					break;
					default: {
						DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
						return False;
					}
				}
			
				if (! AddMerkmal ($1.int3, Len, $1.str_ptr1))
					return False;
			}
			;

BndSection:   BndHeader BndFields Punkt Punkt
			;

BndHeader:    BND_FILE_NAME
			;

BndFields:    BndField
			| BndFields BndField
			;

BndField:     XMIN FieldDescription
			| YMIN FieldDescription
			| XMAX FieldDescription
			| YMAX FieldDescription
			;

TicSection:   TicHeader TicFields Tics
			;

TicHeader:    TIC_FILE_NAME
			;

TicFields:    TicField
			| TicFields TicField
			;

TicField:     ID_TIC FieldDescription
			| XTIC FieldDescription
			| YTIC FieldDescription
			;

Tics:         Tic
			| Tics Tic
			;

Tic:          INT Punkt
			;
%%

Bool CreateTextObj (void)
{
	pTO = new TextObject;
	if (!pTO) {
		DEX_Error (RC_ArcTriasYacc, EC_NOMEMORY);
		return False;
	}
	return True;
}

//  "überwacht" Lesen der MerkmalsFelder
Bool AddMerkmal (long AddFlag, long La, pchar pMName, Bool StoreUserIdField) {
//  Merkmals-Beschreibung nur aufnehmen, wenn Sätze folgen
	if (pMDT -> Cnt () == 0)
		return True;
	if (AddFlag > 0)
	{
		if (!pMDT -> AddMerkmal ((short) La, pMName, StoreUserIdField))
			return False;
	}

//  Test: letztes Feld ?
	if (--ActFieldCnt != 0L)
		return True;

	ActFieldCnt = LONG_MAX;                         // auf ungültigen Wert setzen
	
//  Merkmale einschließlich Geometrie ausgeben
	Entries *pE = NULL;
	Bool Output = False;							// Daten explizit nicht ausgeben
	Bool CheckUniPoly = False;						// Universe-Polygon
	DGeoTyp DGT = DGT_Unknown;
	
	switch (pMDT -> _TableType)
	{
		case PatTable:
		{
			if (pParams -> PalExist)				// Polygontopologie liegt vor
			{   
				pParams -> PalExist = False;		// Topologie wird nach Abarbeitung ungültig
				CheckUniPoly = True;				// 1. Merkmalszeile überlesen           
				PolyOut = True;                  	// Flächen werden jetzt behandelt
				if (pParams -> ImpFlaechen)
				{
					Output = True;					// Flächen importieren
					DGT = DGT_Flaeche;
					
				// 	Konvertierung vorbereiten
					pLE -> Optimize ();				// Linientabelle
					pE = (Entries *) pPlE;   		// Paltabelle
					pE -> Optimize ();										            					
					
				//	Ausgabe-Flags für weitere Abarbeitung setzen
					PointOut = True;				 // Punkte werden ignoriert										
                                        DELETE_OBJ (pPE);                    // PunktListe wird nicht mehr benötigt
				}
			}
			else    								 // Punkte sind im Cover vorhanden
			{
				pE = (Entries *) pPE;
				if (pE -> Count () < (ulong) pMDT -> Cnt ())
					CheckUniPoly = True;				 // 1. Merkmalszeile überlesen           
				else
					CheckUniPoly = False;				 // 1. Merkmalszeile verarbeiten           
				PointOut = True;					 // Punkte werden jetzt behandelt
				if (pParams -> ImpPunkte)
				{
					pE -> Optimize ();
					DGT = DGT_Punkt;                               
					Output = True;
				}                               
            }
		}
		break;  
		case AatTable:								// Linien-Tabelle
		{
			LineOut = True;                         // Linien werden jetzt behandelt
			pE = (Entries *) pLE;
			if (pParams -> ImpLinien)
			{
				pE -> Optimize ();
				DGT = DGT_Linie;                                                                        
				Output = True;					
			}	
		}
		break;
		case OtherTable:							// andere Tabelle als Textdatei
		{
			if (pParams -> ImpTabellen)
			{
				pParams -> TableCnt++;				// Zähler erhöhen
				DGT = DGT_OtherTable;                                                   
				Output = True;					
			}				
		}
		break;
		default:									// sollte nicht passieren
		{
			DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
			return False;
		}
	}
	
	OutKonvMess (DGT);      						// Text an Nutzer ausgeben
	return pMDT -> OutMerkmale (pE, CheckUniPoly, Output);
}

//  Tabellen ggf. ausgeben
Bool ResetTables (void) {
	Bool Ret = True;
	if (pParams -> PalExist && pParams -> ImpFlaechen && !PolyOut)  // es gibt Flächen
	{                                                               // die noch auszugegeben sind
		pParams -> PalExist = False;
		PolyOut = PointOut = True;
		if (!pPlE) 
		{
			DEX_Error (RC_ArcTriasYacc, EC_SYSERROR);
			Ret = False;
		} 
		else 
		{
			pLE -> Optimize ();
			pPlE -> Optimize ();
			Ret = pPlE -> OutAllGeo ();                             // alle Flächen ausgeben
		}                                                           
	}   
			
	if (Ret && !LineOut && pParams -> ImpLinien)                    // Linien sind noch nicht ausg.
	{
		LineOut = False;
		if (pLE) 
		{
			pLE -> Optimize ();
			Ret = pLE -> OutAllGeo ();                              // alle Linien ausgeben
		}
	}
			
	if (Ret && !PointOut && pParams -> ImpPunkte)                   // es gibt noch Punkte
	{
		PointOut = False;                                           // die noch auszugeben sind
		if (pPE) 
		{
			pPE -> Optimize ();
			Ret = pPE -> OutAllGeo ();                              // alle Punkte ausgeben
		}
	}

        DELETE_OBJ (pPE);                                           // Punkte-Tabelle löschen
        DELETE_OBJ (pLE);                                           // Linien-Tabelle löschen
        DELETE_OBJ (pPlE);                                          // Pal-Table löschen

	return Ret;
}

