/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: ColumnIdentList.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 8:47p
 * Updated in $/Products/TRiASQL
 * Fixing headers so all code is in CPP-files
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 11:47a
 * Updated in $/Products/TRiASQL
*/

// ColumnIdentList.cpp : Implementation of cColumnIdentList
#include "stdafx.h"
#include "ColumnIdentList.h"
#include "ColumnIdent.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cColumnIdentList

cColumnIdentList::cColumnIdentList()
{
}

void cColumnIdentList::AddItem( cColumnIdent *pIdent )
{
	CComVariant v = pIdent;
	m_coll.push_back(v);
}


STDMETHODIMP cColumnIdentList::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IColumnIdentList
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


