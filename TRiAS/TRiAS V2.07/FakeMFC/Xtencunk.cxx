// Routinen fuer Klasse CTriasExtension ---------------------------------------
// File: XTENCUNK.CXX

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include <xtensnn.h>

#include <registrx.hxx>

#include "impxtcf.hxx"
#include "cimpxtsn.hxx"

#include "summary.hxx"
#include "summcf.hxx"

#include "strings.h"

#include <xtsnguid.h>
#include <olectl.h>			// IID_IClassFactory2
#include <toolguid.h>		// IID_ITRiASToolBar etc.
#include <statguid.h>		// IID_IProgressIndicator
#include "fmfcguid.h"
#include <itoolbar.h>
#include <dtoolbar.h>
#include <dirisole.h>
#include <SrChoice.h>

#include "ThisDll.h"
#include "Wrapper.h"		// SmartInterfaces
#include "mainfrm.h"
#include "MainUIOwner.h"
#include "TRiASBarObj.h"
#include "ToolBarButton.h"
#include "PropertyChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Globale Objektzähler
extern LONG g_cObj;		// Anzahl der aktiven Objekte
extern LONG g_cLock;	// Anzahl der externen Locks

// Flags aus Registry, die über den Mode von FakeMFC entscheiden ------------
#if defined(_DEBUG)
DWORD g_dwHookFlags = SUBCLASSTRIAS | HOOKTRIAS | SUBCLASSTRIASVIEW;
#else
DWORD g_dwHookFlags = SUBCLASSTRIAS | HOOKTRIAS | SUBCLASSTRIASVIEW;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// ObjektMap (class factories)
CComModule _Module;			// Main module for ATL

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_PropertyChoice, CPropertyChoice)
	OBJECT_ENTRY(CLSID_TRiASToolBar, CTRiASToolBarObj)
	OBJECT_ENTRY(CLSID_TRiASToolBarButton, CToolBarButton)
END_OBJECT_MAP()

#if !defined(_OLECTL_H)
/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer/DllUnregisterServer status codes

#define SELFREG_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define SELFREG_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)
#define SELFREG_S_FIRST    MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x0200)
#define SELFREG_S_LAST     MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x020F)

#define SELFREG_E_TYPELIB           (SELFREG_E_FIRST+0)
// failed to register/unregister type library

#define SELFREG_E_CLASS             (SELFREG_E_FIRST+1)
// failed to register/unregister class
#endif _OLECTL_H

extern "C" HWND __hWndM = NULL;
extern "C" UINT __DexReg = 0;
extern "C" UINT __DexUnReg = 0;
extern "C" UINT __DexCmd = 0;
extern "C" UINT __DexxCmd = 0;
extern "C" UINT __DexNotify = 0;

char g_cbHelpPath[_MAX_PATH];		// Pfad zum Helpverzeichnis

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXEXTENSIONPROC g_pDexxExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
extern "C" DEXDISPATCHPROC g_pDexDispatchProc = NULL;
#endif // __XT && __DEXPROCS

#if !defined(_NOVERSION)
static void PreCalcVersion (void);
#endif // _NOVERSION

extern "C" TCHAR FAR g_pDLLName[_MAX_PATH] = "";
extern "C" HINSTANCE g_hInstance = 0;

extern "C" bool g_fGlobalLic = false;

