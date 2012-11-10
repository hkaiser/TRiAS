#ifndef _EDITCRTL_H
#define _EDITCRTL_H

// editctrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditCtrl window

class CEditCtrl : public CWnd
{
// Construction/Destruction
public:
	CEditCtrl();
	virtual ~CEditCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditCtrl)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditCtrl)
	afx_msg void OnDebugGo();
	afx_msg void OnDebugTracein();
	afx_msg void OnNcDestroy();
	afx_msg void OnDebugTraceover();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CebDebugger *m_pDebugger;
	HACCEL m_hAccel;

	CebDebugger *GetDebugger(void) { return m_pDebugger; }
	bool GetAccelerator(void);
	bool SubClassEditWindow (CebDebugger *pDeb);
};

/////////////////////////////////////////////////////////////////////////////

#endif // _EDITCRTL_H
