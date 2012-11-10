// Rudimente, die minimale Funktionsfaehigkeit einer Erweiterungs-DLL
// demonstrieren
// File: IDENTSDB.CXX

#include "idntsdbp.hxx"

#include <xtsnaux.hxx>
#include <eieruhr.hxx>

#if !defined(WIN16)
#include <itoolbar.h>
#include <ospace/com/iterenum.h>
extern CComModule _Module;

#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/map>		// STL related stuff
#endif // WIN16

#include <registrx.hxx>

#include "Strings.h"
#include "identsdb.h"	// ResourceKonstanten für dieses Beispiel
#include "identres.h"
//#include "defabout.h"

#include "idignore.hxx"
#include "mkignore.hxx"

//#include "defabout.hxx"
#include "identsdb.hxx"

#include "hdrentrx.hxx"

#include <xtsnguid.h>

#include <initguid.h>
#include "idntguid.h"
#include <statguid.h>
#include <undoguid.h>		// GUID
#include <dirisole.h>
#include <triastlb.h>
#if !defined(WIN16)
#define __DToolBar_h__
#include <toolguid.h>
#include "AuxUIOwner.h"
#endif // WIN16

#include "version.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_SUPPORT_QUERYDEFS)
EXTERN_C const CLSID CLSID_QueryDefExt = {0x1BF01AF1,0x33CF,0x11D3,{0x94,0xFA,0x00,0x80,0xC7,0x86,0x29,0x7B}};
EXTERN_C const CLSID CLSID_TRiASCollectObjects = {0x6BE4F280,0x33D1,0x11D3,{0x94,0xFA,0x00,0x80,0xC7,0x86,0x29,0x7B}};
#endif // defined(_SUPPORT_QUERYDEFS)

extern "C" 
bool _XTENSN_EXPORT CALLBACK SelPBDNameHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM)
{
#if !defined(WIN16)
	if (wMsg == WM_INITDIALOG) 
		CentreWindow (::GetParent(hDlg), hDlg);
#endif

return false;
}

extern "C" 
bool _XTENSN_EXPORT CALLBACK CreatePBDNameHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM)
{
	if (wMsg == WM_INITDIALOG) {
#if !defined(WIN16)
		CentreWindow (::GetParent(hDlg), hDlg);
#endif // WIN16

	// verhindern, daß Verzeichnis gewechselt werden kann
	HWND hControl = GetDlgItem (hDlg, lst2); 

		EnableWindow (hControl, false);
		hControl = GetDlgItem (hDlg, cmb2);
		EnableWindow (hControl, false);
	}

return false;
}

#if !defined(WIN16)

// Diese Funktionen werden nur unter 40 installiert und gerufen ---------------
extern "C" 
UINT _XTENSN_EXPORT APIENTRY PBDName40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NOTIFY == wMsg) {
	LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;

		if (CDN_INITDONE == pofn->hdr.code) {
		HWND hDlgP = ::GetParent(hDlg);
					
			CentreWindow (::GetParent (hDlgP), hDlgP);
			return true;
		}
	}
			
return false;	// erstmal alles weiterleiten
}

#endif // WIN16
		

// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
CTriasExtension * NewExtension (void)
{
	return new CIdentsDBExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_IdentsDBExtension, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
//
// ACHTUNG: Im VersionsRC-File (*.rcv) nicht den Eintrag "TRiASSelfRegister" 
// vergessen. Ohne diesen EIntrag wird die Funktion UpdateRegistry nie gerufen.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_IdentsDBExtension, 
				TEXT("TRiAS.IdentsDB.1"), IDS_LONGCLASSNAME,
				IDENTSDB_MAJORVERSION, IDENTSDB_MINORVERSION,
				EFPreLoad);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_IdentsDBExtension, 
				TEXT("TRiAS.IdentsDB.1"));
	}
	return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängeneden Menu's übergeben bekommt.
CIdentsDBExtension::CIdentsDBExtension (void)
		    : CTriasExtension()
{
// keine OProps installiert
	_iOPKText = 0L;
	_iOPLText = 0L;

// erstmal nichts ignorieren
	_AllIdentIgnore = false;
	_AllMCodeIgnore = false;

	m_fSysMode = false;

// keine Fehlerbehandlungen aktiv
	m_lIdentHandled = -1L;
	m_lMCodeHandled = -1L;

// IgnoreListen anlegen
	pIIL = NULL;
	pIML = NULL;

// sonstige Initialisierungen
	m_iMkBase = 10;
	m_pObjProp = NULL;

	m_pPopupMenu = NULL;
}

