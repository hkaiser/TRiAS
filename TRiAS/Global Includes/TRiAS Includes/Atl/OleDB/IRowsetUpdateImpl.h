// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.06.2001 12:31:48 
//
// @doc
// @module IRowsetUpdateImpl.h | Declaration of the <c CIRowsetUpdateImpl> class

#if !defined(_IROWSETUPDATEIMPL_H__B7743F2B_718C_4DA2_9120_7096613A5771__INCLUDED_)
#define _IROWSETUPDATEIMPL_H__B7743F2B_718C_4DA2_9120_7096613A5771__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if _ATL_VER < 0x0700

#include <Atl/OleDb/AtlAlloc.h>

///////////////////////////////////////////////////////////////////////////
// Basisklasse für writable Rowsets mit deferred writing und Undo
template <class T, class Storage, 
		  class UpdateArray = CSimpleArray<Storage>, 
		  class RowClass = CSimpleWritableRow, 
		  class MapClass = CSimpleMap<RowClass::KeyType, RowClass *> >
class ATL_NO_VTABLE IRowsetUpdateImpl : 
	public IRowsetChangeImpl<T, Storage, IRowsetUpdate, RowClass, MapClass>
{
public:
// Destructor
	~IRowsetUpdateImpl()
	{
		m_mapCachedData.RemoveAll();
	}

// IRowsetChange Methods
	STDMETHOD (SetData)(HROW hRow, HACCESSOR hAccessor, void* pSrcData)
	{
	T* pT = static_cast<T *>(this);

		// Check to see if someone is in an event handler.  If we do, then 
		// we should return DB_E_NOTREENTRANT.
		if (!pT->IncrementMutex())
			return DB_E_NOTREENTRANT;
		else
			pT->DecrementMutex();

	// We provide this implementation for use as it adds more 
	// complexity to the SetData function to handle both 
	// immediate and deferred processing.  It also allows us to 
	// cache the original data w/o increasing the size of 
	// IRowsetChangeImpl

	// Determine if we are in immediate or deferred mode, if we are in
	// immediate mode call FlushData.  Otherwise, add the orginal data
	// to the cache
	CComVariant varDeferred;
	HRESULT hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_IRowsetUpdate, &varDeferred);
	bool bDeferred = (FAILED(hr) || varDeferred.boolVal == VARIANT_FALSE) ? false : true;
		
	RowClass *pRow = pT->m_rgRowHandles.Lookup(hRow);

		if (hRow == NULL || pRow == NULL)
			return DB_E_BADROWHANDLE;

	// If we've deleted the row (or are pending) then SetData should fail
		if (pRow->m_status == DBPENDINGSTATUS_DELETED)
			return DB_E_DELETEDROW;

		if (bDeferred) {
			if (pRow->m_status != DBPENDINGSTATUS_CHANGED && 
				pRow->m_status != (DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
			{
			HRESULT hrNotify = pT->Fire_OnRowChange(pT, 1, &hRow, 
					DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_OKTODO, FALSE); 

				if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					return DB_E_CANCELED;

				hrNotify = pT->Fire_OnRowChange(pT, 1, &hRow, 
					DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_ABOUTTODO, FALSE); 
				if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					return DB_E_CANCELED;
			}

		// If a row is soft inserted (i.e. haven't called update yet)
		// then ignore this section.  An undo will cause the row to
		// delete.
			if (pRow->m_status != DBPENDINGSTATUS_NEW) {
			// See if row is already cached, don't make any changes
			//void* pData = (void*)m_mapCachedData.Lookup(hRow, pTemp);
			Storage* pData = m_mapCachedData.Lookup(hRow);

				if (NULL == pData) {
				Storage* pam = NULL;
				
					ATLTRY(pam = new Storage);
					if (pam == NULL) return E_OUTOFMEMORY;

					memcpy(pam, &pT->m_rgRowData[pRow->m_iRowset], sizeof(Storage));
					if (!m_mapCachedData.SetAt(hRow, pam))
						return E_OUTOFMEMORY;
				}
			}
		}

	// NOTE: TransferData will send the SYNCHAFTER phase of the FIRSTCHANGE
	// notification message.  It will handle a veto internally.
		hr = TransferData<T, RowClass, MapClass>(pT, pSrcData, pRow, &(pT->m_rgRowHandles), hAccessor);
		if (FAILED(hr))	return hr;

	// Flush Users Data, if in immediate mode
		if (!bDeferred)	{
		HRESULT hrFlush = pT->FlushData(hRow, hAccessor);

			if (hrFlush == S_OK)
				return hr;  // TransferData may have returned DB_S_ERRORSOCCURRED
			else
				return hrFlush;
		}
		else {
			if (pRow->m_status != DBPENDINGSTATUS_CHANGED && 
				pRow->m_status != (DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
			{
				pT->Fire_OnRowChange(pT, 1, &hRow, 
					DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_DIDEVENT, TRUE);
			}

			if (pRow->m_status != DBPENDINGSTATUS_NEW)
				pRow->m_status = DBPENDINGSTATUS_CHANGED;
			return hr;	// TransferData may have returned DB_S_ERRORSOCCURRED
		}
	}

// IRowsetUpdate Methods
    STDMETHOD (GetOriginalData)(HROW hRow, HACCESSOR hAccessor, void* pData)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetUpdateImpl::GetOriginalData\n"));

	T *pT = static_cast<T *>(this);

	// Check to see if someone is in an event handler.  If we do, then 
	// we should return DB_E_NOTREENTRANT.
		if (!pT->IncrementMutex())
			return DB_E_NOTREENTRANT;
		else
			pT->DecrementMutex();

	// Validate input parameters
	T::_BindType * pBinding = pT->m_rgBindings.Lookup((INT_PTR)hAccessor);

		if (pBinding == NULL)
			return DB_E_BADACCESSORHANDLE;

		if (pData == NULL && pBinding->cBindings != 0)
			return E_INVALIDARG;		

	RowClass* pRow = pT->m_rgRowHandles.Lookup(hRow);

		if (hRow == NULL || pRow == NULL)
			return DB_E_BADROWHANDLE;

	// If the status is DBPENDINGSTATUS_INVALIDROW, the row has been
	// deleted and the change transmitted to the data source.  In 
	// this case, we can't get the original data so return
	// DB_E_DELETEDROW.
		if (pRow->m_status == DBPENDINGSTATUS_INVALIDROW)
			return DB_E_DELETEDROW;

	// Note, need to determine if accessor is not a row accessor

	// Determine if we have a pending insert. In this case, the
	// spec says revert to default values, and if defaults,
	// are not available, then NULLs.
		if (pRow->m_status == DBPENDINGSTATUS_NEW) {
		ATLCOLUMNINFO* pInfo;
		bool bSucceeded = true;
		bool bFailed = false;
		DBORDINAL ulColumns;
		Storage temp;
		
			memcpy(&temp, &pT->m_rgRowData[pRow->m_iRowset], sizeof(Storage));
			pInfo = T::GetColumnInfo(pT, &ulColumns);

			for (ULONG lBind=0; lBind<pBinding->cBindings; lBind++) {
			DBBINDING* pBindCur = &(pBinding->pBindings[lBind]);
			ULONG lColInfo;
			
				for (lColInfo = 0; 
					 lColInfo<ulColumns && pBindCur->iOrdinal != pInfo[lColInfo].iOrdinal; 
					 lColInfo++)
					;
				if (lColInfo == ulColumns)
					return DB_E_BADORDINAL;

			ATLCOLUMNINFO* pColCur = &(pInfo[lColInfo]);
			DBSTATUS dbStat = DBSTATUS_S_DEFAULT;

			// Try to get the default value.  if that doesn't work, then
			// attempt to do a NULL value
				if (FAILED(pT->SetDBStatus(&dbStat, pRow, pColCur))) {
					if ((pColCur->dwFlags & DBCOLUMNFLAGS_ISNULLABLE) ||
						(pColCur->dwFlags & DBCOLUMNFLAGS_MAYBENULL))
					{
					BYTE* pDstTemp = (BYTE*)(&(pT->m_rgRowData[pRow->m_iRowset]) + pColCur->cbOffset);
					
						*pDstTemp = NULL;
						if (pBindCur->dwPart & DBPART_STATUS)
							*((DBSTATUS*)((BYTE*)(pData) + pBindCur->obStatus)) = DBSTATUS_S_ISNULL;
						bSucceeded |= true;
						continue;
					}
					else {
						if (pBindCur->dwPart & DBPART_STATUS)
							*((DBSTATUS*)((BYTE*)(pData) + pBindCur->obStatus)) = DBSTATUS_E_UNAVAILABLE;
						bFailed = true;
						continue;
					}
				}
				else {
					if (pBindCur->dwPart & DBPART_STATUS)
						*((DBSTATUS*)((BYTE*)(pData) + pBindCur->obStatus)) = DBSTATUS_S_OK;
					bSucceeded |= true;
					continue;
				}
			}

			TransferData<T, RowClass, MapClass>(pT, true, pData, pRow, &(pT->m_rgRowHandles), hAccessor);

			memcpy(&pT->m_rgRowData[pRow->m_iRowset], &temp, sizeof(Storage));
			if (!bFailed)
				return S_OK;
			else
				return (bSucceeded ? DB_S_ERRORSOCCURRED : DB_E_ERRORSOCCURRED);
		}

	// Determine if the row is cached, if so, we'll temporarily replace
	// it in m_rgRowData and call TransferData to handle the accessor.
	// It is kind of strange but it saves us from having to reimplement
	// TransferData					

	// REVIEW: Make the map a pointer based map or will this work?
	Storage *pam = m_mapCachedData.Lookup(hRow);
	Storage temp;

		if (pam != NULL) {
			memcpy(&temp, &pT->m_rgRowData[pRow->m_iRowset], sizeof(Storage));
			memcpy(&pT->m_rgRowData[pRow->m_iRowset], pam, sizeof(Storage));
		}

	// We need to trick TransferData to thinking a non-transmitted 
	// deleted row is still alive.  This will be its final state after
	// we return anyway.
		if (pRow->m_status == DBPENDINGSTATUS_DELETED)
			pRow->m_status = DBPENDINGSTATUS_UNCHANGED;
			
	HRESULT hr = TransferData<T, RowClass, MapClass>(pT, true, pData, pRow, &(pT->m_rgRowHandles), hAccessor);

		if (pam != NULL)
			memcpy(&pT->m_rgRowData[pRow->m_iRowset], &temp, sizeof(Storage));

		pRow->m_status = DBPENDINGSTATUS_UNCHANGED;
		return hr;
	}

	STDMETHOD (GetPendingRows)(HCHAPTER /*hReserved*/, DBPENDINGSTATUS dwRowStatus,
            DBCOUNTITEM * pcPendingRows, HROW **prgPendingRows, 
			DBPENDINGSTATUS **prgPendingStatus)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetUpdateImpl::GetPendingRows\n"));

	T *pT = static_cast<T *>(this);
	bool bPending = false;
	RowClass* pRow = NULL;
	//DBROWCOUNT ulRowHandles = (DBROWCOUNT)pT->m_rgRowHandles.GetCount();

		if (pcPendingRows != NULL) {
			*pcPendingRows = 0;
			if (prgPendingRows != NULL)
				*prgPendingRows = NULL;

			if (prgPendingStatus != NULL)
				*prgPendingStatus = NULL;
		}

	// Validate input parameters
		if ((dwRowStatus & ~(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_CHANGED | DBPENDINGSTATUS_DELETED)) != 0)
			return E_INVALIDARG;

	// Validate input parameters
		if ((dwRowStatus & ~(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_CHANGED | DBPENDINGSTATUS_DELETED)) != 0)
			return E_INVALIDARG;

	// Determine how many rows we'll need to return
		for (ULONG iRowset = 0; iRowset < ulRowHandles; iRowset++) {
		// Check to see if a row has a pending status
			pRow = pT->m_rgRowHandles.GetValueAt(iRowset);
			if (pRow->m_status & dwRowStatus)
			{
				if (pcPendingRows != NULL)
					(*pcPendingRows)++;
				bPending = true;
			}
		}

	// In this case, there are no pending rows that match, just exit out
		if (!bPending)
			return S_FALSE;		// There are no pending rows so exit immediately
		else {
		// Here' the consumer just wants to see if there are pending rows
		// we know that so we can exit
			if (pcPendingRows == NULL)
				return S_OK;
		}

	// Allocate arrays for pending rows
		if (prgPendingRows != NULL)	{
			*prgPendingRows = (HROW *)CoTaskMemAlloc(*pcPendingRows * sizeof(HROW));
			if (*prgPendingRows == NULL) {
				*pcPendingRows = 0;
				return E_OUTOFMEMORY;
			}
		}

		if (prgPendingStatus != NULL) {
			*prgPendingStatus = (DBPENDINGSTATUS *)CoTaskMemAlloc(*pcPendingRows * sizeof(DBPENDINGSTATUS));
			if (*prgPendingStatus == NULL) {
				*pcPendingRows = 0;
				CoTaskMemFree(*prgPendingRows);
				*prgPendingRows = NULL;
				return E_OUTOFMEMORY;
			}
			memset(*prgPendingStatus, 0, *pcPendingRows * sizeof(DBPENDINGSTATUS));
		}

		if (prgPendingRows || prgPendingStatus)	{
		ULONG ulRows = 0;
		
			for (ULONG iRowset = 0; iRowset < ulRowHandles; iRowset++) {
				pRow = pT->m_rgRowHandles.GetValueAt(iRowset);
				if (pRow->m_status & dwRowStatus)
				{
					// Add the output row
					pRow->AddRefRow();
					if (prgPendingRows)
						((*prgPendingRows)[ulRows]) = (HROW)pT->m_rgRowHandles.GetKeyAt(iRowset);
					if (prgPendingStatus)
						((*prgPendingStatus)[ulRows]) = (DBPENDINGSTATUS)pRow->m_status;
					ulRows++;
				}
			}

			if (pcPendingRows != NULL)
				*pcPendingRows = ulRows;
		}

	// Return code depending on
		return S_OK;
	}
        
	STDMETHOD (GetRowStatus)(HCHAPTER /*hReserved*/, DBCOUNTITEM cRows, 
		const HROW rghRows[], DBPENDINGSTATUS rgPendingStatus[])
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetUpdateImpl::GetRowStatus\n"));
		T* pT = (T*)this;

	bool bSucceeded = true;
	ULONG ulFetched = 0;

		if (cRows != 0) {
		// check for correct pointers
			if (rghRows == NULL || rgPendingStatus == NULL)
				return E_INVALIDARG;

			for (ULONG ulRows=0; ulRows < cRows; ulRows++) {
			RowClass *pRow = pT->m_rgRowHandles.Lookup(rghRows[ulRows]);
			
				if (pRow == NULL || (pRow->m_status == DBPENDINGSTATUS_INVALIDROW)) {
					rgPendingStatus[ulRows] = DBPENDINGSTATUS_INVALIDROW;
					bSucceeded = false;
					continue;
				}
				if (pRow->m_status != 0)
					rgPendingStatus[ulRows] = pRow->m_status;
				else
					rgPendingStatus[ulRows] = DBPENDINGSTATUS_UNCHANGED;

				ulFetched++;
			}
		}

		if (bSucceeded)
			return S_OK;
		else {
			if (ulFetched > 0)
				return DB_S_ERRORSOCCURRED;
			else
				return DB_E_ERRORSOCCURRED;
		}
	}
        
	STDMETHOD (Undo)(HCHAPTER /*hReserved*/, DBCOUNTITEM cRows, const HROW rghRows[ ],
		DBCOUNTITEM *pcRowsUndone, HROW **prgRowsUndone, 
		DBROWSTATUS **prgRowStatus)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetUpdateImpl::Undo\n"));

	T *pT = static_cast<T *>(this);
	T::ObjectLock lock(pT);

	// Check to see if someone is in an event handler.  If we do, then 
	// we should return DB_E_NOTREENTRANT.
		if (!pT->IncrementMutex()) {
		// Note, we can't set this up above as we may inadvertantly 
		// step on the pcRowsUndone variable.
			if (pcRowsUndone != NULL)
				*pcRowsUndone = NULL;			
			return DB_E_NOTREENTRANT;
		}
		else
			pT->DecrementMutex();

	DBCOUNTITEM ulRows = 0;
	bool bSucceeded = false;
	bool bFailed = false;
	bool bIgnore = false;
	ULONG ulUndone = 0;	

	// the following lines are used to fix the two _alloca calls below.  Those calls are risky 
	// because we may be allocating huge amounts of data.  So instead I'll allocate that data on heap.
	// But if you use _alloca you don't have to worry about cleaning this memory.  So we will use these
	// temporary variables to allocate memory on heap.  As soon as we exit the function, the memory will
	// be cleaned up, just as if we were using alloca. So now, instead of calling alloca, I'll alloc
	// memory on heap using the two smnart pointers below, and then assing it to the actual pointers.
	CHeapPtr<HROW> spTempRowsUndone;
	CHeapPtr<DBROWSTATUS> spTempRowStatus;

	HRESULT hrNotify = S_OK;
	int nReason = 0;

	// Ignore prgRowsUndone/prgRowStatus if pcRowsUndone is NULL and cRows == 0.
		if (pcRowsUndone != NULL || cRows != 0)	{
			if (prgRowsUndone != NULL)
				*prgRowsUndone = NULL;

			if (prgRowStatus != NULL)
				*prgRowStatus = NULL;		
		}
		else {
			bIgnore = true;		// Don't do status or row arrays
		}

	// Check to see how many changes we'll undo 
		if (pcRowsUndone != NULL) {
			*pcRowsUndone = NULL;
			 if (prgRowsUndone == NULL)
				 return E_INVALIDARG;
		}

		if (cRows != 0) {
			if (rghRows == NULL)
				return E_INVALIDARG;
			ulRows = cRows;
		}
		else
			ulRows = (DBCOUNTITEM)pT->m_rgRowHandles.GetCount();

	// NULL out pointers
		if (prgRowsUndone != NULL && ulRows != 0 && bIgnore == false) {
		// Make a temporary buffer as we may not fill up everything
		// in the case where cRows == 0
			if (cRows != 0)
				*prgRowsUndone = (HROW*)CoTaskMemAlloc(ulRows * sizeof(HROW));
			else {
			//*prgRowsUndone = (HROW*)_alloca(ulRows * sizeof(HROW));
				spTempRowsUndone.Allocate(ulRows);
				*prgRowsUndone = spTempRowsUndone;
			}

			if (*prgRowsUndone == NULL)
				return E_OUTOFMEMORY;
		}
		else {
			if (prgRowsUndone != NULL && bIgnore == false)
				*prgRowsUndone = NULL;
		}

		if (prgRowStatus != NULL && ulRows != 0 && bIgnore == false) {
			if (cRows != 0)
				*prgRowStatus = (DBROWSTATUS*)CoTaskMemAlloc(ulRows * sizeof(DBROWSTATUS));
			else {
				//*prgRowStatus = (DBROWSTATUS*)_alloca(ulRows * sizeof(DBROWSTATUS));
				spTempRowStatus.Allocate(ulRows);
				*prgRowStatus = spTempRowStatus;
			}

			if (*prgRowStatus == NULL) {
				if (cRows != 0)
					CoTaskMemFree(*prgRowsUndone);
				*prgRowsUndone = NULL;
				return E_OUTOFMEMORY;
			}
		}
		else {
			if (prgRowStatus != NULL && bIgnore == false)
				*prgRowStatus = NULL;
		}

	RowClass* pRow = NULL;
	ULONG ulRowIdx = 0;

		for (ULONG ulUndoRow = 0; ulUndoRow < ulRows; ulUndoRow++) {
		HROW hRowUndo = NULL;
		ULONG ulCurrentRow = ulUndone;

			if (rghRows != NULL && cRows != 0)
				hRowUndo = rghRows[ulUndoRow];
			else {
				_ASSERTE(ulUndoRow < (ULONG)pT->m_rgRowHandles.GetCount());
				hRowUndo = pT->m_rgRowHandles.GetKeyAt(ulRowIdx++);
			}

			if (prgRowsUndone != NULL && bIgnore == false)
				(*prgRowsUndone)[ulCurrentRow] = hRowUndo;
			
		// Fetch the RowClass and determine if it is valid
			pRow = pT->m_rgRowHandles.Lookup(hRowUndo);
			if (pRow == NULL) {
				if (prgRowStatus != NULL && bIgnore == false)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_INVALID;
				bFailed = true;
				ulUndone++;
				continue;
			}

		// If cRows is zero we'll go through all rows fetched.  We shouldn't
		// increment the count for rows that haven't been modified.
			if (cRows != 0 || (pRow != NULL &&
				pRow->m_status != 0 && pRow->m_status != DBPENDINGSTATUS_UNCHANGED
				&& pRow->m_status != DBPENDINGSTATUS_INVALIDROW))
				ulUndone++;
			else
				continue;


		// AddRef the row if cRows is zero (we will be returning it to the
		// consumer)
			if (cRows == 0)
				pRow->AddRefRow();

		// Fetch the data, note, this may be NULL in several cases
		Storage *pData = m_mapCachedData.Lookup(hRowUndo);

			switch (pRow->m_status)	{
			case DBPENDINGSTATUS_INVALIDROW:	
			// Row has already been hard deleted
				{
					if (prgRowStatus != NULL && bIgnore == false)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_DELETED;
					bFailed = true;
					continue;
				}
				break;

			case DBPENDINGSTATUS_NEW:			
			// Row has been soft inserted
			// If the row is newly inserted, go ahead and mark its
			// row as INVALID (according to the specification).
				{
					hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
						DBREASON_ROW_UNDOINSERT, DBEVENTPHASE_OKTODO, FALSE);

					if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					{
						if (prgRowStatus != NULL && bIgnore == false)
							(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
						bFailed = true;
						continue;
					}

					hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
						DBREASON_ROW_UNDOINSERT, DBEVENTPHASE_ABOUTTODO, FALSE);

					if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					{
						if (prgRowStatus != NULL && bIgnore == false)
							(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
						bFailed = true;
						continue;
					}

					hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
						DBREASON_ROW_UNDOINSERT, DBEVENTPHASE_SYNCHAFTER, FALSE);
					
					if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					{
						if (prgRowStatus != NULL && bIgnore == false)
							(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
						bFailed = true;
						continue;
					}

					if (prgRowStatus != NULL && bIgnore == false)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_S_OK;
					pT->m_rgRowData.RemoveAt(pRow->m_iRowset);

				// Move any other subsequent rows up in the chain
					for (long l = 0; l < pT->m_rgRowHandles.GetCount(); l++)
					{
					RowClass *pCheckRow = pT->m_rgRowHandles.GetValueAt(l);

						if (pCheckRow != NULL && pCheckRow->m_iRowset > pRow->m_iRowset)
							pCheckRow->m_iRowset--;
					}

					pRow->m_status = DBPENDINGSTATUS_INVALIDROW;
					bSucceeded = true;

					pT->Fire_OnRowChange(pT, 1, &hRowUndo, DBREASON_ROW_UNDOINSERT,	DBEVENTPHASE_DIDEVENT, TRUE);
					continue;
				}
				break;

			case 0:								// Row has just been fetched
			case DBPENDINGSTATUS_DELETED:		// Row has been soft deleted
			case DBPENDINGSTATUS_UNCHANGED:		// Row is not changed
				{
					if (pRow->m_status == DBPENDINGSTATUS_DELETED)
					{
						nReason = 1;
						hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
							DBREASON_ROW_UNDODELETE, DBEVENTPHASE_OKTODO, FALSE);

						if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
						{
							if (prgRowStatus != NULL && bIgnore == false)
								(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
							bFailed = true;
							continue;
						}

						hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
							DBREASON_ROW_UNDODELETE, DBEVENTPHASE_ABOUTTODO, FALSE);

						if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
						{
							if (prgRowStatus != NULL && bIgnore == false)
								(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
							bFailed = true;
							continue;
						}

						hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
							DBREASON_ROW_UNDODELETE, DBEVENTPHASE_SYNCHAFTER, FALSE);
						
						if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
						{
							if (prgRowStatus != NULL && bIgnore == false)
								(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
							bFailed = true;
							continue;
						}
					}

					pRow->m_status = DBPENDINGSTATUS_UNCHANGED;

					if (prgRowStatus != NULL && bIgnore == false)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_S_OK;
					bSucceeded = true;

				// Somebody set, then deleted a row most likely
					if (pData != NULL)
						memcpy(&pT->m_rgRowData[pRow->m_iRowset], pData, sizeof(Storage));

					if (nReason == 1)
					{
						pT->Fire_OnRowChange(pT, 1, &hRowUndo, DBREASON_ROW_UNDODELETE,
							DBEVENTPHASE_DIDEVENT, TRUE);
						nReason = 0;
					}
					continue;
				}
				break;

			default:							// Row has been changed
				{
					hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
						DBREASON_ROW_UNDOCHANGE, DBEVENTPHASE_OKTODO, FALSE);

					if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					{
						if (prgRowStatus != NULL && bIgnore == false)
							(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
						bFailed = true;
						continue;
					}

					hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
						DBREASON_ROW_UNDOCHANGE, DBEVENTPHASE_ABOUTTODO, FALSE);

					if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					{
						if (prgRowStatus != NULL && bIgnore == false)
							(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
						bFailed = true;
						continue;
					}

					hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUndo, 
						DBREASON_ROW_UNDOCHANGE, DBEVENTPHASE_SYNCHAFTER, FALSE);
					
					if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
					{
						if (prgRowStatus != NULL && bIgnore == false)
							(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
						bFailed = true;
						continue;
					}

					if (pData == NULL) {
						pT->Fire_OnRowChange(pT, 1, &hRowUndo, DBREASON_ROW_UNDOCHANGE,
								DBEVENTPHASE_FAILEDTODO, FALSE);

						if (prgRowStatus != NULL && bIgnore == false)
							(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_INVALID;
						bFailed = true;
						continue;
					}

				// Copy data back
					memcpy(&pT->m_rgRowData[pRow->m_iRowset], pData, sizeof(Storage));
					if (prgRowStatus != NULL && bIgnore == false)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_S_OK;
					pRow->m_status = DBPENDINGSTATUS_UNCHANGED;
					bSucceeded = true;

				// Remove undo buffer
					m_mapCachedData.RemoveKey(hRowUndo);

				// Check if we need to release the row because it's ref was 0
				// See the IRowset::ReleaseRows section in the spec for more
				// information
					if (pRow->m_dwRef == 0)
					{
						pRow->AddRefRow();	// Artifically bump this to remove it
						if (FAILED(pT->RefRows(1, &hRowUndo, NULL, NULL, false)))
							return E_FAIL;
					}

					pT->Fire_OnRowChange(pT, 1, &hRowUndo, DBREASON_ROW_UNDOCHANGE, DBEVENTPHASE_DIDEVENT, TRUE);
				}
				break;
			}
		}

	// Set the output for rows undone.
		if (pcRowsUndone)
			*pcRowsUndone = ulUndone;

	// In the case where cRows == 0, we need to allocate the final
	// array of data.
		if (cRows == 0) {
		HROW *prowTemp = NULL;
		DBROWSTATUS *prowStatus = NULL;

			if (prgRowsUndone != NULL && ulUndone != 0 && bIgnore == false) {
				prowTemp = (HROW*)CoTaskMemAlloc(ulUndone * sizeof(HROW));
				if (prowTemp == NULL) {
				// Free prgRowsUndone
					if (cRows != 0 && prgRowsUndone != NULL)
						CoTaskMemFree(*prgRowsUndone);

					if (cRows != 0 && prgRowStatus != NULL)
						CoTaskMemFree(*prgRowStatus);

					return E_OUTOFMEMORY;
				}
				memcpy(prowTemp, *prgRowsUndone, (sizeof(HROW)*ulUndone));
				if (cRows != 0)
					CoTaskMemFree(*prgRowsUndone);  // we're finished w/ the temp array
				*prgRowsUndone = prowTemp;
			}
			else {
				if (prgRowsUndone != NULL && bIgnore == false)
					*prgRowsUndone = NULL;
			}

			if (prgRowStatus != NULL && ulUndone != 0 && bIgnore == false) {
				prowStatus = (DBROWSTATUS*)CoTaskMemAlloc(ulUndone * sizeof(DBROWSTATUS));
				if (prowStatus == NULL) {
					if (cRows != 0 && prgRowsUndone != NULL)
						CoTaskMemFree(*prgRowsUndone);

					if (prgRowStatus != NULL && cRows != 0)
						CoTaskMemFree(*prgRowStatus);

					return E_OUTOFMEMORY;
				}
				memcpy(prowStatus, *prgRowStatus, (sizeof(DBROWSTATUS)*ulUndone));
				if (cRows != 0)
					CoTaskMemFree(*prgRowStatus);
				*prgRowStatus = prowStatus;
			}
			else {
				if (prgRowStatus != NULL && bIgnore == false)
					*prgRowStatus = NULL;
			}
		}

	// Send the return value
		if (!bFailed)
			return S_OK;
		else {
			if (!bSucceeded)
				return DB_E_ERRORSOCCURRED;
			else
				return DB_S_ERRORSOCCURRED;
		}
	}
        
	STDMETHOD (Update)(HCHAPTER /*hReserved*/, DBCOUNTITEM cRows,
		const HROW rghRows[], DBCOUNTITEM *pcRows, HROW **prgRows,
		DBROWSTATUS **prgRowStatus)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetUpdateImpl::Update\n"));

	T *pT = static_cast<T *>(this);
	T::ObjectLock lock(pT);

	// Check to see if someone is in an event handler.  If we do, then 
	// we should return DB_E_NOTREENTRANT.
		if (!pT->IncrementMutex()) {
			if (pcRows != NULL)
				*pcRows = NULL;
			return DB_E_NOTREENTRANT;
		}
		else
			pT->DecrementMutex();

	bool bSucceeded = false;
	bool bFailed = false;
	bool bIgnore = false;
	ULONG ulCount = 0;
	DBCOUNTITEM ulRowUpdate = 0;

	// the following lines are used to fix the two _alloca calls below.  Those calls are risky 
	// because we may be allocating huge amounts of data.  So instead I'll allocate that data on heap.
	// But if you use _alloca you don't have to worry about cleaning this memory.  So we will use these
	// temporary variables to allocate memory on heap.  As soon as we exit the function, the memory will
	// be cleaned up, just as if we were using alloca. So now, instead of calling alloca, I'll alloc
	// memory on heap using the two smnart pointers below, and then assing it to the actual pointers.
	CHeapPtr<HROW> spTempRows;
	CHeapPtr<DBROWSTATUS> spTempRowStatus;

		if (pcRows != NULL || cRows != 0) {
			if (prgRows != NULL)
				*prgRows = NULL;

			if (prgRowStatus != NULL)
				*prgRowStatus = NULL;
		}
		else {
			bIgnore = true;
		}

		if (pcRows != NULL) {
			*pcRows = NULL;
			if (prgRows == NULL)
				return E_INVALIDARG;
		}

		if (cRows != 0) {
			if (rghRows == NULL)
				return E_INVALIDARG;
			ulRowUpdate = cRows;
		}
		else
			ulRowUpdate = (DBCOUNTITEM)pT->m_rgRowHandles.GetCount();

	// NULL out pointers
		if (prgRows != NULL && ulRowUpdate != 0  && !bIgnore) {
			if (cRows != 0)
				*prgRows = (HROW*)CoTaskMemAlloc(ulRowUpdate * sizeof(HROW));
			else {
				spTempRows.Allocate(ulRowUpdate);
				*prgRows = spTempRows;
			}
			if (*prgRows == NULL)
				return E_OUTOFMEMORY;
		}
		else {
			if (prgRows != NULL && bIgnore == false)
				*prgRows = NULL;
		}

		if (prgRowStatus != NULL && ulRowUpdate != 0  && !bIgnore) {
			if (cRows != 0)
				*prgRowStatus = (DBROWSTATUS*)CoTaskMemAlloc(ulRowUpdate * sizeof(DBROWSTATUS));
			else {
				spTempRowStatus.Allocate(ulRowUpdate);
				*prgRowStatus = spTempRowStatus;
			}

			if (*prgRowStatus == NULL) {
				CoTaskMemFree(*prgRows);
				*prgRows = NULL;
				return E_OUTOFMEMORY;
			}
		}
		else {
			if (prgRowStatus != NULL && !bIgnore)
				*prgRowStatus = NULL;
		}

	// NOTE:  If cRows is zero, then we should ignore rghRows and 
	// update all of the rows in the cached map.
	RowClass *pRow = NULL;
	ULONG ulRowIdx = 0;
	POSITION pos = pT->m_rgRowHandles.GetStartPosition();

		for (ULONG ulRow = 0; ulRow < ulRowUpdate; ulRow++) {
		void* pData = NULL;
		HROW hRowUpdate = NULL;
		ULONG ulAlreadyProcessed = 0;
		bool bDupRow = false;
		LONG ulCurrentRow = ulCount;

		// Fetch the HROW, RowClass, and Data for the row.  Perform
		// Validation as necessiary
			if (cRows != 0) {
				hRowUpdate = rghRows[ulRow];
				for (ULONG ulCheckDup = 0; ulCheckDup < ulRow; ulCheckDup++)
				{
					if (pT->IsSameRow(hRowUpdate, rghRows[ulCheckDup]) == S_OK)
					{
						ulAlreadyProcessed = ulCheckDup;
						bDupRow = true;
						break;
					}
				}
			}
			else {
				_ASSERTE(ulRow < (ULONG)pT->m_rgRowHandles.GetCount());
				hRowUpdate = pT->m_rgRowHandles.GetKeyAt(ulRowIdx++);
			}

			if (prgRows != NULL && !bIgnore)
				(*prgRows)[ulCurrentRow] = hRowUpdate;

			if (bDupRow) {
			// We've already set the row before, just copy status and
			// continue processing
			//		pT->Fire_OnRowChange(pT, 1, (HROW*)&hRowUpdate, DBREASON_ROW_UPDATE, 
			//			DBEVENTPHASE_DIDEVENT, TRUE); 

				if (prgRowStatus != NULL && !bIgnore)
					(*prgRowStatus)[ulCurrentRow] = (*prgRowStatus)[ulAlreadyProcessed];

				ulCount++;
				continue;
			}

			pRow = pT->m_rgRowHandles.Lookup(hRowUpdate);
			if (pRow == NULL) {
				if (prgRowStatus != NULL  && bIgnore == false)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_INVALID;
				bFailed = true;
				ulCount++;
				continue;
			}

		// If the row is not UNCHANGED, send preliminary notifications before beginning processing
			if (pRow->m_status != 0 && pRow->m_status != DBPENDINGSTATUS_UNCHANGED) {
			HRESULT hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUpdate, DBREASON_ROW_UPDATE, 
														DBEVENTPHASE_OKTODO, FALSE); 

				if ((hrNotify != S_OK) && (hrNotify != E_FAIL))	{
					if (prgRowStatus != NULL && !bIgnore)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
					bFailed = true;
					continue;
				}

				hrNotify = pT->Fire_OnRowChange(pT, 1, &hRowUpdate, DBREASON_ROW_UPDATE, 
														DBEVENTPHASE_ABOUTTODO, FALSE); 
				if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
				{
					if (prgRowStatus != NULL && !bIgnore)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
					bFailed = true;
					continue;
				}

				hrNotify = pT->Fire_OnRowChange(pT, 1, (HROW*)&hRowUpdate, DBREASON_ROW_UPDATE, 
														DBEVENTPHASE_SYNCHAFTER, FALSE);
				if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
				{
					if (prgRowStatus != NULL && !bIgnore)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_CANCELED;
					bFailed = true;
					continue;
				}
			}

		// If cRows is zero we'll go through all rows fetched.  We
		// shouldn't increment the attempted count for rows that are
		// not changed
			if (cRows != 0 || 
					(pRow != NULL && 
					 pRow->m_status !=0 && pRow->m_status != DBPENDINGSTATUS_UNCHANGED &&
					 pRow->m_status != DBPENDINGSTATUS_INVALIDROW)
					)
				ulCount++;
			else
				continue;

			switch(pRow->m_status)
			{
			case DBPENDINGSTATUS_INVALIDROW:		// Row is bad or deleted
				pT->Fire_OnRowChange(pT, 1, (HROW *)&hRowUpdate, DBREASON_ROW_UPDATE, 
						DBEVENTPHASE_FAILEDTODO, TRUE); 

				if (prgRowStatus != NULL && !bIgnore)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_DELETED;
				bFailed = true;
				continue;
				break;

			case DBPENDINGSTATUS_UNCHANGED:
			case 0:
			// If the row's status is not changed, then just put S_OK
			// and continue.  The spec says we should not transmit the
			// request to the data source (as nothing would change).
			//	pT->Fire_OnRowChange(pT, 1, (HROW*)&hRowUpdate, DBREASON_ROW_UPDATE, 
			//		DBEVENTPHASE_DIDEVENT, TRUE); 

				if (prgRowStatus != NULL && bIgnore == false)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_S_OK;
				bSucceeded = true;
				continue;
				break;

			default:
				pData = &pT->m_rgRowData[pRow->m_iRowset]; 
				if (pData == NULL) {
					pT->Fire_OnRowChange(pT, 1, (HROW*)&hRowUpdate, DBREASON_ROW_UPDATE, 
							DBEVENTPHASE_FAILEDTODO, TRUE); 

					if (prgRowStatus != NULL && bIgnore == false)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_INVALID;
					bFailed = true;
					continue;
				}

			// If the rghRows variable is NULL, we now add the row to 
			// prgRows.  We do this because we have determined that the
			// row has changed. AddRef the row as it may not be held by 
			// the consumer.
				if (cRows == 0)
					pRow->AddRefRow();

			// Ask the provider if it is OK to change this row.
			DBROWSTATUS status = DBROWSTATUS_S_OK;
	
				if (FAILED(IsUpdateAllowed(pRow->m_status, hRowUpdate, &status))) {
					pT->Fire_OnRowChange(pT, 1, (HROW*)&hRowUpdate, DBREASON_ROW_UPDATE, 
							DBEVENTPHASE_FAILEDTODO, TRUE); 

					if (prgRowStatus != NULL && bIgnore == false)
						(*prgRowStatus)[ulCurrentRow] = status;
					bFailed = true;
					continue;
				}

				if (pRow->m_status == DBPENDINGSTATUS_DELETED) {
					pT->m_rgRowData.RemoveAt(pRow->m_iRowset);

				// Need to update any outstanding pRow->m_iRowset variables
					for (long i = 0; i < pT->m_rgRowHandles.GetSize(); ++i) {
					RowClass *pCheckRow = pT->m_rgRowHandles.GetValueAt(i);

						if (pCheckRow != NULL && pCheckRow->m_iRowset > pRow->m_iRowset)
							pCheckRow->m_iRowset--;
					}

				// Per the specification, deleted rows transmitted
				// to the data source are set to DBPENDINGSTATUS_INVALIDROW
					pRow->m_status = DBPENDINGSTATUS_INVALIDROW;
				}

				// Copy data back
				if (FAILED(pT->FlushData(hRowUpdate, NULL)))
				{
					if (prgRowStatus != NULL && !bIgnore)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_FAIL;

					pT->Fire_OnRowChange(pT, 1, (HROW*)&hRowUpdate, DBREASON_ROW_UPDATE, 
							DBEVENTPHASE_FAILEDTODO, TRUE); 
					bFailed = true;
					continue;
				}

				if (prgRowStatus != NULL && !bIgnore)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_S_OK;
				bSucceeded = true;

				if (pRow->m_status != DBPENDINGSTATUS_DELETED)
				{
					if (pRow->m_status != DBPENDINGSTATUS_INVALIDROW)
						pRow->m_status = DBPENDINGSTATUS_UNCHANGED;
				}

			// Remove undo buffer.  
				if (m_mapCachedData.Lookup(hRowUpdate) != NULL)
					m_mapCachedData.RemoveKey(hRowUpdate);

			// remove the ref count if the consumer didn't have a handle.
//				if (rghRows == NULL)
//					pRow->ReleaseRow();

			// Check if we need to release the row because it's ref was 0
			// See the IRowset::ReleaseRows section in the spec for more
			// information
				if (pRow->m_dwRef == 0)	{
					pRow->AddRefRow();		// Artifically bump this to remove it
					if (FAILED(pT->RefRows(1, &hRowUpdate, NULL, NULL, false)))
						return E_FAIL;
				}
				pT->Fire_OnRowChange(pT, 1, (HROW*)&hRowUpdate, DBREASON_ROW_UPDATE, 
						DBEVENTPHASE_DIDEVENT, TRUE); 
				break;
			}
		}

	// Set the output for rows undone.
		if (pcRows)	{
			if (cRows == 0)
				*pcRows = ulCount;
			else
				*pcRows = cRows;
		}

	// In the case where cRows == 0, we need to allocate the final
	// array of HROWs and status values.
		if (cRows == 0)	{
		HROW* prowTemp;
		DBROWSTATUS* prowStatus;

			if (prgRows != NULL && ulCount != 0 && !bIgnore) {
				prowTemp = (HROW*)CoTaskMemAlloc(ulCount * sizeof(HROW));
				if (prowTemp == NULL) {
					if (cRows != 0 && prgRows != NULL)
						CoTaskMemFree(*prgRows);

					if (cRows != 0 && prgRowStatus != NULL)
						CoTaskMemFree(*prgRowStatus);

					return E_OUTOFMEMORY;
				}

				memcpy(prowTemp, *prgRows, sizeof(HROW) * ulCount);
				if (cRows != 0)
					CoTaskMemFree(*prgRows);
				*prgRows = prowTemp;
			}
			else {
				if (prgRows != NULL && bIgnore == false)
					*prgRows = NULL;
			}

			if (prgRowStatus != NULL && ulCount != 0 && !bIgnore) {
				prowStatus = (DBROWSTATUS*)CoTaskMemAlloc(ulCount * sizeof(DBROWSTATUS));
				if (prowStatus == NULL)	{
					if (cRows != 0 && prgRows != NULL)
						CoTaskMemFree(*prgRows);

					if (cRows != 0 && prgRowStatus != NULL)
						CoTaskMemFree(*prgRowStatus);

					return E_OUTOFMEMORY;
				}

				memcpy(prowStatus, *prgRowStatus, (sizeof(DBROWSTATUS)*ulCount));
				if (cRows != 0)
					CoTaskMemFree(*prgRowStatus);
				*prgRowStatus = prowStatus;
			}
			else {
				if (prgRowStatus != NULL && !bIgnore)
					*prgRowStatus = NULL;
			}
		}

	// Send the return value
		if (!bFailed)
			return S_OK;
		else {
			if (!bSucceeded)
				return DB_E_ERRORSOCCURRED;
			else
				return DB_S_ERRORSOCCURRED;
		}
	}

	// Callback functions
	HRESULT IsUpdateAllowed(/*[in]*/DBPENDINGSTATUS status, /*[in] */ HROW hRowUpdate, /* [out] */ DBROWSTATUS* pRowStatus)
	{
	// If you need to perform any checks for security, integrity
	// violations, etc. as a result of an update, override this
	// method.

	// Make sure you put the appropriate status in the pRowStatus
	// as it will be returned to the user.
		return S_OK;
	}

// Map containing original data for deferred operation
	CSimpleMap<HROW, Storage *> m_mapCachedData;
};

#endif // _ATL_VER < 0x0700

#endif // !defined(_IROWSETUPDATEIMPL_H__B7743F2B_718C_4DA2_9120_7096613A5771__INCLUDED_)
