// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 20:35:21 
//
// @doc
// @module IRowsetLocateImpl.h | Declaration of the <c IRowsetLocateImpl> class

#if !defined(_IROWSETLOCATEIMPL_H__78092BC2_182B_46A4_85DA_69C3A48FB066__INCLUDED_)
#define _IROWSETLOCATEIMPL_H__78092BC2_182B_46A4_85DA_69C3A48FB066__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

// required for _ATL_VER < 0x0700 only
#if _ATL_VER < 0x0700

///////////////////////////////////////////////////////////////////////////////
// helper class
template<class T, class Base, class RowClass = CSimpleRow, class MapClass = CSimpleMap<RowClass::KeyType, RowClass *> >
class ATL_NO_VTABLE IRowsetLocateImpl : 
	public IRowsetImpl<T, Base, RowClass, MapClass>
{
public:
	STDMETHOD(Compare)(HCHAPTER hReserved, DBBKMARK cbBookmark1,
		const BYTE *pBookmark1, DBBKMARK cbBookmark2, const BYTE *pBookmark2,
		DBCOMPARE *pComparison)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IRowsetLocateImpl::Compare\n");

	// Validate input parameters
		if (pComparison == NULL)
			return E_INVALIDARG;

	HRESULT hr = ValidateBookmark(cbBookmark1, pBookmark1);

		if (hr != S_OK) return hr;

		hr = ValidateBookmark(cbBookmark2, pBookmark2);
		if (hr != S_OK) return hr;
		
	// Return the value based on the bookmark values.  Be sure that
	// they are not specials in which case go below
		if ((*pBookmark1 == *pBookmark2) && (cbBookmark1 != 1) && (cbBookmark2 != 1))
		{
			*pComparison = DBCOMPARE_EQ;
			return S_OK;
		}

	// Determine if we are using ordered or unorder bookmarks
	T* pT = static_cast<T *>(this);
	CComVariant varOrdered;
	HRESULT hrProps = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_ORDEREDBOOKMARKS, &varOrdered);

		if ((*pBookmark1 == DBBMK_FIRST && cbBookmark1 == 1) || 
			(*pBookmark1 == DBBMK_LAST  && cbBookmark1 == 1) ||
			(*pBookmark2 == DBBMK_FIRST && cbBookmark2 == 1) ||
			(*pBookmark2 == DBBMK_LAST  && cbBookmark2 == 1) ||
			(FAILED(hrProps)) || (varOrdered.boolVal == VARIANT_FALSE))
		{
		// If the bookmarks are 'specials' DBBMK_FIRST or DBBMK_LAST or the
		// bookmarks are unordered, then we return NE instead of GT or LT.
			if (*pBookmark1 == *pBookmark2)
				*pComparison = DBCOMPARE_EQ;
			else
				*pComparison = DBCOMPARE_NE;
		}
		else {
		// Return the value based on the bookmark values
			if (*(DBBKMARK *)pBookmark1 == *(DBBKMARK *)pBookmark2)
				*pComparison = DBCOMPARE_EQ;

			if (*(DBBKMARK *)pBookmark1 < *(DBBKMARK *)pBookmark2)
				*pComparison = DBCOMPARE_LT;

			if (*(DBBKMARK *)pBookmark1 > *(DBBKMARK *)pBookmark2)
				*pComparison = DBCOMPARE_GT;
		}
		return S_OK;
	}

	STDMETHOD(GetRowsAt)(HWATCHREGION hReserved1, HCHAPTER hReserved2,
		DBBKMARK cbBookmark, const BYTE * pBookmark, DBROWOFFSET lRowsOffset,
		LONG cRows, ULONG * pcRowsObtained, HROW **prghRows)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IRowsetLocateImpl::GetRowsAt\n");

	// Check the other pointers
		if (pcRowsObtained == NULL || prghRows == NULL) {
			if (NULL != pcRowsObtained)
				*pcRowsObtained = 0;
			return E_INVALIDARG;
		}
		*pcRowsObtained = 0;

	// Check bookmark
	HRESULT hr = ValidateBookmark(cbBookmark, pBookmark);

		if (hr != S_OK) return hr;

	// Set the current row position to the bookmark. Handle any normal values
	T* pT = static_cast<T *>(this);
	T::ObjectLock cab(pT);

	// We need to handle the offset as the start position is defined
	// as the bookmark + offset.  If the offset is negative, and we
	// do not have m_bCanScrollBack then return an error.  The
	// GetNextRows function handles the case where cRows is negative
	// and we don't have m_bCanFetchBack set.
		if (lRowsOffset < 0 && !pT->m_bCanScrollBack)
			return DB_E_CANTSCROLLBACKWARDS;

	DBROWOFFSET iRowsetTemp = pT->m_iRowset;  // Cache the current rowset

		if (cbBookmark != 1) {
		// Determine if this row is deleted or not.
		ULONG ulRowHandle = pT->GetRowHandleFromBookmark(cbBookmark, pBookmark);

		// 0 is uniform value for a deleted bookmark
			if (0 == ulRowHandle) {
				pT->m_iRowset = iRowsetTemp;
				return DB_E_BADBOOKMARK;
			}
			else 
				pT->m_iRowset = ulRowHandle;
		}

		if ((cbBookmark == 1) && (*pBookmark == DBBMK_FIRST))
			pT->m_iRowset = 1;

		if ((cbBookmark == 1) && (*pBookmark == DBBMK_LAST))
			pT->m_iRowset = (DBROWOFFSET)pT->m_rgRowData.GetSize();

	// Set the start position to m_iRowset + lRowsOffset
		pT->m_iRowset += lRowsOffset;

		if (lRowsOffset >= 0)
			pT->m_iRowset -= (cRows >= 0) ? 1 : 0;
		else {
			pT->m_iRowset -= (cRows >= 0) ? 1 : 0;
			if ((LONG)pT->m_iRowset < 0) 
			{
				pT->m_iRowset = iRowsetTemp;
				return DB_S_ENDOFROWSET;
			}
		}
				
		if (pT->m_iRowset > (DWORD)pT->m_rgRowData.GetSize())
		{
			pT->m_iRowset = iRowsetTemp;
			return DB_S_ENDOFROWSET;
		}

	// Call IRowsetImpl::GetNextRows to actually get the rows.
		hr = pT -> GetNextRows(hReserved2, 0, cRows, pcRowsObtained, prghRows);

	// reset the actual row position
		pT->m_iRowset = iRowsetTemp;
		return hr;
	}

	STDMETHOD(GetRowsByBookmark)(HCHAPTER hChapter, ULONG cRows,
		const DBBKMARK rgcbBookmarks[], const BYTE * rgpBookmarks[],
		HROW rghRows[], DBROWSTATUS rgRowStatus[])
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IRowsetLocateImpl::GetRowsByBookmark\n");

		if (rgcbBookmarks == NULL || rgpBookmarks == NULL || rghRows == NULL)
			return E_INVALIDARG;
		if (DB_NULL_HCHAPTER != hChapter)
			return DB_E_NOTSUPPORTED;
		if (cRows == 0)
			return S_OK;	 // No rows fetched in this case.

	T* pT = static_cast<T *>(this);
	T::ObjectLock cab(pT);
	bool bErrors = false;
	bool bFetchedOne = false;

		for (ULONG l = 0; l < cRows; l++) {
		// initialize returned rowhandle
			rghRows[l] = DB_NULL_HROW;

		// Validate each bookmark before fetching the row.	Note, it is
		// an error for the bookmark to be one of the standard values
		HRESULT hr = ValidateBookmark(rgcbBookmarks[l], rgpBookmarks[l], false);

			if (hr != S_OK) {
				bErrors = true;
				if (rgRowStatus != NULL) 
					rgRowStatus[l] = DBROWSTATUS_E_INVALID;
				continue;
			}

		// Fetch the row, we now that it is a valid row after validation.
		ULONG ulRowsObtained = 0;
		ULONG ulRow = pT->GetRowHandleFromBookmark (rgcbBookmarks[l], rgpBookmarks[l]);

			if (0 == ulRow || S_OK != pT->CreateRow(ulRow-1, ulRowsObtained, &rghRows[l])) {
				bErrors = true;
				if (rgRowStatus != NULL) 
					rgRowStatus[l] = DBROWSTATUS_E_INVALID;
				continue;
			} 

			if (rgRowStatus != NULL)
				rgRowStatus[l] = DBROWSTATUS_S_OK;
			bFetchedOne = true;
		}
		if (bErrors)
			return bFetchedOne ? DB_S_ERRORSOCCURRED : DB_E_ERRORSOCCURRED;

		return S_OK;
	}

	STDMETHOD(Hash)(
		HCHAPTER hReserved, DBBKMARK cBookmarks, const DBBKMARK rgcbBookmarks[], 
		const BYTE *rgpBookmarks[], DWORD rgHashedValues[], DBROWSTATUS rgBookmarkStatus[])
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IRowsetLocateImpl::Hash\n");

	T *pT = static_cast<T *>(this);
	T::ObjectLock cab(pT);

	// Validation
	// ROWSET_NOTIFICATION_REENTRANCY_CHECK 
		if (DB_NULL_HCHAPTER != hReserved)
			return DB_E_NOTSUPPORTED;
		if (cBookmarks == 0)
			return S_OK;
		if ((rgHashedValues == NULL) || (cBookmarks != 0 && (rgcbBookmarks == NULL || rgpBookmarks == NULL)))  
			return E_INVALIDARG;

	// Logic for hashing
	ULONG cerrors =0;

		if (rgBookmarkStatus) {
		// Loop through the array hashing them and recording their status
			for (ULONG i = 0; i < cBookmarks; i++) {
				if (SUCCEEDED(HashBmk(rgcbBookmarks[i], rgpBookmarks[i], &(rgHashedValues[i]))))
					rgBookmarkStatus[i] = DBROWSTATUS_S_OK;
				else {
					cerrors++;
					rgBookmarkStatus[i] = DBROWSTATUS_E_INVALID;
				}
			}
		} 
		else {
		// Loop through the array hashing them
			for (ULONG i = 0; i < cBookmarks; i++) {
				if (FAILED(HashBmk(rgcbBookmarks[i], rgpBookmarks[i], &(rgHashedValues[i])))) 
					cerrors++;
			}
		}

		if (cerrors == 0) 
			return S_OK;

		if (cerrors < cBookmarks)
			return DB_S_ERRORSOCCURRED;

		return DB_E_ERRORSOCCURRED;
	}

