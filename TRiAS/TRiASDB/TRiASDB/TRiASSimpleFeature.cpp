// @doc
// @module TRiASSimpleFeature.cpp | Implementation of the <c CTRiASSimpleFeature> class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>
#include <Com/VariantHelpers.h>
#include <Com/SafeArray.h>
#include <Com/ComBool.h>

#include <NativeObject.h>
#include <NativeMerkmal.h>
#include <UniqueHeader.h>
#include <errinst.hxx>

#include "Strings.h"
#include "Wrapper.h"
#include "TRiASDBGuids.h"

#include "TRiASObjects.h"
#include "TRiASFeatures.h"
#include "TRiASSimpleFeature.h"

using namespace trias_nativemerkmal;
using namespace trias_nativeobject;

#import "tlb/Helper.tlb" \
	raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASSimpleFeature);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASSimpleFeature::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASSimpleFeature, CTRiASSimpleFeature)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ParseStringPairs);		// WParseStringPairs

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleFeature

STDMETHODIMP CTRiASSimpleFeature::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleFeature,
		&IID_ITRiASFeature,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CTRiASSimpleFeature::FinalRelease (void)
{
	COM_TRY {
	// aus Objects-Tabelle entfernen
		if (0L != m_lMCode) {
		WTRiASDatabase Parent;

			if (SUCCEEDED(FindSpecificParent (m_BaseUnk, Parent.ppi()))) {
			WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbFeatureMap, (IDispatch *)NULL), false);

//				_ASSERTE(Map.IsValid());	// kann beim Schließen der Database vorkommen
				if (Map.IsValid()) 
					VERIFY(S_OK == Map -> RemoveObject (m_lMCode, OBJECTMAPMODE_RemoveThisReference));
			}
			m_lMCode = 0L;
		}

	// sonstige Aufräumarbeiten
		m_BaseUnk.Assign(NULL);
		m_hPr = NULL;

	} COM_CATCH_IGNORE;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureCallback
STDMETHODIMP CTRiASSimpleFeature::get_DefaultType (BSTR *pbstrType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pbstrType)
		return E_POINTER;

CIID Guid (GetObjectCLSID());
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASSimpleFeature::SetupFeature (SETUPFEATUREMODE rgWhat)
{
	return S_OK;
}

STDMETHODIMP CTRiASSimpleFeature::OnChanging(CHANGEDFEATURE rgWhat, VARIANT vNewValue, VARIANT_BOOL *pfDisAllow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == pfDisAllow)
		return E_POINTER;

	*pfDisAllow = VARIANT_FALSE;		// immer zulassen
	return S_OK;
}

STDMETHODIMP CTRiASSimpleFeature::OnChanged(CHANGEDFEATURE rgWhat, VARIANT vOldValue)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn wir nicht derzeit initialisiert werden
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	switch (rgWhat) {
	case CHANGEDFEATURE_Name:
		_ASSERTE(V_ISBSTR(&vOldValue));
		return OnChangedName(V_BSTR(&vOldValue));

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

	case CHANGEDFEATURE_Length:
		return S_OK;	// no problem at all
		
	default:
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		break;
	}
	return E_INVALIDARG;
}

HRESULT CTRiASSimpleFeature::OnChangedName(BSTR bstrOldName)
{
	USES_CONVERSION;

// Namen vom Bezugsobjekt besorgen
CComBSTR bstrName;
WTRiASFeature BaseFeat;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
	RETURN_FAILED_HRESULT(BaseFeat -> get_Name(CLEARED(&bstrName)))

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// ggf. MCode initialisieren
	if (0 == m_lMCode)
		BaseFeat -> get_Handle ((INT_PTR *)&m_lMCode);

WTRiASDatabase DBase;
CComBool fRW;

	RETURN_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, DBase.ppi()));
    RETURN_FAILED_HRESULT(DBase->get_Updatable(&fRW));

    if (fRW) {
    // neuen Wert in GeoDB/Pbd schreiben
    CNativeMerkmal Merkmal (hPr, m_lMCode);		// evtl. Fehler nicht melden

	    RETURN_FAILED_HRESULT(Merkmal.SetName(OLE2A(bstrName)));
	    RETURN_FAILED_HRESULT(SetPropertyBy (WTRiASPropertyBase(BaseFeat), g_cbNameIsDefault, VARIANT_FALSE, true, LOCALE_ENGLISH));
    }

