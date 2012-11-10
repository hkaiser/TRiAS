/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: LiteralValue.h $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:31p
 * Updated in $/Products/SmallParser
 * Added DataType property
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

// LiteralValue.h : Declaration of the cLiteralValue

#ifndef __LITERALVALUE_H_
#define __LITERALVALUE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cLiteralValue
class ATL_NO_VTABLE cLiteralValue : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cLiteralValue, &CLSID_LiteralValue>,
	public ISupportErrorInfo,
	public IDispatchImpl<ILiteralValue, &IID_ILiteralValue, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cLiteralValue();

	CString GetAsString();

	void SetDataType( PARSER_DATATYPE DataType );
	void SetData( const TCHAR *szText );
	CString GetData();
	PARSER_DATATYPE GetDataType();

protected:
	PARSER_DATATYPE m_DataType;
	CString m_strData;
public:

//	DECLARE_REGISTRY_RESOURCEID(IDR_LITERALVALUE)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cLiteralValue)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(ILiteralValue)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILiteralValue

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
		*pVal = EXPRESSIONITEM_TYPE_LITERALVALUE;
		return S_OK;
		}

public:
	STDMETHOD(get_DataType)(/*[out, retval]*/ PARSER_DATATYPE *pVal);
};

#endif //__LITERALVALUE_H_
