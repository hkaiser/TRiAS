// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.01.2001 09:55:30 
//
// @doc
// @module StatFuncTreeCtrl.cpp | Definition of the <c CStatFuncTreeCtrl> class

#include "StdAfx.h"

#include <ospace/std/set>
#include <PropNamex.h>

#include "Statist.h"
#include "StatFuncTreeCtrl.h"
#include "StatFuncName.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// gecachete GUIDs der StatValues
CStatFuncTreeCtrl::CEnumGuids CStatFuncTreeCtrl::s_StatValueGUIDs;

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
BOOL CStatFuncTreeCtrl::Init(LPCSTR pcSelected)
{
	USES_CONVERSION;

// ImageListen initialisieren
CImageList imgList;

	imgList.Create(IDB_STATFUNCS, 16, 16, RGB(255, 0, 255));
	_ASSERTE(!imgList.IsNull());

	SetImageList(imgList, TVSIL_NORMAL);

CWaitCursor wait;
HTREEITEM hToSelect = NULL;
GUID guid;
CItemMap mapItems;

	s_StatValueGUIDs.InitGuids(CATID_TRiASStatistValue);		// sicher initialisieren
	for (s_StatValueGUIDs.Reset(); S_OK == s_StatValueGUIDs.Next (1, &guid, NULL); /**/)
	{
	WGenericStatistics StatValue;
	HRESULT hr = StatValue.CreateInstance(guid);

		if (FAILED(hr)) {
			if (CLASS_E_NOTLICENSED == hr)
				s_StatValueGUIDs.RemoveActiveItem();
			continue;	// registriert, aber nicht instantiierbar (nicht lizensiert o.ä.)
		}

	// zum Baum hinzufügen
	CComBSTR bstrName;

		if (FAILED(StatValue -> get_Name(&bstrName))) {
			_ASSERTE(SUCCEEDED(E_UNEXPECTED));
			continue;	// Fehler!
		}

	CStatFuncName FuncName (OLE2A(bstrName));
	HTREEITEM hParent = CalcParentItem (mapItems, FuncName.GetGroup().c_str());
	os_string rstr (FuncName.GetSubGroup());
	HTREEITEM hNewItem = NULL;

		if (0 != rstr.length()) {
		HTREEITEM hSubGroup = CalcSubGroupItem (hParent, rstr.c_str());

			if (NULL != hSubGroup)
				hNewItem = InsertItem (FuncName.GetName().c_str(), hSubGroup, TVI_LAST);
			else 
				hNewItem = InsertItem (FuncName.GetName().c_str(), hParent, TVI_LAST);
		} else 
			hNewItem = InsertItem (FuncName.GetName().c_str(), hParent, TVI_LAST);

	// nachsehen, ob dieses Item vorinitialisiert werden soll
	os_string strFull;

		FuncName.GetFullName(strFull);
		if (FuncName.GetName() == pcSelected || strFull == pcSelected)
			hToSelect = hNewItem;

	// Images setzen
		SetItemImage (hNewItem, IMG_STATFUNC, IMG_STATFUNC);

	// StatFunc ans jeweilige Item hängen
	WGenericStatistics StatFunc(StatValue);

		SetItemData (hNewItem, reinterpret_cast<UINT_PTR>(StatFunc.detach()));		// AddRef übernehmen, wird in OnItemDeleted freigegeben
	}

	if (NULL != hToSelect) {
		SelectSetFirstVisible (hToSelect);
		SelectItem (hToSelect);
		m_fHasSelectedItem = true;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// instantiieren einer bestimmten StatFunc
/*static*/
HRESULT CStatFuncTreeCtrl::GetStatFunc (LPCSTR pcStatFunc, IGenericStatistics **ppIStatFunc)
{
GUID guid;

	USES_CONVERSION;
	s_StatValueGUIDs.InitGuids(CATID_TRiASStatistValue);		// sicher initialisieren
	for (s_StatValueGUIDs.Reset(); S_OK == s_StatValueGUIDs.Next (1, &guid, NULL); /**/)
	{
	WGenericStatistics StatValue;
	HRESULT hr = StatValue.CreateInstance(guid);

		if (FAILED(hr)) {
			if (CLASS_E_NOTLICENSED == hr)
				s_StatValueGUIDs.RemoveActiveItem();
			continue;	// registriert, aber nicht instantiierbar (nicht lizensiert o.ä.)
		}

	// versuchen, über den Namen wiederzufinden
	CComBSTR bstrName;

		if (FAILED(StatValue -> get_Name(&bstrName))) {
			_ASSERTE(SUCCEEDED(E_UNEXPECTED));
			continue;	// Fehler!
		}

	CStatFuncName FuncName (OLE2A(bstrName));
	os_string strFull;

		FuncName.GetFullName(strFull);
		if (FuncName.GetName() == pcStatFunc || strFull == pcStatFunc) {
			*ppIStatFunc = StatValue.detach();
			return S_OK;
		}
	}
	return E_FAIL;		// nicht wiedergefunden
}

///////////////////////////////////////////////////////////////////////////////
// Finden des ParentItems im Control, ansonsten TVI_ROOT liefern 
HTREEITEM CStatFuncTreeCtrl::CalcParentItem (CItemMap &rItems, LPCSTR pcGroup)
{
HTREEITEM hItem;
os_string strGroup (pcGroup);
CItemMap::const_iterator it = rItems.find (strGroup);

	if (it == rItems.end()) {
	// erstes mal
		hItem = InsertItem (pcGroup, TVI_ROOT, TVI_LAST);
		SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);

		rItems.insert (make_pair(strGroup, hItem));
	} else
		hItem = (*it).second;

	return hItem;
}

// Finden bzw. hinzufügen eines GruppenItems zu einem Parent
HTREEITEM CStatFuncTreeCtrl::CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup)
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
// Resultate abfragen
HRESULT CStatFuncTreeCtrl::GetSelectedStatFunc (CString &rStrSelected, CString *pStrFull)
{
// neues Item besorgen (vollständigen ObjPropName)
HTREEITEM hItem = GetSelectedItem();

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
	return GetStatFuncName (hItem, rStrSelected, pStrFull);
}

