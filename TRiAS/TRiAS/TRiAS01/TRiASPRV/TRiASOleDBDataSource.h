// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.05.2001 11:44:39 
//
// @doc
// @module TRiASOleDBDataSource.h | Declaration of the <c CTRiASOleDBSource> class

#if !defined(_TRIASOLEDBDATASOURCE_H__DF1EB105_282E_4D0B_A388_4471476FBC96__INCLUDED_)
#define _TRIASOLEDBDATASOURCE_H__DF1EB105_282E_4D0B_A388_4471476FBC96__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/ComBool.h>
#include <Atl/CieThis.h>
#include <Atl/OleDb/IDBDataSourceAdminImpl.h>

#include <TRiASOleDB.h>

#include "resource.h"       // main symbols

#include "Strings.h"
#include "TRiASOleDBRowSet.h"
#include "TRiASOleDBCommand.h"
#include "TRiASOleDBSession.h"

///////////////////////////////////////////////////////////////////////////////
// helper macros für ATL PropertyMaps
#define TRiAS_GEOMETRYTYPE_Type		VT_I4
#define TRiAS_GEOMETRYTYPE_Flags	(DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE)
#define TRiAS_GEOMETRYTYPE_Value	DBPROPVAL_TRiAS_GEOMETRYTABLES

#define TRiAS_GENERATEVIEWS_Type	VT_BOOL
#define TRiAS_GENERATEVIEWS_Flags	(DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE)
#define TRiAS_GENERATEVIEWS_Value	VARIANT_TRUE

#define TRiAS_CREATE_COMPATIBLE_Type	VT_BOOL
#define TRiAS_CREATE_COMPATIBLE_Flags	(DBPROPFLAGS_DATASOURCECREATE | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE)
#define TRiAS_CREATE_COMPATIBLE_Value	VARIANT_FALSE

#define TRiAS_CREATE_COMPRESSED_Type	VT_BOOL
#define TRiAS_CREATE_COMPRESSED_Flags	(DBPROPFLAGS_DATASOURCECREATE | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE)
#define TRiAS_CREATE_COMPRESSED_Value	VARIANT_TRUE

#define TRiAS_DBVERSION_Type		VT_BSTR
#define TRiAS_DBVERSION_Flags		(DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_CHANGE)
#define TRiAS_DBVERSION_Value		OLESTR("")

/////////////////////////////////////////////////////////////////////////////
// CDataSource
class CTRiASOleDBSession;

