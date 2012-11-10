// Routinen fuer Klasse CTriasExtension ---------------------------------------
// File: XTENCUNK.CXX

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include <xtensnn.h>

#include <registrx.hxx>
#include <AniWaitCursor.h>

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
#include "StatusProgress.h"
#if defined(_USE_TOOLBARCUSTOMIZE)
#include "TRiASToolBarCustomizePage.h"
#endif // defined(_USE_TOOLBARCUSTOMIZE)
#include "TRiASToolBarPage.h"
#include "CoolControlManager.h"
#if defined(_USE_DOCKEDTABWINDOW)
#include "ManageTabWindow.h"
#endif // defined(_USE_DOCKEDTABWINDOW)

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
DWORD g_dwHookFlags = 
	TRIASMODE_SubClassTRiAS |
	TRIASMODE_HookTRiAS |
	TRIASMODE_SubClassTRiASView |
	TRIASMODE_InterTRiAS |
	TRIASMODE_GDO;

/////////////////////////////////////////////////////////////////////////////
// ObjectMap (class factories)
CComModule _Module;			// Main module for ATL

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_PropertyChoice, CPropertyChoice)
	OBJECT_ENTRY(CLSID_TRiASToolBar, CTRiASToolBarObj)
	OBJECT_ENTRY(CLSID_TRiASToolBarButton, CToolBarButton)
	OBJECT_ENTRY(CLSID_StatusProgress, CStatusProgress)
	OBJECT_ENTRY(CLSID_TRiASToolBarPage, CTRiASToolBarPage)
#if defined(_USE_TOOLBARCUSTOMIZE)
	OBJECT_ENTRY(CLSID_TRiASToolBarCustomizePage, CTRiASToolBarCustomizePage)
#endif // defined(_USE_TOOLBARCUSTOMIZE)
#if defined(_USE_DOCKEDTABWINDOW)
	OBJECT_ENTRY(CLSID_ManageTabWindows, CManageTabWindows)
#endif // defined(_USE_DOCKEDTABWINDOW)
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
extern "C" DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
extern "C" DEXEXTENSIONPROC g_pDexxExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
extern "C" DEXDISPATCHPROC g_pDexDispatchProc = NULL;
#endif // __XT && __DEXPROCS

#if defined(_XTENSIONSITE_INTERFACE)
EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
#endif // _XTENSIONSITE_INTERFACE

#if !defined(_NOVERSION)
static void PreCalcVersion (void);
#endif // _NOVERSION

extern "C" TCHAR FAR g_pDLLName[_MAX_PATH] = "";
extern "C" HINSTANCE g_hInstance = 0;

#if defined(_DEBUG)
extern "C" bool g_fGlobalLic = false;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

BOOL AmIAdministrator (void)
{
// Plagerized from Microsoft Knowledge Base article Q118626
HANDLE access_token_handle = NULL;
BYTE buffer[1024];
PTOKEN_GROUPS token_groups_p = (PTOKEN_GROUPS) buffer;
DWORD buffer_size = 0;

	if (!OpenThreadToken (GetCurrentThread(), TOKEN_QUERY, TRUE, &access_token_handle)) {
		if (ERROR_NO_TOKEN != GetLastError())
			return FALSE;

	// retry against process token if no thread token exists
		if (!OpenProcessToken (GetCurrentProcess(), TOKEN_QUERY, &access_token_handle))
			return FALSE;
	}

BOOL success = GetTokenInformation (access_token_handle, TokenGroups, buffer, 1024, &buffer_size);

	CloseHandle (access_token_handle);
	access_token_handle = NULL;
	if (!success)
		return FALSE;

SID_IDENTIFIER_AUTHORITY nt_authority_sid = SECURITY_NT_AUTHORITY;
PSID administrators_sid_p = NULL;

	if (!AllocateAndInitializeSid (&nt_authority_sid, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &administrators_sid_p))
		return FALSE;

// assume that we don't find the admin SID.
	success = FALSE;
	for (UINT x = 0; x < token_groups_p->GroupCount; x++)
	{
		if (EqualSid (administrators_sid_p, token_groups_p->Groups[x].Sid)) {
			success = TRUE;
			break;
		}
	}
	FreeSid (administrators_sid_p);
	return success;
}

