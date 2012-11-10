//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//  09.06.93 A.D. uve Potsdam: inline ResID::ResID(uint) geaendert
#ifndef _CVINLINE_HXX
#define _CVINLINE_HXX


inline Pair :: Pair ()
{
	a = b = 0;
}

inline Pair :: Pair ( CoOrd aa, CoOrd bb )
{
	a = aa;
	b = bb;
}

inline Point :: Point ()
{
}

inline Point :: Point ( CoOrd x, CoOrd y )
	: Pair ( x, y )
{
}

inline CoOrd & Point :: X ()
{
	return a;
}

inline CoOrd & Point :: Y ()
{
	return b;
}

inline CoOrd Point :: GetX () const
{
	return a;
}

inline CoOrd Point :: GetY () const
{
	return b;
}

inline Dimension :: Dimension ()
{
}

inline Dimension :: Dimension ( CoOrd width, CoOrd height )
	: Pair ( width, height )
{
}

inline CoOrd & Dimension :: Width ()
{
	return a;
}

inline CoOrd & Dimension :: Height ()
{
	return b;
}

inline Range :: Range ()
{
}

inline Range :: Range ( CoOrd minimum, CoOrd maximum )
	: Pair ( minimum, maximum )
{
}

inline CoOrd & Range :: Min ()
{
	return a;
}

inline CoOrd & Range :: Max ()
{
	return b;
}

inline Selection :: Selection ()
{
}

inline Selection :: Selection ( CoOrd start, CoOrd end )
	: Pair ( start, end )
{
}

inline CoOrd & Selection :: Start ()
{
	return a;
}

inline CoOrd & Selection :: End ()
{
	return b;
}

inline Rectangle :: Rectangle ()
{
	left = right = bottom = top = 0;
}

inline Rectangle :: Rectangle ( Point topleft, Point bottomright )
	: top ( topleft.Y ()), left ( topleft.X ()),
	bottom ( bottomright.Y ()), right ( bottomright.X ())
{
}

inline Rectangle :: Rectangle ( CoOrd t, CoOrd l, CoOrd b, CoOrd r )
	: top ( t ), left ( l ), bottom ( b ), right ( r )
{
}

inline Point Rectangle :: UpperLeft ()
{
	return Point ( left, top );
}

inline Point Rectangle :: LowerRight ()
{
	return Point ( right, bottom );
}

inline CoOrd & Rectangle :: Left ()
{
	return left;
}

inline CoOrd & Rectangle :: Right ()
{
	return right;
}

inline CoOrd & Rectangle :: Top ()
{
	return top;
}

inline CoOrd & Rectangle :: Bottom ()
{
	return bottom;
}

inline CoOrd Rectangle :: Width ()
{
	return right-left;
}

inline CoOrd Rectangle :: Height ()
{
	return top-bottom;
}

inline CvID :: CvID ( uint i)
{
	id = i;
	str = 0;
}

inline CvID :: operator 	const char *()
{
	return str;
}

inline CvID :: operator uint ()
{
	return id; 
}

inline BOOL CvID :: operator==(uint i)
{
	return id == i;
}

inline BOOL operator==(uint n, CvID i) { return i.operator== (n); }

inline BOOL CvID :: operator==(const char*s)
{
	return id == CvID(s);
}

inline BOOL operator==(const char*s, CvID i) { return i.operator == (s); }

inline BOOL CvID :: operator==(CvID &i)
{
	return id == i.id;
}

/*  Der Compiler bevorzugt den Inline-Konstruktor!!?
inline ResID :: ResID ( uint i ) : CvID(i)
{
	src = 0;
}
*/


#ifndef NORESSTRING

inline const char* ResString :: Addr ()
{
	return string;
}

inline ResString :: operator const char*()
{
	return string;
}


inline int ResString :: Len ()
{
	return length;
}

#endif // NORESSTRING
#ifndef NOCOLOR

inline Color :: Color ()
{
	R = G = B = _reserved = 0;
}

inline Color :: Color ( uchar r, uchar g, uchar b )
{
	R = r; G = g; B = b; _reserved = 0;
}

inline uchar & Color :: Red ()
{
	return R;
}

inline uchar & Color :: Green ()
{
	return G;
}

inline uchar & Color :: Blue ()
{
	return B;
}

#endif // NOCOLOR

#ifndef NOCONTROL

inline Control :: Control ()
{
	// Do nothing
}

#ifndef NOSCROLLBAR

inline ScrollBar :: ScrollBar ()
{
	// Do nothing
}

#endif // NOSCROLLBAR
#ifndef NOTEXTCONTROL

inline TextControl :: TextControl ()
{
	// Do nothing
}

#ifndef NOBUTTON

inline Button :: Button ()
{
	// Do nothing
}

#endif // NOBUTTON
#ifndef NOLISTBOX

inline BaseListBox :: BaseListBox ()
{
	// Do nothing
}

#endif // NOLISTBOX
#ifndef NOEDIT

inline Edit :: Edit ()
{
	// Do nothing
}

#endif // NOEDIT
#endif // NOTEXTCONTROL
#endif // NOCONTROL

#if defined(WIN32)

#if !defined(NOWIN95CONTROLS)

// CImageList -----------------------------------------------------------------
#if !defined(NOIMAGEAPIS)
inline HIMAGELIST CImageList::Handle(Service) const
	{ return (this == NULL) ? NULL : m_hImageList; }

inline int CImageList::GetImageCount()
	{ return ImageList_GetImageCount(m_hImageList); }

inline int CImageList::Add(Bitmap* pbmImage, Bitmap* pbmMask)
	{ return ImageList_Add(m_hImageList, (HBITMAP)pbmImage->Handle(), (HBITMAP)pbmMask->Handle()); }

