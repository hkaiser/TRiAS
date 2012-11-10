// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 21:46:18 
//
// @doc
// @module ProxyRowsetImpl.h | Declaration of the <c CProxyRowsetImpl> class

#if !defined(_PROXYROWSETIMPL_H__ABDE07C0_69D8_4DA0_B565_466F55C27FC4__INCLUDED_)
#define _PROXYROWSETIMPL_H__ABDE07C0_69D8_4DA0_B565_466F55C27FC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#include <atldb.h>
#include <ospace/std/string>
#include <idl/IDisconnectableRowset.h>

///////////////////////////////////////////////////////////////////////////////
// CRowsetStorageProxy
// An ATL OLE DB Provider Storage template that forwards the required
// functionality to the Rowset object.
template <class T>
class CRowsetStorageProxy
{
public: 
	static ATLCOLUMNINFO* GetColumnInfo(T *pT, ULONG *pcCols)
	{
		ATLASSERT(pT);
		return pT->StorageProxy_GetColumnInfo(pcCols);
	}
};

///////////////////////////////////////////////////////////////////////////////
// CRowsetArrayTypeProxy
// An ATL OLE DB Provider ArrayType template that forwards the required
// functionality to the Rowset object.
template <class T, class Storage>
class CRowsetArrayTypeProxy
{
public:
	void Associate(T *pRowset)
	{
		m_pRowset = pRowset;
	}

	int GetSize() const
	{
		ATLASSERT(m_pRowset);
		return m_pRowset->ArrayProxy_GetSize();
	}

	unsigned char &operator[](int nIndex) const
	{
		ATLASSERT(m_pRowset);
		return m_pRowset->ArrayProxy_IndexOperator(nIndex);
	}

	HRESULT Add(Storage &storage)
	{
		ATLASSERT(m_pRowset);
		return m_pRowset->ArrayProxy_Add(storage);
	}

	HRESULT RemoveAt(int nIndex)
	{
		ATLASSERT(m_pRowset);
		return m_pRowset->ArrayProxy_RemoveAt(nIndex);
	}

	void RemoveAll()
	{
		ATLASSERT(m_pRowset);
		m_pRowset->ArrayProxy_RemoveAll();
	}

private:
	T *m_pRowset;
};

///////////////////////////////////////////////////////////////////////////////
// CProxyRowsetImpl
// An ATL OLE DB Provider template that represents a Rowset which expects the 
// derived class to be responsible for storing the rowset data within it 
// (rather than working with the Storage and ArrayType classes). 
template<class DataClass, class T, class CreatorClass, 
	class Storage = CRowsetStorageProxy<T>, 
	class ArrayType = CRowsetArrayTypeProxy<T, Storage>,
	class RowClass = CSimpleRow,
	class RowsetInterface = IRowsetImpl<T, IRowset, RowClass> >
