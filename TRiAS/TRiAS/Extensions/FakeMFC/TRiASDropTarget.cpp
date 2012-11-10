// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.09.2000 19:33:56 
//
// @doc
// @module TRiASDropTarget.cpp | Definition of the <c CTRiASDropTarget> class

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <itoolbar.h>

#include "FakeMfc.hxx"
#include "TRiASDropTarget.h"

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(CatInformation);
DefineSmartInterface(EnumGUID);
DefineSmartInterface(EnumString);

///////////////////////////////////////////////////////////////////////////////
// Implementation of OnDragEnter
DROPEFFECT CTRiASDropTarget::OnDragEnter(IDataObject *pDataObj, DWORD grfKeyState, CPoint pt)
{
	if (FAILED(EnsureFileExtensionList()))
		return DROPEFFECT_NONE;

	return DROPEFFECT_NONE;
}

// Implementation of OnDragOver
DROPEFFECT CTRiASDropTarget::OnDragOver(DWORD grfKeyState, CPoint pt)
{
	return DROPEFFECT_NONE;
}

// Implementation of OnDrop
BOOL CTRiASDropTarget::OnDrop(DROPEFFECT dropEffect, CPoint point)
{
	return DROPEFFECT_NONE;
}

// Implementation of OnDragLeave
void CTRiASDropTarget::OnDragLeave()
{
	m_rgDropEffect = DROPEFFECT_NONE;
}

///////////////////////////////////////////////////////////////////////////////
// Einlesen der Liste der gültigen Dateierweiterungen der verschiedenen
// registrierten Datenserver
HRESULT CTRiASDropTarget::EnsureFileExtensionList()
{
	if (!m_fHasExts) {
	// gecachte GUID's verwenden
	GUID guid;

		m_lstExts.clear();

		_ASSERTE(CFakeMFCExtension::s_DBEngineGUIDs.IsValid());
		for (CFakeMFCExtension::s_DBEngineGUIDs.Reset(); S_OK == CFakeMFCExtension::s_DBEngineGUIDs.Next (1, &guid, NULL); /**/)
		{
			if (CLASS_E_NOTLICENSED == InitFileExtensionList(guid))
				CFakeMFCExtension::s_DBEngineGUIDs.RemoveActiveItem();
		}
		m_fHasExts = true;
	}
	return (m_lstExts.size() > 0) ? S_OK : S_FALSE;
}

HRESULT CTRiASDropTarget::InitFileExtensionList (REFGUID rGuid)
{
LPOLESTR poleStr = NULL;

	USES_CONVERSION;
	COM_TRY {
	// DBEngine instantiieren und nach EnumString fragen
	WTRiASDBEngine DBEng;
	WUnknown Unk;
	HRESULT hr = DBEng.CreateInstance(rGuid);

		if (FAILED(hr))
			return hr;		// ggf. nicht instantiierbar (z.B. lizensiert)
			
		THROW_FAILED_HRESULT(DBEng -> EnumDataBaseTypes (Unk.ppi()));

	// jetzt eigentliche Dataserver einfügen
	WEnumString EnumStr(Unk);

		for (EnumStr -> Reset(); S_OK == EnumStr -> Next (1, &poleStr, NULL); /**/)
		{
		CConnectParams Item;
		DWORD dwDummy = 0;
		HRESULT hr = TxGetExtension() -> ReadDataServerParams (dwDummy, &Item, OLE2A(poleStr));

			CoTaskMemFree (poleStr);
			poleStr = NULL;

		// nur dateibasierte Datenquelle untersuchen
			if (!Item.m_fNameIsFile)
				continue;

			m_lstExts.insert(CExtensions::value_type(os_string(Item.m_strDefExt), Item));
		}

	} COM_CATCH_OP(CoTaskMemFree (poleStr));
	return S_OK;
}

