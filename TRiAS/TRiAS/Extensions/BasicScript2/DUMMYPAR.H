#ifndef _DUMMYPAR_H
#define _DUMMYPAR_H

// dummypar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDummyParent dialog

class CDummyParent : public CDialog
{
// Construction
public:
	CDummyParent(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDummyParent)
	enum { IDD = IDD_DUMMYPARENT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDummyParent)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void CenterMe(CWnd* pAlternateOwner = NULL);
};

#endif //_DUMMYPAR_H
