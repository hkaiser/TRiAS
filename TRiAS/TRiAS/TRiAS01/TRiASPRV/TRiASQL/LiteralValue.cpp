/*  Product: Small Parser

  Copyright(C) 1999  Systementor AB, Stefan Holmberg
  Email - stefan.holmberg@systementor.se
  Web:   - http:// www.systementor.se
  
	///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: LiteralValue.cpp $ 
* 
* *****************  Version 4  *****************
* User: Stefan Holmberg Date: 7/13/99    Time: 9:31p
* Updated in $/Products/SmallParser
* Added DataType property
* 
* *****************  Version 3  *****************
* User: Stefan Holmberg Date: 7/13/99    Time: 8:47p
* Updated in $/Products/SmallParser
* Fixing headers so all code is in CPP - files
* 
* *****************  Version 2  *****************
* User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
* Updated in $/Products/SmallParser
*/

// LiteralValue.cpp : Implementation of cLiteralValue
#include "stdafx.h"
#include "LiteralValue.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cLiteralValue

cLiteralValue::cLiteralValue()
{
}

CString cLiteralValue::GetAsString() 
{ 
	return m_strData;
}

void cLiteralValue::SetDataType(PARSER_DATATYPE DataType)
{
	m_DataType = DataType;
}

void cLiteralValue::SetData(const TCHAR *szText)
{
	m_strData = szText;
}

CString cLiteralValue::GetData()
{
	return m_strData;
}

PARSER_DATATYPE cLiteralValue::GetDataType()
{
	return m_DataType;
}

STDMETHODIMP cLiteralValue::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiteralValue
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cLiteralValue::get_DataType(PARSER_DATATYPE *pVal)
{
	*pVal = GetDataType();
	return S_OK;
}
