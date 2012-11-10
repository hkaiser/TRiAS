// ImportInterface-Implementation für den Import von AutoCAD-Daten -----------
// File: ARCIMPIF.CXX

#include "pheader.h"

extern "C" { 
	#include <io.h>				// _filelength ()	
	#include <fcntl.h>			// _OR...
	#include <xtensnn.h>		// DEX_ReReadIdents ()
	#include "arctrias.hr"      // ResourceKonstanten
}

// #include <errinstx.hxx>			// ErrInstall

#include <hpp/filebuff.hxx>         // CFileBuffer

#ifndef WIN32
#include <ole16.h>
#endif

#include "numedit.hxx"          // NumEdit
#include "realedit.hxx"         // RealEdit
#include "helptext.hxx"         // CHelpText
#include "optparam.hxx"         // Params, OptParams
#include "header.hxx"           // Header
#include "tools.hxx"            // CreateIdent/Merkmal
#include "rechstat.hxx"         // RechStatus
#include "impreslt.hxx"         // ImportResult
#include "filepos.hxx"          // weitere Bäume
#include "merkmal.hxx"          // MerkmalsBaum
#include "textconn.hxx"         // CTextDatInfoList
#include "arcimpif.hxx"			// zugeh. Header

// Konstanten
const short BildmasCount = 4;   // X/YMin, X/YMax
const char EoS [] = "        -1         0         0         0         0         0         0";
const char EoP [] = "        -1         0 0.0000000E+00 0.0000000E+00";
const char EoT [] = "-1.0000000E+02";
const char EoT2 [] = " 1.0000000E+00";
const short OutLineCnt = 10;        // alle 10 Zeilen BS-Ausgabe
const long AvrChrPerLine = 50;		// 50 Zeichen durchschn. pro Zeile

// globale Variablen
double Bildmasse [BildmasCount];    // speichert Bildmaße
RechercheStatus *pRechStat = NULL;	// Recherch-Status
Params *pParams = NULL;             // Klasse mit allen möglichen Parametern
MerkmalsBaum *pMDT = NULL;          // Merkmalstabelle
PointEntries *pPE = NULL;           // Geometrie der Punkte
LineEntries *pLE = NULL;            // Geometrie der Linien
PalEntries *pPlE = NULL;            // Pal-Tabelle
CTextDatInfoList *pTDI = NULL;      // OBDC-Info speichern
ResourceFile *pRF = NULL;

// externe Variablen
extern FILE *yyin;

// Prototypen
void IncCounter (long ObjNr = 0); 	// Import-Status akt.
void yyinit_lex (void);
int yyparse (void);					// Datei importieren

#ifdef WIN32
	char *AnsiStringNew (LPCWSTR);	
#else
	DWORD timeGetTime (void) { return GetTickCount (); }
#endif

// Konstruktor/Destruktor -----------------------------------------------------
CImportArcInfo :: CImportArcInfo (LPUNKNOWN pUnk)
		 		: CImportGeoData (pUnk)
{
	pParams = &OptParam;
    pRechStat = NULL;
    _pTempFile = NULL;
	_pCoverName = NULL;
// KK000328
	_pCompName = NULL;
	_pCompFile = NULL;

	m_bIsConfigured = FALSE;
	m_dwStartTime = 0;
	m_bMultipleFiles = FALSE;

    _Reset ();      // alle Werte rücksetzen
}

CImportArcInfo :: ~CImportArcInfo (void)
{
    DELETE_OBJ (pMDT);
}

// *** IImportGeoData methods -------------------------------------------------
// Abfrage der Eigenschaften und Möglichkkeiten des ImportModuls (siehe Flags
// in File IXTENSN.HXX IMPORTCAPS_...
STDMETHODIMP_(DWORD) CImportArcInfo :: Capabilities (void)
{
	return IMPORTCAPS_CANIMPORTGEOMETRY | 
		   IMPORTCAPS_CANIMPORTANSIOEM | IMPORTCAPS_OPTIMPORTANSIOEM |
           IMPORTCAPS_CANIMPORTFEATURES | IMPORTCAPS_MULTIPLEFILES |
		   IMPORTCAPS_SHOULDCONFIG;			// Optionale Parameter 
           ;
}           

STDMETHODIMP CImportArcInfo :: GetConfigInfo (IEnumString **ppEnumCfg, DWORD dwReserved)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CImportArcInfo::put_CS(IUnknown *pICS)
{
	m_CS = pICS;
	return S_OK;	
}

