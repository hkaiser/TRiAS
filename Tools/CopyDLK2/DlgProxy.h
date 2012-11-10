// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__AA38D4D5_E582_4AF5_AE0E_A7B518AF63EC__INCLUDED_)
#define AFX_DLGPROXY_H__AA38D4D5_E582_4AF5_AE0E_A7B518AF63EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCopyDLKDlg;

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKDlgAutoProxy command target

class CCopyDLKDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CCopyDLKDlgAutoProxy)

	CCopyDLKDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CCopyDLKDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyDLKDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCopyDLKDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CCopyDLKDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCopyDLKDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCopyDLKDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__AA38D4D5_E582_4AF5_AE0E_A7B518AF63EC__INCLUDED_)
