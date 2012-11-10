// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.06.2001 14:13:17 
//
// @doc
// @module IRowsetIndexImpl.h | Declaration of the <c IRowsetIndexImpl> class

#if !defined(_IROWSETINDEXIMPL_H__8F4E1149_5E74_4C86_A163_0C6214BEE778__INCLUDED_)
#define _IROWSETINDEXIMPL_H__8F4E1149_5E74_4C86_A163_0C6214BEE778__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDB/DBId.h>

///////////////////////////////////////////////////////////////////////////////
// Implementation of IRowsetIndex interface
template<typename T>
class ATL_NO_VTABLE IRowsetIndexImpl :
	public IRowsetIndex
{
public:
	STDMETHODIMP GetIndexInfo(
		ULONG *pcKeyColumns, DBINDEXCOLUMNDESC **prgIndexColumnDesc, 
		ULONG *pcPropertySets, DBPROPSET **prgPropertySets)
	{
		ATLTRACE2(atlTraceDBProvider, 2, "IRowsetIndexImpl::GetIndexInfo\n");
	
	// Indexinfos liefern
		if (NULL == pcKeyColumns || NULL == prgIndexColumnDesc)
			return E_INVALIDARG;

		*pcKeyColumns = 0;
		*prgIndexColumnDesc = NULL;

	DBINDEXCOLUMNDESC *pIndexColumnDesc = (DBINDEXCOLUMNDESC *)CoTaskMemAlloc(sizeof(DBINDEXCOLUMNDESC));
	DBID *pDbId = (DBID *)CoTaskMemAlloc(sizeof(DBID));

	CAutoMemRelease<DBINDEXCOLUMNDESC, CComFree<DBINDEXCOLUMNDESC> > amr (pIndexColumnDesc);
	CAutoMemRelease<DBID, CComFree<DBID> > amrId (pDbId);

		if (NULL == pIndexColumnDesc || NULL == pDbId) 
			return E_OUTOFMEMORY;

		RETURN_ERROR(CDBIDOps::CopyDBIDs(pDbId, &m_IdxId));
		pIndexColumnDesc -> pColumnID = pDbId;
		pIndexColumnDesc -> eIndexColOrder = DBINDEX_COL_ORDER_ASC;

	// Properties liefern
	const ULONG cPropertyIDSets = 1;
	DBPROPIDSET setIdxProp[cPropertyIDSets];

		setIdxProp[0].cPropertyIDs = 0;
		setIdxProp[0].rgPropertyIDs = NULL;
		setIdxProp[0].guidPropertySet = DBPROPSET_INDEX;

	T *pT = static_cast<T *>(this);
	HRESULT hr = pT->GetPropertiesArgChk(cPropertyIDSets, setIdxProp, pcPropertySets, prgPropertySets);
	
		if(SUCCEEDED(hr)) {
			// MRD - Updated to support custom property sets
			const GUID* pGroup[1];
			pGroup[0] = &DBPROPSET_INDEX;
			const GUID **ppGuid = NULL;
			ULONG ulSets = pT->GetSupportedSetsInGroup(1, pGroup, &ppGuid);
			hr = pT->GetProperties(cPropertyIDSets,	setIdxProp, pcPropertySets, prgPropertySets, ulSets, ppGuid);
		}

	// abschlieﬂende Bereinigung
		if (SUCCEEDED(hr)) {
			*pcKeyColumns = 1;
			*prgIndexColumnDesc = amr.Detach();
			amrId.Detach();
		} 
		return hr;
	}
	STDMETHODIMP Seek(HACCESSOR hAccessor, ULONG cKeyValues, void *pData, DBSEEK dwSeekOptions)
	{
		ATLTRACE2(atlTraceDBProvider, 2, "IRowsetIndexImpl::Seek\n");

		return E_NOTIMPL;
	}
	STDMETHODIMP SetRange(HACCESSOR hAccessor, ULONG cStartKeyColumns, void *pStartData, ULONG cEndKeyColumns, void *pEndData, DBRANGE dwRangeOptions)
	{
		ATLTRACE2(atlTraceDBProvider, 2, "IRowsetIndexImpl::SetRange\n");

		return E_NOTIMPL;
	}

// support functions
	HRESULT SetIndex (DBID *pIdTable, DBID *pIdIndex)
	{
		if (NULL == pIdTable || NULL == pIdIndex)
			return E_INVALIDARG;

		_ASSERTE(S_OK == CDBIDOps::IsValidDBID(pIdTable));
		_ASSERTE(S_OK == CDBIDOps::IsValidDBID(pIdIndex));

		RETURN_ERROR(CDBIDOps::CopyDBIDs(&m_TblId, pIdTable));
		RETURN_ERROR(CDBIDOps::CopyDBIDs(&m_IdxId, pIdIndex));
		return S_OK;
	}

private:
	CDBID m_TblId;
	CDBID m_IdxId;
};

#endif // !defined(_IROWSETINDEXIMPL_H__8F4E1149_5E74_4C86_A163_0C6214BEE778__INCLUDED_)
