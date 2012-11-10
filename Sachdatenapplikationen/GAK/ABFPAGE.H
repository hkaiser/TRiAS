// AbfPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbfPage dialog
class CAbfArtSet;
class CSelNumberDlg;

class CAbfPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CAbfPage)

// Construction
public:
	CAbfPage();
	~CAbfPage();

	// CString GetName ();
	// CString GetVorbehandlung (void);
	// CString GetMengeT (void);
	// CString GetSonderAbfall (void);
	
// Dialog Data
	//{{AFX_DATA(CAbfPage)
	enum { IDD = IDD_ABFAELLE };
	CEdit	m_edVerfahren;
	CErzNrEdit	m_edEAKNummer;
	CEdit	m_edVerbringung;
	CButton	m_btChange;
	CButton	m_btVorbehandlung;
	CStatic	m_stArtenInfo;
	CRealEditBegrenzt m_edMengeT;
	CStatic	m_stSonderAbfall;
	CEdit	m_edDichte;
	CBitmapButton m_btArtNeu;
	CBitmapButton m_btArtDel;
	CBitmapButton m_btArtChange;
	CEdit	m_edAbfArt;
	CRealEditBegrenzt	m_edMengeM;
	CListBox	m_lbAbfallArt;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAbfPage)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetCaption();
	double m_dDichte;
	BOOL m_bOutputArten, m_bAction;
	CAbfArtSet *m_pSet;
	CSelNumberDlg *m_pDlg;	

	BOOL OpenDialog (void);		// Auswahl-Dialog erzeugen
	// BOOL FindActRecord();		// gehe auf akt. Satz
	void OutputAbfarten ();		// gebe Arten in Listbox aus
	void SetControlState (bool disableall = false);	
	void OutputArtenParameter ();
	void OutputMengen (int iType, double dInputMenge = 0.0);
	int OpenSet ();
	// Generated message map functions
	//{{AFX_MSG(CAbfPage)
	afx_msg void OnArtDel();
	afx_msg void OnKillfocusMengem();
	afx_msg void OnKillfocusMenget();
	afx_msg void OnSelchangeAbfallart();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnChangeName(UINT, LONG);
	afx_msg LONG OnChangeNummer(UINT, LONG);
	afx_msg LONG OnDeleteDlg(UINT, LONG);
	virtual BOOL OnInitDialog();
	afx_msg void OnArtneu();
	afx_msg void OnArtChange();
	afx_msg void OnChangeVerbringung();
	afx_msg void OnChangeVerfahren();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