// Implementation
protected:
	HRESULT HashBmk(
		DBBKMARK cbBmk, const BYTE *pbBmk, ULONG *pdwHashedValue, ULONG ulTableSize = 0xffffffff)
	{
		if (cbBmk != sizeof(DWORD) || pbBmk == NULL)
			return E_INVALIDARG;

		ATLASSERT(pdwHashedValue);
		*pdwHashedValue = (*(UNALIGNED ULONG *)pbBmk) % ulTableSize;
		return S_OK;
	}

public:
	HRESULT ValidateBookmark(DBBKMARK cbBookmark, const BYTE* pBookmark, bool fSpecialBmksAreValid = true)
	{
	T *pT = static_cast<T *>(this);

		if (cbBookmark == 0 || pBookmark == NULL)
			return E_INVALIDARG;

	// All of our bookmarks are DWORDs, if they are anything other than
	// sizeof(DWORD) then we have an invalid bookmark
		if (cbBookmark != sizeof(DBBKMARK) && cbBookmark != 1)
		{
			ATLTRACE("Bookmarks are invalid length, should be DBBKMARK's");
			return DB_E_BADBOOKMARK;
		}

	// explicitly detect invalid bookmark
		if (1 == cbBookmark && DBBMK_INVALID == *pBookmark)
			return DB_E_BADBOOKMARK;

	// if special bookmarks aren't valid, test for them
		if (!fSpecialBmksAreValid && 1 == cbBookmark)
			return DB_E_BADBOOKMARK;

	// If the contents of our bookmarks are less than 0 or greater than
	// rowcount, then they are invalid
	UINT nRows = pT->m_rgRowData.GetSize();
	ULONG ulRow = pT->GetRowHandleFromBookmark (cbBookmark, pBookmark);

		if ((ulRow == 0 || ulRow > nRows) && *pBookmark != DBBMK_FIRST && *pBookmark != DBBMK_LAST)
		{
			ATLTRACE("Bookmark has invalid range");
			return DB_E_BADBOOKMARK;
		}
		return S_OK;
	}
	DBBKMARK GetRowHandleFromBookmark(DBBKMARK cbBookmark, const BYTE *pBookmark)
	{
	T *pT = static_cast<T *>(this);

		if ((cbBookmark == 1) && (*pBookmark == DBBMK_FIRST))
			pT->m_iRowset = 1;

		if ((cbBookmark == 1) && (*pBookmark == DBBMK_LAST))
			pT->m_iRowset = (DBROWOFFSET)pT->m_rgRowData.GetSize();

		return *(DBBKMARK *)pBookmark;	// overload for mapping of bookmarks to rownumber
	}
};

#endif // _ATL_VER < 0x0700

#endif // !defined(_IROWSETLOCATEIMPL_H__78092BC2_182B_46A4_85DA_69C3A48FB066__INCLUDED_)
