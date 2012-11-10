// @doc
// @module TRiASObject.cpp | Implementation of CTRiASObject

#include "stdafx.h"

#include <Atl/Ciid.h>

#include "Strings.h"
#include "Wrapper.h"

#include <ChangeValueHelper.h>
#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>
#include <Com/ComBool.h>

#include "TRiASDBEngine.h"
#include "TRiASProperty.h"
#include "TRiASObject.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class if standalone and if aggregated
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASObject);
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(CTRiASObject);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASObject::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASObject, CTRiASObject)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASObject, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);	// WTRiASObjectHandleMap
DefineSmartInterface(OleClientSite);		// WOleClientSite
DefineSmartInterface(BindCtx);				// WBindCtx
DefineSmartInterface(TRiASSimpleObject);	// WTRiASSimpleObject

/////////////////////////////////////////////////////////////////////////////
// CTRiASObject

STDMETHODIMP CTRiASObject::InterfaceSupportsErrorInfo(REFIID riid)
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

void CTRiASObject::FinalRelease()
{
// evtl. aus HandleTabellen entfernen
	if (NULL != m_hObject) {
		COM_TRY {
		// aus globaler Tabelle entfernen
		WTRiASObjectHandleMap MapG (g_pDBEngine -> GetObjectMap());		// throws hr

			VERIFY(S_OK == MapG -> RemoveObject ((LONG)m_hObject, OBJECTMAPMODE_RemoveThisReference));

		// aus Database-Tabelle entfernen
//			if (m_Parent != NULL) {
//			WTRiASObjectHandleMap MapP (GetPropertyFrom (m_Parent, g_cbObjectMap, (IDispatch *)NULL), false);
//
//				_ASSERTE(MapP.IsValid());
//				if (MapP.IsValid()) 
//					VERIFY(S_OK == MapP -> RemoveObject ((LONG)m_hObject, OBJECTMAPMODE_RemoveAllReferences));
//			}
			m_hObject = NULL;

		} COM_CATCH_IGNORE;
	}
	_ASSERTE(NULL == m_hObject);

// sonstige Aufräumarbeiten
	FreePropertiesCollection();

// PropertySupportObjekte freigeben
	ReleasePropertySupportObjects();

	if (m_Features.IsValid() && 0 != m_dwFeatCookie) {
		m_Features -> SetEventSink (GetUnknown(), &m_dwFeatCookie, VARIANT_FALSE);
		m_Features -> putref_RelatedObject(NULL);
	}
	m_Features.Assign(NULL);

	if (m_GeometryFeatures.IsValid() && 0 != m_dwGeoFeatCookie) {
		m_GeometryFeatures -> SetEventSink (GetUnknown(), &m_dwGeoFeatCookie, VARIANT_FALSE);
		m_GeometryFeatures -> putref_RelatedObject(NULL);
	}
	m_GeometryFeatures.Assign(NULL);

	m_Parent = NULL;
	m_Application = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Properties dieses Objektes

STDMETHODIMP CTRiASObject::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASObject::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASObject::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_Application");

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASObject::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// das Nullsetzen des Parent wird als Signal zum Freigeben gewertet
// evtl. alle SubObjekte von ihrem Bezug abhängen
	if (NULL == newVal) {
	// evtl. abhängiges Objekt benachrichtigen
		if (m_pICallback) 
			m_pICallback -> OnFinalRelease();

	// aus Database-Tabelle entfernen
		_ASSERTE(NULL != (IDispatch *)m_Parent);
//		COM_TRY {
//		WDispatch Parent;
//
//			if (SUCCEEDED(FindSpecificParent (oldParent, IID_ITRiASDatabase, Parent.ppv()))) {
//			WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);
//
//				if (Map.IsValid()) 
//					Map -> RemoveObject ((LONG)m_hObject, OBJECTMAPMODE_RemoveAllReferences);
//			}
//		} COM_CATCH;

	// Properties freigeben
		FreePropertiesCollection();

	// PropertySupportObjekte freigeben
		ReleasePropertySupportObjects();

	// Feature-Objekte freigeben
		if (m_Features.IsValid() && 0 != m_dwFeatCookie) {
			m_Features -> SetEventSink (GetUnknown(), &m_dwFeatCookie, VARIANT_FALSE);
			m_Features -> putref_RelatedObject(NULL);
		}
		m_Features.Assign(NULL);

		if (m_GeometryFeatures.IsValid() && 0 != m_dwGeoFeatCookie) {
			m_GeometryFeatures -> SetEventSink (GetUnknown(), &m_dwGeoFeatCookie, VARIANT_FALSE);
			m_GeometryFeatures -> putref_RelatedObject(NULL);
		}
		m_GeometryFeatures.Assign(NULL);
	}

	m_Parent = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASObject::get_Type(OBJECTTYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_Type");

	*pVal = m_rgType;
	return S_OK;
}

STDMETHODIMP CTRiASObject::put_Type(OBJECTTYPE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (OBJECTTYPE_Unknown != m_rgType && OBJECTTYPE_Unknown == newVal)
		return E_INVALIDARG;

	_ASSERTE(OBJECTTYPE_Unknown == m_rgType || (m_rgType & newVal && 1 == BitCount(newVal)));	// Objekttyp ist nicht modifizierbar
	if (OBJECTTYPE_Unknown != m_rgType && (newVal & m_rgType) != newVal)
		return E_UNEXPECTED;		// nur einmal rufen (während der Initialisiereung)

	COM_TRY {
	CChangeValueHelper<OBJECTTYPE> Helper (m_rgType, newVal);

		if (!Helper) {
		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDOBJECT_Type, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchführen
			}

			THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen

			if (m_pICallback && !fModify && S_OK == hr)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECT_Type, Helper.GetOldValue()));

			m_fIsDirty = true;
			Helper.SetValid();
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObject::put_Name(BSTR newVal)
{
	COM_TRY {
	CComBSTR bstr (newVal);

		if (m_bstrName.Length() > 0 || 0 == bstr.Length()) 
			return S_OK;		// nothing to do

	CChangeValueHelper<CComBSTR> Helper (m_bstrName, bstr);

		if (!Helper) {
		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDOBJECT_Name, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchführen
			}

			THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen

			if (m_pICallback && !fModify && S_OK == hr)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECT_Name, Helper.GetOldValue()));

			m_fIsDirty = true;
			Helper.SetValid();
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObject::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_Name");

CComBSTR bstrName (m_bstrName);

	if (!bstrName)
		return E_OUTOFMEMORY;
	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASObject::get_Handle (INT_PTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_Handle");

	if (NULL == m_hObject) 
		EnsureObjectHandle (OBJECTMAPMODE_CreateObjectHandle);
	*pVal = (LONG)m_hObject;
	return S_OK;
}

STDMETHODIMP CTRiASObject::put_Handle (INT_PTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == m_hObject) {
		m_hObject = (HOBJECT)newVal;

	// bei manchen Datenbanken sind die vergebenen Handles bereits eindeutig
	WTRiASDatabase DBase;
	CComBool fObjectHandleIsValid = VARIANT_FALSE;

		if (SUCCEEDED(FindSpecificParent (m_Parent, DBase.ppi()))) 
			fObjectHandleIsValid = GetPropertyFrom (DBase, g_cbObjectHandleIsValid, VARIANT_FALSE);

		if (!fObjectHandleIsValid)
			EnsureObjectHandle (OBJECTMAPMODE(OBJECTMAPMODE_CreateObjectHandle|OBJECTMAPMODE_UsePredefinedHandle));
		return S_OK;
	}
	return S_FALSE;		// Zugriffsnummer wurde bereits vergeben
}

