// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.10.2002 21:06:08 
//
// @doc
// @module CoordSystemTree.cpp | Definition of the <c CCoordSystemTree> class

#include "stdafx.h"
#include "resource.h"

#pragma warning (disable: 4192)
#import "Tlb/TRiASDB.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids 

#include <Com/PropertyHelper.h>
#include <Com/ComBool.h>

#include "CoordSystemTree.h"
#include "SelectCoordSysActionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree

CCoordSystemTree::CCoordSystemTree() :
	m_hSelItem(NULL)
{
}

CCoordSystemTree::~CCoordSystemTree()
{
}

/////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
const TCHAR g_cbCoordSystems[] = 
	TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\CoordinateSystems");

bool CCoordSystemTree::InitCoordSystemsFromRegistry (void)
{
CCurrentUser regCoords (KEY_READ, g_cbCoordSystems);

	if (!regCoords.isValid()) 
		return false;

DWORD i = 0;
char cbEnumKey[_MAX_PATH];
bool fNotEmpty = false;

	while (RegEnumKey (regCoords, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
		if (InitCoordSystem (regCoords, TVI_ROOT, g_cbCoordSystems, cbEnumKey))
			fNotEmpty = true;
		i++;
	}

	if (NULL != m_hSelItem) {
	HTREEITEM hParent = GetParentItem(m_hSelItem);
	HTREEITEM hParentParent = NULL;

		if (NULL != hParent) 
			hParentParent = GetParentItem(hParent);

		if (NULL != hParentParent)
			SelectSetFirstVisible(hParentParent);
		else if (NULL != hParent)
			SelectSetFirstVisible(hParent);
		else
			SelectSetFirstVisible(m_hSelItem);

		SelectItem(m_hSelItem);
	}
	return fNotEmpty;
}

bool CCoordSystemTree::InitCoordSystem (CRegistry &rCurr, HTREEITEM hParent, 
	LPCSTR pcFullKey, LPCSTR pcKey)
{
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (!rCurr.GetSZ (pcKey, cbBuffer, lLen))		// Beschreibung der Klasse lesen
		return false;

CString strFullKey (pcFullKey);

	strFullKey += _T("\\");
	strFullKey += pcKey;

HTREEITEM hItemParent = InsertItem (cbBuffer, IMG_COORDFOLDER, IMG_COORDFOLDER, hParent);
DWORD i = 0;
char cbEnumKey[_MAX_PATH];
CRegistry regEntries (rCurr, KEY_READ, pcKey);
DWORD dwPos = 0;
bool fNotEmpty = false;

	if (!regEntries.GetDWORD (_T("Toolbar32"), dwPos)) {
	// Zwischen‹berschrift, weiter in die Rekursion
		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			if (InitCoordSystem (regEntries, hItemParent, strFullKey, cbEnumKey))
				fNotEmpty = true;
			i++;
		}
	} 
	else {
	// eigentliche Koordinatensysteme
		ASSERT(0 <= dwPos && dwPos <= (DWORD)(m_ilImages.GetImageCount()-1));

		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			if(InitCoordSystemEntry (regEntries, hItemParent, strFullKey, cbEnumKey, dwPos))
				fNotEmpty = true;
			i++;
		}
	}
	if (!fNotEmpty)
		DeleteItem (hItemParent);
	return fNotEmpty;
}

bool CCoordSystemTree::InitCoordSystemEntry (CRegistry &rCurr, HTREEITEM hParent, 
	LPCSTR pcFullKey, LPCSTR pcSubKey, DWORD dwPos)
{
HTREEITEM hItem = InsertItem (pcSubKey, dwPos, dwPos, hParent);

	if (NULL != hItem) {
	CCoordSystemItem *pNewItem = NULL;
	
		ATLTRY(pNewItem = new CCoordSystemItem (pcFullKey, pcSubKey));
		if (!SetItemData (hItem, (DWORD)pNewItem)) {
			TRACE0("Could not set item data\n");
			delete pNewItem;
			return false;
		}

		if (NULL != m_ProjCS.p && NULL == m_hSelItem) {	
		CComQIPtr<ITRiASCS, &IID_ITRiASCS> CS;

			if (SUCCEEDED(pNewItem->GetTRiASCS(&CS))) {
			CComBool fIsEqual;

				if (SUCCEEDED(m_ProjCS -> IsEqual(CS, &fIsEqual))) {
					if (fIsEqual)
						m_hSelItem = hItem;
				}
			}
		}
		return true;
	}
	return false;
}

