// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:11:34 
//
// @doc
// @module TRiASOleDBSessionColSchemaRowset.h | Declaration of the <c CTRiASOleDBSessionColSchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONCOLSCHEMAROWSET_H__B1192F28_A02E_4DFF_AC67_BE9AEC6A56B3__INCLUDED_)
#define _TRIASOLEDBSESSIONCOLSCHEMAROWSET_H__B1192F28_A02E_4DFF_AC67_BE9AEC6A56B3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionColSchemaRowset: RowSet aller verfügbaren Spalten
class CCOLUMNSRowEx :
	public CCOLUMNSRow
{
public:
	BEGIN_PROVIDER_COLUMN_MAP(CCOLUMNSRowEx)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szTableCatalog)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szTableSchema)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTableName)
		PROVIDER_COLUMN_ENTRY("COLUMN_NAME", 4, m_szColumnName)
		PROVIDER_COLUMN_ENTRY("COLUMN_GUID", 5, m_guidColumn)
		PROVIDER_COLUMN_ENTRY("COLUMN_PROPID", 6, m_ulColumnPropID)
		PROVIDER_COLUMN_ENTRY("ORDINAL_POSITION", 7, m_ulOrdinalPosition)
		PROVIDER_COLUMN_ENTRY_FIXED("COLUMN_HASDEFAULT", 8, DBTYPE_BOOL, m_bColumnHasDefault)
		PROVIDER_COLUMN_ENTRY("COLUMN_DEFAULT", 9, m_szColumnDefault)
		PROVIDER_COLUMN_ENTRY("COLUMN_FLAGS", 10, m_ulColumnFlags)
		PROVIDER_COLUMN_ENTRY_FIXED("IS_NULLABLE", 11, DBTYPE_BOOL, m_bIsNullable)
		PROVIDER_COLUMN_ENTRY("DATA_TYPE", 12, m_nDataType)
		PROVIDER_COLUMN_ENTRY("TYPE_GUID", 13, m_guidType)
		PROVIDER_COLUMN_ENTRY("CHARACTER_MAXIMUM_LENGTH", 14, m_ulCharMaxLength)
		PROVIDER_COLUMN_ENTRY("CHARACTER_OCTET_LENGTH", 15, m_ulCharOctetLength)
		PROVIDER_COLUMN_ENTRY("NUMERIC_PRECISION", 16, m_nNumericPrecision)
		PROVIDER_COLUMN_ENTRY("NUMERIC_SCALE", 17, m_nNumericScale)
		PROVIDER_COLUMN_ENTRY("DATETIME_PRECISION", 18, m_ulDateTimePrecision)
		PROVIDER_COLUMN_ENTRY("CHARACTER_SET_CATALOG", 19, m_szCharSetCatalog)
		PROVIDER_COLUMN_ENTRY("CHARACTER_SET_SCHEMA", 20, m_szCharSetSchema)
		PROVIDER_COLUMN_ENTRY("CHARACTER_SET_NAME", 21, m_szCharSetName)
		PROVIDER_COLUMN_ENTRY("COLLATION_CATALOG", 22, m_szCollationCatalog)
		PROVIDER_COLUMN_ENTRY("COLLATION_SCHEMA", 23, m_szCollationSchema)
		PROVIDER_COLUMN_ENTRY("COLLATION_NAME", 24, m_szCollationName)
		PROVIDER_COLUMN_ENTRY("DOMAIN_CATALOG", 25, m_szDomainCatalog)
		PROVIDER_COLUMN_ENTRY("DOMAIN_SCHEMA", 26, m_szDomainSchema)
		PROVIDER_COLUMN_ENTRY("DOMAIN_NAME", 27, m_szDomainName)
		PROVIDER_COLUMN_ENTRY("DESCRIPTION", 28, m_szDescription)
	END_PROVIDER_COLUMN_MAP()

	enum RESTRICT_COLUMNS {
		RESTRICT_COLUMNS__TABLE_CATALOG = 1,
		RESTRICT_COLUMNS__TABLE_SCHEMA = 2,
		RESTRICT_COLUMNS__TABLE_NAME = 3,
		RESTRICT_COLUMNS__COLUMN_NAME = 4,
	};