// Destruktor -----------------------------------------------------------------
CIdentsDBExtension::~CIdentsDBExtension (void) 
{
	DELETE_OBJ(pIIL);
	DELETE_OBJ(pIML);
	DELETE_OBJ(m_pPopupMenu);

	DELETE_OBJ(m_pObjProp);	// fully contained
}

// da wir ein zusätzliches Interface dazugenommen haben, muß ein modifiziertes 
// QueryInterface gegeben sein
HRESULT CIdentsDBExtension::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IObjectProps)
		*ppvObj = m_pObjProp;	// ImportInterface liefern
	else
	// alles andere überlassen wir der BasisKlassse
		return CTriasExtension::QueryInterface (riid, ppvObj);

// AddRef nicht vergessen
	LPUNKNOWN(*ppvObj) -> AddRef();
	return NOERROR;
}

// ObjektPropertyFunktionen ---------------------------------------------------
// IdentifikatorKurzText ------------------------------------------------------
#if defined(WIN16)
#pragma function (memcpy)		// immer HUGE-Variante benutzen
static char s_cbBuffer[2048];		// ZeichenKettenBuffer für OProps
#endif

extern "C"
char * _XTENSN_EXPORT PASCAL OPIdentKText (long lONr, char *pBuffer, short iLen)
{
static long lCnt = 0;		// Idents mit KurzText
static long lCntFull = 0;	// GesamtIdents

	if (lONr == OBJPROP_RESET) {
		lCnt = 0L;
		lCntFull = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
#if !defined(WIN16)
		ltoa (lCntFull, pBuffer, 10);
#else
		ltoa (lCntFull, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif
		return pBuffer;	
	} else if (lONr == OBJPROP_COUNT) {
#if !defined(WIN16)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN16
	        return pBuffer;
	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDS_KTEXTHELP, &g_pTE -> RF()), 128);
	
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
	} else if (lONr != 0) {
		TX_ASSERT(NULL != pBuffer);

	long lIdent = DEX_GetObjIdentEx (lONr);

		if (lIdent != -1L) {	// PBD-Info holen
		PBDDATA pbdData;
		ErrCode RC; 

			pbdData.dwSize = sizeof(PBDDATA);
			pbdData.pbdTyp = 'i';
			pbdData.pbdCode = lIdent;
			pbdData.pbdLText = NULL;
			pbdData.pbdKTextLen = iLen;
			pbdData.pbdLTextLen = 0;
			pbdData.pbdKText = pBuffer;	// gesucht

			if ((RC = DEX_GetPBDData (pbdData)) != EC_OKAY && RC != WC_NOTFOUND && WC_RETURN != RC)
				ClassFromIdentX (lIdent, pBuffer);
			else if (*pBuffer)
				lCnt++;		// hat KurzText
			lCntFull++;
		}
	}
	return pBuffer;
}

// IdentifikatorLangText
extern "C"
char * _XTENSN_EXPORT PASCAL OPIdentLText (long lONr, char *pBuffer, short iLen)
{
static long lCnt = 0;		// Idents mit KurzText
static long lCntFull = 0;	// GesamtIdents

	if (lONr == OBJPROP_RESET) {
		lCnt = 0L;
		lCntFull = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		ltoa (lCntFull, pBuffer, 10);
		return pBuffer;	
	} else if (lONr == OBJPROP_COUNT) {
		ltoa (lCnt, pBuffer, 10);
	        return pBuffer;
	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDS_LTEXTHELP, &g_pTE -> RF()), 128);
	
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
	} else if (lONr != 0) {
		TX_ASSERT(NULL != pBuffer);

	long lIdent = DEX_GetObjIdentEx (lONr);

		if (lIdent != -1L) {	// PBD-Info holen
		PBDDATA pbdData;
		ErrCode RC; 

			INITSTRUCT(pbdData, PBDDATA);
			pbdData.pbdTyp = 'i';
			pbdData.pbdCode = lIdent;
			pbdData.pbdKText = NULL;
			pbdData.pbdKTextLen = 0;
			pbdData.pbdLTextLen = iLen;
			pbdData.pbdLText = pBuffer;	// gesucht

			if ((RC = DEX_GetPBDData (pbdData)) != EC_OKAY && RC != WC_NOTFOUND && WC_RETURN != RC) 
				ClassFromIdentX (lIdent, pBuffer);
			else if (*pBuffer)
				lCnt++;		// hat LangText
			lCntFull++;
		}
	}
	return pBuffer;
}

// ----------------------------------------------------------------------------
// Virtuelle Funktionen, die bei bestimmten Events gerufen werden -------------

