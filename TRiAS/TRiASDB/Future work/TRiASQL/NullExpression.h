/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: NullExpression.h $ 
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

// NullExpression.h : Declaration of the cNullExpression

#ifndef __NULLEXPRESSION_H_
#define __NULLEXPRESSION_H_

#include "resource.h"       // main symbols
#include "TRiASQL.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cNullExpression
class ATL_NO_VTABLE cNullExpression : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cNullExpression, &CLSID_NullExpression>,
	public ISupportErrorInfo,
	public IDispatchImpl<INullExpression, &IID_INullExpression, &LIBID_TRiASQL>
{
public:
	cNullExpression();

//Internal function
	CString GetAsString();


//	DECLARE_REGISTRY_RESOURCEID(IDR_NULLEXPRESSION)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cNullExpression)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(INullExpression)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INullExpression

//IExpressionItem
	STDMETHOD(get_AsString)( BSTR *bstrRet )
		{
		CString strName;
		
		CComBSTR bstrRet2 = GetAsString();
		*bstrRet = bstrRet2.Detach();
		return S_OK;
		}
	STDMETHOD(get_ItemType)(EXPRESSIONITEM_TYPE *pVal)
		{
		*pVal = EXPRESSIONITEM_TYPE_NULLEXPRESSION;
		return S_OK;
		}


public:
};

#endif //__NULLEXPRESSION_H_
