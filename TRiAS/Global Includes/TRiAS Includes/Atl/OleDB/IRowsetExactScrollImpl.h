// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 20:55:19 
//
// @doc
// @module IRowsetExactScrollImpl.h | Declaration of the <c IRowsetExactScrollImpl> class

#if !defined(_IROWSETEXACTSCROLLIMPL_H__69BB653D_52BE_4EA9_B34D_603D007B98F5__INCLUDED_)
#define _IROWSETEXACTSCROLLIMPL_H__69BB653D_52BE_4EA9_B34D_603D007B98F5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDB/IRowsetScrollImpl.h>

///////////////////////////////////////////////////////////////////////////////
// forward declaration
template <class T, class Base>
class ATL_NO_VTABLE CRowsetExactScrollImpl;

///////////////////////////////////////////////////////////////////////////////
// class IRowsetExactScrollImpl
template <class T>
class ATL_NO_VTABLE IRowsetExactScrollImpl : 
	public CRowsetExactScrollImpl<T, IRowsetExactScroll>
{
};

///////////////////////////////////////////////////////////////////////////////
// helper class
template <class T, class Base>
class ATL_NO_VTABLE CRowsetExactScrollImpl : 
	public CRowsetScrollImpl<T, Base>
{
public:
	STDMETHOD(GetExactPosition)(
		HCHAPTER hChapter, ULONG cbBookmark, const BYTE *pBookmark, ULONG *pulPosition, ULONG *pcRows)
	{
	// Our GetApproximatePosition actually gives the exact position
		ATLTRACE2(atlTraceDBProvider, 0, "IRowsetExactScroll::GetExactPosition()\n");
		return GetApproximatePosition (hChapter, cbBookmark, pBookmark, pulPosition, pcRows);
	}
};

#endif // !defined(_IROWSETEXACTSCROLLIMPL_H__69BB653D_52BE_4EA9_B34D_603D007B98F5__INCLUDED_)
