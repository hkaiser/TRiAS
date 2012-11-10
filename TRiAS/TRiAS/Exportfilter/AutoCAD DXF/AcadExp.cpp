// File: ACADDXF.CXX
// Stand vom 13. April 1994
// In dieser Datei befinden sich lokale Funktionen zur Arbeit des Filters

#include "stdafx.h"
#include "AcadDXFImpl.h"

//XX	extern "C" {
    #include <io.h>             // setmode ()
    #include <float.h>			// DBL_MAX
    #include <fcntl.h>			// O_TEXT
    #include <resstrg.h>		// TRIAS-Konstanten
    #include <xtensnxx.h>		// DEXX_MAINWINDOW
//XX	}

#include <attribs.hxx>          // VisInfo ...
#include <impexp.hxx>           // MF, GS ...
#include <ristypes.hxx>         // OT_PUNKT, OT_KANTE, OT_FLAECHE, OT_TEXT
#include <strdup.hxx>           // StringDup

#include "merkmdes.hxx"         // MerkmalDescriptionTree
//XX#include "acaddxf.hr"           // Resourcen-Defines
#include "acaddxf.hxx"          // zugeh. Header
#include "identdes.hxx"         // ExtIdentDescriptionTree

// Konstanten
const char ColorExtension [] = ".VIS";      // Datei-Extension f. Vis-Info
const char VisTempFile [] = "VISINFO";      // Name der VisInfo-Template-Datei
const char VisTempFileExt [] = ".TPL";      // zugeh. Extension
const char InsertTempFileExt [] = ".INS";	// Insert-datei
const char IniFileExt []     = ".INI";      // Ini-File-Extension
const char AcadVersion [] = "AC1004";       	// AutoCAD-Version
const short DummyLength = 270;                  // Header-Dummy-Länge
const double KorrFakt = 0.05;                   // Bildmaße-Korrektur
const short DummyKoOrdSize = 20;                // max. Anz. Digits einer Dummy-Koordinate
const char pStandSymbol [] = "6";               // Name des Standard-Symbols
const short StandSymbol = 6;
const double StandardSymGroesse = 30;           // durchschn. Symbolgröße in mm

// Variablen, die vom Anwender im INI-File gesetzt werden können
double StandTextHoehe = 10.0;                   // Konstanten für Text-Objekte


double StandTextHoeFaktor = 1.0;                // Text-Höhe
double StandLinBrFakt = 0.01;                   // Linienbreite / 100 div.
double StandTextRotFakt = -1.0;                 // Drehrichtungsumkehr
long StandTextMKode = 0L;                       // Merkmalskode eines Textwertes
int g_ifh = 0;									// FileHandle auf INSERT-Datei
long g_lBlockNummer = 1;						// akt. Blocknummer

// globale Variablen
UINT __DexCmd;
UINT __DexxCmd;
HWND __hWndM;

/*XX*/	HPROJECT	hDatasource;			// Handle der aktuellen Datenquelle
char pIniFilePath [_MAX_PATH] = "";             // vollst. Ini-File-Name
char pOutFilePath [_MAX_PATH] = "";             // vollst. Ausgabe-Datei-Name

ExtIdentDescriptionTree *pIDT = NULL;       	// ID-Beschr.-Baum
ExtMerkmalDescriptionTree *pMDT = NULL;     	// Merkmal-Beschr.-Bäume

ResourceFile *pRF = NULL;

OFSTRUCT *pColFileStruct = NULL;                // VisInfo-File-Struct
OFSTRUCT *pVisInfoTemplStruct = NULL;           // VisInfo-Template-Struct
OFSTRUCT *pInsertStruct = NULL;					// Insert-Datei

long Punkte = 0;                                // Elementezähler
long Linien = 0;
long DummyPos = 0;                              // Header-Einfüge-Punkt
long LastID = 0;
double XMin = DBL_MAX;                          // kleinste u. größte Koordinate
double YMin = DBL_MAX;
double XMax = 0;
double YMax = 0;
// KK000229
Bool bBeginn = False;							// Erstabfrage

Bool bCreateBlocks = False;						// Block für jedes Objekt erzeugen

// KK001020
Bool bIsCreateBlocks = False;					// CreateBlocks noch nicht angefaßt
	

Bool AlleMerkmale = False;                      // nicht alle Merkmalse exportieren
Bool FirstData = True;                          // erstmaliges Daten-Ausgeben
Bool ValidMKodes = False;                       // Keine gültigen Merkmals-Kodes
short MaxTextLen = 0;                           // Maximale Länge eines Textobjektes
Bool SymbolWarnung = False;						// noch keine Warnung ausgegeben

// externe Variablen
//XX	extern "C" {                                    
extern char pDLLName [_MAX_PATH];               // Puffer für DLL-Namen
//XX	}
extern HANDLE hDLLInst;

//  Prototypen
//XX	ErrCode OutputWarnungIdent (short ResourceId, long ID, long ObjNr = 0); // Warnung ausgeben
ErrCode OutputWarnung (short ResourceId, long Value, long ObjNr = 0);
void _GetTextObjKode (void);                    // Merkmalskode für Textanbindung lesen
//XX	extern "C" {
void DeletePalette (void);                      // Palette freigeben
//XX	}

//XX#ifndef __NT__
//XX#define HUGE __huge
//XX#else 
//XX#define HUGE
//XX#endif

#if !defined(HUGE)
#define	HUGE
#endif

// lokale Inlinefunktionen
inline
void SetXCon (double X) { if (X < XMin) XMin = X; if (X > XMax) XMax = X; }
inline
void SetYCon (double Y) { if (Y < YMin) YMin = Y; if (Y > YMax) YMax = Y; }
inline
void SetMaxTextLen (short L) { if (L > MaxTextLen) MaxTextLen = L; }

//XX	#ifdef _DEBUG
//XX	HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
//XX	{
//XX	CLASSFROMIDENT CFI;
//XX	
//XX		INITSTRUCT(CFI, CLASSFROMIDENT);
//XX		CFI.ulIdent = ulIdent;
//XX		CFI.pClass = pBuffer;
//XX		CFI.iBuffLen = iBuffLen;
//XX		if (NULL != pBuffer && iBuffLen > 0)
//XX			pBuffer[0] = '\0';
//XX		return DEX_GetClassFromIdent(CFI);
//XX	}
//XX	HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew /*=FALSE*/ )
//XX	{
//XX		if (NULL == pulIdent) 
//XX			return E_POINTER;
//XX	
//XX		IDENTFROMCLASS IFC;
//XX	
//XX		INITSTRUCT(IFC, IDENTFROMCLASS);
//XX		IFC.pcClass = pcClass;
//XX		IFC.fCreateNew = fCreateNew;
//XX	
//XX		//XX	HRESULT hr = DEX_GetIdentFromClass(IFC);
//XX		/*XX*/ _ASSERTE( NULL != hDatasource);
//XX		/*XX*/ HRESULT hr = DEX_GetIdentFromClassEx(hDatasource, IFC);
//XX	
//XX		if (SUCCEEDED(hr)) 
//XX			*pulIdent = IFC.ulIdent;
//XX	
//XX		return hr;
//XX	}
//XX	#endif

