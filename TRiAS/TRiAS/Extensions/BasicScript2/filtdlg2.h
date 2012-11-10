// filtdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilterScriptDlg2 dialog

DefineSmartEnumerator(LONG);

class CFilterScriptPropAct;
class CRunningObjectsHelper;

class CFilterScriptDlg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CFilterScriptDlg2)

private:
// allgemeine Dialogmember setzen
	
	void	Reset();

	HRESULT GetGeneralScripts(IObjectManagement **pp);
	HRESULT GetInfoGeneralScripts(IStreamInfo **ppISI);
	HRESULT GetFilterScripts(IObjectManagement **pp);
	HRESULT GetInfoFilterScripts(IStreamInfo **ppISI);
	HRESULT GetObjFeatScripts(IObjectManagement **ppIObj);
	HRESULT GetInfoObjFeatScripts(IStreamInfo **ppISI);

	void	SetLoadedItem(IRunningObject* p) ;
	HRESULT GetLoadedItem(IRunningObject** ppI);
	BOOL	GetDirty();
	void	SetDirty(BOOL f);
	BOOL	GetInitNew();
	CString GetScriptName();
// allgemeine Debuggermember	
	IRunningObject*			m_pRunningObject;
	CRunningObjectsHelper *	m_pRunningObjs;
	CebDebugger				m_Debug;			// DebuggerControl
	CebInstance		&		m_rInst;
	LPSTR					m_pText;
	ebHCODE					m_hCode;
	ebHCODE					m_hOuterCode;
	CString					m_strStartName;
	HPROJECT m_hPrCtx;

// Breakpointsbearbeitung
	typedef set<int, less<int> > BreakPointList;
	BreakPointList m_setBreakPoints;
	HRESULT	SetKeptBreaks(void);

// eigentliche AKTION ausführen
	HRESULT	RunThread		(long & rlRetObj, ebDWORD dwObj);
	HRESULT RunThreadHelper	(IEnum<long> *pIEnum, IEnum<long> **ppIEnumOut);
	HRESULT SetBreakPoints	(CebThread *pThread);
	BOOL	FilterMessageBox(int iIDS1);
	HRESULT GetText(LPSTR *lplpstrText);
		// LONG_Konvertierung
	_DDocument		*m_pIDoc;
	// Konvertierfunktionen
	HRESULT	ConvertLongToObject (long lObjNr, _DGeoObject **ppIObj);
	HRESULT	GetDocument ();

	// eigentliche Scriptparameter in/out
	WEnumLONG		m_IEnumIn;
	list<WEnumLONG> m_listEnumLongOut;
	list<WEnumLONG>::iterator m_itEnLong; 	

	// Hilfsmember
	DWORD			m_dwSheetBttns;
	
// allgemeine Init.
	HRESULT	OpenInit(void);
	HRESULT FillComboBox(void);
	HRESULT SetRect(void);	
	HRESULT InitSheetButtons(BOOL fNextDisable = false);	
	BOOL	SetButtons(LPCSTR lpcstr);
	HRESULT CreateDebugger();
	HRESULT InitActions (void);
	HRESULT ResetActions(void);
	void	InsertCombo(LPCSTR lpcstr);
	void	DeleteCombo(LPCSTR lpcstr);
	HRESULT	GetInitName(LPSTR lpstrDefaultName, UINT uiLen);

	// Save/Load-Member
	HRESULT		Import	(void);
	HRESULT		Export	(void);
	HRESULT		Open	(LPCSTR lpcstr);
	HRESULT		Save	(void);
	HRESULT		Delete	(void);
	HRESULT		DeleteNew(void);
	HRESULT		SaveLoaded(void);
	HRESULT		OpenScript(LPCSTR lpcstrScriptName);
	HRESULT		ImportScript(void);
	HRESULT		OpenOther(LPCSTR lpcstrScriptName, REFIID, ebHCODE *phCode, LPSTR*);

	int			AskSave (void);
	HRESULT		EntryName(LPCSTR lpcstr);
	BOOL		GenerateCaption (LPCSTR lpcstr);
	LRESULT		WizardFinishNext(void);

	BOOL		m_fModified;

// Font einstellen	
	HFONT	m_hFontOld;
	void	SetFont(void);
	void	ResetFont(void);
	BOOL	ReadRegSettingsFont (LPLOGFONT pLF);
	BOOL	ParseFontInfo (LPSTR pBuffer, LPLOGFONT pLF);

// Notifications
	long Changed(void);
	long RightButtonUp(ebPARAM1 np1);

// Hilfe
	HRESULT LookupKeyword	(LPCSTR lpKeyWord, int & id);
	HRESULT KeywordHelp		(LPCSTR lpKeyWord);

	// Construction
public:
		CFilterScriptDlg2(void);
		~CFilterScriptDlg2(void);

static CFilterScriptDlg2* CreateInstance(void);

	void SetFlags (DWORD dwSheetBttns) { m_dwSheetBttns = dwSheetBttns; }

// Dialogdaten erfragen
	HRESULT GetEnumLONG (IEnum<long> **ppEnum);

// eigentliche AKTION ausführen
	HRESULT DoAction(IEnum<long> *pIEnum);
	HRESULT BeginAction(void);
	HRESULT EndAction(void);
// StartNamen abfragen und setzen
	HRESULT	SetStartName(LPCSTR lpcstrStartName);
	HRESULT	GetStartName(LPSTR lpstrStartName, UINT uiLen);
// von aussen Script starten
	HRESULT OuterInit(void);

	void SetCtxDataSource (HPROJECT hPrCtx) { m_hPrCtx = hPrCtx; }

// Dialog Data
	//{{AFX_DATA(CFilterScriptDlg2)
	enum { IDD = IDD_FILTERDLG };
	CButton	m_bttnEntfernen;
	CButton	m_Test;
	CComboBox	m_cbxFilterScripts;
	//}}AFX_DATA
	enum { ID_DEBUG = IDR_FILTERDEBUGGERCTL };

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFilterScriptDlg2)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	virtual void OnCancel();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFilterScriptDlg2)
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
	afx_msg void OnDebugGo();
	afx_msg void OnDebugTraceIn();
	afx_msg void OnDebugTraceOver();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend CFilterScriptPropAct;
	friend long ebCALLBACK EXPORT HandleFilterDebuggerNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough);
};
