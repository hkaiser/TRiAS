// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.06.2001 19:17:38 
//
// @doc
// @module TRiASOleDBSession.cpp | Definition of the <c CTRiASOleDBSession> class

#include "StdAfx.h"

#include "TRiASOleDBSession.h"
#include "TRiASOleDBDataSource.h"
#include "SchemaRowsets.h"

#include "TRiASOleDBRowSet.h"
#include "TRiASOleDBIndex.h"

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CTRiASOleDBSession::OpenRowset(
	IUnknown *pUnk, DBID *pTID, DBID *pInID, REFIID riid, ULONG cSets, 
	DBPROPSET rgSets[], IUnknown **ppRowset)
{
	ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBSession::OpenRowset\n");
	SetErrorInfo(0, NULL);

// Parameter prüfen bzw. initialisieren
	if (ppRowset != NULL)
		*ppRowset = NULL;

// TabellenNamen ggf. Quoten
	if (NULL == pTID) 
		return OleDBError(NULL != pInID ? DB_E_NOINDEX : E_INVALIDARG);	// Tabelle muß immer gegeben sein

HRESULT hr = E_FAIL;
CDBID TableId (*pTID, CDBID::DBIDMODE_Quoted);

	pTID = &TableId;

	if (NULL == pInID) {
	// Rowset ohne Index erzeugen
	CTRiASOleDBRowset *pRowset;
	
		RETURN_ERROR(hr = CreateRowset(pUnk, pTID, pInID, riid, cSets, rgSets, ppRowset, pRowset));
		if (NULL != ppRowset) {
			RETURN_ERROR(RegisterTable(pTID));
			RETURN_ERROR(pRowset -> RegisterTable(pTID));
		}
		return hr;
	}
	else {
	// Rowset mit Index erzeugen
	CTRiASOleDBIndex *pIndex;
	CDBID IndexId (*pInID, CDBID::DBIDMODE_Quoted);

		pInID = &IndexId;

		RETURN_ERROR(hr = CreateRowset(pUnk, pTID, pInID, riid, cSets, rgSets, ppRowset, pIndex));
		if (NULL != ppRowset) {
			RETURN_ERROR(RegisterTable(pTID));
			RETURN_ERROR(pIndex -> RegisterTable(pTID));
		}
		return hr;
	}
}

///////////////////////////////////////////////////////////////////////////////
// support for ITableDefinition
HRESULT CTRiASOleDBSession::IsExistingTable (DBID *pTableId, INT_PTR *plIdent)
{
	if (DBKIND_NAME == pTableId -> eKind || 
		DBKIND_PGUID_NAME == pTableId -> eKind ||
		DBKIND_GUID_NAME == pTableId -> eKind)
	{
	CComBSTR bstrName(pTableId -> uName.pwszName);
	INT_PTR lIdent = 0;
	CTRiASOleDBSource *pDataSource = NULL;

		MAKE_OLEDB_ERROR(GetDataSourceObject(&pDataSource));
		MAKE_OLEDB_ERROR(SplitTableName(bstrName));
		if (FAILED(pDataSource -> get_Class(bstrName, &lIdent))) 
			return OleDBError(DB_E_NOTABLE);

		if (NULL != plIdent)
			*plIdent = lIdent;
		return S_OK;
	}
	return OleDBError(DB_E_NOTABLE);
}

HRESULT CTRiASOleDBSession::CreateNewTable (DBID *pTableId, INT_PTR *plIdent)
{
	if (DBKIND_NAME == pTableId -> eKind || 
		DBKIND_PGUID_NAME == pTableId -> eKind ||
		DBKIND_GUID_NAME == pTableId -> eKind)
	{
	CComBSTR bstrName(pTableId -> uName.pwszName);
	INT_PTR lIdent = 0;
	CTRiASOleDBSource *pDataSource = NULL;

		MAKE_OLEDB_ERROR(GetDataSourceObject(&pDataSource));
		MAKE_OLEDB_ERROR(SplitTableName(bstrName));
		if (FAILED(pDataSource -> AddClass(bstrName, &lIdent))) 
			return OleDBError(DB_E_NOTABLE);

		if (NULL != plIdent)
			*plIdent = lIdent;
		return S_OK;
	}
	return OleDBError(DB_E_NOTABLE);
}

HRESULT CTRiASOleDBSession::DropExistingTable (DBID *pTableId)
{
	if (DBKIND_NAME == pTableId -> eKind || 
		DBKIND_PGUID_NAME == pTableId -> eKind ||
		DBKIND_GUID_NAME == pTableId -> eKind)
	{
	CComBSTR bstrName(pTableId -> uName.pwszName);
	INT_PTR lIdent = 0;
	CTRiASOleDBSource *pDataSource = NULL;

		MAKE_OLEDB_ERROR(GetDataSourceObject(&pDataSource));
		MAKE_OLEDB_ERROR(SplitTableName(bstrName));
		return SUCCEEDED(pDataSource -> DestroyClass(bstrName)) ? S_OK : OleDBError(DB_E_NOTABLE);
	}
	return OleDBError(DB_E_NOTABLE);
}

