// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 24.04.2002 12:31:03 
//
// @doc
// @module AssociateLayersToClasses.cpp | Definition of the <c CAssociateLayersToClasses> class

#include "bnaimpp.hpp"

#include <errinstx.hxx>

#include "relkey.hxx"
#include "AssociateLayersToClasses.h"

///////////////////////////////////////////////////////////////////////////////
// eigene Messages
const UINT WM_SHOWCOMBO = RegisterWindowMessage("WM_SHOWCOMBO");
const UINT WM_DESTROYCOMBO = RegisterWindowMessage("WM_DESTROYCOMBO");
const UINT WM_ITEMSELECTED = RegisterWindowMessage("WM_ITEMSELECTED");
const UINT WM_ADDNEWENTRY = RegisterWindowMessage("WM_ADDNEWENTRY");
const UINT WM_COPYBNAENTRY = RegisterWindowMessage("WM_COPYBNAENTRY");

///////////////////////////////////////////////////////////////////////////////
// ListView für Gegenüberstellung von Layern und Objektklassen
CAssociateLayersToClasses::CAssociateLayersToClasses(DialogWindow *pW, UINT uiID) :
	ControlWindow (new CListViewCtrl(pW, uiID)),
	m_pList(NULL),
	m_uiID(99),
	m_fGcoProduction(false)
{
}

CAssociateLayersToClasses::~CAssociateLayersToClasses()
{
CImageList *pIL = NULL;

	pIL = SetImageList (NULL, LVSIL_SMALL);
	DELETE_OBJ(pIL);

	if (NULL != GetControl())
		delete (CListViewCtrl *)GetControl();
}

///////////////////////////////////////////////////////////////////////////////
// Initialisieren des Inhaltes
inline
int GetImage (DWORD dwType)
{
	if (dwType & OTPunkt) 
		return IMAGE_POINT;
	if (dwType & OTLinie) 
		return IMAGE_LINE;
	if (dwType & OTFlaeche) 
		return IMAGE_AREA;
	if (dwType & OTText) 
		return IMAGE_TEXT;
	return -1;	
}

inline 
DWORD GetObjTypeFromImage (int iImage)
{
	switch (iImage) {
	case IMAGE_POINT:
		return OTPunkt;

	case IMAGE_LINE:
		return OTLinie;

	case IMAGE_AREA:
		return OTFlaeche;

	case IMAGE_TEXT:
		return OTText;

	default:
		break;
	}

	_ASSERTE(IMAGE_POINT == iImage || IMAGE_LINE == iImage || 
		IMAGE_AREA == iImage || IMAGE_TEXT == iImage);
	return OTAll;
}

BOOL CAssociateLayersToClasses::AddObjType (int &riCnt, TR_Layer *pLayer, DWORD dwType)
{
// Spalten füllen
LV_ITEM lvi;

	lvi.mask = LVIF_IMAGE|LVIF_PARAM;
	lvi.iItem = ++riCnt;
	lvi.iSubItem = PICTURE_COLUMN;
	lvi.iImage = GetImage(dwType);
	lvi.lParam = reinterpret_cast<DWORD>(pLayer);

int iItem = GetListView()->InsertItem (&lvi);

	if (-1 != iItem) {
		memset (&lvi, 0, sizeof(LV_ITEM));
		lvi.mask = LVIF_TEXT;
		lvi.pszText = (LPSTR)pLayer -> BNAText();
		lvi.iItem = iItem;
		lvi.iSubItem = LAYER_COLUMN;
		GetListView()->SetItem (&lvi);

	LPCSTR pcKurzText = pLayer -> KurzText(dwType);
	bool fHasAssoc = (NULL != pcKurzText && '\0' != *pcKurzText);

		memset (&lvi, 0, sizeof(LV_ITEM));
		lvi.mask = LVIF_IMAGE;
		lvi.iItem = iItem;
		lvi.iImage = fHasAssoc ? IMAGE_CHECKED : IMAGE_UNCHECKED;
		lvi.iSubItem = CHECK_COLUMN;
		GetListView()->SetItem (&lvi);

		memset (&lvi, 0, sizeof(LV_ITEM));
		lvi.mask = LVIF_TEXT;
		lvi.pszText = (LPSTR)(fHasAssoc ? pcKurzText : "");
		lvi.iItem = iItem;
		lvi.iSubItem = CLASS_COLUMN;
		GetListView()->SetItem (&lvi);
	}
	return TRUE;
}

