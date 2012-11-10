// ImportInterface-Implementation für den Import von DXF-Daten -----------
// File: DXFIMPIF.CPP

#include "pheader.hpp"

#include <float.h>						// DBL_MAX
#include <xtensnn.h>					// DEX_ReReadIdents ()

#include "lextypes.h"					// lex-spezifische Typ-Definitionen
#include "header.hpp"					// Header
#include "rechstat.hpp"					// RechercheStatus
#include "impreslt.hpp"					// ImportResult
#include "merkmal.hpp"					// MerkmalsBaum
#include "numedit.hpp"					// Numedit
#include "realedit.hpp"          		// RealEdit
#include "helptext.hpp"					// CHelpText
#include "layers.hpp"					// CLayerBaum
#include "block.hpp"					// CBlockTree

#include "optprdlg.hpp"					// OptParamsDlg

// Konstanten
const short OutLineCnt = 40;        	// alle 40 Zeilen BS-Ausgabe

// globale Variablen
double XMin = DBL_MAX;		 			// Bildmaße
double YMin = DBL_MAX;			//EXTMIN/EXTMAX
double XMax = DBL_MIN;
double YMax = DBL_MIN;

// KK000125 - LIMMIN/LIMMAX
double XLMin = DBL_MAX;		 // Bildmaße
double YLMin = DBL_MAX;		//LIMMIN/LIMMAX
double XLMax = DBL_MIN;
double YLMax = DBL_MIN;
//


Params OptParams;						// globales Parameter-Halter-Objekt
RechercheStatus *pRechStat = NULL;		// Fenster auf Recherche-Status
MerkmalsBaum *g_pMB = NULL;				// Merkmals-Beschreibungs-Baum
CLayerBaum *g_pLB = NULL;				// enthält gültige Layernamen

// externe Variablen
extern long lLineNr;
extern TableInfo* pActTable;
extern TableInfo FileTable [];
extern FILE *yyin;

// Prototypen
void yyerror (short sResorceID);
void yyinit_lex (void);
int yyparse (void);
#ifdef WIN32
char *AnsiStringNew (LPCWSTR);	
#endif
void IncCounter (long ObjNr = 0);	// Zeilenzähler erhöhen

// KK991214
#define BACKSLASH	'\\'
static void protocol_open (char *pFile);
static void make_file (char *pNew, char *old, char *ext);


FILE *fpProt = NULL;		// Protokolldatei


Bool GetDebugOutputFlag (void); 	// DebugSection-Eintrag aus win.ini lesen
// KK000531
Bool File_Proof (char *pFile);
                

//-----------------------------------------------------------------------------
// Konstruktor/Destruktor -----------------------------------------------------
CImportAutoCadDxf :: CImportAutoCadDxf (LPUNKNOWN pUnk)
		 		   : CImportGeoData (pUnk)
{
	m_hWnd = NULL;	
}

CImportAutoCadDxf :: ~CImportAutoCadDxf (void)
{
	// nothing else to do
}

// *** IImportGeoData methods -------------------------------------------------
// Abfrage der Eigenschaften und Möglichkkeiten des ImportModuls (siehe Flags
// in File IXTENSN.HXX IMPORTCAPS_...
STDMETHODIMP_(DWORD) CImportAutoCadDxf :: Capabilities (void)
{
//	KK991007
	OptParams.Reset();
	OptParams.m_bOffset = False;	//	Anzeige Offset Import/Datenquelle

	return IMPORTCAPS_CANIMPORTGEOMETRY | 
           IMPORTCAPS_CANIMPORTFEATURES | /* IMPORTCAPS_OPTIMPORTFEATURES |	*/
		   IMPORTCAPS_SHOULDCONFIG | 		// Optionale Parameter
		   IMPORTCAPS_MULTIPLEFILES |
	       /*IMPORTCAPS_CANIMPORTANSIOEM  | */IMPORTCAPS_OPTIMPORTANSIOEM;
           ;
}                 

STDMETHODIMP CImportAutoCadDxf :: GetConfigInfo (IEnumString **ppEnumCfg, DWORD dwReserved)
{
	return ResultFromScode (E_NOTIMPL);
}

