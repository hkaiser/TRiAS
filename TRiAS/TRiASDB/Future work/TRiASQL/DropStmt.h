/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: DropStmt.h $ 
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

// DropStmt.h : Declaration of the cDropStmt

#ifndef __DROPSTMT_H_
#define __DROPSTMT_H_

#include "resource.h"       // main symbols
#include "Parser\ParseTree.h"       // main symbols
#include "TableIdent.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cDropStmt
class ATL_NO_VTABLE cDropStmt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cDropStmt, &CLSID_DropStmt>,
	public ISupportErrorInfo,
	public IDispatchImpl<IDropStmt, &IID_IDropStmt, &LIBID_TRiASQL>
{
public:
	cDropStmt();
	~cDropStmt();

	void Clear();

	void InitializeFromParseTree( CParseTree *pTree );
	CComObject<cTableIdent>			*m_pTableIdent;

//	DECLARE_REGISTRY_RESOURCEID(IDR_DROPSTMT)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cDropStmt)
		COM_INTERFACE_ENTRY(IDropStmt)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDropStmt
public:
	STDMETHOD(get_TableIdent)(/*[out, retval]*/ ITableIdent* *pVal);
};

#endif //__DROPSTMT_H_
