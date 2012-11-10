// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.05.2001 18:22:53 
//
// @doc
// @module TRiASOleDBCommand.cpp | Definition of the <c CTRiASOleDBCommand> class

#include "stdafx.h"

#include <Atl/CieThis.h>

#include "GenerateColumnInfo.h"
#include "TRiASOleDBDataSource.h"
#include "TRiASOleDBRowSet.h"
#include "TRiASOleDBSession.h"
#include "SchemaRowsets.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

/////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBCommand
HRESULT CTRiASOleDBCommand::Execute(
	IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams, 
	LONG * pcRowsAffected, IUnknown ** ppRowset)
{
ObjectLock lock(this);
CTRiASOleDBRowset *pRowset;
HRESULT hr = E_FAIL;

	SetErrorInfo(0, NULL);
	RETURN_ERROR(hr = CreateRowset(pUnkOuter, riid, pParams, pcRowsAffected, ppRowset, pRowset));

	return hr;
}

ATLCOLUMNINFO *CTRiASOleDBCommand::GetRawColumnInfo(ULONG *pcCols) 
{ 
	_ASSERTE(NULL != pcCols);

	if (FAILED(PrepareColumnInfo()))
		return NULL;

	*pcCols = m_pGenColInfo -> GetColumnInfo().GetSize(); 
	return m_pGenColInfo -> GetColumnInfo().GetColumnInfo().GetData(); 
}

HRESULT CTRiASOleDBCommand::PrepareColumnInfo()
{
ObjectLock lock(this);

	if (NULL != m_pGenColInfo && m_pGenColInfo -> IsPrepared()) 
		return S_OK;		// bereits alles vorbereitet

// zugehöriges DataSource object besorgen
CTRiASOleDBSource *pDataSource = NULL;

	MAKE_OLEDB_ERROR(GetDataSourceObject(this, &pDataSource));

// sicherstellen, daß die benötigten Columns bekannt sind
	ATLTRY(m_pGenColInfo = new CGenerateColumnInfo<&IID_ICommand>());
	if (NULL == m_pGenColInfo) return OleDBError(E_OUTOFMEMORY);

STATEMENT_TYPE rgStmtType = STATEMENT_TYPE_UNKNOWN;
HRESULT hr = S_OK;

// m_strCommand enthält entweder den SQL Befehl oder einen Tabellennamen
	MAKE_OLEDB_ERROR(m_pGenColInfo -> PrepareStatement(m_strCommandText, &rgStmtType));

	switch (rgStmtType) {
	case STATEMENT_TYPE_UPDATE:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_SELECT:
		RETURN_ERROR(PrepareSelect(pDataSource));
		break;

	case STATEMENT_TYPE_INSERT:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_DELETE:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_CREATETABLE:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_DROPTABLE:
		hr = OleDBError(E_NOTIMPL);
		break;

	default:
	case STATEMENT_TYPE_UNKNOWN:
		hr = OleDBError(DB_E_ERRORSINCOMMAND);
		break;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Select Statement vorbereiten
HRESULT CTRiASOleDBCommand::PrepareSelect(CTRiASOleDBSource *pDataSource)
{
CComVariant varBookmarks;
HRESULT hr = GetPropValue(&DBPROPSET_ROWSET, DBPROP_BOOKMARKS, &varBookmarks);

	_ASSERTE(NULL != m_pGenColInfo);
	m_pGenColInfo -> SetUseBookmarks(S_OK == hr && VARIANT_TRUE == varBookmarks.boolVal);
	RETURN_ERROR(m_pGenColInfo -> PrepareColumnInfo(pDataSource));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// overloads from ICommandPrepareImpl
HRESULT CTRiASOleDBCommand::PrepareCommand(ULONG cExpectedRuns)
{
ObjectLock lock(this);

	SetErrorInfo(0, NULL);
	return PrepareColumnInfo();
}

HRESULT CTRiASOleDBCommand::UnprepareCommand()
{
ObjectLock lock(this);

	SetErrorInfo(0, NULL);
	if (NULL != m_pGenColInfo)
		m_pGenColInfo -> SetPrepared (false);
	return S_OK;
}

