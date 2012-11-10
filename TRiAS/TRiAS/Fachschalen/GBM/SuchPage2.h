// SuchPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuchPage2 dialog

class CSuchPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSuchPage2)

// Construction
public:
	short m_iOISY;
	CString m_strIdent;
	CString m_strIDE;
	CStrasseSet* m_pSetStrasse;
	CSuchPage2();
	~CSuchPage2();

// Dialog Data
	//{{AFX_DATA(CSuchPage2)
	enum { IDD = IDD_SUCH2 };
	CComboBox	m_cbStrasse;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSuchPage2)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bInit;
	CMapStringToString* m_pmapStrassen;
	// Generated message map functions
	//{{AFX_MSG(CSuchPage2)
	afx_msg void OnSelchangeStrasse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
