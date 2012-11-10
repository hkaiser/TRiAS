// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.05.2001 12:00:05 
//
// @doc
// @module GenerateColumnInfo.cpp | Definition of the <c CGenerateColumnInfoBase> class

#include "StdAfx.h"

#include "SQLVerification.h"
#include "SQLExpression.h"
#include "GenerateColumnInfo.h"

#include "TRiASOleDBSession.h"
#include "TRiASOleDBDataSource.h"
#include "SchemaRowsets.h"

#include "HandleBookmark.h"
#include "HandleObjectGuid.h"
#include "HandleNativeAttribute.h"
#include "HandleGeometry.h"
#include "HandleExpression.h"

///////////////////////////////////////////////////////////////////////////////
// Command ausführen, RowSet bilden
namespace {
	class CEmptyColumnInfoOnError
	{
	public:
		CEmptyColumnInfoOnError(CColumnInfo &rColInfo) :
			m_rColInfo(rColInfo), m_fEmptyArray(true)
		{
		}
		~CEmptyColumnInfoOnError()
		{
			if (m_fEmptyArray)
				m_rColInfo.RemoveAll();
		}

		void SetValid() 
		{ 
			_ASSERTE(m_rColInfo.IsValid());
			m_fEmptyArray = false; 
		}

	private:
		CColumnInfo &m_rColInfo;
		bool m_fEmptyArray;
	};
}

///////////////////////////////////////////////////////////////////////////////
// Stmt vorbereiten
HRESULT CGenerateColumnInfoBase::PrepareStatement(BSTR bstrCommand, STATEMENT_TYPE *prgType)
{
	if (!m_fPrepared) {
		m_Parser.Release();
		MAKE_OLEDB_ERROR(m_Parser.CoCreateInstance(CLSID_Parser));
		MAKE_OLEDB_ERROR(m_Parser -> ParseSQL (bstrCommand));	// SQL Statement vorbereiten
	}
	MAKE_OLEDB_ERROR(m_Parser -> get_StatementType(prgType));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// sicherstellen, daß die benötigten Columns bekannt sind
HRESULT CGenerateColumnInfoBase::PrepareColumnInfo (CTRiASOleDBSource *pDataSource)
{
	if (m_fPrepared) return S_OK;		// schon vorbereitet

// Wrapper fürs Leeren des ColumnFeldes bei Fehlern
CEmptyColumnInfoOnError colWrapper(m_ColInfo);

// wenn Bookmarks gefragt sind, dann zusätzliche Spalte einfügen
	if (m_fUseBookmark) {
	CAtlColumnInfo col (OLESTR("Bookmark"), DBCOL_SPECIALCOL, 2);

		col.cbOffset = 0;
		col.iOrdinal = 0;
		col.wType = DBTYPE_I4;
		col.ulColumnSize = sizeof(DWORD);
		col.bPrecision = 10;
		col.bScale = ~0;
		col.dwFlags = DBCOLUMNFLAGS_ISBOOKMARK|DBCOLUMNFLAGS_ISFIXEDLENGTH;
		if (!m_ColInfo.Add(col))
			return OleDBError(E_OUTOFMEMORY);

	// Bookmark hat kein Handlerobjekt (braucht keines)
		if (!m_ColInfo.Add(NULL))
			return OleDBError(E_OUTOFMEMORY);

		RETURN_ERROR(m_ColInfo.AddToBaseTables(CComBSTR(L"")));
	}

// zusammenstellen der Spalten im Resultat
CComPtr<ISelectStmt> Select;

	MAKE_OLEDB_ERROR(m_Parser -> get_SelectStmt(&Select));
	if (Select == NULL) return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_NOSELECTSTMT);

CComPtr<IGenericStackList> SelectExpressionList;

	MAKE_OLEDB_ERROR(Select -> get_SelectExpressionList(&SelectExpressionList));
	if (SelectExpressionList == NULL) return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_NOSELECTEXPRESSION);

// Feststellen, ob SPezialfall eine Tabelle gegeben ist
	RETURN_ERROR(GetSingleTableName(Select));

// Alias/Table Zuordnung speichern
	RETURN_ERROR(m_TableAliases.InitTableAliases(Select));

// jeder gelieferte Stack enthält eine Expression innerhalb des select stmts
CComVariant vStack;
LONG lCntColumns = 0;
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR(SelectExpressionList -> get__NewEnum(&UnkEnum));
	MAKE_OLEDB_ERROR(SelectExpressionList -> get_Count(&lCntColumns));