BOOL CAssociateLayersToClasses::FInit(TR_LayerTree *pOKSTree, HPROJECT hPr,
	bool fGcoProduction)
{
	m_fGcoProduction = fGcoProduction;
	if (!ControlWindow::FInit())
		return FALSE;

	if ( !pOKSTree )
		return FALSE;

	m_hPr = hPr;

#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = GetListView()->GetExtendedStyle();

		GetListView()->SetExtendedStyle (dwStyleEx | 
			LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	}
#endif

// ImageList initialisieren
ResourceFile RF (g_pDLLName);
CImageList *pIL = NULL;

	m_ilType.CreateList (ResID(IDB_PLFT_LARGE, &RF), 15, 0, RGB(255, 0, 255));
	pIL = SetImageList (&m_ilType, LVSIL_SMALL);
	DELETE_OBJ(pIL);

// Spalten erzeugen
ResString resTyp (ResID (IDS_HEADERTYP, &RF), 32);		// "Typ"
ResString resLayer (ResID (IDS_HEADERLAYER, &RF), 32);	// "Objektklassenschlüssel"
ResString resImport (ResID (IDS_HEADERIMPORT, &RF), 32);	// "Importieren"
ResString resClass (ResID (IDS_HEADERCLASS, &RF), 32);	// "Beschreibung"

	InsertColumn (PICTURE_COLUMN, resTyp, LVCFMT_LEFT, -1, PICTURE_COLUMN);
	InsertColumn (LAYER_COLUMN, resLayer, LVCFMT_LEFT, -1, LAYER_COLUMN);
	InsertColumn (CHECK_COLUMN, resImport, LVCFMT_LEFT, -1, CLASS_COLUMN);
	InsertColumn (CLASS_COLUMN, resClass, LVCFMT_LEFT, -1, CLASS_COLUMN);

// Daten einfügen
CTable t (*pOKSTree);
int iCnt = 0;

	for (t.First(); t.Valid(); t.Next()) {
	TR_LayerLock l(t);

		if (!l) continue;

	// jeden Objekttyp ggf. einzeln einfügen
		if (l->GetTypes() & OTPunkt) AddObjType (iCnt, l, OTPunkt);
		if (l->GetTypes() & OTLinie) AddObjType (iCnt, l, OTLinie);
		if (l->GetTypes() & OTFlaeche) AddObjType (iCnt, l, OTFlaeche);
		if (l->GetTypes() & OTText) AddObjType (iCnt, l, OTText);
	}

// Spaltenbreite anpassen
	FitColumn (PICTURE_COLUMN);
	FitColumn (LAYER_COLUMN);
	FitColumn (CHECK_COLUMN, false);
	FitColumn (CLASS_COLUMN);
	return TRUE;
}

void CAssociateLayersToClasses::FitColumn (int iCol, bool fAccountForHeader)
{
// Call this after your list control is filled     
	SetRedraw(false);

int mincol = iCol < 0 ? 0 : iCol;
int maxcol = iCol < 0 ? GetColumnCount()-1 : iCol;

	for (int col = mincol; col <= maxcol; col++) {
		SetColumnWidth(col, LVSCW_AUTOSIZE);

	int wc1 = GetColumnWidth (col);

		if (fAccountForHeader) {
			SetColumnWidth (col, LVSCW_AUTOSIZE_USEHEADER);

		int wc2 = GetColumnWidth (col);

			SetColumnWidth (col, max(MINCOLWIDTH, max(wc1, wc2)));     
		}
		else 
			SetColumnWidth (col, max(MINCOLWIDTH, wc1));     
	}

//	RecalcHeaderTips(); 
	SetRedraw (true);
	InvalidateRect (Handle(), NULL, true); 
}

