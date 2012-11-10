// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.05.2001 11:50:22 
//
// @doc
// @module TRiASOleDBRowSet.h | Declaration of the <c CTRiASOleDBRowSet> class

#if !defined(_TRIASOLEDBROWSET_H__3F5727E5_69FE_433B_9DAF_8B1ECEB62DD8__INCLUDED_)
#define _TRIASOLEDBROWSET_H__3F5727E5_69FE_433B_9DAF_8B1ECEB62DD8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDB/IObjectWithSiteRowsetImpl.h>
#include <Atl/OleDB/IColumnsRowsetImpl.h>
#include <Atl/OleDB/IRowsetScrollImpl.h>
#include <Atl/OleDB/IRowsetBookmarkImpl.h>

#include <ospace/std/set>

#include "resource.h"       // main symbols
#include "AliasMap.h"
#include "GenerateColumnInfo.h"
#include "TRiASOleDBRow.h"
#include "TRiASOleDBGetDatasource.h"
#include "TRiASOleDBCommand.h"
#include "TRiASOleDBDataSource.h"
#include "AtlColumnInfo.h"

///////////////////////////////////////////////////////////////////////////////
// RowsetRow for IColumnsRowset
//class CColumnsRowsetRowOgc :
//	public CColumnsRowsetRow
//{
//public:
//// OGC specifics
//	ULONG m_nGeomType;
//	ULONG m_nSpatialRefId;
//	WCHAR m_pszSpatialRefSystem[2000];
//
//	CColumnsRowsetRowOgc()
//	{
//		ClearMembers();
//	}
//
//	void ClearMembers()
//	{
//		CColumnsRowsetRow::ClearMembers();
//		m_nGeomType = 0;
//		m_nSpatialRefId = 0;
//		m_pszSpatialRefSystem[0] = NULL;
//	}
//
//	BEGIN_PROVIDER_COLUMN_MAP(CColumnsRowsetRow)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_IDNAME", DBCOLUMN_IDNAME, 1, m_DBCOLUMN_IDNAME)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_GUID", DBCOLUMN_GUID, 2, m_DBCOLUMN_GUID)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_PROPID", DBCOLUMN_PROPID, 3, m_DBCOLUMN_PROPID)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_NAME", DBCOLUMN_NAME, 4, m_DBCOLUMN_NAME)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_NUMBER", DBCOLUMN_NUMBER, 5, m_DBCOLUMN_NUMBER)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_TYPE", DBCOLUMN_TYPE, 6, m_DBCOLUMN_TYPE)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_TYPEINFO", DBCOLUMN_TYPEINFO, 7, m_DBCOLUMN_TYPEINFO)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_COLUMNSIZE", DBCOLUMN_COLUMNSIZE, 8, m_DBCOLUMN_COLUMNSIZE)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_PRECISION", DBCOLUMN_PRECISION, 9, m_DBCOLUMN_PRECISION)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_SCALE", DBCOLUMN_SCALE, 10, m_DBCOLUMN_SCALE)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_FLAGS", DBCOLUMN_FLAGS, 11, m_DBCOLUMN_FLAGS)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_BASECOLUMNNAME", DBCOLUMN_BASECOLUMNNAME, 12, m_DBCOLUMN_BASECOLUMNNAME)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_BASETABLENAME", DBCOLUMN_BASETABLENAME, 13, m_DBCOLUMN_BASETABLENAME)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_KEYCOLUMN", DBCOLUMN_KEYCOLUMN, 14, m_DBCOLUMN_KEYCOLUMN)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_GEOM_TYPE", DBCOLUMN_GEOM_TYPE, 15, m_nGeomType)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_SPATIAL_REF_SYSTEM_ID", DBCOLUMN_SPATIAL_REF_SYSTEM_ID, 16, m_nSpatialRefId)
//		PROVIDER_COLUMN_ENTRY_DBID("DBCOLUMN_SPATIAL_REF_SYSTEM_WKT", DBCOLUMN_SPATIAL_REF_SYSTEM_WKT, 17, m_pszSpatialRefSystem)
//	END_PROVIDER_COLUMN_MAP()
//};

