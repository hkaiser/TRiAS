// Makroporgrammierung mit BasicScript 2.1 ------------------------------------
// File: BSCRIPT.CXX

#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#if defined(WIN32)
#include "afxcmn.h"
#include "registry.hxx"
#endif // WIN32

#include <io.h>
#include <ctype.h>
#include <float.h>

#include <olectl.h>
#include <fnamestr.h>

#include <initguid.h>
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

#include "macrguid.h"

#include "version.h"
#include "toolbarx.h"

#include "conststr.h"

#include "imacro.h"  
#include "imacorg.h"                

#include <ospace/std/string>
#include <fstream.h>

#include "myenum.h"
#include "enumscpt.h"
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "listitem.h"

#include "commsi.h"
#include "analimp.h"
#include "procimp.h"
#include "anpasimp.h" 
#include "saveimp.h"

#include "macro.h"
#include "macroorg.h"

#include "scrptdlg.h"
#include "bscripta.h"
#include "triasext.h"
#include "runscorg.h"
#include "runerr.h"

#ifndef WIN32
#include "waitcur.h"
#endif

#define OS_NO_STREAM_SUPPORT

// Menü anpassen ausschliessen, später weiterbearbeiten
#define NOMENU

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(PersistStorage);
DefineSmartInterface(PropertyActionSequence);

// Bei Runtimefehler setzen zum Debugger hochfahren
CRunErr *g_pRunErr = NULL;

// globale Variablen ----------------------------------------------------------
bool g_fShouldSuspend = false;	// alle Threads unterbrechen
bool g_fShouldAbort = false;	// alle Threads abbrechen

bool g_fMenuLoaded = false;
bool g_fStorageIsValid = false;
HWND g_hWnd = NULL;

extern int 	g_iC;
extern int 	g_iLE;

bool RegPropActPage(REFCLSID rclsid, LPCSTR pcProgID); // z. b. TRiASEx.FilterScript.1
bool UnRegPropActPage(LPCSTR pcProgID); // z. b. TRiASEx.FilterScript.1

bool UnRegAutoStartScriptFile();
bool RegAutoStartScriptFile();

HRESULT LoadStorageMenuItems(IUnknown *pIUnk);
HRESULT LoadStorageMacroScripts(IUnknown *pIUnk);

CRunScriptsOrg * GetRunningScripts (void);

HRESULT MakePathName(LPCSTR pPathName, LPSTR pNameToUse);
CString GetPathName (CString &rPath);
bool LoadString(CString & str, int IDS);

HRESULT		RunThread(	IScriptContainer *pIScriptContainer, 
						CebInstance *pebInstance, 
						const CString& strMacroName,
						bool fAutoStart);
HRESULT		RunThread_File(	IScriptContainer *pIScriptContainer, 
						CebInstance *pebInstance, 
						const CString& strMacroName,
						bool fAutoStart);
HRESULT RunScript(CebEntryInfo & EI, ebHSCRIPT hScript, CRunErr *pRunErr, bool & fE, bool & fBreak, bool fA);
HRESULT ReadIniAutoLoadScript (char *pcMacroName, int iLen);

HRESULT GetMethodType(ebHOBJECT hObject, LPCSTR pEntry);

bool ReadRegSettingsMacrosDirectory(char *pc, DWORD dwL);

bool SetEntryInfoUnLoadScript(CebEntryInfo & EI);
bool SetEntryInfoLoadScript(CebEntryInfo & EI);
bool ResetEntryInfo(CebEntryInfo & EI);

SummitModul g_SummitModuls[] = {
	{ PRODUCT_COM_NAME ebMODEXT, false },	/* Compiler */
	{ PRODUCT_DC_NAME  ebMODEXT, false },	/* Debugger Control */
	{ PRODUCT_RUN_NAME ebMODEXT, false },	/* Runtime */
	{ PRODUCT_DED_NAME ebMODEXT, false },	/* Dialog Editor DLL */
	{ "", false },	
};

HRESULT GetInstalledSummitModuls (void);

HRESULT MakeSubStorage(LPSTORAGE pIRootStorage, LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						bool &fNew, bool fDirect, CLSID clsID);

// Rückruffunktion bei Runtimeerror
extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnRuntimeError (	long lParam, 
															ebLPCTSTR lpMsg, 
															ebDWORD dwErrNum,
															ebWORD wLinNr, 
															ebWORD wCharPos, 
															ebLPCTSTR lpSource,
															ebLPCTSTR lpHelpFile, 
															ebDWORD dwHelpContext)
{
CString strCaption, strPrompt;

	if (!LoadString(strCaption, IDS_LONGCLASSNAME)) 
		return;

char *pPrompt = strPrompt.GetBuffer(MAXSTRLENGTH);
	
	if (pPrompt == NULL) {
		ASSERT(0); return;
	}

CString strErr;

	LoadString(strErr, IDS_RUNTIME_ERROR);
	wsprintf (pPrompt, strErr, dwErrNum, wLinNr, lpMsg);

	::MessageBox(::GetActiveWindow(), pPrompt, (LPCSTR)strCaption, MB_OK);

// Schon SuspendDebugger geladen (Breakpointverarbeitung)
//	if (true == ((CRunErr *)lParam) -> GetSuspendDebugger())
//		return;

	ASSERT(g_pRunErr == NULL);

	g_pRunErr = (CRunErr *)lParam;
	if (g_pRunErr) 
		g_pRunErr -> OnDemandRuntimeError(wLinNr);
}

// Routine, über die die Module enumeriert werden -----------------------------
extern "C" 
ebBOOL ebCALLBACK _XTENSN_EXPORT ebGetNextModule (ebLPSTR lpFileName, long lParam)
{
	if (g_pTE == NULL) return false;

return ((CMacroScriptExtension *)g_pTE) -> GetNextModule (lpFileName);
}

// Routine, die regelmäßig während der Ausführung eines Threads gerufen wird --
extern "C" 
void ebCALLBACK _XTENSN_EXPORT ebPCodeCallBack (ebHTHREAD hThread, ebLONG)
{
	CallMessageQueue();		// Yielding
		
	if (g_fShouldAbort)		// Aborting 
		ebThread_Interrupt (hThread, 1, 0);
	
	if (g_fShouldSuspend) 		// Suspend
		ebThread_Interrupt (hThread, 0, 0);
}

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
{
	return new CMacroScriptExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden. 
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
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
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		if ( !RegPropActPage(CLSID_FilterScript, TEXT("TRiASEx.FilterScript.1")) )
			return false;

// Menü anpassen ausschliessen, später weiterbearbeiten
#ifndef NOMENU
		if ( !RegisterHandler (	CLSID_MacroScriptCustomizePPage, 
								TEXT("TRiASEx.CustomizeMenu.1"), 
								IDS_LONGCLASSNAMECUSTOMIZE, 
								CLSID_DirisProject, 
								TEXT("TRiAS.Application.2")) )
			return false;
#endif
		if ( !RegAutoStartScriptFile())
			return false;

		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_MacroScriptExtension, 
				TEXT("TRiAS.MacroScript.1"), IDS_LONGCLASSNAME,
				SCRIPT_MAJORVERSION, SCRIPT_MINORVERSION,
				EFPreLoad|EFVisible);
	} else {
	// RegDB säubern
		if ( !UnRegPropActPage (TEXT("TRiASEx.FilterScript.1")) )
			return false;

// Menü anpassen ausschliessen, später weiterbearbeiten
#ifndef NOMENU
		if ( !UnRegisterHandler(CLSID_MacroScriptCustomizePPage, 
								TEXT("TRiASEx.CustomizeMenu.1"), 
								CLSID_DirisProject, 
								TEXT("TRiAS.Application.2")) ) 
			return false;
#endif
		if ( !UnRegAutoStartScriptFile())
			return false;

		return ExtOleUnregisterClass (CLSID_MacroScriptExtension, 
					      TEXT("TRiAS.MacroScript.1"));
	}

return true;	// alles ok
}

LPUNKNOWN CMacroScriptExtension :: GetMacroOrg()
{
	ASSERT (m_pMacroOrg);
	return m_pMacroOrg;
}

LPUNKNOWN CMacroScriptExtension :: GetMacroScripts()
{
	ASSERT (m_pMacroScripts);
	return m_pMacroScripts;
}

bool CMacroScriptExtension::RegisterExtensions (LPCSTR pcFPath)
{
HANDLE hFile;
string strFile (pcFPath);
WIN32_FIND_DATA c_file;

	strFile += TEXT("*.EBN");
	if ((hFile = FindFirstFile (strFile.c_str(), &c_file)) == INVALID_HANDLE_VALUE)
		return true; 		// nichts gefunden

	do {
		if (c_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		strFile = string(pcFPath) + c_file.cFileName;

		m_pBScriptExt -> RegisterExtModule (strFile.c_str());
	} while (FindNextFile (hFile, &c_file));

	FindClose (hFile);
	return true;
}

// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden. Die Destruktoren sind 'virtual', so daß auch so
// alles sauber aufgeräumt werden kann.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CMacroScriptExtension :: CMacroScriptExtension (void)
		       : CTriasExtension (IDR_MACRO)
{
	m_hMenu = 0;

	m_pMacroScripts = NULL; 
	m_pMacroOrg = NULL;

	m_pebInst = NULL;
	m_hDCInst = NULL;
	m_pDebugWnd = NULL;

	m_pBScriptExt = CExtendBScript :: CreateInstance (this);
	
	if (m_pBScriptExt) {
	// registriert sich selbst als ExtensionModule
	TCHAR cbModule[_MAX_PATH+1];
	
		GetModuleFileName (g_hInstance, cbModule, _MAX_PATH);
		m_pBScriptExt -> RegisterExtModule (cbModule);

	string strPath (cbModule);

		strPath = get_drive(strPath) + get_path(strPath);
		RegisterExtensions (strPath.c_str());
	}
	
// globale Variablen initialisieren
	g_fShouldSuspend = false;
	g_fShouldAbort = false;
}

// Destruktor -----------------------------------------------------------------
CMacroScriptExtension :: ~CMacroScriptExtension (void) 
{
	if (m_pBScriptExt)
		delete m_pBScriptExt;
}


// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen. Die Semantik hat sich nicht geändert.
#if defined(WIN32)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

STDMETHODIMP_(bool) CMacroScriptExtension :: InitExtension (short iMode)
{
// Initialisierung der BasisKlasse
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	if (m_pBScriptExt == NULL) return false;	// Fehler
	
HRESULT hr = GetInstalledSummitModuls();
	if (FAILED(hr)) return false;

// BScript vorbereiten
ebWORD	wFlags = EBINIT_SEARCH_PROC;

	if (g_SummitModuls[COMPILER].fIsInstalled) 
		wFlags |= EBINIT_USECOMPILER;

	if (g_SummitModuls[RUNTIME].fIsInstalled)
		wFlags |= EBINIT_USERUNTIME;

	m_pebInst = new CebInstance (wFlags, ebGetNextModule);		
	if (m_pebInst == NULL) return false;

// evtl. DebuggerControl explizit laden
	if (g_SummitModuls[DEBUGGER].fIsInstalled) {
		m_hDCInst = LoadLibrary (PRODUCT_DC_NAME ebMODEXT);
		if (LOADLIBRARY_FAILED(m_hDCInst)) {
			m_hDCInst = NULL;
			return false;
		}
	} else 
		m_hDCInst = NULL;
			
// Notifikationen anmelden
	
	// zum Schließen des Debuggers	
	RegisterNotification (WM_CLOSEDEBUGGERDIALOG, false);	
	
	RegisterNotification (DEX_INITIALIZEDSERVER);
	RegisterNotification (DEX_N_EXTENSIONSLOADED);
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_ISCLOSEDPROJECT);        
	RegisterNotification (DEX_PROJECTCLOSE);

	RegisterNotification (DEX_N_SAVESAMESTORAGE);		// für alle Fälle
	RegisterNotification (DEX_N_SAVEOTHERSTORAGE);		
	RegisterNotification (DEX_N_SAVECOMPLETED);		
	RegisterNotification (DEX_N_HANDSOFFSTORAGE);		
        
// Makros nur initialisieren, wenn Projekt offen	
	hr = InitScripts();
	if (FAILED(hr)) return false; 

	hr = GetMenuStructure ();
	if (FAILED(hr)) return false; 

	m_pRunScriptsOrg = new CRunScriptsOrg;
	if (NULL == m_pRunScriptsOrg) { 
		AfxMessageBox(IDS_NOMEMORY); return false; 
	}

return true;
}

