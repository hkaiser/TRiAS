#if !defined(AFX_PPGSELMAPTYPE_H__245D2DB0_FE26_11D1_8F55_0060085FC1CE__INCLUDED_)
#define AFX_PPGSELMAPTYPE_H__245D2DB0_FE26_11D1_8F55_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CPpgSelMapType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgSelMapType dialog

typedef map<HTREEITEM, CComPtr<IUnknown> > MapDWToIUnk;

class CPpgSelMapType : 
	public CPropertyPage 
{
private:
	DECLARE_DYNCREATE(CPpgSelMapType)
	virtual void UpdateControls();

	MapDWToIUnk	m_mapOfEngines;

	CImageList m_ilImages;

//	CString	m_strDisplayName;
// Construction
public:
	CPpgSelMapType();
	~CPpgSelMapType();

// Dialog Data
	//{{AFX_DATA(CPpgSelMapType)
	enum { IDD = IDD_PPGSELMAPTYPE };
	CTreeCtrlEx	m_treeOfEngines;
	CString	m_strDesc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgSelMapType)
	public:
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgSelMapType)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeofengines(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoTreeofengines(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTreeofengines(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustButtons();
	BOOL AdjustDataForSelectedItem(HTREEITEM hItem);
	void AdjustNextPage();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGSELMAPTYPE_H__245D2DB0_FE26_11D1_8F55_0060085FC1CE__INCLUDED_)
