// CreateNewParamWiz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateNewParamWiz dialog

class CCreateNewParamWiz : public CPropertyPage
{
	DECLARE_DYNCREATE(CCreateNewParamWiz)

// Construction
public:
	CCreateNewParamWiz();
	~CCreateNewParamWiz();

	enum CREATEMODE {
		CREATEMODE_Unknown = 0,
		CREATEMODE_ImportData = 1,
		CREATEMODE_EditData = 2,
	};

	CREATEMODE GetCreateMode (void) { return m_iCreateMode; }
	int GetIdentBase (void) { return m_iIdBase; }
	bool GetCompatibilityMode (void) { return m_fCompatible; }

	bool RegisterEntries (void);

// Dialog Data
	enum { 
		IDD = IDD_CREATENEWWIZARD_PARAMS,
		IDD_NT = IDD_CREATENEWWIZARD_PARAMS_NT,
	};
	//{{AFX_DATA(CCreateNewParamWiz)
	CButton	m_rbImportData;
	CButton	m_rbEditData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewParamWiz)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CREATEMODE RetrieveCreateMode (void);
	void AdjustButtons(void);

protected:
	// Generated message map functions
	//{{AFX_MSG(CCreateNewParamWiz)
	afx_msg void OnEditdata();
	afx_msg void OnImportdata();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_iIdBase;
	CREATEMODE m_iCreateMode;
	bool m_fCompatible;
};