HRESULT CMacroScriptExtension :: InitScripts()
{
LPSTORAGE pIRootStorage = NULL;
char cBuffer[_MAX_PATH];	

// Makros nur initialisieren, wenn Projekt offen	
	if (NULL == DEX_GetActiveProject (cBuffer)) return ResultFromScode(S_FALSE);
	
	ASSERT(NULL == m_pMacroScripts);
	m_pMacroScripts = CMacroScripts :: CreateScript(NULL, m_pebInst); 
	
	if (NULL == m_pMacroScripts) 
		return E_OUTOFMEMORY;                                                             

HRESULT hr = LoadStorageMacroScripts(m_pMacroScripts);
	
	if (FAILED(hr)) 
		return hr;  


return NOERROR;
}

HRESULT CMacroScriptExtension :: GetMenuStructure()
{	
// Menüstruktur nur initialisieren, wenn Projekt offen	
char cBuffer[_MAX_PATH];
	if (NULL == DEX_GetActiveProject (cBuffer) || m_pMacroOrg) return NOERROR;
	
CMenu* pMenu = MWind() -> GetMenu() ;
	if (pMenu == NULL) {
		ASSERT(0); return ResultFromScode(E_POINTER);
	}

HMENU hMenu = pMenu -> GetSafeHmenu();
	if (0 == hMenu) {
		ASSERT(0); return ResultFromScode(E_HANDLE);
	}

	ASSERT(m_pMacroScripts); 

	if (m_pMacroScripts == NULL) 
		return ResultFromScode(E_POINTER);

	try {
	WScriptContainer ISC(m_pMacroScripts);		// throws hr

		m_pMacroOrg = CMacroOrg :: Create(NULL, MenuOffset(), ISC);
		if (NULL == m_pMacroOrg) 
			throw E_OUTOFMEMORY;
	
		THROW_FAILED_HRESULT(LoadStorageMenuItems(m_pMacroOrg));

	WAnalyse IA (m_pMacroOrg);		// throws hr
		
		return IA -> GetMenuStructure (hMenu);

	} catch (HRESULT hr) {
		return hr;
	}
}

// Diese Funktion wird gerufen bevor die Erweiterung freigegeben wird.
// An dieser Stelle kann (und soll) der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, und sonstige Aufräumarbeiten durchgeführt werden.
// Die Semantik hat sich nicht geändert.
STDMETHODIMP_(bool) CMacroScriptExtension :: UnLoadExtension (void)
{
// Makros nur entladen, wenn Projekt offen ist
	VERIFY(SUCCEEDED(SaveMacros(NULL, true /* nach Speichern fragen */)));

	UnRegisterNotification (WM_CLOSEDEBUGGERDIALOG, false);

	UnRegisterNotification (DEX_INITIALIZEDSERVER);		// für alle Fälle
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_ISCLOSEDPROJECT);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_N_EXTENSIONSLOADED);

	UnRegisterNotification (DEX_N_SAVESAMESTORAGE);		
	UnRegisterNotification (DEX_N_SAVEOTHERSTORAGE);		
	UnRegisterNotification (DEX_N_SAVECOMPLETED);		
	UnRegisterNotification (DEX_N_HANDSOFFSTORAGE);		

	VERIFY(SUCCEEDED(StopAllRun ()));

	if (m_pRunScriptsOrg) {
		delete m_pRunScriptsOrg;
		m_pRunScriptsOrg = NULL;
	}
	if (m_pMacroOrg) {
		VERIFY(0 == m_pMacroOrg -> Release());
		m_pMacroOrg = NULL;
	}
	if (m_pMacroScripts) {
		VERIFY(0 == m_pMacroScripts -> Release());
		m_pMacroScripts = NULL;
	}

// BasisScript freigeben
	if (m_hDCInst) {
		FreeLibrary (m_hDCInst);
		m_hDCInst = NULL;
	}
	if (m_pebInst) {
		delete m_pebInst;
		m_pebInst = NULL;
	}

return CTriasExtension :: UnLoadExtension();
}

HRESULT CMacroScriptExtension :: Save (REFCLSID rclsid, int IDS/* diesen Storage nach ->*/, LPSTORAGE lpOtherStorage)
{
LPSTORAGE lpProjStor = NULL;
LPSTORAGE lpSubStor = NULL;
LPSTORAGE lpOtherSubStor = NULL;
HRESULT hr = NOERROR;
	
	if (!DEX_GetProjectStorage(lpProjStor))
		return E_FAIL;

CMacroScripts *pMS = CMacroScripts::CreateScript(NULL, m_pebInst); 

	if (NULL == pMS) return E_OUTOFMEMORY;

	try {
	CString strStorName;

		if (!LoadString(strStorName, IDS))
			throw E_FAIL;

	bool fNew = false;	// SubStorage diesen Projektes öffnen
		
		THROW_FAILED_HRESULT(MakeSubStorage(lpProjStor, &lpSubStor, strStorName, fNew, true, rclsid)); 
		if (NULL == lpSubStor) throw E_POINTER;

	// kein SubStorage
		if (fNew) throw E_FAIL;

	// SubStorage des anderen Projektes kreieren
		THROW_FAILED_HRESULT(MakeSubStorage(lpOtherStorage, &lpOtherSubStor, strStorName, fNew, true, CLSID_MenuItems)); 
		if (NULL == lpOtherSubStor) throw E_POINTER;

	// macht auch CopyTo, wenn lpOtherStorage != NULL
	WPersistStorage IPS(pMS);	// throws hr

		THROW_FAILED_HRESULT(IPS -> Load (lpSubStor));
		THROW_FAILED_HRESULT(IPS -> Save (lpOtherSubStor, false /* nicht fSameAsLoad*/));

	} catch (HRESULT hr) {
		
		RELEASE(lpProjStor);
		RELEASE(lpSubStor);
		RELEASE(lpOtherSubStor);

		pMS -> Release();
		return hr;
	}

	RELEASE(lpProjStor);
	RELEASE(lpSubStor);
	RELEASE(lpOtherSubStor);

// von CreateInstance(), macht auch lpSubStorage -> Release()
	pMS -> Release();

return NOERROR;
}

HRESULT CMacroScriptExtension :: DestroyMenuItemsStorage()
{
	if (m_pMacroOrg == NULL) return NOERROR;

	try {
	WSave IS(m_pMacroOrg);		// throws hr
	LPSTORAGE pIS = NULL;
	
		if (!DEX_GetProjectStorage(pIS)) 
			return S_FALSE;
	
		pIS -> Release();
		return IS -> DestroyStorage(IDS_STORAGE_NAME_MENUITEMS);

	} catch (HRESULT hr) {
		return hr;
	}
}

HRESULT CMacroScriptExtension :: SaveMenuItems()
{
	if (m_pMacroOrg == NULL) return NOERROR;

	try {
	WSave IS(m_pMacroOrg);		// throws hr
	LPSTORAGE pIS = NULL;
	
		if (!DEX_GetProjectStorage(pIS))
			return IS -> SaveFile();		
		pIS -> Release();
	
	} catch (HRESULT hr) {
		return hr;
	}

return NOERROR;
}	

HRESULT CMacroScriptExtension :: SaveMenuItems(LPSTORAGE pIOtherStorage)
{
	if (m_pMacroOrg == NULL) return NOERROR;

LPSTORAGE pIS = NULL;

	if (NULL == DEX_GetProjectStorage(pIS)) 
		return E_FAIL;	
	pIS -> Release();

	try {
	WSave IS(m_pMacroOrg);		// throws hr
	LPSTORAGE pISubStor = NULL;
	HRESULT hr = NOERROR;
	
		if (pIOtherStorage) {		
		CString strStorName;

			if (!LoadString(strStorName, IDS_STORAGE_NAME_MENUITEMS)) 
				return ResultFromScode(E_FAIL);
	
		bool fNew = false;
		
			THROW_FAILED_HRESULT(MakeSubStorage(pIOtherStorage, &pISubStor, strStorName, fNew, true, CLSID_MenuItems));
		}

		hr = IS -> Save(pISubStor, pISubStor ? false : true);
		RELEASE(pISubStor);
		return hr;

	} catch (HRESULT hr) {
		return hr;
	}
}

HRESULT CMacroScriptExtension :: SaveCompletedMenuItems(LPSTORAGE pIOtherStorage)
{
	if (m_pMacroOrg == NULL) return NOERROR;

	try {
	WSave IS(m_pMacroOrg);		// throws hr
	LPSTORAGE pISubStor = NULL;
	HRESULT hr = NOERROR;
	
		if (pIOtherStorage) {		
		CString strStorName;
		
			if (!LoadString(strStorName, IDS_STORAGE_NAME_MENUITEMS)) 
				return ResultFromScode(E_FAIL);
	
		bool fNew = false;
			
			THROW_FAILED_HRESULT(MakeSubStorage(pIOtherStorage, &pISubStor, strStorName, fNew, true, CLSID_MenuItems));
		}
	
		hr = IS -> SaveCompleted(pISubStor);
		RELEASE(pISubStor);
		return hr;
	
	} catch (HRESULT hr) {
		return hr;
	}
}

