// Dialogfenster zur Auswahl einer Symbolisierungsart -------------------------
// File: XVISDLG.CXX

#include "visobjp.hxx"

#if defined(WIN32)
#include <registry.hxx>
#endif // WIN32

#include "visobj.h"
#include "xvisdlg.h"

#include "visobj.hxx"
#include "xvisdlg.hxx"
#include <icustom.hxx>
#include "vismtree.hxx"

// FunktionsPrototypen --------------------------------------------------------
short OTypToBits (short iOTyp)
{
	switch (iOTyp) {
	case OGPunkt:
		return OTPunkt;
	case OGLinie:
		return OTLinie;
	case OGFlaeche:
	case OGKreis:
		return OTFlaeche;
	case OGLabel:
	case OGText:
		return OTText;
	case OGKO:
		return OTKO;
	case OGSachObjekt:
		return OTSachObjekt;
	default:
	case OGUnknown:
		break;
	}

return 0;
}

extern "C" {

typedef struct tagOBJCHANGESYMBOL {
	CVisObjExtension *m_pVOExt;
	CVisModule *m_pVM;
	char *m_pVString;
	bool m_fFirst;
	short m_iOTypes;
} OBJCHANGESYMBOL;

// Symbolisierung für ein Objekt neu einstellen -------------------------------
BOOL _XTENSN_EXPORT PASCAL ObjChangeSymbol (long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return true;	// weitermachen

// Symbolisierung nur neu einstellen, wenn Objekttyp übereinstimmt
OBJCHANGESYMBOL *pOCS = (OBJCHANGESYMBOL *)pData;
short iOType = DEX_GetObjectType(lONr);

	if (OTypToBits (iOType) & pOCS -> m_iOTypes) {
	// ObjektTyp setzen
	char cOTyp = ' ';
	
		switch (iOType) {
		case OGPunkt:	cOTyp = 'c'; break;
		case OGLinie:	cOTyp = 'l'; break;
		case OGFlaeche:	cOTyp = 'a'; break;
		case OGLabel:
		case OGText:	cOTyp = 'x'; break;
		default:	return true;	// unbekannter Objekttyp
		}
		*pOCS -> m_pVString = cOTyp;
	
	// Für jedes zu bearbeitende Objekt noch einmal nachfragen, ob 
	// VisString geändert werden soll. Außerdem besteht die Möglichkeit,
	// über die Referenz auf die ObjektNummer ein anderes Objekt
	// als das gegebene zu beeinflussen.
	HRESULT hr = pOCS -> m_pVM -> m_pIVisModule -> 
			SymbolizeObject (pOCS -> m_pVOExt -> hWnd(),
					 lONr, iOType,
					 pOCS -> m_pVString, _MAX_PATH);

	// bei irgend einem Fehler einfach weitermachen
		if (FAILED(hr) && GetScode(hr) != E_NOTIMPL)
			return true;
	
	// String zwischenspeichern
	string strT = pOCS -> m_pVString;	// Zwischenspeichern wegen OemToAnsi

	// als VisInfo wegschreiben	
	bool fResult = pOCS -> m_pVOExt ->
				ModObjectSymbol (lONr, pOCS -> m_pVString, 
				pOCS -> m_fFirst);

		strcpy (pOCS -> m_pVString, strT.c_str());	// zurückkopieren
		return fResult;
	}

return true;	// weitermachen
}

}	// extern "C" 

