// bscripta.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBScriptDebug dialog
class CDummyParent;	// forward declaration

class CBScriptDebug : public CDialog
{
private:
	bool m_fRunModal;
	bool m_fRunError;
	bool m_fEditOnly;

	bool m_fLoadIsRun;
	bool m_fUnLoadIsRun;
	bool m_fMainIsRun;
	bool m_fOtherFunction;

	bool m_fAskSave;
	// *** Hilfe ***
	HRESULT KeywordHelp (LPCSTR lpKeyWord);
	HRESULT LookupKeyword(LPCSTR lpKeyword, int & id);
	HRESULT GetHelpFile	(CString & strPath, LPCSTR pcFileName);
	HRESULT DebuggerHelp(void);
	HRESULT TriasHelp(void);
	// *** nach Script laden bzw. vor Script entladen ***
	bool SetEntryPointLoadScript(void);
	bool SetEntryPointUnLoadScript(void);
	bool ResetEntryInfo(void);
	
	HRESULT	RunScript(int iKindOfProcess);
	HRESULT RunLoadScript(int iKindOfProcess);
	HRESULT RunUnLoadScript(int iKindOfProcess);
	HRESULT RunMain(int iKindOfProcess);

	bool GetWhichEntryMayRun(void);
	HRESULT GetMethodType();

	// bei SetBreakScript(0)
	void DisableToolbarVirtualRun(void);
	void EnableToolbarVirtualRun(void);

	bool FilterMessageBox(int iIDS1);

	CebEntryInfo m_EInfo;

public:                                  
	int LocMessageBox (LPCTSTR lpszText, UINT nType = MB_OK, UINT nIDHelp = (UINT)-1);
	int LocMessageBox (UINT uiRes, UINT nType = MB_OK, UINT nIDHelp = (UINT)-1);

	HRESULT RunModal();

	CBScriptDebug(CebInstance &rInst, CWnd* pParent = NULL, LPUNKNOWN pMacroScripts = NULL);// standard constructor
	~CBScriptDebug (void);

// Dialog Data
	//{{AFX_DATA(CBScriptDebug)
	enum { IDD = IDD_DEBUGGERDLG };
	//}}AFX_DATA
	enum { ID_DEBUG = IDR_DEBUGGERCTL };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CBScriptDebug)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnExit();
	afx_msg void OnDebugCut();
	afx_msg void OnDebugCopy();
	afx_msg void OnDebugBreakpoint();
	afx_msg void OnDebugCallstack();
	afx_msg void OnDebugDelete();
	afx_msg void OnDebugAddwatch();
	afx_msg void OnDebugDeletewatch();
	afx_msg void OnDebugModifyDlg();
	afx_msg void OnDebugHex();
	afx_msg void OnDebugEditdialog();
	afx_msg void OnDebugFind();
	afx_msg void OnDebugFindnext();
	afx_msg void OnDebugFonts();
	afx_msg void OnDebugGo();
	afx_msg void OnDebugGotoline();
	afx_msg void OnDebugNewdialog();
	afx_msg void OnDebugPaste();
	afx_msg void OnDebugRecording();
	afx_msg void OnDebugReplace();
	afx_msg void OnDebugSuspend();
	afx_msg void OnDebugSyntax();
	afx_msg void OnDebugTracein();
	afx_msg void OnDebugTraceover();
	afx_msg void OnDebugUndo();
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnMenuSelect( UINT nItemID, UINT nFlags, HMENU hSysMenu ); 
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDebugNew();
	afx_msg void OnDebugOpen();
	afx_msg void OnDebugSave();
	afx_msg void OnDebugSaveText();
	afx_msg void OnDebugSaveas();
	afx_msg void OnDebugGetHelpOn();
	afx_msg void OnDebugEditorHelp();
	afx_msg void OnDebugTriasHelp();
	afx_msg LRESULT OnCallbackFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEndScript(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer( UINT );
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		      AFX_CMDHANDLERINFO* pHandlerInfo);

#if defined(WIN32)
virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
#endif

private:    
	LPUNKNOWN	m_pMacroScripts; 

	bool m_fStorageManagement;
	bool m_fSaveCompiled;
	bool m_fInitNew;
	bool m_fRMBMenu;	
	bool m_fDisplayFormat;
	bool m_fRunBreak;

	CString m_strFindText;	
	CString m_strMacroName;
	char *	m_pcReplaceWithText;
	char *	m_pcFindText;
	
	ebBOOL m_bMatchCase;      /* = 0, case-insensitive */
	ebBOOL m_bUpDown;
	ebBOOL m_bMatchWholeWord;

	CebInstance &m_rInst;		// übergeordnetes BScriptObject
	CToolBarEx m_wndToolBar;		// Toolbar
	int m_sCX, m_sCY; 			// Größe des Fensters

	unsigned int m_fSendClose : 1;
	unsigned int m_fIsDirty : 1;
	unsigned int m_fEnabled : 1;

	bool m_fClose;
	bool m_fBreakSet;
	bool m_fBreak;
	
	HWND m_hWndSaved;		// Window, which had focus during trace

	CString m_strFileName;		// aktueller Dateiname
	LPSTR m_lpSavedCode;		// Code ohne BreakPoints

	int m_iNumParams;		// Parameter für 'remote debugging'
	BSPARAM *m_pPars;
	
	// Parameter für internes Debugging und anderer Entrypoint als "Main()"
	ebPARAM	m_Types[10];

	struct tagMRUMENU *m_pMRUMenu;	// MRUList-Verwaltung

	CDummyParent *m_pDummyParent;	// unsichtbarer Parent für alle Laufzeitdialoge	
	CWnd *m_pParent;

	UINT m_uiMruID;			// erster MenuID des MRU-Menus
	
	void OutputReachedEOF(void);
	void OutputReachedBOF(void);
	LONG OutPutNoMatch ( CString & str);
		
	LRESULT ReplaceAll(const CString &str);
	LRESULT ReplaceCurrent(const CString &str);
	LRESULT FindNext();

	long Go();
	long Compile(ebLPCOMPILESTRUCT lpcs);
	long CompileEnd();
	long ExeEnd(ebPARAM1 np1);
	long ExeStart();
	long Stop();
	long Changed();
	long RightButtonUp(ebPARAM1 np1);

	HRESULT CreateDebuggerControl(void);
	HRESULT StatusBar(void);
	HRESULT ToolBar(void);
	HRESULT MRU(void);

	bool IsWatch(void);
	
	LONG GetBreakFlag(void);

