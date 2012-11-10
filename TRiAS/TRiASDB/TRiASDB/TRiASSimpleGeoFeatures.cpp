// @doc
// @module TRiASSimpleFeatures.cpp | Implementation of the <c CTRiASSimpleGeoFeatures> class

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"
#include "GlobalVars.h"

#include <NativePbd.h>

#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>

#include "GenObjectMap.h"
#include "TRiASSimpleGeoFeatures.h"

using namespace trias_nativepbd;

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASSimpleGeoFeatures);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASSimpleGeoFeatures::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASSimpleGeoFeatures, CTRiASSimpleGeoFeatures)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleGeoFeatures

STDMETHODIMP CTRiASSimpleGeoFeatures::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleGeoFeatures,
		&IID_ITRiASFeatures,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASFeaturesCallback

STDMETHODIMP CTRiASSimpleGeoFeatures::get_DefaultType (BSTR *pbstrType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pbstrType)
		return E_POINTER;

CIID Guid (CLSID_TRiASSimpleGeoFeature);		// DefaultType der _Elemente_ !
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

// eine neue Objekteigenschaft soll erzeugt werden
STDMETHODIMP CTRiASSimpleGeoFeatures::OnCreate (VARIANT NameOrHandle, BSTR Type, FEATURETYPE rgType, ITRiASFeature **ppIFeat)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	_ASSERTE(FALSE);		// darf nicht gerufen werden
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CTRiASSimpleGeoFeatures::OnChanging(CHANGEDFEATURES rgWhat, VARIANT vNewValue, VARIANT_BOOL *pfDisAllow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == pfDisAllow)
		return E_POINTER;
	*pfDisAllow = VARIANT_FALSE;		// immer zulassen
	return S_OK;
}

// Irgend was wurde modifiziert
STDMETHODIMP CTRiASSimpleGeoFeatures::OnChanged(CHANGEDFEATURES rgWhat, VARIANT vOldValue)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn wir nicht derzeit initialisiert werden
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch(rgWhat) {
	case CHANGEDFEATURES_Name:
		return OnChangedName();

	case CHANGEDFEATURES_Description:
		return OnChangedDescription();

	case CHANGEDFEATURES_Handle:
		return OnChangedHandle();

	default:
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		break;
	}
	return E_INVALIDARG;
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASSimpleGeoFeatures::OnFinalRelease()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Ein Objekt soll gelöscht werden
STDMETHODIMP CTRiASSimpleGeoFeatures::OnDelete (VARIANT vWhich)
{
	_ASSERTE(FALSE);		// darf nicht gerufen werden
	return E_NOTIMPL;
}

HRESULT CTRiASSimpleGeoFeatures::GetOrCreateObject (BSTR bstrName, FEATURETYPE rgType)
{
// Objekt neu erzeugen/wiederverwenden und zur Collection hinzufügen
WDispatch App;
WDispatch Parent;
WTRiASDatabase DBase;
WTRiASFeatures BaseFeats;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeats.ppi()));

	RETURN_FAILED_HRESULT(BaseFeats -> get_Application (App.ppi()));
	RETURN_FAILED_HRESULT(BaseFeats -> get_Parent(Parent.ppi()));		// Parent ist TRiASObjects

// Für TRiAS-Datenbanken werden die Objekteigenschaften nun doch DatenBank-weit erzeugt.
// d.h. Alle Objekte einer DatenBank haben einen identischen Satz von Objekteigenschaften.
	RETURN_FAILED_HRESULT(FindSpecificParent (BaseFeats, DBase.ppi()));

// erstmal versuchen, dieses Objekt selbst wiederzufinden
CComBSTR bstrMk;
WMoniker mkCont, mk;
HFEATURE hGeom = NULL;		// Handle muß vergeben werden

// Mk's von Feats == Mk's von Feat
WTRiASConnection Conn;

	RETURN_FAILED_HRESULT(FindSpecificParent (DBase, Conn.ppi()));
	RETURN_FAILED_HRESULT(MkGetMoniker (Conn, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mkCont.ppi()));
	RETURN_FAILED_HRESULT(CTRiASFeature::GetFeatureMoniker (NULL, bstrName, mkCont, OLEWHICHMK_OBJFULL, mk.ppi()));
	RETURN_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&bstrMk)));

// wenn Objekt noch nicht existiert, dann geht alles seinen Gang und ein neues Handle wird vergeben
	COM_TRY {
	WTRiASObjectHandleMap Map (g_pDBEngine -> GetFeaturesMap());		// throws hr

		Map -> GetObjectHandle (CComVariant(bstrMk), NULL, OBJECTMAPMODE_GetObjectHandle, (INT_PTR *)&hGeom);
	} COM_CATCH;

// Feature evtl. aus der Objects-Map holen
WTRiASFeature Feat;
WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbFeatureMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
CInitializeGeoFeature InitFeat (bstrName, rgType, App, Parent);
HRESULT hr = FindInMapOrCreateObject(Map, (INT_PTR &)hGeom, Feat, CLSID_TRiASSimpleGeoFeature, InitFeat);

	if (S_OK == hr) {		// S_FALSE heißt: Objekt existiert bereits
		RETURN_FAILED_HRESULT(Feat -> put_Handle ((INT_PTR)hGeom));
	}
#if defined(_DEBUG)
	else if (S_FALSE == hr) {
	// versuchen, zu überprüfen, ob es wirklich das geforderte Objekt ist
	INT_PTR hGeomDeb = 0L;

		RETURN_FAILED_HRESULT(Feat -> get_Handle (&hGeomDeb));
		_ASSERTE(hGeom == hGeomDeb);

	CComBSTR bstrNameDeb;

		RETURN_FAILED_HRESULT(Feat -> get_Name (CLEARED(&bstrNameDeb)));
		_ASSERTE(!wcscmp (bstrName, bstrNameDeb));

	CComBSTR bstrMkDeb;
	WMoniker mkDeb;

		RETURN_FAILED_HRESULT(MkGetMoniker (Feat, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mkDeb.ppi()));
		RETURN_FAILED_HRESULT(MkGetDisplayName (mkDeb, CLEARED(&bstrMkDeb)));
		_ASSERTE(!wcscmp (bstrMk, bstrMkDeb));
	}
#endif // defined(_DEBUG)
	else if (FAILED(hr)) {
		RETURN_FAILED_HRESULT(hr);
	}

	RETURN_FAILED_HRESULT(BaseFeats -> _Add (Feat, VARIANT_TRUE));		// liefert S_FALSE, wenn bereits existent
	return hr;
}

STDMETHODIMP CTRiASSimpleGeoFeatures::SetupFeatures(IDispatch *pIObjs, SETUPFEATURESMODE rgMode)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// TRiAS-Datenbanken haben z.Zt. nur eine Geometrie je Objekt
	COM_TRY {
	FEATURETYPE rgType = (FEATURETYPE)(FEATURETYPE_Object | DATATYPE_FROM_VT(VT_ARRAY|VT_UI1) | FEATURETYPE_IsPrimaryFeature | FEATURETYPE_IsGlobal);

		THROW_FAILED_HRESULT(GetOrCreateObject (CComBSTR(g_bstrGeometry), rgType));
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CTRiASSimpleGeoFeatures::OnChangedName()
{
	return S_OK;
}

HRESULT CTRiASSimpleGeoFeatures::OnChangedDescription()
{
	return S_OK;
}

HRESULT CTRiASSimpleGeoFeatures::OnChangedHandle()
{
	return S_OK;
}

