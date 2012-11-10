// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.10.2000 13:18:48 
//
// @doc
// @module SelObjPropList.cpp | Definition of the <c CSelObjPropList> class

#include "trias03p.hxx"
#include "trias03.h"

#include <PropName.hxx>
#include <eieruhr.hxx>
#include <TrCatIds.h>

#include "SelObjPropList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NAME_COLUMN		0
#define GROUP_COLUMN	1
#define SUBGROUP_COLUMN	2

#define MINCOLWIDTH		20

///////////////////////////////////////////////////////////////////////////////
// globales
extern TCHAR g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(EnumObjProps);

///////////////////////////////////////////////////////////////////////////////
// 
CSelObjPropList::CSelObjPropList(pDialogWindow pW, ResID uiRes) :
	CListViewCtrl(pW, uiRes), m_iCurrItem(-1)
{
	m_fUp = false;
	m_fDown = false;
}

CSelObjPropList::~CSelObjPropList()
{
// ImageList wird vom Destruktor ~CImageList freigegeben, hier doppeltes Freigeben verhindern
CImageList *pIL = SetImageList (NULL, LVSIL_SMALL);
	
	DELETE_OBJ(pIL);
}

bool CSelObjPropList::GetObjectProperties(list<os_string> &rProps)
{
char cbBuffer[_MAX_PATH];

	for (int i = 0; i < GetItemCount(); ++i) {
	CPropertyName Prop (OBJPROP_ROOT);

		cbBuffer[0] = '\0';
		GetItemText(i, NAME_COLUMN, cbBuffer, sizeof(cbBuffer));
		Prop.SetName(cbBuffer);

		cbBuffer[0] = '\0';
		GetItemText(i, GROUP_COLUMN, cbBuffer, sizeof(cbBuffer));
		Prop.SetGroup(cbBuffer);

		cbBuffer[0] = '\0';
		GetItemText(i, SUBGROUP_COLUMN, cbBuffer, sizeof(cbBuffer));
		if ('\0' != cbBuffer[0])
			Prop.SetSubGroup(cbBuffer);

	os_string str;

		if (Prop.GetFullName(str))
			rProps.push_back (str);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// 
bool CSelObjPropList::InitControl (IObjectProps *pIProps)
{
	_ASSERTE(NULL != pIProps);
	if (!FInit())
		return false;

// new for 'Nashville' 
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = GetExtendedStyle();

		SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_INFOTIP|LVS_EX_SUBITEMIMAGES);
	}
#endif 

// ImageList erzeugen
ResourceFile RF (g_pDLLName);

	m_ilProps.CreateList (ResID(IDB_OBJPROPTYPES, &RF), 16, 0, RGB(255, 0, 255));

// ImageList zuweisen
CImageList *pIL = SetImageList (&m_ilProps, LVSIL_SMALL);
	
	DELETE_OBJ(pIL);

// Spalten erzeugen
ResString resName (ResID(IDS_OBJPROPERTY_COLUMN, &RF), 64);
ResString resGroup (ResID(IDS_GROUP_COLUMN, &RF), 64);
ResString resSubGroup (ResID(IDS_SUBGROUP_COLUMN, &RF), 64);

	InsertColumn (NAME_COLUMN, resName, LVCFMT_LEFT, -1, NAME_COLUMN);
	InsertColumn (GROUP_COLUMN, resGroup, LVCFMT_LEFT, -1, GROUP_COLUMN);
	InsertColumn (SUBGROUP_COLUMN, resSubGroup, LVCFMT_LEFT, -1, SUBGROUP_COLUMN);

// Liste füllen
	m_Props = pIProps;
	return true;
}

