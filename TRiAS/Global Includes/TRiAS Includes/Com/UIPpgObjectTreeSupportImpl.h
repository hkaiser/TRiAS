#if !defined(_WIZARD_OBJTREEPPG_IMPL_H_B79DA890_2AEE_11d3_998B_0060085FC1CE)
#define _WIZARD_OBJTREEPPG_IMPL_H_B79DA890_2AEE_11d3_998B_0060085FC1CE

#include "com/ErrorMacros2.h"
#include "Pragmas.h"
#pragma HDR_ON()

#ifdef _DEBUG
#undef THIS_FILE
#define	THIS_FILE	(__FILE__)
#endif

const long CUIPpgObjectTreeSupportImpl_VERSION = 0x0100L;
const long LASTKNOWN_CUIPpgObjectTreeSupportImpl_VERSION = CUIPpgObjectTreeSupportImpl_VERSION;

template<class T, const IID *pCLSID>
class ATL_NO_VTABLE CUIPpgObjectTreeSupportImpl
	: public IDispatchImpl<IUIPpgObjectTreeSupport, &IID_IUIPpgObjectTreeSupport>
	, public CErrSupport<T, &IID_IUIPpgObjectTreeSupport>
{
	list<CComVariant>	m_listOfObjects;
	CComVariant			m_vCurrentObject;
	typedef CComObject<CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, list<CComVariant> > > CComEnumVARIANT;
	HRESULT LoadCategory( const CATID *rclsid ) {
		CATID	catIDs[1];
		catIDs[0] = *rclsid;
		CComPtr<ICatInformation>	pCatInformation;
		CComPtr<IEnumCLSID>			pEnumCLSID;
		RETURN_FAILED_HRESULT( pCatInformation.CoCreateInstance( CLSID_StdComponentCategoriesMgr ) );
		RETURN_FAILED_HRESULT( pCatInformation->EnumClassesOfCategories( 1, catIDs, 0, NULL, &pEnumCLSID ) );
		CLSID	clsid(CLSID_NULL);
		ULONG	ulFetched;
		long	lCount = 0;

		for( pEnumCLSID->Reset(); S_OK == pEnumCLSID->Next( 1, &clsid, &ulFetched ); ++lCount ) {
			CComPtr<IUnknown>			pUnknown;
			if( FAILED( pUnknown.CoCreateInstance( clsid ) ) )
				continue;
			m_listOfObjects.push_back( CComVariant(pUnknown) );
		}
		return lCount > 0 ? S_OK : E_FAIL;
	}
public:
	typedef CUIPpgObjectTreeSupportImpl<T,pCLSID>	CUIPpgObjectTreeSupportImpl_t;

	BEGIN_COM_MAP(CUIPpgObjectTreeSupportImpl)
		COM_INTERFACE_ENTRY(IUIPpgObjectTreeSupport)
	END_COM_MAP()

	HRESULT FinalConstruct() {
		const _ATL_CATMAP_ENTRY* pCategories = T::GetCategoryMap();
		for( ; pCategories->iType; ++pCategories ) {
			if( _ATL_CATMAP_ENTRY_REQUIRED != pCategories->iType )
				continue;
			return LoadCategory( pCategories->pcatid );		// nur eine Kategorie erlaubt
		}
		return E_FAIL;			// keine Kategorie gefunden
	}

	STDMETHOD(_NewEnum)(/*[out,retval]*/ IUnknown **ppIEnum) {
		CComEnumVARIANT	*pEnum = NULL;
		ERROR_FAILED_HRESULT( CComEnumVARIANT::CreateInstance( &pEnum ), E_OUTOFMEMORY );		// AddRef ist noch 0
		ERROR_FAILED_HRESULT( pEnum->Init( GetUnknown(), m_listOfObjects ), E_FAIL );
		ERROR_FAILED_HRESULT( pEnum->QueryInterface( IID_IUnknown, reinterpret_cast<void**>(ppIEnum) ), E_NOINTERFACE );
		return S_OK;
	}
	STDMETHOD(get_CurrentObject)(/*[out, retval]*/ VARIANT *pVal) {
		CComVariant	vCurrentObject( m_vCurrentObject );
		vCurrentObject.Detach( pVal );
		return S_OK;
	}
	STDMETHOD(put_CurrentObject)(/*[in]*/ VARIANT newVal) {
		m_vCurrentObject = newVal;
		return S_OK;
	}
	STDMETHOD(get_DisplayStringOfObject)( /*[in]*/ VARIANT vObject, /*[out,retval]*/ BSTR *strDisplayString ) {
		return E_NOTIMPL;
	}
	STDMETHOD(CompareObjects)( VARIANT vObject1, VARIANT vObject2 ) {
		if( V_VT(&vObject1) != V_VT(&vObject1) ) {
			return E_INVALIDARG;
		} else if( V_ISBSTR(&vObject1) ) {
			return 0 == wcsicmp( V_BSTR(&vObject1), V_BSTR(&vObject2) ) ? S_OK : S_FALSE;
		} else if( V_ISUNKNOWN(&vObject1) ) {
			return V_UNKNOWN(&vObject1) == V_UNKNOWN(&vObject2) ? S_OK : S_FALSE;
		} else if( V_ISDISPATCH(&vObject1) ) {
			return V_DISPATCH(&vObject1) == V_DISPATCH(&vObject2) ? S_OK : S_FALSE;
		}
		return S_OK;
	}
	HRESULT	InitNew( ) {
		m_listOfObjects.clear();
		return S_OK;
	}
	HRESULT LoadData( LPSTREAM pStream ) {
		DWORD	dwVersion = 0;
		LoadItem( pStream, dwVersion );
		LoadItem( pStream, m_vCurrentObject );
		return S_OK;
	}
	HRESULT SaveData( LPSTREAM pStream ) {
		DWORD	dwVersion = LASTKNOWN_CUIPpgObjectTreeSupportImpl_VERSION;
		SaveItem( pStream, dwVersion );
		SaveItem( pStream, m_vCurrentObject );
		return S_OK;
	}
	LONGLONG GetSize( ) {
		ULARGE_INTEGER	uliSize, uliSum;
		uliSize.QuadPart = 0;
		uliSum.QuadPart = 0;
		uliSum.QuadPart += SIZEOF( m_vCurrentObject );
		return uliSum.QuadPart;
	}
};

#undef THIS_FILE

#pragma HDR_OFF()

#endif
