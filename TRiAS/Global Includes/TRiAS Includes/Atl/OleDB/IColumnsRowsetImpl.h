// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 19:47:35 
//
// @doc
// @module IColumnsRowsetImpl.h | Declaration of the <c IColumnsRowsetImpl> class

#if !defined(_ICOLUMNSROWSETIMPL_H__B453ABC3_3C01_4B96_A0E3_FA8620C6EC2A__INCLUDED_)
#define _ICOLUMNSROWSETIMPL_H__B453ABC3_3C01_4B96_A0E3_FA8620C6EC2A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#define PROVIDER_COLUMN_ENTRY_DBID(name, dbid, ordinal, member) \
{ \
	(LPOLESTR)OLESTR(name), \
	(ITypeInfo*)NULL, \
	(ULONG)ordinal, \
	DBCOLUMNFLAGS_ISFIXEDLENGTH, \
	(ULONG)sizeof(((_Class*)0)->member), \
	_GetOleDBType(((_Class*)0)->member), \
	(BYTE)0, \
	(BYTE)0, \
	{ \
		EXPANDGUID(dbid.uGuid.guid), \
		(DWORD)dbid.eKind, \
		(LPOLESTR)dbid.uName.ulPropid\
	}, \
	offsetof(_Class, member) \
},

class CColumnsRowsetRow
{
public:
	WCHAR	 m_DBCOLUMN_IDNAME[129];
	GUID	 m_DBCOLUMN_GUID;
	ULONG	 m_DBCOLUMN_PROPID;
	WCHAR	 m_DBCOLUMN_NAME[129];
	ULONG	 m_DBCOLUMN_NUMBER;
	USHORT	 m_DBCOLUMN_TYPE;
	IUnknown *m_DBCOLUMN_TYPEINFO;
	ULONG	 m_DBCOLUMN_COLUMNSIZE;
	USHORT	 m_DBCOLUMN_PRECISION;
	USHORT	 m_DBCOLUMN_SCALE;
	ULONG	 m_DBCOLUMN_FLAGS;
	WCHAR	 m_DBCOLUMN_BASECOLUMNNAME[129];
	WCHAR	 m_DBCOLUMN_BASETABLENAME[129];
	BOOL	 m_DBCOLUMN_KEYCOLUMN;

#if defined(_USE_OGC_OPTIONAL_COLUMNS)
// OGC specifics
	ULONG m_nGeomType;
	ULONG m_nSpatialRefId;
	WCHAR m_pszSpatialRefSystem[2000];
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)

	CColumnsRowsetRow()
	{
		ClearMembers();
	}

	void ClearMembers()
	{
		m_DBCOLUMN_IDNAME[0] = NULL;
		m_DBCOLUMN_GUID = GUID_NULL;
		m_DBCOLUMN_PROPID = 0;
		m_DBCOLUMN_NAME[0] = 0;
		m_DBCOLUMN_NUMBER = 0;
		m_DBCOLUMN_TYPE = 0;
		m_DBCOLUMN_TYPEINFO = 0;
		m_DBCOLUMN_COLUMNSIZE = 0;
		m_DBCOLUMN_PRECISION = 0;
		m_DBCOLUMN_SCALE = 0;
		m_DBCOLUMN_FLAGS = 0;
		m_DBCOLUMN_BASECOLUMNNAME[0] = NULL;
		m_DBCOLUMN_BASETABLENAME[0] = NULL;
		m_DBCOLUMN_KEYCOLUMN = FALSE;
#if defined(_USE_OGC_OPTIONAL_COLUMNS)
// OGC specifics
		m_nGeomType = 0;
		m_nSpatialRefId = 0;
		m_pszSpatialRefSystem[0] = NULL;
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)
	}

	BEGIN_PROVIDER_COLUMN_MAP(CColumnsRowsetRow)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_IDNAME", DBCOLUMN_IDNAME, 1, m_DBCOLUMN_IDNAME)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_GUID", DBCOLUMN_GUID, 2, m_DBCOLUMN_GUID)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_PROPID", DBCOLUMN_PROPID, 3, m_DBCOLUMN_PROPID)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_NAME", DBCOLUMN_NAME, 4, m_DBCOLUMN_NAME)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_NUMBER", DBCOLUMN_NUMBER, 5, m_DBCOLUMN_NUMBER)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_TYPE", DBCOLUMN_TYPE, 6, m_DBCOLUMN_TYPE)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_TYPEINFO", DBCOLUMN_TYPEINFO, 7, m_DBCOLUMN_TYPEINFO)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_COLUMNSIZE", DBCOLUMN_COLUMNSIZE, 8, m_DBCOLUMN_COLUMNSIZE)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_PRECISION", DBCOLUMN_PRECISION, 9, m_DBCOLUMN_PRECISION)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_SCALE", DBCOLUMN_SCALE, 10, m_DBCOLUMN_SCALE)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_FLAGS", DBCOLUMN_FLAGS, 11, m_DBCOLUMN_FLAGS)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_BASECOLUMNNAME", DBCOLUMN_BASECOLUMNNAME, 12, m_DBCOLUMN_BASECOLUMNNAME)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_BASETABLENAME", DBCOLUMN_BASETABLENAME, 13, m_DBCOLUMN_BASETABLENAME)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_KEYCOLUMN", DBCOLUMN_KEYCOLUMN, 14, m_DBCOLUMN_KEYCOLUMN)
