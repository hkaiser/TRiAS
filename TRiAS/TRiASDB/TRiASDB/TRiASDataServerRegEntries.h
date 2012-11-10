///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASDataServerRegEntries.h | Declaration of the <c CTRiASDataServerRegEntries> class

#if !defined(_TRIASDATASERVERREGENTRIES_H__F4B3F949_810E_11D1_9776_00A024D6F582__INCLUDED_)
#define _TRIASDATASERVERREGENTRIES_H__F4B3F949_810E_11D1_9776_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
// {422FB8C3-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASServerEntry = 
	{0x422fb8c3,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineSmartInterface(TRiASDataServerRegEntry);							// WTRiASDataServerRegEntry
DefineEnumerator2(WTRiASDataServerRegEntry, IID_IEnumTRiASServerEntry);	// NEnumWTRiASDataServerRegEntry
DefineSmartEnumerator2(WTRiASDataServerRegEntry, IID_IEnumTRiASServerEntry);	// WEnumWTRiASDataServerRegEntry

/////////////////////////////////////////////////////////////////////////////
// CTRiASDataServerRegEntries

class ATL_NO_VTABLE CTRiASDataServerRegEntries : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public CReportErrorComCoClass<CTRiASDataServerRegEntries, &CLSID_TRiASDataServerRegEntries, &IID_ITRiASDataServerRegEntries>,
	public IDispatchImpl<ITRiASDataServerRegEntries, &IID_ITRiASDataServerRegEntries, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASDataServerRegEntries interface_t;
	typedef ITRiASDataServerRegEntry controlled_t;

	CTRiASDataServerRegEntries()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASDataServerRegEntries)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASDATASERVERREGENTRIES)
	DECLARE_CLASSFACTORY_SINGLETON(CTRiASDataServerRegEntries)	// CTRiASDataServerRegEntries existieren nur einmal
	DECLARE_PROTECT_FINAL_CONSTRUCT();

	BEGIN_COM_MAP(CTRiASDataServerRegEntries)
		COM_INTERFACE_ENTRY(ITRiASDataServerRegEntries)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// Initialisierung/Aufr‰umen
	HRESULT FinalConstruct (void)
	{
		return Refresh();		// alles neu einlesen
	}
	void FinalRelease (void)
	{
		m_Enum.Assign(NULL);	// Enumerator freigeben
	}

	HRESULT CreateNewEnum (IEnum<WTRiASDataServerRegEntry> **ppIEnum)
	{
		ATLTRY(*ppIEnum = new NEnumWTRiASDataServerRegEntry());	// Konstruktor hinterl‰ﬂt RefCnt==1
		return (NULL == *ppIEnum) ? E_OUTOFMEMORY : S_OK;
	}
	HRESULT InitEnum (IEnum<WTRiASDataServerRegEntry> *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASDataServerRegEntries
public:
	STDMETHOD(FindFromServerProgID)(/*[in]*/ BSTR ProgID, /*[out, retval]*/ ITRiASDataServerRegEntry **Entry);
	STDMETHOD(Refresh)();
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASDataServerRegEntries **Entries);
	STDMETHOD(get_Count)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ ITRiASDataServerRegEntry **Entry);
	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **Enum);

protected:
	HRESULT FillWithServerEntries (IEnum<WTRiASDataServerRegEntry> *pIEnum);
	HRESULT InitDataServers (REFGUID rGuid, IEnum<WTRiASDataServerRegEntry> *pIEnum);
	HRESULT InitDataServer (LPCSTR pcProgID, ITRiASDataServerRegEntry **ppIEntry);

protected:
	WEnumWTRiASDataServerRegEntry m_Enum;				// eigener Enumerator
};

#endif // !defined(_TRIASDATASERVERREGENTRIES_H__F4B3F949_810E_11D1_9776_00A024D6F582__INCLUDED_)
