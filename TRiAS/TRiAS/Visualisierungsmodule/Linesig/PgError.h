// PgError.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPgError dialog

class CPgError : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgError)

// Construction
public:
	CPgError();
	CPgError( CStringArray *pError );
	~CPgError();

// Dialog Data
	//{{AFX_DATA(CPgError)
	enum { IDD = IDD_PROPPAGE_ERROR };
	CListBox	m_listError;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgError)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStringArray	*m_pError;
	// Generated message map functions
	//{{AFX_MSG(CPgError)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