HRESULT CCoordSystemTree::InitTreeCrtl (CSelectCoordSysActionDlg *pPage)
{
	m_pPage = pPage;
	if (!m_ilImages.Create (IDB_COORDSYSTEM, 16, 16, RGB(255,0,255))) {
		TRACE0("Could not create imagelist for CoordsystemTree\r\n");
	} else 
		SetImageList(&m_ilImages, TVSIL_NORMAL);

CComQIPtr<ITRiASProject, &IID_ITRiASProject> Proj;

	if (DEX_GetActiveProjectPtr(Proj)) {
	IDispatch *pIProjCS = GetPropertyFrom(Proj, L"TRiASCSService", (IDispatch *)NULL);

		if (NULL != pIProjCS) {
			m_ProjCS = pIProjCS;
			pIProjCS -> Release();		// GetProperty liefert mit AddRef ab
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
BEGIN_MESSAGE_MAP(CCoordSystemTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CCoordSystemTree)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteCoordSystemItem)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree message handlers

void CCoordSystemTree::OnDeleteCoordSystemItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
CCoordSystemItem *pOldItem = (CCoordSystemItem *)pNMTreeView -> itemOld.lParam;

	if (NULL != pOldItem)
		delete pOldItem;
	
	*pResult = 0;
}

void CCoordSystemTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	ASSERT(NULL != hItem);

	if (pNMTreeView -> itemNew.state & TVIS_SELECTED) {
		ASSERT(NULL != m_pPage);
		m_pPage -> SetDescription (hItem);
	}

	AdjustImage (hItem);
}

void CCoordSystemTree::OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	ASSERT(NULL != hItem);
	AdjustImage (hItem);
	*pResult = 0;
}

void CCoordSystemTree::AdjustImage (HTREEITEM hItem)
{
	if (!ItemHasChildren (hItem)) 
		return;		// nur Parents behandeln

	if (GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		SetItemImage (hItem, IMG_COORDOPENFOLDER, IMG_COORDOPENFOLDER);	// ist expandiert
	else
		SetItemImage (hItem, IMG_COORDFOLDER, IMG_COORDFOLDER);			// ist collabiert
}

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree h‰ngt

CCoordSystemItem::CCoordSystemItem (LPCSTR pcRegKey, LPCSTR pcSubKey)
{
	m_strRegKey = pcRegKey;
	m_strRegKey += _T("\\");
	m_strRegKey += pcSubKey;

CCurrentUser regKey (KEY_READ, pcRegKey);
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (regKey.GetSZ (pcSubKey, cbBuffer, lLen))
		m_strFullDesc = cbBuffer;

CCurrentUser regTcf (KEY_READ, m_strRegKey);

	lLen = sizeof(cbBuffer);
	if (regTcf.GetSubSZ ("CoordTcfName", cbBuffer, (ULONG &)lLen))
		m_strTcfName = cbBuffer;
}

HRESULT CCoordSystemItem::GetTRiASCS (ITRiASCS **ppICS)
{
	if (NULL == ppICS)
		return E_POINTER;
	*ppICS = NULL;

	if (0 == m_strTcfName.GetLength())
		return E_INVALIDARG;

	COM_TRY {
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> CS;

		THROW_FAILED_HRESULT(CS.CoCreateInstance(CLSID_TRIASCS));
		THROW_FAILED_HRESULT(CS -> LoadFromFile(CComBSTR(m_strTcfName)));
		*ppICS = CS.Detach();

	} COM_CATCH;
	return S_OK;
}

