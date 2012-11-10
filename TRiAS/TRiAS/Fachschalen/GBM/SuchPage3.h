// SuchPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuchPage3 dialog

class CSuchPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSuchPage3)

// Construction
public:
	CSuchPage3();
	~CSuchPage3();

// Dialog Data
	//{{AFX_DATA(CSuchPage3)
	enum { IDD = IDD_SUCH3 };
	CString	m_strFlur;
	CString	m_strFlurStck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSuchPage3)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSuchPage3)
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
