// $Header: /TRiAS/TRiASDB/TRiASDB/TRiASObjects.cpp 16    15.06.98 21:34 Hartmut Kaiser $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 05/30/1998 07:15:41 PM
//
// @doc
// @module TRiASObjects.cpp | Implementation of CTRiASObjects

#include "stdafx.h"

#include <Atl/Ciid.h>

#include <Com/SafeArray.h>
#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>
#include <Com/EnumVariantIterators.h>
#include <Com/ComBool.h>

#include <ChangeValueHelper.h>

#include <ospace/string/src/regex.h>	// GNU regular expression matcher
#include <ospace/string/regexp.h>

#pragma warning (disable: 4192)		// automatically excluding 'bla' while importing type library 'bla'
#import "tlb/TRiASMDS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 

#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/PBasic.tlh>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#import "tlb/TDBGeo.tlb" raw_interfaces_only	raw_dispinterfaces no_namespace named_guids \
	exclude("_DGMPoint", "_DGMPoints")

#include "Strings.h"
#include "GlobalVars.h"
#include "Wrapper.h"
#include "TRiASDBGuids.h"

#include "TRiASDBEngine.h"
#include "TRiASProperty.h"
#include "TRiASObjects.h"
#include "TRiASFeatures.h"
#include "MakeEnumVariant.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class if standalone and if aggregated
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASObjects);
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(CTRiASObjects);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASObjects::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASObjects, CTRiASObjects)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASObjects, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(OleClientSite);			// WOleClientSite
DefineSmartInterface(BindCtx);					// WBindCtx

DefineSmartInterface2(DMatchString, IID_DMatchString);	// WDMatchString
DefineSmartInterface(MatchPlainText);					// WMatchPlainText
DefineSmartInterface(MatchRegExpr);						// WMatchRegExpr

DefineSmartInterface(TRiASMDSMap);					// WMDSMap
DefineSmartInterface(TRiASCloneGeometry);

/////////////////////////////////////////////////////////////////////////////
// hier benötigte Datentypen
typedef __InEnumIterator<ITRiASObject, ITRiASObjects> InEnumObjs;
typedef __OutEnumIterator<ITRiASObject, ITRiASObjects> OutEnumObjs;

typedef __InEnumIterator<ITRiASFeature, ITRiASFeatures> InEnumFeats;
typedef __OutEnumIterator<ITRiASFeature, ITRiASFeatures> OutEnumFeats;

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjects

STDMETHODIMP CTRiASObjects::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASObjects,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASObjects::FinalConstruct (void)
{
// instance data
	ATLTRY(m_Enum = new TEnumWTRiASObject());
	if (!m_Enum) 
		return E_OUTOFMEMORY;

	m_Enum -> Release();	// Konstruktor hinterläßt RefCnt==1
	return S_OK;
}

void CTRiASObjects::FinalRelease()
{
// evtl. aus HandleTabellen entfernen
	if (NULL != m_hObjects) {
		COM_TRY {
		// aus globaler Tabelle entfernen
		WTRiASObjectHandleMap MapG (g_pDBEngine -> GetObjectsMap());		// throws hr

			VERIFY(S_OK == MapG -> RemoveObject ((LONG)m_hObjects, OBJECTMAPMODE_RemoveThisReference));
		
		// aus Database-Tabelle entfernen
//			if (NULL != m_pIParent) {
//			WTRiASObjectHandleMap MapP (GetPropertyFrom (m_pIParent, g_cbObjectsMap, (IDispatch *)NULL), false);
//
//				if (MapP.IsValid()) 
//					VERIFY(S_OK == MapP -> RemoveObject ((LONG)m_hObjects, OBJECTMAPMODE_RemoveAllReferences));
//			}
			m_hObjects = NULL;

		} COM_CATCH_IGNORE;
	}

// sonstige Aufräumarbeiten
	FreePropertiesCollection();

	m_Enum.Assign(NULL);
	m_Features.Assign(NULL);
	m_GeometryFeatures.Assign(NULL);
	m_pIParent = NULL;
	m_Application = NULL;
}

// Collection laden lassen
HRESULT CTRiASObjects::EnsureObjectsLoaded()
{
	if (IsLoaded())
		return S_OK;

	_ASSERTE(NULL != m_pICallback);		// Callbackinterface muß gesetzt sein
	if (NULL == m_pICallback)
		return E_UNEXPECTED;

// initialiseren der Metadaten etc.
// legt fest, welche Attribute zu den Objekten dieser Collection gehören
// legt fest, wieviele Objekte (erstmal) zu dieser Collection gehören
	RETURN_FAILED_HRESULT(m_pICallback -> SetupObjects(SETUPOBJECTSMODE_Load));

	m_fIsLoaded = true;		// nur einmal laden
	return S_OK;
}

HRESULT CTRiASObjects::EnsureObjectsCount()
{
	_ASSERTE(NULL != m_pIParent);
	_ASSERTE(NULL != m_pICallback);		// Callbackinterface muß gesetzt sein
	if (NULL == m_pICallback)
		return E_UNEXPECTED;

// initialiseren der Metadaten etc.
// legt fest, welche Attribute zu den Objekten dieser Collection gehören
// legt fest, wieviele Objekte (erstmal) zu dieser Collection gehören
	return m_pICallback -> SetupObjects(SETUPOBJECTSMODE_Count);
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASObjects::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return TRIASDB_E_INVALID_PARAMETER;

	*pClassID = CLSID_TRiASObjects;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASObjects::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASObjects::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

long lSignature = 0L;

	THROW_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (OBJECTS_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
	if ((lVersion & ~OBJECTS_VERSION_MINOR_MASK) > LASTKNOWN_OBJECTS_VERSION)
		return TRIASDB_W_NEWEROBJECTSCOLLECTION;

	m_bstrName.Empty();
	m_bstrDesc.Empty();
	m_bstrOKS.Empty();
	RETURN_FAILED_HRESULT(m_bstrName.ReadFromStream (pStm));	// Name
	RETURN_FAILED_HRESULT(m_bstrDesc.ReadFromStream (pStm));	// Description
	RETURN_FAILED_HRESULT(m_bstrOKS.ReadFromStream (pStm));		// Objektklassenschlüssel

	m_bstrDefaultGeom.Empty();
	m_bstrPrimaryKey.Empty();
	if (lVersion >= OBJECTS_VERSION_101) {
		RETURN_FAILED_HRESULT(m_bstrDefaultGeom.ReadFromStream (pStm));		// Name der PrimärGeometrie-Eigenschaft
		RETURN_FAILED_HRESULT(m_bstrPrimaryKey.ReadFromStream (pStm));		// Name des eindeutigen Objektkennzeichens

	LONG fOKSIsIdent = FALSE;

		RETURN_FAILED_HRESULT(LoadLong (pStm, fOKSIsIdent));	// ist OKS gegeben ?
		m_fOksIsIdent = fOKSIsIdent ? true : false;
	}

	_ASSERTE(sizeof(long) == sizeof(OBJECTTYPE));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)m_rgType));		// Objekttypen
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)m_rgCollType));	// Typ der collection

// ab OBJECTS_VERSION_102 wird Parentmoniker nicht mehr geschrieben
	if (lVersion < OBJECTS_VERSION_102) {
	// MonikerDisplayName einlesen, um Parent wiederzufinden
	WMoniker mk;

		RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_IMoniker, mk.ppv()));
		RETURN_FAILED_HRESULT(::BindMoniker (mk, NULL, IID_IDispatch, (LPVOID *)&m_pIParent));
	}

// Aggregat davon in Kenntnis setzen
	if (NULL != m_pICallback)
		m_pICallback -> SetupObjects (SETUPOBJECTSMODE_InitOrLoad);

	m_fIsDirty = false;
	m_fIsInitialized = true;		// CreatePropertiesCollection erfordert initialisiertes Objekt

// Properties-collection anlegen und initialisieren
	return CreatePropertiesCollection();
}

STDMETHODIMP CTRiASObjects::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Formatversion schreiben
	RETURN_FAILED_HRESULT(SaveLong(pStm, OBJECTS_SIGNATURE));
	RETURN_FAILED_HRESULT(SaveLong(pStm, LASTKNOWN_OBJECTS_VERSION));

// eigene Eigenschaften wegschreiben
	RETURN_FAILED_HRESULT(m_bstrName.WriteToStream (pStm));		// Name
	RETURN_FAILED_HRESULT(m_bstrDesc.WriteToStream (pStm));		// Description
	RETURN_FAILED_HRESULT(m_bstrOKS.WriteToStream (pStm));		// Objektklassenschlüssel

// folgendes erst ab OBJECTS_VERSION_101
	RETURN_FAILED_HRESULT(m_bstrDefaultGeom.WriteToStream (pStm));		// Name der PrimärGeometrie-Eigenschaft
	RETURN_FAILED_HRESULT(m_bstrPrimaryKey.WriteToStream (pStm));		// Name des eindeutigen Objektkennzeichens
	RETURN_FAILED_HRESULT(SaveLong (pStm, m_fOksIsIdent ? TRUE : FALSE));	// ist OKS gleichzeitig IDent ?

	RETURN_FAILED_HRESULT(SaveLong (pStm, (long &)m_rgType));	// Objekttypen
	RETURN_FAILED_HRESULT(SaveLong (pStm, (long &)m_rgCollType));	// Typ der collection

// wird ab OBJECTS_VERSION_102 nicht mehr benötigt
// Moniker des Containers dieses Objektes wegschreiben
//WMoniker mk;
//
//	RETURN_FAILED_HRESULT(GetContainerMoniker (mk.ppi()));
//	RETURN_FAILED_HRESULT(::OleSaveToStream (WPersistStream(mk), pStm));

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return TRIASDB_E_INVALID_PARAMETER;

WMoniker mk;

	RETURN_FAILED_HRESULT(GetContainerMoniker (mk.ppi()));		// ignore errors
	RETURN_FAILED_HRESULT(WPersistStream(mk) -> GetSizeMax (pcbSize));

	pcbSize -> QuadPart += LenForStream(m_bstrName) + LenForStream(m_bstrDesc) + 
						   LenForStream(m_bstrOKS) + LenForStream(m_bstrDefaultGeom) +
						   LenForStream(m_bstrPrimaryKey) + 5*sizeof(long);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit

