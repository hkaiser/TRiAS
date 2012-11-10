/////////////////////////////////////////////////////////////////////////////
// erweiterte Controls, die das ganze Handling etwas vereinfachen

#ifndef __AFXCMN_H__
	#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // __AFXCMN_H__

class CTreeCursor;
//		class CTreeCtrl
			class CTreeCtrlEx;
//		class CListCtrl
			class CListCtrlEx;

#if defined(_DEBUG)
		#pragma comment( lib, "LibCtrlExtD.lib" )
#elif defined(_RDEBUG)
		#pragma comment( lib, "LibCtrlExtR.lib" )
#elif defined(NDEBUG)
		#pragma comment( lib, "LibCtrlExt.lib" )
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCursor

class CTreeCursor {
	// Attributes
protected:
	HTREEITEM	m_hTreeItem;
	CTreeCtrlEx	*m_pTree;

	// Implementation
protected:
	CTreeCursor CTreeCursor::_Insert(LPCTSTR strItem,int nImageIndex,HTREEITEM hAfter);

	// Operation
public:
	CTreeCursor();
	CTreeCursor(HTREEITEM hTreeItem, CTreeCtrlEx* pTree);
	CTreeCursor(const CTreeCursor& posSrc);
	~CTreeCursor();
	const CTreeCursor& operator =(const CTreeCursor& posSrc);
	operator HTREEITEM();

	CTreeCursor InsertAfter(LPCTSTR strItem,HTREEITEM hAfter,int nImageIndex = -2);
	CTreeCursor AddHead(LPCTSTR strItem,int nImageIndex = -2);
	CTreeCursor AddTail(LPCTSTR strItem,int nImageIndex = -2);

	int GetImageID();

	BOOL GetRect(LPRECT lpRect, BOOL bTextOnly);
	CTreeCursor GetNext(UINT nCode);
	CTreeCursor GetChild();
	CTreeCursor GetNextSibling();
	CTreeCursor GetPrevSibling();
	CTreeCursor GetParent();
	CTreeCursor GetFirstVisible();
	CTreeCursor GetNextVisible();
	CTreeCursor GetPrevVisible();
	CTreeCursor GetSelected();
	CTreeCursor GetDropHilight();
	CTreeCursor GetRoot();
	CString GetText();
	BOOL GetImage(int& nImage, int& nSelectedImage);
	UINT GetState(UINT nStateMask);
	DWORD GetData();
	BOOL Set(UINT nMask, LPCTSTR lpszItem, int nImage, 
		int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam);
	BOOL SetText(LPCTSTR lpszItem);
	BOOL SetImage(int nImage, int nSelectedImage);
	BOOL SetState(UINT nState, UINT nStateMask);
	BOOL SetData(DWORD dwData);
	BOOL HasChildren();
// Operations
	BOOL Delete();

	BOOL Expand(UINT nCode = TVE_EXPAND);
	CTreeCursor Select(UINT nCode);
	CTreeCursor Select();
	CTreeCursor SelectDropTarget();
	CTreeCursor SelectSetFirstVisible();
	CEdit* EditLabel();
	CImageList* CreateDragImage();
	BOOL SortChildren();
	BOOL EnsureVisible();
};

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

class CTreeCtrlEx : public CTreeCtrl {
	// Attributes
protected:

	// Operation
public:
	CTreeCtrlEx();
	~CTreeCtrlEx();
	CImageList* SetImageList(CImageList* pImageList, int nImageListType = TVSIL_NORMAL);

	CTreeCursor GetNextItem(HTREEITEM hItem, UINT nCode);
	CTreeCursor GetChildItem(HTREEITEM hItem);
	CTreeCursor GetNextSiblingItem(HTREEITEM hItem);
	CTreeCursor GetPrevSiblingItem(HTREEITEM hItem);
	CTreeCursor GetParentItem(HTREEITEM hItem);
	CTreeCursor GetFirstVisibleItem();
	CTreeCursor GetNextVisibleItem(HTREEITEM hItem);
	CTreeCursor GetPrevVisibleItem(HTREEITEM hItem);
	CTreeCursor GetSelectedItem();
	CTreeCursor GetDropHilightItem();
	CTreeCursor GetRootItem();
	CTreeCursor InsertItem(LPTV_INSERTSTRUCT lpInsertStruct);
	CTreeCursor InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
		int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam, 
		HTREEITEM hParent, HTREEITEM hInsertAfter);
	CTreeCursor InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, 
		HTREEITEM hInsertAfter = TVI_LAST);
	CTreeCursor InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	CTreeCursor Select(HTREEITEM hItem, UINT nCode);
	CTreeCursor SelectItem(HTREEITEM hItem);
	CTreeCursor SelectDropTarget(HTREEITEM hItem);
	CTreeCursor SelectSetFirstVisible(HTREEITEM hItem);
	CTreeCursor HitTest(CPoint pt, UINT* pFlags = NULL);
	CTreeCursor HitTest(TV_HITTESTINFO* pHitTestInfo);
};

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

class CListCtrlEx : public CListCtrl {
	// Attributes
protected:

	// Operation
public:
	CListCtrlEx();
	~CListCtrlEx();
	CImageList* SetImageList(CImageList* pImageList, int nImageListType = TVSIL_NORMAL);
	BOOL AddColumn(
		LPCTSTR strItem,int nItem,int nSubItem = -1,
		int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
		int nFmt = LVCFMT_LEFT);
	BOOL AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex = -1);
};

#ifdef	_AFX_ENABLE_INLINES
#define	_AFXWIN_INLINE AFX_INLINE
#include	"lmfcx/lafxCtrl.inl"
#endif
