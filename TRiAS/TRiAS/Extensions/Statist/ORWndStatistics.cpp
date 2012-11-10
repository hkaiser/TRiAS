// $Header: $
// Copyright© 1999-2004 Harmut Kaiser, All rights reserved
// Created: 16.09.2001 21:34:32 
//
// @doc
// @module ORWndStatistics.cpp | Definition of the <c CORWndStatistics> class

#include "StdAfx.h"

#include <Com/Thunk.h>
#include <triastlb.h>

#include "StatistApp.h"
#include "Statist.h"

#include "TreeListView.h"
#include "ORWndStatistics.h"
#include "ObjectCountInORWndClass.h"
#include "ObjectCountInORWnd.h"
#include "InstallObjectCountInORWndProvider.h"
#include "ObjectCountORWndProviderCallback.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Initialisierung des TreeViewControls mit allem notwendigen
// Implementation of InitTreeView
BOOL CORWndStatistics::InitRoot()
{
// Wurzel ist der Workspace
char cbBuffer[_MAX_PATH];
CString strWrkSpace;

	DEX_GetActiveProject(cbBuffer);
	PathStripPath(cbBuffer);
	*PathFindExtension(cbBuffer) = '\0';

	strWrkSpace.Format(IDS_WORKSPACEROOT_INIT, cbBuffer);

HTREEITEM hItemRoot = InsertItem(strWrkSpace, IMG_WORKSPACE, IMG_WORKSPACE, TVI_ROOT, TVI_LAST);

// alle aktuellen Recherchefenster enumerieren
CStdThunkImpl<CORWndStatistics, ENUMNOKEYLONGPROC> 
	Thunk(this, &CORWndStatistics::EnumORWnds);
ENUMNOKEYLONG ENKL;

    ENKL.eFcn = Thunk.GetThunk();
	ENKL.ePtr = &hItemRoot;

	if (DEX_EnumORWindows(ENKL)) {
	// vollständigen Wurzeltext setzen
	int iCnt = DEX_GetOpenConnectionCount (QDCAllOpen);
	TV_ITEM tvi;

		if (1 == iCnt)
			strWrkSpace.Format(IDS_WORKSPACEROOT_ONE, cbBuffer);
		else
			strWrkSpace.Format(IDS_WORKSPACEROOT, cbBuffer, iCnt);

		tvi.mask = TVIF_HANDLE|TVIF_TEXT;
		tvi.hItem = hItemRoot;
		tvi.pszText = (LPSTR)(LPCSTR)strWrkSpace;
		SetItem(&tvi);
		Expand(hItemRoot);
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Enumeration aller aktuellen Recherchefenster
BOOL CORWndStatistics::EnumORWnds(HWND hWnd, BOOL, UINT_PTR *pData)
{
// Namen des RechercheFensters besorgen
DWORD dwBmp = IMG_STATFUNC_ORWND_NODE;
char cbBuffer[_MAX_PATH];
CWindow Wnd(hWnd);

    Wnd.GetWindowText(cbBuffer, sizeof(cbBuffer));

char *left_paren = strrchr(cbBuffer, '(');

    if (NULL != left_paren)
        *left_paren = '\0';

// Item in Baum einhängen und mit dummy [+] versehen
HTREEITEM hRoot = *reinterpret_cast<HTREEITEM *>(pData);
HTREEITEM hItem = InsertItem(cbBuffer, IMG_STATFUNC_ORWND_NODE, 
    IMG_STATFUNC_ORWND_NODE, hRoot, TVI_LAST);
TV_ITEM tvi;

	tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
	tvi.hItem = hItem;
	tvi.cChildren = 1;
	tvi.lParam = reinterpret_cast<LPARAM>(new CORWndItemCallback(hWnd, hItem));
	SetItem(&tvi);
	return TRUE;
}

// wird für jedes zu öffnende Item gerufen
BOOL CORWndStatistics::PopulateItem(HTREEITEM hParent)
{
	if (TVI_ROOT == hParent) 
		return InitRoot();

// Itemspezifische Funktion rufen
CItemCallback *pItemCB = reinterpret_cast<CItemCallback *>(GetItemData(hParent));

	_ASSERTE(NULL != pItemCB);
	return pItemCB->PopulateItem(this, hParent);
}

// wird für jedes zu löschende Item gerufen
void CORWndStatistics::DeletingItem(HTREEITEM hItem)
{
CItemCallback *pItemCB = reinterpret_cast<CItemCallback *>(GetItemData(hItem));

	DELETE_OBJ(pItemCB);
	SetItemData(hItem, NULL);
}

//////////////////////////////////////////////////////////////////////////////
BOOL CORWndStatistics::
CORWndItemCallback::EnumClasses(HOBJECTS lIdent, BOOL, void *pData)
{
char cbBuffer[_MAX_PATH];
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdCode = lIdent;
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = cbBuffer;
	pbdData.pbdKTextLen = sizeof(cbBuffer)-1;

ErrCode RC = DEX_GetPBDData(pbdData);

	if (EC_OKAY == RC || WC_RETURN == RC) {
	// Item in Baum einhängen und mit dummy [+] versehen
	CORWndStatistics *pTarget = reinterpret_cast<CORWndStatistics *>(pData);
	HTREEITEM hItem = pTarget->InsertItem(cbBuffer, IMG_STATFUNC_ORWND_CUM, 
        IMG_STATFUNC_ORWND_CUM, m_hItem, TVI_LAST);
	TV_ITEM tvi;

		tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
		tvi.hItem = hItem;
		tvi.cChildren = 1;
		tvi.lParam = reinterpret_cast<LPARAM>(
            new CORWndObjectClassItemCallback(m_hWnd, lIdent, hItem));
		pTarget->SetItem(&tvi);
	}
    return TRUE;
}

BOOL CORWndStatistics::
CORWndItemCallback::PopulateItem (CORWndStatistics *pTarget, HTREEITEM hParent)
{
// Node für kumulative Werte einfügen
CString strCumulation;

	strCumulation.LoadString(IDS_CUMULATION);
	_ASSERTE(strCumulation.GetLength() > 0);

HTREEITEM hItem = pTarget->InsertItem(strCumulation, IMG_STATFUNC_CUM, IMG_STATFUNC_CUM, m_hItem, TVI_LAST);
TV_ITEM tvi;

	tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
	tvi.hItem = hItem;
	tvi.cChildren = 1;
	tvi.lParam = reinterpret_cast<LPARAM>(new CORWndObjectClassItemCallback(
        m_hWnd, INVALID_HOBJECTS, hItem));
	pTarget->SetItem(&tvi);

// Nodes für einzelne Objektklassen einfügen
CStdThunkImpl<CORWndStatistics::CORWndItemCallback, ENUMNOKEYLONGPROC> 
	Thunk(this, &CORWndStatistics::CORWndItemCallback::EnumClasses);
ENUMNOKEYLONG ENK;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = reinterpret_cast<void *>(pTarget);

	return DEXOR_EnumIdents(m_hWnd, ENK);
}

BOOL CORWndStatistics::
CORWndObjectClassItemCallback::PopulateItem(CORWndStatistics *pTarget, HTREEITEM hParent)
{
	COM_TRY {
		if (INVALID_HOBJECTS == m_lIdent) {
		// kumulative Werte für gesamtes RechercheFenster

		// ValueProvider: Objektanzahl (kumulativ)
			THROW_FAILED_HRESULT(InstallObjectCountInORWndProvider(pTarget, 
                m_hItem, m_hWnd, OBJECTTYPE_AllSimple, IMG_STATFUNC, 1, 
				TLVIS_BOLD, (CObjectCountInORWndProviderCallback *)NULL));
		}
		else {
		// ValueProvider: Objektanzahl eines Objektklasse im ORWnd
			THROW_FAILED_HRESULT(InstallObjectCountInORWndClassProvider(pTarget, 
                m_hItem, m_hWnd, m_lIdent, OBJECTTYPE_AllSimple, 
                IMG_STATFUNC_ORWND, 1, TLVIS_BOLD, 
                (CObjectCountInORWndClassProviderCallback *)NULL));
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Objekte, die an DatasourceItems hängen
//BOOL CORWndStatistics::
//CDataSourceItemCallback::EnumORWnds(INT_PTR lIdent, BOOL, void *pData)
//{
//
//	if (EC_OKAY == RC || WC_RETURN == RC) {
//	// Item in Baum einhängen und mit dummy [+] versehen
//	CORWndStatistics *pTarget = reinterpret_cast<CORWndStatistics *>(pData);
//	HTREEITEM hItem = pTarget->InsertItem(cbBuffer, IMG_STATFUNC_CLASS_CUM, IMG_STATFUNC_CLASS_CUM, m_hItem, TVI_LAST);
//	TV_ITEM tvi;
//
//		tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
//		tvi.hItem = hItem;
//		tvi.cChildren = 1;
//		tvi.lParam = reinterpret_cast<LPARAM>(new CORWndItemCallback(m_hPr, lIdent, hItem));
//		pTarget->SetItem(&tvi);
//	}
//	return TRUE;
//}

//BOOL CORWndStatistics::
//CDataSourceItemCallback::PopulateItem(CORWndStatistics *pTarget, HTREEITEM hParent)
//{
//// Node für kumulative Werte einfügen
//CString strCumulation;
//
//	strCumulation.LoadString(IDS_CUMULATION);
//	_ASSERTE(strCumulation.GetLength() > 0);
//
//HTREEITEM hItem = pTarget->InsertItem(strCumulation, IMG_STATFUNC_CUM, IMG_STATFUNC_CUM, m_hItem, TVI_LAST);
//TV_ITEM tvi;
//
//	tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
//	tvi.hItem = hItem;
//	tvi.cChildren = 1;
//	tvi.lParam = reinterpret_cast<LPARAM>(new CORWndItemCallback(m_hPr, 0, hItem));
//	pTarget->SetItem(&tvi);
//
//// ObjektRechercheFenster anfügen
//CStdThunkImpl<CORWndStatistics::CDataSourceItemCallback, ENUMNOKEYPROC> 
//	Thunk(this, &CORWndStatistics::CDataSourceItemCallback::EnumORWnds);
//ENUMNOKEYLONG ENKL;
//
//    INITSTRUCT(ENKL, ENUMNOKEYLONG);
//    ENKL.eFcn = Thunk.GetThunk();
//	ENKL.ePtr = reinterpret_cast<void *>(pTarget);
//
//	return DEX_EnumORWindows(ENKL);
//}

///////////////////////////////////////////////////////////////////////////////
// Objekte, die an Objektklassen im Baum hängen
//BOOL CORWndStatistics::
//CObjectClassItemCallback::PopulateItem(CORWndStatistics *pTarget, HTREEITEM hParent)
//{
//	COM_TRY {
//		if (INVALID_HOBJECTS == m_lIdent) {
//		// kumulative Werte für gesamte Datenquelle
//
//		// ValueProvider: Objektanzahl (kumulativ)
//			THROW_FAILED_HRESULT(InstallObjectCountInDatasourceProvider(pTarget, m_hItem, 
//				m_hPr, OBJECTTYPE_AllSimple, IMG_STATFUNC, 1, 
//				TLVIS_BOLD, (CObjectCountInDatasourceProviderCallback<CORWndStatistics> *)NULL));
//		}
//		else {
//		// ValueProvider: Objektanzahl (kumulativ)
//			THROW_FAILED_HRESULT(InstallObjectCountInClassProvider(pTarget, m_hItem, 
//				m_lIdent, OBJECTTYPE_AllSimple, IMG_STATFUNC_CLASS, 1, 
//				TLVIS_BOLD, (CObjectCountInClassProviderCallback<CORWndStatistics> *)NULL));
//		}
//
//	} COM_CATCH_RETURN(FALSE);
//	return TRUE;
//}

STDMETHODIMP CORWndStatistics::
CValueProviderCallback::NeedsRefresh()
{
	COM_TRY {
		_ASSERTE(NULL != m_pTarget);
		_ASSERTE(m_Provider.IsValid());

	CComVariant vValue;

		THROW_FAILED_HRESULT(m_Provider -> get_Value(&vValue));
		THROW_FAILED_HRESULT(vValue.ChangeType(VT_BSTR));

	TLVITEM tvItem;

		USES_CONVERSION;
		memset(&tvItem, '\0', sizeof(TLVITEM));
		tvItem.mask = TLVIF_FORMAT|TLVIF_STATE;
		tvItem.iSubItem = VALUE_COLUMN;
		m_pTarget->SendMessage(TVMX_GETSUBITEM, reinterpret_cast<WPARAM>(m_hItem), 
			reinterpret_cast<LPARAM>(&tvItem));

		tvItem.mask = TLVIF_TEXT|TLVIF_FORMAT;
		if (0 != tvItem.state)
			tvItem.mask |= TLVIF_STATE;
		tvItem.pszText = OLE2A(V_BSTR(&vValue));
		m_pTarget->SendMessage(TVMX_SETSUBITEM, reinterpret_cast<WPARAM>(m_hItem), 
			reinterpret_cast<LPARAM>(&tvItem));

	CRect rcItem;

		TreeView_GetItemRect(m_pTarget->m_hWnd, m_hItem, &rcItem, FALSE);
		m_pTarget->InvalidateRect(&rcItem);

	} COM_CATCH;
	return S_OK;
}
