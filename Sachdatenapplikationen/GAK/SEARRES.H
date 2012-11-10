// SearRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchResult dialog
class CSearchSet;

class CSearchResult : public CDialog
{
// Construction
public:
	CSearchResult(CSearchSet *pSet, CWnd* pParent = NULL);  
	CSearchResult(CWnd* pParent = NULL);  
	~CSearchResult (void);

// Dialog Data
	//{{AFX_DATA(CSearchResult)
	enum { IDD = IDD_SEARCH_RESULT };
	CErzNrEdit	m_edErzNr;
	CButton	m_btStammdaten;
	CButton	m_btAbfaelle;
	CStatic	m_stFound;
	CListBoxExt m_lbNummern;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ReadRecordSet (void);
	void EnableControls (BOOL bEnable);
	void ShowData (BOOL bData);
	void SetItemCount (BOOL bFirstTime = FALSE);
	CSearchSet *m_pSet;
	// Generated message map functions
	//{{AFX_MSG(CSearchResult)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAbfaelle();
	afx_msg void OnStamm();
	afx_msg void OnSelchangeNummern();
	afx_msg void OnDblclkNummern();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnChangeErznr();
	afx_msg LONG OnRBDown (UINT, LONG);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
