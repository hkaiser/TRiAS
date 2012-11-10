#if !defined(AFX_IMAGEPROPERTYSHEET_H__8D0D8507_DB27_4A96_AA8D_E3D60DD41355__INCLUDED_)
#define AFX_IMAGEPROPERTYSHEET_H__8D0D8507_DB27_4A96_AA8D_E3D60DD41355__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImagePropertySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImagePropertySheet

class CImagePropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CImagePropertySheet)

// Construction
public:
	CImagePropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CImagePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagePropertySheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImagePropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImagePropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_iLastActivePage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROPERTYSHEET_H__8D0D8507_DB27_4A96_AA8D_E3D60DD41355__INCLUDED_)
