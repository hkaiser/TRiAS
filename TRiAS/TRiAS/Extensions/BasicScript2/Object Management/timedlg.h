#ifndef _TIMEDLG_H
#define _TIMEDLG_H

class CObjectManagement;
class CHideTimerDialog : public CDialog
{
private:

	// Construction
public:
	CHideTimerDialog(CObjectManagement *pIOM, CWnd* pParent = NULL);   // standard constructor
	~CHideTimerDialog(void);

// Dialog Data
	//{{AFX_DATA(CAddFunctionDlg)
	enum { IDD = IDD_HIDETIMERDLG};
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddFunctionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHideTimerDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	CObjectManagement *m_pObjectManagement;
};

#endif _TIMEDLG_H