HRESULT CTRiASObject::EnsureObjectHandle (OBJECTMAPMODE rgMode)
{
// erstes Mal benötigt
	COM_TRY {
	WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());		// throws hr
	CComBSTR bstrName;

	// TRiAS-Objekte benötigen den Namen nicht zu ihrer Identifikation
	WTRiASSimpleObject SimpleObj;

		if (rgMode & OBJECTMAPMODE_UsePredefinedHandle &&
			SUCCEEDED(GetUnknown() -> QueryInterface (SimpleObj.ppi()))) 
		{
			SetType (rgMode, OBJECTMAPMODE_NameDoesNotIdentifyObject);
			bstrName = m_bstrName;		// aus Analogiegründen
		} 
		else {
		// Moniker-DisplayName generieren
			if (FAILED(GetMkName (CLEARED(&bstrName)))) {
				bstrName = g_cbMkObjectDef;
				bstrName.Append(g_cbColon);
				bstrName.Append(m_bstrName);
				bstrName.Append(g_cbColon);
				bstrName.Append(CComBSTR(CIID()));	// eindeutigen Namen erzeugen
			}
			if (!bstrName)
				_com_issue_error(E_OUTOFMEMORY);
		}
		_ASSERTE(sizeof(LONG) == sizeof(HOBJECTS));
		THROW_FAILED_HRESULT(Map -> GetObjectHandle (CComVariant(bstrName), GetUnknown(), rgMode, (INT_PTR *)&m_hObject));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObject::get_ObjectsHandle (INT_PTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_ObjectsHandle");

	*pVal = (LONG)m_hObjects;
	return S_OK;
}

STDMETHODIMP CTRiASObject::put_ObjectsHandle (INT_PTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_hObjects = (HOBJECTS)newVal;
	return S_OK;
}

STDMETHODIMP CTRiASObject::Delete()
{
HRESULT hr = S_FALSE;

	if (NULL != m_pICallback)
		hr = m_pICallback -> OnDelete();	// das Objekt selbst arbeiten lassen

	if (SUCCEEDED(hr)) {
	// alle sonstigen Referenzen freigeben
		if (NULL != m_pICallback)
			m_pICallback -> OnFinalRelease();
		FinalRelease();								
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// liefert vollständigen DisplayName dieses Objektes

HRESULT CTRiASObject::GetMkName (BSTR *pbstrMkName)
{
	COM_TRY {
	// dem aggregierenden Objekt die Chance geben, den Moniker zu berechnen
	WMoniker mk;

		THROW_FAILED_HRESULT(MkGetMoniker (GetControllingUnknown(), OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
		THROW_FAILED_HRESULT(MkGetDisplayName (mk, pbstrMkName));

	} COM_CATCH;
	return S_OK;
}

// Moniker des zugeordneten Containers liefern
HRESULT CTRiASObject::GetContainerMoniker (IMoniker **ppIMk)
{
	COM_TRY {
	WTRiASConnection Parent;
	WMoniker mk;

		THROW_FAILED_HRESULT(FindSpecificParent(m_Parent, Parent.ppi()));
		THROW_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mk.ppi()));
		*ppIMk = mk.detach();

	} COM_CATCH;
	return S_OK;
}

// Den vollständigen Moniker dieses Objektes liefern
HRESULT CTRiASObject::GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk)
{
	COM_TRY {
	WMoniker mk, mkThis, mkItem;
	CComBSTR bstrItem (g_cbMkObjectDef);	// "!MkObjectDef:<Object Name>"

		bstrItem.Append (g_cbColon);

		_ASSERTE(!!m_bstrName && 0 < m_bstrName.Length());
		bstrItem.Append (m_bstrName);

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

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASObject::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == Property)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::CreateProperty");

	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_CreatingProperty (bstrName, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToCreate (bstrName));

	// eigentliche Aktion
	CComObject<CTRiASProperty> *pNew = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASProperty>::CreateInstance (&pNew));

	WTRiASPropertyCallback Supp;
	WTRiASProperty Prop (pNew);		// required AddRef;

		THROW_FAILED_HRESULT(pNew -> put_Name (bstrName));
		THROW_FAILED_HRESULT(GetPropertySupportSite (bstrName, GetUnknown(), NULL, Supp.ppi()));
		THROW_FAILED_HRESULT(pNew -> SetSite (Supp));	// using IObjectWithSite
		*Property = Prop.detach();

	// Events hinterher
		THROW_FAILED_HRESULT(Fire_PropertyCreated (*Property));
		m_fIsDirty = true;

	} COM_CATCH;
	return S_OK;
}

