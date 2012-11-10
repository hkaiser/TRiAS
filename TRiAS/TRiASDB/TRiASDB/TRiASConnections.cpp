// @doc
// @module TRiASConnections.cpp | Implementation of the <c CTRiASConnections> class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include "Strings.h"
#include "Wrapper.h"			// SmartIF's

#include "TRiASDBGuids.h"
#include "TRiASConnection.h"
#include "TRiASConnections.h"
#include "MakeEnumVariant.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASConnections, CTRiASConnections)

/////////////////////////////////////////////////////////////////////////////
// SmartInterface's
DefineSmartInterface(TRiASConnectionEvents);

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnections
STDMETHODIMP CTRiASConnections::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASConnections,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASConnections::FinalConstruct (void)
{
	CTRiASConnection::ResetAskMode();

// init base instance data
HRESULT hr = IPersistStorageOMImpl<CTRiASConnections>::FinalConstruct();

	if (FAILED(hr)) return hr;

// instance data
	ATLTRY(m_Enum = new NEnumWTRiASConnection());
	if (!m_Enum) 
		return E_OUTOFMEMORY;

	m_Enum -> Release();	// Konstruktor hinterl‰ﬂt RefCnt==1
	return S_OK;
}

void CTRiASConnections::FinalRelease()
{
	m_Enum.Assign(NULL);	// Enumerator freigeben
	m_pIParent = NULL;
	m_Application = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASConnections::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASConnections::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASConnections::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::get_Application");

	*pVal = m_pIParent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASConnections::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pIParent = newVal;		// no AddRef !

// das Nullsetzen des Parent wird als Signal zum Freigeben gewertet
// evtl. alle SubObjekte von ihrem Bezug abh‰ngen

// Enumerator bzw. TRiASConnection's freigeben
	if (m_Enum.IsValid()) {
	WTRiASConnection Conn;

		for (m_Enum -> Reset(); S_OK == m_Enum -> Next (1, &Conn, NULL); /**/)
		{
			Conn -> put_Parent (m_pIParent);
		}
	}
	return S_OK;
}

STDMETHODIMP CTRiASConnections::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::get_Application");

	*pVal = m_Enum -> Count();
	return S_OK;
}

STDMETHODIMP CTRiASConnections::_Add(ITRiASConnection *Connection, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// testen, ob dieses Objekt noch nicht in der collection enthalten ist
	_ASSERTE(IsFirstOccurence (m_Enum, Connection, ITRiASConnection::get_Name, (CComBSTR *)NULL));

	if (fFullAdd) {
		COM_TRY {
			THROW_FAILED_HRESULT(Connection -> put_Application (m_Application));
			THROW_FAILED_HRESULT(Connection -> put_Parent (m_pIParent));
		} COM_CATCH;
	}	
	return m_Enum -> AddItem (Connection);
}

STDMETHODIMP CTRiASConnections::RemoveConnection(ITRiASConnection *pIConn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(pIConn -> get_Name (CLEARED(&bstrName)));

	// Enumerator umkopieren und betreffendes Projekt rauswerfen
	WTRiASConnection Conn;
	WEnumWTRiASConnection Enum;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		THROW_FAILED_HRESULT(m_Enum -> Clear());

		for (Enum -> Reset(); S_OK == Enum -> Next (1, &Conn, NULL); /**/)
		{
		CComBSTR bstr;

			THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstr)));
			if (wcscmp(bstrName, bstr))
				m_Enum -> AddItem(Conn);
		}
		_ASSERTE(0 == Enum -> Count() || Enum -> Count() == m_Enum -> Count() +1);
	} COM_CATCH;
	
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASConnections::Add(BSTR Name, ITRiASConnection **ppIConnection)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIConnection) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::Add");

// Erzeugen einer neuen Connection und hinzuf¸gen zur Collection
	COM_TRY {
	// ‹berpr¸fen, ob Connection bereits existiert
	WTRiASConnection Conn;

		{
		WEnumWTRiASConnection Enum;

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Conn, NULL); /**/)
			{
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));
				if (!wcscmp(bstrName, Name)) {
					*ppIConnection = Conn.detach();
					return S_FALSE;		// existiert bereits
				}
			}
		}

	// darf erzeugt werden ?
	VARIANT_BOOL fCreate = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Fire_CreatingConnection (Name, &fCreate));
		if (fCreate != VARIANT_FALSE)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_ConnectionToCreate (Name));

	// jetzt wirklich erzeugen
		THROW_FAILED_HRESULT(m_ObjMan -> CreateObject (CLSID_TRiASConnection, Name, STGM_CREATE, Conn.ppu(), false));

		THROW_FAILED_HRESULT(Conn -> put_Name(Name));
		THROW_FAILED_HRESULT(Conn -> put_Parent(m_pIParent));
		THROW_FAILED_HRESULT(Conn -> put_Application(m_Application));

	// AddConnection(Conn) in ConnectionEvent

	// erfolgreich erzeugt
		THROW_FAILED_HRESULT(Fire_ConnectionCreated (Conn));
		*ppIConnection = Conn.detach();
	} COM_CATCH;
	
	return S_OK;
}

