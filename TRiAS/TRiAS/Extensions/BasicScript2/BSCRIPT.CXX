// Makroporgrammierung mit BasicScript 2.1 ------------------------------------
// File: BSCRIPT.CXX

#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <ospace/file/path.h>

#if !defined(WIN16)
#include "afxcmn.h"
#include <registrx.hxx>
#endif // WIN32

#include <build.h>

#include <new>
#include <io.h>
#include <ctype.h>
#include <float.h>

#include <olectl.h>
#include <shlwapi.h>
#include <delayimp.h>

#include <initguid.h>

#include <iobjman.h>
#include <Esnecil.h>

#include <oleguid.h>
#include <bscrguid.h>
#include <propguid.h>
#include <itriasap.h>
#include <ixtnext.hxx>
#include <triastlb.h>
#define _TriasTLB_H_
#include <dirisole.h>
#include <xtsnguid.h>
#include <ipropseq.hxx>

#include <triastlb_i.c>
//#include <triashelper_i.c>

#include "objmanguid.h"
#include "macrguid.h"

#include "version.h"

#include "conststr.h"
 
#include "iscrprop.h"

#include "bscrext.hxx"

#include "projscr.h"
#include "triasext.h"
#include "macro.h" 
#include "scrptdlg.h"
#include "ofeatpp.h"
#include "proppext.h"
#include "oftppxt.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "runebobs.h"
#include "filtdlg2.h"
#include "filtscr.h"
#include "objfeat.h"
#include "strinfo.h"        
#include "toolbarx.h"
#include "splitter.h"
#include "split.h"
#include "RegisterEbs.h"
#include "wrapxt.h"
#include "expall.h"

#include "tmplman.h"
#include "MacroIntroDlg.h"

#define OS_NO_STREAM_SUPPORT

#define GUID_CCH			39	// Characters in string form of guid, including '\0'
#define MACRO_ITEM_POS		8	// Position des Macrosmenues im Extramenu

extern "C" TCHAR g_pDLLName[_MAX_PATH];

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

SummitModul g_SummitModuls[] = {
	{ PRODUCT_COM_NAME ebMODEXT, false },	/* Compiler */
	{ PRODUCT_DC_NAME  ebMODEXT, false },	/* Debugger Control */
	{ PRODUCT_RUN_NAME ebMODEXT, false },	/* Runtime */
	{ PRODUCT_DED_NAME ebMODEXT, false },	/* Dialog Editor DLL */
	{ "", false },	
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Smartinterfaces
//DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(PersistStorage);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(ScriptProperty);
DefineSmartInterface(Storage);
DefineSmartInterface(StreamInfo);
DefineSmartInterface(OleItemContainer);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(AddScriptProperty);
DefineSmartInterface(EnumUnknown);
DefineSmartInterface(ObjectManagement);

//////////////////////////////////////////////////////////////////////////////////////////////
// Enumeratoren
DefineEnumerator2(os_wstring, IID_IEnumos_wstring);
DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);

//////////////////////////////////////////////////////////////////////////////////////////////
// globale Variablen
namespace {
	char cbTrayMsgBuffer[64];

	LPCSTR GetTrayMsgName(LPCSTR pcTemplate)
	{
		wsprintf (cbTrayMsgBuffer, pcTemplate, GetCurrentProcessId());
		return cbTrayMsgBuffer;
	}
}

UINT CMacroScriptExtension::m_uiTrayMsg = RegisterWindowMessage(GetTrayMsgName("BScript_TrayIconMsg_%lx"));
UINT CMacroScriptExtension::m_uiCreateTrayMsg = RegisterWindowMessage("TaskbarCreated");

//////////////////////////////////////////////////////////////////////////////////////////////
// globale Funktionen
CRunningObjectsHelper * GetRunningObjectsHelper(void);
UINT FileDialog (LPCSTR pcPath, CWnd *pParent, CString & strFileName, BOOL fOpen = true, LPCSTR lpcstrCaption = NULL);
BOOL RegPropActPage(REFCLSID rclsid, LPCSTR pcProgID); // z. b. TRiASEx.FilterScript.1
BOOL UnRegPropActPage(LPCSTR pcProgID); // z. b. TRiASEx.FilterScript.1
BOOL UnRegAutoStartScriptFile();
BOOL RegAutoStartScriptFile();
BOOL RegFileExtensions();
BOOL RegFileExtensions(LPCSTR, LPCSTR, int = -1);
BOOL UnRegFileExtensions();
BOOL UnRegFileExtensions(LPCSTR);
HRESULT MakePathName(LPCSTR pPathName, LPSTR pNameToUse);
CString GetPathName (LPCSTR pcPath);
BOOL LoadString(CString & str, int IDS);
CString GetDefaultName(int IDS);
HRESULT GetInstalledSummitModuls (void);
HRESULT IsObjectManagementModulInstalled (void);
HRESULT MakeSubStorage(LPSTORAGE pIRootStorage, LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						BOOL fDirect, CLSID clsID);
HRESULT MakeDummyStorage(LPCSTR lpstr, LPSTORAGE *lplpStor);
HRESULT OldGeneralStorage(LPSTORAGE lpIRootStorage, int IDS, REFIID riid);
HRESULT OldGeneralStreamInfo(REFCLSID riid, IObjectManagement *pObjM, int IDS, IStreamInfo **ppIStreamInfo);
HRESULT RunThread(ebHTHREAD hThread, ebHSCRIPT hScript);

HRESULT MakeFileName(LPCSTR pPathName, LPSTR pNameToUse, LPCSTR pcFileExt);
CString CorrectExtension (CString &rPath, UINT uiResIDExt);

HRESULT ReadIniAutoLoadScript (char *pcMacroName, int iLen);
BOOL	ReadRegSettingsMacrosDirectory(char *pc, DWORD dwL);
BOOL	ReadRegSettingsLastOpenFile(char *pc, DWORD dwL);
BOOL	SaveRegSettingsLastOpenFile (LPCSTR pc);
BOOL	SaveRegSettingsBSVersion (void);
BOOL	ReadRegSettingsBSVersion(HWND);
BOOL	SaveRegSettingsAutoLoadFile (LPCSTR pc);
BOOL	ReadRegSettingsAutoLoadFile (LPSTR pc, DWORD dwL);

void MessageOldProject(HWND hWnd);
void ErrorMessage(HWND h, LPCSTR lpcstrMessage);
HRESULT MessageRuntimeError(ebLPCSTR lpMsg, DWORD dwErrNum, ebWORD wLineNr, CRunErr **ppRunErr);

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Rückruffunktionen
extern "C" 
ebHSCRIPT ebCALLBACK _XTENSN_EXPORT RequestorProc (ebHTHREAD hThread, ebLPCTSTR pcMacroName, long lParam)
{
	ASSERT(pcMacroName);

	if (!GetRunningObjectsHelper() -> GetOpenProject()) 
		return NULL;

ebHSCRIPT hScript = NULL;
CRelScripts *pRelScripts = (CRelScripts *)lParam;

	if (pRelScripts){
	// ScriptName des übergeordneten Scripts geben lassen
	// vorher bei Run() gesetzt							 1 long == 4 BYTE
	LPSTR lpstrSuperItem = (LPSTR)ebThread_GetLong(hThread, SETLONG_NAME);
	char strSubItem[_MAX_PATH];
	HRESULT hr = pRelScripts -> GetItem(lpstrSuperItem, pcMacroName, strSubItem, _MAX_PATH, &hScript);

		if (SUCCEEDED(hr)) 
			return hScript;
	}
	return NULL;
}

extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnRuntimeError (
	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
	ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext)
{
// Wird für Running-Scripts erzeugt
CRunErr* pRunErr = NULL;
HRESULT hr = MessageRuntimeError(lpMsg, dwErrNum, wLinNr, &pRunErr);

	if (FAILED(hr)) return;

IObjectManagement *pIOM = g_pBSE -> GetGeneralScripts();

	ASSERT(NULL != pIOM);
	if (NULL == pIOM) return;

IStreamInfo *pISI = g_pBSE -> GetInfoGeneralScripts();

	ASSERT(NULL != pISI);
	if (NULL == pISI) return;

	pRunErr -> CreateDebugger (WM_CLOSERUNTIMEDEBUGGERDIALOG, lParam, wLinNr, pIOM, pISI);
}

extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnObjFeatRuntimeError (
	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
	ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext)
{
// Wird für Running-Scripts erzeugt
CRunErr* pRunErr;
HRESULT hr = MessageRuntimeError(lpMsg, dwErrNum, wLinNr, &pRunErr);

	if (FAILED(hr)) return;

IObjectManagement *pIOM = g_pBSE -> GetObjectFeatureScripts();

	ASSERT(NULL != pIOM);
	if (NULL == pIOM) return;

IStreamInfo *pISI = g_pBSE -> GetInfoObjFeatureScripts();

	ASSERT(NULL != pISI);
	if (NULL == pISI) return;

	pRunErr -> CreateDebugger(WM_CLOSERUNTIMEDEBUGGERDIALOG, lParam, wLinNr, pIOM, pISI);
}

extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnFilterRuntimeError (
	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
	ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext)
{
// Wird für Running-Scripts erzeugt
CRunErr* pRunErr;
HRESULT hr = MessageRuntimeError(lpMsg, dwErrNum, wLinNr, &pRunErr);

	if (FAILED(hr)) return;

IObjectManagement *pIOM = g_pBSE -> GetFilterScripts();

	ASSERT(NULL != pIOM);
	if (NULL == pIOM) return;

IStreamInfo *pISI = g_pBSE -> GetInfoFilterScripts();

	ASSERT(NULL != pISI);
	if (NULL == pISI) return;

	pRunErr -> CreateDebugger(WM_CLOSERUNTIMEDEBUGGERDIALOG, lParam, wLinNr, pIOM, pISI);
}

// Routine, über die die Module enumeriert werden -----------------------------
extern "C" 
ebBOOL ebCALLBACK _XTENSN_EXPORT ebGetNextModule (ebLPSTR lpFileName, long lParam)
{
	if (NULL == g_pTE) 
		return false;

	return g_pBSE -> GetNextModule (lpFileName);
}

// Routine, die regelmäßig während der Ausführung eines Threads gerufen wird --
extern "C" 
void ebCALLBACK _XTENSN_EXPORT ebPCodeCallBack (ebHTHREAD hThread, ebLONG)
{
	CallMessageQueue();		// Yielding
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Erweiterung an sich 

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden. 
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_MacroScriptExtension, sizeof (GUID));
	return true;
}

//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.MacroScript.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine 
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		RegPropActPage (CLSID_FilterScript, TEXT("TRiASEx.FilterScript.1"));
		RegAutoStartScriptFile();
		RegFileExtensions();

		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_MacroScriptExtension, 
				TEXT("TRiAS.MacroScript.1"), IDS_LONGCLASSNAME,
				SCRIPT_MAJORVERSION, SCRIPT_MINORVERSION,
				EFPreLoad|EFPriorityLoad2);
	} else {
	// RegDB säubern, evtl. Fehler ignorieren
		UnRegPropActPage (TEXT("TRiASEx.FilterScript.1"));
		UnRegAutoStartScriptFile();
		UnRegFileExtensions();
		return ExtOleUnregisterClass (CLSID_MacroScriptExtension, TEXT("TRiAS.MacroScript.1"));
	}
	return true;	// alles ok
}

// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden. Die Destruktoren sind 'virtual', so daß auch so
// alles sauber aufgeräumt werden kann.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CMacroScriptExtension::CMacroScriptExtension (void)
	: CTriasExtension()
{
	m_pIGeneralScripts = NULL;	
	m_pIFilterScripts = NULL;	
	m_pIObjFeatureScripts = NULL;	
	
	m_pIGeneralScriptsInfo = NULL;	
	m_pIFilterScriptsInfo = NULL;	
	m_pIObjFeatureScriptsInfo = NULL;	

	m_pebInst = NULL;
	m_hDCInst = NULL;
	m_pSplitterDebugger = NULL;
	m_pRunErr = NULL;
	m_pRunningObjHelper = NULL;

	m_lpDummyStorage = NULL;
	m_pTrayIcons = NULL;
	m_lCountRunning = -1L;

// registriert sich selbst als ExtensionModule
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (g_hInstance, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	USES_CONVERSION;
	if (cbShortName == _MAX_PATH)
		return;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

	RegisterExtModule (OLE2A(pszModule));
	m_fProjectIsClosing = false;

	m_pPopupMenu = NULL;
}

// Destruktor -----------------------------------------------------------------
CMacroScriptExtension::~CMacroScriptExtension (void) 
{
	_ASSERTE(-1L == m_lCountRunning);

	if (m_hDCInst) 
		FreeLibrary(m_hDCInst);
	m_hDCInst = NULL;

	DELETE_OBJ(m_pRunningObjHelper);
	DELETE_OBJ(m_pebInst);
	DELETE_OBJ(m_pPopupMenu);
	DELETE_OBJ(m_pTrayIcons);
}

// Da der Compiler in CreateInstance(... nicht weiß, welche FinalConstruct der Basisklassen CObjectProps 
// und CTriasExtension gerufen werden soll 
HRESULT CMacroScriptExtension::FinalConstruct (void)
{
	RETURN_FAILED_HRESULT(CTriasExtension::FinalConstruct());
	RETURN_FAILED_HRESULT(CObjectProperties::FinalConstruct());
	return S_OK;	
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung durch 
// TRiAS gerufen. Hier sollten alle notwendigen Initialisierungen erfolgen. Die Semantik 
// hat sich nicht geändert.
#if defined(WIN32)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

STDMETHODIMP_(BOOL) CMacroScriptExtension::InitExtension (short iMode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

HRESULT hr = NOERROR;

	try {	
	// Initialisierung der BasisKlasse
		if (!CTriasExtension::InitExtension (iMode)) _com_issue_error(E_FAIL);

		{
		CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
		DWORD dwSize = _MAX_PATH;

			if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
				strcpy (g_cbTRiAS, g_cbCopyrightName);		// default
		}		

		InstallMacroMenu();				// Menu einbauen
		RegisterNotifications();		// Notifikationen anmelden	

	// Version der SUMMIT-Module stimmt nicht mit BS_Extension-Version überein
		if (!ReadRegSettingsBSVersion(hWnd())) _com_issue_error(TYPE_E_REGISTRYACCESS);		
	
	// Welche Summit-Dll's sind auf diesem Rechner geladen ?
		THROW_FAILED_HRESULT(GetInstalledSummitModuls());
	
	// BScript vorbereiten
	ebWORD wFlags = EBINIT_SEARCH_DIRECTORY | EBINIT_SEARCH_PROC;

		if (g_SummitModuls[COMPILER].fIsInstalled) 
			wFlags |= EBINIT_USECOMPILER;
		if (g_SummitModuls[RUNTIME].fIsInstalled)
			wFlags |= EBINIT_USERUNTIME;
	
	// MemoryException
		m_pebInst = new CebInstance (wFlags, ebGetNextModule);
		if (NULL == m_pebInst) _com_issue_error(E_OUTOFMEMORY);

		m_pRunningObjHelper = CRunningObjectsHelper::CreateRunningObjectsHelper(m_pebInst);
		if (NULL == m_pRunningObjHelper) _com_issue_error(E_OUTOFMEMORY);

	// Wenn Erweiterung nachgeladen wird, ObjektManagement (in objman?.dll) laden
		THROW_FAILED_HRESULT(LoadScriptManagers());

	// Immer schon vorher wegen BSWrapperExtension's laden
		THROW_FAILED_HRESULT(LoadManagement(&m_pIGeneralScripts, CLSID_CObjectManagement));

	// Für Filerunning laden
		THROW_FAILED_HRESULT(m_pRunningObjHelper -> InitLinkAndStorage(m_pIGeneralScripts, NULL));

	// TrayIconWnd initialisieren
		m_pTrayIcons = new CAnimatedTrayIcon;
	}
	catch (bad_alloc)
	{
		ErrorMessage(GetActiveWindow(), "Speicherallokierung in InitExtension() ist fehlgeschlagen\n.");
		return false;
	}
	catch (_com_error& e)
	{
		char str[MAXSTRLENGTH];
		wsprintf (str, "InitExtension() ist wegen Fehler 0x%x fehlgeschlagen.\n", _COM_ERROR(e));
		ErrorMessage(GetActiveWindow(), str);
		return false;
	}
	return true;
}

void CMacroScriptExtension::ResetExtension()
{
	if (m_pSplitterDebugger)
		m_pSplitterDebugger -> DestroyWindow();
	m_pSplitterDebugger = NULL;

	DestroyRunTimeErrorDebugger();

	UnRegisterNotifications ();	
	UnLoadScriptManagers();

	RemoveAllPropertyFunctions ();
}

void CMacroScriptExtension::RegisterNotifications ()
{
// zum Schließen des Debuggers	
	RegisterNotification (WM_CLOSEDEBUGGERDIALOG, false);	
	RegisterNotification (WM_CLOSERUNTIMEDEBUGGERDIALOG, false);

	RegisterNotification (DEX_INITIALIZEDSERVER);
	RegisterNotification (DEX_N_EXTENSIONSLOADED);
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_ISCLOSEDPROJECT);        
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);

	RegisterNotification (DEX_N_SAVESAMESTORAGE);		// für alle Fälle
	RegisterNotification (DEX_N_SAVEOTHERSTORAGE);		
	RegisterNotification (DEX_N_SAVECOMPLETED);		
	RegisterNotification (DEX_N_HANDSOFFSTORAGE);		

// TrayMessages bei TRiAS anmelden
	RegisterNotification (m_uiTrayMsg, FALSE);
	RegisterNotification (m_uiCreateTrayMsg, FALSE);
}

void CMacroScriptExtension::UnRegisterNotifications ()
{
// zum Schließen des Debuggers	
	UnRegisterNotification (WM_CLOSEDEBUGGERDIALOG, false);	
	UnRegisterNotification (WM_CLOSERUNTIMEDEBUGGERDIALOG, false);
	
	UnRegisterNotification (DEX_INITIALIZEDSERVER);
	UnRegisterNotification (DEX_N_EXTENSIONSLOADED);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_ISCLOSEDPROJECT);        
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);

	UnRegisterNotification (DEX_N_SAVESAMESTORAGE);		// für alle Fälle
	UnRegisterNotification (DEX_N_SAVEOTHERSTORAGE);		
	UnRegisterNotification (DEX_N_SAVECOMPLETED);		
	UnRegisterNotification (DEX_N_HANDSOFFSTORAGE);		

// TrayMessages bei TRiAS anmelden
	UnRegisterNotification (m_uiTrayMsg, FALSE);
	UnRegisterNotification (m_uiCreateTrayMsg, FALSE);
}

// Diese Funktion wird gerufen bevor die Erweiterung freigegeben wird.
// An dieser Stelle kann (und soll) der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, und sonstige Aufräumarbeiten durchgeführt werden.
// Die Semantik hat sich nicht geändert.
STDMETHODIMP_(BOOL) CMacroScriptExtension::UnLoadExtension (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	RemoveMacroMenu();
	StopAllRun ();
	SaveRegSettingsBSVersion();
	ResetExtension();

	DELETE_OBJ(m_pTrayIcons);

	return CTriasExtension::UnLoadExtension();
}

BOOL CMacroScriptExtension::InstallMacroMenu()
{
#if _TRiAS_VER < 0x0400
// Berechtigungen testen
	if (0 == g_dwVer4) {
	CCurrentUser regCfg (KEY_READ, g_cbCfgKey);
	DWORD dwCfg = 0L;

		if (!regCfg.GetDWORD (g_cbFullInstall, dwCfg) || dwCfg != MAGIC_FULLINSTALL)
			return TRUE;		// Menu nicht installieren, da nur MinimalInstallation
	} else
#endif // _TRiAS_VER < 0x0400
	{
	VERIFYLICENSE VL;

		INITSTRUCT(VL, VERIFYLICENSE);
		VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_LessOrEqual;
		VL.lLevelOrOption = CKILEVEL_PLUS;
		if (!DEX_VerifyLicenseLevel(VL))
			return TRUE;		// kein UI installieren
	}

// erst Separator einfügen
//	InstallMenuItem((UINT)-1, 0, IMINormalMenu, EXTRA_MENU_POS);

// PopupMenu einbauen
	if (NULL == m_pPopupMenu) {
		ATLTRY(m_pPopupMenu = new CMenu());
		if (NULL == m_pPopupMenu || !m_pPopupMenu -> LoadMenu (IDR_MACROMENU))
			return FALSE;
	}

INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = EXTRA_MENU_POS;
	imi.iMenuPos = -1;

// PopUpMenu und MenuText holen
char cbBuffer[64];

	imi.hMenu = GetSubMenu (m_pPopupMenu -> m_hMenu, 0);
	ASSERT(NULL != imi.hMenu);
	GetMenuString (m_pPopupMenu -> m_hMenu, 0, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);

	if (!(DEX_QueryMode() & QMSysAdmin)) {
	int iCnt = GetMenuItemCount (imi.hMenu);

		RemoveMenu (imi.hMenu, iCnt-2, MF_BYPOSITION);		// Separator entfernen
		RemoveMenu (imi.hMenu, iCnt-2, MF_BYPOSITION);		// "FilterScript" entfernen
	}

	imi.pMenuText = cbBuffer;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

void CMacroScriptExtension::RemoveMacroMenu()
{
#if _TRiAS_VER < 0x0400
// Berechtigungen testen
	if (0 == g_dwVer4) {
	CCurrentUser regCfg (KEY_READ, g_cbCfgKey);
	DWORD dwCfg = 0L;

		if (!regCfg.GetDWORD (g_cbFullInstall, dwCfg) || dwCfg != MAGIC_FULLINSTALL)
			return;		// Menu nicht installiert, da nur MinimalInstallation
	} else 
#endif // _TRiAS_VER < 0x0400
	{
	VERIFYLICENSE VL;

		INITSTRUCT(VL, VERIFYLICENSE);
		VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_LessOrEqual;
		VL.lLevelOrOption = CKILEVEL_PLUS;
		if (!DEX_VerifyLicenseLevel(VL))
			return;		// kein UI installiert
	}

REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iMenuNum = EXTRA_MENU_POS;
	rmi.iFlag = IMINormalMenu;
	rmi.iMenuPos = -1;
	DEX_RemoveMenuItem (rmi);

//	RemoveMenuItem ((UINT)-1, IMINormalMenu, EXTRA_MENU_POS);
}

STDMETHODIMP_(LRESULT) CMacroScriptExtension::Notification (WPARAM iMsg, LPARAM p)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

HRESULT hr = NOERROR;
LPSTORAGE pIStorage = NULL;

	switch (iMsg) 
	{
	case DEX_N_EXTENSIONSLOADED:	// TRiAS fertig initialisiert
	// an dieser Stelle haben sich alle Erweiterungen angemeldet
		{		// Initialisierung von BasicScript
			Reset();
			if (!ebInst().Create()) 
			{
			// sonstige Initialisierungen
				ebInst().SetPublicSpace (0x00100000L);	// 1MByte StringSpace
				ebInst().SetWindow (hWnd());		// ParentWindow
				ebInst().SetViewportParent(hWnd());	
				ebInst().SetPcodeCallbackProc (ebPCodeCallBack, (ebLONG)this);
			
			// Runtimeerror-Callbackfunktion anmelden				
				ebInst().SetRuntimeErrorProc(&OnRuntimeError, 0);
				// Verschicken (auch an BasicScriptWrapper), dass ebInstance erzeugt
				DEXN_ScriptingEngineActive();
				AutoLoadScriptExtern ();
			} 
			else 
			{
				ResetExtension();
				return false;
			}
		}
		break;          
	case DEX_INITIALIZEDSERVER:
		break;
	case DEX_PROJECTOPEN:
		{
			try 
			{
			// Lädt ALLE Storages und Streamnamen 
				THROW_FAILED_HRESULT(LoadScriptManagers());

			// AutoLoad eines File oder Stream-Scripts
				AutoLoadScript();

			// gespeicherte Objekteigenschaften installieren
				THROW_FAILED_HRESULT(InstallObjectProperties());

			// Debugger eventuell noch vorhanden -> Init mit neuem Objektmanegement
				if (m_pSplitterDebugger)
					m_pSplitterDebugger -> Init (NULL, false, NULL, NULL);
				m_fProjectIsClosing = false;
			}
			catch (_com_error &)
			{
				ResetExtension();
			}
		}
		break;

	case DEX_ISCLOSEDPROJECT:
		{	
			VERIFY(RemoveAllPropertyFunctions ());
			DestroyRunTimeErrorDebugger();
			// Makros in jedem Fall entladen, wenn Projekt geschlossen wird
			UnLoadScriptManagers();
		}
        break;

	case DEX_PROJECTCLOSE:		
		break;

	case DEX_N_PROJECTTOCLOSE:		
		{// an dieser Stelle leere Storages löschen
			if (m_pSplitterDebugger)
				m_pSplitterDebugger -> ResetDebuggerIfOnClose();
			m_fProjectIsClosing = true;
			// Storage altes Projekt freigeben
			if(m_lpDummyStorage)
			{
				VERIFY(SUCCEEDED(Save (NULL, true)));
				VERIFY(SUCCEEDED(SaveCompleted (NULL)));
				VERIFY(SUCCEEDED(HandsOffStorage ()));
				RELEASE(m_lpDummyStorage);
			}
		}	
		break;
	case DEX_N_SAVESAMESTORAGE:
	// im gleichen Storage abspeichern
		{
	// Save Infos of all Objects to Streams in Containers
			VERIFY(SUCCEEDED(Save (NULL, true)));
		}
		break;
	case DEX_N_SAVEOTHERSTORAGE:
	// im anderen Storage abspeichern
		{
	// Save Infos of all Objects to Streams in Containers
			VERIFY(SUCCEEDED(Save ((LPSTORAGE)p, false)));
		}
		break;

	case DEX_N_SAVECOMPLETED:
	// Das Speichern abschliessen.
	// Wenn "Kopie speichern als", alten Substorage beibehalten
	// Wenn "Seichern unter", dann neuen Substorage öffnen
		{
			VERIFY(SUCCEEDED(SaveCompleted ((LPSTORAGE)p)));
		}
		break;
	case DEX_N_HANDSOFFSTORAGE:
	// Storages schliessen bzw. freigeben
		{
			VERIFY(SUCCEEDED(HandsOffStorage ()));
		}
		break;
	default:
		break;
	}

return false;
}

