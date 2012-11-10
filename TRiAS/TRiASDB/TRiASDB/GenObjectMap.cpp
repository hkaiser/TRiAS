// @doc
// @module GenObjectMap.cpp | Implementation of the <c CGenObjectMap> class

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"

#include "GenObjectMap.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CGenObjectMapEntry);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CGenObjectMapEntry::Dump()
{
	USES_CONVERSION;
	COM_TRY {
	__Interface<IDumpObject> Dump (GetObject());
	CComBSTR bstrIsA;

		THROW_FAILED_HRESULT(Dump -> get_IsA (CLEARED(&bstrIsA)));

	os_string str(OLE2A(bstrIsA));

		D_OUT(1) <<
			"CGenObjectMapEntry: pending " << str << ": \r\n" <<
		D_END;
		THROW_FAILED_HRESULT(Dump -> Dump());
		 
	} COM_CATCH;
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
RT_OBJECT_ENTRY(CLSID_GenObjectMap, CGenObjectMap)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);

/////////////////////////////////////////////////////////////////////////////
// CGenObjectMap

HRESULT CGenObjectMap::RemoveIfApplicable (
	OBJECTMAPMODE rgMode, CObjectMap::iterator it, bool fRemoveFromDBMap)
{
ULONG lRefCnt = (*it).second -> Release();
INT_PTR lDBHandle = (*it).second -> Handle();

	if (OBJECTMAPMODE_RemoveAllReferences == rgMode || 0 == lRefCnt) {
	// Eintrag aus Map's lˆschen und freigeben
	CGenObjectMapEntry *pEntry = (*it).second;

		m_Map.erase (it);

	// evtl. aus zus‰tzlicher GeoDB-Map entfernen
		if (fRemoveFromDBMap && 0 != lDBHandle) {
		CGeoHandleMap::iterator ith = m_HandleMap.find (lDBHandle);

			if (ith != m_HandleMap.end())
				m_HandleMap.erase (ith);
		}

	// Speicher freigeben
		delete pEntry;
		return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CGenObjectMap::RemoveObject (INT_PTR lHandle, OBJECTMAPMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	switch (rgMode) {
	case OBJECTMAPMODE_RemoveAllReferences:
	case OBJECTMAPMODE_RemoveThisReference:
		{
		CWriteLock lock(m_sem);
		CObjectMap::iterator it = m_Map.find (lHandle);

			if (it != m_Map.end()) 
				return RemoveIfApplicable (rgMode, it, true);

		// evtl. ist der Eintrag in der zus‰tzlichen GeoDB-Map zu finden
		CGeoHandleMap::iterator ith = m_HandleMap.find (lHandle);

			if (ith != m_HandleMap.end()) {
				it = m_Map.find ((*ith).second);
				if (it != m_Map.end() && S_OK == RemoveIfApplicable (rgMode, it, false)) {
				// alles ok, jedoch aus der alternativen Map
					m_HandleMap.erase (ith);
					return S_OK;
				}
				return S_FALSE;
			}
		}
		return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;

	case OBJECTMAPMODE_RemoveAllObjects:
		{
		// alle Eintr‰ge freigeben
		CWriteLock lock(m_sem);

			for (CObjectMap::iterator it = m_Map.begin(); it != m_Map.end(); ++it) {
			CGenObjectMapEntry *pEntry = (*it).second;

				delete pEntry;
			}

		// jetzt Container selbst freigeben
			m_Map.erase();
			m_HandleMap.erase();
		}
		break;

	default:
		return E_INVALIDARG;
	}
	return S_OK;
}

STDMETHODIMP CGenObjectMap::GetObject (INT_PTR lHandle, IUnknown **ppIObject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIObject)
		return E_POINTER;

CReadLock lock (m_sem);
CObjectMap::iterator it = m_Map.find (lHandle);

	if (it != m_Map.end()) {
		*ppIObject = (*it).second -> GetObject();
		return S_OK;
	}

// evtl. ist der Eintrag in der zus‰tzlichen GeoDB-Map zu finden
CGeoHandleMap::iterator ith = m_HandleMap.find (lHandle);

	if (ith != m_HandleMap.end()) {
		it = m_Map.find ((*ith).second);
		if (it != m_Map.end()) {
			*ppIObject = (*it).second -> GetObject();
			return S_FALSE;		// alles ok, jedoch aus der alternativen Map
		}
	}
	return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;
}

STDMETHODIMP CGenObjectMap::GetObjectEx (
	INT_PTR lHandle, OBJECTMAPMODE rgMode, IUnknown **ppIObject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIObject)
		return E_POINTER;

// zuerst den Eintrag in der zus‰tzlichen GeoDB-Map zu suchen
CReadLock lock (m_sem);

	if (OBJECTMAPMODE_GetObjectFromNativeHandle == rgMode) {
	CGeoHandleMap::iterator ith = m_HandleMap.find (lHandle);

		if (ith != m_HandleMap.end()) {
		CObjectMap::iterator it = m_Map.find ((*ith).second);

			if (it != m_Map.end()) {
				*ppIObject = (*it).second -> GetObject();
				return S_OK;
			}
		}

	CObjectMap::iterator it = m_Map.find (lHandle);

		if (it != m_Map.end()) {
			*ppIObject = (*it).second -> GetObject();
			return S_FALSE;
		}
	} 
	else {
		_ASSERTE(OBJECTMAPMODE_GetObjectFromHandle == rgMode);
		return GetObject (lHandle, ppIObject);
	}
	return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;
}