/////////////////////////////////////////////////////////////////////////////
static AFX_EXTENSION_MODULE TRiASExtension = { NULL, NULL };

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
		TCHAR szModule[_MAX_PATH];

			GetModuleFileName (hInst, szModule, _MAX_PATH);

		TCHAR szModuleShort[_MAX_PATH];
		int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
		LPOLESTR pszModule;

			USES_CONVERSION;
			if (cbShortName == _MAX_PATH)
				return false;
			pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

			strcpy (g_pDLLName, OLE2A(pszModule));
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
			CCurrentUser reg (KEY_READ, g_cbRegConfig);

#if defined(_DEBUG)
			DWORD dwLic = 0;

				reg.GetDWORD (TEXT("GlobalLicense"), dwLic);
				g_fGlobalLic = dwLic ? true : false;
#endif // defined(_DEBUG)

			// HookFlags einlesen
				g_dwHookFlags = 
					TRIASMODE_SubClassTRiAS | 
					TRIASMODE_HookTRiAS | 
					TRIASMODE_SubClassTRiASView |
					TRIASMODE_InterTRiAS |
					TRIASMODE_GDO;

				reg.GetDWORD (TEXT("TRiASMode"), g_dwHookFlags);
			}
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
	AFX_MANAGE_STATE(AfxGetAppModuleState());

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
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	if (g_cObj != 0 || g_cLock != 0)
		return S_FALSE;			// nicht entladen

// MFC/ATL soll entscheiden
return (_Module.GetLockCount()==0 && S_OK == AfxDllCanUnloadNow()) ? S_OK : S_FALSE;
}

// DllRegisterServer - Adds entries to the system registry --------------------
STDAPI _XTENSN_EXPORT DllRegisterServer (void)
{
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetAppModuleState());

BOOL fAmIAdmin = AmIAdministrator();

	if (!COleObjectFactoryEx::UpdateRegistryAll(true) && fAmIAdmin)
		return SELFREG_E_CLASS;

// ATL nicht vergessen
	if (FAILED(_Module.RegisterServer(true)) && fAmIAdmin)
		return SELFREG_E_CLASS;

// eigene TRiASXtension bedienen
// abfragen und registrieren der TypeLibrary
GUID _tlid;
static TCHAR cbBuffer[_MAX_PATH];
bool fName = GetTypeLibName (cbBuffer);		// evtl. Namen holen

	if (GetTypeLibGUID (_tlid) && 
	    !ExtOleRegisterTypeLib (g_hInstance, _tlid, fName ? cbBuffer : NULL) &&
	     fAmIAdmin)
	{
		return SELFREG_E_TYPELIB;
	}
	if (!UpdateRegistry (true) && fAmIAdmin)
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - Removes entries from the system registry -------------
STDAPI _XTENSN_EXPORT DllUnregisterServer (void)
{
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetAppModuleState());

BOOL fAmIAdmin = AmIAdministrator();

	if (!COleObjectFactoryEx::UpdateRegistryAll(false) && fAmIAdmin)
		return SELFREG_E_CLASS;

// ATL nicht vergessen
	if (FAILED(_Module.UnregisterServer()) && fAmIAdmin)
		return SELFREG_E_CLASS;

// eigene TRiASXtension bedienen
GUID _tlid;

	if (GetTypeLibGUID (_tlid) && !ExtOleUnregisterTypeLib (_tlid) && fAmIAdmin)
		return SELFREG_E_TYPELIB;

	if (!UpdateRegistry (false) && fAmIAdmin)
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
STDMETHODIMP CDerivedExtension::QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
	if (riid == IID_MySpecialInterface) {
		*ppv = m_pISpec;
	} else if (...) {
	} else {
	// not supported interface
		return CTriasExtension::QueryInterface (riid, ppvObj);
	}

	(*ppv) -> AddRef();

