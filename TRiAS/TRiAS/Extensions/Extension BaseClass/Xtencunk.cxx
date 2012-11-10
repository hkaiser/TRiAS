// Routinen fuer Klasse CTriasExtension ---------------------------------------
// File: XTENCUNK.CXX

#include "xtensnp.hxx"
#include "impxtcf.hxx"

#include <registrx.hxx>
#include <xtsnguid.h>
#if defined(WIN32)
#include <olectl.h>			// IID_IClassFactory2
#else
#include <olectlid.h>		// IID_IClassFactory2
#endif // WIN32
#include <fnamestr.h>

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(WIN32)
CComModule _Module;			// Main module for ATL
#endif

extern LONG g_cObj;			// Anzahl der aktiven Objekte
extern LONG g_cLock;		// Anzahl der externen Locks

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

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
extern "C" DEXEXTENSIONPROC g_pDexxExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
extern "C" DEXDISPATCHPROC g_pDexDispatchProc = NULL;
#endif // __XT && __DEXPROCS

#if !defined(_NOVERSION)
static void PreCalcVersion (void);
#endif // _NOVERSION

extern "C" TCHAR FAR g_pDLLName[_MAX_PATH] = "";
extern "C" HINSTANCE g_hInstance = 0;

#if defined(_DEBUG)
extern "C" bool g_fGlobalLic = false;
#endif // defined(_DEBUG)

#if _TRiAS_VER < 0x0400
DWORD g_dwVer4 = 0;		// Versionskontrolle
#endif // _TRiAS_VER < 0x0400

#if defined(__MFC__)
#undef TX_ASSERT
#define TX_ASSERT(x) ASSERT(x)
#endif

#if defined(_XTENSIONSITE_INTERFACE)
EXTERN_C const IID IID_ITRiASServiceProvider;
#endif // _XTENSIONSITE_INTERFACE

#if !defined(WIN32)
#if defined(__CV__)	// nicht für MFC
/*
 * LibMain
 *
 * Purpose:
 *  DLL-specific entry point called from LibEntry.
 *
 * Parameters:
 *  hInst           HINSTANCE instance of the DLL.
 *  wDataSeg        WORD segment selector of the DLL's data segment.
 *  wHeapSize       WORD byte count of the heap.
 *  lpCmdLine       LPSTR to command line used to start the module.
 *
 * Return Value:
 *  HANDLE          Instance handle of the DLL.
 *
 */
extern "C" HINSTANCE PASCAL LibMain (HINSTANCE hInst, WORD, 
			   	     WORD cbHeapSize, LPSTR)
{
	if (cbHeapSize != NULL)
		UnlockData(0);

	GetModuleFileName (hInst, g_pDLLName, _MAX_PATH);
	g_hInstance = hInst;

return hInst;
}


/*
 * _WEP
 *
 * Purpose:
 *  Required DLL Exit function.  Does nothing.
 *
 * Parameters:
 *  bSystemExit     bool indicating if the system is being shut
 *                  down or the DLL has just been unloaded.
 *
 * Return Value:
 *  void
 *
 */
extern "C" void FAR PASCAL _WEP(int /*bSystemExit*/)
{
	// nothing to do here
}

#endif // __CV__

#else	// WIN32

///////////////////////////////////////////////////////////////////////////////
char g_cbHelpPath[_MAX_PATH];		// Pfad zum Helpverzeichnis

//#if _MSC_VER < 1000 || defined(__CV__)

#if !defined(__CV__)
static AFX_EXTENSION_MODULE TRiASExtension = { NULL, NULL };
#endif

#if !defined(__CV__)

#if _MSC_VER < 1000
extern void AFXAPI _AfxSetCurrentModuleTlsIndex(DWORD);
extern AFX_MODULE_STATE* AFXAPI AfxPushModuleContext(AFX_MODULE_STATE* psIn);
extern void AFXAPI AfxPopModuleContext(AFX_MODULE_STATE* psIn, BOOL bCopy = FALSE);