inline int CImageList::Add(Bitmap* pbmImage, COLORREF crMask)
	{ return ImageList_AddMasked(m_hImageList, (HBITMAP)pbmImage->Handle(), crMask); }

inline BOOL CImageList::Remove(int nImage)
	{ return ImageList_Remove(m_hImageList, nImage) ? true : false; }

inline BOOL CImageList::Replace(int nImage, Bitmap* pbmImage, Bitmap* pbmMask)
	{ return ImageList_Replace(m_hImageList, nImage, (HBITMAP)pbmImage->Handle(), (HBITMAP)pbmMask->Handle()) ? true : false; }

inline int CImageList::Add(Icon *pIcon)
	{ return ImageList_AddIcon(m_hImageList, (HICON)pIcon->Handle()); }

inline int CImageList::Replace(int nImage, Icon *pIcon)
	{ return ImageList_ReplaceIcon(m_hImageList, nImage, (HICON)pIcon->Handle()); }

inline HICON CImageList::ExtractIcon(int nImage)
	{ return ImageList_ExtractIcon(NULL, m_hImageList, nImage); }

inline COLORREF CImageList::SetBkColor(COLORREF cr)
	{ return ImageList_SetBkColor(m_hImageList, cr); }

inline COLORREF CImageList::GetBkColor()
	{ return ImageList_GetBkColor(m_hImageList); }

inline BOOL CImageList::Draw (HDC hDC, int nImage, Point pt, UINT nStyle)
	{ return ImageList_Draw (m_hImageList, nImage, hDC, pt.X(), pt.Y(), nStyle); }

inline BOOL CImageList::SetOverlayImage(int nImage, int nOverlay)
	{ return ImageList_SetOverlayImage(m_hImageList, nImage, nOverlay) ? true : false; }

inline BOOL CImageList::GetImageInfo(int nImage, IMAGEINFO* pImageInfo)
	{ return ImageList_GetImageInfo(m_hImageList, nImage, pImageInfo) ? true : false; }

inline BOOL CImageList::BeginDrag(int nImage, Point ptHotSpot)
	{ return ImageList_BeginDrag(m_hImageList, nImage, ptHotSpot.X(), ptHotSpot.Y()) ? true : false; }

inline void CImageList::EndDrag()
	{ ImageList_EndDrag(); }

inline BOOL CImageList::DragMove(Point pt)
	{ return ImageList_DragMove(pt.X(), pt.Y()) ? true : false; }

inline BOOL CImageList::SetDragCursorImage(int nDrag, Point ptHotSpot)
	{ return ImageList_SetDragCursorImage(m_hImageList, nDrag, ptHotSpot.X(), ptHotSpot.Y()) ? true : false; }

inline BOOL CImageList::DragShowNolock(BOOL bShow)
	{ return ImageList_DragShowNolock(bShow) ? true : false; }

inline CImageList* CImageList::GetDragImage(Point *lpPoint, Point *lpPointHotSpot)
	{ return new CImageList(ImageList_GetDragImage((LPPOINT)lpPoint, (LPPOINT)lpPointHotSpot));}

inline BOOL CImageList::DragEnter(pWindow pWndLock, Point point)
	{ return ImageList_DragEnter(pWndLock->Handle(API_WINDOW_HWND), point.X(), point.Y()) ? true : false; }

inline BOOL CImageList::DragLeave(pWindow pWndLock)
	{ return ImageList_DragLeave(pWndLock->Handle(API_WINDOW_HWND)) ? true : false; }
#endif // NOIMAGEAPIS

// CTreeViewCtrl --------------------------------------------------------------
#if !defined(NOTREEVIEW)

inline HTREEITEM CTreeViewCtrl::InsertItem (const TV_INSERTSTRUCT *lpInsertStruct)
	{  return (HTREEITEM)::SendMessage(Handle(), TVM_INSERTITEM, 0, (LPARAM)lpInsertStruct); }

inline HTREEITEM CTreeViewCtrl::InsertItem (LPCSTR lpszItem, int nImage, 
	int nSelectedImage, HTREEITEM hParent, HTREEITEM hInsertAfter)
	{ return InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE, lpszItem, nImage, nSelectedImage, 0, 0, 0, hParent, hInsertAfter); }

inline HTREEITEM CTreeViewCtrl::InsertItem (LPCSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
	{ return InsertItem(TVIF_TEXT, lpszItem, 0, 0, 0, 0, 0, hParent, hInsertAfter); }

inline BOOL CTreeViewCtrl::DeleteItem (HTREEITEM hItem)
	{ return ::SendMessage(Handle(), TVM_DELETEITEM, 0, (LPARAM)hItem) ? true : false; }

inline BOOL CTreeViewCtrl::DeleteAllItems (void)
	{ return ::SendMessage(Handle(), TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT) ? true : false; }

inline BOOL CTreeViewCtrl::Expand(HTREEITEM hItem, UINT nCode)
	{ return ::SendMessage(Handle(), TVM_EXPAND, nCode, (LPARAM)hItem) ? true : false; }

inline UINT CTreeViewCtrl::GetCount()
	{ return (UINT)::SendMessage(Handle(), TVM_GETCOUNT, 0, 0); }

inline UINT CTreeViewCtrl::GetIndent()
	{ return (UINT)::SendMessage(Handle(), TVM_GETINDENT, 0, 0); }

inline void CTreeViewCtrl::SetIndent(UINT nIndent)
	{ ::SendMessage(Handle(), TVM_SETINDENT, nIndent, 0); }

inline CImageList *CTreeViewCtrl::GetImageList(UINT nImageList)
	{ return new CImageList ((HIMAGELIST)::SendMessage(Handle(), TVM_GETIMAGELIST, (UINT)nImageList, 0)); }

inline CImageList *CTreeViewCtrl::SetImageList(CImageList* pImageList, int nImageListType)
	{ return new CImageList ((HIMAGELIST)::SendMessage(Handle(), TVM_SETIMAGELIST, (UINT)nImageListType, (LPARAM)pImageList->Handle())); }

inline HTREEITEM CTreeViewCtrl::GetNextItem(HTREEITEM hItem, UINT nCode)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, nCode, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::GetChildItem(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::GetNextSiblingItem(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::GetPrevSiblingItem(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_PREVIOUS, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::GetParentItem(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::GetFirstVisibleItem()
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_FIRSTVISIBLE, 0); }

inline HTREEITEM CTreeViewCtrl::GetNextVisibleItem(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_NEXTVISIBLE, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::GetPrevVisibleItem(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_PREVIOUSVISIBLE, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::GetSelectedItem()
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_CARET, 0); }

inline HTREEITEM CTreeViewCtrl::GetDropHilightItem()
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_DROPHILITE, 0); }

inline HTREEITEM CTreeViewCtrl::GetRootItem()
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_GETNEXTITEM, TVGN_ROOT, 0); }

