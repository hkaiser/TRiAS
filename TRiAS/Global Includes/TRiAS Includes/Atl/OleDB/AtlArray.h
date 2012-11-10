// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 15.07.2001 17:22:58 
//
// @doc
// @module AtlArray.h | Declaration of the <c CAtlArray> class

#if !defined(_ATLARRAY_H__5BD416D5_5649_4FCF_8C40_5C8E4BED9191__INCLUDED_)
#define _ATLARRAY_H__5BD416D5_5649_4FCF_8C40_5C8E4BED9191__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if _ATL_VER < 0x0700

///////////////////////////////////////////////////////////////////////////////
// CAtlArray
template<typename T>
class CAtlArray :
	public CSimpleArray<T>
{
public:
	int GetCount() { return CSimpleArray<T>::GetSize(); }
};

#endif // _ATL_VER < 0x0700

#endif // !defined(_ATLARRAY_H__5BD416D5_5649_4FCF_8C40_5C8E4BED9191__INCLUDED_)