// das Feature in der globalen Features-collection umhängen
WTRiASFeatures Feats (GetPropertyFrom (DBase, g_cbSimpleFeatures, (IDispatch *)NULL), false);
CTRiASFeatures *pFeats = NULL;

	RETURN_FAILED_HRESULT(QueryImplementation(Feats, &pFeats));
	RETURN_FAILED_HRESULT(pFeats -> RemoveFeature(bstrOldName, BaseFeat));
	RETURN_FAILED_HRESULT(pFeats -> _Add (BaseFeat, VARIANT_FALSE));

	return S_OK;
}

HRESULT CTRiASSimpleFeature::OnChangedDescription()
{
	USES_CONVERSION;

// Beschreibung vom Bezugsobjekt besorgen
CComBSTR bstrName;
WTRiASFeature BaseFeat;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
	RETURN_FAILED_HRESULT(BaseFeat -> get_Name(CLEARED(&bstrName)))

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// ggf. MCode initialisieren
	if (0 == m_lMCode)
		BaseFeat -> get_Handle ((INT_PTR *)&m_lMCode);

WTRiASDatabase DBase;
CComBool fRW;

	RETURN_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, DBase.ppi()));
    RETURN_FAILED_HRESULT(DBase->get_Updatable(&fRW));

    if (fRW) {
    // neuen Wert in GeoDB/Pbd schreiben
    CNativeMerkmal Merkmal (hPr, m_lMCode);		// evtl. Fehler nicht melden

	    RETURN_FAILED_HRESULT(Merkmal.SetDescription(OLE2A(bstrName)));
    }
    return S_OK;
}

HRESULT CTRiASSimpleFeature::OnChangedHandle()
{
	return S_OK;
}

HRESULT CTRiASSimpleFeature::OnChangedType()
{
// Beschreibung vom Bezugsobjekt besorgen
FEATURETYPE rgType = FEATURETYPE_Unknown;
WTRiASFeature BaseFeat;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
	RETURN_FAILED_HRESULT(BaseFeat -> get_Type(&rgType))

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// ggf. MCode initialisieren
	if (0 == m_lMCode)
		BaseFeat -> get_Handle ((INT_PTR *)&m_lMCode);

WTRiASDatabase DBase;
CComBool fRW;

	RETURN_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, DBase.ppi()));
    RETURN_FAILED_HRESULT(DBase->get_Updatable(&fRW));

    if (fRW) {
    // neuen Wert in GeoDB/Pbd schreiben
    CNativeMerkmal Merkmal (hPr, m_lMCode);		// evtl. Fehler nicht melden

	    RETURN_FAILED_HRESULT(Merkmal.SetTyp (rgType & FEATURETYPE_TypeMask));
	    RETURN_FAILED_HRESULT(Merkmal.SetReadOnly ((rgType & FEATURETYPE_ReadOnly) ? TRUE : FALSE));
	    RETURN_FAILED_HRESULT(Merkmal.SetSystem ((rgType & FEATURETYPE_System) ? TRUE : FALSE));
    }
	return S_OK;
}

