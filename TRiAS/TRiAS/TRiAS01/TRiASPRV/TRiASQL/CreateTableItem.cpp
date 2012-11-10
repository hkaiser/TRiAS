/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: CreateTableItem.cpp $ 
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

// CreateTableItem.cpp : Implementation of cCreateTableItem
#include "stdafx.h"
#include "CreateTableItem.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cCreateTableItem

cCreateTableItem::cCreateTableItem()
{
}


STDMETHODIMP cCreateTableItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICreateTableItem
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cCreateTableItem::get_DataLength(short *pVal)
{
	*pVal = (short)m_nDataLength;
	return S_OK;
}

STDMETHODIMP cCreateTableItem::get_ColName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	CComBSTR bstrName = m_strColumnName;
	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP cCreateTableItem::get_DataType(PARSER_DATATYPE *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_DataType;
	return S_OK;
}