class ATL_NO_VTABLE CTRiASOleDBSource : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASOleDBSource, &CLSID_TRiASOleDB>,
	public IDBCreateSessionImpl<CTRiASOleDBSource, CTRiASOleDBSession>,
	public IDBInitializeImpl<CTRiASOleDBSource>,
	public IDBPropertiesImpl<CTRiASOleDBSource>,
	public IPersistImpl<CTRiASOleDBSource>,
	public IInternalConnectionImpl<CTRiASOleDBSource>,
	public IDBInfoImpl<CTRiASOleDBSource>,
	public IDBDataSourceAdminImpl<CTRiASOleDBSource, &DBPROPSET_TRiAS_INITDATASOURCE, &DBPROPSET_TRiAS_CREATEDATASOURCE>,
	public CTRiASOleDBErrorBase<CTRiASOleDBSource, &IID_IDBInitialize>,
	public ISupportErrorInfo
{
public:
	CTRiASOleDBSource() :
		m_hPr(NULL), m_dwGeomType(0), m_fViewMode(true)
	{
	}

	HRESULT FinalConstruct()
	{
		return FInit();
	}
	void FinalRelease()
	{
		EnsureDatasourceClosed();
		m_GeoDBService.Release();
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOLEDB)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASOleDBSource)

	BEGIN_PROPSET_MAP(CTRiASOleDBSource)
		BEGIN_PROPERTY_SET(DBPROPSET_DATASOURCEINFO)
			PROPERTY_INFO_ENTRY_VALUE(ACTIVESESSIONS, 0)
			PROPERTY_INFO_ENTRY_VALUE(ALTERCOLUMN, DBCOLUMNDESCFLAGS_DBCID)
			PROPERTY_INFO_ENTRY_VALUE(BYREFACCESSORS, VARIANT_FALSE)
			PROPERTY_INFO_ENTRY_VALUE(CONCATNULLBEHAVIOR, DBPROPVAL_CB_NON_NULL)
			PROPERTY_INFO_ENTRY_EX(DATASOURCENAME, VT_BSTR, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_CHANGE | DBPROPFLAGS_REQUIRED, OLESTR(""), 0)
			PROPERTY_INFO_ENTRY_EX(DATASOURCEREADONLY, VT_BOOL, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_CHANGE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(DATASOURCE_TYPE, VT_I4, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ, DBPROPVAL_DST_TDP, 0)
			PROPERTY_INFO_ENTRY_VALUE(DBMSNAME, g_cbTRiAS)
			PROPERTY_INFO_ENTRY_EX(DBMSVER, VT_BSTR, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_CHANGE | DBPROPFLAGS_REQUIRED, OLESTR(""), 0)
			PROPERTY_INFO_ENTRY_VALUE(DSOTHREADMODEL, DBPROPVAL_RT_APTMTTHREAD | DBPROPVAL_RT_FREETHREAD)
			PROPERTY_INFO_ENTRY_VALUE(IDENTIFIERCASE, DBPROPVAL_IC_SENSITIVE)
			PROPERTY_INFO_ENTRY_VALUE(MAXROWSIZE, 0)
			PROPERTY_INFO_ENTRY_VALUE(MAXROWSIZEINCLUDESBLOB, VARIANT_FALSE)
			PROPERTY_INFO_ENTRY_VALUE(MAXTABLESINSELECT, 0)
			PROPERTY_INFO_ENTRY_VALUE(MULTIPLERESULTS, DBPROPVAL_MR_NOTSUPPORTED)
			PROPERTY_INFO_ENTRY_VALUE(NULLCOLLATION, DBPROPVAL_NC_LOW)
			PROPERTY_INFO_ENTRY_VALUE(OPENROWSETSUPPORT, DBPROPVAL_ORS_TABLE|DBPROPVAL_ORS_INTEGRATEDINDEX)
			PROPERTY_INFO_ENTRY_VALUE(ORDERBYCOLUMNSINSELECT, VARIANT_TRUE)
			PROPERTY_INFO_ENTRY_VALUE(OUTPUTPARAMETERAVAILABILITY, 0)
			PROPERTY_INFO_ENTRY_VALUE(PERSISTENTIDTYPE, DBPROPVAL_PT_NAME)
			PROPERTY_INFO_ENTRY_VALUE(PROVIDERFRIENDLYNAME, g_cbProviderFriendlyName)
			PROPERTY_INFO_ENTRY_EX(PROVIDERMEMORY, VT_BOOL, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_VALUE(PROVIDERNAME, g_cbProviderName)
			PROPERTY_INFO_ENTRY_EX(PROVIDEROLEDBVER, VT_BSTR, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ, OLESTR("02.00"), 0)
			PROPERTY_INFO_ENTRY_VALUE(PROVIDERVER, g_cbProviderVer)
			PROPERTY_INFO_ENTRY_VALUE(QUOTEDIDENTIFIERCASE, DBPROPVAL_IC_SENSITIVE)
			PROPERTY_INFO_ENTRY_VALUE(ROWSETCONVERSIONSONCOMMAND, VARIANT_TRUE)
			PROPERTY_INFO_ENTRY_EX(SERVERNAME, VT_BSTR, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_CHANGE | DBPROPFLAGS_REQUIRED, OLESTR(""), 0)
			PROPERTY_INFO_ENTRY_VALUE(SQLSUPPORT, DBPROPVAL_SQL_SUBMINIMUM)
			PROPERTY_INFO_ENTRY_VALUE(SUBQUERIES, 0)
			PROPERTY_INFO_ENTRY_VALUE(SUPPORTEDTXNISOLEVELS, 0)
			PROPERTY_INFO_ENTRY_VALUE(TABLETERM, g_cbTableTerm)
			PROPERTY_INFO_ENTRY_EX(USERNAME, VT_BSTR, DBPROPFLAGS_DATASOURCEINFO | DBPROPFLAGS_READ | DBPROPFLAGS_CHANGE | DBPROPFLAGS_REQUIRED, OLESTR(""), 0)
		END_PROPERTY_SET(DBPROPSET_DATASOURCEINFO)
		BEGIN_PROPERTY_SET(DBPROPSET_DBINIT)
			PROPERTY_INFO_ENTRY(AUTH_PASSWORD)
			PROPERTY_INFO_ENTRY(AUTH_PERSIST_SENSITIVE_AUTHINFO)
			PROPERTY_INFO_ENTRY(AUTH_USERID)
			PROPERTY_INFO_ENTRY_EX(INIT_DATASOURCE, VT_BSTR, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, OLECHAR(""), 0)
			PROPERTY_INFO_ENTRY(INIT_HWND)
			PROPERTY_INFO_ENTRY(INIT_LCID)
			PROPERTY_INFO_ENTRY_VALUE(INIT_LOCATION, OLESTR("."))
			PROPERTY_INFO_ENTRY_EX(INIT_MODE, VT_I4, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, DB_MODE_READWRITE, 0)
			PROPERTY_INFO_ENTRY_EX(INIT_OLEDBSERVICES, VT_I4, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE | DBPROPFLAGS_REQUIRED, DBPROPVAL_OS_ENABLEALL, 0)
			PROPERTY_INFO_ENTRY_EX(INIT_PROMPT, VT_I2, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, DBPROMPT_NOPROMPT, 0)
			PROPERTY_INFO_ENTRY_VALUE(INIT_PROVIDERSTRING, OLESTR(""))
			PROPERTY_INFO_ENTRY(INIT_TIMEOUT)
		END_PROPERTY_SET(DBPROPSET_DBINIT)
		BEGIN_PROPERTY_SET(DBPROPSET_DATASOURCE)
			PROPERTY_INFO_ENTRY(CURRENTCATALOG)
		END_PROPERTY_SET(DBPROPSET_DATASOURCE)
		BEGIN_PROPERTY_SET(DBPROPSET_SESSION)
			PROPERTY_INFO_ENTRY(SESS_AUTOCOMMITISOLEVELS)
		END_PROPERTY_SET(DBPROPSET_SESSION)

	// TRiAS specifics
		BEGIN_PROPERTY_SET(DBPROPSET_TRiAS_INITDATASOURCE)
			PROPERTY_INFO_ENTRY_VALUE(TRiAS_GEOMETRYTYPE, DBPROPVAL_TRiAS_GEOMETRYTABLES)
			PROPERTY_INFO_ENTRY_VALUE(TRiAS_GENERATEVIEWS, VARIANT_TRUE)
		END_PROPERTY_SET(DBPROPSET_TRiAS_INITDATASOURCE)
		BEGIN_PROPERTY_SET(DBPROPSET_TRiAS_CREATEDATASOURCE)
			PROPERTY_INFO_ENTRY_VALUE(TRiAS_CREATE_COMPATIBLE, 500)
			PROPERTY_INFO_ENTRY_VALUE(TRiAS_CREATE_COMPRESSED, VARIANT_TRUE)
		END_PROPERTY_SET(DBPROPSET_TRiAS_CREATEDATASOURCE)
		BEGIN_PROPERTY_SET(DBPROPSET_TRiAS_DATASOURCEINFO)
			PROPERTY_INFO_ENTRY(TRiAS_DBVERSION, )
		END_PROPERTY_SET(DBPROPSET_TRiAS_DATASOURCEINFO)

	// OGC property set
		BEGIN_PROPERTY_SET(DBPROPSET_OGIS_SPATIAL_OPS)
			PROPERTY_INFO_ENTRY_EX(OGIS_TOUCHES, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_WITHIN, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_CONTAINS, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_CROSSES, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_OVERLAPS, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_DISJOINT, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_INTERSECT, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_ENVELOPE_INTERSECTS, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OGIS_INDEX_INTERSECTS, VT_BOOL, DBPROPFLAGS_DBINIT | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
		END_PROPERTY_SET(DBPROPSET_OGIS_SPATIAL_OPS)

		CHAIN_PROPERTY_SET(CTRiASOleDBCommand)
	END_PROPSET_MAP()

// IDBInfoImpl supporting maps
	BEGIN_DBINFO_KEYWORD_MAP(CTRiASOleDBSource)
	END_DBINFO_KEYWORD_MAP()
	BEGIN_DBINFO_LITERAL_MAP(CTRiASOleDBSource)
		LITERAL_ENTRY(DBLITERAL_BINARY_LITERAL, NULL, NULL, NULL, 255)
		LITERAL_ENTRY(DBLITERAL_CHAR_LITERAL, NULL, OLESTR(".`![]"), NULL, 255)
		LITERAL_ENTRY(DBLITERAL_COLUMN_ALIAS, NULL, OLESTR(".`![]"), NULL, 255)
		LITERAL_ENTRY(DBLITERAL_COLUMN_NAME, NULL, OLESTR(".`"), NULL, 32)
		LITERAL_ENTRY(DBLITERAL_TABLE_NAME, NULL, OLESTR(".`"), NULL, 32)
		LITERAL_ENTRY(DBLITERAL_TEXT_COMMAND, NULL, OLESTR(".`![]"), NULL, -1)
		LITERAL_ENTRY(DBLITERAL_QUOTE_PREFIX, OLESTR("`"), NULL, NULL, 1)
		LITERAL_ENTRY(DBLITERAL_QUOTE_SUFFIX, OLESTR("`"), NULL, NULL, 1)
//		LITERAL_ENTRY(DBLITERAL_CATALOG_SEPARATOR, OLESTR("."), NULL, NULL, 1)
//		LITERAL_ENTRY(DBLITERAL_SCHEMA_SEPARATOR, OLESTR("."), NULL, NULL, 1)
	END_DBINFO_LITERAL_MAP()

	static HRESULT WINAPI _FailIfNotInitialized (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(CTRiASOleDBSource)
		COM_INTERFACE_ENTRY(IDBInitialize)
		COM_INTERFACE_ENTRY(IDBProperties)
		COM_INTERFACE_ENTRY_FUNC(__uuidof(IDBCreateSession), 
					offsetofclass(IDBCreateSession, _ComMapClass),
					_FailIfNotInitialized)
		COM_INTERFACE_ENTRY_FUNC(__uuidof(IDBInfo), 
					offsetofclass(IDBInfo, _ComMapClass),
					_FailIfNotInitialized)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IInternalConnection)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IDBDataSourceAdmin)
		COM_INTERFACE_ENTRY_THIS()
	END_COM_MAP()

public:
// Wrapperfunctions for ITRiASNativeDataSource
	HRESULT get_Classes (ITRiASEnumNativeIdents **ppVal)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_GeoDBService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_GeoDBService -> get_Classes(m_hPr, ppVal);
	}
	HRESULT get_Class (BSTR bstrTable, INT_PTR *plIdent)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_GeoDBService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_GeoDBService -> get_Class(m_hPr, bstrTable, VARIANT_TRUE, plIdent);
	}
	HRESULT AddClass (BSTR bstrTable, INT_PTR *plIdent)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_GeoDBService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_GeoDBService -> AddClass(m_hPr, bstrTable, plIdent);
	}
	HRESULT DestroyClass (BSTR bstrTable)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_GeoDBService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_GeoDBService -> DestroyClass(m_hPr, bstrTable);
	}
	HRESULT get_ClassesHaveDates (VARIANT_BOOL *pfHaveDates)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_GeoDBService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_GeoDBService -> get_IdentsHaveDates(m_hPr, pfHaveDates);
	}
	HRESULT get_Types (INT_PTR lIdent, DWORD *pdwTypes)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_IdentService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_IdentService -> get_Types(m_hPr, lIdent, pdwTypes);
	}
	HRESULT get_Attributes (INT_PTR lIdent, ITRiASEnumNativeAttributes **ppIAttribs)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_IdentService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_IdentService -> get_Attributes(m_hPr, lIdent, ppIAttribs);
	}
	HRESULT get_AttribName (INT_PTR lMCode, BSTR *pbstrName)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_AttribService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_AttribService -> get_Name(m_hPr, lMCode, pbstrName);
	}
	HRESULT get_Attribute (INT_PTR lIdent, BSTR bstrAttrib, INT_PTR *plMCode)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_IdentService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_IdentService -> GetAttribute(m_hPr, lIdent, bstrAttrib, VARIANT_TRUE, plMCode);
	}
	HRESULT AddAttribute (INT_PTR lIdent, BSTR bstrAttrib, INT_PTR *plMCode)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_IdentService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_IdentService -> PutAttribute(m_hPr, lIdent, bstrAttrib, plMCode);
	}
	HRESULT DestroyAttribute (INT_PTR lIdent, BSTR bstrAttrib)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_IdentService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_IdentService -> DestroyAttribute(m_hPr, lIdent, bstrAttrib);
	}
	HRESULT get_ObjectsFromClass (INT_PTR lIdent, DWORD dwTypes, ITRiASExpression *pIExpr, ITRiASEnumNativeObjects **ppIObjsOut)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_IdentService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_IdentService -> get_Objects (m_hPr, lIdent, dwTypes, pIExpr, ppIObjsOut);
	}
	HRESULT get_ObjectsFromAttrib(INT_PTR lIdent, INT_PTR lMCode, BSTR bstrStart, BSTR bstrEnd, DBRANGEENUM rgRange, ITRiASEnumNativeObjects **ppIObjsOut)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_AttribService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_AttribService -> get_Objects (m_hPr, lIdent, lMCode, bstrStart, bstrEnd, rgRange, ppIObjsOut);
	}
	HRESULT get_CoordSystemWKT (UINT *puiCode, BSTR *pbstrCS)
	{
		RETURN_FAILED_HRESULT(EnsureDatasourceOpened());

		_ASSERTE(m_GeoDBService != NULL);	// service instanciated
		_ASSERTE(NULL != m_hPr);			// datasource opened
		return m_GeoDBService -> get_CoordSystemWKT (m_hPr, puiCode, pbstrCS);
	}