// MenuFunktion ---------------------------------------------------------------
bool CVisObjExtension :: DefineSymbol (HWND hORWnd) 
{
// aktiviertes Objekt besorgen
long lActObj = DEX_GetActiveObject (hORWnd);

	if (lActObj == -1) return false;
		
short Status = DEX_GetObjectStatus (lActObj);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return false;

// Fenster anlegen: Auswahl des Symbolisierungsmodules
Window tWnd (hORWnd);
CExtVisDlg EVDlg (&tWnd, &RF(), DEX_GetObjectType(lActObj));

short iModules = EVDlg.FInit();

	if (iModules == -1) return false;		// Fehler
	if (iModules != 1) {
	// kein oder mehr als 1 Modul
		EVDlg.Show (Centre);	// Dialog anzeigen, Auswahl vornehmen
		if (!EVDlg.Result()) return false;
	}
	
// aktivieren des Dialoges im VisModul
	if (m_pVMT == NULL) return false;
	
// sicherstellen, daß dieser VisModule geladen ist
char *pVisModule = EVDlg.GetModuleName();
//char *pTmp = strlwr(pVisModule);
CVisModule *pVM = m_pVMT -> FFindOrAdd (pVisModule, m_pActProject);
char *cbModuleInfo[2];
	
	if (pVM == NULL) return false;
		
	cbModuleInfo[0] = cbModuleInfo[1] = NULL;
	
HANDLEVISINFO *pHVI = GetObjectVisInfo (lActObj, NULL, -1L, cbModuleInfo);

	if (pHVI == NULL) return false;

VisInfo *pVI = VisInfoFromC (*pHVI -> m_pVI, (enum VisType)pHVI -> m_iVTyp);

// VisModule auffordern, das Objekt zu behandeln
OBJCHANGESYMBOL OCS;
ResString rsVModFmt (ResID (IDS_VMODFORMAT, &RF()), 20);
	
	OCS.m_pVString = new char [_MAX_PATH +50];
	if (OCS.m_pVString == NULL) return false;

	strcpy (OCS.m_pVString, rsVModFmt);

	dtHANDLEVISINFO (pHVI);		// Speicher freigeben
	
// Den VisModule fragen, wie er die ausgewählten Objekte symbolisieren
// will. Dazu liefert dieser eine Zeichenkette, die als objektbezogene
// Visualisierung abgespeichert wird und dann beim Zeichnen diesem 
// Module zur Symbolisierung übergeben wird.
HRESULT hr = pVM -> m_pIVisModule -> QueryParameters (
			hWnd(), lActObj, pVI, cbModuleInfo[1],
			&OCS.m_pVString[strlen(OCS.m_pVString)], 
			_MAX_PATH, &OCS.m_iOTypes
	     );
		     
	DELETE_OBJ (pVI);
	DELETE_OBJ(cbModuleInfo[0]);
	DELETE_OBJ(cbModuleInfo[1]);

	if (FAILED(hr)) return false;
		
	strcat (OCS.m_pVString, 
			ResString (ResID (IDS_TRAILER, &RF()), 5));
		
// Eingegebenen String am Objekt/allen selektierten Objekten abspeichern
short iCnt = 0;

	OCS.m_pVOExt = this;
	OCS.m_pVM = pVM;
	OCS.m_fFirst = false;
		
	DEXOR_SelectedObjectsCount (hORWnd, &iCnt); 
	if (iCnt > 1) {
	// alle selektierten behandeln
	ENUMLONGKEY ELK;
			
		ELK.eKey = (long)hORWnd;
		ELK.eFcn = (ENUMLONGKEYPROC)ObjChangeSymbol;
		ELK.ePtr = &OCS;
		DEX_EnumSelectedObjects (ELK);
	} else {
	// lediglich aktiviertes Objekt behandeln
		ObjChangeSymbol (lActObj, false, &OCS);
	}
	DELETE_OBJ (OCS.m_pVString);
	if (OCS.m_fFirst)
		RebuildSight();		// alles neu zeichnen, neu aufbauen
	else 
		DEX_RePaintWait();	// alles neu zeichnen
	
return true;
}


// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CExtVisDlg :: CExtVisDlg (pWindow pW, ResourceFile *pRF, short iObjTyp)
	    : DialogWindow (pW, ResID (EXTSYMBOLDLG, pRF)),
	      m_pbOK (this, IDOK),
#if !defined(WIN32)
	      m_pbHelp (this, IDB_EXTSYMBOLHELP),
#endif //!WIN32
	      m_lbVisModules (this, IDL_EXTSYMBOLTYP, 3),
	      m_iObjTyp (iObjTyp),
	      m_rRF (*pRF)
{
// Controls initialisieren
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif //!WIN32
	m_pbOK.Disable();
	m_lbVisModules.SetColWidth (0, 200);	// Spaltenbreite setzen
	m_lbVisModules.SetColWidth (1, _MAX_PATH);
	m_lbVisModules.SetColWidth (2, 10);

// Variablen initialisieren		
	m_pModuleName = NULL;
}

#pragma warning (default: 4355)

CExtVisDlg :: ~CExtVisDlg (void)
{
	DELETE_OBJ (m_pModuleName);
}


short CExtVisDlg :: FInit (void)
{
// Caption generieren
uint resID;

	switch (m_iObjTyp) {
	case OGPunkt:
		resID = IDS_PUNKTSYMBOLDLG;
		break;
		
	case OGLinie:
		resID = IDS_LINIENSYMBOLDLG;
		break;
		
	case OGFlaeche:
		resID = IDS_FLAECHENSYMBOLDLG;
		break;
		
	case OGLabel:
	case OGText:
		resID = IDS_TEXTSYMBOLDLG;
		break;
		
	default:
		return false;
	}
	SetCaption (ResString (ResID (resID, &m_rRF), 30));

// Speicher anlegen
	m_pModuleName = new char [_MAX_PATH];
	if (m_pModuleName == NULL)
		return -1;	// Fehler
		
// ListBox füllen
short iResult = FillListBox();		// liefert Anzahl der Einträge

	if (iResult > 0) {
	char cbOTypes[10];

		m_pbOK.Enable();
		m_lbVisModules.ChangeCurrentIndex(0);
		m_lbVisModules.GetRow (0, (char *)NULL, m_pModuleName, cbOTypes);
	}
		
return iResult;
}


// ListBox mit zur Verfügung stehenden VisModulen füllen ----------------------
#if defined(WIN32)
const char s_cbVisModules[] = TEXT("Software\\uve\\TRiAS\\VisModules");

