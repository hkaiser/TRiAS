/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: MathFunction.cpp $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:23p
 * Updated in $/Products/SmallParser
 * Added MathFunction property
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

// MathFunction.cpp : Implementation of cMathFunction
#include "stdafx.h"
#include "MathFunction.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cMathFunction


cMathFunction::cMathFunction()
{
}

CString cMathFunction::GetAsString() 
{ 
	switch( m_MathFunction )
	{
	case MATH_FUNCTION_ABS:
		return "ABS";
	}

	_ASSERTE(FALSE);
	return "!!!ERROR!!!"; 
};


void cMathFunction::SetMathFunction( MATH_FUNCTION MathFunction )
{
	m_MathFunction = MathFunction;
}


STDMETHODIMP cMathFunction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMathFunction
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cMathFunction::get_MathFunction(MATH_FUNCTION *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_MathFunction;
	return S_OK;
}
