/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: ColumnIdentList.h $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 8:47p
 * Updated in $/Products/TRiASQL
 * Fixing headers so all code is in CPP-files
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/TRiASQL
*/

// ColumnIdentList.h : Declaration of the cColumnIdentList

#ifndef __COLUMNIDENTLIST_H_
#define __COLUMNIDENTLIST_H_

#include "resource.h"       // main symbols
#include "ColumnIdent.h"

/////////////////////////////////////////////////////////////////////////////
// cTableIdentList
typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<IColumnIdentList, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> IColumnColl;

/////////////////////////////////////////////////////////////////////////////
// cColumnIdentList
class ATL_NO_VTABLE cColumnIdentList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cColumnIdentList, &CLSID_ColumnIdentList>,
	public ISupportErrorInfo,
	public IDispatchImpl<IColumnColl, &IID_IColumnIdentList, &LIBID_TRiASQL>
{
public:
	cColumnIdentList();
	void AddItem( cColumnIdent *pIdent );

//	DECLARE_REGISTRY_RESOURCEID(IDR_COLUMNIDENTLIST)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cColumnIdentList)
		COM_INTERFACE_ENTRY(IColumnIdentList)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IColumnIdentList
public:
};

#endif //__COLUMNIDENTLIST_H_
