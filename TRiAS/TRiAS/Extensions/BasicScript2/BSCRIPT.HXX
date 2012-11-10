// Macroverwaltung
// File: BSCRIPT.HXX

#if !defined(_BSCRIPT_HXX)
#define _BSCRIPT_HXX

#include "AniTrayIcon.h"

///////////////////////////////////////////////////////////////////////////////
// 
#define MAXSTRLENGTH 255

class CRunScripts;
class CRunningObjectsHelper;
class CSplit;
class CObjectProperties;
class CRunErr;

struct IObjectManagement;
struct IStreamInfo;

EXTERN_C const GUID CLSID_MacroScriptExtension;
EXTERN_C const GUID IID_IExtendBScript;

class CMacroScriptExtension : 
	public CTriasExtension,
	public CObjectProperties,
	public IExtendBScript,
	public CComCoClass<CMacroScriptExtension, &CLSID_MacroScriptExtension>
{
private:
	CebInstance *			m_pebInst;
	CSplit				*	m_pSplitterDebugger;
	CRunErr				*	m_pRunErr;
	CRunningObjectsHelper *	m_pRunningObjHelper;
	HINSTANCE m_hDCInst;
	BOOL					m_fProjectIsClosing;
	CExtendModules			m_Modules;
	LPSTORAGE				m_lpDummyStorage;

// tray icon support
	CAnimatedTrayIcon *m_pTrayIcons;
	LONG m_lCountRunning;
	static UINT m_uiTrayMsg;
	static UINT m_uiCreateTrayMsg;

	LRESULT HandleTrayMessages (UINT wMsg, WPARAM wParam, LPARAM lParam);

public:
	HRESULT InitMacroTrayIcons(bool fForcereload = false);
	HRESULT RemoveMacroTrayIcons();

private:
	void ResetExtension(void);

	BOOL MacroScriptCallForFrame(LPCSTR lpcstr = NULL, BOOL fOpenFile = false);
	BOOL MacroScriptCall(void);
	HRESULT RunSequence(void);
	HRESULT InstallObjectProperties(void);

	IStreamInfo *m_pIGeneralScriptsInfo;
	IStreamInfo *m_pIObjFeatureScriptsInfo;
	IStreamInfo *m_pIFilterScriptsInfo;

	IObjectManagement *m_pIGeneralScripts;	
	IObjectManagement *m_pIFilterScripts;	
	IObjectManagement *m_pIObjFeatureScripts;	

	CMenu *m_pPopupMenu;
	BOOL InstallMacroMenu();
	void RemoveMacroMenu();

	void RegisterNotifications (void);
	void UnRegisterNotifications (void);

	HRESULT EnumObjects(IObjectManagement *pIObjManagement, LPENUMUNKNOWN* ppEnumUnk);
	HRESULT IsStorageProject(BOOL, LPSTORAGE *lplpStorage);
	HRESULT DestroyStorage();
	HRESULT DestroyStorage(IObjectManagement *pIObjManagement, int IDS);
	HRESULT LoadScriptManagers(void);
	HRESULT UnLoadScriptManagers(void);
	HRESULT LoadFromStorage(IObjectManagement **ppIObjMan, IStreamInfo **lplpIStreamInfo, REFIID riid, int IDS);
	HRESULT LoadStreamInfos(REFCLSID riid, IObjectManagement *pObjM, IStreamInfo **ppIStreamInfo);
	HRESULT	LoadManagement (IObjectManagement **ppIOM, REFIID riid);
	HRESULT LodeCodeFromResource(HINSTANCE hInst, ebHCODE *phCode, UINT uiID);
	HRESULT OldGeneralStorage(LPSTORAGE lpIRootStorage, LPSTORAGE *lplpISubStorage, int IDS);
	HRESULT OldGeneralStreamInfo(IObjectManagement *pObjM, int IDS, IStreamInfo **ppIStreamInfo);
	HRESULT RenameObject(IObjectManagement *pObjM, LPCSTR lpcstrOld, LPCSTR lpcstr);

	HRESULT HandsOffStorage(IObjectManagement *pIOM);
	HRESULT HandsOffStorage (void);
	HRESULT Save (IObjectManagement *pIOM, int IDS, LPSTORAGE lpIStorage, BOOL fSameAsLoad);
	HRESULT Save (LPSTORAGE lpIStorage, BOOL fSameAsLoad);
	HRESULT SaveCompleted (IObjectManagement *pIOM, int IDS, LPSTORAGE lpIStorage);
	HRESULT SaveCompleted (LPSTORAGE lpIStorage);	

	HRESULT Commit(IObjectManagement *pIObjManagement);

	HRESULT	StopAllRun (void);
	HRESULT AutoLoadScript (void);
	HRESULT AutoLoadScriptExtern (void);

	//////////////////////////////////////////
	// Extended-BScript sonstige Member
	void Reset (void) { m_Modules.Reset(); }
	ULONG Count (void) { return m_Modules.Count(); }

public:
		CMacroScriptExtension (void);
		~CMacroScriptExtension (void);

	HRESULT FinalConstruct (void);

	BEGIN_COM_MAP(CMacroScriptExtension)
		COM_INTERFACE_ENTRY(IExtendBScript)
		COM_INTERFACE_ENTRY(IObjectProps)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CMacroScriptExtension, g_pTE)

