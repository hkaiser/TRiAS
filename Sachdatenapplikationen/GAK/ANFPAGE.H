// AnfallStelle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnfallStelle dialog
class CSelectSet;
class CSelNumberDlg;

class CAnfallStelle : public CPropertyPage
{
	DECLARE_DYNCREATE(CAnfallStelle)

// Construction
public:
	CAnfallStelle();
	~CAnfallStelle();

// Dialog Data
	//{{AFX_DATA(CAnfallStelle)
	enum { IDD = IDD_ANFALLSTELLE };
	CEdit	m_edKreisK;
	CButton	m_btChange;
	CEdit	m_edGKZ;
	CEdit	m_edOrtsName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAnfallStelle)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSelNumberDlg *m_pNumberDlg;		// NummerDialog
	CSelectSet *m_pSet;
	CDaoRecordset *m_pKreisSet;

	CString SetKreisInfo (const char *pGKZ);
	void SetControlState (void);
	int OpenSet ();
	// Generated message map functions
	//{{AFX_MSG(CAnfallStelle)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeGKZ();
	afx_msg LONG OnChangeGemeindeName(UINT, LONG);
	afx_msg LONG OnChangeGemeindeNummer(UINT, LONG);
	afx_msg LONG OnDeleteNumberDlg(UINT, LONG);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