// Props zeigt auf einen bereits existierenden Enumerator und wird durch 
// diese Funktion lediglich mit allen Properties gefüllt.
STDMETHODIMP CTRiASObject::RemoveProperty (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_DeletingProperty (bstrName, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToDelete (bstrName));

// eigentliche Aktion
HRESULT hr = E_FAIL;

	RETURN_FAILED_HRESULT(hr = ReleasePropertySupportSite (bstrName));	// zuständiges Objekt freigeben

// Event hinterher
	if (S_OK == hr) {
		m_fIsDirty = true;
		RETURN_FAILED_HRESULT(Fire_PropertyDeleted (bstrName));
	}
	return hr;		// S_FALSE heißt: nicht gefunden
}

STDMETHODIMP CTRiASObject::get_DatabaseHandle(INT_PTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

WTRiASDatabase DBase;

	if (SUCCEEDED(FindSpecificParent (m_Parent, DBase.ppi()))) 
	{
		RETURN_FAILED_HRESULT(DBase -> get_Handle (pVal));
	}
	return S_OK;
}

STDMETHODIMP CTRiASObject::get_Features(ITRiASFeatures **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_Features");

// evtl. Features initialisieren lassen
	if (!m_Features.IsValid()) {
		_ASSERTE(NULL != m_pICallback);		// Callbackinterface muß gesetzt sein

	HRESULT hr = m_pICallback -> SetupFeatures (
		SETUPFEATURESMODE(SETUPFEATURESMODE_Normal|SETUPFEATURESMODE_Force));

		if (FAILED(hr)) {
			if (E_NOTIMPL != hr)
				return hr;			// sonstiger Fehler

		// nicht alle Objekte können das, Objekteigenschaften von Objektklasse
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());
		WTRiASObjects Objs;
		WTRiASFeatures Feats;

			_ASSERTE(NULL != m_hObjects);
			RETURN_FAILED_HRESULT(Map -> GetObject ((INT_PTR)m_hObjects, Objs.ppu()));
			RETURN_FAILED_HRESULT(Objs -> get_Features (Feats.ppi()));
			RETURN_FAILED_HRESULT(put_Features (Feats));
		}
	}

	_ASSERTE(m_Features.IsValid());
	if (m_Features.IsValid()) {
	WTRiASFeatures Feats (m_Features);

		*pVal = Feats.detach();
		return S_OK;
	}
	return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASObject::get_Features");
}

