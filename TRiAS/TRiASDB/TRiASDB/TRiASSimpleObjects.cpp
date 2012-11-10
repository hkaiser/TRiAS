// @doc
// @module TRiASSimpleObjects.cpp | Implementation of the <c CTRiASSimpleObjects> class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <ospace/views/mapview.h>

#include "Strings.h"
#include "Wrapper.h"
#include "GlobalVars.h"
#include "TRiASDBGuids.h"

#include <Com/PropertyHelper.h>
#include <Com/VariantHelpers.h>
#include <Com/EnumVariantIterators.h>
#include <Com/SafeArray.h>
#include <Com/ComBool.h>

#include "TRiASSimpleObjects.h"
#include "TRiASSimpleObject.h"
#include "TRiASSimpleFeatures.h"
#include "TRiASSimpleGeoFeatures.h"
#include "GenObjectMap.h"

#import "Tlb/TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids \
	exclude("IStaticCollection", "IEnumCoordSystemNames")

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASSimpleObject> CSimpleObjectFactory;
CSimpleObjectFactory MakeSimpleObjects;
#endif // defined(_USE_CLASSFACTORY_CACHE)

///////////////////////////////////////////////////////////////////////////////
// Anfangsgrˆﬂe des LocalHandle-Containers
#define INITIAL_OBJECT_HANDLE_COUNT	32	

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASSimpleObjects);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASSimpleObjects::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASSimpleObjects, CTRiASSimpleObjects)

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASPropertyMapHandler);	// WTRiASPropertyMapHandler
DefineSmartInterface(TRiASSimpleObject);		// WTRiASSimpleObject
DefineSmartInterface(TRiASSearchObjects);		// WTRiASSearchObjects

DefineSmartInterface(TRiASCSTransform);			// WTRiASCSTransform
DefineSmartInterface(TRiASCloneGeometry);		// WTRiASCloneGeometry
DefineSmartInterface(TRiASTransformGeometry);	// WTRiASTransformGeometry
DefineSmartInterface(TRiASSimpleRectangle);		// WTRiASSimpleRectangle

DefineSmartInterface(OleObject);
DefineSmartInterface(BindCtx);

///////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleObjects

STDMETHODIMP CTRiASSimpleObjects::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleObjects,
		&IID_ITRiASObjects,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CTRiASSimpleObjects::FinalRelease (void)
{
// aus Map des Parent's entfernen
//	COM_TRY {
//	WTRiASObjects BaseObjs;
//	WDispatch Parent;
//
//		if (SUCCEEDED(m_BaseUnk -> QueryInterface (IID_ITRiASObjects, BaseObjs.ppv())))
//			BaseObjs -> get_Parent (Parent.ppi());
//			
//	// aus Database-Tabelle entfernen
//		if (Parent.IsValid()) {
//		WTRiASObjectHandleMap MapP (GetPropertyFrom (Parent, g_cbObjectsMap, (IDispatch *)NULL), false);
//
//			_ASSERTE(MapP.IsValid());
//			if (MapP.IsValid()) 
//				VERIFY(S_OK == MapP -> RemoveObject (m_lIdent, OBJECTMAPMODE_RemoveAllReferences));
//		}
//
//	} COM_CATCH_IGNORE;

// sonstige Aufr‰umarbeiten
	DELETE_OBJ(m_pObjs);
	DELETE_OBJ(m_phMap);
	m_BaseUnk.Assign(NULL);
}

HRESULT CTRiASSimpleObjects::RetrievePbdHandle (HPROJECT *phPrPbd)
{
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle(&hPr))
	if (!::GetRelatedProject (hPr, phPrPbd)) 
		return E_UNEXPECTED;

	return S_OK;
}

HRESULT CTRiASSimpleObjects::EnsureLocalHandleCont(bool fClearMap)
{
	if (NULL != m_pObjs) {
		if (fClearMap)
			m_pObjs -> clear();
		return S_OK;
	}
	ATLTRY(m_pObjs = new CLocalHandles);
	return (NULL != m_pObjs) ? S_OK : E_OUTOFMEMORY;
}

