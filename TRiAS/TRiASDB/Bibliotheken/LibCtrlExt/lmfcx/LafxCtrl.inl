#ifdef _AFXWIN_INLINE

/////////////////////////////////////////////////////////////////////////////
// CTreeCursor INLINE functions

_AFXWIN_INLINE CTreeCursor::CTreeCursor() : m_hTreeItem(NULL),	m_pTree(NULL)
	{ }
_AFXWIN_INLINE CTreeCursor::CTreeCursor(HTREEITEM hTreeItem,CTreeCtrlEx* pTree) : m_hTreeItem(hTreeItem), m_pTree(pTree)
	{ }
_AFXWIN_INLINE CTreeCursor::CTreeCursor(const CTreeCursor& posSrc)
	{ *this = posSrc; }
_AFXWIN_INLINE CTreeCursor::~CTreeCursor()
	{ }
_AFXWIN_INLINE CTreeCursor::operator HTREEITEM()
	{ return m_hTreeItem; }
_AFXWIN_INLINE CTreeCursor CTreeCursor::InsertAfter(LPCTSTR strItem,HTREEITEM hAfter,int nImageIndex)
	{ return _Insert(strItem,nImageIndex,hAfter); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::AddHead(LPCTSTR strItem,int nImageIndex)
	{ return _Insert(strItem,nImageIndex,TVI_FIRST); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::AddTail(LPCTSTR strItem,int nImageIndex)
	{ return _Insert(strItem,nImageIndex,TVI_LAST); }
_AFXWIN_INLINE BOOL CTreeCursor::GetRect(LPRECT lpRect, BOOL bTextOnly)
	{ return m_pTree->GetItemRect(m_hTreeItem,lpRect,bTextOnly); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetNext(UINT nCode)
	{ return m_pTree->GetNextItem(m_hTreeItem,nCode); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetChild()
	{ return m_pTree->GetChildItem(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetNextSibling()
	{ return m_pTree->GetNextSiblingItem(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetPrevSibling()
	{ return m_pTree->GetPrevSiblingItem(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetParent()
	{ return m_pTree->GetParentItem(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetFirstVisible()
	{ return m_pTree->GetFirstVisibleItem(); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetNextVisible()
	{ return m_pTree->GetNextVisibleItem(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetPrevVisible()
	{ return m_pTree->GetPrevVisibleItem(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetSelected()
	{ return m_pTree->GetSelectedItem(); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetDropHilight()
	{ return m_pTree->GetDropHilightItem(); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::GetRoot()
	{ return m_pTree->GetRootItem(); }
_AFXWIN_INLINE CString CTreeCursor::GetText()
	{ return m_pTree->GetItemText(m_hTreeItem); }
_AFXWIN_INLINE BOOL CTreeCursor::GetImage(int& nImage, int& nSelectedImage)
	{ return m_pTree->GetItemImage(m_hTreeItem,nImage,nSelectedImage); }
_AFXWIN_INLINE UINT CTreeCursor::GetState(UINT nStateMask)
	{ return m_pTree->GetItemState(m_hTreeItem,nStateMask); }
_AFXWIN_INLINE DWORD CTreeCursor::GetData()
	{ return m_pTree->GetItemData(m_hTreeItem); }
//_AFXWIN_INLINE BOOL SetItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
//	int nSelectedImage,	UINT nState,nStateMask,lParam);
_AFXWIN_INLINE BOOL CTreeCursor::SetText(LPCTSTR lpszItem)
	{ return m_pTree->SetItemText(m_hTreeItem,lpszItem); }
_AFXWIN_INLINE BOOL CTreeCursor::SetImage(int nImage, int nSelectedImage)
	{ return m_pTree->SetItemImage(m_hTreeItem,nImage,nSelectedImage); }
_AFXWIN_INLINE BOOL CTreeCursor::SetState(UINT nState, UINT nStateMask)
	{ return m_pTree->SetItemState(m_hTreeItem,nState,nStateMask); }
_AFXWIN_INLINE BOOL CTreeCursor::SetData(DWORD dwData)
	{ return m_pTree->SetItemData(m_hTreeItem,dwData); }
_AFXWIN_INLINE BOOL CTreeCursor::HasChildren()
	{ return m_pTree->ItemHasChildren(m_hTreeItem); }
// Operations
_AFXWIN_INLINE BOOL CTreeCursor::Delete()
	{ return m_pTree->DeleteItem(m_hTreeItem); }
_AFXWIN_INLINE BOOL CTreeCursor::Expand(UINT nCode)
	{ return m_pTree->Expand(m_hTreeItem,nCode); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::Select(UINT nCode)
	{ return m_pTree->Select(m_hTreeItem,nCode); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::Select()
	{ return m_pTree->SelectItem(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::SelectDropTarget()
	{ return m_pTree->SelectDropTarget(m_hTreeItem); }
_AFXWIN_INLINE CTreeCursor CTreeCursor::SelectSetFirstVisible()
	{ return m_pTree->SelectSetFirstVisible(m_hTreeItem); }
_AFXWIN_INLINE CEdit* CTreeCursor::EditLabel()
	{ return m_pTree->EditLabel(m_hTreeItem); }
_AFXWIN_INLINE CImageList* CTreeCursor::CreateDragImage()
	{ return m_pTree->CreateDragImage(m_hTreeItem); }
_AFXWIN_INLINE BOOL CTreeCursor::SortChildren()
	{ return m_pTree->SortChildren(m_hTreeItem); }
_AFXWIN_INLINE BOOL CTreeCursor::EnsureVisible()
	{ return m_pTree->EnsureVisible(m_hTreeItem); }

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx INLINE functions

_AFXWIN_INLINE CTreeCtrlEx::CTreeCtrlEx() : CTreeCtrl()
	{ }
_AFXWIN_INLINE CTreeCtrlEx::~CTreeCtrlEx()
	{ }
_AFXWIN_INLINE CImageList* CTreeCtrlEx::SetImageList(CImageList* pImageList, int nImageListType)
	{ return CTreeCtrl::SetImageList(pImageList,nImageListType); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetNextItem(HTREEITEM hItem, UINT nCode)
	{ return CTreeCursor(CTreeCtrl::GetNextItem(hItem,nCode),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetChildItem(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::GetChildItem(hItem),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetNextSiblingItem(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::GetNextSiblingItem(hItem),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetPrevSiblingItem(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::GetPrevSiblingItem(hItem),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetParentItem(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::GetParentItem(hItem),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetFirstVisibleItem()
	{ return CTreeCursor(CTreeCtrl::GetFirstVisibleItem(),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetNextVisibleItem(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::GetNextVisibleItem(hItem),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetPrevVisibleItem(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::GetPrevVisibleItem(hItem),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetSelectedItem()
	{ return CTreeCursor(CTreeCtrl::GetSelectedItem(),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetDropHilightItem()
	{ return CTreeCursor(CTreeCtrl::GetDropHilightItem(),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::GetRootItem()
	{ return CTreeCursor(CTreeCtrl::GetRootItem(),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::InsertItem(LPTV_INSERTSTRUCT lpInsertStruct)
	{ return CTreeCursor(CTreeCtrl::InsertItem(lpInsertStruct),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
	int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam, 
	HTREEITEM hParent, HTREEITEM hInsertAfter)
	{ return CTreeCursor(CTreeCtrl::InsertItem(nMask, lpszItem, nImage, 
		nSelectedImage, nState, nStateMask, lParam, hParent, hInsertAfter),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent,HTREEITEM hInsertAfter)
	{ return CTreeCursor(CTreeCtrl::InsertItem(lpszItem, hParent, hInsertAfter),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
		HTREEITEM hParent, HTREEITEM hInsertAfter)
	{ return CTreeCursor(CTreeCtrl::InsertItem(lpszItem, nImage, nSelectedImage,
		hParent, hInsertAfter),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::Select(HTREEITEM hItem, UINT nCode)
	{ return CTreeCursor(CTreeCtrl::Select(hItem,nCode) ? hItem : NULL,this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::SelectItem(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::SelectItem(hItem) ? hItem : NULL,this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::SelectDropTarget(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::SelectDropTarget(hItem) ? hItem : NULL,this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::SelectSetFirstVisible(HTREEITEM hItem)
	{ return CTreeCursor(CTreeCtrl::SelectSetFirstVisible(hItem) ? hItem : NULL,this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::HitTest(CPoint pt, UINT* pFlags)
	{ return CTreeCursor(CTreeCtrl::HitTest(pt,pFlags),this); }
_AFXWIN_INLINE CTreeCursor CTreeCtrlEx::HitTest(TV_HITTESTINFO* pHitTestInfo)
	{ return CTreeCursor(CTreeCtrl::HitTest(pHitTestInfo),this); }

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx INLINE functions

_AFXWIN_INLINE CListCtrlEx::CListCtrlEx() : CListCtrl()
 { }
_AFXWIN_INLINE CListCtrlEx::~CListCtrlEx()
 { }

_AFXWIN_INLINE CImageList* CListCtrlEx::SetImageList(CImageList* pImageList, int nImageListType)
 { return CListCtrl::SetImageList(pImageList,nImageListType); }

#endif //_AFXWIN_INLINE