inline HTREEITEM CTreeViewCtrl::Select(HTREEITEM hItem, UINT nCode)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_SELECTITEM, nCode, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::SelectItem(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_SELECTITEM, TVGN_CARET, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::SelectDropTarget(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_SELECTITEM, TVGN_DROPHILITE, (LPARAM)hItem); }

inline HTREEITEM CTreeViewCtrl::SelectSetFirstVisible(HTREEITEM hItem)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_SELECTITEM, TVGN_FIRSTVISIBLE, (LPARAM)hItem); }

inline BOOL CTreeViewCtrl::GetItem(TV_ITEM *pItem)
	{ return ::SendMessage(Handle(), TVM_GETITEM, 0, (LPARAM)pItem) ? true : false; }

inline BOOL CTreeViewCtrl::SetItem(const TV_ITEM *pItem)
	{ return ::SendMessage(Handle(), TVM_SETITEM, 0, (LPARAM)pItem) ? true : false; }

inline BOOL CTreeViewCtrl::SetItemText(HTREEITEM hItem, LPCSTR lpszItem)
	{ return SetItem(hItem, TVIF_TEXT, lpszItem, 0, 0, 0, 0, NULL); }

inline BOOL CTreeViewCtrl::SetItemImage(HTREEITEM hItem, int nImage, int nSelectedImage)
	{ return SetItem(hItem, TVIF_IMAGE|TVIF_SELECTEDIMAGE, NULL, nImage, nSelectedImage, 0, 0, NULL); }

inline BOOL CTreeViewCtrl::SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask)
	{ return SetItem(hItem, TVIF_STATE, NULL, 0, 0, nState, nStateMask, NULL); }

inline BOOL CTreeViewCtrl::SetItemData(HTREEITEM hItem, DWORD dwData)
	{ return SetItem(hItem, TVIF_PARAM, NULL, 0, 0, 0, 0, (LPARAM)dwData); }

inline HTREEITEM CTreeViewCtrl::HitTest(TV_HITTESTINFO *pHitTestInfo)
	{ return (HTREEITEM)::SendMessage(Handle(), TVM_HITTEST, 0, (LPARAM)pHitTestInfo); }

inline UINT CTreeViewCtrl::GetVisibleCount()
	{ return (UINT)::SendMessage(Handle(), TVM_GETVISIBLECOUNT, 0, 0); }

inline CImageList* CTreeViewCtrl::CreateDragImage(HTREEITEM hItem)
	{ return new CImageList ((HIMAGELIST)::SendMessage(Handle(), TVM_CREATEDRAGIMAGE, 0, (LPARAM)hItem)); }

inline BOOL CTreeViewCtrl::SortChildren(HTREEITEM hItem)
	{ return ::SendMessage(Handle(), TVM_SORTCHILDREN, 0, (LPARAM)hItem) ? true : false; }

inline BOOL CTreeViewCtrl::EnsureVisible(HTREEITEM hItem)
	{ return ::SendMessage(Handle(), TVM_ENSUREVISIBLE, 0, (LPARAM)hItem) ? true : false; }

inline BOOL CTreeViewCtrl::SortChildrenCB(LPTV_SORTCB pSort)
	{ return ::SendMessage(Handle(), TVM_SORTCHILDRENCB, 0, (LPARAM)pSort) ? true : false; }

inline SingleLineEdit *CTreeViewCtrl::GetEditControl (void)
	{ return new SingleLineEdit(GetParent(), (HWND)::SendMessage(Handle(), TVM_GETEDITCONTROL, 0, 0)); }

inline SingleLineEdit *CTreeViewCtrl::EditLabel (HTREEITEM hItem)
	{ return new SingleLineEdit(GetParent(), (HWND)::SendMessage(Handle(), TVM_EDITLABEL, 0, (LPARAM)hItem)); }

#endif // NOTREEVIEW

#if !defined(NOLISTVIEW)

inline COLORREF CListViewCtrl::GetBkColor (void)
	{ return (COLORREF)::SendMessage (Handle(), LVM_GETBKCOLOR, 0, 0L); }

inline BOOL CListViewCtrl::SetBkColor (COLORREF cr)
	{ return ::SendMessage (Handle(), LVM_SETBKCOLOR, 0, cr) ? true : false; }

inline CImageList* CListViewCtrl::GetImageList (int nImageListType)
	{ return new CImageList ((HIMAGELIST)::SendMessage(Handle(), LVM_GETIMAGELIST, nImageListType, 0L)); }

inline CImageList* CListViewCtrl::SetImageList (CImageList* pImageList, int nImageList)
	{ return new CImageList ((HIMAGELIST)::SendMessage(Handle(), LVM_SETIMAGELIST, nImageList, (LPARAM)pImageList->Handle())); }

