// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 19.06.2001 10:47:50 
//
// @doc
// @module TRiASOleDBSessionIdxSchemaRowset.h | Declaration of the <c CTRiASOleDBSessionIdxSchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONIDXSCHEMAROWSET_H__2F19D66A_22E3_442F_85A4_65839560D3A9__INCLUDED_)
#define _TRIASOLEDBSESSIONIDXSCHEMAROWSET_H__2F19D66A_22E3_442F_85A4_65839560D3A9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionIdxSchemaRowset: RowSet aller verfügbaren Spalten
class CINDEXESRow
{
public:
	WCHAR	m_szTableCatalog[129];
	WCHAR	m_szTableSchema[129];
	WCHAR	m_szTableName[129];
	WCHAR	m_szIdxCatalog[129];
	WCHAR	m_szIdxSchema[129];
	WCHAR	m_szIdxName[129];
	VARIANT_BOOL	m_fPrimaryIdx;
	VARIANT_BOOL	m_fUniqueIdx;
	VARIANT_BOOL	m_fClusteredIdx;
	short	m_nIdxType;
	ULONG	m_ulFillFactor;
	ULONG	m_ulInitSize;
	ULONG	m_ulNulls;
	VARIANT_BOOL	m_fSortBookmarks;
	VARIANT_BOOL	m_fAutoUpdate;
	ULONG	m_ulNullColl;
	ULONG	m_ulOrdinal;
	WCHAR	m_szColumnName[129];
	GUID	m_guidColumn;
	ULONG	m_ulColumnPropID;
	short	m_nCollation;
	ULARGE_INTEGER m_ui64Cardinality;
	ULONG	m_ulPages;
	WCHAR	m_szFilter[260];
	VARIANT_BOOL	m_fIntegratedIdx;

	CINDEXESRow() 
	{
		ClearMembers();
	}

	void ClearMembers()
	{
		m_szTableCatalog[0] = NULL;
		m_szTableSchema[0] = NULL;
		m_szTableName[0] = NULL;
		m_szIdxCatalog[0] = NULL;
		m_szIdxSchema[0] = NULL;
		m_szIdxName[0] = NULL;
		m_fPrimaryIdx = VARIANT_FALSE;
		m_fUniqueIdx = VARIANT_FALSE;
		m_fClusteredIdx = VARIANT_TRUE;
		m_nIdxType = DBPROPVAL_IT_OTHER;
		m_ulFillFactor = 100;
		m_ulInitSize = 2048;
		m_ulNulls = DBPROPVAL_IN_DISALLOWNULL;
		m_fSortBookmarks = VARIANT_FALSE;
		m_fAutoUpdate = VARIANT_TRUE;
		m_ulNullColl = DBPROPVAL_NC_LOW;
		m_ulOrdinal = 1;
		m_szColumnName[0] = NULL;
		m_guidColumn = GUID_NULL;
		m_ulColumnPropID = 0;
		m_nCollation = DB_COLLATION_ASC;
		m_ui64Cardinality.QuadPart = 0;
		m_ulPages = 0;
		m_szFilter[0] = NULL;
		m_fIntegratedIdx = VARIANT_TRUE;
	}

