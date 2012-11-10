// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 11/05/1998 12:31:21 PM
//
// @doc
// @module TRiASGuidFeature.cpp | Description goes here

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"

#include <Atl/Ciid.h>
#include <Com/VariantHelpers.h>
#include <Com/MkHelper.h>
#include <Com/PropertyHelper.h>

#include <NativeObject.h>
#include <errinst.hxx>

#include "TRiASDBGuids.h"

#include "TRiASObjects.h"
#include "TRiASGuidFeature.h"

using namespace trias_nativeobject;

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASGuidFeature);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASGuidFeature::Dump()
{
	return S_OK;
}
#endif // defined(_DUMP_PENDING_OBJECTS)

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASGuidFeature, CTRiASGuidFeature)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(OleClientSite);
DefineSmartInterface(TRiASObjectHandleMap);

/////////////////////////////////////////////////////////////////////////////
// CTRiASGuidFeature

STDMETHODIMP CTRiASGuidFeature::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleFeature,
		&IID_ITRiASFeature,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureCallback
STDMETHODIMP CTRiASGuidFeature::get_DefaultType (BSTR *pbstrType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pbstrType)
		return E_POINTER;

CIID Guid (GetObjectCLSID());
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASGuidFeature::SetupFeature (SETUPFEATUREMODE rgWhat)
{
	return S_OK;
}

STDMETHODIMP CTRiASGuidFeature::OnChanging(CHANGEDFEATURE rgWhat, VARIANT vNewValue, VARIANT_BOOL *pfDisAllow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == pfDisAllow)
		return E_POINTER;
	*pfDisAllow = VARIANT_FALSE;		// immer zulassen
	return S_OK;
}

STDMETHODIMP CTRiASGuidFeature::OnChanged(CHANGEDFEATURE rgWhat, VARIANT vOldValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn wir nicht derzeit initialisiert werden
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch (rgWhat) {
	case CHANGEDFEATURE_Name:
		return OnChangedName();

	case CHANGEDFEATURE_Description:
		return OnChangedDescription();

	case CHANGEDFEATURE_Handle:
		return OnChangedHandle();

	case CHANGEDFEATURE_ROMode:
		return OnChangedROMode();

	case CHANGEDFEATURE_Length:
	case CHANGEDFEATURE_Value:
	case CHANGEDFEATURE_Type:
		return S_OK;

	default:
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		break;
	}
	return E_INVALIDARG;
}

HRESULT CTRiASGuidFeature::OnChangedName()
{
	USES_CONVERSION;

// Namen vom Bezugsobjekt besorgen
CComBSTR bstrName;
WTRiASFeature BaseFeat;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
	RETURN_FAILED_HRESULT(BaseFeat -> get_Name(CLEARED(&bstrName)))

// Parent informieren, daß der Name des PrimaryKey sich geändert hat
WTRiASObjects Objs;

	RETURN_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, Objs.ppi()));
	RETURN_FAILED_HRESULT(Objs -> put_PrimaryKey (bstrName));
	return S_OK;
}

HRESULT CTRiASGuidFeature::OnChangedDescription()
{
	return S_OK;
}

HRESULT CTRiASGuidFeature::OnChangedHandle()
{
	return S_OK;
}

HRESULT CTRiASGuidFeature::OnChangedROMode()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Eval: Das, worum es eigentlich geht ...
STDMETHODIMP CTRiASGuidFeature::Eval(ITRiASObject *pIObj, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

HRESULT hr = S_OK;

	COM_TRY {
	// Projekthandle vom Parent erfragen
	HPROJECT hPrFeat = NULL;

		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPrFeat));

	WTRiASSimpleObject Obj (pIObj);		// nur SimpleObjects bearbeiten
	WTRiASDatabase Parent;
	HPROJECT hPrObj = NULL;

		THROW_FAILED_HRESULT(FindSpecificParent(pIObj, Parent.ppi()));
		THROW_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPrObj));

		if (hPrObj != hPrFeat) {
			_ASSERTE(hPrObj == hPrFeat);
			return E_UNEXPECTED;	// TRiAS-Merkmale dürfen nur für TRiAS-Objekte berechnet werden
		}

	// Objektnummer abfragen
	INT_PTR lONr = 0L;

		THROW_FAILED_HRESULT(Obj -> get_LocalHandle(&lONr));

	// Merkmal lesen
	CIID Guid;
	CNativeObject Object (hPrObj, lONr);

		hr = Object.GetObjectGUID (&Guid);
		if (SUCCEEDED(hr)) {
		CComBSTR bstr (Guid);
		CComVariant var (bstr);

			THROW_FAILED_HRESULT(var.Detach (pVal));
		}

	} COM_CATCH;
	return hr;
}