STDMETHODIMP CTRiASObjects::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	m_fIsDirty = false;
	m_fIsInitialized = true;		// CreatePropertiesCollection erfordert initialisiertes Objekt

// Aggregat davon in Kenntnis setzen
	if (NULL != m_pICallback)
		m_pICallback -> SetupObjects (SETUPOBJECTSMODE_InitOrLoad);

// Properties-collection anlegen und initialisieren
	return S_OK;		// jetzt erst bei Bedarf: CreatePropertiesCollection();
}

///////////////////////////////////////////////////////////////////////////////
// liefert vollständigen DisplayName dieses Objektes
HRESULT CTRiASObjects::GetMkName (BSTR *pbstrMkName)
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
HRESULT CTRiASObjects::GetContainerMoniker (IMoniker **ppIMk)
{
	_ASSERTE(NULL != m_pIParent);

	COM_TRY {
	WDispatch Parent;
	WMoniker mk;

		if (FAILED(FindSpecificParent(m_pIParent, IID_ITRiASConnection, Parent.ppv()))) {
		// z.B. Zuordnungsobjektklassen haben das Projekt als Parent
			THROW_FAILED_HRESULT(FindSpecificParent(m_pIParent, IID_ITRiASProject, Parent.ppv()));
		}
		THROW_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mk.ppi()));
		*ppIMk = mk.detach();

	} COM_CATCH;
	return S_OK;
}

