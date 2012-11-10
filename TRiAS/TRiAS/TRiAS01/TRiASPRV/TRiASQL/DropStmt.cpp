/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: DropStmt.cpp $ 
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

// DropStmt.cpp : Implementation of cDropStmt
#include "stdafx.h"
#include "DropStmt.h"
#include "cAtlObjectConverter.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cDropStmt

cDropStmt::cDropStmt()
{
	CComObject<cTableIdent>::CreateInstance( &m_pTableIdent );
	m_pTableIdent->AddRef();
}

cDropStmt::~cDropStmt()
{
	Clear();
}

void cDropStmt::Clear()
{
	RELEASE( m_pTableIdent );
}	




STDMETHODIMP cDropStmt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDropStmt
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void cDropStmt::InitializeFromParseTree( CParseTree *pTree )
{
	CSQLNode *pTableIdent = pTree->GetObjectNameForName( "NameIdent" );
	if ( cAtlObjectConverter::NodeToTableIdentifier( pTableIdent, m_pTableIdent ) == false )
		return;
}


STDMETHODIMP cDropStmt::get_TableIdent(ITableIdent **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pTableIdent;
	(*pVal)->AddRef();
	return S_OK;
}