///////////////////////////////////////////////////////////////////////////////
// Rowset specifics

// forward declaration
class CTRiASOleDBSource;

template <
	class T, 
	class Storage, 
	class CreatorClass, 
	const IID *piid = &IID_IRowset, 
	class ArrayType = CAtlArray<Storage>
>
class CTRiASOleDBRowsetImpl :
	public CRowsetImpl<T, Storage, CreatorClass, ArrayType, CSimpleRow, IRowsetScrollImpl<T> >,
	public CTRiASOleDBErrorBase<T, piid>,
	public IColumnsRowsetImpl<T, CreatorClass>,
	public IRowsetBookmarkImpl<T>
{
public:
	typedef Storage _StorageClass;
	typedef CSimpleRow _RowClass;
	typedef CRowsetImpl<T, Storage, CreatorClass, ArrayType, CSimpleRow, IRowsetScrollImpl<T> > _RowsetBaseClass;
	typedef CreatorClass::_PropClass _PropClass;
	typedef IColumnsRowsetImpl<T, CreatorClass> _ColumnRowsetBase;

	BEGIN_COM_MAP(CTRiASOleDBRowsetImpl)
		COM_INTERFACE_ENTRY(IRowsetLocate)
		COM_INTERFACE_ENTRY(IRowsetScroll)
		COM_INTERFACE_ENTRY(IColumnsRowset)
		COM_INTERFACE_ENTRY(IRowsetBookmark)
		COM_INTERFACE_ENTRY_CHAIN(_RowsetBaseClass)
	END_COM_MAP()

// eine Property wurde geändert
	HRESULT OnPropertyChanged(ULONG iCurSet, DBPROP *pDBProp)
	{
		ATLASSERT(pDBProp != NULL);
		
	DWORD dwPropertyID = pDBProp->dwPropertyID;
		
		if (dwPropertyID == DBPROP_IRowsetLocate ||
			dwPropertyID == DBPROP_IRowsetBookmark ||
			dwPropertyID == DBPROP_LITERALBOOKMARKS ||
			dwPropertyID == DBPROP_ORDEREDBOOKMARKS)
		{
		CComVariant var (pDBProp->vValue);
			
			if (var.boolVal == VARIANT_TRUE) {
			// Set the bookmarks property as these are chained
			CComVariant bookVar(true);
			CDBPropSet set(DBPROPSET_ROWSET);

				set.AddProperty(DBPROP_BOOKMARKS, bookVar);
				
			// If you set IRowsetLocate to true, then the rowset can
			// handle backward scrolling
				if (dwPropertyID == DBPROP_IRowsetLocate)
					set.AddProperty(DBPROP_CANSCROLLBACKWARDS, bookVar);
				
			const GUID* ppGuid[1];

				ppGuid[0] = &DBPROPSET_ROWSET;
				return SetProperties(0, 1, &set, 1, ppGuid);
			}
		}

	// ausschalten der Bookmarks verhindert alles andere
		if (dwPropertyID == DBPROP_BOOKMARKS) {
		CComVariant var (pDBProp->vValue);
			
			if (var.boolVal == VARIANT_FALSE) {
			// Reset the bookmarks property as these are chained
			CComVariant bookVar(false);
			CDBPropSet set(DBPROPSET_ROWSET);

				set.AddProperty(DBPROP_IRowsetLocate, bookVar);
				set.AddProperty(DBPROP_IRowsetBookmark, bookVar);
				set.AddProperty(DBPROP_LITERALBOOKMARKS, bookVar);
				set.AddProperty(DBPROP_ORDEREDBOOKMARKS, bookVar);
				
			const GUID* ppGuid[1];

				ppGuid[0] = &DBPROPSET_ROWSET;
				return SetProperties(0, 1, &set, 1, ppGuid);
			}
		}
		return S_OK;
	}

// eigene Implementation von GetData
	STDMETHODIMP GetData(HROW hRow, HACCESSOR hAccessor, void *pDstData)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - hRow = %d\n", hRow);
		SetErrorInfo(0, NULL);
		if (pDstData == NULL)
			return OleDBError(E_INVALIDARG);

#if _ATL_VER < 0x0700
	_RowClass *pRow = 0;
		
		if (hRow == NULL || (pRow = m_rgRowHandles.Lookup((_RowClass::KeyType)hRow)) == NULL) {
			ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - Bad row handle\n");
			return OleDBError(DB_E_BADROWHANDLE);
		}

	T::_BindType *pBinding = m_rgBindings.Lookup((int)hAccessor);

		if (pBinding == NULL)
			return OleDBError(DB_E_BADACCESSORHANDLE);
#else
	_RowClass *pRow = 0;
	bool fFound = m_rgRowHandles.Lookup((_RowClass::KeyType)hRow, pRow);
	
		if (!fFound || NULL == pRow) {
			ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - Bad row handle\n");
			return OleDBError(DB_E_BADROWHANDLE);
		}

	T::_BindType* pBinding;
	bool bFound = m_rgBindings.Lookup((INT_PTR)hAccessor, pBinding);

		if (!bFound || pBinding == NULL)
			return OleDBError(DB_E_BADACCESSORHANDLE);
#endif // _ATL_VER < 0x0700

	// At this point we know the bindings for the data we're accesssing...
	HRESULT hr = S_OK;
	ULONG cCols = 0;
	ATLCOLUMNINFO *pColInfo = T::GetColumnInfo(static_cast<T *>(this), &cCols);

		ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - Bindings for %d columns\n", pBinding->cBindings);

		for (ULONG iBind = 0; SUCCEEDED(hr) && iBind < pBinding->cBindings; ++iBind) {
		DBBINDING *pBindCur = &(pBinding->pBindings[iBind]);

			for (ULONG iColInfo = 0;
				 iColInfo < cCols && pBindCur->iOrdinal != pColInfo[iColInfo].iOrdinal;
				 ++iColInfo)
				 ;
			if (iColInfo == cCols) {
				ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - Error - bad column Id\n");
				return OleDBError(DB_E_BADORDINAL);
			}

			if (pBindCur->iOrdinal > cCols)	{
				ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - Error - bad ordinal\n");
				return OleDBError(DB_E_BADORDINAL);
			}
			ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - Binding for column ordinal %d\n", pBindCur->iOrdinal);

		// get the data and put it into the destination buffer
		ULONG cbDst = pBindCur->cbMaxLen;
		BYTE *pDstTemp = (BYTE *)pDstData + pBindCur->obValue;
		ATLCOLUMNINFO *pColCurr = &pColInfo[iColInfo];

		ULONG cbCol = 0; 
		void *pSrcTemp = 0; 
		DBSTATUS dbStat = DBSTATUS_S_ISNULL;
		
			hr = static_cast<T *>(this) -> GetColumnData (pRow, pColCurr, cbCol, pSrcTemp, dbStat, pBindCur);
			if (DBSTATUS_S_ISNULL == dbStat) {
				if (pBindCur->dwPart & DBPART_VALUE) 
					*pDstTemp = NULL;
			
				if (pBindCur->dwPart & DBPART_LENGTH)
					*((ULONG *)((BYTE *)(pDstData) + pBindCur->obLength)) = 0;

				if (pBindCur->dwPart & DBPART_STATUS)
					*((DBSTATUS *)((BYTE *)(pDstData) + pBindCur->obStatus)) = DBSTATUS_S_ISNULL;
			}
			else {
				cbDst = cbCol;
				if (pBindCur->dwPart & DBPART_VALUE) {
				// Daten sollen geliefert werden
					if (pBindCur->dwMemOwner == DBMEMOWNER_PROVIDEROWNED)
					{	
					// Set a pointer to the data in the Value location
						*((void **)((BYTE *)(pDstData) + pBindCur->obValue)) = pSrcTemp;
					}
					else {
						hr = m_spConvert->DataConvert(
								pColCurr -> wType,				// the column type
								pBindCur -> wType,				// the required type
								cbCol,							// length of column data
								&cbDst, 						// length of data after conversion
								(BYTE *)pSrcTemp,				// pointer to the column data
								pDstTemp,						// pointer to where to put it...
								pBindCur -> cbMaxLen, 			// max length of destination buffer
								dbStat, 						// source status
								&dbStat,						// dest status
								pBindCur -> bPrecision,			// precision
								pBindCur -> bScale,				// scale
								0); 							// flags - none supplied
					}
				}
					
				if (pBindCur->dwPart & DBPART_LENGTH)
					*((ULONG*)((BYTE*)(pDstData) + pBindCur->obLength)) = cbDst;

				if (pBindCur->dwPart & DBPART_STATUS)
					*((DBSTATUS*)((BYTE*)(pDstData) + pBindCur->obStatus)) = dbStat;
			}
		}
		ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBRowsetImpl::GetData - %s\n", (hr == S_OK ? "OK" : "FAILED"));
		return SUCCEEDED(hr) ? hr : OleDBError(hr);
	}
};

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für alle Rowsets
template<typename T, typename Storage, typename CreatorClass, const IID *piid = &IID_IRowset>
class CTRiASOleDBRowsetBase :
	public IObjectWithSiteRowsetImpl<T, CTRiASOleDBRowsetImpl<T, Storage, CreatorClass, piid> >
{
public:
	typedef IObjectWithSiteRowsetImpl<T, CTRiASOleDBRowsetImpl<T, Storage, CreatorClass, piid> > _RowsetBaseClass;
	typedef _RowsetBaseClass::_StorageClass _StorageClass;
	typedef _RowsetBaseClass::_RowClass _RowClass;
	typedef _RowsetBaseClass::_PropClass _PropClass;

	typedef map<DBBKMARK, ULONG, less<DBBKMARK> > CBookmarkMap;

	CTRiASOleDBRowsetBase() :
		m_pDataSource(NULL), m_pGenColInfo(NULL), 
		m_fAttachedColInfo(true), m_fIsCommandBased(false)
	{
	}
	~CTRiASOleDBRowsetBase() 
	{
		if (!m_fAttachedColInfo)
			DELETE_OBJ(m_pGenColInfo);
	}

	BEGIN_COM_MAP(CTRiASOleDBRowsetBase)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY_CHAIN(_RowsetBaseClass)
	END_COM_MAP()

// Daten eines Feldes liefern
	HRESULT GetColumnData(
		_RowClass *pRow, ATLCOLUMNINFO *pColumn, ULONG &rulSize, void *& rpData, 
		DBSTATUS &rdbStatus, DBBINDING *pBindCur)
	{
	// Datensatz wiederfinden
	ObjectLock lock(this);

		if (pRow->m_iRowset < 0 || m_rgRowData.GetSize() <= pRow->m_iRowset)
			return OleDBError(E_INVALIDARG);		// nicht exitierende Zeile

	// die eigentliche Arbeit macht die entsprechende Row
	CTRiASOleDBRowT<T> &rRow = m_rgRowData[pRow->m_iRowset];

		return rRow.GetData (GetProjectHandle(), pColumn, rulSize, rpData, rdbStatus, pBindCur);
	}
	ULONG GetNumRows() 
	{ 
		return m_rgRowData.GetSize(); 
	}

// Verweis auf DataSource 
	INT_PTR GetProjectHandle() const
	{
		_ASSERTE(NULL != m_pDataSource);
		return m_pDataSource -> GetProjectHandle();
	}
	HRESULT EnsureDatabaseObject()
	{
		if (NULL == m_pDataSource) 
			 return GetDataSourceObject(this, &m_pDataSource);
		return S_OK;
	}

	ATLCOLUMNINFO *GetRawColumnInfo(ULONG *pcCols) 
	{ 
		_ASSERTE(NULL != pcCols);

		if (FAILED(static_cast<T *>(this) -> PrepareColumnInfo()))
			return NULL;

		_ASSERTE(NULL != m_pGenColInfo);
		*pcCols = m_pGenColInfo->GetColumnInfo().GetSize(); 
		return m_pGenColInfo->GetColumnInfo().GetColumnInfo().GetData(); 
	}

	int GetNumCols() 
	{ 
		_ASSERTE(NULL != m_pGenColInfo && m_pGenColInfo -> IsPrepared());
		return m_pGenColInfo->GetColumnInfo().GetColumnInfo().GetSize(); 
	}
	bool GetUseBookmarks() const
	{ 
		_ASSERTE(NULL != m_pGenColInfo && m_pGenColInfo -> IsPrepared());
		return m_pGenColInfo->GetUseBookmarks(); 
	}

	bool MustIndirectGetData(ULONG ulColumn)
	{
		_ASSERTE(NULL != m_pGenColInfo && m_pGenColInfo -> IsPrepared());
		if (!GetUseBookmarks())
			--ulColumn;
		return m_pGenColInfo->GetColumnInfo().MustIndirectGetData(ulColumn);
	}
	bool MustIndirectCompareData(ULONG ulColumn)
	{
		_ASSERTE(NULL != m_pGenColInfo && m_pGenColInfo -> IsPrepared());
		if (!GetUseBookmarks())
			--ulColumn;
		return m_pGenColInfo->GetColumnInfo().MustIndirectCompareData(ulColumn);
	}
	UINT GetDataLen(ULONG ulColumn, void *pData)
	{
		_ASSERTE(NULL != m_pGenColInfo && m_pGenColInfo -> IsPrepared());
		if (!GetUseBookmarks())
			--ulColumn;
		return m_pGenColInfo->GetColumnInfo().GetDataLen(ulColumn, pData);
	}
	CComPtr<IHandleDataAccess> GetHandler(ULONG ulColumn) const
	{
		_ASSERTE(NULL != m_pGenColInfo && m_pGenColInfo -> IsPrepared());
		if (!GetUseBookmarks())
			--ulColumn;
		return m_pGenColInfo->GetColumnInfo().GetHandler(ulColumn);
	}

	HRESULT RegisterTable (DBID *pTableId)
	{
		_ASSERTE(NULL != pTableId);
		return m_BoundTables.Add(CComBSTR(pTableId->uName.pwszName)) ? S_OK : E_OUTOFMEMORY;
	}

protected:
	///////////////////////////////////////////////////////////////////////////////
	// benutzte Tabellen beim Sessionobjekt registrieren
	HRESULT RegisterTables (ISelectStmt *pISelect)
	{
		_ASSERTE(m_fIsCommandBased);
		_ASSERTE(m_pGenColInfo->IsPrepared());
		_ASSERTE(NULL != pISelect);

	CTRiASOleDBSession *pSession = NULL;

		if (FAILED(GetSessionObject(this, &pSession))) 
			return E_UNEXPECTED;

	CComPtr<IParser> Parser;
	CComPtr<ITableIdentList> TableIdentList;

		MAKE_OLEDB_ERROR(m_pGenColInfo -> GetParser(&Parser));
		MAKE_OLEDB_ERROR(pISelect -> get_TableIdentList(&TableIdentList));
		if (TableIdentList == NULL) return OleDBError(DB_E_ERRORSINCOMMAND);

	CComPtr<IUnknown> UnkEnum;

		MAKE_OLEDB_ERROR(TableIdentList -> get__NewEnum(&UnkEnum));

	CComQIPtr<IEnumVARIANT> Tables(UnkEnum);
	CComVariant v;

		_ASSERTE(Tables != NULL);
		for (Tables -> Reset(); S_OK == Tables -> Next(1, &v, NULL); /**/) {
			_ASSERTE(V_ISDISPATCH(&v));

		CComQIPtr<ITableIdent> Table (V_DISPATCH(&v));
		CComBSTR bstrTable;
		INT_PTR lIdent = NULL;

			if (Table == NULL) return OleDBError(E_UNEXPECTED);

			MAKE_OLEDB_ERROR(Table -> get_Name(&bstrTable));
			bstrTable = m_pGenColInfo->ResolveTableAlias(RemoveQuotes(bstrTable));

			if (!VerifyTableIsGiven (Parser, bstrTable))
				return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_TABLENOTGIVENINFROMCLAUSE);	// Table not given in 'From' clause

			MAKE_OLEDB_ERROR(SplitTableName(bstrTable));
			if (FAILED(m_pDataSource -> get_Class(bstrTable, &lIdent)))
				return OleDBError(DB_E_NOTABLE);			// Table does not exist
			_ASSERTE(0 != lIdent);

		CDBID TableId (bstrTable, CDBID::DBIDMODE_Quoted);

			if (m_BoundTables.Add(CComBSTR(TableId.uName.pwszName))) 
				pSession -> RegisterTable(&TableId);
		}
		return S_OK;
	}

