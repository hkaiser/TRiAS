// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:13:23 
//
// @doc
// @module TRiASOleDBSessionPTSchemaRowset.h | Declaration of the <c CTRiASOleDBSessionPTSchemaRowset> class

#if !defined(_TRIASOLEDBSESSIONPTSCHEMAROWSET_H__B8BDF416_0026_4D1B_8408_DB53267DF294__INCLUDED_)
#define _TRIASOLEDBSESSIONPTSCHEMAROWSET_H__B8BDF416_0026_4D1B_8408_DB53267DF294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionPTSchemaRowset: Rowset aller Datentypen des Providers
class CPROVIDER_TYPERowEx :
	public CPROVIDER_TYPERow
{
public:
// Binding Maps
	BEGIN_PROVIDER_COLUMN_MAP(CPROVIDER_TYPERowEx)
		PROVIDER_COLUMN_ENTRY("TYPE_NAME", 1, m_szName)
		PROVIDER_COLUMN_ENTRY("DATA_TYPE", 2, m_nType)
		PROVIDER_COLUMN_ENTRY("COLUMN_SIZE", 3, m_ulSize)
		PROVIDER_COLUMN_ENTRY("LITERAL_PREFIX", 4, m_szPrefix)
		PROVIDER_COLUMN_ENTRY("LITERAL_SUFFIX", 5, m_szSuffix)
		PROVIDER_COLUMN_ENTRY("CREATE_PARAMS", 6, m_szCreateParams)
		PROVIDER_COLUMN_ENTRY_FIXED("IS_NULLABLE", 7, DBTYPE_BOOL, m_bIsNullable)
		PROVIDER_COLUMN_ENTRY_FIXED("CASE_SENSITIVE", 8, DBTYPE_BOOL, m_bCaseSensitive)
#if _ATL_VER < 0x0700
		PROVIDER_COLUMN_ENTRY("SEARCHABLE", 9, m_bSearchable)
#else
		PROVIDER_COLUMN_ENTRY("SEARCHABLE", 9, m_ulSearchable)
#endif // _ATL_VER < 0x0700
		PROVIDER_COLUMN_ENTRY_FIXED("UNSIGNED_ATTRIBUTE", 10, DBTYPE_BOOL, m_bUnsignedAttribute)
		PROVIDER_COLUMN_ENTRY_FIXED("FIXED_PREC_SCALE", 11, DBTYPE_BOOL, m_bFixedPrecScale)
		PROVIDER_COLUMN_ENTRY_FIXED("AUTO_UNIQUE_VALUE", 12, DBTYPE_BOOL, m_bAutoUniqueValue)
		PROVIDER_COLUMN_ENTRY("LOCAL_TYPE_NAME", 13, m_szLocalTypeName)
		PROVIDER_COLUMN_ENTRY("MINIMUM_SCALE", 14, m_nMinScale)
		PROVIDER_COLUMN_ENTRY("MAXIMUM_SCALE", 15, m_nMaxScale)
		PROVIDER_COLUMN_ENTRY("GUID", 16, m_guidType)
		PROVIDER_COLUMN_ENTRY("TYPELIB", 17, m_szTypeLib)
		PROVIDER_COLUMN_ENTRY("VERSION", 18, m_szVersion)
		PROVIDER_COLUMN_ENTRY_FIXED("IS_LONG", 19, DBTYPE_BOOL, m_bIsLong)
		PROVIDER_COLUMN_ENTRY_FIXED("BEST_MATCH", 20, DBTYPE_BOOL, m_bBestMatch)
		PROVIDER_COLUMN_ENTRY_FIXED("IS_FIXEDLENGTH", 21, DBTYPE_BOOL, m_bIsFixedLength)
	END_PROVIDER_COLUMN_MAP()
};