STDMETHODIMP_(LRESULT) CMacroScriptExtension::WindowsNotification (
	UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

HRESULT hr = NOERROR;

	switch (wMsg) {
	case WM_CLOSEDEBUGGERDIALOG:
	// vorher angelegt in CreateDebugger() und schon zerlegt bei DestroyWindow()
		m_pSplitterDebugger = NULL;
		break;

	case WM_CLOSERUNTIMEDEBUGGERDIALOG:
	// bei Laufzeitfehler, dieser Debuggerdialog offen
		DestroyRunTimeErrorDebugger();
		break;

	case WM_CLOSEBREAKPOINTDEBUGGERDIALOG:
		break;	// erstmal nichts

	default:
		if (m_uiTrayMsg == wMsg || m_uiCreateTrayMsg == wMsg)
			return HandleTrayMessages (wMsg, wParam, lParam);
		break;
	}
	return false;
}

STDMETHODIMP_(BOOL) CMacroScriptExtension::MenuInit (
	HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == m_pPopupMenu)
		return FALSE;

	if (hWnd == 0 && hMenu == GetSubMenu (m_pPopupMenu -> m_hMenu, 0)) {
	UINT uiEnabled = (NULL == m_pebInst || NULL == m_pRunningObjHelper || m_pSplitterDebugger) ? MF_GRAYED : MF_ENABLED;

		m_pPopupMenu -> EnableMenuItem (IDM_DBSCRIPT+MenuOffset(), MF_BYCOMMAND | uiEnabled);		

		if (DEX_QueryMode() & QMSysAdmin)
			m_pPopupMenu -> EnableMenuItem (IDM_FILTERSCRIPT+MenuOffset(), MF_BYCOMMAND | uiEnabled);	
			
		if (!g_SummitModuls[DEBUGGER].fIsInstalled)
			uiEnabled = MF_GRAYED;
		m_pPopupMenu -> EnableMenuItem (IDM_STORAGEMACRO+MenuOffset(), MF_BYCOMMAND | uiEnabled);	
			
//		pExtMenu() -> EnableMenuItem (IDM_OBJFEAT+MenuOffset(), MF_BYCOMMAND | uiEnabled);		
//		pExtMenu() -> EnableMenuItem (IDM_FILEMACRO+MenuOffset(), MF_BYCOMMAND | uiEnabled);		
		return true;
	}
	return false;		// nicht für uns
}

STDMETHODIMP_(BOOL) CMacroScriptExtension::MenuCommand (UINT uiMenuID, HWND hWnd) 
{               
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CWaitCursor WC;
HRESULT hr = NOERROR;

	switch (uiMenuID) {
	case IDM_DBSCRIPT: 
		return MacroScriptCall();		// OpenStorageMacro true

	case IDM_STORAGEMACRO: 
		return MacroScriptCallForFrame();

//	case IDM_FILEMACRO:
//		{
//			CString strOpenFile;
//			if (false == FileDialog (NULL, strOpenFile))
//				return true; // Cancel
//			return MacroScriptCallForFrame(strOpenFile, true);// OpenFile true
//		}
//		break;				

	case IDM_FILTERSCRIPT: 
		return SUCCEEDED(RunSequence());

	default:
		break;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// *** IExtendBScript methods *** ---------------------------------------------
STDMETHODIMP CMacroScriptExtension::RegisterExtModule (LPCSTR pModule)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (m_Modules.AddModule (pModule)) return NOERROR;
	return E_OUTOFMEMORY;
}

STDMETHODIMP CMacroScriptExtension::FireEvent (LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// Schon entladen, nachdem Projekt entladen ist 
	if (NULL == m_pRunningObjHelper) 
		return S_FALSE;
	if (0 == strcmp("OnPaintingView", pEntry) || 0 == strcmp("OnViewPainted", pEntry)) 
		return S_FALSE;

// wenn DebuggerFenster offen ist, Script muß im Debugger ausgeführt werden
HRESULT hr = NOERROR;

	if (m_pSplitterDebugger == NULL) 
		hr = GetRunningObjectsHelper() -> RunKeptEntry(pEntry, iNumParams, pPars);
	else
		hr = m_pSplitterDebugger -> RunThread(pEntry, iNumParams, pPars);
	return hr;
}

STDMETHODIMP CMacroScriptExtension::RunScript (LPCSTR lpcstrScriptName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	ASSERT(GetGeneralScripts());
	ASSERT(lpcstrScriptName);
	if (NULL == lpcstrScriptName) return E_POINTER;
	if (NULL == GetGeneralScripts()) return E_UNEXPECTED;

	USES_CONVERSION;

// Ist Objekt vorhanden ? 
WUnknown IU;
HRESULT hr = GetGeneralScripts() -> GetObject(A2OLE(lpcstrScriptName), IU.ppi());

	if (SUCCEEDED(hr))
	// Objekt vorhanden, Stream laufen lassen
		hr = m_pRunningObjHelper -> RunScript (lpcstrScriptName, NOAUTOSTART /*AUTOSTART|RESIDENT*/, CLSID_Script, false);
	else 
	// Objekt nicht vorhanden, also File laden und laufen lassen
		hr = m_pRunningObjHelper -> RunScript(lpcstrScriptName, NOAUTOSTART	/*AUTOSTARTFILE|RESIDENT*/, CLSID_FileScript, true);
	return hr;
}

STDMETHODIMP CMacroScriptExtension::StopScript (LPCSTR lpcstrScriptName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ASSERT(lpcstrScriptName);
	if (NULL == lpcstrScriptName) 
		return E_POINTER;

HRESULT hr = m_pRunningObjHelper -> StopScript(lpcstrScriptName);

	if (FAILED(hr) && BS_E_NOENTRY == hr)
		hr = S_FALSE;		// EntryPoint existiert nicht
	return hr;
}

STDMETHODIMP CMacroScriptExtension::RunText (LPCSTR lpText, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ASSERT(lpText);
	ASSERT(lpEntry);

	if (NULL == lpEntry || NULL == lpText) 
		return E_POINTER;
	return m_pRunningObjHelper -> RunEntry (lpEntry, lpText, NULL, iNumParams, pPars, true);
}

STDMETHODIMP CMacroScriptExtension::RunTextEx (
	LPCSTR lpText, LPCSTR lpName, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars, 
	BOOL fPreBreak, INT_PTR hPrCtx)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ASSERT(NULL != lpText && NULL != lpEntry);

	if (NULL == lpEntry || NULL == lpText) 
		return E_POINTER;
	return m_pRunningObjHelper -> RunEntry (lpEntry, lpText, NULL, iNumParams, pPars, fPreBreak, NULL, hPrCtx);
}

STDMETHODIMP CMacroScriptExtension::RunCode (
	HINSTANCE hInst, int iResID, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ASSERT(NULL != hInst && NULL != lpEntry);

	if (NULL == lpEntry) return E_POINTER;
	if (NULL == hInst) return E_HANDLE;

ebHCODE hCode = NULL;
HRESULT hr = LodeCodeFromResource (hInst, &hCode, iResID);

	if (FAILED(hr)) return hr;

	hr = m_pRunningObjHelper -> RunEntry (lpEntry, NULL, hCode, iNumParams, pPars, true, NULL, 
			reinterpret_cast<INT_PTR>(HACTCONNECTION), reinterpret_cast<INT_PTR>(hInst));
	if (hCode) CoTaskMemFree (hCode);
	return hr; 
}

STDMETHODIMP CMacroScriptExtension::RunCodeEx (
	HINSTANCE hInst, int iResID, LPCSTR lpName, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars,
	BOOL fPreBreak, INT_PTR hPrCtx)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	ASSERT(NULL != hInst && NULL != lpEntry);
	if (NULL == lpEntry) return E_POINTER;
	if (NULL == hInst) return E_HANDLE;

ebHCODE hCode = NULL;
HRESULT hr = LodeCodeFromResource(hInst, &hCode, iResID);

	if (FAILED(hr)) return hr;

	hr = m_pRunningObjHelper -> RunEntry (lpEntry, NULL, hCode, iNumParams, pPars, fPreBreak, lpName, hPrCtx, reinterpret_cast<INT_PTR>(hInst));
	if (hCode) CoTaskMemFree (hCode);
	return hr; 
}

STDMETHODIMP CMacroScriptExtension::ExecuteMethod (
	LPCSTR lpName, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars, 
	BOOL fPreBreak, INT_PTR hPrCtx)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	ASSERT(NULL != lpEntry);
	ASSERT(NULL != lpName);

	if (NULL == lpName || NULL == lpEntry) 
		return E_POINTER;

	return m_pRunningObjHelper -> RunEntry (lpName, lpEntry, iNumParams, pPars, fPreBreak, hPrCtx);
}

