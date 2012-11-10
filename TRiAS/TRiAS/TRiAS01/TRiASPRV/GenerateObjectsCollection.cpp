// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.05.2001 22:06:19 
//
// @doc
// @module GenerateObjectsCollection.cpp | Definition of the <c CGenerateObjectsCollection> class

#include "StdAfx.h"

#include "SQLVerification.h"
#include "SQLExpression.h"

#include "TRiASOleDBSession.h"
#include "TRiASOleDBDataSource.h"
#include "SchemaRowsets.h"

#include "GenerateObjectsCollection.h"

///////////////////////////////////////////////////////////////////////////////
// CGenerateObjectsCollection

HRESULT CGenerateObjectsCollection::PrepareObjectsCollection(
	CTRiASOleDBSource *pDataSource, ITRiASEnumNativeObjects **ppIObjsOut)
{
	_ASSERTE(NULL != pDataSource);
	_ASSERTE(NULL != ppIObjsOut);

// sicherstellen, daß es ein 'select' war
STATEMENT_TYPE rgStmt = STATEMENT_TYPE_UNKNOWN;

	MAKE_OLEDB_ERROR(m_Parser -> get_StatementType(&rgStmt));
	if (STATEMENT_TYPE_SELECT != rgStmt) 
		return OleDBError(DB_E_ERRORSINCOMMAND,TRIASOLEDB_E_SELECTEXPECTED);		// SQL Select statement expected

// ggf. gibt es eine 'where' clause
CComPtr<ISelectStmt> Select;

	MAKE_OLEDB_ERROR(m_Parser -> get_SelectStmt(&Select));
	if (Select == NULL) return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_SELECTEXPECTED);

CComPtr<IGenericStack> WhereClause;

	MAKE_OLEDB_ERROR(Select -> get_WhereExpressionStack(&WhereClause));
	if (WhereClause == NULL) return OleDBError(DB_E_ERRORSINCOMMAND);

LONG lCnt = 0;
CComPtr<ITRiASExpression> ExprTree;		// default: no Where clause

	MAKE_OLEDB_ERROR(WhereClause -> get_Count(&lCnt));

	if (lCnt > 0) {		// Where clause zu ExpressionTree verarbeiten
	CSQLExpression Expr (pDataSource, m_rTableAliases, m_rColumnAliases, &m_rColInfo);

		MAKE_OLEDB_ERROR(Expr.ComposeExpressionTree(WhereClause, &ExprTree));
	}
	RETURN_ERROR(GetObjectListFromTables(pDataSource, Select, ppIObjsOut, ExprTree));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objektmenge sortiert über Index bereitstellen
HRESULT CGenerateObjectsCollection::PrepareObjectsCollection(
	CTRiASOleDBSource *pDataSource, BSTR bstrIndex, ITRiASEnumNativeObjects **ppIObjsOut)
{
	_ASSERTE(NULL != pDataSource);
	_ASSERTE(NULL != bstrIndex && SysStringLen(bstrIndex) > 0);
	_ASSERTE(NULL != ppIObjsOut);

// sicherstellen, daß es ein 'select' war
STATEMENT_TYPE rgStmt = STATEMENT_TYPE_UNKNOWN;

	MAKE_OLEDB_ERROR(m_Parser -> get_StatementType(&rgStmt));
	if (STATEMENT_TYPE_SELECT != rgStmt) 
		return OleDBError(DB_E_ERRORSINCOMMAND,TRIASOLEDB_E_SELECTEXPECTED);		// SQL Select statement expected

// ggf. gibt es eine 'where' clause
CComPtr<ISelectStmt> Select;

	MAKE_OLEDB_ERROR(m_Parser -> get_SelectStmt(&Select));
	if (Select == NULL) return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_SELECTEXPECTED);

	RETURN_ERROR(GetObjectListFromTable(pDataSource, Select, bstrIndex, ppIObjsOut));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert die Objekte der gegebenen Tabelle als Liste (ohne Einschränkungen)
HRESULT CGenerateObjectsCollection::GetObjectListFromTables(
	CTRiASOleDBSource *pDataSource, ISelectStmt *pISelect, 
	ITRiASEnumNativeObjects **ppIObjsOut, ITRiASExpression *pIExpr)
{
	_ASSERTE(NULL != ppIObjsOut);
	*ppIObjsOut = NULL;

// Helperobjekt zum zusammenfassen der Objektmengen
CComPtr<ITRiASNativeObjectsOperations> Oper;

	MAKE_OLEDB_ERROR(Oper.CoCreateInstance(CLSID_TRiASNativeObjectsOperations));

// Tabellen durchgehen und Objekte sammeln
CComPtr<ITableIdentList> TableIdentList;
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR(pISelect -> get_TableIdentList(&TableIdentList));
	MAKE_OLEDB_ERROR(TableIdentList -> get__NewEnum(&UnkEnum));

CComPtr<ITRiASEnumNativeObjects> Objs;
CComQIPtr<IEnumVARIANT> Tables(UnkEnum);
CComVariant v;

	_ASSERTE(Tables != NULL);
	for (Tables -> Reset(); S_OK == Tables -> Next(1, &v, NULL); /**/) {
		_ASSERTE(V_ISDISPATCH(&v));

	CComQIPtr<ITableIdent> Table = V_DISPATCH(&v);
	CComBSTR bstrTable;
	INT_PTR lIdent = NULL;

		if (Table == NULL) return E_UNEXPECTED;

		MAKE_OLEDB_ERROR(Table -> get_Name(&bstrTable));
		bstrTable = ResolveTableAlias(RemoveQuotes(bstrTable));

		if (!VerifyTableIsGiven (m_Parser, bstrTable))
			return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_TABLENOTGIVENINFROMCLAUSE);		// Table not given in 'From' clause

	DWORD dwTypes = 0;

		MAKE_OLEDB_ERROR(SplitTableName(bstrTable, NULL, &dwTypes));
		if (FAILED(pDataSource -> get_Class(bstrTable, &lIdent)))
			return DB_E_NOTABLE;				// Table does not exist
		_ASSERTE(0 != lIdent);

	CComPtr<ITRiASEnumNativeObjects> ObjsIdent;

		MAKE_OLEDB_ERROR(pDataSource -> get_ObjectsFromClass(lIdent, 
			COLLECTIONTYPE_SortedONr|dwTypes, pIExpr, &ObjsIdent));
		if (Objs != NULL) {
		CComPtr<ITRiASEnumNativeObjects> ObjsT;

			MAKE_OLEDB_ERROR(Oper -> Union(Objs, ObjsIdent, &ObjsT));
			Objs = ObjsT;
		}
		else
			Objs = ObjsIdent;
	}