// Helper functions
	HRESULT EnsureDatasourceOpened(INT_PTR *phPr = NULL);
	HRESULT EnsureDatasourceClosed();
	INT_PTR GetProjectHandle() const { return m_hPr; }

// IDBInitialize
	STDMETHOD(Initialize)(void)
	{
		RETURN_FAILED_HRESULT(InitPropertiesDbInit());		// die letzen Initialisierungen
	
	HRESULT hr = IDBInitializeImpl<CTRiASOleDBSource>::Initialize();

		if (SUCCEEDED(hr)) {
			hr = EnsureDatasourceOpened();
			if (FAILED(hr))
				IDBInitializeImpl<CTRiASOleDBSource>::Uninitialize();
		}
		return hr;
	}
	STDMETHOD(Uninitialize)(void)
	{
	HRESULT hr = IDBInitializeImpl<CTRiASOleDBSource>::Uninitialize();

		if (SUCCEEDED(hr))
			hr = EnsureDatasourceClosed();
		return hr;
	}
	DWORD GetGeometryMode() { return m_dwGeomType; }
	bool GetViewMode() { return m_fViewMode; }

// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// support for IDBDataSourceAdmin
	DWORD GetSupportedSetsInSpecialGroup(REFGUID rGuid)
	{
		if (InlineIsEqualGUID (rGuid, DBPROPSET_TRiAS_CREATEDATASOURCE))
			return DBPROPFLAGS_DATASOURCECREATE;
		return 0;
	}
	HRESULT CreateAndOpenDatasource();
	HRESULT CloseAndDestroyDatasource();

