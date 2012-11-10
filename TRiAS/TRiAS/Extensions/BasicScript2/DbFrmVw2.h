// DbFrmVw2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebFormView2 form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDebFormView2 : public CFormView
{
protected:
	CDebFormView2();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDebFormView2)

	CDebuggerCtrl m_DebuggerCtrl;

// Form Data
public:
	//{{AFX_DATA(CDebFormView2)
	enum { IDD = IDD_DEBUGGERCAPTIONDLG };
	CStatic	m_stDebuggerCaption;
	//}}AFX_DATA

// Attributes
public:
	CDebuggerCtrl *GetDebuggerCtrl() { return &m_DebuggerCtrl; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebFormView2)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDebFormView2();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDebFormView2)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_iInitialStaticHeight;
};

/////////////////////////////////////////////////////////////////////////////