inline int CListViewCtrl::GetItemCount (void)
	{ return (int)::SendMessage (Handle(), LVM_GETITEMCOUNT, 0, 0L); }

inline BOOL CListViewCtrl::GetItem (LV_ITEM *pItem)
	{ return ::SendMessage(Handle(), LVM_GETITEM, 0, (LPARAM)pItem) ? true : false; }

inline BOOL CListViewCtrl::SetItem (const LV_ITEM* pItem)
	{ return ::SendMessage (Handle(), LVM_SETITEM, 0, (LPARAM)pItem) ? true : false; }

inline BOOL CListViewCtrl::SetItemState(int nItem, UINT nState, UINT nStateMask)
	{ return SetItem(nItem, 0, LVIF_STATE, NULL, 0, nState, nStateMask, 0); }

inline BOOL CListViewCtrl::SetItemText(int nItem, int nSubItem, LPSTR lpszText)
	{ return SetItem(nItem, nSubItem, LVIF_TEXT, lpszText, 0, 0, 0, 0); }

inline BOOL CListViewCtrl::SetItemData(int nItem, DWORD dwData)
	{ return SetItem(nItem, 0, LVIF_PARAM, NULL, 0, 0, 0, (LPARAM)dwData); }

inline int CListViewCtrl::InsertItem (const LV_ITEM *pItem)
	{ return (int)::SendMessage(Handle(), LVM_INSERTITEM, 0, (LPARAM)pItem); }

inline int CListViewCtrl::InsertItem(int nItem, LPCSTR lpszItem)
	{ return InsertItem(LVIF_TEXT, nItem, lpszItem, 0, 0, 0, 0); }

inline int CListViewCtrl::InsertItem(int nItem, LPCSTR lpszItem, int nImage)
	{ return InsertItem(LVIF_TEXT|LVIF_IMAGE, nItem, lpszItem, 0, 0, nImage, 0); }

inline BOOL CListViewCtrl::DeleteItem(int nItem)
	{ return ::SendMessage(Handle(), LVM_DELETEITEM, nItem, 0L) ? true : false; }

inline BOOL CListViewCtrl::DeleteAllItems()
	{ return ::SendMessage(Handle(), LVM_DELETEALLITEMS, 0, 0L) ? true : false; }

inline UINT CListViewCtrl::GetCallbackMask()
	{ return (UINT)::SendMessage(Handle(), LVM_GETCALLBACKMASK, 0, 0); }

inline BOOL CListViewCtrl::SetCallbackMask(UINT nMask)
	{ return ::SendMessage(Handle(), LVM_SETCALLBACKMASK, nMask, 0) ? true : false; }

inline int CListViewCtrl::GetNextItem(int nItem, int nFlags)
	{ return (int)::SendMessage(Handle(), LVM_GETNEXTITEM, nItem, MAKELPARAM(nFlags, 0)); }

inline int CListViewCtrl::FindItem(LV_FINDINFO* pFindInfo, int nStart)
	{ return (int)::SendMessage(Handle(), LVM_FINDITEM, nStart, (LPARAM)pFindInfo); }

inline int CListViewCtrl::HitTest(LV_HITTESTINFO* pHitTestInfo)
	{ return (int)::SendMessage(Handle(), LVM_HITTEST, 0, (LPARAM)pHitTestInfo); }

inline int CListViewCtrl::GetStringWidth(LPCSTR lpsz)
	{ return (int)::SendMessage(Handle(), LVM_GETSTRINGWIDTH, 0, (LPARAM)lpsz); }

inline BOOL CListViewCtrl::EnsureVisible(int nItem, BOOL bPartialOK)
	{ return ::SendMessage(Handle(), LVM_ENSUREVISIBLE, nItem, MAKELPARAM(bPartialOK, 0)) ? true : false; }

inline BOOL CListViewCtrl::Scroll(Dimension size)
	{ return ::SendMessage(Handle(), LVM_SCROLL, size.Width(), size.Height()) ? true : false; }

inline BOOL CListViewCtrl::RedrawItems(int nFirst, int nLast)
	{ return ::SendMessage(Handle(), LVM_REDRAWITEMS, 0, MAKELPARAM(nFirst, nLast)) ? true : false; }

inline BOOL CListViewCtrl::Arrange(UINT nCode)
	{ return ::SendMessage(Handle(), LVM_ARRANGE, nCode, 0L) ? true : false; }

inline SingleLineEdit *CListViewCtrl::EditLabel(int nItem)
	{ return new SingleLineEdit (GetParent(), (HWND)::SendMessage(Handle(), LVM_EDITLABEL, nItem, 0L)); }

inline SingleLineEdit *CListViewCtrl::GetEditControl()
	{ return new SingleLineEdit (GetParent(), (HWND)::SendMessage(Handle(), LVM_GETEDITCONTROL, 0, 0L)); }

inline BOOL CListViewCtrl::GetColumn(int nCol, LV_COLUMN *pColumn)
	{ return ::SendMessage(Handle(), LVM_GETCOLUMN, nCol, (LPARAM)pColumn) ? true : false; }

inline BOOL CListViewCtrl::SetColumn(int nCol, const LV_COLUMN* pColumn)
	{ return ::SendMessage(Handle(), LVM_SETCOLUMN, nCol, (LPARAM)pColumn) ? true : false; }

inline int CListViewCtrl::InsertColumn(int nCol, const LV_COLUMN* pColumn)
	{ return (int)::SendMessage(Handle(), LVM_INSERTCOLUMN, nCol, (LPARAM)pColumn); }

inline BOOL CListViewCtrl::DeleteColumn(int nCol)
	{ return ::SendMessage(Handle(), LVM_DELETECOLUMN, nCol, 0) ? true : false; }