/////////////////////////////////////////////////////////////////////////////
static AFX_EXTENSION_MODULE TRiASExtension = { NULL, NULL };

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		GetModuleFileName (hInst, g_pDLLName, _MAX_PATH);
		g_hInstance = hInst;

		_Module.Init (ObjectMap, g_hInstance);
	
		{	// HelpPfad generieren
		char cbDrive[_MAX_DRIVE];
		char cbPath[_MAX_PATH];

			_splitpath (g_pDLLName, cbDrive, cbPath, NULL, NULL);
			_makepath (g_cbHelpPath, cbDrive, cbPath, "", "");
		}

		{
		bool fReturn = false;
		CDynLinkLibrary *pDLL = NULL;
		CWinApp *pApp = NULL;
		bool bRegister = !TRiASExtension.bInitialized;

		// Call DisableThreadLibraryCalls if available.
			DisableThreadLibraryCalls (hInst);

		// Shared initialization.
			if (!AfxInitExtensionModule (TRiASExtension, hInst))
				return false;   // failure

		// Initialize DLL's instance(/module) not the app's
			if (!AfxWinInit(hInst, NULL, "", 0)) {
				AfxWinTerm();
				goto Cleanup;       // Init Failed
			}

		// initialize the single instance DLL
			pApp = AfxGetApp();
			if (pApp != NULL && !pApp->InitInstance()) {
				pApp->ExitInstance();
				AfxWinTerm();
				goto Cleanup;       // Init Failed
			}

		// Wire up this DLL into the resource chain.
		// (In the Win32 version it is OK to create this in DllMain.)
			pDLL = new CDynLinkLibrary (TRiASExtension, true);
			if (pDLL == NULL) return false;   // failure

	  	// Extension DLL one-time initialization
		// TRiAS ist erste ResourceQuelle
			AfxSetResourceHandle (GetModuleHandle (NULL));
//			afxCurrentInstanceHandle = GetModuleHandle (TRIAS_MODULENAME);
			fReturn = true;

Cleanup:
			if (!fReturn) return false;

			AfxSetModuleState(AfxGetThreadState()->m_pPrevModuleState);
			AfxGetThreadState()->m_pPrevModuleState = NULL;

		// Register class factories in context of private module state
			if (bRegister)
				COleObjectFactory::RegisterAll();
		}
		{
		// globale Lizensierung überprüfen
		CCurrentUser reg (TEXT("Software\\uve\\TRiAS\\Config"));
		DWORD dwLic = 0;

			reg.GetDWORD (TEXT("GlobalLicense"), dwLic);
			g_fGlobalLic = dwLic ? true : false;
		}
		{
		// HookFlags einlesen
		CCurrentUser reg (TEXT("Software\\uve\\TRiAS\\Extensions\\TRiAS.FakeMFC.1\\Config"));

			g_dwHookFlags = SUBCLASSTRIAS | HOOKTRIAS | SUBCLASSTRIASVIEW;
			reg.GetDWORD (TEXT("HookFlags"), g_dwHookFlags);
		}
		return true;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		{
//			AfxGetThreadState()->m_pPrevModuleState =
//				AfxSetModuleState(AfxGetStaticModuleState());

		CWinApp* pApp = AfxGetApp();
			
			if (pApp != NULL) pApp->ExitInstance();

		// terminate the library before destructors are called
			AfxWinTerm();
			AfxTermExtensionModule (TRiASExtension);
#if defined(WIN32)
			_Module.Term();
#endif // WIN32

#if defined(_DEBUG)
			TRACE0(TEXT("FakeMfc.ext: exiting:\r\n"));
			if (g_cObj != 0) TRACE1(TEXT("\tInfo: Global object count: %ld\r\n"), g_cObj);
			if (g_cLock != 0) TRACE1(TEXT("\tInfo: Global lock count: %ld\r\n"), g_cLock);
			if (_Module.GetLockCount() != 0) TRACE1(TEXT("\tInfo: Global ATL lock count: %ld\r\n"), _Module.GetLockCount());

			TRACE0(TEXT("\t"));

		HRESULT hr = AfxDllCanUnloadNow();

			if (S_OK != hr)
				TRACE1(TEXT("Info: AfxDllCanUnloadNow returns: 0x%lx\r\n"), hr);
#endif // _DEBUG
		}
		break;
	}

return true;
}

/*
 * DllGetClassObject
 *
 * Purpose:
 *  Provides an IClassFactory for a given CLSID that this DLL is
 *  registered to support.  
 *
 * Parameters:
 *  clsID           REFCLSID that identifies the class factory desired.
 *                  Since this parameter is passed this DLL can handle
 *                  any number of objects simply by returning different
 *                  class factories here for different CLSIDs.
 *
 *  riid            REFIID specifying the interface the caller wants
 *                  on the class object, usually IID_ClassFactory.
 *
 *  ppv             LPVOID FAR * in which to return the interface pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, otherwise contains an error SCODE.
 */

extern "C" 
HRESULT _XTENSN_EXPORT PASCAL DllGetClassObject (
				REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
// zuerst MFC interne Abfragen
	AFX_MANAGE_STATE(AfxGetModuleState());

HRESULT hr = AfxDllGetClassObject (rclsid, riid, ppv);

	if (SUCCEEDED(hr)) return S_OK;

// danach ATL fragen
	hr = _Module.GetClassObject(rclsid, riid, ppv);
	if (SUCCEEDED(hr)) return S_OK;

// abfragen, ob PropertySheetHandler gefragt ist
	if (rclsid == CLSID_TRiASDocSummaryInfo) {
	// Check that we can provide the interface
		if (!IsEqualIID(riid, IID_IUnknown) && 
			!IsEqualIID(riid, IID_IClassFactory) && 
			!IsEqualIID(riid, IID_IClassFactory2))
			return ResultFromScode(E_NOINTERFACE);

		*ppv = new CSummaryInfoCF();
		if (NULL == *ppv)
			return ResultFromScode (E_OUTOFMEMORY);
	} else {
	// abfragen und vergleichen des ClassID's
	CLSID clsID;

		if (!GetExtensionCLSID (clsID) || !IsEqualIID (rclsid, clsID))		// rufen der spezifischen Funktion
			return ResultFromScode(E_FAIL);

	// Check that we can provide the interface
		if (!IsEqualIID(riid, IID_IUnknown) && 
			!IsEqualIID(riid, IID_IClassFactory) && 
			!IsEqualIID(riid, IID_IClassFactory2))
			return ResultFromScode(E_NOINTERFACE);

	// Return our IClassFactory for Xtension objects
		*ppv = (LPVOID) new CXtensionClassFactory;
		if (NULL == *ppv)
			return ResultFromScode(E_OUTOFMEMORY);
	}

// Don't forget to AddRef the object through any interface we return
	((LPUNKNOWN)(*ppv)) -> AddRef();

return NOERROR;
}