public:
// support für Bookmarks bzw. IRowsetLocate
// neue Row zum Rowset hinzufügen
	BOOL AddRow (CTRiASOleDBRowT<T> &rRow)
	{
		if (m_rgRowData.Add(rRow)) {
		size_t iCnt = m_Bookmarks.size();

			ATLTRY(m_Bookmarks.insert(CBookmarkMap::value_type(rRow.GetBookmark(), m_rgRowData.GetCount()-1)));
			if (iCnt != m_Bookmarks.size()-1) {
				m_rgRowData.RemoveAt(m_rgRowData.GetCount()-1);		// letzten wieder freigeben
				return FALSE;
			}
			return TRUE;
		}
		return FALSE;
	}
	DBBKMARK GetRowHandleFromBookmark(DBBKMARK cbBookmark, const BYTE *pBookmark)
	{
	// Standardbookmarks verwaltet die Basisklasse
		if (1 == cbBookmark)
			return _RowsetBaseClass::GetRowHandleFromBookmark(cbBookmark, pBookmark);

	// von uns vergebene Bookmarks verwalten wir
	ObjectLock cab(this);
	CBookmarkMap::iterator it = m_Bookmarks.find (*(DBBKMARK *)pBookmark);

		if (it == m_Bookmarks.end())
			return 0;
		return (*it).second+1;
	}

