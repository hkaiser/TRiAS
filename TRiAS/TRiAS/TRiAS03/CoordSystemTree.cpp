// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.10.2002 21:06:08 
//
// @doc
// @module CoordSystemTree.cpp | Definition of the <c CCoordSystemTree> class

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/PropertyHelper.h>
#include <Com/ComBool.h>

#include "CoordSystemTree.h"
#include "SelectCoordSysActionDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree

CCoordSystemTree::CCoordSystemTree(pDialogWindow parent, ResID id) 
:	CTreeViewCtrl(parent, id),
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

os_string strFullKey (pcFullKey);

	strFullKey += TEXT("\\");
	strFullKey += pcKey;

HTREEITEM hItemParent = InsertItem (cbBuffer, IMG_COORDFOLDER, IMG_COORDFOLDER, hParent);
DWORD i = 0;
char cbEnumKey[_MAX_PATH];
CRegistry regEntries (rCurr, KEY_READ, pcKey);
DWORD dwPos = 0;
bool fNotEmpty = false;

	if (!regEntries.GetDWORD (TEXT("Toolbar32"), dwPos)) {
	// Zwischen‹berschrift, weiter in die Rekursion
		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			if (InitCoordSystem (regEntries, hItemParent, strFullKey.c_str(), cbEnumKey))
				fNotEmpty = true;
			i++;
		}
	} 
	else {
	// eigentliche Koordinatensysteme
		_ASSERTE(0 <= dwPos && dwPos <= (DWORD)(m_ilImages.GetImageCount()-1));

		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			if(InitCoordSystemEntry (regEntries, hItemParent, strFullKey.c_str(), cbEnumKey, dwPos))
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
ResourceFile RF (g_pDLLName);

	m_pPage = pPage;
	if (m_ilImages.CreateList (ResID(IDB_COORDSYSTEM, &RF), 16, 16, RGB(255,0,255))) 
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

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree message handlers

void CCoordSystemTree::OnDeleteCoordSystemItem(NMHDR* pNMHDR) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
CCoordSystemItem *pOldItem = (CCoordSystemItem *)pNMTreeView -> itemOld.lParam;

	if (NULL != pOldItem)
		delete pOldItem;
}

void CCoordSystemTree::OnSelchanged(NMHDR* pNMHDR) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	_ASSERTE(NULL != hItem);

	if (pNMTreeView -> itemNew.state & TVIS_SELECTED) {
		_ASSERTE(NULL != m_pPage);
		m_pPage -> SetDescription (hItem);
	}

	AdjustImage (hItem);
}

void CCoordSystemTree::OnItemExpanded(NMHDR* pNMHDR) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	_ASSERTE(NULL != hItem);
	AdjustImage (hItem);
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
	m_strRegKey += TEXT("\\");
	m_strRegKey += pcSubKey;

CCurrentUser regKey (KEY_READ, pcRegKey);
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (regKey.GetSZ (pcSubKey, cbBuffer, lLen))
		m_strFullDesc = cbBuffer;

CCurrentUser regTcf (KEY_READ, m_strRegKey.c_str());

	lLen = sizeof(cbBuffer);
	if (regTcf.GetSubSZ ("CoordTcfName", cbBuffer, (ULONG &)lLen))
		m_strTcfName = cbBuffer;
}

HRESULT CCoordSystemItem::GetTRiASCS (ITRiASCS **ppICS)
{
	if (NULL == ppICS)
		return E_POINTER;
	*ppICS = NULL;

	if (0 == m_strTcfName.size())
		return E_INVALIDARG;

	COM_TRY {
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> CS;

		THROW_FAILED_HRESULT(CS.CoCreateInstance(CLSID_TRIASCS));
		THROW_FAILED_HRESULT(CS -> LoadFromFile(CComBSTR(m_strTcfName.c_str())));
		*ppICS = CS.Detach();

	} COM_CATCH;
	return S_OK;
}

