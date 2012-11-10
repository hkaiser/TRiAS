// ListCtrlEx.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT_EX(LVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

void CListCtrlEx::FitColumn (int iCol)
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

int CListCtrlEx::GetColumnCount(void) const
{
CHeaderCtrl* pHeader = (CHeaderCtrl *)GetDlgItem(0);

	ASSERT_VALID(pHeader);
	return pHeader -> GetItemCount();
}

// HitTestEx	- Determine the row index and column index for a point
// Returns	- the row index or -1 if point is not over a row
// point	- point to be tested.
// col		- to hold the column index
int CListCtrlEx::HitTestEx (CPoint &point, int *col) const
{
int colnum = 0;
int row = HitTest (point, NULL);
	
	if (col)  *col = 0;

// Make sure that the ListView is in LVS_REPORT
	if ((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT) 
		return row;

// Get the top and bottom row visible
	row = GetTopIndex();

int bottom = row + GetCountPerPage();

	if (bottom > GetItemCount()) 
		bottom = GetItemCount();
	
// Get the number of columns
int nColumnCount = GetColumnCount();

// Loop through the visible rows
	for (/**/; row <=bottom; row++) {
	// Get bounding rect of item and check whether point falls in it.
	CRect rect;

		GetItemRect (row, &rect, LVIR_BOUNDS);
		if (rect.PtInRect(point)) {
		// Now find the column
			for (colnum = 0; colnum < nColumnCount; colnum++) {
			int colwidth = GetColumnWidth(colnum);
			
				if (point.x >= rect.left 
					&& point.x <= (rect.left + colwidth))
				{
					if (col) *col = colnum;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}

int CListCtrlEx::InsertColumn(
	int nCol, UINT uiColHead, int nFormat, int nWidth, int nSubItem)
{
	TRY {
	CString strColHead;

		strColHead.LoadString (uiColHead);
		return CListCtrl::InsertColumn (nCol, strColHead, nFormat, nWidth, nSubItem);

	} CATCH_ALL(e) {
		TRACE0("Could not load resources for column headings\r\n");
		return -1;
	} END_CATCH_ALL;
}

///////////////////////////////////////////////////////////////////////////////
// ShowInPlaceList		- Creates an in-place drop down list for any 
//				- cell in the list view control
// Returns			- A temporary pointer to the combo-box control
// nItem			- The row index of the cell
// nCol				- The column index of the cell
// lstItems			- A list of strings to populate the control with
// nSel				- Index of the initial selection in the drop down list
CComboBox* CListCtrlEx::ShowInPlaceList
	(int nItem, int nCol, CStringList &lstItems, int nSel, UINT uiId)
{
// The returned pointer should not be saved

// Make sure that the item is visible
	if (!EnsureVisible (nItem, TRUE)) return NULL;

// Make sure that nCol is valid 
int nColumnCount = GetColumnCount();

	if (nCol >= nColumnCount || GetColumnWidth(nCol) < 10)  
		return NULL;

// Get the column offset
int offset = 0;

	for (int i = 0; i < nCol; i++) 
		offset += GetColumnWidth (i);

CRect rect;

	GetItemRect (nItem, &rect, LVIR_BOUNDS);

// Now scroll if we need to expose the column
CRect rcClient;
int nRight = offset + rect.left + GetColumnWidth (nCol);

	GetClientRect (&rcClient);
	if (offset + rect.left < 0)
	{
	CSize size;

		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll (size);
		rect.left -= size.cx;
	} else if (nRight > rcClient.right) {
	CSize size;

		size.cx = min((offset+rect.left) - rcClient.left, nRight - rcClient.right);
		size.cy = 0;
		Scroll (size);
		rect.right -= size.cx;
		rect.left -= size.cx;
	}

	rect.left += offset+4;
	rect.right = rect.left + GetColumnWidth (nCol) - 3;

int height = rect.bottom-rect.top;

	rect.bottom += 5*height;
	if (rect.right > rcClient.right) rect.right = rcClient.right;

DWORD dwStyle = WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST;
CComboBox *pList = new CInPlaceComboBox(nItem, nCol, &lstItems, nSel);

	pList -> Create (dwStyle, rect, this, uiId);
	pList -> SetItemHeight (-1, height);
	pList -> SetHorizontalExtent (GetColumnWidth (nCol));
	return pList;
}

///////////////////////////////////////////////////////////////////////////////
// EditSubLabel	- Start edit of a sub item label
// Returns		- Temporary pointer to the new edit control
// nItem		- The row index of the item to edit
// nCol			- The column of the sub item.
CEdit* CListCtrlEx::EditSubLabel (int nItem, int nCol, UINT uiChildId)
{
// The returned pointer should not be saved

// Make sure that the item is visible
	if (!EnsureVisible (nItem, TRUE)) return NULL;

// Make sure that nCol is valid
int nColumnCount = GetColumnCount();

	if (nCol >= nColumnCount || GetColumnWidth(nCol) < 5) 
		return NULL;

// Get the column offset
int offset = 0;

	for (int i = 0; i < nCol; i++) 
		offset += GetColumnWidth (i);

CRect rect;

	GetItemRect (nItem, &rect, LVIR_BOUNDS);

// Now scroll if we need to expose the column
CRect rcClient;
int nRight = offset + rect.left + GetColumnWidth (nCol);

	GetClientRect (&rcClient);
	if (offset + rect.left < 0) 
	{
	CSize size;

		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll (size);
		rect.left -= size.cx;
	} else if (nRight > rcClient.right) {
	CSize size;

		size.cx = min((offset+rect.left) - rcClient.left, nRight - rcClient.right);
		size.cy = 0;
		Scroll (size);
		rect.right -= size.cx;
		rect.left -= size.cx;
	}
	rect.right = rect.left + GetColumnWidth (nCol) - 3;

// Get Column alignment
LV_COLUMN lvcol;

	lvcol.mask = LVCF_FMT;
	GetColumn (nCol, &lvcol);

DWORD dwStyle;

	if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
	else if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
	else dwStyle = ES_CENTER;

	rect.left += offset+4;
	rect.right = rect.left + GetColumnWidth (nCol)  - 3;
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	dwStyle |= WS_BORDER|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL;

CEdit *pEdit = new CInPlaceEdit(nItem, nCol, GetItemText (nItem, nCol));

	pEdit -> Create (dwStyle, rect, this, uiChildId);
	return pEdit;
}

void CListCtrlEx::SelectItem (int iIndex, BOOL fSel)
{
UINT uiState = GetItemState (iIndex, LVIS_SELECTED);

	if (fSel) uiState |= LVIS_SELECTED;
	else	  uiState &= ~LVIS_SELECTED;

	SetItemState (iIndex, uiState, LVIS_SELECTED);
	Update (iIndex);
}

///////////////////////////////////////////////////////////////////////////////
//
BOOL CListCtrlEx::PreCreateWindow(CREATESTRUCT& cs) 
{
// default is report view and full row selection	
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;

//	cs.dwExStyle |= LVS_EX_FULLROWSELECT;
	return CListCtrl::PreCreateWindow(cs);
}

void CListCtrlEx::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (GetFocus()!= this) SetFocus();
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CListCtrlEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (GetFocus()!= this) SetFocus();
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CListCtrlEx::OnEndLabelEdit (NMHDR* pNMHDR, LRESULT* pResult)
{
LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
LV_ITEM *plvItem = &plvDispInfo->item;

	if (plvItem->pszText != NULL)
	{
		SetItemText (plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
	}

	*pResult = FALSE;
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CInPlaceComboBox

CInPlaceComboBox::CInPlaceComboBox(int iItem, int iSubItem, CStringList *plstItems, int nSel)
{
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_lstItems.AddTail (plstItems);
	m_nSel = nSel;
	m_bESC = FALSE;
}

CInPlaceComboBox::~CInPlaceComboBox()
{
}

BEGIN_MESSAGE_MAP(CInPlaceComboBox, CComboBox)
	//{{AFX_MSG_MAP(CInPlaceComboBox)
	ON_WM_CREATE()	
	ON_WM_KILLFOCUS()	
	ON_WM_CHAR()	
	ON_WM_NCDESTROY()
	ON_WM_CTLCOLOR()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInPlaceComboBox message handlers
int CInPlaceComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;	

// Set the proper font
CFont* font = GetParent()->GetFont();

	SetFont(font);
	for (POSITION pos = m_lstItems.GetHeadPosition(); pos != NULL;)  
	{
		AddString ((LPCTSTR) (m_lstItems.GetNext (pos)));
	}
	SetCurSel (m_nSel);
	SetFocus();	
	return 0;
}

BOOL CInPlaceComboBox::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN) 	
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)		
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;				// DO NOT process further		
		}	
	}	
	return CComboBox::PreTranslateMessage(pMsg);
}

void CInPlaceComboBox::OnKillFocus(CWnd* pNewWnd) 
{
	CComboBox::OnKillFocus(pNewWnd);

CString str;

	GetWindowText(str);

// Send Notification to parent of ListView ctrl
LV_DISPINFO dispinfo;

	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	dispinfo.hdr.code = LVN_ENDLABELEDIT;

	dispinfo.item.mask = LVIF_TEXT;	
	dispinfo.item.iItem = m_iItem;
	dispinfo.item.iSubItem = m_iSubItem;
	dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
	dispinfo.item.cchTextMax = str.GetLength();
	GetParent()->GetParent()->SendMessage (WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo);

	PostMessage (WM_CLOSE);
}

void CInPlaceComboBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if (nChar == VK_ESCAPE)
			m_bESC = TRUE;
		GetParent()->SetFocus();
		return;	
	}	
	CComboBox::OnChar(nChar, nRepCnt, nFlags);
}

