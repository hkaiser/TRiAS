// PolygisPMFExport.h : Declaration of the CPolygisPMFExport

#ifndef __POLYGISPMFEXPORT_H_
#define __POLYGISPMFEXPORT_H_

const long PMF_VERSION = 0x0100L;
const long LASTKNOWN_PMF_VERSION = PMF_VERSION;

/////////////////////////////////////////////////////////////////////////////
// CPOLYGISPMFExport

class ATL_NO_VTABLE CPolygisPMFExport
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CPolygisPMFExport, &CLSID_PolygisPMFExport>
	, public IDispatchImpl<IPolygisPMFExport, &IID_IPolygisPMFExport, &LIBID_PolygisPMFExport>
	, public CErrSupport<CPolygisPMFExport, &IID_IPolygisPMFExport>
	, public CPersistStreamInitImpl<CPolygisPMFExport, &CLSID_PolygisPMFExport>
	, public CTRiASOEProxyImpl<CPolygisPMFExport, &CLSID_PolygisPMFExport>
{
	DECLARE_ERRSUPPORTENTRY(CPolygisPMFExport, &IID_IPolygisPMFExport);
public:
	CPolygisPMFExport()
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

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)

	BEGIN_COM_MAP(CPolygisPMFExport)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
		COM_INTERFACE_ENTRY(IPolygisPMFExport)
		COM_INTERFACE_ENTRY2(IDispatch, IPolygisPMFExport)
		COM_INTERFACE_ENTRY_CHAIN(CExtDataEngineImpl_t)
//		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASOEProxyImpl_t)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CPolygisPMFExport)
		IMPLEMENTED_CATEGORY(CATID_TRiASExportModule)
	END_CATEGORY_MAP( )

	BEGIN_EXTDATAENGINECAPABILITY_MAP(CPolygisPMFExport)
		EXTDATAENGINECAPABILITY_ENTRY(L"CanExportStandalone", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSpecifyTransformation", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSeparateOutput", TRUE )
//		EXTDATAENGINECAPABILITY_ENTRY(L"NeedRawCoordinates", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"NeedRawCoordinates", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"OutputIsDirectory", FALSE)
//		EXTDATAENGINECAPABILITY_ENTRY(L"EC_StandardMerkmale", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_StandardMerkmale", FALSE )
//		EXTDATAENGINECAPABILITY_ENTRY(L"EC_MerkmalDescription", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_MerkmalDescription", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_IdentDescription", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_Relationen", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"*", FALSE )
	END_EXTDATAENGINECAPABILITY_MAP()

//	DECLARE_REGISTRY_RESOURCEID(IDR_POLYGISPMFEXPORT)
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

// IPolygisPMFExport
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
	DWORD	GetVersion( ) { return LASTKNOWN_PMF_VERSION; }
};

#endif //__PolygisPMFEXPORT_H_