HRESULT CTRiASSimpleObjects::EnsureHandleMap (bool fClearMap)
{
	if (NULL != m_phMap) {
		if (fClearMap)
			m_phMap -> clear();
		return S_OK;
	}
	ATLTRY(m_phMap = new CObjHandleMap);
	return (NULL != m_phMap) ? S_OK : E_OUTOFMEMORY;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASSimpleObjects::GetClassID (CLSID *pClassID)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASSimpleObjects::GetClassID");

	*pClassID = CLSID_TRiASSimpleObjects;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStream

STDMETHODIMP CTRiASSimpleObjects::IsDirty (void)
{
	return m_fIsDirty ? S_OK : WPersistStreamInit(m_BaseUnk) -> IsDirty();
}

STDMETHODIMP CTRiASSimpleObjects::Load (LPSTREAM pStm)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

// diverse Properties modifizieren
WTRiASPropertyMapHandler MapHandler(m_BaseUnk);

	RETURN_FAILED_HRESULT(MapHandler -> ChangeMapEntry (
		CComBSTR(g_cbFeatureMap), (INT_PTR)&CLSID_DatabaseFeatureMap, PROPERTYSUPPORT_AGGREGATE, vtMissing));

CComVariant vTrue(VARIANT_TRUE);

	V_VT(&vTrue) = VT_BOOL;
	RETURN_FAILED_HRESULT(MapHandler -> ChangeMapEntry (
		CComBSTR(FEATUREPROPERTY_HasObjectGuid), (INT_PTR)&CLSID_TRiASVariantProperty, PROPERTYSUPPORT_HASINITDATA, vTrue));

// unsere daten laden
long lSignature = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (SIMPLEOBJECTS_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
	if ((lVersion & ~SIMPLEOBJECTS_VERSION_MINOR_MASK) > LASTKNOWN_SIMPLEOBJECTS_VERSION)
		return TRIASDB_W_NEWEROBJECTSCOLLECTION;

// jetzt alles andere laden
	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Load (pStm));
	RETURN_FAILED_HRESULT(LoadLong (pStm, m_lIdent));			// Identifikator

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObjects::Save (LPSTREAM pStm, BOOL fClearDirty)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	RETURN_FAILED_HRESULT(SaveLong(pStm, SIMPLEOBJECTS_SIGNATURE));
	RETURN_FAILED_HRESULT(SaveLong(pStm, LASTKNOWN_SIMPLEOBJECTS_VERSION));

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveLong (pStm, m_lIdent));			// Identifikator

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObjects::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASSimpleObjects::GetSizeMax");

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> GetSizeMax (pcbSize));
	pcbSize -> QuadPart += 3*sizeof(long);
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////
// OleItemContainerSupport
HRESULT CTRiASSimpleObjects::GetFeature (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	if (BINDSPEED_IMMEDIATE == dwSpeedNeeded)	// muﬂ immer in der GeoDB gesucht werden
		return MK_E_EXCEEDEDDEADLINE;

	COM_TRY {
	WDispatch App;
	WTRiASObjects BaseObjs;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
		THROW_FAILED_HRESULT(BaseObjs -> get_Application (App.ppi()));

	// der Moniker hat folgenden Aufbau
	// entweder:	KurzText
	// oder:		[lMCode]:KurzText
	INT_PTR lMCode = 0L;
	HPROJECT hPr = NULL;

		THROW_FAILED_HRESULT(RetrieveDBHandle (&hPr));
		if (g_cbLBracket[0] != *pcItem) {
		// nur Kurztext gegeben
			THROW_FAILED_HRESULT(CNativeMerkmal::FindMerkmal (hPr, pcItem, (LONG *)&lMCode));
			_ASSERTE(0 != lMCode);
		} 
		else {
		// MerkmalsCode und (hoffentlich) Kurztext gegeben
		LPTSTR pItem = NULL;

			lMCode = strtoul (pcItem+1, &pItem, 16);
			_ASSERTE(0 != lMCode);

			if ('\0' != *pItem && '\0' != *(pItem+1)) {
			// bei dieser Gelegenheit KurzText setzen und damit in Pbd definieren
			CNativeMerkmal Merkmal (hPr, lMCode);

				THROW_FAILED_HRESULT(Merkmal.SetName (pItem+1));
			} 
		}

	WTRiASObjectHandleMap Map (GetPropertyFrom (BaseObjs, g_cbFeatureMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	CInitializeFeature InitFeat (lMCode, DATATYPE_FROM_VT(VT_BSTR) | CNativePbdMerkmal::PBDFEATURETYPE_Object, App, WDispatch(m_BaseUnk));
	WTRiASFeature Feat;

		THROW_FAILED_HRESULT(FindInMapOrCreateObject(Map, lMCode, Feat, CLSID_TRiASSimpleFeature, InitFeat));
		if (!fTestRunningOnly && NULL != ppvObj) 
		{
			THROW_FAILED_HRESULT(Feat -> QueryInterface (riid, ppvObj));
		}

	} COM_CATCH;
	
	return S_OK;
}

//////////////////////////////////////////////////////////////
// IPersistStreamInit

STDMETHODIMP CTRiASSimpleObjects::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	COM_TRY {
	// diverse Properties modifizieren
	WTRiASPropertyMapHandler MapHandler(m_BaseUnk);

		THROW_FAILED_HRESULT(MapHandler -> ChangeMapEntry (
			CComBSTR(g_cbFeatureMap), (INT_PTR)&CLSID_DatabaseFeatureMap, PROPERTYSUPPORT_AGGREGATE, vtMissing));

	CComVariant vTrue(VARIANT_TRUE);

		V_VT(&vTrue) = VT_BOOL;
		THROW_FAILED_HRESULT(MapHandler -> ChangeMapEntry (
			CComBSTR(FEATUREPROPERTY_HasObjectGuid), (INT_PTR)&CLSID_TRiASVariantProperty, PROPERTYSUPPORT_HASINITDATA, vTrue));

	// jetzt fertig initialiseren
		THROW_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> InitNew());

//	WTRiASObjects Objs (m_BaseUnk);
//
//		THROW_FAILED_HRESULT(Objs -> put_DefaultGeometry(g_bstrGeometry));
//		THROW_FAILED_HRESULT(Objs -> put_PrimaryKey(g_bstrFeature));
	} COM_CATCH;

	m_fIsDirty = false;	
	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties

///////////////////////////////////////////////////////////////////////////////
// Methods

STDMETHODIMP CTRiASSimpleObjects::InitTarget(
	LONG lIdent, OBJECTTYPE rgObjType, VARIANT_BOOL fCreate, INT_PTR *phObjs)
{
INT_PTR hObjs = (NULL != phObjs) ? *phObjs : 0L;

	TEST_OUT_PARAM(phObjs);

CComSemaphore<_ThreadModel> Sem (m_lInitData);	// doppeltes Initialisieren verhindern

// erstmal nur Werte zwischenspeichern
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> _Reset());

// wenn nicht zum ersten Mal gerufen, dann muﬂ Ident stimmen
	_ASSERTE(0 == m_lIdent || m_lIdent == lIdent);

char cbBuffer[_MAX_PATH];
bool fUseIdentAsOKS = false;

	if (0 != m_lIdent && m_lIdent == lIdent) {
	OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

		RETURN_FAILED_HRESULT(BaseObjs -> get_Types(&rgTypes));
		RETURN_FAILED_HRESULT(BaseObjs -> put_Types(OBJECTTYPE(rgTypes | rgObjType)));	// Objekttypen kombinieren
		if (!(rgTypes & rgObjType)) 
			ResetCounters();		// Objektz‰hler r¸cksetzen, wenn neuer Objekttyp

	} else if (NULL == hObjs) {
	// erste Initialisierung
		ResetCounters();

		m_lIdent = lIdent;
		RETURN_FAILED_HRESULT(BaseObjs -> put_CollectionType(OBJECTSCOLLECTIONTYPE_Class));
		RETURN_FAILED_HRESULT(BaseObjs -> put_Types(rgObjType));
		RETURN_FAILED_HRESULT(BaseObjs -> put_DefaultGeometry (g_bstrGeometry));
		RETURN_FAILED_HRESULT(BaseObjs -> put_PrimaryKey (g_bstrFeature));

	// und KurzText/Langtext aus Pbd besorgen
	HPROJECT hPr = NULL;

		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

	// existierenden Ident in DB wieder finden
	CNativeIdent Ident (hPr, m_lIdent, OBJECTTYPEToBits(rgObjType), fCreate);

		if (!Ident)	{
			if (!fCreate)	// diese Objektklasse gibt es hier ¸berhaupt nicht
				return TRIASDB_I_OBJECTS_NOT_EXISTS;
			return E_FAIL;	// Objektklasse konnte nicht erzeugt werden
		}

	// BeschreibungsInfos besorgen
	HRESULT hr = E_FAIL;

		Ident.ReportPbdErrors (FALSE);	// evtl. Fehler nicht melden/Rekursion vermeiden
		RETURN_FAILED_HRESULT(hr = Ident.GetName (cbBuffer, sizeof(cbBuffer)));
		RETURN_FAILED_HRESULT(BaseObjs -> put_Name (CComBSTR(cbBuffer)));
		if (S_FALSE == hr) {
		// der Name der Objektklasse ist lediglich tempor‰r generiert
			SetPropertyBy (WTRiASPropertyBase(BaseObjs), g_cbNameIsDefault, VARIANT_TRUE, true, LOCALE_ENGLISH);
		}

		cbBuffer[0] = '\0';		// ausnullen
		if (S_OK == Ident.GetDescription (cbBuffer, sizeof(cbBuffer)))
		{
			RETURN_FAILED_HRESULT(BaseObjs -> put_Description (CComBSTR(cbBuffer)));
		}
		if (SUCCEEDED(Ident.GetOKS (cbBuffer, sizeof(cbBuffer))))
		{
			RETURN_FAILED_HRESULT(BaseObjs -> put_OKS (CComBSTR(cbBuffer)));
		} 
		else
			fUseIdentAsOKS = true;

	// Schreibschutz initialisieren
	BOOL fReadOnly = FALSE;

		RETURN_FAILED_HRESULT(Ident.GetReadOnly (&fReadOnly));
		RETURN_FAILED_HRESULT(BaseObjs -> put_Updatable (CComBool(!fReadOnly)));
	}

// den Identifikator dieses Objektes rauskriegen und dem Basisobjekt mitteilen
	if (NULL == hObjs) {
	// Handle-Voreinstellungen setzen
	long lIdent16 =	m_lIdent;

		if (fUseIdentAsOKS) {		// IdentBase als Database-Property besorgen
		WDispatch Parent;
		os_string strFmt;

			RETURN_FAILED_HRESULT(BaseObjs -> get_Parent(Parent.ppi()));
			if (10 == GetPropertyFrom (Parent, g_cbIdentBaseHdr, 16L, LOCALE_ENGLISH)) 
				strFmt = "%lu";
			else 
				strFmt = "%lx";
		
			wsprintf (cbBuffer, strFmt.c_str(), m_lIdent);
			RETURN_FAILED_HRESULT(BaseObjs -> put_OKS (CComBSTR(cbBuffer)));
		}

	// Handle neu vergeben und Resultat setzen
		RETURN_FAILED_HRESULT(BaseObjs -> put_Handle(lIdent16));
		RETURN_FAILED_HRESULT(BaseObjs -> get_Handle(&hObjs));

	} else {
	// das gegebene Handle muﬂ eindeutig sein
		RETURN_FAILED_HRESULT(BaseObjs -> put_Handle(hObjs));
#if defined(_DEBUG)
	INT_PTR hObjDeb = NULL;

		RETURN_FAILED_HRESULT(BaseObjs -> get_Handle(&hObjDeb));
		_ASSERTE(hObjDeb == hObjs);
#endif // _DEBUG
	}

	*phObjs = hObjs;		// Ergebnis setzen
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObjects::get_Count (OBJECTTYPE rgType, long *plObjCnt)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return E_UNEXPECTED;
	TEST_OUT_PARAM(plObjCnt);

	RETURN_FAILED_HRESULT(EnsureObjectsCount());
	_ASSERTE(HasType (m_rgInitState, INITSTATE_CountsInitialized));

// typspezifischen Objektz‰hler liefern
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

	case OBJECTTYPE_AllSimple:
	case OBJECTTYPE_All:
		*plObjCnt = m_lCountAll;
		break;

	default:
		return E_INVALIDARG;
	}
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObjects::get_Handles (long lCount, INT_PTR *plObjs)
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;
	TEST_OUT_PARAM(plObjs);

	_ASSERTE(!IsBadWritePtr(plObjs, sizeof(HOBJECT)*lCount));

	RETURN_FAILED_HRESULT(EnsureObjectsHandles());				// Handles erzeugen
	_ASSERTE(HasType (m_rgInitState, INITSTATE_HandlesInitialized));

