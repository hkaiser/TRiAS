// TRiASFeatures.cpp : Implementation of CTRiASFeatures

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>

#include "Wrapper.h"
#include "Strings.h"

#include "TRiASFeatures.h"
#include "MakeEnumVariant.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class if standalone and if aggregated
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASFeatures);
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(CTRiASFeatures);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASFeatures::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASFeatures, CTRiASFeatures)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASFeatures, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASFeatures);
DefineSmartInterface(TRiASFeatureEvents);

/////////////////////////////////////////////////////////////////////////////
// CTRiASFeatures

STDMETHODIMP CTRiASFeatures::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASFeatures,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//
HRESULT CTRiASFeatures::FinalConstruct (void)
{
	return CreateNewEnum(m_Enum.ppi());
}

void CTRiASFeatures::FinalRelease()
{
	m_Enum.Assign(NULL);	// Enumerator freigeben
	m_pIParent = NULL;
	m_Application = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASFeatures::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::get_Application");

	*pVal = m_pIParent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASFeatures::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

#if defined(_DEBUG)
// Parent muß entweder TRiASObject oder TRiASObjects sein
WUnknown Unk;

	_ASSERTE(NULL == newVal ||
		   SUCCEEDED(newVal -> QueryInterface(IID_ITRiASObjects, Unk.ppv())) || 
		   SUCCEEDED(newVal -> QueryInterface(IID_ITRiASObject, Unk.ppv())) ||
		   SUCCEEDED(newVal -> QueryInterface(IID_ITRiASDatabase, Unk.ppv())));
#endif // _DEBUG

	if (NULL == newVal) {
	// evtl. abhängiges Objekt benachrichtigen
		if (m_pICallback) 
			m_pICallback -> OnFinalRelease();

	// Enumerator bzw. TRiASFeature's freigeben
		if (m_Enum.IsValid()) {
		WTRiASFeature Feat;

			for (m_Enum -> Reset(); S_OK == m_Enum -> Next (1, &Feat, NULL); /**/)
			{
				Feat -> put_Parent (NULL);
			}
			m_Enum.Assign(NULL);
		}
	}

	m_pIParent = newVal;		// no AddRef !
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::get_Count");

	_ASSERTE(sizeof(LONG) == sizeof(ULONG));	// verify safeness of the following cast
	return m_Enum -> Count((ULONG *)pVal);
}

IMPLEMENT_PROPERTY_ACCESS(CTRiASFeatures, FeaturesType, FEATURESTYPE);

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CTRiASFeatures::_Add(ITRiASFeature *pFeature, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// testen, ob dieses Objekt noch nicht in der collection enthalten ist
CComBSTR bstrName;

    pFeature->get_Name(&bstrName);
	_ASSERTE(IsFirstOccurence (m_Enum, pFeature, ITRiASFeature::get_Name, (CComBSTR *)NULL));

	if (fFullAdd) {
		RETURN_FAILED_HRESULT(pFeature -> put_Application (m_Application));
		RETURN_FAILED_HRESULT(pFeature -> put_Parent (m_pIParent));
	}

// Feststellen, ob dieses Feature bereits vertreten ist
CComBSTR bstr;
WTRiASFeature Item;

	RETURN_FAILED_HRESULT(pFeature -> get_Name(CLEARED(&bstr)));
	if (S_OK == m_Enum -> FindItem (bstr, &Item)) 
		return S_FALSE;		// Item existiert bereits
	return m_Enum -> AddItem (bstr, pFeature);
}

HRESULT CTRiASFeatures::RemoveFeature(ITRiASFeature *pIFeature)
{
CComBSTR bstrName;

	RETURN_FAILED_HRESULT(pIFeature -> get_Name (CLEARED(&bstrName)));
#if defined(_DEBUG)
HRESULT hr = m_Enum -> RemoveItem (bstrName);

	if (S_OK != hr) {
	FEATURETYPE rgType = FEATURETYPE_Unknown;

		RETURN_FAILED_HRESULT(pIFeature -> get_Type (&rgType));

	bool fIsFeatGeometry = (VT_FROM_DATATYPE(rgType) == (VT_ARRAY|VT_UI1)) ? true : false;
	bool fIsFeatsGeometry = (m_FeaturesType == FEATURESTYPE_Geometries) ? true : false;

		_ASSERTE(fIsFeatGeometry  != fIsFeatsGeometry);	// Remove darf nur fehlschlagen, wenn Typen nicht stimmen
	}
#else
	m_Enum -> RemoveItem (bstrName);
#endif // _DEBUG

	return S_OK;
}

