/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: UpdateStmt.h $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:18p
 * Updated in $/Products/SmallParser
 * Added WhereExpressionStack property
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

// UpdateStmt.h : Declaration of the cUpdateStmt

#ifndef __UPDATESTMT_H_
#define __UPDATESTMT_H_

#include "resource.h"       // main symbols
#include "TableIdent.h"
#include "UpdateItemList.h"
#include "GenericStack.h"       // main symbols
#include "parser\parsetree.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cUpdateStmt
class ATL_NO_VTABLE cUpdateStmt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cUpdateStmt, &CLSID_UpdateStmt>,
	public ISupportErrorInfo,
	public IDispatchImpl<IUpdateStmt, &IID_IUpdateStmt, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cUpdateStmt();
	~cUpdateStmt();
	void Clear();

protected:
	CComObject<cGenericStack>			*m_pWhereExpressionStack;
	CComObject<cTableIdent>			*m_pTableIdent;
	CComObject<cUpdateItemList>			*m_pUpdateItemList;

public:
	void InitializeFromParseTree( CParseTree *pTree );


//	DECLARE_REGISTRY_RESOURCEID(IDR_UPDATESTMT)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cUpdateStmt)
		COM_INTERFACE_ENTRY(IUpdateStmt)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUpdateStmt
public:
	STDMETHOD(get_WhereExpressionStack)(/*[out, retval]*/ IGenericStack* *pVal);
	STDMETHOD(get_UpdateItemList)(/*[out, retval]*/ IUpdateItemList* *pVal);
	STDMETHOD(get_TableIdent)(/*[out, retval]*/ ITableIdent* *pVal);
};

#endif //__UPDATESTMT_H_
