// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.06.2001 12:32:02 
//
// @doc
// @module IRowsetChangeImpl.h | Declaration of the <c CIRowsetChangeImpl> class

#if !defined(_IROWSETCHANGEIMPL_H__B6971F12_688C_46C6_AD0B_5C693AF3627E__INCLUDED_)
#define _IROWSETCHANGEIMPL_H__B6971F12_688C_46C6_AD0B_5C693AF3627E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#if _ATL_VER >= 0x0700

// vordefinierte Klassen benutzen
typedef CSimpleRow CSimpleWritableRow;

#else

///////////////////////////////////////////////////////////////////////////////
// Hält eine Row bei verwendung von IRowsetChange bzw. IRowsetUpdate
class CSimpleWritableRow
{
public:
	typedef DBCOUNTITEM KeyType;

	CSimpleWritableRow(DBCOUNTITEM iRowsetCur) 
	{ 
		m_dwRef = 0;
		m_pData = NULL;
		m_iRowset = iRowsetCur; 
		m_iOriginalRowset = iRowsetCur; // used for stronger identity tests
		m_status = 0;
	}
	~CSimpleWritableRow()
	{
		m_pData = NULL;	// Data will be freed seperately
	}
	DWORD AddRefRow() { return CComObjectThreadModel::Increment((LPLONG)&m_dwRef); } 
	DWORD ReleaseRow() { return CComObjectThreadModel::Decrement((LPLONG)&m_dwRef); }

	HRESULT Compare(CSimpleWritableRow *pRow)
	{
		ATLASSERT(pRow != NULL);
		return (m_iRowset == pRow->m_iRowset) ? S_OK : S_FALSE;
	}

	DWORD	m_dwRef;
	void*	m_pData;			// NEW:  For IRowsetChange & IRowsetUpdate
	DBPENDINGSTATUS m_status;	// NEW:  For IRowsetUpdate
	KeyType m_iOriginalRowset;	// NEW:  For IRowsetChange & IRowsetUpdate
	KeyType m_iRowset;
};

///////////////////////////////////////////////////////////////////////////////
// Daten schreiben
template <class T>
inline void SendColumnSetFailureNotification(
	T *pT, HROW hNotifyRow, T::_BindType* pBinding, CSimpleArray<DBORDINAL> &rgColumns)
{
	pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
		rgColumns.GetData(), DBREASON_COLUMN_SET, 
		DBEVENTPHASE_FAILEDTODO, TRUE);
}