#if defined(_USE_OGC_OPTIONAL_COLUMNS)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_GEOM_TYPE", DBCOLUMN_GEOM_TYPE, 15, m_nGeomType)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_SPATIAL_REF_SYSTEM_ID", DBCOLUMN_SPATIAL_REF_SYSTEM_ID, 16, m_nSpatialRefId)
		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_SPATIAL_REF_SYSTEM_WKT", DBCOLUMN_SPATIAL_REF_SYSTEM_WKT, 17, m_pszSpatialRefSystem)
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)
	END_PROVIDER_COLUMN_MAP()
};

template <typename T, typename CreatorClass = T, typename RowsetRow = CColumnsRowsetRow>
class ATL_NO_VTABLE IColumnsRowsetImpl : 
	public IColumnsRowset
{
public:
	class CColumnsRowsetRowset : 
		public CRowsetImpl<CColumnsRowsetRowset, RowsetRow, CreatorClass>
	{
	public:
		CColumnsRowsetRowset() : m_pBack(NULL) {}

		HRESULT PopulateRowset(ULONG numCols, DBCOLUMNINFO *pColInfo)
		{
			_ASSERTE(NULL != m_pBack);

		T *pT = static_cast<T *>(m_pBack);

			for (ULONG i = 0; i < numCols; i++)	{
			// copy data out of the pColInfo struct and into the rowset array 
			RowsetRow data;
			DBID &rcolId = pColInfo[i].columnid;

				switch (rcolId.eKind) {
				case DBKIND_GUID_PROPID:
					if (0 != pColInfo[i].pwszName[0])	// Name ist gegeben
						wcscpy(data.m_DBCOLUMN_IDNAME, pColInfo[i].pwszName);
					data.m_DBCOLUMN_GUID = rcolId.uGuid.guid;
					data.m_DBCOLUMN_PROPID = rcolId.uName.ulPropid;
					break;

				case DBKIND_NAME:
					wcscpy(data.m_DBCOLUMN_IDNAME, pColInfo[i].pwszName);
					break;

				case DBKIND_PGUID_NAME:
					data.m_DBCOLUMN_GUID = *rcolId.uGuid.pguid;
					wcscpy(data.m_DBCOLUMN_IDNAME, pColInfo[i].pwszName);
					break;

				case DBKIND_PGUID_PROPID:
					if (0 != pColInfo[i].pwszName[0])	// Name ist gegeben
						wcscpy(data.m_DBCOLUMN_IDNAME, pColInfo[i].pwszName);
					data.m_DBCOLUMN_GUID = *rcolId.uGuid.pguid;
					data.m_DBCOLUMN_PROPID = rcolId.uName.ulPropid;
					break;

				case DBKIND_PROPID:
					if (0 != pColInfo[i].pwszName[0])	// Name ist gegeben
						wcscpy(data.m_DBCOLUMN_IDNAME, pColInfo[i].pwszName);
					data.m_DBCOLUMN_PROPID = rcolId.uName.ulPropid;
					break;

				case DBKIND_GUID:
					if (0 != pColInfo[i].pwszName[0])	// Name ist gegeben
						wcscpy(data.m_DBCOLUMN_IDNAME, pColInfo[i].pwszName);
					data.m_DBCOLUMN_GUID = rcolId.uGuid.guid;
					break;
				}
			
				wcscpy(data.m_DBCOLUMN_NAME, pColInfo[i].pwszName);
				data.m_DBCOLUMN_NUMBER = pColInfo[i].iOrdinal;
				data.m_DBCOLUMN_TYPE = pColInfo[i].wType;
				data.m_DBCOLUMN_TYPEINFO = pColInfo[i].pTypeInfo;
				data.m_DBCOLUMN_COLUMNSIZE = pColInfo[i].ulColumnSize;
				data.m_DBCOLUMN_PRECISION = pColInfo[i].bPrecision;
				data.m_DBCOLUMN_SCALE = pColInfo[i].bScale;
				data.m_DBCOLUMN_FLAGS = pColInfo[i].dwFlags;

				wcscpy(data.m_DBCOLUMN_BASECOLUMNNAME, pColInfo[i].pwszName);
				{
				HRESULT hr = pT -> GetBaseTableName (rcolId, data);
				
					if (FAILED(hr)) return hr;
				}
				data.m_DBCOLUMN_KEYCOLUMN = (0 == pColInfo[i].iOrdinal) || (pColInfo[i].dwFlags & DBCOLUMNFLAGS_ISROWID);

#if defined(_USE_OGC_OPTIONAL_COLUMNS)
				{
				HRESULT hr = pT -> AddOgcSpecificColumns(i, data);

					if (FAILED(hr)) return hr;
				}
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)

			// Base the keycolumn decision on the flags too?
			// Keycolumn is only used if the column has been displayed :( Pity as this renders the bookmarks
			// useless..
				if (!m_rgRowData.Add(data))
					return E_OUTOFMEMORY;
			}
			return S_OK;
		}

#if defined(_USE_OGC_OPTIONAL_COLUMNS)
		DBSTATUS GetDBStatus(CSimpleRow *pRow, ATLCOLUMNINFO *pInfo)
		{
			_ASSERTE(NULL != m_pBack);

		T *pT = static_cast<T *>(m_pBack);

			switch (pInfo->iOrdinal) {
			case 15:	// DBCOLUMN_GEOM_TYPE
			case 16:	// DBCOLUMN_SPATIAL_REF_SYSTEM_ID
			case 17:	// DBCOLUMN_SPATIAL_REF_SYSTEM_WKT
				return pT -> GetDBStatusColumnRowset(pRow, pInfo);

			default:
				break;
			}
			return DBSTATUS_S_OK;
		}
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)

		void SetBackPointer(IColumnsRowsetImpl<T, CreatorClass> *pBack)
		{
			_ASSERTE(NULL != pBack);
			m_pBack = pBack;
		}

	private:
		IColumnsRowsetImpl<T, CreatorClass> *m_pBack;
	};
	friend CColumnsRowsetRowset;

	STDMETHOD(GetAvailableColumns)(ULONG *pcOptColumns, DBID **prgOptColumns)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IColumnsRowsetImpl::GetAvailableColumns\n");
		if (!pcOptColumns || !prgOptColumns)
			return E_INVALIDARG;