HRESULT CTRiASSimpleFeature::OnChangedROMode()
{
// Beschreibung vom Bezugsobjekt besorgen
VARIANT_BOOL fUpdatable = VARIANT_FALSE;
WTRiASFeature BaseFeat;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
	RETURN_FAILED_HRESULT(BaseFeat -> get_Updatable(&fUpdatable))

// Projekthandle vom Parent erfragen
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

// ggf. MCode initialisieren
	if (0 == m_lMCode)
		BaseFeat -> get_Handle ((INT_PTR *)&m_lMCode);

WTRiASDatabase DBase;
CComBool fRW;

	RETURN_FAILED_HRESULT(FindSpecificParent (m_BaseUnk, DBase.ppi()));
    RETURN_FAILED_HRESULT(DBase->get_Updatable(&fRW));

    if (fRW) {
    // neuen Wert in GeoDB/Pbd schreiben
    CNativeMerkmal Merkmal (hPr, m_lMCode);		// evtl. Fehler nicht melden

	    RETURN_FAILED_HRESULT(Merkmal.SetReadOnly (fUpdatable ? FALSE : TRUE));
    }
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Eval: Das, worum es eigentlich geht ...
STDMETHODIMP CTRiASSimpleFeature::Eval(ITRiASObject *pIObj, VARIANT *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

HRESULT hr = S_OK;

	COM_TRY {
	// Projekthandle vom Parent erfragen
	HPROJECT hPrFeat = NULL;

		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPrFeat));

	WTRiASSimpleObject Obj (pIObj);		// nur SimpleObjects bearbeiten
	WTRiASDatabase Parent;
	HPROJECT hPrObj = NULL;

		THROW_FAILED_HRESULT(FindSpecificParent(pIObj, Parent.ppi()));
		THROW_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPrObj));
		if (hPrObj != hPrFeat) {
			_ASSERTE(hPrObj == hPrFeat);
			return E_UNEXPECTED;	// TRiAS-Merkmale dürfen nur für TRiAS-Objekte berechnet werden
		}

	// Objektnummer abfragen
	INT_PTR lONr = 0L;

		THROW_FAILED_HRESULT(Obj -> get_LocalHandle(&lONr));

	// Merkmal lesen
	CNativeObject Object (hPrObj, lONr);
	os_string str;

		hr = Object.GetTextMerkmal (m_lMCode, str);		// wenn Merkmal existiert, dann Wert liefern
		if (SUCCEEDED(hr)) {
		CComVariant var (str.c_str());

			THROW_FAILED_HRESULT(var.Detach (pVal));
		} 

	} COM_CATCH;

	return hr;
}

STDMETHODIMP CTRiASSimpleFeature::EvalEx(ITRiASObject *pIObj, SAFEARRAY **ppConstraints, VARIANT *pVal)
{
	return Eval (pIObj, pVal);		// ignore constraints	
}

STDMETHODIMP CTRiASSimpleFeature::Update(ITRiASObject *pIObj, VARIANT Val)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;

HRESULT hr = S_OK;

	COM_TRY {
	// Projekthandle vom Parent erfragen
	HPROJECT hPrFeat = NULL;

		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPrFeat));

	WTRiASSimpleObject Obj (pIObj);		// nur SimpleObjects bearbeiten
	WTRiASDatabase Parent;
	HPROJECT hPrObj = NULL;

		THROW_FAILED_HRESULT(FindSpecificParent(pIObj, Parent.ppi()));
		THROW_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPrObj));

		if (hPrObj != hPrFeat) {
			_ASSERTE(hPrObj == hPrFeat);
			return E_UNEXPECTED;	// TRiAS-Merkmale dürfen nur für TRiAS-Objekte berechnet werden
		}

	// Objektnummer abfragen
	INT_PTR lONr = 0L;

		THROW_FAILED_HRESULT(Obj -> get_LocalHandle(&lONr));

    CComBool fRW;

        RETURN_FAILED_HRESULT(Parent->get_Updatable(&fRW));
        if (fRW) {
	    // Merkmal schreiben
	    CNativeObject Object (hPrObj, lONr);
	    CComVariant vNewVal;

		    if (!V_ISNULL(&Val) && SUCCEEDED(vNewVal.ChangeType (VT_BSTR, &Val)))
			    hr = Object.PutTextMerkmal (m_lMCode, OLE2A(V_BSTR(&vNewVal)));
		    else
			    hr = Object.DeleteTextMerkmal (m_lMCode);
        }
        		
	} COM_CATCH;
	return hr;
}

// Kopie der Objekteigenschaft erzeugen
STDMETHODIMP CTRiASSimpleFeature::Clone (ITRiASFeature **ppIFeat)
{
	return E_NOTIMPL;
}