/*
 * DllCanUnloadNow
 *
 * Purpose:
 *  Answers if the DLL can be freed, that is, if there are no
 *  references to anything this DLL provides.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  bool            true if nothing is using us, false otherwise.
 */
extern "C" 
SCODE _XTENSN_EXPORT PASCAL DllCanUnloadNow(void)
{
// zuerst MFC - Kontext setzen
	AFX_MANAGE_STATE(AfxGetModuleState());

	if (g_cObj != 0 || g_cLock != 0)
		return S_FALSE;			// nicht entladen

// MFC/ATL soll entscheiden
return (_Module.GetLockCount()==0 && S_OK == AfxDllCanUnloadNow()) ? S_OK : S_FALSE;
}

// DllRegisterServer - Adds entries to the system registry --------------------
STDAPI _XTENSN_EXPORT DllRegisterServer (void)
{
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetModuleState());
	if (!COleObjectFactoryEx::UpdateRegistryAll(true))
		return SELFREG_E_CLASS;

// ATL nicht vergessen
	if (FAILED(_Module.RegisterServer(true)))
		return SELFREG_E_CLASS;

// eigene TRiASXtension bedienen
// abfragen und registrieren der TypeLibrary
GUID _tlid;
static TCHAR cbBuffer[_MAX_PATH];
bool fName = GetTypeLibName (cbBuffer);		// evtl. Namen holen

	if (GetTypeLibGUID (_tlid) && 
	    !ExtOleRegisterTypeLib (g_hInstance, _tlid, fName ? cbBuffer : NULL))
	{
		return SELFREG_E_TYPELIB;
	}

	if (!UpdateRegistry (true))
		return SELFREG_E_CLASS;

return S_OK;
}


// DllUnregisterServer - Removes entries from the system registry -------------
STDAPI _XTENSN_EXPORT DllUnregisterServer (void)
{
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetModuleState());
	if (!COleObjectFactoryEx::UpdateRegistryAll(false))
		return SELFREG_E_CLASS;

// ATL nicht vergessen
	if (FAILED(_Module.UnregisterServer()))
		return SELFREG_E_CLASS;

// eigene TRiASXtension bedienen
GUID _tlid;

	if (GetTypeLibGUID (_tlid) && !ExtOleUnregisterTypeLib (_tlid))
		return SELFREG_E_TYPELIB;

	if (!UpdateRegistry (false))
		return SELFREG_E_CLASS;

return S_OK;
}

/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the TriasXtension object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here
 *  letting DllCanUnloadNow take care of the rest.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
void FAR PASCAL ObjectDestroyed(void)
{
	piInterlockedDecrement (&g_cObj);
}


// Implementation der Memberfunktionen der XtensionBasisklassse ---------------
// *** IUnknown methods ***
// Alle der abgeleiteten Klasse nicht bekannten Interface-Anforderungen sollten
// an diese Funktion weitergeleitet werden
/*
STDMETHODIMP CDerivedExtension :: QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
	if (riid == IID_MySpecialInterface) {
		*ppv = m_pISpec;
	} else if (...) {
	} else {
	// not supported interface
		return CTriasExtension :: QueryInterface (riid, ppvObj);
	}

	(*ppv) -> AddRef();

return NOERROR;
}
*/
STDMETHODIMP CTriasExtension :: QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown) {
	// Someone is asking us for our controlling IUnknown.
	// CTriasExtension is that IUnknown, so "this" is the answer.
		*ppvObj = this;
	} else if (riid == IID_ITriasXtension || riid == IID_ITriasXtension2) {
	// Someone is asking us for ITriasXtension, return the
	// CImpTriasExtension (the concrete implementation)
		*ppvObj = m_pTXtsn;
	} else {
	// They must have asked for another interface -- something
	// we don't support.  Report the error.
		*ppvObj = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}