// Initialisierung der Erweiterung --------------------------------------------
// Diese Funktion wird (einmalig) gerufen, wenn die Erweiterung vollständig
// installiert ist

STDMETHODIMP_(BOOL) CIdentsDBExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode) || !InitJumpTable())
		return false;

	try {
		pIIL = new IdIgnoreList();
		pIML = new MCodeIgnoreList();
		m_pPopupMenu = new Menu (ResID(PBDEXTENSIONMENU, &RF()));

	} catch (std::bad_alloc) {
		return FALSE;
	}

	m_pObjProp = CObjectProperties::CreateInstance (m_pUnk ? m_pUnk : this);
	if (NULL == m_pObjProp) return false;

// FehlerMeldungen hier vorbeischicken
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_ERRORMESSAGE);
	RegisterNotification (DEX_HEADERREREAD);

// WindowsNotifikationen anfordern
	RegisterNotification (__DexCmd, FALSE);		// alle DEX_... bei uns vorbeischicken

// PropertyFunktionen installieren
	m_pObjProp -> SetGroupName (ResString (IDS_DESCRIPTIONPROPGROUP, 64));
	_iOPKText = AddPropertyFunction (ResString (ResID (IDS_OBJPROPKTEXT, &RF()), 64), 
					 OPIdentKText, PROPCAPS_OBJPROPTYPE_STRING|PROPCAPS_GENERATED);
	_iOPLText = AddPropertyFunction (ResString (ResID (IDS_OBJPROPLTEXT, &RF()), 64),
					 OPIdentLText, PROPCAPS_OBJPROPTYPE_STRING|PROPCAPS_GENERATED);

// wenn Projekt offen ist, dann IdBase erfragen
// aktuelles Projektverzeichnis besorgen
char cbLocDir[_MAX_PATH];

	if (DEX_GetActiveProject (cbLocDir) != NULL) 
		m_iMkBase = DEX_GetMkBase();

	m_fSysMode = true;

// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
			strcpy (g_cbTRiAS, g_cbCopyrightName);		// default
	}		

// Menu's einbauen
	if (!InstallPopupMenu(0) || !InstallPopupMenu(1))
		return FALSE;

INSTALLMENUITEM imi;

	INITSTRUCT(imi, INSTALLMENUITEM);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = OBJCLASS_MENU_POS;
	imi.iMenuPos = -1;

	DEX_InstallMenuItem (imi);		// Separator anhängen
	InstallMenuItem (IDM_IMPORTCODES, IDS_IMPORT_META, IMINormalMenu, OBJCLASS_MENU_POS);
	InstallMenuItem (IDM_EXPORTCODES, IDS_EXPORT_META, IMINormalMenu, OBJCLASS_MENU_POS);

// Toolbar installieren
	return SUCCEEDED(CreateMetaDataToolBar());
}

// Menues einbauen
bool CIdentsDBExtension::InstallPopupMenu (int iIndex)
{
INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = OBJCLASS_MENU_POS;
	imi.iMenuPos = -1;

// PopUpMenu und MenuText holen
char cbBuffer[64];
HMENU hMenu = m_pPopupMenu -> Handle(API_MENU_HMENU);

	imi.hMenu = GetSubMenu (hMenu, iIndex);
	TX_ASSERT(NULL != imi.hMenu);
	GetMenuString (hMenu, iIndex, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);

	imi.pMenuText = cbBuffer;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

void CIdentsDBExtension::RemovePopupMenus()
{
	for (int i = 0; i < 2; i++) {
	REMOVEMENUITEMEX rmi;

		INITSTRUCT(rmi, REMOVEMENUITEMEX);
		rmi.hDex = hDex();
		rmi.iMenuID = -1;
		rmi.iMenuNum = OBJCLASS_MENU_POS;
		rmi.iFlag = IMINormalMenu;
		rmi.iMenuPos = -1;
		DEX_RemoveMenuItem (rmi);
	}
}

// Diese Funktion wird gerufen, bevor die Erweiterung freigeben werden soll
STDMETHODIMP_(BOOL) CIdentsDBExtension::UnLoadExtension (void)
{
// Toolbar freigeben
	RemoveMetaDataToolBar();

// Menu's rauswerfen
	RemoveMenuItem (IDM_EXPORTCODES, IMINormalMenu, OBJCLASS_MENU_POS);
	RemoveMenuItem (IDM_IMPORTCODES, IDS_IMPORT_META, IMINormalMenu, OBJCLASS_MENU_POS);

REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iFlag = IMINormalMenu;
	rmi.iMenuNum = OBJCLASS_MENU_POS;
	rmi.iMenuPos = -1;
	DEX_RemoveMenuItem (rmi);		// Separator entfernen

	RemovePopupMenus();

// PropertyFunctionen freigeben
	RemovePropertyFunction (_iOPKText);
	RemovePropertyFunction (_iOPLText);

// Notifikationen freigeben
	UnRegisterNotification (DEX_HEADERREREAD);
	UnRegisterNotification (DEX_ERRORMESSAGE);	// FehlerNotifikation
	UnRegisterNotification (DEX_PROJECTOPEN);	// abmelden

// WindowsNotifikationen abmelden
	UnRegisterNotification (__DexCmd, FALSE);		// alle DEX_... bei uns vorbeischicken

	FreeJumpTable();
	return CTriasExtension::UnLoadExtension();
}

// Diese Funktion initialisiert das Menu --------------------------------------
bool CIdentsDBExtension::FindMenuItem (HMENU hMenu, UINT uiID)
{
UINT uiCnt = GetMenuItemCount(hMenu);

	uiID += MenuOffset();
	for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
		if (uiID == GetMenuItemID (hMenu, uiLoop))
			return true;
	}

	return false;		// nichts gefunden
}