// Restrictions testen
	static bool ColumnRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_COLUMNS__COLUMN_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_COLUMNS__COLUMN_NAME-1])) {
		// COLUMN_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_COLUMNS__COLUMN_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_COLUMNS__COLUMN_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_COLUMNS__COLUMN_NAME-1]) &&
					CmpQuotedNames(bstrName, V_BSTR(&prgRestrictions[RESTRICT_COLUMNS__COLUMN_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
	static bool TableRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_COLUMNS__TABLE_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_COLUMNS__TABLE_NAME-1])) {
		// TABLE_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_COLUMNS__TABLE_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_COLUMNS__TABLE_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_COLUMNS__TABLE_NAME-1]) &&
					CmpQuotedNames(bstrName, V_BSTR(&prgRestrictions[RESTRICT_COLUMNS__TABLE_NAME-1])))
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
		if (!ColumnRestrictionApply (bstrColName, cRestrictions, prgRestrictions)) {
			wcscpy(m_szTableName, bstrTableName);
			wcscpy(m_szColumnName, bstrColName);
			wcscpy(m_szDescription, bstrColName);
			m_ulOrdinalPosition = 1;
			m_bColumnHasDefault = VARIANT_FALSE;
			m_ulColumnFlags = DBCOLUMNFLAGS_ISROWID|DBCOLUMNFLAGS_ISFIXEDLENGTH;
			m_bIsNullable = VARIANT_FALSE;
			m_nDataType = DBTYPE_UI4;
			m_nNumericPrecision = 10;
			return true;
		}
		return false;
	}

// Spalte für ObjektGuid
	bool FillWithGuid(BSTR bstrTableName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
	CComBSTR bstrColName;

		bstrColName.LoadString(IDS_GUIDNAME);
		if (!ColumnRestrictionApply (bstrColName, cRestrictions, prgRestrictions)) {
			ClearMembers();

			wcscpy(m_szTableName, bstrTableName);
			wcscpy(m_szColumnName, bstrColName);
			wcscpy(m_szDescription, bstrColName);
			m_ulOrdinalPosition = 2;
			m_bColumnHasDefault = VARIANT_FALSE;
			m_ulColumnFlags = DBCOLUMNFLAGS_ISFIXEDLENGTH|DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED;	//|DBCOLUMNFLAGS_WRITE;
			m_bIsNullable = VARIANT_FALSE;
			m_nDataType = DBTYPE_GUID;
			return true;
		}
		return false;
	}

// Spalte für Geometrie
	bool FillWithGeometry(BSTR bstrTableName, ULONG cRestrictions, const VARIANT *prgRestrictions, 
		LPCOLESTR pcoleGeomName, ULONG ulCnt, UINT uiResId = IDS_GEOMETRYNAME)
	{
		if (!ColumnRestrictionApply (pcoleGeomName, cRestrictions, prgRestrictions)) {
			ClearMembers();

		CComBSTR bstrColName;

			bstrColName.LoadString(uiResId);

			wcscpy(m_szTableName, bstrTableName);
			wcscpy(m_szColumnName, pcoleGeomName);
			wcscpy(m_szDescription, bstrColName);
			m_ulOrdinalPosition = ulCnt;
			m_bColumnHasDefault = VARIANT_FALSE;
			m_ulColumnFlags = DBCOLUMNFLAGS_ISLONG;		// |DBCOLUMNFLAGS_WRITE;
			m_bIsNullable = VARIANT_FALSE;
			m_nDataType = DBTYPE_BYTES;
			return true;
		}
		return false;
	}
};

class CTRiASOleDBSessionColSchemaRowset : 
	public CSchemaRowsetImpl<CTRiASOleDBSessionColSchemaRowset, CCOLUMNSRowEx, CTRiASOleDBSession, 
		CAtlArray<CCOLUMNSRow> >
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionColSchemaRowset)
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
		m_GeometryRows.clear();

	// Idents der geöffneten GeoDB
	// zugehöriges DataSourceObjekt besorgen
	CTRiASOleDBSource *pDataSource = NULL;

		RETURN_FAILED_HRESULT(GetDataSourceObject(this, &pDataSource));

	// Idents der geöffneten GeoDB
	CComPtr<ITRiASEnumNativeIdents> Idents;

		RETURN_FAILED_HRESULT(pDataSource -> get_Classes(&Idents));

	// alle Tabellen (Objektklassen) enumerieren und nach Spalten befragen hinzufügen
	CComPtr<IUnknown> UnkEnum;

		RETURN_FAILED_HRESULT(Idents -> get__NewEnum (&UnkEnum));

	// Helper für Objektklasse  instantiieren
	CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
	CComPtr<ITRiASNativeIdent> Ident;
	INT_PTR hPr = NULL;

		RETURN_FAILED_HRESULT(Ident.CoCreateInstance(CLSID_TRiASNativeIdent));
		RETURN_FAILED_HRESULT(pDataSource -> EnsureDatasourceOpened(&hPr));		// DatenbankHandle besorgen

	// alle Tabellen durchgehen
	CComVariant v;
	LONG lCnt = 0;

		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		CComBSTR bstrName;

			RETURN_FAILED_HRESULT(Ident -> get_Name (hPr, V_I4(&v), &bstrName));

		// entscheiden, wie Geometrie abgebildet werden soll
		LONG lCntTable = 0;