HRESULT CTRiASFeatures::RemoveFeature(BSTR bstrName, ITRiASFeature *pIFeature)
{
#if defined(_DEBUG)
HRESULT hr = m_Enum -> RemoveItem (bstrName);

	if (S_OK != hr) {
	FEATURETYPE rgType = FEATURETYPE_Unknown;

		RETURN_FAILED_HRESULT(pIFeature -> get_Type (&rgType));

	bool fIsFeatGeometry = (VT_FROM_DATATYPE(rgType) == (VT_ARRAY|VT_UI1)) ? true : false;
	bool fIsFeatsGeometry = (m_FeaturesType == FEATURESTYPE_Geometries) ? true : false;

		_ASSERTE(fIsFeatGeometry  != fIsFeatsGeometry);	// Remove darf nur fehlschlagen, wenn Typen nicht stimmen
	}
#else
	m_Enum -> RemoveItem (bstrName);
#endif // _DEBUG

	return S_OK;
}

STDMETHODIMP CTRiASFeatures::get_RelatedObject(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::get_RelatedObjects");

WDispatch disp (m_pIRelDisp);

	*pVal = disp.detach();
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::putref_RelatedObject(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pIRelDisp = newVal;		// no AddRef!
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASFeatures::Add(VARIANT NameOrHandle, BSTR Type, FEATURETYPE rgType, ITRiASFeature **ppIFeature)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIFeature) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::Add");

// Erzeugen einer neuen ViewItem und hinzufügen zur Collection
	COM_TRY {
	// Überprüfen, ob Feature bereits existiert
	WTRiASFeature FeatItem;

		if (S_OK == Item (NameOrHandle, FeatItem.ppi())) {
			*ppIFeature = FeatItem.detach();
			return S_FALSE;		// existiert bereits
		}

	// darf erzeugt werden ?
	VARIANT_BOOL fCreate = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Fire_CreatingFeature (NameOrHandle, &fCreate));
		if (fCreate != VARIANT_FALSE)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_FeatureToCreate (NameOrHandle));

		if (NULL != m_pICallback)	// das eigentliche Objekt arbeiten lassen
			THROW_FAILED_HRESULT(m_pICallback -> OnCreate (NameOrHandle, Type, rgType, FeatItem.ppi()));

	// erfolgreich erzeugt
		THROW_FAILED_HRESULT(Fire_FeatureCreated (FeatItem));
		*ppIFeature = FeatItem.detach();

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASFeatures::Item(VARIANT Index, ITRiASFeature **ppIFeature)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIFeature) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::Item");

CComVariant vIndex;
bool fFound = false;

	*ppIFeature = NULL;
	COM_TRY {
	WTRiASFeature Feature;
	WEnumWTRiASFeature Enum;
	INT_PTR hFeatToFind = NULL;

	// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
		if (VT_I4 == V_VT(&Index)) {
		// Handle ist direkt gegeben
			hFeatToFind = V_I4(&Index);
		}
		else if (VT_DISPATCH == V_VT(&Index) || VT_UNKNOWN == V_VT(&Index)) {
		// Objekt ist direkt gegeben
			Feature = V_DISPATCH(&Index);
			THROW_FAILED_HRESULT(Feature -> get_Handle (&hFeatToFind));
		} 
		else if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) 
			hFeatToFind = V_I4(&vIndex);

		if (NULL != hFeatToFind) {
		// Feature über sein Handle suchen
//			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		CLockEnum<TEnumWTRiASFeature::threadmodel_t> Sync(
			*dynamic_cast<TEnumWTRiASFeature *>(m_Enum.p) -> get_sync_object());

			for (m_Enum -> Reset(); S_OK == m_Enum -> Next (1, &Feature, NULL); /**/)
			{
			INT_PTR lHandle = NULL;

				THROW_FAILED_HRESULT(Feature -> get_Handle (&lHandle));
				if (lHandle == hFeatToFind) {
					*ppIFeature = Feature.detach();
					fFound = true;
				}
			}
		} 
		else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {
		// Feature über seinen Namen suchen

		// Kurztext nur dann vergleichen, wenn dieser nicht der DefaultGenerierte ist
		VARIANT_BOOL fNameIsDefault = GetPropertyFrom (Feature, g_cbNameIsDefault, VARIANT_FALSE);

			if (!fNameIsDefault && SysStringLen(V_BSTR(&vIndex)) > 0) {
				if (S_OK == m_Enum -> FindItem (CComBSTR(V_BSTR(&vIndex)), &Feature)) {
					*ppIFeature = Feature.detach();
					fFound = true;
				}
			}
		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::Item");

	} COM_CATCH;

	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_FEATURE);

	return S_OK;
}

