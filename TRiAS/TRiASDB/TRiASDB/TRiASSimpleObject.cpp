// @doc
// @module TRiASSimpleObject.cpp | Implementation of the <c CTRiASSimpleObject> class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>

#include "Strings.h"
#include "Wrapper.h"

#include "TRiASSimpleObject.h"
#include "TRiASSimpleFeatures.h"
#include "TRiASSimpleGeoFeatures.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASSimpleObject);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASSimpleObject::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASSimpleObject, CTRiASSimpleObject)

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleObject

STDMETHODIMP CTRiASSimpleObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleObject,
		&IID_ITRiASObject,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CTRiASSimpleObject::FinalRelease (void)
{
// evtl. aus HandleTabellen entfernen
//	COM_TRY {
//	WTRiASObject BaseObj;
//	WDispatch Parent;
//
//		if (SUCCEEDED(m_BaseUnk -> QueryInterface (IID_ITRiASObject, BaseObj.ppv())))
//			BaseObj -> get_Parent (Parent.ppi());
//			
//	// aus Database-Tabelle entfernen
//		if (Parent != NULL) {
//		WTRiASObjectHandleMap MapP (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);
//
//			_ASSERTE(MapP.IsValid());
//			if (MapP.IsValid()) 
//				MapP -> RemoveObject (m_lONr, OBJECTMAPMODE_RemoveAllReferences);
//		}
//
//	} COM_CATCH_IGNORE;

// sonstige Aufräumarbeiten
	m_BaseUnk.Assign(NULL);
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSimpleObject
STDMETHODIMP CTRiASSimpleObject::InitTarget (
	INT_PTR lONr, OBJECTTYPE rgType, INT_PTR lIdent, INT_PTR hObjs, INT_PTR *phObj)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == phObj) return E_POINTER;

WTRiASObject BaseObj;
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObj.ppi()));
	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

CIID Guid;

	if (0 != lONr) {
	// Objekt existiert bereits
	// Typ und Guid aus der Datenbank lesen und im Bezugsobjekt ablegen
	CNativeObject Obj (hPr, lONr, false);

		if (!Obj) return TRIASDB_E_BADOBJECTHANDLE;

#if defined(_DEBUG)
	DWORD dwTypeDebOrg = OBJECTTYPEToBits (rgType);
	DWORD dwTypeDeb = 0;

		RETURN_FAILED_HRESULT(Obj.GetObjectType (&dwTypeDeb));
		_ASSERTE(dwTypeDeb == 0 || dwTypeDebOrg == 0 || (dwTypeDeb & dwTypeDebOrg) ? true : false);
#endif // _DEBUG

		if (OBJECTTYPE_Unknown == rgType || BitCount(rgType) > 1) {
		// Objekttyp ist noch unbekannt oder nicht eindeutig, also aus Datenbank lesen
		DWORD dwType = 0;

			RETURN_FAILED_HRESULT(Obj.GetObjectType (&dwType));
			rgType = BitsToOBJECTTYPE(dwType);
		}
		RETURN_FAILED_HRESULT(BaseObj -> put_Type (rgType));
		RETURN_FAILED_HRESULT(Obj.GetObjectGUID (&Guid));

#pragma MESSAGE("TODO: Identifikator soll nur vergeben werden, wenn Objekt noch nicht klassifiziert wurde!")

	HRESULT hr = S_OK;
	
		RETURN_FAILED_HRESULT(hr = Obj.GetIdent (NULL));
		if (S_FALSE == hr) {
		// Objekt besitzt noch keinen Identifikator
			RETURN_FAILED_HRESULT(Obj.PutIdent (lIdent));
		}
#if defined(_DEBUG)
		else {
		// wenn Objekt bereits einen Identifikator besitzt, dann darf er nicht hier 
		// modifiziert werden sollen
		INT_PTR lOldIdent = NULL;

			RETURN_FAILED_HRESULT(Obj.GetIdent ((LONG *)&lOldIdent));
			_ASSERTE(lIdent == lOldIdent);
		}
#endif // _DEBUG)

	} else if (NULL == *phObj) { 
	// Objekt neu erzeugen
	CNativeObject Obj (hPr);

		RETURN_FAILED_HRESULT(Obj.CreateObjTemplate (lIdent, &lONr));
		RETURN_FAILED_HRESULT(BaseObj -> put_Type (rgType));
		RETURN_FAILED_HRESULT(Obj.GetObjectGUID (&Guid));
	}