#if defined(_USE_PROP_GEOMETRYAS)
			if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
			// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
			// 4 separaten Spalten

			// Restrictions auswerten
				if (CCOLUMNSRowEx::TableRestrictionApply(bstrName, cRestrictions, prgRestrictions))
					continue;

			// die Objekteigenschaften dieser Objektklasse behandeln
				RETURN_FAILED_HRESULT(FillWithAttributesColumns(pDataSource, V_I4(&v), bstrName, Ident, lCnt, cRestrictions, prgRestrictions, &lCntTable));
				lCnt += lCntTable;
			}
			else 
#endif // defined(_USE_PROP_GEOMETRYAS)
			{
			// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
			// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
			DWORD dwTypes = 0;

				RETURN_FAILED_HRESULT(Ident -> get_Types (hPr, V_I4(&v), &dwTypes));
				if (0 == dwTypes) continue;		// no objects no fun

				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (!(s_rgTypes[i].dwType & dwTypes))
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				CComBSTR bstrTypeName (bstrName);

					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrTypeName.Append(s_rgTypes[i].pcoleObjTypeName);
					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);

				// Restrictions auswerten
					if (CCOLUMNSRowEx::TableRestrictionApply(bstrTypeName, cRestrictions, prgRestrictions))
						continue;

				// die Objekteigenschaften dieser Objektklasse behandeln
					RETURN_FAILED_HRESULT(FillWithAttributesTables(pDataSource, V_I4(&v), bstrTypeName, Ident, lCnt, cRestrictions, prgRestrictions, &lCntTable));
					lCnt += lCntTable;
				}

#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
				if (pDataSource -> GetViewMode()) {
				// Alle Objekte einer Objektklasse sind in einer View abgebildet
				// Restrictions auswerten
					if (CCOLUMNSRowEx::TableRestrictionApply(bstrName, cRestrictions, prgRestrictions))
						continue;

				// die Objekteigenschaften dieser Objektklasse behandeln
					RETURN_FAILED_HRESULT(FillWithAttributesColumns(pDataSource, V_I4(&v), bstrName, Ident, lCnt, cRestrictions, prgRestrictions, &lCntTable, true));
					lCnt += lCntTable;
				}
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
		case 5:		// COLUMN_GUID
		case 9:		// COLUMN_DEFAULT
		case 13:	// TYPE_GUID
		case 17:	// NUMERIC_SCALE
		case 18:	// DATETIME_PRECISION
		case 19:	// CHARACTER_SET_CATALOG
		case 20:	// CHARACTER_SET_SCHEMA
		case 21:	// CHARACTER_SET_NAME
		case 22:	// COLLATION_CATALOG
		case 23:	// COLLATION_SCHEMA
		case 24:	// COLLATION_NAME
		case 25:	// DOMAIN_CATALOG
		case 26:	// DOMAIN_SCHEMA
		case 27:	// DOMAIN_NAME
			return DBSTATUS_S_ISNULL;

		case 6:		// COLUMN_PROPID
		case 14:	// CHARACTER_MAXIMUM_LENGTH
		case 15:	// CHARACTER_OCTET_LENGTH
			if (m_ObjNrRows.find(pRow -> m_iRowset) != m_ObjNrRows.end() ||		
				m_ObjNrRows.find(pRow -> m_iRowset-1) != m_ObjNrRows.end() ||
				m_GeometryRows.find(pRow -> m_iRowset) != m_GeometryRows.end())
			// Objektnummern, Geometrien oder Guids
				return DBSTATUS_S_ISNULL;
			
			break;

		case 16:	// NUMERIC_PRECISION
			if (m_ObjNrRows.find(pRow -> m_iRowset) == m_ObjNrRows.end())
			// nicht Objektnummern 
				return DBSTATUS_S_ISNULL;
			break;

		default:
			break;
		}
		return DBSTATUS_S_OK;
	}