///////////////////////////////////////////////////////////////////////////////
// MessageHandling
LRESULT CAssociateLayersToClasses::Dispatch (Event e)
{
	if (WM_SHOWCOMBO == e.Msg()) 
		return OnShowCombo(e.WParam(), e.LParam());	// InPlaceComboBox anzeigen

	if (WM_ITEMSELECTED == e.Msg())
		OnItemSelected(e.WParam(), e.LParam());

	if (WM_DESTROYCOMBO == e.Msg())
		OnCloseUp(LOWORD(e.WParam()));

	else if (WM_COMMAND == e.Msg() && CBN_CLOSEUP == HIWORD(e.WParam())) 
		PostEvent (WM_DESTROYCOMBO, e.WParam());	// ComboBox zerlegen

	return ControlWindow::Dispatch(e);
}

void CAssociateLayersToClasses::MouseButtonDn (MouseEvt e) 
{
	ControlWindow::MouseButtonDn (e);
	if (!e.isLeftButton())
		return;

int index;
int colnum;

	if ((index = HitTestEx ((POINT &)e.Where(), &colnum)) != -1) {
		if ((GetListView() -> GetItemState(index, LVIS_FOCUSED) & LVIS_FOCUSED) 
			== LVIS_FOCUSED) 
		{
		// Add check for right column
			if (CLASS_COLUMN == colnum)
				PostEvent (WM_SHOWCOMBO, index, colnum);
		} 
	}
}

void CAssociateLayersToClasses::MouseButtonDblClk (MouseEvt e)
{
	ControlWindow::MouseButtonDn (e);
	if (!e.isLeftButton())
		return;

int index;
int colnum;

	if ((index = HitTestEx ((POINT &)e.Where(), &colnum)) != -1) {
		if ((GetListView() -> GetItemState(index, LVIS_FOCUSED) & LVIS_FOCUSED) 
			== LVIS_FOCUSED) 
		{
		// Add check for right column
			PostEvent (WM_SHOWCOMBO, index, CLASS_COLUMN);
		} 
	}
}

///////////////////////////////////////////////////////////////////////////////
// ListView soll gerollt werden, ComboBox zerlegen
void CAssociateLayersToClasses::HorizScroll (ScrollEvt e)
{
	if (::GetFocus() != Handle()) {
		SetFocus();
		Update();
	}
	ControlWindow::HorizScroll (e);
}

void CAssociateLayersToClasses::VertScroll (ScrollEvt e)
{
	if (::GetFocus() != Handle()) {
		SetFocus();
		Update();
	}
	ControlWindow::VertScroll (e);
}