// Objektnamen auf Guid initialisieren
	RETURN_FAILED_HRESULT(BaseObj -> put_Name (CComBSTR(Guid)));

// die Objektnummer dieses Objektes rauskriegen und dem Basisobjekt mitteilen
	if (NULL == *phObj) {
	// Handle neu vergeben und resultat setzen
		RETURN_FAILED_HRESULT(BaseObj -> put_Handle(lONr));
		RETURN_FAILED_HRESULT(BaseObj -> get_Handle(phObj));
	} else {
	// das gegebene Handle muß eindeutig sein
		RETURN_FAILED_HRESULT(BaseObj -> put_Handle(*phObj));
#if defined(_DEBUG)
	INT_PTR hObjDeb = NULL;

		RETURN_FAILED_HRESULT(BaseObj -> get_Handle(&hObjDeb));
		_ASSERTE(hObjDeb == *phObj);
#endif // _DEBUG
	}

// zugehörige Objektklasse mitteilen
	if (0 != hObjs) {
	// Handle der zugehörigen Objektklasse immer setzen, wenn selbige geben ist
		RETURN_FAILED_HRESULT(BaseObj -> put_ObjectsHandle(hObjs));
	}
	else {
		RETURN_FAILED_HRESULT(BaseObj -> get_ObjectsHandle(&hObjs));
		if (0 == hObjs)
		{
			RETURN_FAILED_HRESULT(BaseObj -> put_ObjectsHandle(lIdent));	// erstmal Identifikator verpassen
		}
	}

// sonst noch was zu tun ? :-)
	m_lONr = lONr;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObject::get_LocalHandle (INT_PTR *pHandle)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pHandle)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_LocalHandle ");

	*pHandle = m_lONr;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectCallback

STDMETHODIMP CTRiASSimpleObject::get_DefaultType (BSTR *pbstrType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pbstrType)
		return E_POINTER;

