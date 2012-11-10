/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: GroupByObjList.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// GroupByObjList.h : Declaration of the cGroupByObjList

#ifndef __GROUPBYOBJLIST_H_
#define __GROUPBYOBJLIST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cTableIdentList
typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<IGroupByObjList, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> IGroupByColl;

/////////////////////////////////////////////////////////////////////////////
// cGroupByObjList
class ATL_NO_VTABLE cGroupByObjList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cGroupByObjList, &CLSID_GroupByObjList>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGroupByColl, &IID_IGroupByObjList, &LIBID_TRiASQL>
{
public:
	cGroupByObjList()
	{
	}
//	void Initialize( CGroupByListPtr pList );
//	CGroupByListPtr m_pList;


DECLARE_REGISTRY_RESOURCEID(IDR_GROUPBYOBJLIST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(cGroupByObjList)
	COM_INTERFACE_ENTRY(IGroupByObjList)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGroupByObjList
public:
};

#endif //__GROUPBYOBJLIST_H_
