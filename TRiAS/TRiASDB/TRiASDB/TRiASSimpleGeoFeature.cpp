// @doc
// @module TRiASSimpleGeoFeature.cpp | Implementation of the <c CTRiASSimpleGeoFeature> class

#include "stdafx.h"

#include "Strings.h"

#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>
#include <Com/SafeArray.h>

#include <NativePbd.h>
#include <NativeObject.h>
#include <CSRectGeom.h>

#include "Wrapper.h"
#include "TRiASDBEngine.h"
#include "TRiASSimpleGeoFeature.h"

#import "Tlb/TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids \
	exclude("IStaticCollection", "IEnumCoordSystemNames")

using namespace trias_nativepbd;
using namespace trias_nativeobject;

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASSimpleGeoFeature)

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASSimpleGeoFeature::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASSimpleGeoFeature, CTRiASSimpleGeoFeature)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCSTransform);			// WTRiASCSTransform
DefineSmartInterface(TRiASTransformGeometry);	// WTRiASTransformGeometry
DefineSmartInterface(TRiASCloneGeometry);		// WTRiASCloneGeometry
DefineSmartInterface(TRiASCSGeometryProperties);	// WTRiASCSGeometryProperties
DefineSmartInterface(OleClientSite);			// WOleClientSite

/////////////////////////////////////////////////////////////////////////////
// local required functions
inline GEOMETRYTYPE OBJECTTYPEToGEOMETRYTYPE (OBJECTTYPE rgType)
{
	return static_cast<GEOMETRYTYPE>(rgType);
}

inline OBJECTTYPE GEOMETRYTYPEToOBJECTTYPE (GEOMETRYTYPE rgGeoType)
{
	return static_cast<OBJECTTYPE>(rgGeoType & GEOMETRYTYPE_SimpleMask);
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleGeoFeature

STDMETHODIMP CTRiASSimpleGeoFeature::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleFeature,
		&IID_ITRiASFeature,
		&IID_ITRiASSearchObjects,
	};
	for (unsigned int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CTRiASSimpleGeoFeature::FinalRelease (void)
{
// aus Map des Parent entfernen
//	COM_TRY {
//	WTRiASFeature BaseFeat;
//	WDispatch Parent;
//	INT_PTR hGeom = NULL;
//
//		if (SUCCEEDED(m_BaseUnk -> QueryInterface (IID_ITRiASFeature, BaseFeat.ppv()))) {
//			BaseFeat -> get_Parent (Parent.ppi());
//			BaseFeat -> get_Handle (&hGeom);
//		}
//			
//	// aus Objects-Tabelle entfernen
//	WDispatch DBase;
//
//		if (SUCCEEDED(FindSpecificParent (Parent, IID_ITRiASDatabase, DBase.ppv()))) {
//		WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbFeatureMap, (IDispatch *)NULL), false);
//
//			_ASSERTE(Map.IsValid());
//			if (Map.IsValid() && NULL != hGeom) 
//				VERIFY(S_OK == Map -> RemoveObject ((LONG)hGeom, OBJECTMAPMODE_RemoveAllReferences));
//		}
//	} COM_CATCH_IGNORE;

// sonstige Aufräumarbeiten
	m_BaseUnk.Assign(NULL);
	m_hPr = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureCallback
STDMETHODIMP CTRiASSimpleGeoFeature::get_DefaultType (BSTR *pbstrType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pbstrType)
		return E_POINTER;

CIID Guid (GetObjectCLSID());
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASSimpleGeoFeature::SetupFeature (SETUPFEATUREMODE rgWhat)
{
	return S_OK;
}

STDMETHODIMP CTRiASSimpleGeoFeature::OnChanging(CHANGEDFEATURE rgWhat, VARIANT vNewValue, VARIANT_BOOL *pfDisAllow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == pfDisAllow)
		return E_POINTER;
	*pfDisAllow = VARIANT_FALSE;		// immer zulassen
	return S_OK;
}

STDMETHODIMP CTRiASSimpleGeoFeature::OnChanged(CHANGEDFEATURE rgWhat, VARIANT vOldValue)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn wir nicht derzeit initialisiert werden
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch (rgWhat) {
	case CHANGEDFEATURE_Name:
		return OnChangedName();

	case CHANGEDFEATURE_Description:
		return OnChangedDescription();

	case CHANGEDFEATURE_Handle:
		return OnChangedHandle();

	case CHANGEDFEATURE_ROMode:
		return OnChangedROMode();

	case CHANGEDFEATURE_Value:
		return S_OK;

	case CHANGEDFEATURE_Type:
		return OnChangedType();

	case CHANGEDFEATURE_Length:		// snh
	default:
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		break;
	}
	return E_INVALIDARG;
}

