/////////////////////////////////////////////////////////////////////////////
// CPgOptDraw dialog

class CPgOptDraw : public CBasePpg {
	DECLARE_DYNCREATE(CPgOptDraw)

// Construction
public:
	CPgOptDraw();
	~CPgOptDraw();

// Dialog Data
	//{{AFX_DATA(CPgOptDraw)
	enum { IDD = IDD_PG_OPTDRAW };
	BOOL	m_bBanding;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgOptDraw)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPgOptDraw)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