	BEGIN_PROVIDER_COLUMN_MAP(CINDEXESRow)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szTableCatalog)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szTableSchema)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTableName)
		PROVIDER_COLUMN_ENTRY("INDEX_CATALOG", 4, m_szIdxCatalog)
		PROVIDER_COLUMN_ENTRY("INDEX_SCHEMA", 5, m_szIdxSchema)
		PROVIDER_COLUMN_ENTRY("INDEX_NAME", 6, m_szIdxName)
		PROVIDER_COLUMN_ENTRY_FIXED("PRIMARY_KEY", 7, DBTYPE_BOOL, m_fPrimaryIdx)
		PROVIDER_COLUMN_ENTRY_FIXED("UNIQUE", 8, DBTYPE_BOOL, m_fUniqueIdx)
		PROVIDER_COLUMN_ENTRY_FIXED("CLUSTERED", 9, DBTYPE_BOOL, m_fClusteredIdx)
		PROVIDER_COLUMN_ENTRY("TYPE", 10, m_nIdxType)
		PROVIDER_COLUMN_ENTRY("FILL_FACTOR", 11, m_ulFillFactor)
		PROVIDER_COLUMN_ENTRY("INITIAL_SIZE", 12, m_ulInitSize)
		PROVIDER_COLUMN_ENTRY("NULLS", 13, m_ulNulls)
		PROVIDER_COLUMN_ENTRY_FIXED("SORT_BOOKMARKS", 14, DBTYPE_BOOL, m_fSortBookmarks)
		PROVIDER_COLUMN_ENTRY_FIXED("AUTO_UPDATE", 15, DBTYPE_BOOL, m_fAutoUpdate)
		PROVIDER_COLUMN_ENTRY("NULL_COLLATION", 16, m_ulNullColl)
		PROVIDER_COLUMN_ENTRY("ORDINAL_POSITION", 17, m_ulOrdinal)
		PROVIDER_COLUMN_ENTRY("COLUMN_NAME", 18, m_szColumnName)
		PROVIDER_COLUMN_ENTRY("COLUMN_GUID", 19, m_guidColumn)
		PROVIDER_COLUMN_ENTRY("COLUMN_PROPID", 20, m_ulColumnPropID)
		PROVIDER_COLUMN_ENTRY("COLLATION", 21, m_nCollation)
		PROVIDER_COLUMN_ENTRY("CARDINALITY", 22, m_ui64Cardinality)
		PROVIDER_COLUMN_ENTRY("PAGES", 23, m_ulPages)
		PROVIDER_COLUMN_ENTRY("FILTER_CONDITION", 24, m_szFilter)
		PROVIDER_COLUMN_ENTRY_FIXED("INTEGRATED", 25, DBTYPE_BOOL, m_fIntegratedIdx)
	END_PROVIDER_COLUMN_MAP()

	enum RESTRICT_INDEXES {
		RESTRICT_INDEXES__TABLE_CATALOG = 1,
		RESTRICT_INDEXES__TABLE_SCHEMA = 2,
		RESTRICT_INDEXES__INDEX_NAME = 3,
		RESTRICT_INDEXES__TYPE = 4,
		RESTRICT_INDEXES__TABLE_NAME = 5,
	};

