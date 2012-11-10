/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: UpdateStmt.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:18p
 * Updated in $/Products/SmallParser
 * Added WhereExpressionStack property
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// UpdateStmt.cpp : Implementation of cUpdateStmt
#include "stdafx.h"
#include "UpdateStmt.h"
#include "cAtlObjectConverter.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cUpdateStmt


cUpdateStmt::cUpdateStmt()
{
	CComObject<cTableIdent>::CreateInstance( &m_pTableIdent );
	m_pTableIdent->AddRef();

	CComObject<cUpdateItemList>::CreateInstance( &m_pUpdateItemList );
	m_pUpdateItemList->AddRef();

	CComObject<cGenericStack>::CreateInstance( &m_pWhereExpressionStack );
	m_pWhereExpressionStack->AddRef();
}

cUpdateStmt::~cUpdateStmt()
{
	Clear();
}

void cUpdateStmt::Clear()
{
	RELEASE( m_pTableIdent );
	RELEASE( m_pUpdateItemList );
	RELEASE( m_pWhereExpressionStack );
}



STDMETHODIMP cUpdateStmt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUpdateStmt
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cUpdateStmt::get_TableIdent(ITableIdent **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pTableIdent;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cUpdateStmt::get_UpdateItemList(IUpdateItemList **pVal)
{
	*pVal = m_pUpdateItemList;
	(*pVal)->AddRef();
	return S_OK;
}



void cUpdateStmt::InitializeFromParseTree( CParseTree *pTree )
{

	CSQLNode *pTableIdent = pTree->GetObjectNameForName( "NameIdent" );
	if ( cAtlObjectConverter::NodeToTableIdentifier( pTableIdent, m_pTableIdent ) == false )
		return;

	CSQLNode *pUpdateList = pTree->GetObjectNameForName( "UpdateList" );
	if ( cAtlObjectConverter::NodeToUpdateItemList( pUpdateList, m_pUpdateItemList ) == false )
		return;

	CSQLNode *pWhereClause = pTree->GetObjectNameForName( "WhereClause" );
	if ( cAtlObjectConverter::NodeToExpressionStack( pWhereClause, m_pWhereExpressionStack ) == false )
		return;
}


STDMETHODIMP cUpdateStmt::get_WhereExpressionStack(IGenericStack **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pWhereExpressionStack;
	(*pVal)->AddRef();
	return S_OK;

	return S_OK;
}