protected:
	void InitScript (char *pc);

	bool AskSave(bool fInitNew);
	int AskSaveChanges (void);	// Abfrage, ob Script gespeichert werden soll
	int AskSaveChanges_DB (void);
	void GenerateCaption (void);	// Caption mit Dateinamen richten

	bool OpenNew (void);		// neuen Script laden
	bool OpenNew_DB (void);
	bool OpenFromMRU (UINT uiID);	// Datei aus MRUList öffnen
	bool Open (void);
	bool LoadScript (int fh);	// Text lesen
	bool LoadCode (int fh, ebFILEHEADER &rHead);	// compilierten Script lesen
	bool SaveScript (void);		// allgemein: Script speichern
	bool Save (void);		// Script speichern
	bool SaveCode (bool fCorrectExt);	// compilierten Script speichern
	bool SaveCodeOnly (bool fCorrectExt);
	bool SaveAs (void);		// Script unter neuem Namen speichern
	bool InitNewScript (bool fIsDirty);	// neuen Script setzen

	void EndMRUHandling (void);	// MRUList wegschreiben

	bool SaveScript_InDB (bool fTextOnly);

// zum Lesen in Storageverwaltung "public"
	bool DeleteWatchVariables (void);	// alle Watches entfernen
	HRESULT DeleteFromEnum (void);

	ebHCODE m_hCode;		// evtl. durch uns gelesener Code
		
public:
	bool OpenStream (LPSTR pMacroName);	
	HRESULT Close(void);
	bool DebuggerEnd(void);

	bool BreakSet(LPCSTR pEntryName);
	bool BreakReset();

	HRESULT RunThread(LPCTSTR pEntry, int iNumParams, BSPARAM *pPars);

	CebDebugger 	m_Debug;		// DebuggerControl
	CFindReplaceDialog *m_pFRD;

	CFont m_StatFont;	
	CFont *m_pSBOldFont;

	CStatusBar m_wndStatusBar;		// StatusBar
	
	BOOL m_bFDOpen;
    CMenu *m_pMenu;

	HFONT m_hFontOld;			// vorheriger Font im Debugger
	HICON m_hIcon;
	
inline	CString GetCurMakroName (void) { return m_strMacroName; }
inline	CebScript *GetScript (void) { return m_Debug.GetScript(false); }
inline	int GetState (void) { return m_Debug.GetState(); }
inline	ebHCODE GetCode (bool fWantOwnerShip = true)
		{ return m_Debug.GetCode (fWantOwnerShip); }
inline	HWND GetWindow (void) { return m_Debug.GetWindow(); }
inline	void SetEntryPoint (ebLPENTRYINFO pEI) { m_Debug.SetEntryPoint (pEI); }
inline	void StartScript (void) { m_Debug.StartScript(); }

	bool SetParams (int iNumParams, BSPARAM *pPars);
	void ResetParams (void);

	void EditOnly (void);		// Fenster nur als Editor verwenden
	
	friend long ebCALLBACK EXPORT HandleDebuggerNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough);
	friend void ebCALLBACK EXPORT LineNumberProc(long lParam,ebWORD wLineNo);
};

extern "C" 
UINT ebCALLBACK _XTENSN_EXPORT CallbackFontDlgProc(HWND hWnd, UINT msg,  
					UINT uiParam, long lparam);
extern "C" 
ebBOOL ebCALLBACK _XTENSN_EXPORT KeyboardFilterProc(HWND hWnd, UINT message, 
						WPARAM wParam,LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// dynamische AcceleratorTabelle
typedef struct tagACCELERATOR {
	int cChar;
	UINT cVirtKey;
	UINT wID;
	bool fIdle;
	bool fRunning;
	bool fSuspended;
	bool fHilight;
} Accelerator;

#define	VKCTRL		1
#define VKSHFT		2
#define VKALT		3
#define ANYKEY		4

/////////////////////////////////////////////////////////////////////////////
// sonstige Prototypen
bool ReadSettingsFont (LPLOGFONT pLF );
bool ReadIniSettingsFont (LPLOGFONT pLF );
bool ReadRegSettingsFont (LPLOGFONT pLF );

bool ReadSettingsWindow (RECT *pRect );
bool ReadRegSettingsWindow (RECT *pRect );
bool ReadIniSettingsWindow (RECT *pRect );

bool SaveSettingsFont(CBScriptDebug *pDeb);
bool SaveIniSettingsFont(CBScriptDebug *pDeb);
bool SaveRegSettingsFont(CBScriptDebug *pDeb);

bool SaveSettingsWindow(CBScriptDebug *pDeb);
bool SaveIniSettingsWindow();
bool SaveRegSettingsWindow(CBScriptDebug *pDeb);

BOOL ActivateMenuItem (HWND hWnd, WORD wID, bool fHilight);
bool CustomTranslateAccelerator (CebDebugger *, Accelerator  *pAcc,
		HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool FileErrorMessage (UINT uiResID, CString &rstrFileName);


