// @doc
// @module TRiASObjectsCollection.cpp | Implementation of the <c CTRiASObjectsCollection>
// class

#include "stdafx.h"

#include <ospace/std/set>
#include <ospace/stlex/boolops.h>

#include <Atl/Ciid.h>
#include <Com/VariantHelpers.h>
#include <Com/SafeArray.h>
#include <Com/PropertyHelper.h>
#include <MakeEnumVariant.h>

#include "Wrapper.h"
#include "Strings.h"
#include "GlobalVars.h"

#include "TRiASDBEngine.h"
#include "TRiASObjectsCollection.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASObjectsCollection, CTRiASObjectsCollection)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);	// WTRiASObjectHandleMap

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectsCollection

STDMETHODIMP CTRiASObjectsCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASObjectsCollection,
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
HRESULT CTRiASObjectsCollection::FinalConstruct (void)
{
// instance data
	ATLTRY(m_Enum = new NEnumWTRiASObjects());
	if (!m_Enum) return E_OUTOFMEMORY;

	m_Enum -> Release();	// Konstruktor hinterläßt RefCnt==1

// init base instance data
	return IPSImpl::FinalConstruct();
}

void CTRiASObjectsCollection::FinalRelease()
{
	m_Enum.Assign(NULL);	// Enumerator freigeben
	m_pIParent = NULL;
	m_Application = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASObjectsCollection::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::get_Application");

	*pVal = m_pIParent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// das Nullsetzen des Parent wird als Signal zum Freigeben gewertet
// evtl. alle SubObjekte von ihrem Bezug abhängen
	if (NULL == newVal) {
	// evtl. abhängiges Objekt benachrichtigen
		if (m_pICallback) 
			m_pICallback -> OnFinalRelease();

		COM_TRY {
		// einzelne TRiASObjects informieren
		WEnumVARIANT Enum;
		CComVariant var;

			THROW_FAILED_HRESULT(_NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/)
			{
				if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
					WTRiASObjects(V_UNKNOWN(&var)) -> put_Parent (NULL);
			}
		} COM_CATCH;
	}

	m_pIParent = newVal;		// no AddRef (fully contained)
	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::get_Application");

	*pVal = m_Enum -> Count();
	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::Item (VARIANT Index, ITRiASObjects **pVal)
{
	TEST_OUT_PARAM(pVal);

CComVariant vIndex;
bool fFound = false;

	*pVal = NULL;
	COM_TRY {
	WEnumWTRiASObjects Enum;
	WTRiASObjects Objs;

	// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > m_Enum -> Count())
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::Item");

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(Enum -> Reset());

			if (V_I4(&vIndex) > 1)
			{
				THROW_FAILED_HRESULT(Enum -> Skip (V_I4(&vIndex)-1));
			}
			if (S_OK == Enum -> Next (1, &Objs, NULL))
			{
				*pVal = Objs.detach();
				fFound = true;
			}

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));

		CComBSTR bstrFull, bstrApp;

				if (StringIsOKS(V_BSTR(&vIndex), &bstrFull, CLEARED(&bstrApp))) {
			// Objektklassenschlüssel vergleichen
			CComBSTR bstrCmp (bstrFull);

				for (Enum -> Reset(); S_OK == Enum -> Next (1, &Objs, NULL); /**/)
				{
				CComBSTR bstrOKS;

				// S_FALSE == hr: OKS der Klasse ist lediglich der Identifikator, 
				// also OKS nicht zum Vergleich verwenden
				HRESULT hr = Objs -> get_OKS (CLEARED(&bstrOKS));

					if (FAILED(hr)) {
						if (E_NOTIMPL == hr)
							continue;		// der nächste bitte
						_com_issue_error(hr);
					}
				
				// #AK990802: Vergleich ohne Unterscheidung Groß/Kleinschreibung
					if (S_FALSE == hr || !_wcsicmp(bstrOKS, bstrCmp)) {
					// Kurztext nur dann vergleichen, wenn dieser nicht der DefaultGenerierte ist
					VARIANT_BOOL fNameIsDefault = GetPropertyFrom (Objs, g_cbNameIsDefault, VARIANT_TRUE);

						if (!fNameIsDefault && bstrApp.Length() > 0) {
						// zusätzlich Namen vergleichen
						CComBSTR bstrName;

							THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));
							if (wcscmp (bstrName, bstrApp))
								continue;	// war doch nichts
						} 
						*pVal = Objs.detach();
						fFound = true;
						break;
					}
				}

			} else {
			// Bezeichner (Kurztext) vergleichen
				for (Enum -> Reset(); S_OK == Enum -> Next (1, &Objs, NULL); /**/)
				{
				CComBSTR bstrName;

					THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));
					if (!wcscmp(bstrName, V_BSTR(&vIndex))) {
						*pVal = Objs.detach();
						fFound = true;
						break;
					}
				}
			}

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::Item");

	} COM_CATCH;

	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_OBJECTS);

	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::_NewEnum (/*[out, retval]*/ IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(ppIEnum);

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASObjectsCollection::Add (BSTR Name, BSTR Type, ITRiASObjects **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(pVal);

// Erzeugen einer neuen Objects-collection und hinzufügen zur Collection
	COM_TRY {
	// Überprüfen, ob Objekt bereits existiert
	CComBSTR bstrCmp;
	CComBSTR bstrApp (g_cbNil);
	bool fIsOKS = false;

		{
		WTRiASObjects Objs;
		WEnumWTRiASObjects Enum;

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));

			if (StringIsOKS(Name, CLEARED(&bstrCmp), CLEARED(&bstrApp))) {
			// Objektklassenschlüssel vergleichen
				fIsOKS = true;
				for (Enum -> Reset(); S_OK == Enum -> Next (1, &Objs, NULL); /**/) {
				CComBSTR bstrOKS;

				// S_FALSE == hr: OKS der Klasse ist lediglich der Identifikator, 
				// also OKS nicht zum Vergleich verwenden
				HRESULT hr = Objs -> get_OKS (CLEARED(&bstrOKS));

					if (FAILED(hr)) {
						if (E_NOTIMPL == hr)
							continue;		// der nächste bitte
						_com_issue_error(hr);
					}
				
				// #AK990811: Vergleich ohne Unterscheidung Groß/Kleinschreibung
					if (S_FALSE == hr || !_wcsicmp(bstrOKS, bstrCmp)) {
					// Kurztext nur dann vergleichen, wenn dieser nicht der DefaultGenerierte ist
					VARIANT_BOOL fNameIsDefault = GetPropertyFrom (Objs, g_cbNameIsDefault, VARIANT_TRUE);

						if (!fNameIsDefault && bstrApp.Length() > 0) {
						// zusätzlich Namen vergleichen
						CComBSTR bstrName;

							THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));
							if (wcscmp (bstrName, bstrApp))
								continue;	// war doch nichts
						}
						*pVal = Objs.detach();
						return S_FALSE;		// existiert bereits
					}
				}

			} else {
			// Bezeichner (Kurztext) vergleichen
				bstrCmp = Name;
				for (Enum -> Reset(); S_OK == Enum -> Next (1, &Objs, NULL); /**/) {
				CComBSTR bstrName;

					THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));
					if (!wcscmp(bstrName, bstrCmp)) {
						*pVal = Objs.detach();
						return S_FALSE;		// existiert bereits
					}
				}
			}
		}

	// jetzt wirklich erzeugen und initialisieren
	WTRiASObjects Item;
	CIID ClsId (Type, CIID::INITCIID_InitFromProgId);

		if (!ClsId)	ClsId = CLSID_TRiASSimpleObjects;	// default ClsId

		if (IPSImpl::IsInitialized())	// neues Objekt erzeugen lassen
		{
		WUnknown Unk;

			THROW_FAILED_HRESULT(m_ObjMan -> CreateObject (ClsId, bstrCmp, STGM_CREATE, Unk.ppi(), false));

			Item = Unk;		// QI
			THROW_FAILED_HRESULT(Item -> put_Parent(m_pIParent));
			THROW_FAILED_HRESULT(Item -> put_Application(m_Application));

			THROW_FAILED_HRESULT(m_Enum -> AddItem (Item));
		}
		else if (NULL != m_pICallback) {
		CIID ClsId (Type, CIID::INITCIID_InitFromProgId);
		CComBSTR bstrType;

			if (!ClsId)	{// default ClsId besorgen
				THROW_FAILED_HRESULT(m_pICallback -> get_DefaultType (CLEARED(&bstrType)));
			} else
				bstrType = Type;

			THROW_FAILED_HRESULT(m_pICallback -> OnCreate (CComVariant(Name), bstrType, OBJECTSCOLLECTIONTYPE_Class, Item.ppi()));
		}
				
	// fertig initialisieren und zur Collection hinzufügen
		if (fIsOKS) {
			if (bstrApp.Length())
			{
				THROW_FAILED_HRESULT(Item -> put_Name(bstrApp));
			}
			THROW_FAILED_HRESULT(Item -> put_OKS(bstrCmp));
		}

	// erfolgreich erzeugt
		*pVal = Item.detach();

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::_Add (/*[in]*/ ITRiASObjects *newVal, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (fFullAdd) {
		RETURN_FAILED_HRESULT(newVal -> put_Application (m_Application));
		RETURN_FAILED_HRESULT(newVal -> put_Parent (m_pIParent));
	}

// Testen, ob dieses Objekt noch nicht in der collection enthalten ist
// Test erst nach put_Parent durchführen, da get_Handle einen gültigen Parent erfordert (#HK000123)
	_ASSERTE(IsFirstOccurence (m_Enum, newVal, ITRiASObjects::get_Handle, (INT_PTR *)NULL));
	return m_Enum -> AddItem (newVal);
}