// Diese Funktion wird nur dann gerufen, wenn 'Capabilities' das Flag
// IMPORTCAPS_SHOULDCONFIGURE geliefert hat. Im dieser Funktion sollte die
// Konfiguration des Modules für den nächsten Import durchgeführt werden.
STDMETHODIMP CImportArcInfo :: Configure (HWND hWnd)
{
	m_bIsConfigured = FALSE;
	pParams -> sIdCode = DEX_GetIdBase ();
	pParams -> sMCode = DEX_GetMkBase ();

//	Parameter-Dialog
	Window Parent (hWnd);
	OptParams OP (&Parent, &g_pTE -> RF (), TRUE);
	if (!OP.OpFlag ())
		return ResultFromScode (S_FALSE);
	OP.Show ();
	if (! (OP.Result () && OP.OpFlag ()))
		return ResultFromScode (S_FALSE);

	m_bIsConfigured = OP.OpFlag ();

	return OP.OpFlag () ? ResultFromScode (S_OK) : ResultFromScode (S_FALSE);
//	return ResultFromScode (S_OK);	
}

// Das ist die eigentliche ImportFunktion, die einmal gerufen wird und dann alles
// machen muß, was sie für richtig hält. 
// Der Enumerator pEnumFiles liefert die Dateinamen der zu importierenden Datei(en)
// (ACHTUNG: UNICODE!!! und OLE-TaskAllocator)
STDMETHODIMP CImportArcInfo :: ImportData (IEnumString *pEnumFiles, DWORD dwFlags)
{
	// ErrInstall E1 (WC_BADCOORD);

	LPWSTR pFile = NULL;

	ULONG ulGot = 0;
	HRESULT hr = ResultFromScode (E_FAIL);

//	Parent-Fenster deakt.
	g_pTE -> MWind () -> Disable ();				   // Parent deakt.
	pRF = &g_pTE -> RF ();
	pParams -> DebugOutput = _GetDebugOutputFlag ();   // Flag für Trias aus win.ini lesen                             
	pParams -> bAnsiiText = dwFlags & TOIMPORT_ANSIOEM ? True : False;
	m_dwStartTime = timeGetTime ();

//	mehrere Dateien sel. ?
	int iFileCnt = 0;
	while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot))
	{
		iFileCnt++;
		CoTaskMemFree (pFile);
	}
	m_bMultipleFiles = iFileCnt > 1 ? TRUE : FALSE;

	pEnumFiles -> Reset ();
	pParams -> ResetCounter ();			// interne Zähler zurücksetzen

	{
	//	Recherche-Fenster init.
		RechercheStatus RS (g_pTE -> MWind (), &g_pTE -> RF ());
		pRechStat = &RS;		// Adresse speichern

		while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot)) 
		{// alle Dateien nacheinander abarbeiten
			_Reset ();

	#ifdef WIN32
			hr = ImportArcInfo (AnsiStringNew (pFile));
	#else
			hr = ImportArcInfo (pFile);
	#endif        
			CoTaskMemFree (pFile);

			if (FAILED(hr))	
				break;

		//	ggf. nächsten Ident holen
			if (m_bMultipleFiles && !pParams -> m_bAllCover)
				pParams -> ID = (ulong) DEX_GetUniqueICode (); // Unique Ident von TRIAS
		}
		// pRechStat -> Hide ();		// Status-Anzeige aus
// KK000328
		_Reset ();

	}

//  Ergebnis der Recherche ausgeben
	if (hr == S_OK || pParams -> HasImported ())
	{
		_OutputNotImported ();
		MessageBeep (MB_OK);
		ImportResult IR (g_pTE -> MWind (), &g_pTE -> RF (), timeGetTime () - m_dwStartTime,
						 m_bMultipleFiles ? NULL : pParams -> pCoverName);
		IR.Show ();
	}

	_Reset ();					//	interne Variablen zurücksetzen
	m_bIsConfigured = FALSE;	//	für die nächset Session
	pParams -> ID = 0;

	g_pTE -> MWind () -> Enable ();					// Parent akt.

	// DEX_PostRebuildSight();		// Sicht neu lesen
	return hr;
}