STDMETHODIMP_(BOOL) CIdentsDBExtension::MenuInit (HMENU hMenu, LPARAM, HWND)
{
	if (FindMenuItem (hMenu, IDM_ALLIDENTIGNORE)) {
		if (_AllIdentIgnore || (pIIL && pIIL -> Count())) 
			CheckMenuItem (hMenu, IDM_ALLIDENTIGNORE+MenuOffset(), MF_BYCOMMAND|MF_CHECKED);
		else
			CheckMenuItem (hMenu, IDM_ALLIDENTIGNORE+MenuOffset(), MF_BYCOMMAND|MF_UNCHECKED);
	}

	if (FindMenuItem (hMenu, IDM_ALLMCODEIGNORE)) {
		if (_AllMCodeIgnore || (pIML && pIML -> Count()))
			CheckMenuItem (hMenu, IDM_ALLMCODEIGNORE+MenuOffset(), MF_BYCOMMAND|MF_CHECKED);
		else
			CheckMenuItem (hMenu, IDM_ALLMCODEIGNORE+MenuOffset(), MF_BYCOMMAND|MF_UNCHECKED);
	}
	return true;
}

#if !defined(WIN16)
STDMETHODIMP_(BOOL) CIdentsDBExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	if (NULL != hWnd) return false;		// nicht für uns
	
// Stringsladen und an TRiAS schicken
UINT uiRes = 0L;

	switch (uiMenuID) {
	case IDM_DEFIDENT:			uiRes = ID_METADATA_MODIDENT; break;
	case IDM_DELIDENT:			uiRes = ID_METADATA_DELIDENT; break;
	case IDM_DEFMCODE:			uiRes = ID_METADATA_MODMCODES; break;
	case IDM_DELMCODE:			uiRes = ID_METADATA_DELMCODES; break;
	case IDM_ALLIDENTIGNORE:	uiRes = ID_METADATA_ALLIDENTIGNORE; break;
	case IDM_ALLMCODEIGNORE:	uiRes = ID_METADATA_ALLMCODEIGNORE; break;
	case IDM_IMPORTCODES:		uiRes = ID_METADATA_IMPORTCODES; break;
	case IDM_EXPORTCODES:		uiRes = ID_METADATA_EXPORTCODES; break;
	default:
		break;
	}

	if (uiRes != 0L) {
	ResString resMsg (ResID (uiRes, &RF()), _MAX_PATH);
	char cbString[_MAX_PATH];
	
		strcpy (cbString, resMsg);
		strtok (cbString, "\n");
		DEX_SetMessageString (cbString);
		return true;
	}

return false;
}
#endif // WIN16

// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) CIdentsDBExtension::MenuCommand (UINT MenuItemID, HWND)
{
	switch (MenuItemID) {	
//	case IDM_EXTABOUT:	// AboutBox
//		{
//		AboutBox AB (MWind(), ResID (DEFIDABOUT, &RF()));
//
//			AB.Show (Centre);
//		} 
//		return true;
	
	case IDM_DEFIDENT:	// Identifikator definieren
		return DefineIdentifier();

	case IDM_DELIDENT:	// Identifikator löschen
		return DeleteIdentifier();

	case IDM_DEFMCODE:	// MerkmalsCode definieren
		return DefineMerkmal();

	case IDM_DELMCODE:	// MerkmalsCode löschen
		return DeleteMerkmal();

	case IDM_ALLIDENTIGNORE:
		if (_AllIdentIgnore || (pIIL && pIIL -> Count())) {
			_AllIdentIgnore = false;
			if (pIIL) pIIL -> EveryDelete();
		} else 
			_AllIdentIgnore = true;
		break;

	case IDM_ALLMCODEIGNORE:
		if (_AllMCodeIgnore || (pIML && pIML -> Count())) {
			_AllMCodeIgnore = false;
			if (pIML) pIML -> EveryDelete();
		} else
			_AllMCodeIgnore = true;
		break;

// #HK971202: s. MenuInit
//	case IDM_SELPBDNAME:
//		{
//		// Namen auswählen und neu einstellen
//			if (SelectNewPbdName ()) {
//			// Extension wieder sensibilisieren
//				_AllIdentIgnore = false;
//				_AllMCodeIgnore = false;
//				_AllRCodeIgnore = false;
//				if (pIIL) pIIL -> EveryDelete();
//				if (pIML) pIML -> EveryDelete();
//				if (pIRL) pIRL -> EveryDelete();
//				return true;
//			} else
//				return false;
//		}
//		break;

	case IDM_EXPORTCODES:
		return ExportCodes();

// #HK971202: s. MenuInit
//	case IDM_GENERATENEWPBD:
//		{
//			if (GenerateNewPbd()) {
//			// Extension wieder sensibilisieren
//				_AllIdentIgnore = false;
//				_AllMCodeIgnore = false;
//				_AllRCodeIgnore = false;
//				if (pIIL) pIIL -> EveryDelete();
//				if (pIML) pIML -> EveryDelete();
//				if (pIRL) pIRL -> EveryDelete();
//				return true;
//			} else
//				return false;
//		}

#if !defined(WIN16)
	case IDM_IMPORTCODES:
		return ImportCodes();
#endif // WIN16

	default:
		return false;
	}

return false;
}

STDMETHODIMP_(LRESULT) CIdentsDBExtension::Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) {
	case DEX_ERRORMESSAGE:
		return (LRESULT)HandleErrorMessage ((ERRORMESSAGE *)p);

	case DEX_HEADERREREAD:
	case DEX_PROJECTOPEN:
		m_iMkBase = DEX_GetMkBase();
		break;
		
	default:	// alle anderen Notifikationen weiterreichen
		break;
	}
	return CTriasExtension::Notification(iMsg, p);
}


// ----------------------------------------------------------------------------
// sonstige Memberfunktionen --------------------------------------------------

// Behandeln der FehlerNotifikationen -----------------------------------------
short CIdentsDBExtension::HandleErrorMessage (ERRORMESSAGE *pEM) 
{
Pointer *pOldPointer = NULL;
Pointer locPtr (Arrow);
short RC = EC_OKAY;

	switch (pEM -> emiErrCode) {
	case WC_NOIDENT:
		{
			pOldPointer = MWind() -> ChangePointer (&locPtr);
			RC = DefineNewIdent (*(long *)(pEM -> empData));
			MWind() -> ChangePointer (pOldPointer);
			return RC;
		}

	case WC_NOMERKMAL:
		{
			pOldPointer = MWind() -> ChangePointer (&locPtr);
			RC = DefineNewMCode (*(long *)(pEM -> empData));
			MWind() -> ChangePointer (pOldPointer);
			return RC;
		}


	case EC_INVPBDNAME:	// Invalid PBD_Name
		{
		// als zusätzliche Daten wird ein Pointer auf den Buffer
		// übergeben, der den PBDNamen enthält
			pOldPointer = MWind() -> ChangePointer (&locPtr);
			RC = DefineNewPbd ((HPROJECT)(pEM -> empData));
			MWind() -> ChangePointer (pOldPointer);
			return RC;
		}
		
	case EC_NOPBDNAME:	// HeaderEntry fehlt
		{
			pOldPointer = MWind() -> ChangePointer (&locPtr);
			RC = DefineNewPbd ((HPROJECT)(pEM -> empData));
			MWind() -> ChangePointer (pOldPointer);
			return RC;
		}
	}
	return 0;
}


