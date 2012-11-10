/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: DateFunction.cpp $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:36p
 * Updated in $/Products/SmallParser
 * Added GetDateFunction property
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

// DateFunction.cpp : Implementation of cDateFunction
#include "stdafx.h"
#include "TRiASQL.h"
#include "DateFunction.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cDateFunction

cDateFunction::cDateFunction()
{
}

CString cDateFunction::GetAsString() 
{ 
	switch( m_DateFunction )
		{
		case DATE_FUNCTION_GETDATE:
			return "GETDATE";
		}

	ASSERT(FALSE);
	return "!!!ERROR!!!"; 
};

void cDateFunction::SetDateFunction( DATE_FUNCTION DateFunction )
{
	m_DateFunction = DateFunction;
}

DATE_FUNCTION cDateFunction::GetDateFunction()
{
	return m_DateFunction;
}


STDMETHODIMP cDateFunction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDateFunction
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cDateFunction::get_DateFunction(DATE_FUNCTION *pVal)
{
	// TODO: Add your implementation code here
	*pVal = GetDateFunction();
	return S_OK;
}
