// @doc
// @module TRiASObjectHandleMap.cpp | Implementation of the <c CTRiASObjectHandleMapBase> class

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"

#include "TRiASObjectHandleMap.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CObjectHandleEntry);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CObjectHandleEntry::Dump()
{
	USES_CONVERSION;

os_string str (OLE2A(m_bstrName));

	D_OUT(1) <<
		"\tCObjectHandleEntry: pending " << str << "\r\n" <<
	D_END;
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
RT_OBJECT_ENTRY(CLSID_TRiASObjectHandleMap, CTRiASObjectHandleMap)
RT_OBJECT_ENTRY(CLSID_TRiASObjectsHandleMap, CTRiASObjectsHandleMap)
RT_OBJECT_ENTRY(CLSID_TRiASFeatureHandleMap, CTRiASFeatureHandleMap)
RT_OBJECT_ENTRY(CLSID_TRiASGenericHandleMap, CTRiASGenericHandleMap)

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectHandleMapBase

STDMETHODIMP CTRiASObjectHandleMapBase::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASObjectHandleMap,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTRiASObjectHandleMapBase::GetObjectHandle(
	VARIANT vNameOrHandle, IUnknown *pIObject, OBJECTMAPMODE rgMode, INT_PTR *pHandle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pHandle) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectHandleMapBase::GetObjectHandle");

bool fUseName = !HasType (rgMode, OBJECTMAPMODE_NameDoesNotIdentifyObject);
CComBSTR bstrName;

	if (fUseName) {
		if (V_VT(&vNameOrHandle) != VT_BSTR) 
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectHandleMapBase::GetObjectHandle");

		bstrName = V_BSTR(&vNameOrHandle);

	CObjectNameMap::iterator it = m_Names.find (bstrName);

		if (it != m_Names.end()) {
		// existiert bereits
			*pHandle = (*it).second -> GetCookie();
			return S_FALSE;
		}
	}

// Eintrag existiert noch nicht, ggf. neu erzeugen
LONG lCookie = 0;
HRESULT hr_result = S_OK;

	if (rgMode & OBJECTMAPMODE_UsePredefinedHandle) {
	// mˆglichst vordefinierten Cookie verwenden
	CObjectHandleMap::iterator it = m_Objects.find (*pHandle);

		if (it == m_Objects.end()) {
			lCookie = *pHandle;		// noch nicht vergeben oder bereits vordefiniert vergeben
			EnsureCorrectCookie (lCookie);
		} else 
			hr_result = S_FALSE;
	} 

CObjectHandleEntry *pEntry = NULL;

	if (OBJECTMAPMODE_CreateObjectHandle & rgMode) {
		if (0 == lCookie) 
			lCookie = GetNextCookie();

		_ASSERTE(0 != lCookie);
		_ASSERTE(m_Objects.find(lCookie) == m_Objects.end());	// Handle darf noch nicht vergeben sein !

		try {
			pEntry = new CObjectHandleEntry (pIObject, lCookie, bstrName, rgMode);
			m_Objects.insert(lCookie, pEntry);
			if (fUseName)
				m_Names.insert(bstrName, pEntry);

			*pHandle = lCookie;
			return hr_result;

		} catch (...) {
		// f¸r geordnete Verh‰ltnisse sorgen
			m_Objects.erase(lCookie);
			if (fUseName)
				m_Names.erase(bstrName);
			delete pEntry;
		}
	}

// Eintrag existiert nicht
	return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;
}

STDMETHODIMP CTRiASObjectHandleMapBase::GetObject(INT_PTR lHandle, IUnknown **ppIObject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIObject) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectHandleMapBase::GetObject");

CObjectHandleMap::iterator it = m_Objects.find (lHandle);

	*ppIObject = NULL;
	if (it == m_Objects.end()) 
		return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;		// nicht registriertes Objekt

	*ppIObject = (*it).second -> GetObject(true);
	return S_OK;
}

STDMETHODIMP CTRiASObjectHandleMapBase::GetObjectEx (INT_PTR lHandle, OBJECTMAPMODE rgMode, IUnknown **ppIObject)
{
	return GetObject (lHandle, ppIObject);		// Mode einfach ignorieren
}

STDMETHODIMP CTRiASObjectHandleMapBase::RemoveObject(INT_PTR lHandle, OBJECTMAPMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	switch (rgMode) {
	case OBJECTMAPMODE_RemoveAllReferences:
	case OBJECTMAPMODE_RemoveThisReference:
		{
		CObjectHandleMap::iterator it = m_Objects.find (lHandle);

			if (it == m_Objects.end()) 
				return E_FAIL;		// nicht registriertes Objekt

		// Eintrag aus Map's lˆschen und freigeben
		CObjectHandleEntry *pEntry = (*it).second;

			VERIFY(1 == m_Objects.erase (lHandle));
			if (!HasType (pEntry -> GetMode(), OBJECTMAPMODE_NameDoesNotIdentifyObject))
			{
				VERIFY(1 == m_Names.erase (pEntry -> GetName()));
			}
			delete pEntry;
		}
		break;

	case OBJECTMAPMODE_RemoveAllObjects:
		{
		// alle Eintr‰ge freigeben
			for (CObjectHandleMap::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it) {
			CObjectHandleEntry *pEntry = (*it).second;

				delete pEntry;
			}

		// jetzt Container selbst freigeben
			m_Objects.erase();
			m_Names.erase(m_Names.begin(), m_Names.end());
		}
		break;

	default:
		return E_INVALIDARG;
	}
	return S_OK;
}

STDMETHODIMP CTRiASObjectHandleMapBase::ShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return DeleteCookieHolder(), S_OK;
}

STDMETHODIMP CTRiASObjectHandleMapBase::get_Name (BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectHandleMapBase::get_Name");

// Beschreibungsinfo ist gesetzt
CComBSTR bstr (m_bstrName);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASObjectHandleMapBase::put_Name (BSTR newVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(!wcscmp(m_bstrName, newVal));			// wird bei der Initialisierung festgelegt und muﬂ stimmen
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches f¸r die Konkretheit der Properties zust‰ndig ist

STDMETHODIMP CTRiASGenericHandleMap::PutValue (BSTR Name, VARIANT Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASGenericHandleMap::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASGenericHandleMap::GetValue");

	_ASSERTE(!wcscmp (Name, g_cbGenericMap));	// muﬂ "GenericMap" sein
	if (wcscmp (Name, g_cbGenericMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASGenericHandleMap::GetValue");

WTRiASObjectHandleMap Map (this);		// AddRef

	V_VT(pVal) = VT_DISPATCH;
	V_DISPATCH(pVal) = Map.detach();
	return S_OK;
}

STDMETHODIMP CTRiASGenericHandleMap::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASGenericHandleMap::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASGenericHandleMap::GetType");

	_ASSERTE(!wcscmp (Name, g_cbGenericMap));	// muﬂ "GenericMap" sein
	if (wcscmp (Name, g_cbGenericMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASGenericHandleMap::GetValue");

	*pVal = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CTRiASGenericHandleMap::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASGenericHandleMap::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASGenericHandleMap::GetType");

	_ASSERTE(!wcscmp (Name, g_cbGenericMap));	// muﬂ "GenericMap" sein
	if (wcscmp (Name, g_cbGenericMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASGenericHandleMap::GetValue");

WTRiASObjectHandleMap Map (this);		// AddRef

	V_VT(pVal) = VT_DISPATCH;
	V_DISPATCH(pVal) = Map.detach();

	*pType = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CTRiASGenericHandleMap::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