HRESULT CTRiASOleDBSession::IsExistingColumn (DBID *pTableId, DBID *pColumnId, INT_PTR *plAttrib)
{
// betreffende Tabelle wiederfinden
INT_PTR lIdent = 0;

	MAKE_OLEDB_ERROR(IsExistingTable(pTableId, &lIdent));

// versuchen Spalte wiederzufinden
	if (DBKIND_NAME == pColumnId -> eKind || 
		DBKIND_PGUID_NAME == pColumnId -> eKind ||
		DBKIND_GUID_NAME == pColumnId -> eKind)
	{
	CComBSTR bstrName(pColumnId -> uName.pwszName);
	INT_PTR lAttrib = 0;
	CTRiASOleDBSource *pDataSource = NULL;

		MAKE_OLEDB_ERROR(GetDataSourceObject(&pDataSource));
		if (FAILED(pDataSource -> get_Attribute(lIdent, bstrName, &lAttrib)))
			return OleDBError(DB_E_NOCOLUMN);

		if (NULL != plAttrib)
			*plAttrib = lAttrib;
		return S_OK;
	}
	return OleDBError(DB_E_NOCOLUMN);
}

HRESULT CTRiASOleDBSession::CreateNewColumn (
	DBID *pTableID, const DBCOLUMNDESC *pColumnDesc, DBID **ppColumnID, INT_PTR *plAttrib)
{
DBID *pColIdResult = NULL;
CAutoMemRelease<DBID, CComFree<DBID> > amr(pColIdResult);

	if (NULL != ppColumnID) {
		pColIdResult = (DBID *)CoTaskMemAlloc(sizeof(DBID));
		if (NULL == pColIdResult) return E_OUTOFMEMORY;
	}

// betreffende Tabelle wiederfinden
INT_PTR lIdent = 0;
const DBID *pColumnId = &pColumnDesc->dbcid;

	MAKE_OLEDB_ERROR(IsExistingTable(pTableID, &lIdent));

// versuchen Spalte zu erzeugen
	if (DBKIND_NAME == pColumnId -> eKind || 
		DBKIND_PGUID_NAME == pColumnId -> eKind ||
		DBKIND_GUID_NAME == pColumnId -> eKind)
	{
	CComBSTR bstrName(pColumnId -> uName.pwszName);
	INT_PTR lAttrib = 0;
	CTRiASOleDBSource *pDataSource = NULL;

		MAKE_OLEDB_ERROR(GetDataSourceObject(&pDataSource));
		if (FAILED(pDataSource -> AddAttribute(lIdent, bstrName, &lAttrib)))
			return OleDBError(DB_E_NOCOLUMN);

		if (NULL != ppColumnID) {
		CDBID ColumnId(lAttrib);

			CopyDBIDs(*ppColumnID, &ColumnId);
			amr.Detach();
		}
		if (NULL != plAttrib)
			*plAttrib = lAttrib;

		return S_OK;
	}
	return OleDBError(DB_E_NOCOLUMN);
}

HRESULT CTRiASOleDBSession::DropExistingColumn (DBID *pTableID, DBID *pColumnId)
{
// betreffende Tabelle wiederfinden
INT_PTR lIdent = 0;

	MAKE_OLEDB_ERROR(IsExistingTable(pTableID, &lIdent));

// versuchen Spalte zu wiederzufinden
	if (DBKIND_NAME == pColumnId -> eKind || 
		DBKIND_PGUID_NAME == pColumnId -> eKind ||
		DBKIND_GUID_NAME == pColumnId -> eKind)
	{
	CComBSTR bstrName(pColumnId -> uName.pwszName);
	CTRiASOleDBSource *pDataSource = NULL;

		MAKE_OLEDB_ERROR(GetDataSourceObject(&pDataSource));
		if (FAILED(pDataSource -> DestroyAttribute(lIdent, bstrName)))
			return OleDBError(DB_E_NOCOLUMN);

		return S_OK;
	}
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// support for IAlterTable
HRESULT CTRiASOleDBSession::AlterExistingTable (
	DBID *pTableId, DBID *pNewTableId, ULONG cPropertySets, DBPROPSET rgPropertySets[])
{
	return E_NOTIMPL;
}

HRESULT CTRiASOleDBSession::AlterExistingColumn(
	DBID *pTableId, DBID *pColumnId, DBCOLUMNDESCFLAGS rgColumnDescFlags, DBCOLUMNDESC *pColumnDesc)
{
	return S_OK;
}