bool CIdentsDBExtension::SelectNewPbdName (HPROJECT hPr)
{
// Neuen DatenBasisNamen holen
ResString resTempl (ResID (IDS_PBDOPENTEMPLATE, &RF()), 50);
ResString resCaption (ResID (IDS_PBDOPENCAPTION, &RF()), 64);
COpenDialog ODlg (MWind(), (char *)resTempl.Addr());

#if !defined(WIN16)
	if (IsWin40()) {
		ODlg.AddFlags (OFN_LONGNAMES|OFN_EXPLORER);
		ODlg.SetHookFcn ((HOOKFCN)PBDName40HookFcn);
	} else
#endif
		ODlg.SetHookFcn ((HOOKFCN)SelPBDNameHookFcn);

	ODlg.SetCaption (resCaption);
	ODlg.AddFlags (OFN_HIDEREADONLY|OFN_FILEMUSTEXIST);
	if (!ODlg.Show()) return false;		// Fehler oder Abbruch

int iLen = ODlg.GetFileNameLen();
char *pDBName = new char [iLen+1];

	if (pDBName == NULL) return false;
	ODlg.GetFileName (pDBName, iLen);	// DBName

        DEX_ModMetaName (hPr, pDBName);		// temporär modifizieren

// Speicher wieder freigeben
	DELETE_OBJ(pDBName);
	return true;	// ok
}

// neue Pbd generieren --------------------------------------------------------
bool CIdentsDBExtension::GenerateNewFilePbd (HPROJECT hPr)
{
// IDENTSDB-Unterverzeichnis ggf. anlegen
char *pLocDir = new char [_MAX_PATH];
char *pPath = new char [_MAX_PATH];
char *pFName = new char [_MAX_PATH+1];
char cDrive[_MAX_DRIVE];

	if (DEX_GetDataSourceName (hPr, pLocDir) == NULL) {
		DELETE_OBJ(pLocDir);
		DELETE_OBJ(pPath);
		DELETE_OBJ(pFName);
		return false;
	}

	_splitpath (pLocDir, cDrive, pPath, pFName, NULL);
	strcat (pPath, ResString (ResID (IDS_IDENTSDBSUBDIR, &RF()), 20));
	if (pFName) {	
		strcat (pFName, ResString (ResID (IDS_IDENTSDBEXT, &RF()), 7));
		strlwr (pFName);
	}
	_makepath (pLocDir, cDrive, pPath, g_cbNil, g_cbNil);

// abschließendes '\\' entfernen
char *cptr;

	if (*(cptr = &pLocDir[strlen(pLocDir)-1]) == '\\')
		*cptr = '\0';

	if (chdir (pLocDir) == -1) {
	// Verzeichnis existiert nicht
		if (mkdir (pLocDir) == ENOENT) {
			DELETE_OBJ(pFName);
			DELETE_OBJ(pLocDir);
			DELETE_OBJ(pPath);
			return false;
		}
	}
	
	{
	// Neuen DatenBasisNamen holen
	ResString resTempl (ResID (IDS_PBDCREATETEMPLATE, &RF()), 50);
	ResString resCaption (ResID (IDS_PBDCREATECAPTION, &RF()), 64);
	CSaveAsDialog SDlg (MWind(), (char *)resTempl.Addr());

		SDlg.SetInitialDir (pLocDir);
		SDlg.SetFileName (pFName);

#if !defined(WIN16)
		if (IsWin40()) {
			SDlg.AddFlags (OFN_LONGNAMES|OFN_EXPLORER);
			SDlg.SetHookFcn ((HOOKFCN)PBDName40HookFcn);
		} else
#endif
			SDlg.SetHookFcn ((HOOKFCN)CreatePBDNameHookFcn);

		SDlg.AddFlags (OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR);
		SDlg.SetCaption (resCaption);

		if (!SDlg.Show()) { 
			DELETE_OBJ(pLocDir);
			return false;
		}
		DELETE_OBJ(pLocDir);

		SDlg.GetFileName (pFName, SDlg.GetFileNameLen());	// DBName
	}

// neue PBD anlegen
CREATEDB cDB;

	INITSTRUCT (cDB, CREATEDB);
	cDB.m_pName = pFName;
	cDB.m_pUser = NULL;
	cDB.m_pPassWd = NULL;
	cDB.m_iMode = DBVNormal;
	
	DEX_CreateNewIdentsDB (cDB);

// PBDNamen setzen
bool fRet = false;

	if (DEX_ModMetaName (hPr, pFName)) {
	// HeaderEintrag generieren
	HeaderEntryX HE (ResString (ResID (IDS_PBDNAME, &RF()), 17), hPr);

		_splitpath (pFName, NULL, NULL, pPath, NULL);
		HE.SetEntryText (pPath);
		fRet = (HE.WriteBack() == EC_OKAY);
	}

	DELETE_OBJ(pPath);
	DELETE_OBJ(pFName);
	return fRet;
}

