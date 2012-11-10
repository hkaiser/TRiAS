/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: CreateTableItemList.h $ 
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

// CreateTableItemList.h : Declaration of the cCreateTableItemList

#ifndef __CREATETABLEITEMLIST_H_
#define __CREATETABLEITEMLIST_H_

#include "resource.h"       // main symbols
#include "CreateTableItem.h"

typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<ICreateTableItemList, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> ICreateList;


/////////////////////////////////////////////////////////////////////////////
// cCreateTableItemList
class ATL_NO_VTABLE cCreateTableItemList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cCreateTableItemList, &CLSID_CreateTableItemList>,
	public ISupportErrorInfo,
	public IDispatchImpl<ICreateList, &IID_ICreateTableItemList, &LIBID_TRiASQL>
{
public:
	cCreateTableItemList();
	void AddItem( cCreateTableItem *pIdent );


//	DECLARE_REGISTRY_RESOURCEID(IDR_CREATETABLEITEMLIST)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cCreateTableItemList)
		COM_INTERFACE_ENTRY(ICreateTableItemList)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICreateTableItemList
public:
};

#endif //__CREATETABLEITEMLIST_H_