// If execution reached this point then no error occurred.
	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CTriasExtension :: AddRef (void)
{
	piInterlockedIncrement(&m_dwRefCnt);
	return m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CTriasExtension :: Release (void)
{
	if(piInterlockedDecrement(&m_dwRefCnt) == 0) {
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

///////////////////////////////////////////////////////////////////////////////
// PreTranslateMessage in TRiAS-MessageLoop einhängen
bool App_PreTranslateMessage (MSG *pMsg)
{
	return AfxGetApp() -> PreTranslateMessage (pMsg);
}

bool App_IdleProc (LONG lCount)
{
	return AfxGetApp() -> OnIdle (lCount);
}

// *** ITriasXtension specific functions *** ----------------------------------
STDMETHODIMP_(HDEX) CTriasExtension :: LoadExtension (TRIASLOADEX *pTL, HWND hWnd)
{
	if (pTL == NULL) return NULL;	// ParameterFehler

// übergebene Parameter merken
	m_hDex = (HDEX)g_hInstance;
	__hWndM = m_hWndM = hWnd;
	m_uiMenuOffset = pTL -> m_wMenuDelta;
	if (pTL -> m_dwSize == sizeof(TRIASLOADEX))
		m_iMode = pTL -> m_iMode;

// MenuHandle's und MenuTexte speichern und an TRIAS(R) zurückliefern
	if (pTL -> m_hMenu = MenuHandle())
		strncpy (pTL -> m_szMenuName, MenuEntry().c_str(), DEX_MENUNAMELEN);
	if (pTL -> m_hORMenu = ORMenuHandle())
		strncpy (pTL -> m_szORMenuName, ORMenuEntry().c_str(), DEX_MENUNAMELEN);

#if !defined(__CV__)
// Hauptfenster anlegen
	m_fAttached = false;

	if (g_dwHookFlags & SUBCLASSTRIAS) {
	// FrameObjekt anlegen
		m_pWnd = new CMainFrame();
		if (NULL == m_pWnd) return NULL;

		static_cast<CMainFrame *>(m_pWnd) -> SetDepUnk (this);		// Erweiterung festhalten

	// FrameObjekt an TRiAS-Hauptfenster anhängen
	HWND hWndOld = m_pWnd -> Detach();

		if (NULL != hWndOld && ::IsWindow (hWndOld))
			::DestroyWindow (hWndOld);
		if (!m_pWnd -> SubclassWindow (hWnd))
			return NULL;

	CWinThread *pThread = AfxGetThread();

		if (NULL == pThread -> m_pMainWnd)
			pThread -> m_pMainWnd = m_pWnd;		// set main frame of this thread

		m_fAttached = true;		// Fenster wurde von uns angelegt
	} else {
		if ((m_pWnd = CWnd :: FromHandlePermanent (hWnd)) == NULL) {
		// wir sind die ersten
			m_pWnd = new CWnd();
			if (m_pWnd == NULL) return NULL;
			m_pWnd -> Attach (hWnd);	// trägt hWnd in CWndMap ein
			m_fAttached = true;
		}
	}
#endif // !__CV__

return (HDEX)g_hInstance;
}

// Abgeleitete Funktionen sollten zuerst! diese Funktion rufen ----------------
// STDMETHODIMP_(bool) CDerivedExtension :: InitExtension (short iMode)
// {
//	CTriasExtension :: InitExtension (iMode);
//	...
// }
STDMETHODIMP_(bool) CTriasExtension :: InitExtension (short iMode)
{
	m_iMode = iMode;
	m_fLoaded = true;

	if (g_dwHookFlags & HOOKTRIAS) {
		DEX_AttachIdleProc (App_IdleProc);
		DEX_AttachPreTranslateMsgProc (App_PreTranslateMessage);
	}
	return true;
}

STDMETHODIMP_(bool) CTriasExtension :: UnLoadExtension (void)
{
// zuerst Hooks abmelden
	if (g_dwHookFlags & HOOKTRIAS) {
	bool (*pF)(MSG *) = DEX_DetachPreTranslateMsgProc();
	bool (*pIdle)(LONG) = DEX_DetachIdleProc();

		ASSERT(pF == App_PreTranslateMessage);
		ASSERT(pIdle == App_IdleProc);
	}
	if (g_dwHookFlags & SUBCLASSTRIAS) {
		ASSERT(NULL != m_pWnd);
		static_cast<CMainFrame *>(m_pWnd) -> SetDepUnk (NULL);		// Erweiterung freigeben
	}

	RELEASE (m_pXtnSite);	// TRiAS jetzt freigeben
	m_fLoaded = false;
	
return true;
}

STDMETHODIMP_(bool)  CTriasExtension :: MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	return false;	// keine Menubearbeitung
}

STDMETHODIMP_(bool) CTriasExtension :: MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	return false;	// keine Menubearbeitung
}

STDMETHODIMP_(bool) CTriasExtension :: MenuCommand (WPARAM wParam, HWND hWnd)
{
	return false;	// keine Menubearbeitung
}

STDMETHODIMP_(LRESULT) CTriasExtension :: Notification (WPARAM wParam, LPARAM lParam)
{
	return false;	// keine Notification-Bearbeitung
}

STDMETHODIMP_(LRESULT) CTriasExtension :: WindowsNotification (UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	return false;	// keine Notification-Bearbeitung
}

STDMETHODIMP_(LRESULT) CTriasExtension :: GetCapabilities (UINT uiCap)
{
	switch (uiCap) {
	case DEXCAP_NOTLOADED:
		return m_fLoaded ? false : true;	// true, wenn nicht geladen
		
	case DEXCAP_OBJPROPFUNCS:
		return __TestObjProps();

	case DEXCAP_CLASSPROPFUNCS:
		return __TestClassProps();

	default:
		break;
	}
	
return false;
}

// *** ITriasXtension2 specific functions *** ---------------------------------
STDMETHODIMP CTriasExtension :: SetXtensionSite (ITriasXtensionSite *pXtnSite)
{
	RELEASE(m_pXtnSite);		// alten Pointer freilassen
	m_pXtnSite = pXtnSite;
	ADDREF(m_pXtnSite);		// neuen festhalten

return NOERROR;
}


// Testet, ob ObjectProps installiert sind ------------------------------------
bool CTriasExtension :: __TestObjProps (void)
{
LPOBJECTPROPS pIPropIF = NULL;

// wenn das IObjectProps - Interface nicht unterstütz wird, dann eben nicht
	if (FAILED(QueryInterface (IID_IObjectProps, (LPVOID *)&pIPropIF)))
		return false;

// Enumerator der ObjProperties abfragen
LPENUMOBJPROPS pIObjProps = NULL;
HRESULT hr = pIPropIF -> EnumObjectProps (&pIObjProps);

	pIPropIF -> Release();
	if (FAILED(hr)) return false;

	pIObjProps -> Reset();

// testen, ob wenigstens eine ObjectProp installiert ist
LPOBJECTPROPERTY pIObjProp = NULL;

	hr = pIObjProps -> Next (1, (LPUNKNOWN *)&pIObjProp, NULL);
	if (SUCCEEDED(hr))
		pIObjProp -> Release();
	pIObjProps -> Release();	// Enumerator freigeben

return SUCCEEDED(hr);
}

// Testet, ob ClassProps installiert sind -------------------------------------
bool CTriasExtension :: __TestClassProps (void)
{
LPOBJECTPROPS pIPropIF = NULL;

// wenn das IObjectProps - Interface nicht unterstütz wird, dann eben nicht
	if (FAILED(QueryInterface (IID_IObjectProps, (LPVOID *)&pIPropIF)))
		return false;

// Enumerator liefern lassen
LPENUMOBJPROPS pIClsProps = NULL;
HRESULT hr = pIPropIF -> EnumObjectProps (&pIClsProps);

	pIPropIF -> Release();
	if (FAILED(hr)) return false;

// Testen, ob wenigstens eine ClsProp installiert ist
LPCLASSPROPERTY pIClsProp = NULL;

	pIClsProps -> Reset();
	hr = pIClsProps -> Next (1, (LPUNKNOWN *)&pIClsProp, NULL);
	if (SUCCEEDED(hr))
		pIClsProp -> Release();

	pIClsProps -> Release();	// Enumerator freigeben

return SUCCEEDED(hr);
}

// ----------------------------------------------------------------------------
// Konstruktor/Destruktor -----------------------------------------------------
CTriasExtension :: CTriasExtension (UINT uiMenuID, UINT uiORMenuID)
		 : m_uiMenuID(uiMenuID), m_uiORMenuID(uiORMenuID),
		   m_strMenuEntry (DEX_MENUNAMELEN+1, default_size),
		   m_strORMenuEntry (DEX_MENUNAMELEN+1, default_size)
{
	m_dwRefCnt = 0L;
	m_pNotifProc = NULL;
	m_pUnk = NULL;
	m_pTXtsn = NULL;
	m_pXtnSite = NULL;

	m_hWndM = NULL;
	m_hDex = NULL;
	
	m_uiMenuOffset = 0;
	m_hPopUpMenu = NULL;
	m_hPopUpORMenu = NULL;

	m_iMode = 0;
	m_fLoaded = false;

	m_pWnd = NULL;
	m_fAttached = false;

	m_pLoadedMenu = NULL;
	m_pLoadedORMenu = NULL;

#if !defined(_NOVERSION)
	PreCalcVersion();	// WindowsVersion feststellen
#endif // _NOVERSION
}

// Eigentliche Initialisierung der Basisklasse --------------------------------
bool CTriasExtension :: __FInit (LPUNKNOWN lpUnk, DESTROYNOTIFYPROCPTR pProc)
{
	m_pNotifProc = pProc;
	m_pUnk = lpUnk;		// Controlling unknown

// ITriasXtension initialisieren
	m_pTXtsn = new CImpTriasXtension (lpUnk ? lpUnk : this, this);
	if (NULL == m_pTXtsn) return false;

// Daten dieser Extension initialisieren
char cbBuffer[DEX_MENUNAMELEN];

///////////////////////////////////////////////////////////////////////////////
// MFC-Variante 
// evtl. HauptMenu aufbauen
	if (m_uiMenuID) {
		m_pLoadedMenu = new CMenu();
		if (m_pLoadedMenu == NULL) return false;
		m_pLoadedMenu -> LoadMenu (m_uiMenuID);

	// PopUpMenu und MenuText holen
	HMENU hMenu = m_pLoadedMenu -> m_hMenu;

		m_hPopUpMenu = GetSubMenu (hMenu, 0);
		GetMenuString (hMenu, 0, cbBuffer, DEX_MENUNAMELEN, MF_BYPOSITION);
		m_strMenuEntry = cbBuffer;
	} 
	if (m_uiORMenuID) {
		m_pLoadedORMenu = new CMenu();
		if (m_pLoadedORMenu == NULL) return false;	
		m_pLoadedORMenu -> LoadMenu (m_uiORMenuID);

	// PopUpMenu und MenuText holen
	HMENU hMenu = m_pLoadedORMenu -> m_hMenu;

		m_hPopUpORMenu = GetSubMenu (hMenu, 0);
		GetMenuString (hMenu, 0, cbBuffer, DEX_MENUNAMELEN, MF_BYPOSITION);
		m_strORMenuEntry = cbBuffer;
	} 

// Registrieren der Messages
	__DexCmd = RegisterWindowMessage (TEXT("TriasExtensionMessage"));
	__DexxCmd = RegisterWindowMessage (TEXT("TriasCPPExtensionMessage"));
	__DexReg = RegisterWindowMessage (TEXT("TriasRegisterNotification"));
	__DexUnReg = RegisterWindowMessage (TEXT("TriasUnRegisterNotification"));
	__DexNotify = RegisterWindowMessage (TEXT("TriasNotification"));
	if (__DexCmd == 0 || __DexReg == 0 || 
	    __DexUnReg == 0 || __DexNotify == 0 || __DexxCmd == 0) 
	{
		return false;
	}

#if defined(__XT) && defined(__DEXPROCS)
// externe EntryPoints von Trias finden
HMODULE hTrias = GetModuleHandle (NULL);

	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC"));
	g_pDexxExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXXEXTENSIONPROC"));
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, TEXT("DEXNOTIFICATIONPROCEX"));
	g_pDexDispatchProc = (DEXDISPATCHPROC)GetProcAddress (hTrias, TEXT("DEXDISPATCHPROC"));
#endif // __XT && __DEXPROCS

return true;
}


