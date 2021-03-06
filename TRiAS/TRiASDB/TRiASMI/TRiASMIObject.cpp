// $Header: $
// Copyright� 1998-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 21:21:48 
//
// This file was generated by the TRiASDB Data Server Wizard V1.02.103 (#HK000729)
//
// @doc
// @module TRiASMIObject.cpp | Implementation of the <c CTRiASMIObject> class

#include "stdafx.h"

#include <Com/MkHelper.h>

#include "Strings.h"

#include "TRiASMI.h"
#include "TRiASMIObject.h"
#include "TRiASMIPropertySupport.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTRiASMIObject

STDMETHODIMP CTRiASMIObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASObject,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectCallback

STDMETHODIMP CTRiASMIObject::get_DefaultType (BSTR *pbstrType)
{
	CHECKOUTPOINTER(pbstrType);

CIID Guid (GetObjectCLSID());
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

// called during InitNew/Load
STDMETHODIMP CTRiASMIObject::SetupObject(SETUPOBJECTMODE rgMode)
{
	_ASSERTE(SETUPOBJECTMODE_InitOrLoad == rgMode);		// z.Zt nur dieses
	COM_TRY {
	// Properties zum aggregierten Objekt hinzuf�gen
	WTRiASPropertyMapHandler MapHandler(m_BaseUnk);

		THROW_FAILED_HRESULT(MapHandler -> AddMapEntry (
			CComBSTR(g_cbObjectCursor), (INT_PTR)&CLSID_TRiASMICursorProperty, PROPERTYSUPPORT_NOFLAGS, vtMissing));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASMIObject::OnChanging (CHANGEDOBJECT rgWhat, VARIANT vNewValue, VARIANT_BOOL *pDisAllow)
{
	CHECKOUTPOINTER(pDisAllow);

#if defined(_READWRITE)
	*pDisAllow = VARIANT_FALSE;		// immer einverstanden sein
	return S_OK;
#else
// w�hrend der Initialisierungsphase ist eine Modifikation erlaubt
bool fIsInitializing = false;

	COM_TRY {
	WTRiASObject Obj;
	INT_PTR hObjs = NULL;


		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (Obj.ppi()));
		THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle (&hObjs));
		fIsInitializing = (NULL == hObjs) ? true : false;

	} COM_CATCH;

	if (fIsInitializing) {
		*pDisAllow = VARIANT_FALSE;		// immer einverstanden sein
		return S_FALSE;					// OnChanged trotzdem nicht mehr rufen
	} else {
		*pDisAllow = VARIANT_TRUE;		// verhindert Modifikation (rgWhat siehe OnChanged)
		return TRIASDB_E_OBJECTSNOTUPDATABLE;
	}
#endif // defined(_READWRITE)
}

STDMETHODIMP CTRiASMIObject::OnChanged (CHANGEDOBJECT rgWhat, VARIANT vOldValue)
{
#if defined(_READWRITE)
	return S_OK;
#else
	return TRIASDB_E_OBJECTSNOTUPDATABLE;
#endif // defined(_READWRITE)
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASMIObject::OnFinalRelease()
{
	COM_TRY {
	// unsere Nummer (Cursor) freigeben und damit dieses Objekt aus der Handlemap herausl�schen
		THROW_FAILED_HRESULT(DelPropertyBy (WDispatch(m_BaseUnk), g_cbObjectCursor));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASMIObject::OnDelete()
{
// diese Funktion wird nur dann gerufen, wenn CTRiASMIObjects::OnDelete() E_NOTIMPL
// geliefert hat.
#if defined(_READWRITE)
#pragma TODO("Objekt aus Datenquelle herausl�schen.")

	// S_OK:	wurde erfolgreich gel�scht
	// ansonsten Fehlercode
	return S_OK;
#else
	return TRIASDB_E_OBJECTSNOTUPDATABLE;
#endif // defined(_READWRITE)
}

STDMETHODIMP CTRiASMIObject::SetupFeatures(SETUPFEATURESMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}


/////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CTRiASMIObject::GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	switch (dwWhich) {
    case OLEWHICHMK_CONTAINER:
		return GetContainerMoniker (ppIMk);

	case OLEWHICHMK_OBJREL:
    case OLEWHICHMK_OBJFULL:
		return GetThisMoniker (dwWhich, ppIMk);
	
	default:
		break;
	}
	return E_INVALIDARG;
}

// Moniker des zugeordneten Containers liefern
HRESULT CTRiASMIObject::GetContainerMoniker (IMoniker **ppIMk)
{
	COM_TRY {
	WTRiASObjects Parent;
	WMoniker mk;

		THROW_FAILED_HRESULT(FindSpecificParent(m_BaseUnk, Parent.ppi()));
		THROW_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
		*ppIMk = mk.detach();

	} COM_CATCH;
	return S_OK;
}

// Den vollst�ndigen Moniker dieses Objektes liefern
HRESULT CTRiASMIObject::GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk)
{
	if (NULL == ppIMk)
		return E_POINTER;
	*ppIMk = NULL;

	COM_TRY {
	WMoniker mk, mkThis, mkItem;

		switch (dwWhich) {
		case OLEWHICHMK_OBJREL:
			THROW_FAILED_HRESULT(MkGetMoniker (m_BaseUnk, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mkThis.ppi()));
			break;

		case OLEWHICHMK_OBJFULL:
			THROW_FAILED_HRESULT(GetContainerMoniker (mk.ppi()));
			THROW_FAILED_HRESULT(MkGetMoniker (m_BaseUnk, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mkThis.ppi()));
			THROW_FAILED_HRESULT(mk -> ComposeWith (mkThis, false, mkItem.ppi()));
			break;

		default:
		case OLEWHICHMK_CONTAINER:
			return E_INVALIDARG;
		}

	// Resulttat liefern
		*ppIMk = mkItem.detach();

	} COM_CATCH;
	return S_OK;
}