STDMETHODIMP CTRiASConnections::Item(VARIANT Index, ITRiASConnection **ppIConnection)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIConnection) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::Item");

CComVariant vIndex;
bool fFound = false;

	*ppIConnection = NULL;
	COM_TRY {
	WEnumWTRiASConnection Enum;
	WTRiASConnection Conn;

	// Verhindern, daﬂ als Nummern als Zeichenkette falsch interpretiert werden
		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > m_Enum -> Count())
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::Item");

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(Enum -> Reset());

			if (V_I4(&vIndex) > 1)
			{
				THROW_FAILED_HRESULT(Enum -> Skip (V_I4(&vIndex)-1));
			}
			if (S_OK == Enum -> Next (1, &Conn, NULL))
			{
				*ppIConnection = Conn.detach();
				fFound = true;
			}

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {
		CIID Guid (V_BSTR(&vIndex), CIID::INITCIID_InitFromGuid);

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			if (!Guid) {
			// connection ¸ber ihren Namen suchen
				for (Enum -> Reset(); S_OK == Enum -> Next (1, &Conn, NULL); /**/) {
				CComBSTR bstrName;

					THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));
					if (!wcscmp(bstrName, V_BSTR(&vIndex))) {
						*ppIConnection = Conn.detach();
						fFound = true;
						break;
					}
				}
			} else {
			// Connection ¸ber ihren GuidPath suchen
				for (Enum -> Reset(); S_OK == Enum -> Next (1, &Conn, NULL); /**/) {
				CComBSTR bstrGuid;

					THROW_FAILED_HRESULT(Conn -> get_GuidPath (CLEARED(&bstrGuid)));

				CIID GuidT (bstrGuid, CIID::INITCIID_InitFromGuid);

					if (Guid == GuidT) {
						*ppIConnection = Conn.detach();
						fFound = true;
						break;
					}
				}
			}

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::Item");
	} COM_CATCH;
	
	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_CONNECTION);

	return S_OK;
}

STDMETHODIMP CTRiASConnections::Remove(VARIANT Index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

HRESULT hr_result = S_OK;

	COM_TRY {
	// darf gelˆscht werden ?
	VARIANT_BOOL fDelete = VARIANT_FALSE;

	// Verbindung herauslˆschen
	WEnumWTRiASConnection Enum;
	WTRiASConnection Conn;
	WTRiASConnection ToDelConn;
	long lCnt = 1;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		THROW_FAILED_HRESULT(m_Enum -> Clear());

	CComVariant vIndex;
	CComBSTR bstrName;

		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > m_Enum -> Count())
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::Item");

		// alle auﬂer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Conn, NULL); lCnt++)
			{
				if (lCnt == V_I4(&vIndex)) {
				// zu entfernende Connection gefunden
					THROW_FAILED_HRESULT(Fire_DeletingConnection (Conn, &fDelete));
					if (fDelete == VARIANT_FALSE) {
					CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes lˆschen verhindern

						THROW_FAILED_HRESULT(Fire_ConnectionToDelete (Conn));
						THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));

						ToDelConn = Conn;
						continue;
					}

					hr_result = S_FALSE;		// abgebrochen oder Fehler
				}

			// diese Connection nicht entfernen
				THROW_FAILED_HRESULT(m_Enum -> AddItem(Conn));
			}

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {

		// alle auﬂer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Conn, NULL); lCnt++)
			{
				THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));
				if (!wcscmp(bstrName, V_BSTR(&vIndex))) {
				// zu entfernende Connection gefunden
					THROW_FAILED_HRESULT(Fire_DeletingConnection (Conn, &fDelete));
					if (fDelete == VARIANT_FALSE) {
					CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes lˆschen verhindern

						THROW_FAILED_HRESULT(Fire_ConnectionToDelete (Conn));
						THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));

						ToDelConn = Conn;
						continue;
					}
					hr_result = S_FALSE;		// abgebrochen oder Fehler
				}

			// diese Connection nicht entfernen
				m_Enum -> AddItem(Conn);
			}
			bstrName = V_BSTR(&vIndex);

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::Item");

		_ASSERTE(0 == Enum -> Count() || Enum -> Count() == m_Enum -> Count() +1);

	// erfolgreich gelˆscht
		THROW_FAILED_HRESULT(ToDelConn -> put_Parent (NULL));
		THROW_FAILED_HRESULT(ToDelConn -> Remove ());			// evtl. Datenquelle lˆschen
		THROW_FAILED_HRESULT(m_ObjMan -> DelObject (bstrName));
		THROW_FAILED_HRESULT(Fire_ConnectionDeleted (bstrName));
	} COM_CATCH;
	
	return hr_result;
}