// gesamte Objektmenge liefern
	*ppIObjsOut = Objs.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert die Objekte der gegebenen Tabelle als Liste (ohne Einschränkungen)
HRESULT CGenerateObjectsCollection::GetObjectListFromTable(
	CTRiASOleDBSource *pDataSource, ISelectStmt *pISelect, BSTR bstrIndex, 
	ITRiASEnumNativeObjects **ppIObjsOut)
{
	_ASSERTE(NULL != ppIObjsOut);
	*ppIObjsOut = NULL;

// Tabellen durchgehen und Objekte sammeln
CComPtr<ITableIdentList> TableIdentList;
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR(pISelect -> get_TableIdentList(&TableIdentList));

long lCnt = 0;

	MAKE_OLEDB_ERROR(TableIdentList -> get_Count (&lCnt));
	if (1 != lCnt) 
		return OleDBError(DB_E_ERRORSINCOMMAND);	// nur ein Index zulässig

	MAKE_OLEDB_ERROR(TableIdentList -> get__NewEnum(&UnkEnum));

CComPtr<ITRiASEnumNativeObjects> Objs;
CComQIPtr<IEnumVARIANT> Tables(UnkEnum);
CComVariant v;

	_ASSERTE(Tables != NULL);
	for (Tables -> Reset(); S_OK == Tables -> Next(1, &v, NULL); /**/) {
		_ASSERTE(V_ISDISPATCH(&v));

	CComQIPtr<ITableIdent> Table = V_DISPATCH(&v);
	CComBSTR bstrTable;
	INT_PTR lIdent = NULL;

		if (Table == NULL) return OleDBError(E_UNEXPECTED);

		MAKE_OLEDB_ERROR(Table -> get_Name(&bstrTable));
		bstrTable = ResolveTableAlias(RemoveQuotes(bstrTable));

		if (!VerifyTableIsGiven (m_Parser, bstrTable))
			return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_TABLENOTGIVENINFROMCLAUSE);		// Table not given in 'From' clause

	// Objektklasse und Objekttypen feststellen
	DWORD dwTypes = 0;

		MAKE_OLEDB_ERROR(SplitTableName(bstrTable, NULL, &dwTypes));
		if (FAILED(pDataSource -> get_Class(bstrTable, &lIdent)))
			return OleDBError(DB_E_NOTABLE);				// Table does not exist
		_ASSERTE(0 != lIdent);

	// evtl. Quotes beseitigen
	CComBSTR bstr = RemoveQuotes(bstrIndex);

	// Objekteigenschaft feststellen
	CComBSTR bstrObjNr, bstrGuid;		// spezielle Indizes gesondert gehandeln

		bstrObjNr.LoadString(IDS_OBJNRNAME);
		bstrGuid.LoadString(IDS_GUIDNAME);
		_ASSERTE(bstrObjNr.Length() > 0 && bstrGuid.Length() > 0);
		if (bstrObjNr == bstr) {
		// nach Objektnummer sortieren
			MAKE_OLEDB_ERROR(pDataSource -> get_ObjectsFromClass(lIdent, 
				COLLECTIONTYPE_SortedONr|dwTypes, NULL, &Objs));
			m_rgIdxType = INDEXTYPE_ONr;
		}
		else if (bstrGuid == bstr) {
		// nach Guid sortieren
			MAKE_OLEDB_ERROR(pDataSource -> get_ObjectsFromClass(lIdent, 
				COLLECTIONTYPE_SortedGuid|dwTypes, NULL, &Objs));
			m_rgIdxType = INDEXTYPE_Guid;
		}
		else {
		// 'normale' Objekteigenschaft
		INT_PTR lMCode = 0;

			MAKE_OLEDB_ERROR(pDataSource -> get_Attribute (lIdent, bstr, &lMCode));
			MAKE_OLEDB_ERROR(pDataSource -> get_ObjectsFromAttrib(lIdent, lMCode, 
				NULL, NULL, DBRANGEENUM(DBRANGE_INCLUSIVESTART|DBRANGE_INCLUSIVEEND), &Objs));
			m_rgIdxType = INDEXTYPE_ObjProp;
		}
	}

// gesamte Objektmenge liefern
	*ppIObjsOut = Objs.Detach();
	return S_OK;
}