protected:
#if defined(_USE_PROP_GEOMETRYAS) || defined(_USE_PREDEFINED_GEOMETRYVIEWS)
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

		RETURN_FAILED_HRESULT(pIIdent -> get_Types (hPr, lIdent, &dwTypes));
		if (0 == dwTypes) return S_OK;		// no objects, no fun

	// alle Objekteigenschaften durchgehen
	CComPtr<ITRiASEnumNativeAttributes> Attribs;
	CComPtr<IUnknown> UnkEnum;

		RETURN_FAILED_HRESULT(pIIdent -> get_Attributes(hPr, lIdent, &Attribs));
		RETURN_FAILED_HRESULT(Attribs -> get__NewEnum (&UnkEnum));

	// Helper für Objektklasse  instantiieren
	CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
	CComPtr<ITRiASNativeAttribute> Attrib;

		RETURN_FAILED_HRESULT(Attrib.CoCreateInstance(CLSID_TRiASNativeAttribute));

	// alle Spalten durchgehen
	CComVariant v;
	LONG lCnt = 0;

	// Objektnummer ist eine eigene Spalte
	CCOLUMNSRowEx crData;

		if (crData.FillWithObjNr(bstrTableName, cRestrictions, prgRestrictions)) {
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			m_ObjNrRows.insert(lCntStart);		// Rows mit Objektnummern speichern
			++lCnt;
		}

	// ObjektGuid ist eine eigene Spalte
		if (crData.FillWithGuid(bstrTableName, cRestrictions, prgRestrictions)) {
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			++lCnt;
		}

		if (!fOneGeometry) {
		// jeder GeometrieTyp ist eine eigene Spalte
			for (int i = 0; i < _countof(s_rgTypes); ++i) {
				if (!(s_rgTypes[i].dwType & dwTypes))
					continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				if (crData.FillWithGeometry(bstrTableName, cRestrictions, prgRestrictions, s_rgTypes[i].pcoleGeomName, lCnt+1, s_rgTypes[i].uiResIdDesc)) {
					if (!m_rgRowData.Add(crData))
						return E_OUTOFMEMORY;
					m_GeometryRows.insert(lCntStart + lCnt);
					++lCnt;
				}
			}
		}
		else {
		// alle Geometrien sind in einer Spalte
			if (crData.FillWithGeometry(bstrTableName, cRestrictions, prgRestrictions, OLESTR("OGIS_GEOMETRY"), lCnt+1)) {
				if (!m_rgRowData.Add(crData))
					return E_OUTOFMEMORY;
				m_GeometryRows.insert(lCntStart + lCnt);
				++lCnt;
			}
		}

	// normale Objekteigenschaften aufzählen
		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		// die Objekteigenschaft zu RowSet hinzufügen
		CComBSTR bstrName, bstrDesc;
		INT_PTR lMCode = 0;

			RETURN_FAILED_HRESULT(Attrib -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc));
			if (FAILED(pDataSource -> get_Attribute (lIdent, bstrName, &lMCode)))
				continue;		// nur in Pbd definierte Objekteigenschaft
			_ASSERTE(V_I4(&v) == lMCode);

		// Restrictions auswerten
			if (CCOLUMNSRowEx::ColumnRestrictionApply (bstrName, cRestrictions, prgRestrictions))
				continue;

		// RowSet-Zeile füllen
			crData.ClearMembers();
			wcscpy(crData.m_szTableName, bstrTableName);
			wcscpy(crData.m_szColumnName, bstrName);
			wcscpy(crData.m_szDescription, bstrDesc);
			crData.m_bColumnHasDefault = VARIANT_TRUE;
			crData.m_ulColumnFlags = DBCOLUMNFLAGS_ISNULLABLE|DBCOLUMNFLAGS_MAYBENULL;	//|DBCOLUMNFLAGS_WRITE;
			crData.m_bIsNullable = VARIANT_TRUE;
			crData.m_nDataType = DBTYPE_WSTR;
			crData.m_ulCharMaxLength = LONG_MAX;
			crData.m_ulCharOctetLength = LONG_MAX;
			crData.m_ulOrdinalPosition = ++lCnt;
			crData.m_ulColumnPropID = lMCode;

			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
		}
		*pcRowsAffected = lCnt;
		return S_OK;
	}
