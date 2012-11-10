/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: OrderByList.h $ 
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

// OrderByList.h : Declaration of the cOrderByObjList

#ifndef __ORDERBYLIST_H_
#define __ORDERBYLIST_H_

#include "resource.h"       // main symbols
#include "OrderByObj.h"       // main symbols


typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<IOrderByObjList, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> IOrderByColl;

/////////////////////////////////////////////////////////////////////////////
// cOrderByObjList
class ATL_NO_VTABLE cOrderByObjList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cOrderByObjList, &CLSID_OrderByObjList>,
	public ISupportErrorInfo,
	public IDispatchImpl<IOrderByColl, &IID_IOrderByObjList, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cOrderByObjList();

	void AddItem( cOrderByObj *pIdent );

//	DECLARE_REGISTRY_RESOURCEID(IDR_ORDERBYLIST)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cOrderByObjList)
		COM_INTERFACE_ENTRY(IOrderByObjList)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOrderByList
public:
};

#endif //__ORDERBYLIST_H_
