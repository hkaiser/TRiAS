/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: MathFunction.h $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:23p
 * Updated in $/Products/SmallParser
 * Added MathFunction property
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

// MathFunction.h : Declaration of the cMathFunction

#ifndef __MATHFUNCTION_H_
#define __MATHFUNCTION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cMathFunction
class ATL_NO_VTABLE cMathFunction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cMathFunction, &CLSID_MathFunction>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMathFunction, &IID_IMathFunction, &LIBID_TRiASQL>
{
public:
	cMathFunction();
	
	CString GetAsString();
	void SetMathFunction( MATH_FUNCTION MathFunction );

protected:
	MATH_FUNCTION m_MathFunction;
public:

//	DECLARE_REGISTRY_RESOURCEID(IDR_MATHFUNCTION)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cMathFunction)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(IMathFunction)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMathFunction

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
		*pVal = EXPRESSIONITEM_TYPE_MATHFUNCTION;
		return S_OK;
		}


public:
	STDMETHOD(get_MathFunction)(/*[out, retval]*/ MATH_FUNCTION *pVal);
};

#endif //__MATHFUNCTION_H_
