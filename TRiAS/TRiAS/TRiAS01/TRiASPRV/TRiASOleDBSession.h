// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.05.2001 11:52:45 
//
// @doc
// @module TRiASOleDBSession.h | Declaration of the <c CTRiASOleDBSession> class

#if !defined(_TRIASOLEDBSESSION_H__74955279_B9E8_4D70_BD25_30506B540219__INCLUDED_)
#define _TRIASOLEDBSESSION_H__74955279_B9E8_4D70_BD25_30506B540219__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDB/DBId.h>
#include <Atl/OleDB/ITableDefinitionImpl.h>
#include <Atl/OleDB/IAlterTableImpl.h>

#include "resource.h"		// main symbols

#include "TRiASOleDBDataSource.h"
#include "SQLVerification.h"

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class CTRiASOleDBSessionTRSchemaRowset;
class CTRiASOleDBSessionTISchemaRowset;
class CTRiASOleDBSessionColSchemaRowset;
class CTRiASOleDBSessionPTSchemaRowset;
class CTRiASOleDBSessionStatistSchemaRowset;
class CTRiASOleDBSessionIdxSchemaRowset;
class CTRiASOleDBSessionPrimaryKeysSchemaRowset;

#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
class CTRiASOleDBSessionVRSchemaRowset;
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)

class CTRiASOleDBSessionSchemaOGISTables;
class CTRiASOleDBSessionSchemaOGISGeoColumns;
class CTRiASOleDBSessionSchemaSpatRef;

/////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSession
// 5AFE9B6C-0CB3-424F-BD07-A0152E25BDDE
EXTERN_C const GUID __declspec(selectany) CLSID_TRiASOleDBSession = 
	{ 0x5AFE9B6C, 0x0CB3, 0x424F, 0xBD, 0x07, 0xA0, 0x15, 0x2E, 0x25, 0xBD, 0xDE };

class ATL_NO_VTABLE CTRiASOleDBSession : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public IGetDataSourceImpl<CTRiASOleDBSession>,
	public IOpenRowsetImpl<CTRiASOleDBSession>,
	public ISessionPropertiesImpl<CTRiASOleDBSession>,
	public IObjectWithSiteSessionImpl<CTRiASOleDBSession>,
	public IDBSchemaRowsetImpl<CTRiASOleDBSession>,
	public IDBCreateCommandImpl<CTRiASOleDBSession, CTRiASOleDBCommand>,
	public ITableDefinitionImpl<CTRiASOleDBSession>,
	public IAlterTableImpl<CTRiASOleDBSession>,
	public ISupportErrorInfoImpl<&IID_IOpenRowset>,
	public CTRiASOleDBErrorBase<CTRiASOleDBSession, &IID_IOpenRowset>
{
public:
	CTRiASOleDBSession()
	{
	}
	HRESULT FinalConstruct()
	{
		return FInit();
	}
	STDMETHOD(OpenRowset)(IUnknown *pUnk, DBID *pTID, DBID *pInID, REFIID riid, ULONG cSets, 
		DBPROPSET rgSets[], IUnknown **ppRowset);

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASOleDBSession)

	BEGIN_PROPSET_MAP(CTRiASOleDBSession)
		BEGIN_PROPERTY_SET(DBPROPSET_SESSION)
			PROPERTY_INFO_ENTRY(SESS_AUTOCOMMITISOLEVELS)
		END_PROPERTY_SET(DBPROPSET_SESSION)
	END_PROPSET_MAP()

	BEGIN_COM_MAP(CTRiASOleDBSession)
		COM_INTERFACE_ENTRY(IGetDataSource)
		COM_INTERFACE_ENTRY(IOpenRowset)
		COM_INTERFACE_ENTRY(ISessionProperties)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY(IDBCreateCommand)
		COM_INTERFACE_ENTRY(IDBSchemaRowset)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITableDefinition)
		COM_INTERFACE_ENTRY(IAlterTable)
		COM_INTERFACE_ENTRY_THIS_EX(CLSID_TRiASOleDBSession)
	END_COM_MAP()

	BEGIN_SCHEMA_MAP(CTRiASOleDBSession)
		SCHEMA_ENTRY(DBSCHEMA_TABLES, CTRiASOleDBSessionTRSchemaRowset)
#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
		SCHEMA_ENTRY(DBSCHEMA_VIEWS, CTRiASOleDBSessionVRSchemaRowset)
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)
		SCHEMA_ENTRY(DBSCHEMA_TABLES_INFO, CTRiASOleDBSessionTISchemaRowset)
		SCHEMA_ENTRY(DBSCHEMA_INDEXES, CTRiASOleDBSessionIdxSchemaRowset)
		SCHEMA_ENTRY(DBSCHEMA_COLUMNS, CTRiASOleDBSessionColSchemaRowset)
		SCHEMA_ENTRY(DBSCHEMA_PROVIDER_TYPES, CTRiASOleDBSessionPTSchemaRowset)
		SCHEMA_ENTRY(DBSCHEMA_STATISTICS, CTRiASOleDBSessionStatistSchemaRowset)
		SCHEMA_ENTRY(DBSCHEMA_PRIMARY_KEYS, CTRiASOleDBSessionPrimaryKeysSchemaRowset)
		SCHEMA_ENTRY(DBSCHEMA_OGIS_FEATURE_TABLES, CTRiASOleDBSessionSchemaOGISTables)
		SCHEMA_ENTRY(DBSCHEMA_OGIS_GEOMETRY_COLUMNS, CTRiASOleDBSessionSchemaOGISGeoColumns)
		SCHEMA_ENTRY(DBSCHEMA_OGIS_SPATIAL_REF_SYSTEMS, CTRiASOleDBSessionSchemaSpatRef);
	END_SCHEMA_MAP()