STDMETHODIMP CTRiASObjectsCollection::Remove (VARIANT Index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	// Objects herauslöschen
	WEnumWTRiASObjects Enum;
	WTRiASObjects Objs;
	long lCnt = 1;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		THROW_FAILED_HRESULT(m_Enum -> Clear());

	CComVariant vIndex;
	CComBSTR bstrName;
	WTRiASObjects ObjsToDelete;

		if (SUCCEEDED(vIndex.ChangeType (VT_DISPATCH, &Index)) &&
			SUCCEEDED(V_DISPATCH(&vIndex) -> QueryInterface(ObjsToDelete.ppi()))) 
		{
		// Objektklasse ist direkt gegeben, dann über Handle suchen
		INT_PTR hObjsToDelete = NULL;

			THROW_FAILED_HRESULT(ObjsToDelete -> get_Handle (&hObjsToDelete));

		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Objs, NULL); lCnt++)
			{
			INT_PTR hObjs = NULL;

				THROW_FAILED_HRESULT(Objs -> get_Handle (&hObjs));
				if (hObjs != hObjsToDelete) {
					THROW_FAILED_HRESULT(m_Enum -> AddItem(Objs));
				} else {
					THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));
					if (NULL != m_pICallback) 	// das eigentliche Objekt informieren
						THROW_FAILED_HRESULT(m_pICallback -> OnDelete (CComVariant(Objs)));
				}
			}

		} else if (!V_ISBSTR(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > m_Enum -> Count())
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::Item");

		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Objs, NULL); lCnt++)
			{
				if (lCnt != V_I4(&vIndex)) {
					THROW_FAILED_HRESULT(m_Enum -> AddItem(Objs));
				} else {
					THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));
					if (NULL != m_pICallback) {	// das eigentliche Objekt informieren
					INT_PTR hObjs = NULL;

						THROW_FAILED_HRESULT(Objs -> get_Handle (&hObjs));
						THROW_FAILED_HRESULT(m_pICallback -> OnDelete (CComVariant(Objs)));
					}
				}
			}

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {
		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Objs, NULL); lCnt++)
			{
				THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));
				if (wcscmp(bstrName, V_BSTR(&vIndex)))
					m_Enum -> AddItem(Objs);
				else if (NULL != m_pICallback) {	// das eigentliche Objekt informieren
				INT_PTR hObjs = NULL;

					THROW_FAILED_HRESULT(Objs -> get_Handle (&hObjs));
					THROW_FAILED_HRESULT(m_pICallback -> OnDelete (CComVariant(Objs)));
				}
			}
			bstrName = V_BSTR(&vIndex);

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::Remove");

		_ASSERTE(0 == Enum -> Count() || Enum -> Count() == m_Enum -> Count() +1);

	// erfolgreich gelöscht
		if (IPSImpl::IsInitialized())
		{
			THROW_FAILED_HRESULT(m_ObjMan -> DelObject (bstrName));
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjectsCollection::Refresh ()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObjectsCollection::Refresh");
}

