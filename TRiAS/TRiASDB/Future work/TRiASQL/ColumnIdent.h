/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: ColumnIdent.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// ColumnIdent.h : Declaration of the cColumnIdent

#ifndef __COLUMNIDENT_H_
#define __COLUMNIDENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cColumnIdent
class ATL_NO_VTABLE cColumnIdent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cColumnIdent, &CLSID_ColumnIdent>,
	public ISupportErrorInfo,
	public IDispatchImpl<IColumnIdent, &IID_IColumnIdent, &LIBID_TRiASQL>
{
public:
	cColumnIdent();

	CString GetTableName();
	void SetTableName( const TCHAR *szName );
	CString GetColumnName();
	void SetColumnName( const TCHAR *szName );
	void SetName( const TCHAR *szName );


protected:
	CString m_strTableName;
	CString m_strColumnName;

public:

//DECLARE_REGISTRY_RESOURCEID(IDR_COLUMNIDENT)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cColumnIdent)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(IColumnIdent)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IColumnIdent
public:
	STDMETHOD(get_ColumnName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_TableName)(/*[out, retval]*/ BSTR *pVal);


//IExpressionItem
	STDMETHOD(get_AsString)( BSTR *bstrRet );
	STDMETHOD(get_ItemType)(EXPRESSIONITEM_TYPE *pVal);

};

#endif //__COLUMNIDENT_H_
