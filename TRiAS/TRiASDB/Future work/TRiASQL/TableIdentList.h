/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: TableIdentList.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// TableIdentList.h : Declaration of the cTableIdentList

#ifndef __TABLEIDENTLIST_H_
#define __TABLEIDENTLIST_H_

#include "resource.h"       // main symbols
#include "TableIdent.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cTableIdentList
typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<ITableIdentList, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> ITableColl;

class ATL_NO_VTABLE cTableIdentList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cTableIdentList, &CLSID_TableIdentList>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITableColl, &IID_ITableIdentList, &LIBID_TRiASQL>
{
public:
	cTableIdentList();
	~cTableIdentList();

	void AddItem( cTableIdent *pIdent );


//	DECLARE_REGISTRY_RESOURCEID(IDR_TABLEIDENTLIST)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cTableIdentList)
		COM_INTERFACE_ENTRY(ITableIdentList)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITableIdentList
public:
//	STDMETHOD(get__NewEnum)(/*[out, retval]*/ LPUNKNOWN *pVal);
};

#endif //__TABLEIDENTLIST_H_
