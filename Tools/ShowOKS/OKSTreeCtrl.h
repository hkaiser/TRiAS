// OKSTreeCtrl.h : header file
//

#if !defined(AFX_OKSTREECTRL_H__DF6B9D03_C6A8_11D0_9598_00A024D6F582__INCLUDED_)
#define AFX_OKSTREECTRL_H__DF6B9D03_C6A8_11D0_9598_00A024D6F582__INCLUDED_

#include <ospace/std/set>
#include "OksTree.h"	// Added by ClassView

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DragDropTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// COksTreeCtrl window
class COksTreeCtrl : 
	public CDragDropTreeCtrl
{
/////////////////////////////////////////////////////////////////////////////
// Map für Überwachung der CheckMarks in den Parallel-Hierarchien
public:
	class CCheckMarkInfo
	{
	private:
		os_string m_strTempl;
		HTREEITEM m_hItem;

	public:
		CCheckMarkInfo (HTREEITEM hItem)
			: m_hItem(hItem) {}
		CCheckMarkInfo (HTREEITEM hItem, os_string strTempl)
			: m_hItem(hItem), m_strTempl(strTempl) {}
		CCheckMarkInfo (const CCheckMarkInfo &rCheck)
			: m_hItem(rCheck.GetItem()), m_strTempl(rCheck.GetTemplate()) {}

		CCheckMarkInfo &operator= (const CCheckMarkInfo &rhs)
			{
				if (&rhs != this) {
					m_hItem = rhs.GetItem();
					m_strTempl = rhs.GetTemplate();
				}
				return *this;
			}
		
		int operator< (CCheckMarkInfo &rhs) { return (LONG)rhs.GetItem()<(LONG)GetItem(); }	
		int operator< (const CCheckMarkInfo &rhs) const { return (LONG)rhs.GetItem()<(LONG)GetItem(); }	
		
		HTREEITEM GetItem() const { return m_hItem; }
		os_string GetTemplate() const { return m_strTempl; }
	};
	typedef set<CCheckMarkInfo, less<CCheckMarkInfo> > CCheckMarks;

// Construction
public:
	COksTreeCtrl();

// Attributes
public:
	bool IsSpecialNode (HTREEITEM hItem);
	bool IsExpanded (HTREEITEM hItem);

// Operations
public:
	HRESULT OpenAndParseFile (CString strFile, bool fAddNew = false);
	HRESULT FillControlWithData (void);
	bool InitControl (void);

	void HideStateImage (HTREEITEM hItem);
	UINT GetCheckState (HTREEITEM hItem);
	bool ToggleCheckMark (HTREEITEM hItem);

// Overridables to control drag-drop.   
    virtual void HandleItemMove (HTREEITEM hDragItem, CPoint point);
    virtual BOOL AllowDragOperation (HTREEITEM hItem);
    virtual void HandleDragMove (CImageList *pDragImage, CPoint& pt);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COksTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	os_string GetCode (HTREEITEM hItem = NULL);
	os_string GetCodeConverted (HTREEITEM hItem = NULL);
	os_string GetFullText (void);
	virtual ~COksTreeCtrl();

	HRESULT Save (IStream *pIStm, BOOL fClearDirty);
	HRESULT Load (IStream *pIStm);

	// Generated message map functions
protected:
	//{{AFX_MSG(COksTreeCtrl)
	afx_msg void OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnCheckStateChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	CImageList m_OKSImages;
	CImageList m_OKSCheckMarks;
	oks_tree m_OKSTree;
	CCheckMarks m_setCheck;

private:
	CPoint m_ptLast;
	bool m_fDoChecks;		// CheckMarks selbst machen
	UINT m_uiTimer;			// Timer fürs expandieren

protected:
	void HandleCheckMark (CPoint point, UINT uiMsg);
	void NotifyChecked (HTREEITEM hNewTarget, UINT uiMsg, UINT uiCheckState);
	bool AdjustImage (HTREEITEM hItem);
	bool AdjustChildImages (HTREEITEM hItem);

	os_string GetCheckTemplate (HTREEITEM hItem);
	bool MustRemoveCheck (os_string strNewTempl, os_string strTempl);
};

/////////////////////////////////////////////////////////////////////////////
// special support for CheckBox's in TreeCtrl's
#define TV_CHECK_OFF	(INDEXTOSTATEIMAGEMASK(1))
#define TV_CHECK_ON		(INDEXTOSTATEIMAGEMASK(2))

#define TVN_CHECKSTATECHANGED	(WM_USER+4321)

typedef struct tagNMTREEVIEWCHECK {
    NMHDR hdr;
    UINT action;
    HTREEITEM hItem;
	UINT state;
} NM_TREEVIEWCHECK;

/////////////////////////////////////////////////////////////////////////////
//
#define MAX_OKS_LEVEL	32		// max. 32 Stellen im OKS

/////////////////////////////////////////////////////////////////////////////
// Item expandieren, wenns lange genug aktiv ist
#define TIMER_EXPAND			1		
#define TIMER_EXPAND_TIMEOUT	400

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OKSTREECTRL_H__DF6B9D03_C6A8_11D0_9598_00A024D6F582__INCLUDED_)