CTriasExtension :: ~CTriasExtension (void) 
{
// dann das Fenster freigeben
	if (m_fAttached && ::IsWindow(m_pWnd -> m_hWnd)) {

		if (g_dwHookFlags & SUBCLASSTRIAS) {
		HWND hWndOld = m_pWnd -> UnsubclassWindow();

			ASSERT(hWndOld == hWnd());

		CWinThread *pThread = AfxGetThread();

			if (m_pWnd == pThread -> m_pMainWnd)
				pThread -> m_pMainWnd = NULL;		// detach main frame from thread
		
			static_cast<CMainFrame *>(m_pWnd) -> OnNcDestroy();
		}

	// wenn kein hWnd mehr da ist, dann erfolgte bereits 'delete this'
//		m_pWnd -> m_hWnd = NULL;
//		delete m_pWnd; // -> DestroyWindow();
		m_pWnd = NULL;
	}

// erst jetzt alles andere aufräumen
	DELETE (m_pLoadedMenu);
	DELETE (m_pLoadedORMenu);

	DELETE (m_pTXtsn);
	RELEASE (m_pXtnSite);			// TRiAS jetzt freigeben, wenn noch nicht geschehen

	g_pDexExtensionProc = NULL;
	g_pDexxExtensionProc = NULL;
	g_pDexNotificationProc = NULL;
	g_pDexDispatchProc = NULL;

	g_pTE = NULL;					// keine Extension mehr vorhanden

// ObjektCount wieder runterzählen
	if (m_pNotifProc) (*m_pNotifProc)();
}