bool CExtVisDlg :: LoadVisModuleRegistry (LPCSTR pcKey)
{
string strName, strOldName; 
DWORD dwObjTypes = 0;

// Lesbaren Bezeichner holen
	{
	CCurrentUser regExt (s_cbVisModules);
	TCHAR cbName [_MAX_PATH];
	LONG lLen = _MAX_PATH;

		if (regExt.GetSZ (pcKey, cbName, lLen))		// Name lesen
			strName = cbName;
		else 
			strName = pcKey;
	}

// oldname
	{
	string strKey = string(s_cbVisModules) + TEXT("\\") + pcKey;
	CCurrentUser regExt (strKey.c_str());
	TCHAR cbName [_MAX_PATH];
	LONG lLen = _MAX_PATH;

		if (regExt.GetSZ (TEXT("OldName"), cbName, lLen))		// OldName lesen
			strOldName = cbName;
		else 
			strOldName = pcKey;
	}

// ConfigOptions
	{
	string strKey = string(s_cbVisModules) + TEXT("\\") + pcKey + TEXT("\\Config");
	CCurrentUser regExt (strKey.c_str());

		if (!regExt.GetDWORD (TEXT("ObjTypes"), dwObjTypes))		// Options lesen
			return false;
	}

// in Listbox eintragen
	if (dwObjTypes & OTypToBits (m_iObjTyp)) {
	TCHAR strOTypes[20];

		ultoa (dwObjTypes, strOTypes, 16);
		m_lbVisModules.AddRow (-1, strName.c_str(), strOldName.c_str(), strOTypes);
	}

return true;
}

#endif // WIN32

short CExtVisDlg :: FillListBox (void)
{
#if defined(WIN32)
// Aus Registry alle registrierten Vismodules laden
	if (!IsWin32s()) {
	HKEY hKey = NULL;
	DWORD i = 0;
	char cbKey[_MAX_PATH];
	DWORD retCode = RegOpenKey (HKEY_CURRENT_USER, s_cbVisModules, &hKey);

		if (retCode != ERROR_SUCCESS) return false;

	// alle Erweiterungen mit Priorität laden
		while (RegEnumKey (hKey, i++, cbKey, _MAX_PATH) == ERROR_SUCCESS) 
			LoadVisModuleRegistry (cbKey);

		RegCloseKey (hKey);   // Close the key handle.
	}
#endif // WIN32

// jetzt alle 'alten' laden
ResString rsIni (IDS_PROFILE, 15);
ResString rsParams (IDS_IRISPARS, 15);
ResString rsVModule (ResID (IDS_VISMODULE, &m_rRF), 15);

// VisModule in ListBox schreiben
short iVModNums = GetPrivateProfileInt (
				rsParams, 
				ResString (ResID (IDS_VMODNUMS, &m_rRF), 15), 
				0, rsIni);
	if (iVModNums > 0) {
	// wenn VisModule gegeben sind
	char *pVModNamesStr = new char [iVModNums*80+1];
	char **ppVModNames = new char *[iVModNums];

		if (pVModNamesStr == NULL || ppVModNames == NULL) {
			DELETE_OBJ (pVModNamesStr);
			return -1;	// Fehler
		}
		GetPrivateProfileString (rsVModule, NULL, "", pVModNamesStr,
					 iVModNums*80+1, rsIni);
		ppVModNames[0] = pVModNamesStr;
		
	short len = 0;

		for (short i = 1; i < iVModNums; i++)
			ppVModNames[i] = &pVModNamesStr[len += strlen(ppVModNames[i-1])+1];

	// eintragen der VisModule in die ListBox
		for (i = 0; i < iVModNums; i++) {
		char currVMod[_MAX_PATH];

		// Beschreibung des VisModules lesen
			GetPrivateProfileString (rsVModule, ppVModNames[i], "",
						 currVMod, _MAX_PATH, rsIni);

		// TabularListBox: 1.Spalte VsModuleName, 2. Spalte: iOTypes
		char *pChr = strpbrk (currVMod, ",; \t");
		
			if (pChr == NULL) continue;	// unvollständiger INI-Eintrag
			
		short iOTyp = atoi (pChr+1);

			if (iOTyp & OTypToBits (m_iObjTyp)) {
				*pChr = '\0';		// trennen
				m_lbVisModules.AddRow (-1, ppVModNames[i], 
						       currVMod, pChr+1);
			}
		}
		
	// Speicher wieder freigeben
		DELETE_OBJ (ppVModNames);
		DELETE_OBJ (pVModNamesStr);
	}

return m_lbVisModules.GetCount();	// Anzahl der Einträge liefern
}


// EventHandler dieses DialogFensters -----------------------------------------
void _XTENSN_EXPORT CExtVisDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{
		char cbOTypes[10];
		short iIndex = m_lbVisModules.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_lbVisModules.GetRow (iIndex, (char *)NULL, m_pModuleName, cbOTypes);
				EndDlg (1);
			}
		}
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
		
	case IDB_EXTSYMBOLHELP:
		break;
	}
}

void _XTENSN_EXPORT CExtVisDlg :: ListBoxClk (ControlEvt)
{
char cbOTypes[10];
short iIndex = m_lbVisModules.GetCurrentIndex();
		
	if (iIndex != -1) {
		m_lbVisModules.GetRow (iIndex, (char *)NULL, m_pModuleName, cbOTypes);
		EndDlg (1);
	}
}