// Diese Funktion wird nur dann gerufen, wenn 'Capabilities' das Flag
// IMPORTCAPS_SHOULDCONFIGURE geliefert hat. Im dieser Funktion sollte die
// Konfiguration des Modules für den nächsten Import durchgeführt werden.
STDMETHODIMP CImportAutoCadDxf :: Configure (HWND hWnd)
{
	m_hWnd = hWnd;
//	KK991007
	OptParams.Reset();
	OptParams.m_bOffset = False;	//	Anzeige Offset Import/Datenquelle

//	Parameter-Dialog
	OptParamsDlg OP (g_pTE -> MWind (), & g_pTE -> RF (), &OptParams);
	if (OP.OpFlag ())
		OP.Show ();

	return OP.OpFlag () ? ResultFromScode (S_OK) : ResultFromScode (S_FALSE);
}

// Das ist die eigentliche ImportFunktion, die einmal gerufen wird und dann alles
// machen muß, was sie für richtig hält. 
// Der Enumerator pEnumFiles liefert die Dateinamen der zu importierenden Datei(en)
// (ACHTUNG: UNICODE!!! und OLE-TaskAllocator)
STDMETHODIMP CImportAutoCadDxf :: ImportData (IEnumString *pEnumFiles, DWORD dwFlags)
{
	LPWSTR pFile = NULL;
	ULONG ulGot = 0;
	HRESULT hr = ResultFromScode (E_FAIL);
	
//	Parent-Fenster deakt.
	// g_pTE -> MWind () -> Disable ();

	OptParams.bAnsiiText = dwFlags & TOIMPORT_ANSIOEM ? True : False;
	OptParams.bImpMerkmale = dwFlags & TOIMPORT_FEATURES ? True : False;
	OptParams.bDebugOutput = GetDebugOutputFlag ();

//	Merkmals-Beschreibungs-Baum
	MerkmalsBaum MB;			
	if (MB.Init () == False)	// alle Merkmals-Beschreibungen lesen
		return hr;
	g_pMB = &MB;				// Zeiger speichern

//	Ebenenbaum erzeugen
	CLayerBaum LB;
	if (LB.Init (&g_pTE -> RF (), OptParams.m_pEbenen) == False)
		return hr;
	g_pLB = &LB;

	DWORD dwStartTime = GetTickCount ();            // Übersetzungzeit merken
//  Status-Fenster erzeugen
	{
		RechercheStatus RS (g_pTE -> MWind (), &g_pTE -> RF ());
		pRechStat = &RS;
		BOOL bFirst = TRUE;
	
		while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot)) 
		{// alle Dateien nacheinander abarbeiten
			yyin = NULL;
#ifdef WIN32
			hr = ImportDXF (AnsiStringNew (pFile), bFirst);
#else
			hr = ImportDXF (pFile, bFirst);
#endif        
			bFirst = False;

			if (yyin)
				fclose (yyin);
			CoTaskMemFree (pFile);
			if (FAILED(hr))	
				break;
		}

		DEXN_ReReadIdents ();
		DEXN_ReReadContainer ();

		IStorage *pISt = NULL;
		if (DEX_GetProjectStorage (pISt))
			pISt -> Release ();
		else
			DEX_FlushModifications();

	//  Ergebnis der Recherche ausgeben
		// RS.Hide ();
	}

	MessageBeep (MB_OK);
	ImportResult IR (g_pTE -> MWind (), & g_pTE -> RF (), GetTickCount () - dwStartTime);
	IR.Show ();
	
	// g_pTE -> MWind () -> Enable ();

	// DEX_PostRebuildSight();		// Sicht neu lesen
	return hr;
}

STDMETHODIMP CImportAutoCadDxf::put_CS(IUnknown *pICS)
{
	m_CS = pICS;
	return S_OK;
}

