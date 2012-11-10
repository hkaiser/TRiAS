// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.06.2001 18:46:46 
//
// @doc
// @module IAlterTableImpl.h | Declaration of the <c IAlterTableImpl> class

#if !defined(_IALTERTABLEIMPL_H__4183F39E_2B49_41B5_9B6D_4DAC3F61D1D8__INCLUDED_)
#define _IALTERTABLEIMPL_H__4183F39E_2B49_41B5_9B6D_4DAC3F61D1D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// IAlterTableImpl
template<typename T>
class ATL_NO_VTABLE IAlterTableImpl :
	public IAlterTable
{
public:
	STDMETHODIMP AlterColumn(DBID *pTableId, DBID *pColumnId, 
		DBCOLUMNDESCFLAGS rgColumnDescFlags, DBCOLUMNDESC *pColumnDesc)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IAlterTableImpl::AlterColumn\n");

	// Parameter prüfen
		if (NULL == pTableId)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(pTableId))
			return DB_E_BADTABLEID;
		if (NULL == pColumnId)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(pColumnId))
			return DB_E_BADCOLUMNID;

		if (0 == rgColumnDescFlags)
			return S_OK;		// nothing to do
		if ((DBCOLUMNDESCFLAGS_PROPERTIES & rgColumnDescFlags) == rgColumnDescFlags && 
			0 == pColumnDesc->cPropertySets)
		{
			return S_OK;		// nothing to do
		}
		if ((DBCOLUMNDESCFLAGS_DBCID & rgColumnDescFlags) == rgColumnDescFlags && 
			S_OK == CDBIDOps::CompareDBIDs(pColumnId, &pColumnDesc->dbcid))
		{
			return S_OK;		// nothing to do
		}

	// jetzt Spalte wirklich modifizieren
	T *pT = static_cast<T *>(this);
	T::ObjectLock cab(pT);

		return pT->AlterExistingColumn(pTableId, pColumnId, rgColumnDescFlags, pColumnDesc);
	}
	STDMETHODIMP AlterTable(DBID *pTableId, DBID *pNewTableId, ULONG cPropertySets, DBPROPSET rgPropertySets[])
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IAlterTableImpl::AlterTable\n");

	// Parameter prüfen
		if (NULL == pTableId)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(pTableId))
			return DB_E_BADTABLEID;
		if (NULL != pNewTableId && S_OK != CDBIDOps::IsValidDBID(pNewTableId))
			return DB_E_BADTABLEID;

	T *pT = static_cast<T *>(this);

		if (FAILED(pT->SetPropertiesArgChk(cPropertySets, rgPropertySets)))
			return E_INVALIDARG;

	T::ObjectLock cab(pT);

	// Sicherstellen, daß Tabelle existiert und modifiziert werden kann
		if (FAILED(pT->IsExistingTable(pTableId)))
			return DB_E_NOTABLE;	// Tabelle existiert nicht
		if (NULL != pNewTableId && S_OK == pT->IsExistingTable(pNewTableId))
			return DB_E_DUPLICATETABLEID;

		if (S_OK == pT->IsTableInuse(pTableId))
			return DB_E_TABLEINUSE;	// Tabelle derzeit in Nutzung

		if (NULL != pNewTableId && S_OK == CDBIDOps::CompareDBIDs(pTableId, pNewTableId) && 0 == cPropertySets)
			return S_OK;			// nothing to do

		return pT->AlterExistingTable(pTableId, pNewTableId, cPropertySets, rgPropertySets);
	}

protected:
	HRESULT AlterExistingTable (DBID *pTableId, DBID *pNewTableId, ULONG cPropertySets, DBPROPSET rgPropertySets[])
	{
		return E_NOTIMPL;		// overload to implement table alteration
	}
	HRESULT AlterExistingColumn(DBID *pTableId, DBID *pColumnId, DBCOLUMNDESCFLAGS rgColumnDescFlags, DBCOLUMNDESC *pColumnDesc)
	{
		return E_NOTIMPL;		// overload to implement column alteration
	}
};

#endif // !defined(_IALTERTABLEIMPL_H__4183F39E_2B49_41B5_9B6D_4DAC3F61D1D8__INCLUDED_)