// Beginn des Exports
//XX	extern "C" {
//XX ErrCode EXPORTFLT PASCAL AcadDxfExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hParWnd)
/*XX*/ ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hParWnd, LPCTSTR lpszDatasource )
{


    int fh, vfh, tfh;
    __hWndM = hParWnd;

	fh = vfh = tfh = 0;

// KK000216
    if (OutFlag == OMConcatinate) { 
		if ((fh = OpenFile (lpFileName, &of, OF_WRITE)) < 0)
			return EC_NOFILE;
		FirstData = False;
// KK010131
		_lclose (fh);
	    return EC_OKAY;
	}


    char OutPath[_MAX_PATH];
    char Drive[_MAX_DRIVE], Dir[_MAX_DIR];
    char FName[_MAX_FNAME], Ext[_MAX_EXT];

//  globale Variablen init.     
//	/*XX*/ _ASSERTE( NULL == hDatasource);
	/*XX*/	hDatasource = DEX_GetDataSourceHandleEx( lpszDatasource );


	SymbolWarnung = False;
    YMin = XMin = DBL_MAX;
    XMax = YMax = 0;
    FirstData = True;

// KK000229
//   pIDT = NULL;
//   pMDT = NULL;

    pInsertStruct = pVisInfoTemplStruct = pColFileStruct = NULL;

//   ValidMKodes = False;                 // Keine gültigen MerkmalKodes
    MaxTextLen = 0;
    Punkte = Linien = 0;				// Zähler rücksetzen
// KK010207
 //   DummyPos = LastID = 0;
    DummyPos = 0;
	g_lBlockNummer = 1;					// akt. Blocknummer

//  Resource-File-Objekt init.
// KK000302
	if ( !pRF )
		pRF = new ResourceFile ((char *) pDLLName);
    if (!pRF)
		return EC_NOMEMORY;

//  bei System-Fehler zurück
    ResString RS (IDS_DEXMESSAGE, 80);
    if (!(__DexCmd = RegisterWindowMessage (RS.Addr ())))
		return EC_NODEXMESSAGE;

//  für C++ Nachrichten
    RS = ResString (IDS_DEXXMESSAGE, 80);
    if (!(__DexxCmd = RegisterWindowMessage (RS.Addr ()))) {
		DELETE_OBJ (pRF);
		return EC_NODEXMESSAGE;
    }

//  Ini-Datei-Namen bilden: nur vollständigen Dateinamen !
    _splitpath (pDLLName, Drive, Dir, FName, Ext);
    lstrcpy (pIniFilePath, FName);
    lstrcat (pIniFilePath, IniFileExt);

//  evtl. Standard-Werte init.
    char Buffer [81] = "";
    double Val;

    RS = ResString (ResID (IDS_MERKMALSEXPORTSEC, pRF), 80);
    ResString RS1 (ResID (IDS_STANDARDSTRING, pRF), 80);

//  Abschnitt Merkmalsexport: alle Merkmale exportieren ?
/*--------------in ShortBeginn
    AlleMerkmale = False;
    RS = ResString (ResID (IDS_MERKMALSEXPORTSEC, pRF), 80);
    ResString RS1 (ResID (IDS_STANDARDSTRING, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    RS1 = ResString (ResID (IDS_ALLEVAL, pRF), 10);
	    if (! lstrcmp (RS1.Addr (), strupr (Buffer)))
			AlleMerkmale = True;
    }
---*/

//  Texthöhe
    RS = ResString (ResID (IDS_DXFSTANDARD, pRF), 80);
    RS1 = ResString (ResID (IDS_STTEXTHOEHE, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    Val = atof (Buffer);
	    if (Val)                    // wenn gültiger Wert,
			StandTextHoehe = Val;   // dann übernehmen
    }

//  Texthöhen-Faktor
    RS1 = ResString (ResID (IDS_STTEXTHOEFAKT, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    Val = atof (Buffer);
	    if (Val)                            // wenn gültiger Wert,
			StandTextHoeFaktor = Val;       // dann übernehmen
    }

//  Text-Rotations-Faktor
    RS1 = ResString (ResID (IDS_STTEXTROTFAKT, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    Val = atof (Buffer);
	    if (Val)                            // wenn gültiger Wert,
			StandTextRotFakt = Val;         // dann übernehmen
    }

//  Merkmalskode für Textwert lesen
//    _GetTextObjKode ();	in ShortBeginn

//  Linienbreite
    RS1 = ResString (ResID (IDS_STLINBRFAKT, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    Val = atof (Buffer);
	    if (Val)                            // wenn gültiger Wert,
			StandLinBrFakt = Val;           // dann übernehmen
    }

//  Symbolgroessen-Faktor für Skalierung
    double SymGroesse = StandardSymGroesse;	

    RS1 = ResString (ResID (IDS_STSYMGROESSE, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    Val = atof (Buffer);
	    if (Val)                            // wenn gültiger Wert,
			SymGroesse = Val;               // dann übernehmen
    }

	
//  wenn neue Info angehängt werden soll
// KK 000216 - raus ??
    if (OutFlag == OMConcatinate) { // "append" nicht bei AutoCAD mögl.
		return WC_NOTAPPEND;
   }

    if ((fh = OpenFile (lpFileName, &of, OF_EXIST + OF_CREATE + OF_WRITE)) < 0)
		return EC_NOFILE;

//  Pfad der Ausgabedatei merken
    lstrcpy (pOutFilePath, of.szPathName);

//  Datei für VisInfo-Tabelle öffnen
    _splitpath (lpFileName, Drive, Dir, FName, Ext);
    _makepath (OutPath, Drive, Dir, FName, ColorExtension);
    pColFileStruct = new OFSTRUCT;
    if (!pColFileStruct)
		return EC_NOMEMORY;
    if ((vfh = OpenFile (OutPath, pColFileStruct, OF_EXIST + OF_CREATE + OF_WRITE)) < 0)
		return EC_NOFILE;

//  Datei für VisInfo-Template öffnen
    _makepath (OutPath, Drive, Dir, VisTempFile, VisTempFileExt);
	pVisInfoTemplStruct = new OFSTRUCT;
    if (!pVisInfoTemplStruct)
		return EC_NOMEMORY;
    if ((tfh = OpenFile (OutPath, pVisInfoTemplStruct, OF_EXIST + OF_CREATE + OF_WRITE)) < 0)
		return EC_NOFILE;

//  erweiterten Merkmals-Beschreibungsbaum anlegen

	if (!pMDT)
		pMDT = new ExtMerkmalDescriptionTree ();
    if (!pMDT) {
		DELETE_OBJ (pIDT);
		return EC_NOMEMORY;
    }

//	Beschreibungsbaum anlegen
	if ( !pIDT )
	   pIDT = new ExtIdentDescriptionTree (SymGroesse);
    if (!pIDT) {
		DELETE_OBJ (pMDT);
		return EC_NOMEMORY;
	}

//	Block für jedes Objekt erzeugen
	g_ifh = 0;

// KK000229 - in ShortBeginn
//	ResString resQuestion (ResID (IDS_CREATE_BLOCKS, pRF), 80);
//	ResString resFilter (ResID (IDS_AUTOCAD_CAPTION, pRF), 80);
//	if (IDYES == ::MessageBox (hParWnd, resQuestion.Addr(), resFilter.Addr(), 
//							   MB_ICONQUESTION | MB_YESNO))

//	{
//		bCreateBlocks = True;
//		AlleMerkmale = TRUE;

	if ( bCreateBlocks) {

	//  Insert-Datei erzeugen
		_makepath (OutPath, Drive, Dir, FName, InsertTempFileExt);
		pInsertStruct = new OFSTRUCT;
		if (!pInsertStruct)
			return EC_NOMEMORY;
		if (OpenFile (OutPath, pInsertStruct, OF_EXIST + OF_CREATE + OF_WRITE) < 0)
			return EC_NOFILE;

		if ((g_ifh = OpenFile (NULL, pInsertStruct, OF_REOPEN+OF_WRITE)) < 0)
			return EC_NOFILE;
		setmode (g_ifh, O_TEXT);

	}

//	else
//		bCreateBlocks = FALSE;

    return EC_OKAY;
}

// Ausgeben einer Kommentarzeile -------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportComment (OFSTRUCT &of, const char *lpCommentString)
/*XX*/	ErrCode ExportComment (OFSTRUCT &of, LPCTSTR lpCommentString)
{
    register int fh = 0;     // FileHandle
    register ErrCode EC;

    if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
		return EC_NOFILE;
    _llseek (fh, 0L, SEEK_END);
    setmode (fh, O_TEXT);
    if ((EC = ExportRecord (fh, 999, lpCommentString)) < 0) {
		_lclose (fh);
		return EC;
    }
    return (ErrCode)_lclose (fh);
}

// Ausgeben der HeaderInformation -----------------------------
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportHeader (OFSTRUCT &of, const char *lpHeaderString)
/*XX*/	ErrCode ExportHeader (OFSTRUCT &of, const char *lpHeaderString)
{
    register int fh;     // FileHandle
    register ErrCode EC;

    if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
		return EC_NOFILE;
    _llseek (fh, 0L, SEEK_END);
    setmode (fh, O_TEXT);
    if ((EC = ExportRecord (fh, 999, lpHeaderString)) < 0) {
		_lclose (fh);
		return EC;
    }
    return (ErrCode)_lclose (fh);
}

/*XX*/	ErrCode ExportDescriptionEx(OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescString, DWORD dwStyle) {
	return ExportDescription( of, lpKeyInfo, lpDescString );
}

// Ausgeben der BeschreibungsInformation ------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportDescription (OFSTRUCT &of, const char *, const char *lpDescString)
/*XX*/	ErrCode ExportDescription(OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescString)
{
    register int fh = 0;     // FileHandle
    register ErrCode EC;

    if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
		return EC_NOFILE;
    _llseek (fh, 0L, SEEK_END);
    setmode (fh, O_TEXT);
    if ((EC = ExportRecord (fh, 999, lpDescString)) < 0) {
		_lclose (fh);
		return EC;
    }
    return (ErrCode)_lclose (fh);
}

/////////////////////////////////////////////////////////////////////////
// IdentDescription kommt jetzt "zerpflückt", muß also hier erst 
// zusammengebaut werden
// KK001023
//ErrCode ExportIDDescription(const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, DWORD * pVis) {
ErrCode ExportIDDescription(const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, DWORD * pVis, long lIdent) {
	if (!bBeginn )
		ShortBeginn();

	return EC_OKAY;
}

ErrCode ExportIdentDescription (IdentDescription &ID);

// KK001023
//ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVISINFO ) {
ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVISINFO , long lIdent) {
	VisInfo	*pV = NULL;
	switch( lVisType ) {
	case OT_PUNKT: {
			_ASSERTE( sizeof(PVISINFO) == pVISINFO->dwSize );
			PVISINFO	*p = (PVISINFO*) pVISINFO;
			pV = new PVisInfo( pVISINFO->m_Style
				, pVISINFO->m_Priority
				, Color(GetRValue(pVISINFO->m_C),GetGValue(pVISINFO->m_C),GetBValue(pVISINFO->m_C))
				, Dimension(p->m_Size.cx,p->m_Size.cy)
				, (char*) pVISINFO->m_VisName
				, p->m_iRot
				, Color(GetRValue(p->m_SecC),GetGValue(p->m_SecC),GetBValue(p->m_SecC))
				);
			break;
		}
	case OT_KANTE: {
			_ASSERTE( sizeof(LVISINFO) == pVISINFO->dwSize );
			LVISINFO	*p = (LVISINFO*) pVISINFO;
			pV = new LVisInfo( pVISINFO->m_Style
				, pVISINFO->m_Priority
				, Color(GetRValue(pVISINFO->m_C),GetGValue(pVISINFO->m_C),GetBValue(pVISINFO->m_C))
				, p->m_Width
				, (char*) pVISINFO->m_VisName
				);
			break;
		}
	case OT_FLAECHE: {
			_ASSERTE( sizeof(FVISINFO) == pVISINFO->dwSize );
			FVISINFO	*p = (FVISINFO*) pVISINFO;
			pV = new FVisInfo( pVISINFO->m_Style
				, pVISINFO->m_Priority
				, Color(GetRValue(pVISINFO->m_C),GetGValue(pVISINFO->m_C),GetBValue(pVISINFO->m_C))
				, Color(GetRValue(p->m_FC),GetGValue(p->m_FC),GetBValue(p->m_FC))
				, p->m_iAttrEx
				, (char*) pVISINFO->m_VisName
				);
			break;
		}
	case OT_TEXT: {
			_ASSERTE( sizeof(TVISINFO) == pVISINFO->dwSize );
			TVISINFO	*p = (TVISINFO*) pVISINFO;
			pV = new TVisInfo( pVISINFO->m_Style
				, pVISINFO->m_Priority
				, Color(GetRValue(pVISINFO->m_C),GetGValue(pVISINFO->m_C),GetBValue(pVISINFO->m_C))
				, Dimension(p->m_Size.cx,p->m_Size.cy)
				, p->m_Type
				, p->m_Rot
				, (char*) pVISINFO->m_VisName
				);
			break;
		}
	}

// KK000123
	if (!bBeginn )
		ShortBeginn();


//	ULONG	lIdent;
//	IdentFromClassX( hDatasource, lpszOKS, &lIdent, false );

//	IdentDescription	IDD( lIdent, (char*) lpszOKS, pV, NULL );
// KK000217 - KurzText ist gefragt, nicht OKS
	IdentDescription	IDD( lIdent, (char*) lpszShortDescription, pV, NULL );


	return	ExportIdentDescription(IDD);
}

// Lesen und speichern aller ID-Eigenschaften -------------------------------
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportIdentDescription (IdentDescription &ID)
/*XX*/	ErrCode ExportIdentDescription (IdentDescription &ID)
{
    if (!pIDT)
		return EC_SYSERROR;

//  prüfe Parameter
    VisInfo *pVI = &ID.VisInfoObj ();
    // if (!pVI)                 
		//	als Standard erlaubt --> return OutputWarnungIdent (IDS_IDENTWARNGTYP, ID.ID ());
	if (pVI)
	{		
		switch (pVI -> isA ()) {
			case VT_Punkt : {
			//  Style-Test
	    		short St = pVI -> Style ();
	    		if (! (St == 3 || St == 5 || St == 6 || St == 20 || St == 21 ||
					St == 26 || St == 47 || (St >= 171 && St <= 178) ||
					(St >= 180 && St <= 220) || St == 222 || (St >= 228 && St <= 236) ||
					(St >= 249 && St <= 252))) {
					pVI -> Style () = StandSymbol;
					if (!bCreateBlocks && !SymbolWarnung)
					{
						SymbolWarnung = True;
						DEX_Error (RC_ACADDXF, WC_SYMBOLNOTFOUND);
					}					
	    		}

			//  Symbole ggf. ersetzen
	    		switch (St) {
					case 20:
		    			pVI -> Style () = 178;
					break;
					case 249:
		    			pVI -> Style () = 250;
					break;
	    		}
			}
			break;
			case VT_Linie :
			case VT_Flaeche :
			case VT_Text :
				break;
			case VT_Default:
			default:  
				return OutputWarnungIdent (IDS_IDENTWARNGTYP, ID.ID ());
			break;
		}
	}

    if (pIDT -> AddIDD (ID)) {
		LastID = ID.ID ();          // letzten ID merken
		return EC_OKAY;
    } else
		return EC_NOMEMORY;
}

// Ausgeben der TrailerInformation --------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportTrailer (OFSTRUCT &of, const char *)
/*XX*/	ErrCode ExportTrailer (OFSTRUCT &of, const char *)
{
    ErrCode EC = EC_OKAY;
	int fh = 0;     // FileHandle
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_READWRITE)) < 0)
		return EC_NOFILE;
    _llseek (fh, 0L, SEEK_END);
    setmode (fh, O_TEXT);

//	akt. Section beenden
	if ((EC = ExportRecord (fh, 0, "ENDSEC")) < 0) {
		_lclose (fh);
		return EC;
    }

 //	ggf. INSERT-Datei anhängen
	if (bCreateBlocks)
	{
	//	auch diese Section zuerst beenden
		if ((EC = ExportRecord (g_ifh, 0, "ENDSEC")) < 0) 
		{
			_lclose (fh);
			return EC;
		}
		
	//	Dateien schließen
		_lclose (g_ifh);
		g_ifh = 0;
		_lclose (fh);
		fh = 0;
		
	//	Dateien neu öffnen
		FILE *pActFile = NULL;
		FILE *pDestFile = NULL;
		if ((pActFile = fopen (pInsertStruct -> szPathName, "rt")) == NULL)
			return EC_NOFILE;

	//	Ausgabe-Datei öffnen
		if ((pDestFile = fopen (of.szPathName, "at")) == NULL)
		{
			fclose (pActFile);             
			return EC_NOFILE;
		}
		
	//	Datei umkopieren
	// KK001011 _Zeilenbeschränkung ist beschränkt
//		const short Max = 100;                      // Zeilenlänge
//		const short Max = _MAX_PATH;           // Zeilenlänge
		const short Max = 257;           // Zeilenlänge
		short iFlag = FALSE;

		char Line [Max] = "";                       // 1 Zeile
		while (fgets (Line, Max-1, pActFile))     
		{
			if (ferror (pActFile))
			{
				DEX_Error (RC_ACADDXF, EC = EC_NOREAD);
				break;
			}

/*-------
		//	Original - Benki : evtl. nl anhängen
			if (strchr (Line, '\n') == NULL)
				lstrcat (Line, "\n");
-----------------*/
// KK001024
			if (strchr (Line, '\n') == NULL) {
				lstrcat (Line, "\n");
				iFlag = TRUE;
				
			} else {
				iFlag = FALSE;
			}
// KK001024---------------------------------

		//	Zeile ausgeben		
			if (fputs (Line, pDestFile) < 0)
			{
//XX					EC = EC_NOWRITE;
/*XX*/					EC = EC_NOFILE;
				break;
			}

// KK001024 - zuviel Informationen belasten nur !!!
			while (iFlag ) {

				fgets (Line, Max-1, pActFile);

				if (ferror (pActFile))
				{
					DEX_Error (RC_ACADDXF, EC = EC_NOREAD);
					break;
				}

				if (strchr (Line, '\n') != NULL)
					iFlag = FALSE;

			}
// KK001024---------------------------------

		}

	//	Dateien schließen
		fclose (pActFile);             
		fclose (pDestFile);             

	//	ggf. Datei wieder öffnen
		if (EC_OKAY == EC)
		{
			if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_READWRITE)) < 0)
				return EC_NOFILE;
			_llseek (fh, 0L, SEEK_END);
			setmode (fh, O_TEXT);
		}
	}



