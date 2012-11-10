// TRIASCSSet.h : Declaration of the CTRiASCSSet

#ifndef __TRIASCSSET_H_
#define __TRIASCSSET_H_

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSSet

typedef list< WTRiASCS > ListOfCS;

const long CSSET_VERSION = 0x0100L;
const long LASTKNOWN_CSSET_VERSION = CSSET_VERSION;

// {E2A8BE82-5EB3-11d2-982F-0060085FC1CE}
class ATL_NO_VTABLE CTRiASCSSet : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSSet, &CLSID_TRiASCSSet>,
	public CErrSupport<CTRiASCSSet, &IID_ITRiASCSSet>,
	public IDispatchImpl<ITRiASCSSet, &IID_ITRiASCSSet, &LIBID_TRIASCS>,
	public IConnectionPointContainerImpl<CTRiASCSSet>,
	public CPersistStreamInitImpl<CTRiASCSSet, &CLSID_TRiASCSSet>
{
	ListOfCS	m_listOfCS;
	ListOfCS::iterator	FindItem( const VARIANT& rItem );
	class FillEnum {
		WEnumWTRiASCS&	m_e;
	public:
		FillEnum(WEnumWTRiASCS& e) : m_e(e) { }
		void operator()( WTRiASCS cs ) { m_e->AddItem( cs ); }
	};

	WEnumWTRiASCS	GetEnum() {
		WEnumWTRiASCS	E = new NEnumWTRiASCS;
		E->Release();
		for_each( m_listOfCS.begin(), m_listOfCS.end(), FillEnum(E) );
		return E;
	}
	class CHGLOBAL {
		HGLOBAL	m_hGlobal;
		LPVOID	m_pData;
		void Free() {
			if( m_pData )
				::GlobalUnlock(m_hGlobal);
			if( m_hGlobal )
				::GlobalFree(m_hGlobal);
			m_pData = NULL;
			m_hGlobal = NULL;
		}
		void Attach( const HGLOBAL& src ) {
			Free();
			m_hGlobal = src;
			if( m_hGlobal )
				m_pData = ::GlobalLock( m_hGlobal );
		}
	public:
		CHGLOBAL() : m_hGlobal(NULL), m_pData(0) {}
		CHGLOBAL(DWORD dwSize) : m_hGlobal(NULL), m_pData(0) { 
			if( 0 != dwSize ) 
				Attach( ::GlobalAlloc( GMEM_DISCARDABLE, dwSize ) );
		}
		CHGLOBAL( HGLOBAL h ) : m_hGlobal(NULL), m_pData(0) { Attach(h); }
		~CHGLOBAL() { Free(); }
		HGLOBAL operator=( const HGLOBAL& src ) {
			Attach( src );
			return *this;
		}
		operator LPVOID () { return m_pData; }
		const HGLOBAL& operator*() { return m_hGlobal; }
		DWORD Size( ) { return m_hGlobal ? ::GlobalSize(m_hGlobal) : 0; }
	};
	HRESULT LoadFromMemory( CHGLOBAL& hGlobal );
	HRESULT	SaveToMemory( CHGLOBAL& hGlobal );
	HRESULT	CloneFrom(/*[in]*/ ITRiASCSSet* pSourceSet);
public:
	CTRiASCSSet()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSSET)

	BEGIN_COM_MAP(CTRiASCSSet)
		COM_INTERFACE_ENTRY(ITRiASCSSet)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASCSSet)
	END_CONNECTION_POINT_MAP()
	
// ITRIASCSSet
public:
	STDMETHOD(LoadFromRegistry)(/*[in]*/ TCS_REGISTRYROOT root, /*[in]*/ BSTR strRegKey, /*[in,optional,defaultvalue(NULL)]*/ VARIANT strComputername);
	STDMETHOD(SaveToRegistry)(/*[in]*/ TCS_REGISTRYROOT root, /*[in]*/ BSTR strRegKey, /*[in,optional,defaultvalue(NULL)]*/ VARIANT strComputername);
	STDMETHOD(LoadFromFile)(/*[in]*/ BSTR strFileName);
	STDMETHOD(SaveToFile)(/*[in]*/ BSTR strFile);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(_NewEnum)(/*[out,retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Find)(/*[in]*/ VARIANT Item,/*[out,retval]*/ IDispatch **ppCS );
	STDMETHOD(Remove)(/*[in]*/ VARIANT Item);
	STDMETHOD(Add)(/*[in]*/ VARIANT Item);
// CPersistStreamInit
	HRESULT	OnInitNew( );
	HRESULT LoadData( LPSTREAM pStm, DWORD dwVersion );
	HRESULT SaveData( LPSTREAM pStm, BOOL bClearDirty );
	DWORDLONG	GetDataSize( );

	DWORD	GetSignature( ) { char *s = "CSST"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return LASTKNOWN_CSSET_VERSION; }
};

#endif //__TRIASCSSET_H_
