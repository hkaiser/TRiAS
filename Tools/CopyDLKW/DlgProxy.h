// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__84FF7B43_85E9_4182_89B8_15F5FA27DCE0__INCLUDED_)
#define AFX_DLGPROXY_H__84FF7B43_85E9_4182_89B8_15F5FA27DCE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCopyDLKWDlg;

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKWDlgAutoProxy command target

class CCopyDLKWDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CCopyDLKWDlgAutoProxy)

	CCopyDLKWDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CCopyDLKWDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyDLKWDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCopyDLKWDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CCopyDLKWDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCopyDLKWDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCopyDLKWDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__84FF7B43_85E9_4182_89B8_15F5FA27DCE0__INCLUDED_)
