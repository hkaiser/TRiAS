/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: DateFunction.h $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:36p
 * Updated in $/Products/SmallParser
 * Added GetDateFunction property
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

// DateFunction.h : Declaration of the cDateFunction

#ifndef __DATEFUNCTION_H_
#define __DATEFUNCTION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cDateFunction
class ATL_NO_VTABLE cDateFunction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cDateFunction, &CLSID_DateFunction>,
	public ISupportErrorInfo,
	public IDispatchImpl<IDateFunction, &IID_IDateFunction, &LIBID_TRiASQL>
{
public:
	cDateFunction();
	CString GetAsString();
	void SetDateFunction( DATE_FUNCTION DateFunction );
	DATE_FUNCTION GetDateFunction();

protected:
	DATE_FUNCTION m_DateFunction;
public:

//	DECLARE_REGISTRY_RESOURCEID(IDR_DATEFUNCTION)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cDateFunction)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(IDateFunction)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDateFunction

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
		*pVal = EXPRESSIONITEM_TYPE_DATEFUNCTION;
		return S_OK;
		}



public:
	STDMETHOD(get_DateFunction)(/*[out, retval]*/ DATE_FUNCTION *pVal);
};

#endif //__DATEFUNCTION_H_