STDMETHODIMP CImportArcInfo :: ImportArcInfo (char *pFile)
{
	if (!pFile || !*pFile)
		return ResultFromScode (S_FALSE);

	HRESULT hr = NOERROR;

// KK000328
	pParams ->IsCompressed = _TransferImportFile (pFile);


	if ( pParams ->IsCompressed ) {
		_pCompName = new char [_MAX_PATH];
		if ( _pCompName)
			strcpy (_pCompName, pFile);
	}

	yyin = fopen (pFile, "r");
	if (yyin == NULL) {
		return ResultFromScode (STG_E_PATHNOTFOUND);
	}

// KK000329
	_pCompFile = yyin;

//  "kurzen" Dateinamen bilden und speichern
	if (! pParams -> SetCoverName (pFile))
		return ResultFromScode (S_FALSE);

//  Cover prüfen
	CFileBuffer Buffer;
	if (! Buffer.CreateBuffer ())          // Dateipuffer erzeugen
	{
		DEX_Error (RC_ArcTriasExtInit, EC_NOMEMORY);
		return ResultFromScode (S_FALSE);
	}

	_pCoverName = pFile;


	if (! _CheckCover (Buffer)) // Cover prüfen
		return ResultFromScode (S_FALSE);

//  weitere Parameter lesen/bilden
	pParams -> sIdCode = DEX_GetIdBase ();
	pParams -> sMCode = DEX_GetMkBase ();
	
//	Ident ggf. ändern
	char FName [_MAX_FNAME] = "";
	_splitpath (pFile, NULL, NULL, FName, NULL);

#if _TRiAS_VER > 0x0200

#if _TRiAS_VER < 0x0300
ulong ulIdent = (ulong) DEX_GetIdentFromClassNameCI (FName);
#else
HPROJECT hPr = DEX_GetDataSourceHandle();
ulong ulIdent = (ulong) DEX_GetIdentFromClassNameCIEx (hPr,FName);
#endif

#else
ulong ulIdent = (ulong) DEX_GetIdentFromClassName (FName);
#endif

	if (ulIdent > 0)
		pParams -> ID = ulIdent;

//  optionale Parameter eingeben
	/*
	if (m_bMultipleFiles && m_bIsConfigured)
	{
		if (pParams -> PalExist)					// Pal ist vorhanden 
		{
			pParams -> ImpPunkte = FALSE;			// LabelPunkte nicht import.
			pParams -> ImpFlaechen = TRUE;			// Flächen imp.

		//	wenn Linien Attribute haben, diese imp.
			pParams -> ImpLinien = pParams -> AatFields;
		}
		else
		{
			pParams -> ImpFlaechen = FALSE;			// es sind keine vorhanden
			pParams -> ImpPunkte = TRUE;			// wenn voh., imp.
			pParams -> ImpLinien = TRUE;			// wenn voh., imp.			
		}
	}
	else
	*/
	if (!m_bIsConfigured)
	{//	noch nicht konf.	
		pRechStat -> Hide ();						// Status-Anzeige aus
		OptParams OP (g_pTE -> MWind (), &g_pTE -> RF (), m_bMultipleFiles);
		if (!OP.OpFlag ())
			return ResultFromScode (S_FALSE);
		OP.Show ();
		if (! (OP.Result () && OP.OpFlag ()))
			return ResultFromScode (S_FALSE);

		m_bIsConfigured = TRUE;					// jetzt auch konf.
		m_dwStartTime = timeGetTime ();			// Startzeit merken
	}

//  ID in TRIAS erzeugen
	if (CreateIdent (pParams -> ID, FName, g_pTE -> MWind ()) != EC_OKAY)
		return ResultFromScode (S_FALSE);

//  ggf. Header komplettieren
	Header HD;
	if (! HD.OutScaleAndOffset (Bildmasse))       	// Offset/Scaling beachten
		return ResultFromScode (S_FALSE);
	if (! HD.GetUniqueIdent (pParams -> UnID))     	// unique Ident MK lesen
		return ResultFromScode (S_FALSE);
	if (! HD.GetTextObjMKode (pParams -> TextMK))  	// TextObjMKode lesen
		return ResultFromScode (S_FALSE);
    DEXN_ReReadHeader ();

//  Status-Fenster akt. 
	char szBuffer [50] = "";
	ResString Caption (ResID (IDS_STATCAPTION, pRF), 30);
	wsprintf (szBuffer, Caption.Addr (), pParams -> pCoverName);	// Überschrift
	ResString Elem2 (ResID (IDS_IMPORT_INFO, pRF), 60);
	pRechStat -> ReInit (pParams -> MaxLineNr, 0, szBuffer, NULL, 
						 Elem2.Addr ());
	pRechStat -> Show ();

//  Import starten
	Bool Op = _CreateTrees ();                      // Bäume anlegen
	pTDI -> SetIdent (pParams -> ID);               // ID speichern

// KK000317

	if (pParams -> PalExist)					// Pal ist vorhanden 
	{
		pParams -> ImpPunkte = FALSE;			// LabelPunkte nicht import.
		pParams -> ImpFlaechen = TRUE;			// Flächen imp.

	//	wenn Linien Attribute haben, diese imp.
		pParams -> ImpLinien = pParams -> AatFields;
	}
	else
	{
		pParams -> ImpFlaechen = FALSE;			// es sind keine vorhanden
		pParams -> ImpPunkte = TRUE;			// wenn voh., imp.
		pParams -> ImpLinien = TRUE;			// wenn voh., imp.			
	}


//---------------------------------------------------------------------------------

	if (Op)         
	{               
		void yyinit_lex (void);
		Op = yyparse ();
		DEXN_ReReadIdents ();
		DEXN_ReReadContainer ();

		IStorage *pISt = NULL;
		if (DEX_GetProjectStorage (pISt))
			pISt -> Release ();
		else
			DEX_FlushModifications();
	}                                                            
			
//  ODBC-Infos ausgeben                     
	Op = pTDI -> OutputConnectInfos () == EC_OKAY ? True : False;
	_DeleteTrees ();                                        // Bäume löschen
	pRechStat -> SetValue (pParams -> MaxLineNr);

	hr = Op ? ResultFromScode (S_OK) : ResultFromScode (S_FALSE);

	return hr;
}

