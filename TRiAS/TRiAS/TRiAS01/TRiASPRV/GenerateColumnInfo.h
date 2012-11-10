// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.05.2001 12:01:04 
//
// @doc
// @module GenerateColumnInfo.h | Declaration of the <c CGenerateColumnInfo> class

#if !defined(_GENERATECOLUMNINFO_H__90F3FF77_9342_4393_A611_1C465AD9494C__INCLUDED_)
#define _GENERATECOLUMNINFO_H__90F3FF77_9342_4393_A611_1C465AD9494C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/ComBool.h>

#include "AtlColumnInfo.h"
#include "AliasMap.h"

///////////////////////////////////////////////////////////////////////////////
// Informationen über sämtliche Spaltene eines Rowsets
class CColumnInfo
{
public:
	typedef map<CComBSTR, CComBSTR, less<CComBSTR> > CBaseTableMap;

	CColumnInfo() : m_ColAccess(0) {}
	~CColumnInfo() {}

	BOOL Add (CAtlColumnInfo &rCol)
	{
		return m_ColInfo.Add (rCol);
	}
	BOOL Add (IHandleDataAccess *pIHandler)
	{
	size_t ulSize = m_ColAccess.size();

		m_ColAccess.push_back(CComPtr<IHandleDataAccess>(pIHandler));
		return (m_ColAccess.size() == ulSize+1) ? TRUE : FALSE;
	}
	void RemoveAll()
	{
		m_ColInfo.RemoveAll();
		m_ColAccess.erase();
		m_BaseTables.erase();
	}
	int GetSize()
	{
		_ASSERTE(IsValid());
		return m_ColInfo.GetSize();
	}
	bool IsValid() 
	{
		return m_ColInfo.GetSize() == m_ColAccess.size();
	}

	CSimpleArray<CAtlColumnInfo> &GetColumnInfo() { return m_ColInfo; }

	CComPtr<IHandleDataAccess> GetHandler(ULONG ulColumn) const
	{ 
		_ASSERTE(0 <= ulColumn && ulColumn < m_ColAccess.size());
		return m_ColAccess[ulColumn];
	}

// Liefert, ob Daten als Pointer oder direkt abgegeben werden
	bool MustIndirectGetData(ULONG ulColumn)
	{
		_ASSERTE(0 <= ulColumn && ulColumn < m_ColAccess.size());
	
	// Bookmark gesondert behandeln (hat keinen Handler)
		if (DBCOLUMNFLAGS_ISBOOKMARK & m_ColInfo.m_aT[ulColumn].dwFlags)
			return true;

	// alle anderen Spalten landen hier
	CComBool Value;
	CComPtr<IHandleDataAccess> Handler (m_ColAccess[ulColumn]);

		_ASSERTE(Handler != NULL);
		if (SUCCEEDED(Handler -> get_MustIndirectGetData(&Value)))
			return bool(Value);

		_ASSERTE(FALSE);
		return false;
	}
//	CAtlColumnInfo &rColInfo = m_ColInfo.m_aT[ulColumn];
//
//		if (DBCOLUMNFLAGS_ISROWID & rColInfo.dwFlags)		// Objektnummer
//			return false;
//		if (DBCOLUMNFLAGS_ISBOOKMARK & rColInfo.dwFlags)	// Bookmark
//			return true;
//
//		switch (rColInfo.wType) {
//		case DBTYPE_BSTR:
//			return true;		// BSTR's werden als ptr gehandelt
//
//		case DBTYPE_WSTR:
//		case DBTYPE_GUID:
//		case DBTYPE_BYTES:
//			return false;		// Strings, Guids und Geometrie sind schon als Pointer gespeichert
//
//		default:
//			_ASSERTE(FALSE);	// andere Typen haben wir derzeit nicht
//			break;
//		}
//		return false;
//	}

// Liefert, ob Daten als Pointer oder direkt gespeichert werden
	bool MustIndirectCompareData(ULONG ulColumn)
	{
		_ASSERTE(0 <= ulColumn && ulColumn < m_ColAccess.size());

	// Bookmark gesondert behandeln (hat keinen Handler)
		if (DBCOLUMNFLAGS_ISBOOKMARK & m_ColInfo.m_aT[ulColumn].dwFlags)
			return false;

	// alle anderen Spalten landen hier
	CComBool Value;
	CComPtr<IHandleDataAccess> Handler (m_ColAccess[ulColumn]);

		_ASSERTE(Handler != NULL);
		if (SUCCEEDED(Handler -> get_MustIndirectCompareData(&Value)))
			return bool(Value);

		_ASSERTE(FALSE);
		return false;
	}
//	CAtlColumnInfo &rColInfo = m_ColInfo.m_aT[ulColumn];
//
//		if (DBCOLUMNFLAGS_ISROWID & rColInfo.dwFlags)		// Objektnummer
//			return true;
//		if (DBCOLUMNFLAGS_ISBOOKMARK & rColInfo.dwFlags)	// Bookmark
//			return false;
//
//		switch (rColInfo.wType) {
//		case DBTYPE_BSTR:
//		case DBTYPE_WSTR:
//		case DBTYPE_GUID:
//		case DBTYPE_BYTES:
//			return true;		// Strings, Guids und Geometrie sind schon als Pointer gespeichert
//
//		default:
//			_ASSERTE(FALSE);	// andere Typen haben wir derzeit nicht
//			break;
//		}
//		return false;
//	}

