// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.07.99 20:44:03
//
// @doc
// @module TRiASCollectObjects.cpp | Implementation of the <c CTRiASCollectObjects> class


#include "stdafx.h"

#include <ospace/stl/helper.h>
#include <ospace/views/mapview.h>

#include <MakeEnumVariant.h>
#include <Com/PersistEnumPropStream.h>
#include <Com/MkHelper.h>

#include "QueryDef.h"
#include "QueryDefExt.h"
#include "TRiASCollectObjects.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObject);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(EnumVARIANT);

/////////////////////////////////////////////////////////////////////////////
// CTRiASCollectObjects

STDMETHODIMP CTRiASCollectObjects::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleObjects
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASCollectObjects::_NewEnum (IUnknown **ppIEnum)
{
	TEST_OUT_PARAM(ppIEnum);
	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

HRESULT CTRiASCollectObjects::Item (VARIANT vName, IMoniker **ppIMk)
{
	return E_FAIL;		// simply never find any items
}

HRESULT CTRiASCollectObjects::Remove (VARIANT vName)
{
	return E_FAIL;		// simply never remove any items
}

HRESULT CTRiASCollectObjects::_Add (IMoniker *pIMk, VARIANT_BOOL /*fFullAdd*/)
{
	RETURN_FAILED_HRESULT(m_Enum -> AddItem (pIMk));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectsCallback

STDMETHODIMP CTRiASCollectObjects::get_DefaultType (BSTR *pbstrType)
{
	TEST_OUT_PARAM(pbstrType);
	return E_UNEXPECTED;		// hier nicht unterstützt
}

/////////////////////////////////////////////////////////////////////////////
// Erstmalige Initialisierung
STDMETHODIMP CTRiASCollectObjects::SetupObjects(SETUPOBJECTSMODE rgMode)
{
// doppelte Initialisierung verhindern
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch (rgMode) {
	case SETUPOBJECTSMODE_Count:
		return EnsureObjectCount();

	case SETUPOBJECTSMODE_Load:
		return OnLoadObjects();

	case SETUPOBJECTSMODE_InitOrLoad:
	default:
		break;
	}
	return S_OK;
}

HRESULT CTRiASCollectObjects::EnsureLocalHandleCont(bool fClearMap)
{
	if (NULL != m_pObjs) {
		if (fClearMap)
			m_pObjs -> clear();
		return S_OK;
	}
	ATLTRY(m_pObjs = new CObjHandleMap);
	return (NULL != m_pObjs) ? S_OK : E_OUTOFMEMORY;
}

// Absichern, das das aggregierte Objekt über Objekttypen und Anzahl der Objekte Bescheid weiß
HRESULT CTRiASCollectObjects::EnsureObjectCount()
{
	if (HasType (m_rgInitState, INITSTATE_CountsInitialized))
		return S_OK;		// bereits alles geladen

// bis COLLECTOBJECTS_VERSION_102 sind Zähler und Typen nicht mit gespeichert,
// müssen also live bestimmt werden
	return OnLoadObjects();
}

// Laden aller Objekte im EnumMk und speichern selbiger im aggregierten Objekt
HRESULT CTRiASCollectObjects::OnLoadObjects()
{
	if (HasType (m_rgInitState, INITSTATE_ObjectsLoaded))
		return S_OK;		// bereits alles geladen

	COM_TRY {
	// Zähler rücksetzen, Datenstrukturen initialisieren
		ResetCounters (true);
		THROW_FAILED_HRESULT(EnsureLocalHandleCont(true));
		_ASSERTE(NULL != m_pObjs);

	// Objekt neu einlesen
	CComSemaphore<_ThreadModel> Sem (m_lInitData);		// Teilrekursion verhindern
	WTRiASObjects BaseObjs;
	WTRiASObjectHandleMap Map (((CQueryDefExtension *)g_pTE) -> GetObjectsMap());

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));

	OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
	DWORD dwTypes = 0;

		RETURN_FAILED_HRESULT(BaseObjs -> get_Types(&rgTypes))
		if (OBJECTTYPE_Unknown == rgTypes)	// noch nichts gesetzt --> alle annehmen
			dwTypes = (OTPunkt|OTLinie|OTFlaeche|OTText);
		else {
			dwTypes = OBJECTTYPEToBits(rgTypes);
			rgTypes = OBJECTTYPE_Unknown;
		}

	WMoniker Mk;
	LONG ulCnt = 0;

		for (m_Enum -> Reset(); S_OK == m_Enum -> Next (1, &Mk, NULL); /**/) {
		WTRiASObject Obj;

			if (SUCCEEDED(MkBindToObject (Mk, Obj.ppi()))) {
			// Objekt zu unserer Objektmenge hinzufügen
				THROW_FAILED_HRESULT(BaseObjs -> _Add (Obj, VARIANT_FALSE));

			// am ConnPt der zu diesem Objekt gehörenden Objektklasse anmelden
			INT_PTR hObjs = NULL;

				THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle (&hObjs));
				THROW_FAILED_HRESULT(m_Classes.Insert (GetUnknown(), hObjs));

			OBJECTTYPE rgT = OBJECTTYPE_Unknown;

				THROW_FAILED_HRESULT(Obj -> get_Type (&rgT));
				SetType (rgTypes, rgT);		// Objekttypen nachziehen
				++ulCnt;

				THROW_FAILED_HRESULT(IncrementObjectCount (Obj));
			}
		}
		THROW_FAILED_HRESULT(BaseObjs -> put_Count (ulCnt));

	// vorhandene Objekttypen abgleichen
		if (dwTypes != OBJECTTYPEToBits(rgTypes)) {
		// in einer der Ansichten ist mehr definiert als real vorhanden
			RETURN_FAILED_HRESULT(BaseObjs -> put_Types (rgTypes));
		}
		SetType (m_rgInitState, INITSTATE_CountsInitialized|INITSTATE_ObjectsLoaded);

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::SetupFeatures(SETUPFEATURESMODE rgMode)
{
// Objekte Zuordnungsobjektklassen greifen auf ihre eigenen Objekteigenschaften zu
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Ein neues Objekt soll erzeugt werden
STDMETHODIMP CTRiASCollectObjects::OnCreate (BSTR Name, BSTR Type, OBJECTTYPE rgType, ITRiASObject **ppIObj)
{
	TEST_OUT_PARAM(ppIObj);

	_ASSERTE(FALSE);	// sollte nicht passieren
	return E_UNEXPECTED;
}

/////////////////////////////////////////////////////////////////////////////
// Irgend was wurde modifiziert
STDMETHODIMP CTRiASCollectObjects::OnChanging(CHANGEDOBJECTS rgWhat, VARIANT vNewValue, VARIANT_BOOL *pDisAllow)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (NULL == pDisAllow)
		return E_POINTER;

	*pDisAllow = VARIANT_FALSE;		// immer einverstanden sein
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Irgend was wurde modifiziert
STDMETHODIMP CTRiASCollectObjects::OnChanged(CHANGEDOBJECTS rgWhat, VARIANT vOldValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// nur behandeln, wenn wir nicht derzeit initialisiert werden
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch(rgWhat) {
	case CHANGEDOBJECTS_Name:
		return OnChangedName();

	case CHANGEDOBJECTS_Description:
		return OnChangedDescription();

	case CHANGEDOBJECTS_OKS:
		return OnChangedOKS();

	case CHANGEDOBJECTS_Handle:
		return OnChangedHandle();

	case CHANGEDOBJECTS_Types:
		return OnChangedTypes();

	case CHANGEDOBJECTS_ROMode:
		return OnChangedROMode();

	default:
		break;
	}
	return E_INVALIDARG;
}

/////////////////////////////////////////////////////////////////////////////
// Ein Objekt soll gelöscht werden
STDMETHODIMP CTRiASCollectObjects::OnDelete (INT_PTR hObj)
{
	return S_FALSE;		// gelöscht wird beim Objekt
}

/////////////////////////////////////////////////////////////////////////////
// Ein Objekt soll zu dieser Objektmenge hinzugefügt werden
STDMETHODIMP CTRiASCollectObjects::OnAdd (ITRiASObject *pIObj, CLASSIFYMODE rgMode)
{
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	COM_TRY {
	// zunächst alle Objekt laden
		THROW_FAILED_HRESULT(OnLoadObjects());

	// absichern, daß Objekte nicht doppelt drin sind
	INT_PTR hObj = NULL;
	WTRiASObject ObjT;

		THROW_FAILED_HRESULT(pIObj -> get_Handle (&hObj));
		if (SUCCEEDED(WTRiASObjects(m_BaseUnk) -> Item (CComVariant(hObj), ObjT.ppi())))
			return TRIASDB_I_OBJECT_ALREADY_EXISTS;		// ok, bereits enthalten

	// neues Objekt mit seinem Moniker hier speichern
	WMoniker mk;

		THROW_FAILED_HRESULT(MkGetMoniker (pIObj, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
		THROW_FAILED_HRESULT(m_Enum -> AddItem (mk));

	// am ConnPt der zu diesem Objekt gehörenden Objektklasse anmelden
	INT_PTR hObjs = NULL;

		THROW_FAILED_HRESULT(pIObj -> get_ObjectsHandle (&hObjs));
		THROW_FAILED_HRESULT(m_Classes.Insert (GetUnknown(), hObjs));
		THROW_FAILED_HRESULT(IncrementObjectCount (pIObj));

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Ein Objekt soll aus dieser Objektmenge entfernt werden
STDMETHODIMP CTRiASCollectObjects::OnRemove (ITRiASObject *pIObj)
{
	if (!HasType (m_rgInitState, INITSTATE_ObjectsLoaded))
		return S_OK;		// Objekt wurden noch nicht geladen

	COM_TRY {
	// Objekt wird aus dieser Collection entfernt
	WTRiASObject Obj(pIObj);
	INT_PTR hObjs = NULL;

		THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle (&hObjs));
		THROW_FAILED_HRESULT(m_Classes.Remove (hObjs));		// beim ConnectionPoint abmelden

	// Objektzähler korrigieren und Handle freigeben
		THROW_FAILED_HRESULT(DecrementObjectCount (Obj));
		m_fIsDirty = true;									// MkEnum beim Speichern neu erzeugen

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::MapFeatureHandle (VARIANT vNameOrHandle, VARIANT *pvNewNameOrHandle)
{
	return CComVariant(vNameOrHandle).Detach (pvNewNameOrHandle);
}

namespace {
	class CRemoveHelper
	{
	public:
		CRemoveHelper (ITRiASObjectHandleMap *pIMap) : m_Map(pIMap) {}

		void operator() (CObjHandleMap::value_type &p) throw(_com_error &)
		{
			THROW_FAILED_HRESULT(m_Map -> RemoveObject (p.second, OBJECTMAPMODE_RemoveAllReferences));
		}

	private:
		WTRiASObjectHandleMap m_Map;
	};
}

STDMETHODIMP CTRiASCollectObjects::OnFinalRelease()
{
	if (!HasType (m_rgInitState, INITSTATE_ObjectsLoaded)) {
		_ASSERT(NULL == m_pObjs);
		return S_OK;		// Objekt wurden noch nicht geladen
	}

	COM_TRY {
	// alle Objekte aus der globalen ObjektMap entfernen
		_ASSERTE(NULL != m_pObjs);
		os_for_each (*m_pObjs, CRemoveHelper(((CQueryDefExtension *)g_pTE) -> GetObjectMap()));
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CTRiASCollectObjects::OnChangedName()
{
	return S_OK;
}

HRESULT CTRiASCollectObjects::OnChangedDescription()
{
	return S_OK;
}

HRESULT CTRiASCollectObjects::OnChangedOKS()
{
	return S_OK;
}

HRESULT CTRiASCollectObjects::OnChangedHandle()
{
	return S_OK;
}

HRESULT CTRiASCollectObjects::OnChangedTypes()
{
	return S_OK;
}

HRESULT CTRiASCollectObjects::OnChangedROMode()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASCollectObjects::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = CLSID_TRiASCollectObjects;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStream

STDMETHODIMP CTRiASCollectObjects::IsDirty (void)
{
	return m_fIsDirty ? S_OK : WPersistStreamInit(m_BaseUnk) -> IsDirty();
}

STDMETHODIMP CTRiASCollectObjects::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (INITSTATE_NotInitialized != m_rgInitState)
		return E_UNEXPECTED;

// unsere Daten laden
long lSignature = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (COLLECTOBJECTS_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
	if ((lVersion & ~COLLECTOBJECTS_VERSION_MINOR_MASK) > LASTKNOWN_COLLECTOBJECTS_VERSION)
		return TRIASDB_W_NEWEROBJECTSCOLLECTION;

	COM_TRY {
	// jetzt alles andere laden
	OBJECTSCOLLECTIONTYPE rgCollType = OBJECTSCOLLECTIONTYPE(OBJECTSCOLLECTIONTYPE_Class|OBJECTSCOLLECTIONTYPE_Query);
	WTRiASObjects Objs (m_BaseUnk);

		THROW_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Load (pStm));
		THROW_FAILED_HRESULT(Objs -> put_CollectionType (rgCollType));

	// ObjektMoniker laden
		if (lVersion >= COLLECTOBJECTS_VERSION_101)
		{
			THROW_FAILED_HRESULT(LoadEnumeratedItems (this, pStm, &FMTID_EnumMoniker, (IMoniker *)NULL, lVersion >= COLLECTOBJECTS_VERSION_102));
		}

	// evtl. Typen und Zähler gespeichert
		if (lVersion >= COLLECTOBJECTS_VERSION_104) {
		long lCount = 0;
		OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

			LoadLong (pStm, lCount);
			LoadData (pStm, rgTypes);

			for (int i = 0; i < _countof(m_lCounts); i++)
				LoadLong (pStm, m_lCounts[i]);

			THROW_FAILED_HRESULT(Objs -> put_Count (lCount));
			THROW_FAILED_HRESULT(Objs -> put_Types (rgTypes));

			SetType (m_rgInitState, INITSTATE_CountsInitialized);
		}

	} COM_CATCH;

	m_fIsDirty = false;
	SetType (m_rgInitState, INITSTATE_Initialized|INITSTATE_EnumLoaded);
	return S_OK;
}

namespace {
	class CGetNameFromMoniker :
		public binary_initialize_getname<WMoniker, BSTR *>
	{
	public:
		typedef binary_initialize_getname<WMoniker, BSTR *> base_t;
		typedef base_t::binary_initialize_target binary_initialize_target;

		HRESULT operator() (WMoniker mk, BSTR *val)
		{
		WTRiASObject obj;

			RETURN_FAILED_HRESULT(MkBindToObject (mk, obj.ppi()));
			return obj -> get_Name (val);
		}
	};
}

STDMETHODIMP CTRiASCollectObjects::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	COM_TRY {
		THROW_FAILED_HRESULT(SaveLong(pStm, COLLECTOBJECTS_SIGNATURE));
		THROW_FAILED_HRESULT(SaveLong(pStm, LASTKNOWN_COLLECTOBJECTS_VERSION));

		THROW_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Save (pStm, fClearDirty));

	// ObjektMoniker speichern
	OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
	long lCount = 0;

		if (m_fIsDirty) {
		WTRiASObjects Objs (m_BaseUnk);
		WEnumVARIANT Enum;
		CComVariant v;
	
			THROW_FAILED_HRESULT(m_Enum -> Clear());
			THROW_FAILED_HRESULT(Objs -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			WMoniker Mk;

				_ASSERTE(SUCCEEDED(v.ChangeType (VT_UNKNOWN)));
				THROW_FAILED_HRESULT(MkGetMoniker (V_UNKNOWN(&v), OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, Mk.ppi()));
				THROW_FAILED_HRESULT(m_Enum -> AddItem (Mk))

			OBJECTTYPE rgT = OBJECTTYPE_Unknown;

				THROW_FAILED_HRESULT(WTRiASObject(V_UNKNOWN(&v)) -> get_Type (&rgT));
				
				SetType (rgTypes, rgT);		// Objekttypen nachziehen
				++lCount;					// Objekte zählen
			}
		} else {
		WTRiASObjects Objs (m_BaseUnk);

			THROW_FAILED_HRESULT(Objs -> get_Count (&lCount));
			THROW_FAILED_HRESULT(Objs -> get_Types (&rgTypes));
		}

	CGetNameFromMoniker pred;

		THROW_FAILED_HRESULT(SaveEnumeratedItemsEx (this, pStm, &FMTID_EnumMoniker, pred));

	// Zähler/Typen speichern (ab COLLECTOBJECTS_VERSION_103)
		SaveLong (pStm, lCount);
		SaveData (pStm, rgTypes);
		for (int i = 0; i < _countof(m_lCounts); i++)
			SaveLong (pStm, m_lCounts[i]);

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pcbSize) 
		return E_POINTER;

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> GetSizeMax (pcbSize));
	pcbSize -> QuadPart += 2*sizeof(long);

#pragma TODO("GetSizeMax für die gespeicherten Moniker ausrechnen.")

	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::InitNew (void)
{
	if (INITSTATE_NotInitialized != m_rgInitState)
		return E_UNEXPECTED;

	COM_TRY {
	// jetzt fertig initialiseren
	OBJECTSCOLLECTIONTYPE rgCollType = OBJECTSCOLLECTIONTYPE(OBJECTSCOLLECTIONTYPE_Class|OBJECTSCOLLECTIONTYPE_Query);

		THROW_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> InitNew());
		THROW_FAILED_HRESULT(WTRiASObjects(m_BaseUnk) -> put_CollectionType (rgCollType));
	} COM_CATCH;

	m_fIsDirty = false;	
	m_rgInitState = INITSTATE_Initialized;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectEvents
STDMETHODIMP CTRiASCollectObjects::CreatingObject (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::ObjectToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::ObjectCreated (IDispatch *pIObj)
{
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::ModifyingObject (IDispatch *pIObj, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::ObjectToModify (IDispatch *pIObj)
{
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::ObjectModified (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::DeletingObject (IDispatch *pIObj, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::ObjectToDelete (IDispatch *pIObj)
{
	if (!HasType (m_rgInitState, INITSTATE_ObjectsLoaded))
		return S_OK;		// Objekt wurden noch nicht geladen

	COM_TRY {
	// Objekt wird gelöscht werden, also aus dieser Collection entfernen
	INT_PTR hObjs = NULL;
	WTRiASObject Obj(pIObj);

		THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle (&hObjs));
		THROW_FAILED_HRESULT(WTRiASObjects(m_BaseUnk) -> _Remove (CComVariant(pIObj)));
		THROW_FAILED_HRESULT(m_Classes.Remove (hObjs));		// beim ConnectionPoint abmelden

		THROW_FAILED_HRESULT(DecrementObjectCount (Obj));
		m_fIsDirty = true;									// MkEnum beim Speichern neu erzeugen

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::ObjectDeleted (BSTR Name)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectsEx
STDMETHODIMP CTRiASCollectObjects::get_Count (OBJECTTYPE rgType, long *plObjCnt)
{
	if (!HasType (m_rgInitState, INITSTATE_Initialized))
		return E_UNEXPECTED;
	TEST_OUT_PARAM(plObjCnt);

	RETURN_FAILED_HRESULT(EnsureObjectCount());
	_ASSERTE(HasType (m_rgInitState, INITSTATE_CountsInitialized));

// typspezifischen Objektzähler liefern
	switch (rgType) {
	case OBJECTTYPE_Point:
		*plObjCnt = m_lCounts[0];
		break;

	case OBJECTTYPE_Line:
		*plObjCnt = m_lCounts[1];
		break;

	case OBJECTTYPE_Area:
		*plObjCnt = m_lCounts[2];
		break;

	case OBJECTTYPE_Text:
		*plObjCnt = m_lCounts[3];
		break;

	case OBJECTTYPE_All:
		*plObjCnt = m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3];
		break;

	default:
		return E_INVALIDARG;
	}
	return S_OK;
}

STDMETHODIMP CTRiASCollectObjects::get_LocalHandle (INT_PTR *pVal)
{
	if (!HasType (m_rgInitState, INITSTATE_Initialized))
		return E_UNEXPECTED;
	return WTRiASObjects(m_BaseUnk) -> get_Handle (pVal);	// hat nur ein Handle
}

STDMETHODIMP CTRiASCollectObjects::get_Handles (long lCount, INT_PTR *plObjs)
{
	if (!HasType (m_rgInitState, INITSTATE_Initialized))
		return E_UNEXPECTED;
	TEST_OUT_PARAM(plObjs);

	RETURN_FAILED_HRESULT(OnLoadObjects());				// Handles erzeugen
	_ASSERTE(HasType (m_rgInitState, INITSTATE_ObjectsLoaded));

// Handles umkopieren
	_ASSERTE((size_t)lCount >= m_pObjs -> size());
	_ASSERTE(!IsBadWritePtr(plObjs, sizeof(HOBJECT)*lCount));

// Handles umkopieren
map_values<INT_PTR, INT_PTR, less<INT_PTR> > values (*m_pObjs);

	_ASSERTE((size_t)lCount >= m_pObjs -> size());
	copy (values.begin(), values.end(), plObjs);
	return S_OK;
}

HRESULT CTRiASCollectObjects::GetMappedObjectHandle (INT_PTR hObjOrig, INT_PTR *phObjMapped)
{
	if (!HasType (m_rgInitState, INITSTATE_Initialized))
		return E_UNEXPECTED;
	TEST_OUT_PARAM(phObjMapped);

	COM_TRY {
	CObjHandleMap::iterator it = m_pObjs -> find (hObjOrig);

		if (it == m_pObjs -> end())
			return TRIASDB_E_UNKNOWN_OBJECT;
	
		*phObjMapped = (*it).second;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CTRiASCollectObjects::IncrementObjectCount (ITRiASObject *pIObj)
{
	COM_TRY {
	// ObjectTyp wird benötigt
	OBJECTTYPE rgType = OBJECTTYPE_Unknown;
	INT_PTR hObjOrig = NULL;

		THROW_FAILED_HRESULT(pIObj -> get_Type (&rgType));
		THROW_FAILED_HRESULT(pIObj -> get_Handle (&hObjOrig));

	// jede Inkarnation eines Objektes bekommt ein eigenes Handle
	WTRiASObjectHandleMap Map (((CQueryDefExtension *)g_pTE) -> GetObjectMap());
	OBJECTMAPMODE rgMode = OBJECTMAPMODE(OBJECTMAPMODE_NameDoesNotIdentifyObject|OBJECTMAPMODE_CreateObjectHandle);
	INT_PTR hObj = NULL;

		THROW_FAILED_HRESULT(Map -> GetObjectHandle (vtMissing, pIObj, rgMode, &hObj));

	// Objekthandle speichern
		m_pObjs -> insert(CObjHandleMap::value_type(hObjOrig, hObj));

	// Objekttypenweise zählen
		switch (rgType) {
		case OBJECTTYPE_Point:
			++m_lCounts[0]; 
			break;

		case OBJECTTYPE_Line:
			++m_lCounts[1]; 
			break;

		case OBJECTTYPE_Area:
			++m_lCounts[2]; 
			break;

		case OBJECTTYPE_Text:
			++m_lCounts[3]; 
			break;

		default:
			return E_INVALIDARG;
		}
		_ASSERTE(m_pObjs -> size() == m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3]);

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCollectObjects::DecrementObjectCount (ITRiASObject *pIObj)
{
	COM_TRY {
	// ObjectTyp wird benötigt
	OBJECTTYPE rgType = OBJECTTYPE_Unknown;
	INT_PTR hObj = NULL;

		THROW_FAILED_HRESULT(pIObj -> get_Handle (&hObj));
		THROW_FAILED_HRESULT(pIObj -> get_Type (&rgType));

	// jede Inkarnation eines Objektes hat ein eigenes Handle
	WTRiASObjectHandleMap Map (((CQueryDefExtension *)g_pTE) -> GetObjectMap());
	CObjHandleMap::iterator it = m_pObjs -> find (hObj);

		if (it == m_pObjs -> end())
			THROW_FAILED_HRESULT(E_UNEXPECTED);

		THROW_FAILED_HRESULT(Map -> RemoveObject ((*it).second, OBJECTMAPMODE_RemoveAllReferences));

	// Objekthandle nicht mehr speichern
		m_pObjs -> erase (it);

	// Objekttypenweise zählen
		switch (rgType) {
		case OBJECTTYPE_Point:
			m_lCounts[0] = max(m_lCounts[0]-1L, 0L); 
			break;

		case OBJECTTYPE_Line:
			m_lCounts[1] = max(m_lCounts[1]-1L, 0L); 
			break;

		case OBJECTTYPE_Area:
			m_lCounts[2] = max(m_lCounts[2]-1L, 0L); 
			break;

		case OBJECTTYPE_Text:
			m_lCounts[3] = max(m_lCounts[3]-1L, 0L); 
			break;

		default:
			return E_INVALIDARG;
		}
		_ASSERTE(m_pObjs -> size() == m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3]);

	} COM_CATCH;
	return S_OK;
}