#define NULL_TLS ((DWORD)-1)
#else
void AFXAPI AfxLockGlobals(int nLockType);
void AFXAPI AfxUnlockGlobals(int nLockType);
#define CRIT_OBJECTFACTORYLIST  13
#endif // _MSC_VER

#endif // !__CV__

//#if !defined(__CV__) //&& _MSC_VER < 1000

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

BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
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
				return E_OUTOFMEMORY;
			pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);
			strcpy (g_pDLLName, OLE2A(pszModule));
			g_hInstance = hInst;

			{	// HelpPfad generieren
			char cbDrive[_MAX_DRIVE];
			char cbPath[_MAX_PATH];

				_splitpath (g_pDLLName, cbDrive, cbPath, NULL, NULL);
				_makepath (g_cbHelpPath, cbDrive, cbPath, "", "");
			}

#if defined(WIN32)
			_Module.Init (GetObjectMap(), g_hInstance);
#endif // WIN32
#if !defined(__CV__)
			{
			// NOTE: Important call to _AfxSetCurrentModuleTlsIndex.
	//			_AfxSetCurrentModuleTlsIndex (NULL_TLS);
			bool fReturn = false;
			CDynLinkLibrary *pDLL = NULL;
			CWinApp *pApp = NULL;
			bool bRegister = !TRiASExtension.bInitialized;

			// Call DisableThreadLibraryCalls if available.
				DisableThreadLibraryCalls (hInst);

			// Shared initialization.
				if (!AfxInitExtensionModule (TRiASExtension, hInst)) {
					TRACE1("Could not init ExtensionModule %s\r\n", g_pDLLName);
					return false;   // failure
				}

			// Wire up this DLL into the resource chain.
			// (In the Win32 version it is OK to create this in DllMain.)
				pDLL = new CDynLinkLibrary (TRiASExtension);
				if (pDLL == NULL) {
					TRACE1("Out of memory in DLLInit of %s\r\n", g_pDLLName);
					return false;   // failure
				}
			
				pDLL -> m_bSystem = true;

	  		// Extension DLL one-time initialization
			// TRiAS ist erste ResourceQuelle
			HMODULE hTrias = GetModuleHandle (NULL);

				AfxSetResourceHandle (hTrias);
	//			afxCurrentInstanceHandle = hTrias;
				fReturn = true;

	//Cleanup:
				if (!fReturn) return false;

#if _MSC_VER >= 1000
			// Register class factories in context of private module state
			bool bResult = true;

				if (bRegister) {
				// register this DLL's factories
					AfxLockGlobals(CRIT_OBJECTFACTORYLIST);
					for (COleObjectFactory *pFactory = pDLL->m_factoryList;
						 pFactory != NULL; pFactory = pFactory->m_pNextFactory)
					{
						// register any non-registered, non-doctemplate factories
						if (!pFactory->IsRegistered() &&
							pFactory->GetClassID() != CLSID_NULL && !pFactory->Register())
						{
							TRACE1("Could not init classFactory in %s\r\n", g_pDLLName);
							bResult = false;
						}
					}
					AfxUnlockGlobals(CRIT_OBJECTFACTORYLIST);
				}
				if (!bResult)
					return false;
#endif // _MFC_VER
			}
#else
			// Call DisableThreadLibraryCalls if available.
				DisableThreadLibraryCalls (hInst);
