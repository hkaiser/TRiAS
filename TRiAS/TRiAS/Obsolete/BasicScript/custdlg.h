#ifndef _CUSTDLG_H
#define _CUSTDLG_H

// custdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustDlg dialog

class CCustDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CCustDlg)
	
	WAnpassen			m_IA;
	WScriptContainer	m_ISC;

	vector< int >		vID;
	CString				m_strOldMenuEntry;

	bool m_fSave;

public:
	// Construction
	static CCustDlg* CreateInstance (void);

	CCustDlg();
	~CCustDlg();

// Dialog Data
	//{{AFX_DATA(CCustDlg)
	enum { IDD = IDD_CUSTOMIZEDLG };
	CTreeCtrl	m_trMenuItem;
	CButton	m_OK;
	CButton	m_Rechts;
	CEdit	m_edMenuItem;
	CButton	m_Loeschen;
	CButton	m_Einfuegen;
	CButton	m_Links;
	CComboBox	m_cbProjectMacros;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCustDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEinfuegen();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBeginlabeleditMenutree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditMenutree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLoeschen();
	afx_msg void OnSelChangeMacroList();
	afx_msg void OnSelchangedMenutree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void		Reset(void);
	bool		ResetItems(HTREEITEM hItem);

	HTREEITEM	GetParentNextVisible(void);
	HTREEITEM	GetParentSelectedItem(void);
	CString		GetTextSelectedItem(void);
	DWORD		GetDataSelectedItem(void);

	HRESULT		FillLists(void);
	
	bool		OnEinfuegenInTree(void);
	bool		GetEnvItems(UINT &uiPreID, UINT &uiSucID,
							HTREEITEM hItem);

	bool		SetNewMenu(HTREEITEM hItem);
	bool		SetMenuEntry(HTREEITEM hItem);
	bool		Delete(void);
	bool		CustomizeMenu(HTREEITEM hItem);
	void 		GetInterfaces(void);
	bool		Save(void);
};

HRESULT		Fill(CWnd *pWnd, bool fCB, IScriptContainer * pISC);

typedef enum tagCUSTFLAGS {
	CUSTFLAGS_EDIT = 0x01,		
	CUSTFLAGS_NEWMACRO = 0x02,
	CUSTFLAGS_DELETE = 0x04,
	CUSTFLAGS_INIT = 0x08,
} CUSTOMIZEFLAGS;

typedef struct tagITEMDATA {
	UINT flags;
	CString strMacroText;
	UINT uiID;
} ITEMDATA;

#endif // _CUSTDLG_H
