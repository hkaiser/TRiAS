// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 28.06.2001 11:05:01 
//
// @doc
// @module TRiASOleDBSessionPrimaryKeysSchemaRowset.h | Declaration of the <c CTRiASOleDBSessionPrimaryKeysSchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONPRIMARYKEYSSCHEMAROWSET_H__1B56235E_53F9_4DDC_8378_1727404C42CD__INCLUDED_)
#define _TRIASOLEDBSESSIONPRIMARYKEYSSCHEMAROWSET_H__1B56235E_53F9_4DDC_8378_1727404C42CD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif


#include <Atl/OleDb/SessionRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionPrimaryKeysSchemaRowset: RowSet aller verfügbaren Spalten
class CPRIMARYKEYRow
{
public:
	WCHAR	m_szTableCatalog[129];
	WCHAR	m_szTableSchema[129];
	WCHAR	m_szTableName[129];
	WCHAR	m_szColumnName[129];
	GUID	m_guidColumn;
	ULONG	m_ulColumnPropID;
	ULONG	m_ulOrdinal;
	WCHAR	m_szPrimKeyName[129];

	CPRIMARYKEYRow() 
	{
		ClearMembers();
	}

	void ClearMembers()
	{
		m_szTableCatalog[0] = NULL;
		m_szTableSchema[0] = NULL;
		m_szTableName[0] = NULL;
		m_guidColumn = GUID_NULL;
		m_ulColumnPropID = 0;
		m_ulOrdinal = 1;

	CComBSTR bstrName;

		bstrName.LoadString(IDS_OBJNRNAME);
		_ASSERTE(bstrName.Length() > 0);
		wcscpy (m_szColumnName, bstrName);
		wcscpy (m_szPrimKeyName, bstrName);
	}

	BEGIN_PROVIDER_COLUMN_MAP(CPRIMARYKEYRow)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szTableCatalog)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szTableSchema)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTableName)
		PROVIDER_COLUMN_ENTRY("COLUMN_NAME", 4, m_szColumnName)
		PROVIDER_COLUMN_ENTRY("COLUMN_GUID", 5, m_guidColumn)
		PROVIDER_COLUMN_ENTRY("COLUMN_PROPID", 6, m_ulColumnPropID)
		PROVIDER_COLUMN_ENTRY("ORDINAL", 7, m_ulOrdinal)
		PROVIDER_COLUMN_ENTRY("PK_NAME", 8, m_szPrimKeyName)
	END_PROVIDER_COLUMN_MAP()

	enum RESTRICT_INDEXES {
		RESTRICT_PRIMARYKEY__TABLE_CATALOG = 1,
		RESTRICT_PRIMARYKEY__TABLE_SCHEMA = 2,
		RESTRICT_PRIMARYKEY__TABLE_NAME = 3,
	};

// Restrictions testen
	static bool TableRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_PRIMARYKEY__TABLE_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_PRIMARYKEY__TABLE_NAME-1])) {
		// TABLE_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_PRIMARYKEY__TABLE_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_PRIMARYKEY__TABLE_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_PRIMARYKEY__TABLE_NAME-1]) &&
					CmpQuotedNames(bstrName, V_BSTR(&prgRestrictions[RESTRICT_PRIMARYKEY__TABLE_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
};

class CTRiASOleDBSessionPrimaryKeysSchemaRowset : 
	public CSchemaRowsetImpl<CTRiASOleDBSessionPrimaryKeysSchemaRowset, CPRIMARYKEYRow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionPrimaryKeysSchemaRowset)
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
#if defined(_USE_PROP_GEOMETRYAS)
			if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
			// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
			// 4 separaten Spalten

			// Restrictions auswerten
				if (CPRIMARYKEYRow::TableRestrictionApply(bstrName, cRestrictions, prgRestrictions))
					continue;

			// Objektnummer ist der einzige PrimärIndex
			CPRIMARYKEYRow crData;

			// RowSet-Zeile füllen
				wcscpy(crData.m_szTableName, bstrName);
				if (!m_rgRowData.Add(crData))
					return E_OUTOFMEMORY;
				++lCnt;
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
					if (CPRIMARYKEYRow::TableRestrictionApply(bstrTypeName, cRestrictions, prgRestrictions))
						continue;

				// Objektnummer ist der einzige PrimärIndex
				CPRIMARYKEYRow crData;

				// RowSet-Zeile füllen
					wcscpy(crData.m_szTableName, bstrTypeName);
					if (!m_rgRowData.Add(crData))
						return E_OUTOFMEMORY;
					++lCnt;
				}

#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
			// Alle Objekte einer Objektklasse sind in einer View abgebildet
			// Restrictions auswerten
				if (CPRIMARYKEYRow::TableRestrictionApply(bstrName, cRestrictions, prgRestrictions))
					continue;

			// Objektnummer ist der einzige PrimärIndex
			CPRIMARYKEYRow crData;

			// RowSet-Zeile füllen
				wcscpy(crData.m_szTableName, bstrName);
				if (!m_rgRowData.Add(crData))
					return E_OUTOFMEMORY;
				++lCnt;
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
		case 6:		// COLUMN_PROPID
			return DBSTATUS_S_ISNULL;

		default:
			break;
		}
		return DBSTATUS_S_OK;
	}
};

#endif // !defined(_TRIASOLEDBSESSIONPRIMARYKEYSSCHEMAROWSET_H__1B56235E_53F9_4DDC_8378_1727404C42CD__INCLUDED_)