inline int CListViewCtrl::GetColumnWidth(int nCol)
	{ return (int)::SendMessage(Handle(), LVM_GETCOLUMNWIDTH, nCol, 0); }

inline BOOL CListViewCtrl::SetColumnWidth(int nCol, int cx)
	{ return ::SendMessage(Handle(), LVM_SETCOLUMNWIDTH, nCol, MAKELPARAM(cx, 0)) ? true : false; }

inline CImageList* CListViewCtrl::CreateDragImage(int nItem, LPPOINT lpPoint)
	{ return new CImageList((HIMAGELIST)::SendMessage(Handle(), LVM_CREATEDRAGIMAGE, nItem, (LPARAM)lpPoint)); }

inline BOOL CListViewCtrl::GetViewRect(LPRECT lpRect)
	{ return ::SendMessage(Handle(), LVM_GETVIEWRECT, 0, (LPARAM)lpRect) ? true : false; }

inline COLORREF CListViewCtrl::GetTextColor()
	{ return (COLORREF)::SendMessage(Handle(), LVM_GETTEXTCOLOR, 0, 0L); }

inline BOOL CListViewCtrl::SetTextColor(COLORREF cr)
	{ return ::SendMessage(Handle(), LVM_SETTEXTCOLOR, 0, cr) ? true : false; }

inline COLORREF CListViewCtrl::GetTextBkColor()
	{ return (COLORREF)::SendMessage(Handle(), LVM_GETTEXTBKCOLOR, 0, 0L); }

inline BOOL CListViewCtrl::SetTextBkColor(COLORREF cr)
	{ return ::SendMessage(Handle(), LVM_SETTEXTBKCOLOR, 0, cr) ? true : false; }

inline int CListViewCtrl::GetTopIndex()
	{ return (int)::SendMessage(Handle(), LVM_GETTOPINDEX, 0, 0); }

inline int CListViewCtrl::GetCountPerPage()
	{ return (int)::SendMessage(Handle(), LVM_GETCOUNTPERPAGE, 0, 0); }

inline BOOL CListViewCtrl::GetOrigin(LPPOINT lpPoint)
	{ return ::SendMessage(Handle(), LVM_GETORIGIN, 0, (LPARAM)lpPoint) ? true : false; }

inline BOOL CListViewCtrl::Update(int nItem)
	{ return ::SendMessage(Handle(), LVM_UPDATE, nItem, 0L) ? true : false; }

inline BOOL CListViewCtrl::SetItemState(int nItem, LV_ITEM* pItem)
	{ return ::SendMessage(Handle(), LVM_SETITEMSTATE, nItem, (LPARAM)pItem) ? true : false; }

inline UINT CListViewCtrl::GetItemState(int nItem, UINT nMask)
	{ return (UINT)::SendMessage(Handle(), LVM_GETITEMSTATE, nItem, nMask); }

inline void CListViewCtrl::SetItemCount(int nItems)
	{::SendMessage(Handle(), LVM_SETITEMCOUNT, nItems, 0); }

inline BOOL CListViewCtrl::SortItems(PFNLVCOMPARE pfnCompare, DWORD dwData)
	{ return ::SendMessage(Handle(), LVM_SORTITEMS, dwData, (LPARAM)pfnCompare) ? true : false; }

inline UINT CListViewCtrl::GetSelectedCount()
	{ return (UINT)::SendMessage(Handle(), LVM_GETSELECTEDCOUNT, 0, 0L); }

///////////////////////////////////////////////////////////////////////////////
// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
inline DWORD CListViewCtrl::GetExtendedStyle (void)
	{ return ListView_GetExtendedListViewStyle(Handle()); }

inline DWORD CListViewCtrl::SetExtendedStyle (DWORD dwStyleEx)
	{ return ListView_SetExtendedListViewStyle(Handle(), dwStyleEx); }

inline BOOL CListViewCtrl::GetSubItemRect (int iItem, int iSubItem, int iCode, LPRECT lpRc)
	{ return ListView_GetSubItemRect(Handle(), iItem, iSubItem, iCode, lpRc) ? true : false; }

inline int CListViewCtrl::SubItemHitTest (LV_HITTESTINFO *pHitTestInfo)
	{ return ListView_SubItemHitTest(Handle(), pHitTestInfo); }

inline BOOL CListViewCtrl::SetColumnOrderArray (int iCount, int *piCols)
	{ return ListView_SetColumnOrderArray(Handle(), iCount, piCols) ? true : false; }

inline BOOL CListViewCtrl::GetColumnOrderArray (int iCount, int *piCols)
	{ return ListView_GetColumnOrderArray(Handle(), iCount, piCols) ? true : false; }

inline int CListViewCtrl::SetHotItem (int iItem)
	{ return ListView_SetHotItem(Handle(), iItem); }

inline int CListViewCtrl::GetHotItem (void)
	{ return ListView_GetHotItem(Handle()); }

inline HCURSOR CListViewCtrl::SetHotCursor (HCURSOR hCursor)
	{ return ListView_SetHotCursor(Handle(), hCursor); }

inline HCURSOR CListViewCtrl::GetHotCursor (void)
	{ return ListView_GetHotCursor(Handle()); }

inline DWORD CListViewCtrl::ApproximateViewRect (int iWidth, int iHeight, int iCount)
	{ return ListView_ApproximateViewRect(Handle(), iWidth, iHeight, iCount); }

#else // NashVille not installed

inline DWORD CListViewCtrl::GetExtendedStyle (void)
	{ return 0L; }

inline DWORD CListViewCtrl::SetExtendedStyle (DWORD dwStyleEx)
	{ return 0L; }

inline BOOL CListViewCtrl::GetSubItemRect (int iItem, int iSubItem, int iCode, LPRECT lpRc)
	{ return false; }

