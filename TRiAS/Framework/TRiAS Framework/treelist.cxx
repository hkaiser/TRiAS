// CTreeList - Interface ------------------------------------------------------
// File: TREELIST.CXX

#include "tfrmpre.hxx"
#if _MSC_VER >= 1100
#include <ospace/except/stdex.h>
#endif // _MSC_VER

CTreeViewCtrl :: CTreeViewCtrl (pWindow parent, CvID UsrID, Point where, 
				Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CTreeViewCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CTreeViewCtrl :: CTreeViewCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CTreeViewCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CTreeViewCtrl :: ~CTreeViewCtrl (void)
{
}

CTreeViewCtrl_Imp :: CTreeViewCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_CTreeListCtrl, dwInitStyle)
{
}

CTreeViewCtrl_Imp :: CTreeViewCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_CTreeListCtrl)
{
}

CTreeViewCtrl_Imp :: ~CTreeViewCtrl_Imp (void)
{
	DestroyControl();
}

BOOL CTreeViewCtrl::GetItemRect(HTREEITEM hItem, Rectangle *lpRect, BOOL bTextOnly)
{
	CV_ASSERT(::IsWindow(Handle())); 
	*(HTREEITEM *)lpRect = hItem;

return (BOOL)::SendMessage(Handle(), TVM_GETITEMRECT, (WPARAM)bTextOnly, (LPARAM)lpRect);
}

string CTreeViewCtrl :: GetItemText(HTREEITEM hItem)
{
	CV_ASSERT(::IsWindow(Handle())); 

TV_ITEM item;
string str;
int nLen = 128;
int nRes;
char *pText = NULL;

	item.hItem = hItem;
	item.mask = TVIF_TEXT;
	try {
		do {
			nLen *= 2;
			if (pText) delete pText;
			pText = new char [nLen];

			item.pszText = pText;
			item.cchTextMax = nLen;
			::SendMessage(Handle(), TVM_GETITEM, 0, (LPARAM)&item);
			nRes = strlen(item.pszText);
		} while (nRes == nLen-1);
		if (nRes > 0)
			str = pText;

#if _MSC_VER >= 1100
	} catch (os_length_error) {
#else
	} catch (...) {
#endif // _MSC_VER
		return str;
	}

	delete pText;
	return str;
}

BOOL CTreeViewCtrl::GetItemImage(HTREEITEM hItem, int& nImage, int& nSelectedImage)
{
	CV_ASSERT(::IsWindow(Handle())); 

TV_ITEM item;

	item.hItem = hItem;
	item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE;

BOOL bRes = (BOOL)::SendMessage(Handle(), TVM_GETITEM, 0, (LPARAM)&item);

	if (bRes) {
		nImage = item.iImage;
		nSelectedImage = item.iSelectedImage;
	}

return bRes;
}

UINT CTreeViewCtrl::GetItemState(HTREEITEM hItem, UINT nStateMask)
{
	CV_ASSERT(::IsWindow(Handle())); 

TV_ITEM item;

	item.hItem = hItem;
	item.mask = TVIF_STATE;
	item.stateMask = nStateMask;
	item.state = 0;

	::SendMessage(Handle(), TVM_GETITEM, 0, (LPARAM)&item);

return item.state;
}

DWORD CTreeViewCtrl::GetItemData(HTREEITEM hItem)
{
	CV_ASSERT(::IsWindow(Handle())); 

TV_ITEM item;

	item.hItem = hItem;
	item.mask = TVIF_PARAM;

	::SendMessage(Handle(), TVM_GETITEM, 0, (LPARAM)&item);

return (DWORD)item.lParam;
}

BOOL CTreeViewCtrl::ItemHasChildren(HTREEITEM hItem)
{
	CV_ASSERT(::IsWindow(Handle())); 

TV_ITEM item;

	item.hItem = hItem;
	item.mask = TVIF_CHILDREN;
	::SendMessage(Handle(), TVM_GETITEM, 0, (LPARAM)&item);

return item.cChildren;
}

BOOL CTreeViewCtrl::SetItem(HTREEITEM hItem, UINT nMask, LPCSTR lpszItem, int nImage, 
			int nSelectedImage, UINT nState, UINT nStateMask, 
			LPARAM lParam)
{
	CV_ASSERT(::IsWindow(Handle()));

TV_ITEM item;

	item.hItem = hItem;
	item.mask = nMask;
	item.pszText = (LPSTR) lpszItem;
	item.iImage = nImage;
	item.iSelectedImage = nSelectedImage;
	item.state = nState;
	item.stateMask = nStateMask;
	item.lParam = lParam;

return (BOOL)::SendMessage(Handle(), TVM_SETITEM, 0, (LPARAM)&item);
}

HTREEITEM CTreeViewCtrl::InsertItem(UINT nMask, LPCSTR lpszItem, int nImage, 
	int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, 
	HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	CV_ASSERT(::IsWindow(Handle()));

TV_INSERTSTRUCT tvis;

	tvis.hParent = hParent;
	tvis.hInsertAfter = hInsertAfter;
	tvis.item.mask = nMask;
	tvis.item.pszText = (LPSTR) lpszItem;
	tvis.item.iImage = nImage;
	tvis.item.iSelectedImage = nSelectedImage;
	tvis.item.state = nState;
	tvis.item.stateMask = nStateMask;
	tvis.item.lParam = lParam;

return (HTREEITEM)::SendMessage(Handle(), TVM_INSERTITEM, 0, (LPARAM)&tvis);
}

HTREEITEM CTreeViewCtrl::HitTest (Point pt, UINT *pFlags)
{
	CV_ASSERT(::IsWindow(Handle()));

TV_HITTESTINFO hti;

	hti.pt = (POINT &)pt;

HTREEITEM h = (HTREEITEM)::SendMessage(Handle(), TVM_HITTEST, 0, (LPARAM)&hti);
	
	if (pFlags != NULL) *pFlags = hti.flags;

return h;
}

LRESULT CTreeViewCtrl_Imp :: OnDestroy (Event e)
{
	RemoveImageList (LVSIL_NORMAL);
	RemoveImageList (LVSIL_STATE);

return Control_Imp :: OnDestroy(e);
}

void CTreeViewCtrl::RemoveImageList(int nImageList)
{
	((CTreeViewCtrl_Imp *)control_Imp) -> RemoveImageList (nImageList);
}


void CTreeViewCtrl_Imp::RemoveImageList(int nImageList)
{
HIMAGELIST h = (HIMAGELIST)::SendMessage(Handle(), TVM_GETIMAGELIST, (WPARAM)nImageList, 0L);

	::SendMessage(Handle(), TVM_SETIMAGELIST, (WPARAM)nImageList, NULL);

	if (NULL != h && NULL == _AppImpFind() -> ImagesList() -> Find (h))
		ImageList_Destroy(h);		// uns unbekannte CImageList
}