	UINT GetDataLen (ULONG ulColumn, void *pData)
	{
		_ASSERTE(0 <= ulColumn && ulColumn < m_ColAccess.size());
		
	// Bookmark gesondert behandeln (hat keinen Handler)
		if (DBCOLUMNFLAGS_ISBOOKMARK & m_ColInfo.m_aT[ulColumn].dwFlags)
			return sizeof(INT_PTR);

	// alle anderen Spalten landen hier
	ULONG ulLen = 0;
	CComPtr<IHandleDataAccess> Handler (m_ColAccess[ulColumn]);

		_ASSERTE(Handler != NULL);
		if (SUCCEEDED(Handler -> GetDataLength(pData, &ulLen)))
			return ulLen;

		return 0;
	}
//	CAtlColumnInfo &rColInfo = m_ColInfo.m_aT[ulColumn];
//
//		if (DBCOLUMNFLAGS_ISROWID & rColInfo.dwFlags)		// Objektnummer
//			return sizeof(INT_PTR);
//		if (DBCOLUMNFLAGS_ISBOOKMARK & rColInfo.dwFlags)	// Bookmark
//			return sizeof(INT_PTR);
//
//		switch (rColInfo.wType) {
//		case DBTYPE_BSTR:
//			return SysStringByteLen((BSTR)pData);
//
//		case DBTYPE_GUID:
//			return sizeof(GUID);
//
//		case DBTYPE_WSTR:
//			return SysStringLen((BSTR)pData) * sizeof(OLECHAR);		// Nullbyte nicht mitzählen
//
//		case DBTYPE_BYTES:
//			return SysStringByteLen((BSTR)pData);
//	
//		default:
//			_ASSERTE(FALSE);	// andere Typen haben wir derzeit nicht
//			break;
//		}
//		return 0;
//	}

// liefert zugehörige Expression
	HRESULT GetExpression (LPCOLESTR bstrName, ITRiASExpression **ppIExpr)
	{
	ULONG ulColumn = 0;

		RETURN_ERROR(GetColumnId (bstrName, &ulColumn));

	CComQIPtr<ITRiASExpression> Expr (m_ColAccess[ulColumn].m_T);

		if (Expr == NULL)
			return E_UNEXPECTED;

		_ASSERTE(NULL != ppIExpr);
		*ppIExpr = Expr.Detach();
		return S_OK;
	}
	HRESULT GetExpression (INT_PTR lMCode, ITRiASExpression **ppIExpr)
	{
	ULONG ulColumn = 0;

		RETURN_ERROR(GetColumnId (lMCode, &ulColumn));

	CComQIPtr<ITRiASExpression> Expr (m_ColAccess[ulColumn].m_T);

		if (Expr == NULL)
			return E_UNEXPECTED;

		_ASSERTE(NULL != ppIExpr);
		*ppIExpr = Expr.Detach();
		return S_OK;
	}

