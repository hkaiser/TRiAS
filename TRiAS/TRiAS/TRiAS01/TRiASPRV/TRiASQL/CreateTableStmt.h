/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: CreateTableStmt.h $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 8:47p
 * Updated in $/Products/SmallParser
 * Fixing headers so all code is in CPP-files
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// CreateTableStmt.h : Declaration of the cCreateTableStmt

#ifndef __CREATETABLESTMT_H_
#define __CREATETABLESTMT_H_

#include "resource.h"       // main symbols
#include "Parser\ParseTree.h"       // main symbols
#include "TableIdent.h"
#include "CreateTableItemList.h"

/////////////////////////////////////////////////////////////////////////////
// cCreateTableStmt
class ATL_NO_VTABLE cCreateTableStmt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cCreateTableStmt, &CLSID_CreateTableStmt>,
	public ISupportErrorInfo,
	public IDispatchImpl<ICreateTableStmt, &IID_ICreateTableStmt, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cCreateTableStmt();
	~cCreateTableStmt();
	void Clear();

	
	void InitializeFromParseTree( CParseTree *pTree );

	CComObject<cTableIdent> *m_pTableIdent;
	CComObject<cCreateTableItemList> *m_pCreateTableItemList;

//	DECLARE_REGISTRY_RESOURCEID(IDR_CREATETABLESTMT)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cCreateTableStmt)
		COM_INTERFACE_ENTRY(ICreateTableStmt)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICreateTableStmt
public:
	STDMETHOD(get_CreateTableItemList)(/*[out, retval]*/ ICreateTableItemList* *pVal);
	STDMETHOD(get_TableIdent)(/*[out, retval]*/ ITableIdent * *pVal);
};

#endif //__CREATETABLESTMT_H_
