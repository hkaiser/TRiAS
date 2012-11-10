/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: UpdateItemList.cpp $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// UpdateItemList.cpp : Implementation of cUpdateItemList
#include "stdafx.h"
#include "UpdateItemList.h"
#include "UpdateItem.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cUpdateItemList


cUpdateItemList::cUpdateItemList()
{
}

cUpdateItemList::~cUpdateItemList()
{
}

void cUpdateItemList::AddItem( cUpdateItem *pIdent )
{
	CComVariant v = pIdent;
	m_coll.push_back(v);
}



STDMETHODIMP cUpdateItemList::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUpdateItemList
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}






