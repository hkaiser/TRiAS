// FirmaPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirmaPage dialog
class CFirmaPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFirmaPage)

// Construction
public:
	CFirmaPage();
	~CFirmaPage();

// Dialog Data
	//{{AFX_DATA(CFirmaPage)
	enum { IDD = IDD_FIRMA };
	CButton	m_btUnterschrift;
	CButton	m_btGetAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFirmaPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetControlState (void);
	// Generated message map functions
	//{{AFX_MSG(CFirmaPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetAddress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
