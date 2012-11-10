// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.12.2002 20:15:58 
//
// @doc
// @module ObjectCountORWndProviderCallback.h | Declaration of the <c CObjectCountProviderCallback> class

#if !defined(_OBJECTCOUNTORWNDPROVIDERCALLBACK_H__8EEF24F7_AABE_42E5_8380_439FB721444D__INCLUDED_)
#define _OBJECTCOUNTORWNDPROVIDERCALLBACK_H__8EEF24F7_AABE_42E5_8380_439FB721444D__INCLUDED_

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
class CObjectCountInORWndClassProviderCallback :
	public CORWndStatistics::CValueProviderCallbackORWndClass
{
public:
	CObjectCountInORWndClassProviderCallback(CORWndStatistics *pTarget, 
			HWND hWnd, HOBJECTS lIdent, IValueProvider *pIProvider, 
            HTREEITEM hItem) 
	:	CORWndStatistics::CValueProviderCallbackORWndClass(pTarget, hWnd, lIdent, pIProvider, hItem)
	{
	}
	~CObjectCountInORWndClassProviderCallback()
	{
	}

	BOOL PopulateItem (CORWndStatistics *pTarget, HTREEITEM hParent);

protected:
	short GetObjectTypes();
	BOOL CALLBACK EnumClasses(INT_PTR lIdent, DWORD dwTypes, void *pData);
};

///////////////////////////////////////////////////////////////////////////////
// 
class CObjectCountInORWndProviderCallback :
	public CORWndStatistics::CValueProviderCallbackORWnd
{
public:
	CObjectCountInORWndProviderCallback(CORWndStatistics *pTarget, 
			HWND hWnd, IValueProvider *pIProvider, HTREEITEM hItem) :
		CORWndStatistics::CValueProviderCallbackORWnd(pTarget, hWnd, pIProvider, hItem)
	{
	}
	~CObjectCountInORWndProviderCallback()
	{
	}

	BOOL PopulateItem (CORWndStatistics *pTarget, HTREEITEM hParent);

protected:
	short GetObjectTypes();
	BOOL CALLBACK EnumClasses(INT_PTR lIdent, DWORD dwTypes, void *pData);
};

#endif // !defined(_OBJECTCOUNTORWNDPROVIDERCALLBACK_H__8EEF24F7_AABE_42E5_8380_439FB721444D__INCLUDED_)