#endif // defined(_USE_PROP_GEOMETRYAS) || defined(_USE_PREDEFINED_GEOMETRYVIEWS)

// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
	HRESULT FillWithAttributesTables (
		CTRiASOleDBSource *pDataSource, INT_PTR lIdent, BSTR bstrTableName, ITRiASNativeIdent *pIIdent, 
		LONG lCntStart, ULONG cRestrictions, const VARIANT *prgRestrictions, LONG *pcRowsAffected)
	{
		_ASSERTE(NULL != pDataSource);

	INT_PTR hPr = pDataSource -> GetProjectHandle();
	CComPtr<ITRiASEnumNativeAttributes> Attribs;
	CComPtr<IUnknown> UnkEnum;

		RETURN_FAILED_HRESULT(pIIdent -> get_Attributes(hPr, lIdent, &Attribs));
		RETURN_FAILED_HRESULT(Attribs -> get__NewEnum (&UnkEnum));

	// Helper für Objektklasse  instantiieren
	CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
	CComPtr<ITRiASNativeAttribute> Attrib;

		RETURN_FAILED_HRESULT(Attrib.CoCreateInstance(CLSID_TRiASNativeAttribute));

	// alle Spalten durchgehen
	CComVariant v;
	LONG lCnt = 0;

	// Objektnummer ist eine eigene Spalte
	CCOLUMNSRowEx crData;

		if (crData.FillWithObjNr(bstrTableName, cRestrictions, prgRestrictions)) {
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			m_ObjNrRows.insert(lCntStart);		// Rows mit Objektnummern speichern
			++lCnt;
		}

	// ObjektGuid ist eine eigene Spalte
		if (crData.FillWithGuid(bstrTableName, cRestrictions, prgRestrictions)) {
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			++lCnt;
		}

	// die Geometrie ist eine eigene Spalte
		if (crData.FillWithGeometry(bstrTableName, cRestrictions, prgRestrictions, OLESTR("OGIS_GEOMETRY"), lCnt+1)) {
			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
			m_GeometryRows.insert(lCntStart + lCnt);
			++lCnt;
		}

	// normale Objekteigenschaften aufzählen
		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		// die Objekteigenschaft zu RowSet hinzufügen
		CComBSTR bstrName, bstrDesc;

			RETURN_FAILED_HRESULT(Attrib -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc));

		INT_PTR lMCode = 0;

			if (FAILED(pDataSource -> get_Attribute (lIdent, bstrName, &lMCode)))
				continue;		// nur in Pbd definierte Objekteigenschaft
			_ASSERTE(V_I4(&v) == lMCode);

		// Restrictions auswerten
			if (CCOLUMNSRowEx::ColumnRestrictionApply (bstrName, cRestrictions, prgRestrictions))
				continue;

		// RowSet-Zeile füllen
			crData.ClearMembers();
			wcscpy(crData.m_szTableName, bstrTableName);
			wcscpy(crData.m_szColumnName, bstrName);
			wcscpy(crData.m_szDescription, bstrDesc);
			crData.m_bColumnHasDefault = VARIANT_TRUE;
			crData.m_ulColumnFlags = DBCOLUMNFLAGS_ISNULLABLE|DBCOLUMNFLAGS_MAYBENULL|DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED;	//|DBCOLUMNFLAGS_WRITE;
			crData.m_bIsNullable = VARIANT_TRUE;
			crData.m_nDataType = DBTYPE_WSTR;
			crData.m_ulCharMaxLength = LONG_MAX;
			crData.m_ulCharOctetLength = LONG_MAX;
			crData.m_ulOrdinalPosition = ++lCnt;
			crData.m_ulColumnPropID = lMCode;

			if (!m_rgRowData.Add(crData))
				return E_OUTOFMEMORY;
		}
		*pcRowsAffected = lCnt;
		return S_OK;
	}

private:
	set<CSimpleRow::KeyType> m_ObjNrRows;
	set<CSimpleRow::KeyType> m_GeometryRows;
};

#endif // !defined(_TRIASOLEDBSESSIONCOLSCHEMAROWSET_H__B1192F28_A02E_4DFF_AC67_BE9AEC6A56B3__INCLUDED_)