HRESULT CTRiASSimpleGeoFeature::OnChangedName()
{
	return S_OK;
}

HRESULT CTRiASSimpleGeoFeature::OnChangedDescription()
{
	return S_OK;
}

HRESULT CTRiASSimpleGeoFeature::OnChangedHandle()
{
	return S_OK;
}

HRESULT CTRiASSimpleGeoFeature::OnChangedROMode()
{
	return S_OK;
}

HRESULT CTRiASSimpleGeoFeature::OnChangedType()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Eval: Das, worum es eigentlich geht ...
STDMETHODIMP CTRiASSimpleGeoFeature::Eval(ITRiASObject *pIObj, VARIANT *pVal)
{
CSafeArray sa (VT_VARIANT, 1);

	{
	CSafeArrayLock<VARIANT> lock(sa);

		V_VT(&lock[0]) = VT_ERROR;
		V_ERROR(&lock[0]) = DISP_E_PARAMNOTFOUND;
	}

// erweiterte Routine rufen
SAFEARRAY *psa = sa;

	return EvalEx (pIObj, &psa, pVal);
}

STDMETHODIMP CTRiASSimpleGeoFeature::EvalEx(ITRiASObject *pIObj, SAFEARRAY **ppConstraints, VARIANT *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return TRIASDB_E_INVALID_PARAMETER;

HRESULT hr = S_OK;
SAFEARRAY *psaResult = NULL;

	USES_CONVERSION;
	COM_TRY {
	// Projekthandle vom Parent erfragen
	WTRiASFeature BaseFeat;
	HPROJECT hPrFeat = NULL;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(RetrieveDBHandle (&hPrFeat));

	WTRiASSimpleObject Obj (pIObj);		// nur SimpleObjects bearbeiten
	WTRiASDatabase DBase;
	HPROJECT hPrObj = NULL;

		THROW_FAILED_HRESULT(FindSpecificParent(pIObj, DBase.ppi()));
		THROW_FAILED_HRESULT(DBase -> get_Handle ((INT_PTR *)&hPrObj));
		if (hPrObj != hPrFeat) {
			_ASSERTE(hPrObj == hPrFeat);
			_com_issue_error(TRIASDB_E_BADPROJECTHANDLE);	// TRiAS-Merkmale dürfen nur für TRiAS-Objekte berechnet werden
		}

	// Objektnummer und Namen des Geometriefeldes abfragen
	CComBSTR bstrName;
	INT_PTR lONr = 0L;

		THROW_FAILED_HRESULT(BaseFeat -> get_Name (CLEARED(&bstrName)));
		THROW_FAILED_HRESULT(Obj -> get_LocalHandle(&lONr));

	// Geometrie lesen
	CNativeObject Object (hPrObj, lONr, false);
	LPCSTR pcGeomName = OLE2A(bstrName);
	CIID Guid;		// CSS-Guid

		if (!Object) _com_issue_error(TRIASDB_E_BADOBJECTHANDLE);
		THROW_FAILED_HRESULT(Object.GetGeometryGuid (pcGeomName, &Guid));
	
	// CS-Transformator besorgen
	WTRiASCSTransform CST (GetPropertyFrom (DBase, g_cbTRiASCSTransform, (IDispatch *)NULL), false);

		_ASSERTE(CST.IsValid());

	// evtl. constraint-Rechteck finden
	double dCont[4];		// XMin, XMax, YMin, YMax
	double dWindow[4];		// XMin, XMax, YMin, YMax
	CSafeArray sa (VT_VARIANT);

		if (NULL != ppConstraints && sa.Attach (*ppConstraints, true)) {
		CSafeArrayLock<VARIANT> lock(sa);
		CComVariant vWindow;
		bool fHasWindow = false;

			if (lock.Size() > 1 && SUCCEEDED(vWindow.ChangeType (VT_DISPATCH, &lock[EVALEXPARAM_Window]))) {
			// zweiter optionaler Parameter enthält evtl. Suchfenster
			WDispatch dispRect (V_DISPATCH(&vWindow));
			CCSRectangleGeometry rect (dispRect);

				_ASSERTE(rect.IsValid());
				THROW_FAILED_HRESULT(WTRiASTransformGeometry(dispRect) -> TransformInverse (*(CSID *)&Guid, CST));

				if (SUCCEEDED(rect -> GetRect(&dWindow[0], &dWindow[2], &dWindow[1], &dWindow[3])))
					fHasWindow = true;
			}

		// Geometrie abfragen
			THROW_FAILED_HRESULT(hr = Object.GetGeometry (pcGeomName, &psaResult, fHasWindow ? dWindow : NULL, dCont));
			if (S_OK == hr) {		// nur wenn wirklich alles ok ist
			// evtl. CoordSystemGuid liefern
				if (lock.Size() > 0) {
				// erster optionaler Parameter enthält bei Rückkehr evtl. CoordSysGuid
				CComBSTR bstr (Guid);

					V_VT(&lock[EVALEXPARAM_CoordSysGuid]) = VT_BSTR;
					V_BSTR(&lock[EVALEXPARAM_CoordSysGuid]) = bstr.Detach();
				}

			// evtl. ObjektContainer liefern
				if (lock.Size() > 2) {
				// dritter optionaler Parameter enthält bei Rückkehr evtl. Objektcontainer
				CCSRectangleGeometry rect (dCont[0], dCont[2], dCont[1], dCont[3], 1);
				WDispatch dispRect (rect);

					THROW_FAILED_HRESULT(WTRiASTransformGeometry(dispRect) -> Transform (*(CSID *)&Guid, CST));
					V_VT(&lock[EVALEXPARAM_Envelope]) = VT_DISPATCH;
					V_DISPATCH(&lock[EVALEXPARAM_Envelope]) = dispRect.detach();
				}
			}
		}	// lock goes out of scope
		else {
		// ohne Constraints arbeiten
			THROW_FAILED_HRESULT(hr = Object.GetGeometry (OLE2A(bstrName), &psaResult));
		}

	// GeometrieObjekt erzeugen und Koordinaten transformieren
		if (S_OK == hr) {
		CComVariant vGeom;
		WDispatch disp;
		GEOMETRYTYPE rgType = GEOMETRYTYPE_Unknown;

			V_VT(&vGeom) = VT_ARRAY|VT_UI1;
			V_ARRAY(&vGeom) = psaResult;
			psaResult = NULL;				// doppeltes freigeben verhindern

			THROW_FAILED_HRESULT(g_pDBEngine -> StorageToGeometry (vGeom, &rgType, disp.ppi()));
			THROW_FAILED_HRESULT(WTRiASTransformGeometry(disp) -> Transform (*(CSID *)&Guid, CST));

			V_VT(pVal) = VT_DISPATCH;		// Resultat übergeben
			V_DISPATCH(pVal) = disp.detach();
		} 
		else if (NULL != psaResult) 
			::SafeArrayDestroy (psaResult);

	} COM_CATCH_OP(
		if (NULL != psaResult) ::SafeArrayDestroy (psaResult);
	);

	return hr;
}