//----------------------------------------------------------------------------
//  alle internen Werte rücksetzen
void CImportArcInfo :: _Reset (void) {
    if (_pTempFile && _pCoverName) {
		fclose (_pTempFile);
		int RC = remove (_pCoverName);       // temp. Datei löschen
    }

    // DELETE_VEC (_pCoverName);
	_pCoverName = NULL;
    _pTempFile = NULL;

// KK000328
	// Tempfile der komprimierten Datei wieder löschen
	if ( pParams ->IsCompressed) {
		if ( _pCompFile && _pCompName ) {
			int RC = fclose (_pCompFile);
			RC = remove (_pCompName);
		}
	}

	DELETE_OBJ(_pCompName);
	_pCompFile = NULL;

    if (pParams)
		pParams -> Reset ();        // weitere Parameter rücksetzen
}

// prüfe Cover:
//  + erzeuge temporäre Datei für Konvertietung (alle e00-Dateien in eine)
//  + erzeuge DOS-Datei (aus evtl. UNIX-Datei)
//  + entferne nicht benötigte Sections für LEX/YACC
//  + bestimme und setze aktuelle Skalierung/Offset
//  + bestimme max. Zeilenzahl für Konvertierungs-Zähler
//  + bestimme Polygon-Topologie    
Bool CImportArcInfo :: _CheckCover (CFileBuffer &Buffer) 
{
    const short Max = 100;                      // Zeilenlänge

//  Variablen init.
    FILE *pActFile = NULL;

    char Line [Max] = "";                       // 1 Zeile
    char Drive [_MAX_DRIVE] = "";
    char ActFileName [_MAX_PATH] = "";
    char FName [_MAX_FNAME] = "";
    char Dir   [_MAX_DIR] = "";
    char Ext   [_MAX_EXT] = "";

//  Dateipuffer anlegen
	CFileBuffer InBuffer, TempBuffer;
    if (!InBuffer.CreateBuffer () || !TempBuffer.CreateBuffer ()) 
    {		
		DEX_Error (RC_ArcTriasCheckCover, EC_NOMEMORY);
		return False;
    }

//  temp. Datei erzeugen
    _splitpath (_pCoverName, Drive, Dir, FName, NULL);
    ResString TempExt (ResID (IDS_TEMPEXT, &g_pTE -> RF ()), _MAX_EXT);

// KK990927___________________________________________________

	char * pTempDat = new char [_MAX_PATH];
	if ( pTempDat ) {
		DWORD TD = 0;
		TD = GetTempPath(_MAX_PATH, pTempDat);
		if ( TD > 0 ) {		// Temp-Bereich gefunden
			if ( TD > MAX_PATH) {
				DELETE_OBJ(pTempDat);
				pTempDat = new char [TD + 1];
				if ( pTempDat)
					DWORD TTD = GetTempPath(TD +1, pTempDat);
			}
		}

		if ( pTempDat) {
			char TDrive [_MAX_DRIVE] = "";
		    char TDir   [_MAX_DIR] = "";
 		    _splitpath (pTempDat, TDrive, TDir, NULL, NULL);
			_makepath (_pCoverName, TDrive, TDir, FName, TempExt);
		}

		DELETE_OBJ (pTempDat);

	} else

// KK990927___________________________________________________

	  _makepath (_pCoverName, Drive, Dir, FName, TempExt);

    if ((_pTempFile = fopen (_pCoverName, "wt")) == NULL) 
    {
		DEX_Error (RC_ArcTriasCheckCover, EC_NOTEMPFILE);
		return False;
    }
    setvbuf (_pTempFile, TempBuffer.Addr (), _IOFBF, TempBuffer.GetSize ());

//  check window erzeugen
    ResString Caption (ResID (IDS_COVERCAPTION, &g_pTE -> RF ()), 25);
    char CText [30] = "";
    wsprintf (CText, Caption.Addr (), pParams -> pCoverName); // "kurzer" Name
	ResString strElem2 (ResID (IDS_CHECK_INFO, &g_pTE -> RF ()), 60);
	
//  alle e00-Dateien in die temp. Datei kopieren
    _makepath (ActFileName, Drive, Dir, FName, NULL);
    ErrCode EC = EC_OKAY;
    for (short FileCnt = 0; EC == EC_OKAY; FileCnt++) 
    {
		_splitpath (ActFileName, Drive, Dir, FName, NULL);
		wsprintf (Ext, ".e%02d", FileCnt);
		_makepath (ActFileName, Drive, Dir, FName, Ext);

	//	max. Zeilenzahl ermitteln
		ulong lMaxLineNr = 0;
		int fh = _open (ActFileName, _O_RDONLY | _O_BINARY);

		if ( fh != - 1 && FileCnt > 0 &&pParams ->IsCompressed) {
			DEX_Error (RC_ArcTriasCheckCover, EC = EC_NOREAD);
			return False;
		}


		if (fh != -1)
		{
			lMaxLineNr = _filelength (fh);
			if (lMaxLineNr > 0)
                lMaxLineNr /= AvrChrPerLine;
        }
        if (fh != -1)
			_close (fh);
		else
			break;

	//	Recherche-Fenster akt.
		pRechStat -> ReInit (lMaxLineNr, 0, CText, NULL, strElem2.Addr ());
		pRechStat -> Show ();

		if ((pActFile = fopen (ActFileName, "rt")) == NULL)
			break;                  // alle möglichen Datei kopiert
		setvbuf (pActFile, InBuffer.Addr (), _IOFBF, InBuffer.GetSize ());

	//  akt. Datei in temp. Datei kopieren   
		long lActRow = 0;
		while (fgets (Line, Max, pActFile))                     // bis ans Ende kopieren
		{
			if (ferror (pActFile))
			{
				DEX_Error (RC_ArcTriasCheckCover, EC = EC_NOREAD);
				break;
			}
		//	evtl. nl anhängen
			if (strchr (Line, '\n') == NULL)
				lstrcat (Line, "\n");
				// Line [lstrlen (Line) - 1] = '\n';
		
			if ((EC = _OutputInfo (Line, pActFile)) != EC_OKAY)
			{
				DEX_Error (RC_ArcTriasCheckCover, EC);
				break;
			}            
			
		//	Scrollbalken akt.
			pRechStat -> SetValue (++lActRow);
				
			if (pRechStat -> Break ())               // Nutzerabbruch ?
			{
				EC = EC_USERBREAK;              
				break;                  // keine Meldung ausgeben
			}                               
		}   

	//	Max. Zeilenzahl setzen
		pRechStat -> SetValue (lMaxLineNr);

		fclose (pActFile);              // aktuelle e00-Datei schließen

    }
    fclose (_pTempFile);

    if (EC != EC_OKAY)
		return False;
	
//  temp. Datei im Lese-Modus öffnen
    if ((_pTempFile = fopen (_pCoverName, "rt")) == NULL) {
		DEX_Error (RC_ArcTriasCheckCover, EC_NOTEMPFILE);
		return False;
    }
    
//  übergebenen Datei-Puffer setzen    
    setvbuf (_pTempFile, Buffer.Addr (), _IOFBF, Buffer.GetSize ());

    yyin = _pTempFile;         // Lex auf richtige Datei

    return True;
}

