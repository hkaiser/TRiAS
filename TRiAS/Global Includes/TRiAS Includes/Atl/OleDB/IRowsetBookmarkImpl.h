// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 17.07.2001 10:51:31 
//
// @doc
// @module IRowsetBookmarkImpl.h | Declaration of the <c CIRowsetBookmarkImpl> class

#if !defined(_IROWSETBOOKMARKIMPL_H__1997E303_B93A_465B_91DA_93CE30D85FE9__INCLUDED_)
#define _IROWSETBOOKMARKIMPL_H__1997E303_B93A_465B_91DA_93CE30D85FE9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// IRowsetBookmark: setzt vorraus, daﬂ Klasse ebenfalls von IRowsetLocateImpl
// abgeleitet ist
template<typename T>
class ATL_NO_VTABLE IRowsetBookmarkImpl :
	public IRowsetBookmark
{
public:
	STDMETHODIMP PositionOnBookmark(HCHAPTER hChapter, DBBKMARK cbBookmark, const BYTE *pBookmark)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IRowsetBookmarkImpl::PositionOnBookmark\n");
		if (0 == cbBookmark || NULL == pBookmark)
			return E_INVALIDARG;

		if (DB_NULL_HCHAPTER != hChapter)
			return DB_E_NOTSUPPORTED;

	T *pT = static_cast<T *>(this);
	HRESULT hr = pT->ValidateBookmark(cbBookmark, pBookmark);

		if (hr != S_OK) return hr;

	DBROWOFFSET ulRow = pT->GetRowHandleFromBookmark (cbBookmark, pBookmark);

		if (0 == ulRow) 
			return DB_E_BADBOOKMARK;	// Row not found

	T::ObjectLock cab(pT);

		pT->m_iRowset = ulRow;
		return S_OK;
	}
};

#endif // !defined(_IROWSETBOOKMARKIMPL_H__1997E303_B93A_465B_91DA_93CE30D85FE9__INCLUDED_)