return NOERROR;
}
*/
STDMETHODIMP CTriasExtension::QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown) {
	// Someone is asking us for our controlling IUnknown.
	// CTriasExtension is that IUnknown, so "this" is the answer.
		*ppvObj = this;
	} 
	else if (riid == IID_ITriasXtension || riid == IID_ITriasXtension2) {
	// Someone is asking us for ITriasXtension, return the
	// CImpTriasExtension (the concrete implementation)
		*ppvObj = static_cast<ITriasXtension2 *>(m_pTXtsn);
	} 
	else {
	// They must have asked for another interface -- something
	// we don't support.  Report the error.
		*ppvObj = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}

// If execution reached this point then no error occurred.
	LPUNKNOWN(*ppvObj) -> AddRef();
	return NOERROR;
}

STDMETHODIMP_(ULONG) CTriasExtension::AddRef (void)
{
	piInterlockedIncrement(&m_dwRefCnt);
	return m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CTriasExtension::Release (void)
{
	if(piInterlockedDecrement(&m_dwRefCnt) == 0) {
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

///////////////////////////////////////////////////////////////////////////////
// PreTranslateMessage in TRiAS-MessageLoop einhängen
BOOL App_PreTranslateMessage (MSG *pMsg)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return AfxGetApp() -> PreTranslateMessage (pMsg);
}

BOOL App_IdleProc (LONG lCount)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return AfxGetApp() -> OnIdle (lCount);
}

// *** ITriasXtension specific functions *** ----------------------------------
// remove macro from windowsx.h
#undef SubclassWindow	

STDMETHODIMP_(HDEX) CTriasExtension::LoadExtension (TRIASLOADEX *pTL, HWND hWnd)
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

	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
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
		if ((m_pWnd = CWnd::FromHandlePermanent (hWnd)) == NULL) {
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
// STDMETHODIMP_(bool) CDerivedExtension::InitExtension (short iMode)
// {
//	CTriasExtension::InitExtension (iMode);
//	...
// }
STDMETHODIMP_(BOOL) CTriasExtension::InitExtension (short iMode)
{
	m_iMode = iMode;
	m_fLoaded = true;

	if (g_dwHookFlags & TRIASMODE_HookTRiAS) {
		DEX_AttachIdleProc (App_IdleProc);
		DEX_AttachPreTranslateMsgProc (App_PreTranslateMessage);
	}
	return true;
}

STDMETHODIMP_(BOOL) CTriasExtension::UnLoadExtension (void)
{
// zuerst Hooks abmelden
	if (g_dwHookFlags & TRIASMODE_HookTRiAS) {
	BOOL (*pF)(MSG *) = DEX_DetachPreTranslateMsgProc();
	BOOL (*pIdle)(LONG) = DEX_DetachIdleProc();

		ASSERT(pF == App_PreTranslateMessage);
		ASSERT(pIdle == App_IdleProc);
	}
	if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
		ASSERT(NULL != m_pWnd);
		static_cast<CMainFrame *>(m_pWnd) -> SetDepUnk (NULL);		// Erweiterung freigeben
	}

// dann das Fenster freigeben
//	if (m_fAttached && ::IsWindow(m_pWnd -> m_hWnd)) {
//		if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
//		HWND hWndOld = m_pWnd -> UnsubclassWindow();
//
//			ASSERT(hWndOld == hWnd());
//
//		CWinThread *pThread = AfxGetThread();
//
//			if (m_pWnd == pThread -> m_pMainWnd)
//				pThread -> m_pMainWnd = NULL;		// detach main frame from thread
//		
////			static_cast<CMainFrame *>(m_pWnd) -> OnNcDestroy();
//		}
//
//	// wenn kein hWnd mehr da ist, dann erfolgte bereits 'DELETE_OBJ this'
////		m_pWnd -> m_hWnd = NULL;
////		DELETE_OBJ m_pWnd; // -> DestroyWindow();
//		m_pWnd = NULL;
//	}
//
	RELEASE (m_pXtnSite);	// TRiAS jetzt freigeben
	m_fLoaded = false;
	return true;
}

HWND CTriasExtension::UnsubclassWindow(void)
{
	if (m_fAttached && ::IsWindow(m_pWnd -> m_hWnd)) {
	HWND hWndOld = NULL;

		if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
			hWndOld = m_pWnd -> UnsubclassWindow();

			ASSERT(hWndOld == hWnd());

		CWinThread *pThread = AfxGetThread();

			if (m_pWnd == pThread -> m_pMainWnd)
				pThread -> m_pMainWnd = NULL;		// detach main frame from thread
		}

	// wenn kein hWnd mehr da ist, dann erfolgte bereits 'DELETE_OBJ this'
		m_pWnd = NULL;

		return hWndOld;
	}
	return NULL;
}

