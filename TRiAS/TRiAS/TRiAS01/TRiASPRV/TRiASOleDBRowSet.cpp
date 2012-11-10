// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.05.2001 11:47:12 
//
// @doc
// @module TRiASOleDBRS.cpp | Definition of the <c CTRiASOleDBCommand> class

#include "stdafx.h"

#include <Atl/CieThis.h>

#include "GenerateColumnInfo.h"
#include "GenerateObjectsCollection.h"

#include "TRiASOleDBRowSet.h"
#include "TRiASOleDBSession.h"
#include "TRiASOleDBDataSource.h"
#include "SchemaRowsets.h"
#include "TRiASOleDBGetSession.h"
#include "TRiASOleDBColumnDesc.h"

#include "AtlColumnInfo.h"
#include "OrderByPredicates.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// initialisation etc.
void CTRiASOleDBRowset::FinalRelease()
{
CTRiASOleDBSession *pSession = NULL;

	if (SUCCEEDED(GetSessionObject(this, &pSession))) {
	ULONG iCount = m_BoundTables.GetCount();

		for (ULONG ul = 0; ul < iCount; ++ul) {
		CDBID TableId (m_BoundTables.GetData()[ul]);

			pSession -> UnregisterTable(&TableId);
		}
	}
	_RowsetBaseClass::FinalRelease();
}

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBRowset
STDMETHODIMP CTRiASOleDBRowset::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRowset,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

bool CTRiASOleDBRowset::IsDerivedFromCommand (CTRiASOleDBCommand **ppCommand)
{
	_ASSERTE(NULL != ppCommand);
	*ppCommand = NULL;

CComPtr<ICommand> spCommand;

	if (FAILED(GetSite (IID_ICommand, (void **)&spCommand)))
		return false;		// nicht vom Command abgeleitet

	return SUCCEEDED(QueryImplementation(spCommand, CLSID_TRiASOleDBCommand, ppCommand)) ? true : false;
}

