// Beispielerweiterung --------------------------------------------------------
// File: BSCRIPT.HXX

#if !defined(_BSCRIPT_HXX)
#define _BSCRIPT_HXX
        
#define WM_FINDTEXT (WM_USER + 100)

#define MAXSTRLENGTH 255

void StrValid (char *pc);

class CBScriptDebug;
class CScriptDlg;
class CRunScriptsOrg;

class CMacroScriptExtension : public CTriasExtension {
private:
	CebInstance *m_pebInst;
	CExtendBScript *m_pBScriptExt;
	CBScriptDebug *m_pDebugWnd;		// DebugFenster
	CRunScriptsOrg *m_pRunScriptsOrg;
	
	HINSTANCE m_hDCInst;
	HRESULT InitScripts(void);
	HRESULT SetHomDirBS(void);
	HRESULT SaveMacros (LPSTORAGE pIStorage, bool fAsk);
	HRESULT SaveAsMacros (LPSTORAGE pIStorage);
	HRESULT SaveCompleted(LPSTORAGE pIStorage);
	HRESULT HandsOffStorage(void);
	
	HRESULT Save (REFCLSID rclsid, int IDS, LPSTORAGE lpOtherStorage);

	HRESULT SetNotCommit(bool fNotCommit);
	HRESULT CommitMacros (bool fAsk);
	HRESULT NewSubStorage (LPSTORAGE pIStorage, LPSTORAGE *ppISubStorage);
	HRESULT DestroyMenuItemsStorage(void);
	
	HRESULT SaveMenuItems(void);
	HRESULT SaveMenuItems(LPSTORAGE pIStorage);
	HRESULT SaveCompletedMenuItems(LPSTORAGE pIOtherStorage);
	HRESULT HandsOffStorageMenuItems(void);

	bool MacroScriptCall(void);
	bool ObjectFeatureDlgCall(void);
	bool OtherMenuCommand(UINT uiID);
	bool LoadOtherMenu(void);
	HRESULT RunSequence(void);
	
	HRESULT RunThread(LPCSTR pEntry, ebHCODE hCode, int iNumParams, BSPARAM *pPars);
	HRESULT Compile(ebCOMPILESTRUCT & CompileStruct, LPCSTR lpText);
	HRESULT LodeCodeFromResource(HINSTANCE hInst, ebHCODE *phCode, UINT uiID);

	HRESULT	StopAllRun (void);
	HRESULT AutoLoadScript (void);

	bool RegisterExtensions (LPCSTR pcFPath);

	LPUNKNOWN m_pMacroScripts;	
	LPUNKNOWN m_pMacroOrg;	

	HMENU m_hMenu;

protected:
	bool OnInvokeScript (void);
	bool OnCloseDebugDlg (bool);
	int OnDebugDlg (LPUNKNOWN m_pMacroScripts = NULL, LPSTR pcName = NULL);

public:
		CMacroScriptExtension (void);
		~CMacroScriptExtension (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** ITriasXtension methods ***
	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, 
						  LPARAM lParam);

// sonstige Member
	LPUNKNOWN GetMacroOrg(void);
	LPUNKNOWN GetMacroScripts(void);
	CRunScriptsOrg * GetRunningScripts() { return m_pRunScriptsOrg; }

	bool GetNextModule (LPTSTR pModule) 
		{ return m_pBScriptExt -> GetNextModule (pModule); }
	void Reset (void) { m_pBScriptExt -> Reset(); }
	CebInstance &ebInst (void) { return *m_pebInst; }

	HRESULT FireEvent (LPCTSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT RunText (LPCSTR pText, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT RunCode (HINSTANCE hInst, UINT iResID, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT GetMenuStructure(void);
};

// sonstige globale Funktionen ------------------------------------------------
void CallMessageQueue (void);
bool SetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam);
bool GetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam);
void FreeCompCode (ebHCODE ebhCode);

// Message, für abschalten des modeless - debuggerdialog ----------------------
#define WM_CLOSEDEBUGGERDIALOG	WM_USER+1000
#define WM_OPENPROJECT			WM_USER+1001

typedef struct tagSummitModul {
		LPCSTR lpcModulName;
		bool fIsInstalled;
} SummitModul;

typedef enum {	COMPILER = 0,
				DEBUGGER = 1,
				RUNTIME = 2,
				DLGEDIT = 3,
} SummitModulFlags;

HRESULT GetInstalledSummitModuls();

#endif // _BSCRIPT_HXX
