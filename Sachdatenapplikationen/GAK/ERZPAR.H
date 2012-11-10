// ErzPar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErzeugerParam dialog
class CFirmaSet;
class CErzeugerParam : public CPropertyPage
{
	DECLARE_DYNCREATE(CErzeugerParam)

// Construction
public:
	CErzeugerParam();
	~CErzeugerParam();

	CDaoQueryDef *m_pQueryDef;

// Dialog Data
	//{{AFX_DATA(CErzeugerParam)
	enum { IDD = IDD_ERZEUGER_PARAM };
	CEdit	m_edName;
	CEdit	m_edNummer;
	CButton	m_btSelect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CErzeugerParam)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CErzeugerParam)
	afx_msg void OnHelp();
	afx_msg void OnErzeuger();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CDaoParameterInfo m_QueryInfo;
	void SetWButtons ();
	void OutputName (const CString &);

	CFirmaSet *m_pSet;
};