STDMETHODIMP_(BOOL)  CTriasExtension::MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	return false;	// keine Menubearbeitung
}

STDMETHODIMP_(BOOL) CTriasExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	return false;	// keine Menubearbeitung
}

STDMETHODIMP_(BOOL) CTriasExtension::MenuCommand (WPARAM wParam, HWND hWnd)
{
	return false;	// keine Menubearbeitung
}

STDMETHODIMP_(LRESULT) CTriasExtension::Notification (WPARAM wParam, LPARAM lParam)
{
	return false;	// keine Notification-Bearbeitung
}

STDMETHODIMP_(LRESULT) CTriasExtension::WindowsNotification (UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	return false;	// keine Notification-Bearbeitung
}

STDMETHODIMP_(LRESULT) CTriasExtension::GetCapabilities (UINT uiCap)
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
STDMETHODIMP CTriasExtension::SetXtensionSite (ITriasXtensionSite *pXtnSite)
{
	RELEASE(m_pXtnSite);		// alten Pointer freilassen
#if defined(_XTENSIONSITE_INTERFACE)
	RELEASE (m_pIServiceProvider);
#endif // _XTENSIONSITE_INTERFACE

	m_pXtnSite = pXtnSite;
	ADDREF(m_pXtnSite);		// neuen festhalten

#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != m_pXtnSite)		// evtl. Befehle über Interface absetzen
		m_pXtnSite -> QueryInterface (IID_ITRiASServiceProvider, (LPVOID *)&m_pIServiceProvider);
#endif // _XTENSIONSITE_INTERFACE

	return S_OK;
}


// Testet, ob ObjectProps installiert sind ------------------------------------
BOOL CTriasExtension::__TestObjProps (void)
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
BOOL CTriasExtension::__TestClassProps (void)
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
CTriasExtension::CTriasExtension (UINT uiMenuID, UINT uiORMenuID)
		 : m_uiMenuID(uiMenuID), m_uiORMenuID(uiORMenuID)
{
	m_dwRefCnt = 0L;
	m_pNotifProc = NULL;
	m_pUnk = NULL;
	m_pTXtsn = NULL;
	m_pXtnSite = NULL;
#if defined(_XTENSIONSITE_INTERFACE)
	m_pIServiceProvider = NULL;
#endif // _XTENSIONSITE_INTERFACE

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
BOOL CTriasExtension::__FInit (LPUNKNOWN lpUnk, DESTROYNOTIFYPROCPTR pProc)
{
	m_pNotifProc = pProc;
	m_pUnk = lpUnk;		// Controlling unknown

// ITriasXtension initialisieren
	m_pTXtsn = new CImpTriasXtension (lpUnk ? lpUnk : this, (CFakeMFCExtension *)this);
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
	g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC2"));
	g_pDexxExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXXEXTENSIONPROC"));
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, TEXT("DEXNOTIFICATIONPROCEX"));
	g_pDexDispatchProc = (DEXDISPATCHPROC)GetProcAddress (hTrias, TEXT("DEXDISPATCHPROC"));
#endif // __XT && __DEXPROCS

	if (QMSysAdmin & DEX_QueryMode())
		g_dwHookFlags |= TRIASMODE_GDO;

	return true;
}