// *** ITriasXtension methods ***
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

// ExtendedScriptInterface
	STDMETHOD (RegisterExtModule) (LPCSTR pModule);
	STDMETHOD (FireEvent) (LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	STDMETHOD (RunText) (LPCSTR pText, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	STDMETHOD (RunCode) (HINSTANCE hInst, int iResID, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	STDMETHOD (RunScript) (LPCSTR lpcstrScriptName);
	STDMETHOD (StopScript) (LPCSTR lpcstrScriptName);

	STDMETHOD (RunTextEx) (LPCSTR pText, LPCSTR lpName, LPCSTR pEntry, int iNumParams, BSPARAM *pPars, BOOL fBreakAfterExec, INT_PTR hPrCtx);
	STDMETHOD (RunCodeEx) (HINSTANCE hInst, int iResID, LPCSTR lpName, LPCSTR pEntry, int iNumParams, BSPARAM *pPars, BOOL fBreakAfterExec, INT_PTR hPrCtx);
	STDMETHOD (ExecuteMethod) (LPCSTR lpName, LPCSTR lpEntry, int iNumParams, BSPARAM *pPars, BOOL fBreakAfterExec, INT_PTR hPrCtx);

	STDMETHOD (EntryExists)(THIS_ LPCSTR lpEntry, int iNumParams, struct tagBSPARAM *pPars);

// inline accessors
	IObjectManagement *GetGeneralScripts(void) { return m_pIGeneralScripts; }
	IObjectManagement *GetFilterScripts(void) { return m_pIFilterScripts; }
	IObjectManagement *GetObjectFeatureScripts(void) { return m_pIObjFeatureScripts; }

	IStreamInfo *GetInfoFilterScripts(void) { return m_pIFilterScriptsInfo; }
	IStreamInfo *GetInfoGeneralScripts(void) { return m_pIGeneralScriptsInfo; }
	IStreamInfo *GetInfoObjFeatureScripts(void) { return m_pIObjFeatureScriptsInfo; }

	// Extended-BScript in ebGetNextModule-CallBack gerufen
	BOOL GetNextModule (LPTSTR pModule) 
		{ return m_Modules.GetNextModule (pModule); }

	CebInstance &ebInst (void) { return *m_pebInst; }
	CRunningObjectsHelper * GetRunningObjectsHelper(void) { return m_pRunningObjHelper; }

	HRESULT GetRuntimeDebugger(CRunErr **pp);
	HRESULT CreateRunTimeErrorDebugger(LPCSTR lpcstrMacroName);
	HRESULT DestroyRunTimeErrorDebugger(void);
// damit Library erst zur Laufzeit geladen wird, nicht ebCreateDebugger nutzen
	ebHWND CreateDebuggerControl (ebHWND hWndParent, ebINT x, ebINT y, ebINT width, ebINT height, ebDWORD style, _ebWORD id, ebHINSTANCE hInstance);
};

// sonstige globale Funktionen ------------------------------------------------
void CallMessageQueue (void);
BOOL SetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam);
BOOL GetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam, BOOL fModsParm = false, BOOL fAddRef = false);

