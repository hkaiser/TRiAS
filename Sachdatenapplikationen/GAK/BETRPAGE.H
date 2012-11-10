// BetrPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBetreiberPage dialog

class CBetreiberPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBetreiberPage)

// Construction
public:
	CBetreiberPage();
	~CBetreiberPage();

// Dialog Data
	//{{AFX_DATA(CBetreiberPage)
	enum { IDD = IDD_BETREIBER };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBetreiberPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBetreiberPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
			
	void SetControlState (bool bDisableAll = false);	// JG Parameter hinzugefügt
};
