// DragDropTreeCtrl.h : header file
//

#if !defined(AFX_DRAGDROPTREECTRL_H__70AE4E54_CC45_11D0_95AA_00A024D6F582__INCLUDED_)
#define AFX_DRAGDROPTREECTRL_H__70AE4E54_CC45_11D0_95AA_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// globale Systemvariablen
extern const TCHAR g_cbWindowsSection[];
extern const TCHAR g_cbScrollInset[];
extern const TCHAR g_cbScrollDelay[];

/////////////////////////////////////////////////////////////////////////////
// CDragDropTreeCtrl window

class CDragDropTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CDragDropTreeCtrl();

// Attributes
public:
    void EnableDragDrop (bool fEnable = true) { m_fDragDrop = fEnable; }
	void HideCursor (bool fHide = true) { m_fHideCursor = fHide; }
	void EnableScrolling (bool fEnable = true) { m_fScroll = fEnable; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragDropTreeCtrl)
	//}}AFX_VIRTUAL

// Overridables to control drag-drop.   
    virtual void HandleItemMove (HTREEITEM hDragItem, CPoint point);
    virtual BOOL AllowDragOperation (HTREEITEM hItem);
    virtual void HandleDragMove (CImageList *pDragImage, CPoint& pt);

// Implementation
public:
	virtual ~CDragDropTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDragDropTreeCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg LRESULT OnCustomGetDlgCode (UINT wParam, LPARAM lParam);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	void ScrollUpDown (bool fUp);

private:
    void DoBeginDrag (NM_TREEVIEW *pTV);
    void DoEndDrag (CPoint point, BOOL bMoveItem);

private:
	bool m_fDragDrop;
	bool m_fDragging;
	bool m_fHideCursor;
	bool m_fScroll;
	CImageList *m_pDragImage;
	HTREEITEM m_hDragItem;
	UINT m_uiTimer;
};

/////////////////////////////////////////////////////////////////////////////
// aller 50ms HandleDragMove rufen
#define TIMER_FAKE_MOUSEMOVE			1234
#define TIMER_FAKE_MOUSEMOVE_TIMEOUT	200

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGDROPTREECTRL_H__70AE4E54_CC45_11D0_95AA_00A024D6F582__INCLUDED_)
