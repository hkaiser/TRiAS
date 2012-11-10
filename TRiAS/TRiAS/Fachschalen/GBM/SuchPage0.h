// SuchPage0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuchPage0 dialog

class CSuchPage0 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSuchPage0)

// Construction
public:
	CSuchPage0();
	~CSuchPage0();

// Dialog Data
	//{{AFX_DATA(CSuchPage0)
	enum { IDD = IDD_SUCH0 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSuchPage0)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bInit;
	// Generated message map functions
	//{{AFX_MSG(CSuchPage0)
	afx_msg void OnRadio1();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
