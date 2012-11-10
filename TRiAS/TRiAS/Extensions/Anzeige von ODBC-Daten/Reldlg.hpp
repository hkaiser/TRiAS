// reldlg.hpp : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRelDialog dialog

class CRelDialog : public CDialog
{
// Construction
public:
	CRelDialog(CWnd* pParent, CString &strMaster, CString &strKoppelFeld, HPROJECT hPr);	// standard constructor
	
	ErrCode Result (void) { return m_ecResult; }

protected:                             
// Dialog Data
	//{{AFX_DATA(CRelDialog)
	enum { IDD = IDD_RELATIONS };
	CString m_strMaster, m_strKoppelFeld;
	CListBox m_CAddSlaveList, m_CDelSlaveList;
	CButton m_CFreeRelButton, m_CStoreButton, m_DelButton;
//	CBitmapButton m_btAddRel, m_btRemRel;
	//}}AFX_DATA              
	
	ErrCode m_ecResult;			// Op-Flag
	int m_sMaxStrLen,			// max. Zeichenlänge beider LBs
		  m_sType;				// SQL-DatenTyp

	HPROJECT m_hProject;
	
//	alle möglichen Slave-Anbindungen lesen
	ErrCode ReadSlaves (void);		// max. Zeichenlänge mitführen
	
//	zum aktuellen Master die Slave-Verbindungen lesen
	ErrCode ReadActSlaves (void);  // max. Zeichenlänge mitführen
	
//	aktuelle Anbindung speichern
	void StoreRel (void);	
	               
//	lese SQL-Type zur gegebenen Connection
	short GetSQLType (const char *pMaster, const char *pKoppelFeld);
	
//	selektierten Einträge innerhalb der ListBoxen austauschen	
	void ChangeSelection (CListBox &lbSrc, CListBox &lbDest);
		
// 	Implementation
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	// Generated message map functions
	//{{AFX_MSG(CRelDialog)
	afx_msg void OnAddSlave (void);
	afx_msg void OnDelSlave (void);	 
	afx_msg void OnDelete (void);
	afx_msg void OnOK (void); 
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelWeitere (void);
	afx_msg void OnSelVorhandene (void);	
	afx_msg void OnFreeRelation (void);		
	virtual BOOL OnInitDialog (void);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
