// BrancheP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrancheParam dialog
class CSelectSet;
class CBrancheParam : public CPropertyPage
{
	DECLARE_DYNCREATE(CBrancheParam)

// Construction
public:
	CBrancheParam();
	~CBrancheParam();

	CDaoQueryDef *m_pQueryDef;

// Dialog Data
	//{{AFX_DATA(CBrancheParam)
	enum { IDD = IDD_BRANCHE_PARAM };
	CButton	m_btAlle;
	CButton	m_btChange;
	CEdit	m_edName;
	CRealEdit m_edNummer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBrancheParam)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBrancheParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnChange();
	afx_msg void OnChangeName();
	afx_msg void OnHelp();
	afx_msg void OnChangeNummer();
	afx_msg void OnAlle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CSelectSet *m_pSet;
	CDaoParameterInfo m_QueryInfo;
	CDaoParameterInfo m_QueryInfoAlle;

	void OutputName (const CString &);
	void SetWButtons ();
};
