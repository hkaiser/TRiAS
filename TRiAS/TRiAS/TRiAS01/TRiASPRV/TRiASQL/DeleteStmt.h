/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: DeleteStmt.h $ 
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

// DeleteStmt.h : Declaration of the cDeleteStmt

#ifndef __DELETESTMT_H_
#define __DELETESTMT_H_

#include "resource.h"       // main symbols
#include "Parser\ParseTree.h"       // main symbols
#include "TableIdent.h"
#include "GenericStack.h"

/////////////////////////////////////////////////////////////////////////////
// cDeleteStmt
class ATL_NO_VTABLE cDeleteStmt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cDeleteStmt, &CLSID_DeleteStmt>,
	public ISupportErrorInfo,
	public IDispatchImpl<IDeleteStmt, &IID_IDeleteStmt, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cDeleteStmt();
	~cDeleteStmt();

	void Clear();

	void InitializeFromParseTree( CParseTree *pTree );
	CComObject<cTableIdent>			*m_pTableIdent;
	CComObject<cGenericStack>		*m_pWhereExpressionStack;


//	DECLARE_REGISTRY_RESOURCEID(IDR_DELETESTMT)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cDeleteStmt)
		COM_INTERFACE_ENTRY(IDeleteStmt)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDeleteStmt
public:
	STDMETHOD(get_WhereExpressionStack)(/*[out, retval]*/ IGenericStack* *pVal);
	STDMETHOD(get_TableIdent)(/*[out, retval]*/ ITableIdent* *pVal);
};

#endif //__DELETESTMT_H_