// KK000328
//----------------------------------------------------------------------
//**********************************************************************
//#include <stdio.h>
//#include <ctype.h>

#include "e00compr.h"

Bool CImportArcInfo :: _TransferImportFile ( char *pFile)
{

    E00ReadPtr  hReadPtr;
    E00WritePtr hWritePtr;

    char  *pszInFile = NULL, *pszOutFile = NULL;
    const char  *pszLine;
    int         nStatus = 0, nComprLevel = E00_COMPR_NONE;

    nComprLevel = E00_COMPR_NONE;

    char FName [_MAX_FNAME] = "";
	char TDrive [_MAX_DRIVE] = "";
    char TDir   [_MAX_DIR] = "";
//  temp. Datei erzeugen
    _splitpath (pFile, TDrive, TDir, FName, NULL);
    ResString TempExt (ResID (IDS_DEFAULTEXTENSION, &g_pTE -> RF ()), _MAX_EXT);

	char *pCoverName = new char [_MAX_PATH];
	char * pTempDat = new char [_MAX_PATH];

	if ( pTempDat ) {

		DWORD TD = 0;
		TD = GetTempPath(_MAX_PATH, pTempDat);

		if ( TD > 0 ) {		// Temp-Bereich gefunden
			if ( TD > MAX_PATH) {
				DELETE_OBJ(pTempDat);
				pTempDat = new char [TD + 1];
				if ( pTempDat)
					DWORD TTD = GetTempPath(TD +1, pTempDat);
			}
		}

		if ( pTempDat) {
 		    _splitpath (pTempDat, TDrive, TDir, NULL, NULL);
			_makepath (pCoverName, TDrive, TDir, FName, TempExt);
		}

		DELETE_OBJ (pTempDat);

	} else {

		DELETE_OBJ(pCoverName);
		return false;

	}

    pszInFile = pFile;
	pszOutFile = pCoverName;

    /* ----------------------------------------------------------------
     * Open files and proceed with the conversion
     * ---------------------------------------------------------------*/
    hReadPtr = E00ReadOpen(pszInFile);

    if (hReadPtr)
    {
		if (!hReadPtr->bIsCompressed ) {	// Datei ist nicht komprimiert
	        CPLFree(hReadPtr);				// kein Handlungsbedarf
			hReadPtr = NULL;
			DELETE_OBJ(pszOutFile);
			return false;
		}

        hWritePtr = E00WriteOpen(pszOutFile, nComprLevel);

        if (hWritePtr)
        {
            /* Read lines from input until we reach EOF 
             */
            while((pszLine = E00ReadNextLine(hReadPtr)) != NULL)
            {
                if ((nStatus = CPLGetLastErrorNo()) == 0)
                    nStatus = E00WriteNextLine(hWritePtr, pszLine);

                if (nStatus != 0)
                {
                    /* An error happened while converting the last 
                     * line... abort*/
                    break;
                }
            }

            /* Close files.
             */
            E00WriteClose(hWritePtr);
        }
        else
            nStatus = CPLGetLastErrorNo();

        E00ReadClose(hReadPtr);

		strcpy (pFile ,pszOutFile);

		DELETE_OBJ(pszOutFile);

		return true;
    }
    else
        nStatus = CPLGetLastErrorNo();


	DELETE_OBJ(pszOutFile);

	return false;
}
//------------------------------------------------------------------------

