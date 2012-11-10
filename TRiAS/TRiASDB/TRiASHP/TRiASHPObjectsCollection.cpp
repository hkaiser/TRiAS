// $Header: $
// Copyright� 1998-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.05.2000 19:36:40 
//
// This file was generated by the TRiASDB Data Server Wizard V1.02.086 (#HK000510)
//
// @doc
// @module TRiASHPObjectsCollection.cpp | Implementation of <c CTRiASHPObjectsCollection> class

#include "stdafx.h"

#include "Strings.h"

#include "TRiASHP.h"
#include "TRiASHPDBEngine.h"
#include "TRiASHPObjectsCollection.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Dispatch);
DefineSmartInterface(PersistStreamInit);

DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASObjectsCollection);

/////////////////////////////////////////////////////////////////////////////
// CTRiASHPObjectsCollection

STDMETHODIMP CTRiASHPObjectsCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASObjectsCollection,
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

STDMETHODIMP CTRiASHPObjectsCollection::get_DefaultType (BSTR *pbstrType)
{
	CHECKOUTPOINTER(pbstrType);

CIID Guid (CLSID_TRiASHPObjects);		// DefaultType der _Elemente_ (hier: Objektklasse)!
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen einer neuen Objektklasse
STDMETHODIMP CTRiASHPObjectsCollection::OnCreate (
	VARIANT NameOrHandle, BSTR Type, OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjs)
{
	CHECKOUTPOINTER(ppIObjs);

#if defined(_READWRITE)
// jetzt wirklich erzeugen
CIID ClsId (Type, CIID::INITCIID_InitFromProgId);

	if (!ClsId)	ClsId = CLSID_TRiASHPObjects;	// default ClsId

	RETURN_FAILED_HRESULT(CreateObject (NameOrHandle, rgType, &ClsId, ppIObjs));
	return S_OK;
#else
	return TRIASDB_E_DATABASENOTUPDATABLE;
#endif // defined(_READWRITE)
}

///////////////////////////////////////////////////////////////////////////////
// L�schen einer Objektklasse aus der Datenquelle
STDMETHODIMP CTRiASHPObjectsCollection::OnDelete (VARIANT vWhich)
{
#if defined(_READWRITE)
#pragma TODO("L�schen einer Objektklasse (darf nur was machen, wenn keine Objekte enthalten sind).")
	return S_OK;
#else
	return TRIASDB_E_DATABASENOTUPDATABLE;
#endif // defined(_READWRITE)
}

///////////////////////////////////////////////////////////////////////////////
// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASHPObjectsCollection::OnFinalRelease()
{
	return S_OK;
}

#if defined(_READWRITE)
///////////////////////////////////////////////////////////////////////////////
// Objekt neu erzeugen/wiederverwenden und zur Collection hinzuf�gen
HRESULT CTRiASHPObjectsCollection::CreateObject (
	VARIANT NameOrHandle, DWORD dwType, const CLSID *pClsId, ITRiASObjects **ppIObjs)
{
	USES_CONVERSION;

// diverse Vorbereitungen treffen
WDispatch App;
WDispatch Parent;
WTRiASObjectsCollection BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));

	RETURN_FAILED_HRESULT(BaseObjs -> get_Application (App.ppi()));		// f�r neue Objektklasse
	RETURN_FAILED_HRESULT(BaseObjs -> get_Parent(Parent.ppi()));

// ZugriffsHandle/Namen oder OKS aus NameOrHandle bestimmen
LONG lHandle = 0;
CComVariant v;
bool fHasName = false;
bool fHasOKS = false;
CComBSTR bstrApp, bstrOKS;

	if (VT_BSTR != V_VT(&NameOrHandle) && SUCCEEDED(v.ChangeType (VT_I4, &NameOrHandle)))
		lHandle = V_I4(&v);
	else if (SUCCEEDED(v.ChangeType(VT_BSTR, &NameOrHandle))) {
	// feststellen, obs ein OKS ist, evtl. Namen isolieren
		if (StringIsOKS(V_BSTR(&v), CLEARED(&bstrOKS), CLEARED(&bstrApp))) {
			if (bstrOKS.Length() > 0)
				fHasOKS = true;
		} else 
			bstrApp = V_BSTR(&v);

		if (bstrApp.Length() > 0)
			fHasName = true;
	} else
		return E_INVALIDARG;

// Objektklasse aus Handle/Name/OKS erzeugen
HRESULT hr = S_OK;

	COM_TRY {
	WTRiASObjects Objs (*pClsId);		// zu liefernde Objektklasse erzeugen

	// Objektklasse fertig initialisieren
		THROW_FAILED_HRESULT(WPersistStreamInit(Objs) -> InitNew());
		THROW_FAILED_HRESULT(Objs -> put_Parent (Parent));

	CTRiASHPDatabase *pDB = NULL;
	ULONG ulLayerId = 0L;

		THROW_FAILED_HRESULT(FindSpecificParent (Parent, CLSID_TRiASHPDatabase, (LPVOID *)&pDB));
		THROW_FAILED_HRESULT(pDB -> CreateLayer(OLE2A(bstrApp), &ulLayerId));

	// Objektklasse vervollst�ndigen
		if (fHasName) 	// S_FALSE hei�t: Objekt existiert bereits
			RETURN_FAILED_HRESULT(Objs -> put_Name (bstrApp));
		if (fHasOKS)
			RETURN_FAILED_HRESULT(Objs -> put_OKS (bstrOKS));

	// Typen der Objektklasse setzen
		THROW_FAILED_HRESULT(Objs -> put_CollectionType(OBJECTSCOLLECTIONTYPE(dwType)));
		THROW_FAILED_HRESULT(Objs -> put_Updatable(VARIANT_TRUE));

	// Namen der Standard-Objekteigenschaften (Geometrie und Normal) setzen
		THROW_FAILED_HRESULT(Objs -> put_DefaultGeometry (CComBSTR(g_cbGeometry)));
		THROW_FAILED_HRESULT(Objs -> put_PrimaryKey (CComBSTR(g_cbShapeID)));

		THROW_FAILED_HRESULT(SetPropertyBy (Objs, g_cbObjectsCursor, CComVariant(ulLayerId, VT_I4), true));

	// wenn Objektklasse bereits zu dieser Menge von Objektklassen geh�rt, dann liefert _Add den Wert S_FALSE
		hr = BaseObjs -> _Add (Objs, VARIANT_TRUE);
		if (SUCCEEDED(hr) && NULL != ppIObjs)
			*ppIObjs = Objs.detach();			// evtl. neue/gefundene Objektklasse liefern

	} COM_CATCH;
	return hr;
}
#endif // defined(_READWRITE)
