/////////////////////////////////////////////////////////////////////////////
// CBasePpg dialog

class CBasePpg : public CPropertyPage {
	DECLARE_DYNCREATE(CBasePpg)

	CBasePpg();
// Construction
public:
	CBasePpg( UINT nID );
	~CBasePpg();

// Dialog Data
	BOOL	m_bIsActive;
	//{{AFX_DATA(CBasePpg)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBasePpg)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBasePpg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
