// DlgDocErrors.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPgDocErrors dialog

class CPgDocErrors : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgDocErrors)

// Construction
public:
	CStringArray m_strErrors;
	CPgDocErrors( );
	CPgDocErrors( UINT nIdCaption );
	~CPgDocErrors();

// Dialog Data
	//{{AFX_DATA(CPgDocErrors)
	enum { IDD = IDD_PG_INVALIDDOC };
	CListBox	m_lstErrors;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgDocErrors)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPgDocErrors)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