// Den vollständigen Moniker dieses Objektes liefern
HRESULT CTRiASObjects::GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk)
{
	_ASSERTE(NULL != m_pIParent);
	COM_TRY {
	WMoniker mk, mkThis, mkItem;
	CComBSTR bstrItem (g_cbMkObjectsDef);	// "!MkObjectsDef:[OKS]<ObjectsDef Name>"

		bstrItem.Append (g_cbColon);
		if (NULL != m_bstrOKS.m_str && m_bstrOKS.Length() > 0) {
		// kein OKS da, also Moniker ohne selbigen generieren
			bstrItem.Append (g_cbLBracket);
			bstrItem.Append (m_bstrOKS);
			bstrItem.Append (g_cbRBracket);
		}
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

		case OLEWHICHMK_CONTAINER:
			_ASSERTE(dwWhich != OLEWHICHMK_CONTAINER);

		// und durchfallen ...
		default:
			return E_INVALIDARG;
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASObjects::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Application");

	*pVal = m_pIParent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// das Nullsetzen des Parent wird als Signal zum Freigeben gewertet
// evtl. alle SubObjekte von ihrem Bezug abhängen
	if (NULL == newVal) {
	// Enumerator bzw. TRiASObject's freigeben
		if (!(OBJECTSCOLLECTIONTYPE_Query & m_rgCollType) && m_Enum.IsValid()) {
		// nur bei eigenen Objekten Parent abmelden
		WTRiASObject Obj;

			for (m_Enum -> Reset(); S_OK == m_Enum -> Next (1, &Obj, NULL); /**/)
			{
				Obj -> put_Parent (NULL);
			}
		}

	// evtl. abhängiges Objekt benachrichtigen
		if (m_pICallback) 
			m_pICallback -> OnFinalRelease();

	// Properties freigeben
		FreePropertiesCollection();

		m_Enum.Assign(NULL);
		m_lCount = INVALID_OBJECTCOUNT;

	// PropertySupportObjekte freigeben
		ReleasePropertySupportObjects();

	// Feature-Objekte freigeben
		if (m_Features.IsValid()) {
			m_Features -> SetEventSink (GetUnknown(), &m_dwFeatCookie, VARIANT_FALSE);
			m_Features -> putref_RelatedObject(NULL);
			m_Features -> put_Parent(NULL);
			m_Features.Assign(NULL);
		}

		if (m_GeometryFeatures.IsValid()) {
			m_GeometryFeatures -> SetEventSink (GetUnknown(), &m_dwGeoFeatCookie, VARIANT_FALSE);
			m_GeometryFeatures -> putref_RelatedObject(NULL);
			m_GeometryFeatures -> put_Parent(NULL);
			m_GeometryFeatures.Assign(NULL);
		}

	// aus Database-Tabelle entfernen
//		_ASSERTE(NULL != m_pIParent);
//
//	WTRiASObjectHandleMap MapP (GetPropertyFrom (m_pIParent, g_cbObjectsMap, (IDispatch *)NULL), false);
//
//		_ASSERTE(MapP.IsValid());
//		if (MapP.IsValid()) 
//			MapP -> RemoveObject ((LONG)m_hObjects, OBJECTMAPMODE_RemoveAllReferences);

		m_fIsDirty = false;
		m_fIsInitialized = false;	// muß neu initialisiert werden
	}

	m_pIParent = newVal;		// no AddRef (fully contained)
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Name");
	_ASSERTE(NULL != m_pIParent);

CComBSTR bstrName (m_bstrName);

	if (!bstrName)
		return REPORT_OUTOFMEMORY();

	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Description");
	_ASSERTE(NULL != m_pIParent);

CComBSTR bstrDesc (m_bstrDesc);

	if (!bstrDesc)
		return REPORT_OUTOFMEMORY();

	*pVal = bstrDesc.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_TableName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_TableName");
	_ASSERTE(NULL != m_pIParent);

HRESULT hr = E_FAIL;

	COM_TRY {
	CComBSTR bstrTableName;
	WTRiASConnection Conn;

		THROW_FAILED_HRESULT(FindSpecificParent (m_pIParent, Conn.ppi()));

	WTRiASMDSMap MDSMap (GetPropertyFrom(WTRiASPropertyBase(Conn), g_cbMetaDataMap, (IDispatch *)NULL), false);

		if (MDSMap.IsValid()) {
		// nicht alle Datenbanken haben einen MetaDatenService
			if (!m_bstrOKS || 0 == m_bstrOKS.Length())
				return E_UNEXPECTED;		// zu früh
			THROW_FAILED_HRESULT(MDSMap -> GetAt (m_bstrOKS, &bstrTableName, NULL, NULL, NULL));
		}

		if (!bstrTableName || 0 == bstrTableName.Length()) {
			bstrTableName = m_bstrName;		// Notanker
			hr = S_FALSE;
		} else
			hr = S_OK;

		if (!bstrTableName)
			return REPORT_OUTOFMEMORY();

		*pVal = bstrTableName.Detach();

	} COM_CATCH;
	return hr;
}

STDMETHODIMP CTRiASObjects::get_Updatable (VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Updatable");
	_ASSERTE(NULL != m_pIParent);

	*pVal = m_fUpdatable ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Updatable (VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	VARIANT_BOOL fModify = VARIANT_FALSE;
	VARIANT_BOOL fOldVal = m_fUpdatable ? VARIANT_TRUE : VARIANT_FALSE;

		if ((newVal ? true : false) ^ m_fUpdatable) {
			THROW_FAILED_HRESULT(Fire_ModifyingObjects (CHANGEDOBJECTS_ROMode, GetDispatch(), &fModify));
			if (fModify != VARIANT_FALSE)
				return S_FALSE;		// nicht umbenennen

			if (m_pICallback) {
			HRESULT hr = m_pICallback -> OnChanging (CHANGEDOBJECTS_ROMode, CComVariant(newVal), &fModify);

				if (FAILED(hr)) {
					if(TRIASDB_E_DATABASENOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (VARIANT_TRUE == fModify) 
					return S_FALSE;					// Aktion nicht durchführen
			}
			THROW_FAILED_HRESULT(Fire_ObjectsToModify (CHANGEDOBJECTS_ROMode, GetDispatch()));

			m_fUpdatable = newVal ? true : false;

			if (m_pICallback && !fModify)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECTS_ROMode, CComVariant(fOldVal)));

			THROW_FAILED_HRESULT(Fire_ObjectsModified(CHANGEDOBJECTS_ROMode, m_bstrName));
			m_fIsDirty = true;
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Count");
	_ASSERTE(NULL != m_pIParent);

	if (!HasCount()) {
		RETURN_FAILED_HRESULT(EnsureObjectsCount());
		_ASSERTE(HasCount());
	}

// evtl. ist der Zähler bereits initialisiert, ohne daß Objekte geladen sind
ULONG ulCntEnum = 0;

	RETURN_FAILED_HRESULT(m_Enum -> Count(&ulCntEnum));
	if (0 == ulCntEnum)
		*pVal = m_lCount;
	else
		*pVal = ulCntEnum;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Count(long newVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	_ASSERTE(NULL != m_pIParent);

	m_lCount = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	COM_TRY {
	CComBSTR bstr (newVal);
	CChangeValueHelper<CComBSTR> Helper (m_bstrName, bstr);

		if (bstr.Length() > 0 && !Helper) {
		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			THROW_FAILED_HRESULT(Fire_ModifyingObjects (CHANGEDOBJECTS_Name, GetDispatch(), &fModify));
			if (fModify)
				return S_FALSE;		// nicht umbenennen

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDOBJECTS_Name, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_DATABASENOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchführen
			}
			THROW_FAILED_HRESULT(Fire_ObjectsToModify (CHANGEDOBJECTS_Name, GetDispatch()));

			THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen

			if (m_pICallback && !fModify && S_OK == hr)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECTS_Name, Helper.GetOldValue()));

			THROW_FAILED_HRESULT(Fire_ObjectsModified(CHANGEDOBJECTS_Name, Helper.OldValue()));

			m_fIsDirty = true;
			Helper.SetValid();
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Description(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	COM_TRY {
	CComBSTR bstr (newVal);
	CChangeValueHelper<CComBSTR> Helper (m_bstrDesc, bstr);

		if (!Helper) {
		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			THROW_FAILED_HRESULT(Fire_ModifyingObjects (CHANGEDOBJECTS_Description, GetDispatch(), &fModify));
			if (fModify)
				return S_FALSE;		// nicht umbenennen

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDOBJECTS_Description, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_DATABASENOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchführen
			}
			THROW_FAILED_HRESULT(Fire_ObjectsToModify (CHANGEDOBJECTS_Description, GetDispatch()));

			THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen

			if (m_pICallback && !fModify && S_OK == hr)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECTS_Description, Helper.GetOldValue()));

			THROW_FAILED_HRESULT(Fire_ObjectsModified(CHANGEDOBJECTS_Description, m_bstrName));

			m_fIsDirty = true;
			Helper.SetValid();
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_Types (OBJECTTYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Name");
	_ASSERTE(NULL != m_pIParent);

// Abgleich der Objekttypen veranlassen
	if (m_pICallback && !IsSemaphoreSignaled (m_lSemData, *this)) {
	CComSemaphore<_ThreadModel> Sem (m_lSemData);	// Rekursion verhindern

		m_pICallback -> SetupObjects (SETUPOBJECTSMODE_Count);
	}

	*pVal = m_rgType;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Types (OBJECTTYPE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	_ASSERTE(NULL != m_pIParent);

	COM_TRY {
	CChangeValueHelper<LONG, OBJECTTYPE> Helper (m_rgType, newVal);

		if (!Helper) {
			if (!IsSemaphoreSignaled (m_lSemData, *this)) {
			CComSemaphore<_ThreadModel> Sem (m_lSemData);	// Rekursion verhindern

			// Zuweisung ist notwendig
			CComBool fModify;
			HRESULT hr  = S_OK;

				THROW_FAILED_HRESULT(Fire_ModifyingObjects (CHANGEDOBJECTS_Types, GetDispatch(), &fModify));
				if (fModify)
					return S_FALSE;		// nicht umbenennen

				if (m_pICallback) {
					hr = m_pICallback -> OnChanging (CHANGEDOBJECTS_Types, Helper.GetNewValue(), &fModify);
					if (FAILED(hr)) {
						if(TRIASDB_E_DATABASENOTUPDATABLE != hr) 
							return hr;						// Fehler
					} else if (fModify) 
						return S_FALSE;					// Aktion nicht durchführen
				}
				THROW_FAILED_HRESULT(Fire_ObjectsToModify (CHANGEDOBJECTS_Types, GetDispatch()));

				THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen

				if (m_pICallback && !fModify && S_OK == hr)
					THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECTS_Types, Helper.GetOldValue()));

				THROW_FAILED_HRESULT(Fire_ObjectsModified(CHANGEDOBJECTS_Types, m_bstrName));
			}
			else {
			// wird während get_Types --> SetupObjects (SETUPOBJECTSMODE_Count) --> put_Types
			// gerufen, also lediglich Wert zuweisen und raus
				THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen
			}

			m_fIsDirty = true;
			Helper.SetValid();
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_CollectionType (OBJECTSCOLLECTIONTYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_CollectionType");
	_ASSERTE(NULL != m_pIParent);

	*pVal = m_rgCollType;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_CollectionType (OBJECTSCOLLECTIONTYPE newVal)
{
	m_rgCollType = newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_Features(ITRiASFeatures **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Features");
	_ASSERTE(NULL != m_pIParent);

HRESULT hr = S_OK;

	if (!m_Features.IsValid()) {
		_ASSERTE(NULL != m_pICallback);		// Callbackinterface muß gesetzt sein
		RETURN_FAILED_HRESULT(m_pICallback -> SetupFeatures (
			SETUPFEATURESMODE(SETUPFEATURESMODE_Normal|SETUPFEATURESMODE_Force)));
		hr = S_FALSE;		// Collection neu erzeugt
	}

	_ASSERTE(m_Features.IsValid());
	if (m_Features.IsValid()) {
	WTRiASFeatures Feats (m_Features);

		*pVal = Feats.detach();
		return hr;
	}
	return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASObjects::get_Features");
}

STDMETHODIMP CTRiASObjects::get_Feature(VARIANT vItem, VARIANT_BOOL fCreate, BSTR Type, ITRiASFeature **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Feature");
	_ASSERTE(NULL != m_pIParent);

	if (!m_Features.IsValid()) {
		_ASSERTE(NULL != m_pICallback);		// Callbackinterface muß gesetzt sein
		RETURN_FAILED_HRESULT(m_pICallback -> SetupFeatures (
			SETUPFEATURESMODE(SETUPFEATURESMODE_Normal|SETUPFEATURESMODE_Force)));
	}
	_ASSERTE(m_Features.IsValid());

// evtl. FeatureHandle mappen (Unique Ident ist in GDO Tabellen-spezifisch)
CComVariant vName;
HRESULT hr = E_FAIL;

	if (NULL != m_pICallback) {
		hr = m_pICallback -> MapFeatureHandle (vItem, &vName);
		if (SUCCEEDED(hr)) {
			if (!V_ISI4(&vItem))
				hr = vName.ChangeType (VT_BSTR);
			else {
				vName = vItem;
				hr = E_FAIL;
			}
		}
	} else {
		if (!V_ISI4(&vItem))
			hr = vName.ChangeType (VT_BSTR);
		else 
			vName = vItem;
	}

	if (SUCCEEDED(hr) && !wcscmp (V_BSTR(&vName), g_cbPrimaryKey)) {
	// default Geometriefeld ist gefragt
		vName = m_bstrPrimaryKey;
		hr = m_Features -> Item (vName, pVal);
		if (TRIASDB_E_UNKNOWN_FEATURE == hr && fCreate) {

			hr = m_Features -> Add (vName, Type, FEATURETYPE_Object, pVal);
			if (S_OK == hr)	hr = S_FALSE;		// Feature neu erzeugt
		}
	} 
	else {
	// ein spezielles Feld ist gefordert
		hr = m_Features -> Item (vItem, pVal);
		if (TRIASDB_E_UNKNOWN_FEATURE == hr && fCreate && V_ISI4(&vItem)) {
		// ggf. muß über den Namen gesucht werden
		CComVariant v;

			RETURN_FAILED_HRESULT(v.ChangeType(VT_BSTR, &vItem));
			hr = m_Features -> Item (v, pVal);
		}

		if (TRIASDB_E_UNKNOWN_FEATURE == hr && fCreate) {
		CComVariant v (vItem);

		// vItem enthält entweder MCode oder Namen
			if (V_ISI4(&vItem) || SUCCEEDED(v.ChangeType (VT_BSTR))) {
				hr = m_Features -> Add (v, Type, FEATURETYPE_Object, pVal);
				if (S_OK == hr)	hr = S_FALSE;		// Feature neu erzeugt
			} 
		}
	}
	return hr;
}

HRESULT CTRiASObjects::BindNewFeatures (WTRiASFeatures &rFeats, ITRiASFeatures *pIFeats, DWORD *pdwCookie)
{
// bisherige Features loslassen
	if (rFeats.IsValid()) {
		rFeats -> SetEventSink (GetUnknown(), pdwCookie, VARIANT_FALSE);
		rFeats -> putref_RelatedObject(NULL);
		rFeats.Assign(NULL);
	}

	if (NULL == pIFeats)		// ist i.O.; Features sollen nur zerlegt werden
		return S_OK;

// neue Properties erst bei der alten Objektmenge abmelden, dann hier anmelden
	RETURN_FAILED_HRESULT(pIFeats -> put_Application (m_Application));
	RETURN_FAILED_HRESULT(pIFeats -> put_Parent (GetDispatch()));

//	RETURN_FAILED_HRESULT(pIFeats -> SetEventSink (NULL, pdwCookie, VARIANT_FALSE));
	RETURN_FAILED_HRESULT(pIFeats -> SetEventSink (GetUnknown(), pdwCookie, VARIANT_TRUE));
	RETURN_FAILED_HRESULT(pIFeats -> putref_RelatedObject(GetDispatch()));

	rFeats = pIFeats;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Features(ITRiASFeatures *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == newVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::put_Features");
	_ASSERTE(NULL != m_pIParent);

	if (NULL != newVal)
	{
		RETURN_FAILED_HRESULT(newVal -> put_FeaturesType (FEATURESTYPE_Attributes));
	}
	RETURN_FAILED_HRESULT(BindNewFeatures (m_Features, newVal, &m_dwFeatCookie));
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_GeometryFeatures(ITRiASFeatures **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_GeometryFeatures");
	_ASSERTE(NULL != m_pIParent);

	if (m_GeometryFeatures.IsValid()) {
	WTRiASFeatures Feats (m_GeometryFeatures);

		*pVal = Feats.detach();
		return S_OK;
	}
	return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASObjects::get_GeometryFeatures");
}

STDMETHODIMP CTRiASObjects::get_GeometryFeature(VARIANT vItem, VARIANT_BOOL fCreate, BSTR Type, ITRiASFeature **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_GeometryFeature");
	if (!m_GeometryFeatures.IsValid())
		return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASObjects::get_GeometryFeature");
	_ASSERTE(NULL != m_pIParent);

CComVariant vName;
HRESULT hr = vName.ChangeType (VT_BSTR, &vItem);

	if (SUCCEEDED(hr) && !wcscmp (V_BSTR(&vName), g_cbDefaultGeometry)) {
	// default Geometriefeld ist gefragt
		vName = m_bstrDefaultGeom;
		hr = m_GeometryFeatures -> Item (vName, pVal);
		if (TRIASDB_E_UNKNOWN_FEATURE == hr && fCreate) {
		CComVariant v;

			hr = m_GeometryFeatures -> Add (v, Type, FEATURETYPE_Object, pVal);
			if (S_OK == hr)	hr = S_FALSE;		// Feature neu erzeugt
		}
	} else {
	// ein spezielles Feld ist gefordert
		hr = m_GeometryFeatures -> Item (vName, pVal);
		if (TRIASDB_E_UNKNOWN_FEATURE == hr && fCreate) {
		CComVariant v;

			if (SUCCEEDED(v.ChangeType (VT_BSTR, &vItem))) {
				hr = m_GeometryFeatures -> Add (v, Type, FEATURETYPE_Object, pVal);
				if (S_OK == hr)	hr = S_FALSE;		// Feature neu erzeugt
			} 
		}
	}
	return hr;
}

STDMETHODIMP CTRiASObjects::put_GeometryFeatures(ITRiASFeatures *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == newVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::put_GeometryFeatures");
	_ASSERTE(NULL != m_pIParent);

	if (NULL != newVal)
	{
		RETURN_FAILED_HRESULT(newVal -> put_FeaturesType (FEATURESTYPE_Geometries));
	}
	RETURN_FAILED_HRESULT(BindNewFeatures (m_GeometryFeatures, newVal, &m_dwGeoFeatCookie));
	return S_OK;
}

STDMETHODIMP CTRiASObjects::Item (/*[in]*/ VARIANT vItem, /*[out, retval]*/ ITRiASObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	if (!IsLoaded())
		RETURN_FAILED_HRESULT(EnsureObjectsLoaded());

	COM_TRY {
	VARIANT_BOOL fDelete = VARIANT_FALSE;
	WTRiASObject Obj;
	CComVariant vIndex;
	INT_PTR hObjToFind = NULL;

	// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
		if (VT_I4 == V_VT(&vItem)) {
		// Handle ist direkt gegeben
			hObjToFind = V_I4(&vItem);
#if defined(_DEBUG)
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());

			THROW_FAILED_HRESULT(Map -> GetObject (hObjToFind, Obj.ppu()));
			_ASSERTE(SupportsInterface (Obj, (ITRiASObject *)NULL));
#endif // defined(_DEBUG)
		}
		else if (VT_DISPATCH == V_VT(&vItem)) {
		// Objekt ist direkt gegeben
			Obj = V_DISPATCH(&vItem);
			THROW_FAILED_HRESULT(Obj -> get_Handle (&hObjToFind));
		} 
		else if (VT_BSTR != V_VT(&vItem) && SUCCEEDED(vIndex.ChangeType (VT_I4, &vItem))) {
		// irgend etwas anderes ist gegeben, was sich (hoffentlich) als Handle heraustellt (snh)
			hObjToFind = V_I4(&vIndex);
#if defined(_DEBUG)
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());

			THROW_FAILED_HRESULT(Map -> GetObject (hObjToFind, Obj.ppu()));
			_ASSERTE(SupportsInterface (Obj, (ITRiASObject *)NULL));
#endif // defined(_DEBUG)
		}

		if (NULL != hObjToFind) {
		// Objekt wiederfinden
			if (S_OK == m_Enum -> FindItem (hObjToFind, &Obj)) {
				*ppIObj = Obj.detach();
				return S_OK;
			}
		} 
		else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &vItem))) {
		// Objekt herauslöschen
		WEnumWTRiASObject Enum;

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Obj, NULL); /**/)
			{
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Obj -> get_Name (CLEARED(&bstrName)));
				if (!wcscmp(bstrName, V_BSTR(&vIndex))) {
					*ppIObj = Obj.detach();
					return S_OK;		// gefunden
				}
			}
		}
	} COM_CATCH;
	return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::Item");
}

STDMETHODIMP CTRiASObjects::_NewEnum (/*[out, retval]*/ IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::_NewItem");
	_ASSERTE(NULL != m_pIParent);

	if (!IsLoaded())
		RETURN_FAILED_HRESULT(EnsureObjectsLoaded());
	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASObjects::Add (BSTR Name, BSTR Type, OBJECTTYPE rgType, ITRiASObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIObj) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::Add");
	_ASSERTE(NULL != m_pIParent);

	if (!IsLoaded())
		RETURN_FAILED_HRESULT(EnsureObjectsLoaded());

// Erzeugen eines neuen Objektes und hinzufügen zur Collection
	COM_TRY {
	// Überprüfen, ob Objekt bereits existiert
	WTRiASObject Obj;
		
		if (NULL != Name && SysStringLen(Name) > 0) {		// wenn Objektname gegeben ist
		WEnumWTRiASObject Enum;

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Obj, NULL); /**/)
			{
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Obj -> get_Name (CLEARED(&bstrName)));
				if (!wcscmp(bstrName, Name)) {
					*ppIObj = Obj.detach();
					return S_FALSE;		// existiert bereits
				}
			}
		}

	// darf erzeugt werden ?
	VARIANT_BOOL fCreate = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Fire_CreatingObject (Name, &fCreate));
		if (fCreate != VARIANT_FALSE)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_ObjectToCreate (Name));

		if (NULL != m_pICallback) {	// das eigentliche Objekt arbeiten lassen
		CIID ClsId (Type, CIID::INITCIID_InitFromProgId);
		CComBSTR bstrType;

			if (!ClsId)	{// default ClsId besorgen
				THROW_FAILED_HRESULT(m_pICallback -> get_DefaultType (CLEARED(&bstrType)));
			} else
				bstrType = Type;

			THROW_FAILED_HRESULT(m_pICallback -> OnCreate (Name, bstrType, rgType, Obj.ppi()));

			if (m_rgType != rgType)
				THROW_FAILED_HRESULT(put_Types ((OBJECTTYPE)(m_rgType | rgType)));
		}
		m_fIsDirty = true;

	// erfolgreich erzeugt
		THROW_FAILED_HRESULT(Fire_ObjectCreated (Obj));
		*ppIObj = Obj.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::_Add (ITRiASObject *newVal, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == newVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::_Add");
	_ASSERTE(NULL != m_pIParent);

// testen, ob dieses Objekt noch nicht in der collection enthalten ist
//	_ASSERTE(IsFirstOccurence (m_Enum, newVal, ITRiASObject::get_Handle, (INT_PTR *)NULL));

	if (NULL == m_hObjects)
		EnsureObjectsHandle (OBJECTMAPMODE_CreateObjectHandle);
	_ASSERTE(NULL != m_hObjects);

HRESULT hr = S_OK;

	if (OBJECTSCOLLECTIONTYPE_Class & m_rgCollType) {
		if (NULL != m_pICallback)	// das eigentliche Objekt arbeiten lassen
			hr = m_pICallback -> OnAdd (newVal, CLASSIFYMODE_DoNotClassify);

		if (E_NOTIMPL == hr)
			hr = S_FALSE;

		if (S_OK == hr || S_FALSE == hr) {
		// evtl. Objekttyp hier hinzufügen
		OBJECTTYPE rgType = OBJECTTYPE_Unknown;

			RETURN_FAILED_HRESULT(newVal -> get_Type (&rgType));
			if (OBJECTTYPE_Unknown != rgType)
			{
				RETURN_FAILED_HRESULT(put_Types (OBJECTTYPE(m_rgType | rgType)));
			}

		// Objekt dieser Objektklasse zuordnen
			if (fFullAdd)
				newVal -> put_ObjectsHandle ((long)m_hObjects);
		}
	}

	if (S_OK == hr || S_FALSE == hr) {
	INT_PTR hObj = NULL;

		RETURN_FAILED_HRESULT(newVal -> get_Handle (&hObj));
		RETURN_FAILED_HRESULT(m_Enum -> AddItem (hObj, newVal));
		m_fIsDirty = true;
		++m_lCount;
	}
	return hr;
}

