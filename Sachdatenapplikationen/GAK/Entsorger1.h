#if !defined(AFX_ENTSORGER1_H__0E95DA03_726A_11D2_8CC2_006097A8F384__INCLUDED_)
#define AFX_ENTSORGER1_H__0E95DA03_726A_11D2_8CC2_006097A8F384__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Entsorger1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntsorger1 dialog

class CEntsorger1 : public CBranchPage
{
	DECLARE_DYNCREATE(CEntsorger1)

// Construction
public:
	CEntsorger1(UINT uiID = IDD_ENTSORGER1);
	~CEntsorger1();

// Dialog Data
	//{{AFX_DATA(CEntsorger1)
	enum { IDD = IDD_ENTSORGER1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEntsorger1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void SetControlState (bool bDisableAll = false);	// JG Schalten der Ctrl's

	virtual int OpenSet (void);
	// Generated message map functions
	//{{AFX_MSG(CEntsorger1)
	afx_msg LONG OnChangeNummer(UINT, LONG);
	afx_msg void OnChange();
	afx_msg void OnCopyClipboard();
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	virtual BOOL GetStringData(CString& strTarget);	// ermitteln der Daten des Dialoges als String
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

// some special Text operators
#define ADDTEXT(str1, str2)			\
	str1 += str2 + _T("\r");

#define ADDWINDOWTEXT(ctrl, string) \
{									\
	CString strTemp;				\
	ctrl.GetWindowText(strTemp);	\
	ADDTEXT(string, strTemp);		\
}

#endif // !defined(AFX_ENTSORGER1_H__0E95DA03_726A_11D2_8CC2_006097A8F384__INCLUDED_)
