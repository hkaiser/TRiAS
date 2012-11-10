// EditIDEDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditIDEDlg dialog

class CEditIDEDlg : public CDialog
{
// Construction
public:
	BOOL m_bModDB;
	BOOL m_bModGS;
	BOOL m_bInDB;
	long m_lONr;
	CEditIDEDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditIDEDlg)
	enum { IDD = IDD_EDIT_IDE };
	CButton	m_btnOK;
	CString	m_strOldIDE;
	CString	m_strNeueIDE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditIDEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditIDEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	afx_msg void OnRadio();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