STDMETHODIMP CTRiASGuidFeature::EvalEx(ITRiASObject *pIObj, SAFEARRAY **ppConstraints, VARIANT *pVal)
{
	return Eval (pIObj, pVal);		// ignore constraints	
}

STDMETHODIMP CTRiASGuidFeature::Update(ITRiASObject *pIObj, VARIANT Val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;

	if (VT_ERROR == V_VT(&Val))
		return S_FALSE;			// löschen wird für diese Objekteigenschaft nicht unterstützt

HRESULT hr = S_OK;

	COM_TRY {
	// Projekthandle vom Parent erfragen
	HPROJECT hPrFeat = NULL;

		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPrFeat));

	WTRiASSimpleObject Obj (pIObj);		// nur SimpleObjects bearbeiten
	WTRiASDatabase Parent;
	HPROJECT hPrObj = NULL;

		THROW_FAILED_HRESULT(FindSpecificParent(pIObj, Parent.ppi()));
		THROW_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPrObj));

		if (hPrObj != hPrFeat) {
			_ASSERTE(hPrObj == hPrFeat);
			return E_UNEXPECTED;	// TRiAS-Merkmale dürfen nur für TRiAS-Objekte berechnet werden
		}

	CComVariant vNewVal;

		if (!V_ISNULL(&Val) && SUCCEEDED(vNewVal.ChangeType (VT_BSTR, &Val))) {
		// Objektnummer abfragen, Guid setzen
		INT_PTR lONr = 0L;

			THROW_FAILED_HRESULT(Obj -> get_LocalHandle(&lONr));

		CIID Guid (V_BSTR(&vNewVal), CIID::INITCIID_InitFromGuid);

			if (!Guid) return E_INVALIDARG;		// fehlerhafter Guid

		CNativeObject Object (hPrObj, lONr);

			hr = Object.SetObjectGUID (Guid);
		} else {
		// löschen ??
//			_com_issue_error(E_INVALIDARG);
		}
				
	} COM_CATCH;
	return hr;
}

