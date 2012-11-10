// resdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultDialog dialog

class CResultDialog : public CDialog
{
// Construction
public:
	CResultDialog(CWnd* pParent, BOOL bAbgleich);
	
	BOOL OutputErzeugerListe ();

// Dialog Data
	//{{AFX_DATA(CResultDialog)
	enum { IDD = IDD_RESULT };
	CStatic	m_stDeletedRec;
	CButton	m_btErzListe;
	CString m_strErzListe;
	CDatabase *m_pDatabase;
	CString	m_strAbglCnt;
	CString	m_strEscCnt;
	CString	m_strInListeCnt;
	CString	m_strOutputCnt;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CResultDialog)
	afx_msg void OnOutputErzliste();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL m_bAbgleich;
};
