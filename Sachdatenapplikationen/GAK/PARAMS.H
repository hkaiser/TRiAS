// params.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog

class CParameters : public CDialog
{
// Construction
public:
	CParameters(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CParameters)
	enum { IDD = IDD_PARAMS };
	CEdit	m_edLastAsn;
	CButton	m_btOutputTable;
	CButton	m_btErzeuger;
	CComboBox	m_cbAbfallTableVJ;
	CComboBox	m_cbErzeugerTable;
	CComboBox	m_cbBgsTable;
	CComboBox	m_cbAbfallTable;
	CRealEdit m_edMengeRec;
	CRealEdit m_edMenge;
	CEdit m_edLastErzeuger;
	CButton	m_btErzeugerListe;
	CStatic	m_stErzListe;
	CButton	m_btSonderAbfall;
	CButton	m_btOK;
	CEdit	m_edOutputDB;
	CString	m_strLastErzeuger;
	int		m_iPrioritaet;
	int		m_iModus;
	//}}AFX_DATA
	
	CString m_strLastAsn;
	CString m_strAbfallTable;
	CString m_strErzeugerTable;
	CString m_strBGSTable;
	CString m_strOutputTable;
	CString m_strAbfallTableVJ;
	CString m_strErzListe;
	double m_dMenge, m_dMengeRec;
	BOOL m_bOnlySonderAbfall;
	BOOL m_bAbfallAppend;
	BOOL m_bErzListeAppend;
	BOOL m_bOnlyThisErzeuger;
	BOOL m_bLockErzeugerSelection;
	BOOL m_bLockAbfaelleSelection;
	
	CDatabase *m_pFoxProDB;
	CDatabase *m_pMdbDB;
	
// Implementation
protected:                
	void SetControlState (void);

	CEdit * HasFocus () { return (CEdit *) GetFocus (); }       
	void SetOkButton (void);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

//	SQL-Anweisung ausführen
	//BOOL ExecuteSQL (const char *pSQL);
	
//	FoxPro-Tabelle öffnen                  
	void OpenDBFTable (CString &strTableName, BOOL &bAppend, CString strCaption);

	// Generated message map functions
	//{{AFX_MSG(CParameters)
	afx_msg void OnOutputDb();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeMenge();
	afx_msg void OnSelchangeAbfallTable();
	afx_msg void OnSelchangeBgsTable();
	afx_msg void OnSelchangeErzeugerTable();
	afx_msg void OnSonderabfall();
	afx_msg void OnCreateErzliste();
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnInsert();
	afx_msg void OnDelete();
	afx_msg void OnSelect();
	afx_msg void OnBack();
	afx_msg void OnHelp();
	virtual void OnOK();
	afx_msg void OnChangeMengeRec();
	afx_msg void OnSelchangeVjabfallTable();
	//afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnAbgleich();
	afx_msg void OnKontrolle();
	afx_msg void OnLastErzNrText();
	afx_msg void OnChangeErzNummer();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};
