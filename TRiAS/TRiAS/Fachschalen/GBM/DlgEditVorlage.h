// DlgEditVorlage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditVorlage dialog

//class CSetVorlagen;

class CDlgEditVorlage : public CDialog
{
//	CSetVorlagen	*m_pSetVorlagen;

// Construction
public:
	CDlgEditVorlage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditVorlage)
	enum { IDD = IDD_EDITVORLAGEN };
	CButton	m_btnSelect;
	CButton	m_btnPreview;
	CButton	m_btnNeu;
	CButton	m_btnEdit;
	CListBox	m_lbListe;
	CString	m_strPfad;
	CString	m_strSelectedVName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditVorlage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_cKode[128];
	short m_nVType[128];
	BOOL CreateVorlage( const char*, short );
	CString m_strStandardPfad;
	int GetSelIndex();
	void SetupListe();
	CStringArray m_strarrStatus;
	void InitVorlage( const char*, const char*, short );
	CStringArray m_strarrPfade;
	CStringArray m_strarrVListe;

	// Generated message map functions
	//{{AFX_MSG(CDlgEditVorlage)
	afx_msg void OnEdit();
	afx_msg void OnNeu();
	afx_msg void OnPreview();
	afx_msg void OnSelect();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