//	prüfe Ergebnis des Kopierens
	if (EC_OKAY != EC)
	{
		_lclose (fh);
		return EC;
	}

	
	
//	Dateiende setzen
	if ((EC = ExportRecord (fh, 0, "EOF")) < 0) {
		_lclose (fh);
		return EC;
    }

//  Zeichnungsgrenzen ausgeben
    if ((EC = ExportExtension (fh)) < 0) {
		_lclose (fh);
		return EC;
    }

// KK000302 - Merkmal + ID -Definit. für evtl. 2te Datenquellen - DXF-Export
	bBeginn = False;

    return (ErrCode) _lclose (fh);
}
//XX	}       // extern "C"

// Ausgabe von Standard-Entity-Attributen
ErrCode ExportAttribute (int fh, AcadTyp Typ, GSTRUCT &GS)
{
    register ErrCode EC;
    double Breite;
    char Buff [LineTypeSize] = "";

    if (!pIDT)
		return EC_OKAY;

//  Layer-Name ausgeben
    StringDup LayerName (pIDT -> FindName (GS.Id), False);
    if (!LayerName)     // nicht gef. oder kein Speicher zum kopieren
	// KK001023
	//	return EC_NOMEMORY;
		return EC_NOIDDESCRIPTION;

    if ((EC = ExportRecord (fh, 8, LayerName)) < 0)
		return EC;

//  Farbe ausgeben
    wsprintf (Buff, "%6d", pIDT -> GetColor (GS));
    if ((EC = ExportRecord (fh, 62, Buff)) < 0)
		return EC;

    switch (Typ) {
		case A_PLinie:
	    	Breite = pIDT -> FindWidth (GS.Id, Typ);
		case A_PLinieClosed: {
		//  LinienTyp ausgeben
	    	if ((EC = ExportRecord (fh, 6, pIDT -> GetLineType (GS, Buff))) < 0)
				return EC;

		// Scheitelpunkte-Folgen-Flag
	    	if ((EC = ExportRecord (fh, 66, "     1")) < 0)
				return EC;
		// Polylinien-Flag: geschlossene Linie
	    	if (Typ == A_PLinieClosed)  {   // Flag bei geschl. Linie setzen
				if ((EC = ExportRecord (fh, 70, "     1")) < 0)
		    		return EC;
				Breite = pIDT -> FindWidth (GS.Id, Typ);
	    	}
		//  Linienbreite ausgeben
	    	if (Breite)  {   // nur wenn ungleich 0 ausgeben
				Breite *= StandLinBrFakt;
				if ((EC = ExportRecord (fh, 40, DtoA (Buff, "%-7.1f", Breite))) < 0)
		    		return EC;              // Anfangsbreite
				if ((EC = ExportRecord (fh, 41, DtoA (Buff, "%-7.1f", Breite))) < 0)
			    		return EC;              // Endbreite
	    	}
		}
		break;
		case A_Punkt: {
			if (!bCreateBlocks)
			{
	    		if (ValidMKodes)        // gültige Merkmalskodes
					if ((EC = ExportRecord (fh, 66, "     1")) < 0)
		    			return EC;  // Attribute-Folgen-Flag
	    		short SymbolStyle = pIDT -> FindSymbolStyle (GS.Id);
	    		if (SymbolStyle)    // wenn SymbolName OK
					return ExportRecord (fh, 2, itoa (SymbolStyle, Buff, 10));
	    		else                // sonst StandardSymbol ausgeben
					return ExportRecord (fh, 2, pStandSymbol);
			}
		}
    }
    return EC_OKAY;
}

