// ListCtrlEx.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include "TreeCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CSECTreeCtrlEx

CSECTreeCtrlEx::CSECTreeCtrlEx()
{
}

CSECTreeCtrlEx::~CSECTreeCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CSECTreeCtrlEx, SECTreeCtrl)
	//{{AFX_MSG_MAP(CSECTreeCtrlEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSECTreeCtrlEx message handlers

void CSECTreeCtrlEx::FitColumn (int iCol)
{
// Call this after your list control is filled     
	SetRedraw(false);

int mincol = iCol < 0 ? 0 : iCol;
int maxcol = iCol < 0 ? GetColumnCount()-1 : iCol;

	for (int col = mincol; col <= maxcol; col++) {
		SetColumnWidth(col, LVSCW_AUTOSIZE);

	int wc1 = GetColumnWidth (col);

		SetColumnWidth (col, LVSCW_AUTOSIZE_USEHEADER);

	int wc2 = GetColumnWidth (col);
	int wc = max (MINCOLWIDTH, max(wc1, wc2));

		SetColumnWidth (col, wc);     
	}

//	RecalcHeaderTips(); 
	SetRedraw(true);
	InvalidateRect(NULL, true); 
}

int CSECTreeCtrlEx::InsertColumn(
	int nCol, UINT uiColHead, int nFormat, int nWidth, int nSubItem)
{
	TRY {
	CString strColHead;

		strColHead.LoadString (uiColHead);
		return SECTreeCtrl::InsertColumn (nCol, strColHead, nFormat, nWidth, nSubItem);

	} CATCH_ALL(e) {
		TRACE0("Could not load resources for column headings\r\n");
		return -1;
	} END_CATCH_ALL;
}

int CSECTreeCtrlEx::GetItemIndex (HTREEITEM hItem)
{
	for (int i = 0; i < GetItemCount(); i++) 
	{
		if (hItem == GetItemAt(i))
			return i;
	}
	return -1;
}
