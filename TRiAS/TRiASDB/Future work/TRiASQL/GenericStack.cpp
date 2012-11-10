/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: GenericStack.cpp $ 
 * 
 * *****************  Version 5  *****************
 * User: Stefan Holmberg Date: 7/14/99    Time: 3:18p
 * Updated in $/Products/SmallParser
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:34p
 * Updated in $/Products/SmallParser
 * Added AsName property
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

// GenericStack.cpp : Implementation of cGenericStack
#include "stdafx.h"
#include "TRiASQL.h"
#include "GenericStack.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cGenericStack

cGenericStack::cGenericStack()
{
}

void cGenericStack::AddItem( CComVariant v )
{
	m_coll.push_back(v);
}

void cGenericStack::SetAsName( const TCHAR *szName )
{
	m_strAsName = szName;
}

CString cGenericStack::GetAsName()
{
	return m_strAsName;
}


STDMETHODIMP cGenericStack::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGenericStack
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cGenericStack::Push(VARIANT vObject)
{
	// TODO: Add your implementation code here
	AddItem(vObject);
	return S_OK;
}

STDMETHODIMP cGenericStack::Pop(VARIANT *pvObj)
{
	// TODO: Add your implementation code here
	//From beginning
	int nSize = m_coll.size();
	
	if ( nSize == 0 )
		{
		return Error("Stack is empty");
		}
	

	CComVariant v = m_coll[0];
	v.pdispVal->AddRef();
	m_coll.erase(m_coll.begin(), m_coll.begin()+1);

	nSize = m_coll.size();

	*pvObj = v;
	return S_OK;
}

STDMETHODIMP cGenericStack::Peek(VARIANT *pvObj)
{
	int nSize = m_coll.size();
	
	if ( nSize == 0 )
		{
		return Error("Stack is empty");
		}
	
	CComVariant v = m_coll[0];
	v.pdispVal->AddRef();
	*pvObj = v;
	return S_OK;
}


STDMETHODIMP cGenericStack::get_AsName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	CComBSTR bstrRet2 = GetAsName();
	*pVal = bstrRet2.Detach();
	return S_OK;
}
