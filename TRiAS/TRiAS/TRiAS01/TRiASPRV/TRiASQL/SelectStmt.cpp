/*  Product: Small Parser

  Copyright(C) 1999  Systementor AB, Stefan Holmberg
  Email - stefan.holmberg@systementor.se
  Web:   - http:// www.systementor.se
  
	///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: SelectStmt.cpp $ 
* 
* *****************  Version 2  *****************
* User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
* Updated in $/Products/SmallParser
*/

// SelectStmt.cpp : Implementation of cSelectStmt
#include "stdafx.h"
#include "SelectStmt.h"
#include "cAtlObjectConverter.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cSelectStmt

cSelectStmt::cSelectStmt() :
	m_fDistinct(false), m_fPercent(false), m_uiTopRows(0)
{
	CComObject<cTableIdentList>::CreateInstance(&m_pTableIdentList);
	m_pTableIdentList->AddRef();
	
	CComObject<cOrderByObjList>::CreateInstance(&m_pOrderByObjList);
	m_pOrderByObjList->AddRef();
	
	CComObject<cGenericStack>::CreateInstance(&m_pWhereExpressionStack);
	m_pWhereExpressionStack->AddRef();
	
	CComObject<cColumnIdentList>::CreateInstance(&m_pGroupByList);
	m_pGroupByList->AddRef();
	
	CComObject<cGenericStackList>::CreateInstance(&m_pSelectExpressionStackList);
	m_pSelectExpressionStackList->AddRef();
	
	CComObject<cGenericStack>::CreateInstance(&m_pHavingExpressionStack);
	m_pHavingExpressionStack->AddRef();
}

cSelectStmt::~cSelectStmt()
{
	Clear();
}

void cSelectStmt::Clear()
{
	try
	{
		RELEASE(m_pSelectExpressionStackList);
		RELEASE(m_pTableIdentList);
		RELEASE(m_pOrderByObjList);
		RELEASE(m_pWhereExpressionStack);
		RELEASE(m_pGroupByList);
		RELEASE(m_pHavingExpressionStack);
	}
	catch (_com_error &e)
	{
		MessageBox(NULL, e.ErrorMessage(), e.Source(), MB_OK);
	}
}	

STDMETHODIMP cSelectStmt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISelectStmt
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

void cSelectStmt::InitializeFromParseTree(CParseTree *pTree)
{
	CSQLNode *pSelectClause = pTree->GetObjectNameForName("SelectClause");
	if (!cAtlObjectConverter::NodeToExpressionStackList(pSelectClause, m_pSelectExpressionStackList))
		return;
	
	CSQLNode *pDistinct = pTree->GetObjectNameForName("Distinct");
	if (pDistinct) {
		_ASSERTE(pDistinct->m_NodeType == NodeType_Distinct);
		m_fDistinct = true;
	}
	else
		m_fDistinct = false;

	CSQLNode *pTopRows = pTree->GetObjectNameForName("TopRows");
	if (pTopRows) {
		m_uiTopRows = pTopRows->m_pLeftChild->m_pSQLToken->GetAsLong();
		m_fPercent = (pTopRows->m_NodeType == NodeType_TopRowsPercent) ? true : false;
	}
	else {
		m_uiTopRows = 0;
		m_fPercent = false;
	}

	CSQLNode *pTableIdent = pTree->GetObjectNameForName("FromClause");
	cAtlObjectConverter::NodeToTableIdentifierList(pTableIdent, m_pTableIdentList);
	
	CSQLNode *pWhereClause = pTree->GetObjectNameForName("WhereClause");
	cAtlObjectConverter::NodeToExpressionStack(pWhereClause, m_pWhereExpressionStack);
	
	CSQLNode *pGroupByClause = pTree->GetObjectNameForName("GroupByClause");
	cAtlObjectConverter::NodeToColumnIdentifierList(pGroupByClause, m_pGroupByList);
	
	CSQLNode *pHavingClause = pTree->GetObjectNameForName("HavingClause");
	cAtlObjectConverter::NodeToExpressionStack(pHavingClause, m_pHavingExpressionStack);
	
	CSQLNode *pOrderClause = pTree->GetObjectNameForName("OrderClause");
	cAtlObjectConverter::NodeToOrderByList(pOrderClause, m_pOrderByObjList);
}

STDMETHODIMP cSelectStmt::get_Distinct(VARIANT_BOOL *pVal)
{
	if (m_fDistinct == true)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP cSelectStmt::get_TopRowsPercent(VARIANT_BOOL *pVal)
{
	if (0 == m_uiTopRows)
		return E_UNEXPECTED;

	if (m_fPercent == true)
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP cSelectStmt::get_TopRows(ULONG *pVal)
{
	*pVal = m_uiTopRows;
	return S_OK;
}

STDMETHODIMP cSelectStmt::get_TableIdentList(ITableIdentList **pVal)
{
	*pVal = m_pTableIdentList;
	(*pVal)->AddRef();
	return S_OK;
}


// DEL STDMETHODIMP cSelectStmt::get_ColumnIdentList(IColumnIdentList **pVal)
// DEL {
// DEL 	// TODO: Add your implementation code here
// DEL 	if ( m_pColumnIdentList != NULL )
// DEL 		;
// DEL 	else
// DEL 		{
// DEL 		CComObject<cColumnIdentList>::CreateInstance( &m_pColumnIdentList );
// DEL 		m_pColumnIdentList->Initialize( m_pStatement->GetColumnIdentifierList() );
// DEL 		m_pColumnIdentList->AddRef();
// DEL 		}
// DEL //	m_pTableIdentList->QueryInterface( pVal );
// DEL 	*pVal = m_pColumnIdentList;
// DEL 	(*pVal)->AddRef();
// DEL 	return S_OK;
// DEL }

STDMETHODIMP cSelectStmt::get_OrderByObjList(IOrderByObjList **pVal)
{
	*pVal = m_pOrderByObjList;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cSelectStmt::get_WhereExpressionStack(IGenericStack **pVal)
{
	*pVal = m_pWhereExpressionStack;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cSelectStmt::get_SelectExpressionList(IGenericStackList **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pSelectExpressionStackList;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cSelectStmt::get_HavingExpressionStack(IGenericStack **pVal)
{
	*pVal = m_pHavingExpressionStack;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cSelectStmt::get_GroupByObjList(IColumnIdentList **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pGroupByList;
	(*pVal)->AddRef();
	return S_OK;
}
