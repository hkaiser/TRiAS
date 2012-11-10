// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.06.2001 14:58:25 
//
// @doc
// @module ITableDefinitionImpl.h | Declaration of the <c ITableDefinitionImpl> class

#if !defined(_ITABLEDEFINITIONIMPL_H__87EB9AEF_9708_47CC_AF34_419291D4D9C6__INCLUDED_)
#define _ITABLEDEFINITIONIMPL_H__87EB9AEF_9708_47CC_AF34_419291D4D9C6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDB/DBId.h>		// CDBID

///////////////////////////////////////////////////////////////////////////////
// ITableDefinitionImpl
template<typename T, typename Base = ITableDefinition>
class ATL_NO_VTABLE ITableDefinitionImpl :
	public Base
{
public:
// bei Fehler bereits erzeugte Tabelle wieder löschen, oder für Verwaltung
// temporärer Tabellen
	class CCreateTableWrapper
	{
	public:
		CCreateTableWrapper(T *pSession, CDBID &rTableId) :
			m_pSession(pSession), m_rTableId(rTableId), m_fValidated(false)
		{
			_ASSERTE(NULL != m_pSession);
		}
		~CCreateTableWrapper()
		{
			if (!m_fValidated) {
			ULONG iCount = m_Columns.GetCount();

				for (ULONG ul = 0; ul < iCount; ++ul)
					m_pSession -> DropExistingColumn(&m_rTableId, &m_Columns.GetData()[ul]);
				m_pSession->DropExistingTable(&m_rTableId);
			}
		}

		HRESULT AddColumn (const DBID *pColumnId)
		{
			_ASSERTE(NULL != pColumnId);
			return m_Columns.Add(CDBID(*pColumnId)) ? S_OK : E_OUTOFMEMORY;
		}
		void Validate() { m_fValidated = true; }

	private:
		T *m_pSession;
		CDBID &m_rTableId;
		CAtlArray<CDBID> m_Columns;
		bool m_fValidated;
	};

// ITableDefinition
	STDMETHODIMP CreateTable(
			IUnknown *pUnkOuter, DBID *pTableID, ULONG cColumnDescs,
            const DBCOLUMNDESC rgColumnDescs[], REFIID riid,
            ULONG cPropertySets, DBPROPSET rgPropertySets[],
            DBID **ppTableID, IUnknown **ppRowset)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ITableDefinitionImpl::CreateTable\n");

	// Parameter prüfen
	T *pT = static_cast<T *>(this);

		if (NULL == pTableID && NULL == ppTableID)
			return E_INVALIDARG;
		if (FAILED(pT->SetPropertiesArgChk(cPropertySets, rgPropertySets)))
			return E_INVALIDARG;
		if (FAILED(pT->SetColumnPropertiesArgChk(cColumnDescs, rgColumnDescs)))
			return E_INVALIDARG;

	T::ObjectLock cab(pT);

	CDBID TableId;
	HRESULT hr = S_OK;

		if (NULL == pTableID) {
			hr = pT->GetUniqueTableId(&TableId);
			if (FAILED(hr))
				return hr;
			pTableID = &TableId;
		}
		else if (S_OK != CDBIDOps::IsValidDBID(pTableID))
			return DB_E_BADTABLEID;

	// doppelten Namen vermeiden
		if (S_OK == pT->IsExistingTable(pTableID))
			return DB_E_DUPLICATETABLEID;	// Tabelle existiert bereits

	// Tabelle erzeugen
		hr = pT->CreateNewTable(pTableID);
		if (FAILED(hr)) return hr;

	CCreateTableWrapper Wrap(pT, CDBID(*pTableID));

	// zugehörige Spalten erzeugen
		for (ULONG ulCols = 0; ulCols < cColumnDescs; ++ulCols) {
		// Parameter testen
			if (S_OK != CDBIDOps::IsValidDBID(&rgColumnDescs[ulCols].dbcid)) {
				hr = DB_E_BADCOLUMNID;
				break;
			}

		// Spalte erzeugen lassen
			hr = pT->CreateNewColumn(pTableID, &rgColumnDescs[ulCols]);
			if (FAILED(hr)) break;

			hr = Wrap.AddColumn(&rgColumnDescs[ulCols].dbcid);
			if (FAILED(hr)) break;
		}

	// bei Fehler wieder alles löschen
		if (FAILED(hr)) return hr;

	// neuen Recordset erzeugen
		hr = pT->OpenRowset(pUnkOuter, pTableID, NULL, riid, cPropertySets, rgPropertySets, ppRowset);
		if (SUCCEEDED(hr))
			Wrap.Validate();		// Tabelle nicht wieder löschen

		return hr;
	}
	STDMETHODIMP DropTable(DBID *pTableID)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ITableDefinitionImpl::DropTable\n");

	// Parameter prüfen
		if (NULL == pTableID)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(pTableID))
			return DB_E_BADTABLEID;

	T *pT = static_cast<T *>(this);
	T::ObjectLock cab(pT);

		if (FAILED(pT->IsExistingTable(pTableID)))
			return DB_E_NOTABLE;		// Tabelle existiert nicht
		if (S_OK == pT->IsTableInuse(pTableID))
			return DB_E_TABLEINUSE;		// Tabelle derzeit in Nutzung

		return pT->DropExistingTable(pTableID);
	}
	STDMETHODIMP AddColumn(DBID *pTableID, DBCOLUMNDESC *pColumnDesc, DBID **ppColumnID)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ITableDefinitionImpl::AddColumn\n");

	// Parameter prüfen
	T *pT = static_cast<T *>(this);

		if (NULL == pTableID)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(pTableID))
			return DB_E_BADTABLEID;

		if (NULL == pColumnDesc)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(&pColumnDesc->dbcid))
			return DB_E_BADCOLUMNID;

		if (FAILED(pT->SetColumnPropertiesArgChk(1, pColumnDesc)))
			return E_INVALIDARG;

	T::ObjectLock cab(pT);

		if (FAILED(pT->IsExistingTable(pTableID)))
			return DB_E_NOTABLE;		// Tabelle existiert nicht
		if (S_OK == pT->IsTableInuse(pTableID))
			return DB_E_TABLEINUSE;		// Tabelle derzeit in Nutzung
		if (S_OK == pT->IsExistingColumn(pTableID, &pColumnDesc->dbcid))
			return DB_E_DUPLICATECOLUMNID;	// Spalte existiert bereits

		return pT->CreateNewColumn(pTableID, pColumnDesc, ppColumnID);
	}
	STDMETHODIMP DropColumn(DBID *pTableID, DBID *pColumnID)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ITableDefinitionImpl::DropColumn\n");

	// Parameter prüfen
		if (NULL == pTableID)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(pTableID))
			return DB_E_BADTABLEID;
		if (NULL == pColumnID)
			return E_INVALIDARG;
		if (S_OK != CDBIDOps::IsValidDBID(pColumnID))
			return DB_E_BADCOLUMNID;

	T *pT = static_cast<T *>(this);
	T::ObjectLock cab(pT);

		if (FAILED(pT->IsExistingTable(pTableID)))
			return DB_E_NOTABLE;		// Tabelle existiert nicht
		if (S_OK == pT->IsTableInuse(pTableID))
			return DB_E_TABLEINUSE;		// Tabelle derzeit in Nutzung
		if (FAILED(pT->IsExistingColumn(pTableID, pColumnID)))
			return DB_E_NOCOLUMN;		// Spalte exitiert nicht

		return pT->DropExistingColumn(pTableID, pColumnID);
	}

