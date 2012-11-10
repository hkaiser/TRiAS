/*
File: TRIASARC.CXX

Hauptmodul des TRIAS-Arc/Info-Konverters.

Erarbeitet: J. Benkenstein                                Begonnen am: 30. April 1993
														  Stand vom: 18. August 1994
*/

#include "stdafx.h"       
        
#include "TRiASArcImpl.h"
 
extern "C" {
	#include <io.h>          	// setmode ()
	#include <fcntl.h>       	// O_TEXT
	#include <ctype.h>       	// topupper ()
	#include <xtensnxx.h>   	// DEXX_MAINWINDOW
}

#include <attribs.hxx>    		// VisInfo ...
#include <impexp.hxx>      		// MF, GS ...
#include <resstrg.h>            // Resourcen-Defines

#include "merkmdes.hxx"  		// ExtMerkmalDescriptionTrre
#include "ident.hxx"            // ExtIdentDescriptionTree

// KK000330
#include "e00compr.h"			// Komprimierung


//XX#include "triasarc.hr"      		// Resourcen-Defines           
#include "triasarc.hxx"  		// zugeh. Header

// Konstanten                                                  
const char ObjKlasseTyp = 'A';				// Zeichenkette

//  globale Variablen
HWND __hWndM;
UINT __DexCmd;
extern "C" {
UINT __DexxCmd;
}

long ObjKlasseMK = 0;						// von TRIAS vergebener Merkmalskode für Objekt-Klasse
/*XX*/	long MkBase = 0;
/*XX*/	HPROJECT	hDatasource;			// Handle der aktuellen Datenquelle
double Masstab = 0.0;                 		// aktueller Maßstab

// KK000307
Bool bBeginn = False;							// Erstabfrage


Bool FirstData = True;
Bool TextExist = False;                     // es ex. keine Text-IDs
Bool PolyExist = False;                     // es ex. keine Flächen-IDs
Bool Insel = True;							// Insel separat export.
Bool FourCoverages = FALSE;					// Standard: immer Ausgabe eines Covers pro ID

// KK000330
int nComprLevel = E00_COMPR_NONE;			// Komprimierungsart
char *pSourceFileName = NULL;				// gewählter AusgabeFilename
char *pTempFileName = NULL;					// temporärer File
int pTempFile;

ResourceFile *pRF = NULL;
ExtIdentDescriptionTree *pIDT = NULL;
ExtMerkmalDescriptionTree *pMDT = NULL;
long StandTextMKode = 0L;                   // Merkmalskode eines Textwertes
short g_sTextTruncCnt = 0;					// Zähler für abgeschn. Texte	

//  externe Variablen
extern "C" {
extern char pDLLName [_MAX_PATH];           // Puffer fnr DLL-Name
}

//  Prototypen
ErrCode ExportLineCR (int FileHandle, pchar pLine); // Zeile in Datei mit
													// abschließendem \r\n ausgeben
ErrCode ExportLine (int FileHandle, pchar pLine); // Zeile in Datei ausgeben
ErrCode OutputWarnung (short ResourceId, long Value); // Warnung ausgeben
void _GetTextObjKode (void);            // Merkmalskode fnr Textanbindung lesen

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
//XX	//XX	return DEX_GetClassFromIdent(CFI);
//XX		return DEX_GetClassFromIdentEx(hDatasource,CFI);
//XX	}
//XX	
//XX	HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew /*=false*/)
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

//XX extern "C" {    // alle exportierten Funktionen sollen _pascal sein

static ErrCode EC = EC_OKAY;