// Handles umkopieren
map_keys<INT_PTR, INT_PTR, less<INT_PTR> > keys (*m_phMap);

	_ASSERTE((size_t)lCount >= m_phMap -> size());
	copy (keys.begin(), keys.end(), plObjs);
	return S_OK;
}

HRESULT CTRiASSimpleObjects::EnsureLookupWindow (
	LPCSTR pcGeomName, CNativeObject &rObj, VARIANT vArg, ITRiASSimpleRectangle **ppIRect)
{
	TEST_OUT_PARAM(ppIRect);

	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, DBase.ppi()));

	WTRiASPropertyBase Props (DBase);
	WTRiASSimpleRectangle rect (GetPropertyFrom (Props, g_cbActLookupWindow, (IDispatch *)NULL), false);

		if (!rect.IsValid()) {
		// CS-Transformator besorgen
		CIID Guid;		// CSS-Guid
		WTRiASCSTransform CST (GetPropertyFrom (Props, g_cbTRiASCSTransform, (IDispatch *)NULL), false);
		CComVariant vWindow;

			_ASSERTE(CST.IsValid());
			THROW_FAILED_HRESULT(rObj.GetGeometryGuid (pcGeomName, &Guid));
			THROW_FAILED_HRESULT(vWindow.ChangeType (VT_DISPATCH, &vArg));

			rect = V_DISPATCH(&vWindow);
			THROW_FAILED_HRESULT(WTRiASTransformGeometry(rect) -> TransformInverse (*(CSID *)&Guid, CST));

		// an der Datenquelle wegschreiben
			THROW_FAILED_HRESULT(SetPropertyBy (Props, g_cbActLookupWindow, rect, true));
		}
		*ppIRect = rect.detach();

	} COM_CATCH;
	return S_OK;
}

// Sicherstellen, daﬂ ein gegebenes Objekt geladen ist
STDMETHODIMP CTRiASSimpleObjects::EnsureLoaded (
	INT_PTR hObj, BSTR bstrGeomName, SAFEARRAY **ppConstraints, ITRiASObject **ppIObj)
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;
	TEST_OUT_PARAM(ppIObj);

	USES_CONVERSION;
	COM_TRY {
	// nachsehen, ob dieses Objekt bereits geladen ist
	WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());
	WUnknown Unk;

		if (S_OK == Map -> GetObject (hObj, Unk.ppi()) && SUCCEEDED(Unk -> QueryInterface (ppIObj)))
			return S_OK;		// Objekt existiert bereits

	// wenn nicht, dann nur dieses Objekt laden
		THROW_FAILED_HRESULT(EnsureObjectsHandles());
		_ASSERTE(HasType (m_rgInitState, INITSTATE_HandlesInitialized));

	CObjHandleMap::iterator it = m_phMap -> find (hObj);

		if (it == m_phMap -> end()) {
		// Objekt wird neu erzeugt
		WTRiASObject Obj;
		INT_PTR lONr = 0;

			THROW_FAILED_HRESULT(GetOrCreateObject (hObj, 0L, OBJECTTYPE_Unknown, CLSID_TRiASSimpleObject, Obj.ppi()));
			THROW_FAILED_HRESULT(WTRiASSimpleObject(Obj) -> get_LocalHandle (&lONr));
			m_phMap -> insert (CObjHandleMap::value_type (hObj, lONr));
			*ppIObj = Obj.detach();
		}
		else {
		// Objekt laden, wenn Randbedingungen stimmen
		CSafeArray sa (VT_VARIANT);

			if (NULL != ppConstraints && sa.Attach (*ppConstraints, true)) {
			// evtl. auf Objekttyp bzw. Container achten
			// erster optionaler Parameter enth‰lt evtl. die zu ladenden Objekttypen
			CSafeArrayLock<VARIANT> lock(sa);
			CComVariant vType;

				if (lock.Size() > 0 && SUCCEEDED(vType.ChangeType (VT_I4, &lock[ENSURELOADEDPARAM_ObjectTypes]))) {
				HPROJECT hPr = NULL;

					THROW_FAILED_HRESULT(RetrieveDBHandle (&hPr));

				CNativeObject Obj (hPr, (*it).second);

					if (!Obj) _com_issue_error(TRIASDB_E_BADOBJECTHANDLE);

				DWORD dwType = 0;

					THROW_FAILED_HRESULT(Obj.GetObjectType (&dwType));
					if (!(dwType & V_I4(&vType)))
						return TRIASDB_S_OBJECTDOESNOTFIT;		// Objekttyp stimmt nicht

				// zweiter optionaler Parameter enth‰lt evtl. das Suchfenster
				WTRiASSimpleRectangle rect;
				LPCSTR pcGeomName = OLE2A(bstrGeomName);

					if (lock.Size() > 1 && 
						SUCCEEDED(EnsureLookupWindow (pcGeomName, Obj, lock[ENSURELOADEDPARAM_Window], rect.ppi()))) 
					{
					double dWindow[4];		// XMin, XMax, YMin, YMax

						if (SUCCEEDED(rect -> GetRect(&dWindow[0], &dWindow[2], &dWindow[1], &dWindow[3]))) {
						double dCont[4];		// XMin, XMax, YMin, YMax

							THROW_FAILED_HRESULT(Obj.GetContainer (pcGeomName, dCont));
							if (dCont[1] < dWindow[0] || dCont[0] > dWindow[1] ||
								dCont[3] < dWindow[2] || dCont[2] > dWindow[3])
							{
								return TRIASDB_S_OBJECTDOESNOTFIT;		// Objekt liegt auﬂerhalb des zu ladenden Bereiches
							}
						}
					}
				}
			}

		// Objekt existiert, Randbedingungen stimmen, also laden
			THROW_FAILED_HRESULT(GetOrCreateObject (hObj, (*it).second, OBJECTTYPE_Unknown, CLSID_TRiASSimpleObject, ppIObj));
			_ASSERTE(hObj == (*it).first);		// Handle darf sich nicht ‰ndern
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleObjects::MayUnload (INT_PTR hObj)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

CComSemaphore<_ThreadModel> Sem (m_lOnUnload);	// doppeltes Entladen verhindern
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> _Remove (CComVariant(hObj)));		// aus Objektmenge entfernen

	return S_OK;
}