bool CSelObjPropList::FillWithItems(list<os_string> &rLstProps)
{
CEierUhr Wait(GetParent());
WEnumObjProps Enum;
HRESULT hr = m_Props -> EnumObjectProps (Enum.ppi());

	if (FAILED(hr)) return false;

int iCnt = 0;

	ForwardEvent (WM_SETREDRAW, FALSE);

	DeleteAllItems();		// erstmal alles rauslöschen
	for (list<os_string>::iterator it = rLstProps.begin(); it != rLstProps.end(); ++it) {
	CPropertyName Name ((*it).c_str());
	char cbBuffer[_MAX_PATH];
	WObjectProperty ObjProp;

		if (Name.GetFullName(cbBuffer, sizeof(cbBuffer)) &&
			SUCCEEDED(Enum -> FindByName(cbBuffer, ObjProp.ppi()))) 
		{
		DWORD dwFlags = 0L;		// Flags für Bildchen

			hr = ObjProp -> GetPropInfo (NULL, 0, &dwFlags);
			if (FAILED(hr))	continue;		// Fehler ?

		LV_ITEM lvi;

		// Bildchen in der ersten Spalte
			memset (&lvi, 0, sizeof(LV_ITEM));
			lvi.mask = LVIF_IMAGE|LVIF_TEXT|LVIF_PARAM;
			lvi.pszText = const_cast<char *>(Name.GetName().c_str());
			lvi.iItem = iCnt++;
			lvi.iSubItem = NAME_COLUMN;
			lvi.iImage = m_ilProps.GetImageIndex(dwFlags);
			lvi.lParam = NULL;
			
		int iItem = InsertItem (&lvi);

			if (-1 == iItem) 
				continue;

		// zweite Spalte enthält den Namen
			memset (&lvi, 0, sizeof(LV_ITEM));
			lvi.mask = LVIF_TEXT;
			lvi.pszText = const_cast<char *>(Name.GetGroup().c_str());
			lvi.iItem = iItem;
			lvi.iSubItem = GROUP_COLUMN;
			SetItem (&lvi);

		// dritte Spalte enthält die Group
			if (Name.hasSubGroup()) {
				memset (&lvi, 0, sizeof(LV_ITEM));
				lvi.mask = LVIF_TEXT;
				lvi.pszText = const_cast<char *>(Name.GetSubGroup().c_str());
				lvi.iItem = iItem;
				lvi.iSubItem = SUBGROUP_COLUMN;
				SetItem (&lvi);
			}
		}
	}

// Breite der Spalten anpassen
	FitColumns();
	ForwardEvent (WM_SETREDRAW, TRUE);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// alles, was selektiert ist, nach oben verschieben
bool CSelObjPropList::MoveItemUp (void)
{
int iFocus = GetItemFocus();
int iIndex = GetFirstSelected();

	if (iIndex <= 0) {
		MessageBeep (MB_ICONHAND);
		return false;
	}

int iFocusN = iFocus;
int iFirst = iIndex-1;
int iLast = iIndex;

	do {
	int iIndexN = iIndex-1;

		iLast = max(iLast, iIndex);
		if (iIndex == iFocus)
			iFocusN = iIndexN;		// muß am Schluß sichtbar bleiben

		if (!SwapItems (iIndex, iIndexN)) 
			return false;

		iIndex = GetNextSelected();
	} while (iIndex > 0);

	EnsureVisible (iFocusN, false);

	return RedrawItems (iFirst, iLast);
}

bool CSelObjPropList::MoveItemDown (void)
{
int iFocus = GetItemFocus();
int iIndex = GetLastSelected();	// beim letzten anfangen

	if (iIndex >= GetItemCount()-1) {
		MessageBeep (MB_ICONHAND);
		return false;
	}

int iFocusN = iFocus;
int iFirst = iIndex;
int iLast = iIndex+1;

	do {
	int iIndexN = iIndex+1;

		iFirst = min(iFirst, iIndex);
		if (iIndex == iFocus)
			iFocusN = iIndexN;		// muß am Schluß sichtbar bleiben

		if (!SwapItems (iIndex, iIndexN))
			return false;	 // Fehler

		iIndex = GetPrevSelected();
	} while (iIndex >= 0);

	EnsureVisible (iFocusN, false);
	return RedrawItems (iFirst, iLast);
}

bool CSelObjPropList::SwapItems (int iIndexO, int iIndexN)
{
	if (iIndexO == iIndexN) 
		return false;

// beteiligte Items besorgen
LV_ITEM lviCurr, lviCurrSub, lviCurrSub2;
char cbCurr[64], cbCurrSub[64], cbCurrSub2[64];

	lviCurr.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
	lviCurr.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
	lviCurr.iItem = iIndexO;
	lviCurr.iSubItem = NAME_COLUMN;
	lviCurr.pszText = cbCurr;
	lviCurr.cchTextMax = sizeof(cbCurr);
	GetItem (&lviCurr);

	lviCurrSub.mask = LVIF_TEXT;
	lviCurrSub.iItem = iIndexO;
	lviCurrSub.iSubItem = GROUP_COLUMN;
	lviCurrSub.pszText = cbCurrSub;
	lviCurrSub.cchTextMax = sizeof(cbCurrSub);
	GetItem (&lviCurrSub);

	lviCurrSub2.mask = LVIF_TEXT;
	lviCurrSub2.iItem = iIndexO;
	lviCurrSub2.iSubItem = SUBGROUP_COLUMN;
	lviCurrSub2.pszText = cbCurrSub2;
	lviCurrSub2.cchTextMax = sizeof(cbCurrSub2);
	GetItem (&lviCurrSub2);

LV_ITEM lviPrev, lviPrevSub, lviPrevSub2;
char cbPrev[64], cbPrevSub[64], cbPrevSub2[64];

	lviPrev.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
	lviPrev.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
	lviPrev.iItem = iIndexN;
	lviPrev.iSubItem = NAME_COLUMN;
	lviPrev.pszText = cbPrev;
	lviPrev.cchTextMax = sizeof(cbPrev);
	GetItem (&lviPrev);

	lviPrevSub.mask = LVIF_TEXT;
	lviPrevSub.iItem = iIndexN;
	lviPrevSub.iSubItem = GROUP_COLUMN;
	lviPrevSub.pszText = cbPrevSub;
	lviPrevSub.cchTextMax = sizeof(cbPrevSub);
	GetItem (&lviPrevSub);

	lviPrevSub2.mask = LVIF_TEXT;
	lviPrevSub2.iItem = iIndexN;
	lviPrevSub2.iSubItem = SUBGROUP_COLUMN;
	lviPrevSub2.pszText = cbPrevSub2;
	lviPrevSub2.cchTextMax = sizeof(cbPrevSub2);
	GetItem (&lviPrevSub2);

// beteiligte Items vertauschen
	lviCurr.iItem = lviCurrSub.iItem = lviCurrSub2.iItem = iIndexN;
	SetItem (&lviCurrSub2);
	SetItem (&lviCurrSub);
	SetItem (&lviCurr);

	lviPrev.iItem = lviPrevSub.iItem = lviPrevSub2.iItem = iIndexO;
	SetItem (&lviPrevSub2);
	SetItem (&lviPrevSub);
	SetItem (&lviPrev);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// diverse Helperfunktionen
int CSelObjPropList::GetItemFocus (void)
{
int iCnt = GetItemCount();

	for (int iIndex = 0; iIndex < iCnt; iIndex++) {
	// Alle Einträge der Listbox abarbeiten
	UINT uiState = GetItemState (iIndex, LVIS_FOCUSED);

		if (uiState & LVIS_FOCUSED)
			return iIndex;
	}
	return -1;
}

int CSelObjPropList::GetFirstSelected (void)
{
	m_iCurrItem = -1;				// aufsteigend
	return GetNextSelected();
}

int CSelObjPropList::GetLastSelected (void)
{
	m_iCurrItem = GetItemCount()-1;	// absteigend
	if (IsItemSelected (m_iCurrItem))
		return m_iCurrItem;			// der Letzte ist selektiert

	return GetPrevSelected();
}

int CSelObjPropList::GetNextSelected (void)
{
	return (m_iCurrItem = GetNextItem (m_iCurrItem, LVNI_ALL|LVNI_SELECTED));
}

int CSelObjPropList::GetPrevSelected (void)
{
	return (m_iCurrItem = GetNextItem (m_iCurrItem, LVNI_SELECTED|LVNI_ABOVE));
}

bool CSelObjPropList::IsItemSelected (int iIndex)
{
	_ASSERTE(iIndex >= 0 && iIndex < GetItemCount());

UINT uiState = GetItemState (iIndex, LVIS_SELECTED);

	return (GetItemState(iIndex, LVIS_SELECTED) & LVIS_SELECTED) ? true : false;
}

void CSelObjPropList::FitColumns(int iColMin, int iColMax)
{
// Call this after your list control is filled     
	ForwardEvent(WM_SETREDRAW, FALSE);

int mincol = iColMin < 0 ? 0 : iColMin;
int maxcol = iColMax < 0 ? GetColumnCount()-1 : iColMax;

	for (int col = mincol; col <= maxcol; col++) {
		SetColumnWidth(col, LVSCW_AUTOSIZE);

	int wc1 = GetColumnWidth (col);

		SetColumnWidth (col, LVSCW_AUTOSIZE_USEHEADER);

	int wc2 = GetColumnWidth (col);
	int wc = max (MINCOLWIDTH, max(wc1, wc2));

		SetColumnWidth (col, wc);     
	}

	ForwardEvent(WM_SETREDRAW, TRUE);
	InvalidateRect (Handle(), NULL, true); 
}

int CSelObjPropList::GetColumnCount(void)
{
HWND hCtrl = GetDlgItem (Handle(), 0);

	TX_ASSERT(::IsWindow(hCtrl));
	return Header_GetItemCount (hCtrl);
}