// die zu einem Text-Objekt geh. Höhe ausgeben
ErrCode ExportTextHoehe (int fh, long ID)
{
    if (!pIDT)
		return EC_OKAY;

    double Hoehe = (double) pIDT -> FindTextHoehe (ID);
    if (Hoehe <= 0.0)          // bei ungültigem Wert
		Hoehe = StandTextHoehe;
    else
		Hoehe *= StandTextHoeFaktor;

//  Text-Hoehe ausgeben
    char Buff [10];
    return ExportRecord (fh, 40, DtoA (Buff, "%-4.2f", Hoehe));
}

// den zu einem Text-Objekt geh. Drehwinkel ausgeben
ErrCode ExportTextDrehWinkel (int fh, long ID)
{
    if (!pIDT)
		return EC_OKAY;

    double Wi = (double) pIDT -> FindTextDrehWinkel (ID);
    if (Wi == 0.0)          // bei O Grad keine Info nötig
		return EC_OKAY;
    else {
    //  Text-Drehwinkel ausgeben
		char Buff [10];         // Winkel bei TRIAS in Uhrzeigersinn !
		return ExportRecord (fh, 50, DtoA (Buff, "%-5.2f", Wi*StandTextRotFakt));
    }
}

// Das Text-Merkmal eines Text-Objektes als Text ausgeben
ErrCode ExportText (int fh, pchar pText) {
    ErrCode EC = EC_OKAY;

    if (pText && *pText) {      // wenn Merkmalswert ok
		pchar pNText = CheckUmlaute (pText);
		if (pNText == NULL)
			return EC_NOMEMORY;

	//	Steuerzeichen filtern
		short sLen = strlen (pNText) + 1;
		char *pEndText = new char [sLen];		
		if (!pEndText)
		{
			DELETE_VEC (pNText);
			return EC_NOMEMORY;
		}

		memset (pEndText, 0, sLen);
		char *pActPos = pEndText;				// absolute Zeichenposition
		for (char *pR = pNText; pR && *pR; pR++)
		{
			if ('\\' != *pR)
			{
				*pActPos++ = *pR;			// normales Zeichen
				continue;
			}
		
		//	Steuerzeichen
			if (!*++pR)						// prüfe nächste Zeichen
				break;

			*pActPos++ = ' ';				// durch Leerzeichen ersetzen

		/*
		//	was für ein Steuerzeichen folgt ?
			switch (*pR)
			{
				case 'n':
					*pActPos++ = '\n';		// durch einfachen Backslash ersetzen
				break;
				case 't':					// Tabs auflösen
					*pActPos++ = '\t';
				break;				
				case ' ':
					*pActPos++ = ' ';		// durch einfaches Leerzeichen ersetzen
				break;
				default:					// unbekanntes Steuerzeichen überlesen
				break;				
			}
		*/
		}

		EC = ExportRecord (fh, 1, pEndText);
		DELETE_VEC (pNText);
		DELETE_VEC (pEndText);
		return EC;
    } else 
		ExportRecord (fh, 1, " ");       // dummy-Text raus
		
	return EC;              
}

// Geometrieinformation ausgeben
ErrCode ExportGeometrie (int fh, GSTRUCT &GS, AcadTyp Typ, long First)
{
    register ErrCode EC;
    long Size = GS.GSize;       // Anzahl Stützpunkte

    if (!pIDT)
		return EC_OKAY;

    StringDup LayerName (pIDT -> FindName (GS.Id), False);
    if (!LayerName)         // wenn kein Speicher oder Name nicht gef.
	// KK001023
	//	return EC_NOMEMORY;
		return EC_NOIDDESCRIPTION;


    switch (Typ) {
		case A_Punkt:
		case A_Text:
		case A_Linie: {
	    	if ((EC = ExportPunkt (fh, 10, 20, GS.x[0], GS.y[0])) != EC_OKAY)
				return EC;
	    	if (Typ == A_Linie)    // dann auch noch nächsten Punkt raus
				return ExportPunkt (fh, 11, 21, ((double HUGE *)GS.x)[1], 
												((double HUGE *)GS.y)[1]);
	    	else
				return EC;
		}
		case A_PLinieClosed:
	    	--Size;             // Anfangspunkt verschieden Endpunkt
		case A_PLinie: {
	    	// alle Punkte ausgeben
	    	for (long Ind = First; Ind < (Size + First); Ind++) {
			// VERTEX-Element erzeugen
				if ((EC = ExportRecord (fh, 0, "VERTEX")) < 0)
		    		return EC;

			// Ebenen-Namen ausgeben
				if ((EC = ExportRecord (fh, 8, LayerName)) < 0)
		    		return EC;

			// Koordinaten ausgeben
				if ((EC = ExportPunkt (fh, 10, 20, ((double HUGE *)GS.x)[Ind], 
												   ((double HUGE *)GS.y)[Ind])) != EC_OKAY)
		    		return EC;
	    	}

	    	// abschließende Infos raus
	    	if ((EC = ExportRecord (fh, 0, "SEQEND")) < 0)
				return EC;
	    	if ((EC = ExportRecord (fh, 8, LayerName)) < 0)
				return EC;
		}
		break;
    }

    return EC_OKAY;
}