STDMETHODIMP CTRiASSimpleGeoFeature::Update(ITRiASObject *pIObj, VARIANT Val)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;

	COM_TRY {
	// Projekthandle vom Parent erfragen
	WTRiASFeature BaseFeat;
	HPROJECT hPrFeat = NULL;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(RetrieveDBHandle (&hPrFeat));

	WTRiASSimpleObject Obj (pIObj);		// nur SimpleObjects bearbeiten
	WTRiASDatabase Parent;
	HPROJECT hPrObj = NULL;

		THROW_FAILED_HRESULT(FindSpecificParent(pIObj, Parent.ppi()));
		THROW_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPrObj));
		if (hPrObj != hPrFeat) {
			_ASSERTE(hPrObj == hPrFeat);
			_com_issue_error(TRIASDB_E_BADPROJECTHANDLE);	// TRiAS-Merkmale dürfen nur für TRiAS-Objekte berechnet werden
		}

	// Objektnummer abfragen
	CComBSTR bstrName;
	INT_PTR lONr = 0L;
	OBJECTTYPE rgType = OBJECTTYPE_Unknown;

		THROW_FAILED_HRESULT(BaseFeat -> get_Name (CLEARED(&bstrName)));
		THROW_FAILED_HRESULT(Obj -> get_LocalHandle(&lONr));
		THROW_FAILED_HRESULT(pIObj -> get_Type(&rgType));

	// Geometrie schreiben
	CNativeObject Object (hPrObj, lONr);

		if (V_VT(&Val) == VT_DISPATCH) {
		// Koordinaten und GeometrieRepräsentation konvertieren
		WTRiASCSTransform CST (GetPropertyFrom (Parent, g_cbTRiASCSTransform, (IDispatch *)NULL), false);
		CComVariant vVal;
		CIID Guid;		// CSS-Guid

			USES_CONVERSION;
			THROW_FAILED_HRESULT(Object.GetGeometryGuid (OLE2A(bstrName), &Guid));
			_ASSERTE(CST.IsValid());

		// Geometrie kopieren und entsprechend bearbeiten
		WDispatch disp;

			THROW_FAILED_HRESULT(WTRiASCloneGeometry(V_DISPATCH(&Val)) -> Clone (disp.ppi()));
			THROW_FAILED_HRESULT(WTRiASTransformGeometry(disp) -> TransformInverse (*(CSID *)&Guid, CST));
			if (OBJECTTYPE_Unknown == rgType) {
			// Geometrietyp wird hier festgelegt
			GEOMETRYTYPE rgGeoType = GEOMETRYTYPE_Unknown;

				THROW_FAILED_HRESULT(WTRiASCSGeometryProperties(disp) -> get_Type (&rgGeoType));
				rgType = GEOMETRYTYPEToOBJECTTYPE(rgGeoType);
				THROW_FAILED_HRESULT(pIObj -> put_Type (rgType));
				THROW_FAILED_HRESULT(g_pDBEngine -> GeometryToStorage(rgGeoType, disp, &vVal));

			// Typ des Objektes in seine Objektklasse propagieren
			WTRiASObjectHandleMap Map (g_pDBEngine -> GetObjectsMap());
			WTRiASObjects Objs;
			INT_PTR hObjs = NULL;

				THROW_FAILED_HRESULT(pIObj -> get_ObjectsHandle (&hObjs));
				THROW_FAILED_HRESULT(Map -> GetObject (hObjs, Objs.ppu()));
				THROW_FAILED_HRESULT(Objs -> Classify (pIObj, CLASSIFYMODE_InitObjectType));

			} else {
				THROW_FAILED_HRESULT(g_pDBEngine -> GeometryToStorage(OBJECTTYPEToGEOMETRYTYPE(rgType), disp, &vVal));
			}

			_ASSERTE(OBJECTTYPE_Unknown != rgType);
			THROW_FAILED_HRESULT(Object.PutGeometry ((long)INVALID_HOBJECTS, rgType, OLE2A(bstrName), V_ARRAY(&vVal)));

		} else if (V_VT(&Val) == (VT_ARRAY|VT_UI1)) {
			THROW_FAILED_HRESULT(Object.PutGeometry ((long)INVALID_HOBJECTS, rgType, OLE2A(bstrName), V_ARRAY(&Val)));

		} else 
			_com_issue_error(E_INVALIDARG);

	} COM_CATCH;
	return S_OK;
}

