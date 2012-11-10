/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: SelectStarExpression.cpp $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// SelectStarExpression.cpp : Implementation of cSelectStarExpression
#include "stdafx.h"
#include "SelectStarExpression.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cSelectStarExpression

cSelectStarExpression::cSelectStarExpression()
{
}

CString cSelectStarExpression::GetAsString() 
{ 
	return "*"; 
};


STDMETHODIMP cSelectStarExpression::get_AsString( BSTR *bstrRet )
{
	CComBSTR bstrRet2 = GetAsString();
	*bstrRet = bstrRet2.Detach();
	return S_OK;
}

STDMETHODIMP cSelectStarExpression::get_ItemType(EXPRESSIONITEM_TYPE *pVal)
{
	*pVal = EXPRESSIONITEM_TYPE_SELECTSTAR;
	return S_OK;
}



STDMETHODIMP cSelectStarExpression::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISelectStarExpression
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