// alle Expressions durchgehen und Bezeichner und Datentyp feststellen
CComQIPtr<IEnumVARIANT> EnumStack (UnkEnum);
long lColumns = 0;
bool fFilled = false;
ULONG lOrd = 0;

	_ASSERTE(EnumStack != NULL);
	for (EnumStack -> Reset(); S_OK == EnumStack -> Next(1, &vStack, NULL) && !fFilled; /**/) {
		_ASSERTE(SUCCEEDED(vStack.ChangeType(VT_DISPATCH)));

	CComQIPtr<IGenericStack> Stack (V_DISPATCH(&vStack));

		if (Stack == NULL) 
			return OleDBError(E_UNEXPECTED);
	
		RETURN_ERROR(FillColumn (pDataSource, Stack, lOrd, &fFilled));
	}

	m_ColumnAliases.SetInitialized();			// Aliases jetzt gültig
	m_fPrepared = true;
	colWrapper.SetValid();						// Columns sind jetzt gültig
	return S_OK;
}

// die Spalte(n)beschreibung(en) aus einem Element der SelectList füllen
HRESULT CGenerateColumnInfoBase::FillColumn (
	CTRiASOleDBSource *pDataSource, IGenericStack *pIStack, ULONG &rlOrd, bool *pfFilled)
{
	_ASSERTE(NULL != pIStack && NULL != pfFilled);

// jede Expression kann aus mehreren Items bestehen
LONG lCntItems = 0;
LONG lCustCount = 0;
bool fHasStar = false;
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR(pIStack -> get__NewEnum (&UnkEnum));
	MAKE_OLEDB_ERROR(pIStack -> get_Count(&lCntItems));

CComQIPtr<IEnumVARIANT> EnumItem(UnkEnum);

	_ASSERTE(EnumItem != NULL);
	RETURN_ERROR(SelectHasStar(pDataSource, EnumItem, &fHasStar));

	if (fHasStar) {
	// 'select [Table.]* from tablename' separat behandeln
		_ASSERTE(1 == lCntItems);		// Star muß alleine stehen (snh, da Parser das abfängt)
		RETURN_ERROR(FillAllColumns(pDataSource, rlOrd, lCustCount));
	}
	else {
	CComBSTR bstrAsName;

		MAKE_OLEDB_ERROR(pIStack -> get_AsName(&bstrAsName));
		if (1 == lCntItems) {
		// Ausdruck besteht aus einem einzelnen Term
		CComVariant vItem;

			MAKE_OLEDB_ERROR(pIStack -> Peek(&vItem))
			_ASSERTE(V_ISDISPATCH(&vItem));

		CComQIPtr<IExpressionItem> Item (V_DISPATCH(&vItem));

			RETURN_ERROR(FillColumnFromSingleTerm(pDataSource, Item, rlOrd, lCustCount, bstrAsName));
		}
		else {
		// sonstiger Ausdruck, der in einer Spalte des ErgebnisRowSets mündet
			RETURN_ERROR(FillColumnFromExpression(pDataSource, pIStack, rlOrd, lCustCount, bstrAsName));
		}
	}
	*pfFilled = false;		// weitermachen
	return S_OK;
}

// alle Spalten einer oder mehrerer Tabellen hinzufügen
HRESULT CGenerateColumnInfoBase::FillAllColumns(
	CTRiASOleDBSource *pDataSource, ULONG &rlOrd, LONG &rlCustCount)
{
// Liste der abgefragten Tabellen holen
CComPtr<ISelectStmt> Select;

	MAKE_OLEDB_ERROR(m_Parser -> get_SelectStmt(&Select));

CComPtr<ITableIdentList> TableIdentList;

	MAKE_OLEDB_ERROR(Select -> get_TableIdentList(&TableIdentList));
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
		bstrTable = ResolveTableAlias(RemoveQuotes(bstrTable));

		if (!VerifyTableIsGiven (m_Parser, bstrTable))
			return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_TABLENOTGIVENINFROMCLAUSE);	// Table not given in 'From' clause

	CComBSTR bstrBaseTable(bstrTable);

		MAKE_OLEDB_ERROR(SplitTableName(bstrTable));
		if (FAILED(pDataSource -> get_Class(bstrTable, &lIdent)))
			return OleDBError(DB_E_NOTABLE);			// Table does not exist
		_ASSERTE(0 != lIdent);

		RETURN_ERROR(FillColumnsFromIdent(pDataSource, lIdent, rlOrd, rlCustCount, bstrBaseTable));
	}
	return S_OK;
}