STDMETHODIMP CMacroScriptExtension::EntryExists (LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// Schon entladen, nachdem Projekt entladen ist 
	if (NULL == m_pRunningObjHelper) 
		return S_FALSE;
	if (0 == strcmp("OnPaintingView", pEntry) || 0 == strcmp("OnViewPainted", pEntry)) 
		return S_FALSE;

// wenn DebuggerFenster offen ist, Script muß im Debugger ausgeführt werden
	if (NULL == m_pSplitterDebugger) 
		return GetRunningObjectsHelper() -> EntryExists (pEntry, iNumParams, pPars);

	return m_pSplitterDebugger -> EntryExists (pEntry, iNumParams, pPars);
}
	
// *** END IExtendBScript methods *** ---------------------------------------------
///////////////////////////////////////////////////////////////////////////////

HRESULT CMacroScriptExtension::GetRuntimeDebugger(CRunErr **pp)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	if (m_pRunErr) {
		*pp = m_pRunErr;
		return S_OK;
	}
	return E_UNEXPECTED;
}

HRESULT CMacroScriptExtension::CreateRunTimeErrorDebugger(LPCSTR lpcstrMacroName)
{	// Run bestimmten Entry von fertigem Code
	try {
		THROW_INVALIDSTRING(lpcstrMacroName, S_FALSE);
		if (NULL == m_pRunErr)
			m_pRunErr = new CRunErr (lpcstrMacroName);
		else // Um Neues Script zu laden
			m_pRunErr -> SetName(lpcstrMacroName);
	} catch (bad_alloc) {
		return E_OUTOFMEMORY;
	} catch (_com_error& e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}
HRESULT CMacroScriptExtension::DestroyRunTimeErrorDebugger(void)
{
	if (m_pRunErr) delete m_pRunErr; m_pRunErr = NULL;
	return S_OK;
}

HRESULT CMacroScriptExtension::EnumObjects(IObjectManagement *pIObjManagement, LPENUMUNKNOWN* ppEnumUnk)
{
	return WOleItemContainer(pIObjManagement) -> EnumObjects(0, ppEnumUnk);
}

HRESULT CMacroScriptExtension::StopAllRun ()
{
	if (NULL == GetRunningObjectsHelper()) 
		return E_POINTER;
	return GetRunningObjectsHelper() -> StopAllScripts();
}

HRESULT CMacroScriptExtension::DestroyStorage()
{
HRESULT hres = NOERROR;
HRESULT hr = DestroyStorage(m_pIGeneralScripts, IDS_STORAGE_NAME_MACROSCRIPTS);

	if (FAILED(hr)) hres = hr;

	hr = DestroyStorage(m_pIFilterScripts, IDS_STORAGE_NAME_OPERATESCRIPTS);
	if (FAILED(hr)) hres = hr;

	hr = DestroyStorage(m_pIObjFeatureScripts, IDS_STORAGE_NAME_OBJECTFEATURESCRIPTS);
	if (FAILED(hr)) hres = hr;

	return hres;
}

HRESULT CMacroScriptExtension::DestroyStorage(IObjectManagement *pIObjManagement, int IDS)
{
	ASSERT(pIObjManagement);

	USES_CONVERSION;
	try	{
	WUnknown IU;
	HRESULT hr = pIObjManagement -> EnumStrings(IU.ppi());

		if (FAILED(hr)) _com_issue_error(hr);

	WEnumos_wstring IE = IU;				

		if (IE -> Count() > 1 || !m_fProjectIsClosing) //  nut InfoStream und Projektclose
			return S_FALSE;

	// Storage zerstören, wenn leer
	CString strStorName;

		if (!LoadString (strStorName, IDS)) _com_issue_error(E_OUTOFMEMORY);					

	WStorage IS;	// Altes TRiAS-Projekt

		if (m_lpDummyStorage) {
			hr = m_lpDummyStorage -> DestroyElement(A2OLE(strStorName));

		// Storage nicht vorhanden ?
			if (FAILED(hr) && hr != STG_E_FILENOTFOUND) _com_issue_error(hr);				

		// Alte Projekte selbst Commit()
			THROW_FAILED_HRESULT(m_lpDummyStorage -> Commit(STGC_DEFAULT));
		}
		else if (DEX_GetProjectStorage(IS)) {
		// Neues TRiAS-Projekt			
			hr = IS -> DestroyElement(A2OLE(strStorName));
			
		// Storage nicht vorhanden ?
			if (FAILED(hr) && hr != STG_E_FILENOTFOUND) _com_issue_error(hr);				

		// Hallo TRiAS, doch nochmal Commit() 
			DEX_SetDirtyGeoDB(true);
		}
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CMacroScriptExtension::Commit(IObjectManagement *pIObjManagement)
{
	ASSERT(pIObjManagement);
	if (NULL == pIObjManagement) return E_POINTER;

	USES_CONVERSION;
	
	try
	{
		THROW_FAILED_HRESULT(pIObjManagement -> Commit());
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CMacroScriptExtension::LoadFromStorage(
	IObjectManagement **ppIObjMan, IStreamInfo **lplpIStreamInfo, REFIID riid, int IDS)
{
	ASSERT(ppIObjMan);
	ASSERT(lplpIStreamInfo);

	if (NULL == ppIObjMan || NULL == lplpIStreamInfo) 
		return E_POINTER;
	if (NULL != *ppIObjMan && NULL != *lplpIStreamInfo) 
		return S_OK;		// Schon geladen 

	*ppIObjMan = NULL;
	*lplpIStreamInfo = NULL;

	try {
	WStorage IRootStorage;	// Projekt offen ?
	
		THROW_FAILED_HRESULT(IsStorageProject(false, IRootStorage.ppi()));	// altes TRiAS-Projekt und Fehler beim erzeugen des DummyStgFiles
	
	// Namen des Storages laden
	CString strStorName; 

		if (!LoadString(strStorName, IDS)) _com_issue_error(E_OUTOFMEMORY);

	// Eventuell alten Storage öffnen ("Alte" hiessen "MacroScripts" nun "GeneralScripts")
	WStorage ISubStorage;
	HRESULT hr = OldGeneralStorage(IRootStorage, ISubStorage.ppi(), IDS);
	
		if (FAILED(hr))		// Altes nicht geladen
		{
			THROW_FAILED_HRESULT(MakeSubStorage(IRootStorage, ISubStorage.ppi(), strStorName, false, riid));
		}

	UINT ui = RegisterClipboardFormat(strStorName);

		USES_CONVERSION;
		THROW_FAILED_HRESULT(WriteFmtUserTypeStg (ISubStorage, (CLIPFORMAT)ui, A2OLE(strStorName)));

	// jeweiliges Objektmanagement, wenn nötig, laden
	WObjectManagement ObjMan;

		THROW_FAILED_HRESULT (LoadManagement(ObjMan.ppi(), riid));

	// Storageinhalt laden
	WPersistStorage IPersistStorage(ObjMan);				

		hr = IPersistStorage -> Load(ISubStorage);
		if (S_FALSE == hr) {
			THROW_FAILED_HRESULT(IPersistStorage -> InitNew(ISubStorage));
		}

	// für alte Scripts ebenfalls Streaminfo erzeugen
	WStreamInfo ISI;

		hr = OldGeneralStreamInfo(ObjMan, IDS, ISI.ppi());
		if (FAILED(hr))		// Streaminfo und Objekte in Obj.Man. vorhanden 
		{
			THROW_FAILED_HRESULT(LoadStreamInfos(CLSID_StreamInfo, ObjMan, ISI.ppi()));
		}
		
		*ppIObjMan = ObjMan.detach();
		*lplpIStreamInfo = ISI.detach();
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CMacroScriptExtension::RenameObject(IObjectManagement *pObjM, LPCSTR lpcstrOld, LPCSTR lpcstr)
{
	USES_CONVERSION;
	try
	{
		ASSERT_THROW_INVALIDSTRING(lpcstrOld);
		ASSERT_THROW_INVALIDSTRING(lpcstr);
		HRESULT hr = pObjM -> RenameObject(A2OLE(lpcstrOld), A2OLE(lpcstr));
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return  NOERROR;
}

HRESULT CMacroScriptExtension::OldGeneralStorage(
												   LPSTORAGE lpIRootStorage, 
												   LPSTORAGE *lplpISubStorage, 
												   int IDS)
{
	ASSERT(lpIRootStorage);
	ASSERT(lplpISubStorage);
	ASSERT(IDS);

	if (IDS_STORAGE_NAME_MACROSCRIPTS != IDS) return E_FAIL;

	if (NULL == lplpISubStorage) return E_POINTER;
	*lplpISubStorage = NULL;

	USES_CONVERSION;
	// Bei alten Versionen hiessen allgemeine Script-Storages "MacroScripts" 	
	DWORD dwMode =	STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT;	
	WStorage IStorage;
	HRESULT hr = lpIRootStorage -> OpenStorage (A2OLE("MacroScripts"), 
												NULL, 
												dwMode, 
												NULL,
												0, 
												IStorage.ppi());
	if (FAILED(hr)) return hr;
	
	*lplpISubStorage = IStorage.detach();

	return hr;
}

HRESULT CMacroScriptExtension::OldGeneralStreamInfo(
	IObjectManagement *pObjM, int IDS, IStreamInfo **ppIStreamInfo)
{
	ASSERT(NULL != pObjM);
	ASSERT(NULL != ppIStreamInfo);
//	ASSERT(IDS_STORAGE_NAME_MACROSCRIPTS == IDS);

	if (NULL == ppIStreamInfo) return E_POINTER;

HRESULT hr = NOERROR;
ebSaveStruct SS;

	memset(&SS, 0, sizeof(ebSaveStruct));
	USES_CONVERSION;
	try
	{
		*ppIStreamInfo = NULL;

	// StreamInfoObjekt erstmal erzeugen
	WStreamInfo ISI;

		hr = LoadStreamInfos(CLSID_StreamInfo, pObjM, ISI.ppi());
		THROW_FAILED_HRESULT(hr);
		if (S_OK == hr) {
			*ppIStreamInfo = ISI.detach();
			return S_OK;	// StreamInfo schon vorhanden, RAUS
		}

	// StreamInfo nicht vorhanden
	// StringEnumerator des ObjektManagements geben lassen
	WUnknown IUEnum;

	// Namen geladener Objecte geben lassen
		THROW_FAILED_HRESULT(pObjM -> EnumStrings(IUEnum.ppi()));

	// Query		
	WEnumos_wstring  IE(IUEnum);
	os_wstring oswstr;
	// Namen enumerieren
	CString str (GetDefaultName(IDS_NEWSTREAMINFO));
	CString strOld (GetDefaultName(IDS_STREAMINFOS));

		while (S_OK == IE -> Next(1, &oswstr, NULL)) 
		{
		LPSTR lpstr = OLE2A(oswstr.c_str());

		// Infostream ?, neuer Schleifendurchlauf
			if (0 == _stricmp(str, lpstr) || 0 == _stricmp(strOld, lpstr)) 
				continue;

		// Object zum Namen geben lassen, muss schon geladen sein
		WUnknown IU;
			
			THROW_FAILED_HRESULT(pObjM -> GetObject(A2OLE(lpstr), IU.ppi()));

		// ObjectProperties geben lassen
		WScriptProperty ISP = IU;
	
			THROW_FAILED_HRESULT(ISP -> Get(&SS));

		DWORD dwInfo = SUPERITEM;

			if (NULL != SS.hCode) dwInfo |= CC_CODE;
			if (NULL != SS.pText) dwInfo |= CC_SCRIPT;

			if (SS.hCode) CoTaskMemFree(SS.hCode);
			if (SS.pText) CoTaskMemFree(SS.pText);
			memset(&SS, 0, sizeof(ebSaveStruct));

			THROW_FAILED_HRESULT(ISI -> Set(A2OLE(lpstr), dwInfo));
		}
		*ppIStreamInfo = ISI.detach();
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}

	return hr;
}

HRESULT CMacroScriptExtension::Save (IObjectManagement *pIOM, int IDS, LPSTORAGE lpIStorage, BOOL fSameAsLoad)
{
HRESULT hr = NOERROR;
WPersistStorage IPS(pIOM);
LPSTORAGE pISubStorage = NULL;

	if (!fSameAsLoad) {
	// CopyTo() or SaveAs()
	CString strStorName;
	
		if (!LoadString(strStorName, IDS)) 
			return E_FAIL;
		hr = MakeSubStorage(lpIStorage, &pISubStorage, strStorName, true, CLSID_CObjectManagement);
		if (FAILED(hr)) return hr; 
	}

// Zu Save(), Bei S_OK wurde wirklich etwas abgespeichert, es muß Commit() gemacht werden
	hr = IPS -> Save(pISubStorage, fSameAsLoad);
	if (pISubStorage) {	
	// Wenn woanders hin also CopyTo() oder SaveAs(), auf Eigenen nicht Commit()
		pISubStorage -> Release(); 
		pISubStorage = NULL;
		return hr;
	}
	if (S_OK != hr) return hr;

//( Nun noch Änderungen wirksam machen
	hr = Commit(pIOM);
	if (FAILED(hr)) return hr;
	
	if (m_lpDummyStorage) 
		hr = m_lpDummyStorage -> Commit(STGC_DEFAULT);
	return hr;
}

HRESULT CMacroScriptExtension::Save (LPSTORAGE lpIStorage, BOOL fSameAsLoad)
{
	ASSERT(m_pIGeneralScripts);
	ASSERT(m_pIFilterScripts);
	ASSERT(m_pIObjFeatureScripts);

// bei Fehler Gewährleisten, daß Save() für jedes Management ausgeführt wird
HRESULT hres = NOERROR;
HRESULT hr = Save (m_pIGeneralScripts, IDS_STORAGE_NAME_MACROSCRIPTS, lpIStorage, fSameAsLoad);

	if (FAILED(hr)) hres = hr; 

	hr = Save (m_pIFilterScripts, IDS_STORAGE_NAME_OPERATESCRIPTS, lpIStorage, fSameAsLoad);
	if (FAILED(hr)) hres = hr; 

	hr = Save (m_pIObjFeatureScripts, IDS_STORAGE_NAME_OBJECTFEATURESCRIPTS, lpIStorage, fSameAsLoad);
	if (FAILED(hr)) hres = hr; 

	return hres;
}

HRESULT CMacroScriptExtension::SaveCompleted (IObjectManagement *pIOM, int IDS, LPSTORAGE lpIStorage)
{
	ASSERT(pIOM);

	HRESULT hr = NOERROR;
	WPersistStorage IPS (pIOM);

	LPSTORAGE lpISubStorage = NULL;
	// if SaveAs()
	if (NULL != lpIStorage) 
	{
		CString strStorName;
		if (!LoadString(strStorName, IDS)) return E_FAIL;
		// SubStorage->AddRef()	
		hr = MakeSubStorage(lpIStorage, &lpISubStorage, strStorName, true, CLSID_CObjectManagement);
		if (FAILED(hr)) return hr; 
	}

	hr = IPS -> SaveCompleted(lpISubStorage);
	if (lpISubStorage) lpISubStorage -> Release(); 
	lpISubStorage = NULL;
	// Zerstört Storages, wenn Projekt geschlossenen und Storages leer, ruft Commit()
	return DestroyStorage(pIOM, IDS);
}

HRESULT CMacroScriptExtension::SaveCompleted (LPSTORAGE lpIStorage)
{
	ASSERT(m_pIGeneralScripts);
	ASSERT(m_pIFilterScripts);
	ASSERT(m_pIObjFeatureScripts);

	///////////////////////////////////////////////////////////////////////////////////////
	// bei Fehler Gewährleisten, daß SaveCompleted() für jedes Management ausgeführt wird
	HRESULT hres = NOERROR;
	HRESULT hr = SaveCompleted(m_pIGeneralScripts, IDS_STORAGE_NAME_MACROSCRIPTS, lpIStorage);
	if (FAILED(hr)) hres = hr;

	hr = SaveCompleted(m_pIFilterScripts, IDS_STORAGE_NAME_OPERATESCRIPTS, lpIStorage);
	if (FAILED(hr)) hres = hr;

	hr = SaveCompleted(m_pIObjFeatureScripts, IDS_STORAGE_NAME_OBJECTFEATURESCRIPTS, lpIStorage);
	if (FAILED(hr)) hres = hr;

	return hres;
}

HRESULT CMacroScriptExtension::HandsOffStorage(IObjectManagement *pIOM)
{
	ASSERT(pIOM);

	WPersistStorage IPS (pIOM);

return	IPS -> HandsOffStorage();
}

HRESULT CMacroScriptExtension::HandsOffStorage()
{
	ASSERT(m_pIGeneralScripts);
	ASSERT(m_pIFilterScripts);
	ASSERT(m_pIObjFeatureScripts);

	///////////////////////////////////////////////////////////////////////////////////////
	// bei Fehler Gewährleisten, daß HandsOffStorage() für jedes Management ausgeführt wird
	HRESULT hres = NOERROR; 
	HRESULT hr = HandsOffStorage(m_pIGeneralScripts);
	if (FAILED(hr)) hres = hr;

	hr = HandsOffStorage(m_pIFilterScripts);	
	if (FAILED(hr)) hres = hr;

	hr = HandsOffStorage(m_pIObjFeatureScripts);
	if (FAILED(hr)) hres = hr;

	return hres;
}

HRESULT CMacroScriptExtension::UnLoadScriptManagers()
{
	// Hier nur das ObjectManagement zurücksetzen
	// Selbst erst bei Entladen der Erweiterung löschen
	if (m_pRunningObjHelper)
		m_pRunningObjHelper -> ResetManagement();

	if (m_pIGeneralScripts)
		m_pIGeneralScripts -> Release();
	m_pIGeneralScripts = NULL;
	if (m_pIGeneralScriptsInfo) 
		m_pIGeneralScriptsInfo->Release();
	m_pIGeneralScriptsInfo	= NULL;

	if (m_pIFilterScripts) 
		m_pIFilterScripts -> Release();
	m_pIFilterScripts	= NULL;
	if (m_pIFilterScriptsInfo) 
		m_pIFilterScriptsInfo -> Release();
	m_pIFilterScriptsInfo = NULL;
	
	if (m_pIObjFeatureScripts) 
		m_pIObjFeatureScripts -> Release();
	m_pIObjFeatureScripts	= NULL;
	if (m_pIObjFeatureScriptsInfo) 
		m_pIObjFeatureScriptsInfo -> Release();
	m_pIObjFeatureScriptsInfo = NULL;
	
	return S_OK;
}

HRESULT CMacroScriptExtension::LoadScriptManagers()
{
char cBuffer[_MAX_PATH];

	try {
	// Manager nur laden, wenn Projekt geöffnet
		if (NULL == DEX_GetActiveProject (cBuffer)) 
			return S_FALSE;

		THROW_FAILED_HRESULT(LoadFromStorage(&m_pIGeneralScripts, &m_pIGeneralScriptsInfo, CLSID_CObjectManagement, IDS_STORAGE_NAME_MACROSCRIPTS));
		m_pIGeneralScriptsInfo -> SetManID(MANID_GENERAL);

		THROW_FAILED_HRESULT(LoadFromStorage(&m_pIFilterScripts, &m_pIFilterScriptsInfo, CLSID_CObjectManagement, IDS_STORAGE_NAME_OPERATESCRIPTS));
		m_pIFilterScriptsInfo -> SetManID(MANID_FILTER);

		THROW_FAILED_HRESULT(LoadFromStorage(&m_pIObjFeatureScripts, &m_pIObjFeatureScriptsInfo, CLSID_CObjectManagement, IDS_STORAGE_NAME_OBJECTFEATURESCRIPTS));
		m_pIObjFeatureScriptsInfo -> SetManID(MANID_OBJFEAT);
	}
	catch (_com_error &e)
	{
		if (m_pIGeneralScripts) m_pIGeneralScripts -> Release();
		if (m_pIFilterScripts) m_pIFilterScripts -> Release();
		if (m_pIObjFeatureScripts) m_pIObjFeatureScripts -> Release();

		if (m_pIGeneralScriptsInfo) m_pIGeneralScriptsInfo -> Release();
		if (m_pIFilterScriptsInfo) m_pIFilterScriptsInfo -> Release();
		if (m_pIObjFeatureScriptsInfo) m_pIObjFeatureScriptsInfo -> Release();

		m_pIGeneralScriptsInfo = NULL;
		m_pIObjFeatureScriptsInfo = NULL;
		m_pIFilterScriptsInfo = NULL;

		m_pIFilterScripts = NULL;	
		m_pIObjFeatureScripts = NULL;	
		m_pIGeneralScripts = NULL;

		return _COM_ERROR(e);
	}

// erst init., wenn Storages geladen und Projekt geöffnet
	return m_pRunningObjHelper -> InitLinkAndStorage (m_pIGeneralScripts, m_pIGeneralScriptsInfo);
}

HRESULT CMacroScriptExtension::LoadStreamInfos(REFCLSID riid, IObjectManagement *pObjM, IStreamInfo **ppIStreamInfo)
{		
	ASSERT(pObjM);
	ASSERT(ppIStreamInfo);
	
	if (NULL == ppIStreamInfo) return E_POINTER;
	*ppIStreamInfo = NULL;

HRESULT hr = S_OK;

	USES_CONVERSION;
	try	{
	// InfoStreams öffnen
		CString str, strNewInfo;
		if (!LoadString(str, IDS_STREAMINFOS) || !LoadString(strNewInfo, IDS_NEWSTREAMINFO)) 
			_com_issue_error(E_OUTOFMEMORY);
		// Ist alte Streaminfo vorhanden ? 
		WUnknown IU;		
		hr = pObjM -> GetObject(A2OLE(str), IU.ppi()); 
		if (SUCCEEDED(hr)) 
		{// Ist vorhanden, also umbenennen
			hr = RenameObject(pObjM, str, strNewInfo);
			if (FAILED(hr)) _com_issue_error(hr);
		}	
		// Ist neue Streaminfo vorhanden oder alte umbenannt ? 
		hr = pObjM -> GetObject(A2OLE(strNewInfo), IU.ppi()); 
		if (FAILED(hr))
		{// noch kein Objekt vorhanden, nun immer NEUE Streaminfo (__INFO__) erzeugen
			hr = pObjM -> CreateObject(riid, A2OLE(strNewInfo), STGM_READWRITE, IU.ppi(), false);
			if (FAILED(hr)) _com_issue_error(hr);
			hr = S_FALSE;
		}	
		// Query(...
		WStreamInfo ISI(IU);
		*ppIStreamInfo = ISI.detach();
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return hr;
}

/*
HRESULT CMacroScriptExtension::RunSequence()
{
	HRESULT hr = NOERROR;

	try
	{
		WPersistStreamInit IS;
		HRESULT hr = CoCreateInstance(
									CLSID_PropertyActionSequence,	
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_IPersistStreamInit,
									IS.ppv()); // nur umkopieren
		if (FAILED(hr)) throw hr;

		hr = IS -> InitNew();
		if (FAILED(hr)) throw hr;

		const CLSID * pclsID[2];

		pclsID[0] = &CLSID_SelectIdentObjTyp;
		pclsID[1] = &CLSID_FilterScript;

		CALPCLSID CLSIDs;
		
		CLSIDs.cElems = 2;
		CLSIDs.ppElems = pclsID;

		CString strAppName = GetDefaultName(IDS_LONGCLASSNAME);

			// ADDREF(IS)	
		WPropertyActionSequence ISeq(IS);
		hr = ISeq -> SetDescription(strAppName);
		if (FAILED(hr)) throw hr;

		hr = ISeq -> AddActionsByCLSID(&CLSIDs);
		if (FAILED(hr)) throw hr;

		hr = ISeq -> DoActions( hWnd(), NULL, NULL, NULL);
		// Dlg->Cancel()
		if (hr == E_UNEXPECTED) throw S_FALSE;
		if (FAILED(hr)) throw hr;
	}
	catch (HRESULT hr)
	{
		return hr;
	}

	// find the resrouce in my EXE
	LPSTR lpszTemplateName = MAKEINTRESOURCE(IDR_SEQUENCE);
	HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, "SCRIPT");
	if (hInst == NULL) return ResultFromScode(E_HANDLE);
	RunCode (hInst, IDR_SEQUENCE, "Main", 0, NULL);
// RELEASE(IS)
// RELEASE(IS)
	return hr;
}
*/

HRESULT CMacroScriptExtension::RunSequence()
{	// find the resrouce in my EXE
	LPSTR lpszTemplateName = MAKEINTRESOURCE(IDR_SEQUENCE);
	HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, "SCRIPT");
	if (NULL == hInst) return E_HANDLE;
	return RunCode (hInst, IDR_SEQUENCE, "Main", 0, NULL);;
}

BOOL CMacroScriptExtension::MacroScriptCall()
{
DWORD dwIntro = 0;
CCurrentUser regCfg (KEY_READ, g_cbCfgKey);

	if (!regCfg.GetDWORD(g_cbIntro, dwIntro) || 0 != dwIntro) {
	CMacroIntroDlg Dlg (MWind());

		Dlg.DoModal();
	}

BOOL fResult = true;
CScriptDlg *pSDlg = NULL;

	pSDlg = CScriptDlg::CreateInstance(MWind(), m_pIGeneralScripts, m_pIGeneralScriptsInfo);
	if (NULL == pSDlg) {
		TRACE("Couldn't generate CScriptDlg!\r\n");
		return false;		// Fehler Memory
	}
	if (IDOK != pSDlg -> DoModal()) 
		return true; // Cancel

char str[MAXSTRLENGTH];
BOOL fName = pSDlg -> GetName (str, MAXSTRLENGTH);

	if (pSDlg->GetDel()) {
		fResult = true;
	} 
	else if (fName && pSDlg->GetRun()) {
	// Für Run muß Name bekannt sein
		if (FAILED(m_pRunningObjHelper -> RunScript(str, NOAUTOSTART, CLSID_Script, false))) 
			fResult = false;
	} 
	else if (fName && pSDlg->GetRunFile()) {
	// Für Run muß Name bekannt sein
		if (FAILED(m_pRunningObjHelper -> RunScript(str, pSDlg->GetAutoStart(), CLSID_FileScript, true))) 
			fResult = false;
		else if (pSDlg->GetAutoStart()) 
			SaveRegSettingsAutoLoadFile(str);
	} 
	else if (fName || pSDlg->GetOpenFile()) {
		if (!MacroScriptCallForFrame(str, pSDlg->GetOpenFile())) 
			fResult = false;
	}

	DELETE_OBJ(pSDlg);
	return fResult;
}

BOOL CMacroScriptExtension::MacroScriptCallForFrame(LPCSTR lpcstr, BOOL fOpenFile)
{
CSplit *pDebugger = NULL;

	if (FAILED(CreateDebugger(MWind(), lpcstr, fOpenFile, WM_CLOSEDEBUGGERDIALOG, m_pIGeneralScripts, m_pIGeneralScriptsInfo, &pDebugger)))
		return false; 

	m_pSplitterDebugger = pDebugger;
	return true;
}

HRESULT MakeFileName(LPCSTR pPathName, LPSTR pNameToUse, LPCSTR pcFileExt)
{
	ASSERT(pPathName);
	ASSERT(pNameToUse);
	ASSERT(pcFileExt);

char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];
char *pFName = new char [_MAX_FNAME];

	if (pDrive == NULL || pPath == NULL || pFName == NULL) {
		if (pDrive) delete (pDrive);
		if (pPath) delete (pPath);
		if (pFName) delete (pFName);    
		return ResultFromScode (E_OUTOFMEMORY);
	}
	

	_splitpath (pPathName, pDrive, pPath, pFName, NULL);		// DateiNamen splitten
	_makepath (pNameToUse, pDrive, pPath, pFName, pcFileExt);	// auszugebender Name

// Speicher freigeben
	delete (pDrive);
	delete (pPath);
	delete (pFName);               
		                        
	return S_OK;		
}

// wenn der Debugger nicht läuft und Scripts gespeichert sind !!!
HRESULT ReadIniAutoLoadScript (char *lpstrMacroName, int iLen)
{
char ProjectName[_MAX_PATH];
char IniName[_MAX_PATH];
char RegMacroDirName[_MAX_PATH];
char StartFile[_MAX_FNAME];
HRESULT hr = E_FAIL;

	if (DEX_GetActiveProject(ProjectName)) {
		hr = MakeFileName (ProjectName, IniName, g_cbFileExt_Ini);
		if (FAILED(hr))	return hr;

	// Aus der INI StartFileNamen lesen
		if (GetPrivateProfileString (g_cbBasicScript, g_cbAutoStartPath, g_cbNil, StartFile, _MAX_FNAME, IniName)) 
		{
		// Pfadnamen aus der Registry lesen
			if (!ReadRegSettingsMacrosDirectory(RegMacroDirName, _MAX_PATH)) 
				return E_FAIL;
		
		// Filenamen an Pfad hängen
			strcat(RegMacroDirName, StartFile);
			if (iLen > strlen(RegMacroDirName))	{
				strcpy(lpstrMacroName, RegMacroDirName); 
				return S_OK;
			}
		}
		else if (GetPrivateProfileString (g_cbBasicScript, g_cbAutoStart , g_cbNil, lpstrMacroName, iLen, IniName))  
		// kein Eintrag vorhanden
			return S_FALSE;
	}
	return E_FAIL;
}

BOOL RegAutoStartScriptFile()
{
char cbFilePath[_MAX_PATH];
DWORD dwLen = sizeof(cbFilePath);
CCurrentUser regDirs (g_cbDirKey, true);

	if (!regDirs.GetSubSZ(g_cbMacroDir, cbFilePath, dwLen) || '\0' == cbFilePath[0]) {
	// Verzeichnis existiert noch nicht
	DWORD dwFlags = CSIDL_PERSONAL;

		if (IsWinNT() && IsWin50())
			dwFlags |= CSIDL_FLAG_CREATE;

		SHGetFolderPath(NULL, dwFlags, NULL, 0, cbFilePath);
		PathAppend(cbFilePath, REG_COMPANY_KEY);
		PathAppend(cbFilePath, REG_PRODUCT_KEY);

	CString strMacros;

		VERIFY(strMacros.LoadString(IDS_MACROSUBDIR));

		PathAppend(cbFilePath, strMacros);
		PathAddBackslash(cbFilePath);

		regDirs.SetSubSZ(g_cbMacroDir, cbFilePath);

	// Verzeichnis auch noch erzeugen
		CreateDirectory (cbFilePath, NULL);

	// dynamische DLL's wieder entladen
		__FUnloadDelayLoadedDLL("shlwapi.dll");
		__FUnloadDelayLoadedDLL("shfolder.dll");
	}
	return TRUE;
}

BOOL UnRegAutoStartScriptFile()
{
CCurrentUser CU(g_cbTRiASKey);
	
	return CU.DeleteKey (g_cbDirKeyOnly);
}

HRESULT CMacroScriptExtension::InstallObjectProperties()
{
HRESULT hr = NOERROR;

	USES_CONVERSION;
	try	{
	IStreamInfo *pISI = NULL;
	IObjectManagement *pIObjMan;

	// Storageverwaltung geben lassen
		pIObjMan = GetObjectFeatureScripts();
		pISI = GetInfoObjFeatureScripts();
		if (NULL == pIObjMan || NULL == pISI) 
			_com_issue_error(E_POINTER);

	WUnknown IUEnum;	// Namen geladener Objecte geben lassen
		
		THROW_FAILED_HRESULT(pIObjMan -> EnumStrings(IUEnum.ppi()));

	// Query		
	WEnumos_wstring IE (IUEnum);
	os_wstring oswstr;

	// Namen enumerieren
	CString str = GetDefaultName(IDS_NEWSTREAMINFO);
	CString strOld = GetDefaultName(IDS_STREAMINFOS);

		for (IE -> Reset(); S_OK == IE -> Next(1, &oswstr, NULL); /**/) 
		{
		LPSTR lpstr = OLE2A(oswstr.c_str());
		
		// Infostream ?, neuer Schleifendurchlauf
			if (0 == _stricmp(str, lpstr) || 0 == _stricmp(strOld, lpstr)) 
				continue;

		DWORD dwInfo = 0;

			THROW_FAILED_HRESULT(pISI -> Get(A2OLE(lpstr), &dwInfo));
			if (!(dwInfo & OBJFEAT_INSTALLED)) 
				continue;
			
		WUnknown IU;		// Object zum Namen geben lassen, muss schon geladen sein
			
			THROW_FAILED_HRESULT(pIObjMan -> GetObject(A2OLE(lpstr), IU.ppi()));

		// Funktion Install rufen
		WAddScriptProperty IASP(IU);
		HRESULT hr = IASP -> Install();		// Nicht implementiert trotzdem installieren, Laufzeifehler RAUS

			if (FAILED(hr) && E_NOTIMPL != hr) 
				_com_issue_error(hr);			

		// eigentliche Aktion
		// gefundenes Object in internen Enumerator füllen, AddRef()
		WObjectProperty IOP(IU);
		ULONG ulCooky = AddPropertyFunction (IOP);

			if (0 == ulCooky) _com_issue_error(E_UNEXPECTED);

		// Query...
			THROW_FAILED_HRESULT(IASP -> SetCooky(ulCooky)); // Coocky für Remove merken
		}
	} catch (_com_error &e)	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CMacroScriptExtension::LodeCodeFromResource(HINSTANCE hInst, ebHCODE *phCode, UINT uiID)
{
	ASSERT(hInst);
	ASSERT(phCode);

	USES_CONVERSION;

HRESULT hr = NOERROR;
HRSRC hRes = NULL;
HGLOBAL hMem = NULL;
ebFILEHEADER *pHeader = NULL;
LPVOID lpCode = NULL;
BYTE* lpMem = NULL;

	try	{
	// Finden der Resource dieser Instanz
		hRes = FindResource((HMODULE)hInst, MAKEINTRESOURCE(uiID), "SCRIPT");
		if (NULL == hRes) _com_issue_error(E_HANDLE);

	// Resource in Memory laden
		hMem = LoadResource((HMODULE)hInst, hRes);
		if (NULL == hMem) _com_issue_error(E_HANDLE);

	// lock it, get pointer to first VOID
		lpMem = (BYTE*)LockResource(hMem);
		if (NULL == lpMem) _com_issue_error(E_HANDLE); 

	// Header lesen
		pHeader = (ebFILEHEADER *)lpMem;
		if (pHeader -> id != FH_ID || pHeader -> wVersion != FH_VERSION || 
			0 == pHeader -> dwCodeSz || 0 == pHeader -> dwCode)
		{
			_com_issue_error(E_FAIL);
		}

	// Codepointer erzeugen
		lpCode = CoTaskMemAlloc (pHeader->dwCodeSz);
		if (NULL == lpCode) _com_issue_error(E_OUTOFMEMORY);

	// aus Memory holen
		memcpy(lpCode, &lpMem[pHeader->dwCode], pHeader->dwCodeSz);

	// Codehandle bilden	
		*phCode = ebCode_Create(lpCode);
		if (NULL == *phCode) 
			_com_issue_error(E_HANDLE);
		if (ebCode_GetSize(*phCode) != pHeader->dwCodeSz) 
			_com_issue_error(E_UNEXPECTED);
	}
	catch (_com_error &e)
	{
		if (hMem) {
			UnlockResource(hMem);
			FreeResource(hMem);
		}
		hMem = NULL;
		if (lpCode)	CoTaskMemFree (lpCode);
		lpCode = NULL;
		*phCode = NULL;

		return _COM_ERROR(e);
	}

	UnlockResource(hMem);
	FreeResource(hMem);
	return hr;
}

HRESULT CMacroScriptExtension::AutoLoadScript ()
{
char strMacroName[_MAX_PATH];
HRESULT hr = ReadIniAutoLoadScript (strMacroName, _MAX_PATH);	// Name aus Projekt-INI lesen...

	if (S_FALSE == hr) {
		hr = m_pRunningObjHelper -> RunScript(strMacroName, AUTOSTART, CLSID_Script, false);
		if (FAILED(hr)) return hr;
	}
	else if (S_OK == hr) {
		hr = m_pRunningObjHelper -> RunScript(strMacroName, AUTOSTART, CLSID_FileScript, true);
		if (FAILED(hr)) return hr;
	}
	return hr;		// nichts in der INI
}

HRESULT CMacroScriptExtension::AutoLoadScriptExtern ()
{
	try	{
	char strMacroName[_MAX_PATH];
	
	// Name aus Projekt-INI lesen...
		if (!ReadRegSettingsAutoLoadFile (strMacroName, _MAX_PATH))	
			_com_issue_error(E_FAIL);
	
	// Management laden
		HRESULT hr = LoadManagement(&m_pIGeneralScripts, CLSID_CObjectManagement);
		if (FAILED(hr)) _com_issue_error(hr);
	
	// Für Filerunning laden
		hr = m_pRunningObjHelper -> InitLinkAndStorage(m_pIGeneralScripts, NULL);
		if (FAILED(hr)) _com_issue_error(hr);
	
	// Running File
		hr = m_pRunningObjHelper -> RunScript(strMacroName, AUTOSTARTFILE, CLSID_FileScript, true);
		if (FAILED(hr)) _com_issue_error(hr);
	} catch(_com_error& e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CMacroScriptExtension::LoadManagement (IObjectManagement **ppIOM, REFIID riid)
{
	ASSERT(NULL != ppIOM);
	if (NULL == ppIOM) 
		return E_POINTER;

	if (*ppIOM != NULL) 
		return S_OK;
	return CoCreateInstance (riid, NULL, CLSCTX_INPROC_SERVER, IID_IObjectManagement, (LPVOID *)ppIOM);
}

HRESULT CMacroScriptExtension::IsStorageProject(BOOL fMess, LPSTORAGE *lplpStorage)
{
	ASSERT(lplpStorage);
	if (NULL == lplpStorage) return E_POINTER;

	*lplpStorage = NULL;
	
	// Root schon für altes Projekt erzeugt
	if (NULL != m_lpDummyStorage) 
	{
		*lplpStorage = m_lpDummyStorage;
		(*lplpStorage) -> AddRef();
		return S_OK;
	}

// Projektstorage vorhanden ?
	if (DEX_GetProjectStorage(*lplpStorage))
		return S_OK;		// Storage vorhanden
	
	try	{
	CString strBuffer;
	LPSTR lpstrBuffer = strBuffer.GetBuffer(MAXSTRLENGTH);

	// Projekt geöffnet ?
		if (NULL == DEX_GetActiveProject (lpstrBuffer)) //AddRef()
			_com_issue_error(E_UNEXPECTED);
	
	// eventuell altes Projekt anzeigen
		if (fMess) MessageOldProject(GetActiveWindow());
	
	// Sonst keine weiteren Aktionen möglich
		strBuffer.ReleaseBuffer();
	
	// Richtige Extension anhängen
		strBuffer = CorrectExtension (strBuffer, IDS_DUMMYSTOREXT);
		ASSERT(!strBuffer.IsEmpty());
		if (strBuffer.IsEmpty()) _com_issue_error(E_FAIL); 
	
	// DummyStorage erzeugen
		THROW_FAILED_HRESULT(MakeDummyStorage(strBuffer, lplpStorage));//AddRef()
	
	// Aufheben !!!
		m_lpDummyStorage = *lplpStorage;
		m_lpDummyStorage -> AddRef();
	}
	catch(CMemoryException)
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_FALSE;
}

// damit Library erst zur Laufzeit geladen wird, nicht ebCreateDebugger nutzen
// Darf nicht INLINE sein
ebBOOL CebDebugger::Create()
{
#if defined(EBWIN) || defined(EBWIN32)
	m_hWndDebugger = g_pBSE -> CreateDebuggerControl(	
						m_hWndParent,
						m_X,
						m_Y,
						m_nWidth,
						m_nHeight,
						m_dwStyle,
						m_wId,
						(ebHINSTANCE)m_hInstance
					);
#else
	m_hWndDebugger = ebCreateDebugger(	m_hWndParent,
						m_X,m_Y,m_nWidth,m_nHeight,
						m_dwStyle,
						m_wId,
						0
					);
#endif // EBWIN | EBWIN32

	if (m_hWndDebugger == NULL) {
//		delete this;	//#HK950508
		return 0;
	}
	return 1;
}

ebHWND CMacroScriptExtension::CreateDebuggerControl (
	ebHWND hWndParent, ebINT x, ebINT y, ebINT width, ebINT height, ebDWORD style, _ebWORD id, ebHINSTANCE hInstance)
{						
HRESULT hr = NOERROR;
LPCSTR lpszEntry = "ebCreateDebuggerA";
ebHWND (ebCAPI* proc)(ebHWND hWndParent, ebINT x, ebINT y, ebINT width, ebINT height, ebDWORD style, _ebWORD id, ebINT iRes, ebINT inst);

	if (!g_SummitModuls[DEBUGGER].fIsInstalled)
	{
		TRACE1("Fehler: DLL %s nicht vorhanden!\n", PRODUCT_DC_NAME ebMODEXT);
		return NULL; 
	}

	if (NULL == m_hDCInst) {		// evtl. DebuggerControl explizit laden
	os_path path (g_pDLLName);

		path.filename (PRODUCT_DC_NAME ebMODEXT);

	// #HK990620 work around WinNT4 LoadProcess bug
	char szModuleShort[_MAX_PATH];
	os_string strName = os_string(path).c_str();
	int cbShortName = GetShortPathName (strName.c_str(), szModuleShort, _MAX_PATH);
	LPCSTR pcModule = NULL;

		if (cbShortName == _MAX_PATH)
			return NULL;
		pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strName.c_str() : szModuleShort;

		m_hDCInst = LoadLibrary (pcModule);
		if (LOADLIBRARY_FAILED(m_hDCInst)) 
		{
			TRACE1("Fehler: Konnte %s nicht laden!\n", PRODUCT_DC_NAME ebMODEXT);
			m_hDCInst = NULL;
			return NULL;
		}
	}

	proc = (ebHWND (ebCAPI*)(ebHWND hWndParent, ebINT x, ebINT y, ebINT width, ebINT height, ebDWORD style, _ebWORD id, ebINT iRes, ebINT inst)) GetProcAddress((HMODULE)m_hDCInst, lpszEntry);
	if (NULL == proc)
	{
		TRACE2("Fehler: Konnte nicht %s in %s finden!\n", lpszEntry, PRODUCT_DC_NAME ebMODEXT);
		return NULL;
	}
	return (* proc) (hWndParent, x, y, width, height, style, id, 0, (ebINT)hInstance);
}

// MessageSchleife ------------------------------------------------------------
void CallMessageQueue (void)
{
// Yielding
/*	MSG msg;
	
	while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) 
			return;
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
*/

// nicht jedes mal, nur etwa 10 mal in der Sekunde
static DWORD s_dwLastKickIdleTime = 0;

	if (GetTickCount() - s_dwLastKickIdleTime > 100)  {
		DEX_KickIdle();							// IdleProcessing
		s_dwLastKickIdleTime = GetTickCount();	// DEX_KickIdle dauert auch etwas
	}
}


#if !defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// Stuff for MFC-DLL ----------------------------------------------------------
CExtDLL NEAR MyExtensionDLL (NULL); // ==>> Titel in AFX_IDS_APP_TITLE !!						

#endif // WIN32 

///////////////////////////////////////////////////////////////////////////////
// Allgemeine globale Funktionen 

void MessageOldProject(HWND hWnd)
{
	CString str = GetDefaultName(IDS_OLDPROJECT);
	CString strApp = GetDefaultName(IDS_LONGCLASSNAME);
	UINT uiRes = 0;

	MessageBox (hWnd, str, strApp, MB_OK | MB_ICONINFORMATION);
}

BOOL RegPropActPage(REFCLSID rclsid, LPCSTR pcProgID) // z. b. TRiASEx.FilterScript.1
{
OLECHAR oleszClassID[GUID_CCH];
TCHAR szClassID[GUID_CCH];
int cchGuid = ::StringFromGUID2 (rclsid, oleszClassID, GUID_CCH);

	ASSERT(cchGuid == GUID_CCH);			// Did StringFromGUID2 work?
	if (cchGuid != GUID_CCH) return false;

#if !defined(OLE2ANSI)
	ConvertStrWtoA (oleszClassID, szClassID, GUID_CCH);
#else
	strncpy (szClassID, oleszClassID, GUID_CCH);
	szClassID[GUID_CCH] = '\0';
#endif // OLE2ANSI

char cBuffer[80];

	wsprintf(cBuffer, g_cbPropActKeyFmt, pcProgID);

// Öffnen des Key's (mit Pfad: TRiAS.Application.2\\TRiASEx\\PropertyActions)
CClassesRoot Root(cBuffer, true);

	return Root.SetSubSZ (NULL, szClassID);	// save in reg file...
}

BOOL UnRegPropActPage(LPCSTR pcProgID) // z. b. TRiASEx.FilterScript.1
{
char cBuffer[80];		// window information

	wsprintf(cBuffer, g_cbPropActKey, pcProgID);

CClassesRoot Root(g_cbPropActKey, true);

	return Root.DeleteKey (pcProgID);	// save in reg file...
}

///////////////////////////////////////////////////////////////////////////////
// Indizies der Icons in dieser Datei
#define ICONINDEX_DEFAULT	4
#define ICONINDEX_OBJPROP	7
#define ICONINDEX_PROPACT	6

BOOL RegFileExtensions()
{
	if (!RegFileExtensions(".ebf", TEXT("TRiASEx.GeneralMacroFileScript.1"), ICONINDEX_DEFAULT))
		return false;
	if (!RegFileExtensions(".ebfc", TEXT("TRiASEx.GeneralMacroFileScript.1")))
		return false;

	if (!RegFileExtensions(".ebs", TEXT("TRiASEx.GeneralMacroFileScript.1")))
		return false;
	if (!RegFileExtensions(".ebt", TEXT("TRiASEx.GeneralMacroFileScript.1")))
		return false;
	if (!RegFileExtensions(".ebc", TEXT("TRiASEx.GeneralMacroFileScript.1")))
		return false;
	
	if (!RegFileExtensions(".ebo", TEXT("TRiASEx.ObjectFeatureFileScript.1"), ICONINDEX_OBJPROP))
		return false;
	if (!RegFileExtensions(".eboc", TEXT("TRiASEx.ObjectFeatureFileScript.1")))
		return false;
	return true;
}

extern "C" TCHAR FAR g_pDLLName[_MAX_PATH];

BOOL RegFileExtensions(LPCSTR lpcstr, LPCSTR lpcstrFile, int iIndex)
{
CClassesRoot Root(lpcstr, true);

	if (!Root.SetSubSZ (NULL, lpcstrFile))
		return FALSE;

	if (-1 == iIndex)
		return TRUE;

CString strDefIcon (lpcstrFile);
CString strPath (g_pDLLName);
char cbBuffer[32];

	strDefIcon += TEXT("\\DefaultIcon");
	strPath += ",";
	strPath += ltoa(iIndex, cbBuffer, 10);

CClassesRoot DefIcon (strDefIcon, true);

	return DefIcon.SetSZ (NULL, strPath);
}

BOOL UnRegFileExtensions()
{
	if (!UnRegFileExtensions(".ebs"))
		return false;
	if (!UnRegFileExtensions(".ebt"))
		return false;
	if (!UnRegFileExtensions(".ebc"))
		return false;

	if (!UnRegFileExtensions(".ebo"))
		return false;
	if (!UnRegFileExtensions(".eboc"))
		return false;

	if (!UnRegFileExtensions(".ebf"))
		return false;
	if (!UnRegFileExtensions(".ebfc"))
		return false;
	return true;
}

BOOL UnRegFileExtensions(LPCSTR lpcstr) 
{
CClassesRoot Root(NULL, true);

	return Root.DeleteKey (lpcstr);
}

HRESULT GetInstalledSummitModuls (void)
{
int i = 0;
LPCSTR lpcSumModul = NULL;
OFSTRUCT OFS;

	while (*(lpcSumModul = g_SummitModuls[i].lpcModulName) != '\0') {
		memset (&OFS, 0, sizeof(OFSTRUCT));

   /* Open a file */							// OF_EXIST auch Close()
		if (HFILE_ERROR != OpenFile (lpcSumModul, &OFS, OF_EXIST|OF_READ)) 
			g_SummitModuls[i].fIsInstalled = true;

		i++;
	}
	return S_OK;	
}

HRESULT WriteIniAutoLoadScript (LPCSTR pcMacroName)
{	
	char ProjectName[_MAX_PATH];
	char FileName	[_MAX_PATH];
	HRESULT hr = E_FAIL;

	if (DEX_GetActiveProject(ProjectName)) 
	{
		hr = MakeFileName (ProjectName, FileName, g_cbFileExt_Ini);
		if (FAILED(hr))	return hr;
		if (WritePrivateProfileString (g_cbBasicScript, g_cbAutoStart , pcMacroName, FileName)) 
			return S_OK;
	}

	return hr;
}

BOOL ReadRegSettingsLastOpenFile(char *pc, DWORD dwL)
{
CCurrentUser regDirs (KEY_READ, g_cbDirKey);
DWORD dwLen = dwL;

	if (!regDirs.GetSubSZ (g_cbLastFile, pc, dwLen)) {
		dwLen = dwL;
		return regDirs.GetSubSZ(g_cbMacroDir, pc, dwLen);
	}
	return TRUE;
}

BOOL SaveRegSettingsLastOpenFile (LPCSTR pc)
{ 
CCurrentUser regBS (g_cbDirKey, true);
char cbBuffer[_MAX_PATH];

	strcpy (cbBuffer, pc);
	PathAddBackslash(cbBuffer);
	return regBS.SetSubSZ (g_cbLastFile, cbBuffer);		// save in reg file...	
}                                         

BOOL ParseVersion(LPSTR szVersion, int & iFirst, int & iSecond, int & iThird)
{
	iFirst = 0;
	iSecond = 0;
	iThird = 0;

	LPSTR lpstr = strtok (szVersion, ".");

	if (NULL == lpstr) return false;
	iFirst = atoi (lpstr);
	
	lpstr = strtok (NULL, ".");
	if (NULL == lpstr) return false;
	iSecond = atoi (lpstr);

	lpstr = strtok (NULL, ".");
	if (NULL == lpstr) return false;
	iThird = atoi (lpstr);

	return true;
}

BOOL ReadRegSettingsBSVersion(HWND hWnd)
{
char szVersion[MAXSTRLENGTH];
int iFirstBS = 0, iSecondBS = 0, iThirdBS = 0;
CString str, strApp; 

	szVersion[0] = '\0';
	ebVersion (szVersion);	// volle Version von SUMMIT geben lassen

	if (!ParseVersion(szVersion, iFirstBS, iSecondBS, iThirdBS))
		return false;

	if (!::LoadString(strApp, IDS_LONGCLASSNAME)) 
		return false;

	if (iFirstBS > 2 || iSecondBS > 25 || iThirdBS > ebBUILD_NUMBER) {
		if (!::LoadString(str, IDS_NEWERVERSION)) 
			return false;
		MessageBox(hWnd, str, strApp, MB_OK);
		return true;
	}

	if (iFirstBS < 2 || iSecondBS < 25 || iThirdBS < ebBUILD_NUMBER) {
		if (!::LoadString(str, IDS_OLDERVERSION)) 
			return false;
		MessageBox(hWnd, str, strApp, MB_OK);
		return true;
	}
	return true;
}

BOOL SaveRegSettingsBSVersion (void)
{
CCurrentUser regBS (g_cbCfgKey, true);
char szVersion[MAXSTRLENGTH];
	
	ebVersion (szVersion);
	return regBS.SetSubSZ (g_cbBSVersion, szVersion);	// save in reg file...
}

BOOL ReadRegSettingsMacrosDirectory(char *pc, DWORD dwL)
{
CCurrentUser regBS (KEY_READ, g_cbDirKey);

	if (!regBS.GetSubSZ (g_cbMacroDir, pc, dwL))
		return false;
	
	strcat(pc, "\\");
	return true;
}

BOOL ReadRegSettingsAutoLoadFile(char *pc, DWORD dwL)
{
CCurrentUser regBS (KEY_READ, g_cbCfgKey);

	*pc = '\0';
	if (!regBS.GetSubSZ (g_cbAutoLoadFile, pc, dwL) || 0 == strlen(pc))
		return false;
	return true;
}

BOOL SaveRegSettingsAutoLoadFile (LPCSTR pc)
{ 
CCurrentUser regBS (g_cbCfgKey, true);

	return regBS.SetSubSZ (g_cbAutoLoadFile, pc);		// save in reg file...	
}                                         

void MakePath(LPSTR Buf, LPSTR DirPath)
{
char Path[_MAX_PATH];
char FName[_MAX_FNAME];
char Drive[_MAX_PATH];


	_splitpath (Buf, Drive, Path, FName, NULL);		// DateiNamen splitten
	_makepath (DirPath, Drive, Path, NULL, NULL);	// auszugebender Name
}

CString CorrectExtension (CString &rPath, UINT uiResIDExt)
{
CString strNew, strDrive, strPath, strName, strExt;
	
	TRY {                                       
	char *pNew = strNew.GetBuffer (_MAX_PATH);
	char *pDrive = strDrive.GetBuffer (_MAX_DRIVE);
	char *pPath = strPath.GetBuffer (_MAX_PATH);
	char *pName = strName.GetBuffer (_MAX_FNAME);

		if (!::LoadString (strExt, uiResIDExt)) return  '\0';
	
		_splitpath (rPath, pDrive, pPath, pName, NULL);
		_makepath (pNew, pDrive, pPath, pName, strExt);

   	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  '\0';
	}                  
	END_CATCH

	strNew.ReleaseBuffer();
	return strNew;
}

BOOL FileErrorMessage (UINT uiResID, CString &rstrFileName)
{
CString strPrompt;
CString strOut;
char *pOut = NULL;

	TRY {
		pOut = strOut.GetBuffer (_MAX_PATH);
   		if (pOut == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  false;
	}                  
	END_CATCH

	if (!::LoadString (strPrompt, uiResID)) 
		return false;

	wsprintf (pOut, strPrompt, rstrFileName);
	AfxMessageBox (pOut, MB_OK|MB_ICONEXCLAMATION);
	strOut.ReleaseBuffer();

	return false;		// liefert immer false
}

CString GetPathName (LPCSTR pcPath)
{
CString strDrive, strPath, strName;
	
	TRY {                                       
	char *pNewPath = strPath.GetBuffer (_MAX_PATH);
	char *pDrive = strDrive.GetBuffer (_MAX_DRIVE);
	char *pName = strName.GetBuffer (_MAX_PATH);
		
		if(pNewPath == NULL || pDrive == NULL || pName == NULL)
			return  '\0';

   		_splitpath (pcPath, pDrive, pNewPath, NULL, NULL);
		_makepath (pName, pDrive, pNewPath, g_cbNil, g_cbNil);
		
		if (*pNewPath) 
			pName[strlen(pName)-1] = '\0';	// abschließendes '\\' entfernen
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  '\0';
	}                  
	END_CATCH
	return strName;
}

BOOL IsRemoteDir(LPCSTR cbPath)
{
LPSTR lpstr = (LPSTR)cbPath;
	
	if (*lpstr == '\\') {
		if (*(++lpstr) == '\\')
			return true;
	}
	return false;
}

BOOL IsValidString(LPCSTR lpcstr)
{
	if (NULL == lpcstr || '\0' == *lpcstr) 
		return false;
	return true;
}

BOOL AssertValidString(LPCSTR lpcstr)
{
	ASSERT(NULL != lpcstr);
	if (NULL == lpcstr) return false;
	ASSERT('\0' != *lpcstr);
	 if ('\0' == *lpcstr) return false;
	return true;
}

CRunningObjectsHelper * GetRunningObjectsHelper()
{
	return g_pBSE -> GetRunningObjectsHelper();
}

void ErrorMessage(HWND h, LPCSTR lpcstrMessage)
{	
	::MessageBox (h, lpcstrMessage, "Makroprogrammierung", MB_OK | MB_ICONINFORMATION); 
}

HRESULT MessageRuntimeError(ebLPCSTR lpMsg, DWORD dwErrNum, ebWORD wLineNr, CRunErr **ppRunErr)
{
	ASSERT(ppRunErr);
	if (NULL == ppRunErr) return E_POINTER;
	*ppRunErr = NULL;

	try {
	CString strCaption, strPrompt, strErr;

		if (!LoadString(strCaption, IDS_LONGCLASSNAME) ||  
			!LoadString(strErr, IDS_RUNTIME_ERROR))
			_com_issue_error(E_OUTOFMEMORY);

	LPSTR pPrompt = strPrompt.GetBuffer(MAXSTRLENGTH);

		wsprintf (pPrompt, strErr, dwErrNum, wLineNr, lpMsg);
		::MessageBox(::GetActiveWindow(), pPrompt, strCaption, MB_OK);

	// Projekt schon geschlossen
		if (!GetRunningObjectsHelper() -> GetOpenProject()) 
			_com_issue_error(E_UNEXPECTED);

		THROW_FAILED_HRESULT(g_pBSE -> GetRuntimeDebugger(ppRunErr));
	} 
	catch (_com_error& e) 
	{
		return _COM_ERROR(e);
	}
	catch (CMemoryException) 
	{
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// ObjectMap dieser Erweiterung 

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ExportImportProject, CExportImportProject)
	OBJECT_ENTRY(CLSID_RegisterEbs, CRegisterEbs)
	OBJECT_ENTRY(CLSID_BSWrapperExtension, CBSWrapperExtension)
	OBJECT_ENTRY(CLSID_Script, CMacroScript)
	OBJECT_ENTRY(CLSID_MacroScriptExtension, CMacroScriptExtension)
	OBJECT_ENTRY(CLSID_FileScript, CMacroFileScript)
	OBJECT_ENTRY(CLSID_CreateObjectFeatureScript, CObjectFeatureScript)
	OBJECT_ENTRY(CLSID_CreateObjectFeatureFileScript, CObjectFeatureFileScript)
	OBJECT_ENTRY(CLSID_StreamInfo, CStreamInfo)
	OBJECT_ENTRY(CLSID_FilterScript, CFilterScriptPropAct)
	OBJECT_ENTRY(CLSID_ObjFeatPPExt, CObjFeatPPExt)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		
}

