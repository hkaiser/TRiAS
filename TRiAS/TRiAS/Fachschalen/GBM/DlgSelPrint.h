// DlgSelPrint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelPrint dialog

class CDlgSelPrint : public CDialog
{
// Construction
public:
	CString m_strCaption;
	CDlgSelPrint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelPrint)
	enum { IDD = IDD_PRINT_ANLAGE1 };
	CCheckListBox	m_lbListe2;
	CCheckListBox	m_lbListe1;
	CComboBox	m_cbUmfang;
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
	BOOL		m_bSort;

	BOOL		m_bDok1, m_bVoll1;
	BOOL		m_bDok2, m_bVoll2;
	BOOL		m_bDok3, m_bVoll3;
	BOOL		m_bDok4, m_bVoll4;
	BOOL		m_bD1S1, m_bD1S2, m_bD1S3;
	BOOL		m_bD2S1, m_bD2S2, m_bD2S3;
	BOOL		m_bD3S1, m_bD3S2, m_bD3S3;
	BOOL		m_bD4S1;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelPrint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bExistB;
	BOOL m_bExistA;
	BOOL m_bExist9;
	BOOL m_bExist8;
	BOOL m_bExist7;

	// Generated message map functions
	//{{AFX_MSG(CDlgSelPrint)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListe1();
	virtual void OnOK();
	afx_msg void OnSelchangeListe2();
	afx_msg void OnSelectUmfang();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
