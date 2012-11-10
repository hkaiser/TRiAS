// @doc
// @module TRiASSimpleFeatures.cpp | Implementation of the <c CTRiASSimpleFeatures> class

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"

#include <NativePbd.h>
#include <NativeMerkmal.h>
#include <NativeIdent.h>
#include <NativeObject.h>

#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>

#include "GlobalVars.h"
#include "GenObjectMap.h"
#include "TRiASSimpleFeatures.h"

using namespace trias_nativepbd;
using namespace trias_nativeident;
using namespace trias_nativemerkmal;
using namespace trias_nativeobject;

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASSimpleFeatures);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASSimpleFeatures::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASSimpleFeatures, CTRiASSimpleFeatures)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleFeatures

STDMETHODIMP CTRiASSimpleFeatures::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleFeatures,
		&IID_ITRiASFeatures,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASFeaturesCallback

STDMETHODIMP CTRiASSimpleFeatures::get_DefaultType (BSTR *pbstrType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pbstrType)
		return E_POINTER;

CIID Guid (CLSID_TRiASSimpleFeature);			// DefaultType der _Elemente_ !
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

// eine neue Objekteigenschaft soll erzeugt werden
STDMETHODIMP CTRiASSimpleFeatures::OnCreate (VARIANT NameOrHandle, BSTR Type, FEATURETYPE rgType, ITRiASFeature **ppIFeat)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(ppIFeat);

CIID Guid (Type, CIID::INITCIID_InitFromProgId);

	if (!Guid) Guid = CLSID_TRiASSimpleFeature;
	RETURN_FAILED_HRESULT(GetOrCreateObject (NameOrHandle, rgType, &Guid, FEATURELEN_DEFAULT, ppIFeat));
	return S_OK;
}

STDMETHODIMP CTRiASSimpleFeatures::OnChanging(CHANGEDFEATURES rgWhat, VARIANT vNewValue, VARIANT_BOOL *pfDisAllow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == pfDisAllow)
		return E_POINTER;
	*pfDisAllow = VARIANT_FALSE;		// immer zulassen
	return S_OK;
}

// Irgend was wurde modifiziert
STDMETHODIMP CTRiASSimpleFeatures::OnChanged(CHANGEDFEATURES rgWhat, VARIANT vOldValue)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn wir nicht derzeit initialisiert werden
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch(rgWhat) {
	case CHANGEDFEATURES_Name:
		return OnChangedName();

	case CHANGEDFEATURES_Description:
		return OnChangedDescription();

	case CHANGEDFEATURES_Handle:
		return OnChangedHandle();

	default:
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		break;
	}
	return E_INVALIDARG;
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASSimpleFeatures::OnFinalRelease()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Eine Objekteigenschaftsbeschreibung soll gelöscht werden
STDMETHODIMP CTRiASSimpleFeatures::OnDelete (VARIANT vWhich)
{
// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

	if (V_ISI4(&vWhich)) {
	CNativeMerkmal Merkmal (hPr, V_I4(&vWhich));		// evtl. Fehler nicht melden

		RETURN_FAILED_HRESULT(Merkmal.Delete());
	} else
		RETURN_FAILED_HRESULT(E_NOTIMPL);
	return S_OK;
}

HRESULT CTRiASSimpleFeatures::RetrievePbdHandle (HPROJECT *phPrPbd)
{
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle(&hPr))
	if (!::GetRelatedProject (hPr, phPrPbd)) 
		return E_UNEXPECTED;

	return S_OK;
}

HRESULT CTRiASSimpleFeatures::GetOrCreateObject (
	VARIANT NameOrHandle, DWORD dwType, const CLSID *pClsId, long lLength, ITRiASFeature **ppIFeat)
{
// Objekt neu erzeugen/wiederverwenden und zur Collection hinzufügen
WDispatch App;
WDispatch Parent;
WTRiASDatabase DBase;
WTRiASFeatures BaseFeats;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeats.ppi()));

	RETURN_FAILED_HRESULT(BaseFeats -> get_Application (App.ppi()));
	RETURN_FAILED_HRESULT(BaseFeats -> get_Parent(Parent.ppi()));

#if defined(_DEBUG)
WTRiASObjects Objs;

	_ASSERTE(Parent.IsValid());
	_ASSERTE(SUCCEEDED(Parent -> QueryInterface (Objs.ppi()) || Parent -> QueryInterface (DBase.ppi())));		// Parent ist TRiASObjects
#endif // defined(_DEBUG)