#endif // __CV__
#if defined(_DEBUG)
			{
			// globale Lizensierung überprüfen
			CCurrentUser reg (KEY_READ, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config"));
			DWORD dwLic = 0;

				reg.GetDWORD (TEXT("GlobalLicense"), dwLic);
				g_fGlobalLic = dwLic ? true : false;
			}
#endif // defined(_DEBUG
#if _TRiAS_VER < 0x0400
			{
			CCurrentUser reg (KEY_READ, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config"));

				g_dwVer4 = 0;
				reg.GetDWORD (TEXT("FakeTRiAS4"), g_dwVer4);
			}
#endif // _TRiAS_VER < 0x0400
			{	// Entrypoints bereits hier besorgen, damit DEX_...Messages auch 
				// verfügbar sind, wenn Erweiterung nicht geladen ist.
#if defined(__XT) && defined(__DEXPROCS)
// externe EntryPoints von Trias finden
#if !defined(WIN32)
			HMODULE hTrias = NULL;
#else
			HMODULE hTrias = GetModuleHandle (NULL);
#endif
				g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC"));
				g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC2"));
				g_pDexxExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXXEXTENSIONPROC"));
				g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, TEXT("DEXNOTIFICATIONPROCEX"));
				g_pDexDispatchProc = (DEXDISPATCHPROC)GetProcAddress (hTrias, TEXT("DEXDISPATCHPROC"));
#endif // __XT && __DEXPROCS
			}
		}
		return true;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		{
#if !defined(__CV__)
			AfxTermExtensionModule (TRiASExtension);
#endif // __CV__
			_Module.Term();

#if defined(_DEBUG)
		string strName = g_pDLLName;
		string str = get_name(strName)+get_ext(strName);

#if defined(__CV__)
			TX_TRACE1(TEXT("%s: exiting:\r\n"), str.c_str());
			if (g_cObj != 0) TX_TRACE1(TEXT("\tInfo: Global object count: %ld\r\n"), g_cObj);
			if (g_cLock != 0) TX_TRACE1(TEXT("\tInfo: Global lock count: %ld\r\n"), g_cLock);
			if (_Module.GetLockCount() != 0) TX_TRACE1(TEXT("\tInfo: Global ATL lock count: %ld\r\n"), _Module.GetLockCount());
#else
			TRACE1(TEXT("%s: exiting:\r\n"), str.c_str());
			if (g_cObj != 0) TRACE1(TEXT("\tInfo: Global object count: %ld\r\n"), g_cObj);
			if (g_cLock != 0) TRACE1(TEXT("\tInfo: Global lock count: %ld\r\n"), g_cLock);
			if (_Module.GetLockCount() != 0) TRACE1(TEXT("\tInfo: Global ATL lock count: %ld\r\n"), _Module.GetLockCount());
			
			TRACE0(TEXT("\t"));

		HRESULT hr = AfxDllCanUnloadNow();

			if (S_OK != hr)
				TRACE1(TEXT("Info: AfxDllCanUnloadNow returns: 0x%lx\r\n"), hr);
#endif // !__CV__
#endif // _DEBUG
		// sollten jetzt nicht mehr benötigt werden
			g_pDexExtensionProc = NULL;
			g_pDexExtensionProc2 = NULL;
			g_pDexxExtensionProc = NULL;
			g_pDexNotificationProc = NULL;
			g_pDexDispatchProc = NULL;
		}
		break;
	}

return true;
}
//#endif // !__CV_ || _MSC_VER < 1000

#endif	// WIN32

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
HRESULT _XTENSN_EXPORT FAR PASCAL DllGetClassObject (
				REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv)
{
HRESULT hr = NOERROR;

#if !defined(__CV__) && defined(WIN32)
// zuerst MFC interne Abfragen
	AFX_MANAGE_STATE(AfxGetModuleState());

	hr = AfxDllGetClassObject (rclsid, riid, ppv);
	if (SUCCEEDED(hr)) return S_OK;
#endif // !__CV__

#if defined(WIN32)
// danach ATL fragen
	hr = _Module.GetClassObject(rclsid, riid, ppv);
	if (SUCCEEDED(hr)) return S_OK;
#endif // WIN32

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
	if (*ppv == NULL)
		return ResultFromScode(E_OUTOFMEMORY);

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
HRESULT _XTENSN_EXPORT PASCAL DllCanUnloadNow(void)
{
// Our answer is whether there are any object or locks
	if (g_cObj != 0L || g_cLock != 0)
		return S_FALSE;

#if defined(WIN32)
// ATL befragen
	if (_Module.GetLockCount() > 0)
		return S_FALSE;
#endif // WIN32
#if !defined(__CV__) && defined(WIN32)
// MFC befragen
	AFX_MANAGE_STATE(AfxGetModuleState());
	if (S_FALSE == AfxDllCanUnloadNow()) 
		return S_FALSE;
#endif // !__CV__

	return S_OK;	// darf entladen werden
}


// DllRegisterServer - Adds entries to the system registry --------------------
STDAPI _XTENSN_EXPORT DllRegisterServer (void)
{
BOOL fAmIAdmin = AmIAdministrator();

#if !defined(__CV__) && defined(WIN32)
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetModuleState());
	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE) && fAmIAdmin)
		return SELFREG_E_CLASS;