// support for optional columns in IColumnsRowset
	STDMETHOD(GetColumnsRowset)(IUnknown *pUnkOuter, ULONG cOptColumns, const DBID rgOptColumns[],
		 REFIID riid, ULONG cPropertySets, DBPROPSET rgPropertySets[], IUnknown **ppColRowset)
	{
		SetErrorInfo(0, NULL);
		m_GeometryRows.clear();
		return _ColumnRowsetBase::GetColumnsRowset(pUnkOuter, cOptColumns, rgOptColumns, riid, cPropertySets, rgPropertySets, ppColRowset);
	}
	DBSTATUS GetDBStatusColumnRowset(CSimpleRow *pRow, ATLCOLUMNINFO *pInfo)
	{
	// nur für Geometriespalten definiert
		return (m_GeometryRows.find(pRow->m_iRowset) != m_GeometryRows.end()) ? DBSTATUS_S_OK : DBSTATUS_S_ISNULL;
	}
	HRESULT AddOgcSpecificColumns(ULONG ulRow, CColumnsRowsetRow &rData)
	{
#if defined(_USE_PROP_GEOMETRYAS)
		if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == m_pDataSource -> GetGeometryMode()) {
			for (int i = 0; i < _countof(s_rgTypes); ++i) {
				if (!wcscmp (s_rgTypes[i].pcoleGeomName, rData.m_DBCOLUMN_BASECOLUMNNAME)) {
					rData.m_nGeomType = s_rgTypes[i].uiOGCType;
					rData.m_nSpatialRefId = 1;

				CComBSTR bstrCS;
				UINT uiCode = 0;

					RETURN_ERROR(m_pDataSource -> get_CoordSystemWKT (&uiCode, &bstrCS));
					wcscpy (rData.m_pszSpatialRefSystem, bstrCS);
					m_GeometryRows.insert(ulRow);
					break;
				}
			}
		}
		else
