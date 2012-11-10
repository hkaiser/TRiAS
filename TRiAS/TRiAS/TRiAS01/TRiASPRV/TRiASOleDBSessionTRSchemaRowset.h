// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:06:48 
//
// @doc
// @module TRiASOleDBSessionTRSchemaRowset.h | Declaration of the <c CTRiASOleDBSessionTRSchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONTRSCHEMAROWSET_H__E94D31A8_B9AD_48A0_9D99_11AA96C05F8A__INCLUDED_)
#define _TRIASOLEDBSESSIONTRSCHEMAROWSET_H__E94D31A8_B9AD_48A0_9D99_11AA96C05F8A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>
#include <Atl/Ciid.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionTRSchemaRowset: RowSet aller verfügbaren Tabellen
class CTABLESRowEx
{
public:
	WCHAR m_szCatalog[129];
	WCHAR m_szSchema[129];
	WCHAR m_szTable[129];
	WCHAR m_szType[129];
	WCHAR m_szDesc[257];
	GUID  m_guid;
	ULONG m_ulPropID;
	DBDATE m_dateCreated;
	DBDATE m_dateModified;

	CTABLESRowEx()
	{
		ClearMembers();
	}

	void ClearMembers()
	{
		m_szCatalog[0] = NULL;
		m_szSchema[0] = NULL;
		m_szTable[0] = NULL;
		m_szType[0] = NULL;
		m_szDesc[0] = NULL;
		m_guid = GUID_NULL;
		m_ulPropID = 0;
		memset(&m_dateCreated, 0, sizeof(DBDATE));
		memset(&m_dateModified, 0, sizeof(DBDATE));
	}

