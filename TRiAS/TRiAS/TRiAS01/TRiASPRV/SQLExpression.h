// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 08.06.2001 20:21:09 
//
// @doc
// @module SQLExpression.h | Declaration of the <c CSQLExpression> class

#if !defined(_SQLEXPRESSION_H__4E852ADE_893B_4E5F_9A44_ADCAC27CAEE3__INCLUDED_)
#define _SQLEXPRESSION_H__4E852ADE_893B_4E5F_9A44_ADCAC27CAEE3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/deque>
#include <ospace/std/stack>

#include "GenerateColumnInfo.h"

///////////////////////////////////////////////////////////////////////////////
// Helperklasse um SQL Parser 'IGenericStack' Objekte in ExpressionTree umzusetzen
class CSQLExpression 
{
public:
	typedef stack<CAdapt<CComPtr<ITRiASExpression> > > ExprStack;

	CSQLExpression(CTRiASOleDBSource *pDataSource, CAliasMap &rTableAliases, 
				   CAliasMap &rColumnAliases, CColumnInfo *pColInfo = NULL) :
		m_pDataSource(pDataSource), 
		m_pColInfo(pColInfo), 
		m_rTableAliases(rTableAliases),
		m_rColumnAliases(rColumnAliases)
	{
		_ASSERTE(NULL != m_pDataSource);
	}

	HRESULT ComposeExpressionTree (IGenericStack *pIStack, ITRiASExpression **ppIExprTree);
	HRESULT ComposeExpressionItem (IExpressionItem *pIItem, ITRiASExpression **ppIExprTree);

protected:
	HRESULT ComposeExpressionItem(ExprStack &rTerm, IExpressionItem *pIItem);

	HRESULT GetColumnIdentExpression (IExpressionItem *pIItem, ITRiASExpression **ppIIdent);
	HRESULT GetLiteralExpression (IExpressionItem *pIItem, ITRiASExpression **ppILiteral);
	HRESULT GetCompareExpression (IExpressionItem *pIItem, ExprStack &rStack, ITRiASExpression **ppICompare);
	HRESULT GetMathOpExpression (IExpressionItem *pIItem, ExprStack &rStack, ITRiASExpression **ppICompare);
	HRESULT GetBoolOpExpression (IExpressionItem *pIItem, ExprStack &rStack, ITRiASExpression **ppICompare);

	HRESULT GetExpression (BSTR bstrName, DWORD dwType, ITRiASExpression **ppIExpr);
	HRESULT GetExpression (INT_PTR lMCode, ITRiASExpression **ppIExpr);

private:
	CTRiASOleDBSource *m_pDataSource;
	CColumnInfo *m_pColInfo;
	CAliasMap &m_rTableAliases;
	CAliasMap &m_rColumnAliases;
};

#endif // !defined(_SQLEXPRESSION_H__4E852ADE_893B_4E5F_9A44_ADCAC27CAEE3__INCLUDED_)
