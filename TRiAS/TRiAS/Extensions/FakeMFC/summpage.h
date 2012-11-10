// summpage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSummPage dialog

class CSummPage : public CPropertyPage
{
        DECLARE_DYNCREATE(CSummPage)

// Construction
public:
        CSummPage();
        ~CSummPage();

	void SetSummInfo (CSummInfo *pSI);
	bool IsDirty (void) { return m_fDirty; }
	void SetDirty (bool fDirty = true) 
		{ m_fDirty = fDirty; SetModified (fDirty); }

// Dialog Data
	//{{AFX_DATA(CSummPage)
	enum { IDD = IDD_SUMM_PAGE };
	CString	m_strAuthor;
	CString	m_strKeywd;
	CString	m_strSubj;
	CString	m_strCmt;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSummPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSummPage)
	afx_msg void OnKillfocusAuthor();
	afx_msg void OnKillfocusComments();
	afx_msg void OnKillfocusKeywords();
	afx_msg void OnKillfocusSubject();
	afx_msg void OnKillfocusTitle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CSummInfo *m_pSummInfo;
	bool m_fDirty;

	void SaveChanges (void);
};