class CProxyRowsetImpl:
	public CRowsetImpl<T, Storage, CreatorClass, ArrayType, RowClass, RowsetInterface>,
	public IDisconnectableRowset
{
public:
	friend Storage;
	friend ArrayType;

	typedef CreatorClass::_PropClass _PropClass;
	typedef CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface> ProxyRowsetClass;

	BEGIN_COM_MAP(CProxyRowsetImpl)
		 COM_INTERFACE_ENTRY(IRowset)
		 COM_INTERFACE_ENTRY(IDisconnectableRowset)
		 COM_INTERFACE_ENTRY_CHAIN(_RowsetBaseClass)
	END_COM_MAP()

	CProxyRowsetImpl();
	~CProxyRowsetImpl();

	HRESULT ValidateCommandID(DBID* pTableID, DBID* pIndexID);

	HRESULT OnPropertyChanged(ULONG iCurSet, DBPROP* pDBProp);

// override this from IRowsetImpl
	STDMETHOD(GetData)(HROW hRow, HACCESSOR hAccessor, void *pDstData);

// Connect our rowset class to the data object that we represent.
	HRESULT LinkToObject(DataClass *pThis, IUnknown *pUnkDataObject, LONG* pcRowsAffected);

// IDisconnectableRowset interface
	STDMETHOD(DisconnectRowset)();

// Not used but needs to be defined...
	HRESULT Execute(DBPARAMS * pParams, LONG* pcRowsAffected);

protected:
	virtual void GetColumnInformation(size_t column, DBTYPE &dbType, ULONG &size, string &columnName, DWORD &flags) = 0;
	virtual void GetColumnData(size_t row, size_t column, DBTYPE &dbType, ULONG &size, void *&pData, bool &bIsUpdatable) = 0;
	virtual size_t GetNumColumns() = 0;
	virtual size_t GetNumRows() const = 0;

// default implementations of the following do nothing...
	virtual HRESULT AddRow();
	virtual HRESULT RemoveRow(int nIndex);
	virtual void RemoveAllRows();

	DataClass *m_pDataObject;
	IUnknown *m_pUnkDataObject;

	void InternalGetColumnData(size_t row, size_t column, DBTYPE &dbType, ULONG &size, void *&pData, bool &bIsUpdatable);

private:
	wchar_t *ustrdup(const char *pIn);


// Stuff needed because our Storage object forwards requests to us
	ATLCOLUMNINFO* StorageProxy_GetColumnInfo(ULONG *pcCols);

// Stuff needed because our ArrayType object forwards requests to us
	int ArrayProxy_GetSize() const;
	unsigned char &ArrayProxy_IndexOperator(int nIndex) const;
	BOOL ArrayProxy_Add(Storage &storage);
	BOOL ArrayProxy_RemoveAt(int nIndex);
	void ArrayProxy_RemoveAll();

// Cached column information
	void BuildColumnInfo();
	bool BookmarksRequired();

	ATLCOLUMNINFO *m_pColumnInfo;
	ULONG m_NumCols;
};

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction...
template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::CProxyRowsetImpl() :
	m_pDataObject(0), m_pUnkDataObject(0), m_pColumnInfo(0), m_NumCols(0)
{
	m_rgRowData.Associate((T*)this);
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::~CProxyRowsetImpl()
{
	if (m_pColumnInfo) {
		for (size_t i = 0; i<m_NumCols; i++)
			delete[] m_pColumnInfo[i].pwszName;

		delete[] m_pColumnInfo;

		m_pColumnInfo = 0;
		m_NumCols = 0;
	}
	if (m_pUnkDataObject) {
		m_pUnkDataObject -> Release();
		m_pUnkDataObject = 0;
	}
	m_pDataObject = 0;
}

///////////////////////////////////////////////////////////////////////////////
// 
template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
HRESULT CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::ValidateCommandID(
	DBID* pTableID, DBID* pIndexID)
{
HRESULT hr = _RowsetBaseClass::ValidateCommandID(pTableID, pIndexID);
	
	if (hr != S_OK)
		return hr;

	if (pIndexID != NULL)
		return DB_E_NOINDEX;	// We don't support indexes

	return S_OK;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
HRESULT CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::OnPropertyChanged(
	ULONG iCurSet, DBPROP* pDBProp)
{
	ATLASSERT(pDBProp != NULL);

DWORD dwPropertyID = pDBProp->dwPropertyID;

	if (dwPropertyID == DBPROP_IRowsetLocate ||
		dwPropertyID == DBPROP_LITERALBOOKMARKS ||
		dwPropertyID == DBPROP_ORDEREDBOOKMARKS)
	{
	CComVariant var = pDBProp->vValue;

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
	return S_OK;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
bool CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::BookmarksRequired()
{
CComQIPtr<IRowsetInfo> spProps(this);
CDBPropIDSet set(DBPROPSET_ROWSET);

	set.AddPropertyID(DBPROP_BOOKMARKS);

DBPROPSET* pPropSet = NULL;
ULONG ulPropSet = 0;
HRESULT hr;

	if (spProps) 
		hr = spProps->GetProperties(1, &set, &ulPropSet, &pPropSet);

// Check the property flag for bookmarks, if it is set, set the zero ordinal
// entry in the column map with the bookmark information.
bool bRequired = false;

	if (pPropSet) {
	CComVariant var = pPropSet->rgProperties[0].vValue;
		
		CoTaskMemFree(pPropSet->rgProperties);
		CoTaskMemFree(pPropSet);

		if ((SUCCEEDED(hr) &&(var.boolVal == VARIANT_TRUE))) 
			bRequired = true;
	}
	return bRequired;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
HRESULT CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::LinkToObject(
	DataClass *pDataObject, IUnknown *pUnkDataObject, LONG* pcRowsAffected)
{
	if (!pDataObject || !pUnkDataObject)
		return E_POINTER;

ObjectLock lock(this);

	m_pDataObject = pDataObject;
	if (m_pUnkDataObject) 
		m_pUnkDataObject->Release();

	m_pUnkDataObject = pUnkDataObject;
	m_pUnkDataObject->AddRef();

const LONG numCols = GetNumColumns();

	if (numCols == 0)
		return DB_E_NOTABLE;

	if (pcRowsAffected != NULL)
		*pcRowsAffected = numCols;

	return S_OK;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
HRESULT CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::DisconnectRowset()
{
ObjectLock lock(this);

	if (m_pDataObject)
		m_pDataObject = 0;

	if (m_pUnkDataObject) {
		m_pUnkDataObject->Release();
		m_pUnkDataObject = 0;
	}
	return S_OK;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
STDMETHODIMP CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::GetData(
	HROW hRow, HACCESSOR hAccessor, void *pDstData)
{
	ATLTRACE2(atlTraceDBProvider, 0, "CProxyRowsetImpl::GetData - hRow = %d\n", hRow);

	if (pDstData == NULL)
		return E_INVALIDARG;

RowClass* pRow = 0;
	
	if (hRow == NULL ||(pRow = m_rgRowHandles.Lookup((RowClass::KeyType)hRow)) == NULL) {
		ATLTRACE2(atlTraceDBProvider, 0, "CProxyRowsetImpl::GetData - Bad row handle\n");
		return DB_E_BADROWHANDLE;
	}

_BindType *pBinding = m_rgBindings.Lookup((int)hAccessor);

	if (pBinding == NULL)
		return DB_E_BADACCESSORHANDLE;

// At this point we know the bindings for the data we're accesssing...
HRESULT hr = S_OK;

	ATLTRACE2(atlTraceDBProvider, 0, "CProxyRowsetImpl::GetData - Bindings for %d columns\n", pBinding->cBindings);
	for (ULONG iBind =0; SUCCEEDED(hr) && iBind<pBinding->cBindings; iBind++) {
	DBBINDING* pBindCur = &(pBinding->pBindings[iBind]);

		ATLTRACE2(atlTraceDBProvider, 0, "CProxyRowsetImpl::GetData - Binding for column ordinal %d\n", pBindCur->iOrdinal);

		if (pBindCur->iOrdinal > GetNumColumns())
		{
			ATLTRACE2(atlTraceDBProvider, 0, "CProxyRowsetImpl::GetData - Error - bad ordinal\n");
			return DB_E_BADORDINAL;
		}

	BOOL bProvOwn = (pBindCur->dwMemOwner == DBMEMOWNER_PROVIDEROWNED);

		if (pBindCur->dwMemOwner == DBMEMOWNER_PROVIDEROWNED)
		{
			ATLTRACE2(atlTraceDBProvider, 0, "CProxyRowsetImpl::GetData - Error - we dont support provider owned memory\n");
			return E_FAIL;
		}

	DBSTATUS dbStat = DBSTATUS_S_OK; 
	ULONG cbDst = pBindCur->cbMaxLen;
	BYTE *pDstTemp = (BYTE*)pDstData + pBindCur->obValue;

	ULONG cbCol = 0; 
	void *pSrcTemp = 0; 
	DBTYPE colType; 
	bool bUpdatable;

		InternalGetColumnData(pRow->m_iRowset, pBindCur->iOrdinal, colType, cbCol, pSrcTemp, bUpdatable);
		if (pBindCur->dwPart & DBPART_VALUE) {
			hr = m_spConvert->DataConvert(
					colType,						// the column type
					pBindCur->wType,				// the required type
					cbCol,							// length of column data
					&cbDst, 						// length of data after conversion
					(BYTE*)pSrcTemp,				// pointer to the column data
					pDstTemp,						// pointer to where to put it...
					pBindCur->cbMaxLen, 			// max length of destination buffer
					dbStat, 						// source status
					&dbStat,						// dest status
					pBindCur->bPrecision,			// precision
					pBindCur->bScale,				// scale
					0); 							// flags - none supplied
		}

		if (pBindCur->dwPart & DBPART_LENGTH)
			*((ULONG*)((BYTE*)(pDstData) + pBindCur->obLength)) = cbDst;

		if (pBindCur->dwPart & DBPART_STATUS)
			*((DBSTATUS*)((BYTE*)(pDstData) + pBindCur->obStatus)) = dbStat;
	}

	ATLTRACE2(atlTraceDBProvider, 0, "CProxyRowsetImpl::GetData - %s\n", (hr == S_OK ? "OK" : "FAILED"));
	return hr;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
void CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::InternalGetColumnData(
	size_t row, size_t column, DBTYPE &dbType, ULONG &size, void *&pData, bool &bUpdatable)
{
	if (column == 0) {
	// We handle the bookmark column. 
		dbType = DBTYPE_BYTES;
		size = sizeof(DWORD);

	static DWORD bookmark;
	
		bookmark = row + 1; 	 // The bookmark can't be 0, so we use the row index + 1
		pData = &bookmark;
		bUpdatable = false;
	} else
		GetColumnData(row, column - 1, dbType, size, pData, bUpdatable);
}

///////////////////////////////////////////////////////////////////////////////
// Stuff needed because our storage object passes on the call it gets for
// column information, we own the column map.
template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
ATLCOLUMNINFO* CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::StorageProxy_GetColumnInfo(
	ULONG *pcCols)
{
	if (!m_pColumnInfo) // If we've never been called before, build the column map...
		BuildColumnInfo();

ULONG cCols = m_NumCols;
ATLCOLUMNINFO *pRetCols = m_pColumnInfo;

	if (!BookmarksRequired()) {
	// The column info map always contains the bookmark column as the first col,
	// If bookmarks aren't required, pass out all but the first column info struct, 
	// and adjust the count to suit.
		pRetCols++;
		cCols--;
	}

	if (pcCols != NULL)
		*pcCols = cCols;

	return pRetCols;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
void CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::BuildColumnInfo()
{
// columns start at 1, 0 is reserved for the bookmark column which may or may
// not be required, the actual ATLCOLUMNINFO entry for 0 is always present though
const size_t numCols = GetNumColumns();
	
	m_NumCols = numCols + 1;	 // Add one for the bookmark column
	m_pColumnInfo = new ATLCOLUMNINFO[m_NumCols];

ULONG ulCols = 0;

// Always add the bookmark column
// TODO: This should be called something other than "Bookmark"...

	m_pColumnInfo[ulCols].pwszName = ustrdup("Bookmark");
	m_pColumnInfo[ulCols].pTypeInfo = (ITypeInfo*)NULL; 
	m_pColumnInfo[ulCols].iOrdinal = ulCols;
	m_pColumnInfo[ulCols].dwFlags = DBCOLUMNFLAGS_ISBOOKMARK; 
	m_pColumnInfo[ulCols].ulColumnSize = sizeof(DWORD);
	m_pColumnInfo[ulCols].wType = DBTYPE_BYTES; 
	m_pColumnInfo[ulCols].bPrecision = 0; 
	m_pColumnInfo[ulCols].bScale = 0;
	m_pColumnInfo[ulCols].cbOffset = 0; 
	memset(&(m_pColumnInfo[ulCols].columnid), 0, sizeof(DBID));
	m_pColumnInfo[ulCols].columnid.uName.pwszName = m_pColumnInfo[ulCols].pwszName;

	ulCols++;

ULONG offset = sizeof(DWORD);

	for (size_t i = 0; i<numCols; i++) {
	// Next set the other columns up.
	DBTYPE dbType; 
	ULONG size; 
	string columnName;
	DWORD flags = DBCOLUMNFLAGS_ISFIXEDLENGTH | DBCOLUMNFLAGS_WRITE;

		GetColumnInformation(i, dbType, size, columnName, flags);

		m_pColumnInfo[ulCols].pwszName = ustrdup(columnName.c_str());
		m_pColumnInfo[ulCols].pTypeInfo = (ITypeInfo*)NULL; 
		m_pColumnInfo[ulCols].iOrdinal = ulCols; 
		m_pColumnInfo[ulCols].dwFlags = flags;
		m_pColumnInfo[ulCols].ulColumnSize = size;
		m_pColumnInfo[ulCols].wType = dbType;
		m_pColumnInfo[ulCols].bPrecision = 0xFF; 
		m_pColumnInfo[ulCols].bScale = 0xFF;
		m_pColumnInfo[ulCols].cbOffset = offset;
		memset(&(m_pColumnInfo[ulCols].columnid), 0, sizeof(DBID)); 
		m_pColumnInfo[ulCols].columnid.uName.pwszName = m_pColumnInfo[ulCols].pwszName;

		offset += size; 		// offset isn't used by us.
		ulCols++;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Stuff needed because our ArrayType is just a proxy that forwards all 
// significant requests on to us. We own the data that our recordset represents!
template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
int CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::ArrayProxy_GetSize() const
{
	return GetNumRows();
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
unsigned char &CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::ArrayProxy_IndexOperator(
	int nIndex) const
{
// This should never be called. We dont access the ArrayType using [], but the standard
// templates do and even though we're not using the code that does use [] we have to 
// have one because VC doesnt quite conform to how templates are supposed to work (It
// should only require a function if we actually use it, we dont use it, so it shouldnt
// require it...)
// As such we assert, but we also have to return something or the compiler gets upset...
	ATLASSERT(false);
	
	static unsigned char bugger = 'c';
	return bugger;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
BOOL CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::ArrayProxy_Add(
	Storage &/*storage*/)
{
// The standard ATL OLE DB Provider templates add a new row by creating an instance of
// the rowset class's Storage object and calling Add() on the ArrayType object...
// Our Storage and ArrayType objects are just thin proxies that pass all calls on to
// the Rowset, so we ignore the Storage that's passed in (it's meaningless to us) and
// assume that the Rowset knows how to add a row when we call AddRow()

	return AddRow();
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
BOOL CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::ArrayProxy_RemoveAt(
	int nIndex)
{
// The standard ATL OLE DB Provider templates use an array class as their ArrayType,
// removing a row (which isn't actually done in the standard provider...) can be achieved
// simply by calling RemoveAt(). Our ArrayType is a proxy that passes the call on to us, 
// we call RemoveRow() on the derived Rowset and leave it up to it how or if it does the 
// job.

	return RemoveRow(nIndex);
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
void CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::ArrayProxy_RemoveAll()
{
// The standard ATL OLE DB Provider templates use an array class as their ArrayType,
// RemoveAllRows() is called when the ArrayType object is destroyed, Our ArrayType is 
// a proxy that passes the call on to us, we call RemoveAllRows() on the derived Rowset 
// and leave it up to it how or if it does the job.

	RemoveAllRows();
}

///////////////////////////////////////////////////////////////////////////////
// Default implementations of AddRow(), RemoveRow() and RemoveAllRows() so that
// if the derived Rowset doesnt need them it doesnt have to provide these empty
// implementations....
///////////////////////////////////////////////////////////////////////////////

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
HRESULT CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::AddRow() 
{
	// By default do nothing
	return E_NOTIMPL;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
HRESULT CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::RemoveRow(
	int nIndex)
{
	// By default do nothing
	return E_NOTIMPL;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
void CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::RemoveAllRows()
{
	// By default do nothing
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
wchar_t *CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::ustrdup(const char *pIn)
{
size_t length = strlen(pIn) + 1;
wchar_t *pOut = new wchar_t[length];
	
	if (pOut)
		mbstowcs(pOut, pIn, length);

	return pOut;
}

template <class DataClass, class T, class CreatorClass, class Storage, class ArrayType, class RowClass, class RowsetInterface>
HRESULT CProxyRowsetImpl<DataClass, T, CreatorClass, Storage, ArrayType, RowClass, RowsetInterface>::Execute(DBPARAMS * pParams, LONG* pcRowsAffected)
{
	// This should never be used
	return E_NOTIMPL;
}

#endif // !defined(_PROXYROWSETIMPL_H__ABDE07C0_69D8_4DA0_B565_466F55C27FC4__INCLUDED_)
