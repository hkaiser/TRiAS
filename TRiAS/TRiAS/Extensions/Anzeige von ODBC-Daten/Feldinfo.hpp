// feldinfo.hpp : header file
// Stand vom 30.06.1994
// Erarbeitet: J. Benkenstein	
//
                                                  
class CColumnObjArray;
	                                                  
/////////////////////////////////////////////////////////////////////////////
// CFeldInfo dialog

class CFeldInfo : public CDialog
{                    
private:
	BOOL m_bResult;
	CColumnObjArray *m_pCA;	

// Construction
public:
	CFeldInfo (CWnd* pParent, CColumnObjArray *pCA);

// Dialog Data
	//{{AFX_DATA(CFeldInfo)
	enum { IDD = IDD_FIELDINFO };
	CListBox m_lbFieldInfo;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA   
	
	BOOL Result (void) { return m_bResult; }

// Implementation
protected:
	BOOL ChangeCaption (int iSel);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CFeldInfo)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeFeldList (void);
	virtual BOOL OnInitDialog(void);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