// Notifikationsbehandlung ----------------------------------------------------
LRESULT CTriasExtension :: RegisterNotification (UINT wMsg, bool isLocal) 
{
	if (g_pDexDispatchProc)
		return (*g_pDexDispatchProc)(m_hWndM, __DexReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));

	ASSERT(::IsWindow(m_hWndM));
	return SendMessage (m_hWndM, __DexReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal)); 
}

LRESULT CTriasExtension :: UnRegisterNotification (UINT wMsg, bool isLocal)
{
	if (g_pDexDispatchProc)
		return (*g_pDexDispatchProc)(m_hWndM, __DexUnReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));

	ASSERT(::IsWindow(m_hWndM));
	return SendMessage (m_hWndM, __DexUnReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));
}

HWND CTriasExtension :: GetActiveORWindow (void)
{
	return (HWND)DexExtensionProc((WPARAM)DEX_QUERYACTIVEORWINDOW, 0L);
}

UINT CTriasExtension :: InstallMenuItem (UINT iMenuID, UINT iMenuStr, 
					bool iORMenu, short iPopupNum,
					short iMenuPos)
{
INSTALLMENUITEM imi;

	INITSTRUCT (imi, INSTALLMENUITEM);
	
CString RS; RS.LoadString (iMenuStr);

	imi.pMenuText = (char *)(const char *)RS;
	imi.hDex = hDex();
	imi.iMenuID = iMenuID;
	imi.iFlag = iORMenu;
	imi.iMenuNum = iPopupNum;
	imi.iMenuPos = iMenuPos;

	DEX_InstallMenuItem (imi);

return imi.iMenuID;		// neuen MenuID merken
}

