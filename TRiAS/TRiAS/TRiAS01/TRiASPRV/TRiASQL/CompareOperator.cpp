/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: CompareOperator.cpp $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:38p
 * Updated in $/Products/SmallParser
 * Added CompareOperator property
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

// CompareOperator.cpp : Implementation of cCompareOperator
#include "stdafx.h"
#include "CompareOperator.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cCompareOperator


cCompareOperator::cCompareOperator()
{
}

CString cCompareOperator::GetAsString() 
{ 
	switch( m_CompareOperator )
	{
	case COMPARE_OPERATOR_EQUALS:
		return "=";
	case COMPARE_OPERATOR_NOT_EQUALS:
		return "<>";
	case COMPARE_OPERATOR_MORE:
		return ">";
	case COMPARE_OPERATOR_LESS:
		return "<";
	case COMPARE_OPERATOR_MOREEQUALS:
		return ">=";
	case COMPARE_OPERATOR_LESSEQUALS:
		return "<=";
	case COMPARE_OPERATOR_IS:
		return " is ";
	case COMPARE_OPERATOR_ISNOT:
		return " is not ";
	case COMPARE_OPERATOR_NOT:
		return "not";
	case COMPARE_OPERATOR_LIKE:
		return "like";
	}

	_ASSERTE(FALSE);
	return "!!!ERROR!!!"; 
};


void cCompareOperator::SetCompareOperator( COMPARE_OPERATOR CompareOperator )
{
	m_CompareOperator = CompareOperator;
}




STDMETHODIMP cCompareOperator::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICompareOperator
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cCompareOperator::get_CompareOperator(COMPARE_OPERATOR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_CompareOperator;
	return S_OK;
}