// Beginn des DatenExports ------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd) {
ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd, const char* lpszDatasource ) {
//  globale Variablen init.
	__hWndM = hWnd;
	int fh;

// KK010322
	hDatasource = DEX_GetDataSourceHandleEx( lpszDatasource );


// KK000216
    if (OutFlag == OMConcatinate) { 
		if (nComprLevel != E00_COMPR_NONE) {			// Komprimierungsart
			if ((fh = OpenFile (pTempFileName, &of, OF_WRITE)) < 0)
				return EC_NOFILE;
//			_lclose (fh);
		} else {
			if ((fh = OpenFile (lpFileName, &of, OF_WRITE)) < 0)
				return EC_NOFILE;
		}
// KK000403
		_lclose (fh);

		FirstData = False;
	    return EC_OKAY;
	}

// KK000405 - in ShortBeginn
/*-------------------------------------------------------
	Insel = True;						// Inseln separat exportieren
	FirstData = True;
	PolyExist = TextExist = False;		// es ex. keine Flächen/Text-IDs
	ObjKlasseMK = DEX_GetUniqueMCode ();					// von TRIAS vergebener Merkmalskode für Objekt-Klasse
	MkBase = DEX_GetMkBase ();			// Zahlenbasis für MCodes
	FourCoverages = FALSE;				// Standard: immer Ausgabe eines Covers pro ID
	StandTextMKode = 0L;                // Merkmalskode eines Textwertes
	g_sTextTruncCnt = 0;				// Zähler für abgeschn. Texte
	_ASSERTE( NULL == hDatasource);
---------------------------------------*/

// KK010322
//	hDatasource = DEX_GetDataSourceHandleEx( lpszDatasource );


// KK000307
//	pIDT = NULL;
//	pMDT = NULL;

//	pRF = NULL;

	Masstab = 0.0;          

	EC = EC_OKAY;

//  Resource-File-Objekt init.
// KK000307
	if (!pRF)
		pRF = new ResourceFile ((char *) pDLLName);
	if (!pRF)
		return EC = EC_NOMEMORY;

//  Nachrichten registrieren lassen
	ResString RS (IDS_DEXMESSAGE, 80);
	if (!(__DexCmd = RegisterWindowMessage (RS.Addr ()))) {
		DELETE_OBJ (pRF);
		return EC = EC_NODEXMESSAGE;
	}

//  Maßstab lesen
//XX		SendMessage (__hWndM, __DexCmd, DEX_QUERYACTMASSTAB, (LPARAM) &Masstab);
/*XX*/	DEX_GetActiveZoom(Masstab);
//  fnr C++ Nachrichten
	RS = ResString (IDS_DEXXMESSAGE, 80);
	if (!(__DexxCmd = RegisterWindowMessage (RS.Addr ()))) {
		DELETE_OBJ (pRF);
		return EC = EC_NODEXMESSAGE;
	}

//  wenn neue Info angeh_ngt werden soll
	if (OutFlag == OMConcatinate) {
		DELETE_OBJ (pRF);
		DEX_Error (RC_TRIASARC, WC_NOTAPPEND);
		return EC = WC_NOTAPPEND;
	}

//  Datei ÷ffnen
	if ((fh = OpenFile (lpFileName, &of, OF_CREATE | OF_WRITE)) < 0) {
		DELETE_OBJ (pRF);
		return EC = EC_NOFILE;
	}
	_lclose (fh);

//  Beschreibungsbäume anlegen
	if ( !pIDT)
		pIDT = new ExtIdentDescriptionTree ();
	if (!pIDT) {
		DELETE_OBJ (pRF);
		DELETE_OBJ (pMDT);
		return EC = EC_NOMEMORY;
	}
	if ( !pMDT)
		pMDT = new ExtMerkmalDescriptionTree ();
	if (!pMDT) {
		DELETE_OBJ (pRF);
		DELETE_OBJ (pIDT);
		return EC = EC_NOMEMORY;
	}

//  Merkmalskode fnr Textwert lesen
	_GetTextObjKode ();

	return EC;
}