HRESULT CMacroScriptExtension :: HandsOffStorageMenuItems()
{
	if (m_pMacroOrg == NULL) return NOERROR;

	try {
	WSave IS(m_pMacroOrg);		// throws hr

		return IS -> HandsOffStorage();
	} catch (HRESULT hr) {
		return hr;
	}
}

void MakePath(LPSTR Buf, LPSTR DirPath)
{
char Path[_MAX_PATH];
char FName[_MAX_FNAME];
char Drive[_MAX_PATH];

	// DateiNamen splitten
	_splitpath (Buf, Drive, Path, FName, NULL);
	// auszugebender Name
	_makepath (DirPath, Drive, Path, NULL, NULL);
}

HRESULT CMacroScriptExtension :: SetHomDirBS()
{
char Buf[_MAX_PATH];
	if (! DEX_GetActiveProject(Buf) || !m_pebInst) return ResultFromScode(S_FALSE);

char DirPath[_MAX_PATH];
	
	MakePath(Buf, DirPath);

	ebInst().SetHomeDir(DirPath);

return NOERROR;
}

STDMETHODIMP_(LRESULT) CMacroScriptExtension :: Notification (WPARAM iMsg, LPARAM p)
{
HRESULT hr = NOERROR;
LPSTORAGE pIStorage = NULL;

	switch (iMsg) {
	case DEX_N_EXTENSIONSLOADED:	// TRiAS fertig initialisiert
	// an dieser Stelle haben sich alle Erweiterungen angemeldet
		{		// Initialisierung von BasicScript
			Reset();
			if (!ebInst().Create()) {
			// sonstige Initialisierungen
				ebInst().SetPublicSpace (0x00100000L);	// 1MByte StringSpace
				ebInst().SetWindow (hWnd());		// ParentWindow
				ebInst().SetPcodeCallbackProc (ebPCodeCallBack, (ebLONG)this);
			
			// Runtimeerror-Callbackfunktion anmelden				
				ebInst().SetRuntimeErrorProc(&OnRuntimeError, 0);
				hr = SetHomDirBS();
				if (FAILED(hr)) return false;

			} else {
				if (m_pebInst)
				delete m_pebInst;
			}
		}
		break;          
	case DEX_INITIALIZEDSERVER:
		break;
	case DEX_PROJECTOPEN:
		{			
			hr = SetHomDirBS();
			if(FAILED(hr)) return false;

		// Makros laden, wenn Projekt geöffnet wird 
			hr = InitScripts();
			if (FAILED(hr)) return false;

			AutoLoadScript ();

 // Ist Menü vollständig ?, siehe WindowsNotification()
			RegisterNotification (WM_OPENPROJECT, false);
			if ( ! MWind() -> PostMessage(WM_OPENPROJECT) ) return false;
		}
		break;
	case DEX_ISCLOSEDPROJECT:
		{	
		// Makros in jedem Fall entladen, wenn Projekt geschlossen wird
			if (m_pMacroOrg) {
				VERIFY (0 == m_pMacroOrg -> Release());
				m_pMacroOrg = NULL;
			}
			if (m_pMacroScripts) 
			{
				m_pMacroScripts -> Release();
				m_pMacroScripts = NULL;
			}
			
			ASSERT(g_iLE==0);
			ASSERT(g_iC==0);
		}
        break;
	case DEX_PROJECTCLOSE:		
		{
			hr = StopAllRun ();
			if (FAILED(hr)) return false;
	
			if (!OnCloseDebugDlg(true)) return false;
			
		// Save() für altes Projekt
			hr = CommitMacros (true);
			if (FAILED(hr)) return false;
			
			hr = DestroyMenuItemsStorage();
			if (FAILED(hr)) return false;

			hr = SaveMenuItems();
			if (FAILED(hr)) return false;
		}	
		break;
	case DEX_N_SAVESAMESTORAGE:
	// im gleichen Storage abspeichern
		{
			hr = SaveMacros (NULL, false);
			if (FAILED(hr)) return false;
			
			hr = SaveMenuItems(NULL);
			if (FAILED(hr)) return false;
		}
		break;
	case DEX_N_SAVEOTHERSTORAGE:
	// im anderen Storage abspeichern
		{
			hr = SaveAsMacros ((LPSTORAGE)p);
			if (FAILED(hr)) return false;
			
			hr = SaveMenuItems((LPSTORAGE)p);
			if (FAILED(hr)) return false;

			hr = Save (CLSID_ScriptContainer, IDS_STORAGE_NAME_OPERATESCRIPTS, (LPSTORAGE)p);
			if (FAILED(hr)) return false;
		}
		break;

	case DEX_N_SAVECOMPLETED:
	// Das Speichern abschliessen.
	// Wenn "Kopie speichern als", alten Substorage beibehalten
	// Wenn "Seichern unter", dann neuen Substorage öffnen
		{
			hr = SaveCompleted((LPSTORAGE)p);
			if (FAILED(hr)) return false;

			hr = SaveCompletedMenuItems((LPSTORAGE)p);
			if (FAILED(hr)) return false;
		}
		break;
	case DEX_N_HANDSOFFSTORAGE:
	// Storages schliessen bzw. freigeben
		{
			hr = HandsOffStorage();
			if (FAILED(hr)) return false;			
			
			hr = HandsOffStorageMenuItems();
			if (FAILED(hr)) return false;
		}
		break;
	default:
		break;
	}

return false;
}

HRESULT CMacroScriptExtension :: HandsOffStorage()
{
char cBuffer[_MAX_PATH];
	
// Makros sind nur dann initialisiert, wenn Projekt offen war
	if (NULL != DEX_GetActiveProject (cBuffer)) {

	HRESULT hr = NOERROR; 
	IPersistStorage *pIPS = NULL;		
			hr = m_pMacroScripts -> QueryInterface (IID_IPersistStorage, (LPVOID *)&pIPS);
			if (FAILED(hr)) return hr;
				
			hr = pIPS -> HandsOffStorage();
			pIPS -> Release();
			if (FAILED(hr)) return hr;
	}
	
return NOERROR;
}        	

HRESULT CMacroScriptExtension :: NewSubStorage (LPSTORAGE pIStorage, 
												LPSTORAGE *ppISubStorage)
{
IScriptContainer *pISC = NULL;		
HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IScriptContainer, 
												(LPVOID *)&pISC);
	if (FAILED(hr)) return hr;

	if (pIStorage) hr = pISC -> NewSubStorage (pIStorage, ppISubStorage);
	
	pISC -> Release();

return hr;
}

HRESULT CMacroScriptExtension :: SaveCompleted(LPSTORAGE pIStorage)
{
char cBuffer[_MAX_PATH];	
// Makros sind nur dann initialisiert, wenn Projekt offen war
	if (NULL != DEX_GetActiveProject (cBuffer)) {

	IPersistStorage *pIPS = NULL;		
	HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IPersistStorage, (LPVOID *)&pIPS);
		if (FAILED(hr)) return hr;

	LPSTORAGE pISubStorage = NULL;
// SubStor -> AddRef()
		hr = NewSubStorage (pIStorage, &pISubStorage);
		if (FAILED(hr)) return hr;

// SubStor -> AddRef()
		hr = pIPS -> SaveCompleted(pISubStorage);
		pIPS -> Release();
		if (FAILED(hr)) return hr;				
	
		if(pISubStorage) pISubStorage -> Release();
	}

	SetNotCommit(false);

return NOERROR;
}        	

HRESULT CMacroScriptExtension :: SetNotCommit(bool fNotCommit)
{
IScriptContainer *pISC = NULL;		
HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IScriptContainer, 
														(LPVOID *)&pISC);
	if (FAILED(hr)) return hr;
	pISC -> SetNotCommit(false);
	pISC -> Release();

return NOERROR;
}

HRESULT CMacroScriptExtension :: CommitMacros (bool fAsk)
{
IScriptContainer *pISC = NULL;		
HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IScriptContainer, 
												(LPVOID *)&pISC);
	if (FAILED(hr)) return hr;

	hr = pISC -> Commit(STGC_DEFAULT, fAsk);
	pISC -> Release();

return hr;
}

HRESULT CMacroScriptExtension :: SaveMacros (LPSTORAGE pIStorage, bool fAsk)
{
char cBuffer[_MAX_PATH];	
// Makros sind nur dann initialisiert, wenn Projekt offen war
	if (NULL == DEX_GetActiveProject (cBuffer)) return ResultFromScode(S_FALSE);

IPersistStorage *pIPS = NULL;
HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IPersistStorage, 
											(LPVOID *)&pIPS);
	if (FAILED(hr)) return hr; 

	hr = pIPS -> Save (NULL, true);
	pIPS -> Release();
	if (FAILED(hr)) return hr; 

// Commit() nötig, da "transacted" Speicherung 
	hr = CommitMacros (false);
	if (FAILED(hr)) return hr; 

// Speichern beendet, nochmaliges Bekanntmachen dieses Commit()
	DEX_SetDirtyGeoDB(1);
	
return hr;
}        	

// neuen Storage unter neuer Root anlegen
HRESULT CMacroScriptExtension :: SaveAsMacros (LPSTORAGE pIStorage)
{
	if (NULL == pIStorage)
		return ResultFromScode(E_FAIL);
	
char cBuffer[_MAX_PATH];

// Makros sind nur dann initialisiert, wenn Projekt offen war
	if (NULL != DEX_GetActiveProject (cBuffer)) {
	
	LPSTORAGE pISubStorage = NULL;
	HRESULT hr = NewSubStorage (pIStorage, &pISubStorage);
		if (FAILED(hr)) return hr;

		IPersistStorage *pIPS = NULL;
			hr = m_pMacroScripts -> QueryInterface (IID_IPersistStorage, (LPVOID *)&pIPS);
			if (FAILED(hr)) { 		
				pISubStorage -> Release();
				return hr; 
			}

// Commit() nicht nötig, da direkte Speicherung 
			hr = pIPS -> Save (pISubStorage, false);
			pIPS -> Release();
			pISubStorage -> Release();
			if (FAILED(hr)) return hr; 

	}

return NOERROR;
}        	


