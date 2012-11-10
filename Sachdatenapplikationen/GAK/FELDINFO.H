// FeldInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFeldInfos dialog
class CSelectSet;

class CFeldInfos : public CDialog
{
// Construction
public:
	CFeldInfos(CWnd* pParent, CSelectSet *pSet, 
			   const char *pCaption, const char *pTableName, const char *pName = NULL);   

// Dialog Data
	//{{AFX_DATA(CFeldInfos)
	enum { IDD = IDD_FELDINFO };
	CListCtrl	m_lcFeldInfos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeldInfos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSelectSet *m_pSet;
	CString m_strCaption, m_strTableName, m_strName;

	// Generated message map functions
	//{{AFX_MSG(CFeldInfos)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickFeldinfo(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
