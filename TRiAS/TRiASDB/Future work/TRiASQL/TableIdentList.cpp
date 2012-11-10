/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: TableIdentList.cpp $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// TableIdentList.cpp : Implementation of cTableIdentList
#include "stdafx.h"
#include "TRiASQL.h"
#include "TableIdentList.h"
#include "TableIdent.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cTableIdentList

cTableIdentList::cTableIdentList()
{
}

cTableIdentList::~cTableIdentList()
{
	m_coll.clear();
	for ( int i = 0; i < m_coll.size(); i++ )
		{
		CComVariant v = m_coll[i];
//		if ( v.vt == VT_DISPATCH )
//			 {
//				v.pdispVal->Release();
//			 }
		}
}

void cTableIdentList::AddItem( cTableIdent *pIdent )
{
	CComVariant v = pIdent;
	m_coll.push_back(v);
}



STDMETHODIMP cTableIdentList::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITableIdentList
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

