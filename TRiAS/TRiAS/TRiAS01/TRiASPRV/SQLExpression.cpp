// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 07.06.2001 21:49:21 
//
// @doc
// @module SQLExpression.cpp | Definition of the <c CSQLExpression> class

#include "StdAfx.h"

#include "SQLVerification.h"

#include "TRiASOleDBSession.h"
#include "TRiASOleDBDataSource.h"
#include "SchemaRowsets.h"

#include "Expression.h"
#include "SQLExpression.h"

#include "HandleBookmark.h"
#include "HandleObjectGuid.h"
#include "HandleNativeAttribute.h"
#include "HandleGeometry.h"

///////////////////////////////////////////////////////////////////////////////
// Erzeugen des ExpressionTrees aus einem IGenericStack Objekt
HRESULT CSQLExpression::ComposeExpressionTree(IGenericStack *pIStack, ITRiASExpression **ppIExprTree)
{
	_ASSERTE(NULL != ppIExprTree);

// Azahl der Elemente im Stack
LONG lCnt = 0;

	RETURN_ERROR(pIStack -> get_Count(&lCnt));
	if (0 == lCnt)
		return E_UNEXPECTED;

// der Stack enthält in 'reverse polish notation' die zu erzeugende Expression
ExprStack Terms;

	for (LONG i = 1; i <= lCnt; ++i) {
	CComVariant vItem;

		RETURN_ERROR(pIStack -> get_Item (i, &vItem));
		_ASSERTE(V_ISDISPATCH(&vItem));

	CComQIPtr<IExpressionItem> Item (V_DISPATCH(&vItem));

		if (Item == NULL)
			return E_UNEXPECTED;

		RETURN_ERROR(ComposeExpressionItem(Terms, Item));
	}

// jetzt darf nur noch einer übrig sein
	if (1 != Terms.size())
		return DB_E_ERRORSINCOMMAND;

// Resultat liefern
CComPtr<ITRiASExpression> Result (Terms.top());

	*ppIExprTree = Result.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen des ExpressionTrees aus einem IExpressionItem Objekt
HRESULT CSQLExpression::ComposeExpressionItem(IExpressionItem *pIItem, ITRiASExpression **ppIExprTree)
{
	_ASSERTE(NULL != ppIExprTree);

// der Stack enthält in 'reverse polish notation' die zu erzeugende Expression
ExprStack Terms;

	RETURN_ERROR(ComposeExpressionItem(Terms, pIItem));

// jetzt darf nur noch einer übrig sein
	if (1 != Terms.size())
		return DB_E_ERRORSINCOMMAND;

// Resultat liefern
CComPtr<ITRiASExpression> Result (Terms.top());

	*ppIExprTree = Result.Detach();
	return S_OK;
}

HRESULT CSQLExpression::ComposeExpressionItem(ExprStack &rTerm, IExpressionItem *pIItem)
{
	_ASSERTE(NULL != pIItem);

EXPRESSIONITEM_TYPE rgItemType = EXPRESSIONITEM_TYPE_UNKNOWN;
CComPtr<ITRiASExpression> Ident;

	RETURN_ERROR(pIItem -> get_ItemType(&rgItemType));
	switch (rgItemType) {
	case EXPRESSIONITEM_TYPE_SELECTSTAR:			// '*'
		return DB_E_ERRORSINCOMMAND;

	case EXPRESSIONITEM_TYPE_COLUMNIDENT:			// SpaltenName
		RETURN_ERROR(GetColumnIdentExpression (pIItem, &Ident));
		break;

	case EXPRESSIONITEM_TYPE_LITERALVALUE:			// 'text' oder Zahl
		RETURN_ERROR(GetLiteralExpression (pIItem, &Ident));
		break;

	case EXPRESSIONITEM_TYPE_AGGREGATEFUNCTION:		// min(...), max(...), count(...)
		break;

	case EXPRESSIONITEM_TYPE_DATEFUNCTION:
		break;

	case EXPRESSIONITEM_TYPE_MATHFUNCTION:			// abs(...)
		break;

	case EXPRESSIONITEM_TYPE_GEOMETRYFUNCTION:		// AsText(...)
		break;

	case EXPRESSIONITEM_TYPE_ARITOPERATOR:			// +-*/
		RETURN_ERROR(GetMathOpExpression (pIItem, rTerm, &Ident));
		break;

	case EXPRESSIONITEM_TYPE_BOOLOPERATOR:			// or and
		RETURN_ERROR(GetBoolOpExpression (pIItem, rTerm, &Ident));
		break;

	case EXPRESSIONITEM_TYPE_COMPAREOPERATOR:		// <, >, <>, =, <=, >=, is, is not, not, like
		RETURN_ERROR(GetCompareExpression (pIItem, rTerm, &Ident));
		break;

	case EXPRESSIONITEM_TYPE_NULLEXPRESSION:		// NULL
		break;

	default:
		return DB_E_ERRORSINCOMMAND;
	}

// neues Item im Stack ablegen
	rTerm.push(Ident);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Spalte einer Tabelle
HRESULT CSQLExpression::GetColumnIdentExpression(IExpressionItem *pIItem, ITRiASExpression **ppIIdent)
{
	_ASSERTE(ExpressionHasType(pIItem, EXPRESSIONITEM_TYPE_COLUMNIDENT));

CComQIPtr<IColumnIdent> ColId (pIItem);
CComBSTR bstrName, bstrTable;

	_ASSERTE(ColId != NULL);
	RETURN_ERROR(ColId -> get_ColumnName(&bstrName));
	bstrName = RemoveQuotes(bstrName);

// ggf. Tabellennamen auswerten
	RETURN_ERROR(ColId -> get_TableName(&bstrTable))
	if (0 == bstrTable.Length())
		return DB_E_NOCOLUMN;

// Spalte über MCode wiederfinden
INT_PTR lMCode = 0;

// Tabellennamen ggf. in Objektklasse/Objekttyp zerlegen
DWORD dwType = 0;

	bstrTable = m_rTableAliases.ResolveAlias(RemoveQuotes(bstrTable));
	RETURN_ERROR(SplitTableName(bstrTable, &dwType));

// überprüfen, ob die gegebene Tabelle wirklich existiert
INT_PTR lIdent = 0;

	if (FAILED(m_pDataSource -> get_Class (bstrTable, &lIdent)))
		return DB_E_NOTABLE;		// Tabelle existiert nicht

CComBSTR bstrOrgName (m_rColumnAliases.ResolveAlias(bstrName));		// evtl. Alias auflösen

	if (FAILED(m_pDataSource -> get_Attribute (lIdent, bstrOrgName, &lMCode)))
		return GetExpression(bstrOrgName, dwType, ppIIdent);

	return GetExpression(lMCode, ppIIdent);
}

///////////////////////////////////////////////////////////////////////////////
// finden eines zugehörigen Handlerobjektes
HRESULT CSQLExpression::GetExpression (BSTR bstrName, DWORD dwType, ITRiASExpression **ppIExpr)
{
	_ASSERT(NULL != ppIExpr);

	if (NULL != m_pColInfo) {
	HRESULT hr = m_pColInfo -> GetExpression(bstrName, ppIExpr);

		if (FAILED(hr)) {
		// ggf. ist in der Expression der Spaltenname verwendet und in Select clause ein Alias gegeben
		CComBSTR bstrAlias;
		
			if (m_rColumnAliases.ResolveName(bstrName, &bstrAlias))
				return m_pColInfo -> GetExpression(bstrAlias, ppIExpr);
		}
		return hr;
	}

// die ColumnInfo ist noch nicht zusammengebaut, also direkt instantiieren
// an dieser Stellen können es aber nur die vordefinierten Spalten (Objektnummer, Guid 
// oder Geometrie) sein
CComBSTR bstrObjNr;		// spezielle Spalten gesondert gehandeln

	bstrObjNr.LoadString(IDS_OBJNRNAME);
	_ASSERTE(bstrObjNr.Length() > 0);
	if (bstrObjNr == bstrName) {
	// Objektnummer ist gefragt
	CComObject<CHandleBookmark> *pBookmark = NULL;
	CComPtr<ITRiASExpression> Expr;

		RETURN_ERROR(CComObject<CHandleBookmark>::CreateInstance(&pBookmark));
		Expr = pBookmark;
		*ppIExpr = Expr.Detach();
		return S_OK;
	}

CComBSTR bstrGuid;

	bstrGuid.LoadString(IDS_GUIDNAME);
	_ASSERTE(bstrGuid.Length() > 0);
	if (bstrGuid == bstrName) {
	// ObjGuid ist gefragt
	CComObject<CHandleObjectGuid> *pGuid = NULL;
	CComPtr<ITRiASExpression> Expr;

		RETURN_ERROR(CComObject<CHandleObjectGuid>::CreateInstance(&pGuid));
		Expr = pGuid;
		*ppIExpr = Expr.Detach();
		return S_OK;
	}

	if (!wcsncmp(OLESTR("OGIS_GEOMETRY"), bstrName, wcslen(OLESTR("OGIS_GEOMETRY")))) {
	// Geometrie ist gefragt
	CComObject<CHandleGeometry> *pGeom = NULL;
	CComPtr<ITRiASExpression> Expr;

		RETURN_ERROR(CComObject<CHandleGeometry>::CreateInstance(&pGeom));
		pGeom -> SetTargetType(dwType);
		Expr = pGeom;
		*ppIExpr = Expr.Detach();
		return S_OK;
	}

// alles andere ist hier ein Fehler
	return DB_E_NOCOLUMN;
}

HRESULT CSQLExpression::GetExpression (INT_PTR lMCode, ITRiASExpression **ppIExpr)
{
	_ASSERT(NULL != ppIExpr);

	if (NULL != m_pColInfo)
		return m_pColInfo -> GetExpression(lMCode, ppIExpr);

// die ColumnInfo ist noch nicht zusammengebaut, also direkt instantiieren
CComObject<CHandleNativeAttribute> *pAttribute = NULL;

	RETURN_ERROR(CComObject<CHandleNativeAttribute>::CreateInstance(&pAttribute));
	RETURN_ERROR(pAttribute -> SetAttributeHandle (lMCode));

CComPtr<ITRiASExpression> Expr(pAttribute);

	*ppIExpr = Expr.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
namespace {
	inline VARTYPE ParserTypeToVariantType (PARSER_DATATYPE rgType)
	{
		switch (rgType) {
		default:
		case PARSER_DATATYPE_UNKNOWN:
			break;

		case PARSER_DATATYPE_INTEGER:
			return VT_I4;

		case PARSER_DATATYPE_STRING:
			return VT_BSTR;

		case PARSER_DATATYPE_FLOAT:
			return VT_R8;
		}
		_ASSERTE(rgType != PARSER_DATATYPE_UNKNOWN);
		return VT_ERROR;
	}
	inline ULONG ParserTypeToColSize (PARSER_DATATYPE rgType)
	{
		switch (rgType) {
		default:
		case PARSER_DATATYPE_UNKNOWN:
			break;

		case PARSER_DATATYPE_INTEGER:
			return sizeof(DWORD);

		case PARSER_DATATYPE_STRING:
			return LONG_MAX;

		case PARSER_DATATYPE_FLOAT:
			return sizeof(double);
		}
		_ASSERTE(rgType != PARSER_DATATYPE_UNKNOWN);
		return VT_ERROR;
	}
	inline BYTE ParserTypeToPrec (PARSER_DATATYPE rgType)
	{
		switch (rgType) {
		default:
		case PARSER_DATATYPE_UNKNOWN:
			break;

		case PARSER_DATATYPE_INTEGER:
			return 10;

		case PARSER_DATATYPE_STRING:
			return ~0;

		case PARSER_DATATYPE_FLOAT:
			return 32;
		}
		_ASSERTE(rgType != PARSER_DATATYPE_UNKNOWN);
		return VT_ERROR;
	}
}

///////////////////////////////////////////////////////////////////////////////
// LiteralWert
HRESULT CSQLExpression::GetLiteralExpression(IExpressionItem *pIItem, ITRiASExpression **ppILiteral)
{
	_ASSERTE(ExpressionHasType(pIItem, EXPRESSIONITEM_TYPE_LITERALVALUE));

CComQIPtr<ILiteralValue> Literal (pIItem);

	_ASSERTE(Literal != NULL);

PARSER_DATATYPE rgType = PARSER_DATATYPE_UNKNOWN;
CComVariant vLiteral;

	V_VT(&vLiteral) = VT_BSTR;
	RETURN_ERROR(Literal -> get_AsString(&V_BSTR(&vLiteral)));
	RETURN_ERROR(Literal -> get_DataType(&rgType));
	RETURN_ERROR(vLiteral.ChangeType (ParserTypeToVariantType(rgType)));

CComObject<CConstantExpression> *pExpr = NULL;

	RETURN_ERROR(CComObject<CConstantExpression>::CreateInstance(&pExpr));

CComPtr<ITRiASExpression> Expr (pExpr);		// bump RefCnt

	RETURN_ERROR(pExpr -> Init (vLiteral, ParserTypeToColSize(rgType), ParserTypeToPrec(rgType)));
	*ppILiteral = Expr.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Vergleichsoperatoren
namespace {
	template<typename T>
	inline HRESULT CreateSingleExpression (CSingleBaseExpression **ppSingleBase, T *)
	{
	CComObject<T> *pExpr = NULL;

		RETURN_ERROR(CComObject<T>::CreateInstance(&pExpr));
		*ppSingleBase = pExpr;
		return S_OK;
	}

	template<typename T>
	inline HRESULT CreateDualExpression (CDualBaseExpression **ppDualBase, T *)
	{
	CComObject<T> *pExpr = NULL;

		RETURN_ERROR(CComObject<T>::CreateInstance(&pExpr));
		*ppDualBase = pExpr;
		return S_OK;
	}
}

HRESULT CSQLExpression::GetCompareExpression(
	IExpressionItem *pIItem, ExprStack &rStack, ITRiASExpression **ppICompare)
{
	_ASSERTE(ExpressionHasType(pIItem, EXPRESSIONITEM_TYPE_COMPAREOPERATOR));

CComQIPtr<ICompareOperator> Compare (pIItem);
CDualBaseExpression *pDualExpr = NULL;
CSingleBaseExpression *pSingleExpr = NULL;
COMPARE_OPERATOR rgType = COMPARE_OPERATOR_UNKNOWN;

	_ASSERTE(Compare != NULL);
	RETURN_ERROR(Compare -> get_CompareOperator(&rgType));
	switch (rgType) {
	case COMPARE_OPERATOR_EQUALS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CEqualExpression *)NULL));
		break;

	case COMPARE_OPERATOR_NOT_EQUALS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CNotEqualExpression *)NULL));
		break;

	case COMPARE_OPERATOR_MORE:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CGreaterExpression *)NULL));
		break;

	case COMPARE_OPERATOR_LESS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CLessExpression *)NULL));
		break;

	case COMPARE_OPERATOR_MOREEQUALS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CGreaterEqualExpression *)NULL));
		break;

	case COMPARE_OPERATOR_LESSEQUALS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CLessEqualExpression *)NULL));
		break;

	case COMPARE_OPERATOR_LIKE:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CLikeExpression *)NULL));
		break;

	case COMPARE_OPERATOR_IS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CIsNullExpression *)NULL));
		break;

	case COMPARE_OPERATOR_ISNOT:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CIsNotNullExpression *)NULL));
		break;

	case COMPARE_OPERATOR_NOT:
		RETURN_ERROR(CreateSingleExpression(&pSingleExpr, (CNotExpression *)NULL));
		break;

	default:
	case COMPARE_OPERATOR_UNKNOWN:
		return DB_E_ERRORSINCOMMAND;
	}

	_ASSERTE(NULL != pDualExpr || NULL != pSingleExpr);
	_ASSERTE(!(NULL != pDualExpr && NULL != pSingleExpr));