///////////////////////////////////////////////////////////////////////////////
// UserMessages
#define WM_FINDTEXT (WM_USER + 100)

// Message, für abschalten des modeless - debuggerdialog 
#define WM_CLOSEDEBUGGERDIALOG				WM_USER+1000
#define WM_CLOSERUNTIMEDEBUGGERDIALOG		WM_USER+1002
#define WM_OPENPROJECT						WM_USER+1001
#define WM_CLOSEBREAKPOINTDEBUGGERDIALOG	WM_USER+1003

typedef struct tagSummitModul {
	LPCSTR lpcModulName;
	BOOL fIsInstalled;
} SummitModul;

typedef enum {	
	COMPILER = 0,
	DEBUGGER = 1,
	RUNTIME = 2,
	DLGEDIT = 3,
} SummitModulFlags;

HRESULT GetInstalledSummitModuls();

/////////////////////////////////////////////////////////////////////////////
// dynamische AcceleratorTabelle
typedef struct tagACCELERATOR {
	int cChar;
	UINT cVirtKey;
	UINT wID;
	BOOL fIdle;
	BOOL fRunning;
	BOOL fSuspended;
	BOOL fHilight;
} Accelerator;

#define	VKCTRL		1
#define VKSHFT		2
#define VKALT		3
#define ANYKEY		4

#define CREATETHREAD_EXTRA (6*sizeof(long))		// muß mit Anzahl der nachfolgenden Daten übereinstimmen

#define SETLONG_BREAK		0	// 00000
#define SETLONG_AUTO		4	// 00100
#define SETLONG_NAME		8	// 01000
#define SETLONG_EXT			12	// 01100
#define SETLONG_HPROJECT	16	// 10000
#define SETLONG_HINSTANCE	20	// 10100

#define g_pBSE ((CMacroScriptExtension *)g_pTE)

#define NOAUTOSTART		0
#define AUTOSTARTFILE	1
#define AUTOSTART		2
#define RESIDENT		3

#define COTASKMEMFREE(pointer) 	if (NULL != pointer) { CoTaskMemFree(pointer); pointer = NULL; }

BOOL IsValidString(LPCSTR lpcstr);
BOOL AssertValidString(LPCSTR lpcstr);
void MemFree(LPSTR *lplpstr, int iCount);

#define MEMFREE(pointer, count) 	(MemFree(pointer, count), pointer = NULL, count = 0)

#define THROW_INVALIDSTRING(str, result) if (IsValidString(str)) {} else { _com_issue_error(result); }
#define ASSERT_THROW_INVALIDSTRING(str) if (AssertValidString(str)) {} else { _com_issue_error(E_INVALIDARG); }

#define BS_E_NOENTRY                        _HRESULT_TYPEDEF_(0x80004100L)
#define BS_E_NOTFOUND                       _HRESULT_TYPEDEF_(0x80004200L)
#define BS_E_RUNTIMEERROR                   _HRESULT_TYPEDEF_(0x80004300L)

///////////////////////////////////////////////////////////////////////////////
// Routine, welche PreProzessorkonstanten (vor)definiert
ebINT ebCALLBACK PreDefinedConstants (long lParam, ebLPCSTR lpName, ebLPVOID lpDest);

///////////////////////////////////////////////////////////////////////////////
// Wrapper für TrayIcon handling
class CHandleMacroTrayIcons 
{
public:
	CHandleMacroTrayIcons() { _ASSERTE(NULL != g_pBSE); g_pBSE -> InitMacroTrayIcons(); }
	~CHandleMacroTrayIcons() { _ASSERTE(NULL != g_pBSE); g_pBSE -> RemoveMacroTrayIcons(); }
};


#endif // _BSCRIPT_HXX