ErrCode ExportPunkt (int fh, int GKx, int GKy, double X, double Y)
{
// KK000613
//    pchar pFormat = "%-10.4f";
    pchar pFormat = "%-16.8f";
   char Buff [20];
    register ErrCode EC;

//    X *= dDiv;        // Koordinaten transformieren
//    Y *= dDiv;

    SetXCon (X);        // min. und max. Bildgröße
    SetYCon (Y);        // ggf. Korrigieren

    if ((EC = ExportRecord (fh, GKx, DtoA (Buff, pFormat, X))) < 0)
		return EC;

    return ExportRecord (fh, GKy, DtoA (Buff, pFormat, Y));
}

ErrCode ExportHeaderSection (int fh)
{
    register ErrCode EC;

    if ((EC = ExportRecord (fh, 0, "SECTION")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 2, "HEADER")) < 0)
		return EC;

//  AutoCAD-Version
    if ((EC = ExportRecord (fh, 9, "$ACADVER")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 1, AcadVersion)) < 0)
		return EC;

//  Darstellungs-Modi für Attribute
    if ((EC = ExportRecord (fh, 9, "$ATTMODE")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 70, "     1")) < 0)  // normal
		return EC;

//  akt. Datei-Position merken
    DummyPos = _llseek (fh, 0L, SEEK_CUR);

//  Dummy-Zeichen schreiben
    short Length = DummyLength - 5 + 1;
    pchar pDummy = new char [Length];
    if (!pDummy)
		return EC_NOMEMORY;
    memset (pDummy, ' ', Length - 1);
    pDummy [Length - 1] = '\0';

//  Dummy-Text ausgeben
    if ((EC = ExportRecord (fh, 9, pDummy)) < 0)
		return EC;

    DELETE_VEC (pDummy);

//  akt. Layer-Namen ausgeben
    if ((EC = ExportRecord (fh, 9, "$CLAYER")) < 0)
		return EC;

//  ID mit höchster Priorität wird aktuelle Layer
    StringDup LastLayerName (pIDT -> FindName (LastID), False);
    if (!LastLayerName)
	// KK001023
	//	return EC_NOMEMORY;
		return EC_NOIDDESCRIPTION;

    if ((EC = ExportRecord (fh, 8, LastLayerName)) < 0)
		return EC;

//  akt. Lin.-Typ-Info raus
    if ((EC = ExportRecord (fh, 9, "$CELTYPE")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 6, "BYLAYER")) < 0)
		return EC;

//  akt. Farbe raus
    if ((EC = ExportRecord (fh, 9, "$CECOLOR")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 62, "   256")) < 0)
		return EC;

//  akt. Name des Textstils
    if ((EC = ExportRecord (fh, 9, "$TEXTSTYLE")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 7, "STANDARD")) < 0)
		return EC;

//  Header-Ende
    if ((EC = ExportRecord (fh, 0, "ENDSEC")) < 0)
		return EC;
		
	return EC;              
}

ErrCode ExportLineTable (int fh)
{
    if (OutputResourceTemplate (LINE_TABLE, fh))
		return EC_OKAY;
    else
		return EC_NOLINETABLE;
}

ErrCode ExportVisInfoTemplate (int fh)
{
    if (OutputResourceTemplate (VIS_INFO_TABLE, fh))
		return EC_OKAY;
    else
		return EC_NOVISINFOTEMPLATE;
}

ErrCode ExportExtension (int fh)
{
    pchar pFormat = "%20.6f";
    char Buff [DummyKoOrdSize + 1];
    register ErrCode EC;

    _llseek (fh, DummyPos, SEEK_SET);       // auf Dummy-Position


//  Ausdehnungen ausgeben: min. Ext.
    if ((EC = ExportRecord (fh, 9, "$EXTMIN")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 10, DtoA (Buff, pFormat, XMin))) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 20, DtoA (Buff, pFormat, YMin))) < 0)
		return EC;

//  max. Ext.
    if ((EC = ExportRecord (fh, 9, "$EXTMAX")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 10, DtoA (Buff, pFormat, XMax))) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 20, DtoA (Buff, pFormat, YMax))) < 0)
		return EC;

//  Abmaße korrigieren
    double dX = (XMax - XMin) * KorrFakt;
    double dY = (YMax - YMin) * KorrFakt;
    XMin -= dX;
    YMin -= dY;
    XMax += dX;
    YMax += dY;

//  Grenzen ausgeben: min. Lim.
    if ((EC = ExportRecord (fh, 9, "$LIMMIN")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 10, DtoA (Buff, pFormat, XMin))) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 20, DtoA (Buff, pFormat, YMin))) < 0)
		return EC;

//  max. Lim.
    if ((EC = ExportRecord (fh, 9, "$LIMMAX")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 10, DtoA (Buff, pFormat, XMax))) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 20, DtoA (Buff, pFormat, YMax))) < 0)
		return EC;

    _llseek (fh, 0L, SEEK_END);     // auf Dateiende

    return EC;
}

// AutoCad-Rekord schreiben
ErrCode ExportRecord (int fh, int GruppenKode, const char *pGruppenWert)
{
   char Buff [6];

//      Ausgabe des GruppenKodes
    wsprintf (Buff, "%3d\r\n", GruppenKode);
    if (_lwrite (fh, Buff, 5) != 5)
		return EC_NOSPACE;

// Ausgabe des GruppenWertes
    if (pGruppenWert) {
		register short Len = lstrlen (pGruppenWert);
		if ((short) _lwrite (fh, (pchar) pGruppenWert, Len) != Len)
			return EC_NOSPACE;
    }

// NewLine ausgeben
    lstrcpy (Buff, "\r\n");
    if (_lwrite (fh, Buff, 2) != 2)
		return EC_NOSPACE;

	return EC_OKAY;
}

// Zeile schreiben
ErrCode ExportLine (int fh, const char *pText)
{
   char Buff [3] = "";

//      Zeile ausgeben
    if (pText) {
		register short Len = lstrlen (pText);
		if ((short) _lwrite (fh, pText, Len) != Len)
			return EC_NOSPACE;
    }

//      NewLine ausgeben
    lstrcpy (Buff, "\r\n");
    if (_lwrite (fh, Buff, 2) != 2)
		return EC_NOSPACE;

    return EC_OKAY;
}

//XX	extern "C" {
// Ausgabe eines Geometrie-Objektes mit Merkmalsinformationen --------------------
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, char *)
/*XX*/	ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, LPCTSTR pUniqueIdent, LPCTSTR lpszGUID, LPCTSTR lpszParentClass)
{
    char outBuff [10] = "";
    int fh = 0;                     // Daten-File-Handle
    AcadTyp Typ;                // AutoCAD-Typ
    long *pCount = GS.cnt;      // Anzahl der Stützpunkte in Konturen
    if (!pIDT)
		return EC_OKAY;

//  DXF-Datei öffnen
    if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_READWRITE)) < 0)
		return EC_NOFILE;
    _llseek (fh, 0L, SEEK_END);
    setmode (fh, O_TEXT);

    register ErrCode EC = EC_OKAY;


    if (FirstData) {
		FirstData = False;
		if ((EC = ExportBeforeFirstData (fh)) != EC_OKAY)
	    	return EC;
    } 
	/*XX*/	ULONG	ulIdent = 0;
	/*XX*/	if( FAILED(IdentFromClassX (hDatasource, lpszParentClass, &ulIdent, false ) ) )
	/*XX*/		return EC_SYSERROR;
	/*XX*/	GS.Id = ulIdent;

