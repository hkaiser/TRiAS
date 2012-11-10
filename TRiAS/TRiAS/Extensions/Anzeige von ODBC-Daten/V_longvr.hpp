// v_longvr.hpp : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewLongVar dialog

class CViewLongVar : public CDialog
{                                           
private:
	ErrCode m_sRC; 
	CLongBinary *m_pCLongBinary;

// Construction
public:
	CViewLongVar(CWnd* pParent, CLongBinary* Value, CString& Caption);
	~CViewLongVar (void);				 

// Dialog Data
	//{{AFX_DATA(CViewLongVar)
	enum { IDD = IDD_LONGVAR };
	CEdit	m_Line;
	CString	m_strCaption;
	//}}AFX_DATA
	
	BOOL Result (void) { return m_sRC == EC_OKAY; }
	void Show (void);		// Fenster darstellen

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	//{{AFX_MSG(CViewLongVar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMaxtextLongvar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