STDMETHODIMP CTRiASSimpleObjects::get_LocalHandle (INT_PTR *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return E_UNEXPECTED;
	TEST_OUT_PARAM(pVal);

	*pVal = m_lIdent;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierungsfunktionen

HRESULT CTRiASSimpleObjects::EnsureObjectsCount()
{
	if (HasType (m_rgInitState, INITSTATE_CountsInitialized))
		return S_OK;		// wurden bereits geladen

	ResetCounters (true);

HPROJECT hPr = NULL;
OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
WTRiASObjects BaseObjs;
DWORD dwTypes = 0;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	{
	CComSemaphore<_ThreadModel> Sem (m_lInitData);		// Teilrekursion verhindern

		RETURN_FAILED_HRESULT(BaseObjs -> get_Types(&rgTypes))
		if (OBJECTTYPE_Unknown == rgTypes)	// noch nichts gesetzt --> alle annehmen
			dwTypes = (OTPunkt|OTLinie|OTFlaeche|OTText);
		else
			dwTypes = OBJECTTYPEToBits(rgTypes);
	}
	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

CNativeIdent Ident (hPr, m_lIdent, dwTypes);

// Z‰hler nur dann sofort liefern, wenn's schnell geht (neue GeoDB)
	dwTypes = 0;
	if (E_FAIL == Ident.GetObjectTypesAndCounts (CNativeIdent::LOOKUPSPEED_IMMEDIATE, dwTypes, m_lCounts)) 
	{
	// ansonsten alte Datenbank, daher gleich alles einlesen, da sowieso enumeriert werden muﬂ
		RETURN_FAILED_HRESULT(EnsureLocalHandleCont(true));
		_ASSERTE(NULL != m_pObjs);

	DWORD dwTypesToLookFor = OBJECTTYPEToBits(rgTypes);

		if (0 == dwTypesToLookFor)
			dwTypesToLookFor = Ident.GetTypes();

		RETURN_FAILED_HRESULT(Ident.GetObjects (dwTypesToLookFor, *m_pObjs, m_lCounts));

		if (m_lCounts[0]) SetType (dwTypes, OTPunkt);
		if (m_lCounts[1]) SetType (dwTypes, OTLinie);
		if (m_lCounts[2]) SetType (dwTypes, OTFlaeche);
		if (m_lCounts[3]) SetType (dwTypes, OTText);
		m_lCountAll = m_pObjs -> size();
		SetType (m_rgInitState, INITSTATE_CountsInitialized|INITSTATE_LocalHandlesInitialized);

//		_ASSERTE(m_lCountAll == m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3]);

	} else {
		_ASSERTE(0 == m_lCounts[0] || HasType(dwTypes, OTPunkt));
		_ASSERTE(0 == m_lCounts[1] || HasType(dwTypes, OTLinie));
		_ASSERTE(0 == m_lCounts[2] || HasType(dwTypes, OTFlaeche));
		_ASSERTE(0 == m_lCounts[3] || HasType(dwTypes, OTText));

		m_lCountAll = m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3];
		SetType (m_rgInitState, INITSTATE_CountsInitialized);
	}
	RETURN_FAILED_HRESULT(BaseObjs -> put_Count (m_lCountAll));		// Basisklasse informieren

// vorhandene Objekttypen abgleichen
	if (dwTypes != OBJECTTYPEToBits(rgTypes)) {
	// in einer der Ansichten ist mehr definiert als real vorhanden
		RETURN_FAILED_HRESULT(BaseObjs -> put_Types(BitsToOBJECTTYPE(dwTypes)));
	}

// Features initialisieren
	return EnsureFeatures (VARIANT_FALSE);
}

HRESULT CTRiASSimpleObjects::EnsureObjectsLocalHandles()
{
	if (HasType (m_rgInitState, INITSTATE_LocalHandlesInitialized))
		return S_OK;		// wurden bereits geladen

	ResetCounters();

HPROJECT hPr = NULL;
OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_Types(&rgTypes))
	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

DWORD dwTypes = OBJECTTYPEToBits(rgTypes);
CNativeIdent Ident (hPr, m_lIdent, dwTypes);

	RETURN_FAILED_HRESULT(EnsureLocalHandleCont(true));
	_ASSERTE(NULL != m_pObjs);

	RETURN_FAILED_HRESULT(Ident.GetObjects (dwTypes, *m_pObjs, m_lCounts));
	_ASSERTE(m_lCountAll == m_pObjs -> size());
	_ASSERTE(m_lCountAll == m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3]);

	SetType (m_rgInitState, INITSTATE_CountsInitialized|INITSTATE_LocalHandlesInitialized);

// Features initialisieren
	return EnsureFeatures(VARIANT_FALSE);
}