STDMETHODIMP CGenObjectMap::GetObjectHandle (
	VARIANT vNameOrHandle, IUnknown *pIObject, OBJECTMAPMODE rgMode, INT_PTR *plHandle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == plHandle) 
		return E_POINTER;

	if (!(OBJECTMAPMODE_CreateObjectHandle & rgMode))
		return E_UNEXPECTED;		// diese Funktion kann nur neu erzeugen

#if defined(_DEBUG)
INT_PTR lPreDefHandle = *plHandle;
#endif // defined(_DEBUG)

	if (0L == *plHandle) {
		*plHandle = GetNextCookie();
		_ASSERTE(m_Map.find (*plHandle) == m_Map.end());	// Handle darf noch nicht vergeben sein !
	} else {
	CReadLock lock (m_sem);
	CObjectMap::iterator it = m_Map.find (*plHandle);

		if (it != m_Map.end()) {
#if defined(_DEBUG)
		// die folgende assertion weist darauf hin, daﬂ dieses
		// Objekt inkonsistent registriert werden soll (war ohne AddRef
		// und soll jetzt mit AddRef registriert werden oder v.v.)
			if (OBJECTMAPMODE_RegistrationKeepsAlive & rgMode) {
				_ASSERTE((*it).second -> KeepsAlive());
			} else {
				_ASSERTE(!(*it).second -> KeepsAlive());
			}
#endif // _DEBUG
			(*it).second -> AddRef();
			return S_FALSE;				// existiert bereits
		}
	} // CReadLock aufheben

// ab jetzt wird geschrieben
CWriteLock lock (m_sem);

// evtl. Zuordnung von GeoDB-handle zu vergebenem Handle speichern
INT_PTR lHandle = 0L;

	if (!HasType (rgMode, OBJECTMAPMODE_DoNotRegisterNativeHandle) && 
		VT_I4 == V_VT(&vNameOrHandle) && 0 != V_I4(&vNameOrHandle))
	{
	size_t iHandleSize = m_HandleMap.size();

		lHandle = V_I4(&vNameOrHandle);
		ATLTRY(m_HandleMap.insert (CGeoHandleMap::value_type(lHandle, *plHandle)));
		if (m_HandleMap.size() != iHandleSize+1)
			return E_OUTOFMEMORY;
	}

bool fAddRef = (OBJECTMAPMODE_RegistrationKeepsAlive & rgMode) ? true : false;
size_t iSize = m_Map.size();
CGenObjectMapEntry *pEntry = NULL;

	COM_TRY {
		pEntry = new CGenObjectMapEntry(pIObject, lHandle, fAddRef);
		m_Map.insert (CObjectMap::value_type(*plHandle, pEntry));
	} COM_CATCH;

	_ASSERTE(m_Map.size() == iSize+1);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches f¸r die Konkretheit der Properties zust‰ndig ist

STDMETHODIMP CGenObjectMap::PutValue (BSTR Name, VARIANT Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGenObjectMap::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CGenObjectMap::GetValue");

	_ASSERTE(!wcscmp (Name, g_cbObjectsMap) || !wcscmp (Name, g_cbObjectMap) ||
		   !wcscmp (Name, g_cbFeatureMap));	// muﬂ "ObjectsMap", "ObjectMap" oder "FeatureMap" sein

	if (wcscmp (Name, g_cbObjectsMap) && wcscmp (Name, g_cbObjectMap) && wcscmp (Name, g_cbFeatureMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CGenObjectMap::GetValue");

WTRiASObjectHandleMap Map (this);		// AddRef

	V_VT(pVal) = VT_DISPATCH;
	V_DISPATCH(pVal) = Map.detach();
	return S_OK;
}

STDMETHODIMP CGenObjectMap::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGenObjectMap::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CGenObjectMap::GetType");

	_ASSERTE(!wcscmp (Name, g_cbObjectsMap) || !wcscmp (Name, g_cbObjectMap) ||
		   !wcscmp (Name, g_cbFeatureMap));	// muﬂ "ObjectsMap", "ObjectMap" oder "FeatureMap" sein

	if (wcscmp (Name, g_cbObjectsMap) && wcscmp (Name, g_cbObjectMap) && wcscmp (Name, g_cbFeatureMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CGenObjectMap::GetValue");

	*pVal = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CGenObjectMap::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGenObjectMap::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CGenObjectMap::GetType");

	_ASSERTE(!wcscmp (Name, g_cbObjectsMap) || !wcscmp (Name, g_cbObjectMap) ||
		   !wcscmp (Name, g_cbFeatureMap));	// muﬂ "ObjectsMap", "ObjectMap" oder "FeatureMap" sein

	if (wcscmp (Name, g_cbObjectsMap) && wcscmp (Name, g_cbObjectMap) && wcscmp (Name, g_cbFeatureMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CGenObjectMap::GetValue");

WTRiASObjectHandleMap Map (this);		// AddRef

	V_VT(pVal) = VT_DISPATCH;
	V_DISPATCH(pVal) = Map.detach();

	*pType = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CGenObjectMap::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CGenObjectMap::ShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return DeleteCookieHolder(), S_OK;
}

STDMETHODIMP CGenObjectMap::get_Name (BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASObjectHandleMapBase::get_Name");

// Beschreibungsinfo ist gesetzt
CComBSTR bstr (m_bstrName);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CGenObjectMap::put_Name (BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(0 == m_CookieHolder || m_bstrName == newVal);		// darf nur einmal gerufen werden

	m_bstrName = newVal;
	if (!m_bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	if (0 == m_CookieHolder)
		return InitCookieHolder();
	return S_OK;
}