STDMETHODIMP CTRiASObjects::_Reset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	m_fIsDirty = true;
	m_fIsLoaded = false;

	if (!(OBJECTSCOLLECTIONTYPE_Query & m_rgCollType) && m_Enum.IsValid()) {
	// nur bei eigenen Objekten Parent abmelden
	WTRiASObject Obj;

		for (m_Enum -> Reset(); S_OK == m_Enum -> Next (1, &Obj, NULL); /**/)
		{
			Obj -> put_Parent (NULL);
		}
	}

	m_Enum -> Clear();		// alles bisherige einfach vergessen
	m_lCount = INVALID_OBJECTCOUNT;
	m_rgType = OBJECTTYPE_Unknown;

	if (NULL != m_pICallback)
		m_pICallback -> SetupObjects (SETUPOBJECTSMODE_ResetObjectInfo);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Eine Objekteigenschaft doppeln
class CDeepCopyFeats
{
public:
	CDeepCopyFeats (ITRiASObject *pIObjSrc, ITRiASObject *pIObjDest, ITRiASFeatures *pIDest) : 
		m_Feats(pIDest), m_ObjSrc(pIObjSrc), m_ObjDest(pIObjDest) 
	{
	}

	HRESULT operator()(ITRiASFeature *pIFeat) 
	{
	// Objekteigenschaft erzeugen
	CComBSTR bstrName;
	FEATURETYPE rgType = FEATURETYPE_Unknown;

		RETURN_FAILED_HRESULT(pIFeat -> get_Name (CLEARED(&bstrName)));
		RETURN_FAILED_HRESULT(pIFeat -> get_Type (&rgType));
		
	WTRiASFeature Feat;

		RETURN_FAILED_HRESULT(m_Feats -> Add (CComVariant(bstrName), g_bstrNil, rgType, Feat.ppi()));

	// ist neue Objekteigenschaft schreibgeschützt ?
	VARIANT_BOOL fUpdatable = VARIANT_TRUE;

		RETURN_FAILED_HRESULT(Feat -> get_Updatable (&fUpdatable));
		if ( VARIANT_FALSE == fUpdatable)
			return S_FALSE;		// der nächste bitte

	// Werte umsetzen
	CComVariant vVal;

		if (SUCCEEDED(pIFeat -> Eval (m_ObjSrc, &vVal)))
		{
			RETURN_FAILED_HRESULT(Feat -> Update (m_ObjDest, vVal));
		}
		return S_OK;
	}

private:
	WTRiASFeatures m_Feats;
	WTRiASObject m_ObjSrc;
	WTRiASObject m_ObjDest;
};

