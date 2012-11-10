// SPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartPage2 dialog

class CStartPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CStartPage2)

// Construction
public:
	CString m_strIDE2;
	CString			m_strPfad;
	CTriDBSet*		m_pSetTriDB;
	CVerzSet*		m_pSetVerz;
	COrteSet*		m_pSetOrte;
	CStrasseSet*	m_pSetStrasse;

	CStartPage2();
	~CStartPage2();

// Dialog Data
	//{{AFX_DATA(CStartPage2)
	enum { IDD = IDD_STARTPAGE2 };
	CStatic	m_txtProjekt;
	CStatic	m_txtStrasse;
	CStatic	m_txtOrt;
	CStatic	m_txtIDE;
	CComboBox	m_cbProjekt;
	CComboBox	m_cbStrasse;
	CComboBox	m_cbOrt;
	CEdit	m_edIDE;
	CString	m_strIDE;
	//}}AFX_DATA
	short m_iCurrOISY, m_iCurrISY;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStartPage2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMapStringToString* m_pmapStrassen;
	CStringArray	m_arrOrte;
	CStringArray	m_arrProjName;
	CStringArray	m_arrVerz;
	BOOL			m_bInit;

	void		InitOkButton();
	void		SetupProjektListe();

	// Generated message map functions
	//{{AFX_MSG(CStartPage2)
	afx_msg void OnSelchangeOrt();
	afx_msg void OnSelchangeStrasse();
	afx_msg void OnSelchangeProjekt();
	afx_msg void OnChangeIDE();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
