#if !defined(AFX_PPGNOMENCLATUR_H__B6A2F49A_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_)
#define AFX_PPGNOMENCLATUR_H__B6A2F49A_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PpgNomenclatur.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgNomenclatur dialog

class CPpgNomenclatur : public CPropertyPage {
	DECLARE_DYNCREATE(CPpgNomenclatur)
	virtual void UpdateControls();
// Construction
public:
	CPpgNomenclatur();
	~CPpgNomenclatur();

// Dialog Data
	//{{AFX_DATA(CPpgNomenclatur)
	enum { IDD = IDD_PPGNOMENCLATUR };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgNomenclatur)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgNomenclatur)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGNOMENCLATUR_H__B6A2F49A_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_)
