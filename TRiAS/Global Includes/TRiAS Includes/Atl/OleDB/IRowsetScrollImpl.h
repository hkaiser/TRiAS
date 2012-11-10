// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 20:48:54 
//
// @doc
// @module IRowsetScrollImpl.h | Declaration of the <c IRowsetScrollImpl> class

#if !defined(_IROWSETSCROLLIMPL_H__6C92C8F1_C826_43B3_B91D_0403BCF9E729__INCLUDED_)
#define _IROWSETSCROLLIMPL_H__6C92C8F1_C826_43B3_B91D_0403BCF9E729__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#include <Atl/OleDB/IRowsetLocateImpl.h>

///////////////////////////////////////////////////////////////////////////////
// class IRowsetScrollImpl
template <class T, class Base = IRowsetScroll>
class ATL_NO_VTABLE IRowsetScrollImpl : 
	public IRowsetLocateImpl<T, Base>
{
public:
	STDMETHOD(GetApproximatePosition)(
		HCHAPTER hChapter, DBBKMARK cbBookmark, const BYTE *pBookmark, 
		DBCOUNTITEM *pulPosition, DBCOUNTITEM *pcRows)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IRowsetScroll::GetApproximatePosition()\n");

	T *pT = (T *)this;

		if (hChapter != DB_NULL_HCHAPTER) {
			ATLTRACE2(atlTraceDBProvider, 0, "IRowsetScroll::GetApproximatePosition - (hChapter != DB_NULL_HCHAPTER)\n");
			return E_FAIL;
		}

		if (cbBookmark == 0) {
		// Ignore pBookmark
			if (pulPosition)
				*pulPosition = 0;

			if (pcRows)
				*pcRows = pT->GetNumRows();  
		}
		else {
			if (!pBookmark) {
				ATLTRACE2(atlTraceDBProvider, 0, "IRowsetScroll::GetApproximatePosition - (cbBookmark != 0 && !pBookmark)\n");
				return E_INVALIDARG;
			}

			if (pulPosition) {
				if (cbBookmark == 1) {
					if (*(DBBOOKMARK*)pBookmark == DBBMK_FIRST)
						*pulPosition = 1;
					else if (*(DBBOOKMARK*)pBookmark == DBBMK_LAST)
						*pulPosition = pT->GetNumRows();	
					else if (*(DBBOOKMARK*)pBookmark == DBBMK_INVALID)
						return DB_E_BADBOOKMARK;
				}
				else if (cbBookmark == sizeof(DWORD)) {
				// the bookmark is the row index...
				DWORD bookmark = *(DWORD *)pBookmark;

					if (bookmark < 1 || bookmark > pT->GetNumRows())
						return DB_E_BADBOOKMARK;
				
					*pulPosition = bookmark; 
				}
				else {
					ATLTRACE2(atlTraceDBProvider, 0, "IRowsetScroll::GetApproximatePosition - (cbBookmark != sizeof(DWORD))\n");
					return E_FAIL;
				}
			}

			if (pcRows)
				*pcRows = pT->GetNumRows();
		}

		return S_OK;
	}

	STDMETHOD(GetRowsAtRatio)(
		HWATCHREGION hReserved1, HCHAPTER hChapter, DBCOUNTITEM ulNumerator, DBCOUNTITEM ulDenominator,
		DBROWCOUNT cRows, DBCOUNTITEM *pcRowsObtained, HROW **prghRows)
	{
		ATLTRACE(_T("IRowsetScrollImpl::GetRowsAtRatio"));

	T *pT = (T*)this;

		if (pcRowsObtained == NULL || prghRows == NULL)
			return E_INVALIDARG;

		*pcRowsObtained = 0;
		*prghRows = NULL;

	// Make sure we have a valid ratio
		if ((ulNumerator > ulDenominator) || (ulDenominator == 0))
			return DB_E_BADRATIO;

	// Ensure we don't try to fetch rows backwards if the provider
	// doesn't support it
		if (cRows < 0 && !m_bCanFetchBack)
			return DB_E_CANTFETCHBACKWARDS;

	DBROWOFFSET iRowsetTemp = pT->m_iRowset;  // Cache the current rowset

		if (0 == ulNumerator) {
			if (cRows < 0) {
				pT->m_iRowset = iRowsetTemp;	// reset row position
				return DB_S_ENDOFROWSET;
			} else
				pT->m_iRowset = 0;
		}

		if (ulNumerator == ulDenominator)
		{
			if (cRows < 0)
				pT->m_iRowset = (DBROWOFFSET)pT->GetNumRows();
			else {
				pT->m_iRowset = iRowsetTemp;	// reset row position
				return DB_S_ENDOFROWSET;
			}
		}
			
		pT->m_iRowset = (DBROWCOUNT)(ulNumerator / ulDenominator);
	
	HRESULT hr = pT -> GetNextRows(hChapter, 0, cRows, pcRowsObtained, prghRows);

		pT->m_iRowset = iRowsetTemp;	// reset rowposition
		return hr;
	}
};

#endif // !defined(_IROWSETSCROLLIMPL_H__6C92C8F1_C826_43B3_B91D_0403BCF9E729__INCLUDED_)