// Restrictions testen
	static bool IndexRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_INDEXES__INDEX_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_INDEXES__INDEX_NAME-1])) {
		// COLUMN_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_INDEXES__INDEX_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_INDEXES__INDEX_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_INDEXES__INDEX_NAME-1]) &&
					CmpQuotedNames(bstrName, V_BSTR(&prgRestrictions[RESTRICT_INDEXES__INDEX_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
	static bool TypeRestrictionApply (short nType, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_INDEXES__TYPE && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_INDEXES__TYPE-1])) {
		// COLUMN_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_INDEXES__TYPE-1])) {
				_ASSERTE(V_ISINTEGER(&prgRestrictions[RESTRICT_INDEXES__TYPE-1]));

			CComVariant v;

				v.ChangeType (VT_I4, &prgRestrictions[RESTRICT_INDEXES__TYPE-1]);
				if (nType != V_I4(&v))
					return true;		// not requested
			}
		}
		return false;
	}
	static bool TableRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_INDEXES__TABLE_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_INDEXES__TABLE_NAME-1])) {
		// TABLE_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_INDEXES__TABLE_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_INDEXES__TABLE_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_INDEXES__TABLE_NAME-1]) &&
					CmpQuotedNames(bstrName, V_BSTR(&prgRestrictions[RESTRICT_INDEXES__TABLE_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}

// Spalte für Objektnummer
	bool FillWithObjNr(BSTR bstrTableName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
	CComBSTR bstrColName;

		bstrColName.LoadString(IDS_OBJNRNAME);
		if (!IndexRestrictionApply (bstrColName, cRestrictions, prgRestrictions) && 
			!TypeRestrictionApply (DBPROPVAL_IT_OTHER, cRestrictions, prgRestrictions)) 
		{
			wcscpy(m_szTableName, bstrTableName);
			wcscpy(m_szIdxName, bstrColName);
			m_fPrimaryIdx = VARIANT_TRUE;
			m_fUniqueIdx = VARIANT_TRUE;
			m_nIdxType = DBPROPVAL_IT_OTHER;
			m_fSortBookmarks = VARIANT_TRUE;
			wcscpy(m_szColumnName, bstrColName);
			return true;
		}
		return false;
	}

// Spalte für ObjektGuid
	bool FillWithGuid(BSTR bstrTableName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
	CComBSTR bstrColName;

		bstrColName.LoadString(IDS_GUIDNAME);
		if (!IndexRestrictionApply (bstrColName, cRestrictions, prgRestrictions) && 
			!TypeRestrictionApply (DBPROPVAL_IT_BTREE, cRestrictions, prgRestrictions)) 
		{
			ClearMembers();

			wcscpy(m_szTableName, bstrTableName);
			wcscpy(m_szIdxName, bstrColName);
			m_fUniqueIdx = VARIANT_TRUE;
			m_nIdxType = DBPROPVAL_IT_BTREE;
			wcscpy(m_szColumnName, bstrColName);
			return true;
		}
		return false;
	}
};

class CTRiASOleDBSessionIdxSchemaRowset : 
	public CSchemaRowsetImpl<CTRiASOleDBSessionIdxSchemaRowset, CINDEXESRow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionIdxSchemaRowset)
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

	HRESULT Execute(LONG *pcRowsAffected, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		m_ObjNrRows.clear();		// vorbereiten

	// Idents der geöffneten GeoDB
	// zugehöriges DataSourceObjekt besorgen
	CTRiASOleDBSource *pDataSource = NULL;

		RETURN_ERROR(GetDataSourceObject(this, &pDataSource));

	// Idents der geöffneten GeoDB
	CComPtr<ITRiASEnumNativeIdents> Idents;

		RETURN_ERROR(pDataSource -> get_Classes(&Idents));

	// alle Tabellen (Objektklassen) enumerieren und nach Spalten befragen hinzufügen
	CComPtr<IUnknown> UnkEnum;

		RETURN_ERROR(Idents -> get__NewEnum (&UnkEnum));

	// Helper für Objektklasse  instantiieren
	CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
	CComPtr<ITRiASNativeIdent> Ident;
	INT_PTR hPr = NULL;

		RETURN_ERROR(Ident.CoCreateInstance(CLSID_TRiASNativeIdent));
		RETURN_ERROR(pDataSource -> EnsureDatasourceOpened(&hPr));		// DatenbankHandle besorgen

	// alle Tabellen durchgehen
	CComVariant v;
	LONG lCnt = 0;

		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		CComBSTR bstrName;

			RETURN_ERROR(Ident -> get_Name (hPr, V_I4(&v), &bstrName));

		// entscheiden, wie Geometrie abgebildet werden soll
		LONG lCntTable = 0;

#if defined(_USE_PROP_GEOMETRYAS)
			if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
			// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
			// 4 separaten Spalten

			// Restrictions auswerten
				if (CINDEXESRow::TableRestrictionApply(bstrName, cRestrictions, prgRestrictions))
					continue;

			// die Objekteigenschaften dieser Objektklasse behandeln
				RETURN_ERROR(FillWithAttributesColumns(pDataSource, V_I4(&v), bstrName, Ident, lCnt, cRestrictions, prgRestrictions, &lCntTable));
				lCnt += lCntTable;
			}
			else 
#endif // defined(_USE_PROP_GEOMETRYAS)
			{
			// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
			// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
			DWORD dwTypes = 0;

				RETURN_ERROR(Ident -> get_Types (hPr, V_I4(&v), &dwTypes));
				if (0 == dwTypes) continue;		// no objects no fun

				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (!(s_rgTypes[i].dwType & dwTypes))
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				CComBSTR bstrTypeName (bstrName);

					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrTypeName.Append(s_rgTypes[i].pcoleObjTypeName);
					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);

				// Restrictions auswerten
					if (CINDEXESRow::TableRestrictionApply(bstrTypeName, cRestrictions, prgRestrictions))
						continue;

				// die Objekteigenschaften dieser Objektklasse behandeln
					RETURN_ERROR(FillWithAttributesTables(pDataSource, i, V_I4(&v), bstrTypeName, Ident, lCnt, cRestrictions, prgRestrictions, &lCntTable));
					lCnt += lCntTable;
				}