//  Information über Zeile ausgeben
ErrCode CImportArcInfo :: _OutputInfo (pchar pLine, FILE *pInFile)
{
    static Bool OutLine = False;        // Flag regelt Ein/Ausgabe

//  prüfe Parameter
    if (pLine == NULL || *pLine == NULL)
		return EC_OKAY;

//  prüfe ob Cover-Beginn
    if (strstr (pLine, "EXP  0") == pLine) {
		OutLine = False;
		pParams -> MaxLineNr++;
		return fputs ("EXP  0\n", _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }

//  IFO-Section-Komplett lesen
    if (strstr (pLine, "IFO  2") == pLine || 
		strstr (pLine, "IFO  3") == pLine) 
    {
		OutLine = True;
		pParams -> MaxLineNr++;
		pParams -> DoublePrec = strstr (pLine, "IFO  3") == pLine ? True : False;
		return fputs (pLine, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }

//  prüfe auf Linien
    if (strstr (pLine, "ARC  2") == pLine ||
		strstr (pLine, "ARC  3") == pLine) 
    {
		OutLine = True;
		ResString LS (ResID (IDS_LINSECTION, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (LS.Addr ());
		pParams -> MaxLineNr++;
		return fputs (pLine, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }

//  prüfe auf Punkte
    if (strstr (pLine, "LAB  2") == pLine ||
		strstr (pLine, "LAB  3") == pLine) 
    {
		OutLine = True;
		ResString PuS (ResID (IDS_PKTSECTION, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (PuS.Addr ());
		pParams -> MaxLineNr++;
		return fputs (pLine, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }

//  prüfe auf Texte
    if (strstr (pLine, "TXT  2") == pLine ||
		strstr (pLine, "TXT  3") == pLine)
    {
		OutLine = True;
		ResString TS (ResID (IDS_TXTSECTION, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (TS.Addr ());
		pParams -> MaxLineNr++;
		return fputs (pLine, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }
    

//	suche nach "besonderen" Texten    
    if ((strstr (pLine, "TX") == pLine) && 
		(pLine [2] >= '0') && (pLine [2] <= '9'))
    {
		ResString TS (ResID (IDS_TXTSECTION, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (TS.Addr ());
		
		fputs (pLine, _pTempFile);					// Section-Beginn ausgeben
		pParams -> MaxLineNr++;		
		               
	//	diese Sektion wird "vorgeparst"
		char Buffer [128] = "";                      
		fgets (Buffer, sizeof (Buffer), pInFile);    // Kennung überlesen
				    
	//	alle Einträge konvertieren
		short sCnt;		    
		char *pBuff = NULL;
		while (TRUE)
		{
			fgets (Buffer, sizeof (Buffer), pInFile); // lese Info-Zeile
			if (strstr (Buffer, EoS) == Buffer)		  // Section-Ende	
				break;				
				
			pBuff = Buffer;
			
		// 	suche 2. Ziffer			
			while (*pBuff && *pBuff == ' ')    	// 1. Ziffer
				pBuff++;						
			while (*pBuff && *pBuff != ' ')		// hinter 1. Ziffer
				pBuff++;										
			while (*pBuff && *pBuff == ' ')    	// 2. Ziffer
				pBuff++;										
			if (!*pBuff)
				return EC_SYNTAX;
			while (*pBuff && *pBuff != ' ')		// hinter 2. Ziffer
				pBuff++;										
			while (*pBuff && *pBuff == ' ')    	// 3. Ziffer
				pBuff++;										
			if (!*pBuff)
				return EC_SYNTAX;
			sCnt = atoi (pBuff);										
			sCnt++;								// Anzahl der Real-Zeilen
			
		//	lesen der Integer-Blöcke
			while (TRUE)
			{
				fgets (Buffer, sizeof (Buffer), pInFile);
				if ((strstr (Buffer, EoT) == Buffer) || (strstr (Buffer, EoT2) == Buffer))
					break;			
			}			  
			
		//	lesen der Real-Zeilen
			for (short i = 0; i < sCnt; i++)
				fgets (Buffer, sizeof (Buffer), pInFile);
			fputs (Buffer, _pTempFile);			// die Koordinaten ausgeben
			
		//  und jetzt "ordentlichen" Text erzeugen
			pBuff = Buffer;
			fgets (++pBuff, sizeof (Buffer) - 2, pInFile);
			char ScopeChar = '\"';
			if (strchr (pBuff, '\"'))		// wenn " bereits im Text
				ScopeChar = '\'';           // dieses ScopeChar ben.
			char *pNL = strchr (pBuff, '\n');
			*pNL = ScopeChar;
			*++pNL = '\n';
			*++pNL = '\0';
			Buffer [0] = ScopeChar;
			
			fputs (Buffer, _pTempFile);										
			pParams -> MaxLineNr += 2;							
		}		
		
	//	Section-Ende ausgeben	
		pParams -> MaxLineNr++;	
		return fputs (Buffer, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }

//  prüfe auf Flächen
    if (strstr (pLine, "PAL  2") == pLine ||
		strstr (pLine, "PAL  3") == pLine) 
    {
		pParams -> PalExist = True;
		OutLine = True;
		ResString FS (ResID (IDS_PALSECTION, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (FS.Addr ());
		pParams -> MaxLineNr++;
		return fputs (pLine, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }

//  prüfe auf Linien-Attribute
    if (strstr (pLine, ".AAT") != NULL) {
	pParams -> AatExist = True;
		ResString AAT (ResID (IDS_AAT, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (AAT.Addr ());
		pParams -> MaxLineNr++; 
		
	//      evtl. auch weitere Feld-Infos vorhanden ?
		char *pFieldCnt = strstr (pLine, "XX");
		if (pFieldCnt && (atoi (pFieldCnt+2) > 7))
			pParams -> AatFields = True;                    
		
		return fputs (pLine, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;
    }

//  prüfe auf Flächen-Attribute
    if (strstr (pLine, ".PAT") != NULL) {
		ResString PAT (ResID (IDS_PAT, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (PAT.Addr ());
		pParams -> MaxLineNr++;
		return fputs (pLine, _pTempFile) < 0 ? EC_NOWRITE : EC_OKAY;            
    }

//  prüfe auf Abmaß-Section
    if (strstr (pLine, ".BND") != NULL) {
		if (fputs (pLine , _pTempFile) < 0)
			return EC_NOWRITE;
		ResString BND (ResID (IDS_BNDSECTION, &g_pTE -> RF ()), 80);
		pRechStat -> SetElemText (BND.Addr ());

		char Buffer [128] = "";
		fgets (Buffer, sizeof (Buffer), pInFile);               // XMIN
		fputs (Buffer, _pTempFile);
		fgets (Buffer, sizeof (Buffer), pInFile);               // YMIN
		fputs (Buffer, _pTempFile);
		fgets (Buffer, sizeof (Buffer), pInFile);               // XMAX
		fputs (Buffer, _pTempFile);
		fgets (Buffer, sizeof (Buffer), pInFile);               // YMAX
		fputs (Buffer, _pTempFile);
		fgets (Buffer, sizeof (Buffer), pInFile);                       // Koordinaten
						
	//      Datei-Lese-Schreibfehler                                                
		if (ferror (pInFile))
			return EC_NOREAD;
		if (ferror (_pTempFile))
			return EC_NOWRITE;                                                              
			
		if (pParams -> DoublePrec)
		{
			Buffer [lstrlen (Buffer) - 1] = '\0';               // nl abschneiden                       
			char RestBuffer [50] = "";                       	// Rest der Zahl lesen
			fgets (RestBuffer, sizeof (RestBuffer), pInFile);
			if (ferror (pInFile))
				return EC_NOREAD; 
            // RestBuffer [lstrlen (RestBuffer) - 1] = '\0';		// nl abschneiden		                      
			lstrcat (Buffer, RestBuffer);
		}
		if (fputs (Buffer, _pTempFile) < 0)                      // ausgeben     
			return EC_NOWRITE;

	//  Bildmaße lesen
		pchar pVal = Buffer;
		for (short i = 0; (i < BildmasCount) && *pVal; i++) 
		{
			while (*pVal && *pVal != '.')		
				pVal++;
			if (!*pVal)         // keine Ziffern mehr vorhanden
				break;				
			pVal--;				// 1. Ziffer			
			pVal--;             // ggf. Vorzeichen
			if (*pVal == ' ')   // wenn ohne
				pVal++;			// wieder auf 1. Ziffer	
			Bildmasse [i] = atof (pVal);
			
		//	auf nächste Ziffer			
			while (*pVal && *pVal != '.')		
				pVal++;
			pVal++;				
		}
		pParams -> MaxLineNr += 6;
		return EC_OKAY;
    }

//  wenn gültige Section, dann Zeile ausgeben
    if (OutLine) {
	//  Zeile auf fehlerhafte Zeichen prüfen
		register short Max = lstrlen (pLine);
		for (register short i = 0; i < Max; i++) 
		{
			if (pLine [i] >= ' ' || pLine [i] <= '~')
				continue;                                                               // Zeichen ist OK
					      
		//      Test auf "Sonderzeichen"                                              
			switch (pLine [i])
			{                                               
				case '\r':                                              
				case '\n':                                                                                      
				case 'ä':
				case 'Ä':                               
				case 'ö':
				case 'Ö':
				case 'ü':
				case 'Ü':
				case 'ß':
					continue;
				break; 
				default:                                
					pLine [i] = ' ';
				break;                                  
			}
		}

		if (fputs (pLine, _pTempFile) < 0)
			return EC_NOWRITE;
		pParams -> MaxLineNr++;
    }

//  Section-Ende ?
    if (strstr (pLine, EoS) == pLine) {
		OutLine = False;
		return EC_OKAY;
    }

//  Punkte-Section-Ende
    if (strstr (pLine, EoP) == pLine) {
		OutLine = False;
		return EC_OKAY;
    }

    return EC_OKAY;
}

// Bäume anlegen
Bool CImportArcInfo :: _CreateTrees (void) 
{
	_DeleteTrees ();
	pMDT = new MerkmalsBaum ();
    pPE = new PointEntries;
    pLE = new LineEntries (_pCoverName);
    pPlE = new PalEntries; 
    pTDI = new CTextDatInfoList (&g_pTE -> RF ());

    if (!pMDT || !pPE || !pLE || !pLE -> Result () ||
	!pTDI || !pPlE) 
    {
		_DeleteTrees ();
		return False;
    }

    return True;
}

//  Bäume freigeben
void CImportArcInfo :: _DeleteTrees (void) {
    DELETE_OBJ (pPE);
    DELETE_OBJ (pLE);
    DELETE_OBJ (pPlE);
    DELETE_OBJ (pMDT);            
    DELETE_OBJ (pTDI);
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

//  Konvertierungs-Message ausgeben
void OutKonvMess (DGeoTyp Typ) {
    char Buffer [15] = "";
    switch (Typ) {
		case DGT_Linie:
			lstrcpy (Buffer, "Linien");
		break;
		case DGT_Flaeche:
			lstrcpy (Buffer, "Flächen");
		break;
		case DGT_Text:
			lstrcpy (Buffer, "Texte");
		break;
		case DGT_Symbol:
		case DGT_Punkt:
			lstrcpy (Buffer, "Punkte");
		break;
		case DGT_OtherTable:
			lstrcpy (Buffer, "Tabelle");
		break;
		default:
		case DGT_Unknown:
			lstrcpy (Buffer, " ");
		break;
    }            
				       
	char Text [40] = "importiere ";                                       
				       
    if (Typ == DGT_Unknown)
		lstrcpy (Text, Buffer);
	else            
    {
		lstrcat (Text, Buffer);
		lstrcat (Text, " ...");
	}       

    pRechStat -> SetElemText (Text);
}

//  Import-Status akt.
void IncCounter (long ObjNr) 
{
	if (ObjNr)                                              // wenn Objekt-Nummer gegeben
		pRechStat -> SetValue (pParams -> LineNr, ObjNr);               
	else    
	{       
		if ((++ pParams -> LineNr % OutLineCnt) == 0)
			pRechStat -> SetValue (pParams -> LineNr);
	}                       
}
		
//      DebugSection-Eintrag aus win.ini lesen                
Bool CImportArcInfo :: _GetDebugOutputFlag (void)
{
	ResString Section (ResID (IDS_DEBUGSECTION, &g_pTE -> RF ()), 30);
	ResString Entry (ResID (IDS_DEBUGENTRY, &g_pTE -> RF ()), 30);   
	char Buffer [5] = "";
	
	return  GetProfileString (Section.Addr (), Entry.Addr (), "0", Buffer, sizeof (Buffer)) 
			&& (atoi (Buffer) > 0) ? True : False;
}
			   
//      Anzahl der nicht oder teilweise importierten Objekte ausgeben                           
void CImportArcInfo :: _OutputNotImported (void)
{                    
	if (!pParams -> DebugOutput)
		return;
		
	char Buffer [80];
	if (pParams -> NotImported)
	{
		ResString NotImp (ResID (IDS_NOTIMPORTED, &g_pTE -> RF()), 80);
		wsprintf (Buffer, NotImp.Addr (), pParams -> NotImported);
		OutputDebugString (Buffer);
	}       
	
	if (pParams -> SubImported)
	{
		ResString SubImp (ResID (IDS_ONLYMASCHMPORTED, &g_pTE -> RF()), 80);
		wsprintf (Buffer, SubImp.Addr (), pParams -> SubImported);
		OutputDebugString (Buffer);             
	}
}                                  
        
