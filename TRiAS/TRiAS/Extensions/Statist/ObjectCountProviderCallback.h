// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.12.2002 20:15:58 
//
// @doc
// @module ObjectCountProviderCallback.h | Declaration of the <c CObjectCountProviderCallback> class

#if !defined(_OBJECTCOUNTPROVIDERCALLBACK_H__8EEF24F7_AABE_42E5_8380_439FB721444D__INCLUDED_)
#define _OBJECTCOUNTPROVIDERCALLBACK_H__8EEF24F7_AABE_42E5_8380_439FB721444D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CObjectClassStatistics;

///////////////////////////////////////////////////////////////////////////////
// 
class CObjectCountInClassProviderCallback :
	public CObjectClassStatistics::CValueProviderCallbackClass
{
public:
	CObjectCountInClassProviderCallback(CObjectClassStatistics *pTarget, 
			HOBJECTS lIdent, IValueProvider *pIProvider, HTREEITEM hItem) :
		CObjectClassStatistics::CValueProviderCallbackClass(pTarget, lIdent, pIProvider, hItem)
	{
	}
	~CObjectCountInClassProviderCallback()
	{
	}

	BOOL PopulateItem (CObjectClassStatistics *pTarget, HTREEITEM hParent);
};

///////////////////////////////////////////////////////////////////////////////
// 
class CObjectCountInDatasourceProviderCallback :
	public CObjectClassStatistics::CValueProviderCallbackDatasource
{
public:
	CObjectCountInDatasourceProviderCallback(CObjectClassStatistics *pTarget, 
			HPROJECT hPr, IValueProvider *pIProvider, HTREEITEM hItem) :
		CObjectClassStatistics::CValueProviderCallbackDatasource(pTarget, hPr, pIProvider, hItem)
	{
	}
	~CObjectCountInDatasourceProviderCallback()
	{
	}

	BOOL PopulateItem (CObjectClassStatistics *pTarget, HTREEITEM hParent);

protected:
	short GetObjectTypes();
	BOOL CALLBACK EnumClasses(INT_PTR lIdent, BOOL, void *pData);
};

#endif // !defined(_OBJECTCOUNTPROVIDERCALLBACK_H__8EEF24F7_AABE_42E5_8380_439FB721444D__INCLUDED_)
