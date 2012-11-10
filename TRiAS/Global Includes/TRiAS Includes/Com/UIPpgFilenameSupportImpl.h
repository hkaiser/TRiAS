#if !defined(_WIZARD_FNPPG_IMPL_H_8D00FD21_F032_11d2_9942_00AA002A873B)
#define _WIZARD_FNPPG_IMPL_H_8D00FD21_F032_11d2_9942_00AA002A873B

#include "com/ErrorMacros2.h"
#include "McKinney/OleType.h"
#include "Pragmas.h"
#pragma HDR_ON()

#ifdef _DEBUG
#undef THIS_FILE
#define	THIS_FILE	(__FILE__)
#endif

////////////////////////////////////////////////////////////////////////////////
// @doc TEMPLATE WIZARD CWizardSupportIml

struct WIZPPG_FNAME_DESCR {
	UINT		nIDFileFilter;
	UINT		nIDDescription;
};

#define BEGIN_WIZPPG_FILEFILTER_MAP(theClass) \
	static WIZPPG_FNAME_DESCR* GetFileFilterMap() { \
		static WIZPPG_FNAME_DESCR mmgrFFilters[] = {

#define	WIZPPG_FILEFILTER_ENTRY(entry,descr) \
	{entry, descr},

#define END_WIZPPG_FILEFILTER_MAP() \
	{ 0, 0 } \
		}; \
		return mmgrFFilters; \
	}

const long CUIPpgFilenameSupportImpl_VERSION = 0x0100L;
const long LASTKNOWN_CUIPpgFilenameSupportImpl_VERSION = CUIPpgFilenameSupportImpl_VERSION;

template<class T, const IID *pCLSID>
class ATL_NO_VTABLE CUIPpgFilenameSupportImpl
	: public IDispatchImpl<IUIPpgFilenamesSupport, &IID_IUIPpgFilenamesSupport>
	, public CErrSupport<T, &IID_IUIPpgFilenamesSupport>
{
protected:
	vector<CComBSTR>	m_vecOfFilenames;
	typedef CUIPpgFilenameSupportImpl<T,pCLSID>	CUIPpgFilenameSupportImpl_t;
public:
	BEGIN_COM_MAP(CUIPpgFilenameSupportImpl)
		COM_INTERFACE_ENTRY(IUIPpgFilenamesSupport)
	END_COM_MAP()
// IPpgFilenamesSupport
	STDMETHOD(get_FileFilters)(SAFEARRAY** psaFilters) {
		CHECKOUTPOINTER(psaFilters);
		COM_TRY {
			WIZPPG_FNAME_DESCR	*lpFilter = T::GetFileFilterMap();
			long	nEntry, nEntries;
			for( nEntries = 0; lpFilter->nIDFileFilter; ++lpFilter ) {
				++nEntries;
			}
			MC::ArrayCComBSTR	arr( MC::Dim( (const long) nEntries ) );
			lpFilter = T::GetFileFilterMap();
			for( nEntry = 0; lpFilter->nIDFileFilter; ++lpFilter, ++nEntry ) {
				CComBSTR	strFilter;
				strFilter.LoadString( _Module.GetResourceInstance(), lpFilter->nIDFileFilter );
				_ASSERTE( strFilter && strFilter.Length() );
				arr[ nEntry ] = strFilter;
			}
			*psaFilters = arr.Detach();
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_FileDescriptions)(SAFEARRAY** strDescriptions ) {
		CHECKOUTPOINTER(strDescriptions);
		COM_TRY {
			WIZPPG_FNAME_DESCR	*lpFilter = T::GetFileFilterMap();
			long	nEntry, nEntries = 0;
			for( ; lpFilter->nIDFileFilter; ++lpFilter ) {
				++nEntries;
			}
			MC::ArrayCComBSTR	arr( MC::Dim( (const long) nEntries ) );
			lpFilter = T::GetFileFilterMap();
			for( nEntry = 0; lpFilter->nIDFileFilter; ++lpFilter, ++nEntry ) {
				CComBSTR	strDescription;
				strDescription.LoadString( lpFilter->nIDDescription );
				_ASSERTE( strDescription && strDescription.Length() );
				arr[nEntry] = strDescription;
			}
			*strDescriptions = arr.Detach();
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(put_FileNames)(SAFEARRAY * strFilenames) {
		COM_TRY {
			m_vecOfFilenames.clear();
			MC::ArrayCComBSTR	arr(strFilenames);
			long	nEntry;
			for( nEntry = 0; nEntry < arr.Elements(); ++nEntry ) {
				m_vecOfFilenames.push_back(arr[nEntry]);
			}
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_FileNames)(SAFEARRAY * * strFilenames) {
		COM_TRY {
			MC::ArrayCComBSTR	arr(MC::Dim(m_vecOfFilenames.size()));
			long	nEntry;
			for( nEntry = 0; nEntry < m_vecOfFilenames.size(); ++nEntry ) {
				arr[nEntry] = m_vecOfFilenames[nEntry];
			}
			*strFilenames = arr.Detach();
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(ParseFileNames)(SAFEARRAY** strFilenames, LONG * pResult) {
		CHECKOUTPOINTER(pResult);
		return E_NOTIMPL;
	}
	HRESULT	InitNew( ) {
		m_vecOfFilenames.clear();
		return S_OK;
	}
	HRESULT LoadData( LPSTREAM pStream ) {
		DWORD	dwVersion = 0;
		DWORD	dwItems = 0;
		LoadItem( pStream, dwVersion );
		LoadItem( pStream, dwItems );
		for( DWORD dwItem = 0; dwItem != dwItems; ++dwItem ) {
			CComBSTR	strItem;
			LoadItem( pStream, strItem );
			m_vecOfFilenames.push_back( strItem );
		}
		return S_OK;
	}
	HRESULT SaveData( LPSTREAM pStream ) {
		DWORD	dwVersion = LASTKNOWN_CUIPpgFilenameSupportImpl_VERSION;
		DWORD	dwItems = m_vecOfFilenames.size();
		SaveItem( pStream, dwVersion );
		SaveItem( pStream, dwItems );
		for( vector<CComBSTR>::iterator i = m_vecOfFilenames.begin(); m_vecOfFilenames.end() != i; ++i ) {
			SaveItem( pStream, (*i) );
		}
		return S_OK;
	}
	LONGLONG GetSize( ) {
		ULARGE_INTEGER	uliSize, uliSum;
		uliSize.QuadPart = 0;
		uliSum.QuadPart = 0;
		for( vector<CComBSTR>::iterator i = m_vecOfFilenames.begin(); m_vecOfFilenames.end() != i; ++i ) {
			uliSum.QuadPart += SIZEOF( (*i) );
		}
		return uliSum.QuadPart;
	}
};

#undef THIS_FILE
#pragma HDR_OFF()

#endif // !_WIZARD_FNPPG_IMPL_H_8D00FD21_F032_11d2_9942_00AA002A873B
