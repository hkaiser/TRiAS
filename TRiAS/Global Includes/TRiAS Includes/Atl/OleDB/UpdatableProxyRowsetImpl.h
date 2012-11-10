// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 21:36:44 
//
// @doc
// @module UpdatableProxyRowsetImpl.h | Declaration of the <c CUpdatableProxyRowsetImpl> class

#if !defined(_UPDATABLEPROXYROWSETIMPL_H__C4B0034E_40D6_4C34_B643_074C9FD476C5__INCLUDED_)
#define _UPDATABLEPROXYROWSETIMPL_H__C4B0034E_40D6_4C34_B643_074C9FD476C5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDB/ProxyRowsetImpl.h>
#include <Atl/OleDB/IRowsetChangeImpl.h>
#include <Atl/OleDB/IColumnsRowsetImpl.h>

///////////////////////////////////////////////////////////////////////////////
// CUpdatableProxyRowsetImpl
// An ATL OLE DB Provider template that represents an updatable Rowset which 
// expects the derived class to be responsible for storing the rowset data 
// within it (rather than working with the Storage and ArrayType classes). 
template<class DataClass, class T, class CreatorClass, 
	class Storage = CRowsetStorageProxy<T>, 
	class ArrayType = CRowsetArrayTypeProxy<T, Storage>,
	class RowClass = CSimpleRow,
	class RowsetInterface = IRowsetImpl<T, IRowset, RowClass> >
class CUpdatableProxyRowsetImpl :
	public CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>,
	public IRowsetChangeImpl<T, Storage>,
	public IConnectionPointContainerImpl<CUpdatableProxyRowsetImpl>,
	public IColumnsRowsetImpl<T, CreatorClass>
{
public:
	friend Storage;
	friend ArrayType;

	typedef CreatorClass::_PropClass _PropClass;
	typedef CUpdatableProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface> UpdatableProxyRowsetClass;

	BEGIN_COM_MAP(CUpdatableProxyRowsetImpl)
		COM_INTERFACE_ENTRY(IRowsetChange)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IColumnsRowset)
		COM_INTERFACE_ENTRY_CHAIN(ProxyRowsetClass)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CUpdatableProxyRowsetImpl)
		CONNECTION_POINT_ENTRY(IID_IRowsetNotify)
	END_CONNECTION_POINT_MAP()

// Construction and destruction...
	CUpdatableProxyRowsetImpl() {}
	~CUpdatableProxyRowsetImpl() {}

	HRESULT SetDataHelper(HROW hRow, HACCESSOR hAccessor, void *pSrcData, bool bSendNotifications)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "CUpdatableRowsetImpl::SetDataHelper() - hRow = %d\n", hRow);
 
	RowClass *pRow = 0; 

		if (hRow == 0 || NULL == (pRow = m_rgRowHandles.Lookup((RowClass::KeyType)hRow))) {
			ATLTRACE2(atlTraceDBProvider, 0, "CUpdatableRowsetImpl::SetDataHelper - Error - Bad row handle\n");
			return DB_E_BADROWHANDLE;
		}

	_BindType *pBinding = m_rgBindings.Lookup((int)hAccessor);

		if (pBinding == NULL)
			return DB_E_BADACCESSORHANDLE;

	// convert the pBinding structure into an array of ULONG of column ordinals
	ULONG *rgColumns = 0;
	CAutoMemRelease<ULONG> crapHelper(rgColumns);
		
		if (bSendNotifications) {
			rgColumns = new ULONG[pBinding->cBindings];

			for (size_t i = 0; i < pBinding->cBindings; i++)
				rgColumns[i] = pBinding->pBindings[i].iOrdinal;

			if (!SendPreSetDataNotifications(hRow, pBinding->cBindings, rgColumns)) {
				ATLTRACE2(atlTraceDBProvider, 0, "CUpdatableRowsetImpl::SetDataHelper - cancelled\n", pBinding->cBindings);
				return DB_E_CANCELED;
			}
		}

	HRESULT hr = S_OK;

		for (ULONG iBind = 0; SUCCEEDED(hr) && iBind < pBinding->cBindings; ++iBind) {
		DBBINDING* pBindCur = &(pBinding->pBindings[iBind]);

			ATLTRACE2(atlTraceDBProvider, 0, "CUpdatableRowsetImpl::SetDataHelper - Bindings for column ordinal %d\n", pBindCur->iOrdinal);
			if (pBindCur->iOrdinal > GetNumColumns()) {
				ATLTRACE2(atlTraceDBProvider, 0, "CUpdatableRowsetImpl::SetDataHelper - Error - bad ordinal\n");
				return DB_E_BADORDINAL;
			}

			if (pBindCur->dwMemOwner == DBMEMOWNER_PROVIDEROWNED) {
				ATLTRACE2(atlTraceDBProvider, 0, "CUpdatableRowsetImpl::SetDataHelper - Error - we dont support provider owned memory\n");
				return E_FAIL;
			}

		DBSTATUS dbStat = DBSTATUS_S_OK; 
		ULONG cbDst = pBindCur->cbMaxLen;
			
		// This isn't relevant for strings as they can grow in size...
		// TODO: surely we should be using the size of the data as specified in the binding here?
		ULONG cbCol; 
		DBTYPE colType; 
		void *pData = 0;
		bool bUpdatable = false;

			InternalGetColumnData(pRow->m_iRowset, pBindCur->iOrdinal, colType, cbCol, pData, bUpdatable); 
			if (pBindCur->dwPart & DBPART_VALUE) {
			// TODO: - get this to allocate the buffer as needed and make it the right size...
			// We could write straight into the memory of the derived class if we like (well
			// for stuff that's not translated or variable length...

			const size_t cBufferSize = 256;
			BYTE horribleBuffer[cBufferSize];
			BYTE *pSrcTemp = (BYTE*)pSrcData + pBindCur->obValue;
			BYTE *pDstTemp = horribleBuffer;

				if (bUpdatable) 
					pDstTemp = (BYTE *)pData;

				hr = m_spConvert->DataConvert(
						pBindCur->wType,				// the source type
						colType,						// the required type
						cbCol,							// length of column data
						&cbDst, 						// length of data after conversion
						pSrcTemp,						// pointer to the column data
						pDstTemp,						// pointer to where to put it...
						cBufferSize,					// max length of destination buffer
						dbStat, 						// source status
						&dbStat,						// dest status
						pBindCur->bPrecision,			// precision
						pBindCur->bScale,				// scale
						0); 							// flags - none supplied

				if (!bUpdatable)
					InternalUpdateColumn(pRow->m_iRowset, pBindCur->iOrdinal, pDstTemp);
			}
		}
		
		if (bSendNotifications) {
			if (SUCCEEDED(hr))
				SendPostSetDataNotifications(hRow, pBinding->cBindings, rgColumns);
			else
				SendFailedSetDataNotifications(hRow, pBinding->cBindings, rgColumns);
		}
		return hr;
	}
	
protected:
	virtual void UpdateColumn(size_t row, size_t column, void *pData) = 0;

private:
	void InternalUpdateColumn(size_t row, size_t column, void *pData)
	{
		ATLASSERT(column != 0); 				// Nobody should ever try to write to the bookmark column!
		UpdateColumn(row, column - 1, pData);
	}
};

#endif // !defined(_UPDATABLEPROXYROWSETIMPL_H__C4B0034E_40D6_4C34_B643_074C9FD476C5__INCLUDED_)