void CTriasExtension :: RemoveMenuItem (UINT iMenuID, bool iORMenu, short iPopupNum)
{
REMOVEMENUITEM rmi;

	rmi.dwSize = sizeof(REMOVEMENUITEM);
	rmi.hDex = hDex();
	rmi.iMenuID = iMenuID;
	rmi.iMenuNum = iPopupNum;
	rmi.iFlag = iORMenu;
	DEX_RemoveMenuItem (rmi);
}

// Neues Hauptmenü unterschieben ----------------------------------------------
HMENU CTriasExtension :: EmptyMenu (void)
{
	if (!m_hPopUpMenu) return m_hPopUpMenu;

short n = GetMenuItemCount(m_hPopUpMenu);

	if (!n) return m_hPopUpMenu;

	for (short i = n -1; i >= 0; i--) {
	short id = GetMenuItemID (m_hPopUpMenu, i);

		if (id < 0)
			DestroyMenu (GetSubMenu (m_hPopUpMenu, i));
		DeleteMenu (m_hPopUpMenu, i, MF_BYPOSITION);
	}

return m_hPopUpMenu;
}


// Neues OR-Menü unterschieben ------------------------------------------------
HMENU CTriasExtension :: EmptyORMenu (void)
{
	if (!m_hPopUpORMenu) return m_hPopUpORMenu;

short n = GetMenuItemCount (m_hPopUpORMenu);
	
	if (!n) return m_hPopUpORMenu;

	for (short i = n -1; i >= 0; i--) {
	short id = GetMenuItemID (m_hPopUpORMenu, i);
		
		if (id < 0)
			DestroyMenu (GetSubMenu (m_hPopUpORMenu, i));
		DeleteMenu (m_hPopUpORMenu, i, MF_BYPOSITION);
	}

return m_hPopUpORMenu;
}

// Einklinken eines neuen Werkzeuges in das Werkzeugfenster -------------------
short CTriasExtension :: InstallTool (UINT rsc, const char *pDesc)
{
	if (rsc == 0) return -1;

// Laden der Bitmap 
CBitmap CBmp;

	CBmp.LoadBitmap (rsc);

INSTALLTOOL IT;

	memset (&IT, '\0', sizeof(INSTALLTOOL));
	IT.dwSize = sizeof (INSTALLTOOL);
	IT.hBmp = (HBITMAP)CBmp.Detach();
	IT.pDesc = (char *)pDesc;

// die Bitmap gehört ab jetzt vollständig TRIAS !
	
return DEX_InstallTool (IT);
}

