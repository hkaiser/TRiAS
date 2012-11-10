// BranPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBranchPage dialog
class CSelectSet;
class CSelNumberDlg;

class CBranchPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBranchPage)

// Construction
public:
	CBranchPage(UINT uiID = IDD_BRANCHE, UINT uiCaption = 0);
	virtual ~CBranchPage();

	// virtual CString GetName ();

// Dialog Data
	//{{AFX_DATA(CBranchPage)
	enum { IDD = IDD_BRANCHE };
	CButton	m_btChange;
	CEdit	m_edNummer;
	CEdit	m_edName;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBranchPage)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSelectSet *m_pSet;
	CSelNumberDlg *m_pNumberDlg;		// NummerDialog

	virtual int OpenSet ();
	virtual void SetControlState (void);
	int OutputName (const char *pNummer);
	void Change (const CString &strTableName, UINT uiCaption);
	int OpenSetParam (CDaoDatabase *pDatabase, const CString &strTableName);
	// Generated message map functions
	//{{AFX_MSG(CBranchPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnChangeName(UINT, LONG);
	afx_msg virtual LONG OnChangeNummer(UINT, LONG);
	afx_msg LONG OnDeleteNumberDlg(UINT, LONG);
	afx_msg void OnChangeNummerField();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool m_bInOnChangeNummerField;
};
