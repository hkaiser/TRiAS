/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: InsertStmt.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 8:47p
 * Updated in $/Products/SmallParser
 * Fixing headers so all code is in CPP-files
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// InsertStmt.cpp : Implementation of cInsertStmt
#include "stdafx.h"
#include "InsertStmt.h"
#include "cAtlObjectConverter.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cInsertStmt

cInsertStmt::cInsertStmt()
{
	CComObject<cTableIdent>::CreateInstance( &m_pTableIdent );
	m_pTableIdent->AddRef();

	CComObject<cColumnIdentList>::CreateInstance( &m_pColumnIdentList );
	m_pColumnIdentList->AddRef();

	CComObject<cGenericStackList>::CreateInstance( &m_pInsertExpressionStackList );
	m_pInsertExpressionStackList->AddRef();
}

cInsertStmt::~cInsertStmt()
{
	Clear();
}

void cInsertStmt::Clear()
{
	RELEASE(m_pTableIdent);
	RELEASE(m_pColumnIdentList );
	RELEASE(m_pInsertExpressionStackList);
}	




STDMETHODIMP cInsertStmt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IInsertStmt
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cInsertStmt::get_TableIdent(ITableIdent **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pTableIdent;
	(*pVal)->AddRef();
	return S_OK;
}


void cInsertStmt::InitializeFromParseTree( CParseTree *pTree )
{
	CSQLNode *pColInsList = pTree->GetObjectNameForName( "InsertColSpec" );
	if ( cAtlObjectConverter::NodeToColumnIdentifierList( pColInsList, m_pColumnIdentList ) == false )
		return;

	CSQLNode *pTableIdent = pTree->GetObjectNameForName( "NameIdent" );
	if ( cAtlObjectConverter::NodeToTableIdentifier( pTableIdent, m_pTableIdent ) == false )
		return;

	CSQLNode *pInserts = pTree->GetObjectNameForName("InsertValueList");
	if ( cAtlObjectConverter::NodeToExpressionStackList( pInserts, m_pInsertExpressionStackList ) == false )
		return;
}


STDMETHODIMP cInsertStmt::get_ColumnIdentList(IColumnIdentList **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pColumnIdentList;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cInsertStmt::get_InsertExpressionList(IGenericStackList **pVal)
{
	*pVal = m_pInsertExpressionStackList;
	(*pVal)->AddRef();
	return S_OK;
}
