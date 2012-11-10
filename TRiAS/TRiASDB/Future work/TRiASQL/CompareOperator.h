/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: CompareOperator.h $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:38p
 * Updated in $/Products/SmallParser
 * Added CompareOperator property
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

// CompareOperator.h : Declaration of the cCompareOperator

#ifndef __COMPAREOPERATOR_H_
#define __COMPAREOPERATOR_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cCompareOperator
class ATL_NO_VTABLE cCompareOperator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cCompareOperator, &CLSID_CompareOperator>,
	public ISupportErrorInfo,
	public IDispatchImpl<ICompareOperator, &IID_ICompareOperator, &LIBID_TRiASQL>
{
public:
	cCompareOperator();

	CString GetAsString();

	void SetCompareOperator( COMPARE_OPERATOR CompareOperator );

protected:
	COMPARE_OPERATOR m_CompareOperator;

public:

//	DECLARE_REGISTRY_RESOURCEID(IDR_COMPAREOPERATOR)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cCompareOperator)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(ICompareOperator)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICompareOperator

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
		*pVal = EXPRESSIONITEM_TYPE_COMPAREOPERATOR;
		return S_OK;
		}


public:
	STDMETHOD(get_CompareOperator)(/*[out, retval]*/ COMPARE_OPERATOR *pVal);
};

#endif //__COMPAREOPERATOR_H_
