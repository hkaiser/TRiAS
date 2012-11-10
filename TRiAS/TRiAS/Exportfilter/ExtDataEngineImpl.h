#if !defined(_EXPORTDEF_IMPL_H_12134160_11D5_11d3_996A_0060085FC1CE)
#define _EXPORTDEF_IMPL_H_12134160_11D5_11d3_996A_0060085FC1CE

//////////////////////////////////////////////////////////////////////
// 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Pragmas.h>
#pragma	HDR_ON()

#include <TrCatIDs.h>		// CATID_TRiASExportModule

#pragma warning(disable: 4192)	//automatically excluding 'I...' while importing type library '...'

#import "TRiASCS.tlb"	\
	raw_interfaces_only		\
	, raw_native_types		\
	, no_namespace			\
	, named_guids 

DefineSmartInterface(TRiASCS)

#import "ExportDef.tlb" \
	raw_interfaces_only		\
	, raw_native_types		\
	, no_namespace			\
	, named_guids 

#ifdef _DEBUG
#undef THIS_FILE
#define	THIS_FILE	(__FILE__)
#endif

struct EXTDATAENGINECAPABILITY {
	LPCOLESTR	lpszCap;
	BOOL		bCap;
};

#define BEGIN_EXTDATAENGINECAPABILITY_MAP(theClass) \
	static EXTDATAENGINECAPABILITY* GetCapabilityMap() { \
		static EXTDATAENGINECAPABILITY edeCaps[] = {

#define	EXTDATAENGINECAPABILITY_ENTRY(entry,cap) \
	{entry,cap},

#define END_EXTDATAENGINECAPABILITY_MAP() \
	{ NULL, FALSE} \
		}; \
		return edeCaps; \
	}

const long CExtDataEngineImpl_VERSION_100 = 0x0100L;
const long CExtDataEngineImpl_VERSION_101 = 0x0101L;
const long LASTKNOWN_CExtDataEngineImpl_VERSION = CExtDataEngineImpl_VERSION_101;

