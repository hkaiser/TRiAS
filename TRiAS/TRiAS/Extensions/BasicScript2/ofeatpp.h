#ifndef _OFEATPP_H
#define _OFEATPP_H

// ofeatdlg.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CObjFeatScriptDlg dialog

class CObjFeatInstallDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CObjFeatInstallDlg)

private:
	HRESULT FillListBox(void);
	HRESULT SaveInfo(IObjectManagement *pIOM, IStreamInfo *pISI, DWORD dwInfo, CString str);
	HRESULT Install(void);
	HRESULT	SetApplyButton(HRESULT hr = S_OK);
	HRESULT GetCooky(IObjectManagement *,LPCSTR lpcstr, DWORD & dwID);
	HRESULT SetCooky(IObjectManagement *pIOM, LPCSTR lpcstr, DWORD dwID);
	HRESULT Install(IObjectManagement *pIOM, LPCSTR lpcstr);
	HRESULT Uninstall(IObjectManagement *pIOM, LPCSTR lpcstr);
	HRESULT RefreshObject(IObjectManagement *pIOM, LPCSTR lpcstr, LPUNKNOWN *ppUnk);
	void InitDialogControls(void);

	bool m_fMustBeGray;
	bool m_fLock;
public:
// Construction
	CObjFeatInstallDlg();   // standard constructor
	virtual ~CObjFeatInstallDlg(void);   

// Dialog Data
	//{{AFX_DATA(CObjFeatInstallDlg)
	enum { IDD = IDD_OBJFEATINSTALLPP };
	CStatic	m_staticAvailableItems;
	CCheckListBox	m_clbxMacroList;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjFeatInstallDlg)
	public:
	virtual void OnOK();
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjFeatInstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMacrolist();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //_OFEATPP_H