bool CIdentsDBExtension::GenerateNewCOMPbd (HPROJECT hPr, IStorage *pIStorage)
{
// SubStorage anlegen
IStorage *pISubStorage = NULL;
HRESULT hr = NOERROR;
DWORD dwMode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED;
const LPCSTR pcPbdName = "Beschreibungsdaten";

	hr = pIStorage -> OpenStorage (WideString(pcPbdName), NULL, dwMode, NULL, 0, &pISubStorage);
	if (FAILED(hr)) {	
		if (STG_E_FILENOTFOUND == GetScode(hr)) {
		// existiert noch nicht, anlegen
			dwMode |= STGM_CREATE;
			hr = pIStorage -> CreateStorage (WideString(pcPbdName), dwMode, 0, 0, &pISubStorage);
			if (FAILED(hr)) return false;
		} else
			return false;			// sonstiger Fehler
	}

// neue PBD als COM-SubStorage anlegen
CREATEDBEX cDBEx;

	INITSTRUCT (cDBEx, CREATEDBEX);
	cDBEx.m_pName = NULL;
	cDBEx.m_pUser = NULL;
	cDBEx.m_pPassWd = NULL;
	cDBEx.m_iMode = DBVCompFile;
	cDBEx.m_pIStorage = pISubStorage;
	cDBEx.m_pClsID = &CLSID_TRiASMetaDocument;
	cDBEx.m_pCFStr = "TRiAS.MetaDocument.2";

	if (EC_OKAY != DEX_CreateNewIdentsDB (cDBEx)) {
		pISubStorage -> Release();
		return false;
	}

// PBDNamen setzen
bool fRet = false;

	if (DEX_ModMetaName (hPr, pcPbdName)) {
	// HeaderEintrag generieren: "PBD-NAME":"Name des SubStorages"
	HeaderEntryX HE (ResString (ResID (IDS_PBDNAME, &RF()), 17), hPr);

		HE.SetEntryText ((char *)pcPbdName);
		fRet = (HE.WriteBack() == EC_OKAY);

	// evtl. vorhandenen 'ForceExternPbd' - Eintrag löschen
	HeaderEntryX HE1 (ResString (ResID (IDS_PBDCOMENTRY, &RF()), 17), hPr);

		HE1.DeleteEntry();
	}

	if (fRet) {
		pISubStorage -> Commit (STGC_DEFAULT);
		DEX_SetDirtyGeoDB (true);	// Speichern am Ende erzwingen
	}

	pISubStorage -> Release();
	return fRet;
}