#endif // defined(_USE_PROP_GEOMETRYAS)
		{
			if (!wcscmp(OLESTR("OGIS_GEOMETRY"), rData.m_DBCOLUMN_BASECOLUMNNAME)) {
				rData.m_nGeomType = wkbGeometryCollection;
				rData.m_nSpatialRefId = 1;

			CComBSTR bstrCS;
			UINT uiCode = 0;
				
				RETURN_ERROR(m_pDataSource -> get_CoordSystemWKT (&uiCode, &bstrCS));
				wcscpy (rData.m_pszSpatialRefSystem, bstrCS);
				m_GeometryRows.insert(ulRow);
			}
		}
		return S_OK;
	}

// BaseTableName für IColumnsRowset abfragen
	HRESULT GetBaseTableName(const DBID &rColId, CColumnsRowsetRow &rData)
	{
	// versuchen, Basetablename zu finden
	CComBSTR bstrBaseTable;

		if (DBKIND_PROPID == rColId.eKind || DBKIND_GUID_PROPID == rColId.eKind) {
			if (SUCCEEDED(m_pGenColInfo -> GetColumnInfo().GetBaseTable(rColId.uName.ulPropid, &bstrBaseTable)) && 
				bstrBaseTable.Length() > 0) 
			{
				wcscpy (rData.m_DBCOLUMN_BASETABLENAME, bstrBaseTable);
				return S_OK;
			}
		}
		else {
			if (SUCCEEDED(m_pGenColInfo -> GetColumnInfo().GetBaseTable(rColId.uName.pwszName, &bstrBaseTable)) &&
				bstrBaseTable.Length() > 0) 
			{
				wcscpy (rData.m_DBCOLUMN_BASETABLENAME, bstrBaseTable);
				return S_OK;
			}
		}
		return _ColumnRowsetBase::GetBaseTableName(rColId, rData);
	}