STDMETHODIMP CTRiASObject::get_GeometryFeatures(ITRiASFeatures **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObject::get_GeometryFeatures");

// evtl. Features initialisieren lassen
	if (!m_GeometryFeatures.IsValid()) {
		_ASSERTE(NULL != m_pICallback);		// Callbackinterface muß gesetzt sein

	HRESULT hr = m_pICallback -> SetupFeatures (
		SETUPFEATURESMODE(SETUPFEATURESMODE_Normal|SETUPFEATURESMODE_Force));

		if (FAILED(hr)) {
			if (E_NOTIMPL != hr)
				return hr;			// sonstiger Fehler

		// nicht alle Objekte können das, Objekteigenschaften von Objektklasse
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());
		WTRiASObjects Objs;
		WTRiASFeatures GeoFeats;

			_ASSERTE(NULL != m_hObjects);
			RETURN_FAILED_HRESULT(Map -> GetObject ((INT_PTR)m_hObjects, Objs.ppu()));
			RETURN_FAILED_HRESULT(Objs -> get_GeometryFeatures (GeoFeats.ppi()));
			RETURN_FAILED_HRESULT(put_GeometryFeatures(GeoFeats));
		}
	}

	_ASSERTE(m_GeometryFeatures.IsValid());
	if (m_GeometryFeatures.IsValid()) {
	WTRiASFeatures Feats (m_GeometryFeatures);

		*pVal = Feats.detach();
		return S_OK;
	}
	return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASObject::get_GeometryFeatures");
}