STDMETHODIMP CTRiASConnections::_NewEnum (IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::_NewItem");

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASConnections::_Clone(ITRiASConnections **ppIConns)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIConns) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnections::_Clone");

CComObject<CTRiASConnections> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASConnections>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> InitObjMan (m_ObjMan, m_Stg, m_StgMode));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));

		THROW_FAILED_HRESULT(pNew -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pNew -> put_Parent (m_pIParent));

	WTRiASConnections Conns (pNew);		// pending AddRef

		*ppIConns = Conns.detach();

	} COM_CATCH_OP(DELETE_OBJ(pNew));

	return S_OK;
}

STDMETHODIMP CTRiASConnections::SetEventSink (IUnknown *pIUnk, VARIANT_BOOL fAdvise)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (fAdvise) {
		_ASSERTE(m_dwCookie == 0);
		return AtlAdvise (pIUnk, GetUnknown(), IID_ITRiASConnectionEvents, &m_dwCookie);
	} else {
		_ASSERTE(m_dwCookie != 0);

	DWORD dwCookie = m_dwCookie;

		m_dwCookie = 0L;
		return AtlUnadvise (pIUnk, IID_ITRiASConnectionEvents, dwCookie);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Events verschicken
HRESULT CTRiASConnections::Fire_CreatingConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> CreatingConnection (Name, pVal);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectionToCreate (BSTR Name)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionToCreate (Name);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectionCreated (IDispatch * pIConn)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionCreated (pIConn);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_DeletingConnection (IDispatch *pIConn, VARIANT_BOOL * pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> DeletingConnection (pIConn, pVal);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectionToDelete (IDispatch * pIConn)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionToDelete (pIConn);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectionDeleted(BSTR Name)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionDeleted (Name);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_RenamingConnection(BSTR OldName, BSTR NewName, VARIANT_BOOL * pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> RenamingConnection (OldName, NewName, pVal);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectionToRename(BSTR OldName, BSTR NewName)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionToRename (OldName, NewName);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectionRenamed(IDispatch *pIConn)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionRenamed (pIConn);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	_ASSERTE(m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ChangingConnectedDatasource (pIConn, pVal);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectedDatasourceToChange (IDispatch *pIConn)
{
	_ASSERTE(m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectedDatasourceToChange (pIConn);
	return S_OK;
}

HRESULT CTRiASConnections::Fire_ConnectedDatasourceChanged (IDispatch *pIConn)
{
	_ASSERTE(m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ConnectedDatasourceChanged (pIConn);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ITRiASConnectionEvents
STDMETHODIMP CTRiASConnections::CreatingConnection (BSTR Name, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionToCreate (BSTR Name)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionCreated (IDispatch *pIConn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WTRiASConnection Conn (pIConn);

		THROW_FAILED_HRESULT(_Add(Conn, VARIANT_TRUE));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnections::OpeningConnection (BSTR Name, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionToOpen (BSTR Name)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionOpened (IDispatch *pIConn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ClosingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionToClose (IDispatch *pIConn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionClosed (BSTR Name)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::DeletingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionToDelete (IDispatch *pIConn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn nicht wir derzeit bearbeitet werden
	if (IsSemaphoreSignaled (m_lSemDel, *this)) 
		return S_OK;

	COM_TRY {
	WTRiASConnection Conn (pIConn);

		THROW_FAILED_HRESULT(RemoveConnection (Conn));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionDeleted (BSTR Name)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::RenamingConnection (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectionToRename (BSTR OldName, BSTR NewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return RenameObject (OldName, NewName);
}

STDMETHODIMP CTRiASConnections::ConnectionRenamed (IDispatch *pIConn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectedDatasourceToChange (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASConnections::ConnectedDatasourceChanged (IDispatch *pIConn)
{
	return S_OK;
}

