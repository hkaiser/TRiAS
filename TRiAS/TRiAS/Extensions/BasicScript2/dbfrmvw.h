// dbfrmvw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDebFormView : public CFormView
{
protected:
	CDebFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDebFormView)

// Form Data
public:
	//{{AFX_DATA(CDebFormView)
	enum { IDD = IDD_TREECAPTIONDLG };
	CTabCtrl	m_tabProject;
	CStatic	m_stTreeCaption;
	CRelMacroTreeBox	m_treeRelMacros;
	//}}AFX_DATA

// Attributes
public:
	CRelMacroTreeBox* GetTreeCtrl() { return &m_treeRelMacros; }
	BOOL Init (UINT uiManID);
	BOOL ResetIfOnClose (UINT & uiManID);
	UINT GetManID();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDebFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDebFormView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTabproject(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString m_strTab;
	CImageList m_ImageList;
	int m_iInitialTabItemsWidth;

	HRESULT SetTabsOnSize(int iViewWindowWidth); 
	HRESULT InitialTabs(void); 

	int m_iSelect;
};

