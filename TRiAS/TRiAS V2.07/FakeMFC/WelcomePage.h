// WelcomePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage dialog

class CWelcomePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CWelcomePage)

// Construction
public:
	CWelcomePage();
	~CWelcomePage();

	enum OPENMODE {
		OPENMODE_Unknown = 0,
		OPENMODE_OpenExistend = 1,
		OPENMODE_OpenMRU = 2,
		OPENMODE_CreateNew = 3,
	};

// Dialog Data
	//{{AFX_DATA(CWelcomePage)
	enum { IDD = IDD_WIZARD_PAGE };
	CStatic	m_ftMRUProject;
	CButton	m_cbDontShowFurther;
	CButton	m_rbOpenOldProject;
	CButton	m_rbOpenLast;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWelcomePage)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	OPENMODE GetOpenMode (void) { return m_iOpenMode; }

protected:
	// Generated message map functions
	//{{AFX_MSG(CWelcomePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCreateNewProject();
	afx_msg void OnOpenMruProject();
	afx_msg void OnOpenOldProject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustButtons(void);
	OPENMODE RetrieveOpenMode (void);

private:
	OPENMODE m_iOpenMode;
};
