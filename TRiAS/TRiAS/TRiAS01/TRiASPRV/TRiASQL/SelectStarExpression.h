/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: SelectStarExpression.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// SelectStarExpression.h : Declaration of the cSelectStarExpression

#ifndef __SELECTSTAREXPRESSION_H_
#define __SELECTSTAREXPRESSION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cSelectStarExpression
class ATL_NO_VTABLE cSelectStarExpression : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cSelectStarExpression, &CLSID_SelectStarExpression>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISelectStarExpression, &IID_ISelectStarExpression, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cSelectStarExpression();

	CString GetAsString();

//	DECLARE_REGISTRY_RESOURCEID(IDR_SELECTSTAREXPRESSION)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cSelectStarExpression)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(ISelectStarExpression)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISelectStarExpression


// IExpressionItem
	STDMETHOD(get_AsString)( BSTR *bstrRet );
	STDMETHOD(get_ItemType)(EXPRESSIONITEM_TYPE *pVal);


public:
};

#endif //__SELECTSTAREXPRESSION_H_