#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
			// Alle Objekte einer Objektklasse sind in einer View abgebildet
			// Restrictions auswerten
				if (CINDEXESRow::TableRestrictionApply(bstrName, cRestrictions, prgRestrictions))
					continue;

			// die Objekteigenschaften dieser Objektklasse behandeln
				RETURN_ERROR(FillWithAttributesColumns(pDataSource, V_I4(&v), bstrName, Ident, lCnt, cRestrictions, prgRestrictions, &lCntTable, true));
				lCnt += lCntTable;
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)
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
		case 4:		// INDEX_CATALOG
		case 5:		// INDEX_SCHEMA
		case 19:	// COLUMN_GUID
		case 24:	// FILTER_CONDITION
			return DBSTATUS_S_ISNULL;

		case 20:	// m_ulColumnPropID
			if (m_ObjNrRows.find(pRow -> m_iRowset) != m_ObjNrRows.end() ||		// Objektnummer
				m_ObjNrRows.find(pRow -> m_iRowset - 1) != m_ObjNrRows.end())	// Guid
				return DBSTATUS_S_ISNULL;
			break;

		default:
			break;
		}
		return DBSTATUS_S_OK;
	}

protected:
#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 4 separaten Spalten
	HRESULT FillWithAttributesColumns (
		CTRiASOleDBSource *pDataSource, INT_PTR lIdent, BSTR bstrTableName, ITRiASNativeIdent *pIIdent, 
		LONG lCntStart, ULONG cRestrictions, const VARIANT *prgRestrictions, LONG *pcRowsAffected,
		bool fOneGeometry = false)
	{
		_ASSERTE(NULL != pDataSource);

	// Objekttypen feststellen
	INT_PTR hPr = pDataSource->GetProjectHandle();
	DWORD dwTypes = 0;

		RETURN_ERROR(pIIdent -> get_Types (hPr, lIdent, &dwTypes));
		if (0 == dwTypes) return S_OK;		// no objects, no fun

	DWORD lPoints, lLines, lAreas, lTexts, lCounts;

		RETURN_ERROR(pIIdent -> get_Counts (hPr, lIdent, &lPoints, &lLines, &lAreas, &lTexts, &lCounts));

	// alle Objekteigenschaften durchgehen
	CComPtr<ITRiASEnumNativeAttributes> Attribs;
	CComPtr<IUnknown> UnkEnum;

		RETURN_ERROR(pIIdent -> get_Attributes(hPr, lIdent, &Attribs));
		RETURN_ERROR(Attribs -> get__NewEnum (&UnkEnum));

	// Helper für Objektklasse  instantiieren
	CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
	CComPtr<ITRiASNativeAttribute> Attrib;

		RETURN_ERROR(Attrib.CoCreateInstance(CLSID_TRiASNativeAttribute));

	// alle Spalten durchgehen
	CComVariant v;
	LONG lCnt = 0;

	// Objektnummer ist ein eigener Index
	CINDEXESRow crData;

		if (crData.FillWithObjNr(bstrTableName, cRestrictions, prgRestrictions)) {
			crData.m_ui64Cardinality.QuadPart = lCounts;
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			m_ObjNrRows.insert(lCntStart);		// Rows mit Objektnummern speichern
			++lCnt;
		}

	// ObjektGuid ist ein eigener Index
		if (crData.FillWithGuid(bstrTableName, cRestrictions, prgRestrictions)) {
			crData.m_ui64Cardinality.QuadPart = lCounts;
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			++lCnt;
		}

	// normale Objekteigenschaften aufzählen
		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		// die Objekteigenschaft zu RowSet hinzufügen
		CComBSTR bstrName, bstrDesc;
		INT_PTR lMCode = 0;

			RETURN_ERROR(Attrib -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc));
			if (FAILED(pDataSource -> get_Attribute (lIdent, bstrName, &lMCode)))
				continue;		// nur in Pbd definierte Objekteigenschaft
			_ASSERTE(V_I4(&v) == lMCode);

		// Restrictions auswerten
			if (CINDEXESRow::IndexRestrictionApply(bstrName, cRestrictions, prgRestrictions) ||
				CINDEXESRow::TypeRestrictionApply(DBPROPVAL_IT_BTREE, cRestrictions, prgRestrictions))
				continue;

		// RowSet-Zeile füllen
			crData.ClearMembers();
			wcscpy(crData.m_szTableName, bstrTableName);
			wcscpy(crData.m_szIdxName, bstrName);
			crData.m_nIdxType = DBPROPVAL_IT_BTREE;
			crData.m_fSortBookmarks = VARIANT_TRUE;
			crData.m_ulColumnPropID = lMCode;
			wcscpy(crData.m_szColumnName, bstrName);

			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			++lCnt;
		}
		*pcRowsAffected = lCnt;
		return S_OK;
	}
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)

// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
	HRESULT FillWithAttributesTables (
		CTRiASOleDBSource *pDataSource, int iTypeIndex, INT_PTR lIdent, BSTR bstrTableName, ITRiASNativeIdent *pIIdent, 
		LONG lCntStart, ULONG cRestrictions, const VARIANT *prgRestrictions, LONG *pcRowsAffected)
	{
		_ASSERTE(NULL != pDataSource);
		_ASSERTE(0 <= iTypeIndex && iTypeIndex < _countof(s_rgTypes));

	INT_PTR hPr = pDataSource -> GetProjectHandle();
	CComPtr<ITRiASEnumNativeAttributes> Attribs;
	CComPtr<IUnknown> UnkEnum;

		RETURN_ERROR(pIIdent -> get_Attributes(hPr, lIdent, &Attribs));
		RETURN_ERROR(Attribs -> get__NewEnum (&UnkEnum));

	DWORD lCounts[4], lCountAll;

		RETURN_ERROR(pIIdent -> get_Counts (hPr, lIdent, &lCounts[0], &lCounts[1], &lCounts[2], &lCounts[3], &lCountAll));

	// Helper für Objektklasse  instantiieren
	CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
	CComPtr<ITRiASNativeAttribute> Attrib;

		RETURN_ERROR(Attrib.CoCreateInstance(CLSID_TRiASNativeAttribute));

	// alle Spalten durchgehen
	CComVariant v;
	LONG lCnt = 0;

	// Objektnummer ist eine eigene Spalte
	CINDEXESRow crData;

		if (crData.FillWithObjNr(bstrTableName, cRestrictions, prgRestrictions)) {
			crData.m_ui64Cardinality.QuadPart = lCounts[iTypeIndex];
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			m_ObjNrRows.insert(lCntStart);		// Rows mit Objektnummern speichern
			++lCnt;
		}

	// ObjektGuid ist eine eigene Spalte
		if (crData.FillWithGuid(bstrTableName, cRestrictions, prgRestrictions)) {
			crData.m_ui64Cardinality.QuadPart = lCounts[iTypeIndex];
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			++lCnt;
		}

	// normale Objekteigenschaften aufzählen
		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		// die Objekteigenschaft zu RowSet hinzufügen
		CComBSTR bstrName, bstrDesc;

			RETURN_ERROR(Attrib -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc));

		INT_PTR lMCode = 0;

			if (FAILED(pDataSource -> get_Attribute (lIdent, bstrName, &lMCode)))
				continue;		// nur in Pbd definierte Objekteigenschaft
			_ASSERTE(V_I4(&v) == lMCode);

		// Restrictions auswerten
			if (CINDEXESRow::IndexRestrictionApply(bstrName, cRestrictions, prgRestrictions) ||
				CINDEXESRow::TypeRestrictionApply(DBPROPVAL_IT_BTREE, cRestrictions, prgRestrictions))
				continue;

		// RowSet-Zeile füllen
			crData.ClearMembers();
			wcscpy(crData.m_szTableName, bstrTableName);
			wcscpy(crData.m_szIdxName, bstrName);
			crData.m_nIdxType = DBPROPVAL_IT_BTREE;
			crData.m_ulNulls = DBPROPVAL_IN_IGNORENULL;
			crData.m_fSortBookmarks = VARIANT_TRUE;
			crData.m_ulColumnPropID = lMCode;
			wcscpy(crData.m_szColumnName, bstrName);

			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			++lCnt;
		}
		*pcRowsAffected = lCnt;
		return S_OK;
	}

private:
	set<CSimpleRow::KeyType> m_ObjNrRows;
};

#endif // !defined(_TRIASOLEDBSESSIONIDXSCHEMAROWSET_H__2F19D66A_22E3_442F_85A4_65839560D3A9__INCLUDED_)