inline int CListViewCtrl::SubItemHitTest (LV_HITTESTINFO *pHitTestInfo)
	{ return -1; }

inline BOOL CListViewCtrl::SetColumnOrderArray (int iCount, int *piCols)
	{ return 0; }

inline BOOL CListViewCtrl::GetColumnOrderArray (int iCount, int *piCols)
	{ return false; }

inline int CListViewCtrl::SetHotItem (int iItem)
	{ return -1; }

inline int CListViewCtrl::GetHotItem (void)
	{ return -1; }

inline HCURSOR CListViewCtrl::SetHotCursor (HCURSOR hCursor)
	{ return NULL; }

inline HCURSOR CListViewCtrl::GetHotCursor (void)
	{ return NULL; }

inline DWORD CListViewCtrl::ApproximateViewRect (int iWidth, int iHeight, int iCount)
	{ return 0L; }
#endif

#endif // NOLISTVIEW

#if !defined(NOTOOLTIP)

inline void CToolTipCtrl::Activate(BOOL bActivate)
	{ ::SendMessage(Handle(), TTM_ACTIVATE, bActivate, 0L); }

inline void CToolTipCtrl::SetToolInfo(LPTOOLINFO lpToolInfo)
	{ ::SendMessage(Handle(), TTM_SETTOOLINFO, 0, (LPARAM)lpToolInfo); }

inline void CToolTipCtrl::RelayEvent(LPMSG lpMsg)
	{ ::SendMessage(Handle(), TTM_RELAYEVENT, 0, (LPARAM)lpMsg); }

inline void CToolTipCtrl::SetDelayTime(UINT nDelay)
	{ ::SendMessage(Handle(), TTM_SETDELAYTIME, 0, nDelay); }

inline int CToolTipCtrl::GetToolCount()
	{ return (int)::SendMessage(Handle(), TTM_GETTOOLCOUNT, 0, 0L); }

#endif // NOTOOLTIP

#if !defined(NOTOOLBAR)

inline BOOL CToolBarCtrl::EnableButton(int nID, BOOL bEnable)
	{ return ::SendMessage(Handle(), TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0)) ? true : false; }

inline BOOL CToolBarCtrl::CheckButton(int nID, BOOL bCheck)
	{ return ::SendMessage(Handle(), TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0)) ? true : false; }

inline BOOL CToolBarCtrl::PressButton(int nID, BOOL bPress)
	{ return ::SendMessage(Handle(), TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0)) ? true : false; }

inline BOOL CToolBarCtrl::HideButton(int nID, BOOL bHide)
	{ return ::SendMessage(Handle(), TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0)) ? true : false; }

inline BOOL CToolBarCtrl::Indeterminate(int nID, BOOL bIndeterminate)
	{ return ::SendMessage(Handle(), TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0)) ? true : false; }

inline BOOL CToolBarCtrl::IsButtonEnabled(int nID)
	{ return ::SendMessage(Handle(), TB_ISBUTTONENABLED, nID, 0) ? true : false; }

inline BOOL CToolBarCtrl::IsButtonChecked(int nID)
	{ return ::SendMessage(Handle(), TB_ISBUTTONCHECKED, nID, 0) ? true : false; }

inline BOOL CToolBarCtrl::IsButtonPressed(int nID)
	{ return ::SendMessage(Handle(), TB_ISBUTTONPRESSED, nID, 0) ? true : false; }

inline BOOL CToolBarCtrl::IsButtonHidden(int nID)
	{ return ::SendMessage(Handle(), TB_ISBUTTONHIDDEN, nID, 0) ? true : false; }

inline BOOL CToolBarCtrl::IsButtonIndeterminate(int nID)
	{ return ::SendMessage(Handle(), TB_ISBUTTONINDETERMINATE, nID, 0) ? true : false; }

inline BOOL CToolBarCtrl::SetState(int nID, UINT nState)
	{ return ::SendMessage(Handle(), TB_SETSTATE, nID, MAKELPARAM(nState, 0)) ? true : false; }

inline int CToolBarCtrl::GetState(int nID)
	{ return (int) ::SendMessage(Handle(), TB_GETSTATE, nID, 0L); }

inline BOOL CToolBarCtrl::AddButtons(int nNumButtons, LPTBBUTTON lpButtons)
	{ return ::SendMessage(Handle(), TB_ADDBUTTONS, nNumButtons, (LPARAM)lpButtons) ? true : false; }

inline BOOL CToolBarCtrl::InsertButton(int nIndex, LPTBBUTTON lpButton)
	{ return ::SendMessage(Handle(), TB_INSERTBUTTON, nIndex, (LPARAM)lpButton) ? true : false; }

inline BOOL CToolBarCtrl::DeleteButton(int nIndex)
	{ return ::SendMessage(Handle(), TB_DELETEBUTTON, nIndex, 0) ? true : false; }

inline BOOL CToolBarCtrl::GetButton(int nIndex, LPTBBUTTON lpButton)
	{ return ::SendMessage(Handle(), TB_GETBUTTON, nIndex, (LPARAM)lpButton) ? true : false; }

inline int CToolBarCtrl::GetButtonCount()
	{ return (int) ::SendMessage(Handle(), TB_BUTTONCOUNT, 0, 0L); }

inline UINT CToolBarCtrl::CommandToIndex(UINT nID)
	{ return (UINT) ::SendMessage(Handle(), TB_COMMANDTOINDEX, nID, 0L); }

inline void CToolBarCtrl::Customize()
	{ ::SendMessage(Handle(), TB_CUSTOMIZE, 0, 0L); }

// lpszStrings are separated by zeroes, last one is marked by two zeroes
inline int CToolBarCtrl::AddStrings(LPCSTR lpszStrings)
	{ return (int) ::SendMessage(Handle(), TB_ADDSTRING, 0, (LPARAM)lpszStrings); }

