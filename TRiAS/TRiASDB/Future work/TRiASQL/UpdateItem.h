/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: UpdateItem.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// UpdateItem.h : Declaration of the cUpdateItem

#ifndef __UPDATEITEM_H_
#define __UPDATEITEM_H_

#include "resource.h"       // main symbols
#include "ColumnIdent.h"       // main symbols
#include "GenericStack.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cUpdateItem
class ATL_NO_VTABLE cUpdateItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cUpdateItem, &CLSID_UpdateItem>,
	public ISupportErrorInfo,
	public IDispatchImpl<IUpdateItem, &IID_IUpdateItem, &LIBID_TRiASQL>
{
public:
	cUpdateItem();
	~cUpdateItem();
	void Clear();

	CComObject<cColumnIdent>			*m_pColumnIdent;
	CComObject<cGenericStack>			*m_pExpressionStack;


//	DECLARE_REGISTRY_RESOURCEID(IDR_UPDATEITEM)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cUpdateItem)
		COM_INTERFACE_ENTRY(IUpdateItem)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUpdateItem
public:
	STDMETHOD(get_ExpressionStack)(/*[out, retval]*/ IGenericStack* *pVal);
	STDMETHOD(get_ColumnIdent)(/*[out, retval]*/ IColumnIdent* *pVal);
};

#endif //__UPDATEITEM_H_
