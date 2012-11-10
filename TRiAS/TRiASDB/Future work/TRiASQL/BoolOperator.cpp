/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: BoolOperator.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:45p
 * Updated in $/Products/SmallParser
 * Added BoolOperator property
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// BoolOperator.cpp : Implementation of cBoolOperator
#include "stdafx.h"
#include "TRiASQL.h"
#include "BoolOperator.h"


#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// cBoolOperator


cBoolOperator::cBoolOperator()
{
}

CString cBoolOperator::GetAsString() 
{ 
	switch( m_BoolOperator )
		{
		case BOOL_OPERATOR_AND:
			return "AND";
		case BOOL_OPERATOR_OR:
			return "OR";
		}
	ASSERT(FALSE);
	return "!!!ERROR!!!"; 
};


void cBoolOperator::SetBoolOperator( BOOL_OPERATOR BoolOperator )
{
	m_BoolOperator = BoolOperator;
}

STDMETHODIMP cBoolOperator::get_AsString( BSTR *bstrRet )
{
	CComBSTR bstrRet2 = GetAsString();
	*bstrRet = bstrRet2.Detach();
	return S_OK;
}

STDMETHODIMP cBoolOperator::get_ItemType(EXPRESSIONITEM_TYPE *pVal)
{
	*pVal = EXPRESSIONITEM_TYPE_BOOLOPERATOR;
	return S_OK;
}




STDMETHODIMP cBoolOperator::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBoolOperator
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cBoolOperator::get_BoolOperator(BOOL_OPERATOR *pVal)
{
	*pVal = m_BoolOperator;
	return S_OK;
}