// neu erzeugtes Objekt fertig initialisieren
	if (NULL != pDualExpr) {
		_ASSERTE(rStack.size() >= 2);		// mind. 2 Elemente werden gebraucht

	// binary function
	CComPtr<ITRiASExpression> Expr (pDualExpr);			// bump RefCnt

	// abhängige Expressions einhängen
	CComPtr<ITRiASExpression> RightExpr(rStack.top());	// may be NULL

		rStack.pop();

	CComPtr<ITRiASExpression> LeftExpr(rStack.top());

		if (LeftExpr == NULL)
			return E_UNEXPECTED;
		rStack.pop();

		RETURN_ERROR(pDualExpr -> Init (LeftExpr, RightExpr));
		*ppICompare = Expr.Detach();
	}
	else {
		_ASSERTE(rStack.size() >= 1);		// mind. 1 Element wird gebraucht

	// unary Operationen
	CComPtr<ITRiASExpression> Expr (pSingleExpr);		// bump RefCnt

		_ASSERTE(NULL != pSingleExpr);

	// abhängige Expression einhängen
	CComPtr<ITRiASExpression> SubExpr (rStack.top());

		if (SubExpr == NULL)
			return E_UNEXPECTED;
		rStack.pop();

		RETURN_ERROR(pSingleExpr -> Init (SubExpr));
		*ppICompare = Expr.Detach();
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Mathematische Operation (+-*/)
HRESULT CSQLExpression::GetMathOpExpression(
	IExpressionItem *pIItem, ExprStack &rStack, ITRiASExpression **ppIMathOp)
{
	_ASSERTE(ExpressionHasType(pIItem, EXPRESSIONITEM_TYPE_ARITOPERATOR));

CComQIPtr<IAritOperator> MathOp (pIItem);
CDualBaseExpression *pDualExpr = NULL;
ARIT_OPERATOR rgType = ARIT_OPERATOR_UNKNOWN;
bool fNegate = false;

	_ASSERTE(MathOp != NULL);
	RETURN_ERROR(MathOp -> get_AritOperator(&rgType));
	switch (rgType) {
	case ARIT_OPERATOR_PLUS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CPlusExpression *)NULL));
		break;

	case ARIT_OPERATOR_MINUS:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CMinusExpression *)NULL));
		break;

	case ARIT_OPERATOR_MULTIPLY:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CTimesExpression *)NULL));
		break;

	case ARIT_OPERATOR_DIVIDE:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CDividesExpression *)NULL));
		break;

	default:
	case ARIT_OPERATOR_UNKNOWN:
		return DB_E_ERRORSINCOMMAND;
	}
	_ASSERTE(NULL != pDualExpr);

