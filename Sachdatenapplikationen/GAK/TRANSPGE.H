// TransPge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTranspPage dialog

class CTranspPage : public CBranchPage
{
	DECLARE_DYNCREATE(CTranspPage)

// Construction
public:
//	CString GetOrt (void);
//	CString GetPlz (void);
//	CString GetStrasse (void);
	CTranspPage();
	~CTranspPage();

//	virtual CString GetName ();

// Dialog Data
	//{{AFX_DATA(CTranspPage)
	enum { IDD = IDD_TRANSPORTEUR };
	CEdit	m_edBemerkungen;
	CButton	m_btEigen;
	CEdit	m_edStrasse;
	CEdit	m_edPlz;
	CEdit	m_edOrt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTranspPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL FindActRecord (void);
	virtual void SetControlState (bool bDisableAll = FALSE);	// Schalten der Control's 
														// JG 981028
														// mit bDisableAll werden alle ausgeschaltet
	virtual int OpenSet (void);
	void OutputTransParam (const char *pNummer);

	// Generated message map functions
	//{{AFX_MSG(CTranspPage)
	afx_msg void OnEigentransport();
	afx_msg void OnChange();
	afx_msg LONG OnChangeNummer(UINT, LONG);
	afx_msg LONG OnChangeName(UINT, LONG);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
