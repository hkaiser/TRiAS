// CListViewCtrl - Interface --------------------------------------------------
// File: LISTVIEW.CXX

#include "tfrmpre.hxx"
#if _MSC_VER >= 1100
#include <ospace/except/stdex.h>
#endif // _MSC_VER

CListViewCtrl :: CListViewCtrl (pWindow parent, CvID UsrID, Point where, 
				Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CListViewCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CListViewCtrl :: CListViewCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CListViewCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CListViewCtrl :: ~CListViewCtrl (void)
{
}

CListViewCtrl_Imp :: CListViewCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_CListViewCtrl, dwInitStyle)
{
}

CListViewCtrl_Imp :: CListViewCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_CListViewCtrl)
{
}

CListViewCtrl_Imp :: ~CListViewCtrl_Imp (void)
{
	DestroyControl();		// DestroyWindow
}

BOOL CListViewCtrl :: GetItemRect (int nItem, LPRECT lpRect, UINT nCode)
{
	CV_ASSERT(::IsWindow(Handle())); 
	lpRect->left = nCode;

return (BOOL)::SendMessage(Handle(), LVM_GETITEMRECT, (WPARAM)nItem, (LPARAM)lpRect);
}

int CListViewCtrl :: InsertColumn (int nCol, LPCSTR lpszColumnHeading, int nFormat, 
				   int nWidth, int nSubItem)
{
LV_COLUMN column;

	column.mask = LVCF_TEXT|LVCF_FMT;
	column.pszText = (LPSTR)lpszColumnHeading;
	column.fmt = nFormat;
	if (nWidth != -1) {
		column.mask |= LVCF_WIDTH;
		column.cx = nWidth;
	}
	if (nSubItem != -1) {
		column.mask |= LVCF_SUBITEM;
		column.iSubItem = nSubItem;
	}

return InsertColumn (nCol, &column);
}

int CListViewCtrl :: InsertItem (UINT nMask, int nItem, LPCSTR lpszItem, 
				 UINT nState, UINT nStateMask,
				 int nImage, LPARAM lParam)
{
	CV_ASSERT(::IsWindow(Handle())); 

LV_ITEM item;

	item.mask = nMask;
	item.iItem = nItem;
	item.iSubItem = 0;
	item.pszText = (LPSTR)lpszItem;
	item.state = nState;
	item.stateMask = nStateMask;
	item.iImage = nImage;
	item.lParam = lParam;

return CListViewCtrl::InsertItem(&item);
}

int CListViewCtrl :: HitTest (Point pt, UINT *pFlags)
{
	CV_ASSERT(::IsWindow(Handle()));

LV_HITTESTINFO hti;

	hti.pt = (POINT &)pt;

int nRes = (int)::SendMessage(Handle(), LVM_HITTEST, 0, (LPARAM)&hti);

	if (pFlags != NULL)
		*pFlags = hti.flags;

return nRes;
}

BOOL CListViewCtrl :: SetItem (int nItem, int nSubItem, UINT nMask, 
			       LPCSTR lpszItem, int nImage, UINT nState, 
			       UINT nStateMask, LPARAM lParam)
{
	CV_ASSERT(::IsWindow(Handle())); 

LV_ITEM lvi;

	lvi.mask = nMask;
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;
	lvi.stateMask = nStateMask;
	lvi.state = nState;
	lvi.pszText = (LPSTR) lpszItem;
	lvi.iImage = nImage;
	lvi.lParam = lParam;

return (BOOL)::SendMessage (Handle(), LVM_SETITEM, 0, (LPARAM)&lvi);
}

string CListViewCtrl :: GetItemText (int nItem, int nSubItem)
{
	CV_ASSERT(::IsWindow(Handle())); 

LV_ITEM lvi;

	memset(&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;

char *pText = NULL;
int nLen = 128;
int nRes;
string str;

	try {
		do {
			nLen *= 2;
			if (pText) delete pText;
			pText = new char [nLen];
			lvi.cchTextMax = nLen;
			lvi.pszText = (LPSTR)pText;
			nRes = (int)::SendMessage (Handle(), LVM_GETITEMTEXT, (WPARAM)nItem,
						  (LPARAM)&lvi);
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

int CListViewCtrl :: GetItemText (int nItem, int nSubItem, LPSTR lpszText, int nLen)
{ 
	CV_ASSERT(::IsWindow(Handle())); 
	
LV_ITEM lvi;

	memset(&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;
	lvi.cchTextMax = nLen;
	lvi.pszText = lpszText;

return (int)::SendMessage(Handle(), LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi);
}

DWORD CListViewCtrl::GetItemData(int nItem)
{
	CV_ASSERT(::IsWindow(Handle())); 

LV_ITEM lvi;

	memset(&lvi, 0, sizeof(LV_ITEM));
	lvi.iItem = nItem;
	lvi.mask = LVIF_PARAM;
	::SendMessage(Handle(), LVM_GETITEM, 0, (LPARAM)&lvi);

return (DWORD)lvi.lParam;
}

LRESULT CListViewCtrl_Imp :: OnDestroy (Event e)
{
	RemoveImageList (LVSIL_NORMAL);
	RemoveImageList (LVSIL_SMALL);
	RemoveImageList (LVSIL_STATE);

return Control_Imp :: OnDestroy(e);
}

void CListViewCtrl::RemoveImageList(int nImageList)
{
	((CListViewCtrl_Imp *)control_Imp) -> RemoveImageList(nImageList);
}

void CListViewCtrl_Imp::RemoveImageList(int nImageList)
{
HIMAGELIST h = (HIMAGELIST)SendMessage (Handle(), LVM_GETIMAGELIST, (WPARAM)nImageList, 0L);

	::SendMessage(Handle(), LVM_SETIMAGELIST, (WPARAM)nImageList, NULL);

	if (NULL != h && NULL == _AppImpFind() -> ImagesList() -> Find (h))
		ImageList_Destroy(h);		// uns unbekannte CImageList
}