STDMETHODIMP CTRiASObjectsCollection::_Clone (/*[out, retval]*/ ITRiASObjectsCollection **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::_Clone");

CComObject<CTRiASObjectsCollection> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASObjectsCollection>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));
		if (IPSImpl::IsInitialized())
		{
			THROW_FAILED_HRESULT(pNew -> InitObjMan (m_ObjMan, m_Stg, m_StgMode));
		}
		THROW_FAILED_HRESULT(pNew -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pNew -> put_Parent (m_pIParent));

	WTRiASObjectsCollection ObjsColl (pNew);		// pending AddRef

		*pVal = ObjsColl.detach();

	} COM_CATCH_OP(delete pNew);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectCallback

STDMETHODIMP CTRiASObjectsCollection::putref_ObjectsCollectionCallback(ITRiASObjectsCollectionCallback * pICB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pICallback = pICB;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Recherchefunktionalität
STDMETHODIMP CTRiASObjectsCollection::ConsiderSearch(BSTR bstrCommand, SAFEARRAY *pParams)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	// 1. betroffene Objekteigenschaft finden
	WTRiASFeature Feat;
	WTRiASObjects Objs;
	HRESULT hr = GetSearchFeature (pParams, Feat.ppi(), Objs.ppi());

		if (S_OK == hr) {
		// alles ok, Objekteigenschaft zuerst versuchen, global zu behandeln
		WTRiASSearchObjects ToSearch;

			if (SUCCEEDED(Feat.QueryInterface(ToSearch)) && 
				S_OK == ToSearch -> ConsiderSearch (bstrCommand, pParams))
			{
			// Objekteigenschaft kann es selbst
				return S_OK;
			} else {
			// Objekteigenschaft muß lokal für Objektklassen behandelt werden

			// eine bestimmte Objektklasse untersuchen
				if (Objs.IsValid())
					return CEnumConsiderSearch::ConsiderSearch (Objs, bstrCommand, pParams);

			// alle Objektklassen durchgehen
				if (boolop_and(InEnumObjsColl(GetObjectsDefs()), InEnumObjsColl(), CEnumConsiderSearch(bstrCommand, pParams)))
					return S_OK;
				return TRIASDB_S_SEARCH_NOT_SUPPORTED;
			}

		} else if (TRIASDB_S_SHOULDHANDLEOBJECTS == hr) {
		// Objekteigenschaft muß lokal für Objektklassen behandelt werden

		// eine bestimmte Objektklasse untersuchen
			if (Objs.IsValid())
				return CEnumConsiderSearch::ConsiderSearch (Objs, bstrCommand, pParams);

			// alle Objektklassen durchgehen
			if (boolop_and(InEnumObjsColl(GetObjectsDefs()), InEnumObjsColl(), CEnumConsiderSearch(bstrCommand, pParams)))
				return S_OK;

			return TRIASDB_S_SEARCH_NOT_SUPPORTED;
		} 
		else if (TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED == hr) 
			return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;		// darf fehlschlagen

	} COM_CATCH;
	return TRIASDB_S_SEARCH_NOT_SUPPORTED;
}

