/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: AritOperator.h $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:45p
 * Updated in $/Products/SmallParser
 * Added AritOperator property
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// AritOperator.h : Declaration of the cAritOperator

#ifndef __ARITOPERATOR_H_
#define __ARITOPERATOR_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cAritOperator
class ATL_NO_VTABLE cAritOperator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cAritOperator, &CLSID_AritOperator>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAritOperator, &IID_IAritOperator, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cAritOperator();

	CString GetAsString();

	void SetAritOperator( ARIT_OPERATOR AritOperator );

protected:
	ARIT_OPERATOR m_AritOperator;

public:

//	DECLARE_REGISTRY_RESOURCEID(IDR_ARITOPERATOR)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cAritOperator)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(IAritOperator)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAritOperator



//IExpressionItem
	STDMETHOD(get_AsString)( BSTR *bstrRet );
	STDMETHOD(get_ItemType)(EXPRESSIONITEM_TYPE *pVal);

public:
	STDMETHOD(get_AritOperator)(/*[out, retval]*/ ARIT_OPERATOR *pVal);
};

#endif //__ARITOPERATOR_H_