//  prüfe Geometrie
    Bool Check = True;
    switch (GS.Typ) {
		case OT_PUNKT: {
	    	if (GS.GSize != 1) {
				Check = False;                            
				OutputWarnung (IDS_NOPOINT, GS.Id, GS.ON);
			break;
	    	}
	    	Typ = A_Punkt;
			if (bCreateBlocks)
				lstrcpy (outBuff, "POINT");
			else
	    		lstrcpy (outBuff, "INSERT");
		}
		break;
		case OT_KANTE:  {
	    	if (GS.GSize < 2) {
				Check = False;  
				OutputWarnung (IDS_NOLINE, GS.Id, GS.ON);
				break;
	    	}

	    	Typ = A_PLinie;
	    	lstrcpy (outBuff, "POLYLINE");
		} 
		break;
		case OT_FLAECHE: {
	    	long Idx = 0;
	    	for (long *pCnt = GS.cnt; *pCnt; pCnt++) {
				if  (*pCnt < 4 ||
		    		(((double HUGE *)GS.x)[Idx] != ((double HUGE *)GS.x)[Idx+*pCnt-1]) ||
		    		(((double HUGE *)GS.y)[Idx] != ((double HUGE *)GS.y)[Idx+*pCnt-1])) {
		    		Check = False; 
		    		OutputWarnung (IDS_NOAREA, GS.Id, GS.ON);
		    	break;
				}
				Idx += *pCnt;
	    	}
	    	if (!Check)
				break;

	    	Typ = A_PLinieClosed;
	    	lstrcpy (outBuff, "POLYLINE");
	    	GS.GSize = *pCount;     // Anzahl der Stützpunkte der äußeren Fl.
		}
		break;
		case OT_TEXT: {
	    	if (GS.GSize != 1) {
				Check = False; 
				OutputWarnungIdent (IDS_NOTEXT, GS.Id, GS.ON);
			break;
	    	}
	    	Typ = A_Text;
	    	lstrcpy (outBuff, "TEXT");
		}
		break;
		default:
	    	Check = False;
    }

//  Objekt-Geometrie OK ?
    if (! Check) {
		_lclose (fh);
		return WC_UNKOBJECTTYP;     // unbekanntes Objekt
    }

//	bei Blockerzeugung: Blockanfang
	if (bCreateBlocks)	
	{

// KK000314
// Tausch Layer gegen Blockanfang
	//  Layer-Namen ausgeben
		StringDup LayerName (pIDT -> FindName (GS.Id), False);
		if (!LayerName)
		{
			_lclose (fh);
		// KK001023
		//	return EC_NOMEMORY;
			return EC_NOIDDESCRIPTION;
		}	
		
	//	Blockanfang		
		if ((EC = ExportRecord (fh, 0, "BLOCK")) < 0)
		{
			_lclose (fh);
			return EC;
		}


		if ((EC = ExportRecord (fh, 8, LayerName)) < 0)
		{
			_lclose (fh);
			return EC;
		}

	//	Blockname
		char BlockBuffer [20] = "";
		if ((EC = ExportRecord (fh, 2, ltoa (g_lBlockNummer, BlockBuffer, 10))) < 0)
		{
			_lclose (fh);
			return EC;
		}
		g_lBlockNummer++;

	//  Attribute-Folgen-Flag setzen
		if ((EC = ExportRecord (fh, 70, (ValidMKodes) ? "    2" : "     0")) < 0)
		{
			_lclose (fh);
			return EC;
		}

	//	Block-Basis-Punkt: X
		if ((EC = ExportRecord (fh, 10, "0.0")) < 0)
		{
			_lclose (fh);
			return EC;
		}
		
	//	Y
		if ((EC = ExportRecord (fh, 20, "0.0")) < 0)
		{
			_lclose (fh);
			return EC;
		}		

	//	Insert-Eintrag ausgeben 
		if ((EC = ExportRecord (g_ifh, 0, "INSERT")) < 0)
		{
			_lclose (fh);
			return EC;
		}		

		if ((EC = ExportRecord (g_ifh, 8, LayerName)) < 0)
		{
			_lclose (fh);
			return EC;
		}

	//	ggf. Attribute-Folgen-Flag
		if (ValidMKodes && MF)
		{
			if ((EC = ExportRecord (g_ifh, 66, "1")) < 0)
			{
				_lclose (fh);
				return EC;
			}
		}

	//	Blocknamen ausgeben
		if ((EC = ExportRecord (g_ifh, 2, BlockBuffer)) < 0)
		{
			_lclose (fh);
			return EC;
		}

	//	Insert-Punkt: X
		if ((EC = ExportRecord (g_ifh, 10, "0.0")) < 0)
		{
			_lclose (fh);
			return EC;
		}
		
	//	Y
		if ((EC = ExportRecord (g_ifh, 20, "0.0")) < 0)
		{
			_lclose (fh);
			return EC;
		}		
	}
	
//  Entity-Kopf ausgeben
	if ((EC = ExportRecord (fh, 0, outBuff)) < 0) 
	{
		_lclose (fh);
		return EC;
	}

//  Entity-Attribute ausgeben
    if ((EC = ExportAttribute (fh, Typ, GS)) < 0) {
		_lclose (fh);
		return EC;
    }

//  Geometrieinformation ausgeben
    if ((EC = ExportGeometrie (fh, GS, Typ)) < 0) {
		_lclose (fh);
		return EC;
    }

	if (!bCreateBlocks)
	{		
	//  bitte Punkt-Merkmale und ggf. Drehwinkel zusätzlich ins DXF-File ausgeben
		if (Typ == A_Punkt) 
		{
			if ((EC = pIDT -> OutputSymAttrs (fh, GS.Id)) < 0)
			{
				_lclose (fh);
	    		return EC;      // ID-bezogenen Symbol-Drehwinkel ausgeben
			}
			if ((EC = pMDT -> OutputAttrVal (fh, GS, MF)) < 0) 
			{
	    		_lclose (fh);
	    		return EC;
			}
		}
    }

//  bei Text-Objekt dessen spezifische Attribute ausgeben
    if (Typ == A_Text)  {
		pchar pText = MF -> MText;                // auf Standardwert setzen
		while (MF -> MCode) {
	    	if (MF -> MCode == StandTextMKode) {  // wenn Kode gef.
				pText = MF -> MText;              // dessen Wert ist Textwert
				break;
	    	}
	    	MF++;
		}
		SetMaxTextLen (pText ? lstrlen (pText) : 0);
		if ((EC = ExportTextHoehe (fh, GS.Id)) < 0) {
	    	_lclose (fh);
	    	return EC;
		}
		if ((EC = ExportText (fh, pText)) < 0) {
	    	_lclose (fh);            // DXF-File
	    	return EC;
		}
		if ((EC = ExportTextDrehWinkel (fh, GS.Id)) < 0) {
	    	_lclose (fh);
	    	return EC;
		}
    }

//  berarbeite evtl. Innenflächen einer Fläche
    if (Typ == A_PLinieClosed) {
		long AktIndex = *pCount;

    // für alle Teilflächen
		for (pCount++; *pCount; pCount++) {

		// Entity-Kopf ausgeben
	    	if ((EC = ExportRecord (fh, 0, outBuff)) < 0) {
				_lclose (fh);
				return EC;
	    	}

		// Entity-Attribute ausgeben
	    	if ((EC = ExportAttribute (fh, Typ, GS)) < 0) {
				_lclose (fh);
				return EC;
	    	}
	    	GS.GSize = *pCount;

		// Geometrieinformation ausgeben
	    	if ((EC = ExportGeometrie (fh, GS, Typ, AktIndex)) < 0) {
				_lclose (fh);
				return EC;
	    	}

	    	AktIndex += *pCount;
		}   // end_for
    }       // end_if

//	ggf. Merkmale und Blockende ausgeben
	if (bCreateBlocks)	
	{
	//  Attribut-Definitionen in normale Datei ausgeben
		if (ValidMKodes && pMDT)
		{
			if ((EC = pMDT -> OutputAttrDef (fh, MF)) < 0)
			{
				_lclose (fh);
				return EC;
			}

		//	Merkmale in INSERT-Datei
			if ((EC = pMDT -> OutputAttrVal (g_ifh, GS, MF)) < 0) 
			{
	    		_lclose (fh);
	    		return EC;
			}
		}
	
	//	Blockende in normale Datei ausgeben
		if ((EC = ExportRecord (fh, 0, "ENDBLK")) < 0)
		{
			_lclose (fh);
			return EC;
		}
	}

    return (ErrCode) _lclose (fh);
}
//XX	}       // extern "C"