///////////////////////////////////////////////////////////////////////////////
// Eine Geometrie-Objekteigenschaft doppeln
//class CDeepCopyGeoFeats
//{
//public:
//	CDeepCopyGeoFeats (ITRiASObject *pIObjSrc, ITRiASObject *pIObjDest, ITRiASFeatures *pIDest) : 
//		m_Feats(pIDest), m_ObjSrc(pIObjSrc), m_ObjDest(pIObjDest), m_sa(VT_VARIANT, 3)
//	{
//	CSafeArrayLock<VARIANT> lock(m_sa);
//
//	// der erste optionale Parameter enthält bei der Rückkehr den CS-Guid
//		V_VT(&lock[EVALEXPARAM_CoordSysGuid]) = VT_ERROR;
//		V_ERROR(&lock[EVALEXPARAM_CoordSysGuid]) = DISP_E_PARAMNOTFOUND;
//
//	// der zweite optionale Parameter enthält evtl. Suchfenster, 
//	// hier NULL da die Geometrie immer gebraucht wird
//		V_VT(&lock[EVALEXPARAM_Window]) = VT_ERROR;
//		V_ERROR(&lock[EVALEXPARAM_Window]) = DISP_E_PARAMNOTFOUND;
//
//	// dritter optionaler Parameter enthält bei Rückkehr evtl. Objektcontainer
//		V_VT(&lock[EVALEXPARAM_Envelope]) = VT_ERROR;
//		V_ERROR(&lock[EVALEXPARAM_Envelope]) = DISP_E_PARAMNOTFOUND;
//	}
//
//	HRESULT operator()(ITRiASFeature *pIFeat) 
//	{
//	// Objekteigenschaft erzeugen
//	CComBSTR bstrName;
//	FEATURETYPE rgType = FEATURETYPE_Unknown;
//
//		RETURN_FAILED_HRESULT(pIFeat -> get_Name (CLEARED(&bstrName)));
//		RETURN_FAILED_HRESULT(pIFeat -> get_Type (&rgType));
//		
//	WTRiASFeature Feat;
//
//		RETURN_FAILED_HRESULT(m_Feats -> Add (CComVariant(bstrName), g_bstrNil, rgType, Feat.ppi()));
//
//	// ist neue Geo-Objekteigenschaft schreibgeschützt ?
//	VARIANT_BOOL fUpdatable = VARIANT_TRUE;
//
//		RETURN_FAILED_HRESULT(Feat -> get_Updatable (&fUpdatable));
//		if (!fUpdatable)
//			return S_FALSE;		// der nächste bitte
//
//	// Wert umsetzen
//	SAFEARRAY *psa = m_sa;
//	CComVariant	vGeometry;
//		
//		if (SUCCEEDED(pIFeat -> EvalEx (m_ObjSrc, &psa, &vGeometry))) {
//		// ohne Geometrie ist es sinnlos
//			RETURN_EXPR_FALSE(V_ISDISPATCH(&vGeometry), E_FAIL);
//
//		WTRiASCloneGeometry	geoClone;
//		WDispatch geoObject;
//
//			RETURN_FAILED_HRESULT(V_DISPATCH(&vGeometry) -> QueryInterface (geoClone.ppi()));
//			RETURN_FAILED_HRESULT(geoClone -> Clone (geoObject.ppi()));
//
//		// jetzt die Geometrie zurückschreiben
//			RETURN_FAILED_HRESULT(Feat -> Update (m_ObjDest, CComVariant(geoObject)));
//		}
//		return S_OK;
//	}
//
//private:
//	WTRiASFeatures m_Feats;
//	WTRiASObject m_ObjSrc;
//	WTRiASObject m_ObjDest;
//	CSafeArray m_sa;			// enthält 3 Parameter
//};

// Objekt hierhin umklassifizieren
STDMETHODIMP CTRiASObjects::Classify (ITRiASObject *pIObj, CLASSIFYMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObj)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::Classify");
	_ASSERTE(NULL != m_pIParent);

	if (NULL == m_hObjects) 
		EnsureObjectsHandle (OBJECTMAPMODE_CreateObjectHandle);
	_ASSERTE(NULL != m_hObjects);

// wenns bereits zu uns gehört, dann schnell wieder raus
HOBJECTS hObjs = NULL;

	RETURN_FAILED_HRESULT(pIObj -> get_ObjectsHandle ((INT_PTR *)&hObjs));
	if (m_hObjects == hObjs && !HasType (rgMode, CLASSIFYMODE_InitObjectType))
		return S_FALSE;

	if (!IsLoaded())
		RETURN_FAILED_HRESULT(EnsureObjectsLoaded());

// evtl. nur innerhalb der Datenquelle umklassifizieren
	if (HasType (rgMode, CLASSIFYMODE_DatasourceOnly)) {
	WTRiASDatabase ParentSrc, ParentDest;

		RETURN_FAILED_HRESULT(FindSpecificParent (pIObj, ParentSrc.ppi()));
		RETURN_FAILED_HRESULT(FindSpecificParent (m_pIParent, ParentDest.ppi()));
		if (ParentSrc != ParentDest)	// kann nicht umklassifizieren, da andere Datenquelle
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::Classify");
	}

// zuerst das Targetobjekt befragen, ob es die Aktion durchführen will
CComBSTR bstrType;

	m_fIsDirty = true;
	if (NULL != m_pICallback) {
	HRESULT hr = m_pICallback -> OnAdd (pIObj, rgMode);

		if (E_NOTIMPL != hr) 
			return hr;		// ok, erledigt oder Fehler

		RETURN_FAILED_HRESULT(m_pICallback -> get_DefaultType (CLEARED(&bstrType)));
	}

// ansonsten alles selbst machen (wie immer)
	if (CLASSIFYMODE_DoNotClassify == rgMode || HasType (rgMode, CLASSIFYMODE_InitObjectType))
		return S_OK;	// keine Umklassifizierung vornehmen, lediglich testen, ob was zu tun wäre

// wenn Datenquelle oder Zieltabelle schreibgeschützt ist, dann mit Fehler raus
	if (!m_fUpdatable)
	{
		RETURN_FAILED_HRESULT(TRIASDB_E_DATABASENOTUPDATABLE);
	}

// dazu Objekt neu erzeugen
CComBSTR bstrName;
OBJECTTYPE rgObjType = OBJECTTYPE_Unknown;
WTRiASObject NewObj;

	RETURN_FAILED_HRESULT(pIObj -> get_Name (CLEARED(&bstrName)));
	RETURN_FAILED_HRESULT(pIObj -> get_Type (&rgObjType));
	RETURN_FAILED_HRESULT(Add (bstrName, bstrType, rgObjType, NewObj.ppi()));

// (1) alle Objekteigenschaften umkopieren
WTRiASFeatures FeatsSrc, FeatsDest;

	if (FAILED(pIObj -> get_Features (FeatsSrc.ppi()))) 
	{
		RETURN_FAILED_HRESULT(get_Features (FeatsSrc.ppi()));
	}
	RETURN_FAILED_HRESULT(NewObj -> get_Features (FeatsDest.ppi()));

	for_each (InEnumFeats(FeatsSrc), InEnumFeats(), CDeepCopyFeats(pIObj, NewObj, FeatsDest));

#pragma MESSAGE("TODO: Geometrie-Objekteigenschaften generisch kopieren!")

// (2) Geometrie umkopieren
CComVariant vVal;
CSafeArray sa (VT_VARIANT, 3);		// enthält 2 Parameter

	{
	CSafeArrayLock<VARIANT> lock(sa);

	// der erste optionale Parameter enthält bei der Rückkehr den CS-Guid
		V_VT(&lock[EVALEXPARAM_CoordSysGuid]) = VT_ERROR;
		V_ERROR(&lock[EVALEXPARAM_CoordSysGuid]) = DISP_E_PARAMNOTFOUND;

	// der zweite optionale Parameter enthält evtl. Suchfenster, hier NULL da die Geometrie immer gebraucht wird
		V_VT(&lock[EVALEXPARAM_Window]) = VT_ERROR;
		V_ERROR(&lock[EVALEXPARAM_Window]) = DISP_E_PARAMNOTFOUND;

	// dritter optionaler Parameter enthält bei Rückkehr evtl. Objektcontainer
		V_VT(&lock[EVALEXPARAM_Envelope]) = VT_ERROR;
		V_ERROR(&lock[EVALEXPARAM_Envelope]) = DISP_E_PARAMNOTFOUND;
	}

// (1a) Geometrie vom Quellobjekt besorgen
WTRiASObjects pTRiASObjects;
WTRiASFeature pTRiASGeoFeature;
CComBSTR strGeometry;

	RETURN_FAILED_HRESULT(FindSpecificParent( pIObj, pTRiASObjects.ppi() ) );
	RETURN_FAILED_HRESULT(pTRiASObjects->get_DefaultGeometry( CLEARED(strGeometry) ) );
	RETURN_FAILED_HRESULT(pTRiASObjects->get_GeometryFeature(CComVariant(strGeometry), VARIANT_FALSE, CComBSTR(g_cbNil), pTRiASGeoFeature.ppi()));

SAFEARRAY *psa = sa;
CComVariant	vGeometry;
	
	RETURN_FAILED_HRESULT(pTRiASGeoFeature->EvalEx(pIObj, &psa, &vGeometry));	// ohne Geometrie ist es sinnlos, also gleich zurück
	RETURN_EXPR_FALSE(V_ISDISPATCH(&vGeometry), E_FAIL);

// (1b) selbige kopieren
WTRiASCloneGeometry	geoClone;
WDispatch geoObject;

	RETURN_FAILED_HRESULT(V_DISPATCH(&vGeometry) -> QueryInterface (geoClone.ppi()));
	RETURN_FAILED_HRESULT(geoClone -> Clone (geoObject.ppi()));

// (1c) jetzt die Geometrie an meinem Objekt zurückschreiben
	RETURN_FAILED_HRESULT(get_GeometryFeature(CComVariant(m_bstrDefaultGeom), VARIANT_FALSE, CComBSTR(g_cbNil), pTRiASGeoFeature.ppi()));
	vGeometry = CComVariant(geoObject);
	RETURN_FAILED_HRESULT(pTRiASGeoFeature->Update(NewObj, vGeometry));

