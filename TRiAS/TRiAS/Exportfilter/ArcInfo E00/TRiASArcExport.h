// TRiASArcExport.h : Declaration of the CTRiASArcExport

#ifndef __TRIASARCEXPORT_H_
#define __TRIASARCEXPORT_H_

const long ASC_VERSION = 0x0100L;
const long LASTKNOWN_ASC_VERSION = ASC_VERSION;

/////////////////////////////////////////////////////////////////////////////
// CTRiASArcExport
class ATL_NO_VTABLE CTRiASArcExport
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CTRiASArcExport, &CLSID_TRiASArcExport>
	, public IDispatchImpl<ITRiASArcExport, &IID_ITRiASArcExport, &LIBID_TRiASArcExport>
	, public CErrSupport<CTRiASArcExport, &IID_ITRiASArcExport>
	, public CPersistStreamInitImpl<CTRiASArcExport, &CLSID_TRiASArcExport>
	, public CTRiASOEProxyImpl<CTRiASArcExport, &CLSID_TRiASArcExport>
{
	DECLARE_ERRSUPPORTENTRY(CTRiASArcExport, &IID_ITRiASArcExport);

	CComBSTR	m_strProjectName;
	int			m_nCoords;		// zur Dreiergruppenbildung
//	ofstream	m_os;
//	DOUBLEBUF	m_dblBuf;
public:
	CTRiASArcExport()
		: CTRiASOEProxyImpl_t( IDS_DISPLAYNAME, IDS_DEFEXT )
		, m_strProjectName(L"")
		, m_nCoords(0)
	{
	}
	HRESULT FinalConstruct() {
		COM_TRY {
			ERROR_FAILED_HRESULT( CExtDataEngineImpl_t_FinalConstruct(), E_FAIL );
//			CExtDataEngineImpl_t::put_SeparateOutput(TRUE);
		} COM_CATCH;
		CExtDataEngineImpl_t::put_SeparateDirs(TRUE);
		return S_OK;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASARCEXPORT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)

	BEGIN_COM_MAP(CTRiASArcExport)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
		COM_INTERFACE_ENTRY(ITRiASArcExport)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASArcExport)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASOEProxyImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CExtDataEngineImpl_t)
//		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CTRiASArcExport)
		IMPLEMENTED_CATEGORY(CATID_TRiASExportModule)
	END_CATEGORY_MAP( )

	BEGIN_EXTDATAENGINECAPABILITY_MAP(CTRiASArcExport)
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
		EXTDATAENGINECAPABILITY_ENTRY( L"*", TRUE )
	END_EXTDATAENGINECAPABILITY_MAP()

// ITRiASArcExport
public:
// ITRiASExtDataEngine
	STDMETHOD(ExportData)(IDispatch * pXMLDocument) {
		return E_NOTIMPL;
	}
	STDMETHOD(ImportData)(IDispatch * * ppXMLDocument) {
		return E_NOTIMPL;
	}
	STDMETHOD(put_SeparateDirs)(long bVal) {	// Dateien beim Splitten immer in separate Verzeichnisse
		m_bSeparateDirs = TRUE;
		return S_OK;
	}
// CPersistStreamInitImpl
	HRESULT	OnInitNew( );
	HRESULT LoadData( LPSTREAM pStm, DWORD dwVersion );
	HRESULT SaveData( LPSTREAM pStm, BOOL bClearDirty );
	LONGLONG GetDataSize( );
	DWORD	GetSignature( ) { char *s = "TASC"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return LASTKNOWN_ASC_VERSION; }
};

#endif //__TRIASARCEXPORT_H_
