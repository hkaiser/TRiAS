// AtlasBNAExport.h : Declaration of the CAtlasBNAExport

#ifndef __ATLASBNAEXPORT_H_
#define __ATLASBNAEXPORT_H_

const long BNA_VERSION = 0x0100L;
const long LASTKNOWN_BNA_VERSION = BNA_VERSION;

/////////////////////////////////////////////////////////////////////////////
// CAtlasBNAExport

class ATL_NO_VTABLE CAtlasBNAExport
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CAtlasBNAExport, &CLSID_AtlasBNAExport>
	, public IDispatchImpl<IAtlasBNAExport, &IID_IAtlasBNAExport, &LIBID_AtlasBNAExport>
	, public CErrSupport<CAtlasBNAExport, &IID_IAtlasBNAExport>
	, public CPersistStreamInitImpl<CAtlasBNAExport, &CLSID_AtlasBNAExport>
	, public CTRiASOEProxyImpl<CAtlasBNAExport, &CLSID_AtlasBNAExport>
{
	DECLARE_ERRSUPPORTENTRY(CAtlasBNAExport, &IID_IAtlasBNAExport);
public:
	CAtlasBNAExport()
		: CTRiASOEProxyImpl_t( IDS_DISPLAYNAME, IDS_DEFEXT )
	{
	}
	HRESULT FinalConstruct() {
		COM_TRY {
			ERROR_FAILED_HRESULT( CExtDataEngineImpl_t_FinalConstruct(), E_FAIL );
//			CExtDataEngineImpl_t::put_SeparateOutput(TRUE);
		} COM_CATCH;
		return S_OK;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ATLASBNAEXPORT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)

	BEGIN_COM_MAP(CAtlasBNAExport)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
		COM_INTERFACE_ENTRY(IAtlasBNAExport)
		COM_INTERFACE_ENTRY2(IDispatch, IAtlasBNAExport)
		COM_INTERFACE_ENTRY_CHAIN(CExtDataEngineImpl_t)
//		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASOEProxyImpl_t)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CAtlasBNAExport)
		IMPLEMENTED_CATEGORY(CATID_TRiASExportModule)
	END_CATEGORY_MAP( )

	BEGIN_EXTDATAENGINECAPABILITY_MAP(CAtlasBNAExport)
		EXTDATAENGINECAPABILITY_ENTRY(L"CanExportStandalone", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSpecifyTransformation", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSeparateOutput", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"NeedRawCoordinates", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"OutputIsDirectory", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_StandardMerkmale", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_MerkmalDescription", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_IdentDescription", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_Relationen", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"*", FALSE )
	END_EXTDATAENGINECAPABILITY_MAP()

// IAtlasBNAExport
public:
// ITRiASExtDataEngine
	STDMETHOD(ExportData)(IDispatch * pXMLDocument) {
		return E_NOTIMPL;
	}
	STDMETHOD(ImportData)(IDispatch * * ppXMLDocument) {
		return E_NOTIMPL;
	}
// CPersistStreamInitImpl
	HRESULT	OnInitNew( );
	HRESULT LoadData( LPSTREAM pStm, DWORD dwVersion );
	HRESULT SaveData( LPSTREAM pStm, BOOL bClearDirty );
	LONGLONG GetDataSize( );
	DWORD	GetSignature( ) { char *s = "ABNA"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return LASTKNOWN_BNA_VERSION; }
};

#endif //__ATLASBNAEXPORT_H_