CIID Guid (GetObjectCLSID());
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObject::SetupObject(SETUPOBJECTMODE rgMode)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObject::OnChanging (CHANGEDOBJECT rgWhat, VARIANT vNewValue, VARIANT_BOOL *pfDisAllow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == pfDisAllow)
		return E_POINTER;
	*pfDisAllow = VARIANT_FALSE;		// immer zulassen
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObject::OnChanged (CHANGEDOBJECT rgWhat, VARIANT vOldValue)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASSimpleObject::OnFinalRelease()
{
// evtl. aus HandleTabellen entfernen
	COM_TRY {
	WTRiASObject BaseObj;
	WDispatch Parent;

		if (SUCCEEDED(m_BaseUnk -> QueryInterface (BaseObj.ppi())))
			BaseObj -> get_Parent (Parent.ppi());
			
	// aus Database-Tabelle entfernen
		if (Parent != NULL) {
		WTRiASObjectHandleMap MapP (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);

			_ASSERTE(MapP.IsValid());
			if (MapP.IsValid()) 
				MapP -> RemoveObject (m_lONr, OBJECTMAPMODE_RemoveAllReferences);
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObject::OnDelete()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Objekt aus GeoDB herauslöschen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

CNativeObject Obj (hPr, m_lONr);

	if (!Obj)
		return TRIASDB_E_BADOBJECTHANDLE;
	return Obj.Delete (TRUE);
}

HRESULT CTRiASSimpleObject::EnsureFeatures(VARIANT_BOOL fForceSetup)
{
// unterstützte Attribute mit Objektmenge assoziieren
//	if (!m_fHasFeatures || fForceSetup) {
//	CComObject<CTRiASSimpleFeatures> *pNewFeats = NULL;
//
//		COM_TRY {
//		// Features-Collection erzeugen und initialisieren
//			THROW_FAILED_HRESULT(CComObject<CTRiASSimpleFeatures>::CreateInstance(&pNewFeats));
//
//		WTRiASFeatures Feats (pNewFeats -> GetUnknown());
//
//			pNewFeats = NULL;		// doppeltes delete im Fehlerfall vermeiden
//
//			THROW_FAILED_HRESULT(WTRiASObject(m_BaseUnk) -> put_Features (Feats))
//			THROW_FAILED_HRESULT(Feats -> Refresh());	// Features erstmalig einlesen
//			m_fHasFeatures = true;
//
//		} COM_CATCH_OP(delete pNewFeats);
//	}

// unterstützte Attribute mit Objektmenge assoziieren
//	if (!m_fHasGeoFeatures || fForceSetup) {
//	CComObject<CTRiASSimpleGeoFeatures> *pNewGeoFeats = NULL;
//
//		COM_TRY {
//		// Features-Collection erzeugen und initialisieren
//			THROW_FAILED_HRESULT(CComObject<CTRiASSimpleGeoFeatures>::CreateInstance(&pNewGeoFeats));
//
//		WTRiASFeatures Feats (pNewGeoFeats -> GetUnknown());
//
//			pNewGeoFeats = NULL;		// doppeltes delete im Fehlerfall vermeiden
//
//			THROW_FAILED_HRESULT(WTRiASObject(m_BaseUnk) -> put_GeometryFeatures (Feats))
//			THROW_FAILED_HRESULT(Feats -> Refresh());	// Features erstmalig einlesen
//
//			m_fHasGeoFeatures = true;
//
//		} COM_CATCH_OP(delete pNewGeoFeats);
//	}
//	return S_OK;
	return E_NOTIMPL;		// die BasisKlasse macht das richtig für uns
}

STDMETHODIMP CTRiASSimpleObject::SetupFeatures(SETUPFEATURESMODE rgMode)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

	return EnsureFeatures((rgMode & SETUPFEATURESMODE_Force) ? VARIANT_TRUE : VARIANT_FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASSimpleObject::GetClassID (CLSID *pClassID)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASSimpleObject::GetClassID");

	*pClassID = CLSID_TRiASSimpleObject;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStream

STDMETHODIMP CTRiASSimpleObject::IsDirty (void)
{
	return m_fIsDirty ? S_OK : WPersistStreamInit(m_BaseUnk) -> IsDirty();
}

STDMETHODIMP CTRiASSimpleObject::Load (LPSTREAM pStm)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

long lSignature = 0L;

	THROW_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (SIMPLEOBJECT_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
	if ((lVersion & ~SIMPLEOBJECT_VERSION_MINOR_MASK) > LASTKNOWN_SIMPLEOBJECT_VERSION)
		return TRIASDB_W_NEWEROBJECT;

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Load (pStm));
//	RETURN_FAILED_HRESULT(LoadLong (pStm, m_lIdent));			// Identifikator

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObject::Save (LPSTREAM pStm, BOOL fClearDirty)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	RETURN_FAILED_HRESULT(SaveLong(pStm, SIMPLEOBJECT_SIGNATURE));
	RETURN_FAILED_HRESULT(SaveLong(pStm, LASTKNOWN_SIMPLEOBJECT_VERSION));

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Save (pStm, fClearDirty));
//	RETURN_FAILED_HRESULT(SaveLong (pStm, m_lIdent));			// Identifikator

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObject::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASSimpleObject::GetSizeMax");

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> GetSizeMax (pcbSize));
	pcbSize -> QuadPart += 2*sizeof(long);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit

STDMETHODIMP CTRiASSimpleObject::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

HRESULT hr = WPersistStreamInit(m_BaseUnk) -> InitNew();

	if (SUCCEEDED(hr)) {
		m_fIsDirty = false;	
		m_fIsInitialized = true;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Abhängige Textobjekte
/*static*/
HRESULT CALLBACK CTRiASSimpleObject::EnumRelatedObjectCallBack (INT_PTR lObj, int iRelType, UINT_PTR dwData)
{
CEnumRelatedObjectCallback *pERO = reinterpret_cast<CEnumRelatedObjectCallback *>(dwData);

	pERO -> iRelType = iRelType;
	pERO -> lONr = lObj;
	return S_OK;
}

HRESULT CTRiASSimpleObject::get_RelatedObject (ITRiASObject **ppIObj)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIObj) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASSimpleObject::get_RelatedObject");
	*ppIObj = NULL;

HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// Handle des abhängigen Objektes besorgen
CNativeObject Obj (hPr, m_lONr, false);
INT_PTR lONr = 0;
CEnumRelatedObjectCallback ERT;

	if (!Obj) 
		return TRIASDB_E_BADOBJECTHANDLE;

	if (SUCCEEDED(Obj.EnumBegleitObject(EnumRelatedObjectCallBack, reinterpret_cast<UINT_PTR>(&ERT)))) {
	// Konsistenz prüfen
#if defined(_DEBUG)
	CNativeObject ObjSec (hPr, ERT.lONr, false);
	DWORD dwType = 0;

		_ASSERTE(!!ObjSec);
		ObjSec.GetObjectType(&dwType);
		_ASSERTE(((ERT.iRelType & BRELP) && (dwType & OTText)) || ((ERT.iRelType & BRELA) && !(dwType & OTText)));
#endif // defined(_DEBUG)

	// zugehöriges COM-Objekt wiederfinden
	WTRiASObject BaseObj;
	WDispatch Parent;

		if (SUCCEEDED(m_BaseUnk -> QueryInterface (BaseObj.ppi())))
			BaseObj -> get_Parent (Parent.ppi());
			
	// aus Database-Tabelle entfernen
		_ASSERTE(Parent.IsValid());
	
	WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);
	WUnknown Unk;

		_ASSERTE(Map.IsValid());
		if (S_OK == Map -> GetObjectEx (ERT.lONr, OBJECTMAPMODE_GetObjectFromNativeHandle, Unk.ppi())) 
			return Unk -> QueryInterface (ppIObj);
	}
	return TRIASDB_I_NO_OBJECT_FOUND;		// es gibt kein abhängiges Objekt
}