STDMETHODIMP CTRiASFeatures::Remove(VARIANT Index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

HRESULT hr_return = S_OK;

	COM_TRY {
	// darf gelöscht werden ?
	VARIANT_BOOL fDelete = VARIANT_FALSE;
	WEnumWTRiASFeature Enum;
	WTRiASFeature Feature;

	CComVariant vIndex;
	CComBSTR bstrName;

		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
		// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(m_Enum -> Clear());

		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Feature, NULL); /**/)
			{
			INT_PTR lHandle = NULL;

				THROW_FAILED_HRESULT(Feature -> get_Handle (&lHandle));
				THROW_FAILED_HRESULT(Feature -> get_Name (CLEARED(&bstrName)));
				if (lHandle == V_I4(&vIndex)) {
					THROW_FAILED_HRESULT(Fire_DeletingFeature (Feature, &fDelete));
					if (fDelete == VARIANT_FALSE) {
					CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes löschen verhindern

						THROW_FAILED_HRESULT(Fire_FeatureToDelete (Feature));

						if (m_pICallback)	// evtl. in Datenquelle löschen
							THROW_FAILED_HRESULT(m_pICallback -> OnDelete (Index));

					// erfolgreich gelöscht
						THROW_FAILED_HRESULT(Fire_FeatureDeleted (bstrName));
						continue;
					}
				// wenn nicht gelöscht werden soll, dann einfach durchfallen
				// ...
					hr_return = S_FALSE;
				} 
				THROW_FAILED_HRESULT(m_Enum -> AddItem(bstrName, Feature));
			}

#if defined(_DEBUG)
		ULONG ulCntDeb = 0L;
		ULONG ulCntDebN = 0L;

			THROW_FAILED_HRESULT(m_Enum -> Count (&ulCntDeb));
			THROW_FAILED_HRESULT(Enum -> Count (&ulCntDebN));
			_ASSERTE(0 == ulCntDebN || ulCntDebN == ulCntDeb + 1);
#endif // _DEBUG

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {
		// das gewünschte herauslöschen
			THROW_FAILED_HRESULT(Fire_DeletingFeature (Feature, &fDelete));
			if (fDelete != VARIANT_FALSE) 
				return S_FALSE;		// soll nicht gelöscht werden
			{
			CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes löschen verhindern

				THROW_FAILED_HRESULT(Fire_FeatureToDelete (Feature));
			}
			VERIFY(S_OK == m_Enum -> RemoveItem (CComBSTR(V_BSTR(&vIndex))));
			bstrName = V_BSTR(&vIndex);

			if (m_pICallback)	// evtl. in Datenquelle löschen
				THROW_FAILED_HRESULT(m_pICallback -> OnDelete (vIndex));

		// erfolgreich gelöscht
			THROW_FAILED_HRESULT(Fire_FeatureDeleted (bstrName));
		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::Item");

	} COM_CATCH;
	return hr_return;
}

STDMETHODIMP CTRiASFeatures::_NewEnum (IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::_NewItem");

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASFeatures::_Clone(ITRiASFeatures **ppIFeatures)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIFeatures) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::_Clone");

CComObject<CTRiASFeatures> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASFeatures>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));

		THROW_FAILED_HRESULT(pNew -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pNew -> put_Parent (m_pIParent));

	WTRiASFeatures Features (pNew);		// pending AddRef

		*ppIFeatures = Features.detach();

	} COM_CATCH_OP(delete pNew);

	return S_OK;
}

