///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASConnections.h | Declaration of the <c CTRiASConnections>

#if !defined(_TRIASCONNECTIONS_H__470786E4_838A_11D1_9779_00A024D6F582__INCLUDED_)
#define _TRIASCONNECTIONS_H__470786E4_838A_11D1_9779_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"			// main symbols
#include "PersistStgImpl.h"		// IPersistStorageOMImpl

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
// {422FB8C0-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASConnection = 
	{0x422fb8c0,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineEnumerator2(WTRiASConnection, IID_IEnumTRiASConnection);			// NEnumWTRiASConnection
DefineSmartEnumerator2(WTRiASConnection, IID_IEnumTRiASConnection);		// WEnumWTRiASConnection

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnections

class ATL_NO_VTABLE CTRiASConnections : 
	public ISupportErrorInfo,
	public IPersistStorageOMImpl<CTRiASConnections>,
	public CReportErrorComCoClass<CTRiASConnections, &CLSID_TRiASConnections, &IID_ITRiASConnections>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASConnectionEvents,
	public IDispatchImpl<ITRiASConnections, &IID_ITRiASConnections, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASConnections interface_t;
	typedef ITRiASConnection controlled_t;

	CTRiASConnections()
		: m_pIParent(NULL), m_lSemDel(0), m_dwCookie(0)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASConnections)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCONNECTIONS)

	BEGIN_COM_MAP(CTRiASConnections)
		COM_INTERFACE_ENTRY(ITRiASConnections)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASConnections)
		COM_INTERFACE_ENTRY(ITRiASConnectionEvents)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IID(IID_IPersistStorage, IPersistStorageOMImpl<CTRiASConnections>)
		COM_INTERFACE_ENTRY2_IID(IID_IPersist, IPersist, IPersistStorageOMImpl<CTRiASConnections>)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct (void);
	void FinalRelease (void);

	HRESULT InitEnum (IEnum<WTRiASConnection> *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASConnections
public:
	STDMETHOD(RemoveConnection)(/*[in]*/ ITRiASConnection *pIConn);
	STDMETHOD(SetEventSink)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ VARIANT_BOOL fAdvise);
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASConnections **Conns);
	STDMETHOD(_Add)(/*[in]*/ ITRiASConnection *Connection, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL FullAdd);

	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Index);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ ITRiASConnection **Connection);
	STDMETHOD(Add)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASConnection **Connection);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);

	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

// ITRiASConnectionEvents
	STDMETHOD(CreatingConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionCreated)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(OpeningConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToOpen)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionOpened)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ClosingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToClose)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionClosed)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToDelete)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionDeleted)(/*[in]*/ BSTR Name);
	STDMETHOD(RenamingConnection)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToRename)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName);
	STDMETHOD(ConnectionRenamed)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ChangingConnectedDatasource)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectedDatasourceToChange)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectedDatasourceChanged)(/*[in]*/ IDispatch *pIConn);

// must be implemented for IPersistStorageOMImpl<>
//	HRESULT AddTeanant (IUnknown *pIUnk) throw (_com_error &)
//		{ return _Add (WTRiASConnection(pIUnk)); }
	LPCTSTR GetDescription() const 
		{ return g_cbTRiASConnections; }

protected:
// Events verschicken
	HRESULT Fire_CreatingConnection (BSTR Name, VARIANT_BOOL *pVal);
	HRESULT Fire_ConnectionToCreate (BSTR Name);
	HRESULT Fire_ConnectionCreated (IDispatch * pIConn);
	HRESULT Fire_DeletingConnection (IDispatch *pIConn, VARIANT_BOOL * pVal);
	HRESULT Fire_ConnectionToDelete (IDispatch * pIConn);
	HRESULT Fire_ConnectionDeleted(BSTR Name);
	HRESULT Fire_RenamingConnection(BSTR OldName, BSTR NewName, VARIANT_BOOL * pVal);
	HRESULT Fire_ConnectionToRename(BSTR OldName, BSTR NewName);
	HRESULT Fire_ConnectionRenamed(IDispatch *pIConn);
	HRESULT Fire_ChangingConnectedDatasource(IDispatch *pIConn, VARIANT_BOOL *pVal);
	HRESULT Fire_ConnectedDatasourceToChange(IDispatch *pIConn);
	HRESULT Fire_ConnectedDatasourceChanged(IDispatch *pIConn);

private:
	CComPtr<IDispatch> m_Application;
	IDispatch *m_pIParent;			// no AddRef (fully contained)

// connection spezifische member
	WEnumWTRiASConnection m_Enum;	// eigener Enumerator

	LONG m_lSemDel;					// Semaphore für Eventbehandlung
	DWORD m_dwCookie;				// ConnectionEvents
};

#endif // !defined(_TRIASCONNECTIONS_H__470786E4_838A_11D1_9779_00A024D6F582__INCLUDED_)
