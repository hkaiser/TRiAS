/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: AritOperator.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:45p
 * Updated in $/Products/SmallParser
 * Added AritOperator property
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// AritOperator.cpp : Implementation of cAritOperator
#include "stdafx.h"
#include "TRiASQL.h"
#include "AritOperator.h"


#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// cAritOperator

cAritOperator::cAritOperator()
{
}

CString cAritOperator::GetAsString() 
{ 
	switch( m_AritOperator )
		{
		case ARIT_OPERATOR_PLUS:
			return "+";
		case ARIT_OPERATOR_MINUS:
			return "-";
		case ARIT_OPERATOR_DIVIDE:
			return "/";
		case ARIT_OPERATOR_MULTIPLY:
			return "*";
		}
	ASSERT(FALSE);
	return "!!!ERROR!!!"; 
};

void cAritOperator::SetAritOperator( ARIT_OPERATOR AritOperator )
{
	m_AritOperator = AritOperator;
}


STDMETHODIMP cAritOperator::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAritOperator
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP cAritOperator::get_AsString( BSTR *bstrRet )
{
	CComBSTR bstrRet2 = GetAsString();
	*bstrRet = bstrRet2.Detach();
	return S_OK;
}

STDMETHODIMP cAritOperator::get_ItemType(EXPRESSIONITEM_TYPE *pVal)
{
	*pVal = EXPRESSIONITEM_TYPE_ARITOPERATOR;
	return S_OK;
}

STDMETHODIMP cAritOperator::get_AritOperator(ARIT_OPERATOR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_AritOperator;
	return S_OK;
}