template <class T, class RowClass>
inline void SendRowsFirstChangeFailureNotification(
	T *pT, RowClass *pRow, HROW *phNotifyRow, bool bDeferred)
{
	if (bDeferred)
	{
	// Determine if we are really in a first row change 
		if (pRow->m_status != DBPENDINGSTATUS_CHANGED && 
			pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
		{
			pT->Fire_OnRowChange(pT, 1, phNotifyRow, 
				DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_FAILEDTODO, TRUE);
		}
	}
}

template <class T, class RowClass, class MapClass>
HRESULT TransferData(T *pT, void* pData, RowClass* pRow, MapClass *pMap, HACCESSOR hAccessor)
{
	ATLTRACE(atlTraceDBProvider, 2, _T("TransferData\n"));

bool bFailed = false;
bool bSucceeded = false;
HRESULT hr = S_OK;

CSimpleArray<DBORDINAL> rgColumns;
HROW hNotifyRow = NULL;

	for (int i = 0; i < pT->m_rgRowHandles.GetSize(); i++) {
	RowClass* pCheckRow = pT->m_rgRowHandles.GetValueAt(i);

		if (pCheckRow == pRow) {
			hNotifyRow = pT->m_rgRowHandles.GetKeyAt(i);
			break;
		}
	}
	_ASSERTE(NULL != hNotifyRow);

// We need to send the DBREASON_ROW_FIRSTCHANGE notification's
// SYNCHAFTER phase in this function.  IFF. we're deferred and
// we have a newly changed row.
CComVariant varDeferred;
bool bDeferred;

	hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_IRowsetUpdate, &varDeferred);
	bDeferred = (FAILED(hr) || varDeferred.boolVal == VARIANT_FALSE) ? false : true;

// Check for a deleted row
	if (pRow->m_iRowset >= pT->m_rgRowData.GetCount())
	{
		SendRowsFirstChangeFailureNotification(pT, pRow, &hNotifyRow, bDeferred);
		return DB_E_DELETEDROW;
	}

// NOTE: This was checking against DBPENDINGSTATUS_DELETED.  Instead, it 
// should check for DBPENDINGSTATUS_INVALIDROW (means a forced deleted
// row).
	if (pRow->m_status == DBPENDINGSTATUS_INVALIDROW)
	{
		SendRowsFirstChangeFailureNotification(pT, pRow, &hNotifyRow, bDeferred);
		return DB_E_DELETEDROW;
	}

T::_BindType *pBinding = pT->m_rgBindings.Lookup((INT_PTR)hAccessor);

	if (NULL == pBinding)
	{
		SendRowsFirstChangeFailureNotification(pT, pRow, &hNotifyRow, bDeferred);
		return DB_E_BADACCESSORHANDLE;
	}

	if (pData == NULL && pBinding->cBindings != 0)
	{
		SendRowsFirstChangeFailureNotification(pT, pRow, &hNotifyRow, bDeferred);
		return E_INVALIDARG;
	}
	
void *pSrcData = pData;
void *pDstData = (void *)&(pT->m_rgRowData[(LONG)pRow->m_iRowset]);

// Send the OKTODO notification
	if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
		pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
	{
		for (DBORDINAL l = 0; l < pBinding->cBindings; l++)
		{
			if (!rgColumns.Add(pBinding->pBindings[l].iOrdinal))
				return E_OUTOFMEMORY;
		}

	HRESULT hrNotify = pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
			rgColumns.GetData(), DBREASON_COLUMN_SET, DBEVENTPHASE_OKTODO, FALSE);

		if ((hrNotify != S_OK) && (hrNotify != E_FAIL))	{
			if (bDeferred)
				pT->Fire_OnRowChange(pT, 1, &hNotifyRow, DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_FAILEDTODO, TRUE);
			return DB_E_CANCELED;
		}

		hrNotify = pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings,
			rgColumns.GetData(), DBREASON_COLUMN_SET, DBEVENTPHASE_ABOUTTODO, FALSE);
		if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
		{
			if (bDeferred)
				pT->Fire_OnRowChange(pT, 1, &hNotifyRow, DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_FAILEDTODO, TRUE);
			return DB_E_CANCELED;
		}

		hrNotify = pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
			rgColumns.GetData(), DBREASON_COLUMN_SET, DBEVENTPHASE_SYNCHAFTER, FALSE);
		if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
		{
			if (bDeferred)
				pT->Fire_OnRowChange(pT, 1, &hNotifyRow, DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_FAILEDTODO, TRUE);
			return DB_E_CANCELED;
		}
	}

	if (bDeferred && pRow->m_status != DBPENDINGSTATUS_CHANGED &&
		pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
	{
	HRESULT hrNotify = pT->Fire_OnRowChange(pT, 1, &hNotifyRow, 
			DBREASON_ROW_FIRSTCHANGE, DBEVENTPHASE_SYNCHAFTER, FALSE);

		if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
		{
			pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, rgColumns.GetData(), DBREASON_COLUMN_SET, DBEVENTPHASE_FAILEDTODO, TRUE);
			return DB_E_CANCELED;
		}
	}