STDMETHODIMP CImportAutoCadDxf :: ImportDXF (char *pFile, BOOL bFirst)
{
	if (!pFile || !*pFile)
		return ResultFromScode (S_FALSE);
	
	HRESULT hr = NOERROR;

	protocol_open (pFile);

// KK000531
	if (!File_Proof(pFile)) {
		if (fpProt) {
			ResString strText (ResID (IDS_NOENDEKENNZEICHEN, &g_pTE -> RF ()), 80);
			ResString strCaption (ResID (IDS_PARSERERRORCAP, & g_pTE -> RF ()), 20);

			fprintf (fpProt,strText.Addr() );

			MessBox MB (strCaption.Addr (), strText.Addr(), g_pTE -> MWind ());
			MB.SetType (OkayButton | ExclamationIcon);
			MB.Show ();

		}
		return ResultFromScode (S_FALSE);
	}

	yyin = fopen (pFile, "r");
	if (yyin == NULL)
		return ResultFromScode (STG_E_PATHNOTFOUND);


//	Parameter einstellen
	lLineNr = 0;						// Zeilenzähler rücksetzen
	pActTable = &FileTable [0];			// File-Tabelle einstellen
	XMax = YMax = 0;					// Bildmaße init.
	XMin = YMin = DBL_MAX;
//	OptParams.Reset ();								// opt. Parameter-Klasse erzeugen
	if (! OptParams.SetFileParams (pFile))			// Dateinamen speichern	(8 Zeichen max.)
		return ResultFromScode (S_FALSE);			// max. Zeilenzahl setzen	

//  ggf. Header komplettieren
	Header HD;
	if (bFirst)
	{
		if (! HD.GetUniqueIdent (OptParams.UnIdMKode))  	// unique Ident MK lesen
			return ResultFromScode (S_FALSE);
		if (! HD.GetTextObjMKode (OptParams.TextMKode))  	// TextObjMKode lesen
			return ResultFromScode (S_FALSE);

		if (OptParams.m_bImpTextDrehWi)
		{
			if (! HD.GetTextObjWinkel (OptParams.m_ulTextWinkel))  	// TextObjWinkelMCode lesen
				return S_FALSE;
		}
		if (OptParams.m_bImpTextHoehe)
		{
			if (! HD.GetTextObjHoehe (OptParams.m_ulTextHoehe))  	// TextObjHoeheMCode lesen
				return S_FALSE;
		}
		if (OptParams.m_bImpSymDrehWi)
		{
			if (! HD.GetSymObjWinkel (OptParams.m_ulSymWinkel))  	// SymbolObjWinkelMCode lesen
				return S_FALSE;
		}
		if (OptParams.m_bImpComment)
		{
			if (! HD.GetComment (OptParams.m_ulComment))  			// CommentMCode lesen
				return S_FALSE;
		}

		if (!HD.SetTextFlag())										// PosTxtAtBaseLine
			return S_FALSE;

		DEXN_ReReadHeader ();										// Trias soll Header neu lesen		
		OptParams.BildMasseOk = HD.MatrixExists ();
	}	

	ResString strImpText (ResID (OptParams.BildMasseOk ? IDS_IMPORTTEXT : IDS_CHECKTEXT, 
						  &g_pTE -> RF ()), 80);

//  Status-Fenster akt. 
	pRechStat -> SetParams (OptParams.MaxLineNr, OptParams.pFileName, (char *) strImpText.Addr (),
							&g_pTE -> RF ());
	pRechStat -> Show ();

//	Blockmanager anlegen
	CBlockTree BlockTree;
	
//  prüfe starten
	int Op = 1;		// alles Ok
	yyinit_lex ();
	Op = yyparse ();

	if ( Op == 0) {
		yyerror (IDS_NOWORKING);
	}

	if (bFirst && (Op == -1))		// bisher nur geparst ?
	{	
	//	ermittelte Bildmaße OK ?
		if (HD.OutScaleAndOffset ())
		{
			DEXN_ReReadHeader ();				// Trias soll Header neu lesen		
			OptParams.BildMasseOk = True;		// Flag für Übersetzung

		//	RechercheStatus akt.: Text und Balken
			ResString strImpText (ResID (IDS_IMPORTTEXT, &g_pTE -> RF ()), 80);
			pRechStat -> _ActionText.SetText ((char *)strImpText.Addr ());
			OptParams.MaxLineNr = lLineNr;		// max. Anzahl ist jetzt bekannt
			lLineNr = 0;			// aktueller Zeilenzähler
			pRechStat -> SetValue (0L);		// Balken stellen
			fseek (yyin, 0, SEEK_SET);	// Datei-Zeiger an den Anfang
			yyinit_lex ();
			Op = yyparse ();	// jetzt importieren der Objekte						
		}								
	}                                                         

// evtl. Protokolldatei schließen
	if (fpProt) {
		fclose (fpProt);
		fpProt = NULL;
	}


	hr = (Op >= 0) ? ResultFromScode (S_OK) : ResultFromScode (S_FALSE);
	return hr;
}