// Ausgeben einer Kommentarzeile -------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportComment (OFSTRUCT &of, const char *pText) {
ErrCode ExportComment (OFSTRUCT &of, const char *pText) {
//  Datei ÷ffnen und Dateizeiger ans Ende positionieren
	if (EC != EC_OKAY)
		return EC;

	int fh;
	if ((fh = OpenFile (of.szPathName, &of, OF_WRITE)) < 0)
		return EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kommentar komplettieren
	ResString Comment (ResID (IDS_COMMENT, pRF), 10);
	if ((EC = ExportLine (fh, (pchar) Comment.Addr ())) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

//  Text ausgeben
	AnsiToOem ((char _huge*) pText, (char _huge*) pText);
	if ((EC = ExportLineCR (fh, (pchar) pText)) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

	return EC = (ErrCode) _lclose (fh);
}

// Ausgeben der HeaderInformation ----------------------------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportHeader (OFSTRUCT &of, const char *pText) {
ErrCode ExportHeader (OFSTRUCT &of, const char *pText) {
    if (EC != EC_OKAY)
    	return EC;
	
//  Datei ÷ffnen und Dateizeiger ans Ende positionieren
	int fh;
	if ((fh = OpenFile (of.szPathName, &of, OF_WRITE)) < 0) 
		return EC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kommentar komplettieren
	ResString Comment (ResID (IDS_COMMENT, pRF), 10);
	if ((EC = ExportLine (fh, (pchar) Comment.Addr ())) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

//  Text ausgeben
	AnsiToOem ((char _huge*) pText, (char _huge*) pText);
	if ((EC = ExportLineCR (fh, (pchar) pText)) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

	return EC = (ErrCode) _lclose (fh);
}

// Ausgeben der BeschreibungsInformation ------------------------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportDescription (OFSTRUCT &of, const char *pT1, const char *pT2) {
ErrCode ExportDescriptionEx(OFSTRUCT &of, const char *pT1, const char *pT2, DWORD dwStyle) {
	if (EC != EC_OKAY)
		return EC;						   
						   
//  Datei ÷ffnen und Dateizeiger ans Ende positionieren
	int fh;
	if ((fh = OpenFile (of.szPathName, &of, OF_WRITE)) < 0) 
		return EC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kommentar komplettieren
	ResString Comment (ResID (IDS_COMMENT, pRF), 10);
	if ((EC = ExportLine (fh, (pchar) Comment.Addr ())) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

//  Text ausgeben
	AnsiToOem ((char _huge*) pT1, (char _huge*) pT1);
	if ((EC = ExportLine (fh, (pchar) pT1)) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

	AnsiToOem ((char _huge*) pT2, (char _huge*) pT2);
	if ((EC = ExportLineCR (fh, (pchar) pT2)) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

	return EC = (ErrCode) _lclose (fh);
}

ErrCode ExportIDDescription(const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, DWORD * pVis) {
	if (!bBeginn )
		ShortBeginn();

	return EC_OKAY;
}


ErrCode ExportIdentDescription (IdentDescription &ID);

// KK001023
//ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVISINFO ) {
ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVISINFO , long lIdent) {
	if (EC != EC_OKAY)
		return EC;

// KK000308
	if (!bBeginn )
		ShortBeginn();

	/////////////////////////////////////////////////////////////////////////
	// IdentDescription kommt jetzt "zerpflückt", muß also hier erst 
	// zusammengebaut werden
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

// KK001023
	ULONG	ulIdent;
	if (!lIdent) {
		IdentFromClassX( hDatasource, lpszOKS, &ulIdent, false );
		if (ulIdent != 0)
			lIdent = ulIdent;
	}

//	IdentDescription	IDD( lIdent, (char*) lpszOKS, pV, NULL );
// KK000307 - KurzText ist gefragt, nicht OKS
	IdentDescription	IDD( lIdent, (char*) lpszShortDescription, pV, NULL );


	return	ExportIdentDescription(IDD);
}

// Lesen und speichern aller ID-Eigenschaften -------------------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportIdentDescription (IdentDescription &IDD) {
/*XX*/	ErrCode ExportIdentDescription (IdentDescription &IDD)
{
//	DELETE_OBJ(pV);

	if (!pIDT)	
		return EC = EC_SYSERROR;

//  prüfe Parameter
	VisInfo *pVI = &IDD.VisInfoObj ();
	if (!pVI)                 
	{
		// return OutputWarnungIdent (IDS_IDENTWARNGTYP, IDD.ID ());
		FourCoverages = TRUE;
		TextExist = TRUE;
		return pIDT -> AddIDD (IDD);
	}
	
	switch (pVI -> isA ()) {
		case VT_Punkt :
		case VT_Linie :
		case VT_Flaeche :
				PolyExist = True;
		case VT_Text : {
			if (pVI -> isA () == VT_Text)
				TextExist = True;
			return pIDT -> AddIDD (IDD);
		}
		break;
		case VT_Default:
		default:                                  
			return OutputWarnungIdent (IDS_IDENTWARNGATTR, IDD.ID ());
		break;
	}
}

/*XX*/	ErrCode ExportMerkmalDescription (long lMCode, char *pbuf,short locMTyp, short iLen)
{
	if (!bBeginn )
		ShortBeginn();
// KK000309
	iLen = 80; // ???	// Bei E00 nicht die Länge des KurzTextes sonder den Wert 80 !!!

	MerkmalDescription MD (DEX_MapHandleToMCode(lMCode), pbuf, 
			   locMTyp, iLen);
	return ArcInfoExportMerkmalDescription (MD);
}
// Lesen und speichern aller Merkmals-Eigenschaften -------------------------
ErrCode EXPORTFLT PASCAL ArcInfoExportMerkmalDescription (MerkmalDescription &MD) {
	if (EC != EC_OKAY)
		return EC;

	if (!pMDT)
		return EC = EC_SYSERROR;

	Bool OK = True;
	switch (toupper (MD.MTyp ())) {
		case 'A':                  // ASCII
		case 'I':                  // Integer
		case 'F':                  // Float
			OK = True;
		break;
		case 'B':                  // Sicht-Merkmal
		case 'C':                  // Id-Merkmal
			return EC;  		   // werden nicht exportiert
		break;
		default:                                
		{  
//XX			uint Rid = DEX_GetMkBase () == 10 ? IDS_MERKMWARNGTYP
			uint Rid = 10 == MkBase ? IDS_MERKMWARNGTYP
											  : IDS_MERKMWARNGTYPX;
			return OutputWarnung (Rid, MD.MCode ());
		}			
		break;
	}

//  prüfe Text-Zeiger und Länge
	if (MD.MLen () == 0)
		return EC_OKAY;			// dieses Merkmal nicht export.			
	return pMDT -> AddMerkmDescr (MD) ? (EC = EC_OKAY) : (EC = EC_NOMEMORY);
}

// Ausgeben der TrailerInformation --------------------------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportTrailer (OFSTRUCT &of, const char *) {
ErrCode ExportTrailer (OFSTRUCT &of, const char *) {
//	if (EC != EC_OKAY)
//		return EC;

	if (!pIDT)
		return EC = EC_SYSERROR;

//  ImportMakro ausgeben
	int fh;
 
	if (nComprLevel != E00_COMPR_NONE) {			// Komprimierungsart
		if ((fh = OpenFile (pSourceFileName, &of, OF_WRITE)) < 0)
			return EC = EC_NOFILE;
	} else {
		if ((fh = OpenFile (of.szPathName, &of, OF_WRITE)) < 0)
			return EC = EC_NOFILE;
	}

	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

	if ((EC = pIDT -> OutputImportMakro (fh)) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

//  abschließende Infos ausgeben
	if ((EC = pIDT -> OutputLastData ()) != EC_OKAY) {
		_lclose (fh);
		return EC;
	}

// KK000307 - Merkmal + ID -Definit. für evtl. 2te Datenquellen - ARC-Export
	bBeginn = False;

	return EC = (ErrCode) _lclose (fh);
}

// Ausgabe eines Geometrie-Objektes mit Merkmalsinformation --------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *pMF, RSTRUCT *, char *) {
ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *pMF, RSTRUCT *, LPCTSTR lpszUniqueIdent, LPCTSTR lpszGUID, LPCTSTR lpszParentClass) {
	if (EC != EC_OKAY)
		return EC;
		
	if (!pIDT)
		return EC = EC_SYSERROR;

	if (FirstData) {                //  1. Daten ?
		FirstData = False;
		if ((EC = ExportBeforeFirstData (of.szPathName)) != EC_OKAY) {
			ExportBreak(of);
			return EC;
		}
	}

	/*XX*/	ULONG	ulIdent = 0;
	/*XX*/	if( FAILED(IdentFromClassX (hDatasource, lpszParentClass, &ulIdent, false ) ) )
	/*XX*/		return EC_SYSERROR;
	/*XX*/	GS.Id = ulIdent;
	return EC = pIDT -> OutputData (GS, pMF);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------
ErrCode ShortEnd (void)
{

	OFSTRUCT of;
	ErrCode EC = ExportEnd(of);
// KK000307
	bBeginn = False;							// Erstabfrage
	return EC_OKAY;

}
//---------------------------------------------------------------
ErrCode ShortBeginn (void)
{
	if (bBeginn )
		return EC_OKAY;

	ErrCode EC = ShortEnd();

// KK000405 - aus ExportBeginn !!!

	Insel = True;						// Inseln separat exportieren
	FirstData = True;
	PolyExist = TextExist = False;		// es ex. keine Flächen/Text-IDs
	ObjKlasseMK = DEX_GetUniqueMCode ();					// von TRIAS vergebener Merkmalskode für Objekt-Klasse
	MkBase = DEX_GetMkBase ();			// Zahlenbasis für MCodes
	FourCoverages = FALSE;				// Standard: immer Ausgabe eines Covers pro ID
	StandTextMKode = 0L;                // Merkmalskode eines Textwertes
	g_sTextTruncCnt = 0;				// Zähler für abgeschn. Texte

//	_ASSERTE( NULL == hDatasource);

	Masstab = 0.0;          


//  Resource-File-Objekt init.
	if ( !pRF)
	    pRF = new ResourceFile ((char *) pDLLName);
    if (!pRF)
		return EC_NOMEMORY;

	hDatasource = DEX_GetDataSourceHandle();

	if ( pIDT) 
		DELETE_OBJ(pIDT);
	if ( !pIDT )
	   pIDT = new ExtIdentDescriptionTree ();

	if ( pMDT) 
		DELETE_OBJ(pMDT);
	if (!pMDT) 
		pMDT = new ExtMerkmalDescriptionTree ();

	bBeginn = TRUE;

	return EC_OKAY;
}
//--------------------------------------------------------------




// Ende des DatenExports ------------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportEnd (OFSTRUCT &) {
ErrCode ExportEnd (OFSTRUCT &) {
//	ggf. Fehler-Meldung ausgeben
	if (g_sTextTruncCnt > 0)		 // Zähler für abgeschn. Texte	
		OutputWarnung (IDS_TEXT_TRUNC_WARN, g_sTextTruncCnt);

	DELETE_OBJ (pRF);

//  Beschreibungsb_ume l÷schen
	DELETE_OBJ (pIDT);
	DELETE_OBJ (pMDT);

	/*XX*/	hDatasource = NULL;

	remove (pTempFileName);

	DELETE_OBJ(pSourceFileName);				// gewählter AusgabeFilename
	DELETE_OBJ(pTempFileName);					// temporärer File

	return EC_OKAY;
}

//XX	ErrCode EXPORTFLT PASCAL ArcInfoExportBreak (OFSTRUCT &of) {
ErrCode ExportBreak (OFSTRUCT &of) {
	if (!pIDT)
		return EC_SYSERROR;

//  Import-Makro l÷schen
	remove (of.szPathName);

	return pIDT -> DeleteAllFiles ();
}

//XX }          // extern "C"

//  Daten vor dem 1. Export ausgeben
ErrCode ExportBeforeFirstData (pchar pPath) {
	if (EC != EC_OKAY)
		return EC;

	if (!pIDT || !pMDT)
		return EC = EC_SYSERROR;

//  prünfe Anzahl Einträge
	if (!pIDT -> Count ())
		return EC = EC_NOIDDESCRIPTION;

	pIDT -> Optimize ();

/*
//  alle ungünltigen Merkmalsbeschreibungen löschen
	if ((EC = pMDT -> DeleteUnvalids ()) != EC_OKAY)
		return EC;
*/
    
	pMDT -> Optimize ();		// jetzt den Merkmalsbaum optimieren    
    
//  Exportparameter im Dilaog prüfen        
	BOOL bEnable = pMDT -> Count () > 0 ? TRUE : FALSE;
	if ((EC = pIDT -> CheckCoverNameDialog (bEnable)) != EC_OKAY)
		return EC;
		
//	wenn nur 4 Coverages, dann noch Merkmal "Objekt-Klasse hinzufügen"	
	if (FourCoverages)
	{   
		ResString Text (ResID (IDS_OBJCLASSNAME, pRF), 15);                      
//XX		ObjKlasseMK = DEX_GetUniqueMCode ();
		MerkmalDescription MD (ObjKlasseMK, (char *) Text.Addr (), 
							   ObjKlasseTyp, KurzTextLen);
		
	//	Beschreibung speichern		    
		if (! pMDT -> AddMerkmDescr (MD))
			return EC_SYSERROR;
	}

// KK000331
	if (nComprLevel != E00_COMPR_NONE) {
		ErrCode EC = CreateTempDaten ( pPath);
		if (EC == EC_OKAY) {
			int fh;
			OFSTRUCT of;
			if ((fh = OpenFile (pTempFileName, &of, OF_CREATE | OF_WRITE)) < 0) {
				DELETE_OBJ (pRF);
				return EC = EC_NOFILE;
			}
			_lclose (fh);

			return EC = pIDT -> OutputFirstData (pTempFileName);
		}
	}


//  HeaderInfos für Cover ausgeben
	return EC = pIDT -> OutputFirstData (pPath);
}

//---------------------------------------------------------------------------
ErrCode CreateTempDaten (char *pPath)
{

	if ( !pPath)
		return EC_SYSERROR;

	if ( pSourceFileName )				// gewählter AusgabeFilename
		DELETE_OBJ( pSourceFileName );

	if ( pTempFileName)					// temporärer File
		DELETE_OBJ(pTempFileName);

	pSourceFileName = new char [_MAX_PATH];

	if ( !pSourceFileName ) {
		nComprLevel = E00_COMPR_NONE;
		return EC_SYSERROR;
	}

	pTempFileName = new char [_MAX_PATH];

	if ( !pTempFileName ) {
		nComprLevel = E00_COMPR_NONE;
		DELETE_OBJ( pSourceFileName );
		return EC_SYSERROR;
	}

	strcpy(pSourceFileName,pPath);			// OriginalFileName sichern!

// Temp suchen
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
			char FName [_MAX_FNAME] = "";
			char Ext   [_MAX_EXT] = "";
			char Drive [_MAX_DRIVE] = "";
		    char Dir   [_MAX_DIR] = "";
  		    _splitpath (pPath, Drive, Dir, FName, Ext);
		    _splitpath (pTempDat, Drive, Dir, NULL, NULL);
			_makepath (pTempFileName, Drive, Dir, FName, Ext);
		}

		DELETE_OBJ (pTempDat);

	} else {
		nComprLevel = E00_COMPR_NONE;
		DELETE_OBJ( pSourceFileName );
		DELETE_OBJ( pTempFileName );
		return EC_SYSERROR;
	}

	return EC_OKAY;

}
//---------------------------------------------------------------------------
ErrCode SetTempDaten (OFSTRUCT &of)
{
	return EC_OKAY;
}
//---------------------------------------------------------------------------
ErrCode OutputWarnungIdent (short ResourceId, long Ident) {
	if (!pRF)
	   return EC_SYSERROR;

	Window *pParent = (Window *) SendMessage (__hWndM, __DexxCmd,
											   DEXX_MAINWINDOW, 0L);
	if (!pParent)
		return EC_NODEXMESSAGE;

	ResString Caption (ResID (IDS_WARNUNG, pRF), 20);
	ResString TextFormat (ResID (ResourceId, pRF), 80);
	char Buffer [100] = "";
	char tBuffer [30] = "";
	ClassFromIdentX (Ident, tBuffer, sizeof(tBuffer));
	wsprintf (Buffer, TextFormat.Addr (), tBuffer);
	MessBox MB (Caption.Addr (), Buffer, pParent);
	MB.SetType (OkayButton | ExclamationIcon);
	MB.Show ();
	return EC_OKAY;
}

ErrCode OutputWarnung (short ResourceId, long Value) {
	if (!pRF)
	   return EC_SYSERROR;

	Window *pParent = (Window *) SendMessage (__hWndM, __DexxCmd,
											   DEXX_MAINWINDOW, 0L);
	if (!pParent)
		return EC_NODEXMESSAGE;

	ResString Caption (ResID (IDS_WARNUNG, pRF), 20);
	ResString TextFormat (ResID (ResourceId, pRF), 80);
	char Buffer [100] = "";
	wsprintf (Buffer, TextFormat.Addr (), Value);
	MessBox MB (Caption.Addr (), Buffer, pParent);
	MB.SetType (OkayButton | ExclamationIcon);
	MB.Show ();
	return EC_OKAY;
}

//  Merkmalskode fnr Textwert lesen
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
	for (; i < KeySize; i++)         // Key mit ' ' auffüllen
		Entry.hdrKey [i] = ' ';

//  Kode von TRIAS lesen
	DEX_ReadGeoDBHdrEntry (Entry);
	if (Kode [0] && atol (Kode))
		StandTextMKode = atol (Kode);
	else
		StandTextMKode = 0L;
}