STDMETHODIMP CTRiASObjectsCollection::SearchObjects(
	BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::SearchObjects");

	COM_TRY {
	// 1. betroffene Objekteigenschaft finden
	WTRiASFeature Feat;
	WTRiASObjects Objs;
	HRESULT hr = GetSearchFeature (pParams, Feat.ppi(), Objs.ppi());

		if (S_OK == hr) {
		// alles ok, Objekteigenschaft zuerst versuchen, global zu behandeln
		WTRiASSearchObjects ToSearch;

			if (SUCCEEDED(Feat.QueryInterface(ToSearch)) && 
				S_OK == ToSearch -> ConsiderSearch (bstrCommand, pParams))
			{
			HRESULT hr = ToSearch -> SearchObjects (bstrCommand, pIObjs, pParams);

				if (S_OK == hr) {
					THROW_FAILED_HRESULT(ConstraintObjects (pIObjs));
				} else if (TRIASDB_I_NO_OBJECTS_FOUND == hr || S_FALSE == hr)
					return TRIASDB_I_NO_OBJECTS_FOUND;

				THROW_FAILED_HRESULT(hr);	// alle andere Fehler melden

			} else {
			// die Objekteigenschaft unterstützt diese Recherche nicht, jede Objektklasse einzeln testen
				COM_TRY {
				// nur eine bestimmte Objektklasse testen
					if (Objs.IsValid())		
						return CEnumSearchObjs::SearchObjects (Objs, bstrCommand, pParams, pIObjs);

				// alle Objektklassen nacheinander testen
					if (!boolop_and(InEnumObjsColl(GetObjectsDefs()), InEnumObjsColl(), CEnumSearchObjs(bstrCommand, pParams, pIObjs)))
						return TRIASDB_S_SEARCH_NOT_SUPPORTED;

				} COM_CATCH_EX(e) {
				// unbekannte Objekteigenschaft stillschweigend übergehen
					if (TRIASDB_E_UNKNOWN_FEATURE == _COM_ERROR(e))
						return TRIASDB_S_SEARCH_NOT_SUPPORTED;

				// ansonsten Fehler melden
					THROW_FAILED_HRESULT(_COM_ERROR(e));
				} 
			}
		} 
		else if (TRIASDB_S_SHOULDHANDLEOBJECTS == hr) {
		// Objekteigenschaft muß lokal für Objektklassen behandelt werden

		// nur eine bestimmte Objektklasse testen
			if (Objs.IsValid())		
				return CEnumSearchObjs::SearchObjects (Objs, bstrCommand, pParams, pIObjs);

		// alle Objektklassen nacheinander testen
			if (!boolop_and(InEnumObjsColl(GetObjectsDefs()), InEnumObjsColl(), CEnumSearchObjs(bstrCommand, pParams, pIObjs)))
				return TRIASDB_S_SEARCH_NOT_SUPPORTED;
		} 
		else if (TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED == hr) 
			return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;	// darf so fehlschlagen

	} COM_CATCH;
	return S_OK;
}