CTriasExtension::~CTriasExtension (void) 
{
//// dann das Fenster freigeben
//	if (m_fAttached && ::IsWindow(m_pWnd -> m_hWnd)) {
//
//		if (g_dwHookFlags & TRIASMODE_SubClassTRiAS) {
//		HWND hWndOld = m_pWnd -> UnsubclassWindow();
//
//			ASSERT(hWndOld == hWnd());
//
//		CWinThread *pThread = AfxGetThread();
//
//			if (m_pWnd == pThread -> m_pMainWnd)
//				pThread -> m_pMainWnd = NULL;		// detach main frame from thread
//		
//			static_cast<CMainFrame *>(m_pWnd) -> OnNcDestroy();
//		}
//
//	// wenn kein hWnd mehr da ist, dann erfolgte bereits 'DELETE_OBJ this'
////		m_pWnd -> m_hWnd = NULL;
////		DELETE_OBJ m_pWnd; // -> DestroyWindow();
//		m_pWnd = NULL;
//	}
//
// erst jetzt alles andere aufräumen
	DELETE_OBJ (m_pLoadedMenu);
	DELETE_OBJ (m_pLoadedORMenu);

	DELETE_OBJ (m_pTXtsn);
	RELEASE (m_pXtnSite);			// TRiAS jetzt freigeben, wenn noch nicht geschehen
#if defined(_XTENSIONSITE_INTERFACE)
	RELEASE (m_pIServiceProvider);
#endif // _XTENSIONSITE_INTERFACE

	g_pDexExtensionProc = NULL;
	g_pDexExtensionProc2 = NULL;
	g_pDexxExtensionProc = NULL;
	g_pDexNotificationProc = NULL;
	g_pDexDispatchProc = NULL;

	g_pTE = NULL;					// keine Extension mehr vorhanden

// ObjektCount wieder runterzählen
	if (m_pNotifProc) (*m_pNotifProc)();
}


// Notifikationsbehandlung ----------------------------------------------------
LRESULT CTriasExtension::RegisterNotification (UINT wMsg, BOOL isLocal) 
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != m_pIServiceProvider)
		return LRESULT(m_pIServiceProvider -> DexDispatchProc (m_hWndM, __DexReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal)));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexDispatchProc)
		return (*g_pDexDispatchProc)(m_hWndM, __DexReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));

	ASSERT(::IsWindow(m_hWndM));
	return SendMessage (m_hWndM, __DexReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal)); 
}

LRESULT CTriasExtension::UnRegisterNotification (UINT wMsg, BOOL isLocal)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != m_pIServiceProvider)
		return LRESULT(m_pIServiceProvider -> DexDispatchProc (m_hWndM, __DexUnReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal)));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexDispatchProc)
		return (*g_pDexDispatchProc)(m_hWndM, __DexUnReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));

	ASSERT(::IsWindow(m_hWndM));
	return SendMessage (m_hWndM, __DexUnReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));
}

HWND CTriasExtension::GetActiveORWindow (void)
{
	return (HWND)DexExtensionProc((WPARAM)DEX_QUERYACTIVEORWINDOW, 0L);
}

UINT CTriasExtension::InstallMenuItem (
	UINT iMenuID, UINT iMenuStr, UINT iORMenu, short iPopupNum, short iMenuPos)
{
INSTALLMENUITEM imi;

	INITSTRUCT (imi, INSTALLMENUITEM);
	
CString RS; 

	if (0 != iMenuStr) {
		VERIFY(RS.LoadString (iMenuStr));
		imi.pMenuText = (char *)(const char *)RS;
	}
	imi.hDex = hDex();
	imi.iMenuID = iMenuID;
	imi.iFlag = iORMenu;
	imi.iMenuNum = iPopupNum;
	imi.iMenuPos = iMenuPos;

	DEX_InstallMenuItem (imi);
	return imi.iMenuID;		// neuen MenuID merken
}