#endif // !__CV__
#if defined(WIN32)
// ATL nicht vergessen
#if defined(__ATL_11_USED__) || defined(__ATL_20_USED__) || defined(__ATL_70_USED__)
	if (FAILED(_Module.RegisterServer(false)) && fAmIAdmin)		// Typelib wird separat registriert
		return SELFREG_E_CLASS;
#else
	if (FAILED(_Module.UpdateRegistry(true)) && fAmIAdmin)
		return SELFREG_E_CLASS;
#endif // __ATL_11_USED__
#endif // WIN32

// abfragen und registrieren der TypeLibrary
GUID _tlid;
static TCHAR cbBuffer[_MAX_PATH];
bool fName = GetTypeLibName (cbBuffer);		// evtl. Namen holen

	if (GetTypeLibGUID (_tlid) && 
	    !ExtOleRegisterTypeLib (g_hInstance, _tlid, fName ? cbBuffer : NULL) &&
	    fAmIAdmin)
	{
		return ResultFromScode(SELFREG_E_TYPELIB);
	}

	if (!UpdateRegistry (true) && fAmIAdmin)
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


// DllUnregisterServer - Removes entries from the system registry -------------
STDAPI _XTENSN_EXPORT DllUnregisterServer (void)
{
BOOL fAmIAdmin = AmIAdministrator();

#if !defined(__CV__) && defined(WIN32)
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetModuleState());
	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE) && fAmIAdmin)
		return SELFREG_E_CLASS;
#endif // !__CV__
#if defined(WIN32)
// ATL nicht vergessen
#if defined(__ATL_11_USED__) || defined(__ATL_20_USED__) || defined(__ATL_70_USED__)
	if (FAILED(_Module.UnregisterServer()) && fAmIAdmin)
		return SELFREG_E_CLASS;
#else
	if (FAILED(_Module.UpdateRegistry(false)) && fAmIAdmin)
		return SELFREG_E_CLASS;
#endif // __ATL_11_USED__
#endif // WIN32

GUID _tlid;

	if (GetTypeLibGUID (_tlid) && !ExtOleUnregisterTypeLib (_tlid) && fAmIAdmin)
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!UpdateRegistry (false) && fAmIAdmin)
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
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

// *** ITriasXtension specific functions *** ----------------------------------
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
	if ((m_pWnd = CWnd::FromHandlePermanent (hWnd)) == NULL) {
	// wir sind die ersten
		m_pWnd = new CWnd();
		if (m_pWnd == NULL) return NULL;
		m_pWnd -> Attach (hWnd);	// trägt hWnd in CWndMap ein
		m_fAttached = true;
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
#if defined(WIN32) && defined(__CV__)
	RegisterNotification (DEX_ISCLOSEDPROJECT);
#endif 
	m_iMode = iMode;
	m_fLoaded = true;
	return true;
}

