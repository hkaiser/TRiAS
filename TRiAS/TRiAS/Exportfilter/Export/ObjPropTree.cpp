// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 23.08.2002 09:00:41 
//
// @doc
// @module ObjPropTree.cpp | Definition of the <c CObjPropTree> class

#include "stdafx.h"
#include "export.h"

#include <ospace/std/set>
#include <ospace/std/list>
#include <PropNamex.h>

#include "resource.h"
#include "ObjPropTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjPropTree

CObjPropTree::CObjPropTree(INCLUDEOBJPROP pFcn, bool fUseCheckMarks, 
		bool fUsePartialCheckMarks) :
	m_pFcn(pFcn), m_fHasSelectedItem(false)
{
#if defined(_USE_CHECKMARK_OBJPROPTREE)
	m_fUseCheckMarks = fUseCheckMarks;
	m_fUsePartialCheckMarks = fUsePartialCheckMarks;
	m_lLimitCnt = -1;
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
}

CObjPropTree::~CObjPropTree()
{
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
inline 
bool SetContainsString (set<os_string> &rSet, os_string &rStr)
{
set<os_string>::iterator it = rSet.find(rStr);

	return (it != rSet.end()) ? true : false;
}

int GetImageIndex (DWORD dwFlags)
{
	if (dwFlags & PROPCAPS_OBJPROPTYPE_INTEGER)
		return IMG_INTEGERPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_DOUBLE)
		return IMG_DOUBLEPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_BOOL)
		return IMG_BOOLPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_DATE)
		return IMG_DATUMPROP;

	return IMG_TEXTPROP;
}

