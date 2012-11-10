// dsnpage.hpp : header file
//

#ifndef _DSN_PAGE_HPP
#define _DSN_PAGE_HPP

/////////////////////////////////////////////////////////////////////////////
// CDsnPage dialog

class CDsnPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDsnPage)

// Construction
public:
	CDsnPage();
	~CDsnPage();

// Dialog Data
	//{{AFX_DATA(CDsnPage)
	enum { IDD = IDD_DATENQUELLE };
	CTabbedDialogs m_tbDsn;
	CButton	m_btDelNotExist;
	CButton	m_btImpNotExist;
	CListBox	m_lbTable;
	CButton m_btTrias;
	CButton m_btTable;
	CString m_strTableName;
	CString m_strDataSource;
	CFileDlg m_dlgFileDsn;
	CUserDlg m_dlgUserDsn;
	CUserDlg m_dlgSystemDsn;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDsnPage)
	public:
	virtual void OnCancel();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	DataSourceType m_tDsn;

	// Generated message map functions
	//{{AFX_MSG(CDsnPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTable();
	afx_msg void OnButtonOnTable();
	afx_msg void OnButtonOnTrias();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL ModifyButtonsText (void);		// Button-Text akt.
	BOOL ReadParams (void);				// akt. Parameter lesen
	void SetControlState (void);		// Status aller Kontrols akt.
	void ResetOdbcInfos (void);			// Odbc-Infos rücksetzen	
	CPropertySheet *GetParent (void) { return (CPropertySheet *) 
											   CWnd :: GetParent (); }
public:
	BOOL GetUserEntries (BOOL bGet = TRUE);		// Nutzereingaben lesen
};

#endif 		// _DSN_PAGE_HPP


