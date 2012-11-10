/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: CreateTableStmt.cpp $ 
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

// CreateTableStmt.cpp : Implementation of cCreateTableStmt
#include "stdafx.h"
#include "TRiASQL.h"
#include "CreateTableStmt.h"
#include "cAtlObjectConverter.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cCreateTableStmt

cCreateTableStmt::cCreateTableStmt()
{
	CComObject<cTableIdent>::CreateInstance( &m_pTableIdent );
	m_pTableIdent->AddRef();

	CComObject<cCreateTableItemList>::CreateInstance( &m_pCreateTableItemList );
	m_pCreateTableItemList->AddRef();
}

cCreateTableStmt::~cCreateTableStmt()
{
	Clear();
}

void cCreateTableStmt::Clear()
{
	RELEASE( m_pTableIdent );
	RELEASE( m_pCreateTableItemList );
}	



STDMETHODIMP cCreateTableStmt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICreateTableStmt
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void cCreateTableStmt::InitializeFromParseTree( CParseTree *pTree )
{
	CSQLNode *pTableIdent = pTree->GetObjectNameForName( "NameIdent" );
	if ( cAtlObjectConverter::NodeToTableIdentifier( pTableIdent, m_pTableIdent ) == false )
		return;

	CSQLNode *pCreateTableList = pTree->GetObjectNameForName( "ColDataTypeList" );
	if ( cAtlObjectConverter::NodeToCreateTableItemList( pCreateTableList, m_pCreateTableItemList ) == false )
		return;
}

STDMETHODIMP cCreateTableStmt::get_TableIdent(ITableIdent **pVal)
{
	*pVal = m_pTableIdent;
	(*pVal)->AddRef();
	return S_OK;
}


STDMETHODIMP cCreateTableStmt::get_CreateTableItemList(ICreateTableItemList **pVal)
{
	*pVal = m_pCreateTableItemList;
	(*pVal)->AddRef();
	return S_OK;
}