BOOL CObjPropTree::Init(IObjectProps *pIProps, list<os_string> &rStrs)
{
#if !defined(_USE_CHECKMARK_OBJPROPTREE)
// derzeit ohne Checkmarks, also nur max. eine Voreinstellung
	_ASSERTE(1 >= rStrs.size());
#endif // !defined(_USE_CHECKMARK_OBJPROPTREE)

	if (FAILED(pIProps->QueryInterface(m_Props.ppi()))) {
		_ASSERTE(FALSE);
		return FALSE;
	}

// ImageListen initialisieren
	{
		AFX_MANAGE_STATE(AfxGetAppModuleState());
		m_imgList.Create(IDB_OBJPROPTYPES, 16, 16, RGB(255, 0, 255));
		_ASSERTE(NULL != HIMAGELIST(m_imgList));

		SetImageList(&m_imgList, TVSIL_NORMAL);

#if defined(_USE_CHECKMARK_OBJPROPTREE)
		if (UseCheckMarks()) {
			m_imgListCk.Create(IDB_CHECKMARKS, 15, 0, RGB(255, 255, 255));
			_ASSERTE(NULL != HIMAGELIST(m_imgListCk));

			SetImageList(&m_imgListCk, TVSIL_STATE);
		}
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
	}

// Objekteigenschaften in Gruppen sortiert im Baum einhängen
set<os_string> setStrs;

	copy (rStrs.begin(), rStrs.end(), inserter(setStrs, setStrs.begin()));
	
CWaitCursor wait;
WEnumObjProps IEnum;
HRESULT hr = pIProps -> EnumObjectProps (IEnum.ppi());

	if (FAILED(hr)) return hr;

// Objekteigenschaften durchgehen
WObjectProperty IProp;
char cbPropInfo[_MAX_PATH];
HTREEITEM hToSelect = NULL;
CItemMap mapItems;

	m_fShowLimitWarning = true;
	for (IEnum -> Reset(); S_OK == IEnum -> Next (1, IProp.ppu(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
	DWORD dwFlags = 0L;

		hr = IProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);
		if (FAILED(hr) || !m_pFcn(dwFlags))
			continue;		// nur gewünschte ObjProps anzeigen

	// ParentItem der Property aus dem Baum besorgen
	CPropertyName PropName (cbPropInfo);
	HTREEITEM hParent = CalcParentItem (mapItems, PropName.GetGroup().c_str());
	os_string rstr (PropName.GetSubGroup());
	HTREEITEM hNewItem = NULL;

		if (0 != rstr.length()) {
		HTREEITEM hSubGroup = CalcSubGroupItem (hParent, rstr.c_str());

			if (NULL != hSubGroup)
				hNewItem = InsertItem (PropName.GetName().c_str(), hSubGroup, TVI_LAST);
			else 
				hNewItem = InsertItem (PropName.GetName().c_str(), hParent, TVI_LAST);
		} else 
			hNewItem = InsertItem (PropName.GetName().c_str(), hParent, TVI_LAST);

	// nachsehen, ob dieses Item vorinitialisiert werden soll
	os_string strFull;

		PropName.GetFullName(strFull);
#if defined(_USE_CHECKMARK_OBJPROPTREE)
		if (PropName.hasSubGroup()) {
		string strName (PropName.GetSubGroup() + '\\' + PropName.GetName());

			if (SetContainsString(setStrs, strName) || SetContainsString(setStrs, strFull)) {
				hToSelect = hNewItem;
				if (UseCheckMarks()) 
					SetCheckStateEx(hToSelect, TV_CHECK_ON);
			} else if (UseCheckMarks())
				SetCheckStateEx(hNewItem, TV_CHECK_OFF);
		} 
		else if (SetContainsString(setStrs, PropName.GetName()) || SetContainsString(setStrs, strFull)) {
			hToSelect = hNewItem;
			if (UseCheckMarks()) 
				SetCheckStateEx(hToSelect, TV_CHECK_ON);
		} else if (UseCheckMarks())
			SetCheckStateEx(hNewItem, TV_CHECK_OFF);
#else
		if (PropName.hasSubGroup()) {
		string strName (PropName.GetSubGroup() + '\\' + PropName.GetName());

			if (SetContainsString(setStrs, strName) || SetContainsString(setStrs, strFull)) 
				hToSelect = hNewItem;
		} 
		else if (SetContainsString(setStrs, PropName.GetName()) || SetContainsString(setStrs, strFull)) 
			hToSelect = hNewItem;
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

	// Images setzen
	int iIndex = GetImageIndex (dwFlags);

		SetItemImage (hNewItem, iIndex, iIndex);

	// Objekteigenschaft ans jeweilige Item hängen
	WObjectProperty ObjProp (IProp);

		SetItemData (hNewItem, reinterpret_cast<UINT_PTR>(ObjProp.detach()));		// AddRef übernehmen, wird in OnItemDeleted freigegeben
	}

	if (NULL != hToSelect) {
		SelectSetFirstVisible (hToSelect);
		SelectItem (hToSelect);
		m_fHasSelectedItem = true;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// wiederfinden einer bestimmten Objekteigenschaft
/*static*/
HRESULT CObjPropTree::GetObjectProp (
	LPCSTR pcObjPropName, IObjectProps *pIProps, IObjectProperty **ppIObjProp)
{
WEnumObjProps IEnum;
HRESULT hr = pIProps -> EnumObjectProps (IEnum.ppi());

	if (FAILED(hr)) return hr;

// Objekteigenschaften durchgehen
WObjectProperty IProp;
char cbPropInfo[_MAX_PATH];

	for (IEnum -> Reset(); S_OK == IEnum -> Next (1, IProp.ppu(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
	DWORD dwFlags = 0L;

		if (FAILED(IProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags)))
			continue;

	CPropertyName PropName (cbPropInfo);
	os_string strFull;

		PropName.GetFullName(strFull);
		if (PropName.GetName() == pcObjPropName || strFull == pcObjPropName) {
			*ppIObjProp = IProp.detach();
			return S_OK;
		}
	}
	return E_FAIL;		// nicht wiedergefunden
}

#if defined(_USE_CHECKMARK_OBJPROPTREE)
bool CObjPropTree::ToggleCheckMark (HTREEITEM hItem)
{
	if (!UseCheckMarks() || NULL == hItem)
		return false;

bool fWasOn = false;
UINT uiCurrState = GetCheckState(hItem);
UINT uiState = TV_CHECK_NOMARK;

	switch (uiCurrState) {
	case TV_CHECK_OFF:
		uiState = TV_CHECK_ON;
		m_fShowLimitWarning = true;
		break;

	case TV_CHECK_ON:
		uiState = TV_CHECK_OFF;
		fWasOn = true;
		break;

	case TV_CHECK_PARTIAL_ON:
		if (UsePartialCheckMarks()) {
			uiState = TV_CHECK_ON;
			fWasOn = true;
		}
		break;

	case TV_CHECK_PASSIVE:
	case TV_CHECK_NOMARK:
		break;

	default:
		_ASSERTE(FALSE);
		break;
	}
	
	SetCheckStateEx(hItem, uiState);
	return fWasOn;
}
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

///////////////////////////////////////////////////////////////////////////////
// Finden des ParentItems im Control, ansonsten TVI_ROOT liefern 
HTREEITEM CObjPropTree::CalcParentItem (CItemMap &rItems, LPCSTR pcGroup)
{
HTREEITEM hItem;
os_string strGroup (pcGroup);
CItemMap::const_iterator it = rItems.find (strGroup);

	if (it == rItems.end()) {
	// erstes mal
		hItem = InsertItem (pcGroup, TVI_ROOT, TVI_LAST);
		SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);

		rItems.insert (make_pair(strGroup, hItem));

#if defined(_USE_CHECKMARK_OBJPROPTREE)
		if (UseCheckMarks()) {
			if (UsePartialCheckMarks()) 
				SetCheckStateEx(hItem, TV_CHECK_OFF);
			else
				HideStateImage(hItem);
		}
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

	} else
		hItem = (*it).second;

	return hItem;
}

// Finden bzw. hinzufügen eines GruppenItems zu einem Parent
HTREEITEM CObjPropTree::CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup)
{
HTREEITEM hChild = GetChildItem (hParent);

	while (NULL != hChild) {
	CString str = GetItemText(hChild);

		if (str == pcSubGroup) 
			return hChild;		// SubGroup gibt es schon

		hChild = GetNextItem (hChild, TVGN_NEXT);
	}

// nichts gefunden, also neue SubGroup einfügen
HTREEITEM hNewItem = InsertItem (pcSubGroup, hParent, TVI_LAST);
	
	if (NULL != hNewItem)
		SetItemImage (hNewItem, IMG_FOLDER, IMG_FOLDER);

	return hNewItem;
}

///////////////////////////////////////////////////////////////////////////////
// 
#if defined(_USE_CHECKMARK_OBJPROPTREE)
void CObjPropTree::SetCheckStateEx (HTREEITEM hItem, UINT uiState, 
	bool fPropagateUp, bool fPropagateDown)
{
	if (!UseCheckMarks())
		return;

// ggf. Limit sicherstellen
	if (TV_CHECK_ON == uiState && 
		-1 != m_lLimitCnt && CountSelectedItems() >= m_lLimitCnt)
	{
		if (m_fShowLimitWarning) {
		// Limit ist erreicht, Meldung ausgeben und nichts tun
			AFX_MANAGE_STATE(AfxGetAppModuleState());

		CString strLimitText;
		CString strCaption;

			strLimitText.Format(IDS_LIMITTEXT, m_lLimitCnt);
			_ASSERTE(!strLimitText.IsEmpty());
			VERIFY(strCaption.LoadString(IDS_LONGCLASSNAME));
			::MessageBox(GetSafeHwnd(), strLimitText, strCaption, MB_OK);
			m_fShowLimitWarning = false;
		}
		return;
	}

// jetzt wirklich bearbeiten
	SetCheckState(hItem, uiState);

// ggf. die Änderung nach oben/unten propagieren
	if (UsePartialCheckMarks()) {
	HTREEITEM hParent = GetParentItem(hItem);

		if (fPropagateUp && (TVI_ROOT != hParent && NULL != hParent)) {
		UINT uiOldState = GetCheckState(hParent);
		UINT uiNewState = CalcParentCheckState(hParent);

			if (uiOldState != uiNewState)
				SetCheckStateEx(hParent, uiNewState, true, false);	// eine Etage hoch, aber nicht wieder runter
		}

	// wenns eindeutig ist, dann alle drunter liegenden auch umschalten
		if (fPropagateDown && (TV_CHECK_ON == uiState || TV_CHECK_OFF == uiState)) {
		HTREEITEM hChildItem = NULL;

			if (TVI_ROOT == hItem)
				hChildItem = GetNextItem (NULL, TVGN_CHILD);
			else 
				hChildItem = GetChildItem (hItem);
		
			while (NULL != hChildItem) {
				SetCheckStateEx (hChildItem, uiState, false, true);	// nicht wieder nach oben propagieren
				hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
			}
		}
	}
}

UINT CObjPropTree::CalcParentCheckState (HTREEITEM hItem)
{
	_ASSERTE(UsePartialCheckMarks());

UINT uiCurrState = GetCheckState(hItem);

	if (TV_CHECK_NOMARK == uiCurrState || TV_CHECK_PASSIVE == uiCurrState)
		return uiCurrState;		// hat nichts anzuhaken

// jetzt alle Childs durchgehen, um unseren CheckState zu berechnen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else 
		hChildItem = GetChildItem (hItem);

UINT uiMinState = TV_CHECK_ON;
UINT uiMaxState = TV_CHECK_NOMARK;

	while (NULL != hChildItem) {
	UINT uiState = GetCheckState(hChildItem);
	
		switch (uiState) {
		case TV_CHECK_NOMARK:
		case TV_CHECK_PASSIVE:
			break;	// do not bother

		case TV_CHECK_OFF:
			if (TV_CHECK_ON != uiMaxState && TV_CHECK_PARTIAL_ON != uiMaxState)
				uiMaxState = uiState;
			uiMinState = uiState;
			break;

		case TV_CHECK_PARTIAL_ON:
			if (TV_CHECK_ON != uiMaxState)
				uiMaxState = uiState;
			if (TV_CHECK_OFF != uiMinState)
				uiMinState = uiState;
			break;

		case TV_CHECK_ON:
			uiMaxState = uiState;
			if (TV_CHECK_OFF != uiMinState && TV_CHECK_PARTIAL_ON != uiMinState)
				uiMinState = uiState;
			break;

		default:
			_ASSERTE(FALSE);
			break;
		}
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return (uiMinState == uiMaxState) ? uiMinState : TV_CHECK_PARTIAL_ON;
}

void CObjPropTree::HandleCheckMark(CPoint point, UINT uiMsg)
{
TV_HITTESTINFO ht;

	ht.pt.x = point.x;
	ht.pt.y = point.y;

HTREEITEM hNewTarget = HitTest (&ht);

	if (hNewTarget && (ht.flags & TVHT_ONITEMSTATEICON)) {
	UINT uiState = ChangingCheckState (hNewTarget, uiMsg);

		if (TV_CHECK_NOCHANGE != uiState) {
			if (TV_CHECK_NOMARK != uiState)
				SetCheckState (hNewTarget, uiState);
			else
				ToggleCheckMark (hNewTarget);
			NotifyChecked (hNewTarget, uiMsg, GetCheckState(hNewTarget));
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Notifikationen verschicken
void CObjPropTree::NotifyChecked (HTREEITEM hNewTarget, UINT uiMsg, UINT uiCheckState)
{
NM_TREEVIEWCHECK nmCheck;

	nmCheck.hdr.hwndFrom = GetSafeHwnd();
	nmCheck.hdr.idFrom = GetDlgCtrlID();
	nmCheck.hdr.code = TVN_CHECKSTATECHANGED;
	nmCheck.hItem = hNewTarget;
	nmCheck.action = uiMsg;
	nmCheck.state = uiCheckState;
	GetParent()->SendMessage(WM_NOTIFY, nmCheck.hdr.idFrom, (LPARAM)&nmCheck);
}

UINT CObjPropTree::ChangingCheckState (HTREEITEM hNewTarget, UINT uiMsg)
{
NM_TREEVIEWCHECK nmCheck;

	nmCheck.hdr.hwndFrom = GetSafeHwnd();
	nmCheck.hdr.idFrom = GetDlgCtrlID();
	nmCheck.hdr.code = TVN_CHANGINGCHECKSTATE;
	nmCheck.hItem = hNewTarget;
	nmCheck.action = uiMsg;
	nmCheck.state = TV_CHECK_NOMARK;
	GetParent()->SendMessage(WM_NOTIFY, nmCheck.hdr.idFrom, (LPARAM)&nmCheck);

	return nmCheck.state;
}

#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

///////////////////////////////////////////////////////////////////////////////
// Resultate abfragen
HRESULT CObjPropTree::GetSelectedObjProp (CString &rStrSelected, CString *pStrFull)
{
// neues Item besorgen (vollständigen ObjPropName)
HTREEITEM hItem;

	hItem = GetSelectedItem();
	if (NULL == hItem) {
		_ASSERTE(NULL == hItem);
		return E_UNEXPECTED;
	}

// wenn ein hChild da ist, dann einfach weitermachen
HTREEITEM hChild = GetChildItem (hItem);

	if (NULL != hChild) return S_FALSE;

// gültiges Item
HTREEITEM hParent = GetParentItem (hItem);

	if (NULL == hParent) {
		_ASSERTE(NULL == hItem);
		return E_UNEXPECTED;
	}
	return GetObjPropName (hItem, rStrSelected, pStrFull);
}

HRESULT CObjPropTree::GetObjPropName(HTREEITEM hItem, CString &rStrSelected, CString *pStrFull)
{
int iLoop = 0;
CString str ("");
CString strSubGroup ("");
CString strItem = GetItemText (hItem);

	do {
	CString strT = GetItemText (hItem);

		strSubGroup = str;
		if (iLoop > 0)
			str = strT + '\\' + str;
		else
			str = strT;

		hItem = GetParentItem (hItem);
		iLoop++;

	} while (NULL != hItem);
	
	if (NULL != pStrFull) {
	CString strT ("OBJPROP_ROOT\\");

		strT += str;
		*pStrFull = strT;
	}
	if (iLoop > 2)	// mit subgroup ?
		rStrSelected = strSubGroup;
	else
		rStrSelected = strItem;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// liefert alle angehakten Items
#if defined(_USE_CHECKMARK_OBJPROPTREE)
HRESULT CObjPropTree::GetSelectedObjProps (list<os_string> &rlstObjProps, HTREEITEM hItem)
{
	if (NULL == hItem) 
		return S_OK;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
		if (TV_CHECK_ON == GetCheckState(hItem)) {
		CString strFull, strName;

			if (SUCCEEDED(GetObjPropName(hItem, strName, &strFull))) 
				rlstObjProps.push_back (os_string(strFull));
		}
		hChildItem = GetChildItem (hItem);
	}

// anschließend alle Childs abtesten
	while (NULL != hChildItem) {
	HRESULT hr = GetSelectedObjProps (rlstObjProps, hChildItem);

		if (FAILED(hr)) 
			return hr;
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return S_OK;
}
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

///////////////////////////////////////////////////////////////////////////////
// nachsehen, ob was selektiert wurde
int CObjPropTree::CountSelectedItems (HTREEITEM hItem, int iCnt)
{
#if defined(_USE_CHECKMARK_OBJPROPTREE)
	if (NULL == hItem) 
		return iCnt;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
		if (!ItemHasChildren(hItem) && TV_CHECK_ON == GetCheckState(hItem))
			++iCnt;

		hChildItem = GetChildItem (hItem);
	}

// anschließend alle Childs abtesten
	while (NULL != hChildItem) {
		iCnt = CountSelectedItems (hChildItem, iCnt);
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return iCnt;
#else
	return NULL != GetSelectedItem() ? 1 : 0;
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
}

// Implementation of GetSelectObject
HRESULT CObjPropTree::GetSelectObject(IUnknown **ppIUnk)
{
// neues Item besorgen (vollständigen ObjPropName)
HTREEITEM hItem = GetSelectedItem();

	if (NULL == hItem) {
		_ASSERTE(NULL == hItem);
		return E_UNEXPECTED;
	}

// wenn ein hChild da ist, dann einfach weitermachen
HTREEITEM hChild = GetChildItem (hItem);

	if (NULL != hChild) 
		return S_FALSE;

// gültiges Item
HTREEITEM hParent = GetParentItem (hItem);

	if (NULL == hParent) {
		_ASSERTE(NULL == hItem);
		return E_UNEXPECTED;
	}

WObjectProperty ObjProp (reinterpret_cast<IObjectProperty *>(GetItemData(hItem)));

	if (!ObjProp.IsValid()) {
		_ASSERTE(ObjProp.IsValid());
		return E_UNEXPECTED;
	}
	return ObjProp -> QueryInterface(ppIUnk);
}

///////////////////////////////////////////////////////////////////////////////
// 
BEGIN_MESSAGE_MAP(CObjPropTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CObjPropTree)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjPropTree message handlers

void CObjPropTree::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	AdjustParentImage (pNMTreeView -> itemNew.hItem);
	*pResult = 0;
}

void CObjPropTree::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemOld.hItem;
WObjectProperty ObjProp(reinterpret_cast<IObjectProperty *>(GetItemData(hItem)));

	if (ObjProp.IsValid()) 
		ObjProp -> Release();		// zusätzliche Freigabe
	
	*pResult = 0;
}

void CObjPropTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW *)pNMHDR;

	if ((TVC_BYMOUSE|TVC_BYKEYBOARD) & pNMTreeView -> action) {
	// verhindern, daß erstes Element ggf. bei der Initialisierung gehakt wird
	HTREEITEM hItem = GetSelectedItem();

		if (NULL != hItem) {
#if defined(_USE_CHECKMARK_OBJPROPTREE)
			if (UseCheckMarks()) {
			TV_HITTESTINFO ht;

				GetCursorPos(&ht.pt);
				ScreenToClient(&ht.pt);

			HTREEITEM hNewTarget = HitTest (&ht);

				if ((GetItemState (hItem, TVIS_SELECTED) & TVIS_SELECTED) &&
					(hItem == hNewTarget) && !(ht.flags & TVHT_ONITEMSTATEICON))
				{
					m_fShowLimitWarning = true;
					SetCheckStateEx(hItem, TV_CHECK_ON);
				}
			}
			else
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
			{
				if (!ItemHasChildren(hItem)) 	// childnode fertig selektiert
					m_fHasSelectedItem = true;
			}
		}
	}
	*pResult = 0;
}

void CObjPropTree::OnLButtonDown(UINT nFlags, CPoint point) 
{
#if defined(_USE_CHECKMARK_OBJPROPTREE)
	if (UseCheckMarks())
		HandleCheckMark(point, WM_LBUTTONDOWN);
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CObjPropTree::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
#if defined(_USE_CHECKMARK_OBJPROPTREE)
	if (UseCheckMarks())
		HandleCheckMark(point, WM_LBUTTONDOWN);
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}