// Spalten für eine Objektklasse hinzufügen
HRESULT CGenerateColumnInfoBase::FillColumnsFromIdent (
	CTRiASOleDBSource *pDataSource, INT_PTR lIdent, ULONG &rlOrd, LONG &rlCustCount, 
	BSTR bstrBaseTable)
{
// zuerst Objektnummer, GUID und Geometrie hinzufügen
	RETURN_ERROR(FillObjNrColumn (pDataSource, rlOrd));
	RETURN_ERROR(FillObjGuidColumn (pDataSource, rlOrd));
	RETURN_ERROR(FillGeometryColumn (pDataSource, rlOrd, lIdent, bstrBaseTable));

// jetzt Objekteigenschaften 
CComPtr<ITRiASEnumNativeAttributes> Attribs;
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR(pDataSource -> get_Attributes(lIdent, &Attribs));
	MAKE_OLEDB_ERROR(Attribs -> get__NewEnum(&UnkEnum));

CComVariant v;
CComQIPtr<IEnumVARIANT> EnumAttribs(UnkEnum);

	_ASSERTE(EnumAttribs != NULL);
	for (EnumAttribs -> Reset(); S_OK == EnumAttribs -> Next(1, &v, NULL); /**/) {
		_ASSERTE(V_ISI4(&v));

	CComBSTR bstrName;
	INT_PTR lMCode = 0;

		MAKE_OLEDB_ERROR(pDataSource -> get_AttribName(V_I4(&v), &bstrName));
		if (FAILED(pDataSource -> get_Attribute (lIdent, bstrName, &lMCode)))
			continue;		// nur in Pbd definierte Objekteigenschaft
		_ASSERTE(V_I4(&v) == lMCode);
		RETURN_ERROR(AddIdentColumn (pDataSource, bstrName, lMCode, rlOrd, rlCustCount, bstrBaseTable));
	}
	return S_OK;
}

// Spaltenbeschreibung aus einzelnem Term berechnen
HRESULT CGenerateColumnInfoBase::FillColumnFromSingleTerm(
	CTRiASOleDBSource *pDataSource, IExpressionItem *pIItem, ULONG &rlOrd, LONG &rlCustCount,
	BSTR bstrAsName)
{
	_ASSERTE(NULL != pDataSource && NULL != pIItem);

EXPRESSIONITEM_TYPE rgItemType = EXPRESSIONITEM_TYPE_UNKNOWN;

	RETURN_FAILED_HRESULT(pIItem -> get_ItemType(&rgItemType));
	switch (rgItemType) {
	case EXPRESSIONITEM_TYPE_SELECTSTAR:			// select * from tablename
		return OleDBError(DB_E_ERRORSINCOMMAND);

	case EXPRESSIONITEM_TYPE_COLUMNIDENT:			// select ident from tablename 
		RETURN_ERROR(AddIdentColumn (pDataSource, pIItem, rlOrd, rlCustCount, bstrAsName));
		break;

	case EXPRESSIONITEM_TYPE_LITERALVALUE:			// select 'text' from tablename 
	case EXPRESSIONITEM_TYPE_AGGREGATEFUNCTION:		// select min(ident) from tablename
	case EXPRESSIONITEM_TYPE_DATEFUNCTION:
	case EXPRESSIONITEM_TYPE_MATHFUNCTION:
	case EXPRESSIONITEM_TYPE_GEOMETRYFUNCTION:
		RETURN_ERROR(AddFunctionColumn (pDataSource, pIItem, rlOrd, rlCustCount, bstrAsName));
		break;

	case EXPRESSIONITEM_TYPE_ARITOPERATOR:
	case EXPRESSIONITEM_TYPE_BOOLOPERATOR:
	case EXPRESSIONITEM_TYPE_COMPAREOPERATOR:
	case EXPRESSIONITEM_TYPE_NULLEXPRESSION:
	default:
		return OleDBError(DB_E_ERRORSINCOMMAND);
	}
	return S_OK;
}

