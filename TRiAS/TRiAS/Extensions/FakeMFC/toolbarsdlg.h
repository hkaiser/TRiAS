// ToolbarsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolbarsDlg dialog

class CToolBarsDlg : public CDialog
{
// Construction
public:
	CToolBarsDlg(CMainFrame* pParent, IEnumITRiASBar *pIEnum, BOOL fShowTT, BOOL fCoolLook); 

// Dialog Data
	//{{AFX_DATA(CToolBarsDlg)
	enum { IDD = IDD_TRIASTOOLBARS };
	CButton	m_pbCoolLook;
	CButton	m_pbRemove;
	CButton	m_pbCustomize;
	CEdit	m_ecToolBarName;
	CButton	m_pbNew;
	CButton	m_pbReset;
	CCheckListBox	m_lbToolBars;
	BOOL	m_fShowToolTips;
	//}}AFX_DATA
	BOOL m_fCoolLook;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool UpdateShownToolBars (int iIndex);
	bool ActivateEntry (int iIndex);

#if defined(_USE_SEC_CLASSES)
	void Terminate (void);
#endif // _USE_SEC_CLASSES

	// Generated message map functions
	//{{AFX_MSG(CToolBarsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomize();
	afx_msg void OnSelchangeToolbarlist();
	afx_msg void OnRemove();
	afx_msg void OnKillfocusToolbarname();
	afx_msg void OnResetToolbar();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_iCurrIndex;
	WEnumITRiASBar m_Bars;

#if defined(_USE_SEC_CLASSES)
	class SECToolBarManager *m_pControlBarManager;

public:
	void SetManager(SECToolBarManager* pManager);
#endif // _USE_SEC_CLASSES
};
