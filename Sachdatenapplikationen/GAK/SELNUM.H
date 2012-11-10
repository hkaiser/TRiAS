// SelNum.h : header file
//

class CSelectSet;

/////////////////////////////////////////////////////////////////////////////
// CSelNumberDlg dialog

class CSelNumberDlg : public CDialog
{
// Construction
public:
//	nichtmodaler Dialog
	CSelNumberDlg (CWnd* pParent, CSelectSet *pSet, 
				   UINT iCaptionID, const char *pTableName, const char *pSelection = NULL,
				   UINT uiThirdFieldId = 0, BOOL bReadName = FALSE);

//	modaler Dialog
	CSelNumberDlg (CWnd* pParent, CSelectSet *pSet, 
				   const char *pTableName, UINT iCaptionID, 
				   BOOL bReadName = FALSE, const char *pSelection = NULL);

	CString m_strNumber;
	void StoreSelection (const char *pNummer, const char *pName = NULL);

// Dialog Data
	//{{AFX_DATA(CSelNumberDlg)
	enum { IDD = IDD_SEL_NUMMER };
	CStatic	m_stCnt;
	CEdit	m_edSearch;
	CEdit	m_edNummer;
	CButton	m_btStore;
	CButton	m_btOk;
	CListCtrl m_lcListe;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelNumberDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	protected:
	BOOL m_bIsModal, m_bReadName, m_bIngnoreChange;
	CWnd *m_pParent;
	CString m_strSelection, m_strName;	// selekt. Name
	CString m_strTableName;
	CSelectSet *m_pSet;
	UINT m_uiCaptionID;
	UINT m_uiThirdFieldId;

	void ChangeName (const CString &strNewSel);
	BOOL ChangeNummer (const CString &strNewSel);
	void SendValues (void);			// Werte an Parent senden

// Generated message map functions
	//{{AFX_MSG(CSelNumberDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClickSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnChangeSearch();
	afx_msg void OnChangeNummer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