#if !defined(_USE_OGC_OPTIONAL_COLUMNS)
	const ULONG c_numOptColumns = 3;
#else
	const ULONG c_numOptColumns = 6;
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)

		*pcOptColumns = 0;
		*prgOptColumns = NULL;

	DBID *pOptCols = (DBID *)CoTaskMemAlloc(sizeof(DBID) * c_numOptColumns);

		if (NULL == pOptCols) return E_OUTOFMEMORY;

		memset(pOptCols, 0, sizeof(DBID) * c_numOptColumns);
		CDBIDOps::CopyDBIDs(&pOptCols[0], &DBCOLUMN_BASETABLENAME);
		CDBIDOps::CopyDBIDs(&pOptCols[1], &DBCOLUMN_BASECOLUMNNAME);
		CDBIDOps::CopyDBIDs(&pOptCols[2], &DBCOLUMN_KEYCOLUMN);

#if defined(_USE_OGC_OPTIONAL_COLUMNS)
	// OGC columns
		CDBIDOps::CopyDBIDs(&pOptCols[3], &DBCOLUMN_GEOM_TYPE);
		CDBIDOps::CopyDBIDs(&pOptCols[4], &DBCOLUMN_SPATIAL_REF_SYSTEM_ID);
		CDBIDOps::CopyDBIDs(&pOptCols[5], &DBCOLUMN_SPATIAL_REF_SYSTEM_WKT);
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)
	
		*pcOptColumns = c_numOptColumns;
		*prgOptColumns = pOptCols;
		return S_OK;
	}

	STDMETHOD(GetColumnsRowset)(IUnknown *pUnkOuter, ULONG cOptColumns, const DBID rgOptColumns[],
		 REFIID riid, ULONG cPropertySets, DBPROPSET rgPropertySets[], IUnknown **ppColRowset)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IColumnsRowsetImpl::GetColumnsRowset\n");

	// need to create our columns rowset, 
	// then populate it from the actual rowset that we represent...
	
	// We can do that by using IColumnsInfo...
	CColumnsRowsetRowset *pColRowset = 0;
	HRESULT hr = CreateRowset(pUnkOuter, riid, cPropertySets, rgPropertySets, pColRowset, ppColRowset);

		 if (SUCCEEDED(hr)) {
			if (NULL != pColRowset)	{
			T *pT = static_cast<T *>(this);
			CComQIPtr<IColumnsInfo> spColumnsInfo = pT->GetUnknown();

				if (spColumnsInfo) {
				ULONG numCols = 0;
				DBCOLUMNINFO *pColInfo = 0;
				OLECHAR *pNotUsed = 0;

					hr = spColumnsInfo->GetColumnInfo(&numCols, &pColInfo, &pNotUsed);
					if (SUCCEEDED(hr)) {
						pColRowset -> SetBackPointer(this);
						hr = pColRowset->PopulateRowset(numCols, pColInfo);
					}

					if (pNotUsed)
						CoTaskMemFree(pNotUsed);
					CoTaskMemFree(pColInfo);
				}
			} else
				hr = E_UNEXPECTED;
		} 

		if (SUCCEEDED(hr)) {
		// dieser Rowset darf keine BookmarkSpalte haben
		CComVariant vBookmarks (false);

			pColRowset -> SetPropValue (&DBPROPSET_ROWSET, DBPROP_BOOKMARKS, &vBookmarks);
		}
		return hr;
	}

