/*  Product: Small Parser

  Copyright (C) 1999  Systementor AB, Stefan Holmberg
  Email - stefan.holmberg@systementor.se
  Web:   - http://www.systementor.se
  
	///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: ColumnIdent.cpp $ 
* 
* *****************  Version 2  *****************
* User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
* Updated in $/Products/SmallParser
*/

// ColumnIdent.cpp : Implementation of cColumnIdent
#include "stdafx.h"
#include "ColumnIdent.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cColumnIdent

cColumnIdent::cColumnIdent()
{
}


STDMETHODIMP cColumnIdent::get_AsString( BSTR *bstrRet )
{
	CString strName;
	
	if ( m_strTableName.GetLength() )
		strName = m_strTableName + "." ;
	
	strName += m_strColumnName;
	
	CComBSTR bstrRet2 = strName;
	*bstrRet = bstrRet2.Detach();
	
	return S_OK;
}

STDMETHODIMP cColumnIdent::get_ItemType(EXPRESSIONITEM_TYPE *pVal)
{
	*pVal = EXPRESSIONITEM_TYPE_COLUMNIDENT;
	return S_OK;
}



STDMETHODIMP cColumnIdent::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IColumnIdent
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cColumnIdent::get_TableName(BSTR *pVal)
{
	CComBSTR bstrName = m_strTableName;
	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP cColumnIdent::get_ColumnName(BSTR *pVal)
{
	CComBSTR bstrName = m_strColumnName;
	*pVal = bstrName.Detach();
	return S_OK;
}



CString cColumnIdent::GetTableName()
{
	return m_strTableName;
}

CString cColumnIdent::GetColumnName()
{
	return m_strColumnName;
}


void cColumnIdent::SetTableName( const TCHAR *str1 )
{
	m_strTableName = str1;
}


void cColumnIdent::SetColumnName( const TCHAR *str1 )
{
	m_strColumnName = str1;
}


void cColumnIdent::SetName( const TCHAR *szName )
{
	CString strTemp = szName;
	int nIndex = strTemp.Find( "." );
	if ( nIndex >= 0 )
	{
		SetTableName( strTemp.Left( nIndex ) );
		SetColumnName( strTemp.Mid( nIndex+1) );
	}
	else
	{
		SetTableName("");
		SetColumnName( szName );
	}
}

