/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: TableIdent.cpp $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// TableIdent.cpp : Implementation of cTableIdent
#include "stdafx.h"
#include "TableIdent.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cTableIdent

cTableIdent::cTableIdent()
{
}

cTableIdent::~cTableIdent()
{
	m_strName.Empty();
	m_strAlias.Empty();
}

void cTableIdent::SetName( CString strName )
{
	m_strName = strName;
}

void cTableIdent::SetAlias(CString strAlias)
{
	m_strAlias = strAlias;
}

STDMETHODIMP cTableIdent::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITableIdent
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cTableIdent::get_Name(BSTR *pVal)
{
CComBSTR bstrName (m_strName);

	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP cTableIdent::get_Alias(BSTR *pVal)
{
	_ASSERTE(NULL != pVal);

	if (m_strAlias.GetLength() > 0) {
	CComBSTR bstrAlias (m_strAlias);

		*pVal = bstrAlias.Detach();
		return S_OK;
	}
	
	*pVal = NULL;
	return S_FALSE;
}