// Spaltenbeschreibung aus Ausdruck berechnen
HRESULT CGenerateColumnInfoBase::FillColumnFromExpression(
	CTRiASOleDBSource *pDatasource, IGenericStack *pIStack, ULONG &rlOrd, LONG &rlCustCount,
	BSTR bstrAsName)
{
// Expression aus GenericStack erzeugen
	_ASSERTE(NULL != pIStack);
	_ASSERTE(m_TableAliases.IsInitialized());

	USES_CONVERSION;

CComPtr<ITRiASExpression> ExprTree;
CSQLExpression Expr(pDatasource, m_TableAliases, m_ColumnAliases);

	MAKE_OLEDB_ERROR(Expr.ComposeExpressionTree(pIStack, &ExprTree));

// Spalte definieren
CString strName;

	strName.Format(IDS_EXPRESSIONPREFIX, rlCustCount++);
	
CAtlColumnInfo col(strName, bstrAsName);
ULONG ulColSize = LONG_MAX;
DBTYPE rgType = DBTYPE_WSTR;
BYTE bPrec = ~0;

	RETURN_ERROR(ExprTree -> GetTypeInfo(&ulColSize, &rgType, &bPrec));

	col.iOrdinal = ++rlOrd;
	col.dwFlags = DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED; 
	col.ulColumnSize = ulColSize;
	col.wType = rgType;
	col.bPrecision = bPrec;
	col.bScale = ~0; 
	col.cbOffset = 0;

	if (!m_ColInfo.Add(col))
		return OleDBError(E_OUTOFMEMORY);

	MAKE_OLEDB_ERROR(m_ColumnAliases.AddAlias(A2OLE(strName), bstrAsName));

// Handlerobjekt für diese Spalte erzeugen und initialisieren
CComObject<CHandleExpression> *pExprHandler = NULL;

	MAKE_OLEDB_ERROR(CComObject<CHandleExpression>::CreateInstance(&pExprHandler));
	MAKE_OLEDB_ERROR(pExprHandler -> SetExpression(ExprTree));
	if (!m_ColInfo.Add(CComPtr<IHandleDataAccess>(pExprHandler)))
		return OleDBError(E_OUTOFMEMORY);

	return m_ColInfo.AddToBaseTables(CComBSTR(L""));
}

///////////////////////////////////////////////////////////////////////////////
// Spalten für spezielle Objekteigenschaften beschreiben (ObjNr, Guid, Geometrie)
HRESULT CGenerateColumnInfoBase::FillObjNrColumn (
	CTRiASOleDBSource *pDatasource, ULONG &rlOrd, BSTR bstrAsName)
{
CAtlColumnInfo col(IDS_OBJNRNAME, bstrAsName);

	col.iOrdinal = ++rlOrd;
	col.dwFlags = DBCOLUMNFLAGS_ISROWID|DBCOLUMNFLAGS_ISFIXEDLENGTH; 
	col.ulColumnSize = sizeof(DWORD);
	col.wType = DBTYPE_UI4;
	col.bPrecision = 10;
	col.bScale = ~0; 
	col.cbOffset = 0;

	if (!m_ColInfo.Add(col))
		return OleDBError(E_OUTOFMEMORY);

	MAKE_OLEDB_ERROR(m_ColumnAliases.AddAlias(IDS_OBJNRNAME, bstrAsName));

// Handlerobjekt für diese Spalte erzeugen und initialisieren
CComObject<CHandleBookmark> *pBookmark = NULL;

	MAKE_OLEDB_ERROR(CComObject<CHandleBookmark>::CreateInstance(&pBookmark));
	if (!m_ColInfo.Add(CComPtr<IHandleDataAccess>(pBookmark)))
		return OleDBError(E_OUTOFMEMORY);

	return m_ColInfo.AddToBaseTables(CComBSTR(L""));
}

