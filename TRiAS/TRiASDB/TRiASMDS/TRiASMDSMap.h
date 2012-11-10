// TRiASMDSMap.h : Declaration of the CTRiASMDSMap

#ifndef __TRIASMDSMAP_H_
#define __TRIASMDSMAP_H_

/////////////////////////////////////////////////////////////////////////////
// CTRiASMDSMap

const long MAP_VERSION = 0x0000L;			// ursprünglich
const long MAP_VERSION_NAME = 0x0100L;		// m_strName hinzugekommen
const long MAP_VERSION_DATA = 0x0101L;		// m_vData hinzugekommen
const long LASTKNOWN_MAP_VERSION = MAP_VERSION_DATA;

typedef struct tagMDSValue {
	CComBSTR	m_strName;
	CComBSTR	m_strShort;
	CComBSTR	m_strLong;
	CComVariant	m_vData;
	tagMDSValue () {}
	tagMDSValue (const CComBSTR& n, const CComBSTR &s, const CComBSTR &l, const CComVariant &d)
		: m_strName(n)
		, m_strShort(s)
		, m_strLong(l)
		, m_vData(d)
	{}
	tagMDSValue (const BSTR& n, const BSTR &s, const BSTR &l, const VARIANT &d)
		: m_strName(n)
		, m_strShort(s)
		, m_strLong(l)
		, m_vData(d)
	{}
	tagMDSValue& operator= (const tagMDSValue& r) {
		m_strName = r.m_strName;
		m_strShort = r.m_strShort;
		m_strLong = r.m_strLong;
		m_vData = r.m_vData;
		return *this;
	}
} MDSValue;

typedef	map<CComBSTR, MDSValue> MapOfKeys;

typedef CComBSTR & (*GetIteratorData)(const MapOfKeys::iterator& it, CComBSTR &strHelp);

#include "TRiASValueEventsCP.h"

class CTRiASMDSMap : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASMDSMap, &CLSID_TRiASMDSMap>,
	public CErrSupport<CTRiASMDSMap, &IID_ITRiASMDSMap>,
	public IDispatchImpl<ITRiASMDSMap, &IID_ITRiASMDSMap, TLB_TRiASMDS_SIGNAT>,
	public CPersistStreamInitImpl<CTRiASMDSMap, &CLSID_TRiASMDSMap>,
	public CProxyITRiASValueEvents<CTRiASMDSMap>,
	public IConnectionPointContainerImpl<CTRiASMDSMap>
{
protected:
	MapOfKeys m_mapOfKeys;

public:
	CTRiASMDSMap() 
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASMDSMAP)

	BEGIN_MSG_MAP(CTRiASMDSMap)
	END_MSG_MAP()

	BEGIN_COM_MAP(CTRiASMDSMap)
		COM_INTERFACE_ENTRY(ITRiASMDSMap)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist,IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream,IPersistStreamInit)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()
	
	BEGIN_CONNECTION_POINT_MAP(CTRiASMDSMap)
		CONNECTION_POINT_ENTRY(IID_ITRiASValueEvents)
	END_CONNECTION_POINT_MAP()

//	BEGIN_PROPERTY_MAP(CTRiASMDSMap)
//	END_PROPERTY_MAP()

	HRESULT SearchItem (const BSTR& strSearch, GetIteratorData func, long lSearchMode, WTRiASMDSStringColl& pValues);

// ITRiASMDSMap
public:
	DECLARE_DEBUG_FUNCENTRY_1(CTRiASMDSMap,_NewEnum,/*[out,retval]*/ IUnknown**, ppIEnum);
	DECLARE_DEBUG_FUNCENTRY_0(CTRiASMDSMap,Clear);
	DECLARE_DEBUG_FUNCENTRY_5(CTRiASMDSMap,SetAt
		, /*[in]*/ BSTR, strKey
		, /*[in]*/ BSTR, strName
		, /*[in]*/ BSTR, strValue
		, /*[in]*/ BSTR, strDescription
		, /*[in]*/ VARIANT, vData
		);
	DECLARE_DEBUG_FUNCENTRY_5(CTRiASMDSMap,GetAt
		, /*[in]*/ BSTR, strKey
		, /*[out]*/ BSTR*, pbstrName
		, /*[out]*/ BSTR*, pbstrDescription
		, /*[out]*/ BSTR*, pbstrValue
		, /*[out]*/ VARIANT*, vData
		);
	DECLARE_DEBUG_FUNCENTRY_1(CTRiASMDSMap,RemoveAt
		, /*[in]*/ BSTR, strKey
		);
	DECLARE_DEBUG_FUNCENTRY_3(CTRiASMDSMap,Search
		, /*[in]*/ BSTR, strSearch
		, /*[in, defaultvalue(mdsSM_Compare)]*/ long, lSearchMode
		, /*[in,out]*/ ITRiASMDSStringColl**, pValues
		);

	HRESULT	OnInitNew( );
	HRESULT LoadData( LPSTREAM pStm, DWORD dwVersion );
	HRESULT SaveData( LPSTREAM pStm, BOOL bClearDirty );
	ULONG	GetDataSize( );

	DWORD	GetSignature( ) { char *s = "MDSM"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return LASTKNOWN_MAP_VERSION; }
};

#endif //__TRIASMDSMAP_H_
