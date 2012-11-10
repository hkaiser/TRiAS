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
#include "TRiASQL.h"
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
}

void cTableIdent::SetName( CString strName )
{
	m_strName = strName;
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
	// TODO: Add your implementation code here
	CComBSTR bstrName = m_strName;

	*pVal = bstrName.Detach();
	return S_OK;
}
