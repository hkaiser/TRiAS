// PartPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPartnerPage dialog

class CPartnerPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPartnerPage)

// Construction
public:
	CPartnerPage();
	~CPartnerPage();

// Dialog Data
	//{{AFX_DATA(CPartnerPage)
	enum { IDD = IDD_ANSPRECH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPartnerPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetControlState (void);
	// Generated message map functions
	//{{AFX_MSG(CPartnerPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
