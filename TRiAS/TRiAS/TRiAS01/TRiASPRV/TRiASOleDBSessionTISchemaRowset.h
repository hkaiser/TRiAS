// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:09:52 
//
// @doc
// @module TRiASOleDBSessionTISchemaRowset.h | Declaration of the <c CTRiASOleDBSessionTISchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONTISCHEMAROWSET_H__312EDBF1_7254_43CD_A554_7F0303118C2D__INCLUDED_)
#define _TRIASOLEDBSESSIONTISCHEMAROWSET_H__312EDBF1_7254_43CD_A554_7F0303118C2D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionTISchemaRowset: Table Information Schema Rowset
class CTABLEINFORow 
{
public:
	WCHAR m_szCatalog[129];
	WCHAR m_szSchema[129];
	WCHAR m_szTable[129];
	WCHAR m_szType[129];
	GUID  m_guid;
	VARIANT_BOOL m_fBookmarks;
	LONG m_uiBookmarkType;
	USHORT m_uiBookmarkDataType;
	ULONG m_ulBookmarkMaxLen;
	ULONG m_ulBookmarkInfo;
	LARGE_INTEGER m_i64TableVersion;
	ULARGE_INTEGER m_ui64Cardinality;
	WCHAR m_szDesc[257];
	ULONG m_ulPropID;

	CTABLEINFORow() 
	{
		ClearMembers();
	}

	void ClearMembers()
	{
		m_szCatalog[0] = NULL;
		m_szSchema[0] = NULL;
		m_szTable[0] = NULL;
		m_szType[0] = NULL;
		m_guid = GUID_NULL;
		m_fBookmarks = VARIANT_TRUE;					// Objektnummer
		m_uiBookmarkType = DBPROPVAL_BMK_NUMERIC;
		m_uiBookmarkDataType = DBTYPE_I4;
		m_ulBookmarkMaxLen = sizeof(LONG);
		m_ulBookmarkInfo = DBPROPVAL_BI_CROSSROWSET;
		m_i64TableVersion.QuadPart = 0;
		m_ui64Cardinality.QuadPart = 0;
		m_szDesc[0] = NULL;
		m_ulPropID = 0;
	}

	BEGIN_PROVIDER_COLUMN_MAP(CTABLEINFORow)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szCatalog)	// restriction 1 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szSchema)	// restriction 2 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTable)		// restriction 3
		PROVIDER_COLUMN_ENTRY("TABLE_TYPE", 4, m_szType)		// restriction 4
		PROVIDER_COLUMN_ENTRY("TABLE_GUID", 5, m_guid)
		PROVIDER_COLUMN_ENTRY_FIXED("BOOKMARKS", 6, DBTYPE_BOOL, m_fBookmarks)
		PROVIDER_COLUMN_ENTRY("BOOKMARK_TYPE", 7, m_uiBookmarkType)
		PROVIDER_COLUMN_ENTRY("BOOKMARK_DATATYPE", 8, m_uiBookmarkDataType)
		PROVIDER_COLUMN_ENTRY("BOOKMARK_MAXIMUM_LENGTH", 9, m_ulBookmarkMaxLen)
		PROVIDER_COLUMN_ENTRY("BOOKMARK_INFORMATION", 10, m_ulBookmarkInfo)
		PROVIDER_COLUMN_ENTRY("TABLE_VERSION", 11, m_i64TableVersion)
		PROVIDER_COLUMN_ENTRY("CARDINALITY", 12, m_ui64Cardinality)
		PROVIDER_COLUMN_ENTRY("DESCRIPTION", 13, m_szDesc)
		PROVIDER_COLUMN_ENTRY("TABLE_PROPID", 14, m_ulPropID)
	END_PROVIDER_COLUMN_MAP()

	enum RESTRICT_TABLEINFO {
		RESTRICT_TABLEINFO__TABLE_CATALOG = 1,
		RESTRICT_TABLEINFO__TABLE_SCHEMA = 2,
		RESTRICT_TABLEINFO__TABLE_NAME = 3,
		RESTRICT_TABLEINFO__TABLE_TYPE = 4,
	};