inline BOOL CToolBarCtrl::GetItemRect(int nIndex, LPRECT lpRect)
	{ return ::SendMessage(Handle(), TB_GETITEMRECT, nIndex, (LPARAM)lpRect) ? true : false; }

inline void CToolBarCtrl::SetButtonStructSize(int nSize)
	{ ::SendMessage(Handle(), TB_BUTTONSTRUCTSIZE, nSize, 0L); }

inline BOOL CToolBarCtrl::SetButtonSize(Dimension size)
	{ return ::SendMessage(Handle(), TB_SETBUTTONSIZE, 0, MAKELPARAM(size.Width(), size.Height())) ? true : false; }

inline BOOL CToolBarCtrl::SetBitmapSize(Dimension size)
	{ return ::SendMessage(Handle(), TB_SETBITMAPSIZE, 0, MAKELPARAM(size.Width(), size.Height())) ? true : false; }

inline void CToolBarCtrl::AutoSize()
	{ ::SendMessage(Handle(), TB_AUTOSIZE, 0, 0L); }

inline void CToolBarCtrl::SetToolTips(CToolTipCtrl* pTip)
	{ ::SendMessage(Handle(), TB_SETTOOLTIPS, (WPARAM)pTip->Handle(), 0L); }

inline void CToolBarCtrl::SetOwner(pWindow pWnd)
	{ ::SendMessage(Handle(), TB_SETPARENT, (WPARAM)pWnd->Handle(), 0L); }

inline void CToolBarCtrl::SetRows(int nRows, BOOL bLarger, LPRECT lpRect)
	{ ::SendMessage(Handle(), TB_SETROWS, MAKELPARAM(nRows, bLarger), (LPARAM)lpRect); }

inline int CToolBarCtrl::GetRows()
	{ return (int) ::SendMessage(Handle(), TB_GETROWS, 0, 0L); }

inline BOOL CToolBarCtrl::SetCmdID(int nIndex, UINT nID)
	{ return ::SendMessage(Handle(), TB_SETCMDID, nIndex, nID) ? true : false; }

inline UINT CToolBarCtrl::GetBitmapFlags()
	{ return (UINT) ::SendMessage(Handle(), TB_GETBITMAPFLAGS, 0, 0L); }

#endif // NOTOOLBAR

#if !defined(NOSTATUSBAR)

inline BOOL CStatusBarCtrl::SetText(LPCSTR lpszText, int nPane, int nType)
	{ return ::SendMessage(Handle(), SB_SETTEXT, (nPane|nType), (LPARAM)lpszText) ? true : false; }

inline BOOL CStatusBarCtrl::SetParts(int nParts, int* pWidths)
	{ return ::SendMessage(Handle(), SB_SETPARTS, nParts, (LPARAM)pWidths) ? true : false; }

inline BOOL CStatusBarCtrl::SetBorders(int* pBorders)
	{ return ::SendMessage(Handle(), SB_SETPARTS, 0, (LPARAM)pBorders) ? true : false; }

inline int CStatusBarCtrl::GetParts(int nParts, int* pParts)
	{ return (int) ::SendMessage(Handle(), SB_GETPARTS, nParts, (LPARAM)pParts); }

inline BOOL CStatusBarCtrl::GetBorders(int* pBorders)
	{ return ::SendMessage(Handle(), SB_GETBORDERS, 0, (LPARAM)pBorders) ? true : false; }

inline void CStatusBarCtrl::SetMinHeight(int nMin)
	{ ::SendMessage(Handle(), SB_SETMINHEIGHT, nMin, 0L); }

inline BOOL CStatusBarCtrl::SetSimple(BOOL bSimple)
	{ return ::SendMessage(Handle(), SB_SIMPLE, bSimple, 0L) ? true : false; }

inline BOOL CStatusBarCtrl::GetRect(int nPane, LPRECT lpRect)
	{ return ::SendMessage(Handle(), SB_GETRECT, nPane, (LPARAM)lpRect) ? true : false; }

#endif // NOSTATUSBAR

#if !defined(NOUPDOWN)

inline UINT CSpinButtonCtrl::GetAccel(int nAccel, UDACCEL* pAccel)
	{ return (UINT) LOWORD(::SendMessage(Handle(), UDM_GETACCEL, nAccel, (LPARAM)pAccel)); }

inline UINT CSpinButtonCtrl::GetBase()
	{ return (UINT) LOWORD(::SendMessage(Handle(), UDM_GETBASE, 0, 0l)); }

inline int CSpinButtonCtrl::GetPos()
	{ return (int) LOWORD(::SendMessage(Handle(), UDM_GETPOS, 0, 0l)); }

inline DWORD CSpinButtonCtrl::GetRange()
	{ return (DWORD) ::SendMessage(Handle(), UDM_GETRANGE, 0, 0l); }

inline BOOL CSpinButtonCtrl::SetAccel(int nAccel, UDACCEL* pAccel)
	{ return LOWORD(::SendMessage(Handle(), UDM_SETACCEL, nAccel, (LPARAM)pAccel)) ? true : false; }

inline int CSpinButtonCtrl::SetBase(int nBase)
	{ return (int) ::SendMessage(Handle(), UDM_SETBASE, nBase, 0L); }

inline int CSpinButtonCtrl::SetPos(int nPos)
	{ return (int) (short) LOWORD(::SendMessage(Handle(), UDM_SETPOS, 0, MAKELPARAM(nPos, 0))); }

inline void CSpinButtonCtrl::SetRange(int nLower, int nUpper)
	{ ::SendMessage(Handle(), UDM_SETRANGE, 0, MAKELPARAM(nUpper, nLower)); }

