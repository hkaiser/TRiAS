// TRiASProperty.cpp : Implementation of CTRiASProperty
#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"

#include "TRiASProperty.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this clas
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASProperty);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASProperty::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASProperty, CTRiASProperty)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASProperty, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASProperty
// Ist lediglich zuständig für die Speicherinterne Verwaltung

STDMETHODIMP CTRiASProperty::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASProperty,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// Helperfunktion für QueryInterface
HRESULT WINAPI CTRiASProperty::_Choice (void *pv, REFIID iid, void** ppvObject, DWORD dw)
{
CTRiASProperty *pThis = (CTRiASProperty *)pv;

// Wenn im nicht initialisiertem Zustand nach IPersist... gefragt wird, dann soll das
// Objekt gerade geladen werden. Da es aber gespeichert wurde, muß das angehängte
// SupportObjekt seinerseits Hilfe beim Speichern brauchen.
	if (pThis -> IsInitialized() && !pThis -> NeedsSavingHelp()) 
		return E_NOINTERFACE;		// Supportobjekt  speichert die Property selbst

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis+dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperty::get_Name");

CComBSTR bstr (m_bstrName);

	if (!bstr)
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

// die erste Funktion, die gerufen werden muß !
STDMETHODIMP CTRiASProperty::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bstrName = newVal;
	if (!m_bstrName)
		return REPORT_OUTOFMEMORY();

	m_fIsDirty = true;

// Name wird als erstes gesetzt, danach gilt das Objekt als initialisiert
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperty::get_Description");

CComBSTR bstr (m_bstrDesc);

	if (!bstr)
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASProperty::put_Description(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bstrDesc = newVal;
	if (!m_bstrDesc)
		return REPORT_OUTOFMEMORY();

	m_fIsDirty = true;

// Name wird als erstes gesetzt, danach gilt das Objekt als initialisiert
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::get_Inherited(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperty::get_Inherited");

	*pVal = m_fInherited ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::get_Value(VARIANT * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperty::get_Value");

// zuständigen Server arbeiten lassen
	return m_Support -> GetValue (m_bstrName, pVal);
}

STDMETHODIMP CTRiASProperty::put_Value(VARIANT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);

// zuständigen Server arbeiten lassen
	RETURN_FAILED_HRESULT(m_Support -> PutValue (m_bstrName, newVal));
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::get_Type(PROPERTY_TYPE * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperty::get_Type");

// zuständigen Server arbeiten lassen
	return m_Support -> GetType (m_bstrName, pVal);
}

STDMETHODIMP CTRiASProperty::put_Type(PROPERTY_TYPE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);

// zuständigen Server arbeiten lassen
	RETURN_FAILED_HRESULT(m_Support -> PutType (m_bstrName, newVal));
	m_fIsDirty = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASProperty::SetValueAndType(VARIANT Val, PROPERTY_TYPE Type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);

// zuständigen Server arbeiten lassen
	RETURN_FAILED_HRESULT(m_Support -> PutValueAndType (m_bstrName, Val, Type));
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::GetValueAndType(VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	if (NULL == pVal || NULL == pType) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperty::get_Type");

// zuständigen Server arbeiten lassen
	return m_Support -> GetValueAndType (m_bstrName, pVal, pType);
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASProperty::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperty::GetClassID");

	*pClassID = CLSID_TRiASProperty;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASProperty::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASProperty::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

// Version prüfen
long lSignature = 0L;

	THROW_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (PROPERTY_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
	if ((lVersion & ~PROPERTY_VERSION_MINOR_MASK) > LASTKNOWN_PROPERTY_VERSION)
		return TRIASDB_W_NEWERVIEW;

// Supportobjekt instantiieren
CLSID ClsId;
WTRiASPropertyCallback Supp;

	RETURN_FAILED_HRESULT(::ReadClassStm (pStm, &ClsId));
	RETURN_FAILED_HRESULT(Supp.CreateInstance (ClsId));

	m_bstrName.Empty();
	RETURN_FAILED_HRESULT(m_bstrName.ReadFromStream (pStm));
	m_bstrDesc.Empty();
	if (lVersion >= PROPERTY_VERSION_101)	// BeschreibungsInfo erst ab V1.01
	{
		RETURN_FAILED_HRESULT(m_bstrDesc.ReadFromStream (pStm));
	}

PROPERTY_TYPE rgType;
CComVariant Value;

	_ASSERTE(sizeof(long) == sizeof(PROPERTY_TYPE));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)rgType));
	RETURN_FAILED_HRESULT(Value.ReadFromStream (pStm));

	RETURN_FAILED_HRESULT(Supp -> PutValueAndType(m_bstrName, Value, rgType));
	RETURN_FAILED_HRESULT(SetPropertySupportSite (Supp));

	_ASSERTE(NeedsSavingHelp());

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);

	_ASSERTE(NeedsSavingHelp());

CLSID ClsId;

	{
	CComQIPtr<IPersist, &IID_IPersist> ps (m_Support);

		if (NULL == ps.p)
			return E_UNEXPECTED;	// Supportobjekt muß IPersist unterstützen
		RETURN_FAILED_HRESULT(ps -> GetClassID (&ClsId));
	}

	RETURN_FAILED_HRESULT(SaveLong (pStm, PROPERTY_SIGNATURE));
	RETURN_FAILED_HRESULT(SaveLong (pStm, PROPERTY_VERSION_101));
	RETURN_FAILED_HRESULT(::WriteClassStm (pStm, ClsId));	// ClsId des Supportobjektes

	RETURN_FAILED_HRESULT(m_bstrName.WriteToStream (pStm));
	RETURN_FAILED_HRESULT(m_bstrDesc.WriteToStream (pStm));

PROPERTY_TYPE rgType;
CComVariant Value;

	RETURN_FAILED_HRESULT(m_Support -> GetValueAndType(m_bstrName, &Value, &rgType));
	RETURN_FAILED_HRESULT(SaveLong (pStm, rgType));
	RETURN_FAILED_HRESULT(Value.WriteToStream (pStm));

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASProperty::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CTRiASProperty::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

// DefaultNamen aus Adresse generieren
TCHAR cbBuffer[_MAX_PATH];

	wsprintf (cbBuffer, g_cbDefPropName, this);
	m_bstrName = cbBuffer;
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CTRiASProperty::SetSite (IUnknown *pISite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WTRiASPropertyCallback Site (pISite);

		return SetPropertySupportSite (Site);

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProperty::GetSite (REFIID riid, void **ppvSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	return m_Support -> QueryInterface (riid, ppvSite);
}



STDMETHODIMP CTRiASProperty::Refresh()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_bstrName || !m_Support) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);

// zuständigen Server arbeiten lassen
HRESULT hr = m_Support -> Refresh(m_bstrName);

	if (FAILED(hr) && E_NOTIMPL != hr)
	{
		RETURN_FAILED_HRESULT(hr);
	}
	m_fIsDirty = true;
	return S_OK;
}
