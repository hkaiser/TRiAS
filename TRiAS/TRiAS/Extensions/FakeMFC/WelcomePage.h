// WelcomePage.h : header file
//

#include "StaticFilespec.h"

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage dialog

class CWelcomePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CWelcomePage)

// Construction
public:
	CWelcomePage();
	~CWelcomePage();

// Dialog Data
	//{{AFX_DATA(CWelcomePage)
	enum { IDD = IDD_WIZARD_PAGE };
	CStaticFilespec	m_ftMRUProject;
	CButton	m_cbDontShowFurther;
	CButton	m_rbOpenOldProject;
	CButton	m_rbOpenLast;
	CButton m_rbCreateNew;
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

	COpenNewPropertySheet *GetPropSheet()
	{
		ASSERT_KINDOF(COpenNewPropertySheet, GetParent());
		return (COpenNewPropertySheet *)GetParent();
	}

// Implementation
public:
	PROJECTOPENMODE GetOpenMode (void) { return m_iOpenMode; }

protected:
	// Generated message map functions
	//{{AFX_MSG(CWelcomePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCreateNewProject();
	afx_msg void OnOpenMruProject();
	afx_msg void OnOpenOldProject();
	afx_msg void OnDoubleclickedCreatenewproject();
	afx_msg void OnDoubleclickedOpenmruproject();
	afx_msg void OnDoubleclickedOpenoldproject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustButtons(void);
	PROJECTOPENMODE RetrieveOpenMode (void);

private:
	PROJECTOPENMODE m_iOpenMode;
};
