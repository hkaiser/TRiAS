// ImpRslt2.hpp : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportResult2 dialog
#ifndef _IMP_RSLT2_HPP
#define _IMP_RSLT2_HPP

class CImportResult2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CImportResult2)

// Construction
public:
	CImportResult2();
	~CImportResult2();

// Dialog Data
	//{{AFX_DATA(CImportResult2)
	enum { IDD = IDD_IMP_ABGL_RES2 };
	CStatic	m_stDoppTable;
	CStatic	m_stDoppTrias;
	CStatic	m_stValNew;
	CStatic	m_stValError;
	CStatic	m_stValDoppTrias;
	CStatic	m_stValDoppTable;
	CStatic	m_stValDelete;
	CStatic	m_stValAbgleich;
	CStatic	m_stNew;
	CStatic	m_stError;
	CStatic	m_stDelete;
	CStatic	m_stAbgleich;
	//}}AFX_DATA


#ifdef WIN32
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImportResult2)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImportResult2)
	afx_msg void OnShowProtokoll();
	//}}AFX_MSG
#else		// WIN16	
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImportResult2)
	protected:
	virtual BOOL DestroyWindow();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LONG OnSetFocusToControl (UINT, LONG);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImportResult2)
	afx_msg void OnShowProtokoll();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
#endif		// WIN16	 
	DECLARE_MESSAGE_MAP()

	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd :: GetParent (); }
	void GetResults (void);
};

#endif		// _IMP_RSLT2_HPP