HRESULT CGenerateColumnInfoBase::FillObjGuidColumn (
	CTRiASOleDBSource *pDatasource, ULONG &rlOrd, BSTR bstrAsName)
{
CAtlColumnInfo col(IDS_GUIDNAME, bstrAsName);

	col.iOrdinal = ++rlOrd;
	col.dwFlags = DBCOLUMNFLAGS_ISFIXEDLENGTH|DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED;		// |DBCOLUMNFLAGS_WRITE; 
	col.ulColumnSize = sizeof(GUID);
	col.wType = DBTYPE_GUID;
	col.bPrecision = ~0;
	col.bScale = ~0; 
	col.cbOffset = 0;

	if (!m_ColInfo.Add(col))
		return OleDBError(E_OUTOFMEMORY);

	MAKE_OLEDB_ERROR(m_ColumnAliases.AddAlias(IDS_GUIDNAME, bstrAsName));

// Handlerobjekt für diese Spalte erzeugen und initialisieren
CComObject<CHandleObjectGuid> *pGuid = NULL;

	MAKE_OLEDB_ERROR(CComObject<CHandleObjectGuid>::CreateInstance(&pGuid));
	if (!m_ColInfo.Add(CComPtr<IHandleDataAccess>(pGuid)))
		return OleDBError(E_OUTOFMEMORY);

	return m_ColInfo.AddToBaseTables(CComBSTR(L""));
}

