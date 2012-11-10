
// CScriptDlg.h : header file
//
#ifndef _SCRPTDLG_H
#define _SCRPTDLG_H
/////////////////////////////////////////////////////////////////////////////
// CScriptDlg dialog

class CScriptDlg : public CDialog
{
private:    
	HRESULT ImportFileToStorage();
	IObjectManagement	*m_pIObjManagement;
	IStreamInfo			*m_pIObjInfo;

	CString	m_strMacroName;

	BOOL m_fRun;
	BOOL m_fEntf;
	BOOL m_fOpenFile;
	BOOL m_fRunFile;
	BOOL m_fAutoStart;

	HRESULT	IsRunning(LPCSTR);
	HRESULT LinkScript(void);
	HRESULT	Stop(void);

	HRESULT SetButtons(void);
	HRESULT	FillListBox(void);
	HRESULT FindFileName(const CString & strLBName, CString & strPathName);
	UINT	OpenFileDialog (CString & strFileName, BOOL & fAuto, LPCSTR lpcstr);
	UINT	ImportFileDialog (CString & strFileName, LPCSTR lpcstrCaption) ;
	HRESULT SetAutoStart(void);

// Construction
public:
	
static CScriptDlg* CreateInstance(CWnd* pParent, IObjectManagement *pIObjectManagement, IStreamInfo *pISI);

		CScriptDlg(CWnd* pParent, IObjectManagement *m_pIObjManagement, IStreamInfo *pISI); 
		~CScriptDlg();

// Dialog Data
	//{{AFX_DATA(CScriptDlg)
	enum { IDD = IDD_SCRIPTDLG };
	CButton	m_cckAutoStart;
	CButton	m_Cancel;
	CButton	m_Run;
	CButton	m_Edit;
	CListBox	m_lbxMakroList;
	CEdit	m_eMacroName;
	//}}AFX_DATA

	BOOL	GetName(LPSTR , int);
	BOOL	GetDel (void) { return m_fEntf; }
	BOOL	GetRun (void) { return m_fRun; }	 
	BOOL	GetOpenFile (void) { return m_fOpenFile; }	 
	BOOL	GetRunFile (void) { return m_fRunFile; }	 
	BOOL	GetAutoStart (void) { return m_fAutoStart; }	 

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
	afx_msg void OnDblclkMakrolist();
	afx_msg void OnAutoStart();
	afx_msg void OnOpenfile();
	afx_msg void OnRunfile();
	afx_msg void OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
     
#endif // _SCRPTDLG_H

