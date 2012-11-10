#if !defined(AFX_SELNUMBERDLGUSAGE_H__D687F955_E68D_11D2_8D1B_006097A8F384__INCLUDED_)
#define AFX_SELNUMBERDLGUSAGE_H__D687F955_E68D_11D2_8D1B_006097A8F384__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelNumberDlgUsage.h : header file
//

class CSelectSet;
class CSelNumberDlg;

/////////////////////////////////////////////////////////////////////////////
// CSelNumberDlgUsage dialog
//
// Basisklasse für Dialoge, die die Klasse CSelDlg benutzen wollen
// die Funktionen DoChangeNummer, DoChangeName sind pur virtuell
// Um den entsprechenden Dialog aufzurufen, ist die funktion Change aufzurufen
class CSelNumberDlgUsage : public CDialog
{
// Construction
public:
	CSelNumberDlgUsage(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelNumberDlgUsage();
// Dialog Data
	//{{AFX_DATA(CSelNumberDlgUsage)
//	enum { IDD = 0};	// JG no default template
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelNumberDlgUsage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelNumberDlgUsage)
	afx_msg LONG OnChangeName(UINT, LONG);
	afx_msg virtual LONG OnChangeNummer(UINT, LONG);
	afx_msg LONG OnDeleteNumberDlg(UINT, LONG);	
	afx_msg void OnClose();
	// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void Change(const CString &strTableName, UINT uiCaption, CString& strAktNummer, CSelectSet* pSelectSet);
	virtual void DoChangeName(CString& strName) = NULL;
	virtual void DoChangeNummer(CString& strNummer) = NULL;

protected:
// Member
	CSelNumberDlg *m_pNumberDlg;		// NummerDialog
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELNUMBERDLGUSAGE_H__D687F955_E68D_11D2_8D1B_006097A8F384__INCLUDED_)