// Kopie der Objekteigenschaft erzeugen
STDMETHODIMP CTRiASGuidFeature::Clone (ITRiASFeature **ppIFeat)
{
	return E_NOTIMPL;
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASGuidFeature::OnFinalRelease()
{
	COM_TRY {
	WTRiASFeature BaseFeat;
	WDispatch Parent;
	INT_PTR hFeat = NULL;

		if (SUCCEEDED(m_BaseUnk -> QueryInterface (BaseFeat.ppi()))) {
			BaseFeat -> get_Parent (Parent.ppi());
			BaseFeat -> get_Handle (&hFeat);
		}
			
	// aus Objects-Tabelle entfernen
	WTRiASDatabase DBase;

		if (SUCCEEDED(FindSpecificParent (Parent, DBase.ppi()))) {
		WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbFeatureMap, (IDispatch *)NULL), false);

			_ASSERTE(Map.IsValid());
			if (Map.IsValid() && NULL != hFeat) 
				VERIFY(S_OK == Map -> RemoveObject ((LONG)hFeat, OBJECTMAPMODE_RemoveAllReferences));
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASSimpleFeature
STDMETHODIMP CTRiASGuidFeature::get_LocalHandle (INT_PTR *pVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASGuidFeature::InitTarget (VARIANT vName, FEATURETYPE rgType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized) {					// nur einmal initialisieren
	CComSemaphore<_ThreadModel> Sem (m_lInitData);	// doppeltes Initialisieren verhindern (recursion!)

	// erstmal nur Werte zwischenspeichern
	WTRiASFeature BaseFeat;
	CComVariant vArg;

		RETURN_FAILED_HRESULT(vArg.ChangeType(VT_BSTR, &vName));
		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		RETURN_FAILED_HRESULT(BaseFeat -> put_Name (V_BSTR(&vArg)));

	// Typ der Objekteigenschaft setzen
		rgType = (FEATURETYPE)((rgType & ~FEATURETYPE_DataTypeMask) | DATATYPE_FROM_VT(VT_BSTR));
		RETURN_FAILED_HRESULT(BaseFeat -> put_Type (rgType));

		m_fIsInitialized = true;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IOleObject
STDMETHODIMP CTRiASGuidFeature::GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
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
HRESULT CTRiASGuidFeature::GetContainerMoniker (IMoniker **ppIMk)
{
	COM_TRY {
	WMoniker mk;
	WTRiASConnection Parent;
	WTRiASFeature BaseFeat;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(FindSpecificParent (BaseFeat, Parent.ppi()));
		THROW_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mk.ppi()));
		*ppIMk = mk.detach();

	} COM_CATCH;
	return S_OK;
}

// Den vollständigen Moniker dieses Objektes liefern
HRESULT CTRiASGuidFeature::GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk)
{
	COM_TRY {
	// Moniker eines Features hat folgende Struktur:
	// MkFeature:Name, den Typ (ClsId) muß sowieso der Container kennen
	WMoniker mk, mkThis, mkItem;
	CComBSTR bstrItem (g_cbMkFeature);		// "!MkFeature:__ObjGuid__"

		bstrItem.Append (g_cbColon);
		bstrItem.Append (g_cbObjGuid);

		if (!bstrItem)
			_com_issue_error(E_OUTOFMEMORY);

		switch (dwWhich) {
		case OLEWHICHMK_OBJREL:
			{
				THROW_FAILED_HRESULT(::CreateItemMoniker(g_cbMkDel, bstrItem, mkThis.ppi()));
				*ppIMk = mkThis.detach();
			}
			break;

		case OLEWHICHMK_OBJFULL:
			{
				THROW_FAILED_HRESULT(GetContainerMoniker (mk.ppi()));
				THROW_FAILED_HRESULT(::CreateItemMoniker(g_cbMkDel, bstrItem, mkThis.ppi()));
				THROW_FAILED_HRESULT(mk -> ComposeWith (mkThis, false, mkItem.ppi()));
				*ppIMk = mkItem.detach();
			}
			break;

		default:
		case OLEWHICHMK_CONTAINER:
			return E_INVALIDARG;
		}
	} COM_CATCH;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSearchObjects

STDMETHODIMP CTRiASGuidFeature::ConsiderSearch (BSTR bstrCommand, SAFEARRAY *pParams)
{
int iMode = ModeFromSearchCommand(bstrCommand);

	if (SMExactMatch != iMode)
		return TRIASDB_S_SEARCH_NOT_SUPPORTED;		// negate ist nicht unterstützt

	return S_OK;	// ok, kann hier gesucht werden
}

STDMETHODIMP CTRiASGuidFeature::SearchObjects (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
	if (S_OK != ConsiderSearch(bstrCommand, pParams))
		return TRIASDB_S_SEARCH_NOT_SUPPORTED;		// not supported search

	USES_CONVERSION;

// hier benötigte InterfacePointer besorgen
WTRiASDatabase Parent;
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(FindSpecificParent(m_BaseUnk, Parent.ppi()));
	RETURN_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPr));

WTRiASObjectHandleMap ObjMap (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
WTRiASObjectHandleMap ObjsMap (GetPropertyFrom (Parent, g_cbObjectsMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab

// Parameter für die Recherche aus ParameterFeld herausholen
CComBSTR bstrPattern;	// SuchString
int iMode = 0;			// SuchMode

	RETURN_FAILED_HRESULT(RetrieveSearchParams (bstrCommand, pParams, CLEARED(&bstrPattern), &iMode));
	_ASSERTE(SMExactMatch == iMode);

// eigentliche Recherche durchführen
CIID Guid (bstrPattern);

	if (!Guid)	// Suchpattern ist kein Guid
		return TRIASDB_I_NO_OBJECTS_FOUND;		// nichts gefunden
		
INT_PTR hObject = NULL;
ErrInstall EI (WC_NOTFOUND);
HRESULT hr = CNativeObject::FindObjectFromGUID (hPr, Guid, &hObject);

	if (HRESULT_FROM_ERRCODE(WC_NOTFOUND) == hr)
		return TRIASDB_I_NO_OBJECTS_FOUND;		// nichts gefunden
	if (S_OK != hr)
		return hr;

// sicherstellen, daß in zugehöriger Objektklasse alle Objekte geladen sind
CNativeObject Obj (hPr, hObject);
INT_PTR lIdent = 0;

	RETURN_FAILED_HRESULT(Obj.GetIdent (&lIdent));

WTRiASObjects Objs;
CTRiASObjects *pObjs = NULL;

	RETURN_FAILED_HRESULT(ObjsMap -> GetObject (lIdent, Objs.ppu()));
	RETURN_FAILED_HRESULT(QueryImplementation (Objs, &pObjs));		// no addref !
	RETURN_FAILED_HRESULT(pObjs -> EnsureObjectsLoaded());

// Objekt evtl. aus der DatabaseMap holen
WTRiASObject Object;

	hr = ObjMap -> GetObject (hObject, Object.ppu());
	if (SUCCEEDED(hr))
	{
		RETURN_FAILED_HRESULT(pIObjs -> _Add (Object, VARIANT_TRUE));
	}
	return SUCCEEDED(hr) ? S_OK : hr;
}

STDMETHODIMP CTRiASGuidFeature::ConstraintObjects (ITRiASObjects *pObjs)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));
	return E_NOTIMPL;
}