protected:
// function provides unique tablename
	HRESULT GetUniqueTableId (DBID *pTableId)
	{
		if (NULL == pTableId) 
			return E_POINTER;

	CString strName;

		for (int i = 0; i < 64; ++i) {		// REVIEW: is 64 enough?
			strName.Format ("NewTable%02d", i);

		CDBID TableId(strName);
		HRESULT hr = static_cast<T *>(this)->IsExistingTable(&TableId);

			if (FAILED(hr)) {
				if (DB_E_NOTABLE != hr) 
					return hr;
			
			// Table does not exist
				return CDBIDOps::CopyDBIDs(pTableId, &TableId);
			}
		}
		return DB_E_NOTABLE;
	}
	HRESULT IsExistingTable (DBID *pTableId, INT_PTR *plIdent = NULL)
	{
		return DB_E_NOTABLE;	// overload this or GetUniqueTableId
	}
	HRESULT CreateNewTable (DBID *pTableId, INT_PTR *plIdent = NULL)
	{
		return E_NOTIMPL;		// overload to create new Table
	}
	HRESULT DropExistingTable (DBID *pTableId)
	{
		return E_NOTIMPL;		// overload to drop a table
	}
	HRESULT IsExistingColumn (DBID *pTableId, DBID *pColumnId, INT_PTR *plAttrib = NULL)
	{
		return DB_E_NOCOLUMN;
	}
	HRESULT CreateNewColumn (DBID *pTableID, const DBCOLUMNDESC *pColumnDesc, DBID **ppColumnID = NULL, INT_PTR *plAttrib = NULL)
	{
		return E_NOTIMPL;		// overload to create new column
	}
	HRESULT DropExistingColumn (DBID *pTableID, DBID *pColumnID)
	{
		return E_NOTIMPL;		// overload to drop a column
	}

// Testen der Gültigkeit sämtlicher ColumnProperties
	HRESULT SetColumnPropertiesArgChk(const ULONG cColumnDescs, const DBCOLUMNDESC rgColumnDescs[])
	{
		if (0 != cColumnDescs && NULL == rgColumnDescs)
			return E_INVALIDARG;

	T *pT = static_cast<T *>(this);

		for (ULONG ul = 0; ul < cColumnDescs; ++ul) {
		HRESULT hr = pT->SetPropertiesArgChk(rgColumnDescs[ul].cPropertySets, rgColumnDescs[ul].rgPropertySets);

			if (FAILED(hr))
				return hr;
		}
		return S_OK;
	}
};

#endif // !defined(_ITABLEDEFINITIONIMPL_H__87EB9AEF_9708_47CC_AF34_419291D4D9C6__INCLUDED_)