HRESULT CGenerateColumnInfoBase::FillGeometryColumn (
	CTRiASOleDBSource *pDataSource, ULONG &rlOrd, INT_PTR lIdent, BSTR bstrBaseTable, 
	DWORD dwType, BSTR bstrAsName)
{
#if defined(_USE_PROP_GEOMETRYAS)
	if (DBPROPVAL_TRiAS_GEOMETRYCOLUMNS == pDataSource -> GetGeometryMode()) {
		_ASSERTE(0 == dwType);		// Geometrietyp nicht aus Tabellennamen

	// alle Geometrien in der jeweiligen Tabelle (Objektklasse), jedoch in 
	// 4 separaten Spalten
	DWORD dwTypes = 0;

		MAKE_OLEDB_ERROR(pDataSource -> get_Types (lIdent, &dwTypes));
		for (int i = 0; i < _countof(s_rgTypes); ++i) {
			if (!(s_rgTypes[i].dwType & dwTypes))
				continue;		// diesen Objekttyp gibt es in dieser Tabelle nicht

		CAtlColumnInfo col (s_rgTypes[i].pcoleGeomName, bstrAsName);

			col.iOrdinal = ++rlOrd;
			col.dwFlags = DBCOLUMNFLAGS_ISLONG|DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED;				// |DBCOLUMNFLAGS_WRITE; 
			col.ulColumnSize = ~0;
			col.wType = DBTYPE_BYTES;
			col.bPrecision = ~0;
			col.bScale = ~0; 
			col.cbOffset = 0;
			if (!m_ColInfo.Add(col))
				return OleDBError(E_OUTOFMEMORY);

			MAKE_OLEDB_ERROR(m_ColumnAliases.AddAlias(s_rgTypes[i].pcoleGeomName, bstrAsName));

		// Handlerobjekt für diese Spalte erzeugen und initialisieren
		CComObject<CHandleGeometry> *pGeom = NULL;

			MAKE_OLEDB_ERROR(CComObject<CHandleGeometry>::CreateInstance(&pGeom));
			if (!m_ColInfo.Add(CComPtr<IHandleDataAccess>(pGeom)))
				return OleDBError(E_OUTOFMEMORY);

			MAKE_OLEDB_ERROR(m_ColInfo.AddToBaseTables(bstrBaseTable));
		}
	} 
	else 
#endif // defined(_USE_PROP_GEOMETRYAS)
	{
		_ASSERTE(DBPROPVAL_TRiAS_GEOMETRYTABLES == pDataSource -> GetGeometryMode());

	// alle Objekte jedes der Objekttypen werden in jeweils einer eigenen Tabelle zusammen
	// gefaßt. Der TabellenName besteht aus Objektklassen-Kurztext und Objekttyp
	CAtlColumnInfo col (OLESTR("OGIS_GEOMETRY"), bstrAsName);

		col.iOrdinal = ++rlOrd;
		col.dwFlags = DBCOLUMNFLAGS_ISLONG|DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED;				// |DBCOLUMNFLAGS_WRITE; 
		col.ulColumnSize = ~0;
		col.wType = DBTYPE_BYTES;
		col.bPrecision = ~0;
		col.bScale = ~0; 
		col.cbOffset = 0;
		if (!m_ColInfo.Add(col))
			return OleDBError(E_OUTOFMEMORY);

		MAKE_OLEDB_ERROR(m_ColumnAliases.AddAlias(OLESTR("OGIS_GEOMETRY"), bstrAsName));

	// Handlerobjekt für diese Spalte erzeugen und initialisieren
	CComObject<CHandleGeometry> *pGeom = NULL;

		MAKE_OLEDB_ERROR(CComObject<CHandleGeometry>::CreateInstance(&pGeom));
		pGeom -> SetTargetType(dwType);
		if (!m_ColInfo.Add(CComPtr<IHandleDataAccess>(pGeom)))
			return OleDBError(E_OUTOFMEMORY);

		MAKE_OLEDB_ERROR(m_ColInfo.AddToBaseTables(bstrBaseTable));
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Spalte definieren, der einem Ident entspricht (Objekteigenschaft ?)

HRESULT CGenerateColumnInfoBase::AddIdentColumn (
	CTRiASOleDBSource *pDatasource, IExpressionItem *pIItem, ULONG &rlOrd, LONG &rlCustCount, 
	BSTR bstrAsName)
{
	_ASSERTE(ExpressionHasType(pIItem, EXPRESSIONITEM_TYPE_COLUMNIDENT));

CComQIPtr<IColumnIdent> ColId (pIItem);
CComBSTR bstrName, bstrTableName;

// sicherstellen, daß die Tabelle wirklich existiert
	MAKE_OLEDB_ERROR(ColId -> get_TableName(&bstrTableName));
	if (0 == bstrTableName.Length()) {
		if (0 == m_bstrSingleTable.Length()) {
		// da in TRiAS-Datenbanken alle Objektklassen identische Objekteigenschaften
		// besitzen, muß die gewünschte Tabelle __immer__ mit gegeben sein
			return OleDBError(DB_E_NOTABLE);		// Tabelle ist nicht gegeben
		}

	// da nur eine Tabelle gegeben ist, kann diese verwendet werden
		bstrTableName = m_bstrSingleTable;
	}

// Tabellennamen ggf. in Objektklasse/Objekttyp zerlegen
DWORD dwType = 0;

	bstrTableName = ResolveTableAlias(RemoveQuotes(bstrTableName));

CComBSTR bstrBaseTable (bstrTableName);

	MAKE_OLEDB_ERROR(SplitTableName(bstrTableName, &dwType));

// überprüfen, ob die gegebene Tabelle wirklich existiert
INT_PTR lIdent = 0;

	if (FAILED(pDatasource -> get_Class (bstrTableName, &lIdent)))
		return OleDBError(DB_E_NOTABLE);		// Tabelle existiert nicht

// überprüfen, ob die gegebene Spalte (Objekteigenschaft) wirklich existiert
INT_PTR lMCode = 0;

	MAKE_OLEDB_ERROR(ColId -> get_ColumnName(&bstrName));
	bstrName = RemoveQuotes(bstrName);

CComBSTR bstrObjNr, bstrGuid;		// spezielle Spalten gesondert gehandeln

	bstrObjNr.LoadString(IDS_OBJNRNAME);
	_ASSERTE(bstrObjNr.Length() > 0);
	if (bstrObjNr == bstrName) 
		return FillObjNrColumn(pDatasource, rlOrd, bstrAsName);

	bstrGuid.LoadString(IDS_GUIDNAME);
	_ASSERTE(bstrGuid.Length() > 0);
	if (bstrGuid == bstrName) 
		return FillObjGuidColumn(pDatasource, rlOrd, bstrAsName);

	if (!wcsncmp(OLESTR("OGIS_GEOMETRY"), bstrName, wcslen(OLESTR("OGIS_GEOMETRY"))))
		return FillGeometryColumn(pDatasource, rlOrd, lIdent, bstrBaseTable, dwType, bstrAsName);

// 'normale' Objekteigenschaft
	if (FAILED(pDatasource -> get_Attribute (lIdent, bstrName, &lMCode)))
		return OleDBError(DB_E_NOCOLUMN);

	MAKE_OLEDB_ERROR(AddIdentColumn (pDatasource, bstrName, lMCode, rlOrd, rlCustCount, bstrBaseTable, bstrAsName));
	return S_OK;
}

HRESULT CGenerateColumnInfoBase::AddIdentColumn(
	CTRiASOleDBSource *pDatasource, BSTR bstrName, INT_PTR lMCode, ULONG &rlOrd, LONG &rlCustCount, 
	BSTR bstrBaseTable, BSTR bstrAsName)
{
CAtlColumnInfo col (bstrName, bstrAsName, lMCode);

// normale Objekteigenschaft
	col.dwFlags = DBCOLUMNFLAGS_ISNULLABLE|DBCOLUMNFLAGS_MAYBENULL|DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED;		// |DBCOLUMNFLAGS_WRITE
	col.ulColumnSize = LONG_MAX;
	col.wType = DBTYPE_WSTR;
	col.iOrdinal = ++rlOrd;
	col.bPrecision = ~0;
	col.bScale = ~0; 
	col.cbOffset = 0;

	if (!m_ColInfo.Add(col))
		return OleDBError(E_OUTOFMEMORY);

	MAKE_OLEDB_ERROR(m_ColumnAliases.AddAlias(bstrName, bstrAsName));

// Handlerobjekt für diese Spalte erzeugen und initialisieren
CComObject<CHandleNativeAttribute> *pAttribute = NULL;

	MAKE_OLEDB_ERROR(CComObject<CHandleNativeAttribute>::CreateInstance(&pAttribute));
	MAKE_OLEDB_ERROR(pAttribute -> SetAttributeHandle (lMCode));
	if (!m_ColInfo.Add(CComPtr<IHandleDataAccess>(pAttribute)))
		return OleDBError(E_OUTOFMEMORY);

	return m_ColInfo.AddToBaseTables(bstrBaseTable);
}

///////////////////////////////////////////////////////////////////////////////
// Berechnete Spalte definieren
HRESULT CGenerateColumnInfoBase::AddFunctionColumn (
	CTRiASOleDBSource *pDatasource, IExpressionItem *pIItem, ULONG &rlOrd, LONG &rlCustCount,
	BSTR bstrAsName)
{
// Expression aus IExpressionItem erzeugen
	_ASSERTE(NULL != pIItem);
	_ASSERTE(m_TableAliases.IsInitialized());

	USES_CONVERSION;

CComPtr<ITRiASExpression> ExprTree;
CSQLExpression Expr(pDatasource, m_TableAliases, m_ColumnAliases);

	MAKE_OLEDB_ERROR(Expr.ComposeExpressionItem(pIItem, &ExprTree));

// Spalte definieren
CString strName;

	strName.Format(IDS_EXPRESSIONPREFIX, rlCustCount++);
	
CAtlColumnInfo col(strName, bstrAsName);

	col.iOrdinal = ++rlOrd;
	col.dwFlags = DBCOLUMNFLAGS_MAYDEFER|DBCOLUMNFLAGS_CACHEDEFERRED; 
	col.ulColumnSize = LONG_MAX;
	col.wType = DBTYPE_WSTR;
	col.bPrecision = ~0;
	col.bScale = ~0; 
	col.cbOffset = 0;

	if (!m_ColInfo.Add(col))
		return OleDBError(E_OUTOFMEMORY);

	MAKE_OLEDB_ERROR(m_ColumnAliases.AddAlias(A2OLE(strName), bstrAsName));

// Handlerobjekt für diese Spalte erzeugen und initialisieren
CComObject<CHandleExpression> *pExprHandler = NULL;

	MAKE_OLEDB_ERROR(CComObject<CHandleExpression>::CreateInstance(&pExprHandler));
	MAKE_OLEDB_ERROR(pExprHandler -> SetExpression(ExprTree));
	if (!m_ColInfo.Add(CComPtr<IHandleDataAccess>(pExprHandler)))
		return OleDBError(E_OUTOFMEMORY);

	return m_ColInfo.AddToBaseTables(CComBSTR(L""));
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob ein 'select [Table.]* from tablename ...' vorliegt
HRESULT CGenerateColumnInfoBase::SelectHasStar(
	CTRiASOleDBSource *pDataSource, IEnumVARIANT *pIEnum, bool *pfHasStar)
{
	_ASSERTE(NULL != pIEnum);
	_ASSERTE(NULL != pfHasStar);

// einfach alle durchgehen und nachsehen, ob EXPRESSIONITEM_TYPE_SELECTSTAR dabei ist
CComVariant vItem;

	for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &vItem, NULL) && !*pfHasStar; /**/) {
		_ASSERTE(V_ISDISPATCH(&vItem));

	CComQIPtr<IExpressionItem> Item = V_DISPATCH(&vItem);

		if (Item == NULL) 
			continue;

	EXPRESSIONITEM_TYPE rgItemType = EXPRESSIONITEM_TYPE_UNKNOWN;

		MAKE_OLEDB_ERROR(Item -> get_ItemType(&rgItemType));
		switch (rgItemType) {
		case EXPRESSIONITEM_TYPE_SELECTSTAR:	// select [Table.]* from tablename
			*pfHasStar = true;
			break;

		case EXPRESSIONITEM_TYPE_COLUMNIDENT:
			RETURN_ERROR(ItemHasStar (pDataSource, Item, pfHasStar));
			break;

		default:
			break;
		}
	}
	return S_OK;
}

// analysiert, ob ein SpaltenId als Tabelle.* gegeben ist
HRESULT CGenerateColumnInfoBase::ItemHasStar (
	CTRiASOleDBSource *pDataSource, IExpressionItem *pIItem, bool *pfHasStar)
{
	_ASSERTE(ExpressionHasType(pIItem, EXPRESSIONITEM_TYPE_COLUMNIDENT));

CComQIPtr<IColumnIdent> ColId = pIItem;
CComBSTR bstrName, bstrTableName;

// sicherstellen, daß die Tabelle wirklich existiert
	MAKE_OLEDB_ERROR(ColId -> get_TableName(&bstrTableName));
	if (0 == bstrTableName.Length()) {
		if (0 == m_bstrSingleTable.Length()) 
			return OleDBError(DB_E_NOTABLE);	// ohne Tabellenname müßte es ein EXPRESSION_TYPE_STAR sein

	// nur eine Tabelle gegeben, also diese verwenden
		bstrTableName = m_bstrSingleTable;
	}

// Tabellennamen ggf. in Objektklasse/Objekttyp zerlegen
	bstrTableName = ResolveTableAlias(RemoveQuotes(bstrTableName));
	if (!VerifyTableIsGiven (m_Parser, bstrTableName))
		return OleDBError(DB_E_ERRORSINCOMMAND, TRIASOLEDB_E_TABLENOTGIVENINFROMCLAUSE);

// Tabelle muß existieren und muß in der 'From' clause gegeben sein
INT_PTR lIdent = 0;

	MAKE_OLEDB_ERROR(SplitTableName(bstrTableName));
	if (FAILED(pDataSource -> get_Class (bstrTableName, &lIdent)))
		return OleDBError(DB_E_NOTABLE);		// Tabelle existiert nicht

	MAKE_OLEDB_ERROR(ColId -> get_ColumnName(&bstrName));

	*pfHasStar = bstrName.Length() > 0 && bstrName[0] == L'*';
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Wenn nur eine Tabelle in der Query gegeben ist, dann können die einzelnen
// Felder ohne die Tabellenspezifikation gegeben sein. Ansonsten müssen
// alle Spalten als 'Tabelle.Spalte' vorgegeben werden
HRESULT CGenerateColumnInfoBase::GetSingleTableName(ISelectStmt *pISelect)
{
	m_bstrSingleTable.Empty();

CComPtr<ITableIdentList> TableIdentList;

	MAKE_OLEDB_ERROR(pISelect -> get_TableIdentList(&TableIdentList));
	if (TableIdentList == NULL) return OleDBError(DB_E_ERRORSINCOMMAND);

long lTableCnt = 0;

	MAKE_OLEDB_ERROR(TableIdentList -> get_Count(&lTableCnt));
	if (lTableCnt > 1) return S_OK;

// es ist nur eine Tabelle gegeben
CComPtr<IUnknown> UnkEnum;

	MAKE_OLEDB_ERROR(TableIdentList -> get__NewEnum(&UnkEnum));

CComQIPtr<IEnumVARIANT> Tables(UnkEnum);
CComVariant v;

	_ASSERTE(Tables != NULL);

	MAKE_OLEDB_ERROR(Tables -> Reset()); 
	if (S_OK == Tables -> Next(1, &v, NULL)) {
		_ASSERTE(V_ISDISPATCH(&v));

	CComQIPtr<ITableIdent> Table (V_DISPATCH(&v));

		if (Table == NULL) 
			return OleDBError(E_UNEXPECTED);
		MAKE_OLEDB_ERROR(Table -> get_Name(&m_bstrSingleTable));
	} 
	else
		return OleDBError(E_UNEXPECTED);

	_ASSERTE(m_bstrSingleTable.Length() > 0);
	return S_OK;
}

