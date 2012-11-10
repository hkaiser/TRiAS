/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: OrderByList.cpp $ 
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

// OrderByList.cpp : Implementation of cOrderByList
#include "stdafx.h"
#include "TRiASQL.h"
#include "OrderByList.h"
#include "OrderByObj.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cOrderByList

cOrderByObjList::cOrderByObjList()
{
}

void cOrderByObjList::AddItem( cOrderByObj *pIdent )
{
	CComVariant v = pIdent;
	m_coll.push_back(v);
}


STDMETHODIMP cOrderByObjList::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IOrderByObjList
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

