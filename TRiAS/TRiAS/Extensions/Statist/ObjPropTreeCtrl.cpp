// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.01.2001 11:36:00 
//
// @doc
// @module ObjPropTreeCtrl.cpp | Definition of the <c CObjPropTreeCtrl> class

#include "StdAfx.h"

#include <ospace/std/set>
#include <PropNamex.h>

#include "Statist.h"
#include "ObjPropTreeCtrl.h"

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
inline bool SetContainsString (set<os_string> &rSet, os_string &rStr)
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

BOOL CObjPropTreeCtrl::Init(IObjectProps *pIProps, list<os_string> &rStrs)
{
#if !defined(_USE_CHECKMARK_OBJPROPTREE)
// derzeit ohne Checkmarks, also nur max. eine Voreinstellung
	_ASSERTE(1 >= rStrs.size());
#endif // !defined(_USE_CHECKMARK_OBJPROPTREE)

// ImageListen initialisieren
CImageList imgList;

	imgList.Create(IDB_OBJPROPTYPES, 16, 16, RGB(255, 0, 255));
	_ASSERTE(!imgList.IsNull());

	SetImageList(imgList, TVSIL_NORMAL);

#if defined(_USE_CHECKMARK_OBJPROPTREE)
	if (UseCheckMarks()) {
	CImageList imgListCk;

		imgListCk.Create(IDB_CHECKMARKS, 15, 0, RGB(255, 255, 255));
		_ASSERTE(!imgListCk.IsNull());

		SetImageList(imgListCk, TVSIL_STATE);
	}
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

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
HRESULT CObjPropTreeCtrl::GetObjectProp (
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
bool CObjPropTreeCtrl::ToggleCheckMark (HTREEITEM hItem)
{
	if (!UseCheckMarks() || NULL == hItem)
		return false;

bool fWasOn = false;
UINT uiCurrState = GetCheckState(hItem);
UINT uiState = TV_CHECK_NOMARK;

	switch (uiCurrState) {
	case TV_CHECK_OFF:
		uiState = TV_CHECK_ON;
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
HTREEITEM CObjPropTreeCtrl::CalcParentItem (CItemMap &rItems, LPCSTR pcGroup)
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
HTREEITEM CObjPropTreeCtrl::CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup)
{
HTREEITEM hChild = GetChildItem (hParent);

	while (NULL != hChild) {
	CString str;

		if (GetItemText (hChild, str) && str == pcSubGroup) 
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
void CObjPropTreeCtrl::SetCheckStateEx (HTREEITEM hItem, UINT uiState, bool fPropagateUp, bool fPropagateDown)
{
	if (!UseCheckMarks())
		return;

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

UINT CObjPropTreeCtrl::CalcParentCheckState (HTREEITEM hItem)
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
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

///////////////////////////////////////////////////////////////////////////////
// Resultate abfragen
HRESULT CObjPropTreeCtrl::GetSelectedObjProp (CString &rStrSelected, CString *pStrFull)
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

HRESULT CObjPropTreeCtrl::GetObjPropName(HTREEITEM hItem, CString &rStrSelected, CString *pStrFull)
{
int iLoop = 0;
CString str ("");
CString strSubGroup ("");
CString strItem;

	GetItemText (hItem, strItem);
	do {
	CString strT;

		GetItemText (hItem, strT);
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
HRESULT CObjPropTreeCtrl::GetSelectedObjProps (list<os_string> &rlstObjProps, HTREEITEM hItem)
{
	if (NULL == hItem) 
		return S_OK;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
		if (TV_CHECK_ON == GetCheckState(hItem)) {
		os_string strFull, strName;

			if (SUCCEEDED(GetObjPropName(hItem, strName, &strFull))) 
				rlstObjProps.push_back (strFull);
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
int CObjPropTreeCtrl::CountSelectedItems (HTREEITEM hItem, int iCnt)
{
#if defined(_USE_CHECKMARK_OBJPROPTREE)
	if (NULL == hItem) 
		return iCnt;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
		if (TV_CHECK_ON == GetCheckState(hItem))
			++iCnt;

		hChildItem = GetChildItem (hItem);
	}

// anschließen alle Childs abtesten
	while (NULL != hChildItem) {
		iCnt = CountSelectedItems (hChildItem, iCnt);
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return iCnt;
#else
	return NULL != GetSelectedItem() ? 1 : 0;
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
}

///////////////////////////////////////////////////////////////////////////////
// MessageReflection
LRESULT CObjPropTreeCtrl::OnItemExpanded (NMHDR *pNmHdr)
{
	AdjustParentImage (((NM_TREEVIEW *)pNmHdr) -> itemNew.hItem);
	return TRUE;
}

// Item wurde gelöscht, ggf. IObjectProperty freigeben
LRESULT CObjPropTreeCtrl::OnItemDeleted(NMHDR *pNmHdr)
{
HTREEITEM hItem = reinterpret_cast<NM_TREEVIEW  *>(pNmHdr) -> itemOld.hItem;
WObjectProperty ObjProp(reinterpret_cast<IObjectProperty *>(GetItemData(hItem)));

	if (ObjProp.IsValid()) 
		ObjProp -> Release();		// zusätzliche Freigabe
	return TRUE;
}

LRESULT CObjPropTreeCtrl::OnSelChanged (NMHDR *pNmHdr)
{
	if ((TVC_BYMOUSE|TVC_BYKEYBOARD) & ((NM_TREEVIEW *)pNmHdr) -> action) {
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
	return TRUE;
}

void CObjPropTreeCtrl::OnKillFocus(HWND hWnd)
{
	if (!m_fHasSelectedItem)
		::PostMessage(GetParent(), WM_CANCELDIALOG, 0, 0);
	SetMsgHandled(FALSE);
}

void CObjPropTreeCtrl::OnLButtonDown (UINT uiFlags, CPoint ptPos)
{
CRect rc;

	GetWindowRect (&rc);
	ClientToScreen (&ptPos);
	m_fHasSelectedItem = false;
	if (!rc.PtInRect(ptPos)) 
		::PostMessage(GetParent(), WM_CANCELDIALOG, 0, 0);		// daneben geklickt

	SetMsgHandled(FALSE);
}

void CObjPropTreeCtrl::OnLButtonUp (UINT uiFlags, CPoint ptPos)
{
	if (m_fHasSelectedItem) {
	CRect rc;

		GetWindowRect (&rc);
		ClientToScreen (&ptPos);
		if (rc.PtInRect(ptPos)) 
			::PostMessage(GetParent(), WM_ITEMSELECTED, 0, 0);
	}
	SetMsgHandled(FALSE);
}

// Implementation of GetSelectObject
HRESULT CObjPropTreeCtrl::GetSelectObject(IUnknown **ppIUnk)
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