// wenn Projekt ein COM-Document ist, dann PBD direkt als SubStorage erzeugen
// ansonsten in einem Unterverzeichnis
bool CIdentsDBExtension::GenerateNewPbd (HPROJECT hPr)
{
IStorage *pIStorage = NULL;

	DEX_GetDataSourceStorage(hPr, pIStorage);		// ProjektStorage abfragen
	if (NULL == pIStorage) 
		return GenerateNewFilePbd(hPr);
	else {
	bool fRet = GenerateNewCOMPbd (hPr, pIStorage);

		pIStorage -> Release();
		return fRet;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ControlBar styles (from AFXRES.H)
#define CBRS_ALIGN_LEFT     0x1000L
#define CBRS_ALIGN_TOP      0x2000L
#define CBRS_ALIGN_RIGHT    0x4000L
#define CBRS_ALIGN_BOTTOM   0x8000L
#define CBRS_ALIGN_ANY      0xF000L

#define CBRS_BORDER_LEFT    0x0100L
#define CBRS_BORDER_TOP     0x0200L
#define CBRS_BORDER_RIGHT   0x0400L
#define CBRS_BORDER_BOTTOM  0x0800L
#define CBRS_BORDER_ANY     0x0F00L

#define CBRS_TOOLTIPS       0x0010L
#define CBRS_FLYBY          0x0020L
#define CBRS_FLOAT_MULTI    0x0040L
#define CBRS_BORDER_3D      0x0080L
#define CBRS_HIDE_INPLACE   0x0008L
#define CBRS_SIZE_DYNAMIC   0x0004L
#define CBRS_SIZE_FIXED     0x0002L
#define CBRS_FLOATING       0x0001L

#define AFX_IDW_DOCKBAR_TOP             0xE81B

DefineSmartInterface(TRiASBar);
// DefineSmartInterface(TRiASToolBar);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASUIOwner);

// Toolbar instatiieren -------------------------------------------------------
const int NOSTRING = 0;
const TBBUTTON buttonsMeta[] =
{	
	{ 0, ID_METADATA_MODIDENT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_METADATA_DELIDENT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 2, ID_METADATA_MODMCODES, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 3, ID_METADATA_DELMCODES, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
//	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
//	{ 4, ID_METADATA_MODRCODES, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
//	{ 5, ID_METADATA_DELRCODES, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
};
#define NUMBUTTONS_META (sizeof(buttonsMeta)/sizeof(buttonsMeta[0]))

TBBUTTON *CopyButtons (const TBBUTTON *pBttns, int iCnt)
{
	try {
	TBBUTTON *pBtnCopy = new TBBUTTON [iCnt];

		for (int i = 0; i < iCnt; i++) 
			pBtnCopy[i] = pBttns[i];

		return pBtnCopy;
	} catch (...) {
		return NULL;
	} 
}

HRESULT CIdentsDBExtension::CreateMetaDataToolBar (void)
{
TBBUTTON *pBtnCopy = NULL;

	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	WTRiASBar Bar;
	ResString strCap (ResID (IDS_METATOOLCAPTION, &RF()), 128);
	DWORD dwStyle = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
					CBRS_BORDER_ANY|CBRS_FLYBY|CBRS_FLOATING;

		if (IsWin40()) dwStyle |= CBRS_BORDER_3D;

	// ToolBar erzeugen
	HRESULT hr = BarCont -> AddTRiASBar (strCap, dwStyle, TRIASTOOLBAR_PREDEFINED, Bar.ppi());

		if (FAILED(hr)) throw hr;

	// Bitmaps hinzufügen
	WTRiASToolBar Tools (Bar);		// throws HRESULT
	int iOffset = -1;

		hr = Tools -> AddBitmap (g_hInstance, IDB_METADATA, 6, &iOffset);
		if (FAILED(hr)) return hr;

		pBtnCopy = CopyButtons (buttonsMeta, NUMBUTTONS_META);
		if (NULL == pBtnCopy) throw E_OUTOFMEMORY;

	TBBUTTON *pCurr = pBtnCopy;

		for (int i = 0; i < NUMBUTTONS_META; i++, pCurr++) {
			if (!(TBSTYLE_SEP & pCurr -> fsStyle))
				pCurr -> iBitmap += iOffset;
//			pBtnCopy -> idCommand += MenuOffset();
		}
	
	// UIOwner erzeugen
	WTRiASUIOwner UIOwner;
	
		try {
		CComObject<CAuxUIOwner> *pOwner = NULL;
		HRESULT hr = CComObject<CAuxUIOwner>::CreateInstance(&pOwner);

			if (FAILED(hr)) throw hr;
			UIOwner = (ITRiASUIOwner *)pOwner;		// AddRef !
		
			hr = pOwner -> SetExtension (this);
			if (FAILED(hr)) throw hr;
		
		} catch (_com_error &hr) {
			return _COM_ERROR(hr);
		} catch (...) {
			throw E_OUTOFMEMORY;
		}			
	
	// Buttons hinzufügen
		hr = Tools -> AddButtons (pBtnCopy, NUMBUTTONS_META, UIOwner);
		if (FAILED(hr)) throw hr;

	// Toolbar jetzt floaten
	Point pt (50, 50);

		ClientToScreen (MWind() -> Handle(), (POINT *)&pt);
		hr = Tools -> FloatBar ((POINT &)pt, dwStyle);
		if (FAILED(hr)) throw hr;

		DELETE_OBJ(pBtnCopy);

	} catch (_com_error &hr) {
		DELETE_OBJ(pBtnCopy);
		return _COM_ERROR(hr);
	}

return NOERROR;
}

HRESULT CIdentsDBExtension::RemoveMetaDataToolBar (void)
{
	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	ResString strCap (ResID (IDS_METATOOLCAPTION, &RF()), 128);

	// ToolBar beseitigen
		return BarCont -> DeleteTRiASBar (strCap);

	} catch (_com_error &hr) {
		return _COM_ERROR(hr);
	}
}

#if defined(_SUPPORT_QUERYDEFS)
///////////////////////////////////////////////////////////////////////////////
// Nachsehen, ob Zuordnungsobjektklassen verfügbar sind
DefineSmartInterface(TriasXtension);

BOOL CIdentsDBExtension::HasQueryDef()
{
WTriasXtension QueryDef;

	if (SUCCEEDED(QueryDef.CreateInstance (CLSID_QueryDefExt))) 
		return QueryDef -> GetCapabilities (DEXCAP_NOTLOADED) ? FALSE : TRUE;

	return FALSE;
}
#endif // defined(_SUPPORT_QUERYDEFS)