void CTriasExtension::RemoveMenuItem (
	UINT iMenuID, UINT iORMenu, short iPopupNum, short iMenuPos)
{
REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = iMenuID;
	rmi.iMenuNum = iPopupNum;
	rmi.iFlag = iORMenu;
	rmi.iMenuPos = iMenuPos;
	DEX_RemoveMenuItem (rmi);
}

// Neues Hauptmenü unterschieben ----------------------------------------------
HMENU CTriasExtension::EmptyMenu (void)
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
HMENU CTriasExtension::EmptyORMenu (void)
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
short CTriasExtension::InstallTool (UINT rsc, const char *pDesc)
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

short CTriasExtension::InstallTool (const char *pRsc, const char *pDesc)
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

void CTriasExtension::RemoveTool (short iToolID)
{
	DEX_RemoveTool (iToolID);
}


#if !defined(_NOVERSION)

// WindowsVersion feststellen -------------------------------------------------
static bool s_fWin31 = false;
static bool s_fWin40 = false;
static bool s_fWin41 = false;
static bool s_fWin50 = false;
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
	s_fWin50 = false;

	if (dwVersion < ~0x7fffffff) {			// Windows NT
		s_fWinNT = true;
		if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) == 4) {
			s_fWin40 = true;	// NT4.0
			s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) > 4) {
			s_fWin50 = true;	// NT5.0
			s_fWin40 = true;
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

BOOL IsWin31 (void) { return s_fWin31; }
BOOL IsWin40 (void) { return s_fWin40; }
BOOL IsWin41 (void) { return s_fWin41; }
BOOL IsWin50 (void) { return s_fWin50; }
BOOL IsWin32s (void) { return s_fWin32s; }
BOOL IsWinNT (void) { return s_fWinNT; }

#endif // !_NOVERSION

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc (w, l));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	ASSERT(::IsWindow(__hWndM));

return::SendMessage (__hWndM, __DexCmd, w, l);
}
LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc2 (hPr, w, l));
#endif // _XTENSIONSITE_INTERFACE

	ASSERT(NULL != g_pDexExtensionProc2);
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	ASSERT(::IsWindow(__hWndM));
	return::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _DEBUG

LRESULT PASCAL DexxExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexxExtensionProc)
		return (*g_pDexxExtensionProc)(w, l);

	ASSERT(::IsWindow(__hWndM));

return::SendMessage (__hWndM, __DexxCmd, w, l);
}

LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexNotificationProc (w, l, FALSE));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	ASSERT(::IsWindow(__hWndM));
	return::SendMessage (__hWndM, __DexNotify, w, l);
}

LRESULT PASCAL DexPostNotificationProc (WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexNotificationProc (w, l, TRUE));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

	ASSERT(::IsWindow(__hWndM));
	return::PostMessage (__hWndM, __DexNotify, w, l);
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

///////////////////////////////////////////////////////////////////////////////
// Generieren des vollen Pfades einer CursorDatei
namespace {
	LPCSTR MakeCursorPath (LPCSTR pcCursor, LPSTR pBuffer, int iLen = _MAX_PATH)
	{
	CCurrentUser regDir (KEY_READ, _T("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Directories"));
	char cbCursorDir[_MAX_PATH];
	DWORD dwLen = _MAX_PATH;

		if (!regDir.GetSubSZ (_T("Cursors"), cbCursorDir, dwLen))
			return NULL;

	CCurrentUser regCursors (KEY_READ, _T("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Cursors"));
	char cbBuff[_MAX_PATH];

		dwLen = _MAX_PATH;
		if (!regCursors.GetSubSZ (pcCursor, cbBuff, dwLen))
			return NULL;

		dwLen = ::SearchPath (cbCursorDir, cbBuff, NULL, iLen, pBuffer, NULL);
		if (0 == dwLen) return NULL;

		return pBuffer;
	}
	inline HCURSOR LoadCursorFromPath(LPCSTR pcName)
	{
	LPCSTR pcCursorPath = MakeCursorPath (pcName, (LPSTR)_alloca(_MAX_PATH));

		if (NULL != pcCursorPath)
			return ::LoadCursorFromFile(pcCursorPath);
		return NULL;		
	}
	inline int IndexFromANICURSOR (int rgType)
	{
		ASSERT(rgType > 0);
		return rgType-1;
	}
	inline int Sign (int iCode)
	{
		return (0 == iCode) ? 0 : ((iCode > 0) ? 1 : -1);
	}
	inline int Value (int rgCode)
	{
		return (0 == rgCode) ? 0 : ((rgCode > 0) ? IndexFromANICURSOR(rgCode) : IndexFromANICURSOR(-rgCode));
	}
} // namespace