// (2) jetzt alle Geometrie-Objekteigenschaften umkopieren
//	if (FAILED(pIObj -> get_GeometryFeatures (FeatsSrc.ppi()))) 
//	{
//		RETURN_FAILED_HRESULT(get_GeometryFeatures (FeatsSrc.ppi()));
//	}
//	RETURN_FAILED_HRESULT(NewObj -> get_GeometryFeatures (FeatsDest.ppi()));
//
//	for_each (InEnumFeats(FeatsSrc), InEnumFeats(), CDeepCopyGeoFeats(pIObj, NewObj, FeatsDest));

// altes Objekt löschen
WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());
WTRiASObjects Objs;

	RETURN_FAILED_HRESULT(Map -> GetObject ((INT_PTR)hObjs, Objs.ppu()));

// Objekt löschen, altes Handle beibehalten
INT_PTR hObj = NULL;

	RETURN_FAILED_HRESULT(pIObj -> get_Handle (&hObj));
	RETURN_FAILED_HRESULT(Objs -> Delete (CComVariant(pIObj)));
	RETURN_FAILED_HRESULT(NewObj -> put_Handle (hObj));

#if defined(_DEBUG)
// das neue Objekt muß das Handle des alten Objektes haben
INT_PTR hObjNew = NULL;

	RETURN_FAILED_HRESULT(NewObj -> get_Handle (&hObjNew));
	_ASSERTE(hObj == hObjNew);
#endif // defined(_DEBUG)

	return S_OK;
}

// Objekt aus Objektmenge entfernen
STDMETHODIMP CTRiASObjects::_Remove (VARIANT vWhich)
{
	return RemoveDeleteHelper (vWhich, false);		// nicht wirklich löschen, nur entfernen
}

// Objekt (physisch) löschen
STDMETHODIMP CTRiASObjects::Delete (VARIANT vWhich)
{
	return RemoveDeleteHelper (vWhich, true);		// wirklich löschen
}

HRESULT CTRiASObjects::RemoveDeleteHelper (VARIANT vWhich, bool fForceDelete)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!IsLoaded())
		RETURN_FAILED_HRESULT(EnsureObjectsLoaded());

HRESULT hr_return = S_OK;

	COM_TRY {
	VARIANT_BOOL fDelete = VARIANT_FALSE;
	WTRiASObject Obj;
	CComVariant vIndex;
	INT_PTR hObjToRemove = NULL;
#if defined(_DEBUG)
	ULONG ulCount = m_lCount;
#endif // defined(_DEBUG)

	// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
		if (VT_I4 == V_VT(&vWhich)) {
		// Handle ist direkt gegeben
			hObjToRemove = V_I4(&vWhich);

		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());

			THROW_FAILED_HRESULT(Map -> GetObject (hObjToRemove, Obj.ppu()));
			_ASSERTE(SupportsInterface (Obj, (ITRiASObject *)NULL));
		}
		else if (VT_DISPATCH == V_VT(&vWhich)) {
		// Objekt ist direkt gegeben
			Obj = V_DISPATCH(&vWhich);
			THROW_FAILED_HRESULT(Obj -> get_Handle (&hObjToRemove));
		} 
		else if (VT_BSTR != V_VT(&vWhich) && SUCCEEDED(vIndex.ChangeType (VT_I4, &vWhich))) {
		// irgend etwas anderes ist gegeben, was sich (hoffentlich) zu einem Handle machen läßt (snh)
			hObjToRemove = V_I4(&vIndex);

		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());

			THROW_FAILED_HRESULT(Map -> GetObject (hObjToRemove, Obj.ppu()));
			_ASSERTE(SupportsInterface (Obj, (ITRiASObject *)NULL));
		}

		if (NULL != hObjToRemove) {
#if defined(_DEBUG)
		ULONG ulCntDeb = 0L;
		
			THROW_FAILED_HRESULT(m_Enum -> Count(&ulCntDeb));
#endif // _DEBUG

		// Objekt herauslöschen
			if (fForceDelete) {
				THROW_FAILED_HRESULT(Fire_DeletingObject (Obj, &fDelete));
				if (fDelete == VARIANT_FALSE) {
					THROW_FAILED_HRESULT(Fire_ObjectToDelete (Obj));
					THROW_FAILED_HRESULT(OnDelete ((HOBJECT)hObjToRemove));
				} else
					hr_return = S_FALSE;
			} 
			else {
				THROW_FAILED_HRESULT(OnRemove (Obj));
			}
			THROW_FAILED_HRESULT(m_Enum -> RemoveItem (hObjToRemove));

//			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
//			THROW_FAILED_HRESULT(m_Enum -> Clear());
//
//		// alle außer dem einen Kopieren
//			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Obj, NULL); /**/)
//			{
//			INT_PTR hObj = NULL;
//
//				THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));
//				if (hObj == hObjToRemove) {
//					if (fForceDelete) {
//						THROW_FAILED_HRESULT(Fire_DeletingObject (Obj, &fDelete));
//						if (fDelete == VARIANT_FALSE) {
//							THROW_FAILED_HRESULT(Fire_ObjectToDelete (Obj));
//							THROW_FAILED_HRESULT(OnDelete ((HOBJECT)hObj));
//							continue;
//						}
//					// wenn nicht gelöscht werden soll, dann einfach durchfallen
//					// ...
//						hr_return = S_FALSE;
//					} else {
//						THROW_FAILED_HRESULT(OnRemove (Obj));
//						continue;
//					}
//				} 
//				THROW_FAILED_HRESULT(m_Enum -> AddItem(Obj));
//			}

#if defined(_DEBUG)
		ULONG ulCntDebN = 0L;
		
			THROW_FAILED_HRESULT(m_Enum -> Count(&ulCntDebN));
			_ASSERTE(S_FALSE == hr_return || 0 == ulCntDeb || ulCntDeb == ulCntDebN + 1);
#endif // _DEBUG
		} 
		else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &vWhich))) {
		// Objekt herauslöschen
		WEnumWTRiASObject Enum;

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(m_Enum -> Clear());

		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Obj, NULL); /**/)
			{
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Obj -> get_Name (CLEARED(&bstrName)));
				if (!wcscmp(bstrName, V_BSTR(&vIndex))) {
					if (fForceDelete) {
						THROW_FAILED_HRESULT(Fire_DeletingObject (Obj, &fDelete));
						if (fDelete == VARIANT_FALSE) {
							THROW_FAILED_HRESULT(Fire_ObjectToDelete (Obj));

						INT_PTR hObj = NULL;

							THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));
							THROW_FAILED_HRESULT(OnDelete ((HOBJECT)hObj));
							continue;
						}
					// wenn nicht gelöscht werden soll, dann einfach durchfallen
					// ...
						hr_return = S_FALSE;
					} else {
						THROW_FAILED_HRESULT(OnRemove (Obj));
						continue;
					}
				} 

			INT_PTR hObj = NULL;

				THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));
				THROW_FAILED_HRESULT(m_Enum -> AddItem(hObj, Obj));
			}

#if defined(_DEBUG)
		ULONG ulCntDeb = 0L;
		ULONG ulCntDebN = 0L;
		
			THROW_FAILED_HRESULT(m_Enum -> Count(&ulCntDeb));
			THROW_FAILED_HRESULT(Enum -> Count(&ulCntDebN));
			_ASSERTE(S_FALSE == hr_return || 0 == ulCntDebN || ulCntDebN == ulCntDeb + 1);
#endif // _DEBUG
		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::RemoveDeleteHelper");

	// erfolgreich gelöscht
		if (fForceDelete)
			THROW_FAILED_HRESULT(Fire_ObjectDeleted (NULL));
		m_fIsDirty = true;		// collection ist jetzt dirty

// Zähler sollte schon zwischdurch mit put_count korrigiert sein
#if defined(_DEBUG)
		ulCount = m_lCount+1;
#endif // defined(_DEBUG)

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::SetEventSink (/*[in]*/ IUnknown *Unk, /*[in]*/ VARIANT_BOOL fAdvise)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObjects::SetEventSink");
}

STDMETHODIMP CTRiASObjects::Refresh ()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_fIsDirty = true;

// rücksetzen der internen Datenstrukturen
	_Reset();

// und neu einlesen
	_ASSERTE(!m_fIsLoaded);
