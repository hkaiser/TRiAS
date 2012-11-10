#if !defined(AFX_TRIASCHILD_H__139DED32_68CD_11D2_8CBD_006097A8F384__INCLUDED_)
#define AFX_TRIASCHILD_H__139DED32_68CD_11D2_8CBD_006097A8F384__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TRiASChild.h : header file
//

#include "Resource.h"	// Ressourcen

/////////////////////////////////////////////////////////////////////////////
// CTRiASChild dialog

class CTRiASChild : public CDialog
{
// Construction
public:
	CTRiASChild(CWnd* pParent = NULL, UINT uiResID = IDD);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTRiASChild)
	enum { IDD = IDD_TRIASCHILD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASChild)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	CComVariant GetIcon()
	{ 
		EnsureIcon();
		return CComVariant(reinterpret_cast<INT_PTR>(m_hIcon), VT_I4); 
	}

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTRiASChild)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool EnsureIcon();

// Datamember
protected:
	COLORREF m_BackColor;
	HICON m_hIcon;

// Accessors
public:
	void SetBackgroundColor(COLORREF cBackColor);	
	COLORREF GetBackgroundColor();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIASCHILD_H__139DED32_68CD_11D2_8CBD_006097A8F384__INCLUDED_)
