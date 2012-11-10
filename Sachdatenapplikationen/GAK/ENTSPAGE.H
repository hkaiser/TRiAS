// EntsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntsPage dialog

class CEntsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CEntsPage)

// Construction
public:
	CEntsPage();
	~CEntsPage();

// Dialog Data
	//{{AFX_DATA(CEntsPage)
	enum { IDD = IDD_ENTSORGUNG };
	CButton	m_btLiegtVor;
	CEdit	m_edANummer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEntsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetControlState (void);
	// Generated message map functions
	//{{AFX_MSG(CEntsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnLiegtVor();
	afx_msg void OnChangeAnummer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