HRESULT CTRiASOleDBRowset::Execute(DBPARAMS *pParams, LONG *pcRowsAffected)
{
// Daten auf der Grundlage der Kriterien zusammensuchen
ObjectLock lock(this);

// wenn der Recordset aus einem Command kommt, dann ggf. die dortigen Daten verwenden
CTRiASOleDBCommand *pCommand = NULL;

	if (IsDerivedFromCommand(&pCommand)) {
	// vom Command erzeugt
		m_pGenColInfo = pCommand -> GetGeneratedColunmInfo();
		if (NULL == m_pGenColInfo)
			return OleDBError(E_OUTOFMEMORY);
		m_fAttachedColInfo = true;
		m_fIsCommandBased = true;
	} 

// ggf. GenColInfo erzeugen	
	if (NULL == m_pGenColInfo) {
	// alles lokal anlegen
		ATLTRY(m_pGenColInfo = new CGenerateColumnInfo<&IID_IRowset>());
		if (NULL == m_pGenColInfo) return OleDBError(E_OUTOFMEMORY);

		m_fAttachedColInfo = false;
	}
	_ASSERTE(NULL != m_pGenColInfo);

STATEMENT_TYPE rgStmtType = STATEMENT_TYPE_UNKNOWN;
HRESULT hr = S_OK;

	MAKE_OLEDB_ERROR(m_pGenColInfo->PrepareStatement(m_strCommandText, &rgStmtType));

	switch (rgStmtType) {
	case STATEMENT_TYPE_UPDATE:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_SELECT:
		RETURN_ERROR(ExecuteSelect (pParams, pcRowsAffected));
		break;

	case STATEMENT_TYPE_INSERT:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_DELETE:
		hr = OleDBError(E_NOTIMPL);
		break;

	case STATEMENT_TYPE_CREATETABLE:
		RETURN_ERROR(ExecuteCreateTable (pParams, pcRowsAffected));
		pCommand -> m_bRowsetReturned = false;	// keinen Rowset liefern
		break;

	case STATEMENT_TYPE_DROPTABLE:
		RETURN_ERROR(ExecuteDropTable (pParams, pcRowsAffected));
		pCommand -> m_bRowsetReturned = false;	// keinen Rowset liefern
		break;

	default:
	case STATEMENT_TYPE_UNKNOWN:
		hr = OleDBError(DB_E_ERRORSINCOMMAND);
		break;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Select Statement auswerten
HRESULT CTRiASOleDBRowset::ExecuteSelect (DBPARAMS *pParams, LONG *pcRowsAffected)
{
// feststellen, wieviele Rows maximal geliefert werden sollen
ULONG ulMaxRows = 0;
CComVariant vMaxRows(0, VT_I4);
HRESULT hr = GetPropValue(&DBPROPSET_ROWSET, DBPROP_MAXROWS, &vMaxRows);

	if (SUCCEEDED(hr) && SUCCEEDED(vMaxRows.ChangeType(VT_UI4)))
		ulMaxRows = V_UI4(&vMaxRows);

// vorbereitende Selektionsaufgaben
CComPtr<ITRiASEnumNativeObjects> Objs;

	RETURN_ERROR(PrepareColumnInfo());			// benötigte Spalten
	RETURN_ERROR(PrepareObjectsList(&Objs));	// Objektmenge

// Distinct auswerten
CComPtr<IParser> Parser;
CComPtr<ISelectStmt> Select;
CComBool fDistinct;

	MAKE_OLEDB_ERROR(m_pGenColInfo -> GetParser(&Parser));
	MAKE_OLEDB_ERROR(Parser -> get_SelectStmt(&Select));
	MAKE_OLEDB_ERROR(Select -> get_Distinct(&fDistinct))

// ggf. TOP num [PERCENT] auswerten
ULONG ulTopRows = 0;
CComBool fPercent;

	MAKE_OLEDB_ERROR(Select -> get_TopRows(&ulTopRows));
	if (0 != ulTopRows) {
		MAKE_OLEDB_ERROR(Select -> get_TopRowsPercent(&fPercent));
		ulMaxRows = ulTopRows;
	}

// ggf. 'ORDER BY' auswerten
CComPtr<IOrderByObjList> OrderByList;
LONG lOrderByCnt = 0;

	MAKE_OLEDB_ERROR(Select -> get_OrderByObjList(&OrderByList));
	MAKE_OLEDB_ERROR(OrderByList -> get_Count(&lOrderByCnt));

// rudimentären Rowset bauen
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR_EX2(Objs -> get__NewEnum(&UnkEnum), E_UNEXPECTED);

CComQIPtr<IEnumVARIANT> Enum(UnkEnum);
CComVariant vObj;

	_ASSERTE(Enum != NULL);
	for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&vObj), NULL); /**/) {
		_ASSERTE(VT_I4 == V_VT(&vObj));

	CTRiASOleDBRow Row (*this, V_I4(&vObj));

		if (fDistinct) {
		// nachsehen, ob es eine identische zeile vielleicht schon gibt
		bool fContinue  = false;
		ULONG iCount = m_rgRowData.GetCount();

			for (ULONG ul = 0; ul < iCount; ++ul) {
				if (S_OK == Row.CompareRows (m_rgRowData.GetData()[ul])) {
					fContinue = true;
					break;	// eine solche Row gibt es schon
				}
			}
			if (fContinue)
				continue;
		}

	// diese Row zum Rowset hinzufügen
		if (!AddRow(Row))
			return OleDBError(E_OUTOFMEMORY);

	// ggf. nur eine bestimmte Anzahl von Rows liefern
		if (!fPercent && 0 == lOrderByCnt && 0 != ulMaxRows && m_rgRowData.GetCount() >= ulMaxRows)
			break;		// genug für heute
	}

	if (lOrderByCnt > 0) {
	// ORDER BY ist gegeben, in umgekehrter Reihenfolge sortieren
		for (LONG i = lOrderByCnt; i > 0; --i) {
		// Informationen über zu sortierende Spalte heraussuchen
		CComVariant vItem;

			RETURN_ERROR(OrderByList -> get_Item (i, &vItem));
			_ASSERTE(V_ISDISPATCH(&vItem));

		CComQIPtr<IOrderByObj> OrderBy (V_DISPATCH(&vItem));

			if (OrderBy == NULL) return OleDBError(E_UNEXPECTED);

		CComBool fAsc;		// aufsteigend sortieren ?
		CComPtr<IColumnIdent> Column;

			MAKE_OLEDB_ERROR(OrderBy -> get_Asc(&fAsc));
			MAKE_OLEDB_ERROR(OrderBy -> get_ColumnIdent(&Column));

		// jetzt wirklich sortieren
		ULONG ulColumn = 0;
		INT_PTR hPr = GetProjectHandle();
		size_t iCount = m_rgRowData.GetCount();

			RETURN_ERROR(FindColumnId (Column, &ulColumn));

		ULONG ulColumnCorr = ulColumn + (GetUseBookmarks() ? 0 : 1);

			_ASSERTE(!(DBCOLUMNFLAGS_ISBOOKMARK & m_pGenColInfo->GetColumnInfo().GetColumnInfo().GetData()[ulColumn].dwFlags));
			if (DBCOLUMNFLAGS_ISROWID & m_pGenColInfo->GetColumnInfo().GetColumnInfo().GetData()[ulColumn].dwFlags) {
			// Bookmark/Objektnummer
			COrderByPredAscONr OrderBy(hPr, ulColumnCorr);

				if (fAsc) {
				COrderByPredAscONr::CCompareHook Hook(&OrderBy, COrderByPredAscONr::compare);

					qsort (m_rgRowData.GetData(), iCount, sizeof(CTRiASOleDBRow), Hook.GetThunk());
				} 
				else {
				COrderByPredAscONr::CCompareHook Hook(&OrderBy, COrderByPredAscONr::invcompare);

					qsort (m_rgRowData.GetData(), iCount, sizeof(CTRiASOleDBRow), Hook.GetThunk());
				}
			}
			else if (DBTYPE_WSTR == m_pGenColInfo->GetColumnInfo().GetColumnInfo().GetData()[ulColumn].wType) {
			// als BSTR gespeicherte Daten
			COrderByPredAsc OrderBy(hPr, ulColumnCorr);

				if (fAsc) {
				COrderByPredAsc::CCompareHook Hook(&OrderBy, COrderByPredAsc::compare);

					qsort (m_rgRowData.GetData(), iCount, sizeof(CTRiASOleDBRow), Hook.GetThunk());
				} 
				else {
				COrderByPredAsc::CCompareHook Hook(&OrderBy, COrderByPredAsc::invcompare);

					qsort (m_rgRowData.GetData(), iCount, sizeof(CTRiASOleDBRow), Hook.GetThunk());
				}
			}
			else {
			// binär vergleichen
			COrderByPredAscBin OrderBy(hPr, ulColumnCorr);

				if (fAsc) {
				COrderByPredAscBin::CCompareHook Hook(&OrderBy, COrderByPredAscBin::compare);

					qsort (m_rgRowData.GetData(), iCount, sizeof(CTRiASOleDBRow), Hook.GetThunk());
				} 
				else {
				COrderByPredAscBin::CCompareHook Hook(&OrderBy, COrderByPredAscBin::invcompare);

					qsort (m_rgRowData.GetData(), iCount, sizeof(CTRiASOleDBRow), Hook.GetThunk());
				}
			}

		// Bookmarks neu erzeugen
		CBookmarkMap mapBmks;

			for (size_t i = 0; i < iCount; ++i) {
			size_t iCnt = mapBmks.size();

				ATLTRY(mapBmks.insert(CBookmarkMap::value_type(m_rgRowData[i].GetBookmark(), i)));
				if (iCnt != mapBmks.size()-1) 
					return OleDBError(E_OUTOFMEMORY);
			}
			m_Bookmarks.swap(mapBmks);
		}

	// ggf. nur die ersten Rows liefern
		if (0 != ulMaxRows) {
		size_t iCount = m_rgRowData.GetCount();

			ulTopRows = ulMaxRows;
			if (fPercent) 
				ulTopRows = ulMaxRows * iCount;
			for (ULONG ulIndex = iCount-1; ulIndex >= ulTopRows; --ulIndex)
				m_rgRowData.RemoveAt(ulIndex);
			_ASSERTE(m_rgRowData.GetCount() == ulTopRows);
		}
	}
	else if (fPercent) {
	// nur die ersten ulMaxRows Prozent liefern
	size_t iCount = m_rgRowData.GetCount();

		ulTopRows = ulMaxRows * iCount;
		for (ULONG ulIndex = iCount-1; ulIndex >= ulTopRows; --ulIndex)
			m_rgRowData.RemoveAt(ulIndex);
		_ASSERTE(m_rgRowData.GetCount() == ulTopRows);
	}

