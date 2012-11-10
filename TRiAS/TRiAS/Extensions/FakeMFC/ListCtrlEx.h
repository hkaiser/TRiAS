// ListCtrlEx.h : header file
//

#if !defined(AFX_LISTCTRLEX_H__AFEAD085_7006_11D1_9749_00A024D6F582__INCLUDED_)
#define AFX_LISTCTRLEX_H__AFEAD085_7006_11D1_9749_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CInPlaceComboBox window

class CInPlaceComboBox : public CComboBox
{
// Construction
public:
	CInPlaceComboBox(int iItem, int iSubItem, CStringList *plstItems, int nSel);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceComboBox)
	public:	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcDestroy();	
	afx_msg void OnCloseup();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int m_iItem;
	int m_iSubItem;	
	CStringList m_lstItems;
	int m_nSel;
	BOOL m_bESC;				// To indicate whether ESC key was pressed
};

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit window

class CInPlaceEdit : public CEdit
{
// Construction
public:
	CInPlaceEdit(int iItem, int iSubItem, CString sInitText);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int m_iItem;
	int m_iSubItem;
	CString m_sInitText;
	BOOL m_bESC;		// To indicate whether ESC key was pressed
};

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window

class CListCtrlEx : 
	public CListCtrl
{
// Construction
public:
	CListCtrlEx();

// Attributes
public:

// Operations
public:
	int GetColumnCount(void) const;
	void FitColumn (int iCol = -1);
	int HitTestEx (CPoint &point, int *col) const;
	int InsertColumn(int nCol, UINT uiColHead,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	void SelectItem (int iIndex, BOOL fSel);

	CComboBox *ShowInPlaceList (int nItem, int nCol, CStringList &lstItems, 
		int nSel, UINT uiId = IDC_INPLACECOMBO);
	CEdit* EditSubLabel (int nItem, int nCol, UINT uiChildId = IDC_INPLACEEDIT);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#define MINCOLWIDTH		10

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLEX_H__AFEAD085_7006_11D1_9749_00A024D6F582__INCLUDED_)
