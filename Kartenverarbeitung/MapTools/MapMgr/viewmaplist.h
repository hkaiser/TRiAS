#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewMapList form view

class CViewMapList : public CFormView
{
protected:
	void ChangePicture();
	void ReloadListBox();
	CMapMgrDoc* GetDocument() const;
	CViewMapList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewMapList)

// Form Data
public:
	//{{AFX_DATA(CViewMapList)
	enum { IDD = IDD_FORM_MAPLIST };
	CUpDownList	m_lbMapIdents;
	CString	m_strMapIdent;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewMapList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewMapList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewMapList)
	afx_msg void OnSelchangeMaplist();
	afx_msg void OnDblclkMaplist();
	//}}AFX_MSG
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	afx_msg void OnAddItem();
	afx_msg void OnDelItem();
	DECLARE_MESSAGE_MAP()
};

#ifdef NDEBUG
inline CMapMgrDoc* CViewMapList::GetDocument() const
{
	return (CMapMgrDoc*) CFormView::GetDocument();
}
#endif

/////////////////////////////////////////////////////////////////////////////
