// DlgVisu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVisu dialog

class CDlgVisu : public CDialog
{
// Construction
public:
	short m_iArtVisu;
	CDlgVisu(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVisu)
	enum { IDD = IDD_VISU };
	CComboBox	m_cbArtVisu;
	CButton	m_btnVisuParam;
	CString	m_strArtVisu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVisu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVisu)
	virtual BOOL OnInitDialog();
	afx_msg void OnVisuParam();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
