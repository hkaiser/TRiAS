// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.06.2001 14:23:50 
//
// @doc
// @module TRiASOleDBIndex.cpp | Definition of the <c CTRiASOleDBIndex> class

#include "StdAfx.h"

#include <Atl/CieThis.h>

#include "GenerateColumnInfo.h"
#include "GenerateObjectsCollection.h"

#include "TRiASOleDBSession.h"
#include "TRiASOleDBDataSource.h"
#include "SchemaRowsets.h"

#include "TRiASOleDBRowSet.h"
#include "TRiASOleDBIndex.h"

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBIndex
STDMETHODIMP CTRiASOleDBIndex::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRowset,
		&IID_IRowsetIndex,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// gewünschten Rowset zusammenbauen
HRESULT CTRiASOleDBIndex::Execute(DBPARAMS *pParams, LONG *pcRowsAffected)
{
// ggf. GenColInfo erzeugen	
	if (NULL == m_pGenColInfo) {
	// alles lokal anlegen
		ATLTRY(m_pGenColInfo = new CGenerateColumnInfo<&IID_IRowsetIndex>());
		if (NULL == m_pGenColInfo) return OleDBError(E_OUTOFMEMORY);
	}

STATEMENT_TYPE rgStmtType = STATEMENT_TYPE_UNKNOWN;
HRESULT hr = S_OK;

	MAKE_OLEDB_ERROR(m_pGenColInfo->PrepareStatement(m_strCommandText, &rgStmtType));
	switch (rgStmtType) {
	case STATEMENT_TYPE_UPDATE:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_SELECT:
		RETURN_ERROR(ExecuteSelect (pParams, pcRowsAffected));
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

HRESULT CTRiASOleDBIndex::ExecuteSelect (DBPARAMS *pParams, LONG *pcRowsAffected)
{
// feststellen, wieviele Rows maximal geliefert werden sollen
ULONG lMaxRows = 0;
CComVariant vMaxRows(0, VT_I4);
HRESULT hr = GetPropValue(&DBPROPSET_ROWSET, DBPROP_MAXROWS, &vMaxRows);

	if (SUCCEEDED(hr) && SUCCEEDED(vMaxRows.ChangeType(VT_UI4)))
		lMaxRows = V_UI4(&vMaxRows);

// vorbereitende Selektionsaufgaben
CComPtr<ITRiASEnumNativeObjects> Objs;

	RETURN_ERROR(PrepareColumnInfo());			// benötigte Spalten
	RETURN_ERROR(PrepareObjectsList(&Objs));	// Objektmenge

// rudimentären Rowset bauen
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR_EX2(Objs -> get__NewEnum(&UnkEnum), E_UNEXPECTED);

ObjectLock lock(this);
CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
CComVariant vObj;

	_ASSERTE(Enum != NULL);
	for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&vObj), NULL); /**/) {
		_ASSERTE(VT_I4 == V_VT(&vObj));

	// diese Row zum Rowset hinzufügen
	CTRiASOleDBRow Row (*this, V_I4(&vObj));

		if (!m_rgRowData.Add(Row))
			return OleDBError(E_OUTOFMEMORY);

	// ggf. nur eine bestimmte Anzahl von Rows liefern
		if (0 != lMaxRows && m_rgRowData.GetCount() >= lMaxRows)
			break;		// genug für heute
	}

// Anzahl der erzeugten Rows liefern
	if (pcRowsAffected != NULL) 
		*pcRowsAffected = m_rgRowData.GetCount();

	return S_OK;
}

HRESULT CTRiASOleDBIndex::PrepareColumnInfo()
{
ObjectLock lock(this);

	_ASSERTE(NULL != m_pGenColInfo);
	if (m_pGenColInfo->IsPrepared()) 
		return S_OK;		// bereits alles vorbereitet

// m_strCommand enthält entweder den SQL Befehl oder einen Tabellennamen
	MAKE_OLEDB_ERROR(EnsureDatabaseObject());

// sicherstellen, daß die benötigten Columns bekannt sind
// wenn Bookmarks gefragt sind, dann zusätzliche Spalte einfügen
CComVariant varBookmarks;
HRESULT hr = GetPropValue(&DBPROPSET_ROWSET, DBPROP_BOOKMARKS, &varBookmarks);

	m_pGenColInfo->SetUseBookmarks(S_OK == hr && VARIANT_TRUE == varBookmarks.boolVal);
	RETURN_ERROR(m_pGenColInfo->PrepareColumnInfo(m_pDataSource));
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Menge der Objekte der Resultatmenge (sortiert nach Index)
HRESULT CTRiASOleDBIndex::PrepareObjectsList(ITRiASEnumNativeObjects **ppIObjsOut)
{
ObjectLock lock(this);

// Objektmenge anfordern
CGenerateObjectsCollection Helper (m_pGenColInfo);

	MAKE_OLEDB_ERROR(EnsureDatabaseObject());
	MAKE_OLEDB_ERROR(Helper.PrepareObjectsCollection(m_pDataSource, m_strIndexText, ppIObjsOut));

// zusätzliche Properties setzen
CComVariant vPrimaryKey(false);
CComVariant vUnique(false);
CComVariant vIdxType(DBPROPVAL_IN_IGNORENULL, VT_I4);

	switch (Helper.GetIndexType()) {
	default:
	case CGenerateObjectsCollection::INDEXTYPE_Unknown:
		return OleDBError(E_UNEXPECTED);

	case CGenerateObjectsCollection::INDEXTYPE_ONr:
		V_BOOL(&vPrimaryKey) = VARIANT_TRUE;
		V_BOOL(&vUnique) = VARIANT_TRUE;
		V_I4(&vIdxType) = DBPROPVAL_IN_DISALLOWNULL;
		break;

	case CGenerateObjectsCollection::INDEXTYPE_Guid:
		V_BOOL(&vUnique) = VARIANT_TRUE;
		V_I4(&vIdxType) = DBPROPVAL_IN_DISALLOWNULL;
		break;

	case CGenerateObjectsCollection::INDEXTYPE_ObjProp:
		break;
	}

CComVariant vTrue(true);

	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_ROWSET, DBPROP_IRowsetIndex, &vTrue));

	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_INDEX, DBPROP_INDEX_PRIMARYKEY, &vPrimaryKey));
	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_INDEX, DBPROP_INDEX_TYPE, &vIdxType));
	MAKE_OLEDB_ERROR(SetPropValue(&DBPROPSET_INDEX, DBPROP_INDEX_UNIQUE, &vUnique));

	return S_OK;
}