// Für TRiAS-Datenbanken werden die Objekteigenschaften nun doch DatenBank-weit erzeugt.
// d.h. Alle Objekte einer DatenBank haben einen identischen Satz von Objekteigenschaften.
	RETURN_FAILED_HRESULT(FindSpecificParent (BaseFeats, DBase.ppi()));

// ZugriffsHandle finden
INT_PTR lMCode = 0L;
CComVariant v;
bool fHasName = false;
#if defined(_DEBUG)
bool fHasLocalHandle = true;		// erstmal zugunsten des Angeklagten entscheiden
#endif // defined(_DEBUG)

	if (VT_BSTR != V_VT(&NameOrHandle) && SUCCEEDED(v.ChangeType (VT_I4, &NameOrHandle)))
		lMCode = V_I4(&v);
	else if (SUCCEEDED(v.ChangeType(VT_BSTR, &NameOrHandle))) {
	// erstmal versuchen, dieses Objekt selbst wiederzufinden
	CComBSTR bstrMk;
	WMoniker mkCont, mk;

	// Mk's von Feats == Mk's von Feat
		if (FEATURETYPE_IsGlobal & dwType) {
		// Parent muß Connection sein, da Objekteigenschaft global zu Datenquelle ist (z.B. __ObjGuid__)
		WTRiASConnection Conn;

			RETURN_FAILED_HRESULT(FindSpecificParent (DBase, Conn.ppi()));
			RETURN_FAILED_HRESULT(MkGetMoniker (Conn, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJREL, mkCont.ppi()));
		} else 
			RETURN_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mkCont.ppi()));

		RETURN_FAILED_HRESULT(CTRiASFeature::GetFeatureMoniker (NULL, V_BSTR(&v), mkCont, OLEWHICHMK_OBJFULL, mk.ppi()));
		RETURN_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&bstrMk)));

	// wenn Objekt noch nicht existiert, dann geht alles seinen Gang und ein neues Handle wird vergeben
		COM_TRY {
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetFeaturesMap());		// throws hr

			Map -> GetObjectHandle (CComVariant(bstrMk), NULL, OBJECTMAPMODE_GetObjectHandle, (INT_PTR *)&lMCode);
#if defined(_DEBUG)
			fHasLocalHandle = false;
#endif // defined(_DEBUG)
		} COM_CATCH;

		fHasName = true;
	} else
		return E_INVALIDARG;

// Feature evtl. aus der Objects-Map holen
WTRiASFeature Feat;
WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbFeatureMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
CInitializeFeature InitFeat (lMCode, dwType, App, Parent);
HRESULT hr = FindInMapOrCreateObject(Map, lMCode, Feat, *pClsId, InitFeat);

	if (S_OK == hr) {	// S_FALSE heißt: Objekt existiert bereits
		RETURN_FAILED_HRESULT(Feat -> put_Handle (lMCode));
		RETURN_FAILED_HRESULT(Feat -> put_Length (lLength));		// etwas willkürlich!
		if (fHasName) 
			RETURN_FAILED_HRESULT(Feat -> put_Name (V_BSTR(&v)));
	} 
#if defined(_DEBUG)
	else if (S_FALSE == hr) {
	// versuchen, zu überprüfen, ob es wirklich das geforderte Objekt ist
	INT_PTR lMCodeDeb = 0L;
	CComBSTR bstrNameDeb;

		if (fHasLocalHandle) {
			RETURN_FAILED_HRESULT(WTRiASSimpleFeature(Feat) -> get_LocalHandle (&lMCodeDeb));
		} else {
			RETURN_FAILED_HRESULT(Feat -> get_Handle (&lMCodeDeb));
		}
		_ASSERTE(lMCode == lMCodeDeb);
		if (fHasName) {
			RETURN_FAILED_HRESULT(Feat -> get_Name (CLEARED(&bstrNameDeb)));
			_ASSERTE(!wcscmp(V_BSTR(&v), bstrNameDeb));
		}
	}
#endif // defined(_DEBUG)
	else if (FAILED(hr)) {
		RETURN_FAILED_HRESULT(hr);
	}

// wenn Feature bereits zu dieser Objektklasse gehört, dann liefert _Add den Wert S_FALSE
	hr = BaseFeats -> _Add (Feat, VARIANT_TRUE);
	if (SUCCEEDED(hr) && NULL != ppIFeat)
		*ppIFeat = Feat.detach();	// evtl. neue Objekteigenschaft liefern
	return hr;
}

