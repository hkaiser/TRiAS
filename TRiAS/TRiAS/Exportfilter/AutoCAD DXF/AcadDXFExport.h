// AcadDXFExport.h : Declaration of the CAcadDXFExport

#ifndef __ACADDXFEXPORT_H_
#define __ACADDXFEXPORT_H_

const long DXF_VERSION = 0x0100L;
const long LASTKNOWN_DXF_VERSION = DXF_VERSION;

/////////////////////////////////////////////////////////////////////////////
// CAcadDXFExport
class ATL_NO_VTABLE CAcadDXFExport
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CAcadDXFExport, &CLSID_AcadDXFExport>
	, public IDispatchImpl<IAcadDXFExport, &IID_IAcadDXFExport, &LIBID_AcadDXFExport>
	, public CErrSupport<CAcadDXFExport, &IID_IAcadDXFExport>
	, public CPersistStreamInitImpl<CAcadDXFExport, &CLSID_AcadDXFExport>
	, public CTRiASOEProxyImpl<CAcadDXFExport, &CLSID_AcadDXFExport>
{
	DECLARE_ERRSUPPORTENTRY(CAcadDXFExport, &IID_IAcadDXFExport);
public:
	CAcadDXFExport()
		: CTRiASOEProxyImpl_t( IDS_DISPLAYNAME, IDS_DEFEXT )
	{
	}
	HRESULT FinalConstruct() {
		COM_TRY {
			ERROR_FAILED_HRESULT( CExtDataEngineImpl_t_FinalConstruct(), E_FAIL );
			CExtDataEngineImpl_t::put_SeparateOutput(TRUE);
		} COM_CATCH;
		return S_OK;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ACADDXFEXPORT)
	DECLARE_NOT_AGGREGATABLE(CAcadDXFExport)
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CAcadDXFExport)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
		COM_INTERFACE_ENTRY(IAcadDXFExport)
		COM_INTERFACE_ENTRY2(IDispatch, IAcadDXFExport)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASOEProxyImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CExtDataEngineImpl_t)
//		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CAcadDXFExport)
		IMPLEMENTED_CATEGORY(CATID_TRiASExportModule)
	END_CATEGORY_MAP( )

	BEGIN_EXTDATAENGINECAPABILITY_MAP(CAcadDXFExport)
		EXTDATAENGINECAPABILITY_ENTRY( L"CanExportStandalone", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY( L"CanSpecifyTransformation", FALSE )
// KK000817 - mal rein
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSeparateOutput", TRUE )

//		EXTDATAENGINECAPABILITY_ENTRY( L"MustSeparateOutput", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY( L"NeedRawCoordinates", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY( L"EC_StandardMerkmale", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY( L"EC_MerkmalDescription", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY( L"EC_IdentDescription", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY( L"EC_Relationen", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"OutputIsDirectory", FALSE)
// Kk000817
		EXTDATAENGINECAPABILITY_ENTRY( L"*", FALSE )
//		EXTDATAENGINECAPABILITY_ENTRY( L"*", TRUE )
	END_EXTDATAENGINECAPABILITY_MAP()

// IAcadDXFExport
public:

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
	DWORD	GetSignature( ) { char *s = "TDXF"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return LASTKNOWN_DXF_VERSION; }
};

#endif //__ACADDXFEXPORT_H_