void CInPlaceComboBox::OnNcDestroy()
{
	CComboBox::OnNcDestroy();
	delete this;
}

void CInPlaceComboBox::OnCloseup()
{
	GetParent()->SetFocus();
}

///////////////////////////////////////////////////////////////////////////////
// Breite des DropDownFensters gleich hier mit anpassen
HBRUSH CInPlaceComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor) {
	case CTLCOLOR_EDIT:
		break;

	case CTLCOLOR_LISTBOX:
		{             
		// benötigte Breite feststellen
		long iListWidth = 0;
		CDC *pDC = GetDC();
		CFont *pOldFont = pDC -> SelectObject (GetFont());

			for (int i = 0; i < GetCount(); i++) {
			CString str;
			CSize sz;

				GetLBText (i, str);
				GetTextExtentPoint32 (pDC -> GetSafeHdc(), str, str.GetLength(), &sz);
				if (pWnd -> GetStyle() & WS_VSCROLL)
					sz.cx += GetSystemMetrics (SM_CXVSCROLL);
				iListWidth = max (iListWidth, sz.cx);
			}

		// jetzt die neue breite setzen
			if (0 < iListWidth) {
			CRect rect;
				
				pWnd->GetWindowRect(&rect);
				if (rect.Width() < iListWidth) {
				// FensterRahmen und etwas Platz lassen
					rect.right = rect.left + iListWidth + 4*GetSystemMetrics(SM_CXBORDER) +2;
					pWnd->MoveWindow(&rect);
				}
			}
			pDC -> SelectObject (pOldFont);
			ReleaseDC(pDC);
		}
		break;
	}
	return hbr; 
}

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit

CInPlaceEdit::CInPlaceEdit(int iItem, int iSubItem, CString sInitText)
	: m_sInitText (sInitText) 
{
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_bESC = FALSE;
}

CInPlaceEdit::~CInPlaceEdit()
{
}


BEGIN_MESSAGE_MAP(CInPlaceEdit, CEdit)
	//{{AFX_MSG_MAP(CInPlaceEdit)
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_CHAR()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit message handlers

BOOL CInPlaceEdit::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) 
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE ||
			pMsg->wParam == VK_ESCAPE || GetKeyState (VK_CONTROL))
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;			// DO NOT process further
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}


void CInPlaceEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

CString str;

	GetWindowText(str);

// Send Notification to parent of ListView ctrl
LV_DISPINFO dispinfo;

	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	dispinfo.hdr.code = LVN_ENDLABELEDIT;

	dispinfo.item.mask = LVIF_TEXT;
	dispinfo.item.iItem = m_iItem;
	dispinfo.item.iSubItem = m_iSubItem;
	dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
	dispinfo.item.cchTextMax = str.GetLength();

	GetParent()->GetParent()->SendMessage (WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo);

	PostMessage (WM_CLOSE);
}

void CInPlaceEdit::OnNcDestroy()
{
	CEdit::OnNcDestroy();

	delete this;
}

void CInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if (nChar == VK_ESCAPE) 
			m_bESC = TRUE;
		GetParent()->SetFocus();
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);

// Resize edit control if needed
// Get text extent
CString str;

	GetWindowText (str);

CWindowDC dc(this);
CFont *pFont = GetParent()->GetFont();
CFont *pFontDC = dc.SelectObject (pFont);
CSize size = dc.GetTextExtent (str);

	dc.SelectObject (pFontDC);
	size.cx += 5;				// add some extra buffer

// Get client rect
CRect rect, parentrect;

	GetClientRect (&rect);
	GetParent()->GetClientRect (&parentrect);

// Transform rect to parent coordinates
	ClientToScreen (&rect);
	GetParent()->ScreenToClient (&rect);

// Check whether control needs to be resized
// and whether there is space to grow
	if (size.cx > rect.Width())
	{
		if (size.cx + rect.left < parentrect.right)
			rect.right = rect.left + size.cx;
		else
			rect.right = parentrect.right;
		MoveWindow (&rect);
	}
}

int CInPlaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

// Set the proper font
CFont* font = GetParent()->GetFont();

	SetFont(font);

	SetWindowText (m_sInitText);
	SetFocus();
	SetSel (0, -1);
	return 0;
}

