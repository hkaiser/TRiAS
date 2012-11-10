// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:14:43 
//
// @doc
// @module TRiASOleDBSessionSchemaOGISTables.h | Declaration of the <c CTRiASOleDBSessionSchemaOGISTables> class

#if !defined(_TRIASOLEDBSESSIONSCHEMAOGISTABLES_H__514ECE5B_F6D2_498E_857C_AD62BE958596__INCLUDED_)
#define _TRIASOLEDBSESSIONSCHEMAOGISTABLES_H__514ECE5B_F6D2_498E_857C_AD62BE958596__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

/////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionSchemaOGISTables 
class COGISTablesRow
{
public:
	WCHAR m_szAlias[129];
	WCHAR m_szCatalog[4];
	WCHAR m_szSchema[4];
	WCHAR m_szTableName[129];
	WCHAR m_szColumnName[129];
	WCHAR m_szDGName[129];

	COGISTablesRow()
	{
		m_szAlias[0] = NULL;
		m_szCatalog[0] = NULL;
		m_szSchema[0] = NULL;
		m_szTableName[0] = NULL;
		m_szColumnName[0] = NULL;
		m_szDGName[0] = NULL;
	}

	BEGIN_PROVIDER_COLUMN_MAP(COGISTablesRow)
		PROVIDER_COLUMN_ENTRY("FEATURE_TABLE_ALIAS", 1, m_szAlias)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 2, m_szCatalog)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 3, m_szSchema)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 4, m_szTableName)
		PROVIDER_COLUMN_ENTRY("ID_COLUMN_NAME", 5, m_szColumnName)
		PROVIDER_COLUMN_ENTRY("DG_COLUMN_NAME", 6, m_szDGName)
	END_PROVIDER_COLUMN_MAP()
};

namespace {
	LPCOLESTR GetMainGeometryNameFromTypes (DWORD dwTypes)
	{
		_ASSERTE(0 != dwTypes);
		for (int i = 0; i < _countof(s_rgTypes); ++i) {
			if (s_rgTypes[i].dwType & dwTypes)
				return s_rgTypes[i].pcoleGeomName;		// die erste existierende Geometrie
		}
		return NULL;		// not found any Geometry
	}
}

class CTRiASOleDBSessionSchemaOGISTables:
	public CSchemaRowsetImpl<CTRiASOleDBSessionSchemaOGISTables, COGISTablesRow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionSchemaOGISTables)
		BEGIN_PROPERTY_SET(DBPROPSET_ROWSET)
			PROPERTY_INFO_ENTRY(IAccessor)
			PROPERTY_INFO_ENTRY(IColumnsInfo)
			PROPERTY_INFO_ENTRY(IConvertType)
			PROPERTY_INFO_ENTRY(IRowset)
			PROPERTY_INFO_ENTRY(IRowsetIdentity)
			PROPERTY_INFO_ENTRY(IRowsetInfo)
			PROPERTY_INFO_ENTRY(CANFETCHBACKWARDS)
			PROPERTY_INFO_ENTRY(CANHOLDROWS)
			PROPERTY_INFO_ENTRY(CANSCROLLBACKWARDS)
			PROPERTY_INFO_ENTRY_VALUE(MAXOPENROWS, 0)
			PROPERTY_INFO_ENTRY_VALUE(MAXROWS, 0)
		END_PROPERTY_SET(DBPROPSET_ROWSET)
	END_PROPSET_MAP()

	HRESULT Execute(LONG* pcRowsAffected, ULONG, const VARIANT*)
	{
	// Idents der geöffneten GeoDB
	// zugehöriges DataSourceObjekt besorgen
	CTRiASOleDBSource *pDataSource = NULL;

		RETURN_FAILED_HRESULT(GetDataSourceObject(this, &pDataSource));

	// Idents der geöffneten GeoDB
	CComPtr<ITRiASEnumNativeIdents> Idents;

		RETURN_FAILED_HRESULT(pDataSource -> get_Classes(&Idents));

	// alle Tabellen (Objektklassen) enumerieren und zu RowSet hinzufügen
	CComPtr<IUnknown> UnkEnum;

		RETURN_FAILED_HRESULT(Idents -> get__NewEnum (&UnkEnum));

	CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
	CComPtr<ITRiASNativeIdent> Ident;
	INT_PTR hPr = NULL;

		RETURN_FAILED_HRESULT(Ident.CoCreateInstance(CLSID_TRiASNativeIdent));
		RETURN_FAILED_HRESULT(pDataSource -> EnsureDatasourceOpened(&hPr));

	CComVariant v;
	LONG lCnt = 0;

		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); ++lCnt) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		CComBSTR bstrName, bstrDesc, bstrOKS;

			RETURN_FAILED_HRESULT(Ident -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc, &bstrOKS));

		// entscheiden, wie Geometrie abgebildet werden soll
		DWORD dwTypes = 0;
		CComBSTR bstrColName;

			bstrColName.LoadString(IDS_OBJNRNAME);
			RETURN_FAILED_HRESULT(Ident -> get_Types (hPr, V_I4(&v), &dwTypes));
			if (0 == dwTypes)
				continue;		// no objects, no geometry!

#if defined(_USE_PROP_GEOMETRYAS)
			if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
			// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
			// 4 separaten Spalten
			COGISTablesRow trData;

				wcscpy(trData.m_szAlias, bstrDesc);
				wcscpy(trData.m_szTableName, bstrName);
				wcscpy(trData.m_szColumnName, bstrColName);
				wcscpy(trData.m_szDGName, GetMainGeometryNameFromTypes(dwTypes));

				if (!m_rgRowData.Add(trData))
					return E_OUTOFMEMORY;
			} 
			else 
#endif // defined(_USE_PROP_GEOMETRYAS)
			{
			// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
			// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
			COGISTablesRow trData;

				wcscpy(trData.m_szAlias, bstrDesc);
				wcscpy(trData.m_szColumnName, bstrColName);
				wcscpy(trData.m_szDGName, OLESTR("OGIS_GEOMETRY"));

				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (!(s_rgTypes[i].dwType & dwTypes))
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				CComBSTR bstrTypeName (bstrName);

					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrTypeName.Append(s_rgTypes[i].pcoleObjTypeName);
					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);

					wcscpy(trData.m_szTableName, bstrTypeName);
					if (!m_rgRowData.Add(trData))
						return E_OUTOFMEMORY;
				}
			}
		}
		*pcRowsAffected = lCnt;
		return S_OK;
	}

	DBSTATUS GetDBStatus(CSimpleRow *pRow, ATLCOLUMNINFO *pInfo)
	{
		switch(pInfo->iOrdinal) {
		case 2:		// TABLE_CATALOG
		case 3:		// TABLE_SCHEMA
			return DBSTATUS_S_ISNULL;

		default:
			return DBSTATUS_S_OK;
		}
	}
};

#endif // !defined(_TRIASOLEDBSESSIONSCHEMAOGISTABLES_H__514ECE5B_F6D2_498E_857C_AD62BE958596__INCLUDED_)
