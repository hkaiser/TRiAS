// ImpParPg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportParamPage dialog

class CImportParamPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CImportParamPage)

// Construction
public:
	CImportParamPage();
	~CImportParamPage();

	void SetParams (CImportParams &Params);

// Dialog Data
	//{{AFX_DATA(CImportParamPage)
	enum { IDD = IDD_RECORDS_SELECT };
	CButton	m_btActIndex;
	CButton	m_btAllRecords;
	CButton	m_btAlwaysMod;
	CButton	m_btOnlyWithRef;
	CButton	m_btOnlyWithoutRef;
	CButton	m_btNeverMod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImportParamPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImportParams *m_pParams;
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd::GetParent (); }
	// Generated message map functions
	//{{AFX_MSG(CImportParamPage)
	afx_msg void OnAllRecords();
	afx_msg void OnAlwaysMod();
	afx_msg void OnNeverMod();
	afx_msg void OnOnlyNotReferenz();
	afx_msg void OnOnlyReferenz();
	afx_msg void OnAlwaysIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