DBORDINAL cCols;
ATLCOLUMNINFO* pColInfo = T::GetColumnInfo(pT, &cCols);

	for (DBORDINAL iBind =0; iBind < pBinding->cBindings; iBind++) {
	DBBINDING *pBindCur = &(pBinding->pBindings[iBind]);
	DBORDINAL iColInfo;

		for (iColInfo = 0; 
			 iColInfo < cCols && pBindCur->iOrdinal != pColInfo[iColInfo].iOrdinal;
			 iColInfo++)
			 ;
		if (iColInfo == cCols)
		{
			SendColumnSetFailureNotification(pT, hNotifyRow, pBinding, rgColumns);
			SendRowsFirstChangeFailureNotification(pT, pRow, &hNotifyRow, bDeferred);
			return DB_E_BADORDINAL;
		}

	ATLCOLUMNINFO* pColCur = & (pColInfo[iColInfo]);	// Ordinal found at iColInfo
	BYTE *pSrcTemp = (BYTE *)pSrcData + pBindCur->obValue;
	BYTE *pDstTemp = NULL;

		if (pBindCur->dwPart & DBPART_VALUE)
			pDstTemp = (BYTE *)pDstData + pColCur->cbOffset;

	// Check to see that the appropriate data parts are available
		if ((pBindCur->dwPart & DBPART_LENGTH) &&
			!(pBindCur->dwPart & DBPART_VALUE) &&
			!(pBindCur->dwPart & DBPART_STATUS))
		{
			if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
				pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
			{
				pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings,
					rgColumns.GetData(), DBREASON_COLUMN_SET, DBEVENTPHASE_FAILEDTODO, 
					TRUE);
			}

		// Not sure why you would want to run SetData here!
			bFailed = true;
			continue;
		}

	// Handle the the status for any consumer issues
	DBSTATUS dbStat = DBSTATUS_S_OK;

	// Allow the provider to do checking for DBSTATUS_S_ISNULL
		if (pBindCur->dwPart & DBPART_STATUS) {
			dbStat = *((DBSTATUS *)((BYTE *)(pSrcData) + pBindCur->obStatus));

		// Return DBSTATUS_E_UNAVAILABLE if the status is DBSTATUS_S_OK
		//	and either the value part is not bound or the length part is
		//	bound and the type is DBTYPE_BYTES.

		// REVIEW: There was another entry of code here with LENGTH, NO VALUE,
		//	and status was not DBSTATUS_S_ISNULL.  May need to regenerate that
			if (dbStat == DBSTATUS_S_OK)
			{
				if (!(pBindCur->dwPart & DBPART_VALUE) ||
					((pBindCur->dwPart & DBPART_LENGTH) && (pBindCur->wType == DBTYPE_BYTES)))
				{
					// Can't set non-null columns w/o a value part
					if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
						pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
					{
						pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings,
							rgColumns.GetData(), DBREASON_COLUMN_SET, DBEVENTPHASE_FAILEDTODO, 
							TRUE);
					}

					bFailed = true;
					* ((DBSTATUS*)((BYTE*)(pSrcData) + pBindCur->obStatus)) = DBSTATUS_E_UNAVAILABLE;
					continue;
				}
			}

			switch (dbStat) {
			case DBSTATUS_S_ISNULL:
				{
					if (!(pColCur->dwFlags & DBCOLUMNFLAGS_ISNULLABLE) ||
						FAILED(pT->SetDBStatus(&dbStat, pRow, pColCur)))
					{
						if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
							pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
						{
							pT->Fire_OnFieldChange(pT, hNotifyRow, 
								pBinding->cBindings, rgColumns.GetData(), 
								DBREASON_COLUMN_SET, DBEVENTPHASE_FAILEDTODO, 
								TRUE);
						}

					// Special processing for attempting to write, read-only columns
						if (!(pColCur->dwFlags & DBCOLUMNFLAGS_ISNULLABLE))
							*((DBSTATUS *)((BYTE *)(pSrcData) + pBindCur->obStatus)) = DBSTATUS_E_INTEGRITYVIOLATION;

						bFailed = true;
					}
					else {
						if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
							pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
						{
							pT->Fire_OnFieldChange(pT, hNotifyRow, 1, &iBind, 
								DBREASON_COLUMN_SET, DBEVENTPHASE_DIDEVENT, TRUE);
						}

						bSucceeded = true;
						dbStat = DBSTATUS_S_OK;
						if (pBindCur->dwPart & DBPART_VALUE)
							*pDstTemp = NULL;
					}
					continue;
				}
				break;

			case DBSTATUS_S_DEFAULT:
			case DBSTATUS_S_IGNORE:
				{
				HRESULT hrStatus = pT->SetDBStatus(&dbStat, pRow, pColCur);
				
					*((DBSTATUS*)((BYTE*)(pSrcData) + pBindCur->obStatus)) = dbStat;

					if (FAILED(hrStatus))
					{
						if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
							pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
						{
							pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
								rgColumns.GetData(), DBREASON_COLUMN_SET, 
								DBEVENTPHASE_FAILEDTODO, TRUE);
						}

					// Note, status should be set by SetDBStatus
						bFailed = true;
					}
					else {
						if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
							pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
						{
							pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
								rgColumns.GetData(), DBREASON_COLUMN_SET, 
								DBEVENTPHASE_DIDEVENT, TRUE);
						}
						bSucceeded = true;
					}
					continue;
				}
				break;

			case DBSTATUS_S_OK:
			// Still call SetDBStatus here as they may have locks on 
			// integrity contstraints to observe
				if (FAILED(pT->SetDBStatus(&dbStat, pRow, pColCur)))
				{
					if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
						pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
					{
						pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
							rgColumns.GetData(), DBREASON_COLUMN_SET, 
							DBEVENTPHASE_FAILEDTODO, TRUE);
					}

					bFailed = true;
					*((DBSTATUS *)((BYTE*)(pSrcData) + pBindCur->obStatus)) = dbStat;
					continue;
				}
				break;

			default:
				{
					*((DBSTATUS*)((BYTE*)(pSrcData) + pBindCur->obStatus)) = DBSTATUS_E_BADSTATUS;
					if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
						pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
					{
						pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
							rgColumns.GetData(), DBREASON_COLUMN_SET, 
							DBEVENTPHASE_FAILEDTODO, TRUE);
					}
					bFailed = true;
					continue;
				}
				break;
			}
		}

	// Determine sizes of input and output columns
	DBLENGTH cbCol = 0;
	DBLENGTH cbDst = pColCur->ulColumnSize;

		switch (pColCur->wType)	{
		case DBTYPE_STR:
			{
				// Use the length field when setting data 
				if (pBindCur->dwPart & DBPART_LENGTH)
					cbCol = * ((DBLENGTH*)((BYTE*)(pSrcData) + pBindCur->obLength));
				else
					cbCol = strlen((LPSTR)(pSrcTemp));	// was cbDst
				
				if (cbCol >= cbDst)
				{
					if (cbCol > (cbDst + 1)) // over maximum case
					{
						if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
							pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
						{
							pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
								rgColumns.GetData(), DBREASON_COLUMN_SET, 
								DBEVENTPHASE_FAILEDTODO, TRUE);
						}

						bFailed = true;
						if (pBindCur->dwPart & DBPART_STATUS)
							*((DBSTATUS*)((BYTE*)(pSrcData) + pBindCur->obStatus)) = DBSTATUS_E_CANTCONVERTVALUE;
						continue;
					}
				}
				cbCol = cbDst;	// Leave room for NULL term. need to copy for WSTR
			}
			break;

		case DBTYPE_WSTR:
		case DBTYPE_BSTR:
			{
				if (pBindCur->dwPart & DBPART_LENGTH)
					cbCol = *((DBLENGTH *)((BYTE *)(pSrcData) + pBindCur->obLength)); 
				else
					cbCol = wcslen((LPWSTR)(pSrcData)) * sizeof(WCHAR);

				if (cbCol >= cbDst)
				{
					if (cbCol > (cbDst + 1)) // over maximum case
					{
						if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
							pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
						{
							pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
								rgColumns.GetData(), DBREASON_COLUMN_SET, 
								DBEVENTPHASE_FAILEDTODO, TRUE);
						}

						bFailed = true;
						if (pBindCur->dwPart & DBPART_STATUS)
							*((DBSTATUS *)((BYTE *)(pSrcData) + pBindCur->obStatus)) = DBSTATUS_E_CANTCONVERTVALUE;
						continue;
					}
				}
				cbCol = cbDst;	// Leave room for NULL term. need to copy for WSTR
			}
			break;

		case DBTYPE_BYTES:
			{
				if (pBindCur->dwPart & DBPART_LENGTH)
					cbCol = * ((DBLENGTH *)((BYTE*)(pSrcData) + pBindCur->obLength)); 
				else {
					if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
						pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
					{
						pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
							rgColumns.GetData(), DBREASON_COLUMN_SET, 
							DBEVENTPHASE_FAILEDTODO, TRUE);
					}

				// If no length part is bound for DBTYPE_BYTES, it is an error
					bFailed = true;
					continue;
				}

				if (cbCol >= cbDst)
					cbCol = cbDst;	// Leave room for NULL term. need to copy for WSTR
			}
			break;

		default:
			cbDst = pColCur->ulColumnSize;
			break;
		}

	// Handle cases where we have provider owned memory.  Note, these should be
	// with DBTYPE_BYREF (otherwise, it doesn't make sense).
		if (pBindCur->dwPart & DBPART_VALUE)
		{
			if (pBindCur->dwMemOwner == DBMEMOWNER_PROVIDEROWNED 
				&& pBindCur->wType & DBTYPE_BYREF)
			{
				* (BYTE**)pDstTemp = pSrcTemp;
			}
			else
			{
				ATLASSERT(pT->m_spConvert != NULL);
				hr = pT->m_spConvert->DataConvert(pColCur->wType, pBindCur->wType, 
						cbCol, &cbDst, pSrcTemp, pDstTemp, pBindCur->cbMaxLen, 
						dbStat, &dbStat, pBindCur->bPrecision, pBindCur->bScale, 0);
			}
		}
		if (pBindCur->dwPart & DBPART_LENGTH)
			*((DBLENGTH *)((BYTE *)(pSrcData) + pBindCur->obLength)) = cbDst;

		if (pBindCur->dwPart & DBPART_STATUS)
			*((DBSTATUS *)((BYTE *)(pSrcData) + pBindCur->obStatus)) = dbStat; 

		if (FAILED(hr)) {
			if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
				pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
			{
				pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
					rgColumns.GetData(), DBREASON_COLUMN_SET, 
					DBEVENTPHASE_FAILEDTODO, TRUE);
			}
			bFailed = true;
		}
		else {
			bSucceeded = true;
		}
	}

	// Return error codes to the consumer
	if (bFailed)
	{
//		SendColumnSetFailureNotification( pT, hNotifyRow, pBinding, rgColumns );
		SendRowsFirstChangeFailureNotification(pT, pRow, &hNotifyRow, bDeferred);
		return (bSucceeded != false) ? DB_S_ERRORSOCCURRED : DB_E_ERRORSOCCURRED;
	}
	else {
		if (/* pRow->m_status != DBPENDINGSTATUS_NEW && */
			pRow->m_status !=(DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED))
		{
			pT->Fire_OnFieldChange(pT, hNotifyRow, pBinding->cBindings, 
				rgColumns.GetData(), DBREASON_COLUMN_SET, 
				DBEVENTPHASE_DIDEVENT, TRUE);
		}
		return hr;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für writable Rowsets
template <class T, class Storage, 
		  class BaseInterface = IRowsetChange,
		  class RowClass = CSimpleWritableRow, 
		  class MapClass = CSimpleMap<RowClass::KeyType, RowClass *> >
class ATL_NO_VTABLE IRowsetChangeImpl : 
	public BaseInterface
{
public:
	// IRowsetChange Methods
	STDMETHOD(DeleteRows)(HCHAPTER /*hReserved*/, DBCOUNTITEM cRows, const HROW rghRows[], DBROWSTATUS rgRowStatus[])
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetChangeImpl::DeleteRows"));

	T *pT = static_cast<T *>(this);
	T::ObjectLock lock(pT);

	// Check to see if someone is in an event handler.  If we do, then 
	// we should return DB_E_NOTREENTRANT.
		if (!pT->IncrementMutex())
			return DB_E_NOTREENTRANT;
		else
			pT->DecrementMutex();

	// Check to see if the DBPROP_UPDATABILITY value DBPROPVAL_UP_CHANGE
	// is set.  If not, then this method should return DB_E_NOTSUPPORTED.
	BOOL bSuccess = false;
	BOOL bFailed = false;
	CComVariant varChange;
	HRESULT hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_UPDATABILITY, &varChange);

		if (!(varChange.iVal & DBPROPVAL_UP_DELETE))
			return DB_E_NOTSUPPORTED;

	// NO-OP if cRows is zero
		if (cRows == 0)
			return S_OK;

		if (rghRows == NULL && cRows >= 1)
			return E_INVALIDARG;

	// Determine if we're in immediate or deferred mode
	CComVariant varDeferred;
	bool bDeferred;

		hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_IRowsetUpdate, &varDeferred);
		bDeferred = (SUCCEEDED(hr) && VARIANT_TRUE == varDeferred.boolVal) ? true : false;

	// Loop through and delete rows
		for (DBCOUNTITEM l = 0; l < cRows; l++) {
		HROW hRow = rghRows[l];
		RowClass *pRow;
		DBROWSTATUS rowStat = DBROWSTATUS_S_OK;

		// Handle events
		HRESULT hrNotify = pT->Fire_OnRowChange(pT, 1, &rghRows[l],	DBREASON_ROW_DELETE, DBEVENTPHASE_OKTODO, FALSE); 

			if (S_FALSE == hrNotify)
			{
				bFailed |= true;
				if (rgRowStatus != NULL)
					rgRowStatus[l] = DBROWSTATUS_E_CANCELED;
				continue;
			}
			else {
				hrNotify = pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_ABOUTTODO, FALSE);
				if (S_FALSE == hrNotify)
				{
					bFailed |= true;
					if (rgRowStatus != NULL)
						rgRowStatus[l] = DBROWSTATUS_E_CANCELED;

					continue;
				}
			}

		// Send sync after now as it gets tricky to replace stuff once 
		// we're in the method.
			hrNotify = pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_SYNCHAFTER, FALSE);
			if (S_FALSE == hrNotify)
			{
				bFailed |= true;
				if (rgRowStatus != NULL)
					rgRowStatus[l] = DBROWSTATUS_E_CANCELED;
				continue;
			}

		// Attempt to locate the row in our map
		bool bFound = pT->m_rgRowHandles.Lookup(hRow, pRow);

			if (!bFound || pRow == NULL)
			{
				bFailed |= true;
				if (rgRowStatus != NULL)
					rgRowStatus[l] = DBROWSTATUS_E_INVALID;
				continue;
			}

		// Check if the row has already been deleted.  Note, we
		// use DBPENDINGSTATUS_DELETED in the immediate case as
		// well.
			if (pRow->m_status == DBPENDINGSTATUS_DELETED) 
				pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_FAILEDTODO, TRUE);

				if (rgRowStatus != NULL)
					rgRowStatus[l] = DBROWSTATUS_E_DELETED;
				bFailed |= true;
				continue;
			}

		// Delete the row
			if (bDeferred)
			{
			// Mark the row as deleted but do not remove it until 
			// IRowsetUpdate::Update is called.
				if (pRow->m_status != DBPENDINGSTATUS_INVALIDROW)
				{
					pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_DIDEVENT, FALSE);
					bSuccess |= true;
					rowStat = DBROWSTATUS_S_OK;
				}
				else {
					pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_FAILEDTODO, FALSE);
					bFailed |= true;

				// unsigned high bit signified neg. number
					if (pRow->m_dwRef & 0x80000000)		
						rowStat = DBROWSTATUS_E_INVALID;
					else
						rowStat = DBROWSTATUS_E_DELETED;
				}
			}
			else {
			// Remove the m_rgRowData and m_rgRowLink entries.  The 
			// HROW will be released in IRowset::ReleaseRows.  
			// Remove the link by NULLing out the pointer
//				if(!pT->m_rgRowData.RemoveAt(pRow->m_iRowset))
				if (pRow->m_iRowset < 0 || pRow->m_iRowset >= pT->m_rgRowData.GetCount())
				{
					pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_FAILEDTODO, FALSE);
					rowStat = DBROWSTATUS_E_INVALID;
					bFailed |= true;
				}
				else {
					pT->m_rgRowData.RemoveAt(pRow->m_iRowset);

				// Perform the actual delete of the row.  Send notificaitons
				// to inform the consumer of the change.

				// Need to update any outstanding pRow->m_iRowset
				// variables
					for (int i = 0; i < m_rgRowHandles.GetSize(); i++)
					RowClass* pCheckRow = m_rgRowHandles.GetValueAt(i);

						if (pCheckRow != NULL && pCheckRow->m_iRowset > pRow->m_iRowset)
							pCheckRow->m_iRowset--;
					}

					if (FAILED(pT->FlushData(rghRows[l], NULL))) {
						pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_FAILEDTODO, FALSE);
						bFailed |= true;
						rowStat = DBROWSTATUS_E_FAIL;
					}
					else {
					// Send DIDEVENT
						pT->Fire_OnRowChange(pT, 1, &rghRows[l], DBREASON_ROW_DELETE, DBEVENTPHASE_DIDEVENT, FALSE);
						rowStat = DBROWSTATUS_S_OK;
						bSuccess |= true;
					}
				}
			}

		// We use the status even in immediate mode to determine if a
		// row has been deleted from the cache but not release
			if (pRow->m_status == DBPENDINGSTATUS_NEW)
				pRow->m_status = DBPENDINGSTATUS_INVALIDROW;
			else {
				if (pRow->m_status != DBPENDINGSTATUS_INVALIDROW)
					pRow->m_status = DBPENDINGSTATUS_DELETED;
			}

			if (rgRowStatus != NULL)
				rgRowStatus[l] = rowStat;
		}

		hr = S_OK;
		if (bFailed)
			hr = bSuccess ? DB_S_ERRORSOCCURRED : DB_E_ERRORSOCCURRED;

		return hr;
	}

	STDMETHOD(SetData)(HROW hRow, HACCESSOR hAccessor, void* pSrcData)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetChangeImpl::SetData\n"));

	T *pT = static_cast<T *>(this);
	T::ObjectLock lock(pT);

	// Check to see if someone is in an event handler.  If we do, then 
	// we should return DB_E_NOTREENTRANT.
		if (!pT->IncrementMutex())
			return DB_E_NOTREENTRANT;
		else
			pT->DecrementMutex();

	// Check to see if the DBPROP_UPDATABILITY value DBPROPVAL_UP_CHANGE
	// is set.  If not, then this method should return DB_E_NOTSUPPORTED.
	RowClass *pRow;
	CComVariant varChange;
	HRESULT hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_UPDATABILITY, &varChange);

		if (!(varChange.iVal & DBPROPVAL_UP_CHANGE))
			return DB_E_NOTSUPPORTED;
		
		if (hRow == NULL)
			return DB_E_BADROWHANDLE;
		if (NULL ==(pRow = pT->m_rgRowHandles.Lookup(hRow)))
			return DB_E_BADROWHANDLE;
		if (hRow == NULL)
			return DB_E_BADROWHANDLE;
		hr = TransferData<T, RowClass, MapClass>(pT, pSrcData, pRow, &(pT->m_rgRowHandles), hAccessor);
		if (FAILED(hr))
			return hr;

	// Flush Users Data
		HRESULT hrFlush = pT->FlushData(hRow, hAccessor);

		if (SUCCEEDED(hrFlush))
			return hr;	// note: we could have DB_S_ERRORSOCCURRED from TransferData
		else
			return hrFlush;
	}

	STDMETHOD(InsertRow)(HCHAPTER /*hReserved*/, HACCESSOR hAccessor, 
					void* pData, HROW* phRow)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetChangeImpl::InsertRow\n"));

	T *pT = static_cast<T *>(this);
	T::ObjectLock lock(pT);

	HRESULT hrNotify = S_OK;	// Used for responses to notifications

	// Check to see if someone is in an event handler.  If we do, then 
	// we should return DB_E_NOTREENTRANT.
		if (!pT->IncrementMutex()) {
		// Note, we can't set this above because we may inadvertantly
		// step on someone elses *phRow
			if (phRow != NULL)
				*phRow = NULL;
			return DB_E_NOTREENTRANT;
		}
		else
			pT->DecrementMutex();

	// Check to see if the DBPROP_UPDATABILITY value DBPROPVAL_UP_CHANGE
	// is set.  If not, then this method should return DB_E_NOTSUPPORTED.
	CComVariant varChange;
	HRESULT hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_UPDATABILITY, &varChange);

		if (!(varChange.iVal & DBPROPVAL_UP_INSERT))
			return DB_E_NOTSUPPORTED;

		if (phRow != NULL)
			*phRow = NULL;

	// validate that the hAccessor is valid
	T::_BindType* pBinding = pT->m_rgBindings.Lookup((INT_PTR)hAccessor);

		if (pBinding == NULL)
			return DB_E_BADACCESSORHANDLE;

	// validate parameters
	if (pData == NULL && pBinding->cBindings != 0)
		return E_INVALIDARG;

	// Check to see if DBPROP_CANHOLDROWS is set to false.  In this case,
	// return a DB_E_ROWSNOTRELEASED if there are any pending changes.
	CComVariant varHoldRows;

		hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_CANHOLDROWS, &varHoldRows);

		if (FAILED(hr) || varHoldRows.boolVal == VARIANT_FALSE)	{
			if (pT->m_rgRowHandles.GetCount() > 0) {
				for (int i = 0; i < pT->m_rgRowHandles.GetSize(); i++) {
				RowClass* pCheckRow = pT->m_rgRowHandles.GetValueAt(i);
				
					if (pCheckRow != NULL && pCheckRow->m_status != DBPENDINGSTATUS_UNCHANGED)
						return DB_E_ROWSNOTRELEASED;
				}
			}
		}

	// REVIEW:  We should check DBPROP_IMMOBILEROWS and then call an ordering routine in the user's code.
	// Create a row and place into m_rgRowData
	Storage newRow;		// Create an instance of the users data
	CComVariant var;
	HRESULT hrProps = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_BOOKMARKS, &var);

		if (SUCCEEDED(hrProps) && var.boolVal != VARIANT_FALSE)	{
		DBORDINAL cCols;
		ATLCOLUMNINFO* pInfo = T::GetColumnInfo(pT, &cCols);

			ATLASSERT(pInfo != NULL);
			for (DBORDINAL i = 0; i < cCols; i++) {
				if (pInfo[i].iOrdinal == 0)	{
					switch (pInfo[i].wType)
					{
					case DBTYPE_BYTES: // review: check the line below (used to be DWORD instead of DBBKMARK)
						*((DBBKMARK *)(&newRow + pInfo[i].cbOffset)) = (ULONG_PTR)(pT->m_rgRowData.GetCount() + 1);
						break;

					default:
						_ASSERTE(FALSE);
						break
					};
				}
			}
		}

	// Call CreateRow to make a new hRow
	HROW hInsertedRow = NULL;
	DBCOUNTITEM ulRowsObtained = 0;
	size_t lSize = pT->m_rgRowData.GetCount();

		hr = pT->CreateRow ((LONG_PTR)lSize, ulRowsObtained, &hInsertedRow);
		
		if (FAILED(hr))	
			return hr;

		hrNotify = pT->Fire_OnRowChange(pT, 1, &hInsertedRow, DBREASON_ROW_INSERT,
			DBEVENTPHASE_OKTODO, FALSE);
		if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
		{
			pT->m_rgRowHandles.RemoveKey((RowClass::KeyType)hInsertedRow);
			return DB_E_CANCELED;
		}

		hrNotify = pT->Fire_OnRowChange(pT, 1, &hInsertedRow, DBREASON_ROW_INSERT,
			DBEVENTPHASE_ABOUTTODO, FALSE);
		if ((hrNotify != S_OK) && (hrNotify != E_FAIL))
		{
			pT->m_rgRowHandles.RemoveKey((RowClass::KeyType)hInsertedRow);
			return DB_E_CANCELED;
		}

	// Add in the storage and linkeage for the row 
	CComVariant varOrderedInsert;

	// REVIEW: Need to determine if we want ordered insertions
	bool bOrderedInsert;

		hr = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_IMMOBILEROWS, &varOrderedInsert);
		bOrderedInsert = (FAILED(hr) || varOrderedInsert.boolVal != VARIANT_FALSE) ? false : true;

		if (!pT->m_rgRowData.Add(newRow)) {
			ATLTRACE(atlTraceDBProvider, 0, _T("Failed to add record Out of Memory"));
			return E_OUTOFMEMORY;
		}

	// Set the inserted row's status to DBPENDINGSTATUS_NEW if it is deferred.
	// This will prevent a spurious Notification for ROW_FIRSTCHANGE from 
	// firing in IRowsetUpdateImpl::SetData.
	CComVariant varDeferred;
	HRESULT hrDeferred = pT->GetPropValue(&DBPROPSET_ROWSET, DBPROP_IRowsetUpdate, &varDeferred);
	bool bDeferred = (FAILED(hrDeferred) || varDeferred.boolVal == VARIANT_FALSE) ? false : true;
	RowClass* pRow = pT->m_rgRowHandles.Lookup(hInsertedRow);

		ATLASSERT(pRow != NULL);

	// Set the status to NEW + UNCHANGED so we don't generate COLUMN_SET or 
	// FIRSTCHANGE events in SetData. We'll switch it back to zero after the 
	// operation.
		pRow->m_status = DBPENDINGSTATUS_NEW | DBPENDINGSTATUS_UNCHANGED;

	// Call SetData, if necessary
		if (pData != NULL) {
			hr = SetData(hInsertedRow, hAccessor, pData);
			if (FAILED(hr))	{
				pT->Fire_OnRowChange(pT, 1, &hInsertedRow, DBREASON_ROW_INSERT,
					DBEVENTPHASE_FAILEDTODO, TRUE);
			}
		}

		if (!bDeferred)
			pRow->m_status = 0;
		else
			pRow->m_status = DBPENDINGSTATUS_NEW;

		hrNotify = pT->Fire_OnRowChange(pT, 1, &hInsertedRow, DBREASON_ROW_INSERT,
			DBEVENTPHASE_SYNCHAFTER, FALSE);
		if ((hrNotify != S_OK) && (hrNotify != E_FAIL)) {
		// Remove storage
		RowClass* pRow = pT->m_rgRowHandles.Lookup(hInsertedRow, pRow);

			ATLASSERT(pRow != NULL);
			pT->m_rgRowData.RemoveAt(pRow->m_iRowset);

		// Remove Handle
			pT->m_rgRowHandles.RemoveKey((RowClass::KeyType)hInsertedRow);
			return DB_E_CANCELED;
		}

		pT->Fire_OnRowChange(pT, 1, &hInsertedRow, DBREASON_ROW_INSERT,
			DBEVENTPHASE_DIDEVENT, TRUE);

		if (phRow != NULL && SUCCEEDED(hr))
			*phRow = hInsertedRow;
				
		return hr;
 	}        

// Callbacks to Provider
	HRESULT FlushData(HROW, HACCESSOR)
	{
		return S_OK;	// The provider overrides this function to commit data to its store
	}
};

#endif // _ATL_VER < 0x0700

#endif // !defined(_IROWSETCHANGEIMPL_H__B6971F12_688C_46C6_AD0B_5C693AF3627E__INCLUDED_)
