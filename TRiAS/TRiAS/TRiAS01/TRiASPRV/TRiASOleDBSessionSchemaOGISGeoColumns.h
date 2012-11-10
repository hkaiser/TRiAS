// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:16:02 
//
// @doc
// @module TRiASOleDBSessionSchemaOGISGeoColumns.h | Declaration of the <c CTRiASOleDBSessionSchemaOGISGeoColumns> class

#if !defined(_TRIASOLEDBSESSIONSCHEMAOGISGEOCOLUMNS_H__D4BEDC69_29C9_41AF_8173_C519433E8A48__INCLUDED_)
#define _TRIASOLEDBSESSIONSCHEMAOGISGEOCOLUMNS_H__D4BEDC69_29C9_41AF_8173_C519433E8A48__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionSchemaOGISGeoColumns
class COGISGeometryRow
{
public:
	WCHAR m_szCatalog[4];
	WCHAR m_szSchema[4];
	WCHAR m_szTableName[129];
	WCHAR m_szColumnName[129];
	unsigned int m_nGeomType;
	int m_nSpatialRefId;
	
	COGISGeometryRow()
	{
		m_szCatalog[0] = NULL;
		m_szSchema[0] = NULL;
		m_szTableName[0] = NULL;
		m_szColumnName[0] = NULL;
		m_nGeomType = 0;
		m_nSpatialRefId = 0;
	}

	BEGIN_PROVIDER_COLUMN_MAP(COGISGeometryRow)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szCatalog)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szSchema)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTableName)
		PROVIDER_COLUMN_ENTRY("COLUMN_NAME", 4, m_szColumnName)
		PROVIDER_COLUMN_ENTRY("GEOM_TYPE", 5, m_nGeomType)
		PROVIDER_COLUMN_ENTRY("SPATIAL_REF_SYSTEM_ID", 6, m_nSpatialRefId)
	END_PROVIDER_COLUMN_MAP()
};

class CTRiASOleDBSessionSchemaOGISGeoColumns:
	public CSchemaRowsetImpl<CTRiASOleDBSessionSchemaOGISGeoColumns, COGISGeometryRow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionSchemaOGISGeoColumns)
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

#if defined(_USE_PROP_GEOMETRYAS)
			if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
			// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
			// 4 separaten Spalten
			COGISGeometryRow trData;

				wcscpy(trData.m_szTableName, bstrName);
				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (!(s_rgTypes[i].dwType & dwTypes))
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

					wcscpy(trData.m_szColumnName, s_rgTypes[i].pcoleGeomName);
					trData.m_nGeomType = s_rgTypes[i].uiOGCType;
					trData.m_nSpatialRefId = 1;		// alle Geometrien sind bezüglich ein und des selben KoordSystems
					if (!m_rgRowData.Add(trData))
						return E_OUTOFMEMORY;
				}
			} 
			else 
#endif // defined(_USE_PROP_GEOMETRYAS)
			{
			// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
			// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
			COGISGeometryRow trData;

				wcscpy(trData.m_szColumnName, OLESTR("OGIS_GEOMETRY"));
				trData.m_nSpatialRefId = 1;		// alle Geometrien sind bezüglich ein und des selben KoordSystems

				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (!(s_rgTypes[i].dwType & dwTypes))
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				CComBSTR bstrTypeName (bstrName);

					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrTypeName.Append(s_rgTypes[i].pcoleObjTypeName);
					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);

					wcscpy(trData.m_szTableName, bstrTypeName);
					trData.m_nGeomType = s_rgTypes[i].uiOGCType;
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
		case 1:		// TABLE_CATALOG
		case 2:		// TABLE_SCHEMA
			return DBSTATUS_S_ISNULL;

		default:
			return DBSTATUS_S_OK;
		}
	}
};

#endif // !defined(_TRIASOLEDBSESSIONSCHEMAOGISGEOCOLUMNS_H__D4BEDC69_29C9_41AF_8173_C519433E8A48__INCLUDED_)
