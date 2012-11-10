// ToolbarsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolBarsPage dialog

class CToolBarsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CToolBarsPage)

// Construction
public:
	CToolBarsPage(); 
	~CToolBarsPage(); 

// Dialog Data
	//{{AFX_DATA(CToolBarsPage)
	enum { IDD = IDD_TRIASTOOLBARSPAGE };
	CButton	m_pbCoolLook;
	CButton	m_pbRemove;
	CEdit	m_ecToolBarName;
	CButton	m_pbNew;
	CButton	m_pbReset;
	CButton	m_pbResetAll;
	CCheckListBox	m_lbToolBars;
	BOOL	m_fShowToolTips;
	//}}AFX_DATA
	DWORD m_fCoolLook;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool UpdateShownToolBars (int iIndex);
	bool ActivateEntry (int iIndex);
	HRESULT RemoveBar (LPCSTR pcName);
	BOOL FillToolbarList();

#if defined(_USE_SEC_CLASSES)
	void Terminate (void);
#endif // _USE_SEC_CLASSES

	// Generated message map functions
	//{{AFX_MSG(CToolBarsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeToolbarlist();
	afx_msg void OnRemove();
	afx_msg void OnKillfocusToolbarname();
	afx_msg void OnResetToolbar();
	afx_msg void OnResetAllToolbars();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCoollook();
	afx_msg void OnTooltips();
	afx_msg void OnChangeToolbarname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual void OnReset();

private:
	int m_iCurrIndex;

#if defined(_USE_SEC_CLASSES)
	class SECToolBarManager *m_pControlBarManager;

public:
	void SetManager(SECToolBarManager* pManager);
#endif // _USE_SEC_CLASSES
};
