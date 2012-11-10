#if !defined(AFX_PPGSELADDFILE_H__B6A2F499_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_)
#define AFX_PPGSELADDFILE_H__B6A2F499_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PpgSelAddFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgSelAddFile dialog

class CPpgSelAddFile : 
	public CPropertyPage 
{
	DECLARE_DYNCREATE(CPpgSelAddFile)
	virtual void UpdateControls();

// Construction
public:
	CPpgSelAddFile();
	~CPpgSelAddFile();

// Dialog Data
	//{{AFX_DATA(CPpgSelAddFile)
	enum { IDD = IDD_PPGSELADDFILE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgSelAddFile)
//	public:
//	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgSelAddFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonsrcmap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGSELADDFILE_H__B6A2F499_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_)
