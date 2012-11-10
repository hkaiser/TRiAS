// filtdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilterScriptDlg dialog

DefineEnumerator(LONG);
DefineSmartEnumerator(LONG);

class CFilterScriptPropAct;

class CFilterScriptDlg : public CPropertyPage
{
	typedef set<int, less<int> > BreakPointList;

	DECLARE_DYNCREATE(CFilterScriptDlg)

private:
// allgemeine Dialogmember setzen
	void	Reset();
	bool	FInit(void);

// allgemeine Debuggermember	
	CebEntryInfo	m_EI;
	CebScript		* m_pScript; 
	CebDebugger 	m_Debug;			// DebuggerControl
	CebInstance		&m_rInst;
	CebThread		* m_pThread;
	ebPARAM			m_Types[2];
	CRunErr			* m_pSuspendDeb;	// on demand debugging
	CRunErr			* m_pRunErr;

// eigentliche AKTION ausführen
	HRESULT	RunThread		(long & rlRetObj, ebDWORD dwObj);
	HRESULT RunThreadHelper	(IEnum<long> *pIEnum, IEnum<long> *pIEnumOut);
	HRESULT CreateScriptAndThread (ebHCODE hCode);
	HRESULT	OnDemandDebugger (CRunErr **ppSuspendDeb);
	HRESULT SetRuntimeErrorProc(CRunErr **ppDeb);
	HRESULT SetBreakPoints	(CebThread *pThread);
	HRESULT SetEntryInfoAction (CebEntryInfo & EI, bool fMethodType, UINT uiID, int iParamCnt);
	bool FilterMessageBox(int iIDS1);
	
	BreakPointList m_setBreakPoints;

// LONG_Konvertierung
	_DDocument *m_pIDoc;

// Konvertierfunktionen
	HRESULT	ConvertLongToObject (long lObjNr, _DGeoObject **ppIObj);
	HRESULT	GetDocument ();

// eigentliche Scriptparameter in/out
	WEnumLONG m_IEnumIn;
	list<WEnumLONG> m_listEnumLongOut;
	list<WEnumLONG>::iterator m_itEnLong; 	

// Hilfsmember
	CString m_strMacroName;
	bool m_fIsDirty;	
	bool m_fInitNew;
	LPSTR m_pText;

	DWORD m_dwSheetBttns;
	
// Hilfsfunktionen Debugger-Initialisierung
	HRESULT InitNewOperateScript(void);
	HRESULT InitOperateScript(LPCSTR pc);
	HRESULT CreateScript(void);

// allgemeine Init.
	HRESULT Fill(void);
	HRESULT SetRect(void);	
	HRESULT InitSheetButtons(bool fNextDisable = false);	
	HRESULT GetText(void);

// Save, Load Member
	CMacroScripts *m_pOperateScripts;

	HRESULT		LoadStorage(void);
	int			AskSaveChanges (void);
	HRESULT		AskSave (void);
	HRESULT		LoadScript(void);
	HRESULT		LoadInitialScript(void);
	HRESULT		SaveScript(void);
	HRESULT		Delete (void);
	HRESULT		GetScriptInfo(const CString & str, DWORD & dwInfo);
	HRESULT		OnYes(void);
	HRESULT		EntryName();

	bool		m_fEntfernen;
	bool		m_fModified;

// Font einstellen	
	HFONT		m_hFontOld;
	void		SetFont(void);
	void		ResetFont(void);

// Notifications
	long Changed(void);
	long RightButtonUp(ebPARAM1 np1);

// Hilfe
	HRESULT LookupKeyword	(LPCSTR lpKeyWord, int & id);
	HRESULT KeywordHelp		(LPCSTR lpKeyWord);

	// Construction
public:
		CFilterScriptDlg(void);
		~CFilterScriptDlg(void);

static CFilterScriptDlg* CreateInstance(void);

	void SetFlags (DWORD dwSheetBttns) { m_dwSheetBttns = dwSheetBttns; }

// Dialogdaten erfragen
	HRESULT GetEnumLONG (IEnum<long> **ppEnum);

// eigentliche AKTION ausführen
	HRESULT DoAction(IEnum<long> *pIEnum);
	HRESULT BeginAction(void);
	HRESULT EndAction(void);

// Import/Export
	bool SaveScriptAsFile (CString &rstrFileName);
	bool SaveCode (bool fCorrectExt, CString &rstrFileName);
	bool Open (CString &rstrFileName);
	bool LoadScriptFromFile (int fh, CString &rstrFileName);
	bool LoadCode (int fh, ebFILEHEADER &rHead, CString &rstrFileName);

	LRESULT WizardFinishNext(void);

// Dialog Data
	//{{AFX_DATA(CFilterScriptDlg)
	enum { IDD = IDD_FILTERDLG };
	CButton	m_bttnEntfernen;
	CButton	m_Test;
	CComboBox	m_cbxFilterScripts;
	//}}AFX_DATA
	enum { ID_DEBUG = IDR_FILTERDEBUGGERCTL };

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFilterScriptDlg)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual void OnCancel();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFilterScriptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSyntaxTest();
	afx_msg void OnEditChangeCB();
	afx_msg void OnSelChangeCB();
	afx_msg void OnKillFocusCB();
	afx_msg void OnEntfernen();
	afx_msg void OnDebugCut();
	afx_msg void OnDebugCopy();
	afx_msg void OnDebugPaste();
	afx_msg void OnDebugDelete();
	afx_msg void OnDebugUndo();
	afx_msg void OnDebugEditdialog();
	afx_msg void OnDebugNewdialog();
	afx_msg void OnDebugBreakpoint();
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnDebugGetHelpOn();
	afx_msg void OnDebugSave();
	afx_msg void OnDebugImport();
	afx_msg void OnDebugExport();
	// Dummies
	afx_msg void OnDebugGo();
	afx_msg void OnDebugTraceIn();
	afx_msg void OnDebugTraceOver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend CFilterScriptPropAct;
	friend long ebCALLBACK EXPORT HandleFilterDebuggerNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough);
};