protected:
// GeoDB Service instantiieren
	HRESULT EnsureServices()
	{
		if (m_GeoDBService == NULL) {
			RETURN_FAILED_HRESULT(m_GeoDBService.CoCreateInstance(CLSID_TRiASNativeDataSource));
		}
		if (m_IdentService == NULL) {
			RETURN_FAILED_HRESULT(m_IdentService.CoCreateInstance(CLSID_TRiASNativeIdent));
		}
		if (m_AttribService == NULL) {
			RETURN_FAILED_HRESULT(m_AttribService.CoCreateInstance(CLSID_TRiASNativeAttribute));
		}
		return S_OK;
	}
	HRESULT GetDataSourceParams (BSTR *pbstrName, DWORD *pdwMode, DWORD *pdwPrompt, HWND *phWnd);
	HRESULT GetDataSourceCreateParams (int *piCompatible, bool *pfCompressed);
	HRESULT GetProviderString (BSTR *pbstrProvider);
	HRESULT AnalyseProviderString (BSTR bstrProvString);

	HRESULT InitPropertiesDbInit();
	HRESULT InitProperties();
	bool GetDefaultDataStore (BSTR *pbstrLoc);
	HRESULT AskUserForParameters(HWND hWnd, CComBSTR &rbstrName, DWORD &rdwMode);

private:
	CComPtr<ITRiASNativeDataSource> m_GeoDBService;
	CComPtr<ITRiASNativeIdent> m_IdentService;
	CComPtr<ITRiASNativeAttribute> m_AttribService;
	INT_PTR m_hPr;
	DWORD m_dwGeomType;		// Geometrie als zusätzliche Spalten oder Tabellen liefern
	bool m_fViewMode;		// vordefinierte Views erzeugen
};

#endif // !defined(_TRIASOLEDBDATASOURCE_H__DF1EB105_282E_4D0B_A388_4471476FBC96__INCLUDED_)