HRESULT CStatFuncTreeCtrl::GetStatFuncName(HTREEITEM hItem, CString &rStrSelected, CString *pStrFull)
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
	CString strT ("STATFUNC_ROOT\\");

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
// nachsehen, ob was selektiert wurde
int CStatFuncTreeCtrl::CountSelectedItems (HTREEITEM hItem, int iCnt)
{
	return NULL != CTreeViewCtrl::GetSelectedItem() ? 1 : 0;
}

///////////////////////////////////////////////////////////////////////////////
// MessageReflection
LRESULT CStatFuncTreeCtrl::OnItemExpanded (NMHDR *pNmHdr)
{
	AdjustParentImage (((NM_TREEVIEW *)pNmHdr) -> itemNew.hItem);
	return TRUE;
}

LRESULT CStatFuncTreeCtrl::OnItemDeleted(NMHDR *pNmHdr)
{
HTREEITEM hItem = reinterpret_cast<NM_TREEVIEW  *>(pNmHdr) -> itemOld.hItem;
WGenericStatistics StatFunc(reinterpret_cast<IGenericStatistics *>(GetItemData(hItem)));

	if (StatFunc.IsValid()) 
		StatFunc -> Release();		// zusätzliche Freigabe
	return TRUE;
}

LRESULT CStatFuncTreeCtrl::OnSelChanged (NMHDR *pNmHdr)
{
	if ((TVC_BYMOUSE|TVC_BYKEYBOARD) & ((NM_TREEVIEW *)pNmHdr) -> action) {
	// verhindern, daß erstes Element ggf. bei der Initialisierung gehakt wird
	HTREEITEM hItem = CTreeViewCtrl::GetSelectedItem();

		if (NULL != hItem && !ItemHasChildren(hItem)) 	// childnode fertig selektiert
			m_fHasSelectedItem = true;
		else
			m_fHasSelectedItem = false;
	}
	return TRUE;
}

void CStatFuncTreeCtrl::OnKillFocus(HWND hWnd)
{
	if (!m_fHasSelectedItem)
		::PostMessage(GetParent(), WM_CANCELDIALOG, 0, 0);
	SetMsgHandled(FALSE);
}

void CStatFuncTreeCtrl::OnLButtonDown (UINT uiFlags, CPoint ptPos)
{
CRect rc;

	GetWindowRect (&rc);
	ClientToScreen (&ptPos);
	if (!rc.PtInRect(ptPos)) {
		::PostMessage(GetParent(), WM_CANCELDIALOG, 0, 0);		// daneben geklickt
		m_fHasSelectedItem = false;
	}
	SetMsgHandled(FALSE);
}

void CStatFuncTreeCtrl::OnLButtonUp (UINT uiFlags, CPoint ptPos)
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

///////////////////////////////////////////////////////////////////////////////
// StatFunc Guids in cache speichern
HRESULT CStatFuncTreeCtrl::
CEnumGuids::InitGuids (REFGUID rGuid, bool fForce)
{
	if (!m_fIsInitialized || fForce) {
		Clear();					// alles bisherige vergessen
		m_fIsInitialized = false;
		
	// neu füllen
		COM_TRY {
		WEnumGUID EnumGuids;		// Enumerator der StatFunc Objekte
		WCatInformation CatInfo (CLSID_CatSimpleCache);	// throws hr
		GUID guid, guidImpl[1]; 

			guidImpl[0] = rGuid;
			THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

		// alle Guids umkopieren
			for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
				THROW_FAILED_HRESULT(AddItem (guid));

		} COM_CATCH;
		m_fIsInitialized = true;
	} 
	return S_OK;
}

// Implementation of GetSelectObject
HRESULT CStatFuncTreeCtrl::GetSelectObject(IUnknown **ppIUnk)
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

WGenericStatistics StatFunc (reinterpret_cast<IGenericStatistics *>(GetItemData(hItem)));

	if (!StatFunc.IsValid()) {
		_ASSERTE(StatFunc.IsValid());
		return E_UNEXPECTED;
	}
	return StatFunc -> QueryInterface(ppIUnk);
}