// Kopie der Objekteigenschaft erzeugen
STDMETHODIMP CTRiASSimpleGeoFeature::Clone (ITRiASFeature **ppIFeat)
{
	return E_NOTIMPL;
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASSimpleGeoFeature::OnFinalRelease()
{
	COM_TRY {
	WTRiASFeature BaseFeat;
	WDispatch Parent;
	INT_PTR hGeom = NULL;

		if (SUCCEEDED(m_BaseUnk -> QueryInterface (BaseFeat.ppi()))) {
			BaseFeat -> get_Parent (Parent.ppi());
			BaseFeat -> get_Handle (&hGeom);
		}
			
	// aus Objects-Tabelle entfernen
	WTRiASDatabase DBase;

		if (SUCCEEDED(FindSpecificParent (Parent, DBase.ppi()))) {
		WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbFeatureMap, (IDispatch *)NULL), false);

			_ASSERTE(Map.IsValid());
			if (Map.IsValid() && NULL != hGeom) 
				VERIFY(S_OK == Map -> RemoveObject ((LONG)hGeom, OBJECTMAPMODE_RemoveAllReferences));
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASSimpleFeature
STDMETHODIMP CTRiASSimpleGeoFeature::get_LocalHandle (INT_PTR *pVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASSimpleGeoFeature::InitTarget (VARIANT vName, FEATURETYPE rgType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;

// Initialisierung
	if (!m_fIsInitialized) {
	CComSemaphore<_ThreadModel> Sem (m_lInitData);	// doppeltes Initialisieren verhindern

	// erstmal nur Werte zwischenspeichern
	WTRiASFeature BaseFeat;

		_ASSERTE(m_BaseUnk.IsValid());
		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));

	CComVariant bstrName;

		RETURN_FAILED_HRESULT(bstrName.ChangeType (VT_BSTR, &vName));

	CString str;

		str.Format(IDS_GEOMETRYFEATURE, OLE2A(V_BSTR(&bstrName)));
		RETURN_FAILED_HRESULT(BaseFeat -> put_Name (V_BSTR(&bstrName)));
		RETURN_FAILED_HRESULT(BaseFeat -> put_Description (CComBSTR(str)));

	// Typ der Objekteigenschaft setzen
		RETURN_FAILED_HRESULT(BaseFeat -> put_Type (rgType));

		m_fIsInitialized = true;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSearchObjects
HRESULT CTRiASSimpleGeoFeature::ConsiderSearch (
	BSTR bstrCommand, SAFEARRAY *pParams)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!wcscmp (SEARCHCOMMAND_IntersectsWindow, bstrCommand))
		return S_OK;
	return TRIASDB_S_SEARCH_NOT_SUPPORTED;	// hier wird lediglich die Geometrierecherche unterstützt
}

namespace {
	HRESULT RetrieveSearchParams (
		HPROJECT hPr, ITRiASCSTransform *pICST, SAFEARRAY *pParams, double dWindow[4], BOOL *pfExact)
	{
		COM_TRY {
		CSafeArray sa(VT_VARIANT);

			if (NULL == pParams || !sa.Attach (pParams, true)) 
				return E_INVALIDARG;

		CSafeArrayLock<VARIANT> lock(sa);
		WDispatch clonedRect;

			{
			// Das übergebene Suchrechteck darf nicht verändert werden !!
			CComVariant vRect;
		
				if (FAILED(vRect.ChangeType (VT_DISPATCH, &lock[0])))
					_com_issue_error(E_INVALIDARG);

				THROW_FAILED_HRESULT(WTRiASCloneGeometry(V_DISPATCH(&vRect)) -> Clone (clonedRect.ppi()));
			}

		CCSRectangleGeometry rect (clonedRect);
		GUID Guid;

			_ASSERTE(rect.IsValid());
			THROW_FAILED_HRESULT(::GetGeometryGuid (hPr, 0L, NULL, &Guid));
			THROW_FAILED_HRESULT(WTRiASTransformGeometry(clonedRect) -> TransformInverse (*(CSID *)&Guid, pICST));
			if (FAILED(rect.get_XMin(&dWindow[0])) || FAILED(rect.get_XMax(&dWindow[1])) ||
				FAILED(rect.get_YMin(&dWindow[2])) || FAILED(rect.get_YMax(&dWindow[3])))
			{
				_com_issue_error(E_UNEXPECTED);
			}

		CComVariant vExact;

			if (lock.Size() > 1 && SUCCEEDED(vExact.ChangeType (VT_BOOL, &lock[2]))) 
				*pfExact = V_BOOL(&vExact) ? TRUE : FALSE;
			else
				*pfExact = FALSE;

		} COM_CATCH;
		return S_OK;
	}
} // namespace

/* static */
HRESULT CALLBACK CTRiASSimpleGeoFeature::FindObjectCallBack (INT_PTR lObject, UINT_PTR dwData)
{
	_ASSERTE(0L != dwData);

// Objekt evtl. aus der DatabaseMap holen
CFindObjectCallback *pData = reinterpret_cast<CFindObjectCallback *>(dwData);
WTRiASObject Object;
HRESULT hr = pData -> m_Map -> GetObject (lObject, Object.ppu());

	if (SUCCEEDED(hr))
	{
		RETURN_FAILED_HRESULT(pData -> m_Objs -> _Add (Object, VARIANT_FALSE));
	}
	return S_OK;		// Objekt ist noch nicht (nicht mehr) geladen
}

HRESULT CTRiASSimpleGeoFeature::SearchObjects (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (wcscmp (SEARCHCOMMAND_IntersectsWindow, bstrCommand))
		return E_NOTIMPL;		// not supported search

	USES_CONVERSION;
	COM_TRY {
	// hier benötigte InterfacePointer besorgen
	WTRiASDatabase Parent;
	WTRiASProperties Props;
	HPROJECT hPr = NULL;

		THROW_FAILED_HRESULT(FindSpecificParent(m_BaseUnk, Parent.ppi()));
		THROW_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPr));
		THROW_FAILED_HRESULT(GetProperties (Parent, Props.ppi()));

	WTRiASObjectHandleMap ObjMap (GetProperty (Props, g_cbObjectMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	WTRiASCSTransform CST (GetProperty (Props, g_cbTRiASCSTransform, (IDispatch *)NULL), false);

	// Parameter für die Geometrierecherche aus ParameterFeld herausholen
	double dWindow[4];		// übergebenes Suchfenster
	BOOL fExact = FALSE;

		THROW_FAILED_HRESULT(RetrieveSearchParams (hPr, CST, pParams, dWindow, &fExact));

	// Namen des Geometriefeldes besorgen
	WTRiASFeature BaseFeat;
	CComBSTR bstrFeatName;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseFeat.ppi()));
		THROW_FAILED_HRESULT(BaseFeat -> get_Name (CLEARED(&bstrFeatName)));

	// eigentliche Geometrierecherche durchführen
	WTRiASObjects Objs (pIObjs);
	CFindObjectCallback FindObjectData;

		FindObjectData.m_Map = ObjMap;
		FindObjectData.m_Objs = Objs;
		THROW_FAILED_HRESULT(CNativeObject::EnumObjectsInWindow (hPr, OLE2A(bstrFeatName), dWindow, FindObjectCallBack, (UINT_PTR)&FindObjectData, fExact));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleGeoFeature::ConstraintObjects (ITRiASObjects *pIObjs)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(SUCCEEDED(E_NOTIMPL));
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// IOleObject
STDMETHODIMP CTRiASSimpleGeoFeature::GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
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

// Moniker des zugeordneten Containers liefern
HRESULT CTRiASSimpleGeoFeature::GetContainerMoniker (IMoniker **ppIMk)
{
	COM_TRY {
	WMoniker mk;
	WTRiASConnection Parent;
	WTRiASFeature BaseFeat;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(FindSpecificParent (BaseFeat, Parent.ppi()));
		THROW_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mk.ppi()));
		*ppIMk = mk.detach();

	} COM_CATCH;
	return S_OK;
}

// Den vollständigen Moniker dieses Objektes liefern
HRESULT CTRiASSimpleGeoFeature::GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk)
{
	COM_TRY {
	// Moniker eines Features hat folgende Struktur:
	// MkFeature:Name, den Typ (ClsId) muß sowieso der Container kennen
	WMoniker mk, mkThis, mkItem;
	CComBSTR bstrItem (g_cbMkFeature);		// "!MkFeature:Geometry"

		bstrItem.Append (g_cbColon);
		bstrItem.Append (g_cbGeometry);

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

