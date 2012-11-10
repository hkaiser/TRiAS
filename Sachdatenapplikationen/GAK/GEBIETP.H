// GebietP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGebietParam dialog
class CSelectSet;
class CGebietParam : public CPropertyPage
{
	DECLARE_DYNCREATE(CGebietParam)

// Construction
public:
	CGebietParam();
	~CGebietParam();

	CDaoQueryDef *m_pQueryDef;

// Dialog Data
	//{{AFX_DATA(CGebietParam)
	enum { IDD = IDD_GEBIET_PARAM };
	CButton	m_btSelectGemeinde;
	CEdit	m_edGKZ;
	CStatic	m_stGemeinde;
	CButton	m_btSelectKreis;
	CButton	m_btAlleGemeinden;
	//}}AFX_DATA

	bool m_bSelectAll;	// kann der Knopf alle ausgewählt werden
	bool m_bSelect;		// kann ein Kreis/Gemeinde ausgewählt werden

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGebietParam)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGebietParam)
	afx_msg void OnHelp();
	afx_msg void OnAlleGemeinden();
	afx_msg void OnGemeindeSelect();
	afx_msg void OnKreisSelect();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeGkz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CSelectSet *m_pSet;
	CSelectSet *m_pSetKreis;
	CDaoParameterInfo m_QueryInfoGemeinde,
					  m_QueryInfoAlleGemeinden,	
					  m_QueryInfoKreis,
					  m_QueryInfoAlleKreise;

	void OutputName (const CString &, CSelectSet *pSet);
	void SetWButtons ();
};