STDMETHODIMP_(LRESULT) CMacroScriptExtension :: WindowsNotification (
				UINT wMsg, WPARAM wParam, LPARAM lParam)
{
HRESULT hr = NOERROR;

	switch (wMsg) {
	case WM_CLOSEDEBUGGERDIALOG:
		
	// bei Laufzeitfehler, dieser Debuggerdialog offen
		if (g_pRunErr) {
			delete g_pRunErr;
			g_pRunErr = NULL;
		}
		return OnCloseDebugDlg(false);		// normaler Duggerdialog

	case WM_OPENPROJECT:
	// MenuStruktur analysieren
	//		hr = GetMenuStructure ();
	//		if (FAILED(hr)) return false;

		UnRegisterNotification (WM_OPENPROJECT, false);
		break;

	default:
		break;
	}
	
return false;
}

bool IsValidFile()
{
char Buffer[_MAX_PATH];
	
	if(NULL == DEX_GetActiveProject(Buffer)) 
		return false;

char Name[MAXSTRLENGTH];
HRESULT hr = MakeFileName(Buffer, Name, "men");
	
	if(FAILED(hr)) return false;

fstream file(Name, ios::in | ios::binary | ios::nocreate);
	if(file.fail()) return false;

return true;
}

bool IsValidStorage(int IDS)
{
char Buffer[_MAX_PATH];
LPSTORAGE pIS = NULL;
CString strStorName;
LPSTORAGE pIStorage = NULL; 
HRESULT hr = NOERROR;

	if (NULL == DEX_GetActiveProject(Buffer) || NULL == DEX_GetProjectStorage(pIS)) 
		return false;
	
	if (!LoadString(strStorName, IDS)) {
		pIS -> Release(); return false;
	}
	// Überprüfen, ob Storage vorhanden
	USES_CONVERSION;
	hr = pIS -> OpenStorage (A2OLE(strStorName), 
								NULL, 
								STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, 
								NULL, 0, &pIStorage);
	pIS -> Release();
// schon geladen, also vorhanden
	if (GetScode(hr) == STG_E_ACCESSDENIED) return true;
// kein Storage vorhanden, oder anderer Fehler			
	if (FAILED(hr)) return false;

// erfolgreich geöffnet
	if (pIStorage) pIStorage -> Release();
	
return true;
}

STDMETHODIMP_(bool) CMacroScriptExtension :: MenuInit (
				HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	if (hWnd == 0 && hMenu == MenuHandle()) {

	UINT uiEnabled = MF_GRAYED;

		pExtMenu() -> CheckMenuItem (IDM_TEST+MenuOffset(), 
			MF_BYCOMMAND | (m_pDebugWnd ? MF_CHECKED : MF_UNCHECKED));

		uiEnabled = (!g_SummitModuls[DEBUGGER].fIsInstalled || m_pDebugWnd) ? MF_GRAYED : MF_ENABLED;
		pExtMenu() -> EnableMenuItem (IDM_DBSCRIPT+MenuOffset(), MF_BYCOMMAND | uiEnabled);		

		uiEnabled = (!g_SummitModuls[DEBUGGER].fIsInstalled) ? MF_GRAYED : MF_ENABLED;
		pExtMenu() -> EnableMenuItem (IDM_TEST+MenuOffset(), MF_BYCOMMAND | uiEnabled);		

		uiEnabled = (!g_SummitModuls[RUNTIME].fIsInstalled) ? MF_GRAYED : MF_ENABLED;		
		pExtMenu() -> EnableMenuItem (IDM_MENULOAD+MenuOffset(), MF_BYCOMMAND | uiEnabled);

		if (IsValidStorage(IDS_STORAGE_NAME_MENUITEMS) || IsValidFile())
			g_fStorageIsValid = true;

		uiEnabled = (g_fStorageIsValid == false || g_fMenuLoaded == true) ?	MF_GRAYED : MF_ENABLED;
		pExtMenu() -> EnableMenuItem (IDM_MENULOAD+MenuOffset(), MF_BYCOMMAND | uiEnabled);

		return true;
	}
	
return false;		// nicht für uns
}

HRESULT CMacroScriptExtension :: RunSequence()
{
WPersistStreamInit IS;
HRESULT hr = CoCreateInstance(CLSID_PropertyActionSequence,	NULL,
							  CLSCTX_INPROC_SERVER,
							  IID_IPersistStreamInit,
							  (LPVOID *) IS.ppi()); // nur umkopieren
	if (FAILED(hr)) return hr;

	hr = IS -> InitNew();
	if (FAILED(hr)) return hr;

const CLSID * pclsID[2];

	pclsID[0] = &CLSID_SelectIdentObjTyp;
	pclsID[1] = &CLSID_FilterScript;

CALPCLSID CLSIDs;

	CLSIDs.cElems = 2;
	CLSIDs.ppElems = pclsID;

	try {
	WPropertyActionSequence ISeq(IS);	// throws hr

		THROW_FAILED_HRESULT(ISeq -> SetDescription("FilterScript"));
		THROW_FAILED_HRESULT(ISeq -> AddActionsByCLSID(&CLSIDs));

		hr = ISeq -> DoActions (hWnd(), NULL, NULL, NULL);
		if (GetScode(hr) == E_UNEXPECTED) return S_FALSE;

		if (FAILED(hr)) return hr;
	
	} catch (HRESULT hr) {
		return hr;
	}

return hr;
}

bool CMacroScriptExtension :: MacroScriptCall()
{
CScriptDlg SDlg (MWind(), m_pMacroScripts);
	
	if (SDlg.DoModal() != IDOK || SDlg.GetDel ())
		return true;

char str[MAXSTRLENGTH];

	if(!SDlg.GetName (str, MAXSTRLENGTH)) 
		return false;			

	if (SDlg.GetRun ()) {
	
	WScriptContainer ISC(m_pMacroScripts);

	HRESULT hr = ::RunThread(ISC, m_pebInst, str, false);
		
		if (FAILED(hr)) 
			return false;

		return true;
	}

	ASSERT(NULL == m_pDebugWnd);		
				
return OnDebugDlg (m_pMacroScripts, str); 
}

bool CMacroScriptExtension :: OtherMenuCommand(UINT uiID)
{
	if (m_pMacroOrg == NULL) return false;

	uiID += MenuOffset();

WProcess IPr (m_pMacroOrg);

HRESULT	hr = IPr -> MenuCommand(uiID);
	if(FAILED(hr)) return false;

return true;
}


bool CMacroScriptExtension :: LoadOtherMenu()
{ 
	if (g_fMenuLoaded == true) return true;

HRESULT hr = GetMenuStructure ();
	if (FAILED(hr)) {
		ASSERT(0); return false;
	}

CMenu* pMenu = MWind() -> GetMenu() ;
HMENU hMenu = pMenu -> GetSafeHmenu();
	if (0 == hMenu) return ResultFromScode(E_FAIL);

	try {
	LPSTORAGE pIStorage = NULL; 
	WSave IS(m_pMacroOrg);		// throws hr

		if (NULL == DEX_GetProjectStorage(pIStorage)) { 
		// nur einmal laden, ansonsten LoadFile() return S_FALSE
			THROW_FAILED_HRESULT(IS -> LoadFile());
		}
		else {
			pIStorage -> Release();
			hr = IS -> LoadFromStorage();
			if(FAILED(hr) || GetScode(hr) == S_FALSE) return true;
		}

		THROW_FAILED_HRESULT(IS -> InsertMenu(hMenu));

	} catch (HRESULT) {
		return false;
	}

	g_fMenuLoaded = true;

return true;
}

STDMETHODIMP_(bool) CMacroScriptExtension :: MenuCommand (UINT uiMenuID, HWND hWnd) 
{               
HWND g_hWnd = hWnd;
CWaitCursor WC;
HRESULT hr = NOERROR;
IDispatch *pDispatch = NULL;

	switch (uiMenuID) {
	
	case IDM_EDITSCRIPT:
		return OnInvokeScript();
	break;				
	
	case IDM_TEST:
		return OnDebugDlg();
	break;		
	
	case IDM_DBSCRIPT: 
		return MacroScriptCall();
	break;				
	
	case IDM_MENULOAD: 
		return LoadOtherMenu();
	break;				
	
	case IDM_FILTERSCRIPT: 
		hr = RunSequence();
		if (FAILED(hr)) return false;
		return true;
	break;				
	
	default:
		return OtherMenuCommand(uiMenuID);
	break;

	}
	
return false;
}

// Rufen einer Basic-Routine von außen ----------------------------------------
bool SetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam)
{
	switch (rParam.wType & TYP_TYPEMASK) {
	case TYP_EMPTY:
	case TYP_NULL:		break;
	case TYP_BOOLEAN:	return rThread.SetParamBool (iIndex, *(ebBOOL *)pParam);
	case TYP_INTEGER:	return rThread.SetParamInt (iIndex, *(short *)pParam);
	case TYP_LONG:		return rThread.SetParamLong (iIndex, *(long *)pParam);
	case TYP_SINGLE:	return rThread.SetParamSingle (iIndex, *(float *)pParam);
	case TYP_DOUBLE:   	return rThread.SetParamDouble (iIndex, *(double *)pParam);
	case TYP_CURRENCY: 	return rThread.SetParamCurrency (iIndex, *(ebCURRENCY *)pParam);
	case TYP_DATE:     	return rThread.SetParamDate (iIndex, *(double *)pParam);
	case TYP_STRING:
		{
			if (rParam.wType & TYP_MODSPARM)
	   			return rThread.SetParamString (iIndex, ::ebCreateString (rThread.GetHandle(), *(LPCSTR *)pParam));
			else
	   			return rThread.SetParamString (iIndex, ::ebCreateString (rThread.GetHandle(), (LPCSTR)pParam));
		}
	case TYP_OLEOBJECT:	return rThread.SetParamOleObject (iIndex, *(ebDWORD *)pParam);
	case TYP_ERROR:  	break;
	case TYP_VARIANT:	return rThread.SetParamVariant (iIndex, *(ebVARIANT *)pParam);
	case TYP_APPOBJECT:	return rThread.SetParamObject (iIndex, *(ebDWORD *)pParam);
	case TYP_DIALOG: 	break;
	case TYP_USERDEF:	break;
	}
	
return false;
}


