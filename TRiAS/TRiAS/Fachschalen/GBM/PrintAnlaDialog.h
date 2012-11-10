// PrintAnlaDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintAnlaDialog dialog

class CPrintAnlaDialog : public CDialog
{
// Construction
public:
	CPrintAnlaDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintAnlaDialog)
	enum { IDD = IDD_PRINT_ANLAGE };
	CComboBox	m_cbUmfang;
	BOOL	m_bSort;
	CString	m_strObjekt;
	//}}AFX_DATA

	// Inputvariablen
	CString		m_strIDE;		// Ident des akt. Grundstückes
	CString		m_strGrund;		// Bezeichnung Einzelgrundstück
	CString		m_strStr;		// Bezeichnung Straße
	CString		m_strOrt;		// Bezeichnung Ortslage
	CString		m_strOrte;		// Bezeichnung Gesamtprojekt
	CString		m_strSelected;	// Bezeichnung Ausgewählte GS
	CString		m_strMarked;	// Bezeichnung Markierte GS
	short		m_iA1, m_iA2, m_iA3;	// Anzahl Grundstücke (jeweils)
	short		m_iA4, m_iA5;

	// Outputvariablen
	short		m_iUmfang;	// 0 ==> Einzelgrundstück, ...
	short		m_iVonAnlage;
	short		m_iBisAnlage;
	short		m_iSelAnlaMode;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintAnlaDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void	SelectAnlage( short );

	// Generated message map functions
	//{{AFX_MSG(CPrintAnlaDialog)
	afx_msg void OnSelectUmfang();
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
