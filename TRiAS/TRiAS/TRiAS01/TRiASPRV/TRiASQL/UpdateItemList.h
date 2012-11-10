/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: UpdateItemList.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// UpdateItemList.h : Declaration of the cUpdateItemList

#ifndef __UPDATEITEMLIST_H_
#define __UPDATEITEMLIST_H_

#include "resource.h"       // main symbols
#include "UpdateItem.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cUpdateItemList
typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<IUpdateItemList, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> IUpdateItemColl;

class ATL_NO_VTABLE cUpdateItemList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cUpdateItemList, &CLSID_UpdateItemList>,
	public ISupportErrorInfo,
	public IDispatchImpl<IUpdateItemColl, &IID_IUpdateItemList, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cUpdateItemList();
	~cUpdateItemList();



	void AddItem( cUpdateItem *pIdent );

//	DECLARE_REGISTRY_RESOURCEID(IDR_UPDATEITEMLIST)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cUpdateItemList)
		COM_INTERFACE_ENTRY(IUpdateItemList)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUpdateItemList
public:
};

#endif //__UPDATEITEMLIST_H_
