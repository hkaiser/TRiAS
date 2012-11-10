#ifndef _DEBCTRL_H
#define _DEBCTRL_H
 
/////////////////////////////////////////////////////////////////////////////////
// Wrapper für BasicScript-Debuggercontrol

DefineSmartInterface(ObjectManagement);

class CSplit;
class CDummyParent;
class CFindReplaceDialog;
class CEditCtrl;
class CRunningObjectsHelper;

class CDebuggerCtrl : public CWnd
{
	// Constructors
public:
	DECLARE_DYNCREATE(CDebuggerCtrl)
	
	CDebuggerCtrl();
	virtual ~CDebuggerCtrl();

private: 
	// BasicScript-Debuggercontrol
	CebDebugger	m_Debug;
	CEditCtrl	*m_pEditCtrl;

	// Initialisierung des Debuggers, wenn Parent kreiert
	CebInstance		*	GetBSInstance(void);
	// Aufbewahrung der Superitems und Subitems, "long" eigentlich RunningScriptsOrg aus Subitems
	CEditCtrl	*	GetEditCtrl(void) { return m_pEditCtrl; }
	CRelScripts *	GetRelScripts(void) { return m_pRelGeneralScripts; }
	
	HRESULT GetGeneralScripts(IObjectManagement **ppIObj);
	HRESULT GetInfoGeneralScripts(IStreamInfo **ppISI);
	HRESULT GetFilterScripts(IObjectManagement **ppIObj);
	HRESULT GetInfoFilterScripts(IStreamInfo **ppISI);
	HRESULT GetObjFeatScripts(IObjectManagement **ppIObj);
	HRESULT GetInfoObjFeatScripts(IStreamInfo **ppISI);

public:
	BOOL		CreateDebuggerControl (DWORD dwStyle, HWND hWnd, const RECT& rect, UINT nID);
	HRESULT		SwitchManagement(IObjectManagement *pIOM, IStreamInfo *pISI);
	HRESULT		InitDebuggerCtrl(CSplit *pMainFrame);
	CebDebugger *	GetDebugger(void) { return &m_Debug; }
	HRESULT		RunThread(LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT		EntryExists (LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT		RunModal(void);
	BOOL DebuggerEnd(void);
	void SetWindowSize(int cx, int cy);
	void ResetIfOnClose();

	HRESULT CanOpen		(void);
	HRESULT CanRemove	(void);
	HRESULT CanInsert	(void);
	HRESULT CanImport	(void);
	HRESULT CanEdit		(void);

	BOOL IsRBTreeMenu();
	void SetRBTreeMenu(BOOL f);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebuggerCtrl)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

protected:
	afx_msg LRESULT OnEndScript(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CDebuggerCtrl)
	afx_msg LRESULT OnCallbackFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNew();
	afx_msg void OnOpen();
	afx_msg void OnSaveas();
	afx_msg void OnSave();
	afx_msg void OnReplace();
	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void OnTimer(void);

	// OnIdleZugriff von Mainframe
	void OnUpdateDebugFunctionInsert(CCmdUI* pCmdUI);
	void OnUpdateDebugCut(CCmdUI* pCmdUI);   
	void OnUpdateDebugPause(CCmdUI* pCmdUI);   
	void OnUpdateDebugCopy(CCmdUI* pCmdUI);   
	void OnUpdateDebugBreakpoint(CCmdUI* pCmdUI);   
	void OnUpdateDebugCallstack(CCmdUI* pCmdUI);   
	void OnUpdateDebugDelete(CCmdUI* pCmdUI);   
	void OnUpdateDebugAddwatch(CCmdUI* pCmdUI);   
	void OnUpdateDebugDeletewatch(CCmdUI* pCmdUI);   
	void OnUpdateDebugModifyDlg(CCmdUI* pCmdUI);   
	void OnUpdateDebugHex(CCmdUI* pCmdUI);   
	void OnUpdateDebugEditdialog(CCmdUI* pCmdUI);   
	void OnUpdateDebugFind(CCmdUI* pCmdUI);   
	void OnUpdateDebugFindNext(CCmdUI* pCmdUI);   
	void OnUpdateDebugFonts(CCmdUI* pCmdUI);   
	void OnUpdateDebugGo(CCmdUI* pCmdUI);   
	void OnUpdateDebugGotoline(CCmdUI* pCmdUI);   
	void OnUpdateDebugNewdialog(CCmdUI* pCmdUI);   
	void OnUpdateDebugPaste(CCmdUI* pCmdUI);   
	void OnUpdateDebugRecording(CCmdUI* pCmdUI);   
	void OnUpdateDebugReplace(CCmdUI* pCmdUI);   
	void OnUpdateDebugSuspend(CCmdUI* pCmdUI);   
	void OnUpdateDebugSyntax(CCmdUI* pCmdUI);   
	void OnUpdateDebugTracein(CCmdUI* pCmdUI);   
	void OnUpdateDebugTraceover(CCmdUI* pCmdUI);   
	void OnUpdateDebugUndo(CCmdUI* pCmdUI);   
	// Persistenz
	void OnUpdateDebugRemove(CCmdUI* pCmdUI);
	void OnUpdateDebugFilterInsert(CCmdUI* pCmdUI);
	void OnUpdateDebugObjfeatinsert(CCmdUI* pCmdUI);
	void OnUpdateDebugInsert(CCmdUI* pCmdUI);
	void OnUpdateDebugNew(CCmdUI* pCmdUI);   
	void OnUpdateDebugOpen(CCmdUI* pCmdUI);   
	void OnUpdateDebugSave(CCmdUI* pCmdUI);   
	void OnUpdateDebugSaveas(CCmdUI* pCmdUI);   
	void OnUpdateDebugExportall(CCmdUI* pCmdUI) ;
	void OnUpdateDebugImport(CCmdUI* pCmdUI);
	void OnUpdateDebugFilterImport(CCmdUI* pCmdUI);
	void OnUpdateDebugObjfeatimport(CCmdUI* pCmdUI);
	void OnUpdateDebugNewFile(CCmdUI* pCmdUI);

	void OnUpdateDebugGetHelpOn(CCmdUI* pCmdUI);   
	void OnUpdateDebugEditorHelp(CCmdUI* pCmdUI);   
	void OnUpdateDebugTriasHelp(CCmdUI* pCmdUI);  
	// MRU enabeln
	void OnUpdateDebugMRU(CMenu *pMenu, int nID, UINT uiMruID);
	
	// Menüzugriff von Mainframe
	afx_msg void OnDebugCut();
	afx_msg void OnDebugCopy();
	afx_msg void OnDebugDelete();
	afx_msg void OnDebugBreakpoint();
	afx_msg void OnDebugCallstack();
	afx_msg void OnDebugAddwatch();
	afx_msg void OnDebugDeletewatch();
	afx_msg void OnDebugModifyDlg();
	afx_msg void OnDebugHex();
	afx_msg void OnDebugEditdialog();
	afx_msg void OnDebugFind();
	afx_msg void OnDebugFindnext();
	afx_msg void OnDebugFonts();
	afx_msg void OnDebugGo();
	afx_msg void OnDebugPause();
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
	// Persistenz
	BOOL OnDebugNew(LPCSTR lpstr);
	BOOL OnDebugOpen(LPCSTR lpstr, ebHCODE hCode);
	BOOL OnDebugSave(LPSTR *lplpstr, ebHCODE *phCode, DWORD & dwSaveFlag);
	BOOL OnDebugSaveas(LPSTR *lplpstr, ebHCODE *phCode, DWORD & dwSaveFlag);// Export
	BOOL OnDebugFunctionInsert(LPCSTR lpcstrFunctionText);// Export

	afx_msg void OnDebugGetHelpOn();
	afx_msg void OnDebugEditorHelp();
	afx_msg void OnDebugTriasHelp();

	afx_msg void OnDebugInsert();
	afx_msg void OnDebugRemove();

protected:
	//////////////////////////////////
	// Debugger-Settings
	LPSTR	m_pText;
	ebHCODE m_hCode;
	//////////////////////////////////
	// Sonstiges
	
	// *** Variablen
	HFONT	m_hFontOld;
	CebEntryInfo m_EInfo;
	BOOL m_fDisplayFormat;
	BOOL m_fIsModifiedOpen;
	BOOL m_fIsModifiedSaveAs;
	BOOL m_fIsInsertSaveText;
	BOOL m_fIsModifiedNew;
	CSplit *m_pMainFrame;
	// Parameter für 'remote debugging'
	int m_iNumParams;
	BSPARAM *m_pPars;
	// Find/Replace und andere Editormember
	CString m_strFindText;	
	char *	m_pcReplaceWithText;
	char *	m_pcFindText;
	ebBOOL m_bMatchCase;      /* = 0, case-insensitive */
	ebBOOL m_bUpDown;
	ebBOOL m_bMatchWholeWord;
	CFindReplaceDialog *m_pFRD;
	// Save, Load, geladenes Script neu ?
	BOOL m_fAskSave;
	// Modus
	BOOL m_fRunModal;
	BOOL m_fRunError;
	BOOL m_fEditOnly;
	BOOL m_fBreakSet;
	// what's Running ?
	BOOL m_fLoadIsRun;
	BOOL m_fUnLoadIsRun;
	BOOL m_fMainIsRun;
	// from where
	BOOL m_fOtherFunction;
	// Menü rechte Maustaste ?
	BOOL m_fRMBMenu;
	// Window, which had focus during trace
	HWND m_hWndSaved;
	// Fenster sollte geschlossen werden
	BOOL m_fSendClose;
	BOOL m_fEnabled;
	// unsichtbarer Parent für alle Laufzeitdialoge	
	CDummyParent *m_pDummyParent;	
	BOOL m_bFDOpen;
	// für OnSize
	BOOL m_fRecursiv;
	// Relscripts für Running
	LPSTR				m_lpstrRequestorName;
	CRelScripts *		m_pRelGeneralScripts;
	WObjectManagement	m_IObjManagement;
	// *** Funktionen
	//Registry
	BOOL SaveRegSettingsFont (void);
	BOOL ReadRegSettingsFont (LPLOGFONT pLF);
	BOOL ParseFontInfo (LPSTR pBuffer, LPLOGFONT pLF);
	// Accelerator
	HACCEL m_hAccel;

	/////////////////////////////////////////////
	// Zugriff auf Parentmember 
	CSplit *			GetMainFrame(void);
	CStatusBar *		GetStatusbar(void);
	CFrameToolBar *		GetToolbar(void); 
	// Resets
	void ResetFont(void);
	void ResetFindReplaceDialog(void);
	void DeleteDummyParent(void);
	void ResetDebuggerMember(void);
	HTREEITEM	GetChildItemSel(ITreeItem **ppIT);
	/////////////////////////////
	// Properties loaded Item
	void	GetInitCaretPos (int & ix, int & iy, int & fSelect);
	BOOL	GetDirty(void);
	void	SetDirty(BOOL);
	BOOL	GetInitNew(void);
	void	GenerateCaption(void);
	CString	GetScriptName(void);
	CString	GetParentName(void);
	BOOL	GetLoadedItem(ITreeItem **ppIT);
	BOOL	GetEditOnly(void);
	void	SetEditOnly(BOOL fEdit);
	HRESULT SetCode(ebHCODE hCode);
	HRESULT GetCode(ebHCODE *phCode);
	/////////////////////////////
	// Properties selected Item
	BOOL IsScript_Selected(void);
	BOOL IsFunction_Selected();
	int	 GetPopUpMenuID();
	BOOL IsTreeFocused(void);
	BOOL IsLabelEdit_Selected(void);
	CString	GetScriptName_Selected(void);
	BOOL	GetInitNew_Selected();

	void GetTreeRect(RECT *prect);
	void GetViewRectDebugger(RECT *prect);
// Inits
	BOOL SubClassEditWindow(void);
	void SetFont(void);
	void SetModus();
	BOOL ModifyMenu(CMenu *pMenu, int IDS, UINT uiMenuID, LPCSTR lpcstrName = NULL);

	BOOL GetAccelerator(void);
// Running
	BOOL SetEntryPointLoadScript(void);
	BOOL SetEntryPointUnLoadScript(void);
	BOOL ResetEntryInfo(void);

	HRESULT LinkScript	(void);
	// Externe Scripts starten
	HRESULT SetEntryInfo (CebEntryInfo & EI, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	BOOL GetWhichEntryMayRun(void);
	BOOL	BreakReset(void);
	BOOL	ModalReset(ebHTHREAD h);
	BOOL	SetOtherFunction(BOOL);
	BOOL	SetParams (int iNumParams, BSPARAM *pPars);
	void	ResetParams (void);
	HRESULT	RunScript(int iKindOfProcess);
	HRESULT RunLoadScript(int iKindOfProcess);
	HRESULT RunUnLoadScript(int iKindOfProcess);
	HRESULT RunMain(int iKindOfProcess);
	HRESULT GetMethodType(void);

	// Speichern, Laden
	BOOL	SetScript (LPSTR lpstr, ebHCODE hCode);
	BOOL	SetPosition(void);
	BOOL	GetScript (LPSTR *lplpstr, ebHCODE *phCode, DWORD & dwSaveFlag);
	int		AskSave(void);

	// Hilfe 
	HRESULT KeywordHelp (LPCSTR lpKeyWord);
	HRESULT LookupKeyword(LPCSTR lpKeyword, int & id);
	HRESULT GetHelpFile	(CString & strPath, LPCSTR pcFileName);
	HRESULT DebuggerHelp(void);
	HRESULT TriasHelp(void);
	// Sonstige 
	HRESULT	EnumFunctions(HTREEITEM hItem = NULL);
	LONG	GetBreakFlag(void);
	BOOL	IsWatch(void);
	// RelatedScripts-Bearbeitung
	void	DeleteRelated(void);
	HRESULT SwitchRelated(void);
	HRESULT AddRelatedScript(void);
	HRESULT DeleteRelatedScript(void);

	// Rückrufausführung
	long RightButtonUp (ebPARAM1 np1);
	long Stop(void);
	long Compile(ebLPCOMPILESTRUCT lpcs);
	long CompileEnd(void);
	long Changed(void);
	long ExeEnd(ebPARAM1 np1);
	long Go(void);
	long ExeStart(void);
	long Switch(void);
	long UnSwitch(void);
		// Editorfunktionen
	LRESULT FindNext(void);
	LRESULT ReplaceAll(const CString &str);
	LRESULT	ReplaceCurrent(const CString &str);
	void OutputReachedEOF(void);
	void OutputReachedBOF(void);
	LONG OutPutNoMatch (CString & strFind);

	BOOL DeleteWatchVariables (void);		// alle Watches entfernen

	/////////////////////////////////////////////////
	// Updatehelper
	HRESULT UpdateImportOperations(CCmdUI* pCmdUI, UINT ui);
	HRESULT UpdateOpenOperations(CCmdUI* pCmdUI, UINT ui);
	HRESULT UpdateInsertOperations(CCmdUI* pCmdUI, UINT ui);
	HRESULT UpdateGoOperations(CCmdUI* pCmdUI, UINT ui);
	HRESULT DisableIfClosedProject(UINT ui, CCmdUI* pCmdUI, CMenu *p = NULL);

	// um private-Zugriff vom Parent zu ermöglichen
	friend long ebCALLBACK EXPORT HandleDebuggerCtrlNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough);
	friend ebBOOL ebCALLBACK _XTENSN_EXPORT KeyboardFilterDebCtrlProc(HWND hWnd, UINT message, WPARAM wParam,LPARAM lParam);
	friend void ebCALLBACK EXPORT LineNumberProc(long lParam, ebWORD wLineNo);
	friend UINT ebCALLBACK _XTENSN_EXPORT CallbackFontProc(HWND hWnd, UINT msg,  
							UINT uiParam, long lParam);

};

extern "C" 
ebHSCRIPT ebCALLBACK _XTENSN_EXPORT RequestorProc (ebHTHREAD hThread, ebLPCTSTR pcMacroName, long lParam);

void ebCALLBACK EXPORT CompilerError(
	long lParam,
	ebLPCTSTR lpMsg,
	ebDWORD dwErrNum,
	ebWORD wLine,
	ebWORD wCharPos,
	ebLPCTSTR lpSource,
	ebLPCTSTR lpHelpFile,
	ebDWORD dwContext);


static enum tagKindOfProcess {	TRACEINTO, 
								TRACEOVER, 
								GO,
								ABORT
} KindOfProcess;

#define PROJECTCLOSE_FLAG	1
#define TRIASCLOSE_FLAG		2
#define ALWAYSCLOSE_FLAG	4

#endif _DEBCTRL_H
