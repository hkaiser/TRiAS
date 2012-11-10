// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 18:17:01 
//
// @doc
// @module TRiASOleDBSessionSchemaSpatRef.h | Declaration of the <c CTRiASOleDBSessionSchemaSpatRef> class

#if !defined(_TRIASOLEDBSESSIONSCHEMASPATREF_H__1F6B41B7_15DE_464D_9209_615F2E0C3EBB__INCLUDED_)
#define _TRIASOLEDBSESSIONSCHEMASPATREF_H__1F6B41B7_15DE_464D_9209_615F2E0C3EBB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/SessionRowsetImpl.h>

/////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBSessionSchemaSpatRef
// Note quite sure what to do with this yet!
class COGISSpatRow
{
public:
	int m_nSpatialRefId;
	WCHAR m_szAuthorityName[129];
	WCHAR m_nAuthorityId;
	WCHAR m_pszSpatialRefSystem[2000];

	COGISSpatRow()
	{
		m_nSpatialRefId = 0;
		m_szAuthorityName[0] = NULL;
		m_nAuthorityId = 0;
		m_pszSpatialRefSystem[0] = NULL;
	}

	BEGIN_PROVIDER_COLUMN_MAP(COGISSpatRow)
		PROVIDER_COLUMN_ENTRY("SPATIAL_REF_SYSTEM_ID", 1, m_nSpatialRefId)
		PROVIDER_COLUMN_ENTRY("AUTHORITY_NAME", 2, m_szAuthorityName)
		PROVIDER_COLUMN_ENTRY("AUTHORITY_ID", 3, m_nAuthorityId)
		PROVIDER_COLUMN_ENTRY_WSTR("SPATIAL_REF_SYSTEM_WKT", 4, m_pszSpatialRefSystem)
	END_PROVIDER_COLUMN_MAP()
};

class CTRiASOleDBSessionSchemaSpatRef:
	public CSchemaRowsetImpl<CTRiASOleDBSessionSchemaSpatRef, COGISSpatRow, CTRiASOleDBSession>
{
public:
	BEGIN_PROPSET_MAP(CTRiASOleDBSessionSchemaSpatRef)
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
	// zugehöriges DataSourceObjekt besorgen
	CTRiASOleDBSource *pDataSource = NULL;
	CComBSTR bstrCS;
	UINT uiCode = 0;

		RETURN_ERROR(GetDataSourceObject(this, &pDataSource));
		RETURN_ERROR(pDataSource -> get_CoordSystemWKT (&uiCode, &bstrCS));

	COGISSpatRow trData;

		wcscpy(trData.m_szAuthorityName, OLESTR("EPSG"));
		trData.m_nAuthorityId = 1;
		trData.m_nSpatialRefId = uiCode;
		wcscpy(trData.m_pszSpatialRefSystem, bstrCS);	// L"PROJCS[\"unknown\"]");
		if (!m_rgRowData.Add(trData))
			return E_OUTOFMEMORY;

		*pcRowsAffected = 1;
		return S_OK;
	}
};

#endif // !defined(_TRIASOLEDBSESSIONSCHEMASPATREF_H__1F6B41B7_15DE_464D_9209_615F2E0C3EBB__INCLUDED_)
