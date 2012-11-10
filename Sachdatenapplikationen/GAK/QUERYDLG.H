// QueryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog

class CQueryDialog : public CDialog
{
// Construction
public:
	CQueryDialog(CWnd* pParent = NULL);   // standard constructor
	~CQueryDialog(void);  

//	Recherche ausführen
	void DoRecherche (const CDaoQueryDefInfo &m_QueryInfo, BOOL bCallExtern = FALSE);
	CDaoQueryDefInfo m_QueryInfo;		// Info speichern

// Dialog Data
	//{{AFX_DATA(CQueryDialog)
	enum { IDD = IDD_QUERY_SELECT };
	CButton	m_btAbfrageArt;
	CStatic	m_stInfo;
	CButton	m_btImport;
	CStatic	m_stSelectInfo;
	CButton	m_btBlatt;
	CButton m_btListe;
	CListCtrl	m_lcQueries;
	CButton	m_btOk;
	CButton	m_btNew;
	CButton	m_btDelete;
	CButton	m_btChange;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bDatenBlatt;	// Ausgabe in Datenblatt
	CDaoDatabase m_Database;
	void SetControlState (void);				// Zustand der Controls setzen
	BOOL GetQueryInfo (CDaoQueryDefInfo &Info);	// Info der sel. Abfrage lesen
	BOOL CheckListenOutput (const CString strSQL);
	void ReadQueryDefCollection (void);			// Listbox neu füllen
	void SelectItem (const CString& strFind);	// Item selekt.	
	void GetParameters (CDaoQueryDef &Query);	// Parameter zur Abfrage lesen

	// Generated message map functions
	//{{AFX_MSG(CQueryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAendern();
	afx_msg void OnDelete();
	afx_msg void OnNeu();
	virtual void OnOK();
	afx_msg void OnClickQueries(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkQueries(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatenblatt();
	afx_msg void OnQueryListe();
	afx_msg void OnImport();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnStandard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
