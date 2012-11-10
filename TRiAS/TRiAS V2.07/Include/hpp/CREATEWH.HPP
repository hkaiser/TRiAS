/*
Mit Hilfe dieses Dilaogs kann die WHERE-Klausel einer SQL-SELECT-Anweisung als
Kombination aus TRIAS-Merkmalen und Feldnamen einer Tabelle erzeugt werden.

Erarbeitet: J. Benkenstein 				Stand vom 28.10.1994
*/
  
#ifndef _CREATE_KLAUSEL
#define _CREATE_KLAUSEL  

/////////////////////////////////////////////////////////////////////////////
// CCreateWhereKlDlg dialog
                           
class CDataBaseExt;
                           
class CCreateWhereKlDlg : public CDialog
{
// Construction
public:
	CCreateWhereKlDlg(CWnd* pParent, CDataBaseExt *pDataBase,
					  CString &strKlausel, 
					  CString &strTableNames);	// durch Komma getrennt
					  
//	weitere Member
	ErrCode Result (void) { return m_ErrCode; }
					  
protected:					  
	CTableInfoTree m_TableTree;				// TableBaum

	BOOL ReadOperators (WORD wUnits);		// Init. OperatorListBox und Feld
	BOOL ReadFunctions (WORD wUnits);		// Init. FunctionListBox und Feld
	BOOL CheckKlausel (void);				//	aktuelle Klausel prüfen     
	 
	//	prüfe und lese Beschreibungs-Info einer skalaren Funktion
	void GetScaleFunction (uint &uIndex, uint uResID,	
						   UDWORD uwCheckFlag, UDWORD fFlag);

// Dialog Data
	//{{AFX_DATA(CCreateWhereKlDlg)
	enum { IDD = IDD_CREATE_WHERE };
	CListBox	m_lbFields;
	CListBox	m_lbFunctions;
	CListBox	m_lbOperators;
	CListBox	m_lbMerkmale;
	CEdit		m_edKlausel;
	CHelpText	m_stDescription;
	CButton	m_btBeenden;
	CButton	m_btCheckKlausel;
	CButton	m_btAsText, m_btAsDate, m_btAsNum;
	CString &m_strKlausel;
	CString &m_strTableNames;
	CDataBaseExt *m_pDataBase;                   
	ErrCode m_ErrCode;                  
	BOOL m_bParse;
	//}}AFX_DATA

// Implementation
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CCreateWhereKlDlg)
	afx_msg void OnChangeKlausel (void);
	afx_msg void OnCheckKlausel (void);
	afx_msg void OnSelchangeMerkmale (void);
	afx_msg void OnDblclkMerkmale (void);
	afx_msg void OnDblclkOperators (void);
	afx_msg void OnSelchangeOperators (void);
	afx_msg void OnSelchangeFunctions (void);
	afx_msg void OnDblclkFunctions (void);
	afx_msg void OnDblclkFields (void);
	virtual void OnOK (void);
	afx_msg void OnSelchangeFields (void);
	virtual BOOL OnInitDialog (void);
	afx_msg void OnAsText (void);
	afx_msg void OnAsDate (void);
	afx_msg void OnAsNum (void);	
	afx_msg void OnSetfocusKlausel (void);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 		// _CREATE_KLAUSEL