STDMETHODIMP_(BOOL) CTriasExtension::UnLoadExtension (void)
{
	RELEASE (m_pXtnSite);	// TRiAS jetzt freigeben
	m_fLoaded = false;
#if defined(WIN32) && defined(__CV__)
	UnRegisterNotification (DEX_ISCLOSEDPROJECT);
	m_pViewWnd = NULL;
#endif

return true;
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
#if defined(WIN32) && defined(__CV__)
	if (wParam == DEX_ISCLOSEDPROJECT)
		m_pViewWnd = NULL;
#endif // WIN32)

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
	ADDREF(m_pXtnSite);			// neuen festhalten

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

#if defined(__CV__)
	m_pRF = NULL;
	m_pMainWnd = NULL;
#if defined(WIN32)
	m_pViewWnd = NULL;
#endif // WIN32
#else // __CV__
#if !defined(WIN32)
	AfxSetResourceHandle (g_hInstance);
#endif // WIN32
	m_pWnd = NULL;
	m_fAttached = false;
#endif	// __CV__

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
	m_pTXtsn = new CImpTriasXtension (lpUnk ? lpUnk : this, this);
	if (NULL == m_pTXtsn) return false;

// Daten dieser Extension initialisieren
char cbBuffer[DEX_MENUNAMELEN];

#if defined(__CV__)
	m_pRF = new ResourceFile (g_pDLLName);
	if (m_pRF == NULL) return false;

// evtl. HauptMenu aufbauen
	if (m_uiMenuID) {
		m_pLoadedMenu = new Menu (ResID (m_uiMenuID, m_pRF));
		if (m_pLoadedMenu == NULL) return false;

	// PopUpMenu und MenuText holen
	HMENU hMenu = m_pLoadedMenu -> Handle (API_MENU_HMENU);

		m_hPopUpMenu = GetSubMenu (hMenu, 0);
		GetMenuString (hMenu, 0, cbBuffer, DEX_MENUNAMELEN, MF_BYPOSITION);
		m_strMenuEntry = cbBuffer;
	} 
	if (m_uiORMenuID) {
		m_pLoadedORMenu = new Menu (ResID (m_uiORMenuID, m_pRF));
		if (m_pLoadedORMenu == NULL) return false;	

	// PopUpMenu und MenuText holen
	HMENU hMenu = m_pLoadedORMenu -> Handle (API_MENU_HMENU);

		m_hPopUpORMenu = GetSubMenu (hMenu, 0);
		GetMenuString (hMenu, 0, cbBuffer, DEX_MENUNAMELEN, MF_BYPOSITION);
		m_strORMenuEntry = cbBuffer;
	} 
#else // __CV__
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
#endif // __CV__

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
	return true;
}


CTriasExtension::~CTriasExtension (void) 
{
	DELETE_OBJ (m_pLoadedMenu);
	DELETE_OBJ (m_pLoadedORMenu);
#if defined(__CV__)
	DELETE_OBJ (m_pRF);
#else
	if (m_pWnd && m_fAttached) {		// nur zerlegen, wenn neu erzeugt
		m_pWnd -> m_hWnd = NULL;
		delete m_pWnd;
	}
#endif // !__CV__

	DELETE_OBJ (m_pTXtsn);
	RELEASE (m_pXtnSite);				// TRiAS jetzt freigeben, wenn noch nicht geschehen
#if defined(_XTENSIONSITE_INTERFACE)
	RELEASE (m_pIServiceProvider);
#endif // _XTENSIONSITE_INTERFACE

	if (m_pNotifProc) (*m_pNotifProc)();
	
	if (this == g_pTE) 
		g_pTE = NULL;		// keine Extension mehr vorhanden
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

	TX_ASSERT(::IsWindow(m_hWndM));
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

	TX_ASSERT(::IsWindow(m_hWndM));
	return SendMessage (m_hWndM, __DexUnReg, (WPARAM)m_hDex, MAKELONG (wMsg, isLocal));
}

HWND CTriasExtension::GetActiveORWindow (void)
{
	return (HWND)DexExtensionProc((WPARAM)DEX_QUERYACTIVEORWINDOW, 0L);
}

#if _MSC_VER <= 1020
UINT CTriasExtension::InstallMenuItem (UINT iMenuID, UINT iMenuStr, 
					bool iORMenu, short iPopupNum, short iMenuPos)
#else
UINT CTriasExtension::InstallMenuItem (UINT iMenuID, UINT iMenuStr, 
					UINT iORMenu, short iPopupNum, short iMenuPos)
