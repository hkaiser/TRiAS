
// CScriptDlg.h : header file
//
#ifndef _SCRPTDLG_H
#define _SCRPTDLG_H
/////////////////////////////////////////////////////////////////////////////
// CScriptDlg dialog

class CScriptDlg : public CDialog
{
private:    
	HRESULT				IsRunning(const CString & str);
	HRESULT				Stop(const CString & str);

	bool				SetButtons(void);
	bool				FillList (IScriptContainer *pIScriptContainer);

	LPUNKNOWN			m_pMacroScripts;
	IScriptContainer	*m_pIScriptContainer;	
	CString				m_strMacroName;

	bool m_fRun;
	bool m_fEntf;


// Construction
public:
	
	CScriptDlg(CWnd* pParent = NULL, LPUNKNOWN pMacroScripts = NULL); 
				// standard constructor
	~CScriptDlg();

// Dialog Data
	//{{AFX_DATA(CScriptDlg)
	enum { IDD = IDD_SCRIPTDLG };
	CButton	m_cckAutoStart;
	CButton	m_Entfernen;
	CButton	m_Cancel;
	CButton	m_Run;
	CButton	m_Edit;
	CListBox	m_lbxMakroList;
	CEdit	m_eMacroName;
	//}}AFX_DATA

	bool	GetName(char *pc, int iLen);
	bool	GetDel (void) { return m_fEntf; }
	bool	GetRun (void) { return m_fRun; }	 
	HRESULT	Run	(LPCSTR lpstr);

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CScriptDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelChangeMakrolist();
	afx_msg void OnChangeMacroname();
	virtual void OnCancel();
	afx_msg void OnRun();
	afx_msg void OnEntfernen();
	afx_msg void OnDblclkMakrolist();
	afx_msg void OnAutoStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
     
#endif // _SCRPTDLG_H