/* static */
HRESULT CALLBACK CTRiASSimpleFeatures::EnumFeatureCallBack (INT_PTR lMCode, DWORD dwType, UINT_PTR dwData)
{
	_ASSERTE(0L != dwData);

CEnumFeatureCallback *pData = reinterpret_cast<CEnumFeatureCallback *>(dwData);

// wird jetzt zentral in NativeMerkmal.cpp::InsertEntry gemacht
//	if (CNativePbdMerkmal::PBDFEATURETYPE_Object == (dwType & CNativePbdMerkmal::PBDFEATURETYPE_TypeMask)) 
	{
	HRESULT hr =  pData -> m_pThis -> GetOrCreateObject (CComVariant(lMCode), DATATYPE_FROM_VT(VT_BSTR) | dwType | FEATURETYPE_IsGlobal);	// Objektmerkmal, immer BSTR
		
		return SUCCEEDED(hr) ? S_OK : hr;		// S_FALSE unterdrücken, da sonst Enumeration abgebrochen wird
	}
	return S_OK;
}

STDMETHODIMP CTRiASSimpleFeatures::SetupFeatures(IDispatch *pIParent, SETUPFEATURESMODE rgSetupMode)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	// 'normale Merkmale' hinzufügen
	HPROJECT hPr = NULL;
	CEnumFeatureCallback CallbackData;

		CallbackData.m_pThis = this;

		THROW_FAILED_HRESULT(RetrieveDBHandle (&hPr));

	// das Parentobjekt ist entweder eine Objektmenge oder ein einzelnes Objekt
	WTRiASObjects Objs;
	WTRiASSimpleObject Obj;

		_ASSERTE(NULL != pIParent);
		if (SUCCEEDED(pIParent -> QueryInterface (Objs.ppi()))) {
			THROW_FAILED_HRESULT(CNativeIdent::EnumRelatedMCodes (hPr, EnumFeatureCallBack, reinterpret_cast<UINT_PTR>(&CallbackData)));
		} 
		else if (SUCCEEDED(pIParent -> QueryInterface(Obj.ppi()))) {
		INT_PTR hObj = NULL;

			THROW_FAILED_HRESULT(Obj -> get_LocalHandle (&hObj));

		CNativeObject Object (hPr, hObj);

			if (!Object) 
				return E_UNEXPECTED;
			THROW_FAILED_HRESULT(Object.EnumRelatedMCodes (EnumFeatureCallBack, reinterpret_cast<UINT_PTR>(&CallbackData)));
		} 
		else {
			_ASSERTE(SUCCEEDED(E_UNEXPECTED));
			return E_UNEXPECTED;
		}

	// ObjGuid als PrimärAttribut hinzufügen
	FEATURETYPE rgType = (FEATURETYPE)(DATATYPE_FROM_VT(VT_BSTR)|CNativePbdMerkmal::PBDFEATURETYPE_Object|FEATURETYPE_IsPrimaryFeature|FEATURETYPE_IsGlobal);

		THROW_FAILED_HRESULT(GetOrCreateObject(CComVariant(g_cbObjGuid), rgType, &CLSID_TRiASGuidFeature, FEATURELEN_GUID));

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CTRiASSimpleFeatures::OnChangedName()
{
	return S_OK;
}

HRESULT CTRiASSimpleFeatures::OnChangedDescription()
{
	return S_OK;
}

HRESULT CTRiASSimpleFeatures::OnChangedHandle()
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSimpleFeatures
STDMETHODIMP CTRiASSimpleFeatures::get_Feature (INT_PTR lLocalHandle, ITRiASFeature **ppIFeat)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

bool fFound = false;

	COM_TRY {
	WTRiASFeatures BaseFeats;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeats.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(BaseFeats -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(VT_DISPATCH == V_VT(&v));

		WTRiASSimpleFeature SimpleFeat;

			if (FAILED(V_UNKNOWN(&v) -> QueryInterface(SimpleFeat.ppi())))
				continue;		// funktioniert lediglich für TRiAS-Objekteigenschaften

		INT_PTR lHandle = NULL;

			if (SUCCEEDED(SimpleFeat -> get_LocalHandle (&lHandle)) && lHandle == lLocalHandle) {
			// gefunden (get_LocalHandle kann E_NOTIMPL liefern)
			WTRiASFeature Feat (SimpleFeat);

				*ppIFeat = Feat.detach();
				fFound = true;
				break;
			}
		}

	} COM_CATCH;
	return fFound ? S_OK : TRIASDB_E_UNKNOWN_FEATURE;
}

