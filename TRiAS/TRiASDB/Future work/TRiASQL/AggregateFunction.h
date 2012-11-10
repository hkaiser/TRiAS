/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: AggregateFunction.h $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:44p
 * Updated in $/Products/SmallParser
 * Added AggregateFunction property
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// AggregateFunction.h : Declaration of the cAggregateFunction

#ifndef __AGGREGATEFUNCTION_H_
#define __AGGREGATEFUNCTION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cAggregateFunction
class ATL_NO_VTABLE cAggregateFunction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cAggregateFunction, &CLSID_AggregateFunction>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAggregateFunction, &IID_IAggregateFunction, &LIBID_TRiASQL>
{
public:
	cAggregateFunction();

////// Internal functions
	void SetAggregateFunction( AGGREGATE_FUNCTION AggregateFunction );
	CString GetAsString();

protected:
	AGGREGATE_FUNCTION m_AggregateFunction;

public:

//DECLARE_REGISTRY_RESOURCEID(IDR_AGGREGATEFUNCTION)
	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cAggregateFunction)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(IAggregateFunction)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAggregateFunction


//IExpressionItem
	STDMETHOD(get_AsString)( BSTR *bstrRet );
	STDMETHOD(get_ItemType)(EXPRESSIONITEM_TYPE *pVal);


public:
	STDMETHOD(get_AggregateFunction)(/*[out, retval]*/ AGGREGATE_FUNCTION *pVal);
};

#endif //__AGGREGATEFUNCTION_H_