HRESULT CTRiASSimpleObject::put_RelatedObject (ITRiASObject *pIObj)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

CNativeObject Obj (hPr, m_lONr, false);
DWORD dwType = 0;

	if (!Obj) 
		return TRIASDB_E_BADOBJECTHANDLE;

	RETURN_FAILED_HRESULT(Obj.GetObjectType(&dwType));

// evtl. Begleitrelation löschen
INT_PTR lONrB = Obj.AssociatedObject();
bool fHadRelatedObject = false;

	if (0 != lONrB) {
		if (lONrB > 0) {
		// dieses Objekt muß ein Textobjekt sein
			_ASSERTE(dwType & OTText);
			RETURN_FAILED_HRESULT(Obj.DeleteRelation(lONrB, 0, BRELP));
		} else {
		// dieses Objekt darf kein Textobjekt sein
			_ASSERTE(!(dwType & OTText));
			RETURN_FAILED_HRESULT(Obj.DeleteRelation(-lONrB, 0, BRELA));
		}
		fHadRelatedObject = true;
	}

	if (NULL == pIObj) 
		return fHadRelatedObject ? S_OK : TRIASDB_I_NO_OBJECT_FOUND;		// es gibt kein abhängiges Objekt
	else {
	// Begleitrelation neu erzeugen
		if (dwType & OTText) {
		WTRiASSimpleObject SecObj;
		INT_PTR lObjSec = 0;

			RETURN_FAILED_HRESULT(pIObj -> QueryInterface(SecObj.ppi()));
			RETURN_FAILED_HRESULT(SecObj -> get_LocalHandle(&lObjSec));

		CNativeObject SecObjN (hPr, lObjSec, false);

			if (!SecObjN)
				return TRIASDB_E_BADOBJECTHANDLE;
			RETURN_FAILED_HRESULT(SecObjN.PutRelation(m_lONr, 0, BRELP))
		}
		else {
		WTRiASSimpleObject SecObj;
		INT_PTR lObjSec = 0;

			RETURN_FAILED_HRESULT(pIObj -> QueryInterface(SecObj.ppi()));
			RETURN_FAILED_HRESULT(SecObj -> get_LocalHandle(&lObjSec));
			RETURN_FAILED_HRESULT(Obj.PutRelation(lObjSec, 0, BRELA))
		}
	}
	return S_OK;
}