// Restrictions testen
	static bool TableNameRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_TABLEINFO__TABLE_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_NAME-1])) {
		// TABLE_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_NAME-1]) &&
					CmpQuotedNames (bstrName, V_BSTR(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
	static bool TableTypeRestrictionApply (LPCOLESTR bstrType, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_TABLEINFO__TABLE_TYPE && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_TYPE-1])) {
		// TABLE_TYPE restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_TYPE-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_TYPE-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_TYPE-1]) &&
					wcscmp(bstrType, V_BSTR(&prgRestrictions[RESTRICT_TABLEINFO__TABLE_TYPE-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
};

class CTRiASOleDBSessionTISchemaRowset :
	public CSchemaRowsetImpl<CTRiASOleDBSessionTISchemaRowset, CTABLEINFORow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionTISchemaRowset)
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

	HRESULT Execute (LONG* pcRowsAffected, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
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
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		CComBSTR bstrName, bstrDesc, bstrOKS;

			RETURN_FAILED_HRESULT(Ident -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc, &bstrOKS));

		// entscheiden, wie Geometrie abgebildet werden soll
#if defined(_USE_PROP_GEOMETRYAS)
			if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
			// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
			// 4 separaten Spalten

			// Restrictions auswerten
				if (CTABLEINFORow::TableNameRestrictionApply (bstrName, cRestrictions, prgRestrictions) ||
					CTABLEINFORow::TableTypeRestrictionApply (OLESTR("TABLE"), cRestrictions, prgRestrictions))
				{
					continue;
				}

			CTABLEINFORow trData;
			DWORD lPoints, lLines, lAreas, lTexts, lCounts;

				RETURN_FAILED_HRESULT(Ident -> get_Counts (hPr, V_I4(&v), &lPoints, &lLines, &lAreas, &lTexts, &lCounts));

				trData.m_ulPropID = V_I4(&v);				// Identifikator
				wcscpy(trData.m_szTable, bstrName);
				wcscpy(trData.m_szType, OLESTR("TABLE"));
				trData.m_ui64Cardinality.QuadPart = lCounts;
				wcscpy(trData.m_szDesc, bstrDesc);
				if (!m_rgRowData.Add(trData))
					return E_OUTOFMEMORY;
				++lCnt;
			} 
			else 
#endif // defined(_USE_PROP_GEOMETRYAS)
			{
			// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
			// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
			CTABLEINFORow trData;
			DWORD lCounts[4], lAllObjs;

				RETURN_FAILED_HRESULT(Ident -> get_Counts (hPr, V_I4(&v), &lCounts[0], &lCounts[1], &lCounts[2], &lCounts[3], &lAllObjs));
				if (0 == lAllObjs) continue;		// no objects, no fun

				trData.m_ulPropID = V_I4(&v);				// Identifikator
				wcscpy(trData.m_szType, OLESTR("TABLE"));

				_ASSERTE(_countof(s_rgTypes) == _countof(lCounts));
				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (0 == lCounts[i])
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				CComBSTR bstrTypeName (bstrName);

					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrTypeName.Append(s_rgTypes[i].pcoleObjTypeName);
					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);

				// Restrictions auswerten
					if (CTABLEINFORow::TableNameRestrictionApply (bstrTypeName, cRestrictions, prgRestrictions) ||
						CTABLEINFORow::TableTypeRestrictionApply (OLESTR("TABLE"), cRestrictions, prgRestrictions))
					{
						continue;
					}

				// Langtext erzeugen ('Langtext (Geometrietyp)')
				CComBSTR bstrFullDesc (bstrDesc);
				CComBSTR bstrType;

					bstrType.LoadString(s_rgTypes[i].uiResId);
					_ASSERTE(bstrType.Length() > 0);
					bstrFullDesc.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrFullDesc.AppendBSTR(bstrType);
					bstrFullDesc.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);
					wcscpy(trData.m_szDesc, bstrFullDesc);			// Langtext

				// wirklich gefragt, also Tabelle einfügen
					wcscpy(trData.m_szTable, bstrTypeName);
					trData.m_ui64Cardinality.QuadPart = lCounts[i];
					if (!m_rgRowData.Add(trData))
						return E_OUTOFMEMORY;
					++lCnt;
				}

#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
				if (pDataSource -> GetViewMode()) {
				// Restrictions auswerten
					if (CTABLEINFORow::TableNameRestrictionApply (bstrName, cRestrictions, prgRestrictions) ||
						CTABLEINFORow::TableTypeRestrictionApply (OLESTR("VIEW"), cRestrictions, prgRestrictions))
					{
						continue;
					}

					trData.ClearMembers();
					wcscpy(trData.m_szTable, bstrName);
					wcscpy(trData.m_szType, OLESTR("VIEW"));
					trData.m_ulPropID = V_I4(&v);				// Identifikator
					trData.m_ui64Cardinality.QuadPart = lAllObjs;
					wcscpy(trData.m_szDesc, bstrDesc);
					if (!m_rgRowData.Add(trData))
						return E_OUTOFMEMORY;
					++lCnt;
				}
#endif // defined(_USE_PREDEFINED_GEOMETRYVIEWS)
			}
		}
		*pcRowsAffected = lCnt;
		return S_OK;
	}

	DBSTATUS GetDBStatus(CSimpleRow *, ATLCOLUMNINFO* pInfo)
	{
		switch (pInfo->iOrdinal) {
		case 1:		// TABLE_CATALOG
		case 2:		// TABLE_SCHEMA
		case 5:		// TABLE_GUID
		case 11:	// TABLE_VERSION
			return DBSTATUS_S_ISNULL;

		default:
			return DBSTATUS_S_OK;
		}
	}
};

#endif // !defined(_TRIASOLEDBSESSIONTISCHEMAROWSET_H__312EDBF1_7254_43CD_A554_7F0303118C2D__INCLUDED_)
