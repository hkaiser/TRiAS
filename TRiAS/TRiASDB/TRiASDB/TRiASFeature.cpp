// @doc
// @module TRiASFeature.cpp | Implementation of CTRiASFeature

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Com/ComBool.h>

#include "Wrapper.h"
#include "Strings.h"

#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>
#include <ChangeValueHelper.h>

#include "TRiASDBEngine.h"
#include "TRiASProperty.h"
#include "TRiASFeature.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class if standalone and if aggregated
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASFeature);
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST_AGGR(CTRiASFeature);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASFeature::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASFeature, CTRiASFeature)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASFeature, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASFeatureEvents);		// WTRiASFeatureEvents
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(BindCtx);					// WBindCtx
DefineSmartInterface(OleClientSite);			// WOleClientSite

/////////////////////////////////////////////////////////////////////////////
// CTRiASFeature

STDMETHODIMP CTRiASFeature::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASFeature,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CTRiASFeature::FinalRelease()
{
// evtl. aus HandleTabellen entfernen
	if (NULL != m_hFeature) {
		COM_TRY {
		// aus globaler Tabelle entfernen
		WTRiASObjectHandleMap Map (g_pDBEngine -> GetFeaturesMap());		// throws hr

			VERIFY(S_OK == Map -> RemoveObject ((LONG)m_hFeature, OBJECTMAPMODE_RemoveThisReference));
			m_hFeature = NULL;

		} COM_CATCH_IGNORE;
	}
	_ASSERTE(NULL == m_hFeature);

// sonstige Aufr‰umarbeiten
	FreePropertiesCollection();
	ReleasePropertySupportObjects();	// SupportObjekte freigeben

	m_Parent = NULL;
	m_Application = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASFeature::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Application");

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

#if defined(_DEBUG)
// Parent muﬂ entweder TRiASObject oder TRiASObjects sein
WUnknown Unk;

	_ASSERTE(NULL == newVal ||
		   SUCCEEDED(newVal -> QueryInterface(IID_ITRiASObjects, Unk.ppv())) || 
		   SUCCEEDED(newVal -> QueryInterface(IID_ITRiASObject, Unk.ppv())) ||
		   SUCCEEDED(newVal -> QueryInterface(IID_ITRiASDatabase, Unk.ppv())));
#endif // _DEBUG

// das Nullsetzen des Parent wird als Signal zum Freigeben gewertet
// evtl. alle SubObjekte von ihrem Bezug abh‰ngen
	if (NULL == newVal) {
	// evtl. abh‰ngiges Objekt benachrichtigen
		if (m_pICallback) 
			m_pICallback -> OnFinalRelease();

		FinalRelease();
	}
	m_Parent = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Description");

// Wenn keine BeschreibungsInfo gesetzt ist, dann liefert diese Funktion den Namen
	if (!m_bstrDesc || 0 == m_bstrDesc.Length()) 
		return E_FAIL;

// Beschreibungsinfo ist gesetzt
CComBSTR bstr (m_bstrDesc);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Description(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	CComBSTR bstr(newVal);
	CChangeValueHelper<CComBSTR> Helper (m_bstrDesc, bstr);

		if (!Helper) {
		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			THROW_FAILED_HRESULT(Fire_ModifyingFeature (GetDispatch(), &fModify));
			if (fModify)
				return S_FALSE;		// nicht umbenennen

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDFEATURE_Description, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchf¸hren
			}
			THROW_FAILED_HRESULT(Fire_FeatureToModify (GetDispatch()));

			THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen

			if (m_pICallback && !fModify && S_OK == hr)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDFEATURE_Description, Helper.GetOldValue()));

			THROW_FAILED_HRESULT(Fire_FeatureModified(m_bstrName));

			m_fIsDirty = true;
			Helper.SetValid();
		}

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASFeature::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Name");

