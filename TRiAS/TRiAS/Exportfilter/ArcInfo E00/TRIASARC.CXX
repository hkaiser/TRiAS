/*
File: TRIASARC.CXX

Hauptmodul des TRIAS-Arc/Info-Konverters.

Erarbeitet: J. Benkenstein                                Begonnen am: 30. April 1993
														  Stand vom: 18. August 1994
*/

#include "pheader.h"               
 
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

#include "triasarc.hr"      		// Resourcen-Defines           
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
double Masstab = 0.0;                 		// aktueller Maßstab
Bool FirstData = True;
Bool TextExist = False;                     // es ex. keine Text-IDs
Bool PolyExist = False;                     // es ex. keine Flächen-IDs
Bool Insel = True;							// Insel separat export.
Bool FourCoverages = FALSE;					// Standard: immer Ausgabe eines Covers pro ID
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

#ifdef _DEBUG
HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
{
CLASSFROMIDENT CFI;

	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdent(CFI);
}

HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, bool fCreateNew)
{
	if (NULL == pulIdent) 
		return E_POINTER;

	IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = pcClass;
	IFC.fCreateNew = fCreateNew;

	HRESULT hr = DEX_GetIdentFromClass(IFC);

	if (SUCCEEDED(hr)) 
		*pulIdent = IFC.ulIdent;

	return hr;
}
#endif

extern "C" {    // alle exportierten Funktionen sollen _pascal sein

static ErrCode EC = EC_OKAY;

// Beginn des DatenExports ------------------------------------------------
ErrCode EXPORTFLT PASCAL ArcInfoExportBegin (char *lpFileName, OFSTRUCT &of,
											OutMode OutFlag, HWND hWnd) {
//  globale Variablen init.
	__hWndM = hWnd;
	Insel = True;						// Inseln separat exportieren
	FirstData = True;
	PolyExist = TextExist = False;		// es ex. keine Flächen/Text-IDs
	ObjKlasseMK = 0;					// von TRIAS vergebener Merkmalskode für Objekt-Klasse
	FourCoverages = FALSE;				// Standard: immer Ausgabe eines Covers pro ID
	StandTextMKode = 0L;                // Merkmalskode eines Textwertes
	g_sTextTruncCnt = 0;				// Zähler für abgeschn. Texte	

	pIDT = NULL;
	pMDT = NULL;
	pRF = NULL;
	Masstab = 0.0;          
	EC = EC_OKAY;

//  Resource-File-Objekt init.
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
	SendMessage (__hWndM, __DexCmd, DEX_QUERYACTMASSTAB, (LPARAM) &Masstab);

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

	int fh;
//  Datei ÷ffnen
	if ((fh = OpenFile (lpFileName, &of, OF_CREATE | OF_WRITE)) < 0) {
		DELETE_OBJ (pRF);
		return EC = EC_NOFILE;
	}
	_lclose (fh);

//  Beschreibungsb_ume anlegen
	pIDT = new ExtIdentDescriptionTree ();
	if (!pIDT) {
		DELETE_OBJ (pRF);
		return EC = EC_NOMEMORY;
	}

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
ErrCode EXPORTFLT PASCAL ArcInfoExportComment (OFSTRUCT &of, const char *pText) {
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
ErrCode EXPORTFLT PASCAL ArcInfoExportHeader (OFSTRUCT &of, const char *pText) {
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
ErrCode EXPORTFLT PASCAL ArcInfoExportDescription (OFSTRUCT &of, const char *pT1,
						   const char *pT2) {
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

// Lesen und speichern aller ID-Eigenschaften -------------------------------
ErrCode EXPORTFLT PASCAL ArcInfoExportIdentDescription (IdentDescription &IDD) {
	if (EC != EC_OKAY)
		return EC;

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
			uint Rid = DEX_GetMkBase () == 10 ? IDS_MERKMWARNGTYP
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
ErrCode EXPORTFLT PASCAL ArcInfoExportTrailer (OFSTRUCT &of, const char *) {
	if (EC != EC_OKAY)
		return EC;

	if (!pIDT)
		return EC = EC_SYSERROR;

//  ImportMakro ausgeben
	int fh;
	if ((fh = OpenFile (of.szPathName, &of, OF_WRITE)) < 0)
		return EC = EC_NOFILE;
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

	return EC = (ErrCode) _lclose (fh);
}

// Ausgabe eines Geometrie-Objektes mit Merkmalsinformation --------------------
ErrCode EXPORTFLT PASCAL ArcInfoExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *pMF,
										    RSTRUCT *, char *) {
	if (EC != EC_OKAY)
		return EC;
		
	if (!pIDT)
		return EC = EC_SYSERROR;

	if (FirstData) {                //  1. Daten ?
		FirstData = False;
		if ((EC = ExportBeforeFirstData (of.szPathName)) != EC_OKAY)
			return EC;
	}

	return EC = pIDT -> OutputData (GS, pMF);
}

// Ende des DatenExports ------------------------------------------------------
ErrCode EXPORTFLT PASCAL ArcInfoExportEnd (OFSTRUCT &) {
//	ggf. Fehler-Meldung ausgeben
	if (g_sTextTruncCnt > 0)		 // Zähler für abgeschn. Texte	
		OutputWarnung (IDS_TEXT_TRUNC_WARN, g_sTextTruncCnt);

	DELETE_OBJ (pRF);

//  Beschreibungsb_ume l÷schen
	DELETE_OBJ (pIDT);
	DELETE_OBJ (pMDT);

	return EC_OKAY;
}

ErrCode EXPORTFLT PASCAL ArcInfoExportBreak (OFSTRUCT &of) {
	if (!pIDT)
		return EC_SYSERROR;

//  Import-Makro l÷schen
	remove (of.szPathName);

	return pIDT -> DeleteAllFiles ();
}

}          // extern "C"

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
		ObjKlasseMK = DEX_GetUniqueMCode ();
		MerkmalDescription MD (ObjKlasseMK, (char *) Text.Addr (), 
							   ObjKlasseTyp, KurzTextLen);
		
	//	Beschreibung speichern		    
		if (! pMDT -> AddMerkmDescr (MD))
			return EC_SYSERROR;
	}

//  HeaderInfos für Cover ausgeben
	return EC = pIDT -> OutputFirstData (pPath);
}

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
