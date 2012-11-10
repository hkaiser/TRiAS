// OpProDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenProjektDlg dialog

class COpenProjektDlg : public CDialog
{
// Construction
public:
	CString			m_strPfad;
	CTriDBSet*		m_pSetTriDB;
	CVerzSet*		m_pSetVerz;
	COrteSet*		m_pSetOrte;
	CStrasseSet*	m_pSetStrasse;

	COpenProjektDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenProjektDlg)
	enum { IDD = IDD_OPENPROJEKT };
	CButton	m_btnOK;
	CStatic	m_txtProjekt;
	CStatic	m_txtStrasse;
	CStatic	m_txtOrt;
	CStatic	m_txtIDE;
	CEdit	m_edIDE;
	CComboBox	m_cbStrasse;
	CComboBox	m_cbOrt;
	CComboBox	m_cbProjekt;
	CString	m_strIDE;
	//}}AFX_DATA
	short m_iCurrOISY, m_iCurrISY;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenProjektDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitOkButton();
	CMapStringToString* m_pmapStrassen;
	CStringArray m_arrOrte;
	CStringArray m_arrProjName;
	CStringArray m_arrVerz;

	void	SetupProjektListe();

	// Generated message map functions
	//{{AFX_MSG(COpenProjektDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProjekt();
	afx_msg void OnSelchangeOrt();
	afx_msg void OnSelchangeStrasse();
	afx_msg void OnChangeIDE();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