void CAssociateLayersToClasses::OnClick (NMHDR *pNMHDR, LRESULT *plResult)
{
POINT pt;
Rectangle rcWnd (CanvasRect());

	GetCursorPos(&pt);
	ScreenToClient(Handle(), &pt);
	pt.y = rcWnd.Height() - pt.y -1;

int index;
int colnum;

	if ((index = HitTestEx (pt, &colnum)) != -1) {
		if ((GetListView() -> GetItemState(index, LVIS_FOCUSED) & LVIS_FOCUSED) 
			== LVIS_FOCUSED) 
		{
		// Add check for right column
			if (CHECK_COLUMN == colnum)
				PostEvent (WM_ITEMSELECTED, index, colnum);
		} 
	}
	*plResult = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// HitTestEx    - Determine the row index and column index for a point
// Returns      - the row index or -1 if point is not over a row
// point        - point to be tested.
// col          - to hold the column index
int CAssociateLayersToClasses::HitTestEx (POINT point, int *col) 
{
RECT rc;

	GetClientRect (Handle(), &rc);
	point.y = (rc.bottom-rc.top) - point.y -1;

int colnum = 0;
int row = GetListView() -> HitTest ((Point &)point, NULL);

	if (col) *col = 0;

// Make sure that the ListView is in LVS_REPORT
	if ((GetStyle() & LVS_TYPEMASK) != LVS_REPORT)
		return row;

// Get the top and bottom row visible
	row = GetListView() -> GetTopIndex();

int bottom = row + GetListView() -> GetCountPerPage();

	if (bottom > GetListView() -> GetItemCount())
		bottom = GetListView() -> GetItemCount();

// Get the number of columns
int nColumnCount = GetColumnCount();

// Loop through the visible rows
	for (/**/ ; row <=bottom; row++) {
	// Get bounding rect of item and check whether point falls in it.
	RECT rect;

		GetListView() -> GetItemRect (row, &rect, LVIR_BOUNDS);
		if (PtInRect (&rect, (POINT &)point)) {
		// Now find the column
			for (colnum = 0; colnum < nColumnCount; colnum++) {
			int colwidth = GetColumnWidth (colnum);

				if (point.x >= rect.left && point.x <= (rect.left + colwidth))
				{
					if (col) 
						*col = colnum;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// ShowInPlaceList		- Creates an in-place drop down list for any 
//				- cell in the list view control
// Returns			- A temporary pointer to the combo-box control
// nItem			- The row index of the cell
// nCol				- The column index of the cell
// lstItems			- A list of strings to populate the control with
// nSel				- Index of the initial selection in the drop down list
ComboBox* CAssociateLayersToClasses::ShowInPlaceList(int nItem, int nCol, 
	CStringList &lstItems, int nSel, LPCSTR pcInitEntry)
{
// The returned pointer should not be saved

// Make sure that the item is visible
	if (!GetListView() -> EnsureVisible (nItem, TRUE)) 
		return NULL;

// Make sure that nCol is valid 
int nColumnCount = GetColumnCount();

	if (nCol >= nColumnCount || GetColumnWidth(nCol) < 10) 
		return NULL;

// Get the column offset
int offset = 0;

	for (int i = 0; i < nCol; i++)
		offset += GetColumnWidth (i);

RECT rect;
	
	GetListView() -> GetItemRect (nItem, &rect, LVIR_BOUNDS);

// Now scroll if we need to expose the column
RECT rcClient;
int nRight = offset + rect.left + GetColumnWidth (nCol);

	GetClientRect (Handle(), &rcClient);
	if (offset + rect.left < 0) {
	Dimension size (offset + rect.left, 0);

		GetListView() -> Scroll (size);
		rect.left -= size.Width();

	} 
	else if (nRight > rcClient.right) {
	Dimension size (min((offset+rect.left) - rcClient.left, nRight - rcClient.right), 0);

		GetListView() -> Scroll (size);
		rect.right -= size.Width();
		rect.left -= size.Width();
	}

	rect.left += offset + 2;
	rect.right = rect.left + GetColumnWidth (nCol) - 3 ;

int height = rect.bottom-rect.top;

	rect.bottom += 6*height;
	if (rect.right > rcClient.right) 
		rect.right = rcClient.right;

DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|CBS_DROPDOWNLIST|
	CBS_DISABLENOSCROLL|CBS_SORT;
Point pt (rect.left, (rcClient.bottom-rcClient.top) - rect.bottom + 3);
Dimension dim (rect.right-rect.left, rect.bottom-rect.top);

	_ASSERTE(NULL == m_pList);
	m_pList = new CInPlaceCombo (this, ++m_uiID, pt, dim, dwStyle);
	m_pList -> Create (nItem, nCol, lstItems, nSel, pcInitEntry);
	m_pList -> SetItemHeight (-1, height);
	if (IsWin40())
		m_pList -> SetHorizontalExtent (GetColumnWidth (nCol));

	return m_pList -> GetComboBox();
}

///////////////////////////////////////////////////////////////////////////////
// InPlaceComboBox anzeigen
extern "C" 
BOOL CALLBACK FillComboBoxList (long lIdent, bool, void *pData)
{
char cbText[_MAX_PATH];
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;		// Nun mit Text definieren

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbText;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = sizeof(cbText)-1;
	pbdData.pbdLTextLen = 0;
	if (EC_OKAY != DEX_GetPBDData(pbdData))
		return TRUE;	// trotzdem weitermachen

	((CStringList *)pData) -> insert(cbText);
	return TRUE;
}

BOOL CAssociateLayersToClasses::OnShowCombo (int index, int colnum)
{
	if (-1 == index)
		index = GetFocusItem();
	if (-1 == index) {
		if (0 == GetItemCount())
			return FALSE;
		index = 0;
	}

// ComboBox erzeugen und füllen
CStringList lstItems;
ENUMLONGKEY ENK;

	ENK.eKey = 'i';
	ENK.eFcn = (ENUMLONGKEYPROC)FillComboBoxList;
	ENK.ePtr = &lstItems;
	DEX_EnumPBDDataEx (m_hPr, ENK);

ResourceFile RF (g_pDLLName);
ResString resNewItem (ResID(IDS_NEWITEM, &RF), 32);
ResString resBnaItem (ResID(IDS_BNAITEM, &RF), 32);

	ATLTRY(lstItems.insert(resNewItem.Addr()));
	if (!m_fGcoProduction) {
		ATLTRY(lstItems.insert(resBnaItem.Addr()));
	}
	if (0 == lstItems.size())
		MessageBeep (MB_ICONEXCLAMATION);
	else {
		Update();		// evtl. existierende ComboBox sicher ausblenden

		m_vecItems.erase();

	// derzeit selektierte Items speichern
	int iIndex = GetFirstSelected();

		while (-1 != iIndex) {
			m_vecItems.push_back(iIndex);
			iIndex = GetNextSelected();
		}

	// Voreinstellung für ComboBox berechnen
	int iInit = 0;
	string strItem = GetListView()->GetItemText(index, colnum);
	CStringList::iterator end = lstItems.end();

		for (CStringList::iterator it = lstItems.begin(); 
			 it != end; ++it, ++iInit) 
		{
			if (strItem == *it) 
				break;
		}
		if (iInit >= lstItems.size())
			iInit = -1;

	// ComboBox anzeigen
		ShowInPlaceList (index, colnum, lstItems, iInit, "");
	}
	return TRUE;
}

void CAssociateLayersToClasses::FocusChange (FocusChangeEvt e)
{
	if (e.gotFocus() && NULL != m_pList)
		m_pList -> OnCloseup();
	ControlWindow::FocusChange(e);
}

void CAssociateLayersToClasses::OnCloseUp (UINT uiID)
{
	_ASSERTE(uiID == m_uiID);
	if (NULL != m_pList)			// nur, wenn nicht 'ESC'
		m_pList -> OnCloseup();
}

void CAssociateLayersToClasses::OnEndLabelEdit (NMHDR *pNMHDR, LRESULT *plResult)
{
	_ASSERTE(pNMHDR -> idFrom == m_uiID);

LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
LV_ITEM	*plvItem = &plvDispInfo->item;	

	if (NULL != plvItem->pszText) {
	ResourceFile RF (g_pDLLName);
	ResString resNewItem (ResID(IDS_NEWITEM, &RF), 32);
	ResString resBnaItem (ResID(IDS_BNAITEM, &RF), 32);

		if (!strcmp(resNewItem, plvItem->pszText)) {
			GetParent()->PostEvent(WM_ADDNEWENTRY);
		}
		else if (!strcmp(resBnaItem, plvItem->pszText)) {
			GetParent()->PostEvent(WM_COPYBNAENTRY);
		}
		else {
		bool fFound = false;		// selektierten Eintrag auf jeden Fall behandeln
		CSelectedItems::iterator end = m_vecItems.end();

			for (CSelectedItems::iterator it = m_vecItems.begin(); it != end; ++it) {
				SetClassText (*it, plvItem->pszText);
				if (*it == plvItem->iItem)
					fFound = true;
			}
			if (!fFound)
				SetClassText (plvItem->iItem, plvItem->pszText);
		}
	}
	else {
	// CheckState wieder zurücksetzen
		OnItemSelected(plvItem->iItem, CHECK_COLUMN);
	}

	m_pList = NULL;
	*plResult = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Zurückschreiben einer neuen Objektklasse
bool CAssociateLayersToClasses::SetClassText (int iIndex, LPCSTR pcNewClass)
{
	if (iIndex == -1 || iIndex > GetItemCount())
		return false;

	_ASSERTE(NULL != pcNewClass);
	GetListView()->SetItemText(iIndex, CLASS_COLUMN, (LPSTR)pcNewClass);
	SetCheckState(iIndex, (NULL != pcNewClass && '\0' != pcNewClass[0]) ? true : false);

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// CheckBox umschalten
void CAssociateLayersToClasses::OnItemSelected (int index, int colnum)
{
	_ASSERTE(colnum == CHECK_COLUMN);

bool fChecked = !GetCheckState(index);
bool fFound = false;		// selektierten Eintrag auf jeden Fall behandeln
int iIndex = GetFirstSelected();

	while (-1 != iIndex) {
		SetCheckState (iIndex, fChecked);
		if (!fChecked)
			ResetClassText(iIndex);
		if (iIndex == index)
			fFound = true;
		iIndex = GetNextSelected();
	}

	if (!fFound) {
		SetCheckState (index, fChecked);
		if (!fChecked)
			ResetClassText(index);
	}

// wenn Haken gesetzt wurde, ohne das Text da ist, dann Zuordnung erzwingen
	if (fChecked && 0 == GetListView()->GetItemText(index, CLASS_COLUMN).size())
		PostEvent(WM_SHOWCOMBO, index, CLASS_COLUMN);
}

///////////////////////////////////////////////////////////////////////////////
// CheckState behandeln
bool CAssociateLayersToClasses::GetCheckState(int iIndex)
{
LV_ITEM lvi;

	memset(&lvi, '\0', sizeof(LV_ITEM));
	lvi.mask = LVIF_IMAGE;
	lvi.iItem = iIndex;
	lvi.iSubItem = CHECK_COLUMN;
	GetListView()->GetItem(&lvi);
	return (IMAGE_CHECKED == lvi.iImage ) ? true : false;
}

void CAssociateLayersToClasses::SetCheckState (int iIndex, bool fCheck)
{
LV_ITEM lvi;

	memset(&lvi, '\0', sizeof(LV_ITEM));
	lvi.mask = LVIF_IMAGE;
	lvi.iItem = iIndex;
	lvi.iSubItem = CHECK_COLUMN;
	lvi.iImage = fCheck ? IMAGE_CHECKED : IMAGE_UNCHECKED;
	GetListView()->SetItem(&lvi);
}

void CAssociateLayersToClasses::ResetClassText(int iIndex)
{
// Text löschen
LV_ITEM lvi;

	memset(&lvi, '\0', sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = iIndex;
	lvi.pszText = "";
	lvi.iSubItem = CLASS_COLUMN;
	GetListView()->SetItem(&lvi);
}

// Liefert Nutzerauswahl
string CAssociateLayersToClasses::GetLayerName(int iIndex)
{
	_ASSERTE(-1 <= iIndex && iIndex < GetItemCount());
	if (-1 == iIndex)
		iIndex = GetFocusItem();

char cbBuffer[_MAX_PATH];
LV_ITEM lvi;

	memset(&lvi, '\0', sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = iIndex;
	lvi.iSubItem = LAYER_COLUMN;
	lvi.pszText = cbBuffer;
	lvi.cchTextMax = sizeof(cbBuffer);
	GetListView()->GetItem(&lvi);

	return cbBuffer;
}

string CAssociateLayersToClasses::GetClassName(int iIndex)
{
	_ASSERTE(-1 <= iIndex && iIndex < GetItemCount());
	if (-1 == iIndex)
		iIndex = GetFocusItem();

char cbBuffer[_MAX_PATH];
LV_ITEM lvi;

	memset(&lvi, '\0', sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = iIndex;
	lvi.iSubItem = CLASS_COLUMN;
	lvi.pszText = cbBuffer;
	lvi.cchTextMax = sizeof(cbBuffer);
	GetListView()->GetItem(&lvi);

	return cbBuffer;
}

DWORD CAssociateLayersToClasses::GetObjType(int iIndex)
{
	_ASSERTE(-1 <= iIndex && iIndex < GetItemCount());
	if (-1 == iIndex)
		iIndex = GetFocusItem();

LV_ITEM lvi;

	memset(&lvi, '\0', sizeof(LV_ITEM));
	lvi.mask = LVIF_IMAGE;
	lvi.iItem = iIndex;
	lvi.iSubItem = PICTURE_COLUMN;
	GetListView()->GetItem(&lvi);

	return GetObjTypeFromImage(lvi.iImage);
}

bool CAssociateLayersToClasses::GetDoImport(int iIndex)
{
	_ASSERTE(-1 <= iIndex && iIndex < GetItemCount());
	if (-1 == iIndex)
		iIndex = GetFocusItem();

	return GetCheckState(iIndex);
}