STDMETHODIMP CTRiASFeatures::SetEventSink (IUnknown *pIUnk, DWORD *pdwCookie, VARIANT_BOOL fAdvise)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pdwCookie) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeatures::SetEventSink");

	if (fAdvise) {
		if (NULL != pIUnk) {
			_ASSERTE(*pdwCookie == 0);
			return AtlAdvise (pIUnk, GetUnknown(), IID_ITRiASFeatureEvents, pdwCookie);
		}
	} else {
		if (NULL != pIUnk) {
			_ASSERTE(*pdwCookie != 0);

		DWORD dwCookie = *pdwCookie;

			*pdwCookie = 0L;
			return AtlUnadvise (pIUnk, IID_ITRiASFeatureEvents, dwCookie);
		}
	}
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::putref_FeaturesCallback (ITRiASFeaturesCallback *pICB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pICallback = pICB;
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::Refresh()
{
	return RefreshEx (SETUPFEATURESMODE_Normal);
}

STDMETHODIMP CTRiASFeatures::RefreshEx(SETUPFEATURESMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_pICallback)
		return S_FALSE;		// standalone objekt

	_ASSERTE(NULL != m_pIParent);

// neuen (leeren) Enumerator erzeugen
WEnumWTRiASFeature Enum;

	RETURN_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
	m_Enum -> Clear();

// und vom übergeordneten Objekt füllen lassen
	_ASSERTE(NULL != m_pIRelDisp);

HRESULT hr = m_pICallback -> SetupFeatures (m_pIRelDisp, rgMode);

	if (IMPL_AND_FAILED(hr)) {
		m_Enum = Enum.detach();		// alten Enumerator wieder einstellen
		return hr;
	}

// E_NOTIMPL gilt als iO
	return (S_OK == hr) ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Events verschicken
HRESULT CTRiASFeatures::Fire_CreatingFeature (VARIANT NameOrHandle, VARIANT_BOOL *pVal)
{
// wenn noch kein Parent gegeben ist (noch an keine Objektklasse gebunden), dann muß auch 
// noch niemand benachrichtigt werden
	if (NULL != m_pIParent) {
	WTRiASFeatureEvents Events;

		if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
			return Events -> CreatingFeature (NameOrHandle, pVal);
	}
	return S_OK;
}

HRESULT CTRiASFeatures::Fire_FeatureToCreate (VARIANT NameOrHandle)
{
// wenn noch kein Parent gegeben ist (noch an keine Objektklasse gebunden), dann muß auch 
// noch niemand benachrichtigt werden
	if (NULL != m_pIParent) {
	WTRiASFeatureEvents Events;

		if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
			return Events -> FeatureToCreate (NameOrHandle);
	}
	return S_OK;
}

HRESULT CTRiASFeatures::Fire_FeatureCreated (IDispatch * pIConn)
{
// wenn noch kein Parent gegeben ist (noch an keine Objektklasse gebunden), dann muß auch 
// noch niemand benachrichtigt werden
	if (NULL != m_pIParent) {
	WTRiASFeatureEvents Events;

		if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
			return Events -> FeatureCreated (pIConn);
	}
	return S_OK;
}

HRESULT CTRiASFeatures::Fire_DeletingFeature (IDispatch *pIConn, VARIANT_BOOL * pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASFeatureEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> DeletingFeature (pIConn, pVal);
	return S_OK;
}

HRESULT CTRiASFeatures::Fire_FeatureToDelete (IDispatch * pIConn)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASFeatureEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> FeatureToDelete (pIConn);
	return S_OK;
}

HRESULT CTRiASFeatures::Fire_FeatureDeleted(BSTR Name)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASFeatureEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> FeatureDeleted (Name);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureEvents
STDMETHODIMP CTRiASFeatures::CreatingFeature (VARIANT NameOrHandle, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::FeatureToCreate (VARIANT NameOrHandle)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::FeatureCreated (IDispatch *pIFeature)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WTRiASFeature Feature (pIFeature);
	WTRiASFeature Item;
	CComBSTR bstr;

		THROW_FAILED_HRESULT(Feature -> get_Name (&bstr));
		if (S_OK != m_Enum -> FindItem (bstr, &Item)) 
		{
			THROW_FAILED_HRESULT(_Add (Feature, VARIANT_TRUE));
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::ModifyingFeature (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::FeatureToModify (IDispatch *pIViewItem)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::FeatureModified (BSTR Name)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::DeletingFeature (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::FeatureToDelete (IDispatch *pIFeature)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn nicht wir derzeit bearbeitet werden
	if (IsSemaphoreSignaled (m_lSemDel, *this)) 
		return S_OK;

	COM_TRY {
	WTRiASFeature Feature (pIFeature);

		THROW_FAILED_HRESULT(RemoveFeature (Feature));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASFeatures::FeatureDeleted (BSTR Name)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}


