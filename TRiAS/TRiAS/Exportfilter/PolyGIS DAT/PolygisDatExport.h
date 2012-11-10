// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.11.2000 09:03:13 
//
// @doc
// @module CpolygisDatExport.h | Declaration of the <c CPolygisDatExport> class

#ifndef __POLYGISDATEXPORT_H_
#define __POLYGISDATEXPORT_H_

const long ASC_VERSION = 0x0100L;
const long LASTKNOWN_ASC_VERSION = ASC_VERSION;

/////////////////////////////////////////////////////////////////////////////
// CPolygisDatExport
class ATL_NO_VTABLE CPolygisDatExport
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CPolygisDatExport, &CLSID_PolygisDAT>
	, public IDispatchImpl<IPolygisDatExport, &IID_IPolygisDatExport, &LIBID_PolygisDAT>
	, public CErrSupport<CPolygisDatExport, &IID_IPolygisDatExport>
	, public CPersistStreamInitImpl<CPolygisDatExport, &CLSID_PolygisDAT>
	, public CTRiASOEProxyImpl<CPolygisDatExport, &CLSID_PolygisDAT>
{
	DECLARE_ERRSUPPORTENTRY(CPolygisDatExport, &IID_IPolygisDatExport);

	CComBSTR	m_strProjectName;
	int			m_nCoords;		// zur Dreiergruppenbildung
public:
	CPolygisDatExport()
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

	DECLARE_REGISTRY_RESOURCEID(IDR_POLYGISDATEXPORT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)

	BEGIN_COM_MAP(CPolygisDatExport)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
		COM_INTERFACE_ENTRY(IPolygisDatExport)
		COM_INTERFACE_ENTRY2(IDispatch, IPolygisDatExport)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASOEProxyImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CExtDataEngineImpl_t)
//		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CPolygisDatExport)
		IMPLEMENTED_CATEGORY(CATID_TRiASExportModule)
	END_CATEGORY_MAP( )

	BEGIN_EXTDATAENGINECAPABILITY_MAP(CPolygisDatExport)
		EXTDATAENGINECAPABILITY_ENTRY(L"CanExportStandalone", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSpecifyTransformation", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"NeedRawCoordinates", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"OutputIsDirectory", FALSE)
// KK000817 - mal rein
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSeparateOutput", TRUE )

		EXTDATAENGINECAPABILITY_ENTRY(L"EC_StandardMerkmale", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_MerkmalDescription", TRUE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_IdentDescription", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_Relationen", FALSE )
		EXTDATAENGINECAPABILITY_ENTRY(L"*", TRUE )
	END_EXTDATAENGINECAPABILITY_MAP()

// IPolygisDatExport
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

#endif //__POLYGISDATEXPORT_H_
