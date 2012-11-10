// FeldInfoDialog.h : header file
//

#ifndef _FELDINFO_DIALOG
#define _FELDINFO_DIALOG

class CColumnObjArray;

/////////////////////////////////////////////////////////////////////////////
// CFeldInfoDialog dialog

class CFeldInfoDialog : public CDialog
{
private:
	BOOL m_bResult;
	CColumnObjArray *m_pCA;	
	short m_sNameSort, m_sLenSort, m_sTypeSort;
	
// Construction
public:
	CFeldInfoDialog(CWnd* pParent, CColumnObjArray *pCA);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFeldInfoDialog)
	enum { IDD = IDD_FIELDINFO };
	CListCtrl	m_lcFeldInfo;
	//}}AFX_DATA

	BOOL Result (void) { return m_bResult; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeldInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ChangeCaption (int iSel);

	// Generated message map functions
	//{{AFX_MSG(CFeldInfoDialog)
	afx_msg void OnDestroy();
	afx_msg void OnColumnclickFieldInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteitemFieldinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickFieldinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif		// _FELDINFO_DIALOG
