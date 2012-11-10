// SPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartPage1 dialog

class CStartPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CStartPage1)

// Construction
public:
	short m_iMRU;
	short m_iSelect;
	CStartPage1();
	~CStartPage1();

// Dialog Data
	//{{AFX_DATA(CStartPage1)
	enum { IDD = IDD_STARTPAGE1 };
	CComboBox	m_cbMRU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStartPage1)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStringArray m_strarrMRU;
	// Generated message map functions
	//{{AFX_MSG(CStartPage1)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMRU();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