bool GetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam, bool fModsPar)
{
	switch (rParam.wType & TYP_TYPEMASK) {
	case TYP_EMPTY:
	case TYP_NULL:		break;
	case TYP_BOOLEAN:	return rThread.GetParamBool (iIndex, (ebBOOL *)pParam);
	case TYP_INTEGER:	return rThread.GetParamInt (iIndex, (WORD *)pParam);
	case TYP_LONG:		return rThread.GetParamLong (iIndex, (long *)pParam);
	case TYP_SINGLE:	return rThread.GetParamSingle (iIndex, (float *)pParam);
	case TYP_DOUBLE:   	return rThread.GetParamDouble (iIndex, (double *)pParam);
	case TYP_CURRENCY: 	return rThread.GetParamCurrency (iIndex, (ebCURRENCY *)pParam);
	case TYP_DATE:     	return rThread.GetParamDate (iIndex, (double *)pParam);
	case TYP_STRING:
		{
		ebHSUB hStr = NULL;
			
			if ((rParam.wType & TYP_MODSPARM) || fModsPar) {
				if (rThread.GetParamString (iIndex, &hStr)) {
				LPSTR pStr = ::ebLockString (rThread.GetHandle(), hStr);

					if (*(LPSTR *)pParam) CoTaskMemFree (*(LPSTR *)pParam);
						*(LPSTR *)pParam = (LPSTR)CoTaskMemAlloc (strlen(pStr)+1);
					if (NULL != *(LPSTR *)pParam)	// Ergebnis kopieren
						strcpy (*(LPSTR *)pParam, pStr);

					::ebUnlockString (rThread.GetHandle(), hStr);
//					::ebFreeString (rThread.GetHandle(), hStr);
					return true;
				}
			} else {
				if (rThread.GetParamString (iIndex, &hStr)) {
//					::ebFreeString (rThread.GetHandle(), hStr);
					return true;
				}
			}
		}
		break;
	case TYP_OLEOBJECT:	return rThread.GetParamOleObject (iIndex, (ebDWORD *)pParam);
	case TYP_ERROR:  	break;
	case TYP_VARIANT:	return rThread.GetParamVariant (iIndex, (ebVARIANT *)pParam);
	case TYP_APPOBJECT:	return rThread.GetParamObject (iIndex, (ebDWORD *)pParam);
	case TYP_DIALOG: 	break;
	case TYP_USERDEF:	break;
	}
	
return false;
}

HRESULT RunThread(CebThread & Thread, ebHSCRIPT hScript)
{
LONG lThreadState = TS_IDLE;
bool fWarning = true;
	
	do {
		Thread.Start();
		lThreadState = Thread.GetState();
		if (lThreadState == TS_SUSPENDED) {
		// Breakpoint in CallBackfunktion ausgelöst
			if (fWarning) {
				AfxMessageBox (IDS_ILLBREAKPOINT); 	// Warnung an Nutzer
				fWarning = false;			// aber nur einmal
			}
			
		// Breakpoint löschen
		ebDBGINFO DI;
		
			Thread.GetDebugInfo (&DI);
			::ebClearBreakPoint ((ebHOBJECT)hScript, DI.wCurrent);
		}
	} while (lThreadState != TS_IDLE);

return NOERROR;
}

HRESULT SetEntryInfo (CebEntryInfo & EI, LPCTSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	ASSERT(pEntry);

	EI.SetEntryName (pEntry);			
	EI.SetParamsCount (iNumParams);
	if (pPars) {	
		if (iNumParams > 0) 
			EI.SetParams (&pPars -> pTypes[1]);			
		if (pPars -> pTypes[0].wType != 0) {
			EI.SetMethodType (true);	// Funktion
			EI.SetRetType (&pPars -> pTypes[0]);
		}
	}
return NOERROR;
}

//
// *** wenn der Debugger läuft !!! ***
//
HRESULT CBScriptDebug::RunThread(LPCTSTR pEntry, int iNumParams, BSPARAM *pPars)
{
int iState = GetState();
HRESULT hr = NOERROR; 
	
	switch (iState) {
	case ES_EXECUTING:	// Debugger ist busy, do it your self
		{
		ebHCODE hCode = GetCode (false);					
			if(NULL == hCode) return ResultFromScode (E_FAIL);

		ebHSCRIPT hScript = ebDebugger_GetScript(GetWindow(), false);		
			if (hScript == NULL) return ResultFromScode (E_FAIL);

		CebEntryInfo EI;
			hr = SetEntryInfo(EI, pEntry, iNumParams, pPars);		
			if (FAILED(hr)) return hr;
		
		// EntryPoint überprüfen
			if (ebCheckEntry ((ebHOBJECT)hCode, EI.GetEntryInfo()))
				return ResultFromScode (S_FALSE);

		// Ist EndScript() Function, raus			
		// darf NUR bei Unload() gerufen werden !!!
			hr = ::GetMethodType(hCode, pEntry);
			if (FAILED(hr)) return S_FALSE;

			EI.SetEntryName (TEXT(""));		// optimierten Entry verwenden
			
		// Thread erzeugen
		CebThread Thread (hScript, EI.GetEntryInfo());
		
			if (Thread.Create(2*sizeof(long))) return ResultFromScode (E_FAIL);
	
			Thread.SetRuntimeErrorProc(&OnRuntimeError, 0);

		// Parameter setzen
			for (int i = 1; i <= iNumParams; i++) 
				SetParam (Thread, i, pPars -> pTypes[i], pPars -> pValues[i]);		
		// eigenliches RUN
		// Routine rufen, bis die CallbackFunktion erfolgreich abgeschlossen wurde
		//
			hr = ::RunThread(Thread, hScript);
			if (FAILED(hr)) return hr;

		LONG iError = Thread.GetErrorNumber();
		LONG iLine = Thread.GetErrorLine();
		
		// evtl. Rückgabewert abfragen
			if (pPars -> pTypes[0].wType != 0) 
				GetParam (Thread, 0, pPars -> pTypes[0], pPars -> pValues[0], true);
		
		// evtl. Parameter zurückschreiben
			for (int iOut = 0; iOut <= iNumParams; iOut++) {
				if (iOut > 0 && pPars -> pTypes[iOut].wType & TYP_MODSPARM)
					GetParam (Thread, iOut, pPars -> pTypes[iOut], pPars -> pValues[iOut], true);

			// Parameter ausnullen, damit eventuelle AppObjektpointer nicht released werden: 
				if (TYP_APPOBJECT == pPars -> pTypes[iOut].wType) {
				DWORD dw = 0L;

					SetParam (Thread, iOut, pPars -> pTypes[iOut], &dw);
				}
			}
		}
		break;

	case ES_IDLE:		// das ganze dem Debugger überlassen
		{		
		CebEntryInfo EI;
		char cbEntry[ENTRYNAMESZ];
			
			EI.GetEntryName (cbEntry);		
			hr = SetEntryInfo(EI, pEntry, iNumParams, pPars);		
			if (FAILED(hr)) return hr;
		
		ebLPENTRYINFO pEI = EI.GetEntryInfo();
			
			if (pEI == NULL) return ResultFromScode(E_FAIL);

				// für EntryPoint überprüfen
		ebHCODE hCode = GetCode (false);					
			if (hCode == NULL || ebCheckEntry ((ebHOBJECT)hCode, pEI)) return ResultFromScode(S_FALSE);
		
		// Ist EndScript() Function, raus
			hr = ::GetMethodType(hCode, pEntry);
			if (FAILED(hr)) return S_FALSE;

			SetEntryPoint (pEI);
		//
		// eigentliches Starten des Threads im Debugger
		//		
			BreakSet(pEntry);

// noch Breakpoint bearbeiten		
			if (SetParams (iNumParams, pPars)) StartScript();		
					
		// alten Startpunkt wieder einstellen (Sub Main())
			EI.SetEntryName (cbEntry);
			SetEntryPoint (pEI);
			ResetParams();			
		}
		break;

	case ES_SUSPENDED:
		break;
	}

return NOERROR;
}

//
// *** wenn der Debugger nicht läuft und Scripts gespeichert sind !!! ***
//
HRESULT RunKeptThread(	LPCTSTR pEntry, 
					int iNumParams, 
					BSPARAM *pPars)
{
ebHSCRIPT hScript = NULL;
HRESULT hr = GetRunningScripts() -> FindNext(&hScript, pEntry, true);
bool fAuto = false;
	
	while (GetScode(hr) == S_OK) {
		if (NULL != hScript) {
	// EntryPoint setzen
		CebEntryInfo EI;

			hr = SetEntryInfo(EI, pEntry, iNumParams, pPars);		
			if (FAILED(hr)) return hr;

		// Thread erzeugen
		CebThread Thread (hScript, EI.GetEntryInfo());		

			if (Thread.Create(2*sizeof(long))) return ResultFromScode(E_FAIL);
		
		// EntryPoint überprüfen
			if (ebCheckEntry ((ebHOBJECT)Thread.GetHandle(), EI.GetEntryInfo()))
				return ResultFromScode (S_FALSE);

			// Parameter setzen
			for (int i = 1; i <= iNumParams; i++) 
				SetParam (Thread, i, pPars -> pTypes[i], pPars -> pValues[i]);

		// wurde Script AutoStart geladen ?
			if (hScript == GetRunningScripts() -> GetAutoStart()) {
				fAuto = true;
				Thread.SetLong(4, 1);
			} else {
				fAuto = false;
				Thread.SetLong(4, 0);
			}

		// nicht Break voreinstellen
			Thread.SetLong(0, 0);

			// eventuell Runtime Errorbehandlung
			Thread.SetRuntimeErrorProc(&OnRuntimeError, 0);

		// eigentliches RUN
		// Routine rufen, bis die CallbackFunktion erfolgreich abgeschlossen wurde
			hr = RunThread(Thread, hScript);			
			if (FAILED(hr)) return hr;
		
			// evtl. Rückgabewert abfragen
			if (pPars -> pTypes[0].wType != 0) 
				GetParam (Thread, 0, pPars -> pTypes[0], pPars -> pValues[0], true);			
			
			// evtl. Parameter zurückschreiben
			for (int iOut = 0; iOut <= iNumParams; iOut++) {
				if (iOut > 0 && pPars -> pTypes[iOut].wType & TYP_MODSPARM)
					GetParam (Thread, iOut, pPars -> pTypes[iOut], pPars -> pValues[iOut], true);
			
			// Parameter ausnullen, damit eventuelle AppObjektpointer nicht released werden: 
				if (TYP_APPOBJECT == pPars -> pTypes[iOut].wType) {
				DWORD dw = 0L;

					SetParam (Thread, iOut, pPars -> pTypes[iOut], &dw);
				}
			}
			
		// boolsche Variable im Extrabuffer zum Zerstören des Scripts
			if (Thread.GetLong(0)) {

			bool fError = true, fBreak = true;

				hr = SetEntryInfoUnLoadScript(EI);		
				if (FAILED(hr)) return hr;
				// RunUnLoadScript

				hr = RunScript(EI, hScript, NULL, fError, fBreak, fAuto);
				if(FAILED(hr)) return hr;

				::ebDestroyThread(Thread.Detach());

				hr = GetRunningScripts() -> Delete (hScript); 
				if(FAILED(hr)) return hr;
			}

		}// if hScript

		hScript = NULL;
// nächsten Script finden		
		hr = GetRunningScripts() -> FindNext(&hScript, pEntry, false);
	} // while HRESULT == S_OK bis Ende der Map

return NOERROR;
}