class CTRiASOleDBSessionPTSchemaRowset : 
	public CSchemaRowsetImpl<CTRiASOleDBSessionPTSchemaRowset, CPROVIDER_TYPERowEx, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionPTSchemaRowset)
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

	HRESULT Execute(LONG *pcRowsAffected, ULONG, const VARIANT *)
	{
		USES_CONVERSION;

	CPROVIDER_TYPERowEx trData[4];

	// DBTYPE_STR
		wcscpy(trData[0].m_szName, OLESTR("ObjectProperty"));
		trData[0].m_nType = DBTYPE_WSTR;
		trData[0].m_bCaseSensitive = VARIANT_TRUE;
		trData[0].m_ulSize = LONG_MAX;
		wcscpy(trData[0].m_szPrefix, OLESTR("'"));
		wcscpy(trData[0].m_szSuffix, OLESTR("'"));
		trData[0].m_szCreateParams[0] = NULL;
		trData[0].m_bIsNullable = VARIANT_TRUE;
		trData[0].m_bCaseSensitive = VARIANT_TRUE;
#if _ATL_VER < 0x0700
		trData[0].m_bSearchable = DB_SEARCHABLE;
#else
		trData[0].m_ulSearchable = DB_SEARCHABLE;
#endif // if _ATL_VER < 0x0700
		trData[0].m_bUnsignedAttribute = VARIANT_TRUE;
		trData[0].m_bFixedPrecScale = VARIANT_TRUE;
		trData[0].m_bAutoUniqueValue = VARIANT_FALSE;

	CComBSTR bstrStringName;

		bstrStringName.LoadString(IDS_STRINGNAME);
		wcscpy(trData[0].m_szLocalTypeName, bstrStringName);
		trData[0].m_bIsLong = VARIANT_FALSE;
		trData[0].m_bBestMatch = VARIANT_TRUE;
		trData[0].m_bIsFixedLength = VARIANT_FALSE;
		m_rgRowData.Add(trData[0]);

	// DBTYPE_BYTES
		wcscpy(trData[1].m_szName, OLESTR("Geometry"));
		trData[1].m_nType = DBTYPE_BYTES;
		trData[1].m_ulSize = 0x1ffffffe;
		wcscpy(trData[1].m_szPrefix, OLESTR("0x"));
		wcscpy(trData[1].m_szSuffix, OLESTR(""));
		trData[1].m_szCreateParams[0] = NULL;
		trData[1].m_bIsNullable = VARIANT_TRUE;
		trData[1].m_bCaseSensitive = VARIANT_FALSE;
#if _ATL_VER < 0x0700
		trData[0].m_bSearchable = DB_UNSEARCHABLE;
#else
		trData[0].m_ulSearchable = DB_UNSEARCHABLE;
#endif // if _ATL_VER < 0x0700
		trData[1].m_bUnsignedAttribute = VARIANT_TRUE;
		trData[1].m_bFixedPrecScale = VARIANT_TRUE;
		trData[1].m_bAutoUniqueValue = VARIANT_FALSE;

	CComBSTR bstrGeometryName;

		bstrGeometryName.LoadString(IDS_GEOMETRYNAME);
		wcscpy(trData[1].m_szLocalTypeName, bstrGeometryName);
		trData[1].m_nMaxScale = 0;
		trData[1].m_bIsLong = VARIANT_TRUE;
		trData[1].m_bBestMatch = VARIANT_TRUE;
		trData[1].m_bIsFixedLength = VARIANT_FALSE;
		m_rgRowData.Add(trData[1]);

	// DBTYPE_GUID
		wcscpy(trData[2].m_szName, OLESTR("UniqueObjectId"));
		trData[2].m_nType = DBTYPE_GUID;
		trData[2].m_bCaseSensitive = VARIANT_TRUE;
		trData[2].m_ulSize = 16;
		wcscpy(trData[2].m_szPrefix, OLESTR("{"));
		wcscpy(trData[2].m_szSuffix, OLESTR("}"));
		trData[2].m_szCreateParams[0] = NULL;
		trData[2].m_bIsNullable = VARIANT_TRUE;
		trData[2].m_bCaseSensitive = VARIANT_TRUE;
#if _ATL_VER < 0x0700
		trData[0].m_bSearchable = DB_SEARCHABLE;
#else
		trData[0].m_ulSearchable = DB_SEARCHABLE;
#endif // if _ATL_VER < 0x0700
		trData[2].m_bUnsignedAttribute = VARIANT_TRUE;
		trData[2].m_bFixedPrecScale = VARIANT_TRUE;
		trData[2].m_bAutoUniqueValue = VARIANT_TRUE;

	CComBSTR bstrGuidName;

		bstrGuidName.LoadString(IDS_GUIDNAME);
		wcscpy(trData[2].m_szLocalTypeName, bstrGuidName);
		trData[2].m_bIsLong = VARIANT_FALSE;
		trData[2].m_bBestMatch = VARIANT_TRUE;
		trData[2].m_bIsFixedLength = VARIANT_TRUE;
		m_rgRowData.Add(trData[2]);

	// DBTYPE_UI4
		wcscpy(trData[3].m_szName, OLESTR("ObjectHandle"));
		trData[3].m_nType = DBTYPE_UI4;
		trData[3].m_bCaseSensitive = VARIANT_FALSE;
		trData[3].m_ulSize = 10;
		trData[3].m_szPrefix[0] = NULL;
		trData[3].m_szSuffix[0] = NULL;
		trData[3].m_szCreateParams[0] = NULL;
		trData[3].m_bIsNullable = VARIANT_FALSE;
		trData[3].m_bCaseSensitive = VARIANT_FALSE;
#if _ATL_VER < 0x0700
		trData[0].m_bSearchable = DB_SEARCHABLE;
#else
		trData[0].m_ulSearchable = DB_SEARCHABLE;
#endif // if _ATL_VER < 0x0700
		trData[3].m_bUnsignedAttribute = VARIANT_TRUE;
		trData[3].m_bFixedPrecScale = VARIANT_TRUE;
		trData[3].m_bAutoUniqueValue = VARIANT_TRUE;

	CComBSTR bstrObjNrName;

		bstrObjNrName.LoadString(IDS_OBJNRNAME);
		wcscpy(trData[3].m_szLocalTypeName, bstrObjNrName);
		trData[3].m_bIsLong = VARIANT_FALSE;
		trData[3].m_bBestMatch = VARIANT_TRUE;
		trData[3].m_bIsFixedLength = VARIANT_TRUE;
		m_rgRowData.Add(trData[3]);

		*pcRowsAffected = 3;
		return S_OK;
	}

	DBSTATUS GetDBStatus(CSimpleRow *pRow, ATLCOLUMNINFO *pInfo)
	{
		switch(pInfo->iOrdinal) {
		case 4:		// m_szPrefix
			if (3 == pRow -> m_iRowset) 
				return DBSTATUS_S_ISNULL;
			return DBSTATUS_S_OK;

		case 5:		// m_szSuffix
			if (1 == pRow -> m_iRowset || 3 == pRow -> m_iRowset) 
				return DBSTATUS_S_ISNULL;
			return DBSTATUS_S_OK;

		case 6:		// m_szCreateParams
		case 14:	// m_nMinScale
		case 15:	// m_nMaxScale
		case 16:	// m_guidType
		case 17:	// m_szTypeLib
		case 18:	// m_szVersion
			return DBSTATUS_S_ISNULL;

		default:
			return DBSTATUS_S_OK;
		}
	}
};

#endif // !defined(_TRIASOLEDBSESSIONPTSCHEMAROWSET_H__B8BDF416_0026_4D1B_8408_DB53267DF294__INCLUDED_)