HRESULT CTRiASObject::BindNewFeatures (WTRiASFeatures &rFeats, ITRiASFeatures *pIFeats, DWORD *pdwCookie)
{
// neue Properties erst bei der alten Objektmenge abmelden, dann hier anmelden
	COM_TRY {
	WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());
	WUnknown Objs;

		_ASSERTE(NULL != m_hObjects);
		THROW_FAILED_HRESULT(Map -> GetObject ((INT_PTR)m_hObjects, Objs.ppi()));

	// bisherige Features loslassen
		if (rFeats.IsValid()) {
			rFeats -> SetEventSink (Objs, pdwCookie, VARIANT_FALSE);

		WDispatch Disp;

			THROW_FAILED_HRESULT(rFeats -> get_RelatedObject(Disp.ppi()));
			if (Disp.IsValid() && Disp == WUnknown(GetUnknown()))
				rFeats -> putref_RelatedObject(NULL);
			rFeats.Assign(NULL);
		}
		if (NULL == pIFeats)		// ist i.O.; Features sollen nur zerlegt werden
			return S_OK;

		THROW_FAILED_HRESULT(pIFeats -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pIFeats -> put_Parent (WDispatch(Objs)));

//		THROW_FAILED_HRESULT(pIFeats -> SetEventSink (NULL, pdwCookie, VARIANT_FALSE));
		THROW_FAILED_HRESULT(pIFeats -> SetEventSink (Objs, pdwCookie, VARIANT_TRUE));

	WDispatch Disp;

		THROW_FAILED_HRESULT(pIFeats -> get_RelatedObject(Disp.ppi()));
		if (!Disp.IsValid()) {
		// related Object nur setzen, wenn noch keins da ist (#HK011127)
			THROW_FAILED_HRESULT(pIFeats -> putref_RelatedObject(GetDispatch()));
		}

	} COM_CATCH;

	rFeats = pIFeats;
	return S_OK;
}

STDMETHODIMP CTRiASObject::put_Features(ITRiASFeatures *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL != newVal)
	{
		RETURN_FAILED_HRESULT(newVal -> put_FeaturesType (FEATURESTYPE_Attributes));
	}
	RETURN_FAILED_HRESULT(BindNewFeatures (m_Features, newVal, &m_dwFeatCookie));	// newVal darf NULL sein !
	return S_OK;
}

STDMETHODIMP CTRiASObject::put_GeometryFeatures(ITRiASFeatures *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL != newVal)
	{
		RETURN_FAILED_HRESULT(newVal -> put_FeaturesType (FEATURESTYPE_Geometries));
	}
	RETURN_FAILED_HRESULT(BindNewFeatures (m_GeometryFeatures, newVal, &m_dwGeoFeatCookie));	// newVal darf NULL sein !
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IOleObject
STDMETHODIMP CTRiASObject::GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
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

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASObject::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return TRIASDB_E_INVALID_PARAMETER;

	*pClassID = CLSID_TRiASObject;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CTRiASObject::SaveObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObject::SaveObject");
}

STDMETHODIMP CTRiASObject::GetContainer (IOleContainer **ppContainer)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObject::GetContainer");
}

STDMETHODIMP CTRiASObject::ShowObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObject::ShowObject");
}

STDMETHODIMP CTRiASObject::OnShowWindow (BOOL fShow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObject::OnShowWindow");
}

STDMETHODIMP CTRiASObject::RequestNewObjectLayout()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObject::RequestNewObjectLayout");
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASObject::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASObject::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

