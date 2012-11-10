// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:08:15 
//
// @doc
// @module TRiASOleDBSessionVRSchemaRowset.h | Declaration of the <c CTRiASOleDBSessionVRSchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONVRSCHEMAROWSET_H__0BCBBBF1_8006_467E_BD76_7C2F35009C68__INCLUDED_)
#define _TRIASOLEDBSESSIONVRSCHEMAROWSET_H__0BCBBBF1_8006_467E_BD76_7C2F35009C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionVRSchemaRowset: RowSet aller verfügbaren Views
class CVIEWSRow
{
public:
	WCHAR m_szCatalog[129];
	WCHAR m_szSchema[129];
	WCHAR m_szTable[129];
	WCHAR m_szViewDefinition[257];
	VARIANT_BOOL m_fCheckOption;
	VARIANT_BOOL m_fUpdatable;
	WCHAR m_szDesc[257];
	DBDATE m_dateCreated;
	DBDATE m_dateModified;

	CVIEWSRow()
	{
		ClearMembers();
	}

	void ClearMembers()
	{
		m_szCatalog[0] = NULL;
		m_szSchema[0] = NULL;
		m_szTable[0] = NULL;
		m_szViewDefinition[0] = NULL;
		m_fCheckOption = VARIANT_FALSE;
		m_fUpdatable = VARIANT_FALSE;
		m_szDesc[0] = NULL;
		memset(&m_dateCreated, 0, sizeof(DBDATE));
		memset(&m_dateModified, 0, sizeof(DBDATE));
	}

	BEGIN_PROVIDER_COLUMN_MAP(CVIEWSRow)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szCatalog)	// restriction 1 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szSchema)	// restriction 2 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTable)		// restriction 3
		PROVIDER_COLUMN_ENTRY("VIEW_DEFINITION", 4, m_szViewDefinition)
		PROVIDER_COLUMN_ENTRY_FIXED("CHECK_OPTION", 5, DBTYPE_BOOL, m_fCheckOption)
		PROVIDER_COLUMN_ENTRY_FIXED("IS_UPDATABLE", 6, DBTYPE_BOOL, m_fUpdatable)
		PROVIDER_COLUMN_ENTRY("DESCRIPTION", 7, m_szDesc)
		PROVIDER_COLUMN_ENTRY("DATE_CREATED", 8, m_dateCreated)
		PROVIDER_COLUMN_ENTRY("DATE_MODIFIED", 9, m_dateModified)
	END_PROVIDER_COLUMN_MAP()

// defined restrictions
	enum RESTRICT_VIEWS {
		RESTRICT_VIEWS__TABLE_CATALOG = 1,
		RESTRICT_VIEWS__TABLE_SCHEMA = 2,
		RESTRICT_VIEWS__TABLE_NAME = 3,
	};

// Restrictions testen
	static bool TableNameRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_VIEWS__TABLE_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_VIEWS__TABLE_NAME-1])) {
		// TABLE_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_VIEWS__TABLE_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_VIEWS__TABLE_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_VIEWS__TABLE_NAME-1]) &&
					CmpQuotedNames (bstrName, V_BSTR(&prgRestrictions[RESTRICT_VIEWS__TABLE_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
};

class CTRiASOleDBSessionVRSchemaRowset : 
	public CSchemaRowsetImpl<CTRiASOleDBSessionVRSchemaRowset, CVIEWSRow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionVRSchemaRowset)
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
		_ASSERTE(NULL != pcRowsAffected);

	// zugehöriges DataSourceObjekt besorgen
	CTRiASOleDBSource *pDataSource = NULL;

		RETURN_FAILED_HRESULT(GetDataSourceObject(this, &pDataSource));

	// Views existieren nur beim GeometryMode 'DBPROPVAL_TRiAS_GEOMETRYTABLES'
		if (DBPROPVAL_TRiAS_GEOMETRYTABLES != pDataSource -> GetGeometryMode()) {
			*pcRowsAffected = 0;
			return S_OK;
		}

	// Views nur bei Wunsch erzeugen
		if (!pDataSource -> GetViewMode()) {
			*pcRowsAffected = 0;
			return S_OK;
		}

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

		USES_CONVERSION;

	CComVariant v;
	LONG lCnt = 0;

		_ASSERTE(Enum != NULL);
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			_ASSERTE(V_ISI4(&v));	// muß Handle sein

		DWORD dwTypes = 0;

			RETURN_FAILED_HRESULT(Ident -> get_Types (hPr, V_I4(&v), &dwTypes));
			if (0 == dwTypes) continue;		// no objects, no fun

		CComBSTR bstrName, bstrDesc, bstrOKS;

			RETURN_FAILED_HRESULT(Ident -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc, &bstrOKS));
		// alle Geometrien in der jeweiligen Tabelle (Objektklasse) in einer Spalte
		// Restrictions auswerten
			if (CTABLESRowEx::TableNameRestrictionApply (bstrName, cRestrictions, prgRestrictions))
			{
				continue;
			}

		CVIEWSRow trData;

			wcscpy(trData.m_szTable, bstrName);			// Kurztext
			wcscpy(trData.m_szDesc, bstrDesc);			// Langtext
			trData.m_fCheckOption = VARIANT_TRUE;
			trData.m_fUpdatable = VARIANT_FALSE;

		CString strSelect;
		bool fFirst = true;

			trData.m_szViewDefinition[0] = 0;
			if (dwTypes & OTPunkt) {
				strSelect.Format(g_cbViewSelectP, bstrName);
				wcscpy(trData.m_szViewDefinition, A2OLE(strSelect));
				fFirst = false;
			}
			if (dwTypes & OTLinie) {
				if (!fFirst)
					wcscat(trData.m_szViewDefinition, OLESTR(" UNION "));
				strSelect.Format(g_cbViewSelectL, bstrName);
				wcscat(trData.m_szViewDefinition, A2OLE(strSelect));
				fFirst = false;
			}
			if (dwTypes & OTFlaeche) {
				if (!fFirst)
					wcscat(trData.m_szViewDefinition, OLESTR(" UNION "));
				strSelect.Format(g_cbViewSelectA, bstrName);
				wcscat(trData.m_szViewDefinition, A2OLE(strSelect));
				fFirst = false;
			}
			if (dwTypes & OTText) {
				if (!fFirst)
					wcscat(trData.m_szViewDefinition, OLESTR(" UNION "));
				strSelect.Format(g_cbViewSelectT, bstrName);
				wcscat(trData.m_szViewDefinition, A2OLE(strSelect));
				fFirst = false;
			}

			if (!m_rgRowData.Add(trData))
				return E_OUTOFMEMORY;
			
			++lCnt;
		} 
		*pcRowsAffected = lCnt;
		return S_OK;
	}
	DBSTATUS GetDBStatus(CSimpleRow *, ATLCOLUMNINFO* pInfo)
	{
		switch (pInfo->iOrdinal) {
		case 1:		// TABLE_CATALOG
		case 2:		// TABLE_SCHEMA
		case 8:		// DATE_CREATED
		case 9:		// DATE_MODIFIED
			return DBSTATUS_S_ISNULL;

		default:
			return DBSTATUS_S_OK;
		}
	}
};

#endif // !defined(_TRIASOLEDBSESSIONVRSCHEMAROWSET_H__0BCBBBF1_8006_467E_BD76_7C2F35009C68__INCLUDED_)