// Beschreibungsinfo ist gesetzt
CComBSTR bstr (m_bstrName);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	CComBSTR bstr(newVal);
	CChangeValueHelper<CComBSTR> Helper (m_bstrName, bstr);

		if (bstr.Length() > 0 && !Helper) {
		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			THROW_FAILED_HRESULT(Fire_ModifyingFeature (GetDispatch(), &fModify));
			if (fModify)
				return S_FALSE;		// nicht umbenennen

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDFEATURE_Name, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchf¸hren
			}
			THROW_FAILED_HRESULT(Fire_FeatureToModify (GetDispatch()));

			THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen
			if (m_pICallback && !fModify && S_OK == hr)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDFEATURE_Name, Helper.GetOldValue()));

			THROW_FAILED_HRESULT(Fire_FeatureModified(m_bstrName));

			m_fIsDirty = true;
			Helper.SetValid();
		}

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASFeature::get_Handle (INT_PTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Handle");

	if (NULL == m_hFeature) 
		EnsureFeatureHandle (OBJECTMAPMODE_CreateObjectHandle);
	*pVal = (LONG)m_hFeature;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Handle (INT_PTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (NULL == m_hFeature || m_hFeature != (HFEATURE)newVal) {
		EnsureFeatureHandle (OBJECTMAPMODE(OBJECTMAPMODE_CreateObjectHandle|OBJECTMAPMODE_UsePredefinedHandle), (HFEATURE)newVal);
		return S_OK;
	}
	return S_FALSE;		// Zugriffsnummer wurde bereits vergeben
}

HRESULT CTRiASFeature::EnsureFeatureHandle (OBJECTMAPMODE rgMode, HFEATURE hFeatNew)
{
// erstes Mal benˆtigt
	COM_TRY {
	CChangeValueHelper<INT_PTR, HFEATURE> Helper (m_hFeature, hFeatNew);

		if (!(rgMode & OBJECTMAPMODE_UsePredefinedHandle) || !Helper) {
		// Moniker-DisplayName generieren
		CComBSTR bstrName;

			if (FAILED(GetMkName (CLEARED(&bstrName), rgMode))) {
				bstrName = g_cbMkFeature;
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
				hr = m_pICallback -> OnChanging (CHANGEDFEATURE_Handle, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchf¸hren
			}

		WTRiASObjectHandleMap Map (g_pDBEngine -> GetFeaturesMap());		// throws hr
		INT_PTR hFeature = Helper.NewValue();

			_ASSERTE(sizeof(INT_PTR) == sizeof(HFEATURE));
			THROW_FAILED_HRESULT(Map -> GetObjectHandle (CComVariant(bstrName), GetUnknown(), rgMode, &hFeature));
			THROW_FAILED_HRESULT(Helper.Assign (hFeature));

			if (m_pICallback && !fModify && S_OK == hr) {
			HRESULT hr = m_pICallback -> OnChanged (CHANGEDFEATURE_Handle, Helper.GetOldValue());

				if (FAILED(hr)) {
					Map -> RemoveObject ((LONG)hFeature, OBJECTMAPMODE_RemoveAllReferences);		// Fehler nicht fatal
					THROW_FAILED_HRESULT(hr);
				}
			}
			m_fIsDirty = true;
			Helper.SetValid();
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::putref_FeatureCallback (ITRiASFeatureCallback *pICB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pICallback = pICB;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::get_Type(FEATURETYPE * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Type");

	*pVal = m_rgType;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Type(FEATURETYPE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	CChangeValueHelper<FEATURETYPE> Helper (m_rgType, newVal);

		if (!Helper) {
		// Zuweisung ist notwendig
		CComBool fModify;
		HRESULT hr = S_OK;

			THROW_FAILED_HRESULT(Fire_ModifyingFeature (GetDispatch(), &fModify));
			if (fModify)
				return S_FALSE;		// Typ nicht modifizieren

			if (m_pICallback) {
				hr = m_pICallback -> OnChanging (CHANGEDFEATURE_Type, Helper.GetNewValue(), &fModify);
				if (FAILED(hr)) {
					if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
						return hr;						// Fehler
				} else if (fModify) 
					return S_FALSE;					// Aktion nicht durchf¸hren
			}
			THROW_FAILED_HRESULT(Fire_FeatureToModify (GetDispatch()));

			THROW_FAILED_HRESULT(Helper.Assign());		// hier zuweisen

			if (m_pICallback && !fModify && S_OK == hr)
				THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDFEATURE_Type, Helper.GetOldValue()));

			THROW_FAILED_HRESULT(Fire_FeatureModified(m_bstrName));

			m_fIsDirty = true;
			Helper.SetValid();
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::get_Updatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Type");

	*pVal = (m_rgType & FEATURETYPE_ReadOnly) ? VARIANT_FALSE : VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Updatable(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	VARIANT_BOOL fModify = VARIANT_FALSE;
	VARIANT_BOOL fOldVal = (m_rgType & FEATURETYPE_ReadOnly) ? VARIANT_TRUE : VARIANT_FALSE;

		if (m_pICallback) {
		HRESULT hr = m_pICallback -> OnChanging (CHANGEDFEATURE_ROMode, CComVariant(newVal), &fModify);

			if (FAILED(hr)) {
				if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
					return hr;					// Fehler
			} else if (VARIANT_TRUE == fModify) 
				return S_FALSE;					// Aktion nicht durchf¸hren
		}

		m_rgType = (FEATURETYPE)(m_rgType & ~FEATURETYPE_ReadOnly);
		if (!newVal)
			m_rgType = (FEATURETYPE)(m_rgType | FEATURETYPE_ReadOnly);

		if (m_pICallback && !fModify)
			THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDFEATURE_ROMode, CComVariant(fOldVal)));

		m_fIsDirty = true;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::get_Length(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::get_Length");

	*pVal = m_lLength;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::put_Length(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	VARIANT_BOOL fModify = VARIANT_FALSE;
	long fOldVal = m_lLength;

		if (m_pICallback) {
		HRESULT hr = m_pICallback -> OnChanging (CHANGEDFEATURE_Length, CComVariant(newVal), &fModify);

			if (FAILED(hr)) {
				if(TRIASDB_E_OBJECTSNOTUPDATABLE != hr) 
					return hr;						// Fehler
			} else if (VARIANT_TRUE == fModify) 
				return S_FALSE;						// Aktion nicht durchf¸hren
		}

		m_lLength = newVal;
		if (m_pICallback && !fModify)
			THROW_FAILED_HRESULT(m_pICallback -> OnChanged (CHANGEDFEATURE_Length, CComVariant(fOldVal)));

		m_fIsDirty = true;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Methoden

STDMETHODIMP CTRiASFeature::Eval(ITRiASObject *pIObj, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObj || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::Eval");
	if (NULL == m_pICallback)
		return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASFeature::Eval");

HRESULT hr = m_pICallback -> Eval (pIObj, pVal);

	if (FAILED(hr)) 
		return E_FAIL;		// Objekteigenschaft exitiert nicht
	return hr;
}

STDMETHODIMP CTRiASFeature::EvalEx(ITRiASObject *pIObj, SAFEARRAY **ppConstraints, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObj || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::Eval");
	if (NULL == m_pICallback)
		return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASFeature::Eval");

	return m_pICallback -> EvalEx (pIObj, ppConstraints, pVal);
}

STDMETHODIMP CTRiASFeature::Update(ITRiASObject *pIObj, VARIANT Val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObj)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::Update");
	if (NULL == m_pICallback)
		return REPORT_DBERROR_ROUT(E_UNEXPECTED, "CTRiASFeature::Update");

	RETURN_FAILED_HRESULT(m_pICallback -> Update (pIObj, Val));
	RETURN_FAILED_HRESULT(pIObj -> put_Features (NULL));		// Features bei Bedarf neu einlesen
	return S_OK;
}

// Kopie der Objekteigenschaft erzeugen
STDMETHODIMP CTRiASFeature::Clone (ITRiASFeature **ppIFeat)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// liefert vollst‰ndigen DisplayName dieses Objektes
HRESULT CTRiASFeature::GetMkName (BSTR *pbstrMkName, OBJECTMAPMODE rgMode)
{
	COM_TRY {
	// dem aggregierenden Objekt die Chance geben, den Moniker zu berechnen
	WMoniker mk;

		THROW_FAILED_HRESULT(MkGetMoniker (GetControllingUnknown(), OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
		THROW_FAILED_HRESULT(MkGetDisplayName (mk, pbstrMkName));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Den vollst‰ndigen Moniker eines Features liefern (statische Funktion)
/* static */
HRESULT CTRiASFeature::GetFeatureMoniker (
	INT_PTR hFeature, BSTR bstrName, IMoniker *pIContMk,
	DWORD dwWhich, IMoniker **ppIMk, OBJECTMAPMODE rgMode)
{
// Moniker eines Features hat folgende Struktur:
// MkFeature:Name, den Typ (ClsId) muﬂ sowieso der Container kennen
WMoniker mk, mkThis, mkItem;
CComBSTR bstrItem (g_cbMkFeature);		// "!MkFeature:<Feature Name>"

	bstrItem.Append (g_cbColon);
	if ((OBJECTMAPMODE_UsePredefinedHandle & rgMode) && NULL != hFeature) {
	// ggf. Moniker durch Handle eindeutig machen
	wchar_t cbBuffer[64];

		_ultow (hFeature, cbBuffer, 16);
		if (wcslen (cbBuffer) > 0) {
			bstrItem.Append (g_cbLBracket);
			bstrItem.Append (cbBuffer);
			bstrItem.Append (g_cbRBracket);
			bstrItem.Append (g_cbColon);
		}
	}
	bstrItem.Append (bstrName);
	if (!bstrItem)
		return E_OUTOFMEMORY;

	switch (dwWhich) {
	case OLEWHICHMK_OBJREL:
		{
			RETURN_FAILED_HRESULT(::CreateItemMoniker(g_cbMkDel, bstrItem, mkThis.ppi()));
			*ppIMk = mkThis.detach();
		}
		break;

	case OLEWHICHMK_OBJFULL:
		{
			_ASSERTE(NULL != pIContMk);
			RETURN_FAILED_HRESULT(::CreateItemMoniker(g_cbMkDel, bstrItem, mkThis.ppi()));
			RETURN_FAILED_HRESULT(pIContMk -> ComposeWith (mkThis, false, mkItem.ppi()));
			*ppIMk = mkItem.detach();
		}
		break;

	default:
	case OLEWHICHMK_CONTAINER:
		return E_INVALIDARG;
	}
	return S_OK;
}

// Den vollst‰ndigen Moniker dieses Objektes liefern
HRESULT CTRiASFeature::GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk, OBJECTMAPMODE rgMode)
{
	switch (dwWhich) {
	case OLEWHICHMK_OBJREL:
		return GetFeatureMoniker (m_hFeature, m_bstrName, NULL, dwWhich, ppIMk, rgMode);

	case OLEWHICHMK_OBJFULL:
		{
		WMoniker mk;

			RETURN_FAILED_HRESULT(MkGetMoniker (m_Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
			return GetFeatureMoniker (m_hFeature, m_bstrName, mk, dwWhich, ppIMk, rgMode);
		}

	default:
	case OLEWHICHMK_CONTAINER:
		return E_INVALIDARG;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Events verschicken

HRESULT CTRiASFeature::Fire_ModifyingFeature (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASFeatureEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ModifyingFeature (pIViewItem, pVal);
	return S_OK;
}

HRESULT CTRiASFeature::Fire_FeatureToModify (IDispatch *pIViewItem)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASFeatureEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> FeatureToModify (pIViewItem);
	return S_OK;
}

HRESULT CTRiASFeature::Fire_FeatureModified (BSTR Name)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASFeatureEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> FeatureModified (Name);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASFeature::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return TRIASDB_E_INVALID_PARAMETER;

	*pClassID = CLSID_TRiASFeature;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASFeature::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASFeature::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

long lSignature = 0L;

	THROW_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (FEATURE_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
	if ((lVersion & ~FEATURE_VERSION_MINOR_MASK) > LASTKNOWN_FEATURE_VERSION)
		return TRIASDB_W_NEWERFEATURE;

	m_bstrName.Empty();
	m_bstrDesc.Empty();
	RETURN_FAILED_HRESULT(m_bstrName.ReadFromStream (pStm));	// Name
	RETURN_FAILED_HRESULT(m_bstrDesc.ReadFromStream (pStm));	// Description

	_ASSERTE(sizeof(long) == sizeof(FEATURETYPE));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)m_rgType));	// Merkmalstyp

// MonikerDisplayName einlesen, um Parent wiederzufinden
WMoniker mk;

	RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_IMoniker, mk.ppv()));
	RETURN_FAILED_HRESULT(::BindMoniker (mk, NULL, IID_IDispatch, (LPVOID *)&m_Parent));

// Aggregat davon in Kenntnis setzen
	if (NULL != m_pICallback)
		m_pICallback -> SetupFeature (SETUPFEATUREMODE_InitOrLoad);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Formatversion schreiben
	RETURN_FAILED_HRESULT(SaveLong(pStm, FEATURE_SIGNATURE));
	RETURN_FAILED_HRESULT(SaveLong(pStm, LASTKNOWN_FEATURE_VERSION));

// eigene Eigenschaften wegschreiben
	RETURN_FAILED_HRESULT(m_bstrName.WriteToStream (pStm));		// Name
	RETURN_FAILED_HRESULT(m_bstrDesc.WriteToStream (pStm));		// Description

	RETURN_FAILED_HRESULT(SaveLong (pStm, (long &)m_rgType));	// Merkmalstyp

// Moniker des Containers dieses Objektes wegschreiben
WMoniker mk;

	RETURN_FAILED_HRESULT(MkGetMoniker (m_Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
	RETURN_FAILED_HRESULT(::OleSaveToStream (WPersistStream(mk), pStm));

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASFeature::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return TRIASDB_E_INVALID_PARAMETER;

WMoniker mk;

	RETURN_FAILED_HRESULT(MkGetMoniker (m_Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
	RETURN_FAILED_HRESULT(WPersistStream(mk) -> GetSizeMax (pcbSize));

	pcbSize -> QuadPart += LenForStream(m_bstrName) + LenForStream(m_bstrDesc) + 2*sizeof(long);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit

STDMETHODIMP CTRiASFeature::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

// Aggregat davon in Kenntnis setzen
	if (NULL != m_pICallback)
		m_pICallback -> SetupFeature (SETUPFEATUREMODE_InitOrLoad);

	m_fIsDirty = false;	
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASPropertySupport

STDMETHODIMP CTRiASFeature::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == Property)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASFeature::CreateProperty");

	COM_TRY {
	// evtl. abschlieﬂende Leerzeichen abschneiden
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

STDMETHODIMP CTRiASFeature::RemoveProperty (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// evtl. abschlieﬂende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_DeletingProperty (bstrName, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToDelete (bstrName));

// eigentliche Aktion
HRESULT hr = E_FAIL;

	RETURN_FAILED_HRESULT(hr = ReleasePropertySupportSite (bstrName));	// zust‰ndiges Objekt freigeben

// Event hinterher
	if (S_OK == hr) {
		m_fIsDirty = true;
		RETURN_FAILED_HRESULT(Fire_PropertyDeleted (bstrName));
	}
	return hr;		// S_FALSE heiﬂt: nicht gefunden
}

/////////////////////////////////////////////////////////////////////////////
// IOleObject
STDMETHODIMP CTRiASFeature::GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	switch (dwWhich) {
    case OLEWHICHMK_CONTAINER:
		return MkGetMoniker (m_Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, ppIMk);

	case OLEWHICHMK_OBJREL:
    case OLEWHICHMK_OBJFULL:
		return GetThisMoniker (dwWhich, ppIMk);
	
	default:
		break;
	}
	return E_INVALIDARG;
}

