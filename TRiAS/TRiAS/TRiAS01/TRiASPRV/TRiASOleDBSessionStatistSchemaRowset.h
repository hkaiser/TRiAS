// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 21:41:52 
//
// @doc
// @module TRiASOleDBSessionStatistSchemaRowset.h | Declaration of the <c CTRiASOleDBSessionStatistSchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONSTATISTSCHEMAROWSET_H__C577C66E_C67E_4BAE_9FB6_462AA77BC380__INCLUDED_)
#define _TRIASOLEDBSESSIONSTATISTSCHEMAROWSET_H__C577C66E_C67E_4BAE_9FB6_462AA77BC380__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionStatistSchemaRowset: Table Statistics Schema Rowset
class CSTATISTICSRow 
{
public:
	WCHAR m_szCatalog[129];
	WCHAR m_szSchema[129];
	WCHAR m_szTable[129];
	ULARGE_INTEGER m_ui64Cardinality;

	CSTATISTICSRow() 
	{
		ClearMembers();
	}

	void ClearMembers()
	{
		m_szCatalog[0] = NULL;
		m_szSchema[0] = NULL;
		m_szTable[0] = NULL;
		m_ui64Cardinality.QuadPart = 0;
	}

	BEGIN_PROVIDER_COLUMN_MAP(CSTATISTICSRow)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szCatalog)	// restriction 1 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szSchema)	// restriction 2 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTable)		// restriction 3
		PROVIDER_COLUMN_ENTRY("CARDINALITY", 4, m_ui64Cardinality)
	END_PROVIDER_COLUMN_MAP()

	enum RESTRICT_STATISTICS {
		RESTRICT_STATISTICS__TABLE_CATALOG = 1,
		RESTRICT_STATISTICS__TABLE_SCHEMA = 2,
		RESTRICT_STATISTICS__TABLE_NAME = 3,
	};

// Restrictions testen
	static bool TableNameRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_STATISTICS__TABLE_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_STATISTICS__TABLE_NAME-1])) {
		// TABLE_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_STATISTICS__TABLE_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_STATISTICS__TABLE_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_STATISTICS__TABLE_NAME-1]) &&
					CmpQuotedNames (bstrName, V_BSTR(&prgRestrictions[RESTRICT_STATISTICS__TABLE_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
};

class CTRiASOleDBSessionStatistSchemaRowset :
	public CSchemaRowsetImpl<CTRiASOleDBSessionStatistSchemaRowset, CSTATISTICSRow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionStatistSchemaRowset)
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
				if (CSTATISTICSRow::TableNameRestrictionApply (bstrName, cRestrictions, prgRestrictions))
					continue;

			CSTATISTICSRow trData;
			DWORD lPoints, lLines, lAreas, lTexts, lCounts;

				RETURN_FAILED_HRESULT(Ident -> get_Counts (hPr, V_I4(&v), &lPoints, &lLines, &lAreas, &lTexts, &lCounts));

				wcscpy(trData.m_szTable, bstrName);
				trData.m_ui64Cardinality.QuadPart = lCounts;
				if (!m_rgRowData.Add(trData))
					return E_OUTOFMEMORY;
				++lCnt;
			} 
			else 
#endif // defined(_USE_PROP_GEOMETRYAS)
			{
			// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
			// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
			CSTATISTICSRow trData;
			DWORD lCounts[4], lAllObjs;

				RETURN_FAILED_HRESULT(Ident -> get_Counts (hPr, V_I4(&v), &lCounts[0], &lCounts[1], &lCounts[2], &lCounts[3], &lAllObjs));
				if (0 == lAllObjs) continue;		// no objects, no fun

				_ASSERTE(_countof(s_rgTypes) == _countof(lCounts));
				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (0 == lCounts[i])
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				CComBSTR bstrTypeName (bstrName);

					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrTypeName.Append(s_rgTypes[i].pcoleObjTypeName);
					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);

				// Restrictions auswerten
					if (CSTATISTICSRow::TableNameRestrictionApply (bstrTypeName, cRestrictions, prgRestrictions))
						continue;

				// wirklich gefragt, also Tabelle einfügen
					wcscpy(trData.m_szTable, bstrTypeName);
					trData.m_ui64Cardinality.QuadPart = lCounts[i];
					if (!m_rgRowData.Add(trData))
						return E_OUTOFMEMORY;
					++lCnt;
				}
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
			return DBSTATUS_S_ISNULL;

		default:
			return DBSTATUS_S_OK;
		}
	}
};

#endif // !defined(_TRIASOLEDBSESSIONSTATISTSCHEMAROWSET_H__C577C66E_C67E_4BAE_9FB6_462AA77BC380__INCLUDED_)