// Objekt wird logisch freigegeben
STDMETHODIMP CTRiASSimpleFeature::OnFinalRelease()
{
	COM_TRY {
	// aus Features-Tabelle entfernen
		if (0 != m_lMCode) {
		WTRiASDatabase Parent;

			if (SUCCEEDED(FindSpecificParent (m_BaseUnk, Parent.ppi()))) {
			WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbFeatureMap, (IDispatch *)NULL), false);

				_ASSERTE(Map.IsValid());
				if (Map.IsValid()) 
					VERIFY(S_OK == Map -> RemoveObject (m_lMCode, OBJECTMAPMODE_RemoveThisReference));
			}
			m_lMCode = 0L;
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASSimpleFeature
STDMETHODIMP CTRiASSimpleFeature::get_LocalHandle (INT_PTR *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(pVal);

	*pVal = m_lMCode;
	return S_OK;
}

STDMETHODIMP CTRiASSimpleFeature::InitTarget (VARIANT vMCode, FEATURETYPE rgType)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CComSemaphore<_ThreadModel> Sem (m_lInitData);	// doppeltes Initialisieren verhindern
CComVariant vArg;

	RETURN_FAILED_HRESULT(vArg.ChangeType(VT_I4, &vMCode));

// Initialisierung
	_ASSERTE(0 == m_lMCode || m_lMCode == V_I4(&vArg));		// nur einmal initialisieren
	if (0 == m_lMCode) {
	// erste Initialisiereung
		m_lMCode = V_I4(&vArg);
		if (0 == m_lMCode) {
		HPROJECT hPr = NULL;

			THROW_FAILED_HRESULT(RetrieveDBHandle(&hPr));
			m_lMCode = CUniqueHeader(hPr).GetNextUniqueCode(CUniqueHeader::UNIQUETYPE_MCODE);
		}
		_ASSERTE(0 != m_lMCode);

	// erstmal nur Werte zwischenspeichern
	WTRiASFeature BaseFeat;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));

	// und KurzText/Langtext aus Pbd besorgen
	HPROJECT hPr = NULL;

		RETURN_FAILED_HRESULT(RetrieveDBHandle (&hPr));

	CNativeMerkmal Merkmal (hPr, m_lMCode);		// evtl. Fehler nicht melden
	HRESULT hr = S_OK;
	char cbBuffer[_MAX_PATH];

	// Kurztext aus GeoDB lesen
		cbBuffer[0] = '\0';		// ausnullen
		RETURN_FAILED_HRESULT(hr = Merkmal.GetName(cbBuffer, sizeof(cbBuffer)));
		RETURN_FAILED_HRESULT(BaseFeat -> put_Name (CComBSTR(cbBuffer)));
		if (S_FALSE == hr) {
		// der Name der Objekteigenschaft ist lediglich temporär generiert
			SetPropertyBy (WTRiASPropertyBase(BaseFeat), g_cbNameIsDefault, VARIANT_TRUE, true, LOCALE_ENGLISH);
		}

	// Langtext aus GeoDB lesen
		cbBuffer[0] = '\0';		// ausnullen
		if (S_OK == Merkmal.GetDescription(cbBuffer, sizeof(cbBuffer)))
		{
			RETURN_FAILED_HRESULT(BaseFeat -> put_Description (CComBSTR(cbBuffer)));
		}

	// Typ der Objekteigenschaft setzen, TRiAS besitzt nur Textmerkmale
		rgType = (FEATURETYPE)((rgType & ~FEATURETYPE_DataTypeMask) | DATATYPE_FROM_VT(VT_BSTR));
		RETURN_FAILED_HRESULT(BaseFeat -> put_Type (rgType));

	// Handle-Voreinstellungen setzen
		RETURN_FAILED_HRESULT(BaseFeat -> put_Handle(m_lMCode));
	}
	return S_OK;
}