//	return EnsureObjectsLoaded();
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_Handle (INT_PTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_Handle");
	_ASSERTE(NULL != m_pIParent);

	if (NULL == m_hObjects) 
		EnsureObjectsHandle (OBJECTMAPMODE_CreateObjectHandle);

	*pVal = (LONG)m_hObjects;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_Handle (INT_PTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	if (NULL == m_hObjects || m_hObjects != (HOBJECTS)newVal) {
		EnsureObjectsHandle (OBJECTMAPMODE(OBJECTMAPMODE_CreateObjectHandle|OBJECTMAPMODE_UsePredefinedHandle), (HOBJECTS)newVal);
		return S_OK;
	}
	return S_FALSE;		// Zugriffsnummer wurde bereits vergeben
}

HRESULT CTRiASObjects::EnsureObjectsHandle (OBJECTMAPMODE rgMode, HOBJECTS hObjsNew)
{
// erstes Mal benötigt
	COM_TRY {
	CChangeValueHelper<INT_PTR, HOBJECTS> Helper (m_hObjects, hObjsNew);

		if (!(rgMode & OBJECTMAPMODE_UsePredefinedHandle) || !Helper) {
		// Moniker-DisplayName generieren
		CComBSTR bstrName;

			if (OBJECTSCOLLECTIONTYPE_Temporary & m_rgCollType || FAILED(GetMkName (CLEARED(&bstrName)))) {
				bstrName = g_cbMkObjectsDef;
				bstrName.Append(g_cbColon);
				bstrName.Append(m_bstrName);
				bstrName.Append(g_cbColon);
				bstrName.Append(CComBSTR(CIID()));	// eindeutigen Namen erzeugen
			}
			if (!bstrName)
				_com_issue_error(E_OUTOFMEMORY);

		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDOBJECTS_Handle, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_DATABASENOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchführen
			}

		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());		// throws hr
		INT_PTR hObjs = Helper.NewValue();

			_ASSERTE(sizeof(LONG) == sizeof(HOBJECTS));
			THROW_FAILED_HRESULT(Map -> GetObjectHandle (CComVariant(bstrName), GetUnknown(), rgMode, &hObjs));
			THROW_FAILED_HRESULT(Helper.Assign (hObjs));

			if (m_pICallback && !fModify && S_OK == hr) {
			HRESULT hr = m_pICallback -> OnChanged (CHANGEDOBJECTS_Handle, Helper.GetOldValue());

				if (FAILED(hr)) {
					Map -> RemoveObject ((LONG)hObjs, OBJECTMAPMODE_RemoveAllReferences);		// fehler nicht fatal
					THROW_FAILED_HRESULT(hr);
				}
			}
			m_fIsDirty = true;
			Helper.SetValid();
		}
	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_OKS(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_OKS");
	_ASSERTE(NULL != m_pIParent);

	if (!m_bstrOKS || 0 == m_bstrOKS.Length()) {
		_ASSERTE(m_fOksIsIdent);
	
		if (NULL == m_hObjects)
			EnsureObjectsHandle (OBJECTMAPMODE_CreateObjectHandle);
		_ASSERTE(NULL != m_hObjects);

	char cbBuffer[64];

		if (10 == GetPropertyFrom (m_pIParent, g_cbIdentBaseHdr, 16L, LOCALE_ENGLISH)) 
			wsprintf (cbBuffer, "%lu", m_hObjects);
		else 
			wsprintf (cbBuffer, "%lx", m_hObjects);
		m_bstrOKS = cbBuffer;
	}

CComBSTR bstrOKS (m_bstrOKS);

	if (!bstrOKS)
		return REPORT_OUTOFMEMORY();

	*pVal = bstrOKS.Detach();
	return m_fOksIsIdent ? S_FALSE : S_OK;
}

STDMETHODIMP CTRiASObjects::put_OKS(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	COM_TRY {
	CComBSTR bstr;

		if (StringIsOKS (newVal, CLEARED(&bstr))) {
		CChangeValueHelper<CComBSTR> Helper (m_bstrOKS, bstr);

			if (bstr.Length() > 0 && !Helper) {
			// Zuweisung ist notwendig
			CComBool fModify;
			HRESULT hr = S_OK;

				THROW_FAILED_HRESULT(Fire_ModifyingObjects (CHANGEDOBJECTS_OKS, GetDispatch(), &fModify));
				if (fModify)
					return S_FALSE;		// nicht umbenennen

				if (m_pICallback) {
					hr = m_pICallback -> OnChanging (CHANGEDOBJECTS_OKS, Helper.GetNewValue(), &fModify);
					if (FAILED(hr)) {
						if(TRIASDB_E_DATABASENOTUPDATABLE != hr) 
							return hr;						// Fehler
					} else if (fModify) 
						return S_FALSE;					// Aktion nicht durchführen
				}
				THROW_FAILED_HRESULT(Fire_ObjectsToModify (CHANGEDOBJECTS_OKS, GetDispatch()));

				THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen
				m_fOksIsIdent = false;

				if (m_pICallback && !fModify && S_OK == hr)
					THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECTS_OKS, Helper.GetOldValue()));

				THROW_FAILED_HRESULT(Fire_ObjectsModified(CHANGEDOBJECTS_OKS, m_bstrName));

				m_fIsDirty = true;
				Helper.SetValid();
			}
		} else {
			bstr = newVal;

		CChangeValueHelper<CComBSTR> Helper (m_bstrOKS, bstr);

			if (bstr.Length() > 0 && !Helper) {
			// Zuweisung ist notwendig
			CComBool fModify;
			HRESULT hr = S_OK;

				if (m_pICallback) {
					hr = m_pICallback -> OnChanging (CHANGEDOBJECTS_OKS, Helper.GetNewValue(), &fModify);
					if (FAILED(hr)) {
						if(TRIASDB_E_DATABASENOTUPDATABLE != hr) 
							return hr;						// Fehler
					} else if (fModify) 
						return S_FALSE;					// Aktion nicht durchführen
				}

				THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen
				m_fOksIsIdent = false;

				if (m_pICallback && !fModify && S_OK == hr)
					THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDOBJECTS_OKS, Helper.GetOldValue()));

				m_fIsDirty = true;
				Helper.SetValid();
			}
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_DefaultGeometry(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_DefaultGeometry");
	_ASSERTE(NULL != m_pIParent);

CComBSTR bstrGeom (m_bstrDefaultGeom);

	if (!bstrGeom)
		return REPORT_OUTOFMEMORY();

	*pVal = bstrGeom.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_DefaultGeometry(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	m_bstrDefaultGeom = newVal;
	if (!m_bstrDefaultGeom)
		return REPORT_OUTOFMEMORY();
	return S_OK;
}

STDMETHODIMP CTRiASObjects::get_PrimaryKey(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::get_PrimaryKey");
	_ASSERTE(NULL != m_pIParent);

CComBSTR bstrGeom (m_bstrPrimaryKey);

	if (!bstrGeom)
		return REPORT_OUTOFMEMORY();

	*pVal = bstrGeom.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASObjects::put_PrimaryKey(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	m_bstrPrimaryKey = newVal;
	if (!m_bstrPrimaryKey)
		return REPORT_OUTOFMEMORY();
	return S_OK;
}

STDMETHODIMP CTRiASObjects::_Clone (/*[out, retval]*/ ITRiASObjects **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::_Clone");
	_ASSERTE(NULL != m_pIParent);

	if (!IsLoaded())
		RETURN_FAILED_HRESULT(EnsureObjectsLoaded());

CComObject<CTRiASObjects> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASObjects>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));

	HOBJECTS hObjects = NULL;

		_ASSERTE(sizeof(LONG) == sizeof(HOBJECTS));	// ensure correctness of the following cast
		if (SUCCEEDED(get_Handle ((INT_PTR *)&hObjects)))
			pNew -> SetObjectsHandle (hObjects);

		THROW_FAILED_HRESULT(pNew -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pNew -> put_Parent (m_pIParent));
		THROW_FAILED_HRESULT(pNew -> put_CollectionType(m_rgCollType));
		THROW_FAILED_HRESULT(pNew -> put_Types(m_rgType));
		THROW_FAILED_HRESULT(pNew -> put_Name (m_bstrName));
		if (NULL != m_bstrOKS.m_str)
		{
			THROW_FAILED_HRESULT(pNew -> put_OKS (m_bstrOKS));
		}

	WTRiASObjects Objs (pNew);		// pending AddRef

		*pVal = Objs.detach();

	} COM_CATCH_OP(delete pNew);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Recherchefunktionalität

// Generieren und initialisieren des entsprechenden Match-Objektes
/* static */
HRESULT CTRiASObjects::GetMatchObject (BSTR bstrCommand, BSTR bstrPattern, DMatchString **ppIMatch)
{
	if (NULL == ppIMatch) return E_POINTER;

// je nach gewählten Optionen das richtige MatchObjekt generieren
WDMatchString Match;

	COM_TRY {
	int iMode = MainModeFromSearchCommand(bstrCommand);
	int iSubMode = ModeFromSearchCommand(bstrCommand);

		if (SMRegularExpression == iMode) {
		// mit RegularExpressions suchen
			Match = WDMatchString (CLSID_MatchRegExprExakt);
			WMatchRegExpr(Match) -> put_FullMatch ((SMSubstringMatch == iSubMode) ? VARIANT_TRUE : VARIANT_FALSE);
		} 
		else if (SMInexactMatch == iMode) {
		// ungefähres Matching
			Match = WDMatchString (CLSID_MatchFuzzy);
		} 
		else {
		// Text vollständig wiederfinden (bzw. Textanfang)
			Match = WDMatchString (CLSID_MatchPlainTextExakt);

		WMatchPlainText MatchTxt(Match);

			MatchTxt -> put_ExistanceOnly ((SMExistanceOnly == iSubMode) ? VARIANT_TRUE : VARIANT_FALSE);
			MatchTxt -> put_FullMatch ((SMSubstringMatch == iSubMode) ? VARIANT_FALSE : VARIANT_TRUE);
			MatchTxt -> put_TestBOB ((SMSubStringStartMatch == iSubMode) ? VARIANT_TRUE : VARIANT_FALSE);
		}

	// zu suchenden Text setzen
		THROW_FAILED_HRESULT(Match -> put_MatchText (bstrPattern));
		THROW_FAILED_HRESULT(Match -> put_MatchCase ((iSubMode & SMIgnoreCase) ? VARIANT_FALSE : VARIANT_TRUE));
		THROW_FAILED_HRESULT(Match -> put_NegateMatch ((iSubMode & SMNegateResult) ? VARIANT_TRUE : VARIANT_FALSE));

	} COM_CATCH;

	*ppIMatch = Match.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt löschen
HRESULT CTRiASObjects::OnDelete(HOBJECT hObj)
{
WDispatch Parent;

	if (OBJECTSCOLLECTIONTYPE_Query & m_rgCollType)
		return S_FALSE;		// Objekt nicht physisch löschen, da dies hier keine Tabelle ist

// erstmal die Objektklasse fragen, obs sie's tun will (getan hat)
HRESULT hr = S_FALSE;

	m_fIsDirty = true;
	if (NULL != m_pICallback) {		// das eigentliche Objekt informieren
		hr = m_pICallback -> OnDelete ((INT_PTR)hObj);
		if (S_FALSE != hr && E_NOTIMPL != hr)
			return hr;		// S_FALSE heißt: nicht hier
	}

// jetzt Objekt selbst bemühen
WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());	// GetProperty liefert AddRef'ed ab
WTRiASObject Obj;

	if (Map.IsValid() && SUCCEEDED(Map -> GetObject ((INT_PTR)hObj, Obj.ppu()))) {
		_ASSERTE(SupportsInterface (Obj, (ITRiASObject *)NULL));

		RETURN_FAILED_HRESULT(Obj -> Delete());
		return S_OK;
	}

	RETURN_FAILED_HRESULT(E_UNEXPECTED);		// einer muß es ja machen
	return S_OK;		// sonst mault der compilator (it's braindead)
}

