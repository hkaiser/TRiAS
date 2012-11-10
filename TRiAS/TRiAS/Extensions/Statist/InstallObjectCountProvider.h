// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.12.2002 20:54:36 
//
// @doc
// @module InstallObjectCountProvider.h | Declaration of the <c CInstallObjectCountProvider> class

#if !defined(_INSTALLOBJECTCOUNTPROVIDER_H__2BB45BEB_14F8_450D_A43A_DFB3646420FF__INCLUDED_)
#define _INSTALLOBJECTCOUNTPROVIDER_H__2BB45BEB_14F8_450D_A43A_DFB3646420FF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Helper funktion zur Installation der Objektzähler-ValueProvider für eine 
// Datenquelle
template <typename CallbackT>
inline HRESULT 
InstallObjectCountInDatasourceProvider (CObjectClassStatistics *pTarget, 
	HTREEITEM hParent, HPROJECT hPr, OBJECTTYPE rgTypes, int iImage, 
	int iChildren, int iState, CallbackT *)
{
	COM_TRY {
	CComObject<CObjectCountInDatasource> *pProvider = NULL;
	WValueProvider Provider;

		THROW_FAILED_HRESULT(CComObject<CObjectCountInDatasource>::CreateInstance(&pProvider));
		Provider = pProvider;

	WTriasXtensionSite Site;

		THROW_FAILED_HRESULT(g_pTE -> GetXtensionSite(Site.ppi()));
		pProvider -> SetData(hPr, rgTypes);

	// Node erzeugen und einfügen
	CComBSTR bstrName;

		USES_CONVERSION;
		THROW_FAILED_HRESULT(Provider -> get_Name(&bstrName));

	HTREEITEM hItem = pTarget->InsertItem(OLE2A(bstrName), iImage, iImage, hParent, TVI_LAST);
	CallbackT *pValueProvider = new CallbackT(pTarget, hPr, Provider, hItem);

		THROW_FAILED_HRESULT(pProvider -> SetXtsnSite(Site, pValueProvider));

	TV_ITEM tvi;

		memset(&tvi, '\0', sizeof(TV_ITEM));
		tvi.mask = TVIF_HANDLE|TVIF_PARAM|TVIF_CHILDREN;
		tvi.hItem = hItem;
		tvi.cChildren = iChildren;
		tvi.lParam = reinterpret_cast<LPARAM>(pValueProvider);
		pTarget->SetItem(&tvi);

	// zum ersten mal den Wert bestimmen
	CComVariant vValue;

		THROW_FAILED_HRESULT(Provider -> get_Value(&vValue));
		THROW_FAILED_HRESULT(vValue.ChangeType(VT_BSTR));

	TLVITEM tvItem;

		memset(&tvItem, '\0', sizeof(TLVITEM));
		tvItem.mask = TLVIF_TEXT|TLVIF_FORMAT;
		if (TLVIS_NORMAL != iState)
			tvItem.mask |= TLVIF_STATE;
		tvItem.pszText = OLE2A(V_BSTR(&vValue));
		tvItem.format = TLVIFMT_RIGHT;
		tvItem.state = iState;
		tvItem.stateMask = iState;
		tvItem.iSubItem = VALUE_COLUMN;
		pTarget->SendMessage(TVMX_SETSUBITEM, reinterpret_cast<WPARAM>(hItem), 
			reinterpret_cast<LPARAM>(&tvItem));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helper funktion zur Installation der Objektzähler-ValueProvider für 
// Objektklassen
template <typename CallbackT>
inline HRESULT 
InstallObjectCountInClassProvider (CObjectClassStatistics *pTarget, 
	HTREEITEM hParent, HOBJECTS lIdent, OBJECTTYPE rgTypes, int iImage, 
	int iChildren, int iState, CallbackT *)
{
	COM_TRY {
	CComObject<CObjectCountInClass> *pProvider = NULL;
	WValueProvider Provider;

		THROW_FAILED_HRESULT(CComObject<CObjectCountInClass>::CreateInstance(&pProvider));
		Provider = pProvider;

	WTriasXtensionSite Site;

		THROW_FAILED_HRESULT(g_pTE -> GetXtensionSite(Site.ppi()));
		pProvider -> SetObjClass(lIdent, rgTypes);

	// Node erzeugen und einfügen
	CComBSTR bstrName;

		USES_CONVERSION;
		THROW_FAILED_HRESULT(Provider -> get_Name(&bstrName));

	HTREEITEM hItem = pTarget->InsertItem(OLE2A(bstrName), iImage, iImage, hParent, TVI_LAST);
	CallbackT *pValueProvider = new CallbackT(pTarget, lIdent, Provider, hItem);

		THROW_FAILED_HRESULT(pProvider -> SetXtsnSite(Site, pValueProvider));

	TV_ITEM tvi;

		memset(&tvi, '\0', sizeof(TV_ITEM));
		tvi.mask = TVIF_HANDLE|TVIF_PARAM|TVIF_CHILDREN;
		tvi.hItem = hItem;
		tvi.cChildren = iChildren;
		tvi.lParam = reinterpret_cast<LPARAM>(pValueProvider);
		pTarget->SetItem(&tvi);

	// zum ersten mal den Wert bestimmen
		THROW_FAILED_HRESULT(pValueProvider -> NeedsRefresh());

	CComVariant vValue;

		THROW_FAILED_HRESULT(Provider -> get_Value(&vValue));
		THROW_FAILED_HRESULT(vValue.ChangeType(VT_BSTR));

	TLVITEM tvItem;

		memset(&tvItem, '\0', sizeof(TLVITEM));
		tvItem.mask = TLVIF_TEXT|TLVIF_FORMAT;
		if (TLVIS_NORMAL != iState)
			tvItem.mask |= TLVIF_STATE;
		tvItem.pszText = OLE2A(V_BSTR(&vValue));
		tvItem.format = TLVIFMT_RIGHT;
		tvItem.state = iState;
		tvItem.stateMask = iState;
		tvItem.iSubItem = VALUE_COLUMN;
		pTarget->SendMessage(TVMX_SETSUBITEM, reinterpret_cast<WPARAM>(hItem), 
			reinterpret_cast<LPARAM>(&tvItem));

	} COM_CATCH;
	return S_OK;
}

#endif // !defined(_INSTALLOBJECTCOUNTPROVIDER_H__2BB45BEB_14F8_450D_A43A_DFB3646420FF__INCLUDED_)