#endif // NOUPDOWN

#if !defined(NOPROGRESS)

inline void CProgressCtrl::SetRange(int nLower, int nUpper)
	{ ::SendMessage(Handle(), PBM_SETRANGE, 0, MAKELPARAM(nLower, nUpper)); }

inline int CProgressCtrl::SetPos(int nPos)
	{ return (int) LOWORD(::SendMessage(Handle(), PBM_SETPOS, nPos, 0L)); }

inline int CProgressCtrl::OffsetPos(int nPos)
	{ return (int) LOWORD(::SendMessage(Handle(), PBM_DELTAPOS, nPos, 0L)); }

inline int CProgressCtrl::SetStep(int nStep)
	{ return (int) LOWORD(::SendMessage(Handle(), PBM_SETSTEP, nStep, 0L)); }

inline int CProgressCtrl::StepIt()
	{ return (int) LOWORD(::SendMessage(Handle(), PBM_STEPIT, 0, 0L)); }

#endif // NOPROGRESS
#if !defined(NOANIMATE)

inline BOOL CAnimateCtrl::Open(LPCTSTR lpszName)
	{ return ::SendMessage(Handle(), ACM_OPEN, 0, (LPARAM)lpszName) ? true : false; }

inline BOOL CAnimateCtrl::Open(UINT nID)
	{ return ::SendMessage(Handle(), ACM_OPEN, 0, nID) ? true : false; }

inline BOOL CAnimateCtrl::Play(UINT nFrom, UINT nTo, UINT nRep)
	{ return ::SendMessage(Handle(), ACM_PLAY, nRep, MAKELPARAM(nFrom, nTo)) ? true : false; }

inline BOOL CAnimateCtrl::Stop()
	{ return ::SendMessage(Handle(), ACM_STOP, 0, 0L) ? true : false; }

inline BOOL CAnimateCtrl::Close()
	{ return ::SendMessage(Handle(), ACM_OPEN, 0, 0L) ? true : false; }

inline BOOL CAnimateCtrl::Seek(UINT nTo)
	{ return ::SendMessage(Handle(), ACM_PLAY, 0, MAKELPARAM(nTo, nTo)) ? true : false; }

#endif // NOANIMATE

// BEGIN: #HK001012
// CHotKeyCtrl
inline void CHotKeyCtrl::SetHotKey(WORD wVirtualKeyCode, WORD wModifiers)
	{ ::SendMessage(Handle(), HKM_SETHOTKEY, MAKELONG(wVirtualKeyCode, wModifiers), 0); }

inline DWORD CHotKeyCtrl::GetHotKey() const
	{ return ::SendMessage(const_cast<CHotKeyCtrl *>(this) -> Handle(), HKM_GETHOTKEY, 0, 0); }

inline void CHotKeyCtrl::GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers) const
	{ DWORD dw = ::SendMessage(const_cast<CHotKeyCtrl *>(this) -> Handle(), HKM_GETHOTKEY, 0, 0); wVirtualKeyCode = LOWORD(dw); wModifiers = HIWORD(dw); }

inline void CHotKeyCtrl::SetRules(WORD wInvalidComb, WORD wModifiers)
	{ ::SendMessage(Handle(), HKM_SETRULES, wInvalidComb, MAKELPARAM(wModifiers, 0)); }
// END: #HK001012

// BEGIN: #HK030317
// ComboBoxEx
inline ComboBox::ComboBox()
	{}
inline DWORD ComboBoxEx::GetExtendedStyle()
	{ return (DWORD) ::SendMessage(Handle(), CBEM_GETEXTENDEDSTYLE, 0, 0); }
inline DWORD ComboBoxEx::SetExtendedStyle(DWORD dwExMask, DWORD dwExStyles)
	{ return (DWORD) ::SendMessage(Handle(), CBEM_SETEXTENDEDSTYLE, (DWORD) dwExMask, (LPARAM) dwExStyles); }
inline BOOL ComboBoxEx::HasEditChanged()
	{ return (BOOL) ::SendMessage(Handle(), CBEM_HASEDITCHANGED, 0, 0); }
inline SingleLineEdit* ComboBoxEx::GetEditCtrl()
	{ return new SingleLineEdit(GetParent(), (HWND)::SendMessage(Handle(), CBEM_GETEDITCONTROL, 0, 0)); }
inline CImageList* ComboBoxEx::SetImageList(CImageList* pImageList)
	{ return new CImageList((HIMAGELIST)::SendMessage(Handle(), CBEM_SETIMAGELIST, 0, (LPARAM)pImageList->Handle())); }
inline CImageList* ComboBoxEx::GetImageList() 
	{ return new CImageList((HIMAGELIST)::SendMessage(Handle(), CBEM_GETIMAGELIST, 0, 0)); }
// END: #HK030317

#endif // NOWIN95CONTROLS

#ifndef NOEVENT
// added following functions: #HK960913
inline UINT &Event::Msg (void) { return wMsg; }
inline WPARAM &Event::WParam (void) { return wParam; }
inline LPARAM &Event::LParam (void) { return lParam; }

// ADDED: #HK970809
inline Event::Event (UINT WMsg, WPARAM WParam, LPARAM LParam, void *pExtra)
	: wMsg(WMsg), wParam(WParam), lParam(LParam), EvtExtra(pExtra)
{
	// nothing else to do
}
inline Event::Event (void)
	: wMsg(0), wParam(0), lParam(0), EvtExtra(NULL)
{
	// nothing else to do
}

inline const HELPINFO *HelpRequestEvt :: GetHelpInfo (void)
	{ return (HelpWmHelp == (HelpType)wParam) ? (const HELPINFO *)lParam : NULL; }
#endif // NOEVENT

#endif // WIN32

#endif // _CVINLINE_HXX