//------------------------------------------------------------------------
// Vor dem erstmaligen Datenausgeben Header u.a. Infos ausgeben
ErrCode ExportBeforeFirstData (int fh)
{
    register ErrCode EC = EC_OKAY;      

//  alle Layernamen auf richtige Zeichen prüfen u. ggf. begrenzen
   if (!pIDT -> CheckLayerNames ())
		return EC_NOMEMORY;

//  Baum optimieren
    pIDT -> Optimiere ();           // Baum und interne Variablen optimieren

//  Schreibe Header-Section
    if ((EC = ExportHeaderSection (fh)) < 0) {
		_lclose (fh);
		if ( EC == EC_NOIDDESCRIPTION) {
			ResString resQuestion (ResID (IDS_ERRNOIDENT, pRF), 80);
			ResString resFilter (ResID (IDS_AUTOCAD_CAPTION, pRF), 80);

			::MessageBox (__hWndM, resQuestion.Addr(), resFilter.Addr(), 
							   MB_ICONQUESTION | MB_OK);
			EC = EC_USERBREAK;			// Abbruch
		}
		return EC;
    }
//*-------------hier mal nicht
//  Table-Section-Beginn
    if ((EC = ExportRecord (fh, 0, "SECTION")) < 0) {
		_lclose (fh);
		return EC;
    }
    if ((EC = ExportRecord (fh, 2, "TABLES")) < 0) {
		_lclose (fh);
		return EC;
    }

//  Schreibe Table-Section
    if ((EC = ExportLineTable (fh)) < 0) {
		_lclose (fh);
		return EC;
    }

//  VisInfo-Template-Datei öffnen
    int v_fh = 0;
    if ((v_fh = OpenFile (NULL, pVisInfoTemplStruct,
			  OF_REOPEN+OF_WRITE)) < 0) {
		_lclose (fh);
		return EC_NOFILE;
    }
    setmode (v_fh, O_TEXT);

//  VisInfo-Template-Datei schreiben
    if ((EC = ExportVisInfoTemplate (v_fh)) < 0) {
		_lclose (fh);
		_lclose (v_fh);
		return EC;
    }

    _lclose (v_fh);

//  VisInfo-Datei öffnen
    int cfh = 0;
    if ((cfh = OpenFile (NULL, pColFileStruct, OF_REOPEN+OF_WRITE)) < 0) {
		_lclose (fh);
		return EC_NOFILE;
    }
    setmode (cfh, O_TEXT);

//  Layer-Section schreiben
    if ((EC = pIDT -> OutputLayerTable (fh, cfh)) < 0) {
		_lclose (cfh);
		_lclose (fh);
		return EC;
    }
    _lclose (cfh);

//  Table-Section-Ende
    if ((EC = ExportRecord (fh, 0, "ENDSEC")) < 0) {
		_lclose (fh);
		return EC;
    }
//-------------------------------------*/

//  Block-Section ausgeben
    if ((EC = ExportBlocksSection (fh)) != EC_OKAY)
		return EC;

//  Entity-Section-Beginn in richtige Datei ausgeben
	int _fh = bCreateBlocks ? g_ifh : fh;

	if ((EC = ExportRecord (_fh, 0, "SECTION")) < 0) {
		_lclose (fh);
		return EC;
    }
    if ((EC = ExportRecord (_fh, 2, "ENTITIES")) < 0) {
		_lclose (fh);
		return EC;
    }

   return EC;
}
//---------------------------------------------------------------------------------
//XX	extern "C" {
// Nutzer-Abbruch: Alle erzeugten Dateien löschen !
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportBreak (OFSTRUCT &of)
/*XX*/	ErrCode ExportBreak (OFSTRUCT &of)
{
//  DXF-Datei
    remove (of.szPathName);

//  Visualisierungs-Dateien
    remove (pColFileStruct -> szPathName);
    remove (pVisInfoTemplStruct -> szPathName);

    return EC_OKAY;
}
//XX	}       // extern "C"

// Blocks-Section ausgeben
ErrCode ExportBlocksSection (int fh) {

    register ErrCode EC = EC_OKAY;

//  Section-Beginn ausgeben
    if ((EC = ExportRecord (fh, 0, "SECTION")) < 0) {
		return EC;
    }
    if ((EC = ExportRecord (fh, 2, "BLOCKS")) < 0) {
		return EC;
    }

//	hier nur den Anfang der Section ausgeben
	if (bCreateBlocks)
		return EC;

//  Standard-Symbol ausgeben
    if ((EC = ExportRecord (fh, 0, "BLOCK")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 8, "0")) < 0)
		return EC;

//  Blockname
    if ((EC = ExportRecord (fh, 2, pStandSymbol)) < 0)
		return EC;

//  Attribute-Folgen-Flag setzen
    if ((EC = ExportRecord (fh, 70, (ValidMKodes) ? "     2" : "     0")) < 0)
		return EC;

//  Symbol-Körper ausgeben
    if (! OutputResourceTemplate (ST_SYMBOL, fh))
		return EC_NOSYMBOL;

//  Attribut-Definitionen ausgeben
    if (ValidMKodes && pMDT)
	{
		if ((EC = pMDT -> OutputAttrDef (fh, NULL)) < 0)
			return EC;
	}

    if ((EC = ExportRecord (fh, 0, "ENDBLK")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 8, "0")) < 0)
		return EC;

//  alle Symbole ausgeben
    if (!pIDT || (pIDT -> OutputSymbole (fh, atoi (pStandSymbol), NULL) != EC_OKAY))
		return EC_NOSYMBOL;

//  Section-Ende ausgeben
    if ((EC = ExportRecord (fh, 0, "ENDSEC")) < 0) {
		return EC;
    }
    return EC;
}

//XX	extern "C" {
//  Export beenden
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportEnd (OFSTRUCT &) 
/*XX*/	ErrCode ExportEnd (OFSTRUCT &) 
{
//	Insert-Datei immer löschen
	if (g_ifh > 0)			//	Datei schließen
		_lclose (g_ifh);
	if (pInsertStruct && pInsertStruct -> szPathName)
		remove (pInsertStruct -> szPathName);

	DELETE_OBJ (pIDT);                  // ID-Beschr.-Baum löschen
    DELETE_OBJ (pColFileStruct);        // File-Struktur für VisInfo-Tabelle
    DELETE_OBJ (pVisInfoTemplStruct);   // File-Struktur für VisInf-Template löschen
    DELETE_OBJ (pRF);                   // ResourceFile
    DELETE_OBJ (pMDT);                  // Merkmals-Beschreibungs-Baum löschen
	DELETE_OBJ (pInsertStruct);			// Insert-Sruct
    DeletePalette ();					// Farbpalette freigeben

	/*XX*/	hDatasource = NULL;

    return EC_OKAY;
}