long lSignature = 0L;

	THROW_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (OBJECT_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
	if ((lVersion & ~OBJECT_VERSION_MINOR_MASK) > LASTKNOWN_OBJECT_VERSION)
		return TRIASDB_W_NEWEROBJECT;

	m_bstrName.Empty();
	RETURN_FAILED_HRESULT(m_bstrName.ReadFromStream (pStm));	// Name
	_ASSERTE(sizeof(long) == sizeof(OBJECTTYPE));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)m_rgType));	// Objekttyp

// MonikerDisplayName einlesen, um Parent wiederzufinden
WMoniker mk;

	RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_IMoniker, mk.ppv()));
	RETURN_FAILED_HRESULT(::BindMoniker (mk, NULL, IID_IDispatch, (LPVOID *)&m_Parent));

// Aggregat davon in Kenntnis setzen
	if (NULL != m_pICallback)
		m_pICallback -> SetupObject (SETUPOBJECTMODE_InitOrLoad);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASObject::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Formatversion schreiben
	RETURN_FAILED_HRESULT(SaveLong(pStm, OBJECT_SIGNATURE));
	RETURN_FAILED_HRESULT(SaveLong(pStm, LASTKNOWN_OBJECT_VERSION));

// eigene Eigenschaften wegschreiben
	RETURN_FAILED_HRESULT(m_bstrName.WriteToStream (pStm));		// Name
	RETURN_FAILED_HRESULT(SaveLong (pStm, (long &)m_rgType));	// Objekttypen

// Moniker des Containers dieses Objektes wegschreiben
WMoniker mk;

	RETURN_FAILED_HRESULT(GetContainerMoniker (mk.ppi()));
	RETURN_FAILED_HRESULT(::OleSaveToStream (WPersistStream(mk), pStm));

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASObject::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return TRIASDB_E_INVALID_PARAMETER;

WMoniker mk;

	RETURN_FAILED_HRESULT(GetContainerMoniker (mk.ppi()));		// ignore errors
	RETURN_FAILED_HRESULT(WPersistStream(mk) -> GetSizeMax (pcbSize));

	pcbSize -> QuadPart += LenForStream(m_bstrName) + 3*sizeof(long);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit

STDMETHODIMP CTRiASObject::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

// Aggregat davon in Kenntnis setzen
	if (NULL != m_pICallback)
		m_pICallback -> SetupObject (SETUPOBJECTMODE_InitOrLoad);

	m_fIsDirty = false;	
	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectCallback

STDMETHODIMP CTRiASObject::putref_ObjectCallback(ITRiASObjectCallback * pICB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pICallback = pICB;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureEvents
STDMETHODIMP CTRiASObject::CreatingFeature (VARIANT NameOrHandle, VARIANT_BOOL *pVal)
{
	return Fire_CreatingFeature (NameOrHandle, pVal);
}

STDMETHODIMP CTRiASObject::FeatureToCreate (VARIANT NameOrHandle)
{
	return Fire_FeatureToCreate (NameOrHandle);
}

STDMETHODIMP CTRiASObject::FeatureCreated (IDispatch *pIFeature)
{
	m_fIsDirty = true;
	return Fire_FeatureCreated (pIFeature);
}

STDMETHODIMP CTRiASObject::ModifyingFeature (IDispatch *pIFeature, VARIANT_BOOL *pVal)
{
	return Fire_ModifyingFeature (pIFeature, pVal);
}

STDMETHODIMP CTRiASObject::FeatureToModify (IDispatch *pIFeature)
{
	return Fire_FeatureToModify (pIFeature);
}

STDMETHODIMP CTRiASObject::FeatureModified (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_FeatureModified (Name);
}

STDMETHODIMP CTRiASObject::DeletingFeature (IDispatch *pIFeature, VARIANT_BOOL *pVal)
{
	return Fire_DeletingFeature (pIFeature, pVal);
}

STDMETHODIMP CTRiASObject::FeatureToDelete (IDispatch *pIFeature)
{
	return Fire_FeatureToDelete (pIFeature);
}

STDMETHODIMP CTRiASObject::FeatureDeleted (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_FeatureDeleted (Name);
}