	HRESULT GetColumnId (LPCOLESTR bstrName, ULONG *pulColId)
	{
		_ASSERTE(NULL != pulColId);

	// versuchen, Spalte wiederzufinden
		for (int i = 0; i < m_ColInfo.GetSize(); ++i) {
			if (DBKIND_NAME != m_ColInfo.m_aT[i].columnid.eKind) 
			// ggf. im Namen suchen
				continue;	// nur über MCode suchen

			if (!wcscmp(m_ColInfo.m_aT[i].pwszName, bstrName)) {
				*pulColId = i;
				return S_OK;
			}
		}
		return DB_E_NOCOLUMN;
	}
	HRESULT GetColumnId (INT_PTR lMCode, ULONG *pulColId)
	{
		_ASSERTE(NULL != pulColId);

	// versuchen, Spalte wiederzufinden
		for (int i = 0; i < m_ColInfo.GetSize(); ++i) {
			if (DBKIND_PROPID != m_ColInfo.m_aT[i].columnid.eKind)
				continue;	// nur über MCode suchen

			if (m_ColInfo.m_aT[i].columnid.uName.ulPropid == lMCode) {
				*pulColId = i;
				return S_OK;
			}
		}
		return DB_E_NOCOLUMN;
	}

// Namen der BaseTables zu Spaltennamen zuordnen
	HRESULT AddToBaseTables (BSTR bstrBaseTable)
	{
	size_t ulSize = m_BaseTables.size();

		m_BaseTables.push_back(CComBSTR(bstrBaseTable));
		return (m_BaseTables.size() == ulSize+1) ? S_OK : E_OUTOFMEMORY;
	}

	HRESULT GetBaseTable (LPCOLESTR bstrName, BSTR *pbstrBaseTable)
	{
	ULONG ulColumn = 0;

		RETURN_ERROR(GetColumnId (bstrName, &ulColumn));

	CComBSTR bstrBaseTable (m_BaseTables[ulColumn].m_T);

		*pbstrBaseTable = bstrBaseTable.Detach();
		return S_OK;
	}
	HRESULT GetBaseTable (INT_PTR lMCode, BSTR *pbstrBaseTable)
	{
	ULONG ulColumn = 0;

		RETURN_ERROR(GetColumnId (lMCode, &ulColumn));

	CComBSTR bstrBaseTable (m_BaseTables[ulColumn].m_T);

		*pbstrBaseTable = bstrBaseTable.Detach();
		return S_OK;
	}

private:
	CSimpleArray<CAtlColumnInfo> m_ColInfo;
	vector<CAdapt<CComPtr<IHandleDataAccess> > > m_ColAccess;
	vector<CAdapt<CComBSTR> > m_BaseTables;		// AsName-->BaseTable
};

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class CTRiASOleDBSource;
class CTRiASOleDBRowset;

class CGenerateColumnInfoBase
{
public:
	CGenerateColumnInfoBase() : 
		m_fUseBookmark(false), m_fPrepared(false)
	{
	}
	~CGenerateColumnInfoBase() 
	{
	}

	HRESULT PrepareColumnInfo (CTRiASOleDBSource *pDataSource);
	HRESULT PrepareStatement(BSTR bstrCommand, STATEMENT_TYPE *prgType);

// Fehlerbehandlung
	virtual HRESULT OleDBError (HRESULT hrErr, DWORD dwMinor = IDENTIFIER_SDK_ERROR) = 0;

// accessors
	void SetUseBookmarks(bool fUseBookmark = true) { m_fUseBookmark = fUseBookmark; }
	bool GetUseBookmarks() const { return m_fUseBookmark; }

	CColumnInfo &GetColumnInfo() 
	{
		_ASSERTE(IsPrepared());
		return m_ColInfo;
	}
	HRESULT GetParser(IParser **ppIParser)
	{
		_ASSERTE(NULL != ppIParser && m_Parser != NULL);
		return (*ppIParser = m_Parser) -> AddRef(), S_OK;
	}
	CAliasMap &GetTableAliases()
	{
		_ASSERTE(IsPrepared());
		return m_TableAliases;
	}
	CAliasMap &GetColumnAliases()
	{
		_ASSERTE(IsPrepared());
		return m_ColumnAliases;
	}