/* static */
HRESULT CALLBACK CTRiASSimpleObjects::EnumObjectCallBack (INT_PTR lObject, DWORD dwType, UINT_PTR dwData)
{
	_ASSERTE(0L != dwData);
	_ASSERTE(1 == BitCount (dwType));		// jeweils nur ein Objekttyp erlaubt

CEnumObjectCallback *pData = (CEnumObjectCallback *)dwData;
INT_PTR hObj = NULL;

	_ASSERTE(pData -> m_dwTypes & dwType);

OBJECTTYPE rgType = BitsToOBJECTTYPE(dwType);
HRESULT hr = pData -> m_pThis -> GetOrCreateObject (hObj, lObject, rgType, CLSID_TRiASSimpleObject);

	if (SUCCEEDED(hr)) {
		if (!HasType (pData -> m_pThis -> m_rgInitState, INITSTATE_CountsInitialized)) 
			pData -> m_pThis -> IncrementObjectCount (rgType, FALSE);
		
	// immer zur Map hinzuf¸gen, da lediglich (maximal) Counts initialisiert sind
		_ASSERTE(NULL != pData -> m_pThis -> m_phMap);		// muﬂ bereits initialisiert sein
		pData -> m_pThis -> m_phMap -> insert (CObjHandleMap::value_type (hObj, lObject));
		return S_OK;	// S_FALSE unterdr¸cken, da sonst Enumeration abgebrochen wird
	}
	return hr;	
}

// Sicherstellen, daﬂ den Objektnummern Handles zugeordnet sind
HRESULT CTRiASSimpleObjects::EnsureObjectsHandles()
{
	if (HasType (m_rgInitState, INITSTATE_HandlesInitialized))
		return S_OK;		// wurden bereits geladen

	RETURN_FAILED_HRESULT(EnsureObjectsLocalHandles());		// Objektnummern sicherstellen
	_ASSERTE(HasType (m_rgInitState, INITSTATE_LocalHandlesInitialized));
	_ASSERTE(NULL != m_pObjs);

	RETURN_FAILED_HRESULT(EnsureHandleMap());
	_ASSERTE(NULL != m_phMap);

WDispatch Parent;
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_Parent(Parent.ppi()));

WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
INT_PTR lCookieHolder = g_pDBEngine -> GetCookieHolder (CComBSTR(g_cbObjectMap));

	for (CLocalHandles::iterator it = m_pObjs -> begin(); it != m_pObjs -> end(); ++it)
	{
	WTRiASObject Obj;

		if (FAILED(Map -> GetObjectEx (*it, OBJECTMAPMODE_GetObjectFromNativeHandle, Obj.ppu())))	// noch nie geladen
			m_phMap -> insert (CObjHandleMap::value_type (g_pDBEngine -> GetNextCookie(lCookieHolder), *it));
		else {
		// Objekt hat bereits eine Zugriffsnummer
			_ASSERTE(SupportsInterface (Obj, (ITRiASObject *)NULL));

		INT_PTR hObj = NULL;

			RETURN_FAILED_HRESULT(Obj -> get_Handle (&hObj));
			m_phMap -> insert (CObjHandleMap::value_type (hObj, *it));
		}
	}

	ClearType (m_rgInitState, INITSTATE_LocalHandlesInitialized);
	SetType (m_rgInitState, INITSTATE_HandlesInitialized);
	DELETE_OBJ(m_pObjs);
	return S_OK;
}

HRESULT CTRiASSimpleObjects::EnsureObjectsLoaded()
{
	if (HasType (m_rgInitState, INITSTATE_ObjectsInitialized))
		return S_OK;		// wurden bereits geladen

// Objekte zur collection hinzuf¸gen
	if (HasType (m_rgInitState, INITSTATE_LocalHandlesInitialized))
	{
		_ASSERTE(!HasType (m_rgInitState, INITSTATE_HandlesInitialized));
		RETURN_FAILED_HRESULT(EnsureObjectsHandles());		// Handles zu Objektnummern zuordnen
		_ASSERTE(HasType (m_rgInitState, INITSTATE_HandlesInitialized));
	}

	if (HasType (m_rgInitState, INITSTATE_HandlesInitialized)) {
	// Objektnummern bereits eingelesen (kein DB-Zugriff mehr notwendig), Handles zugeordnet
		for (CObjHandleMap::iterator it = m_phMap -> begin(); it != m_phMap -> end(); ++it)
		{
		INT_PTR hObj = (*it).first;

			RETURN_FAILED_HRESULT(GetOrCreateObject (hObj, (*it).second, OBJECTTYPE_Unknown, CLSID_TRiASSimpleObject));
			_ASSERTE((*it).first == hObj);	// darf sich nicht mehr ‰ndern
		}
	} 
	else {
	// noch nichts (auﬂer vielleicht die Z‰hler) eingelesen
	OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
	WTRiASObjects BaseObjs;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
		RETURN_FAILED_HRESULT(BaseObjs -> get_Types(&rgTypes))

	HPROJECT hPr = NULL;

		ResetCounters();
		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));
		RETURN_FAILED_HRESULT(EnsureHandleMap (true));

	CNativeIdent Ident (hPr, m_lIdent, OBJECTTYPEToBits(rgTypes));
	CEnumObjectCallback CallBackData;

		CallBackData.m_pThis = this;
		CallBackData.m_pIdent = &Ident;
#if defined(_DEBUG)
		CallBackData.m_dwTypes = OBJECTTYPEToBits(rgTypes);
#endif // _DEBUG
		RETURN_FAILED_HRESULT(Ident.EnumObjects (EnumObjectCallBack, (UINT_PTR)&CallBackData));

	// Objekte wurden in EnumObjectsCallbck mitgez‰hlt
		SetType (m_rgInitState, INITSTATE_CountsInitialized);
		_ASSERTE(m_lCountAll == m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3]);
	}
	SetType (m_rgInitState, INITSTATE_ObjectsInitialized);

// Features initialisieren
	return EnsureFeatures(VARIANT_FALSE);
}

HRESULT CTRiASSimpleObjects::EnsureFeatures(VARIANT_BOOL fForceSetup)
{
// da alle Objektklassen in TRiAS einen identischen Satz von Eigenschaften 
// (Merkmalen) besitzen, wird diese Collection auch nur einmal gehalten (an
// der Datenbank).
WTRiASPropertyBase PropBase;

// unterst¸tzte Attribute mit Objektmenge assoziieren
	if (!m_fHasFeatures || fForceSetup) {
		COM_TRY {
		WTRiASDatabase DBase;

			THROW_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, DBase.ppi()));
			THROW_FAILED_HRESULT(DBase -> QueryInterface(PropBase.ppi()));

		VARIANT_BOOL fHasFeats = GetPropertyFrom (PropBase, g_cbHasSimpleFeatures, VARIANT_FALSE);
		WTRiASFeatures Feats (GetPropertyFrom (PropBase, g_cbSimpleFeatures, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab

			_ASSERTE(Feats.IsValid());
			THROW_FAILED_HRESULT(WTRiASObjects(m_BaseUnk) -> put_Features (Feats))

			if (!fHasFeats) {
			// Features-Collection initialisieren
				THROW_FAILED_HRESULT(Feats -> Refresh());	// Features erstmalig einlesen
				THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbHasSimpleFeatures, CComVariant(true)));
			}
			m_fHasFeatures = true;

		} COM_CATCH;
	}

