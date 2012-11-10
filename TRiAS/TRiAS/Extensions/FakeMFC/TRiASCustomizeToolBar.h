///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CTRiASCustomizeToolBar.h | Description goes here

#if !defined(_TRIASCUSTOMIZETOOLBAR_H__A213557B_B102_11D2_95A2_006008447800__INCLUDED_)
#define _TRIASCUSTOMIZETOOLBAR_H__A213557B_B102_11D2_95A2_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRiASCustomizeToolBar dialog

class CTRiASCustomizeToolBar : public SECToolBarCmdPage
{
	DECLARE_DYNCREATE(CTRiASCustomizeToolBar)

// Construction
public:
	CTRiASCustomizeToolBar();
	~CTRiASCustomizeToolBar();

// Dialog Data
	//{{AFX_DATA(CTRiASCustomizeToolBar)
	enum { IDD = IDD_CUSTOMIZE_TOOLBAR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTRiASCustomizeToolBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTRiASCustomizeToolBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnSetActive();
	virtual void OnReset();

// Sets the button description based on id passed in
	virtual void SetDescription(int nID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_TRIASCUSTOMIZETOOLBAR_H__A213557B_B102_11D2_95A2_006008447800__INCLUDED_)
