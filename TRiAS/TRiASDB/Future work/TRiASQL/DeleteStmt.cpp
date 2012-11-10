/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: DeleteStmt.cpp $ 
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

// DeleteStmt.cpp : Implementation of cDeleteStmt
#include "stdafx.h"
#include "TRiASQL.h"
#include "DeleteStmt.h"
#include "cAtlObjectConverter.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cDeleteStmt

cDeleteStmt::cDeleteStmt()
{
	CComObject<cTableIdent>::CreateInstance( &m_pTableIdent );
	m_pTableIdent->AddRef();

	CComObject<cGenericStack>::CreateInstance( &m_pWhereExpressionStack );
	m_pWhereExpressionStack->AddRef();
}

cDeleteStmt::~cDeleteStmt()
{
	Clear();
}

void cDeleteStmt::Clear()
{
	RELEASE( m_pTableIdent );
}	


STDMETHODIMP cDeleteStmt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDeleteStmt
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



void cDeleteStmt::InitializeFromParseTree( CParseTree *pTree )
{
	CSQLNode *pTableIdent = pTree->GetObjectNameForName( "NameIdent" );
	if ( cAtlObjectConverter::NodeToTableIdentifier( pTableIdent, m_pTableIdent ) == false )
		return;

	CSQLNode *pWhereClause = pTree->GetObjectNameForName( "WhereClause" );
	if ( cAtlObjectConverter::NodeToExpressionStack( pWhereClause, m_pWhereExpressionStack ) == false )
		return;
}


STDMETHODIMP cDeleteStmt::get_TableIdent(ITableIdent **pVal)
{
	*pVal = m_pTableIdent;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cDeleteStmt::get_WhereExpressionStack(IGenericStack **pVal)
{
	*pVal = m_pWhereExpressionStack;
	(*pVal)->AddRef();
	return S_OK;
}
