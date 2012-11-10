/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: UpdateItem.cpp $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// UpdateItem.cpp : Implementation of cUpdateItem
#include "stdafx.h"
#include "UpdateItem.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cUpdateItem



cUpdateItem::cUpdateItem()
{
	CComObject<cColumnIdent>::CreateInstance( &m_pColumnIdent );
	m_pColumnIdent->AddRef();

	CComObject<cGenericStack>::CreateInstance( &m_pExpressionStack );
	m_pExpressionStack->AddRef();
}

cUpdateItem::~cUpdateItem()
{
	Clear();
}

void cUpdateItem::Clear()
{
	RELEASE( m_pColumnIdent );
	RELEASE( m_pExpressionStack );
}


STDMETHODIMP cUpdateItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUpdateItem
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cUpdateItem::get_ColumnIdent(IColumnIdent **pVal)
{
	*pVal = m_pColumnIdent;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP cUpdateItem::get_ExpressionStack(IGenericStack **pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pExpressionStack;
	(*pVal)->AddRef();
	return S_OK;
}
