// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.11.2000 09:03:13 
//
// @doc
// @module DirisASCExport.h | Declaration of the <c CDirisASCExport> class

#ifndef __DIRISASCEXPORT_H_
#define __DIRISASCEXPORT_H_

const long ASC_VERSION = 0x0100L;
const long LASTKNOWN_ASC_VERSION = ASC_VERSION;

/////////////////////////////////////////////////////////////////////////////
// CDirisASCExport
class ATL_NO_VTABLE CDirisASCExport
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CDirisASCExport, &CLSID_DirisASCExport>
	, public IDispatchImpl<IDirisASCExport, &IID_IDirisASCExport, &LIBID_DirisASCExport>
	, public CErrSupport<CDirisASCExport, &IID_IDirisASCExport>
	, public CPersistStreamInitImpl<CDirisASCExport, &CLSID_DirisASCExport>
	, public CTRiASOEProxyImpl<CDirisASCExport, &CLSID_DirisASCExport>
{
	DECLARE_ERRSUPPORTENTRY(CDirisASCExport, &IID_IDirisASCExport);

	CComBSTR	m_strProjectName;
	int			m_nCoords;		// zur Dreiergruppenbildung
public:
	CDirisASCExport()
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
		return S_OK;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_DIRISASCEXPORT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)

	BEGIN_COM_MAP(CDirisASCExport)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
		COM_INTERFACE_ENTRY(IDirisASCExport)
		COM_INTERFACE_ENTRY2(IDispatch, IDirisASCExport)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASOEProxyImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CExtDataEngineImpl_t)
//		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CDirisASCExport)
		IMPLEMENTED_CATEGORY(CATID_TRiASExportModule)
	END_CATEGORY_MAP( )

	BEGIN_EXTDATAENGINECAPABILITY_MAP(CDirisASCExport)
		EXTDATAENGINECAPABILITY_ENTRY(L"CanExportStandalone", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSpecifyTransformation", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"NeedRawCoordinates", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"OutputIsDirectory", FALSE)
// KK000817 - mal rein
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSeparateOutput", TRUE )

		EXTDATAENGINECAPABILITY_ENTRY(L"EC_StandardMerkmale", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_MerkmalDescription", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_IdentDescription", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_Relationen", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"*", TRUE )
	END_EXTDATAENGINECAPABILITY_MAP()

// IDirisASCExport
public:
// ITRiASExtDataEngine
	STDMETHOD(ExportData)(IDispatch * pXMLDocument) {
		return E_NOTIMPL;
	}
	STDMETHOD(ImportData)(IDispatch * * ppXMLDocument) {
		return E_NOTIMPL;
	}
//	STDMETHOD(put_SeparateOutput)(long bVal) {	// Dateien immer Splitten
//		CExtDataEngineImpl_t::put_SeparateOutput(TRUE);
//		return S_OK;
//	}

//  CPersistStreamInitImpl
	HRESULT	OnInitNew( );
	HRESULT LoadData( LPSTREAM pStm, DWORD dwVersion );
	HRESULT SaveData( LPSTREAM pStm, BOOL bClearDirty );
	LONGLONG GetDataSize( );
	DWORD	GetSignature( ) { char *s = "TASC"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return LASTKNOWN_ASC_VERSION; }
};
// IXMLDocument

#endif //__DIRISASCEXPORT_H_
