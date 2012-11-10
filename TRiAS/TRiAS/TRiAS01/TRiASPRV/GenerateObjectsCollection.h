// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.05.2001 21:05:28 
//
// @doc
// @module GenerateObjectsCollection.h | Declaration of the <c CGenerateObjectsCollection> class

#if !defined(_GENERATEOBJECTSCOLLECTION_H__F146171A_F996_4F3A_8413_6AFEDFD21271__INCLUDED_)
#define _GENERATEOBJECTSCOLLECTION_H__F146171A_F996_4F3A_8413_6AFEDFD21271__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "AliasMap.h"

///////////////////////////////////////////////////////////////////////////////
// CGenerateObjectsCollection
class CGenerateObjectsCollection
{
public:
	CGenerateObjectsCollection(CGenerateColumnInfoBase *pGenColInfo) :
		m_rColInfo(pGenColInfo->GetColumnInfo()), 
		m_rTableAliases(pGenColInfo->GetTableAliases()), 
		m_rColumnAliases(pGenColInfo->GetColumnAliases()),
		m_rgIdxType(INDEXTYPE_Unknown)
	{
		pGenColInfo->GetParser(&m_Parser);
		
		_ASSERTE(m_Parser != NULL);
		_ASSERTE(m_rTableAliases.IsInitialized());
		_ASSERTE(m_rColumnAliases.IsInitialized());
	}
	~CGenerateObjectsCollection()
	{
	}

	HRESULT PrepareObjectsCollection(CTRiASOleDBSource *pDataSource, ITRiASEnumNativeObjects **ppIObjsOut);
	HRESULT PrepareObjectsCollection(CTRiASOleDBSource *pDataSource, BSTR bstrIndex, ITRiASEnumNativeObjects **ppIObjsOut);

// Fehlerbehandlung
	HRESULT OleDBError (HRESULT hrErr, DWORD dwMinor = IDENTIFIER_SDK_ERROR)
	{
		return ::OleDBError(hrErr, CLSID_TRiASOleDB, IID_IRowset, dwMinor);
	}

// Alias auflösen
	CComBSTR ResolveTableAlias(CComBSTR &rbstrAlias)
	{
		return m_rTableAliases.ResolveAlias(rbstrAlias);
	}

// Index verwalten
	enum INDEXTYPE {
		INDEXTYPE_Unknown = 0,
		INDEXTYPE_ONr = 1,
		INDEXTYPE_Guid = 2,
		INDEXTYPE_ObjProp = 3,
	};
	INDEXTYPE GetIndexType() const { return m_rgIdxType; }

protected:
	HRESULT GetObjectListFromTables(CTRiASOleDBSource *pDataSource, ISelectStmt *pISelect, ITRiASEnumNativeObjects **ppIObjsOut, ITRiASExpression *pIExpr = NULL);
	HRESULT GetObjectListFromTable(CTRiASOleDBSource *pDataSource, ISelectStmt *pISelect, BSTR bstrIndex, ITRiASEnumNativeObjects **ppIObjsOut);

private:
	CComPtr<IParser> m_Parser;
	CColumnInfo &m_rColInfo;
	CAliasMap &m_rTableAliases;
	CAliasMap &m_rColumnAliases;
	INDEXTYPE m_rgIdxType;
};

#endif // !defined(_GENERATEOBJECTSCOLLECTION_H__F146171A_F996_4F3A_8413_6AFEDFD21271__INCLUDED_)