HRESULT CMacroScriptExtension::StopAllRun ()
{
ebHSCRIPT hScript = NULL;
CebEntryInfo EI;
HRESULT hr = NOERROR;
char Entry[MAXSTRLENGTH];

	while (S_OK == GetRunningScripts() -> FindNext(Entry, MAXSTRLENGTH, &hScript)) {

		if (FAILED(hr)) return hr;

bool fRunTimeError = false, fBreak = true, fAuto = false;

		hr = SetEntryInfoUnLoadScript(EI);		
		if (FAILED(hr)) return hr;

		if (GetRunningScripts() -> GetAutoStart() == hScript)
			fAuto = true;		

		// UnLoadScript
		hr = RunScript(EI, hScript, NULL, fRunTimeError, fBreak, fAuto);
		if (FAILED(hr)) return hr;

		hr = GetRunningScripts() -> EndThreadRunning(hScript);
		if (FAILED(hr)) return hr;

		hr = GetRunningScripts() -> Delete(hScript);
		if (FAILED(hr)) return hr;		
	}

return hr;
}

HRESULT CMacroScriptExtension::AutoLoadScript ()
{
	ASSERT(m_pebInst);

char *pcMacroName = NULL;
CString str;

	try {
	WScriptContainer ISC(m_pMacroScripts);	// throws hr

		pcMacroName = str.GetBuffer(MAXSTRLENGTH);

	// Name aus Projekt-INI lesen...
	HRESULT hr = ReadIniAutoLoadScript (pcMacroName, MAXSTRLENGTH);

		if (FAILED(hr)) throw hr;

		str.ReleaseBuffer();
		if (str.IsEmpty()) throw E_FAIL;

		if (S_FALSE == hr)
			hr = ::RunThread(ISC, m_pebInst, str, true);
		else
			hr = RunThread_File(ISC, m_pebInst, str, true);

	} catch (HRESULT hr) {
		return hr;
	} catch (...) {
		return E_OUTOFMEMORY;
	}

return S_OK;
}

HRESULT ReadIniAutoLoadScript (char *pcMacroName, int iLen)
{
	
char ProjectName[_MAX_PATH];
char FileName	[_MAX_PATH];

HRESULT hr = E_FAIL;

	if (DEX_GetActiveProject(ProjectName)) {

		hr = MakeFileName (ProjectName, FileName, g_cbFileExt_Ini);
		if (FAILED(hr))	return hr;

		if (GetPrivateProfileString (g_cbBasicScript, g_cbAutoStartPath, g_cbNil, pcMacroName, iLen, FileName)) 
		{
			return S_OK;
		}
		else if (GetPrivateProfileString (g_cbBasicScript, g_cbAutoStart , g_cbNil, pcMacroName, iLen, FileName))  
	// kein Eintrag vorhanden
			return S_FALSE;
		}

return E_FAIL;
}

bool RegAutoStartScriptFile()
{
HMODULE hModule = GetModuleHandle(TRIAS_MODULENAME);
	if (NULL == hModule) return false;

char Path[_MAX_PATH];
char FilePath[_MAX_PATH];

	if (NULL == GetModuleFileName(hModule, FilePath, _MAX_PATH))
		return false;

HRESULT	hr = MakePathName(FilePath, Path);
	if (FAILED(hr)) return false;

	Path[strlen(Path)-1] = '\0'; 

int ch = '\\';
LPSTR pdest = strrchr(Path, ch);

	*(pdest + 1) = '\0';

	strcat(Path, g_cbMacroDir); 

CCurrentUser CU(g_cbDirKey, true);
	
	if (!CU.SetSubSZ (g_cbMacroDir, Path))	// save in reg file...
		return false;

return true;
}

bool UnRegAutoStartScriptFile()
{
CCurrentUser CU(g_cbTRiASKey);
	
	if (!CU.DeleteKey (g_cbDirKeyOnly))	// save in reg file...
		return false;

return true;
}

HRESULT GetMethodType(ebHOBJECT hObject, LPCSTR pEntry)
{
	ASSERT(NULL != hObject);

ebPROCINFO PI;
ebBOOL fNext = true;

ebHENUM hEnum = ebGetFirstProc(hObject, &PI);
	
	if (hEnum == NULL) return E_FAIL;

CString strUnLoad;
		
	if (!LoadString(strUnLoad, IDS_UNLOADSCRIPT))
		return E_FAIL;

	// wenn pEntry == NULL, dann schon Unload in irgendeiner Form gerufen
	// es ist also klar, daß Unload ausgeführt werden soll
	if (NULL != pEntry && 0 != strcmp (strUnLoad, pEntry)) 
		return NOERROR;

	while (fNext) {
		if (0 == strcmp (strUnLoad, PI.szName)) {
			if (1 == PI.wType) {
				ebEnumClose(hEnum);
				return E_FAIL;
			}
		}
		fNext = ebGetNextProc(hEnum, &PI);
	}		
	
	ebEnumClose(hEnum);

return NOERROR;
}

HRESULT CMacroScriptExtension :: FireEvent (
		LPCTSTR pEntry, int iNumParams, BSPARAM *pPars)
{
CString strBuf;
char * pBuf = strBuf.GetBuffer(_MAX_PATH);
HWND hWnd = NULL;

	if (DEX_GetActiveProject(pBuf)) {
		strBuf.ReleaseBuffer();
		ebInst().SetHomeDir(GetPathName(strBuf));
		hWnd = ebInst().GetWindow();
	}
	
HRESULT hr = NOERROR;
// wenn DebuggerFenster offen ist, Script muß im Debugger ausgeführt werden

	if (m_pDebugWnd == NULL) {
		hr = RunKeptThread(pEntry, iNumParams, pPars);
		if (FAILED(hr)) return hr;
	} else { 
		hr = m_pDebugWnd -> RunThread(pEntry, iNumParams, pPars);
		if (FAILED(hr)) return hr;
	}
				
return hr;
}

HRESULT CMacroScriptExtension :: RunText (LPCSTR lpText, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars)
{
	ASSERT(lpText);
	ASSERT(lpEntry);
	ASSERT(pPars);

	ebCOMPILESTRUCT CompileStruct;

	HRESULT hr = Compile(CompileStruct, lpText);
	if (FAILED(hr)) return hr;

	hr = RunThread(lpEntry, CompileStruct.hCode, iNumParams, pPars);
	if (CompileStruct.hCode) ebCode_Free(CompileStruct.hCode);

return hr;
}

HRESULT CMacroScriptExtension :: RunCode (HINSTANCE hInst, UINT uiResID, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars)
{

	ebHCODE hCode = NULL;

	HRESULT hr = LodeCodeFromResource(hInst, &hCode, uiResID);
	if (FAILED(hr)) return hr;

	hr = RunThread(lpEntry, hCode, iNumParams, pPars);
	if (hCode) CoTaskMemFree (hCode);

return hr; 
}

// QueryInterface ist jetzt notwendig, da ein weiteres Interface unterstützt wird
STDMETHODIMP CMacroScriptExtension :: QueryInterface (REFIID riid, LPVOID *ppv) 
{
// hier nur nach zusätzlichen Inetrfaces fragen
	if (riid == IID_IExtendBScript) {
	// sollte das Interface noch nicht existieren, dann Fehler melden
	// es ist entweder zu spät, oder ein fehler ist aufgetreten
		if (m_pBScriptExt == NULL) 
			return ResultFromScode (E_NOINTERFACE);
		
		*ppv = m_pBScriptExt;
		LPUNKNOWN (*ppv) -> AddRef();
		return NOERROR;
	}

// den Rest macht die BasisKlasse
return CTriasExtension :: QueryInterface (riid, ppv);
}

// MessageSchleife ------------------------------------------------------------
void CallMessageQueue (void)
{
// Yielding
	DEX_KickIdle();			// IdleProcessing
}


#if !defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// Stuff for MFC-DLL ----------------------------------------------------------
CExtDLL NEAR MyExtensionDLL (NULL); // ==>> Titel in AFX_IDS_APP_TITLE !!						

#endif // WIN32 

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// *** Allgemeine globale Funktionen ***
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

HRESULT CMacroScriptExtension :: Compile(ebCOMPILESTRUCT & CompileStruct, LPCSTR lpText)
{
	ASSERT(lpText);

	CebCompiler Compiler;

	memset(&CompileStruct, 0, sizeof(ebLPCOMPILESTRUCT)); 
	
	CompileStruct.wVersion = CS_VERSION;						/* version of this structure (CS_VERSION) */
	CompileStruct.lpText = lpText;	 							/* Script to be compiled */
	CompileStruct.hInstance = m_pebInst -> GetHandle();			/* instance of the application (returned fro ebInit) */

	HRESULT hr = NOERROR;

	if (Compiler.Compile(&CompileStruct))
		return E_FAIL;

return NOERROR;
}

HRESULT CMacroScriptExtension :: LodeCodeFromResource(HINSTANCE hInst, ebHCODE *phCode, UINT uiID)
{
	ASSERT(hInst);
	ASSERT(phCode);

	USES_CONVERSION;

	HRESULT     hr = NOERROR;
	HRSRC       hRes = NULL;
	HGLOBAL     hMem = NULL;
	ebFILEHEADER *pHeader = NULL;
	LPVOID lpCode = NULL;
	BYTE *pdwMem = NULL;

	try
	{	// Finden der Resource dieser Instanz
		hRes = FindResource((HMODULE)hInst, MAKEINTRESOURCE(uiID), "SCRIPT");
		if (NULL == hRes) throw E_HANDLE;

		// Resource in Memory laden
		hMem = LoadResource((HMODULE)hInst, hRes);
		if (NULL == hMem) throw E_HANDLE;

		// lock it, get pointer to first DWORD
		pdwMem = (BYTE *)LockResource(hMem);
		if (NULL == pdwMem) throw E_POINTER;

		// Header lesen
		pHeader = (ebFILEHEADER *)pdwMem;

		if (pHeader->id!=FH_ID || pHeader->wVersion!=FH_VERSION || 0 == pHeader->dwCodeSz || 0 == pHeader->dwCode) 	
			throw E_FAIL;

		// Codepointer erzeugen
		lpCode = CoTaskMemAlloc (pHeader->dwCodeSz);
		if (NULL == lpCode) throw E_OUTOFMEMORY;

		// aus Memory holen
		memcpy(lpCode, &pdwMem[pHeader->dwCode], pHeader->dwCodeSz);

		// Codehandle bilden	
		*phCode = NULL;
		*phCode = ebCode_Create(lpCode);
		if (NULL == *phCode) throw E_HANDLE;
		if (ebCode_GetSize(*phCode) != pHeader->dwCodeSz) return E_FAIL;
	}
	catch(HRESULT hr)
	{
		if (hMem) {
			UnlockResource(hMem);
			FreeResource(hMem);
		}
		hMem = NULL;
		if (lpCode)	CoTaskMemFree (lpCode);
		lpCode = NULL;
		*phCode = NULL;

		return hr;
	}

	UnlockResource(hMem);
	FreeResource(hMem);

return hr;
}