CComPtr<ITRiASExpression> Expr (pDualExpr);		// bump RefCnt

// abhängige Expressions 
CComPtr<ITRiASExpression> RightExpr(rStack.top());

	if (RightExpr == NULL)
		return E_UNEXPECTED;
	rStack.pop();

CComPtr<ITRiASExpression> LeftExpr(rStack.top());

	if (LeftExpr == NULL)
		return E_UNEXPECTED;
	rStack.pop();

// fertig initialisieren
	RETURN_ERROR(pDualExpr -> Init (LeftExpr, RightExpr));
	*ppIMathOp = Expr.Detach();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Logische binäre Operationen
HRESULT CSQLExpression::GetBoolOpExpression(
	IExpressionItem *pIItem, ExprStack &rStack, ITRiASExpression **ppIBoolOp)
{
	_ASSERTE(ExpressionHasType(pIItem, EXPRESSIONITEM_TYPE_BOOLOPERATOR));

CComQIPtr<IBoolOperator> BoolOp (pIItem);
CDualBaseExpression *pDualExpr = NULL;
BOOL_OPERATOR rgType = BOOL_OPERATOR_UNKNOWN;
bool fNegate = false;

	_ASSERTE(BoolOp != NULL);
	RETURN_ERROR(BoolOp -> get_BoolOperator(&rgType));
	switch (rgType) {
	case BOOL_OPERATOR_AND:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (CAndExpression *)NULL));
		break;

	case BOOL_OPERATOR_OR:
		RETURN_ERROR(CreateDualExpression(&pDualExpr, (COrExpression *)NULL));
		break;

	default:
	case BOOL_OPERATOR_UNKNOWN:
		return DB_E_ERRORSINCOMMAND;
	}
	_ASSERTE(NULL != pDualExpr);

CComPtr<ITRiASExpression> Expr (pDualExpr);		// bump RefCnt

// abhängige Expressions 
CComPtr<ITRiASExpression> RightExpr(rStack.top());

	if (RightExpr == NULL)
		return E_UNEXPECTED;
	rStack.pop();

CComPtr<ITRiASExpression> LeftExpr(rStack.top());

	if (LeftExpr == NULL)
		return E_UNEXPECTED;
	rStack.pop();

// fertig initialisieren
	RETURN_ERROR(pDualExpr -> Init (LeftExpr, RightExpr));
	*ppIBoolOp = Expr.Detach();

	return S_OK;
}

