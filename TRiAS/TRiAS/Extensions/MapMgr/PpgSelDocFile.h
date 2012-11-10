#if !defined(AFX_PPGSELDOCFILE_H__B6A2F499_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_)
#define AFX_PPGSELDOCFILE_H__B6A2F499_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PpgSelDocFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgSelDocFile dialog

class CPpgSelDocFile : public CPropertyPage {
	DECLARE_DYNCREATE(CPpgSelDocFile)
	virtual void UpdateControls();
// Construction
public:
	CPpgSelDocFile();
	~CPpgSelDocFile();

// Dialog Data
	//{{AFX_DATA(CPpgSelDocFile)
	enum { IDD = IDD_PPGSELDOCFILE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgSelDocFile)
//	public:
//	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgSelDocFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnASCIIFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButton m_btnCheckAscii;
	BOOL	m_bCheckAscii;
	CStatic	m_textDescription;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGSELDOCFILE_H__B6A2F499_1AF7_11D2_8F7D_0060085FC1CE__INCLUDED_)