HRESULT CMacroScriptExtension :: RunThread(LPCSTR pEntry, ebHCODE hCode, int iNumParams, BSPARAM *pPars)
{
	ASSERT(pEntry);
	ASSERT(hCode);
	ASSERT(pPars);

	// EntryPoint setzen
	CebEntryInfo EI;

	HRESULT hr = SetEntryInfo(EI, pEntry, iNumParams, pPars);		
	if (FAILED(hr)) return hr;
	// EntryPoint überprüfen
	if (ebCheckEntry ((ebHOBJECT)hCode, EI.GetEntryInfo())) 
		return E_ABORT;

	// Script erzeugen
	CebScript Script(m_pebInst, hCode, NULL, 0);
	if (Script.Create()) return E_FAIL;
		
	// Thread erzeugen
	CebThread Thread (Script.GetHandle(), EI.GetEntryInfo());		
	if (Thread.Create(2*sizeof(long))) return E_FAIL;

	// Parameter setzen
	for (int i = 1; i <= iNumParams; i++) 
		SetParam (Thread, i, pPars -> pTypes[i], pPars -> pValues[i]);

	// nicht Break voreinstellen
	Thread.SetLong(0, 0);

	// eventuell Runtime Errorbehandlung
	Thread.SetRuntimeErrorProc(&OnRuntimeError, 0);

// eigentliches RUN
// Routine rufen, bis die CallbackFunktion erfolgreich abgeschlossen wurde
	hr = ::RunThread(Thread, Script.GetHandle());			
	if (FAILED(hr)) return hr;

	// evtl. Rückgabewert abfragen
	if (pPars -> pTypes[0].wType != 0) 
		GetParam (Thread, 0, pPars -> pTypes[0], pPars -> pValues[0], true);			
	
	// evtl. Parameter zurückschreiben
	for (int iOut = 0; iOut <= iNumParams; iOut++) 
	{
		if (iOut > 0 && pPars -> pTypes[iOut].wType & TYP_MODSPARM) 
			GetParam (Thread, iOut, pPars -> pTypes[iOut], pPars -> pValues[iOut], true);

	// Parameter ausnullen, damit eventuelle AppObjektpointer nicht released werden: 
		if (TYP_APPOBJECT == pPars -> pTypes[iOut].wType) {
		DWORD dw = 0L;

			SetParam (Thread, iOut, pPars -> pTypes[iOut], &dw);
		}
	}

return NOERROR;
}

bool RegPropActPage(REFCLSID rclsid, LPCSTR pcProgID) // z. b. TRiASEx.FilterScript.1
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

	if (!Root.SetSubSZ (NULL, szClassID))	// save in reg file...
		return false;

return true;
}

bool UnRegPropActPage(LPCSTR pcProgID) // z. b. TRiASEx.FilterScript.1
{
char cBuffer[80];
// window information
	wsprintf(cBuffer, g_cbPropActKey, pcProgID);

CClassesRoot Root(g_cbPropActKey, true);

	if (!Root.DeleteKey (pcProgID))	// save in reg file...
		return false;

return true;
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

return NOERROR;	
}

CRunScriptsOrg * GetRunningScripts (void)
{
	return ((CMacroScriptExtension *)g_pTE) -> GetRunningScripts();
}

HRESULT LoadStorageMacroScripts(IUnknown *pIUnk)
{
	ASSERT(pIUnk);

char cBuffer[_MAX_PATH];	
// Makros nur initialisieren, wenn Projekt offen	
	if (NULL == DEX_GetActiveProject (cBuffer)) return ResultFromScode(S_FALSE);

IScriptContainer *pISC = NULL; 			
HRESULT	hr = pIUnk -> QueryInterface (IID_IScriptContainer, 
													(LPVOID *) &pISC);
	if (FAILED(hr)) return hr; 

// Initialisiert alle Storages und öffnet Streams, fügt diese in Liste ein
LPSTORAGE pIRootStorage = NULL; 
	DEX_GetProjectStorage (pIRootStorage);	// macht Storage->Addref()		
	hr = pISC -> InitStorages (pIRootStorage, cBuffer);

	if (pIRootStorage) 
		pIRootStorage -> Release();		// !!

	pISC -> Release();
	
return hr; 		
}

HRESULT LoadStorageMenuItems(IUnknown *pIUnk)
{
	ASSERT(NULL != pIUnk);

// Makros nur initialisieren, wenn Projekt offen	
	if (!DEX_TestActiveProject()) 
		return S_FALSE;

LPSTORAGE pIStorage = NULL;

	if (NULL == DEX_GetProjectStorage(pIStorage)) 
		return E_UNEXPECTED;

	try {
	WSave IS(pIUnk);
	HRESULT hr = NOERROR;

	CString strStorName;

		if (!LoadString(strStorName, IDS_STORAGE_NAME_MENUITEMS)) {
			pIStorage -> Release();	
			return ResultFromScode(E_FAIL);
		}

	bool fNew = false;
	LPSTORAGE pISubStorage = NULL;

		hr = MakeSubStorage(pIStorage, &pISubStorage, strStorName, fNew, true, CLSID_MenuItems);
		pIStorage -> Release();
		if (FAILED(hr)) return hr; 

	// Load() return S_FALSE, wenn kein Storage zu öffnen ist
	//	 SubStorage->AddRef()
		hr = IS -> Load(pISubStorage);

	// liefert immer S_FALSE 
		if (FAILED(hr) && GetScode(hr) == STG_E_FILENOTFOUND) 
			hr = IS -> InitNew(pISubStorage);
		pISubStorage -> Release();
		return hr;

	} catch (HRESULT hr){
		return hr;
	}
}

HRESULT LoadCode (int fh, ebFILEHEADER &rHead, ebHCODE *phCode, LPSTR *ppText)
{
	*phCode = NULL;
	*ppText = NULL;

LPVOID lpCode = CoTaskMemAlloc(rHead.dwCodeSz);
	if(lpCode == NULL) return E_OUTOFMEMORY;

LPSTR pText = (LPSTR)CoTaskMemAlloc(rHead.dwScriptSz);
	if (pText == NULL) return E_OUTOFMEMORY; 
		
	_llseek (fh, rHead.dwScript, SEEK_SET);
	if (_lread (fh, pText, (UINT)rHead.dwScriptSz) != (UINT)rHead.dwScriptSz) {
		return E_FAIL;
	}

	_llseek (fh, rHead.dwCode, SEEK_SET);
	if (_hread (fh, lpCode, rHead.dwCodeSz) != (LONG)rHead.dwCodeSz) {
		return E_FAIL;
	}
	
	*phCode = ebCode_Create(lpCode);
	*ppText = pText;

return NOERROR;
}                                                                               

HRESULT OpenFile (bool fAutoStart, const CString & strFileName, LPSTR *ppText, ebHCODE *phCode)
{
CString str;
LPSTR pcDirName = NULL;
int fh = 0;

// entweder aus der registry Pfadnamen für Autostart holen
// oder ganzen Filenamen mit Pfad übergeben
	if (fAutoStart) {
		try {
			pcDirName = str.GetBuffer(_MAX_PATH);
		} catch (...) {
			return E_OUTOFMEMORY;
		}
		if (!ReadRegSettingsMacrosDirectory(pcDirName, _MAX_PATH)) 
			return E_FAIL;
		strcat(pcDirName, strFileName);
		str.ReleaseBuffer();
		fh = _lopen (str, OF_READ);
		if (HFILE_ERROR == fh) return E_HANDLE;
	} else {
		fh = _lopen (strFileName, OF_READ);
		if (HFILE_ERROR == fh) return E_HANDLE;
	}

ebFILEHEADER Head; 
int iBytes = _lread (fh, (LPSTR)&Head, sizeof(Head));

	if (iBytes == sizeof(Head) && 
		Head.id == FH_ID && Head.wVersion == FH_VERSION) {
	HRESULT hr = LoadCode (fh, Head, phCode, ppText);
		_lclose (fh);
		fh = NULL;
		if (FAILED(hr)) return hr;
	} else {
		_lclose (fh);
		fh = NULL;
		return E_FAIL;
	}
		
return NOERROR;
}

