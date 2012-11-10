// SelectConnectionOpenNew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectionOpenNew dialog

class CSelectConnectionOpenNew : public CPropertyPage
{
	DECLARE_DYNCREATE(CSelectConnectionOpenNew)

// Construction
public:
	CSelectConnectionOpenNew(UINT uiID = IDD_NEW, UINT uiIDCap = IDD_CAPTION_NEW);
	~CSelectConnectionOpenNew();

// Dialog Data
	//{{AFX_DATA(CSelectConnectionOpenNew)
	enum { 
		IDD_NEW = IDD_CONNECTION_OPENNEW,
		IDD_CAPTION_NEW = IDS_CREATENEWWIZARD,
		IDD_ADD = IDD_CONNECTION_ADDDATASOURCE,
		IDD_CAPTION_ADD = IDS_ADDDATASOURCE,
	};
	CButton	m_rbCreateDatasource;
	CButton	m_rbOpenDatasource;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSelectConnectionOpenNew)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	// JG SetStandAlone should be public -> moving   public out of #if-brackets
public:
#if defined(_DEBUG)
// public:
	virtual BOOL OnWizardFinish();
#endif // _DEBUG

// Implementation
	void SetStandAlone() { m_fStandAlone = TRUE; }

	COpenNewPropertySheet *GetPropSheet()
	{
		ASSERT_KINDOF(COpenNewPropertySheet, GetParent());
		return (COpenNewPropertySheet *)GetParent();
	}

protected:
	// Generated message map functions
	//{{AFX_MSG(CSelectConnectionOpenNew)
	afx_msg void OnCreatedatasource();
	afx_msg void OnOpendatasource();
	virtual BOOL OnInitDialog();
	afx_msg void OnDoubleclickedCreatedatasource();
	afx_msg void OnDoubleclickedOpendatasource();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DATASOURCEMODE RetrieveOpenMode (void);
	void AdjustButtons(void);

private:
	DATASOURCEMODE m_iDatasourceMode;
	BOOL m_fStandAlone;
};