// existierende GeometrieFeatures initialisieren
	if (!m_fHasGeoFeatures || fForceSetup) {
		COM_TRY {
			if (!PropBase.IsValid()) {
			WTRiASDatabase DBase;

				THROW_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, DBase.ppi()));
				THROW_FAILED_HRESULT(DBase -> QueryInterface(PropBase.ppi()));
			}

		VARIANT_BOOL fHasGeoFeats = GetPropertyFrom (PropBase, g_cbHasSimpleGeoFeatures, VARIANT_FALSE);
		WTRiASFeatures GeoFeats (GetPropertyFrom (PropBase, g_cbSimpleGeoFeatures, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab

			_ASSERTE(GeoFeats.IsValid());
			THROW_FAILED_HRESULT(WTRiASObjects(m_BaseUnk) -> put_GeometryFeatures (GeoFeats))

			if (!fHasGeoFeats) {
			// Features-Collection initialisieren
				THROW_FAILED_HRESULT(GeoFeats -> Refresh());	// Features erstmalig einlesen
				THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbHasSimpleGeoFeatures, CComVariant(true)));
			}
			m_fHasGeoFeatures = true;

		} COM_CATCH;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectsCallback

STDMETHODIMP CTRiASSimpleObjects::get_DefaultType (BSTR *pbstrType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(pbstrType);

CIID Guid (CLSID_TRiASSimpleObject);		// DefaultType der _Elemente_ !
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

HRESULT CTRiASSimpleObjects::GetOrCreateObject (
	INT_PTR &rhObj, LONG lObject, OBJECTTYPE rgType, REFCLSID rClsId, 
	ITRiASObject **ppIObj, BOOL fCountObjects)
{
// Object neu erzeugen/wiederverwenden und zur Collection hinzuf¸gen
WDispatch App;
WDispatch Parent;
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));

	RETURN_FAILED_HRESULT(BaseObjs -> get_Application (App.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_Parent(Parent.ppi()));

// ObjektHandle holen
INT_PTR hObjs = 0;

	RETURN_FAILED_HRESULT(BaseObjs -> get_Handle (&hObjs));

WTRiASObject Object;
WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
CInitializeSimpleObject InitObj (App, Parent, m_lIdent, hObjs, rgType);
HRESULT hr = E_FAIL;
OBJECTMAPMODE rgMode = OBJECTMAPMODE(OBJECTMAPMODE_CreateObjectHandle);
//OBJECTMAPMODE rgMode = OBJECTMAPMODE(OBJECTMAPMODE_CreateObjectHandle|OBJECTMAPMODE_DoNotRegisterNativeHandle);

#if defined(_USE_CLASSFACTORY_CACHE)
	if (IsEqualCLSID(rClsId, CLSID_TRiASSimpleObject))
		hr = FindInMapOrCreateObjectEx(Map, lObject, rhObj, Object, MakeSimpleObjects, InitObj, rgMode);
	else
#endif // defined(_USE_CLASSFACTORY_CACHE)
		hr = FindInMapOrCreateObjectEx(Map, lObject, rhObj, Object, rClsId, InitObj, rgMode);

	if (S_OK == hr) {		// S_FALSE heiﬂt: Objekt existiert bereits
		RETURN_FAILED_HRESULT(BaseObjs -> _Add (Object, VARIANT_FALSE));

	// zus‰tzlich Objekte Z‰hlen (da wir ja einmal dabei sind ...)
		if (fCountObjects && HasType (m_rgInitState, INITSTATE_CountsInitialized)) {
#if defined(_DEBUG)
		OBJECTTYPE rgTypeDeb = OBJECTTYPE_Unknown;

			RETURN_FAILED_HRESULT(Object -> get_Type (&rgTypeDeb));
			_ASSERTE(OBJECTTYPE_Unknown == rgType || rgType == rgTypeDeb);
#endif // _DEBUG

		// bei bisher unbekanntem Typ, diesen herausfinden, da IncCount sonst fehlerhaft ist
			if (OBJECTTYPE_Unknown == rgType)
			{
				RETURN_FAILED_HRESULT(Object -> get_Type(&rgType));
			}

//			_ASSERTE(OBJECTTYPE_Unknown != rgType);		// jetzt sollte der Objekttyp bekannt sein
			IncrementObjectCount (rgType);
		}
	}
	if (SUCCEEDED(hr) && NULL != ppIObj)
		*ppIObj = Object.detach();

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// Erstmalige Initialisierung
STDMETHODIMP CTRiASSimpleObjects::SetupObjects(SETUPOBJECTSMODE rgMode)
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

// doppelte Initialisierung verhindern
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch (rgMode) {
	case SETUPOBJECTSMODE_Count:
		return EnsureObjectsCount();

	case SETUPOBJECTSMODE_Load:
		return EnsureObjectsLoaded();

	case SETUPOBJECTSMODE_InitOrLoad:
		return S_OK;

	case SETUPOBJECTSMODE_ResetObjectInfo:
		ResetCounters(true);		// alles vergessen
		return S_OK;

	default:
		_ASSERTE(SETUPOBJECTSMODE_Count == rgMode || 
			SETUPOBJECTSMODE_Load == rgMode || 
			SETUPOBJECTSMODE_InitOrLoad == rgMode ||
			SETUPOBJECTSMODE_ResetObjectInfo == rgMode);
		break;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CTRiASSimpleObjects::SetupFeatures(SETUPFEATURESMODE rgMode)
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

	return EnsureFeatures((rgMode & SETUPFEATURESMODE_Force) ? TRUE : FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// Ein neues Objekt soll erzeugt werden
STDMETHODIMP CTRiASSimpleObjects::OnCreate (BSTR Name, BSTR Type, OBJECTTYPE rgType, ITRiASObject **ppIObj)
{
	TEST_OUT_PARAM(ppIObj);

// nur behandeln, wenn wir nicht derzeit initialisiert werden
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	COM_TRY {
	// jetzt wirklich erzeugen
	CIID ClsId (Type, CIID::INITCIID_InitFromProgId);

		if (!ClsId)	ClsId = CLSID_TRiASSimpleObject;	// default ClsId
	
	WTRiASObject Obj;
	INT_PTR hObj = NULL;	// Handle muﬂ vergeben werden

		THROW_FAILED_HRESULT(GetOrCreateObject (hObj, 0L, rgType, ClsId, Obj.ppi(), TRUE));

	// Objekte bereits instantiiert, nun das Objekthandle zu unserer Liste hinzuf¸ge
		if (HasType (m_rgInitState, INITSTATE_ObjectsInitialized|INITSTATE_HandlesInitialized)) {
		INT_PTR lONr = 0L;
		
			THROW_FAILED_HRESULT(WTRiASSimpleObject(Obj) -> get_LocalHandle (&lONr));
			m_phMap -> insert (CObjHandleMap::value_type (hObj, lONr));
		}
		else if (HasType (m_rgInitState, INITSTATE_LocalHandlesInitialized)) {
		// Handles bereits eingelesen, nun die Objektnummer zu unserer Liste hinzuf¸gen
		INT_PTR lONr = 0;

			THROW_FAILED_HRESULT(WTRiASSimpleObject(Obj) -> get_LocalHandle (&lONr));
			m_pObjs -> push_back ((ULONG)lONr);
		}

// Der Name eines GeoDB-Objektes ist ab sofort (#HK000312) dessen Guid (Eindeutigkeit und
// Invarianz des Monikers)
//		THROW_FAILED_HRESULT(Obj -> put_Name(Name));
		*ppIObj = Obj.detach();

//#pragma MESSAGE("TODO: Sobald Objekttyp f¸r neu erzeugtes Objekt feststeht, Objektz‰hler korrigieren!")
//		if (OBJECTTYPE_Unknown != rgType)
//			IncrementObjectCount (rgType); 	// neues Objekt z‰hlen (da wir ja einmal dabei sind ...)

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Irgend was wurde modifiziert
STDMETHODIMP CTRiASSimpleObjects::OnChanging(CHANGEDOBJECTS rgWhat, VARIANT vNewValue, VARIANT_BOOL *pDisAllow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == pDisAllow)
		return E_POINTER;

	*pDisAllow = VARIANT_FALSE;		// immer einverstanden sein
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Irgend was wurde modifiziert
STDMETHODIMP CTRiASSimpleObjects::OnChanged(CHANGEDOBJECTS rgWhat, VARIANT vOldValue)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

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
// Ein Objekt soll gelˆscht werden
STDMETHODIMP CTRiASSimpleObjects::OnDelete (INT_PTR hObj)
{
WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectMap());	// GetProperty liefert AddRef'ed ab
WTRiASObject Obj;

	if (Map.IsValid() && SUCCEEDED(Map -> GetObject ((INT_PTR)hObj, Obj.ppu()))) {
		_ASSERTE(SupportsInterface (Obj, (ITRiASObject *)NULL));
		RETURN_FAILED_HRESULT(OnRemove (Obj));		// gelˆscht wird beim Objekt
		RETURN_FAILED_HRESULT(Obj -> Delete());		// Objekt selbst auffordern, sich zu lˆschen
		return S_OK;		// ok, alles vorbei
	}

	RETURN_FAILED_HRESULT(E_UNEXPECTED);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Ein Objekt soll zu dieser Objektmenge hinzugef¸gt werden
STDMETHODIMP CTRiASSimpleObjects::OnAdd (ITRiASObject *pIObj, CLASSIFYMODE rgMode)
{
	if (CLASSIFYMODE_DoNotClassify == rgMode)
		return S_OK;	// nicht umklassifizieren/Rekursion verhindern

//	RETURN_FAILED_HRESULT(EnsureObjectsLoaded());		// Objekte m¸ssen geladen sein

// das Objekt muﬂ ein TRiAS-Objekt sein
WTRiASSimpleObject SimpleObj;
INT_PTR lONr = 0L;

	if (FAILED(pIObj -> QueryInterface(SimpleObj.ppi())))
		return E_UNEXPECTED;
	RETURN_FAILED_HRESULT(SimpleObj -> get_LocalHandle (&lONr));

	if (!HasType (rgMode, CLASSIFYMODE_InitObjectType)) {
	// jetzt Objekt umklassifizieren
	HPROJECT hPr = NULL;

		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

	CNativeObject Obj (hPr, lONr);

		if (!Obj) return TRIASDB_E_BADOBJECTHANDLE;

		RETURN_FAILED_HRESULT(Obj.ModifyIdent (m_lIdent));

		COM_TRY {
		// Objekt aus seiner Objektklasse entfernen
		INT_PTR hObjs = NULL;
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());
		WUnknown Unk;

			THROW_FAILED_HRESULT(pIObj -> get_ObjectsHandle (&hObjs));
			THROW_FAILED_HRESULT(Map -> GetObject (hObjs, Unk.ppi()));
			THROW_FAILED_HRESULT(WTRiASObjects(Unk) -> _Remove (CComVariant(pIObj)));

		// jetzt Objekt dieser ObjsColl hinzuf¸gen
			THROW_FAILED_HRESULT(WTRiASObjects(m_BaseUnk) -> _Add (pIObj, VARIANT_TRUE));

		} COM_CATCH;
	}

// lokale Daten nachziehen
OBJECTTYPE rgType = OBJECTTYPE_Unknown;
INT_PTR hObj = NULL;

	RETURN_FAILED_HRESULT(pIObj -> get_Handle (&hObj));
	if (HasType (m_rgInitState, INITSTATE_CountsInitialized)) {
		RETURN_FAILED_HRESULT(pIObj -> get_Type (&rgType));

	// Objekttyp an der Objektklasse korrigieren
	OBJECTTYPE rgObjsTypes = OBJECTTYPE_Unknown;
	WTRiASObjects BaseObjs(m_BaseUnk);

		RETURN_FAILED_HRESULT(BaseObjs -> get_Types(&rgObjsTypes));
		RETURN_FAILED_HRESULT(BaseObjs -> put_Types(OBJECTTYPE(rgType | rgObjsTypes)));	// Objekttypen kombinieren

	// Z‰hler nachf¸hren
		IncrementObjectCount (rgType, CLASSIFYMODE_InitObjectType != rgMode);
	}
	if (HasType (m_rgInitState, INITSTATE_LocalHandlesInitialized)) 
		m_pObjs -> push_back ((ULONG)lONr);
	if (HasType (m_rgInitState, INITSTATE_HandlesInitialized)) 
		m_phMap -> insert(CObjHandleMap::value_type (hObj, lONr));

	return S_OK;
}

STDMETHODIMP CTRiASSimpleObjects::MapFeatureHandle (VARIANT vNameOrHandle, VARIANT *pvNewNameOrHandle)
{
	return CComVariant(vNameOrHandle).Detach (pvNewNameOrHandle);
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASSimpleObjects::OnFinalRelease()
{
// aus Map des Parent's entfernen
	COM_TRY {
	WTRiASObjects BaseObjs;
	WDispatch Parent;

		if (SUCCEEDED(m_BaseUnk -> QueryInterface (BaseObjs.ppi())))
			BaseObjs -> get_Parent (Parent.ppi());
			
	// aus Database-Tabelle entfernen
		if (Parent.IsValid()) {
		INT_PTR hObjs = NULL;

			THROW_FAILED_HRESULT(BaseObjs -> get_Handle (&hObjs));

		WTRiASObjectHandleMap MapP (GetPropertyFrom (Parent, g_cbObjectsMap, (IDispatch *)NULL), false);

			_ASSERTE(MapP.IsValid());
			if (MapP.IsValid()) 
				VERIFY(S_OK == MapP -> RemoveObject (hObjs, OBJECTMAPMODE_RemoveAllReferences));
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Ein Objekt soll aus dieser Objektmenge entfernt werden
STDMETHODIMP CTRiASSimpleObjects::OnRemove (ITRiASObject *pIObj)
{
	if (IsSemaphoreSignaled (m_lOnUnload, *this)) 
		return S_FALSE;		// Objekt lediglich entladen

// Z‰hler etc. korrigieren
OBJECTTYPE rgType = OBJECTTYPE_Unknown;

	if (HasType (m_rgInitState, INITSTATE_CountsInitialized)) {
		RETURN_FAILED_HRESULT(pIObj -> get_Type (&rgType));
		DecrementObjectCount (rgType);
	}
	if (HasType (m_rgInitState, INITSTATE_LocalHandlesInitialized)) {
		m_pObjs -> clear();
		ClearType (m_rgInitState, INITSTATE_LocalHandlesInitialized);
	}
	if (HasType (m_rgInitState, INITSTATE_HandlesInitialized)) {
	INT_PTR hObj = NULL;

		RETURN_FAILED_HRESULT(pIObj -> get_Handle (&hObj));

	CObjHandleMap::iterator it = m_phMap -> find (hObj);

		_ASSERTE(it != m_phMap -> end());
		m_phMap -> erase(it);
	}
	return S_FALSE;		// not here
}

/////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CTRiASSimpleObjects::OnChangedName()
{
	USES_CONVERSION;

// Namen vom Bezugsobjekt besorgen
CComBSTR bstrName;

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_Name (CLEARED(&bstrName)));

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// ggf. Ident initialisieren
	if (0 == m_lIdent)
		BaseObjs -> get_Handle ((INT_PTR *)&m_lIdent);

// neuen Wert in GeoDB schreiben
CNativeIdent Ident (hPr, m_lIdent);

	RETURN_FAILED_HRESULT(Ident.SetName (OLE2A(bstrName)));
	RETURN_FAILED_HRESULT(SetPropertyBy (WTRiASPropertyBase(BaseObjs), g_cbNameIsDefault, VARIANT_FALSE, true, LOCALE_ENGLISH));
	return S_OK;
}

HRESULT CTRiASSimpleObjects::OnChangedDescription()
{
	USES_CONVERSION;

// Beschreibung vom Bezugsobjekt besorgen
CComBSTR bstrDesc;
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_Description(CLEARED(&bstrDesc)))

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// ggf. Ident initialisieren
	if (0 == m_lIdent)
		BaseObjs -> get_Handle ((INT_PTR *)&m_lIdent);

// neuen Wert in GeoDB schreiben
CNativeIdent Ident (hPr, m_lIdent);

	return Ident.SetDescription (OLE2A(bstrDesc));
}

HRESULT CTRiASSimpleObjects::OnChangedOKS()
{
	USES_CONVERSION;

// Objektklassenschl¸ssel vom Bezugsobjekt besorgen
CComBSTR bstrOKS;
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_OKS(CLEARED(&bstrOKS)))

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// Ident muﬂ initialisiert sein
	_ASSERTE(0 != m_lIdent);

// neuen Wert in GeoDB schreiben
CNativeIdent Ident (hPr, m_lIdent);

	RETURN_FAILED_HRESULT(Ident.SetOKS (OLE2A(bstrOKS)));

// Kurztext kann sich ge‰ndert haben
char cbBuffer[_MAX_PATH];
HRESULT hr = E_FAIL;

	Ident.ReportPbdErrors (FALSE);	// evtl. Fehler nicht melden/Rekursion vermeiden
	RETURN_FAILED_HRESULT(hr = Ident.GetName (cbBuffer, sizeof(cbBuffer)));
	if (S_FALSE == hr) {
	// der Name der Objektklasse ist lediglich tempor‰r generiert
		SetPropertyBy (WTRiASPropertyBase(BaseObjs), g_cbNameIsDefault, VARIANT_TRUE, true, LOCALE_ENGLISH);
	}

CComSemaphore<_ThreadModel> Sem (m_lInitData);	// doppeltes Initialisieren verhindern

	RETURN_FAILED_HRESULT(BaseObjs -> put_Name (CComBSTR (cbBuffer)));
	return S_OK;
}

HRESULT CTRiASSimpleObjects::OnChangedHandle()
{
	return S_OK;
}

HRESULT CTRiASSimpleObjects::OnChangedTypes()
{
	return S_OK;
}

HRESULT CTRiASSimpleObjects::OnChangedROMode()
{
// Schreibschutzflag vom Bezugsobjekt besorgen
CComBool fUpdatable;;
WTRiASObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	RETURN_FAILED_HRESULT(BaseObjs -> get_Updatable (&fUpdatable))

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// Ident muﬂ initialisiert sein
	_ASSERTE(0 != m_lIdent);

// neuen Wert in GeoDB schreiben
CNativeIdent Ident (hPr, m_lIdent);

	return Ident.SetReadOnly (!fUpdatable);
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSearchObjects
STDMETHODIMP CTRiASSimpleObjects::ConsiderSearch (BSTR bstrCommand, SAFEARRAY *pParams)
{
WTRiASSearchObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	return BaseObjs -> ConsiderSearch (bstrCommand, pParams);
}

STDMETHODIMP CTRiASSimpleObjects::SearchObjects (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
WTRiASSearchObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	return BaseObjs -> SearchObjects (bstrCommand, pIObjs, pParams);
}

STDMETHODIMP CTRiASSimpleObjects::ConstraintObjects (ITRiASObjects *pIObjs)
{
WTRiASSearchObjects BaseObjs;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObjs.ppi()));
	return BaseObjs -> ConstraintObjects (pIObjs);
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
void CTRiASSimpleObjects::IncrementObjectCount (OBJECTTYPE rgType, BOOL fFullCnt)
{
	switch (rgType) {
	case OBJECTTYPE_Point:
		m_lCounts[0]++; break;
	case OBJECTTYPE_Line:
		m_lCounts[1]++; break;
	case OBJECTTYPE_Area:
		m_lCounts[2]++; break;
	case OBJECTTYPE_Text:
		m_lCounts[3]++; break;
	}

	if (!HasType (m_rgInitState, INITSTATE_CountsInitialized) || !fFullCnt) 	
		return;

	m_lCountAll++;
	WTRiASObjects(m_BaseUnk) -> put_Count (m_lCountAll);		// Basisklasse informieren

//	_ASSERTE(m_lCountAll == m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3]);
}

void CTRiASSimpleObjects::DecrementObjectCount (OBJECTTYPE rgType)
{
	if (!HasType (m_rgInitState, INITSTATE_CountsInitialized)) 	
		return;

	switch (rgType) {
	case OBJECTTYPE_Point:
		m_lCounts[0] = max(m_lCounts[0]-1L, 0L); break;
	case OBJECTTYPE_Line:
		m_lCounts[1] = max(m_lCounts[1]-1L, 0L); break;
	case OBJECTTYPE_Area:
		m_lCounts[2] = max(m_lCounts[2]-1L, 0L); break;
	case OBJECTTYPE_Text:
		m_lCounts[3] = max(m_lCounts[3]-1L, 0L); break;
	}
	m_lCountAll = max(m_lCountAll-1L, 0L);
	WTRiASObjects(m_BaseUnk) -> put_Count (m_lCountAll);		// Basisklasse informieren

//	_ASSERTE(m_lCountAll == m_lCounts[0] + m_lCounts[1] + m_lCounts[2] + m_lCounts[3]);
}