protected:
#if defined(_USE_OGC_OPTIONAL_COLUMNS)
	HRESULT AddOgcSpecificColumns(ULONG iRow, RowsetRow &rData)
	{
		return S_OK;
	}
#endif // defined(_USE_OGC_OPTIONAL_COLUMNS)

	DBSTATUS GetDBStatusColumnRowset(CSimpleRow *pRow, ATLCOLUMNINFO *pInfo)
	{
		return DBSTATUS_S_OK;
	}

// Notanker für trübe Stunden ...
	HRESULT GetBaseTableName(const DBID &rColId, RowsetRow &rData)
	{
		wcscpy(rData.m_DBCOLUMN_BASETABLENAME, L"TABLE");
		return S_OK;
	}

private:
	HRESULT CreateRowset(IUnknown *pUnkOuter, REFIID riid, ULONG cPropertySets, DBPROPSET rgPropertySets[],
		 CColumnsRowsetRowset *&pRowsetObj, IUnknown **ppRowset)
	{
	HRESULT hr;
	T *pT = static_cast<T *>(this);

		if (ppRowset != NULL)
			*ppRowset = NULL;

		if ((pUnkOuter != NULL) && !InlineIsEqualUnknown(riid))
			return DB_E_NOAGGREGATION;

	CComPolyObject<CColumnsRowsetRowset> *pPolyObj;
		
		if (FAILED(hr = CComPolyObject<CColumnsRowsetRowset>::CreateInstance(pUnkOuter, &pPolyObj)))
			return hr;
		
	// Ref the created COM object and Auto release it on failure
	CComPtr<IUnknown> spUnk;
		
		hr = pPolyObj->QueryInterface(&spUnk);
		if (FAILED(hr))	{
			delete pPolyObj; // must hand delete as it is not ref'd
			return hr;
		}
		
	// Get a pointer to the Rowset instance
		pRowsetObj = &(pPolyObj->m_contained);
		if (FAILED(hr = pRowsetObj->FInit(pT)))
			return hr;

	// Set Properties that were passed in.
		hr = pRowsetObj->SetPropertiesArgChk(cPropertySets, rgPropertySets);
		if (FAILED(hr))
			return hr;

	const GUID *ppGuid[1];
	
		ppGuid[0] = &DBPROPSET_ROWSET;

	// Call SetProperties.The true in the last parameter indicates
	// the special behavior that takes place on rowset creation (i.e.
	// it succeeds as long as any of the properties were not marked
	// as DBPROPS_REQUIRED.
		hr = pRowsetObj->SetProperties(0, cPropertySets, rgPropertySets, 1, ppGuid, true);
		if (FAILED(hr))
			return hr;

		pRowsetObj -> SetSite(pT -> GetUnknown());
		if (InlineIsEqualGUID(riid, IID_NULL) || NULL == ppRowset) {
			if (ppRowset != NULL)
				*ppRowset = NULL;
			return hr;
		}

		if (InlineIsEqualGUID(riid, IID_NULL) || ppRowset == NULL)
		{
			if (ppRowset != NULL)
				*ppRowset = NULL;
			return hr;
		}

		hr = pPolyObj -> QueryInterface(riid, (void **)ppRowset);
		if (FAILED(hr))	return hr;

#if _ATL_VER < 0x0700
		for (ULONG iBind = 0; iBind < pT->m_rgBindings.GetSize(); ++iBind) {
		T::_BindType* pBind = NULL;
		T::_BindType* pBindSrc = NULL;

			ATLTRY(pBind = new T::_BindType);
			if (NULL == pBind) {
				ATLTRACE2(atlTraceDBProvider, 0, "Failed to allocate memory for new Binding\n");
				return E_OUTOFMEMORY;
			}

		// auto cleanup on failure
		CAutoMemRelease<T::_BindType> amr(pBind);

			pBindSrc = pT -> m_rgBindings.GetValueAt(iBind);
			if (NULL == pBindSrc) {
				ATLTRACE2(atlTraceDBProvider, 0, "The map appears to be corrupted, failing!!\n");
				return E_FAIL;
			}
			if (!pRowsetObj -> m_rgBindings.Add(pT -> m_rgBindings.GetKeyAt(iBind), pBind))	{
				ATLTRACE2(atlTraceDBProvider, 0, "Failed to add hAccessor to Map\n");
				return E_OUTOFMEMORY;
			}

			if (0 != pBindSrc -> cBindings) {
				ATLTRY(pBind -> pBindings = new DBBINDING[pBindSrc -> cBindings])
				if (NULL == pBind->pBindings) {
					ATLTRACE2(atlTraceDBProvider, 0, "Failed to Allocate dbbinding Array\n");
				
				// We added it, must now remove on failure
					pRowsetObj -> m_rgBindings.Remove(pT -> m_rgBindings.GetKeyAt(iBind));
					return E_OUTOFMEMORY;
				}
			} else
				pBind->pBindings = NULL; // NULL Accessor

			pBind->dwAccessorFlags = pBindSrc->dwAccessorFlags;
			pBind->cBindings = pBindSrc->cBindings;
			pBind->dwRef = 1;
			memcpy(pBind->pBindings, pBindSrc->pBindings, (pBindSrc->cBindings)*sizeof(DBBINDING));
			pBind = amr.Detach();
		}
#else // _ATL_VER < 0x0700
		for (POSITION pos = pT->m_rgBindings.GetStartPosition(); NULL != pos; pT->m_rgBindings.GetNext(pos)) { 
		T::_BindType* pBind = NULL;
		T::_BindType* pBindSrc = NULL;

			ATLTRY(pBind = new T::_BindType);
			if (NULL == pBind) {
				ATLTRACE2(atlTraceDBProvider, 0, "Failed to allocate memory for new Binding\n");
				return E_OUTOFMEMORY;
			}

		// auto cleanup on failure
		CAutoPtr<T::_BindType> amr(pBind);

			pBindSrc = pT->m_rgBindings.GetValueAt(pos);
			if (NULL == pBindSrc) {
				ATLTRACE2(atlTraceDBProvider, 0, "The map appears to be corrupted, failing!!\n");
				return E_FAIL;
			}
			
			if (!pRowsetObj -> m_rgBindings.SetAt(pT -> m_rgBindings.GetKeyAt(pos), pBind))	{
				ATLTRACE2(atlTraceDBProvider, 0, "Failed to add hAccessor to Map\n");
				return E_OUTOFMEMORY;
			}

			if (0 != pBindSrc -> cBindings) {
				ATLTRY(pBind -> pBindings = new DBBINDING[pBindSrc -> cBindings])
				if (NULL == pBind->pBindings) {
					ATLTRACE2(atlTraceDBProvider, 0, "Failed to Allocate dbbinding Array\n");
				
				// We added it, must now remove on failure
					pRowsetObj -> m_rgBindings.RemoveKey(pT -> m_rgBindings.GetKeyAt(pos));
					return E_OUTOFMEMORY;
				}
			} else
				pBind->pBindings = NULL; // NULL Accessor

			pBind->dwAccessorFlags = pBindSrc->dwAccessorFlags;
			pBind->cBindings = pBindSrc->cBindings;
			pBind->dwRef = 1;
			memcpy(pBind->pBindings, pBindSrc->pBindings, (pBindSrc->cBindings)*sizeof(DBBINDING));
			pBind = amr.Detach();
		}
#endif // _ATL_VER < 0x0700
		return hr;
	}
};

#endif // !defined(_ICOLUMNSROWSETIMPL_H__B453ABC3_3C01_4B96_A0E3_FA8620C6EC2A__INCLUDED_)
