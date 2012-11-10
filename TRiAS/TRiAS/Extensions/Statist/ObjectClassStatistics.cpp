// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.09.2001 21:34:32 
//
// @doc
// @module ObjectClassStatistics.cpp | Definition of the <c CObjectClassStatistics> class

#include "StdAfx.h"

#include <Com/Thunk.h>
#include <triastlb.h>

#include "StatistApp.h"
#include "Statist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "TreeListView.h"
#include "ObjectClassStatistics.h"
#include "ObjectCountInClass.h"
#include "ObjectCountInDatasource.h"
#include "InstallObjectCountProvider.h"

///////////////////////////////////////////////////////////////////////////////
// Initialisierung des TreeViewControls mit allem notwendigen
// Implementation of InitTreeView
BOOL CObjectClassStatistics::InitRoot()
{
// Wurzel ist der Workspace
char cbBuffer[_MAX_PATH];
CString strWrkSpace;

	DEX_GetActiveProject(cbBuffer);
	PathStripPath(cbBuffer);
	*PathFindExtension(cbBuffer) = '\0';

	strWrkSpace.Format(IDS_WORKSPACEROOT_INIT, cbBuffer);

HTREEITEM hItemRoot = InsertItem(strWrkSpace, IMG_WORKSPACE, IMG_WORKSPACE, TVI_ROOT, TVI_LAST);

// alle aktuellen Datenquellen enumerieren
CStdThunkImpl<CObjectClassStatistics, ENUMNOKEYLONGPROC> 
	Thunk(this, &CObjectClassStatistics::EnumDataSources);
ENUMNOKEYLONG ENK;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = &hItemRoot;
	if (DEX_EnumDataSourceHandles(ENK)) {
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
// Enumeration aller aktuellen Datenquellen
namespace {
// mappen der RegistryBmpNo auf unsere Imagelist
	int g_cbBmps[] = {
		IMG_NOICON, IMG_NOICON, IMG_DATASOURCE_GDO, IMG_NOICON,
		IMG_NOICON, IMG_DATASOURCE, IMG_DATASOURCE, IMG_DATASOURCE, 
		IMG_NOICON, IMG_NOICON, IMG_NOICON, IMG_DATASOURCE_TRiAS1,
		IMG_DATASOURCE_TRiAS2, IMG_DATASOURCE_TRiAS3, IMG_DATASOURCE_TRiAS_EMBEDDED, IMG_DATASOURCE_TRiAS1, 
		IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_MAPINFO, IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_MAPINFO, 
		IMG_DATASOURCE_OLEDB, IMG_DATASOURCE_OLEDB, IMG_DATASOURCE_POLYGIS, IMG_DATASOURCE_POLYGIS,
		IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_GDO, IMG_DATASOURCE_MEMDB
	};
}

EXTERN_C const CLSID CLSID_TRiASDataServerRegEntries;

BOOL CObjectClassStatistics::EnumDataSources (HPROJECT hPr, BOOL, UINT_PTR *pData)
{
// Namen der Datenquelle besorgen
char cbBuffer[_MAX_PATH];

	DEX_GetDataSourceShortName(hPr, cbBuffer);

// Icon der Datenquelle besorgen
DWORD dwBmp = IMG_DATASOURCE;

	{
	__Interface<ITRiASConnection> Conn;

		if (DEX_GetDataSourcePtr(hPr, *Conn.ppv())) {
		__Interface<ITRiASDatabase> DBase;

			if (SUCCEEDED(Conn -> get_Database (DBase.ppi()))) {
				USES_CONVERSION;

			CComBSTR bstrProgID;		// ProgID des TRiAS-DataBase-TargetObjektes

				if (SUCCEEDED(DBase -> get_Type (&bstrProgID))) {
				__Interface<ITRiASDataServerRegEntries> Entries(CLSID_TRiASDataServerRegEntries);
				__Interface<ITRiASDataServerRegEntry> Entry;

					if (SUCCEEDED(Entries -> FindFromServerProgID (bstrProgID, Entry.ppi()))) 
						Entry -> get_ToolboxBitmap32 ((LONG *)&dwBmp);
				}
			}
		}
	}

// Item in Baum einhängen und mit dummy [+] versehen
	_ASSERTE(0 <= dwBmp && dwBmp < _countof(g_cbBmps));

HTREEITEM hRoot = *reinterpret_cast<HTREEITEM *>(pData);
HTREEITEM hItem = InsertItem(cbBuffer, g_cbBmps[dwBmp], g_cbBmps[dwBmp], hRoot, TVI_LAST);
TV_ITEM tvi;

	tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
	tvi.hItem = hItem;
	tvi.cChildren = 1;
	tvi.lParam = reinterpret_cast<LPARAM>(new CDataSourceItemCallback(hPr, hItem));
	SetItem(&tvi);
	return TRUE;
}

// wird für jedes zu öffnende Item gerufen
BOOL CObjectClassStatistics::PopulateItem(HTREEITEM hParent)
{
	if (TVI_ROOT == hParent) 
		return InitRoot();

// Itemspezifische Funktion rufen
CItemCallback *pItemCB = reinterpret_cast<CItemCallback *>(GetItemData(hParent));

	_ASSERTE(NULL != pItemCB);
	return pItemCB->PopulateItem(this, hParent);
}

// wird für jedes zu löschende Item gerufen
void CObjectClassStatistics::DeletingItem(HTREEITEM hItem)
{
CItemCallback *pItemCB = reinterpret_cast<CItemCallback *>(GetItemData(hItem));

	DELETE_OBJ(pItemCB);
	SetItemData(hItem, NULL);
}

///////////////////////////////////////////////////////////////////////////////
// Objekte, die an DatasourceItems hängen
BOOL CObjectClassStatistics::
CDataSourceItemCallback::EnumClasses(INT_PTR lIdent, BOOL, void *pData)
{
char cbBuffer[_MAX_PATH];
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdCode = lIdent;
	pbdData.pbdTyp = 'i';
	pbdData.pbdKText = cbBuffer;
	pbdData.pbdKTextLen = sizeof(cbBuffer)-1;

ErrCode RC = DEX_GetPBDDataEx(m_hPr, pbdData);

	if (EC_OKAY == RC || WC_RETURN == RC) {
	// Item in Baum einhängen und mit dummy [+] versehen
	CObjectClassStatistics *pTarget = reinterpret_cast<CObjectClassStatistics *>(pData);
	HTREEITEM hItem = pTarget->InsertItem(cbBuffer, IMG_STATFUNC_CLASS_CUM, 
        IMG_STATFUNC_CLASS_CUM, m_hItem, TVI_LAST);
	TV_ITEM tvi;

		tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
		tvi.hItem = hItem;
		tvi.cChildren = 1;
		tvi.lParam = reinterpret_cast<LPARAM>(new CObjectClassItemCallback(m_hPr, lIdent, hItem));
		pTarget->SetItem(&tvi);
	}
	return TRUE;
}

BOOL CObjectClassStatistics::
CDataSourceItemCallback::PopulateItem(CObjectClassStatistics *pTarget, HTREEITEM hParent)
{
// Node für kumulative Werte einfügen
CString strCumulation;

	strCumulation.LoadString(IDS_CUMULATION);
	_ASSERTE(strCumulation.GetLength() > 0);

HTREEITEM hItem = pTarget->InsertItem(strCumulation, IMG_STATFUNC_CUM, 
    IMG_STATFUNC_CUM, m_hItem, TVI_LAST);
TV_ITEM tvi;

	tvi.mask = TVIF_HANDLE|TVIF_CHILDREN|TVIF_PARAM;
	tvi.hItem = hItem;
	tvi.cChildren = 1;
	tvi.lParam = reinterpret_cast<LPARAM>(new CObjectClassItemCallback(m_hPr, 
        INVALID_HOBJECTS, hItem));
	pTarget->SetItem(&tvi);

// Objektklassen anfügen
CStdThunkImpl<CObjectClassStatistics::CDataSourceItemCallback, ENUMNOKEYPROC> 
	Thunk(this, &CObjectClassStatistics::CDataSourceItemCallback::EnumClasses);
ENUMNOKEY ENK;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = reinterpret_cast<void *>(pTarget);

	return DEX_EnumClasses(m_hPr, ENK);
}

///////////////////////////////////////////////////////////////////////////////
// Objekte, die an Objektklassen im Baum hängen
BOOL CObjectClassStatistics::
CObjectClassItemCallback::PopulateItem(CObjectClassStatistics *pTarget, HTREEITEM hParent)
{
	COM_TRY {
		if (INVALID_HOBJECTS == m_lIdent) {
		// kumulative Werte für gesamte Datenquelle

		// ValueProvider: Objektanzahl (kumulativ)
			THROW_FAILED_HRESULT(InstallObjectCountInDatasourceProvider(pTarget, 
                m_hItem, m_hPr, OBJECTTYPE_AllSimple, IMG_STATFUNC, 1, 
				TLVIS_BOLD, (CObjectCountInDatasourceProviderCallback *)NULL));
		}
		else {
		// ValueProvider: Objektanzahl (kumulativ)
			THROW_FAILED_HRESULT(InstallObjectCountInClassProvider(pTarget, 
                m_hItem, m_lIdent, OBJECTTYPE_AllSimple, IMG_STATFUNC_CLASS, 1, 
				TLVIS_BOLD, (CObjectCountInClassProviderCallback *)NULL));
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

STDMETHODIMP CObjectClassStatistics::
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