	BEGIN_PROVIDER_COLUMN_MAP(CTABLESRowEx)
		PROVIDER_COLUMN_ENTRY("TABLE_CATALOG", 1, m_szCatalog)	// restriction 1 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_SCHEMA", 2, m_szSchema)	// restriction 2 (not implemeted)
		PROVIDER_COLUMN_ENTRY("TABLE_NAME", 3, m_szTable)		// restriction 3
		PROVIDER_COLUMN_ENTRY("TABLE_TYPE", 4, m_szType)		// restriction 4
		PROVIDER_COLUMN_ENTRY("TABLE_GUID", 5, m_guid)
		PROVIDER_COLUMN_ENTRY("DESCRIPTION", 6, m_szDesc)
		PROVIDER_COLUMN_ENTRY("TABLE_PROPID", 7, m_ulPropID)
		PROVIDER_COLUMN_ENTRY("DATE_CREATED", 8, m_dateCreated)
		PROVIDER_COLUMN_ENTRY("DATE_MODIFIED", 9, m_dateModified)
	END_PROVIDER_COLUMN_MAP()

// defined restrictions
	enum RESTRICT_TABLES {
		RESTRICT_TABLES__TABLE_CATALOG = 1,
		RESTRICT_TABLES__TABLE_SCHEMA = 2,
		RESTRICT_TABLES__TABLE_NAME = 3,
		RESTRICT_TABLES__TABLE_TYPE = 4,
	};

// Restrictions testen
	static bool TableNameRestrictionApply (LPCOLESTR bstrName, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_TABLES__TABLE_NAME && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_TABLES__TABLE_NAME-1])) {
		// TABLE_NAME restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_TABLES__TABLE_NAME-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_TABLES__TABLE_NAME-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_TABLES__TABLE_NAME-1]) &&
					CmpQuotedNames (bstrName, V_BSTR(&prgRestrictions[RESTRICT_TABLES__TABLE_NAME-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
	static bool TableTypeRestrictionApply (LPCOLESTR bstrType, ULONG cRestrictions, const VARIANT *prgRestrictions)
	{
		if (cRestrictions >= RESTRICT_TABLES__TABLE_TYPE && VT_EMPTY != V_VT(&prgRestrictions[RESTRICT_TABLES__TABLE_TYPE-1])) {
		// TABLE_TYPE restriction given
			if (VT_NULL != V_VT(&prgRestrictions[RESTRICT_TABLES__TABLE_TYPE-1])) {
				_ASSERTE(VT_BSTR == V_VT(&prgRestrictions[RESTRICT_TABLES__TABLE_TYPE-1]));
				if (NULL != V_BSTR(&prgRestrictions[RESTRICT_TABLES__TABLE_TYPE-1]) &&
					wcscmp(bstrType, V_BSTR(&prgRestrictions[RESTRICT_TABLES__TABLE_TYPE-1])))
				{
					return true;		// not requested
				}
			}
		}
		return false;
	}
};

class CTRiASOleDBSessionTRSchemaRowset : 
	public CSchemaRowsetImpl<CTRiASOleDBSessionTRSchemaRowset, CTABLESRowEx, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionTRSchemaRowset)
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

	// zuerst mal Version der Datenquelle feststellen
		RETURN_FAILED_HRESULT(pDataSource -> get_ClassesHaveDates (&m_fHasDates));

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
		CIID Guid;

			RETURN_FAILED_HRESULT(Ident -> GetMetaData (hPr, V_I4(&v), &bstrName, &bstrDesc, &bstrOKS));
			RETURN_FAILED_HRESULT(Ident -> get_Guid(hPr, V_I4(&v), &Guid));

#if defined(_USE_PROP_GEOMETRYAS)
		// entscheiden, wie Geometrie abgebildet werden soll
			if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
			// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
			// 4 separaten Spalten

			// Restrictions auswerten
				if (CTABLESRowEx::TableNameRestrictionApply (bstrName, cRestrictions, prgRestrictions) ||
					CTABLESRowEx::TableTypeRestrictionApply (OLESTR("TABLE"), cRestrictions, prgRestrictions))
				{
					continue;
				}

			CTABLESRowEx trData;

				trData.m_ulPropID = V_I4(&v);				// Identifikator
				trData.m_guid = Guid;

				wcscpy(trData.m_szTable, bstrName);			// Kurztext
				wcscpy(trData.m_szDesc, bstrDesc);			// Langtext
				wcscpy(trData.m_szType, OLESTR("TABLE"));

				if (m_fHasDates) {
				DATE dCreation = 0;
				DATE dModification = 0;

					RETURN_FAILED_HRESULT(Ident -> get_CreationDate(hPr, V_I4(&v), &dCreation));
					RETURN_FAILED_HRESULT(Ident -> get_ModificationDate(hPr, V_I4(&v), &dModification));

					trData.m_dateCreated = DbDateFromDate(dCreation);
					trData.m_dateModified = DbDateFromDate(dModification);
				}

				if (!m_rgRowData.Add(trData))
					return E_OUTOFMEMORY;
				
				++lCnt;
			} 
			else 
#endif // defined(_USE_PROP_GEOMETRYAS)
			{
			// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
			// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
			DWORD dwTypes = 0;

				RETURN_FAILED_HRESULT(Ident -> get_Types (hPr, V_I4(&v), &dwTypes));
				if (0 == dwTypes) continue;		// no objects, no fun

			CTABLESRowEx trData;

				trData.m_ulPropID = V_I4(&v);				// Identifikator
				trData.m_guid = Guid;
				wcscpy(trData.m_szType, OLESTR("TABLE"));

				for (int i = 0; i < _countof(s_rgTypes); ++i) {
					if (!(s_rgTypes[i].dwType & dwTypes))
						continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

				CComBSTR bstrTypeName (bstrName);

					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_PREFIX);
					bstrTypeName.Append(s_rgTypes[i].pcoleObjTypeName);
					bstrTypeName.Append(TABLE_OBJTYPE_DELIMITER_STR_POSTFIX);

				// Restrictions auswerten
					if (CTABLESRowEx::TableNameRestrictionApply (bstrTypeName, cRestrictions, prgRestrictions) ||
						CTABLESRowEx::TableTypeRestrictionApply (OLESTR("TABLE"), cRestrictions, prgRestrictions))
					{
						continue;
					}

				// Langtext erzeugen ('Langtext (Geometrietyp)')
				CComBSTR bstrFullDesc (bstrDesc);
				CComBSTR bstrType;

					bstrType.LoadString(s_rgTypes[i].uiResId);
					_ASSERTE(bstrType.Length() > 0);
					bstrFullDesc.Append(L" (");
					bstrFullDesc.AppendBSTR(bstrType);
					bstrFullDesc.Append(L")");
					wcscpy(trData.m_szDesc, bstrFullDesc);			// Langtext

				// wirklich gefragt, also Tabelle einfügen
					wcscpy(trData.m_szTable, bstrTypeName);			// Kurztext/GEOTYP

					if (m_fHasDates) {
					DATE dCreation = 0;
					DATE dModification = 0;

						RETURN_FAILED_HRESULT(Ident -> get_CreationDate(hPr, V_I4(&v), &dCreation));
						RETURN_FAILED_HRESULT(Ident -> get_ModificationDate(hPr, V_I4(&v), &dModification));

						trData.m_dateCreated = DbDateFromDate(dCreation);
						trData.m_dateModified = DbDateFromDate(dModification);
					}

					if (!m_rgRowData.Add(trData))
						return E_OUTOFMEMORY;
				
					++lCnt;
				}

#if defined(_USE_PREDEFINED_GEOMETRYVIEWS)
				if (pDataSource -> GetViewMode()) {
				// Restrictions auswerten
					if (CTABLESRowEx::TableNameRestrictionApply (bstrName, cRestrictions, prgRestrictions) ||
						CTABLESRowEx::TableTypeRestrictionApply (OLESTR("VIEW"), cRestrictions, prgRestrictions))
					{
						continue;
					}

					trData.ClearMembers();

					trData.m_ulPropID = V_I4(&v);			// Identifikator
					trData.m_guid = Guid;
					wcscpy(trData.m_szTable, bstrName);		// blanker Kurztext
					wcscpy(trData.m_szDesc, bstrDesc);		// Langtext
					wcscpy(trData.m_szType, OLESTR("VIEW"));

					if (m_fHasDates) {
					DATE dCreation = 0;
					DATE dModification = 0;

						RETURN_FAILED_HRESULT(Ident -> get_CreationDate(hPr, V_I4(&v), &dCreation));
						RETURN_FAILED_HRESULT(Ident -> get_ModificationDate(hPr, V_I4(&v), &dModification));

						trData.m_dateCreated = DbDateFromDate(dCreation);
						trData.m_dateModified = DbDateFromDate(dModification);
					}

				// die VIEW ist gefragt, also einfügen
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
			return DBSTATUS_S_ISNULL;

		case 8:		// DATE_CREATED
		case 9:		// DATE_MODIFIED
			return m_fHasDates ? DBSTATUS_S_OK : DBSTATUS_S_ISNULL;

		default:
			return DBSTATUS_S_OK;
		}
	}

private:
	CComBool m_fHasDates;
};

#endif // !defined(_TRIASOLEDBSESSIONTRSCHEMAROWSET_H__E94D31A8_B9AD_48A0_9D99_11AA96C05F8A__INCLUDED_)
