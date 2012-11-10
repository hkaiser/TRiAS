/*  Product: Small Parser

  Copyright (C) 1999  Systementor AB, Stefan Holmberg
  Email - stefan.holmberg@systementor.se
  Web:   - http://www.systementor.se
  
	///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: AggregateFunction.cpp $ 
* 
* *****************  Version 3  *****************
* User: Stefan Holmberg Date: 7/13/99    Time: 9:44p
* Updated in $/Products/SmallParser
* Added AggregateFunction property
* 
* *****************  Version 2  *****************
* User: Stefan Holmberg Date: 7/11/99    Time: 11:45a
* Updated in $/Products/SmallParser

*/

// AggregateFunction.cpp : Implementation of cAggregateFunction
#include "stdafx.h"
#include "AggregateFunction.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cAggregateFunction

cAggregateFunction::cAggregateFunction()
{
}

void cAggregateFunction::SetAggregateFunction( AGGREGATE_FUNCTION AggregateFunction )
{
	m_AggregateFunction = AggregateFunction;
}

CString cAggregateFunction::GetAsString() 
{ 
	switch( m_AggregateFunction )
	{
	case AGGREGATE_FUNCTION_SUM:
		return "SUM";
	case AGGREGATE_FUNCTION_COUNT:
		return "COUNT";
	case AGGREGATE_FUNCTION_MIN:
		return "MIN";
	case AGGREGATE_FUNCTION_MAX:
		return "MAX";
	case AGGREGATE_FUNCTION_AVG:
		return "AVG";
	}
	
	_ASSERTE(FALSE);
	return "!!!ERROR!!!"; 
};




STDMETHODIMP cAggregateFunction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAggregateFunction
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP cAggregateFunction::get_AsString( BSTR *bstrRet )
{
	_ASSERTE(NULL != bstrRet);
	CComBSTR bstrRet2 = GetAsString();
	*bstrRet = bstrRet2.Detach();
	return S_OK;
}

STDMETHODIMP cAggregateFunction::get_ItemType(EXPRESSIONITEM_TYPE *pVal)
{
	_ASSERTE( pVal );
	*pVal = EXPRESSIONITEM_TYPE_AGGREGATEFUNCTION;
	return S_OK;
}

STDMETHODIMP cAggregateFunction::get_AggregateFunction(AGGREGATE_FUNCTION *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_AggregateFunction;
	return S_OK;
}
