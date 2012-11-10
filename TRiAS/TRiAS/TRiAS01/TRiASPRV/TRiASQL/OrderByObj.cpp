/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: OrderByObj.cpp $ 
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

// OrderByObj.cpp : Implementation of cOrderByObj
#include "stdafx.h"
#include "OrderByObj.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cOrderByObj

cOrderByObj::cOrderByObj()
{
	CComObject<cColumnIdent>::CreateInstance( &m_pColumnIdent );
	m_pColumnIdent->AddRef();
}

cOrderByObj::~cOrderByObj()
{
	Clear();
}

void cOrderByObj::Clear()
{
	if ( m_pColumnIdent )
		m_pColumnIdent->Release();
	m_pColumnIdent = NULL;
}

void cOrderByObj::SetAsc( bool fAsc )
{
	m_fAsc = fAsc;
}

STDMETHODIMP cOrderByObj::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IOrderByObj
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cOrderByObj::get_Asc(VARIANT_BOOL *pVal)
{
	if ( m_fAsc )
		*pVal = VARIANT_TRUE;
	else
		*pVal = VARIANT_FALSE;		
	return S_OK;
}

STDMETHODIMP cOrderByObj::get_ColumnIdent(IColumnIdent **pVal)
{
	*pVal = m_pColumnIdent;
	(*pVal)->AddRef();

	return S_OK;
}