BOOL CThisDLL::InitInstance (void)
{
	g_hInstance = m_hInstance;
//	GetCtrlManager().InstallHook (-1, FALSE);

	SetRegistryKey (_T("TRiAS"));

// WaitCursor initialisieren
	m_hAniCursors[IndexFromANICURSOR(ANICURSOR_WAIT)] = LoadCursorFromPath(_T("Wait"));
	m_hAniCursors[IndexFromANICURSOR(ANICURSOR_LOAD)] = LoadCursorFromPath(_T("Load"));
	m_hAniCursors[IndexFromANICURSOR(ANICURSOR_SAVE)] = LoadCursorFromPath(_T("Save"));
	m_hAniCursors[IndexFromANICURSOR(ANICURSOR_PRINT)] = LoadCursorFromPath(_T("Print"));
	return true;
}

int CThisDLL::ExitInstance (void)
{
	if (GetCtrlManager().IsHooked())
		GetCtrlManager().UninstallHook();

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

void CThisDLL::DoWaitCursor(int nCode)
{
int iMode = Sign(nCode);
int iAbs = Value(nCode);

	ASSERT(iAbs >= 0 && iAbs < ANICURSOR_MAX);
	if (NULL == m_hAniCursors[iAbs]) 
		CWinApp::DoWaitCursor(iMode);
	else {
	// 0 => restore, 1=> begin, -1=> end
		ASSERT(m_hAniCursors[iAbs] != NULL);

#pragma TODO("DoWaitCursor threadsicher machen!")

		m_nWaitCursorCount += iMode;
		if (m_nWaitCursorCount > 0)
		{
		HCURSOR hcurPrev = ::SetCursor(m_hAniCursors[iAbs]);

			if (nCode > 0 && m_nWaitCursorCount == 1)
				m_hcurWaitCursorRestore = hcurPrev;
		} else {
		// turn everything off
			m_nWaitCursorCount = 0;     // prevent underflow
			::SetCursor(m_hcurWaitCursorRestore);
		}
	}
}

void GlobalUnlockAndFree(HGLOBAL hGlobal)
{
	if (hGlobal == NULL)
		return;

	// avoid bogus warning error messages from various debugging tools
	ASSERT(GlobalFlags(hGlobal) != GMEM_INVALID_HANDLE);
	UINT nCount = GlobalFlags(hGlobal) & GMEM_LOCKCOUNT;
	while (nCount--)
		GlobalUnlock(hGlobal);

	// finally, really free the handle
	GlobalFree(hGlobal);
}

// Printersupport
BOOL CThisDLL::UpdatePrinterSelection(DVTARGETDEVICE *pdvt)
{
// alles bisherige freigeben ...
	if (m_hDevMode != NULL)
		GlobalUnlockAndFree(m_hDevMode);
	if (m_hDevNames != NULL)
		GlobalUnlockAndFree(m_hDevNames);
	m_hDevMode = NULL;
	m_hDevNames = NULL;

// ... und aus der DVTARGETDEVICE-Struktur wieder zusammenbauen

// neuen Speicher anfordern und Daten reinkopieren
// DEVNAMES kopieren
UINT nMaxOffset = max(pdvt->tdDriverNameOffset, pdvt->tdDeviceNameOffset);
	
	nMaxOffset = max((UINT)pdvt->tdPortNameOffset, nMaxOffset);

DWORD dwDevNamesSize = (DWORD)(nMaxOffset + lstrlen((LPTSTR)pdvt+nMaxOffset)+1);

	m_hDevNames = GlobalAlloc (GHND, dwDevNamesSize);
	if (NULL == m_hDevNames)
		return FALSE;

LPDEVNAMES pNewDN = (LPDEVNAMES)GlobalLock (m_hDevNames);	

	if (NULL == pNewDN) {
		GlobalFree (m_hDevNames);
		m_hDevNames = NULL;
		return FALSE;
	}
	memcpy (pNewDN, (DEVNAMES *)&pdvt->tdDriverNameOffset, dwDevNamesSize);
	pNewDN -> wDriverOffset -= sizeof(DWORD);
	pNewDN -> wDeviceOffset -= sizeof(DWORD);
	pNewDN -> wOutputOffset -= sizeof(DWORD);
	pNewDN -> wDefault = 0;
	GlobalUnlock (m_hDevNames);

// evtl. DEVMODE kopieren
    if (0 != pdvt -> tdExtDevmodeOffset) {
	LPDEVMODE pDevMode = (LPDEVMODE)((LPSTR)pdvt + pdvt->tdExtDevmodeOffset);
	DWORD dwDevModeSize = (DWORD) (pDevMode->dmSize + pDevMode->dmDriverExtra);

		m_hDevMode = GlobalAlloc (GHND, dwDevModeSize);
		if (NULL == m_hDevMode)
			return FALSE;

	LPSTR pNewDM = (LPSTR)GlobalLock (m_hDevMode);	

		if (NULL == pNewDM) {
			GlobalFree (m_hDevMode);
			m_hDevMode = NULL;
			return FALSE;
		}
		memcpy (pNewDM, pDevMode, dwDevModeSize);
		GlobalUnlock (m_hDevMode);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// Stuff for MFC-DLL 
CThisDLL MyExtensionDLL (NULL); // ==>> Titel in AFX_IDS_APP_TITLE !!

///////////////////////////////////////////////////////////////////////////////
//
int __cdecl VMessageBox (CWnd *pWnd, UINT uiCaption, UINT rgType, UINT uiText, ...)
{
	TRY {
	CString strCaption; strCaption.LoadString (uiCaption);
	CString strFormat; strFormat.LoadString (uiText);
	TCHAR cbOut[2*_MAX_PATH];
	va_list params;

		va_start (params, uiText);
		wvsprintf (cbOut, strFormat, params);
		va_end (params);

		return pWnd -> MessageBox (cbOut, strCaption, rgType);

	} CATCH (CMemoryException, e) {
		return 0;
	} END_CATCH;
}

int __cdecl VMessageBox (CWnd *pWnd, LPCSTR pcCaption, UINT rgType, UINT uiText, ...)
{
	TRY {
	CString strFormat; strFormat.LoadString (uiText);
	TCHAR cbOut[2*_MAX_PATH];
	va_list params;

		va_start (params, uiText);
		wvsprintf (cbOut, strFormat, params);
		va_end (params);

		return pWnd -> MessageBox (cbOut, pcCaption, rgType);

	} CATCH (CMemoryException, e) {
		return 0;
	} END_CATCH;
}

string FakeTRiASName (UINT resID, ...)
{
	TRY {
	CString resTempl; resTempl.LoadString (resID);
	TCHAR cbOut[_MAX_PATH];
	va_list params;

		va_start (params, resID);
		wvsprintf (cbOut, resTempl, params);
		va_end (params);

		return string(cbOut);
	
	} CATCH (CMemoryException, e) {
	// irgendein Fehler
		return string(g_cbNil);
	} END_CATCH;
}

string FakeTRiASName (LPCSTR pcTempl, ...)
{
	TRY {
	va_list params;
	TCHAR cbOut[_MAX_PATH];

		va_start (params, pcTempl);
		wvsprintf (cbOut, pcTempl, params);
		va_end (params);

		return string(cbOut);
	
	} CATCH (CMemoryException, e) {
	// irgendein Fehler
		return string(g_cbNil);
	} END_CATCH;
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
