// RectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRectDlg dialog

class CRectDlg : public CDialog
{
// Construction
public:
	CRectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRectDlg)
	enum { IDD = IDD_MANIPRECT };
	long	m_lFrameLeft;
	long	m_lFrameTop;
	long	m_lFrameRight;
	long	m_lFrameBottom;
	long	m_lClipLeft;
	long	m_lClipTop;
	long	m_lClipRight;
	long	m_lClipBottom;
	long	m_lPageLeft;
	long	m_lPageTop;
	long	m_lPageRight;
	long	m_lPageBottom;
	long	m_lRectLeft;
	long	m_lRectTop;
	long	m_lRectRight;
	long	m_lRectBottom;
	BOOL	m_bUseMetaFile;
	//}}AFX_DATA
	BOOL	m_bEditClipBox;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetPage();
	afx_msg void OnSetRect();
	afx_msg void OnSetFrame();
	afx_msg void OnSetClipBox();
	afx_msg void OnChangeTB();
	afx_msg void OnChangeLR();
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnSetfocusEdit2();
	afx_msg void OnSetfocusEdit3();
	afx_msg void OnSetfocusEdit4();
	afx_msg void OnSetfocusEdit5();
	afx_msg void OnSetfocusEdit6();
	afx_msg void OnSetfocusEdit7();
	afx_msg void OnSetfocusEdit8();
	afx_msg void OnSetfocusEdit9();
	afx_msg void OnSetfocusEdit10();
	afx_msg void OnSetfocusEdit11();
	afx_msg void OnSetfocusEdit12();
	afx_msg void OnSetfocusEdit13();
	afx_msg void OnSetfocusEdit14();
	afx_msg void OnSetfocusEdit15();
	afx_msg void OnSetfocusEdit53();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