//
// *** MAIN ausführen !!! ***
//
HRESULT RunThread(	IScriptContainer *pIScriptContainer, 
					CebInstance *pebInstance, 
					const CString& strMacroName,
					bool fAutoStart)
{
	if (!g_SummitModuls[RUNTIME].fIsInstalled) return ResultFromScode(E_FAIL);

	ASSERT(pIScriptContainer);
	ASSERT(pebInstance);
	ASSERT(!strMacroName.IsEmpty());

	
char *pcMakroText = NULL;                                                      
ebHCODE hCode = NULL;                  
HRESULT	hr = NOERROR;
CRunErr *pRunErr = NULL;
bool fRunTimeError = false;
ebHSCRIPT hScript = NULL;
	
	try {
		
	// zur Sicherheit
	DWORD dwInfo;

		hr = pIScriptContainer -> GetScriptInfo(strMacroName, &dwInfo);
		if(FAILED(hr)) throw hr;
		if(!(dwInfo & CC_CODE)) throw E_FAIL;

	CString strBuf;
	char * pBuf = NULL;
		
		pBuf = strBuf.GetBuffer(_MAX_PATH);
		if (NULL == pBuf) throw E_OUTOFMEMORY;

		if (!DEX_GetActiveProject(pBuf)) throw E_FAIL;

		strBuf.ReleaseBuffer();
		
		pebInstance -> SetHomeDir(GetPathName(strBuf));

		hr = pIScriptContainer -> GetScript (strMacroName, &pcMakroText, &hCode);
		if (FAILED(hr)) throw hr;

		ASSERT(NULL!=hCode);
		ASSERT(NULL!=pcMakroText);

		if (NULL == hCode) throw E_HANDLE;
		if (NULL == pcMakroText) throw E_POINTER;
		
	CebScript Sc(pebInstance, hCode, NULL, 0);

		if (Sc.Create()) throw E_FAIL;
	
		ASSERT(Sc.GetHandle());

// kann nach ScriptCreate wieder freigegeben werden
		CoTaskMemFree(hCode); hCode = NULL; 
			
	// Thread erzeugen
	LPUNKNOWN pIUnk = NULL;
		
		hr = pIScriptContainer -> QueryInterface(IID_IUnknown, (LPVOID *) &pIUnk);	
		if (FAILED(hr)) throw hr;

	// eventuell Runtime Errorbehandlung
		pRunErr = new CRunErr (pIUnk, pcMakroText, strMacroName);
		pIUnk -> Release();
		if (pcMakroText) CoTaskMemFree (pcMakroText); pcMakroText = NULL;
		ASSERT(NULL != pRunErr);
		if (pRunErr == NULL) throw E_OUTOFMEMORY;
		
		hr = GetRunningScripts() -> Add (Sc.GetHandle(), strMacroName);
						// nur einmal gleichen Script mit gleichem Namen ausführen !!!
		if (FAILED(hr) || GetScode(hr) == S_FALSE) {
			hScript = Sc.Detach();
			throw hr; 
		}

		// Script wurde AutoStart geladen
		if (true == fAutoStart) 
			GetRunningScripts() -> SetAutoStart(Sc.GetHandle());

	//
	// Thread ausführen
	//
	CebEntryInfo EI;
	bool fBreakMain = true, fBreakLoad = true, fBreak = true;

		hr = SetEntryInfoLoadScript(EI);		
		if (FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}

		// LoadScript
		hr = RunScript(EI, Sc.GetHandle(), pRunErr, fRunTimeError, fBreakLoad, fAutoStart);
		if (FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}
		hr = ResetEntryInfo(EI);		
		if (FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}
		// Main
		hr = RunScript(EI, Sc.GetHandle(), pRunErr, fRunTimeError, fBreakMain, fAutoStart);
		if(FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}
		
	// boolsche Variable im Extrabuffer zum Zerstören des Scripts
		if (false == fBreakMain || false == fBreakLoad) {
		// Script nicht zerstören
			Sc.Detach();
		} else {
			hr = SetEntryInfoUnLoadScript(EI);		
			if (FAILED(hr)) {
				hScript = Sc.Detach();
				throw hr; 
			}
			// UnLoadScript
			hr = RunScript(EI, Sc.GetHandle(), pRunErr, fRunTimeError, fBreak, fAutoStart);
			if (FAILED(hr)) {
				hScript = Sc.Detach();
				throw hr; 
			}
			hr = GetRunningScripts() -> Delete (Sc.GetHandle());
			if(FAILED(hr)) {
				hScript = Sc.Detach();
				throw hr; 
			}
		}
	
// sollte Fehler auftreten, wird "pRunErr" erst mit schliessen des gerufenen Debuggers gelöscht
		DELETE (pRunErr);

	} catch (HRESULT hResult) {
		if (pcMakroText) CoTaskMemFree (pcMakroText); 
		if (hCode) CoTaskMemFree(hCode); 
		if (false == fRunTimeError) 
			DELETE (pRunErr);
		if (hScript) {
			GetRunningScripts() -> Delete (hScript);
		}
		return hResult; 
	}

return NOERROR;
}

HRESULT RunThread_File(	IScriptContainer *pIScriptContainer,
						CebInstance *pebInstance, 
						const CString& strFileName,
						bool fAutoStart)
{
	if (!g_SummitModuls[RUNTIME].fIsInstalled) return E_FAIL;

	ASSERT(!strFileName.IsEmpty());
	ASSERT(pebInstance);

char *pcMakroText = NULL;                                                      
ebHCODE hCode = NULL;                  
HRESULT	hr = NOERROR;
CRunErr *pRunErr = NULL;
bool fRunTimeError = false;
ebHSCRIPT hScript = NULL;

	try {
	
		hr = OpenFile (true /* AutoStart*/, strFileName, &pcMakroText, &hCode);
		if (FAILED(hr)) throw hr;
		if (NULL == pcMakroText) throw E_POINTER;
		if (NULL == hCode) throw E_HANDLE;

	CebScript Sc(pebInstance, hCode, NULL, 0);

		if (Sc.Create())  
			throw E_FAIL;
	
		ASSERT(Sc.GetHandle());

// kann nach ScriptCreate wieder freigegeben werden
		CoTaskMemFree(hCode); hCode = NULL; 
			
	// Thread erzeugen
	LPUNKNOWN pIUnk = NULL;
		
		hr = pIScriptContainer -> QueryInterface(IID_IUnknown, (LPVOID *) &pIUnk);	
		if (FAILED(hr)) throw hr;

	// eventuell Runtime Errorbehandlung
		pRunErr = new CRunErr (pIUnk, pcMakroText, strFileName);
		pIUnk -> Release();
		if (pcMakroText) CoTaskMemFree (pcMakroText); pcMakroText = NULL;
		ASSERT(NULL != pRunErr);
		if (pRunErr == NULL) 
			throw E_OUTOFMEMORY;
		
		hr = GetRunningScripts() -> Add (Sc.GetHandle(), strFileName);
						// nur einmal gleichen Script mit gleichem Namen ausführen !!!
		if (FAILED(hr) || GetScode(hr) == S_FALSE) {
			hScript = Sc.Detach();
			throw hr; 
		}

		// Script wurde AutoStart geladen
		if (true == fAutoStart) 
			GetRunningScripts() -> SetAutoStart(Sc.GetHandle());

	//
	// Thread ausführen
	//
	CebEntryInfo EI;
	bool fBreakMain = true, fBreakLoad = true, fBreak = true;

		hr = SetEntryInfoLoadScript(EI);		
		if (FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}
		// LoadScript
		hr = RunScript(EI, Sc.GetHandle(), pRunErr, fRunTimeError, fBreakLoad, fAutoStart);
		if (FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}
		hr = ResetEntryInfo(EI);		
		if (FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}
		// Main
		hr = RunScript(EI, Sc.GetHandle(), pRunErr, fRunTimeError, fBreakMain, fAutoStart);
		if(FAILED(hr)) {
			hScript = Sc.Detach();
			throw hr; 
		}
		
	// boolsche Variable im Extrabuffer zum Zerstören des Scripts
		if (false == fBreakMain || false == fBreakLoad) {
		// Script nicht zerstören
			Sc.Detach();
		} else {
			hr = SetEntryInfoUnLoadScript(EI);		
			if (FAILED(hr)) {
				hScript = Sc.Detach();
				throw hr; 
			}
			// UnLoadScript
			hr = RunScript(EI, Sc.GetHandle(), pRunErr, fRunTimeError, fBreak, fAutoStart);
			if (FAILED(hr)) {
				hScript = Sc.Detach();
				throw hr; 
			}
			hr = GetRunningScripts() -> Delete (Sc.GetHandle());
			if(FAILED(hr)) {
				hScript = Sc.Detach();
				throw hr; 
			}
		}
	
// sollte Fehler auftreten, wird "pRunErr" erst mit schliessen des gerufenen Debuggers gelöscht
		DELETE (pRunErr);

	} catch (HRESULT hResult) {
		if (pcMakroText) CoTaskMemFree (pcMakroText); 
		if (hCode) CoTaskMemFree(hCode); 
		if (false == fRunTimeError) 
			DELETE (pRunErr);
		if (hScript) {
			GetRunningScripts() -> Delete (hScript);
		}
		return hResult; 
	}

return NOERROR;
}

bool ResetEntryInfo(CebEntryInfo & EI)
{
CString str;

	if (!LoadString(str, IDS_MAIN)) return false;

	EI.SetEntryName(str); // "Main()"
	EI.GetEntryInfo() -> dwEntry = 0;
	EI.GetEntryInfo() -> wParms = 0;
	EI.GetEntryInfo() -> lpParms = NULL;
	EI.GetEntryInfo() -> RetParm.wType = 0;
	EI.GetEntryInfo() -> isFunc = 0;	// Sub and not a Function
	
return true;
}

bool SetEntryInfoLoadScript(CebEntryInfo & EI)
{
CString str; 

	if (!ResetEntryInfo(EI)) return false;

	if (!LoadString(str, IDS_LOADSCRIPT)) return false;

	EI.SetEntryName(str); // "LoadScript"
	
return true;
}

bool SetEntryInfoUnLoadScript(CebEntryInfo & EI)
{
CString str;

	if (!ResetEntryInfo(EI)) return false;

	if (!LoadString(str, IDS_UNLOADSCRIPT)) return false;

	EI.SetEntryName(str);

return true;
}
			
HRESULT RunScript(CebEntryInfo & EI, ebHSCRIPT hScript, CRunErr *pRunErr, 
				  bool & fErr, bool & fBreak, bool fAutoStart)
{
	ASSERT(NULL != hScript);
	ASSERT(NULL != EI.GetEntryInfo());

		// *** EntryPoint überprüfen ***
	if (ebCheckEntry (hScript, EI.GetEntryInfo())) 
		return S_FALSE;

	// neuen Thread von fertigem Script (m_pScript) erzeugen
CebThread Thread (hScript, EI.GetEntryInfo());

	if (Thread.Create(2*sizeof(long))) return E_FAIL;

	ASSERT(Thread.GetHandle());

char Name[MAXSTRLENGTH];
	
	EI.GetEntryName(Name);

	// Ist EndScript() Function, raus
HRESULT	hr = GetMethodType(Thread.GetHandle(), Name);
	if (FAILED(hr)) return S_FALSE;

	Thread.SetRuntimeErrorProc(&OnRuntimeError, pRunErr ? (ebDWORD)pRunErr : 0);		
	Thread.SetLong(0, true);

	if (fAutoStart)
		Thread.SetLong(4, 1);

	// Routine rufen, bis die CallbackFunktion erfolgreich abgeschlossen wurde	
	hr = RunThread(Thread, hScript);
	if (FAILED(hr)) return hr;
	
	fErr = true;
	if (Thread.GetErrorNumber() == 0) {
		fErr = false;
	} else {
		return E_ABORT;
	}

	fBreak = false;
	// boolsche Variable im Extrabuffer zum Zerstören des Scripts
	if (Thread.GetLong(0)) {
		fBreak = true;
	}

return hr;
}

HRESULT WriteIniAutoLoadScript (LPCSTR pcMacroName)
{	
char ProjectName[_MAX_PATH];
char FileName	[_MAX_PATH];

HRESULT hr = E_FAIL;

	if (DEX_GetActiveProject(ProjectName)) {

		hr = MakeFileName (ProjectName, FileName, g_cbFileExt_Ini);
		if (FAILED(hr))	return hr;

		if (WritePrivateProfileString (g_cbBasicScript, g_cbAutoStart , pcMacroName, FileName)) 
			return NOERROR;
	}

return hr;
}

bool ReadRegSettingsMacrosDirectory(char *pc, DWORD dwL)
{
CCurrentUser regBS (g_cbDirKey);

	if (!regBS.GetSubSZ (g_cbMacroDir, pc, dwL))
		return false;
	
	strcat(pc, "\\");

return true;
}