/*XX*/	ErrCode ExportMerkmalDescription (long lMCode, char *pbuf,short locMTyp, short iLen)
{
	if (!bBeginn )
		ShortBeginn();

	MerkmalDescription MD (DEX_MapHandleToMCode(lMCode), pbuf, 
			   locMTyp, iLen);
	return ExportMerkmalDescriptions (MD);
}
//XX	ErrCode EXPORTFLT PASCAL AcadDxfExportMerkmalDescription (MerkmalDescription &MD)
//*XX*/	ErrCode AcadDxfExportMerkmalDescription (MerkmalDescription &MD)
/*XX*/	ErrCode ExportMerkmalDescriptions (MerkmalDescription &MD)
{
    Bool OK = True;
    switch (toupper (MD.MTyp ())) {
		case 'A':           // ASCII
		case 'I':           // Integer
		case 'F':           // Float
	    	OK = True;
		break;
		case 'B':           // Sicht-Merkmal
		case 'C':           // Id-Merkmal
	    	return EC_OKAY;     // werden nicht exportiert
		break;
		default:                                   
			uint rid = DEX_GetMkBase () == 10 ? IDS_MERKMWARNGTYP
											  : IDS_MERKMWARNGTYPX;
	    	return OutputWarnung (rid, MD.MCode ());
		break;
    }

//  prüfe Text-Zeiger und Länge
	if (MD.MLen () == 0)
		return EC_OKAY;			// diese Merkmale nicht ausgeben

//    if (!pMDT)
//		return EC_SYSERROR;

	if (!pMDT) {
		pMDT = new ExtMerkmalDescriptionTree ();
	}

    return pMDT -> AddMerkmDescr (MD) ? EC_OKAY : EC_NOMEMORY;
}
//XX	}       // extern "C"
//---------------------------------------------------------------
//---------------------------------------------------------------
ErrCode ShortEnd (void)
{

	OFSTRUCT of;
	ErrCode EC = ExportEnd(of);

	StandTextMKode = 0L;                       // Merkmalskode eines Textwertes
	g_ifh = 0;									// FileHandle auf INSERT-Datei
	g_lBlockNummer = 1;						// akt. Blocknummer

	Punkte = 0;                                // Elementezähler
	Linien = 0;
	DummyPos = 0;                              // Header-Einfüge-Punkt
	LastID = 0;
	XMin = DBL_MAX;                          // kleinste u. größte Koordinate
	YMin = DBL_MAX;
	XMax = 0;
	YMax = 0;
// KK000229
	bBeginn = False;							// Erstabfrage

//	bCreateBlocks = False;						// Block für jedes Objekt erzeugen

	AlleMerkmale = False;                      // nicht alle Merkmalse exportieren
	FirstData = True;                          // erstmaliges Daten-Ausgeben
	ValidMKodes = False;                       // Keine gültigen Merkmals-Kodes
	MaxTextLen = 0;                           // Maximale Länge eines Textobjektes
	SymbolWarnung = False;						// noch keine Warnung ausgegeben
	return EC_OKAY;

}
//---------------------------------------------------------------
ErrCode ShortBeginn (void)
{
	if (bBeginn )
		return EC_OKAY;

	ErrCode EC = ShortEnd();

    char Drive[_MAX_DRIVE], Dir[_MAX_DIR];
    char FName[_MAX_FNAME], Ext[_MAX_EXT];

//  Resource-File-Objekt init.
	if ( !pRF)
	    pRF = new ResourceFile ((char *) pDLLName);
    if (!pRF)
		return EC_NOMEMORY;

    ValidMKodes = False;                 // Keine gültigen MerkmalKodes

//  Ini-Datei-Namen bilden: nur vollständigen Dateinamen !
    _splitpath (pDLLName, Drive, Dir, FName, Ext);
    lstrcpy (pIniFilePath, FName);
    lstrcat (pIniFilePath, IniFileExt);

    char Buffer [81] = "";
    double Val;

//  Abschnitt Merkmalsexport: alle Merkmale exportieren ?
    AlleMerkmale = False;
    ResString RS (ResID (IDS_MERKMALSEXPORTSEC, pRF), 80);
    ResString RS1 (ResID (IDS_STANDARDSTRING, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    RS1 = ResString (ResID (IDS_ALLEVAL, pRF), 10);
	    if (! lstrcmp (RS1.Addr (), strupr (Buffer)))
			AlleMerkmale = True;
    }


//  Merkmalskode für Textwert lesen
    _GetTextObjKode ();

	hDatasource = DEX_GetDataSourceHandle();


	ResString resQuestion (ResID (IDS_CREATE_BLOCKS, pRF), 80);
	ResString resFilter (ResID (IDS_AUTOCAD_CAPTION, pRF), 80);

// KK001020
	if ( !bIsCreateBlocks) {	// Noch nicht gefragt !!!


		if (IDYES == ::MessageBox (__hWndM, resQuestion.Addr(), resFilter.Addr(), 
							   MB_ICONQUESTION | MB_YESNO))
		{
			bCreateBlocks = True;
			AlleMerkmale = TRUE;
			bIsCreateBlocks = TRUE;	// KK001020
		} else {
			bCreateBlocks = FALSE;
		}
	} else {
		bCreateBlocks = True;
		AlleMerkmale = TRUE;
	}

//  Symbolgroessen-Faktor für Skalierung
    double SymGroesse = StandardSymGroesse;	

    RS1 = ResString (ResID (IDS_STSYMGROESSE, pRF), 80);
    if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
	    Val = atof (Buffer);
	    if (Val)                            // wenn gültiger Wert,
			SymGroesse = Val;               // dann übernehmen
    }

	if ( pIDT) 
		DELETE_OBJ(pIDT);
	if ( !pIDT )
	   pIDT = new ExtIdentDescriptionTree (SymGroesse);

	if ( pMDT) 
		DELETE_OBJ(pMDT);
	if (!pMDT) 
		pMDT = new ExtMerkmalDescriptionTree ();

	bBeginn = TRUE;

	return EC_OKAY;
}
//--------------------------------------------------------------
ErrCode OutputWarnungIdent (short ResourceId, long Id, long ObjNr) {
    if (!pRF)
       return EC_SYSERROR;

    Window *pParent = (Window *) SendMessage (__hWndM, __DexxCmd,
					      DEXX_MAINWINDOW, 0L);
    if (!pParent)
		return EC_NODEXMESSAGE;

    ResString Caption (ResID (IDS_WARNUNG, pRF), 20);
    ResString TextFormat (ResID (ResourceId, pRF), 90);
    char Buffer [120] = "";
	char tBuffer [30] = "";
	ClassFromIdentX (Id, tBuffer, False);
    if (ObjNr)
		wsprintf (Buffer, TextFormat.Addr (), tBuffer, ObjNr);
    else
		wsprintf (Buffer, TextFormat.Addr (), tBuffer);
    MessBox MB (Caption.Addr (), Buffer, pParent);
    MB.SetType (OkayButton | ExclamationIcon);
    MB.Show ();
    return EC_OKAY;
}

ErrCode OutputWarnung (short ResourceId, long Value, long ObjNr) {
    if (!pRF)
       return EC_SYSERROR;

    Window *pParent = (Window *) SendMessage (__hWndM, __DexxCmd,
					      DEXX_MAINWINDOW, 0L);
    if (!pParent)
		return EC_NODEXMESSAGE;

    ResString Caption (ResID (IDS_WARNUNG, pRF), 20);
    ResString TextFormat (ResID (ResourceId, pRF), 90);
    char Buffer [120] = "";
	char tBuffer [30] = "";
	if (ObjNr)
		wsprintf (Buffer, TextFormat.Addr (), Value, ObjNr);
    else
		wsprintf (Buffer, TextFormat.Addr (), Value);
    MessBox MB (Caption.Addr (), Buffer, pParent);
    MB.SetType (OkayButton | ExclamationIcon);
    MB.Show ();
    return EC_OKAY;
}

//  Merkmalskode für Textwert lesen
void _GetTextObjKode (void) {
//  Variablen init.
    char Kode [20] = "";
    GEODBHDRENTRY Entry;
    Entry.dwSize = sizeof (GEODBHDRENTRY);
    Entry.lphdrText = Kode;
    Entry.hdrTextLen = sizeof (Kode);
    short KeySize = sizeof (Entry.hdrKey);
    ResString KeyRes (ResID (IDS_TEXTOBJMKODE, pRF), KeySize);
    lstrcpy (Entry.hdrKey, KeyRes.Addr ());
    short i = lstrlen (Entry.hdrKey);
    for (; i < KeySize; i++)     // Key mit ' ' auffüllen
		Entry.hdrKey [i] = ' ';

//  Kode von TRIAS lesen
    DEX_ReadGeoDBHdrEntry (Entry);
    if (Kode [0] && atol (Kode))
		StandTextMKode = atol (Kode);
    else
		StandTextMKode = 0L;
}

//  - deutsche Umlaute und "ß" ersetzen
//  - Zeiger auf neuen Namen liefern (muß über delete freigegeben werden)
// KK001009 - Ergänzung : DXF mag "_" und " " nicht
pchar CheckUmlaute (pchar pName) {
//  Parameter prüfen
    if (!pName)
		return NULL;

    short MaxSize = lstrlen (pName);

//  Puffer für Dateinamen anfordern
    pchar pOldName = new char [MaxSize + 1];
    if (!pOldName)
		return NULL;
    lstrcpy (pOldName, pName);

//  Zielpuffer anfordern, Platz für Umlautekonvertierung
    pchar pNewName = new char [(2 * MaxSize) + 1];
    if (!pNewName) {
		DELETE_OBJ (pOldName);
		return NULL;
    }
    *pNewName = '\0';

//  Zeiger merken
    pchar pNewNameSave = pNewName;
    pchar pOldNameSave = pOldName;

//  deutsche Umlaute und "ß" ersetzen
    while (*pOldName) {
		switch (*pOldName) {
	    	case 'á':
				*pNewName++ = 's';
				*pNewName = 's';
	    	break;
	    	case '„':
				*pNewName++ = 'a';
				*pNewName = 'e';
	    	break;
	    	case 'Ž':
				*pNewName++ = 'A';
				*pNewName = 'e';
	    	break;
	    	case '':
				*pNewName++ = 'u';
				*pNewName = 'e';
	    	break;
	    	case 'š':
				*pNewName++ = 'U';
				*pNewName = 'e';
	    	break;
	    	case '”':
				*pNewName++ = 'o';
				*pNewName = 'e';
	    	break;  	
	    	case '™':
				*pNewName++ = 'O';
				*pNewName = 'e';
	    	break;
	    	default:
				*pNewName = *pOldName;
		}

		pNewName++;
		pOldName++;
    }   // end while

    *pNewName = '\0';                    // akt. Ende setzen
    DELETE_OBJ (pOldNameSave);               // alten Puffer löschen

    return pNewNameSave;                 // mit neuem Puffer zurück
}