short CTriasExtension :: InstallTool (const char *pRsc, const char *pDesc)
{
	if (pRsc == NULL) return -1;

// Laden der Bitmap 
CBitmap CBmp;

	CBmp.LoadBitmap (pRsc);

INSTALLTOOL IT;

	memset (&IT, '\0', sizeof(INSTALLTOOL));
	IT.dwSize = sizeof (INSTALLTOOL);
	IT.hBmp = (HBITMAP)CBmp.Detach();
	IT.pDesc = (char *)pDesc;

// die Bitmap gehört ab jetzt vollständig TRIAS !
	
return DEX_InstallTool (IT);
}

void CTriasExtension :: RemoveTool (short iToolID)
{
	DEX_RemoveTool (iToolID);
}


#if !defined(_NOVERSION)

// WindowsVersion feststellen -------------------------------------------------
static bool s_fWin31 = false;
static bool s_fWin40 = false;
static bool s_fWin41 = false;
static bool s_fWinNT = false;
static bool s_fWin32s = false;

static void PreCalcVersion (void)
{
// Initialise Version Info
DWORD dwVersion = GetVersion();

	s_fWin31 = false;
	s_fWinNT = false;
	s_fWin32s = false;
	s_fWin40 = false;
	s_fWin41 = false;

	if (dwVersion < ~0x7fffffff) {			// Windows NT
		s_fWinNT = true;
		if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) > 3) {
			s_fWin40 = true;	// NT4.0
			s_fWin31 = true;
		}
	} else if (LOBYTE(LOWORD(dwVersion)) < 4) {	// Win32s
		if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
		    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin31 = true;
		s_fWin32s = true;
	} else {					// Chicago or Memphis
		if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin41 = true;
		s_fWin31 = true;
		s_fWin40 = true;
	}
}

bool IsWin31 (void) { return s_fWin31; }
bool IsWin40 (void) { return s_fWin40; }
bool IsWin41 (void) { return s_fWin41; }
bool IsWin32s (void) { return s_fWin32s; }
bool IsWinNT (void) { return s_fWinNT; }

#endif // !_NOVERSION

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	ASSERT(::IsWindow(__hWndM));

return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _DEBUG

LRESULT PASCAL DexxExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexxExtensionProc)
		return (*g_pDexxExtensionProc)(w, l);

	ASSERT(::IsWindow(__hWndM));

return :: SendMessage (__hWndM, __DexxCmd, w, l);
}

LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	ASSERT(::IsWindow(__hWndM));

return :: SendMessage (__hWndM, __DexNotify, w, l);
}

LRESULT PASCAL DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

	ASSERT(::IsWindow(__hWndM));

return :: PostMessage (__hWndM, __DexNotify, w, l);
}

#endif // __XT && __DEXPROCS

/////////////////////////////////////////////////////////////////////////////
// Library init -- wird von der MFC gerufen
BEGIN_MESSAGE_MAP(CThisDLL, CWinApp)
	//{{AFX_MSG_MAP(CThisDLL)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool CThisDLL :: InitInstance (void)
{
	g_hInstance = m_hInstance;

	SetRegistryKey (_T("uve"));
	return true;
}

int CThisDLL::ExitInstance (void)
{
// any DLL termination goes here (WEP-like code)
	return CWinApp::ExitInstance();
}

BOOL CThisDLL::IsIdleMessage (MSG *pMsg)
{
	if (!CWinApp::IsIdleMessage (pMsg) || pMsg->message == WM_TIMER) 
		return FALSE;
	else
		return TRUE;
}

// In this override of OnIdle we are doing UI for our app.
// Since this needs to be as fast as possible to give the user
// the best result we do our updates first when lCount is zero
// then we call the library to do its work.
/*
#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler

bool CExtDLL::OnIdle(LONG lCount)
{
	if (lCount == 0)
	{
		ASSERT(m_pMainWnd != NULL);

		// look for any top-level windows owned by us
		// we use 'HWND's to avoid generation of too many temporary CWnds
		for (HWND hWnd = ::GetWindow(m_pMainWnd->m_hWnd, GW_HWNDFIRST);
				hWnd != NULL; hWnd = ::GetNextWindow(hWnd, GW_HWNDNEXT))
		{
			if (::GetParent(hWnd) == m_pMainWnd->m_hWnd)
			{
				// if owned window is active, move the activation to the
				//   application window
//				if (GetActiveWindow() == hWnd && (::GetCapture() == NULL))
//					m_pMainWnd->SetActiveWindow();

				// also update the buttons for the top-level window
				SendMessage(hWnd, WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0L);
			}
		}
	}
	return CWinApp::OnIdle(lCount);
}

*/
