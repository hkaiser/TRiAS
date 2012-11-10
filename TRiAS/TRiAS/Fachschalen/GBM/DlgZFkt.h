// DlgZFkt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgZusatzFkt dialog

class CDlgZusatzFkt : public CDialog
{
// Construction
public:
	UINT m_uiResID;
	CString m_strParameter;
	CString m_strScriptResName;
	CStringArray* m_arrIM;
	CString m_strScriptFileName;
	CStringArray* m_arrZF;
	CDlgZusatzFkt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgZusatzFkt)
	enum { IDD = IDD_EXTRAS };
	CListBox	m_lbListe;
	CString	m_strEintrag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgZusatzFkt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT GetMacroResID( const char* );
	CMapStringToString m_mapMac;
	CMapStringToString m_mapFkt;
	CMapStringToString m_mapParam;

	// Generated message map functions
	//{{AFX_MSG(CDlgZusatzFkt)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
