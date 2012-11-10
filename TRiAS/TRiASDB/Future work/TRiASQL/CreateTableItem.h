/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: CreateTableItem.h $ 
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

// CreateTableItem.h : Declaration of the cCreateTableItem

#ifndef __CREATETABLEITEM_H_
#define __CREATETABLEITEM_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cCreateTableItem
class ATL_NO_VTABLE cCreateTableItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cCreateTableItem, &CLSID_CreateTableItem>,
	public ISupportErrorInfo,
	public IDispatchImpl<ICreateTableItem, &IID_ICreateTableItem, &LIBID_TRiASQL>
{
public:
	cCreateTableItem();

	int m_nDataLength;
	CString m_strColumnName;
	PARSER_DATATYPE m_DataType;

//DECLARE_REGISTRY_RESOURCEID(IDR_CREATETABLEITEM)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cCreateTableItem)
		COM_INTERFACE_ENTRY(ICreateTableItem)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICreateTableItem
public:
	STDMETHOD(get_DataType)(/*[out, retval]*/ PARSER_DATATYPE *pVal);
	STDMETHOD(get_ColName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_DataLength)(/*[out, retval]*/ short *pVal);
};

#endif //__CREATETABLEITEM_H_