HRESULT CTRiASSimpleFeature::RetrievePbdHandle (HPROJECT *phPrPbd)
{
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(RetrieveDBHandle(&hPr))
	if (!::GetRelatedProject (hPr, phPrPbd)) 
		return E_UNEXPECTED;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSearchObjects

STDMETHODIMP CTRiASSimpleFeature::ConsiderSearch (BSTR bstrCommand, SAFEARRAY *pParams)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

HRESULT hr = TRIASDB_S_SEARCH_NOT_RECOMMENDED;	// nicht zu empfehlen
int iMode = ModeFromSearchCommand(bstrCommand);

	if (SMNegateResult & iMode)
		return TRIASDB_S_SEARCH_NOT_SUPPORTED;		// negate ist nicht unterstützt

	switch (iMode) {
	case SMExactMatch:
	case SMSubStringStartMatch:
	case SMExistanceOnly:
		hr = S_OK;		// geht schnell
		break;

	case SMInexactMatch:
	case SMSubstringMatch:
		break;			// einzelner Test

	default:
	case SMRegularExpression:
	case SMSubRegularExpression:
		hr = TRIASDB_S_SEARCH_NOT_SUPPORTED;	// not impl (yet)
		break;
	}
	return hr;
}

/* static */
HRESULT CALLBACK CTRiASSimpleFeature::FindObjectCallBack (INT_PTR lObject, UINT_PTR dwData)
{
	_ASSERTE(0L != dwData);

CFindObjectCallback *pData = reinterpret_cast<CFindObjectCallback *>(dwData);

// sicherstellen, daß in zugehöriger Objektklasse alle Objekte geladen sind
CNativeObject Obj (pData -> m_hPr, lObject);
INT_PTR lIdent = 0;

	RETURN_FAILED_HRESULT(Obj.GetIdent (&lIdent));

WTRiASObjects Objs;
CTRiASObjects *pObjs = NULL;

	RETURN_FAILED_HRESULT(pData -> m_ObjsMap -> GetObject (lIdent, Objs.ppu()));
	RETURN_FAILED_HRESULT(QueryImplementation (Objs, &pObjs));		// no addref !
	RETURN_FAILED_HRESULT(pObjs -> EnsureObjectsLoaded());

// Objekt evtl. aus der DatabaseMap holen
WTRiASObject Object;
HRESULT hr = pData -> m_ObjMap -> GetObject (lObject, Object.ppu());

	if (SUCCEEDED(hr))
	{
		RETURN_FAILED_HRESULT(pData -> m_Objs -> _Add (Object, VARIANT_TRUE));
	}
	return S_OK;		// Objekt ist noch nicht (nicht mehr) geladen
}

STDMETHODIMP CTRiASSimpleFeature::SearchObjects (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (S_OK != ConsiderSearch(bstrCommand, pParams))
		return TRIASDB_S_SEARCH_NOT_SUPPORTED;		// not supported search

	USES_CONVERSION;

// hier benötigte InterfacePointer besorgen
WTRiASDatabase Parent;
HPROJECT hPr = NULL;

	RETURN_FAILED_HRESULT(FindSpecificParent(m_BaseUnk, Parent.ppi()));
	RETURN_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)&hPr));

WTRiASObjectHandleMap ObjMap (GetPropertyFrom (Parent, g_cbObjectMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
WTRiASObjectHandleMap ObjsMap (GetPropertyFrom (Parent, g_cbObjectsMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab

// Parameter für die Recherche aus ParameterFeld herausholen
CComBSTR bstrPattern;	// SuchString
int iMode = 0;			// SuchMode

	RETURN_FAILED_HRESULT(RetrieveSearchParams (bstrCommand, pParams, CLEARED(&bstrPattern), &iMode));

// eigentliche Recherche durchführen
WTRiASObjects Objs (pIObjs);
CFindObjectCallback FindObjectData;

	FindObjectData.m_hPr = hPr;
	FindObjectData.m_ObjMap = ObjMap;
	FindObjectData.m_ObjsMap = ObjsMap;
	FindObjectData.m_Objs = Objs;

ErrInstall EI (WC_NOTFOUND);
HRESULT hr = CNativeObject::FindTextMerkmal (hPr, m_lMCode, OLE2A(bstrPattern), iMode, FindObjectCallBack, (UINT_PTR)&FindObjectData);

	if (HRESULT_FROM_ERRCODE(WC_NOTFOUND) == hr)
		return TRIASDB_I_NO_OBJECTS_FOUND;		// nichts gefunden
	return hr;
}

STDMETHODIMP CTRiASSimpleFeature::ConstraintObjects (ITRiASObjects *pObjs)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(SUCCEEDED(E_NOTIMPL));
	return E_NOTIMPL;
}