template<class T, const IID *pCLSID>
class ATL_NO_VTABLE CExtDataEngineImpl
	: public IDispatchImpl<ITRiASExtDataEngine, &IID_ITRiASExtDataEngine, &LIBID_EXPORTDEFLib>
	, public CErrSupport<T, &IID_ITRiASExtDataEngine>
{
private:
	UINT		m_iNameID;		// Ressource-ID für Anzeigename
	UINT		m_iExtID;		// Ressource-ID für Default-Extension
	WTRiASCS	m_pTRiASCS;		// Koordinatensystem für Ausgabe

protected:
	CComBSTR	m_strFilename;	// Dateiname für Ausgabedatei
	long		m_bSeparate;	// Ausgabe separieren?
	long		m_bSeparateDirs;	// Separation in einzelne Verzeichnisse?
	long		m_bAppend;		// Ausgabe an vorhandene Datei anhängen?
	long		m_bSelect;		// Ausgabe Objekte aus selektierten Bereich?
	long		m_bExportObjProps;	// COM-Objekteigenschaften ausgeben

public:
	typedef CExtDataEngineImpl CExtDataEngineImpl_t;
	CExtDataEngineImpl( UINT iNameID, UINT iExtID )
		: m_iNameID( iNameID )
		, m_iExtID( iExtID )
		, m_strFilename(L"")
		, m_bSeparate(FALSE)
		, m_bSelect(FALSE)
		, m_bSeparateDirs(FALSE)
		, m_bAppend(FALSE)
		, m_bExportObjProps(FALSE)
	{}
	HRESULT CExtDataEngineImpl_t_FinalConstruct() {
		WUnknown	pUnknown;
		RETURN_FAILED_HRESULT( ::CoCreateInstance( CLSID_TRIASCS, NULL, CLSCTX_ALL, pUnknown.GetIID(), pUnknown.ppv() ) );
		RETURN_FAILED_HRESULT( pUnknown->QueryInterface( m_pTRiASCS.GetIID(), m_pTRiASCS.ppv() ) );
		return S_OK;
	}

	BEGIN_COM_MAP(CExtDataEngineImpl)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
	END_COM_MAP()

	STDMETHOD(get_Name)(BSTR * pbstrName) {
		CComBSTR	strDisplayname;
		strDisplayname.LoadString(IDS_DISPLAYNAME);
		*pbstrName = strDisplayname.Detach();
		return S_OK;
	}
	STDMETHOD(get_Extension)(BSTR * pbstrDefExt) {
		CComBSTR	strDefExt;
		strDefExt.LoadString(IDS_DEFEXT);
		*pbstrDefExt = strDefExt.Detach();
		return S_OK;
	}
	STDMETHOD(get_Filename)(BSTR * pVal) {
		CHECKOUTPOINTER(pVal);
		*pVal = ::SysAllocString( m_strFilename );
		return S_OK;
	}
	STDMETHOD(put_Filename)(BSTR pVal) {
		m_strFilename = pVal;
		return S_OK;
	}
	STDMETHOD(get_CoordSystem)(IDispatch * * pVal) {
		COM_TRY {
			CHECKOUTPOINTER(pVal);
			WTRiASCS	pTRiASCS(m_pTRiASCS);
			*pVal = pTRiASCS.Detach();
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(put_CoordSystem)(IDispatch * pVal) {
		COM_TRY {
			WTRiASCS	pTRiASCS;
			ERROR_FAILED_HRESULT( pVal->QueryInterface( pTRiASCS.GetIID(), pTRiASCS.ppv() ), E_FAIL );
			m_pTRiASCS = pTRiASCS;
		} COM_CATCH;
		return S_OK;
	}
// KK000816
	STDMETHOD(get_SelectOutput)(long* pbVal) {
		CHECKOUTPOINTER(pbVal);
		*pbVal = m_bSelect;
		return S_OK;
	}
	STDMETHOD(put_SelectOutput)(long bVal) {
		m_bSelect = bVal;
		return S_OK;
	}

	STDMETHOD(get_SeparateOutput)(long* pbVal) {
		CHECKOUTPOINTER(pbVal);
		*pbVal = m_bSeparate;
		return S_OK;
	}
	STDMETHOD(put_SeparateOutput)(long bVal) {
		m_bSeparate = bVal;
		return S_OK;
	}
	STDMETHOD(get_SeparateDirs)(long* pbVal) {
		CHECKOUTPOINTER(pbVal);
		*pbVal = m_bSeparateDirs;
		return S_OK;
	}
	STDMETHOD(put_SeparateDirs)(long bVal) {
		m_bSeparateDirs = bVal;
		return S_OK;
	}
	STDMETHOD(get_AppendOutput)(long* pbVal) {
		CHECKOUTPOINTER(pbVal);
		*pbVal = m_bAppend;
		return S_OK;
	}
	STDMETHOD(put_AppendOutput)(long bVal) {
		m_bAppend = bVal;
		return S_OK;
	}
	STDMETHOD(get_Capability)(BSTR strCapability, long* pbYesNo ) {
		CHECKOUTPOINTER(pbYesNo);
		*pbYesNo = FALSE;
		COM_TRY {
			EXTDATAENGINECAPABILITY	*lpCaps = T::GetCapabilityMap();
			for( ; lpCaps->lpszCap; ++lpCaps ) {
				if( 0 == wcsicmp( L"*", lpCaps->lpszCap ) ) {
					*pbYesNo = lpCaps->bCap;
					break;
				}
				if( 0 == wcsicmp( strCapability, lpCaps->lpszCap ) ) {
					*pbYesNo = lpCaps->bCap;
					break;
				}
			}
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(get_ExportObjProps)(long* pbVal) {
		CHECKOUTPOINTER(pbVal);
		*pbVal = m_bExportObjProps;
		return S_OK;
	}
	STDMETHOD(put_ExportObjProps)(long bVal) {
		m_bExportObjProps = bVal;
		return S_OK;
	}
/////////////////////////////////////////////////////////////////////////
// die folgenden drei Funktionen *müssen* implementiert werden!!
//	STDMETHOD(ExportData)(IDispatch * pXMLDocument) {
//		return E_NOTIMPL;
//	}
//	STDMETHOD(ImportData)(IDispatch * * ppXMLDocument) {
//		return E_NOTIMPL;
//	}
// CPersistStreamInitImpl
	HRESULT	OnInitNew( ) {
		m_bSeparate = FALSE;
		m_bSeparateDirs = FALSE;
		m_bAppend = FALSE;
		m_bSelect = FALSE;
		m_bExportObjProps = FALSE;
		m_strFilename = L"";
		WPersistStreamInit(m_pTRiASCS)->InitNew();
		return S_OK;
	}
	HRESULT LoadData( LPSTREAM pStm ) {
		DWORD	dwVersion;
		LoadItem(pStm, dwVersion);
		LoadItem(pStm, m_strFilename);
		LoadItem(pStm, m_bSeparate);
		LoadItem(pStm, m_bAppend);
		if (dwVersion > CExtDataEngineImpl_VERSION_100) {
			LoadItem(pStm, m_bSeparateDirs);
			LoadItem(pStm, m_bExportObjProps);
		}
		LoadObject(pStm, m_pTRiASCS.ppu());
		return S_OK;
	}
	HRESULT SaveData( LPSTREAM pStm, BOOL bClearDirty ) {
		DWORD	dwVersion = LASTKNOWN_CExtDataEngineImpl_VERSION;
		SaveItem(pStm, dwVersion);
		SaveItem(pStm, m_strFilename);
		SaveItem(pStm, m_bSeparate);
		SaveItem(pStm, m_bAppend);
		SaveItem(pStm, m_bSeparateDirs);
		SaveItem(pStm, m_bExportObjProps);
		SaveObject(pStm, m_pTRiASCS, bClearDirty);
		return S_OK;
	}
	LONGLONG GetDataSize( ) {
		ULARGE_INTEGER	uliSize, uliSum;
		uliSize.QuadPart = 0;
		uliSum.QuadPart = 0;
		uliSize.QuadPart += sizeof(DWORD);	// Version
		uliSize.QuadPart += SIZEOF(m_strFilename);
		uliSize.QuadPart += sizeof(m_bSeparate);
		uliSize.QuadPart += sizeof(m_bAppend);
		uliSize.QuadPart += sizeof(m_bSeparateDirs);
		uliSize.QuadPart += sizeof(m_bExportObjProps);
		uliSum.QuadPart += uliSize.QuadPart;
		WPersistStreamInit(m_pTRiASCS)->GetSizeMax( &uliSize );
		uliSum.QuadPart += uliSize.QuadPart;
		return uliSum.QuadPart;
	}
};

///////////////////////////////////////////////////////////////////////////////
// LizensierungsHelper für Classfactory
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

BOOL GetLicenseKey (LPWSTR pwKey, size_t iLen);
BOOL GetLicensed (void);
BOOL SetLicensed (LPCSTR lpNewKey);

class CVerifyExportLicense 
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR strKey;

		USES_CONVERSION;
		if ((GetLicenseKey(0, &strKey) && 0 == wcscmp (strKey, bstr)) || ::SetLicensed (OLE2A(bstr))) 
		{
			return TRUE;
		}
		return FALSE;
	}
	static BOOL GetLicenseKey (DWORD, BSTR *pBstr)
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;
			
		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}
	static BOOL IsLicenseValid()
	{
		return g_fGlobalLic || ::GetLicensed(); 
	}
};

#pragma	HDR_OFF()

#endif // _EXPORTDEF_IMPL_H_12134160_11D5_11d3_996A_0060085FC1CE