	bool IsPrepared() { return m_fPrepared; }
	void SetPrepared(bool fPrepared) 
	{ 
		m_fPrepared = fPrepared; 
		if (!fPrepared) {
			m_Parser = NULL;
			m_ColInfo.RemoveAll();
			m_TableAliases.Tidy();
			m_ColumnAliases.Tidy();
		}
	}

	CComBSTR ResolveTableAlias(CComBSTR &rbstrAlias)
	{
		return m_TableAliases.ResolveAlias(rbstrAlias);
	}
	CComBSTR ResolveColumnAlias(CComBSTR &rbstrAlias)
	{
		return m_ColumnAliases.ResolveAlias(rbstrAlias);
	}

protected:
	HRESULT FillAllColumns(CTRiASOleDBSource *pDataSource, ULONG &rlOrd, LONG &rlCustCount);
	HRESULT FillColumnsFromIdent (CTRiASOleDBSource *pDataSource, INT_PTR lIdent, ULONG &rlOrd, LONG &rlCustCount, BSTR bstrBaseTable);

	HRESULT FillColumn (CTRiASOleDBSource *pDataSource, IGenericStack *pIStack, ULONG &rlOrd, bool *pfFilled);
	HRESULT FillColumnFromSingleTerm(CTRiASOleDBSource *pDatasource, IExpressionItem *pIItem, ULONG &rlOrd, LONG &rlCustCount, BSTR bstrAsName);
	HRESULT FillColumnFromExpression(CTRiASOleDBSource *pDatasource, IGenericStack *pIStack, ULONG &rlOrd, LONG &rlCustCount, BSTR bstrAsName);
	HRESULT FillObjNrColumn (CTRiASOleDBSource *pDatasource, ULONG &rlOrd, BSTR bstrAsName = NULL);
	HRESULT FillObjGuidColumn (CTRiASOleDBSource *pDatasource, ULONG &rlOrd, BSTR bstrAsName = NULL);
	HRESULT FillGeometryColumn (CTRiASOleDBSource *pDatasource, ULONG &rlOrd, INT_PTR lIdent, BSTR bstrBaseTable, DWORD dwType = 0, BSTR bstrAsName = NULL);

	HRESULT SelectHasStar(CTRiASOleDBSource *pDataSource, IEnumVARIANT *pIEnum, bool *pfHasStar);
	HRESULT ItemHasStar (CTRiASOleDBSource *pDataSource, IExpressionItem *pIItem, bool *pfHasStar);

	HRESULT AddIdentColumn (CTRiASOleDBSource *pDatasource, IExpressionItem *pIItem, ULONG &rlOrd, LONG &rlCustCount, BSTR bstrAsName);
	HRESULT AddIdentColumn(CTRiASOleDBSource *pDatasource, BSTR bstrName, INT_PTR lMCode, ULONG &rlOrd, LONG &rlCustCount, BSTR bstrBaseTable, BSTR bstrAsName = NULL);
	HRESULT AddFunctionColumn (CTRiASOleDBSource *pDatasource, IExpressionItem *pIItem, ULONG &rlOrd, LONG &rlCustCount, BSTR bstrAsName);

	HRESULT GetSingleTableName(ISelectStmt *pISelect);

protected:
	CComPtr<IParser> m_Parser;
	CColumnInfo m_ColInfo;
	CAliasMap m_TableAliases;
	CAliasMap m_ColumnAliases;
	CComBSTR m_bstrSingleTable;		// Spezialfall: eine Tabelle (Spalten können ohne 'Tabelle.' gegeben sein)

private:
	bool m_fUseBookmark;
	bool m_fPrepared;
};

template<const IID *pIId, const CLSID *pClsId = &CLSID_TRiASOleDB>
class CGenerateColumnInfo :
	public CGenerateColumnInfoBase
{
public:
	CGenerateColumnInfo() : 
		CGenerateColumnInfoBase()
	{
	}

// Fehlerbehandlung
	HRESULT OleDBError (HRESULT hrErr, DWORD dwMinor = IDENTIFIER_SDK_ERROR)
	{
		return ::OleDBError(hrErr, *pClsId, *pIId, dwMinor);
	}
};

#endif // !defined(_GENERATECOLUMNINFO_H__90F3FF77_9342_4393_A611_1C465AD9494C__INCLUDED_)