namespace {
// testen, obs eine Zuordnungsobjektklasse ist
	inline HRESULT IsParentProject (ITRiASObjects *pIObjs)
	{
	WDispatch Parent;

		RETURN_FAILED_HRESULT(pIObjs -> get_Parent (Parent.ppi()));
		return SupportsInterface (Parent, (ITRiASProject *)NULL) ? S_OK : S_FALSE;
	}

// testen, ob das gegebene Objekt in einer der Zuordnungsobjektklassen vertreten ist
	inline HRESULT TestObjectInObjects (
		ITRiASObjectHandleMap *pIMap, CComVariant &rvObj, set<INT_PTR>::iterator first, set<INT_PTR>::iterator last)
	{
	WTRiASObjects Objs;
	WTRiASObject Obj;

		while (first != last) {
			RETURN_FAILED_HRESULT(pIMap -> GetObject (*first, Objs.ppu()));
			_ASSERTE(SupportsInterface (Objs, (ITRiASObjects *)NULL));

			if (S_OK == Objs -> Item (rvObj, Obj.ppi()))
				return S_OK;		// hier enthalten
			++first;
		}
		return S_FALSE;		// nicht vertreten
	}
}

// Ausgabeobjektmenge auf Objekte einer der enthaltenen Objektklassen beschränken
STDMETHODIMP CTRiASObjectsCollection::ConstraintObjects(ITRiASObjects *pIObjs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectsCollection::ConstraintObjects");

	COM_TRY {
	// alle verwendbaren Objectshandles aufsammeln
	set<INT_PTR> ObjsHandles;	// Normale Objektklassen dieser Collection
	set<INT_PTR> QueryHandles;	// Zuordnungsobjektklassen dieser Collection
	WEnumWTRiASObjects Enum;
	WTRiASObjects CurrObjs;
	INT_PTR hObjs = NULL;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &CurrObjs, NULL); /**/)
		{
			if (FAILED(CurrObjs -> get_Handle (&hObjs)))
				continue;

			if (S_OK == IsParentProject (CurrObjs))
				QueryHandles.insert (hObjs);	// Zuordnungsobjektklasse
			else
				ObjsHandles.insert (hObjs);		// 'normale' Objektklasse
		}
		
	// alle Objekte durchgehen und Zugehörigkeit testen
	WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());
	WEnumVARIANT EnumObjs;
	CComVariant v;

		THROW_FAILED_HRESULT(pIObjs -> _NewEnum (EnumObjs.ppu()));
		for (EnumObjs -> Reset(); S_OK == EnumObjs -> Next (1, CLEARED(&v), NULL); /**/) 
		{
			_ASSERTE(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

		WTRiASObject Obj (V_DISPATCH(&v));

			if (FAILED(Obj -> get_ObjectsHandle (&hObjs)))
				continue;
			_ASSERTE(NULL != hObjs);
		
		set<INT_PTR>::iterator it = ObjsHandles.find (hObjs);

			if (it == ObjsHandles.end()) {
			// durch keine 'normale' Objektklasse vertreten
			INT_PTR hObj = NULL;

				THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));

			// Feststellen, ob dieses Objekt in einer der Zuordnungsobjektklassen enthalten ist
			CComVariant vObj (hObj, VT_I4);

				if (S_OK != TestObjectInObjects (Map, vObj, QueryHandles.begin(), QueryHandles.end()))
					pIObjs -> _Remove (vObj);		// aus Eingabemenge herauslösen
			}
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Eine bestimmte Objekteigenschaft liefern
HRESULT CTRiASObjectsCollection::GetSearchFeature (
	SAFEARRAY *pParams, ITRiASFeature **ppIFeat, ITRiASObjects **ppIObjs)
{
	_ASSERTE(NULL != ppIFeat);
	_ASSERTE(NULL != ppIObjs);

	*ppIFeat = NULL;
	*ppIObjs = NULL;

	COM_TRY {
	// Objekteigenschaft aus Parameterfeld herauslösen
	CSafeArray sa(VT_VARIANT);

		if (NULL == pParams || !sa.Attach (pParams, true)) 
			return E_INVALIDARG;

	CSafeArrayLock<VARIANT> lock(sa);

		if (lock.Size() > 3) {
		// Objektklasse ist gegeben
		WTRiASObjects Objs;
		CComVariant v;

			if (VT_DISPATCH == V_VT(&lock[3])) {
			// Objektklasse ist direkt gegeben
				Objs = WTRiASObjects (V_DISPATCH(&lock[1]));

			} 
			else if (VT_BSTR != V_VT(&lock[3]) && SUCCEEDED(v.ChangeType (VT_I4, &lock[3]))) {
			// Handle gegeben, über globale Map wiederfinden
			WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());		// throws hr
			HRESULT hr = Map -> GetObject (V_I4(&v), Objs.ppu());

				if(FAILED(hr))
					return hr;		// evtl.existiert Objekteigenschaft mit diesem MCode noch nicht
			} 
			else {
				THROW_FAILED_HRESULT(E_UNEXPECTED);
			}
			*ppIObjs = Objs.detach();
		}

		if (lock.Size() > 1) {
		// Objekteigenschaft ist gegeben
		WTRiASFeature Feat;
		CComVariant v;

			if (VT_DISPATCH == V_VT(&lock[1])) {
			// Objekteigenschaft ist direkt gegeben
				Feat = WTRiASFeature (V_DISPATCH(&lock[1]));

			} 
			else if (VT_BSTR != V_VT(&lock[1]) && SUCCEEDED(v.ChangeType (VT_I4, &lock[1]))) {
			// Handle gegeben, über globale Map wiederfinden
			WTRiASObjectHandleMap Map (g_pDBEngine -> GetFeaturesMap());		// throws hr
			HRESULT hr = Map -> GetObject (V_I4(&v), Feat.ppu());

				if(FAILED(hr))
					return hr;		// evtl.existiert Objekteigenschaft mit diesem MCode noch nicht
			} 
			else if (SUCCEEDED(v.ChangeType (VT_BSTR, &lock[1]))) {
			// Name der Objekteigenschaft ist gegeben
				return TRIASDB_S_SHOULDHANDLEOBJECTS;
			} 
			else {
				THROW_FAILED_HRESULT(E_UNEXPECTED);
			}
			*ppIFeat = Feat.detach();

		} else
			return TRIASDB_S_SHOULDHANDLEOBJECTS;		// Objektklassen einzeln befragen

	} COM_CATCH;
	return S_OK;
}

