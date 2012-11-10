// abglpge.hpp : header file
//

#ifndef _ABGLEICH_PAGE
#define _ABGLEICH_PAGE

/////////////////////////////////////////////////////////////////////////////
// CAbgleichPage dialog

class CAbgleichPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CAbgleichPage)

// Construction
public:
	CAbgleichPage();
	~CAbgleichPage();

	BOOL GetUserEntries (BOOL bGet = TRUE);

// Dialog Data
	//{{AFX_DATA(CAbgleichPage)
	enum { IDD = IDD_ABGLEICH };
	CButton	m_btTrias;
	CButton	m_btTable;
	CListBox m_lbAuswahl;
	CEdit m_edAuswahl;
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAbgleichPage)
	public:
	virtual void OnCancel();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef WIN32
	// Generated message map functions
	//{{AFX_MSG(CAbgleichPage)
	afx_msg void OnEditchangeAbgleich();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeAbgleich();
	afx_msg void OnDestroy();
	//}}AFX_MSG
#else           
	afx_msg void OnEditchangeAbgleich();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeAbgleich();
	afx_msg void OnDestroy();
    afx_msg LONG OnSetFocusToControl (UINT, LONG);
#endif	// WIN16	
	DECLARE_MESSAGE_MAP()
	
	void SetOkButton ();			//	Ok-Button aktivieren/deaktivieren
	BOOL ReadParams (void);			// akt. Parameter lesen
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd :: GetParent (); }
	BOOL ReadActSelection (const char *);	//	lese Einstellungen zur akt. Selektion	
};

#endif          //_ABGLEICH_PAGE

