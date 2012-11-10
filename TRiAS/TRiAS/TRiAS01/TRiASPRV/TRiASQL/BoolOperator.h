/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: BoolOperator.h $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:45p
 * Updated in $/Products/SmallParser
 * Added BoolOperator property
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// BoolOperator.h : Declaration of the cBoolOperator

#ifndef __BOOLOPERATOR_H_
#define __BOOLOPERATOR_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cBoolOperator
class ATL_NO_VTABLE cBoolOperator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cBoolOperator, &CLSID_BoolOperator>,
	public ISupportErrorInfo,
	public IDispatchImpl<IBoolOperator, &IID_IBoolOperator, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cBoolOperator();

	CString GetAsString();
	void SetBoolOperator( BOOL_OPERATOR BoolOperator );

protected:
	BOOL_OPERATOR m_BoolOperator;

public:


//	DECLARE_REGISTRY_RESOURCEID(IDR_BOOLOPERATOR)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cBoolOperator)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(IBoolOperator)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBoolOperator

//IExpressionItem
	STDMETHOD(get_AsString)( BSTR *bstrRet );
	STDMETHOD(get_ItemType)(EXPRESSIONITEM_TYPE *pVal);


public:
	STDMETHOD(get_BoolOperator)(/*[out, retval]*/ BOOL_OPERATOR *pVal);
};

#endif //__BOOLOPERATOR_H_