// Objekt entfernen
HRESULT CTRiASObjects::OnRemove (ITRiASObject *pIObj)
{
	m_fIsDirty = true;

HRESULT hr = S_OK;

	if (NULL != m_pICallback) {
	// das eigentliche Objekt informieren
		RETURN_FAILED_HRESULT(hr = m_pICallback -> OnRemove (pIObj));
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSearchObjects
STDMETHODIMP CTRiASObjects::ConsiderSearch (BSTR bstrCommand, SAFEARRAY * /*pParams*/)
{
	_ASSERTE(NULL != m_pIParent);

	if (!wcscmp(bstrCommand, SEARCHCOMMAND_IntersectsWindow))
		return TRIASDB_S_SEARCH_NOT_SUPPORTED;

	return S_OK;	// beliebige (außer Geometrie-)Recherchen werden sequentiell unterstützt
}

// Eine bestimmte Objekteigenschaft liefern
HRESULT CTRiASObjects::GetSearchFeature (SAFEARRAY *pParams, ITRiASFeature **ppIFeat)
{
	_ASSERTE(NULL != ppIFeat);
	_ASSERTE(NULL != m_pIParent);

	COM_TRY {
	// Objekteigenschaft aus Parameterfeld herauslösen
	CSafeArray sa(VT_VARIANT);

		if (NULL == pParams || !sa.Attach (pParams, true)) 
			return E_INVALIDARG;

	CSafeArrayLock<VARIANT> lock(sa);
	WTRiASFeature Feat;

		if (VT_DISPATCH == V_VT(&lock[1])) {
		// Objekteigenschaft ist direkt gegeben
			Feat = WTRiASFeature (V_DISPATCH(&lock[1]));
		} 
		else {
		// Objekteigenschaft auf üblichem Wege besorgen
		HRESULT hr = get_Feature (lock[1], VARIANT_FALSE, g_bstrNil, Feat.ppi());

			if (FAILED(hr))
				return hr;	// evtl. gehört die Objekteigenschaft mit diesem MCode nicht zu dieser ObjKlassse
		}
		*ppIFeat = Feat.detach();

	} COM_CATCH;
	return S_OK;
}

// PredikatKlasse, die die eigentliche Recherche im 'remove_copy_if' -
// Algorithmus durchführt
namespace {
	const int SEARCH_BUFFERSIZE = 2048;

	class CSearch 
	{
	public:
		CSearch (DMatchString *pIMatch, ITRiASFeature *pIObjProp) : 
			m_Match(pIMatch), m_ObjProp(pIObjProp), m_fNotNegate(true)
		{
		CComBool fNegate;

			m_Match -> get_NegateMatch (&fNegate);
			m_fNotNegate = bool(!fNegate);
		} 
		~CSearch (void) {}

		bool operator() (ITRiASObject *pIObj) throw(_com_error) 	// zu untersuchendes Objekt
		{
		CComVariant vResult;
		HRESULT hr = m_ObjProp -> Eval (pIObj, &vResult);

			if (hr == E_FAIL || hr == HRESULT_FROM_ERRCODE(WC_NOTFOUND) || 
				FAILED(vResult.ChangeType (VT_BSTR))) 
			{
			// Objekt unterstützt diese OE nicht oder Resultat nicht als String darstellbar
				return m_fNotNegate;	// gematched/nicht gematched
			}
			THROW_FAILED_HRESULT(hr);	// sonstiger Fehler, nicht wieder rufen

		int iResult = 0;

			m_Match -> MatchString (V_BSTR(&vResult), &iResult);
			return iResult != 0 ? false : true;		// gematched oder auch nicht
		// false heißt gematched, true heißt nicht in Ausgabemenge übernehmen
		}

	private:
		WDMatchString m_Match;
		WTRiASFeature m_ObjProp;
		bool m_fNotNegate;
	};
}; // namespace 

STDMETHODIMP CTRiASObjects::SearchObjects(BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

	COM_TRY {
	// zu untersuchende Objekteigenschaft besorgen
	WTRiASFeature Feat;
	HRESULT hr = GetSearchFeature (pParams, Feat.ppi());

		if (TRIASDB_E_UNKNOWN_FEATURE == hr)
			return hr;
		THROW_FAILED_HRESULT(hr);

	// Vorbereitungen für Recherche: 
	// Parameter für die Recherche aus ParameterFeld herausholen, MatchObjekt erzeugen und initialisieren
	CComBSTR bstrPattern;	// SuchString
	WDMatchString Match;

		THROW_FAILED_HRESULT(RetrieveSearchParams (bstrCommand, pParams, CLEARED(&bstrPattern)));
		THROW_FAILED_HRESULT(GetMatchObject (bstrCommand, bstrPattern, Match.ppi()));

	// Eigentliche Recherche: alle Objekte dieser Objektklasse durchgehen und durch MatchObjekt 
	// überprüfen lassen

	// alle Objekte der Eingabemenge durchgehen und auf Match testen
		remove_copy_if(InEnumObjs(this), InEnumObjs(), OutEnumObjs(pIObjs), CSearch(Match, Feat));	

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjects::ConstraintObjects(ITRiASObjects *pIObjs)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// IOleObject
STDMETHODIMP CTRiASObjects::GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_pIParent);

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

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CTRiASObjects::SaveObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObjects::SaveObject");
}

STDMETHODIMP CTRiASObjects::GetContainer (IOleContainer **ppContainer)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObjects::GetContainer");
}

STDMETHODIMP CTRiASObjects::ShowObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObjects::ShowObject");
}

STDMETHODIMP CTRiASObjects::OnShowWindow (BOOL fShow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObjects::OnShowWindow");
}

STDMETHODIMP CTRiASObjects::RequestNewObjectLayout()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASObjects::RequestNewObjectLayout");
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASObjects::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == Property)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjects::CreateProperty");

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

// Einlesen aller Eigenschaften der Objektmenge und aller lokaler Props des
// Objektes.

STDMETHODIMP CTRiASObjects::RemoveProperty (BSTR Name)
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
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectsCallback

STDMETHODIMP CTRiASObjects::putref_ObjectsCallback(ITRiASObjectsCallback * pICB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pICallback = pICB;	// no AddRef !
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureEvents
STDMETHODIMP CTRiASObjects::CreatingFeature (VARIANT NameOrHandle, VARIANT_BOOL *pVal)
{
	return Fire_CreatingFeature (NameOrHandle, pVal);
}

STDMETHODIMP CTRiASObjects::FeatureToCreate (VARIANT NameOrHandle)
{
	return Fire_FeatureToCreate (NameOrHandle);
}

STDMETHODIMP CTRiASObjects::FeatureCreated (IDispatch *pIFeature)
{
	m_fIsDirty = true;
	return Fire_FeatureCreated (pIFeature);
}

STDMETHODIMP CTRiASObjects::ModifyingFeature (IDispatch *pIFeature, VARIANT_BOOL *pVal)
{
	return Fire_ModifyingFeature (pIFeature, pVal);
}

STDMETHODIMP CTRiASObjects::FeatureToModify (IDispatch *pIFeature)
{
	return Fire_FeatureToModify (pIFeature);
}

STDMETHODIMP CTRiASObjects::FeatureModified (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_FeatureModified (Name);
}

STDMETHODIMP CTRiASObjects::DeletingFeature (IDispatch *pIFeature, VARIANT_BOOL *pVal)
{
	return Fire_DeletingFeature (pIFeature, pVal);
}

STDMETHODIMP CTRiASObjects::FeatureToDelete (IDispatch *pIFeature)
{
	return Fire_FeatureToDelete (pIFeature);
}

STDMETHODIMP CTRiASObjects::FeatureDeleted (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_FeatureDeleted (Name);
}

HRESULT CTRiASObjects::PropertiesRefreshed()
{
	RETURN_FAILED_HRESULT(SetPropertyBy (this, g_cbNameIsDefault, VARIANT_FALSE, true, LOCALE_ENGLISH));
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// OKS behandeln (globale Funktionen)

namespace {

// eigentlich passiert ja alles hier in der folgenden Klasse
	class COKSRegExpr :
		public os_regexp
	{
	public:
		COKSRegExpr() { pattern (g_cbOKS); }

		bool StringIsOKS (BSTR bstrToTest, BSTR *pbstrStripped = NULL, BSTR *pbstrAppendix = NULL)
		{ 
			USES_CONVERSION;

		// Eingabezeichenkette analysieren
		os_string strToTest (OLE2A(bstrToTest));
		int iMatched = match(strToTest);

			if (iMatched <= 0) 
				return false; 

		os_string strT;

			if (group(7).size() > 0) {
			// vierter Fall gefunden (Monikerformat)
				strT = group(7);
				if (NULL != pbstrAppendix) {
				CComBSTR bstrApp ((group(8).size() > 0) ? os_string(group(8)).c_str() : g_cbNil);

					*pbstrAppendix = bstrApp.Detach();
				}

			} else if (group(4).size() > 0) {
			// dritter Fall gefunden ('[hexdigits]...')
				strT = group(4);
				if (NULL != pbstrAppendix) {
					_ASSERTE(group(5).size() > 0);

				CComBSTR bstrApp (os_string(group(5)).c_str());

					*pbstrAppendix = bstrApp.Detach();
				}
			} else if (group(1).size() > 0) {
			// ersten Fall gefunden ('[hexdigits]')
				strT = group(1);
			} else if (group(3).size() > 0) {
			// zweiten Fall gefunden ('hexdigits:...')
				strT = group(3);
			} else
				return false;

			if (0 == strT.size()) 
				return false;

		// Resultat liefern, wenn gewünscht
			if (NULL != pbstrStripped) {
			CComBSTR bstrRes (strT.c_str());

				*pbstrStripped = bstrRes.Detach();
			}
			return true;
		}
	};

	COKSRegExpr g_TestOKS;

}; // namespace

bool StringIsOKS (BSTR bstrToStrip, BSTR *pStripped, BSTR *pbstrAppendix)
{
	return g_TestOKS.StringIsOKS (bstrToStrip, pStripped, pbstrAppendix);
}