// benutzte Tabellen registrieren
	if (m_fIsCommandBased) 
		RegisterTables (Select);
		
// Anzahl der erzeugten Rows liefern
	if (pcRowsAffected != NULL)
		*pcRowsAffected = m_rgRowData.GetCount();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Tabelle erzeugen

HRESULT CTRiASOleDBRowset::ExecuteCreateTable(DBPARAMS *pParams, LONG *pcRowsAffected)
{
	if (!m_fIsCommandBased)
		return OleDBError(E_UNEXPECTED);

CComPtr<IParser> Parser;
CComPtr<ICreateTableStmt> CreateTable;

	MAKE_OLEDB_ERROR(m_pGenColInfo -> GetParser(&Parser));
	MAKE_OLEDB_ERROR(Parser -> get_CreateTableStmt(&CreateTable));

CComPtr<ITableIdent> TableIdent;
CComBSTR bstrTable;

	MAKE_OLEDB_ERROR(CreateTable -> get_TableIdent(&TableIdent));
	MAKE_OLEDB_ERROR(TableIdent -> get_Name(&bstrTable));

	bstrTable = RemoveQuotes(bstrTable);
	MAKE_OLEDB_ERROR(SplitTableName(bstrTable));

// Tabelle erzeugen
CDBID TableId (bstrTable);
CTRiASOleDBSession *pSession = NULL;

	MAKE_OLEDB_ERROR(GetSessionObject(this, &pSession));
	if (S_OK == pSession -> IsExistingTable(&TableId))
		return OleDBError(DB_E_DUPLICATETABLEID);	// Tabelle existiert bereits

	MAKE_OLEDB_ERROR(pSession -> CreateNewTable(&TableId));

// Spalten erzeugen
CTRiASOleDBSession::CCreateTableWrapper Wrap(pSession, TableId);
CComPtr<ICreateTableItemList> CreateItemList;

	MAKE_OLEDB_ERROR(CreateTable -> get_CreateTableItemList(&CreateItemList));

CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR(CreateItemList -> get__NewEnum(&UnkEnum));

CComQIPtr<IEnumVARIANT> Columns(UnkEnum);
CComVariant v;

	_ASSERTE(Columns != NULL);
	for (Columns -> Reset(); S_OK == Columns -> Next(1, &v, NULL); /**/) {
		_ASSERTE(V_ISDISPATCH(&v));
	
	CComQIPtr<ICreateTableItem> Column (V_DISPATCH(&v));
	CComBSTR bstrColumn;
	PARSER_DATATYPE rgType = PARSER_DATATYPE_UNKNOWN;

		MAKE_OLEDB_ERROR(Column -> get_ColName(&bstrColumn));
		MAKE_OLEDB_ERROR(Column -> get_DataType(&rgType))
	
	CObjectPropertyColumnDesc rgColumn(bstrColumn);

		if (S_OK != pSession -> IsExistingColumn(&TableId, &rgColumn.dbcid))
		{
			MAKE_OLEDB_ERROR(pSession -> CreateNewColumn (&TableId, &rgColumn));
		}
		MAKE_OLEDB_ERROR(Wrap.AddColumn(&rgColumn.dbcid));
	}

	Wrap.Validate();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Tabelle löschen
HRESULT CTRiASOleDBRowset::ExecuteDropTable(DBPARAMS *pParams, LONG *pcRowsAffected)
{
	if (!m_fIsCommandBased)
		return OleDBError(E_UNEXPECTED);

CComPtr<IParser> Parser;
CComPtr<IDropStmt> DropTable;

	MAKE_OLEDB_ERROR(m_pGenColInfo -> GetParser(&Parser));
	MAKE_OLEDB_ERROR(Parser -> get_DropTableStmt(&DropTable));

CComPtr<ITableIdent> TableIdent;
CComBSTR bstrTable;

	MAKE_OLEDB_ERROR(DropTable -> get_TableIdent(&TableIdent));
	MAKE_OLEDB_ERROR(TableIdent -> get_Name(&bstrTable));

	bstrTable = RemoveQuotes(bstrTable);
	MAKE_OLEDB_ERROR(SplitTableName(bstrTable));

// Tabelle erzeugen
CDBID TableId (bstrTable);
CTRiASOleDBSession *pSession = NULL;

	MAKE_OLEDB_ERROR(GetSessionObject(this, &pSession));
	if (S_OK != pSession -> IsExistingTable(&TableId))
		return OleDBError(DB_E_NOTABLE);	// Tabelle existiert nicht

	MAKE_OLEDB_ERROR(pSession -> DropExistingTable(&TableId));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Wiederfinden einer Spalte über den [Table.]Namen
HRESULT CTRiASOleDBRowset::FindColumnId (IColumnIdent *pIIdent, ULONG *pulColId)
{
	_ASSERTE(NULL != pulColId);

CComBSTR bstrName, bstrTableName;

	MAKE_OLEDB_ERROR(pIIdent -> get_ColumnName(&bstrName));
	bstrName = RemoveQuotes(bstrName);

// sicherstellen, daß die Tabelle wirklich existiert
	MAKE_OLEDB_ERROR(pIIdent -> get_TableName(&bstrTableName));
	if (0 == bstrTableName.Length()) {
	// keine Tabelle gegeben
		MAKE_OLEDB_ERROR(m_pGenColInfo->GetColumnInfo().GetColumnId(bstrName, pulColId));
	}
	else {
	// Tabellennamen ggf. in Objektklasse/Objekttyp zerlegen
		bstrTableName = m_pGenColInfo->ResolveTableAlias(RemoveQuotes(bstrTableName));
		MAKE_OLEDB_ERROR(SplitTableName(bstrTableName));

	// überprüfen, ob die gegebene Tabelle wirklich existiert
	INT_PTR lIdent = 0;

		if (FAILED(m_pDataSource -> get_Class (bstrTableName, &lIdent)))
			return OleDBError(DB_E_NOTABLE);		// Tabelle existiert nicht

	// überprüfen, ob die gegebene Spalte (Objekteigenschaft) wirklich existiert
	INT_PTR lMCode = 0;

		if (FAILED(m_pDataSource -> get_Attribute (lIdent, bstrName, &lMCode))) {
			MAKE_OLEDB_ERROR(m_pGenColInfo->GetColumnInfo().GetColumnId(bstrName, pulColId));
		} 
		else {
			MAKE_OLEDB_ERROR(m_pGenColInfo->GetColumnInfo().GetColumnId(lMCode, pulColId));
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Menge der Objekte der Resultatmenge 
HRESULT CTRiASOleDBRowset::PrepareObjectsList(ITRiASEnumNativeObjects **ppIObjsOut)
{
ObjectLock lock(this);

// m_strCommand enthält entweder den SQL Befehl oder einen Tabellennamen
	MAKE_OLEDB_ERROR(EnsureDatabaseObject());

CGenerateObjectsCollection Helper (m_pGenColInfo);

	MAKE_OLEDB_ERROR(Helper.PrepareObjectsCollection(m_pDataSource, ppIObjsOut));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Zusammensuchen der Informationen zu den zu erzeugenden Spalten, inclusive
// der IFetchData Objekte, die die Daten dieser Spalten liefern
HRESULT CTRiASOleDBRowset::PrepareColumnInfo()
{
ObjectLock lock(this);

	_ASSERTE(NULL != m_pGenColInfo);
	if (m_pGenColInfo->IsPrepared()) 
		return S_OK;		// bereits alles vorbereitet

// m_strCommand enthält entweder den SQL Befehl oder einen Tabellennamen
	MAKE_OLEDB_ERROR(EnsureDatabaseObject());

// sicherstellen, daß die benötigten Columns bekannt sind
// wenn Bookmarks gefragt sind, dann zusätzliche Spalte einfügen
CComVariant varBookmarks;
HRESULT hr = GetPropValue(&DBPROPSET_ROWSET, DBPROP_BOOKMARKS, &varBookmarks);

	m_pGenColInfo->SetUseBookmarks(S_OK == hr && VARIANT_TRUE == varBookmarks.boolVal);
	RETURN_ERROR(m_pGenColInfo->PrepareColumnInfo(m_pDataSource));
	
	return S_OK;
}