//-----------------------------------------------------------------------------
// Protokolldatei eröffnen ----------------------------------------------------
static void protocol_open (char *pFile) 
{
char cbProtocol[_MAX_PATH];

	make_file (cbProtocol, pFile, ".lsx");

	if (fpProt)
		fclose (fpProt);		// evtl. vorherige Datei schließen

	fpProt = fopen (cbProtocol, "w");
	if (fpProt)
		setvbuf (fpProt, NULL, _IONBF, 0);	// Buffering ausschalten
}


// Neue Extension anhängen ----------------------------------------------------
static void make_file (char *pNew, char *old, char *ext) 
{
char *cptr;

	strcpy (pNew, old);
	for (cptr = &pNew[strlen(pNew) -1]; cptr >= pNew; --cptr) {
		if (*cptr == '.') {
			strcpy (cptr, ext);
			break;
		}
		if (*cptr == BACKSLASH || cptr == pNew) {
			strcat (pNew, ext);
			break;
		}
	}
}

// FehlerAusgabeRoutine -------------------------------------------------------
void yyerror (short sResourceID)
{
//	:: MessageBeep (MB_OK);	
	char Buffer [_MAX_PATH] = "";
	ResString strCaption (ResID (IDS_PARSERERRORCAP, & g_pTE -> RF ()), 20);
	ResString strText (ResID (sResourceID, & g_pTE -> RF ()), 80);
	ResString strFormat (ResID (IDS_PARSERERROR, & g_pTE -> RF ()), 50);
	wsprintf (Buffer, strFormat, OptParams.pFileName, strText.Addr ());
	char lBuffer [20] = "";
	lstrcat (Buffer, ltoa (lLineNr, lBuffer, 10));
	lstrcat (Buffer, ".");

// KK991213
//	MessBox MB (strCaption.Addr (), Buffer, pRechStat ? pRechStat : g_pTE -> MWind ());
//	MB.SetType (OkayButton | ExclamationIcon);
//	MB.Show ();

	if (fpProt) fprintf (fpProt, Buffer);


}

// Konvertierung UNICODE --> ANSI ---------------------------------------------
#ifdef WIN32
inline char *__ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
	int badConversion = false;
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, 
			     		NULL, &badConversion);
	return buf;
}

char *AnsiStringNew (LPCWSTR strIn)
{
	static char buf[_MAX_PATH];
  	return (__ConvertStrWtoA (strIn, buf, _MAX_PATH));
}            
#endif

//  Import-Status akt.
void IncCounter (long ObjNr) 
{
	if (!pRechStat)
		return;
	if (ObjNr)                              // wenn Objekt-Nummer gegeben
		pRechStat -> SetValue (lLineNr, ObjNr);               
	else    
	{       
		if ((lLineNr % OutLineCnt) == 0)
			pRechStat -> SetValue (lLineNr);
	}                       
}

// DebugSection-Eintrag aus win.ini lesen                
Bool GetDebugOutputFlag (void)
{
	ResString Section (ResID (IDS_DEBUGSECTION, & g_pTE -> RF ()), 30);
	ResString Entry (ResID (IDS_DEBUGENTRY, & g_pTE -> RF ()), 30);   
	char Buffer [5] = "";
	
	return  GetProfileString (Section.Addr (), Entry.Addr (), "0", Buffer, sizeof (Buffer)) 
			&& (atoi (Buffer) > 0) ? True : False;
}

//----------------------------------------------------------------------------------
// Datei prüfen ----------------------------------------------------
Bool File_Proof (char *pFile)
{

	HFILE hf = _lopen (pFile,OF_READ);
	if ( HFILE_ERROR  == hf)
		return False;

	long lOffset = _llseek(hf,-16,FILE_END);

	if ( -1L == lOffset ) {
		_lclose(hf);
		return False;
	}

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer) {
		_lclose(hf);
		return False;
	}

	*pBuffer = '\0';

	UINT ii = _lread (hf,pBuffer,16);
	if ( HFILE_ERROR == ii) {
		_lclose(hf);
		return False;
	}

	_lclose(hf);

// EOF
	char *aptr = pBuffer;
	char *cptr = strrchr(pBuffer,'\0');
	cptr--;


	while ( cptr != aptr ) 
	{
		if ( *cptr >= 'A' && *cptr <= 'Z' )  {
			if ( 0 == strncmp(cptr,"EOF",3))
				return True;
		}

		cptr--;
	}

	DELETE_OBJ(pBuffer);


	return False;
}

//--------------------------------------------------------------------------------------