public:
	HRESULT GetDataSourceObject (CTRiASOleDBSource **ppDataSource)
	{
	CComPtr<IDBCreateSession> spCreate;
	HRESULT hr = E_FAIL;

		if (FAILED(hr = GetSite (IID_IDBCreateSession, (void **)&spCreate))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the DataSource from Session...\n");
			return hr;
		}
		return QueryImplementation(spCreate, ppDataSource);
	}

// GetSchemas helper
	void SetRestrictions(ULONG cRestrictions, GUID *rguidSchema, ULONG* rgRestrictions)
	{
		for (ULONG i = 0; i < cRestrictions; ++i) {
			if (InlineIsEqualGUID(DBSCHEMA_TABLES, rguidSchema[i]))
				rgRestrictions[i] = 0xc;		// [TABLE_CATALOG, TABLE_SCHEMA,] TABLE_NAME, TABLE_TYPE
#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
			else if (InlineIsEqualGUID(DBSCHEMA_VIEWS, rguidSchema[i]))
				rgRestrictions[i] = 0x4;		// [TABLE_CATALOG, TABLE_SCHEMA,] TABLE_NAME
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)
			else if (InlineIsEqualGUID(DBSCHEMA_TABLES_INFO, rguidSchema[i]))
				rgRestrictions[i] = 0xc;		// [TABLE_CATALOG, TABLE_SCHEMA,] TABLE_NAME, TABLE_TYPE
			else if (InlineIsEqualGUID(DBSCHEMA_INDEXES, rguidSchema[i]))
				rgRestrictions[i] = 0x1c;		// [TABLE_CATALOG, TABLE_SCHEMA,] INDEX_NAME, TYPE, TABLE_NAME
			else if (InlineIsEqualGUID(DBSCHEMA_COLUMNS, rguidSchema[i]))
				rgRestrictions[i] = 0xc;		// [TABLE_CATALOG, TABLE_SCHEMA,] TABLE_NAME, COLUMN_NAME
			else if (InlineIsEqualGUID(DBSCHEMA_PROVIDER_TYPES, rguidSchema[i]))
				rgRestrictions[i] = 0x3;		// DATA_TYPE, BEST_MATCH
			else if (InlineIsEqualGUID(DBSCHEMA_STATISTICS, rguidSchema[i]))
				rgRestrictions[i] = 0x4;		// [TABLE_CATALOG, TABLE_SCHEMA,] TABLE_NAME
			else if (InlineIsEqualGUID(DBSCHEMA_PRIMARY_KEYS, rguidSchema[i]))
				rgRestrictions[i] = 0x4;		// [TABLE_CATALOG, TABLE_SCHEMA,] TABLE_NAME
			else if (InlineIsEqualGUID(DBSCHEMA_OGIS_FEATURE_TABLES, rguidSchema[i]) ||
					 InlineIsEqualGUID(DBSCHEMA_OGIS_GEOMETRY_COLUMNS, rguidSchema[i]) ||
					 InlineIsEqualGUID(DBSCHEMA_OGIS_SPATIAL_REF_SYSTEMS, rguidSchema[i]))
			{
				rgRestrictions[i] = 0;			// no required restrictions
			}
		}
	}

// support for ITableDefinition
	HRESULT IsExistingTable (DBID *pTableId, INT_PTR *plIdent = NULL);
	HRESULT CreateNewTable (DBID *pTableId, INT_PTR *plIdent = NULL);
	HRESULT DropExistingTable (DBID *pTableId);

	HRESULT IsExistingColumn (DBID *pTableId, DBID *pColumnId, INT_PTR *plAttrib = NULL);
	HRESULT CreateNewColumn (DBID *pTableID, const DBCOLUMNDESC *pColumnDesc, DBID **ppColumnID = NULL, INT_PTR *plAttrib = NULL);
	HRESULT DropExistingColumn (DBID *pTableID, DBID *pColumnID);

// support for IAlterTable
	HRESULT AlterExistingTable (DBID *pTableId, DBID *pNewTableId, ULONG cPropertySets, DBPROPSET rgPropertySets[]);
	HRESULT AlterExistingColumn(DBID *pTableId, DBID *pColumnId, DBCOLUMNDESCFLAGS rgColumnDescFlags, DBCOLUMNDESC *pColumnDesc);

// Tabellen, die derzeit in einem Rowset gebunden sind
	HRESULT RegisterTable (DBID *pTableId)
	{
	CDBID TableId(*pTableId, CDBID::DBIDMODE_Quoted);
	int iIndex = m_RowsetTables.FindKey(TableId);

		if (-1 == iIndex) {
		// der erste Verweis
			if (!m_RowsetTables.Add(TableId, 1))
				return E_OUTOFMEMORY;
		} else 
			++m_RowsetTables.GetValueAt(iIndex);
		return S_OK;
	}
	HRESULT UnregisterTable (DBID *pTableId)
	{
	CDBID TableId(*pTableId, CDBID::DBIDMODE_Quoted);
	int iIndex = m_RowsetTables.FindKey(TableId);

		if (-1 != iIndex) {
			if (0 == --m_RowsetTables.GetValueAt(iIndex)) {
				m_RowsetTables.Remove(TableId);
				return S_OK;
			}
			return S_FALSE;
		}
		return E_UNEXPECTED;
	}
	HRESULT IsTableInuse (DBID *pTableId)
	{
		return (-1 != m_RowsetTables.FindKey(CDBID(*pTableId, CDBID::DBIDMODE_Quoted))) ? S_OK : S_FALSE;
	}

private:
	CSimpleMap<CDBID, ULONG> m_RowsetTables;
};

#endif // !defined(_TRIASOLEDBSESSION_H__74955279_B9E8_4D70_BD25_30506B540219__INCLUDED_)