#endif _MSC_VER <= 1020
{
INSTALLMENUITEM imi;

	INITSTRUCT (imi, INSTALLMENUITEM);
	
#if defined(__CV__)
ResString RS (ResID (iMenuStr, &RF()), 50);

	if (0 != iMenuStr) 
		imi.pMenuText = (char *)(const char *)RS;
#else
CString RS; 

	if (0 != iMenuStr) {
		RS.LoadString (iMenuStr);
		imi.pMenuText = (char *)(const char *)RS;
	}
#endif

	imi.hDex = hDex();
	imi.iMenuID = iMenuID;
	imi.iFlag = iORMenu;
	imi.iMenuNum = iPopupNum;
	imi.iMenuPos = iMenuPos;

	DEX_InstallMenuItem (imi);
	return imi.iMenuID;		// neuen MenuID merken
}

#if _MSC_VER <= 1020
void CTriasExtension::RemoveMenuItem (UINT iMenuID, bool iORMenu, short iPopupNum)
#else
void CTriasExtension::RemoveMenuItem (UINT iMenuID, UINT iORMenu, short iPopupNum, short iMenuPos)
#endif // _MSC_VER <= 1020
{
REMOVEMENUITEMEX rmi;

	rmi.dwSize = sizeof(REMOVEMENUITEMEX);
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
#if defined(__CV__)

short CTriasExtension::InstallTool (ResID rsc, LPCTSTR pDesc)
{
	if (rsc.Handle() == 0) return -1;

// Laden der Bitmap 
HBITMAP hBmp;

	if ((uint)rsc) hBmp = LoadBitmap (rsc.Handle(), MAKEINTRESOURCE((uint)rsc));
	else	       hBmp = LoadBitmap (rsc.Handle(), (const char *)rsc);

INSTALLTOOL IT;

	memset (&IT, '\0', sizeof(INSTALLTOOL));
	IT.dwSize = sizeof (INSTALLTOOL);
	IT.hBmp = hBmp;
	IT.pDesc = (char *)pDesc;

// die Bitmap gehört ab jetzt vollständig TRIAS !

return DEX_InstallTool (IT);
}

#else // __CV__

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
#endif // __CV__

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

#if defined(WIN32)
	if (dwVersion < ~0x7fffffff) {			// Windows NT
		s_fWinNT = true;
		if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion))== 4) {
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
			s_fWin41 = true;	// 4.10
		s_fWin31 = true;
		s_fWin40 = true;
	}
#else
	if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
	    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
		s_fWin31 = true;
#endif
}

BOOL IsWin31 (void) { return s_fWin31; }
BOOL IsWin40 (void) { return s_fWin40; }
BOOL IsWin41 (void) { return s_fWin41; }
BOOL IsWin50 (void) { return s_fWin50; }
BOOL IsWin32s (void) { return s_fWin32s; }
BOOL IsWinNT (void) { return s_fWinNT; }

#endif // !_NOVERSION

#if defined(__XT) && defined(__DEXPROCS)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
#if defined(_DEBUG)	// ansonsten inline
LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc (w, l));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	TX_ASSERT(::IsWindow(__hWndM));

return::SendMessage (__hWndM, __DexCmd, w, l);
}
LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc2 (hPr, w, l));
#endif // _XTENSIONSITE_INTERFACE

	TX_ASSERT(NULL != g_pDexExtensionProc2);
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	TX_ASSERT(::IsWindow(__hWndM));
	return::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _DEBUG

LRESULT PASCAL DexxExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexxExtensionProc)
		return (*g_pDexxExtensionProc)(w, l);

	TX_ASSERT(::IsWindow(__hWndM));
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

	TX_ASSERT(::IsWindow(__hWndM));
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

	TX_ASSERT(::IsWindow(__hWndM));
	return::PostMessage (__hWndM, __DexNotify, w, l);
}
#endif // __XT && __DEXPROCS

///////////////////////////////////////////////////////////////////////////////
// Globale Funktionen
#if defined(_DEBUG) // ansonsten inline
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

HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew)
{
	if (NULL == pulIdent) return E_POINTER;

IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = pcClass;
	IFC.fCreateNew = fCreateNew;

HRESULT hr = DEX_GetIdentFromClass(IFC);

	if (SUCCEEDED(hr)) 
		*pulIdent = IFC.ulIdent;

	return hr;
}
#if _MSC_VER >= 1100
HRESULT ClassFromIdentX (HPROJECT hPr, ULONG ulIdent, char *pBuffer, int iBuffLen)
{
CLASSFROMIDENT CFI;

	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdentEx(hPr, CFI);
}

HRESULT IdentFromClassX (HPROJECT hPr, LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew)
{
	if (NULL == pulIdent) return E_POINTER;

IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = pcClass;
	IFC.fCreateNew = fCreateNew;

HRESULT hr = DEX_GetIdentFromClassEx(hPr, IFC);

	if (SUCCEEDED(hr)) 
		*pulIdent = IFC.ulIdent;

	return hr;
}
#endif // _MSC_VER >= 1100
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Code, der spezifisch für die Klassenbibliotheken ist 
#if defined(__CV__)

pWindow CTriasExtension::MWind (void) 
{
	if (m_pMainWnd == NULL)
		m_pMainWnd = (pWindow)DexxExtensionProc((WPARAM)DEXX_MAINWINDOW, 0L);

	TX_ASSERT(NULL != m_pMainWnd);
	return m_pMainWnd;
}

pWindow CTriasExtension::ORWind (HWND hWnd)
{
	return (pWindow)DexxExtensionProc((WPARAM)DEXX_ORWINDOW, (LPARAM)(void *)hWnd);
}

#if defined(WIN32)
pWindow CTriasExtension::MVWind (void) 
{
	if (m_pViewWnd == NULL) {
	// Testen, ob überhaupt ein Projekt geöffnet ist
		if (!DEX_TestActiveProject())
			return NULL;	// no project, no fun
		
		m_pViewWnd = (pWindow)DexxExtensionProc((WPARAM)DEX_QUERYACTIVEVIEWWINDOW, 0L);
	}

	TX_ASSERT(NULL != m_pViewWnd);
	return m_pViewWnd;
}

int CallAppExec (ExecType et);

int	App::Exec	(ExecType et)
{
	return CallAppExec (et);
}
#endif // WIN32

#else // __CV__

/////////////////////////////////////////////////////////////////////////////

#if !defined(WIN16)
/*
// Library init -- wird von der MFC gerufen
bool CExtDLL::InitInstance (void)
{
	GetModuleFileName (m_hInstance, g_pDLLName, _MAX_PATH);
	g_hInstance = m_hInstance;

// TRiAS ist erste ResourceQuelle
HMODULE hTrias = GetModuleHandle (TRIAS_MODULENAME);

	AfxSetResourceHandle (hTrias);
	afxCurrentInstanceHandle = hTrias;

// als MFC-Extension eintragen
AFX_MODULE_STATE *pState = AfxGetModuleState();

	pState -> m_bSystem = true;

AFX_MODULE_PROCESS_STATE *pMState = AfxGetModuleProcessState();
CDynLinkLibrary *pDLL = pMState -> m_libraryList.GetHead();

	pDLL -> m_bSystem = true;

return true;
}

int CExtDLL::ExitInstance (void)
{
// any DLL termination goes here (WEP-like code)
	return CWinApp::ExitInstance();
}
*/

#else

// Library init -- wird von der MFC gerufen
bool CExtDLL::InitInstance (void)
{
// any DLL initialization goes here
//	SetDialogBkColor();     // grey dialogs in the DLL as well
	GetModuleFileName (m_hInstance, g_pDLLName, _MAX_PATH);
	g_hInstance = m_hInstance;

	return CWinApp::InitInstance();
}

int CExtDLL::ExitInstance (void)
{
// any DLL termination goes here (WEP-like code)
	return CWinApp::ExitInstance();
}

#endif // WIN16

#endif // __CV__
