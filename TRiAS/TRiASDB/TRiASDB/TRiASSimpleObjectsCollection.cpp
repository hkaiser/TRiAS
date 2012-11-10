// @doc 
// @module TRiASSimpleObjectsCollection.cpp | Implementation of <c CTRiASSimpleObjectsCollection> class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>

#include "Strings.h"
#include "Wrapper.h"

#include "TRiASDBEngine.h"
#include "TRiASSimpleObjects.h"
#include "TRiASSimpleObjectsCollection.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASSimpleObjectsCollection, CTRiASSimpleObjectsCollection)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleObjectsCollection

STDMETHODIMP CTRiASSimpleObjectsCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleObjectsCollection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectsCollectionCallback

STDMETHODIMP CTRiASSimpleObjectsCollection::get_DefaultType (BSTR *pbstrType)
{
	TEST_OUT_PARAM(pbstrType);

CIID Guid (CLSID_TRiASSimpleObjects);		// DefaultType der _Elemente_ !
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

// Erzeugen einer neuen Objektklasse
STDMETHODIMP CTRiASSimpleObjectsCollection::OnCreate (
	VARIANT NameOrHandle, BSTR Type, OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjs)
{
	TEST_OUT_PARAM(ppIObjs);

// jetzt wirklich erzeugen
CIID ClsId (Type, CIID::INITCIID_InitFromProgId);

	if (!ClsId)	ClsId = CLSID_TRiASSimpleObjects;	// default ClsId

	RETURN_FAILED_HRESULT(CreateObject (NameOrHandle, rgType, &ClsId, ppIObjs));
	return S_OK;
}

// Löschen einer Objektklasse (darf nur was machen, wenn keine Objekte enthalten sind)
STDMETHODIMP CTRiASSimpleObjectsCollection::OnDelete (VARIANT vWhich)
{
INT_PTR lIdent = 0L;

	if (!V_ISI4(&vWhich)) {
		COM_TRY {
		CComVariant v;

			THROW_FAILED_HRESULT(v.ChangeType (VT_DISPATCH, &vWhich));
			THROW_FAILED_HRESULT(WTRiASSimpleObjects(V_DISPATCH(&v)) -> get_LocalHandle (&lIdent));
		} COM_CATCH;

	} else 
		lIdent = V_I4(&vWhich);

// jetzt wirklich löschen
	ASSERT(0 != lIdent);

HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// existierenden Ident in DB wieder finden
CNativeIdent Ident (hPr, lIdent);
HRESULT hr = Ident.HasObjects();

	if (S_OK == hr)
		hr = E_UNEXPECTED;		// darf nicht passieren
	if (FAILED(hr))
		return hr;

	return Ident.Delete();
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASSimpleObjectsCollection::OnFinalRelease()
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt neu erzeugen/wiederverwenden und zur Collection hinzufügen
HRESULT CTRiASSimpleObjectsCollection::CreateObject (
	VARIANT NameOrHandle, DWORD dwType, const CLSID *pClsId, ITRiASObjects **ppIObjs)
{
WDispatch App;
WDispatch Parent;
WTRiASDatabase DBase;
WTRiASObjectsCollection BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));

	RETURN_FAILED_HRESULT(BaseObjs -> get_Application (App.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_Parent(Parent.ppi()));

	RETURN_FAILED_HRESULT(FindSpecificParent (BaseObjs, DBase.ppi()));

// ZugriffsHandle finden
LONG lIdent = 0;
CComVariant v;
bool fHasName = false;
bool fHasOKS = false;
CComBSTR bstrApp, bstrOKS;

	if (VT_BSTR != V_VT(&NameOrHandle) && SUCCEEDED(v.ChangeType (VT_I4, &NameOrHandle)))
		lIdent = V_I4(&v);
	else if (SUCCEEDED(v.ChangeType(VT_BSTR, &NameOrHandle))) {
		lIdent = g_pDBEngine -> GetNextCookie (CComBSTR(g_cbObjectsMap));
		if (StringIsOKS(V_BSTR(&v), CLEARED(&bstrOKS), CLEARED(&bstrApp))) {
			if (bstrOKS.Length() > 0)
				fHasOKS = true;
		} else 
			bstrApp = V_BSTR(&v);

		if (bstrApp.Length() > 0)
			fHasName = true;
	} else
		return E_INVALIDARG;

// Objektklasse evtl. aus der Objects-Map holen
WTRiASObjects Objs;
WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbObjectsMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
CCreateSimpleObjects CreateObjs (App, Parent);
INT_PTR hObjs = NULL;		// wird vergeben
HRESULT hr = CreateObjectEx (Map, lIdent, hObjs, Objs, *pClsId, CreateObjs);

	if (S_OK == hr) {
		if (fHasName) 	// S_FALSE heißt: Objekt existiert bereits
			RETURN_FAILED_HRESULT(Objs -> put_Name (bstrApp));
		if (fHasOKS)
			RETURN_FAILED_HRESULT(Objs -> put_OKS (bstrOKS));
	}

// wenn Feature bereits zu dieser Objektklasse gehört, dann liefert _Add den Wert S_FALSE
	hr = BaseObjs -> _Add (Objs, VARIANT_TRUE);
	if (SUCCEEDED(hr) && NULL != ppIObjs)
		*ppIObjs = Objs.detach();			// evtl. neue Objektklasse liefern
	return hr;
}