protected:
	CTRiASOleDBSource *m_pDataSource;
	CGenerateColumnInfoBase *m_pGenColInfo;
	CAtlArray<CComBSTR> m_BoundTables;
	CBookmarkMap m_Bookmarks;					// Bookmark(ONr) --> RowNr
	set<CSimpleRow::KeyType> m_GeometryRows;	// OGC specifics
	bool m_fIsCommandBased;
	bool m_fAttachedColInfo;
};

///////////////////////////////////////////////////////////////////////////////
// der eigentliche Rowset

// 37D5ECA8-84D6-414F-B672-85D25D2D2B2E
EXTERN_C const GUID __declspec(selectany) CLSID_TRiASOleDBRowset = 
	{ 0x37D5ECA8, 0x84D6, 0x414F, 0xB6, 0x72, 0x85, 0xD2, 0x5D, 0x2D, 0x2B, 0x2E };

class CTRiASOleDBRowset :
	public CTRiASOleDBRowsetBase<CTRiASOleDBRowset, CTRiASOleDBRowT<CTRiASOleDBRowset>, CTRiASOleDBCommand>,
	public ISupportErrorInfo
{
public:
	typedef CTRiASOleDBRowsetBase<CTRiASOleDBRowset, CTRiASOleDBRowT<CTRiASOleDBRowset>, CTRiASOleDBCommand> _RowsetBaseClass;
	typedef CTRiASOleDBRowT<CTRiASOleDBRowset> CTRiASOleDBRow;

	CTRiASOleDBRowset() 
	{
	}
	~CTRiASOleDBRowset()
	{
	}

	HRESULT FinalConstruct()
	{
		return _RowsetBaseClass::FinalConstruct();
	}
	void FinalRelease();

	HRESULT Execute(DBPARAMS *pParams, LONG* pcRowsAffected);
	HRESULT ExecuteSelect (DBPARAMS *pParams, LONG *pcRowsAffected);
	HRESULT ExecuteCreateTable (DBPARAMS *pParams, LONG *pcRowsAffected);
	HRESULT ExecuteDropTable (DBPARAMS *pParams, LONG *pcRowsAffected);

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASOleDBRowset)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CTRiASOleDBRowset)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_CHAIN(_RowsetBaseClass)
	END_COM_MAP()

public:
// Analyse eines SQL Statements (support for CTRiASOleDBRow)
	HRESULT PrepareColumnInfo();
	HRESULT PrepareObjectsList(ITRiASEnumNativeObjects **ppIObjsOut);
	HRESULT FindColumnId (IColumnIdent *pIIdent, ULONG *pulColId);

	bool IsDerivedFromCommand (CTRiASOleDBCommand **ppCommand);

// ISupportErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);
};

#endif // !defined(_TRIASOLEDBROWSET_H__3F5727E5_69FE_433B_9DAF_8B1ECEB62DD8__INCLUDED_)
